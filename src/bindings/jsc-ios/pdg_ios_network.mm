// iOS client transport. Network.framework runs on a serial worker queue;
// JavaScriptCore objects are accessed/protected exclusively on the PDG thread.
#include "pdg_ios_network.h"
#ifdef PDG_USE_WEBTRANSPORT
#include "webtransport/pdg_webtransport.h"
#endif
#import <Foundation/Foundation.h>
#import <Network/Network.h>
#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cmath>

namespace {
struct Event {
    std::string type, json;
    std::vector<uint8_t> bytes;
};
struct Connection {
    JSObjectRef callback = nullptr; // Only accessed on the PDG thread.
    nw_connection_t tcp = nil, udp = nil;
    nw_endpoint_t local = nil, remote = nil;
    int udpFD = -1;
    dispatch_source_t udpRead = nil;
    std::mutex mutex;
    std::deque<Event> events;
    size_t incoming = 0, limit = 4 * 1024 * 1024;
    std::atomic<size_t> outgoing{0}, sends{0};
    std::atomic<bool> closed{false}, stopping{false}, udpActive{false}, endQueued{false}, killQueued{false};
    bool websocket = false;
    bool tcpReady = false, udpReady = false; // Worker queue only.
};
using NetworkHandle = std::shared_ptr<Connection>;
JSContextRef context = nullptr;
dispatch_queue_t queue;
std::map<unsigned, NetworkHandle> connections; // PDG thread only.
unsigned nextID = 1;

std::string json(id object) {
    NSData *data = [NSJSONSerialization dataWithJSONObject:object options:0 error:nil];
    return std::string(static_cast<const char *>(data.bytes), data.length);
}
void push(NetworkHandle c, Event event) {
    std::lock_guard<std::mutex> lock(c->mutex);
    c->incoming += event.bytes.size();
    c->events.push_back(std::move(event));
}
Event errorEvent(const char *type, const char *code, const char *message, nw_error_t error = nil) {
    return {type, json(@{@"code":@(code), @"message":@(message), @"transport":@"native",
        @"nativeCode":@(error ? nw_error_get_error_code(error) : 0)}), {}};
}
void cancelUDP(NetworkHandle c) {
    c->udpActive = false;
    c->udpReady = false;
    if (c->udpRead) {
        dispatch_source_cancel(c->udpRead);
        c->udpRead = nil;
        c->udpFD = -1; // The source cancellation handler closes the descriptor.
    }
    if (c->udp) {
        nw_connection_set_state_changed_handler(c->udp, nil);
        nw_connection_cancel(c->udp);
        c->udp = nil;
    }
}
void finish(NetworkHandle c, const Event *error = nullptr) {
    if (c->closed.exchange(true)) return;
    c->stopping = true;
    if (error) {
        Event event = *error;
        if (c->websocket) {
            auto pos = event.json.find("\"native\"");
            if (pos != std::string::npos) event.json.replace(pos, 8, "\"websocket\"");
        }
        push(c, std::move(event));
    }
    cancelUDP(c);
    if (c->tcp) {
        nw_connection_set_state_changed_handler(c->tcp, nil);
        nw_connection_cancel(c->tcp);
        c->tcp = nil;
    }
    push(c, {"close", "null", {}});
}
NSDictionary *endpoint(nw_endpoint_t ep) {
    const char *host = nw_endpoint_get_hostname(ep);
    uint16_t port = nw_endpoint_get_port(ep);
    return @{@"address":host ? @(host) : @"", @"port":@(port)};
}
void receive(NetworkHandle c, bool udp) {
    nw_connection_t connection = udp ? c->udp : c->tcp;
    if (!connection || c->closed) return;
    auto handler = ^(dispatch_data_t data, nw_content_context_t content, bool complete, nw_error_t error) {
        if (c->closed || (udp && !c->udp)) return;
        if (error) {
            Event event = errorEvent(udp ? "udpError" : "error", udp ? "ERR_UDP_RECEIVE" : "ERR_NETWORK_RECEIVE", "Network receive failed", error);
            if (udp) { cancelUDP(c); push(c, event); } else finish(c, &event);
            return;
        }
        if (c->websocket) {
            if (!content && complete) { finish(c); return; }
            nw_protocol_metadata_t metadata = content ? nw_content_context_copy_protocol_metadata(content, nw_protocol_copy_ws_definition()) : nil;
            nw_ws_opcode_t opcode = metadata ? nw_ws_metadata_get_opcode(metadata) : nw_ws_opcode_invalid;
            if (opcode == nw_ws_opcode_close) { finish(c); return; }
            if (opcode == nw_ws_opcode_text) {
                Event event = errorEvent("error", "ERR_WEBSOCKET_TEXT", "PDG requires binary WebSocket messages"); finish(c, &event); return;
            }
            if (opcode != nw_ws_opcode_binary && opcode != nw_ws_opcode_cont) { receive(c, false); return; }
        }
        if (data && dispatch_data_get_size(data)) {
            size_t size = dispatch_data_get_size(data);
            bool overflow;
            { std::lock_guard<std::mutex> lock(c->mutex); overflow = size > c->limit - c->incoming || c->events.size() >= 256; }
            if (overflow) {
                Event event = errorEvent("error", "ERR_NETWORK_BACKPRESSURE", "Incoming network buffer limit exceeded");
                finish(c, &event);
                return;
            }
            const void *bytes = nullptr;
            __attribute__((objc_precise_lifetime)) dispatch_data_t mapped = dispatch_data_create_map(data, &bytes, &size);
            (void)mapped; // Keep the mapped storage alive while copying.
            Event event{udp ? "datagram" : "data", "", {}};
            const uint8_t *begin = static_cast<const uint8_t *>(bytes);
            event.bytes.assign(begin, begin + size);
            push(c, std::move(event));
        }
        if (!udp && !c->websocket && complete) { push(c, {"end", "null", {}}); finish(c); }
        else receive(c, udp);
    };
    if (udp || c->websocket) nw_connection_receive_message(connection, handler);
    else nw_connection_receive(connection, 1, 64 * 1024, handler);
}
NetworkHandle lookup(JSContextRef ctx, size_t count, const JSValueRef args[]) {
    if (!count) return nullptr;
    double id = JSValueToNumber(ctx, args[0], nullptr);
    if (!std::isfinite(id) || id < 1 || id > 0xffffffff || id != std::floor(id)) return nullptr;
    auto it = connections.find(static_cast<unsigned>(id));
    return it == connections.end() ? nullptr : it->second;
}
JSValueRef open(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t count, const JSValueRef args[], JSValueRef *exception) {
    if (count < 4) return JSValueMakeUndefined(ctx);
    JSStringRef hostString = JSValueToStringCopy(ctx, args[0], exception);
    if (!hostString || *exception) return JSValueMakeUndefined(ctx);
    std::vector<char> host(JSStringGetMaximumUTF8CStringSize(hostString));
    JSStringGetUTF8CString(hostString, host.data(), host.size());
    JSStringRelease(hostString);
    double port = JSValueToNumber(ctx, args[1], exception);
    JSObjectRef callback = JSValueToObject(ctx, args[2], exception);
    double limit = JSValueToNumber(ctx, args[3], exception);
    if (*exception || !JSObjectIsFunction(ctx, callback) || !std::isfinite(port) || port < 1 || port > 65535 || port != std::floor(port) || !(limit >= 1024 && limit <= 64 * 1024 * 1024) || limit != std::floor(limit)) {
        JSStringRef message = JSStringCreateWithUTF8CString("Invalid iOS network endpoint or buffer limit");
        JSValueRef value = JSValueMakeString(ctx, message);
        *exception = JSObjectMakeError(ctx, 1, &value, nullptr);
        JSStringRelease(message);
        return JSValueMakeUndefined(ctx);
    }
    double timeout = count > 4 ? JSValueToNumber(ctx, args[4], exception) : 5000;
    if (*exception || !std::isfinite(timeout) || timeout <= 0 || timeout > 0xffffffff) return JSValueMakeUndefined(ctx);
    NSURL *url = nil;
    if (count > 5 && !JSValueIsUndefined(ctx, args[5])) {
        JSStringRef value = JSValueToStringCopy(ctx, args[5], exception);
        if (!value || *exception) return JSValueMakeUndefined(ctx);
        std::vector<char> text(JSStringGetMaximumUTF8CStringSize(value));
        JSStringGetUTF8CString(value, text.data(), text.size()); JSStringRelease(value);
        url = [NSURL URLWithString:@(text.data())];
        if (!url.host.length || (![url.scheme isEqualToString:@"ws"] && ![url.scheme isEqualToString:@"wss"]) || url.user || url.password || url.fragment || (url.port && (url.port.integerValue < 1 || url.port.integerValue > 65535))) {
            JSStringRef message = JSStringCreateWithUTF8CString("Invalid WebSocket URL");
            JSValueRef value = JSValueMakeString(ctx, message);
            *exception = JSObjectMakeError(ctx, 1, &value, nullptr); JSStringRelease(message);
            return JSValueMakeUndefined(ctx);
        }
    }
    NetworkHandle c = std::make_shared<Connection>();
    c->websocket = url != nil;
    c->callback = callback; c->limit = static_cast<size_t>(limit);
    JSValueProtect(ctx, callback);
    unsigned id = nextID++;
    connections[id] = c;
    std::string address(host.data()), service = std::to_string(static_cast<unsigned>(port));
    dispatch_async(queue, ^{
        nw_parameters_t parameters = nw_parameters_create_secure_tcp([url.scheme isEqualToString:@"wss"] ? NW_PARAMETERS_DEFAULT_CONFIGURATION : NW_PARAMETERS_DISABLE_PROTOCOL, ^(nw_protocol_options_t options) {
            nw_tcp_options_set_enable_keepalive(options, true);
            nw_tcp_options_set_keepalive_idle_time(options, 2);
            nw_tcp_options_set_keepalive_interval(options, 2);
            nw_tcp_options_set_keepalive_count(options, 3);
        });
        if (c->websocket) {
            nw_protocol_options_t ws = nw_ws_create_options(nw_ws_version_13);
            nw_ws_options_add_subprotocol(ws, "pdg-net-v1");
            nw_ws_options_set_auto_reply_ping(ws, true);
            nw_ws_options_set_maximum_message_size(ws, c->limit);
            nw_protocol_stack_prepend_application_protocol(nw_parameters_copy_default_protocol_stack(parameters), ws);
        }
        nw_endpoint_t target = c->websocket ? nw_endpoint_create_url(url.absoluteString.UTF8String) : nw_endpoint_create_host(address.c_str(), service.c_str());
        c->tcp = nw_connection_create(target, parameters);
        nw_connection_set_queue(c->tcp, queue);
        nw_connection_set_state_changed_handler(c->tcp, ^(nw_connection_state_t state, nw_error_t error) {
            if (c->closed) return;
            if (state == nw_connection_state_ready && !c->tcpReady) {
                if (c->websocket) {
                    nw_protocol_metadata_t metadata = nw_connection_copy_protocol_metadata(c->tcp, nw_protocol_copy_ws_definition());
                    nw_ws_response_t response = metadata ? nw_ws_metadata_copy_server_response(metadata) : nil;
                    const char *protocol = response ? nw_ws_response_get_selected_subprotocol(response) : nullptr;
                    if (!protocol || strcmp(protocol, "pdg-net-v1")) {
                        Event event = errorEvent("error", "ERR_WEBSOCKET_PROTOCOL", "PDG WebSocket subprotocol required"); finish(c, &event); return;
                    }
                }
                c->tcpReady = true;
                nw_path_t path = nw_connection_copy_current_path(c->tcp);
                c->local = nw_path_copy_effective_local_endpoint(path);
                c->remote = nw_path_copy_effective_remote_endpoint(path);
                if (!c->local || !c->remote) {
                    Event event = errorEvent("error", "ERR_NETWORK_ENDPOINT", "Connected endpoint unavailable"); finish(c, &event); return;
                }
                push(c, {"connect", json(@{@"local":endpoint(c->local), @"remote":endpoint(c->remote)}), {}});
                receive(c, false);
            } else if (state == nw_connection_state_failed) {
                Event event = errorEvent("error", "ERR_NETWORK_CONNECT", "Connection establishment failed", error); finish(c, &event);
            }
        });
        nw_connection_start(c->tcp);
        // Bound failed DNS/path attempts even when the game's timers are paused.
        std::weak_ptr<Connection> weak = c;
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, static_cast<int64_t>(timeout * NSEC_PER_MSEC)), queue, ^{
            NetworkHandle c = weak.lock();
            if (c && !c->tcpReady && !c->closed) {
                Event event = errorEvent("error", "ERR_CONNECT_TIMEOUT", "Connection establishment timed out"); finish(c, &event);
            }
        });
    });
    return JSValueMakeNumber(ctx, id);
}
JSValueRef write(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t count, const JSValueRef args[], JSValueRef *exception) {
    NetworkHandle c = lookup(ctx, count, args);
    if (!c || c->stopping || c->closed || count < 3) return JSValueMakeBoolean(ctx, false);
    JSObjectRef array = JSValueToObject(ctx, args[1], exception);
    if (*exception || JSValueGetTypedArrayType(ctx, array, exception) != kJSTypedArrayTypeUint8Array) return JSValueMakeBoolean(ctx, false);
    size_t size = JSObjectGetTypedArrayByteLength(ctx, array, exception);
    size_t offset = JSObjectGetTypedArrayByteOffset(ctx, array, exception);
    JSObjectRef buffer = JSObjectGetTypedArrayBuffer(ctx, array, exception);
    const uint8_t *bytes = static_cast<uint8_t *>(JSObjectGetArrayBufferBytesPtr(ctx, buffer, exception));
    if (*exception) return JSValueMakeBoolean(ctx, false);
    bool udp = JSValueToBoolean(ctx, args[2]);
    if (udp && !c->udpActive) return JSValueMakeBoolean(ctx, false);
    if (!size) return JSValueMakeBoolean(ctx, true);
    if (c->sends >= 256 || (udp && size > 1492) || size > c->limit || c->outgoing.load() > c->limit - size) {
        if (udp ? !c->udpActive.exchange(false) : c->stopping.exchange(true)) return JSValueMakeBoolean(ctx, false);
        dispatch_async(queue, ^{
            Event event = errorEvent(udp ? "udpError" : "error", "ERR_NETWORK_BACKPRESSURE", "Outgoing network buffer limit exceeded");
            if (udp) { cancelUDP(c); push(c, event); } else finish(c, &event);
        });
        return JSValueMakeBoolean(ctx, false);
    }
    // Copy JS storage before returning to JavaScript or crossing threads.
    NSData *copy = [NSData dataWithBytes:bytes + offset length:size];
    c->outgoing += size; c->sends++;
    dispatch_async(queue, ^{
        nw_connection_t connection = udp ? c->udp : c->tcp;
        if (udp && c->udpFD >= 0 && !c->closed) {
            ssize_t sent = send(c->udpFD, copy.bytes, copy.length, 0);
            c->outgoing -= size; c->sends--;
            if (sent != static_cast<ssize_t>(size)) {
                cancelUDP(c); push(c, errorEvent("udpError", "ERR_UDP_SEND", "UDP send failed"));
            }
            return;
        }
        if (!connection || c->closed) { c->outgoing -= size; c->sends--; return; }
        dispatch_data_t data = dispatch_data_create(copy.bytes, copy.length, queue, ^{ (void)copy; });
        nw_content_context_t content = NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT;
        if (c->websocket) {
            content = nw_content_context_create("pdg-binary");
            nw_content_context_set_metadata_for_protocol(content, nw_ws_create_metadata(nw_ws_opcode_binary));
        }
        nw_connection_send(connection, data, content, true, ^(nw_error_t error) {
            c->outgoing -= size; c->sends--;
            if (c->closed) return;
            if (error) {
                Event event = errorEvent(udp ? "udpError" : "error", "ERR_NETWORK_SEND", "Network send failed", error);
                if (udp) { cancelUDP(c); push(c, event); } else finish(c, &event);
            }
        });
    });
    return JSValueMakeBoolean(ctx, true);
}
// Some Network.framework implementations ignore the requested UDP source port.
// BSD datagrams preserve the legacy PDG pairing when the bound endpoint differs.
void startBoundUDP(NetworkHandle c) {
    const sockaddr *local = nw_endpoint_get_address(c->local);
    const sockaddr *remote = nw_endpoint_get_address(c->remote);
    int fd = local && remote ? socket(local->sa_family, SOCK_DGRAM, 0) : -1;
    if (fd < 0 || bind(fd, local, local->sa_len) != 0 || connect(fd, remote, remote->sa_len) != 0 || fcntl(fd, F_SETFL, O_NONBLOCK) != 0) {
        if (fd >= 0) ::close(fd);
        push(c, errorEvent("udpError", "ERR_UDP_BIND", "UDP could not bind the TCP local endpoint"));
        return;
    }
    c->udpFD = fd;
    c->udpRead = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, fd, 0, queue);
    dispatch_source_set_event_handler(c->udpRead, ^{
        if (c->closed || c->udpFD != fd) return;
        uint8_t bytes[65536];
        for (unsigned i = 0; i < 64; ++i) {
            ssize_t size = recv(fd, bytes, sizeof(bytes), 0);
            if (size < 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
                    cancelUDP(c); push(c, errorEvent("udpError", "ERR_UDP_RECEIVE", "UDP receive failed"));
                }
                return;
            }
            if (!size) continue;
            bool overflow;
            { std::lock_guard<std::mutex> lock(c->mutex);
                overflow = static_cast<size_t>(size) > c->limit - c->incoming || c->events.size() >= 256; }
            if (overflow) {
                cancelUDP(c); push(c, errorEvent("udpError", "ERR_NETWORK_BACKPRESSURE", "UDP incoming buffer limit exceeded")); return;
            }
            Event event{"datagram", "", {}};
            event.bytes.assign(bytes, bytes + size); push(c, std::move(event));
        }
    });
    dispatch_source_set_cancel_handler(c->udpRead, ^{ ::close(fd); });
    dispatch_resume(c->udpRead);
    c->udpActive = true;
    push(c, {"udpReady", "null", {}});
}
JSValueRef startUDP(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t count, const JSValueRef args[], JSValueRef *) {
    NetworkHandle c = lookup(ctx, count, args);
    if (c) dispatch_async(queue, ^{
        if (c->websocket || c->closed || c->udp || c->udpFD >= 0 || !c->local || !c->remote) return;
        nw_parameters_t parameters = nw_parameters_create_secure_udp(NW_PARAMETERS_DISABLE_PROTOCOL, NW_PARAMETERS_DEFAULT_CONFIGURATION);
        // Use resolved numeric endpoints to keep UDP paired with the TCP peer.
        std::string localPort = std::to_string(nw_endpoint_get_port(c->local));
        nw_endpoint_t local = nw_endpoint_create_host(nw_endpoint_get_hostname(c->local), localPort.c_str());
        nw_parameters_set_local_endpoint(parameters, local);
        nw_parameters_set_reuse_local_address(parameters, true);
        std::string remotePort = std::to_string(nw_endpoint_get_port(c->remote));
        nw_endpoint_t remote = nw_endpoint_create_host(nw_endpoint_get_hostname(c->remote), remotePort.c_str());
        c->udp = nw_connection_create(remote, parameters);
        nw_connection_set_queue(c->udp, queue);
        nw_connection_set_state_changed_handler(c->udp, ^(nw_connection_state_t state, nw_error_t error) {
            if (!c->udp || c->closed) return;
            if (state == nw_connection_state_ready && !c->udpReady) {
                c->udpReady = true;
                nw_path_t path = nw_connection_copy_current_path(c->udp);
                nw_endpoint_t bound = nw_path_copy_effective_local_endpoint(path);
                if (!bound || nw_endpoint_get_port(bound) != nw_endpoint_get_port(c->local)) {
                    cancelUDP(c); startBoundUDP(c); return;
                }
                c->udpActive = true;
                push(c, {"udpReady", "null", {}}); receive(c, true);
            }
            else if (state == nw_connection_state_failed) {
                Event event = errorEvent("udpError", "ERR_UDP_CONNECT", "UDP connection failed", error); cancelUDP(c); push(c, event);
            }
        });
        nw_connection_start(c->udp);
    });
    return JSValueMakeUndefined(ctx);
}
JSValueRef closeUDP(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t count, const JSValueRef args[], JSValueRef *) {
    NetworkHandle c = lookup(ctx, count, args);
    if (c) dispatch_async(queue, ^{ cancelUDP(c); });
    return JSValueMakeUndefined(ctx);
}
JSValueRef close(JSContextRef ctx, JSObjectRef, JSObjectRef, size_t count, const JSValueRef args[], JSValueRef *) {
    NetworkHandle c = lookup(ctx, count, args);
    bool force = count > 1 && JSValueToBoolean(ctx, args[1]);
    if (c && (force ? c->killQueued.exchange(true) : c->endQueued.exchange(true))) return JSValueMakeUndefined(ctx);
    if (c) c->stopping = true;
    if (c) dispatch_async(queue, ^{
        if (c->closed) return;
        if (force || !c->tcpReady) finish(c);
        else {
            cancelUDP(c);
            nw_content_context_t content = NW_CONNECTION_FINAL_MESSAGE_CONTEXT;
            if (c->websocket) {
                content = nw_content_context_create("pdg-close");
                nw_protocol_metadata_t metadata = nw_ws_create_metadata(nw_ws_opcode_close);
                nw_ws_metadata_set_close_code(metadata, nw_ws_close_code_normal_closure);
                nw_content_context_set_metadata_for_protocol(content, metadata);
            }
            nw_connection_send(c->tcp, nil, content, true, ^(nw_error_t error) { finish(c); });
            std::weak_ptr<Connection> weak = c;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), queue, ^{ if (auto c = weak.lock()) finish(c); });
        }
    });
    return JSValueMakeUndefined(ctx);
}
#ifdef PDG_USE_WEBTRANSPORT
JSValueRef webTransportCommand(JSContextRef ctx,JSObjectRef,JSObjectRef,size_t count,const JSValueRef args[],JSValueRef* exception) {
    if(count!=1 || !JSValueIsString(ctx,args[0])) {
        JSStringRef message=JSStringCreateWithUTF8CString("Expected a WebTransport JSON request");
        JSValueRef value=JSValueMakeString(ctx,message);JSStringRelease(message);
        *exception=JSObjectMakeError(ctx,1,&value,nullptr);return JSValueMakeUndefined(ctx);
    }
    JSStringRef input=JSValueToStringCopy(ctx,args[0],exception);
    std::vector<char> request(JSStringGetMaximumUTF8CStringSize(input));
    JSStringGetUTF8CString(input,request.data(),request.size());JSStringRelease(input);
    char* result=pdg_wt_command(request.data());
    JSStringRef output=JSStringCreateWithUTF8CString(result?result:"null");pdg_wt_free(result);
    JSValueRef value=JSValueMakeString(ctx,output);JSStringRelease(output);return value;
}
#endif
void property(JSObjectRef object, const char *name, JSObjectCallAsFunctionCallback callback) {
    JSStringRef string = JSStringCreateWithUTF8CString(name);
    JSObjectSetProperty(context, object, string, JSObjectMakeFunctionWithCallback(context, string, callback), kJSPropertyAttributeReadOnly, nullptr);
    JSStringRelease(string);
}
}
void JSC_IOS_NetworkInstall(JSContextRef ctx, JSObjectRef process) {
    context = ctx;
#ifdef PDG_USE_WEBTRANSPORT
    property(process,"_webTransportCommand",webTransportCommand);
#endif
    queue = dispatch_queue_create("org.pdg.network", DISPATCH_QUEUE_SERIAL);
    JSObjectRef bridge = JSObjectMake(ctx, nullptr, nullptr);
    property(bridge, "open", open); property(bridge, "write", write); property(bridge, "udp", startUDP);
    property(bridge, "close", close); property(bridge, "closeUDP", closeUDP);
    JSStringRef name = JSStringCreateWithUTF8CString("_iosNetwork");
    JSObjectSetProperty(ctx, process, name, bridge, kJSPropertyAttributeReadOnly, nullptr);
    JSStringRelease(name);
}
JSValueRef JSC_IOS_NetworkIdle() {
    // Snapshot IDs: callbacks may connect, close, throw, or mutate other sessions.
    std::vector<unsigned> ids;
    for (auto &entry : connections) ids.push_back(entry.first);
    for (unsigned id : ids) {
        auto it = connections.find(id);
        if (it == connections.end()) continue;
        NetworkHandle c = it->second;
        // Limit work per engine tick, leaving queued data bounded until the next tick.
        for (unsigned i = 0; i < 64; ++i) {
            Event event;
            { std::lock_guard<std::mutex> lock(c->mutex);
                if (c->events.empty()) break;
                event = std::move(c->events.front()); c->events.pop_front(); c->incoming -= event.bytes.size(); }
            JSStringRef type = JSStringCreateWithUTF8CString(event.type.c_str());
            JSValueRef args[2] = {JSValueMakeString(context, type), JSValueMakeNull(context)};
            JSStringRelease(type);
            if (event.type == "data" || event.type == "datagram") {
                JSObjectRef array = JSObjectMakeTypedArray(context, kJSTypedArrayTypeUint8Array, event.bytes.size(), nullptr);
                memcpy(JSObjectGetTypedArrayBytesPtr(context, array, nullptr), event.bytes.data(), event.bytes.size());
                args[1] = array;
            } else {
                JSStringRef text = JSStringCreateWithUTF8CString(event.json.c_str());
                args[1] = JSValueMakeFromJSONString(context, text); JSStringRelease(text);
            }
            JSValueRef exception = nullptr;
            JSObjectCallAsFunction(context, c->callback, nullptr, 2, args, &exception);
            if (event.type == "close") {
                JSValueUnprotect(context, c->callback); c->callback = nullptr; connections.erase(id);
            }
            if (exception) return exception;
            if (event.type == "close") break;
        }
    }
    return nullptr;
}
void JSC_IOS_NetworkSuspend() {
#ifdef PDG_USE_WEBTRANSPORT
    pdg_wt_suspend();
#endif
    for (auto &entry : connections) {
        NetworkHandle c = entry.second;
        dispatch_async(queue, ^{
            Event event = errorEvent("error", "ERR_NETWORK_BACKGROUND", "iOS application entered the background"); finish(c, &event);
        });
    }
}
void JSC_IOS_NetworkShutdown() {
#ifdef PDG_USE_WEBTRANSPORT
    pdg_wt_suspend();
#endif
    for (auto &entry : connections) {
        NetworkHandle c = entry.second;
        dispatch_async(queue, ^{ finish(c); });
        JSValueUnprotect(context, c->callback);
    }
    connections.clear();
}
