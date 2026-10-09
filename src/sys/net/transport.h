#pragma once
#include "pdg/net/network.h"
#include <deque>

namespace pdg::net_detail {
using Bytes = std::vector<uint8_t>;
struct Event {
    enum Type { Ready, Data, Datagram, Error, Closed } type;
    Bytes bytes;
    NetError error;
};
struct Transport {
    virtual ~Transport() = default;
    virtual void poll() = 0;
    virtual bool write(Bytes bytes) = 0;
    virtual bool datagram(const Bytes&) { return false; }
    virtual void close(bool kill) = 0;
    virtual void startDatagrams() {}
    virtual bool datagramsReady() const { return false; }
    std::deque<Event> events;
    NetEndpoint local, remote;
    std::string origin;
    NetTransport kind = NetTransport::Native;
    bool secure = false, closed = false, ready = false;
    size_t maxDatagramSize = 0;
};
struct Listener {
    virtual ~Listener() = default;
    virtual void poll() = 0;
    virtual void close(bool closeExisting) = 0;
    std::deque<std::shared_ptr<Transport>> accepted;
    NetListener address{NetTransport::Native, {}, false};
    bool ready = false, closed = false;
    NetError error;
};
struct ResolvedAddress { std::vector<uint8_t> address; int family = 0; std::string error; };
ResolvedAddress resolve(const std::string& host, uint16_t port);
std::shared_ptr<Transport> connectSocket(const ResolvedAddress&, const NetConnectOptions&, const NetClientOptions&, NetTransport);
std::shared_ptr<Listener> listenSocket(const ResolvedAddress&, const NetServerOptions&, NetTransport);
std::shared_ptr<Transport> connectWebTransport(const NetConnectOptions&, const NetClientOptions&);
std::shared_ptr<Listener> listenWebTransport(const NetServerOptions&);
void initializeSockets();
void shutdownSockets();
std::string urlHost(const std::string& url);
uint16_t urlPort(const std::string& url);
std::string urlPath(const std::string& url);
void validateLimits(const NetLimits&);
} // namespace pdg::net_detail
