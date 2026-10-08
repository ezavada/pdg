#include "transport.h"
#include <mbedtls/base64.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <mbedtls/net_sockets.h>
#include <mbedtls/sha1.h>
#include <mbedtls/ssl.h>
#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstring>
#include <map>
#include <mutex>
#include <stdexcept>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <wincrypt.h>
using Socket=SOCKET;
constexpr Socket invalidSocket=INVALID_SOCKET;
static int socketError(){return WSAGetLastError();}
static bool pendingError(int e){return e==WSAEWOULDBLOCK || e==WSAEINPROGRESS;}
static void releaseSocket(Socket s){closesocket(s);}
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
using Socket=int;
constexpr Socket invalidSocket=-1;
static int socketError(){return errno;}
static bool pendingError(int e){return e==EAGAIN || e==EWOULDBLOCK || e==EINPROGRESS || e==EINTR;}
static void releaseSocket(Socket s){::close(s);}
#endif
#ifdef __APPLE__
#include <Security/Security.h>
#endif
namespace pdg::net_detail {
namespace {
using Clock=std::chrono::steady_clock;
using Time=Clock::time_point;
void nonblocking(Socket fd){
#ifdef _WIN32
    u_long value=1;if(ioctlsocket(fd,FIONBIO,&value))throw std::runtime_error("Cannot set socket nonblocking");
#else
    if(fcntl(fd,F_SETFL,fcntl(fd,F_GETFL)|O_NONBLOCK)<0)throw std::runtime_error("Cannot set socket nonblocking");
#ifdef SO_NOSIGPIPE
    int yes=1;setsockopt(fd,SOL_SOCKET,SO_NOSIGPIPE,&yes,sizeof(yes));
#endif
#endif
}
int sendSocket(Socket fd,const uint8_t* bytes,size_t size){
#ifdef MSG_NOSIGNAL
    return static_cast<int>(::send(fd,bytes,static_cast<int>(size),MSG_NOSIGNAL));
#else
    return static_cast<int>(::send(fd,reinterpret_cast<const char*>(bytes),static_cast<int>(size),0));
#endif
}
NetEndpoint endpoint(const sockaddr* address){
    char host[NI_MAXHOST],port[NI_MAXSERV];
    if(address && !getnameinfo(address,address->sa_family==AF_INET?sizeof(sockaddr_in):sizeof(sockaddr_in6),host,sizeof(host),port,sizeof(port),NI_NUMERICHOST|NI_NUMERICSERV))
        return {host,static_cast<uint16_t>(std::stoul(port))};
    return {};
}
NetEndpoint socketEndpoint(Socket fd,bool peer){sockaddr_storage a{};
#ifdef _WIN32
    int size=sizeof(a);
#else
    socklen_t size=sizeof(a);
#endif
    if(peer)getpeername(fd,reinterpret_cast<sockaddr*>(&a),&size);else getsockname(fd,reinterpret_cast<sockaddr*>(&a),&size);
    return endpoint(reinterpret_cast<sockaddr*>(&a));
}
std::string lower(std::string s){for(auto& c:s)c=static_cast<char>(std::tolower(static_cast<unsigned char>(c)));return s;}
std::string trim(std::string s){auto first=s.find_first_not_of(" \t");if(first==std::string::npos)return {};return s.substr(first,s.find_last_not_of(" \t")-first+1);}
bool token(std::string s,const std::string& wanted){size_t start=0;do{auto end=s.find(',',start);if(lower(trim(s.substr(start,end-start)))==wanted)return true;if(end==std::string::npos)break;start=end+1;}while(start<s.size());return false;}
std::string base64(const uint8_t* data,size_t size){std::string out((size+2)/3*4+1,'\0');size_t n=0;if(mbedtls_base64_encode(reinterpret_cast<uint8_t*>(out.data()),out.size(),&n,data,size))throw std::runtime_error("Base64 encoding failed");out.resize(n);return out;}
std::string acceptKey(const std::string& key){auto text=key+"258EAFA5-E914-47DA-95CA-C5AB0DC85B11";uint8_t digest[20];mbedtls_sha1(reinterpret_cast<const uint8_t*>(text.data()),text.size(),digest);return base64(digest,sizeof(digest));}
struct ParsedUrl{std::string scheme,host,path,authority;uint16_t port;};
ParsedUrl parseUrl(const std::string& url){
    const auto marker=url.find("://");if(marker==std::string::npos)throw std::invalid_argument("A web transport requires an explicit URL");
    ParsedUrl value;value.scheme=url.substr(0,marker);if(value.scheme!="ws" && value.scheme!="wss" && value.scheme!="https")throw std::invalid_argument("Unsupported web transport scheme");
    auto start=marker+3,end=url.find('/',start);value.authority=url.substr(start,end-start);value.path=end==std::string::npos?"/":url.substr(end);
    if(value.authority.empty() || url.find_first_of(" \t\r\n#")!=std::string::npos || value.authority.find('@')!=std::string::npos)throw std::invalid_argument("Invalid web transport URL");
    std::string port;
    if(value.authority[0]=='['){auto close=value.authority.find(']');if(close==std::string::npos)throw std::invalid_argument("Invalid IPv6 URL");value.host=value.authority.substr(1,close-1);if(close+1<value.authority.size()){if(value.authority[close+1]!=':')throw std::invalid_argument("Invalid URL port");port=value.authority.substr(close+2);}}
    else{auto colon=value.authority.find(':');value.host=value.authority.substr(0,colon);if(colon!=std::string::npos)port=value.authority.substr(colon+1);}
    value.port=value.scheme=="ws"?80:443;
    if(!port.empty()){if(port.find_first_not_of("0123456789")!=std::string::npos || port.size()>5)throw std::invalid_argument("Invalid URL port");auto n=std::stoul(port);if(!n || n>65535)throw std::invalid_argument("Invalid URL port");value.port=static_cast<uint16_t>(n);}
    else if(value.authority.back()==':')throw std::invalid_argument("Missing URL port");
    if(value.host.empty())throw std::invalid_argument("Missing URL host");return value;
}
#ifdef __APPLE__
bool platformTrust(mbedtls_x509_crt* chain,const std::string& host){
    auto certificates=CFArrayCreateMutable(nullptr,0,&kCFTypeArrayCallBacks);
    for(auto* p=chain;p;p=p->next){auto data=CFDataCreate(nullptr,p->raw.p,p->raw.len);auto cert=SecCertificateCreateWithData(nullptr,data);CFRelease(data);if(cert){CFArrayAppendValue(certificates,cert);CFRelease(cert);}}
    auto name=CFStringCreateWithCString(nullptr,host.c_str(),kCFStringEncodingUTF8);auto policy=SecPolicyCreateSSL(true,name);CFRelease(name);
    SecTrustRef trust=nullptr;bool valid=false;
    if(SecTrustCreateWithCertificates(certificates,policy,&trust)==errSecSuccess){SecTrustSetNetworkFetchAllowed(trust,false);valid=SecTrustEvaluateWithError(trust,nullptr);CFRelease(trust);}
    CFRelease(policy);CFRelease(certificates);return valid;
}
#elif defined(_WIN32)
bool platformTrust(mbedtls_x509_crt* chain,const std::string& host){
    HCERTSTORE store=CertOpenStore(CERT_STORE_PROV_MEMORY,0,0,0,nullptr);PCCERT_CONTEXT leaf=nullptr;
    for(auto* p=chain;p;p=p->next){PCCERT_CONTEXT cert=nullptr;CertAddEncodedCertificateToStore(store,X509_ASN_ENCODING,p->raw.p,static_cast<DWORD>(p->raw.len),CERT_STORE_ADD_ALWAYS,&cert);if(!leaf)leaf=cert;else if(cert)CertFreeCertificateContext(cert);}
    CERT_CHAIN_PARA params{};params.cbSize=sizeof(params);PCCERT_CHAIN_CONTEXT context=nullptr;bool valid=false;
    if(leaf && CertGetCertificateChain(nullptr,leaf,nullptr,store,&params,CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL,nullptr,&context)){
        int n=MultiByteToWideChar(CP_UTF8,0,host.c_str(),-1,nullptr,0);std::wstring name(n,L'\0');MultiByteToWideChar(CP_UTF8,0,host.c_str(),-1,name.data(),n);
        SSL_EXTRA_CERT_CHAIN_POLICY_PARA ssl{};ssl.cbSize=sizeof(ssl);ssl.dwAuthType=AUTHTYPE_SERVER;ssl.pwszServerName=name.data();
        CERT_CHAIN_POLICY_PARA policy{};policy.cbSize=sizeof(policy);policy.pvExtraPolicyPara=&ssl;
        CERT_CHAIN_POLICY_STATUS status{};status.cbSize=sizeof(status);valid=CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL,context,&policy,&status) && !status.dwError;
        CertFreeCertificateChain(context);
    }
    if(leaf)CertFreeCertificateContext(leaf);CertCloseStore(store,0);return valid;
}
#endif
struct Random {
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context context;
    Random(){mbedtls_entropy_init(&entropy);mbedtls_ctr_drbg_init(&context);if(mbedtls_ctr_drbg_seed(&context,mbedtls_entropy_func,&entropy,nullptr,0)){mbedtls_ctr_drbg_free(&context);mbedtls_entropy_free(&entropy);throw std::runtime_error("Cannot initialize random generator");}}
    ~Random(){mbedtls_ctr_drbg_free(&context);mbedtls_entropy_free(&entropy);}
};
struct TlsConfig {
    mbedtls_ssl_config config;
    mbedtls_x509_crt certificates,anchors;
    mbedtls_pk_context key;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context random;
    std::string host;
    TlsConfig(const NetTlsOptions& options,bool server,std::string hostname):host(std::move(hostname)){
        mbedtls_ssl_config_init(&config);mbedtls_x509_crt_init(&certificates);mbedtls_x509_crt_init(&anchors);mbedtls_pk_init(&key);mbedtls_entropy_init(&entropy);mbedtls_ctr_drbg_init(&random);
        try{
            if(mbedtls_ctr_drbg_seed(&random,mbedtls_entropy_func,&entropy,nullptr,0) || mbedtls_ssl_config_defaults(&config,server?MBEDTLS_SSL_IS_SERVER:MBEDTLS_SSL_IS_CLIENT,MBEDTLS_SSL_TRANSPORT_STREAM,MBEDTLS_SSL_PRESET_DEFAULT))throw std::runtime_error("Cannot initialize TLS");
            mbedtls_ssl_conf_rng(&config,mbedtls_ctr_drbg_random,&random);
            if(server){
                if(options.certFile.empty() || options.keyFile.empty() || mbedtls_x509_crt_parse_file(&certificates,options.certFile.c_str()) || mbedtls_pk_parse_keyfile(&key,options.keyFile.c_str(),nullptr,mbedtls_ctr_drbg_random,&random) || mbedtls_ssl_conf_own_cert(&config,&certificates,&key))throw std::runtime_error("Invalid TLS certificate or key");
                mbedtls_ssl_conf_authmode(&config,MBEDTLS_SSL_VERIFY_NONE);
            }else{
                std::string ca=options.caFile;
#if !defined(__APPLE__) && !defined(_WIN32)
                if(ca.empty())for(const char* file:{"/etc/ssl/certs/ca-certificates.crt","/etc/pki/tls/certs/ca-bundle.crt","/etc/ssl/ca-bundle.pem","/etc/ssl/cert.pem"})if(access(file,R_OK)==0){ca=file;break;}
                if(ca.empty())throw std::runtime_error("System CA bundle unavailable");
#endif
                if(!ca.empty()){
                    if(mbedtls_x509_crt_parse_file(&anchors,ca.c_str())<0)throw std::runtime_error("Cannot read CA bundle");mbedtls_ssl_conf_ca_chain(&config,&anchors,nullptr);
                }
#if defined(__APPLE__) || defined(_WIN32)
                else mbedtls_ssl_conf_verify(&config,[](void* context,mbedtls_x509_crt* cert,int depth,uint32_t* flags){auto* self=static_cast<TlsConfig*>(context);*flags=depth==0 && !platformTrust(cert,self->host)?MBEDTLS_X509_BADCERT_NOT_TRUSTED:0;return 0;},this);
#endif
                mbedtls_ssl_conf_authmode(&config,MBEDTLS_SSL_VERIFY_REQUIRED);
            }
        }catch(...){dispose();throw;}
    }
    void dispose(){mbedtls_ssl_config_free(&config);mbedtls_x509_crt_free(&certificates);mbedtls_x509_crt_free(&anchors);mbedtls_pk_free(&key);mbedtls_ctr_drbg_free(&random);mbedtls_entropy_free(&entropy);}
    ~TlsConfig(){dispose();}
};
struct SocketTransport;
struct UdpSocket {
    Socket fd=invalidSocket;
    std::map<std::string,std::weak_ptr<SocketTransport>> peers;
    ~UdpSocket(){if(fd!=invalidSocket)releaseSocket(fd);}
    void poll();
};
std::string peerKey(NetEndpoint e){return e.address+":"+std::to_string(e.port);}
struct SocketTransport final : Transport, std::enable_shared_from_this<SocketTransport> {
    Socket fd=invalidSocket;
    bool server=false,connecting=false,tlsReady=false,ending=false,udpReady=false,udpEnabled=false;
    size_t budget,frameLimit,pending=0,offset=0;
    std::deque<Bytes> output;
    Bytes input,fragments;
    bool fragmented=false;
    std::shared_ptr<TlsConfig> tlsConfig;
    mbedtls_ssl_context tls;
    Random randomness;
    std::shared_ptr<UdpSocket> udp;
    ResolvedAddress remoteAddress;
    std::string path="/pdg",authority,host,key;
    std::vector<std::string> origins;
    Time closeDeadline{},nextDatagram{};
    unsigned datagramStarts=0;
    SocketTransport(Socket socket,NetTransport transport,bool isServer,const NetLimits& limits):fd(socket),server(isServer),budget(limits.maxPendingBytes),frameLimit(limits.maxFrameSize){kind=transport;mbedtls_ssl_init(&tls);nonblocking(fd);int yes=1;setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,reinterpret_cast<const char*>(&yes),sizeof(yes));}
    ~SocketTransport(){mbedtls_ssl_free(&tls);if(fd!=invalidSocket)releaseSocket(fd);}
    void setupTls(std::shared_ptr<TlsConfig> config){
        secure=true;tlsConfig=std::move(config);if(mbedtls_ssl_setup(&tls,&tlsConfig->config))throw std::runtime_error("Cannot create TLS session");
        if(!server && mbedtls_ssl_set_hostname(&tls,host.c_str()))throw std::runtime_error("Cannot set TLS hostname");
        mbedtls_ssl_set_bio(&tls,this,[](void* context,const unsigned char* bytes,size_t size){auto* s=static_cast<SocketTransport*>(context);int n=sendSocket(s->fd,bytes,size);return n<0?(pendingError(socketError())?MBEDTLS_ERR_SSL_WANT_WRITE:MBEDTLS_ERR_NET_SEND_FAILED):n;},
            [](void* context,unsigned char* bytes,size_t size){auto* s=static_cast<SocketTransport*>(context);int n=static_cast<int>(::recv(s->fd,reinterpret_cast<char*>(bytes),static_cast<int>(size),0));return n<0?(pendingError(socketError())?MBEDTLS_ERR_SSL_WANT_READ:MBEDTLS_ERR_NET_RECV_FAILED):n;},nullptr);
    }
    void finish(){if(closed)return;closed=true;ready=false;udpReady=false;if(fd!=invalidSocket){releaseSocket(fd);fd=invalidSocket;}output.clear();pending=0;events.push_back({Event::Closed,{},{}});}
    void fail(std::string code,std::string message){if(closed)return;events.push_back({Event::Error,{}, {std::move(code),std::move(message),kind,remote}});finish();}
    bool queue(Bytes bytes){if(closed || bytes.size()>budget-pending || output.size()>=256){if(!closed)fail("ERR_BACKPRESSURE","Pending transport output limit exceeded");return false;}pending+=bytes.size();output.push_back(std::move(bytes));return true;}
    void announce(){if(ready || closed)return;ready=true;local=socketEndpoint(fd,false);remote=socketEndpoint(fd,true);events.push_back({Event::Ready,{},{}});}
    Bytes frame(const Bytes& bytes,uint8_t opcode){
        const bool mask=!server;Bytes out;out.push_back(0x80|opcode);
        if(bytes.size()<126)out.push_back((mask?0x80:0)|static_cast<uint8_t>(bytes.size()));
        else if(bytes.size()<=65535){out.push_back((mask?0x80:0)|126);out.push_back(bytes.size()>>8);out.push_back(bytes.size());}
        else{out.push_back((mask?0x80:0)|127);for(int i=7;i>=0;i--)out.push_back(static_cast<uint8_t>(uint64_t(bytes.size())>>(i*8)));}
        uint8_t masking[4]{};if(mask){if(mbedtls_ctr_drbg_random(&randomness.context,masking,4))throw std::runtime_error("Cannot mask WebSocket frame");out.insert(out.end(),masking,masking+4);}
        for(size_t i=0;i<bytes.size();i++)out.push_back(bytes[i]^(mask?masking[i%4]:0));return out;
    }
    bool write(Bytes bytes) override {if(!ready || ending || closed)return false;return queue(kind==NetTransport::WebSocket?frame(bytes,2):std::move(bytes));}
    void close(bool kill) override {if(closed)return;if(kill || !ready){finish();return;}if(ending)return;ending=true;closeDeadline=Clock::now()+std::chrono::seconds(2);if(kind==NetTransport::WebSocket)queue(frame({},8));}
    void beginHttp(){
        if(server)return;
        uint8_t bytes[16];if(mbedtls_ctr_drbg_random(&randomness.context,bytes,sizeof(bytes)))throw std::runtime_error("Cannot generate WebSocket key");key=base64(bytes,sizeof(bytes));
        std::string request="GET "+path+" HTTP/1.1\r\nHost: "+authority+"\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Key: "+key+"\r\nSec-WebSocket-Version: 13\r\nSec-WebSocket-Protocol: pdg-net-v1\r\n";
        if(!origin.empty())request+="Origin: "+origin+"\r\n";request+="\r\n";queue(Bytes(request.begin(),request.end()));
    }
    void http(){
        std::string text(input.begin(),input.end());auto end=text.find("\r\n\r\n");
        if(end==std::string::npos){if(input.size()>16384)fail("ERR_WEBSOCKET_PROTOCOL","HTTP upgrade headers exceed limit");return;}
        if(end>16384){fail("ERR_WEBSOCKET_PROTOCOL","HTTP upgrade headers exceed limit");return;}
        auto first=text.find("\r\n");std::string line=text.substr(0,first);std::map<std::string,std::string> headers;
        for(size_t start=first+2;start<end;){auto stop=text.find("\r\n",start),colon=text.find(':',start);if(colon==std::string::npos || colon>=stop){fail("ERR_WEBSOCKET_PROTOCOL","Invalid HTTP header");return;}auto name=lower(text.substr(start,colon-start));if(headers.count(name)){fail("ERR_WEBSOCKET_PROTOCOL","Duplicate HTTP header");return;}headers[name]=trim(text.substr(colon+1,stop-colon-1));start=stop+2;}
        if(lower(headers["upgrade"])!="websocket" || !token(headers["connection"],"upgrade")){fail("ERR_WEBSOCKET_PROTOCOL","WebSocket upgrade required");return;}
        if(server){
            auto space=line.find(' '),next=line.find(' ',space+1);if(space==std::string::npos || next==std::string::npos){fail("ERR_WEBSOCKET_PROTOCOL","Invalid HTTP request line");return;}auto requested=line.substr(space+1,next-space-1);auto query=requested.find('?');
            std::array<uint8_t,32> decoded{};size_t length=0;
            if(line.rfind("GET ",0)!=0 || line.substr(next)!=" HTTP/1.1" || requested.substr(0,query)!=path || headers["sec-websocket-version"]!="13" || mbedtls_base64_decode(decoded.data(),decoded.size(),&length,reinterpret_cast<const uint8_t*>(headers["sec-websocket-key"].data()),headers["sec-websocket-key"].size()) || length!=16 || !token(headers["sec-websocket-protocol"],"pdg-net-v1")){fail("ERR_WEBSOCKET_PROTOCOL","Invalid PDG WebSocket upgrade");return;}
            origin=headers["origin"];if(std::find(origins.begin(),origins.end(),origin)==origins.end() && std::find(origins.begin(),origins.end(),"*")==origins.end()){fail("ERR_WEBSOCKET_ORIGIN","WebSocket origin rejected");return;}
            auto response="HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: "+acceptKey(headers["sec-websocket-key"])+"\r\nSec-WebSocket-Protocol: pdg-net-v1\r\n\r\n";queue(Bytes(response.begin(),response.end()));
        }else if(line.rfind("HTTP/1.1 101 ",0)!=0 || headers["sec-websocket-accept"]!=acceptKey(key) || headers["sec-websocket-protocol"]!="pdg-net-v1"){fail("ERR_WEBSOCKET_PROTOCOL","PDG WebSocket upgrade rejected");return;}
        input.erase(input.begin(),input.begin()+end+4);announce();
    }
    void frames(){
        size_t consumed=0;
        for(unsigned count=0;count<64 && !closed;count++){
            auto available=input.size()-consumed;if(available<2)break;auto* p=input.data()+consumed;
            bool fin=p[0]&0x80,mask=p[1]&0x80;uint8_t op=p[0]&15;uint64_t length=p[1]&127;size_t prefix=2;
            if((p[0]&0x70) || mask!=server || (op!=0 && op!=2 && op!=8 && op!=9 && op!=10)){fail("ERR_WEBSOCKET_PROTOCOL","Invalid binary WebSocket frame");break;}
            if(length==126){if(available<4)break;length=(uint64_t(p[2])<<8)|p[3];prefix=4;if(length<126){fail("ERR_WEBSOCKET_PROTOCOL","Noncanonical frame length");break;}}
            else if(length==127){if(available<10)break;length=0;for(unsigned i=2;i<10;i++)length=(length<<8)|p[i];prefix=10;if(length<=65535 || (p[2]&128)){fail("ERR_WEBSOCKET_PROTOCOL","Invalid frame length");break;}}
            if((op>=8 && (!fin || length>125)) || length>budget || length>frameLimit+65540){fail("ERR_FRAME_TOO_LARGE","WebSocket frame exceeds limit");break;}
            if(mask)prefix+=4;if(available<prefix || length>available-prefix)break;
            Bytes bytes(static_cast<size_t>(length));for(size_t i=0;i<bytes.size();i++)bytes[i]=p[prefix+i]^(mask?p[prefix-4+i%4]:0);consumed+=prefix+bytes.size();
            if(op==8){if(bytes.size()==1){fail("ERR_WEBSOCKET_PROTOCOL","Invalid close frame");break;}if(!ending)queue(frame(bytes,8));ending=true;closeDeadline=Clock::now()+std::chrono::seconds(2);}
            else if(op==9)queue(frame(bytes,10));
            else if(op==10){}
            else{
                if((op==0 && !fragmented) || (op==2 && fragmented)){fail("ERR_WEBSOCKET_PROTOCOL","Invalid fragmented message");break;}
                if(bytes.size()>budget-fragments.size()){fail("ERR_BACKPRESSURE","Fragmented WebSocket message exceeds limit");break;}
                if(op==2 && fin)events.push_back({Event::Data,std::move(bytes),{}});
                else{fragments.insert(fragments.end(),bytes.begin(),bytes.end());fragmented=!fin;if(fin){events.push_back({Event::Data,std::move(fragments),{}});fragments.clear();}}
            }
        }
        if(consumed)input.erase(input.begin(),input.begin()+consumed);
    }
    void poll() override {
        if(closed)return;
        if(connecting){
#ifdef _WIN32
            fd_set set;FD_ZERO(&set);FD_SET(fd,&set);timeval wait{};if(select(0,nullptr,&set,nullptr,&wait)<=0)return;
#else
            pollfd descriptor{fd,POLLOUT,0};if(::poll(&descriptor,1,0)<=0)return;
#endif
            int error=0;
#ifdef _WIN32
            int size=sizeof(error);
#else
            socklen_t size=sizeof(error);
#endif
            getsockopt(fd,SOL_SOCKET,SO_ERROR,reinterpret_cast<char*>(&error),&size);if(error){fail("ERR_NETWORK_CONNECT","TCP connection failed");return;}connecting=false;local=socketEndpoint(fd,false);remote=socketEndpoint(fd,true);
            if(!secure){if(kind==NetTransport::Native)announce();else beginHttp();}
        }
        if(secure && !tlsReady){int status=mbedtls_ssl_handshake(&tls);if(status==MBEDTLS_ERR_SSL_WANT_READ || status==MBEDTLS_ERR_SSL_WANT_WRITE)return;
            if(status){fail(!server && mbedtls_ssl_get_verify_result(&tls)?"ERR_TLS_CERTIFICATE":"ERR_TLS_HANDSHAKE","TLS handshake failed");return;}tlsReady=true;beginHttp();}
        for(unsigned count=0;count<16 && !output.empty() && !closed;count++){
            auto& bytes=output.front();auto n=secure?mbedtls_ssl_write(&tls,bytes.data()+offset,bytes.size()-offset):sendSocket(fd,bytes.data()+offset,bytes.size()-offset);
            if(n<0){if((secure && (n==MBEDTLS_ERR_SSL_WANT_READ || n==MBEDTLS_ERR_SSL_WANT_WRITE)) || (!secure && pendingError(socketError())))break;fail("ERR_NETWORK_WRITE","Transport write failed");break;}
            if(!n)break;offset+=n;pending-=n;if(offset==bytes.size()){output.pop_front();offset=0;}
        }
        if(ending && (output.empty() || Clock::now()>=closeDeadline)){finish();return;}
        std::array<uint8_t,32768> buffer;
        for(unsigned count=0;count<16 && !closed && events.size()<64;count++){
            int n=secure?mbedtls_ssl_read(&tls,buffer.data(),std::min(buffer.size(),budget)):static_cast<int>(::recv(fd,reinterpret_cast<char*>(buffer.data()),std::min(buffer.size(),budget),0));
            if(n==0 || n==MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY){finish();break;}
            if(n<0){if((secure && (n==MBEDTLS_ERR_SSL_WANT_READ || n==MBEDTLS_ERR_SSL_WANT_WRITE)) || (!secure && pendingError(socketError())))break;fail("ERR_NETWORK_READ","Transport read failed");break;}
            if(kind==NetTransport::Native)events.push_back({Event::Data,Bytes(buffer.begin(),buffer.begin()+n),{}});
            else{if(static_cast<size_t>(n)>budget-input.size()){fail("ERR_BACKPRESSURE","Incoming WebSocket buffer exceeded limit");break;}input.insert(input.end(),buffer.begin(),buffer.begin()+n);if(!ready)http();if(ready)frames();}
        }
        if(udp){udp->poll();if(udpEnabled && !udpReady && datagramStarts<10 && Clock::now()>=nextDatagram){sendStart();nextDatagram=Clock::now()+std::chrono::milliseconds(500);datagramStarts++;}}
    }
    void sendStart(){static const std::string start="_pdg-dgram-start";if(udp)sendto(udp->fd,start.data(),static_cast<int>(start.size()),0,reinterpret_cast<const sockaddr*>(remoteAddress.address.data()),static_cast<int>(remoteAddress.address.size()));}
    void startDatagrams() override;
    bool datagramsReady() const override{return udpReady && !closed;}
    bool datagram(const Bytes& bytes) override {if(!udpReady || !udp || closed || bytes.size()>1492)return false;return sendto(udp->fd,reinterpret_cast<const char*>(bytes.data()),static_cast<int>(bytes.size()),0,reinterpret_cast<const sockaddr*>(remoteAddress.address.data()),static_cast<int>(remoteAddress.address.size()))==static_cast<int>(bytes.size());}
};
std::shared_ptr<UdpSocket> bindUdp(const ResolvedAddress& address){
    auto udp=std::make_shared<UdpSocket>();udp->fd=socket(address.family,SOCK_DGRAM,IPPROTO_UDP);if(udp->fd==invalidSocket)throw std::runtime_error("Cannot create UDP socket");nonblocking(udp->fd);
    if(bind(udp->fd,reinterpret_cast<const sockaddr*>(address.address.data()),static_cast<int>(address.address.size())))throw std::runtime_error("Cannot bind UDP socket");return udp;
}
void SocketTransport::startDatagrams(){
    if(kind!=NetTransport::Native || closed || udpEnabled)return;
    if(!udp){try{udp=bindUdp(resolve(local.address,local.port));}catch(...){return;}}
    udpEnabled=true;maxDatagramSize=1492;udp->peers[peerKey(remote)]=shared_from_this();sendStart();datagramStarts=1;nextDatagram=Clock::now()+std::chrono::milliseconds(500);
}
void UdpSocket::poll(){
    for(auto it=peers.begin();it!=peers.end();)if(it->second.expired())it=peers.erase(it);else ++it;
    std::array<uint8_t,1500> bytes;
    for(unsigned i=0;i<32;i++){
        sockaddr_storage source{};
#ifdef _WIN32
        int size=sizeof(source);
#else
        socklen_t size=sizeof(source);
#endif
        int n=static_cast<int>(recvfrom(fd,reinterpret_cast<char*>(bytes.data()),bytes.size(),0,reinterpret_cast<sockaddr*>(&source),&size));if(n<0)break;
        auto key=peerKey(endpoint(reinterpret_cast<sockaddr*>(&source)));auto it=peers.find(key);if(it==peers.end())continue;auto peer=it->second.lock();if(!peer || peer->closed){peers.erase(it);continue;}
        std::string_view value(reinterpret_cast<char*>(bytes.data()),n);
        if(value=="_pdg-dgram-start"){bool first=!peer->udpReady;peer->udpReady=true;if(peer->server || first)peer->sendStart();}
        else if(n<=1492 && peer->udpReady && peer->events.size()<64)peer->events.push_back({Event::Datagram,Bytes(bytes.begin(),bytes.begin()+n),{}});
    }
}
struct SocketListener final : Listener {
    Socket fd=invalidSocket;
    NetServerOptions options;
    std::shared_ptr<UdpSocket> udp;
    std::shared_ptr<TlsConfig> tls;
    ~SocketListener(){if(fd!=invalidSocket)releaseSocket(fd);}
    void close(bool) override {closed=true;ready=false;if(fd!=invalidSocket){releaseSocket(fd);fd=invalidSocket;}}
    void poll() override {
        if(closed)return;if(udp)udp->poll();
        for(unsigned count=0;count<32;count++){
            sockaddr_storage source{};
#ifdef _WIN32
            int size=sizeof(source);
#else
            socklen_t size=sizeof(source);
#endif
            Socket socket=accept(fd,reinterpret_cast<sockaddr*>(&source),&size);if(socket==invalidSocket)break;
            try{
                auto transport=std::make_shared<SocketTransport>(socket,address.transport,true,options);socket=invalidSocket;
                transport->local=socketEndpoint(transport->fd,false);transport->remote=endpoint(reinterpret_cast<sockaddr*>(&source));
                transport->remoteAddress.address.assign(reinterpret_cast<uint8_t*>(&source),reinterpret_cast<uint8_t*>(&source)+size);transport->remoteAddress.family=source.ss_family;
                if(address.transport==NetTransport::Native){transport->udp=udp;transport->announce();}
                else{transport->path=options.webSocket.path;transport->origins=options.webSocket.allowedOrigins;if(tls)transport->setupTls(tls);}
                accepted.push_back(std::move(transport));
            }catch(const std::exception& e){if(socket!=invalidSocket)releaseSocket(socket);error={"ERR_NETWORK_ACCEPT",e.what(),address.transport,address.endpoint};}
        }
    }
};
}
void initializeSockets(){
#ifdef _WIN32
    WSADATA value;if(WSAStartup(MAKEWORD(2,2),&value))throw std::runtime_error("Cannot initialize Winsock");
#endif
}
void shutdownSockets(){
#ifdef _WIN32
    WSACleanup();
#endif
}
ResolvedAddress resolve(const std::string& host,uint16_t port){
    addrinfo hints{},*addresses=nullptr;hints.ai_family=AF_UNSPEC;hints.ai_socktype=SOCK_STREAM;
    auto service=std::to_string(port);ResolvedAddress result;int error=getaddrinfo(host.c_str(),service.c_str(),&hints,&addresses);
    if(error || !addresses){result.error="Cannot resolve network endpoint";return result;}
    // Prefer IPv4 for localhost to match the default IPv4 PDG listener.
    auto* selected=addresses;for(auto* p=addresses;p;p=p->ai_next)if(p->ai_family==AF_INET){selected=p;break;}
    result.family=selected->ai_family;result.address.assign(reinterpret_cast<uint8_t*>(selected->ai_addr),reinterpret_cast<uint8_t*>(selected->ai_addr)+selected->ai_addrlen);freeaddrinfo(addresses);return result;
}
std::string urlHost(const std::string& url){return parseUrl(url).host;}
uint16_t urlPort(const std::string& url){return parseUrl(url).port;}
std::string urlPath(const std::string& url){return parseUrl(url).path;}
void validateLimits(const NetLimits& limits){if(limits.maxFrameSize==0 || limits.maxFrameSize>64*1024*1024 || limits.maxPendingBytes<1024 || limits.maxPendingBytes>64*1024*1024 || limits.maxFrameSize>limits.maxPendingBytes || limits.handshakeTimeout.count()<0)throw std::invalid_argument("Invalid networking limits");}
std::shared_ptr<Transport> connectSocket(const ResolvedAddress& address,const NetConnectOptions& info,const NetClientOptions& limits,NetTransport kind){
    auto fd=socket(address.family,SOCK_STREAM,IPPROTO_TCP);if(fd==invalidSocket)throw NetError{"ERR_NETWORK_SOCKET","Cannot create TCP socket",kind,{}};
    std::shared_ptr<SocketTransport> transport;
    try{
        transport=std::make_shared<SocketTransport>(fd,kind,false,limits);fd=invalidSocket;transport->remoteAddress=address;
        if(kind==NetTransport::WebSocket){auto url=parseUrl(info.webSocketUrl);transport->host=url.host;transport->path=url.path;transport->authority=url.authority;transport->origin=info.origin;
            if(info.origin.find_first_of("\r\n")!=std::string::npos)throw std::invalid_argument("Invalid WebSocket origin");
            if(url.scheme=="wss")transport->setupTls(std::make_shared<TlsConfig>(info.tls,false,url.host));else if(url.scheme!="ws")throw std::invalid_argument("WebSocket requires ws or wss URL");
        }
        transport->connecting=true;int status=::connect(transport->fd,reinterpret_cast<const sockaddr*>(address.address.data()),static_cast<int>(address.address.size()));
        if(status && !pendingError(socketError()))throw NetError{"ERR_NETWORK_CONNECT","TCP connection failed",kind,{}};
        return transport;
    }catch(...){if(fd!=invalidSocket)releaseSocket(fd);throw;}
}
std::shared_ptr<Listener> listenSocket(const ResolvedAddress& resolved,const NetServerOptions& opts,NetTransport kind){
    auto listener=std::make_shared<SocketListener>();listener->options=opts;listener->address.transport=kind;
    auto address=resolved;
    if(kind==NetTransport::WebSocket && opts.webSocket.secure)listener->tls=std::make_shared<TlsConfig>(opts.webSocket.tls,true,"");
    listener->fd=socket(address.family,SOCK_STREAM,IPPROTO_TCP);if(listener->fd==invalidSocket)throw NetError{"ERR_NETWORK_SOCKET","Cannot create listener",kind,{}};
    nonblocking(listener->fd);int yes=1;setsockopt(listener->fd,SOL_SOCKET,SO_REUSEADDR,reinterpret_cast<char*>(&yes),sizeof(yes));
    int status=bind(listener->fd,reinterpret_cast<const sockaddr*>(address.address.data()),static_cast<int>(address.address.size()));
    if(status && kind==NetTransport::Native && !opts.fixedPort && opts.serverPort){
        for(unsigned next=unsigned(opts.serverPort)+1;status && next<=65535 && next<unsigned(opts.serverPort)+100;next++){
            if(address.family==AF_INET)reinterpret_cast<sockaddr_in*>(address.address.data())->sin_port=htons(next);
            else reinterpret_cast<sockaddr_in6*>(address.address.data())->sin6_port=htons(next);
            status=bind(listener->fd,reinterpret_cast<const sockaddr*>(address.address.data()),static_cast<int>(address.address.size()));
        }
    }
    if(status)throw NetError{"ERR_LISTEN_BIND","Cannot bind TCP listener",kind,{}};
    if(::listen(listener->fd,128))throw NetError{"ERR_LISTEN_BIND","Cannot listen on TCP port",kind,{}};
    listener->address.endpoint=socketEndpoint(listener->fd,false);listener->address.secure=bool(listener->tls);
    if(kind==NetTransport::Native && !opts.noDatagram){address=resolve(listener->address.endpoint.address,listener->address.endpoint.port);try{listener->udp=bindUdp(address);}catch(const std::exception&){/* Reliable TCP remains available without UDP. */}}
    listener->ready=true;return listener;
}
} // namespace pdg::net_detail
