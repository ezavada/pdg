// Optional native C++ networking. This header is not a script binding input.
#ifndef PDG_NET_NETWORK_H
#define PDG_NET_NETWORK_H
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <vector>

namespace pdg {
class ISerializable;
class NetConnection;
using NetConnectionPtr = std::shared_ptr<NetConnection>;
enum class NetTransport { Native, WebSocket, WebTransport };
enum class NetDelivery { Reliable, Unreliable };
enum class NetTransportPolicy { Auto, NativeOnly, WebSocketOnly, WebTransportRequired };
enum class NetMessageType { String, Json, Bytes, MemBlock, Serializable };
struct NetEndpoint { std::string address; uint16_t port = 0; };
struct NetError {
    std::string code, message;
    NetTransport transport = NetTransport::Native;
    NetEndpoint endpoint;
};
struct NetLimits {
    size_t maxFrameSize = 1024 * 1024, maxPendingBytes = 4 * 1024 * 1024;
    std::chrono::milliseconds handshakeTimeout{5000};
};
struct NetTlsOptions {
    std::string certFile, keyFile, caFile;
    // Lowercase hex SHA-256 DER certificate digests; WebTransport clients only.
    std::vector<std::string> serverCertificateHashes;
};
struct NetClientOptions : NetLimits { bool noDatagram = false; };
struct NetConnectOptions {
    std::string host = "localhost";
    uint16_t port = 5000, webPort = 5443;
    std::string webPath = "/pdg";
    std::string webSocketUrl, webTransportUrl, origin;
    NetTransportPolicy transportPolicy = NetTransportPolicy::Auto;
    NetTlsOptions tls;
    std::chrono::milliseconds timeout{5000}, webTransportTimeout{1500}, capabilityCacheTimeout{30000};
};
struct NetListenerOptions {
    bool enabled = false, secure = true;
    std::string host, path = "/pdg";
    uint16_t port = 5443;
    NetTlsOptions tls;
    std::vector<std::string> allowedOrigins;
};
struct NetServerOptions : NetLimits {
    bool native = true, noDatagram = false, reservationRequired = false, fixedPort = false;
    std::string serverAddr = "0.0.0.0";
    uint16_t serverPort = 5000;
    NetListenerOptions webSocket, webTransport;
    bool allowPartialListen = false;
    size_t maxConnections = 1024, maxConnectionsPerIP = 32,
        maxConnectionsPerOrigin = 1024, maxConnectionsPerMinute = 120, maxIncompleteHandshakes = 128;
    std::chrono::milliseconds idleTimeout{30000};
};
struct NetListener { NetTransport transport; NetEndpoint endpoint; bool secure = false; };

/// An owned message. JSON is UTF-8 JSON text; objects are reconstructed by PDG factories.
class NetMessage {
public:
    static NetMessage string(std::string value);
    static NetMessage json(std::string value);
    static NetMessage bytes(std::span<const uint8_t> value);
    static NetMessage memBlock(std::span<const uint8_t> value);
    NetMessageType type() const { return type_; }
    const std::string& text() const { return text_; }
    const std::vector<uint8_t>& data() const { return data_; }
    const std::shared_ptr<ISerializable>& object() const { return object_; }
private:
    NetMessageType type_ = NetMessageType::String;
    std::string text_;
    std::vector<uint8_t> data_;
    std::shared_ptr<ISerializable> object_;
    friend struct NetCodec;
};

/// All methods and callbacks belong to the thread that constructs this runtime.
/// poll() dispatches bounded I/O and callbacks; it never waits for DNS or socket I/O.
class NetRuntime {
public:
    NetRuntime();
    ~NetRuntime();
    NetRuntime(const NetRuntime&) = delete;
    NetRuntime& operator=(const NetRuntime&) = delete;
    void poll();
private:
    friend struct NetAccess;
    struct Impl;
    std::shared_ptr<Impl> impl_;
    friend class NetClient;
    friend class NetServer;
    friend class NetConnection;
};

class NetConnection {
public:
    NetConnection(const NetConnection&) = delete;
    NetConnection& operator=(const NetConnection&) = delete;
    using MessageCallback = std::function<void(NetConnection&, const NetMessage&, NetDelivery)>;
    /// Serialize and queue owned reliable output; returns this connection.
    /// Throws NetError if the serialized payload exceeds maxFrameSize.
    NetConnection& send(const NetMessage& message);
    NetConnection& send(const std::string& message);
    NetConnection& send(const ISerializable& message);
    NetConnection& send(std::span<const uint8_t> message);
    NetConnection& sendJson(const std::string& json);
    /// Falls back to reliable delivery when datagrams are unavailable, oversized or rejected.
    NetConnection& sendDgram(const NetMessage& message);
    NetConnection& sendDgram(const std::string& message);
    NetConnection& sendDgram(const ISerializable& message);
    NetConnection& sendDgram(std::span<const uint8_t> message);
    /// Replace the message handler. Copy the message to retain it after this callback.
    NetConnection& onMessage(MessageCallback callback);
    NetConnection& onClose(std::function<void()> callback);
    NetConnection& onError(std::function<void(const NetError&)> callback);
    /// Close once; kill discards queued output, otherwise it drains before closing.
    void close(bool kill = false);
    bool connected() const;
    bool hasDgram() const;
    bool secure() const;
    NetTransport transport() const;
    NetEndpoint localEndpoint() const;
    NetEndpoint remoteEndpoint() const;
private:
    friend struct NetAccess;
    struct Impl;
    explicit NetConnection(std::shared_ptr<Impl>);
    std::shared_ptr<Impl> impl_;
    friend class NetClient;
    friend class NetServer;
    friend class NetRuntime;
};

class NetClient {
public:
    explicit NetClient(NetRuntime& runtime, NetClientOptions options = {});
    ~NetClient();
    NetClient(const NetClient&) = delete;
    NetClient& operator=(const NetClient&) = delete;
    /// Start an asynchronous connection attempt. Callback follows the PDG handshake.
    NetClient& connect(NetConnectOptions options, std::function<void(NetConnectionPtr)> callback,
        std::string clientKey = {});
    void cancelConnect();
    NetClient& onError(std::function<void(const NetError&)> callback);
private:
    friend struct NetAccess;
    struct Impl;
    std::shared_ptr<Impl> impl_;
};

class NetServer {
public:
    explicit NetServer(NetRuntime& runtime, NetServerOptions options = {});
    ~NetServer();
    NetServer(const NetServer&) = delete;
    NetServer& operator=(const NetServer&) = delete;
    /// Start requested listeners. Return true from the callback to accept a peer.
    NetServer& listen(std::function<bool(NetConnectionPtr)> callback);
    NetServer& onReady(std::function<void(const std::vector<NetListener>&)> callback);
    NetServer& onError(std::function<void(const NetError&)> callback);
    NetServer& expectClient(std::string key, std::string ip = "*",
        std::chrono::seconds ttl = std::chrono::seconds{-1}, bool singleUse = false);
    NetServer& broadcast(const NetMessage& message,
        std::function<bool(const NetConnection&)> filter = {});
    NetServer& broadcast(const ISerializable& message,
        std::function<bool(const NetConnection&)> filter = {});
    void shutdown(bool closeExisting = true, bool kill = false);
    bool listening() const;
    std::vector<NetListener> listeners() const;
    std::vector<NetConnectionPtr> connections() const;
private:
    friend struct NetAccess;
    struct Impl;
    std::shared_ptr<Impl> impl_;
};
} // namespace pdg
#endif
