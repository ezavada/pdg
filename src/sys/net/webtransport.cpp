#include "transport.h"
#include "webtransport/pdg_webtransport_native.h"
#include <stdexcept>

namespace pdg::net_detail {
namespace {
struct QuicTransport final : Transport {
    unsigned id;
    explicit QuicTransport(unsigned handle):id(handle){kind=NetTransport::WebTransport;secure=true;}
    ~QuicTransport(){if(!closed)wt::close(id,true);wt::release(id);}
    void endpoint(const wt::Event& event){
        local={event.local.address,event.local.port};remote={event.remote.address,event.remote.port};
        maxDatagramSize=event.maxDatagramSize;
    }
    void poll() override {
        for(auto& e:wt::poll(id)){
            switch(e.type){
            case wt::Event::Ready:endpoint(e);ready=true;events.push_back({Event::Ready,{},{}});break;
            case wt::Event::Data:events.push_back({Event::Data,std::move(e.bytes),{}});break;
            case wt::Event::Datagram:events.push_back({Event::Datagram,std::move(e.bytes),{}});break;
            case wt::Event::Error:events.push_back({Event::Error,{}, {e.code,e.message,kind,remote}});break;
            case wt::Event::Close:if(!closed){closed=true;events.push_back({Event::Closed,{},{}});}break;
            default:break;
            }
        }
    }
    bool write(Bytes bytes) override {return !closed && wt::write(id,std::move(bytes));}
    bool datagram(const Bytes& bytes) override {return !closed && bytes.size()<=maxDatagramSize && wt::write(id,bytes,true);}
    void close(bool kill) override {if(!closed)wt::close(id,kill);}
    bool datagramsReady() const override {return ready && !closed && maxDatagramSize>0;}
};
struct QuicListener final : Listener {
    unsigned id;
    bool stopped=false;
    explicit QuicListener(unsigned handle):id(handle){address.transport=NetTransport::WebTransport;address.secure=true;}
    ~QuicListener(){wt::stop(id);wt::release(id);}
    void poll() override {
        for(auto& e:wt::poll(id)){
            if(e.type==wt::Event::Ready){ready=true;address.endpoint={e.local.address,e.local.port};}
            else if(e.type==wt::Event::Error)error={e.code,e.message,NetTransport::WebTransport,address.endpoint};
            else if(e.type==wt::Event::Close)closed=true;
            else if(e.type==wt::Event::Accept){
                auto transport=std::make_shared<QuicTransport>(e.id);transport->endpoint(e);transport->ready=true;
                transport->events.push_back({Event::Ready,{},{}});
                if(stopped)transport->close(true);else accepted.push_back(std::move(transport));
            }
        }
    }
    void close(bool closeExisting) override {stopped=true;if(closeExisting)wt::close(id,true);else wt::stop(id);}
};
wt::Options base(const NetLimits& limits){wt::Options o;o.maxPendingBytes=limits.maxPendingBytes;o.timeout=limits.handshakeTimeout.count()?limits.handshakeTimeout.count():5000;return o;}
}
std::shared_ptr<Transport> connectWebTransport(const NetConnectOptions& info,const NetClientOptions& limits){
    auto opts=base(limits);opts.host=urlHost(info.webTransportUrl);opts.port=urlPort(info.webTransportUrl);
    opts.path=urlPath(info.webTransportUrl);opts.caFile=info.tls.caFile;opts.certificateHashes=info.tls.serverCertificateHashes;
    opts.timeout=info.timeout.count();auto result=wt::open(opts);
    if(!result.id)throw NetError{result.code,result.message,NetTransport::WebTransport,{opts.host,opts.port}};
    return std::make_shared<QuicTransport>(result.id);
}
std::shared_ptr<Listener> listenWebTransport(const NetServerOptions& info){
    auto opts=base(info);opts.server=true;const auto& listener=info.webTransport;
    opts.host=listener.host.empty()?info.serverAddr:listener.host;opts.port=listener.port;opts.path=listener.path;
    opts.certFile=listener.tls.certFile;opts.keyFile=listener.tls.keyFile;opts.allowedOrigins=listener.allowedOrigins;
    opts.maxConnections=info.maxConnections;opts.maxConnectionsPerIP=info.maxConnectionsPerIP;
    opts.maxConnectionsPerOrigin=info.maxConnectionsPerOrigin;opts.maxConnectionsPerMinute=info.maxConnectionsPerMinute;
    opts.idleTimeout=info.idleTimeout.count();auto result=wt::open(opts);
    if(!result.id)throw NetError{result.code,result.message,NetTransport::WebTransport,{opts.host,opts.port}};
    return std::make_shared<QuicListener>(result.id);
}
} // namespace pdg::net_detail
