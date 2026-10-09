'use strict';
var browser = typeof document !== 'undefined';
var Transport = require((browser || typeof require.resolve !== 'function') ? 'net_transport' : './net_transport').WebSocketTransport;
exports.connect = function(info, onOpen, onError) {
    var limit = require((browser || typeof require.resolve !== 'function') ? 'net_transport' : './net_transport').positiveLimit;
    ['maxFrameSize','maxPendingBytes','timeout','handshakeTimeout'].forEach(function(name) { if (info[name] !== undefined) limit(info[name], 1, name); });
    var secure = info.secure !== false;
    var url = info.webSocketUrl;
    if (!url) {
        if (!info.host) throw new TypeError('WebSocket host or webSocketUrl required');
        var host = info.host.indexOf(':') >= 0 && info.host[0] !== '[' ? '[' + info.host + ']' : info.host;
        url = (secure ? 'wss://' : 'ws://') + host + ':' + (info.webPort === undefined ? 5443 : info.webPort) + (info.webPath || '/pdg');
    }
    var parsed = new URL(url);
    if (parsed.protocol !== 'ws:' && parsed.protocol !== 'wss:') throw new TypeError('Expected ws: or wss: URL');
    if (parsed.protocol === 'ws:' && info.secure !== false) throw new TypeError('Insecure WebSocket requires secure:false');
    if (browser && location.protocol === 'https:' && parsed.protocol === 'ws:') throw new TypeError('HTTPS pages require wss:');
    var WS = browser ? globalThis.WebSocket : require(typeof require.resolve !== 'function' ? 'net_ws_bundle' : './net_ws_bundle').WebSocket;
    if (typeof WS !== 'function') throw Object.assign(new Error('WebSocket unavailable'), {code:'ERR_TRANSPORT_UNAVAILABLE'});
    var ws = browser ? new WS(url, 'pdg-net-v1') : new WS(url, 'pdg-net-v1', info.tls || {});
    var adapter = new Transport(ws, Object.assign({}, info, {secure:parsed.protocol === 'wss:'}));
    var finished = false;
    var timer = setTimeout(function() { fail(Object.assign(new Error('WebSocket establishment timed out'), {code:'ERR_CONNECT_TIMEOUT'})); }, info.timeout || 5000);
    function fail(error) {
        if (finished) return;
        finished = true; clearTimeout(timer); adapter.destroy();
        error.transport = 'websocket'; onError(error);
    }
    adapter.on('error', fail);
    adapter.on('close', function() { fail(Object.assign(new Error('WebSocket closed before connecting'), {code:'ERR_CONNECT_CLOSED'})); });
    function open() {
        if (finished) return;
        if (ws.protocol !== 'pdg-net-v1') { fail(Object.assign(new Error('PDG WebSocket subprotocol required'), {code:'ERR_WEBSOCKET_PROTOCOL'})); return; }
        finished = true; clearTimeout(timer); onOpen(adapter);
    }
    if (typeof ws.on === 'function') ws.on('open', open); else ws.addEventListener('open', open);
    return adapter;
};
