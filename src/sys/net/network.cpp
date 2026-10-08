#include "transport.h"
#include "pdg/sys/serializer.h"
#include "pdg/sys/deserializer.h"
#include "pdg/sys/serializable.h"
#include <cJSON.h>
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>
#include <stdexcept>
#include <thread>

namespace pdg {
using namespace net_detail;
namespace {
using Clock=std::chrono::steady_clock;
using Time=Clock::time_point;
uint32_t readNumber(const Bytes& bytes,size_t start,unsigned size){uint32_t value=0;for(unsigned i=0;i<size;i++)value=(value<<8)|bytes[start+i];return value;}
void appendNumber(Bytes& out,size_t value,unsigned size){for(int i=static_cast<int>(size)-1;i>=0;i--)out.push_back(static_cast<uint8_t>(value>>(i*8)));}
bool utf8(const std::string& value){
    const auto* bytes=reinterpret_cast<const uint8_t*>(value.data());
    for(size_t i=0;i<value.size();){auto first=bytes[i++];unsigned count=0;uint8_t low=0x80,high=0xbf;
        if(first<0x80)continue;if(first>=0xc2 && first<=0xdf)count=1;else if(first>=0xe0 && first<=0xef){count=2;if(first==0xe0)low=0xa0;if(first==0xed)high=0x9f;}
        else if(first>=0xf0 && first<=0xf4){count=3;if(first==0xf0)low=0x90;if(first==0xf4)high=0x8f;}else return false;
        if(count>value.size()-i)return false;if(bytes[i]<low || bytes[i]>high)return false;i++;while(--count)if(bytes[i++]<0x80 || bytes[i-1]>0xbf)return false;
    }return true;
}
void textValid(const std::string& value){if(value.find('\0')!=std::string::npos || !utf8(value))throw std::invalid_argument("Network strings require UTF-8 without embedded NUL");}
void jsonValid(const std::string& value){textValid(value);auto* parsed=cJSON_ParseWithOpts(value.c_str(),nullptr,1);if(!parsed)throw std::invalid_argument("Invalid JSON message");cJSON_Delete(parsed);}
void durationValid(std::chrono::milliseconds value,bool zero=false){if(value.count()<(zero?0:1) || value.count()>0xffffffff)throw std::invalid_argument("Invalid network timeout");}
Bytes commandFrame(char cmd,const std::string& text){if(text.size()>65535)throw std::invalid_argument("Handshake command exceeds limit");Bytes out{static_cast<uint8_t>(cmd)};appendNumber(out,text.size(),2);out.insert(out.end(),text.begin(),text.end());return out;}
std::string derivedUrl(const NetConnectOptions& opts,const char* scheme){auto host=opts.host;if(host.empty() || !opts.webPort || opts.webPath.empty() || opts.webPath.front()!='/')throw std::invalid_argument("Invalid web endpoint");if(host.find(':')!=std::string::npos && host.front()!='[')host="["+host+"]";return std::string(scheme)+"://"+host+":"+std::to_string(opts.webPort)+opts.webPath;}
}
struct NetCodec {
    static Bytes encode(const NetMessage& message){
        Serializer writer;switch(message.type_){
        case NetMessageType::String:writer.serialize_1u('s');writer.serialize_str(message.text_.c_str());break;
        case NetMessageType::Json:writer.serialize_1u('j');writer.serialize_str(message.text_.c_str());break;
        case NetMessageType::Bytes:writer.serialize_1u('b');writer.serialize_mem(message.data_.data(),static_cast<uint32>(message.data_.size()));break;
        case NetMessageType::MemBlock:writer.serialize_1u('m');writer.serialize_mem(message.data_.data(),static_cast<uint32>(message.data_.size()));break;
        case NetMessageType::Serializable:writer.serialize_1u('o');writer.serialize_obj(message.object_.get());break;
        }return Bytes(writer.getData().begin(),writer.getData().end());
    }
    static Bytes encode(const ISerializable& object){Serializer writer;writer.serialize_1u('o');writer.serialize_obj(&object);return Bytes(writer.getData().begin(),writer.getData().end());}
    static NetMessage decode(const Bytes& bytes){
        if(bytes.size()<3 || bytes.size()>0xffffffff)throw std::invalid_argument("Truncated serialized message");
        // Deserializer takes ownership of a malloc buffer in the native core.
        struct Reader:Deserializer{bool exhausted()const{return p==mDataEnd;}};Reader reader;auto* copy=std::malloc(bytes.size());if(!copy)throw std::bad_alloc();std::memcpy(copy,bytes.data(),bytes.size());reader.setDataPtr(copy,static_cast<uint32>(bytes.size()));
        NetMessage message;auto type=reader.deserialize_1u();
        if(type=='s' || type=='j'){
            auto size=reader.deserialize_strGetLen();if(size>bytes.size())throw std::invalid_argument("Invalid string length");std::vector<char> text(size+1);auto copied=reader.deserialize_str(text.data(),text.size());message.text_.assign(text.data(),copied);textValid(message.text_);message.type_=type=='s'?NetMessageType::String:NetMessageType::Json;if(type=='j')jsonValid(message.text_);
        }else if(type=='b' || type=='m'){
            auto size=reader.deserialize_memGetLen();if(size>bytes.size())throw std::invalid_argument("Invalid byte length");message.data_.resize(size);reader.deserialize_mem(message.data_.data(),size);message.type_=type=='b'?NetMessageType::Bytes:NetMessageType::MemBlock;
        }else if(type=='o'){
            auto* object=reader.deserialize_obj();if(!object)throw std::invalid_argument("Serializable class is not registered");message.object_={object,[](ISerializable* p){p->release();}};message.type_=NetMessageType::Serializable;
        }else throw std::invalid_argument("Unknown serialized message type");
        if(!reader.exhausted())throw std::invalid_argument("Trailing serialized data");
        return message;
    }
};
NetMessage NetMessage::string(std::string value){textValid(value);NetMessage message;message.text_=std::move(value);return message;}
NetMessage NetMessage::json(std::string value){jsonValid(value);NetMessage message;message.type_=NetMessageType::Json;message.text_=std::move(value);return message;}
NetMessage NetMessage::bytes(std::span<const uint8_t> value){if(value.size()>64*1024*1024)throw std::invalid_argument("Message exceeds supported limit");NetMessage message;message.type_=NetMessageType::Bytes;message.data_.assign(value.begin(),value.end());return message;}
NetMessage NetMessage::memBlock(std::span<const uint8_t> value){auto message=bytes(value);message.type_=NetMessageType::MemBlock;return message;}
struct NetAccess {
    using Runtime=NetRuntime::Impl;
    using Connection=NetConnection::Impl;
    using Client=NetClient::Impl;
    using Server=NetServer::Impl;
    static NetConnectionPtr wrap(const std::shared_ptr<Connection>&);
    static std::shared_ptr<Connection> get(const NetConnectionPtr& value){return value->impl_;}
};
struct NetRuntime::Impl : std::enable_shared_from_this<Impl> {
    const std::thread::id owner=std::this_thread::get_id();
    bool polling=false,stopping=false;
    std::atomic<bool> alive{true};
    std::mutex mutex;
    std::condition_variable wake;
    std::deque<std::function<void()>> tasks,lookups;
    std::vector<std::shared_ptr<NetAccess::Connection>> connections;
    std::vector<std::weak_ptr<NetAccess::Server>> servers;
    std::map<std::string,Time> failedEndpoints;
    std::thread resolver;
    Impl(){initializeSockets();resolver=std::thread([this]{for(;;){std::function<void()> job;{std::unique_lock<std::mutex> lock(mutex);wake.wait(lock,[this]{return stopping || !lookups.empty();});if(stopping)break;job=std::move(lookups.front());lookups.pop_front();}job();}});}
    void stopResolver(){{std::lock_guard<std::mutex> lock(mutex);stopping=true;lookups.clear();}wake.notify_all();if(resolver.joinable())resolver.join();}
    ~Impl(){stopResolver();shutdownSockets();}
    void check() const {if(std::this_thread::get_id()!=owner)throw std::logic_error("Networking must run on its runtime thread");if(!alive)throw std::logic_error("Network runtime is shut down");}
    void post(std::function<void()> fn){std::lock_guard<std::mutex> lock(mutex);if(alive)tasks.push_back(std::move(fn));}
    void lookup(std::string host,uint16_t port,std::function<void(ResolvedAddress)> fn){
        auto weak=weak_from_this();std::lock_guard<std::mutex> lock(mutex);if(lookups.size()>=1024)throw NetError{"ERR_BACKPRESSURE","Too many endpoint lookups",NetTransport::Native,{}};
        lookups.push_back([weak,host=std::move(host),port,fn=std::move(fn)]{auto address=resolve(host,port);if(auto self=weak.lock())self->post([fn,address=std::move(address)]()mutable{fn(std::move(address));});});wake.notify_one();
    }
};
struct NetConnection::Impl : std::enable_shared_from_this<Impl> {
    std::weak_ptr<NetAccess::Runtime> runtime;
    std::weak_ptr<NetConnection> facade;
    std::shared_ptr<Transport> io;
    NetClientOptions limits;
    bool server=false,required=false,complete=false,started=false,closing=false,closed=false,errorReported=false,remoteDgram=false,advertised=false,versionSeen=false;
    Bytes input;
    std::string key;
    Time deadline=Time::max(), overallDeadline=Time::max();
    MessageCallback messageCallback;
    std::function<void()> closeCallback;
    std::function<void(const NetError&)> errorCallback;
    std::function<bool(const std::string&,const std::string&)> checkKey;
    std::function<void(NetConnectionPtr)> opened;
    void check(){auto owner=runtime.lock();if(!owner)throw std::logic_error("Network runtime is gone");owner->check();}
    NetError error(std::string code,std::string message)const{return {std::move(code),std::move(message),io?io->kind:NetTransport::Native,io?io->remote:NetEndpoint{}};}
    void report(NetError e){if(errorReported || closed)return;errorReported=true;auto callback=errorCallback;if(callback)callback(e);}
    void fail(std::string code,std::string message){if(closed)return;closing=true;if(io)io->close(true);report(error(std::move(code),std::move(message)));}
    void close(bool kill){if(closed)return;closing=true;if(io)io->close(kill);else finish();}
    void finish(){if(closed)return;if(!complete && !errorReported)report(error("ERR_HANDSHAKE_CLOSED","Connection closed before PDG handshake completed"));closed=true;complete=false;input.clear();auto callback=closeCallback;closeCallback={};opened={};checkKey={};messageCallback={};if(callback)callback();}
    bool datagrams()const{return complete && !closed && !closing && !limits.noDatagram && io && io->datagramsReady() && (io->kind!=NetTransport::WebTransport || remoteDgram);}
    void version(){if(io->kind==NetTransport::WebTransport && !advertised){advertised=true;io->write(commandFrame('D',!limits.noDatagram && io->maxDatagramSize?"1":"0"));}io->write(commandFrame('V',"1"));}
    void established(){if(complete || closed || closing)return;complete=true;deadline=Time::max();auto callback=opened;opened={};auto connection=NetAccess::wrap(shared_from_this());if(callback)callback(connection);if(!closing && io->kind==NetTransport::Native && !limits.noDatagram)io->startDatagrams();}
    void start(){if(started || closed)return;started=true;deadline=overallDeadline;if(limits.handshakeTimeout.count()>0)deadline=std::min(deadline,Clock::now()+limits.handshakeTimeout);
        if(!server){if(!key.empty())io->write(commandFrame('K',key));version();}}
    void handle(char command,const std::string& value){
        if(command=='D' && io->kind==NetTransport::WebTransport && !complete && (value=="0" || value=="1")){remoteDgram=value=="1";return;}
        if(command=='K' && server && !versionSeen && !complete){if(!checkKey || !checkKey(value,io->remote.address)){fail("ERR_BAD_CLIENT_KEY","Client reservation key rejected");return;}required=false;return;}
        if(command!='V' || complete || required || value.empty() || value.size()>9 || value.find_first_not_of("0123456789")!=std::string::npos){fail(required?"ERR_BAD_CLIENT_KEY":"ERR_UNSUPPORTED_PROTOCOL","Invalid PDG handshake command");return;}
        auto versionNumber=std::stoul(value);if(versionNumber<1){fail("ERR_UNSUPPORTED_PROTOCOL","Invalid PDG protocol version");return;}
        if(server){if(!versionSeen){versionSeen=true;version();if(versionNumber==1)established();}else if(versionNumber==1)established();else fail("ERR_UNSUPPORTED_PROTOCOL","Client rejected PDG protocol version");}
        else if(versionNumber==1)established();else fail("ERR_UNSUPPORTED_PROTOCOL","Server requires an unsupported PDG protocol version");
    }
    void deliver(const Bytes& bytes,NetDelivery delivery){
        if(closed || closing || !complete)return;if(bytes.size()>limits.maxFrameSize){fail("ERR_FRAME_TOO_LARGE","Incoming message exceeds frame limit");return;}NetMessage message;
        try{message=NetCodec::decode(bytes);}catch(const std::exception& e){fail("ERR_REMOTE_BAD_DATA",e.what());return;}
        auto callback=messageCallback;if(callback){auto connection=NetAccess::wrap(shared_from_this());callback(*connection,message,delivery);}
    }
    void receive(Bytes bytes){
        if(bytes.size()>limits.maxPendingBytes-input.size()){fail("ERR_BACKPRESSURE","Incoming PDG buffer limit exceeded");return;}input.insert(input.end(),bytes.begin(),bytes.end());size_t offset=0;
        for(unsigned frames=0;frames<256 && !closing;frames++){
            if(input.size()-offset<3)break;char cmd=static_cast<char>(input[offset]);unsigned prefix=cmd=='A'?5:3;if(input.size()-offset<prefix)break;
            if(cmd!='A' && cmd!='V' && cmd!='K' && !(cmd=='D' && io->kind==NetTransport::WebTransport)){fail("ERR_REMOTE_BAD_DATA","Unknown PDG frame command");break;}
            auto length=readNumber(input,offset+1,prefix-1);if(length>limits.maxFrameSize){fail("ERR_FRAME_TOO_LARGE","Incoming PDG frame exceeds limit");break;}
            if(length>input.size()-offset-prefix)break;auto start=input.begin()+offset+prefix;
            if(cmd=='A'){if(!complete){fail("ERR_HANDSHAKE_REQUIRED","Application data arrived before authentication");break;}deliver(Bytes(start,start+length),NetDelivery::Reliable);}
            else handle(cmd,std::string(start,start+length));offset+=prefix+length;
        }
        if(offset)input.erase(input.begin(),input.begin()+offset);
    }
    void send(Bytes bytes,bool datagram){check();if(!complete || closing || closed)throw std::logic_error("Connection is not established");if(bytes.size()>limits.maxFrameSize)throw error("ERR_FRAME_TOO_LARGE","Reliable message exceeds frame limit");
        if(datagram && datagrams() && bytes.size()<=io->maxDatagramSize && io->datagram(bytes))return;
        Bytes frame{'A'};appendNumber(frame,bytes.size(),4);frame.insert(frame.end(),bytes.begin(),bytes.end());if(!io->write(std::move(frame)) && !io->closed)fail("ERR_BACKPRESSURE","Transport rejected reliable output");
    }
    void poll(){
        if(closed)return;if(deadline!=Time::max() && Clock::now()>=deadline){fail(started?"ERR_HANDSHAKE_TIMEOUT":"ERR_CONNECT_TIMEOUT","Connection establishment timed out");if(!io)finish();}
        if(io){io->poll();if(io->ready && !started)start();
            for(unsigned i=0;i<64 && !io->events.empty();i++){
                auto event=std::move(io->events.front());io->events.pop_front();
                if(event.type==Event::Ready)start();else if(event.type==Event::Data && !closing)receive(std::move(event.bytes));
                else if(event.type==Event::Datagram && datagrams())deliver(event.bytes,NetDelivery::Unreliable);
                else if(event.type==Event::Error){closing=true;report(std::move(event.error));}
                else if(event.type==Event::Closed)finish();
            }
            if(!input.empty() && !closing)receive({});
        }
    }
};
NetConnectionPtr NetAccess::wrap(const std::shared_ptr<Connection>& impl){if(auto object=impl->facade.lock())return object;auto object=NetConnectionPtr(new NetConnection(impl));impl->facade=object;return object;}
struct NetClient::Impl : std::enable_shared_from_this<Impl> {
    std::weak_ptr<NetAccess::Runtime> runtime;
    NetClientOptions options;
    NetConnectOptions info;
    std::function<void(const NetError&)> errors;
    std::function<void(NetConnectionPtr)> connected;
    std::shared_ptr<NetAccess::Connection> pending;
    std::string key,cacheKey;
    Time deadline;
    uint64_t generation=0;
    bool active=false;
    void check(){auto owner=runtime.lock();if(!owner)throw std::logic_error("Network runtime is gone");owner->check();}
    void cancel(){generation++;active=false;connected={};if(pending){pending->opened={};pending->errorCallback={};pending->close(true);pending.reset();}}
    void failed(uint64_t token,NetError error){
        if(token!=generation || !active)return;auto owner=runtime.lock();if(!owner)return;
        bool fallback=pending && !pending->started && error.transport==NetTransport::WebTransport && info.transportPolicy==NetTransportPolicy::Auto && (error.code=="ERR_TRANSPORT_UNAVAILABLE" || error.code=="ERR_WEBTRANSPORT_UNSUPPORTED" || error.code=="ERR_CONNECT_TIMEOUT");
        if(fallback && Clock::now()<deadline){
            if(info.capabilityCacheTimeout.count() && error.code!="ERR_TRANSPORT_UNAVAILABLE"){
                for(auto it=owner->failedEndpoints.begin();it!=owner->failedEndpoints.end();)if(it->second<=Clock::now())it=owner->failedEndpoints.erase(it);else ++it;
                if(owner->failedEndpoints.size()>=128)owner->failedEndpoints.erase(owner->failedEndpoints.begin());owner->failedEndpoints[cacheKey]=Clock::now()+info.capabilityCacheTimeout;
            }
            auto previous=pending;previous->opened={};previous->errorCallback={};previous->close(true);pending.reset();start(NetTransport::WebSocket);return;
        }
        active=false;connected={};if(pending){pending->opened={};pending->close(true);}auto callback=errors;if(callback)callback(error);
    }
    void start(NetTransport kind){
        auto owner=runtime.lock();if(!owner || !owner->alive)return;auto token=++generation;
        auto connection=std::make_shared<NetAccess::Connection>();connection->runtime=owner;connection->limits=options;connection->key=key;
        auto remaining=std::chrono::duration_cast<std::chrono::milliseconds>(deadline-Clock::now());
        auto attempt=kind==NetTransport::WebTransport && info.transportPolicy==NetTransportPolicy::Auto?std::min(remaining,info.webTransportTimeout):remaining;
        connection->overallDeadline=deadline;connection->deadline=Clock::now()+attempt;pending=connection;owner->connections.push_back(connection);auto weak=weak_from_this();
        connection->errorCallback=[weak,token,connectionWeak=std::weak_ptr<NetAccess::Connection>(connection)](const NetError& e){if(auto self=weak.lock()){if(self->active)self->failed(token,e);else if(auto c=connectionWeak.lock();c && c->complete){auto callback=self->errors;if(callback)callback(e);}}};
        connection->opened=[weak,token](NetConnectionPtr value){if(auto self=weak.lock()){if(!self->active || token!=self->generation){value->close(true);return;}self->active=false;self->pending.reset();auto callback=std::move(self->connected);if(callback)callback(value);}else value->close(true);};
        // Replace the attempt deadline with the overall deadline once transport is ready.
        if(remaining.count()<=0){connection->fail("ERR_CONNECT_TIMEOUT","Overall connection deadline elapsed");return;}
        try{
            if(kind==NetTransport::WebTransport){auto opts=info;opts.timeout=attempt;connection->io=connectWebTransport(opts,options);}
            else{
                std::string host=kind==NetTransport::Native?info.host:urlHost(info.webSocketUrl);uint16_t port=kind==NetTransport::Native?info.port:urlPort(info.webSocketUrl);
                owner->lookup(host,port,[weak,token,connection,kind](ResolvedAddress address){auto self=weak.lock();if(!self || !self->active || token!=self->generation || connection->closing)return;
                    if(!address.error.empty()){connection->fail("ERR_NETWORK_DNS",address.error);return;}
                    try{connection->io=connectSocket(address,self->info,self->options,kind);}catch(const NetError& e){connection->report(e);connection->close(true);}catch(const std::exception& e){connection->report({"ERR_TLS_CONFIG",e.what(),kind,{}});connection->close(true);}
                });
            }
        }catch(const NetError& e){connection->report(e);connection->close(true);}catch(const std::exception& e){connection->report({"ERR_TRANSPORT_CONFIG",e.what(),kind,{}});connection->close(true);}
    }
};
struct NetServer::Impl : std::enable_shared_from_this<Impl> {
    std::weak_ptr<NetAccess::Runtime> runtime;
    NetServerOptions options;
    bool starting=false,listening=false,cancelled=false,failedStartup=false;
    uint64_t generation=0;
    size_t pendingStarts=0;
    Time startupDeadline;
    std::vector<std::shared_ptr<Listener>> hosts;
    std::vector<std::weak_ptr<NetAccess::Connection>> pending;
    std::vector<NetConnectionPtr> accepted;
    std::function<bool(NetConnectionPtr)> connected;
    std::function<void(const std::vector<NetListener>&)> ready;
    std::function<void(const NetError&)> errors;
    struct Reservation{std::string key,ip;Time until;bool once;};
    std::vector<Reservation> reservations;
    std::map<std::string,std::pair<Time,size_t>> attempts;
    void check(){auto owner=runtime.lock();if(!owner)throw std::logic_error("Network runtime is gone");owner->check();}
    void report(const NetError& error){auto callback=errors;if(callback)callback(error);}
    bool keyAllowed(const std::string& key,const std::string& ip){
        if(!options.reservationRequired)return true;auto now=Clock::now();reservations.erase(std::remove_if(reservations.begin(),reservations.end(),[now](const auto& item){return item.until<now;}),reservations.end());
        for(auto it=reservations.begin();it!=reservations.end();it++)if(it->key==key && (it->ip=="*" || it->ip==ip)){if(it->once)reservations.erase(it);return true;}return false;
    }
    std::vector<NetListener> addresses()const{std::vector<NetListener> result;for(auto& host:hosts)if(host->ready && !host->closed)result.push_back(host->address);return result;}
    void shutdown(bool closeExisting,bool kill){
        cancelled=true;generation++;starting=false;listening=false;
        for(auto& host:hosts){host->close(closeExisting);for(auto& socket:host->accepted)socket->close(true);host->accepted.clear();}
        for(auto& item:pending)if(auto c=item.lock())c->close(true);pending.clear();
        if(closeExisting){auto connections=accepted;for(auto& c:connections)NetAccess::get(c)->close(kill);accepted.clear();}
    }
    void startupError(NetError error){if(cancelled)return;failedStartup=true;if(!options.allowPartialListen){shutdown(true,true);report(error);}else report(error);}
    void start(NetTransport kind){
        auto owner=runtime.lock();auto token=generation;auto weak=weak_from_this();pendingStarts++;
        if(kind==NetTransport::WebTransport){try{hosts.push_back(listenWebTransport(options));}catch(const NetError& e){startupError(e);}catch(const std::exception& e){startupError({"ERR_LISTEN_CONFIG",e.what(),kind,{}});}pendingStarts--;return;}
        const auto& web=options.webSocket;auto host=kind==NetTransport::Native?options.serverAddr:(web.host.empty()?options.serverAddr:web.host);auto port=kind==NetTransport::Native?options.serverPort:web.port;
        owner->lookup(host,port,[weak,token,kind,host,port](ResolvedAddress address){auto self=weak.lock();if(!self || self->cancelled || token!=self->generation)return;self->pendingStarts--;
            if(!address.error.empty()){self->startupError({"ERR_NETWORK_DNS",address.error,kind,{host,port}});return;}
            try{self->hosts.push_back(listenSocket(address,self->options,kind));}catch(const NetError& e){self->startupError(e);}catch(const std::exception& e){self->startupError({"ERR_LISTEN_CONFIG",e.what(),kind,{host,port}});}
        });
    }
    void accept(std::shared_ptr<Transport> socket){
        auto owner=runtime.lock();if(!owner || !listening){socket->close(true);return;}
        size_t ipCount=0;for(auto& connection:accepted)if(connection->remoteEndpoint().address==socket->remote.address)ipCount++;
        for(auto& item:pending)if(auto c=item.lock();c && c->io && c->io->remote.address==socket->remote.address)ipCount++;
        for(auto it=attempts.begin();it!=attempts.end();)if(Clock::now()-it->second.first>std::chrono::minutes(1))it=attempts.erase(it);else ++it;
        if(attempts.size()>=4096 && !attempts.count(socket->remote.address)){socket->close(true);return;}
        auto& rate=attempts[socket->remote.address];if(rate.second==0)rate.first=Clock::now();rate.second++;
        if(owner->connections.size()>=4096 || pending.size()>=options.maxIncompleteHandshakes || accepted.size()+pending.size()>=options.maxConnections || ipCount>=options.maxConnectionsPerIP || rate.second>options.maxConnectionsPerMinute){socket->close(true);return;}
        auto connection=std::make_shared<NetAccess::Connection>();connection->runtime=owner;connection->io=std::move(socket);connection->server=true;connection->required=options.reservationRequired;
        static_cast<NetLimits&>(connection->limits)=options;connection->limits.noDatagram=options.noDatagram;
        if(options.handshakeTimeout.count())connection->overallDeadline=connection->deadline=Clock::now()+options.handshakeTimeout;
        auto weak=weak_from_this();connection->checkKey=[weak](const std::string& key,const std::string& ip){auto self=weak.lock();return self && self->keyAllowed(key,ip);};
        connection->errorCallback=[weak](const NetError& error){if(auto self=weak.lock())self->report(error);};
        connection->opened=[weak](NetConnectionPtr value){auto self=weak.lock();if(!self || !self->listening){value->close(true);return;}
            auto io=NetAccess::get(value)->io;
            if(io->kind==NetTransport::WebSocket){size_t count=0;for(auto& c:self->accepted)if(c->connected() && NetAccess::get(c)->io->origin==io->origin)count++;
                if(count>=self->options.maxConnectionsPerOrigin){value->close(true);self->report({"ERR_CONNECTION_LIMIT","WebSocket origin connection limit exceeded",io->kind,io->remote});return;}}
            auto callback=self->connected;
            try{if(callback && callback(value) && self->listening)self->accepted.push_back(value);else value->close(true);}catch(...){value->close(true);throw;}
        };
        pending.push_back(connection);owner->connections.push_back(std::move(connection));
    }
    void poll(){
        if(cancelled)return;
        pending.erase(std::remove_if(pending.begin(),pending.end(),[](const auto& item){auto c=item.lock();return !c || c->closed || c->complete;}),pending.end());
        accepted.erase(std::remove_if(accepted.begin(),accepted.end(),[](const auto& c){return !c->connected();}),accepted.end());
        for(auto& host:hosts){host->poll();if(!host->error.code.empty()){auto error=std::move(host->error);host->error={};host->close(true);startupError(std::move(error));if(cancelled)return;}}
        if(starting && Clock::now()>=startupDeadline){for(auto& host:hosts)if(!host->ready)host->close(true);pendingStarts=0;generation++;startupError({"ERR_CONNECT_TIMEOUT","Listener startup timed out",NetTransport::Native,{}});if(cancelled)return;}
        if(starting && pendingStarts==0){bool waiting=false;for(auto& host:hosts)if(!host->ready && !host->closed)waiting=true;
            if(!waiting){starting=false;listening=!addresses().empty();if(!listening){if(!failedStartup)startupError({"ERR_LISTEN_CONFIG","No listeners started",NetTransport::Native,{}});return;}auto callback=ready;if(callback)callback(addresses());}
        }
        for(auto& host:hosts){if(!listening){while(host->accepted.size()>options.maxIncompleteHandshakes){host->accepted.front()->close(true);host->accepted.pop_front();}continue;}
            while(!host->accepted.empty()){auto transport=std::move(host->accepted.front());host->accepted.pop_front();accept(std::move(transport));}}
    }
};
NetRuntime::NetRuntime():impl_(std::make_shared<Impl>()){}
NetRuntime::~NetRuntime(){impl_->alive=false;impl_->stopResolver();for(auto& connection:impl_->connections){connection->opened={};connection->errorCallback={};connection->closeCallback={};connection->messageCallback={};}for(auto& item:impl_->servers)if(auto server=item.lock()){server->errors={};server->ready={};server->connected={};server->shutdown(true,true);}
    for(auto& connection:impl_->connections){connection->opened={};connection->errorCallback={};connection->closeCallback={};connection->messageCallback={};if(connection->io)connection->io->close(true);connection->closed=true;connection->complete=false;}
    impl_->connections.clear();{std::lock_guard<std::mutex> lock(impl_->mutex);impl_->tasks.clear();impl_->lookups.clear();}}
void NetRuntime::poll(){impl_->check();if(impl_->polling)throw std::logic_error("Recursive networking poll");impl_->polling=true;struct Reset{bool& value;~Reset(){value=false;}} reset{impl_->polling};
    std::deque<std::function<void()>> tasks;{std::lock_guard<std::mutex> lock(impl_->mutex);tasks.swap(impl_->tasks);}for(auto& task:tasks)task();
    auto servers=impl_->servers;for(auto& item:servers)if(auto server=item.lock())server->poll();
    auto connections=impl_->connections;for(auto& connection:connections)connection->poll();
    impl_->connections.erase(std::remove_if(impl_->connections.begin(),impl_->connections.end(),[](const auto& c){return c->closed;}),impl_->connections.end());
    impl_->servers.erase(std::remove_if(impl_->servers.begin(),impl_->servers.end(),[](const auto& s){return s.expired();}),impl_->servers.end());
}
NetConnection::NetConnection(std::shared_ptr<Impl> value):impl_(std::move(value)){}
NetConnection& NetConnection::send(const NetMessage& message){impl_->check();impl_->send(NetCodec::encode(message),false);return *this;}
NetConnection& NetConnection::send(const std::string& message){return send(NetMessage::string(message));}
NetConnection& NetConnection::send(const ISerializable& message){impl_->check();impl_->send(NetCodec::encode(message),false);return *this;}
NetConnection& NetConnection::send(std::span<const uint8_t> message){return send(NetMessage::bytes(message));}
NetConnection& NetConnection::sendJson(const std::string& json){return send(NetMessage::json(json));}
NetConnection& NetConnection::sendDgram(const NetMessage& message){impl_->check();impl_->send(NetCodec::encode(message),true);return *this;}
NetConnection& NetConnection::sendDgram(const std::string& message){return sendDgram(NetMessage::string(message));}
NetConnection& NetConnection::sendDgram(const ISerializable& message){impl_->check();impl_->send(NetCodec::encode(message),true);return *this;}
NetConnection& NetConnection::sendDgram(std::span<const uint8_t> message){return sendDgram(NetMessage::bytes(message));}
NetConnection& NetConnection::onMessage(MessageCallback callback){impl_->check();impl_->messageCallback=std::move(callback);return *this;}
NetConnection& NetConnection::onClose(std::function<void()> callback){impl_->check();impl_->closeCallback=std::move(callback);return *this;}
NetConnection& NetConnection::onError(std::function<void(const NetError&)> callback){impl_->check();impl_->errorCallback=std::move(callback);return *this;}
void NetConnection::close(bool kill){impl_->check();impl_->close(kill);}
bool NetConnection::connected()const{impl_->check();return impl_->complete && !impl_->closing && !impl_->closed;}
bool NetConnection::hasDgram()const{impl_->check();return impl_->datagrams();}
bool NetConnection::secure()const{impl_->check();return impl_->io && impl_->io->secure;}
NetTransport NetConnection::transport()const{impl_->check();return impl_->io?impl_->io->kind:NetTransport::Native;}
NetEndpoint NetConnection::localEndpoint()const{impl_->check();return impl_->io?impl_->io->local:NetEndpoint{};}
NetEndpoint NetConnection::remoteEndpoint()const{impl_->check();return impl_->io?impl_->io->remote:NetEndpoint{};}
NetClient::NetClient(NetRuntime& runtime,NetClientOptions options):impl_(std::make_shared<Impl>()){runtime.impl_->check();validateLimits(options);impl_->runtime=runtime.impl_;impl_->options=options;}
NetClient::~NetClient(){impl_->cancel();}
NetClient& NetClient::onError(std::function<void(const NetError&)> callback){impl_->check();impl_->errors=std::move(callback);return *this;}
void NetClient::cancelConnect(){impl_->check();impl_->cancel();}
NetClient& NetClient::connect(NetConnectOptions options,std::function<void(NetConnectionPtr)> callback,std::string key){
    impl_->check();durationValid(options.timeout);durationValid(options.webTransportTimeout);durationValid(options.capabilityCacheTimeout,true);textValid(key);if(key.size()>65535)throw std::invalid_argument("Reservation key exceeds handshake limit");
    if(!callback)throw std::invalid_argument("Connection callback required");if(impl_->active)throw std::logic_error("Connection attempt already in progress");
    auto owner=impl_->runtime.lock();if(owner->connections.size()>=4096)throw std::runtime_error("Too many network connections");
    auto kind=NetTransport::Native;
    if(options.transportPolicy==NetTransportPolicy::WebTransportRequired || (options.transportPolicy==NetTransportPolicy::Auto && !options.webTransportUrl.empty()))kind=NetTransport::WebTransport;
    else if(options.transportPolicy==NetTransportPolicy::WebSocketOnly || (options.transportPolicy==NetTransportPolicy::Auto && !options.webSocketUrl.empty()))kind=NetTransport::WebSocket;
    if(options.webTransportUrl.empty() && kind==NetTransport::WebTransport)options.webTransportUrl=derivedUrl(options,"https");
    if(options.webSocketUrl.empty() && kind!=NetTransport::Native)options.webSocketUrl=options.webTransportUrl.empty()?derivedUrl(options,"wss"):"wss"+options.webTransportUrl.substr(5);
    if(!options.webTransportUrl.empty()){if(options.webTransportUrl.rfind("https://",0)!=0)throw std::invalid_argument("WebTransport requires HTTPS");urlHost(options.webTransportUrl);}
    if(!options.webSocketUrl.empty()){if(options.webSocketUrl.rfind("ws://",0)!=0 && options.webSocketUrl.rfind("wss://",0)!=0)throw std::invalid_argument("WebSocket requires ws or wss");urlHost(options.webSocketUrl);}
    std::string cache=options.webTransportUrl+"|"+options.tls.caFile;for(auto& pin:options.tls.serverCertificateHashes){if(pin.size()!=64 || pin.find_first_not_of("0123456789abcdef")!=std::string::npos)throw std::invalid_argument("Certificate hashes require lowercase SHA-256 hex");cache+="|"+pin;}
    if(kind==NetTransport::WebTransport && options.capabilityCacheTimeout.count() && options.transportPolicy==NetTransportPolicy::Auto && owner->failedEndpoints.count(cache) && owner->failedEndpoints[cache]>Clock::now())kind=NetTransport::WebSocket;
    impl_->info=std::move(options);impl_->cacheKey=std::move(cache);impl_->key=std::move(key);impl_->connected=std::move(callback);impl_->active=true;impl_->deadline=Clock::now()+impl_->info.timeout;impl_->start(kind);return *this;
}
NetServer::NetServer(NetRuntime& runtime,NetServerOptions options):impl_(std::make_shared<Impl>()){
    runtime.impl_->check();validateLimits(options);durationValid(options.idleTimeout);for(auto n:{options.maxConnections,options.maxConnectionsPerIP,options.maxConnectionsPerOrigin,options.maxConnectionsPerMinute,options.maxIncompleteHandshakes})if(n==0 || n>4096)throw std::invalid_argument("Invalid network admission limit");
    for(const auto* listener:{&options.webSocket,&options.webTransport})if(listener->enabled && (listener->path.empty() || listener->path.front()!='/' || listener->path.find_first_of("\r\n")!=std::string::npos))throw std::invalid_argument("Invalid web listener path");
    if(options.webTransport.enabled && !options.webTransport.secure)throw std::invalid_argument("WebTransport requires TLS");
    impl_->runtime=runtime.impl_;impl_->options=std::move(options);runtime.impl_->servers.push_back(impl_);
}
NetServer::~NetServer(){impl_->errors={};impl_->shutdown(true,true);}
NetServer& NetServer::onError(std::function<void(const NetError&)> callback){impl_->check();impl_->errors=std::move(callback);return *this;}
NetServer& NetServer::onReady(std::function<void(const std::vector<NetListener>&)> callback){impl_->check();impl_->ready=std::move(callback);return *this;}
NetServer& NetServer::listen(std::function<bool(NetConnectionPtr)> callback){
    impl_->check();if(impl_->starting || impl_->listening)throw std::logic_error("Server is already listening");if(!callback)throw std::invalid_argument("Accept callback required");if(!impl_->options.native && !impl_->options.webSocket.enabled && !impl_->options.webTransport.enabled)throw std::invalid_argument("At least one listener must be enabled");
#if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
    throw std::logic_error("iOS networking supports clients only");
#endif
    impl_->hosts.clear();impl_->cancelled=false;impl_->failedStartup=false;impl_->pendingStarts=0;impl_->starting=true;impl_->generation++;impl_->connected=std::move(callback);impl_->startupDeadline=Clock::now()+std::chrono::seconds(5);
    if(impl_->options.native)impl_->start(NetTransport::Native);if(!impl_->cancelled && impl_->options.webSocket.enabled)impl_->start(NetTransport::WebSocket);if(!impl_->cancelled && impl_->options.webTransport.enabled)impl_->start(NetTransport::WebTransport);return *this;
}
NetServer& NetServer::expectClient(std::string key,std::string ip,std::chrono::seconds ttl,bool once){impl_->check();textValid(key);if(ttl.count()<-1 || ttl.count()>0xffffffff || key.size()>65535)throw std::invalid_argument("Invalid reservation");impl_->reservations.push_back({std::move(key),std::move(ip),ttl.count()==-1?Time::max():Clock::now()+ttl,once});return *this;}
NetServer& NetServer::broadcast(const NetMessage& message,std::function<bool(const NetConnection&)> filter){impl_->check();auto bytes=NetCodec::encode(message);auto connections=impl_->accepted;for(auto& connection:connections)if(connection->connected() && (!filter || filter(*connection)))connection->impl_->send(bytes,false);return *this;}
NetServer& NetServer::broadcast(const ISerializable& message,std::function<bool(const NetConnection&)> filter){impl_->check();auto bytes=NetCodec::encode(message);auto connections=impl_->accepted;for(auto& connection:connections)if(connection->connected() && (!filter || filter(*connection)))connection->impl_->send(bytes,false);return *this;}
void NetServer::shutdown(bool closeExisting,bool kill){impl_->check();impl_->shutdown(closeExisting,kill);}
bool NetServer::listening()const{impl_->check();return impl_->listening;}
std::vector<NetListener> NetServer::listeners()const{impl_->check();return impl_->addresses();}
std::vector<NetConnectionPtr> NetServer::connections()const{impl_->check();std::vector<NetConnectionPtr> result;for(auto& connection:impl_->accepted)if(connection->connected())result.push_back(connection);return result;}
} // namespace pdg
