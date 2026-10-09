#pragma once
// Typed, owned-buffer interface shared by native C++ consumers and the JSON bridge.
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
namespace pdg::wt {
struct Endpoint { std::string address; uint16_t port = 0; };
struct Options {
    bool server = false;
    std::string host = "localhost", path = "/pdg", certFile, keyFile, caFile;
    uint16_t port = 5443;
    size_t maxPendingBytes = 4 * 1024 * 1024, maxConnections = 1024,
        maxConnectionsPerIP = 32, maxConnectionsPerOrigin = 1024, maxConnectionsPerMinute = 120;
    uint64_t timeout = 5000, idleTimeout = 30000;
    std::vector<std::string> allowedOrigins, certificateHashes;
};
struct Result { unsigned id = 0; std::string code, message; };
struct Event {
    enum Type { Ready, Accept, Data, Datagram, Error, Close } type;
    unsigned id = 0;
    Endpoint local, remote;
    size_t maxDatagramSize = 0;
    std::vector<uint8_t> bytes;
    std::string code, message;
};
Result open(const Options& options);
std::vector<Event> poll(unsigned id);
bool write(unsigned id, std::vector<uint8_t> bytes, bool datagram = false);
void close(unsigned id, bool force = false);
void stop(unsigned id);
// Discard a native owner handle after closing or stopping it.
void release(unsigned id);
} // namespace pdg::wt
