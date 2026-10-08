// Native protocol tests and the C++ endpoint for JavaScript interoperability tests.
#include "pdg/net/network.h"
#include "pdg/sys/serializable.h"
#include "pdg/sys/serializer.h"
#include "pdg/sys/deserializer.h"
#include "pdg/sys/initializer.h"
#include <iostream>
#include <stdexcept>
#include <thread>
namespace pdg {
bool Initializer::allowHorizontalOrientation() noexcept{return true;}
bool Initializer::allowVerticalOrientation() noexcept{return true;}
const char* Initializer::getAppName(bool) noexcept{return "Native network tests";}
const char* Initializer::getMainResourceFileName() noexcept{return nullptr;}
bool Initializer::installGlobalHandlers() noexcept{return false;}
bool Initializer::getGraphicsEnvironmentDimensions(Rect,Rect,long& width,long& height,uint8& depth) noexcept{width=height=1;depth=32;return false;}
}
using namespace pdg;
using namespace std::chrono_literals;
struct NetworkTestMessage : Serializable<NetworkTestMessage> {
    uint8_t one=15;uint16_t two=99;
    uint32 getMyClassTag()const override{return 0x50444757;}
    uint32 getSerializedSize(ISerializer*)const override{return 3;}
    void serialize(ISerializer* s)const override{s->serialize_1u(one);s->serialize_2u(two);}
    void deserialize(IDeserializer* d)override{one=d->deserialize_1u();two=d->deserialize_2u();}
};
void require(bool value,const char* what){if(!value)throw std::runtime_error(what);}
template<class F>void until(NetRuntime& runtime,F predicate){auto deadline=std::chrono::steady_clock::now()+8s;while(!predicate()){require(std::chrono::steady_clock::now()<deadline,"network test timeout");runtime.poll();std::this_thread::sleep_for(1ms);}}
void sendAll(NetConnection& c){
    c.send(std::string("Unicode: héllo 🌍"));c.sendJson("{\"score\":42}");
    std::vector<uint8_t> bytes{0,127,255};c.send(bytes);c.send(NetMessage::memBlock(std::vector<uint8_t>{112,100,103,0,127,255}));
    NetworkTestMessage object;c.send(object);c.sendDgram(std::string("reliable fallback"));c.sendDgram(bytes);c.sendDgram(object);
    // Queued messages must own their data before these local values disappear.
    bytes.assign(3,99);object.one=0;object.two=0;
}
void checkMessage(const NetMessage& message,unsigned index){
    switch(index){
    case 0:require(message.type()==NetMessageType::String && message.text()=="Unicode: héllo 🌍","unicode");break;
    case 1:require(message.type()==NetMessageType::Json && message.text()=="{\"score\":42}","json");break;
    case 2:case 6:require(message.type()==NetMessageType::Bytes && message.data()==std::vector<uint8_t>({0,127,255}),"bytes");break;
    case 3:require(message.type()==NetMessageType::MemBlock && message.data()==std::vector<uint8_t>({112,100,103,0,127,255}),"memblock");break;
    case 4:case 7:{auto object=std::dynamic_pointer_cast<NetworkTestMessage>(message.object());require(object && object->one==15 && object->two==99,"serializable factory");break;}
    case 5:require(message.text()=="reliable fallback","datagram reliable fallback");break;
    default:throw std::runtime_error("unexpected message");
    }
}
void selftest(NetTransport transport,bool datagrams=false,bool fallback=false){
    NetRuntime runtime;NetServerOptions opts;opts.serverAddr="127.0.0.1";opts.serverPort=0;opts.noDatagram=!datagrams;opts.reservationRequired=true;
    if(transport==NetTransport::WebSocket){opts.native=false;opts.webSocket.enabled=true;opts.webSocket.secure=false;opts.webSocket.port=0;opts.webSocket.allowedOrigins={"*"};}
    NetServer server(runtime,opts);NetClient client(runtime,{.noDatagram=!datagrams});NetConnectionPtr peer,connection;
    unsigned errors=0,received=0,closed=0;uint16_t port=0;
    server.onError([&](const NetError& e){errors++;std::cerr<<e.code<<": "<<e.message<<'\n';}).expectClient("secret","127.0.0.1",10s,true);
    server.onReady([&](const auto& listeners){port=listeners.front().endpoint.port;}).listen([&](auto c){peer=c;c->onMessage([](auto& c,const auto& m,auto){c.send(m);});return true;});
    until(runtime,[&]{return port || errors;});require(errors==0,"listener");
    NetConnectOptions connect;connect.host="127.0.0.1";connect.port=port;
    if(transport==NetTransport::WebSocket){connect.webSocketUrl="ws://127.0.0.1:"+std::to_string(port)+"/pdg";connect.transportPolicy=NetTransportPolicy::WebSocketOnly;if(fallback){connect.transportPolicy=NetTransportPolicy::Auto;connect.webTransportUrl="https://127.0.0.1:"+std::to_string(port)+"/pdg";connect.webTransportTimeout=100ms;}}
    client.onError([&](const auto& e){errors++;std::cerr<<e.code<<": "<<e.message<<'\n';}).connect(connect,[&](auto c){connection=c;c->onClose([&]{closed++;}).onMessage([&](auto&,const auto& m,auto delivery){require(delivery==NetDelivery::Reliable,"fallback carrier");checkMessage(m,received++);});sendAll(*c);},"secret");
    until(runtime,[&]{return received==8 || errors;});require(errors==0 && received==8,"round trip");
    if(datagrams){
        until(runtime,[&]{return connection->hasDgram() && peer->hasDgram();});
        unsigned packets=0;connection->onMessage([&](auto&,const auto& m,auto delivery){require(m.text()=="UDP","UDP message");require(delivery==NetDelivery::Reliable,"echo reliable carrier");packets++;});
        peer->onMessage([](auto& c,const auto& m,auto delivery){require(delivery==NetDelivery::Unreliable,"UDP delivery");c.send(m);});
        connection->sendDgram("UDP");until(runtime,[&]{return packets==1;});
        // Oversized datagrams must use the reliable channel without truncation.
        std::string large(2000,'x');connection->onMessage([&](auto&,const auto& m,auto delivery){require(m.text()==large && delivery==NetDelivery::Reliable,"oversized fallback");packets++;});
        peer->onMessage([](auto& c,const auto& m,auto delivery){require(delivery==NetDelivery::Reliable,"oversized reliable carrier");c.send(m);});
        connection->sendDgram(large);until(runtime,[&]{return packets==2;});
        connection->onMessage([&](auto&,const auto& m,auto){checkMessage(m,received++);});
        peer->onMessage([](auto& c,const auto& m,auto){c.send(m);});
    }
    bool foreignRejected=false;std::thread thread([&]{try{runtime.poll();}catch(const std::logic_error&){foreignRejected=true;}});thread.join();require(foreignRejected,"thread affinity");
    server.shutdown(false);connection->send(std::string("Unicode: héllo 🌍"));received=0;until(runtime,[&]{return received==1 || errors;});require(!errors,"shutdown preserves sessions");
    connection->close();connection->close();until(runtime,[&]{return closed==1;});for(unsigned i=0;i<10;i++)runtime.poll();require(closed==1,"exactly one close");
    bool rejected=false;try{connection->send("late");}catch(const std::logic_error&){rejected=true;}require(rejected,"send after close");
}
void rejectionTests(){
    NetRuntime runtime;NetServerOptions options;options.serverAddr="127.0.0.1";options.serverPort=0;options.noDatagram=true;options.reservationRequired=true;
    NetServer server(runtime,options);NetClient client(runtime);unsigned accepted=0,errors=0;uint16_t port=0;
    server.onError([&](const NetError& e){require(e.code=="ERR_BAD_CLIENT_KEY","reservation error code");errors++;}).onReady([&](const auto& listeners){port=listeners[0].endpoint.port;}).listen([&](auto){accepted++;return true;});
    until(runtime,[&]{return port!=0;});NetConnectOptions connect;connect.host="127.0.0.1";connect.port=port;
    unsigned clientErrors=0;client.onError([&](const auto&){clientErrors++;}).connect(connect,[&](auto){throw std::runtime_error("Unauthenticated callback");},"wrong");
    until(runtime,[&]{return errors==1 && clientErrors==1;});require(accepted==0,"authentication before application callback");
    for(unsigned i=0;i<10;i++)runtime.poll();require(errors==1 && clientErrors==1,"one error per failure");
    client.connect(connect,[&](auto){throw std::runtime_error("Cancelled callback");},"wrong");client.cancelConnect();for(unsigned i=0;i<20;i++){runtime.poll();std::this_thread::sleep_for(1ms);}require(clientErrors==1,"cancel suppresses callback");
    NetClientOptions bounded;bounded.maxFrameSize=1024;bounded.maxPendingBytes=2048;NetClient limits(runtime,bounded);NetConnectionPtr limited;
    server.expectClient("valid");limits.connect(connect,[&](auto c){limited=c;},"valid");until(runtime,[&]{return bool(limited);});
    bool tooLarge=false;try{limited->sendDgram(std::string(2048,'x'));}catch(const NetError& e){tooLarge=e.code=="ERR_FRAME_TOO_LARGE";}require(tooLarge && limited->connected(),"frame limit rejects without destroying session");
    limited->close(true);server.shutdown(true,true);
}
void lifetimeTest(){
    auto runtime=std::make_unique<NetRuntime>();NetServerOptions opts;opts.serverAddr="127.0.0.1";opts.serverPort=0;opts.noDatagram=true;
    auto server=std::make_unique<NetServer>(*runtime,opts);auto client=std::make_unique<NetClient>(*runtime);NetConnectionPtr connection;uint16_t port=0;unsigned callbacks=0;
    server->onReady([&](const auto& listeners){port=listeners[0].endpoint.port;}).listen([](auto){return true;});until(*runtime,[&]{return port!=0;});
    NetConnectOptions endpoint;endpoint.host="127.0.0.1";endpoint.port=port;client->connect(endpoint,[&](auto c){connection=c;c->onClose([&]{callbacks++;});});until(*runtime,[&]{return bool(connection);});
    runtime.reset();require(callbacks==0,"runtime destruction suppresses callbacks");bool inert=false;try{connection->send("late");}catch(const std::logic_error&){inert=true;}require(inert,"expired runtime");client.reset();server.reset();
}
int main(int argc,char** argv){try{
    IDeserializer::registerClass<NetworkTestMessage>();
    if(argc==2 && std::string(argv[1])=="--selftest"){
        selftest(NetTransport::Native);selftest(NetTransport::Native,true);selftest(NetTransport::WebSocket);selftest(NetTransport::WebSocket,false,true);rejectionTests();lifetimeTest();
        bool rejected=false;try{NetMessage::json("bad");}catch(const std::invalid_argument&){rejected=true;}require(rejected,"invalid JSON");
        std::cout<<"PASS native C++ networking, serialization, fallback, thread affinity, and shutdown\n";return 0;
    }
    require(argc>=3,"usage: --selftest | --server transport [cert key] | --client transport port [CA]");
    std::string mode=argv[1],kind=argv[2];bool automatic=kind=="wt-auto",blocked=kind=="native-blocked";if(automatic)kind="wt";if(blocked)kind="native";NetRuntime runtime;
    if(mode=="--server"){
        NetServerOptions opts;opts.serverAddr="127.0.0.1";opts.serverPort=0;opts.noDatagram=true;opts.reservationRequired=true;
        if(blocked){require(argc>=4,"blocked UDP port required");opts.serverPort=std::stoi(argv[3]);opts.fixedPort=true;opts.noDatagram=false;}
        if(kind!="native")opts.native=false;
        auto* listener=kind=="wt"?&opts.webTransport:&opts.webSocket;
        if(kind!="native"){listener->enabled=true;listener->port=0;listener->secure=kind!="ws";listener->allowedOrigins={"*"};if(argc>=5){listener->tls.certFile=argv[3];listener->tls.keyFile=argv[4];}}
        NetServer server(runtime,opts);bool stop=false;
        server.expectClient("interop").onError([](const auto& e){throw std::runtime_error(e.code+": "+e.message);}).onReady([](const auto& listeners){std::cout<<listeners.front().endpoint.port<<std::endl;}).listen([&](auto c){c->onMessage([&](auto& c,const auto& m,auto){if(m.type()==NetMessageType::String && m.text()=="done"){c.send(m);c.close();stop=true;}else c.send(m);});return true;});
        until(runtime,[&]{return stop;});for(unsigned i=0;i<100;i++){runtime.poll();std::this_thread::sleep_for(1ms);}return 0;
    }
    require(mode=="--client" && argc>=4,"client arguments");NetClient client(runtime,{.noDatagram=true});NetConnectionPtr connection;unsigned received=0;bool done=false;
    NetConnectOptions opts;opts.host="127.0.0.1";opts.port=static_cast<uint16_t>(std::stoi(argv[3]));
    if(kind!="native"){auto url=std::string(kind=="wt"?"https":kind=="wss"?"wss":"ws")+"://127.0.0.1:"+argv[3]+"/pdg";if(kind=="wt"){opts.webTransportUrl=url;opts.transportPolicy=automatic?NetTransportPolicy::Auto:NetTransportPolicy::WebTransportRequired;}else{opts.webSocketUrl=url;opts.transportPolicy=NetTransportPolicy::WebSocketOnly;}if(argc>=5)opts.tls.caFile=argv[4];}
    client.onError([](const auto& e){throw std::runtime_error(e.code+": "+e.message);}).connect(opts,[&](auto c){connection=c;c->onMessage([&](auto& c,const auto& m,auto delivery){if(received<8){require(delivery==NetDelivery::Reliable,"fallback carrier");checkMessage(m,received++);if(received==8)c.send("done");}else{require(m.text()=="done","final drain");done=true;}});sendAll(*c);},"interop");
    until(runtime,[&]{return done;});std::cout<<"PASS C++ client "<<kind<<std::endl;return 0;
}catch(const NetError& e){std::cerr<<e.code<<": "<<e.message<<std::endl;return 1;}catch(const std::exception& e){std::cerr<<e.what()<<std::endl;return 1;}}
