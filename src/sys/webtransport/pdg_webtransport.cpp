#include "pdg_webtransport.h"
#include "pdg_webtransport_native.h"
#include <picoquic.h>
#include <picoquic_utils.h>
#include <pico_webtransport.h>
#include <tls_api.h>
#include <ptls_mbedtls.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/sha256.h>
#include <cJSON.h>
#include <atomic>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <cmath>
#include <exception>
#include <deque>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
// Exported by the pinned backend, but omitted from its public header.
extern "C" ptls_mbedtls_verify_certificate_t* ptls_mbedssl_init_verify_certificate_complete(
    mbedtls_x509_crt*, mbedtls_x509_crl*,
    int (*)(void*, mbedtls_x509_crt*, int, uint32_t*), void*);
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <wincrypt.h>
using Socket = SOCKET;
static void closeSocket(Socket fd) { closesocket(fd); }
#else
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
using Socket = int;
static void closeSocket(Socket fd) { close(fd); }
#endif
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#endif
namespace {
using Json = std::unique_ptr<cJSON, decltype(&cJSON_Delete)>;
Json object() { return Json(cJSON_CreateObject(), cJSON_Delete); }
std::string text(cJSON* j, const char* key, const char* fallback = "") {
    auto* value = cJSON_GetObjectItemCaseSensitive(j, key);
    return cJSON_IsString(value) ? value->valuestring : fallback;
}
double number(cJSON* j, const char* key, double fallback) {
    auto* value = cJSON_GetObjectItemCaseSensitive(j, key);
    return cJSON_IsNumber(value) ? value->valuedouble : fallback;
}
void string(cJSON* j, const char* key, const std::string& value) { cJSON_AddStringToObject(j, key, value.c_str()); }
std::string encode(cJSON* j) { char* raw=cJSON_PrintUnformatted(j); std::string out=raw?raw:"null"; cJSON_free(raw); return out; }
Json error(const char* code, const std::string& message) {
    auto j=object();string(j.get(),"code",code);string(j.get(),"message",message);string(j.get(),"transport","webtransport");return j;
}
uint64_t now() { return picoquic_current_time(); }
struct Endpoint { std::string host; uint16_t port=0; };
Endpoint endpoint(const sockaddr* address) {
    char host[NI_MAXHOST]={}; char port[NI_MAXSERV]={};
    if (address && !getnameinfo(address,address->sa_family==AF_INET?sizeof(sockaddr_in):sizeof(sockaddr_in6),host,sizeof(host),port,sizeof(port),NI_NUMERICHOST|NI_NUMERICSERV))
        return {host,static_cast<uint16_t>(std::stoi(port))};
    return {};
}
void addEndpoint(cJSON* j,const char* key,Endpoint value) {
    auto ep=object();string(ep.get(),"address",value.host);cJSON_AddNumberToObject(ep.get(),"port",value.port);cJSON_AddItemToObject(j,key,ep.release());
}
struct Event { std::string type, json; std::vector<uint8_t> bytes; };
struct Engine;
struct State {
    unsigned id=0; size_t limit=4*1024*1024, incoming=0, outgoing=0;
    std::atomic<bool> closed{false}, stopping{false}, killQueued{false};
    std::atomic<bool> ready{false};
    bool announced=false, detached=false, certificateFailed=false;
    size_t inflight=0, pendingWrites=0;
    std::deque<Event> events;
    Engine* engine=nullptr; // Worker thread only below this line.
    picoquic_cnx_t* connection=nullptr;
    h3zero_callback_ctx_t* h3=nullptr;
    h3zero_stream_ctx_t* control=nullptr;
    uint64_t reliable=UINT64_MAX, deadline=0, endDeadline=0;
    size_t offset=0;
    std::deque<std::vector<uint8_t>> reliableWrites, datagrams;
};
struct Options {
    bool server=false;
    std::string host,path="/pdg",cert,key,ca;
    uint16_t port=0;
    size_t limit=4*1024*1024,maxConnections=1024,maxPerIP=32,maxPerOrigin=1024,maxPerMinute=120;
    uint64_t timeout=5000000, idle=30000000;
    std::vector<std::string> origins,hashes;
};
struct Engine {
    Options options;
    std::shared_ptr<State> owner;
    Socket socket=-1;
    sockaddr_storage local={};
    picoquic_quic_t* quic=nullptr;
    picohttp_server_path_item_t path={};
    picohttp_server_parameters_t http={};
    std::map<unsigned,std::shared_ptr<State>> sessions;
    std::map<std::string,std::pair<uint64_t,size_t>> attempts;
    std::map<unsigned,std::pair<std::string,std::string>> admissions;
    uint64_t closingDeadline=0;
    bool accepting=true;
    ~Engine() { if(quic)picoquic_free(quic);if(socket!=static_cast<Socket>(-1))closeSocket(socket); }
};
struct Manager {
#ifdef _WIN32
    struct SocketRuntime {
        SocketRuntime(){WSADATA data;WSAStartup(MAKEWORD(2,2),&data);}
        ~SocketRuntime(){WSACleanup();}
    } socketRuntime;
#endif
    std::mutex mutex;std::condition_variable wake;
    std::map<unsigned,std::shared_ptr<State>> states;
    std::deque<std::function<void()>> work;
    std::deque<std::function<void()>> lookups;
    std::vector<std::unique_ptr<Engine>> engines;
    unsigned next=1;bool stop=false;
    std::thread thread, resolver;
    Manager();~Manager();
};
Manager& manager() { static Manager m;return m; }
std::shared_ptr<State> find(unsigned id) {
    auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
    auto it=m.states.find(id);return it==m.states.end()?nullptr:it->second;
}
std::shared_ptr<State> create(size_t limit,uint64_t deadline=0) {
    auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
    if(m.states.size()>=4096)return nullptr;
    auto s=std::make_shared<State>();s->id=m.next++;s->limit=limit;s->deadline=deadline;m.states.emplace(s->id,s);return s;
}
void enqueue(std::function<void()> fn) {
    auto& m=manager();{std::lock_guard<std::mutex> lock(m.mutex);m.work.push_back(std::move(fn));}m.wake.notify_one();
}
void finish(State* s,const char* code=nullptr,const std::string& message={}) {
    auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
    if(s->closed)return;s->closed=true;s->stopping=true;
    if(code){auto j=error(code,message);s->events.push_back({"error",encode(j.get()),{}});}
    s->events.push_back({"close","null",{}});
}
void push(State* s,Event event) {
    bool overflow=false;
    {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
        if(s->closed)return;
        overflow=event.bytes.size()>s->limit-s->incoming || s->events.size()>=256;
        if(!overflow){s->incoming+=event.bytes.size();s->events.push_back(std::move(event));}
    }
    if(overflow){finish(s,"ERR_BACKPRESSURE","Incoming WebTransport buffer limit exceeded");if(s->connection)picoquic_close(s->connection,1);}
}
Json info(State* s) {
    auto j=object();sockaddr* address=nullptr;
    picoquic_get_peer_addr(s->connection,&address);addEndpoint(j.get(),"remote",endpoint(address));
    picoquic_get_local_addr(s->connection,&address);auto local=endpoint(address);
    if(!local.port)local=endpoint(reinterpret_cast<sockaddr*>(&s->engine->local));
    addEndpoint(j.get(),"local",local);
    // Conservative QUIC payload budget; oversized PDG payloads use the stream.
    const auto* peer=picoquic_get_transport_parameters(s->connection,0);
    cJSON_AddNumberToObject(j.get(),"maxDatagramSize",peer && peer->max_datagram_frame_size>12 ? std::min<uint64_t>(1100,peer->max_datagram_frame_size-12) : 0);
    return j;
}
void announce(State* s) {
    if(s->announced)return;s->announced=true;s->ready=true;s->deadline=0;
    auto j=info(s);
    if(s->engine->options.server){cJSON_AddNumberToObject(j.get(),"id",s->id);push(s->engine->owner.get(),{"accept",encode(j.get()),{}});}
    else push(s,{"ready",encode(j.get()),{}});
}
// Chain trust is checked before the TLS CertificateVerify signature. The latter
// always uses Mbed TLS; a pin never bypasses proof of possession of the key.
struct Verifier { ptls_verify_certificate_t super={};ptls_verify_certificate_t* signatures=nullptr;Options options;State* owner=nullptr; };
int verifiedFlags(void*,mbedtls_x509_crt*,int,uint32_t* flags) { *flags=0;return 0; }
bool platformTrust(ptls_iovec_t* certs,size_t count,const char* hostname) {
#ifdef __APPLE__
    CFMutableArrayRef chain=CFArrayCreateMutable(nullptr,0,&kCFTypeArrayCallBacks);
    for(size_t i=0;i<count;i++){CFDataRef data=CFDataCreate(nullptr,certs[i].base,certs[i].len);SecCertificateRef cert=SecCertificateCreateWithData(nullptr,data);CFRelease(data);if(!cert){CFRelease(chain);return false;}CFArrayAppendValue(chain,cert);CFRelease(cert);}
    CFStringRef name=CFStringCreateWithCString(nullptr,hostname?hostname:"",kCFStringEncodingUTF8);
    SecPolicyRef policy=SecPolicyCreateSSL(true,name);CFRelease(name);SecTrustRef trust=nullptr;
    bool ok=SecTrustCreateWithCertificates(chain,policy,&trust)==errSecSuccess;
    if(ok){SecTrustSetNetworkFetchAllowed(trust,false);ok=SecTrustEvaluateWithError(trust,nullptr);}
    if(trust)CFRelease(trust);CFRelease(policy);CFRelease(chain);return ok;
#elif defined(_WIN32)
    HCERTSTORE store=CertOpenStore(CERT_STORE_PROV_MEMORY,0,0,0,nullptr);
    PCCERT_CONTEXT leaf=nullptr;
    for(size_t i=0;i<count;i++){PCCERT_CONTEXT cert=nullptr;CertAddEncodedCertificateToStore(store,X509_ASN_ENCODING,certs[i].base,static_cast<DWORD>(certs[i].len),CERT_STORE_ADD_ALWAYS,&cert);if(i==0)leaf=cert;else if(cert)CertFreeCertificateContext(cert);}
    CERT_CHAIN_PARA params={};params.cbSize=sizeof(params);PCCERT_CHAIN_CONTEXT chain=nullptr;
    bool ok=leaf && CertGetCertificateChain(nullptr,leaf,nullptr,store,&params,CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL,nullptr,&chain);
    std::wstring name;if(hostname){int n=MultiByteToWideChar(CP_UTF8,0,hostname,-1,nullptr,0);name.resize(n);MultiByteToWideChar(CP_UTF8,0,hostname,-1,name.data(),n);}
    SSL_EXTRA_CERT_CHAIN_POLICY_PARA ssl={};ssl.cbSize=sizeof(ssl);ssl.dwAuthType=AUTHTYPE_SERVER;ssl.pwszServerName=name.data();
    CERT_CHAIN_POLICY_PARA policy={};policy.cbSize=sizeof(policy);policy.pvExtraPolicyPara=&ssl;CERT_CHAIN_POLICY_STATUS status={};status.cbSize=sizeof(status);
    ok=ok && CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL,chain,&policy,&status) && !status.dwError;
    if(chain)CertFreeCertificateChain(chain);if(leaf)CertFreeCertificateContext(leaf);CertCloseStore(store,0);return ok;
#else
    (void)certs;(void)count;(void)hostname;return false; // Linux uses the Mbed TLS CA verifier below.
#endif
}
int verify(ptls_verify_certificate_t* base,ptls_t* tls,const char* hostname,
    int (**signature)(void*,uint16_t,ptls_iovec_t,ptls_iovec_t),void** context,ptls_iovec_t* certs,size_t count) {
    auto* v=reinterpret_cast<Verifier*>(base);if(!count)return PTLS_ALERT_BAD_CERTIFICATE;
    bool trusted=false;
    if(!v->options.hashes.empty()){
        uint8_t hash[32];mbedtls_sha256(certs[0].base,certs[0].len,hash,0);char hex[65];
        for(size_t i=0;i<32;i++)snprintf(hex+2*i,3,"%02x",hash[i]);
        mbedtls_x509_crt leaf;mbedtls_x509_crt_init(&leaf);
        if(!mbedtls_x509_crt_parse_der(&leaf,certs[0].base,certs[0].len)){
            // Hash deployments match browser requirements: current, short-lived EC certificates.
            auto seconds=[](mbedtls_x509_time t){std::tm tm={};tm.tm_year=t.year-1900;tm.tm_mon=t.mon-1;tm.tm_mday=t.day;tm.tm_hour=t.hour;tm.tm_min=t.min;tm.tm_sec=t.sec;
#ifdef _WIN32
                return _mkgmtime(&tm);
#else
                return timegm(&tm);
#endif
            };
            auto validity=seconds(leaf.valid_to)-seconds(leaf.valid_from);
            trusted=validity>0 && validity<=14*24*3600 && !mbedtls_x509_time_is_past(&leaf.valid_to) && !mbedtls_x509_time_is_future(&leaf.valid_from)
                && mbedtls_pk_can_do(&leaf.pk,MBEDTLS_PK_ECKEY) && std::find(v->options.hashes.begin(),v->options.hashes.end(),hex)!=v->options.hashes.end();
        }
        mbedtls_x509_crt_free(&leaf);
    } else if(!v->options.ca.empty()) trusted=true; // The signature verifier also validates this CA chain and hostname.
    else trusted=platformTrust(certs,count,hostname);
#if !defined(__APPLE__) && !defined(_WIN32)
    if(v->options.hashes.empty())trusted=true; // Mbed TLS loads the system CA file.
#endif
    if(!trusted){v->owner->certificateFailed=true;return PTLS_ALERT_BAD_CERTIFICATE;}
    int result=v->signatures->cb(v->signatures,tls,hostname,signature,context,certs,count);
    if(result)v->owner->certificateFailed=true;
    return result;
}
void disposeVerifier(ptls_verify_certificate_t* base) {
    auto* v=reinterpret_cast<Verifier*>(base);ptls_mbedtls_dispose_verify_certificate(v->signatures);delete v;
}
bool installVerifier(Engine* e) {
    auto* v=new Verifier;v->options=e->options;v->owner=e->owner.get();
    std::string ca=e->options.ca;
#if !defined(__APPLE__) && !defined(_WIN32)
    if(ca.empty() && e->options.hashes.empty()){
        for(const char* candidate:{"/etc/ssl/certs/ca-certificates.crt","/etc/pki/tls/certs/ca-bundle.crt","/etc/ssl/ca-bundle.pem","/etc/ssl/cert.pem"})
            if(access(candidate,R_OK)==0){ca=candidate;break;}
        if(ca.empty()){delete v;return false;}
    }
#endif
    if(!ca.empty()) {unsigned nonempty=0;v->signatures=ptls_mbedtls_get_certificate_verifier(ca.c_str(),&nonempty);}
    else {auto* signatures=ptls_mbedssl_init_verify_certificate_complete(nullptr,nullptr,verifiedFlags,nullptr);v->signatures=signatures?&signatures->super:nullptr;}
    if(!v->signatures){delete v;return false;}
    v->super.cb=verify;v->super.algos=v->signatures->algos;
    picoquic_set_verify_certificate_callback(e->quic,&v->super,disposeVerifier);return true;
}
int callback(picoquic_cnx_t* cnx,uint8_t* bytes,size_t length,picohttp_call_back_event_t event,h3zero_stream_ctx_t* stream,void* context);
int serverCallback(picoquic_cnx_t* cnx,uint8_t* bytes,size_t length,picohttp_call_back_event_t event,h3zero_stream_ctx_t* stream,void* context) {
    if(event==picohttp_callback_connect)return callback(cnx,bytes,length,event,stream,context);
    // Upstream reselects the URL callback when the first CONNECT capsule arrives,
    // issuing a POST notification with Engine context but preserving State context
    // on the upgraded stream. Restore its session callback before handling data.
    if(stream && stream->is_upgraded){
        stream->path_callback=callback;
        return event==picohttp_callback_post?0:callback(cnx,bytes,length,event,stream,stream->path_callback_ctx);
    }
    // Ordinary HTTP requests never have a session State.
    return event==picohttp_callback_free?0:-1;
}
int originValidator(const uint8_t* origin,size_t length,const uint8_t*,size_t,void* context) {
    auto* e=static_cast<Engine*>(context);std::string value(reinterpret_cast<const char*>(origin?origin:reinterpret_cast<const uint8_t*>("")),length);
    bool allow=std::find(e->options.origins.begin(),e->options.origins.end(),value)!=e->options.origins.end() || std::find(e->options.origins.begin(),e->options.origins.end(),"*")!=e->options.origins.end();
    return allow && e->accepting && !e->owner->closed?0:-1;
}
int callback(picoquic_cnx_t* cnx,uint8_t* bytes,size_t length,picohttp_call_back_event_t event,h3zero_stream_ctx_t* stream,void* context) {
    auto* s=static_cast<State*>(context);
    if(event==picohttp_callback_connect){
        auto* e=static_cast<Engine*>(context);if(e->owner->closed || !e->accepting)return -1;
        const auto& header=stream->ps.stream_state.header;
        std::string origin=header.origin?std::string(reinterpret_cast<const char*>(header.origin),header.origin_length):"";
        // Upstream invokes origin_validator only when an Origin header exists.
        // Validate its absence here too, using the documented empty-string rule.
        if(std::find(e->options.origins.begin(),e->options.origins.end(),origin)==e->options.origins.end() &&
            std::find(e->options.origins.begin(),e->options.origins.end(),"*")==e->options.origins.end())return -1;
        if(stream->ps.stream_state.header.wt_available_protocols && picowt_select_wt_protocol(stream,"pdg-net-v1"))return -1;
        sockaddr* address=nullptr;picoquic_get_peer_addr(cnx,&address);auto ip=endpoint(address).host;
        size_t ipCount=0,originCount=0;for(auto& entry:e->admissions){auto st=e->sessions[entry.first];if(st->closed)continue;if(entry.second.first==ip)ipCount++;if(entry.second.second==origin)originCount++;}
        for(auto it=e->attempts.begin();it!=e->attempts.end();)if(now()-it->second.first>60000000)it=e->attempts.erase(it);else ++it;
        if(e->attempts.size()>=4096 && !e->attempts.count(ip))return -1;
        auto& rate=e->attempts[ip];if(!rate.first)rate.first=now();rate.second++;
        if(e->sessions.size()>=e->options.maxConnections || ipCount>=e->options.maxPerIP || originCount>=e->options.maxPerOrigin || rate.second>e->options.maxPerMinute)return -1;
        auto state=create(e->options.limit);if(!state)return -1;s=state.get();s->engine=e;s->connection=cnx;s->h3=static_cast<h3zero_callback_ctx_t*>(picoquic_get_callback_context(cnx));s->control=stream;s->deadline=now()+e->options.timeout;
        e->sessions.emplace(s->id,state);e->admissions[s->id]={ip,origin};
        stream->path_callback=callback;stream->path_callback_ctx=s;
        return h3zero_declare_stream_prefix(s->h3,stream->stream_id,callback,s);
    }
    if(!s)return 0;
    if(event==picohttp_callback_deregister){s->detached=true;s->connection=nullptr;finish(s,s->ready?nullptr:(s->certificateFailed?"ERR_TLS_CERTIFICATE":"ERR_WEBTRANSPORT_CONNECT"),"WebTransport connection closed before establishment");return 0;}
    if(event==picohttp_callback_free){if(stream==s->control)finish(s,s->ready?nullptr:(s->certificateFailed?"ERR_TLS_CERTIFICATE":"ERR_WEBTRANSPORT_CONNECT"),"WebTransport connection closed before establishment");return 0;}
    if(s->closed)return 0;
    switch(event){
    case picohttp_callback_connect_accepted:{
        auto* reliable=picowt_create_local_stream(cnx,1,s->h3,s->control->stream_id);
        if(!reliable){finish(s,"ERR_WEBTRANSPORT_STREAM","Unable to open reliable stream");picoquic_close(cnx,1);break;}
        reliable->path_callback=callback;reliable->path_callback_ctx=s;
        s->reliable=reliable->stream_id;announce(s);break;
    }
    case picohttp_callback_connect_refused:
        finish(s,stream->ps.stream_state.header.status==404?"ERR_WEBTRANSPORT_UNSUPPORTED":"ERR_WEBTRANSPORT_REJECTED","WebTransport session rejected");picoquic_close(cnx,1);break;
    case picohttp_callback_post_data:
    case picohttp_callback_post_fin:
        if(stream->stream_id==s->control->stream_id){if(event==picohttp_callback_post_fin)finish(s);break;}
        if(s->reliable==UINT64_MAX){if((stream->stream_id&3)!=0){picowt_reset_stream(cnx,stream,1);break;}s->reliable=stream->stream_id;announce(s);}
        if(stream->stream_id!=s->reliable){picowt_reset_stream(cnx,stream,1);break;}
        if(length)push(s,{"data","",std::vector<uint8_t>(bytes,bytes+length)});
        if(event==picohttp_callback_post_fin){finish(s);picoquic_close(cnx,0);}break;
    case picohttp_callback_post_datagram:
        if(s->ready && length<=1100)push(s,{"datagram","",std::vector<uint8_t>(bytes,bytes+length)});break;
    case picohttp_callback_provide_data:
        if(stream->stream_id==s->reliable && !s->reliableWrites.empty()){
            auto& data=s->reliableWrites.front();size_t n=std::min(length,data.size()-s->offset);
            bool more=n<data.size()-s->offset || s->reliableWrites.size()>1;
            auto* destination=picoquic_provide_stream_data_buffer(bytes,n,0,more);if(!destination)break;
            memcpy(destination,data.data()+s->offset,n);s->offset+=n;
            {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);s->inflight+=n;}
            if(s->offset==data.size()){s->reliableWrites.pop_front();s->offset=0;auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);s->pendingWrites--;}
        }break;
    case picohttp_callback_provide_datagram:
        if(!s->datagrams.empty()){
            auto data=std::move(s->datagrams.front());s->datagrams.pop_front();
            if(data.size()<=length){auto* dest=h3zero_provide_datagram_buffer(bytes,data.size(),!s->datagrams.empty());if(dest)memcpy(dest,data.data(),data.size());}
            {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);s->outgoing-=data.size();s->pendingWrites--;}
        }break;
    case picohttp_callback_reset:
    case picohttp_callback_stop_sending:
        if(stream->stream_id==s->reliable || stream->stream_id==s->control->stream_id)finish(s);break;
    case picohttp_callback_deregister:
    case picohttp_callback_free:finish(s);break;
    default:break;
    }
    return 0;
}
void openEngine(std::shared_ptr<State> owner,Options options,sockaddr_storage target) {
    if(owner->closed || owner->stopping)return;
    auto engine=std::make_unique<Engine>();auto* e=engine.get();e->options=std::move(options);e->owner=owner;owner->engine=e;
    e->quic=picoquic_create(static_cast<uint32_t>(e->options.server?e->options.maxConnections:1),e->options.server?e->options.cert.c_str():nullptr,e->options.server?e->options.key.c_str():nullptr,
        nullptr,"h3",h3zero_callback,e->options.server?&e->http:nullptr,nullptr,nullptr,nullptr,now(),nullptr,nullptr,nullptr,0);
    if(!e->quic){finish(owner.get(),"ERR_TLS_CONFIG","Unable to initialize WebTransport TLS");return;}
    picowt_set_default_transport_parameters(e->quic);
    picoquic_tp_t parameters=*picoquic_get_default_tp(e->quic);
    parameters.initial_max_data=e->options.limit;parameters.initial_max_stream_data_bidi_local=e->options.limit;parameters.initial_max_stream_data_bidi_remote=e->options.limit;
    parameters.initial_max_stream_data_uni=65536;parameters.initial_max_stream_id_bidir=8;parameters.initial_max_stream_id_unidir=12;parameters.max_idle_timeout=e->options.idle/1000;
    picoquic_set_default_tp(e->quic,&parameters);
    int family=target.ss_family;
    e->socket=socket(family,SOCK_DGRAM,IPPROTO_UDP);if(e->socket==static_cast<Socket>(-1)){finish(owner.get(),"ERR_NETWORK_SOCKET","Unable to create QUIC socket");return;}
#ifdef _WIN32
    u_long nonblocking=1;ioctlsocket(e->socket,FIONBIO,&nonblocking);
#else
    fcntl(e->socket,F_SETFL,O_NONBLOCK);
#endif
    e->local=target;
    if(!e->options.server){if(family==AF_INET){auto* a=reinterpret_cast<sockaddr_in*>(&e->local);a->sin_addr.s_addr=INADDR_ANY;a->sin_port=0;}else{auto* a=reinterpret_cast<sockaddr_in6*>(&e->local);a->sin6_addr=in6addr_any;a->sin6_port=0;}}
    int length=family==AF_INET?sizeof(sockaddr_in):sizeof(sockaddr_in6);
    if(bind(e->socket,reinterpret_cast<sockaddr*>(&e->local),length)){finish(owner.get(),"ERR_LISTEN_BIND","Unable to bind WebTransport UDP port");return;}
#ifdef _WIN32
    int localLength=sizeof(e->local);
#else
    socklen_t localLength=sizeof(e->local);
#endif
    getsockname(e->socket,reinterpret_cast<sockaddr*>(&e->local),&localLength);
    if(e->options.server){
        e->path.path=e->options.path.c_str();e->path.path_length=e->options.path.size();e->path.path_callback=serverCallback;e->path.path_app_ctx=e;
        e->path.connect_protocol="webtransport";e->path.connect_protocol_length=12;e->path.origin_validator=originValidator;e->path.origin_validator_ctx=e;
        e->http.path_table=&e->path;e->http.path_table_nb=1;
        auto j=object();auto address=endpoint(reinterpret_cast<sockaddr*>(&e->local));string(j.get(),"address",address.host);cJSON_AddNumberToObject(j.get(),"port",address.port);string(j.get(),"transport","webtransport");cJSON_AddBoolToObject(j.get(),"secure",true);push(owner.get(),{"ready",encode(j.get()),{}});owner->ready=true;
    }else{
        if(!installVerifier(e)){finish(owner.get(),"ERR_TLS_CONFIG","Unable to initialize certificate trust");return;}
        auto* s=owner.get();
        if(picowt_prepare_client_cnx(e->quic,reinterpret_cast<sockaddr*>(&target),&s->connection,&s->h3,&s->control,now(),e->options.host.c_str())){finish(s,"ERR_WEBTRANSPORT_CONNECT","Unable to initialize WebTransport session");return;}
        s->h3->no_print=1;s->h3->no_disk=1;
        std::string authority=(e->options.host.find(':')==std::string::npos?e->options.host:"["+e->options.host+"]")+":"+std::to_string(e->options.port);
        if(picowt_connect(s->connection,s->h3,s->control,authority.c_str(),e->options.path.c_str(),callback,s,"pdg-net-v1")){finish(s,"ERR_WEBTRANSPORT_CONNECT","Unable to send WebTransport CONNECT");return;}
        e->sessions.emplace(s->id,owner);picoquic_start_client_cnx(s->connection);
    }
    manager().engines.push_back(std::move(engine));
}
void tick(Engine* e) {
    uint8_t packet[65536];sockaddr_storage peer={};
    for(unsigned i=0;i<32;i++){
#ifdef _WIN32
        int n=sizeof(peer);int size=recvfrom(e->socket,reinterpret_cast<char*>(packet),sizeof(packet),0,reinterpret_cast<sockaddr*>(&peer),&n);
#else
        socklen_t n=sizeof(peer);ssize_t size=recvfrom(e->socket,packet,sizeof(packet),0,reinterpret_cast<sockaddr*>(&peer),&n);
#endif
        if(size<0)break;picoquic_incoming_packet(e->quic,packet,size,reinterpret_cast<sockaddr*>(&peer),reinterpret_cast<sockaddr*>(&e->local),0,0,now());
    }
    for(auto it=e->sessions.begin();it!=e->sessions.end();){auto s=it->second;
        if(s->connection && s->inflight && picoquic_is_cnx_backlog_empty(s->connection)) {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);s->outgoing-=s->inflight;s->inflight=0;}
        if(!s->closed && s->endDeadline && (now()>=s->endDeadline || (s->reliableWrites.empty() && s->datagrams.empty() && (!s->connection || picoquic_is_cnx_backlog_empty(s->connection))))){if(s->connection)picoquic_close(s->connection,0);finish(s.get());}
        if(!s->closed && s->deadline && now()>s->deadline){finish(s.get(),"ERR_CONNECT_TIMEOUT","WebTransport establishment timed out");if(s->connection)picoquic_close(s->connection,1);}
        if(!s->closed && s->connection && ((s->h3 && s->h3->connection_closed) || picoquic_get_cnx_state(s->connection)==picoquic_state_disconnected)){auto code=picoquic_get_local_error(s->connection);finish(s.get(),s->certificateFailed?"ERR_TLS_CERTIFICATE":(code?"ERR_WEBTRANSPORT_CONNECT":nullptr),"WebTransport connection closed");}
        if(s->detached){e->admissions.erase(s->id);it=e->sessions.erase(it);
            if(e->options.server && !s->announced){auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);m.states.erase(s->id);}
        }else ++it;
    }
    for(unsigned i=0;i<32;i++){sockaddr_storage to={},from={};size_t size=0;int iface=0;
        if(picoquic_prepare_next_packet(e->quic,now(),packet,sizeof(packet),&size,&to,&from,&iface,nullptr,nullptr)||!size)break;
        sendto(e->socket,reinterpret_cast<const char*>(packet),static_cast<int>(size),0,reinterpret_cast<sockaddr*>(&to),to.ss_family==AF_INET?sizeof(sockaddr_in):sizeof(sockaddr_in6));
    }
    if(e->options.server && !e->accepting && e->sessions.empty())finish(e->owner.get());
}
Manager::Manager():thread([this]{
    for(;;){std::deque<std::function<void()>> jobs;{std::unique_lock<std::mutex> lock(mutex);wake.wait_for(lock,std::chrono::milliseconds(2),[this]{return stop || !work.empty();});if(stop)break;jobs.swap(work);}
        for(auto& job:jobs)job();
        std::vector<std::shared_ptr<State>> pending;
        {std::lock_guard<std::mutex> lock(mutex);for(auto& entry:states)if(!entry.second->engine && entry.second->deadline && !entry.second->closed)pending.push_back(entry.second);}
        for(auto s:pending)if(now()>=s->deadline)finish(s.get(),"ERR_CONNECT_TIMEOUT","WebTransport endpoint lookup timed out");
        for(auto it=engines.begin();it!=engines.end();){auto* e=it->get();
            if(e->owner->closed && !e->closingDeadline){
                e->closingDeadline=now()+100000;
                for(auto& entry:e->sessions){auto s=entry.second;finish(s.get());if(s->connection)picoquic_close(s->connection,0);}
            }
            if(e->closingDeadline && now()>=e->closingDeadline){
                std::vector<unsigned> unannounced;for(auto& entry:e->sessions)if(e->options.server && !entry.second->announced)unannounced.push_back(entry.first);
                it=engines.erase(it);std::lock_guard<std::mutex> lock(mutex);for(auto id:unannounced)states.erase(id);
            }else{tick(e);++it;}
        }
    }
    engines.clear();
}),resolver([this]{
    for(;;){std::function<void()> lookup;{std::unique_lock<std::mutex> lock(mutex);wake.wait(lock,[this]{return stop || !lookups.empty();});if(stop)break;lookup=std::move(lookups.front());lookups.pop_front();}lookup();}
}){}
Manager::~Manager(){{std::lock_guard<std::mutex> lock(mutex);stop=true;}wake.notify_all();thread.join();resolver.join();}
std::vector<std::string> strings(cJSON* j,const char* key){std::vector<std::string> values;auto* array=cJSON_GetObjectItemCaseSensitive(j,key);cJSON* value=nullptr;cJSON_ArrayForEach(value,array)if(cJSON_IsString(value))values.emplace_back(value->valuestring);return values;}
bool writeOwned(std::shared_ptr<State> s,std::vector<uint8_t> bytes,bool datagram){
    if(!s || bytes.size()>s->limit || (datagram && bytes.size()>1100))return false;
        {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);if(s->closed || s->stopping || !s->ready)return false;
            if(bytes.empty())return true;
            if(bytes.size()>s->limit-s->outgoing || m.work.size()>=1024 || s->pendingWrites>=256){s->stopping=true;m.work.push_back([s]{finish(s.get(),"ERR_BACKPRESSURE","Outgoing WebTransport buffer limit exceeded");if(s->connection)picoquic_close(s->connection,1);});m.wake.notify_one();return false;}s->outgoing+=bytes.size();s->pendingWrites++;}
        enqueue([s,bytes=std::move(bytes),datagram]()mutable{if(s->closed)return;if(datagram){s->datagrams.push_back(std::move(bytes));h3zero_set_datagram_ready(s->connection,s->control->stream_id);}else{s->reliableWrites.push_back(std::move(bytes));auto* stream=h3zero_find_stream(s->h3,s->reliable);if(stream)picoquic_mark_active_stream(s->connection,s->reliable,1,stream);}});
    return true;
}
Json command(cJSON* request){
    std::string action=text(request,"action");
    if(action=="open"){
#ifdef PDG_WEBTRANSPORT_CLIENT_ONLY
        if(cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(request,"server")))return error("ERR_TRANSPORT_UNAVAILABLE","This platform supports WebTransport clients only");
#endif
        for(const char* name:{"port","maxPendingBytes","timeout","idleTimeout"}){
            auto* item=cJSON_GetObjectItemCaseSensitive(request,name);
            if(item && !cJSON_IsNumber(item))return error("ERR_TRANSPORT_CONFIG","WebTransport endpoint limits must be numbers");
        }
        Options o;o.server=cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(request,"server"));o.host=text(request,"host","localhost");o.path=text(request,"path","/pdg");o.cert=text(request,"certFile");o.key=text(request,"keyFile");o.ca=text(request,"caFile");
        auto integer=[](double value,double low,double high){return std::isfinite(value) && value>=low && value<=high && std::floor(value)==value;};
        double port=number(request,"port",5443),limit=number(request,"maxPendingBytes",4*1024*1024),timeout=number(request,"timeout",5000),idle=number(request,"idleTimeout",30000);
        if(!integer(port,o.server?0:1,65535) || !integer(limit,1024,64*1024*1024) || !integer(timeout,1,0xffffffff) || !integer(idle,1,0xffffffff) || o.host.empty() || o.path.empty() || o.path[0]!='/')return error("ERR_TRANSPORT_CONFIG","Invalid WebTransport endpoint or limit");
        o.port=static_cast<uint16_t>(port);o.limit=static_cast<size_t>(limit);o.timeout=static_cast<uint64_t>(timeout)*1000;o.idle=static_cast<uint64_t>(idle)*1000;
        for(const char* name:{"maxConnections","maxConnectionsPerIP","maxConnectionsPerOrigin","maxConnectionsPerMinute"}){
            auto* item=cJSON_GetObjectItemCaseSensitive(request,name);
            if(item && (!cJSON_IsNumber(item) || !integer(item->valuedouble,1,4096)))return error("ERR_TRANSPORT_CONFIG","Invalid WebTransport admission limit");
        }
        o.maxConnections=static_cast<size_t>(number(request,"maxConnections",1024));o.maxPerIP=static_cast<size_t>(number(request,"maxConnectionsPerIP",32));o.maxPerOrigin=static_cast<size_t>(number(request,"maxConnectionsPerOrigin",1024));o.maxPerMinute=static_cast<size_t>(number(request,"maxConnectionsPerMinute",120));
        o.origins=strings(request,"allowedOrigins");o.hashes=strings(request,"certificateHashes");
        for(const auto& hash:o.hashes)if(hash.size()!=64 || hash.find_first_not_of("0123456789abcdef")!=std::string::npos)return error("ERR_TRANSPORT_CONFIG","Certificate hashes must be lowercase SHA-256 hex");
        if(o.maxConnections<1 || o.maxConnections>4096 || (o.server && (o.cert.empty() || o.key.empty())))return error("ERR_TRANSPORT_CONFIG","WebTransport requires valid limits and TLS certificate files");
        auto s=create(o.limit,now()+o.timeout);if(!s)return error("ERR_BACKPRESSURE","Too many native WebTransport handles");
        {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);m.lookups.push_back([s,o]{
            if(s->closed || s->stopping)return;
            sockaddr_storage target={};addrinfo hints={};hints.ai_socktype=SOCK_DGRAM;hints.ai_family=AF_UNSPEC;addrinfo* addresses=nullptr;
            auto port=std::to_string(o.port);
            if(getaddrinfo(o.host.c_str(),port.c_str(),&hints,&addresses)||!addresses){enqueue([s]{finish(s.get(),"ERR_NETWORK_DNS","WebTransport endpoint lookup failed");});return;}
            memcpy(&target,addresses->ai_addr,addresses->ai_addrlen);freeaddrinfo(addresses);
            enqueue([s,o,target]{openEngine(s,o,target);});
        });m.wake.notify_all();}
        auto j=object();cJSON_AddNumberToObject(j.get(),"id",s->id);return j;
    }
    double handle=number(request,"id",0);if(!std::isfinite(handle) || handle<0 || handle>0xffffffff || std::floor(handle)!=handle)return error("ERR_TRANSPORT_CONFIG","Invalid WebTransport handle");
    unsigned id=static_cast<unsigned>(handle);auto s=find(id);
    if(action=="poll"){
        auto array=Json(cJSON_CreateArray(),cJSON_Delete);if(!s)return array;
        auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
        for(unsigned i=0;i<64 && !s->events.empty();i++){auto event=std::move(s->events.front());s->events.pop_front();s->incoming-=event.bytes.size();auto j=object();string(j.get(),"type",event.type);
            if(!event.json.empty())cJSON_AddItemToObject(j.get(),"value",cJSON_Parse(event.json.c_str()));
            else{auto data=Json(cJSON_CreateArray(),cJSON_Delete);for(uint8_t byte:event.bytes)cJSON_AddItemToArray(data.get(),cJSON_CreateNumber(byte));cJSON_AddItemToObject(j.get(),"value",data.release());}
            cJSON_AddItemToArray(array.get(),j.release());
        }
        if(s->closed && s->events.empty())m.states.erase(id);return array;
    }
    if(action=="stop"){
        if(s)enqueue([s]{if(s->closed)return;if(!s->ready || !s->engine || !s->engine->options.server)finish(s.get());else s->engine->accepting=false;});return object();
    }
    if(action=="close"){
        bool force=cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(request,"force"));
        if(s && force && !s->killQueued.exchange(true)){s->stopping=true;enqueue([s]{if(s->connection)picoquic_close(s->connection,0);finish(s.get());});}
        else if(s && !s->stopping.exchange(true))enqueue([s]{if(!s->ready || !s->connection)finish(s.get());else s->endDeadline=now()+2000000;});
        return object();
    }
    if(action=="write"){
        auto j=object();cJSON_AddBoolToObject(j.get(),"accepted",false);if(!s)return j;
        bool datagram=cJSON_IsTrue(cJSON_GetObjectItemCaseSensitive(request,"datagram"));auto* data=cJSON_GetObjectItemCaseSensitive(request,"data");int n=cJSON_GetArraySize(data);
        if(!cJSON_IsArray(data) || n<0 || static_cast<size_t>(n)>s->limit || (datagram && n>1100))return j;
        std::vector<uint8_t> bytes;bytes.reserve(n);cJSON* value=nullptr;cJSON_ArrayForEach(value,data){if(!cJSON_IsNumber(value) || value->valuedouble<0 || value->valuedouble>255 || value->valuedouble!=value->valueint)return j;bytes.push_back(static_cast<uint8_t>(value->valueint));}
        if(!writeOwned(s,std::move(bytes),datagram))return j;
        cJSON_ReplaceItemInObject(j.get(),"accepted",cJSON_CreateBool(true));return j;
    }
    return error("ERR_TRANSPORT_CONFIG","Unknown WebTransport bridge command");
}
}
extern "C" char* pdg_wt_command(const char* request){
    if(!request || strlen(request)>128*1024*1024)return nullptr;
    try{
        Json parsed(cJSON_ParseWithOpts(request,nullptr,1),cJSON_Delete);auto result=parsed?command(parsed.get()):error("ERR_TRANSPORT_CONFIG","Invalid bridge request");return cJSON_PrintUnformatted(result.get());
    }catch(const std::exception& exception){auto result=error("ERR_NETWORK_NATIVE",exception.what());return cJSON_PrintUnformatted(result.get());}
}
extern "C" void pdg_wt_free(char* result){cJSON_free(result);}
namespace pdg::wt {
Result open(const Options& o) {
    auto j=object();string(j.get(),"action","open");cJSON_AddBoolToObject(j.get(),"server",o.server);
    string(j.get(),"host",o.host);string(j.get(),"path",o.path);string(j.get(),"certFile",o.certFile);
    string(j.get(),"keyFile",o.keyFile);string(j.get(),"caFile",o.caFile);
    const std::pair<const char*,double> numbers[]={{"port",double(o.port)},{"maxPendingBytes",double(o.maxPendingBytes)},
        {"maxConnections",double(o.maxConnections)},{"maxConnectionsPerIP",double(o.maxConnectionsPerIP)},
        {"maxConnectionsPerOrigin",double(o.maxConnectionsPerOrigin)},{"maxConnectionsPerMinute",double(o.maxConnectionsPerMinute)},
        {"timeout",double(o.timeout)},{"idleTimeout",double(o.idleTimeout)}};
    for(auto entry:numbers)cJSON_AddNumberToObject(j.get(),entry.first,entry.second);
    for(auto entry:{std::make_pair("allowedOrigins",&o.allowedOrigins),std::make_pair("certificateHashes",&o.certificateHashes)}){
        auto* array=cJSON_AddArrayToObject(j.get(),entry.first);
        for(const auto& value:*entry.second)cJSON_AddItemToArray(array,cJSON_CreateString(value.c_str()));
    }
    auto result=command(j.get());return {static_cast<unsigned>(number(result.get(),"id",0)),text(result.get(),"code"),text(result.get(),"message")};
}
std::vector<Event> poll(unsigned id) {
    std::vector<Event> result;auto s=find(id);if(!s)return result;
    std::deque<::Event> events;
    {auto& m=manager();std::lock_guard<std::mutex> lock(m.mutex);
        for(unsigned i=0;i<64 && !s->events.empty();i++){
            s->incoming-=s->events.front().bytes.size();events.push_back(std::move(s->events.front()));s->events.pop_front();
        }
        if(s->closed && s->events.empty())m.states.erase(id);
    }
    for(auto& value:events){
        Event e;
        if(value.type=="ready")e.type=Event::Ready;
        else if(value.type=="accept")e.type=Event::Accept;
        else if(value.type=="data")e.type=Event::Data;
        else if(value.type=="datagram")e.type=Event::Datagram;
        else if(value.type=="error")e.type=Event::Error;
        else e.type=Event::Close;
        e.bytes=std::move(value.bytes);
        if(!value.json.empty()){
            Json j(cJSON_Parse(value.json.c_str()),cJSON_Delete);
            auto endpoint=[](cJSON* value){return Endpoint{text(value,"address"),static_cast<uint16_t>(number(value,"port",0))};};
            e.id=static_cast<unsigned>(number(j.get(),"id",0));e.maxDatagramSize=static_cast<size_t>(number(j.get(),"maxDatagramSize",0));
            e.local=endpoint(cJSON_GetObjectItemCaseSensitive(j.get(),"local"));
            if(e.local.address.empty())e.local=endpoint(j.get());
            e.remote=endpoint(cJSON_GetObjectItemCaseSensitive(j.get(),"remote"));e.code=text(j.get(),"code");e.message=text(j.get(),"message");
        }
        result.push_back(std::move(e));
    }
    return result;
}
bool write(unsigned id,std::vector<uint8_t> bytes,bool datagram){return writeOwned(find(id),std::move(bytes),datagram);}
void close(unsigned id,bool force){auto j=object();string(j.get(),"action","close");cJSON_AddNumberToObject(j.get(),"id",id);cJSON_AddBoolToObject(j.get(),"force",force);command(j.get());}
void stop(unsigned id){auto j=object();string(j.get(),"action","stop");cJSON_AddNumberToObject(j.get(),"id",id);command(j.get());}
void release(unsigned id){
    // Accept events own handles that a stopped native listener may never consume.
    // Retain their states for worker cancellation before discarding those handles.
    std::vector<std::shared_ptr<State>> abandoned;
    auto& m=manager();
    {std::lock_guard<std::mutex> lock(m.mutex);auto it=m.states.find(id);if(it==m.states.end())return;
        for(const auto& event:it->second->events)if(event.type=="accept"){
            Json value(cJSON_Parse(event.json.c_str()),cJSON_Delete);auto child=m.states.find(static_cast<unsigned>(number(value.get(),"id",0)));
            if(child!=m.states.end()){abandoned.push_back(child->second);m.states.erase(child);}
        }
        m.states.erase(it);
    }
    for(auto& state:abandoned)enqueue([state]{finish(state.get());if(state->connection)picoquic_close(state->connection,1);});
}
} // namespace pdg::wt
extern "C" void pdg_wt_suspend(){enqueue([]{for(auto& engine:manager().engines){for(auto& session:engine->sessions)finish(session.second.get(),"ERR_NETWORK_BACKGROUND","iOS application entered the background");if(!engine->options.server)finish(engine->owner.get(),"ERR_NETWORK_BACKGROUND","iOS application entered the background");}});}
