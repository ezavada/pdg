// Standalone-only host. Never embedded in an Emscripten artifact.
'use strict';
var wsModule = require(typeof require.resolve !== 'function' ? 'net_ws_bundle' : './net_ws_bundle');
var Transport = require(typeof require.resolve !== 'function' ? 'net_transport' : './net_transport').WebSocketTransport;
exports.listen = function(owner, opts) {
    var limit = require(typeof require.resolve !== 'function' ? 'net_transport' : './net_transport').positiveLimit;
    ['maxFrameSize','maxPendingBytes','maxConnections','maxConnectionsPerIP','maxConnectionsPerOrigin','maxConnectionsPerMinute','maxIncompleteHandshakes','idleTimeout'].forEach(function(name) { if (opts[name] !== undefined) limit(opts[name], 1, name); });
    var origins = opts.allowedOrigins || [];
    if (!Array.isArray(origins) || origins.some(function(origin) { return typeof origin !== 'string'; })) throw new TypeError('allowedOrigins must be an array of strings');
    if (origins.indexOf('*') !== -1) console.warn('PDG WebSocket development wildcard permits every origin');
    var secure = opts.secure !== false;
    var tls = opts.tls || {};
    var host = opts.host || owner.serverAddr;
    var port = opts.port === undefined ? 5443 : opts.port;
    var path = opts.path || '/pdg';
    if (typeof port !== 'number' || !Number.isInteger(port) || port < 0 || port > 65535) throw new TypeError('Invalid WebSocket port');
    if (path[0] !== '/') throw new TypeError('WebSocket path must start with /');
    if (owner._nativeEnabled && port !== 0 && port === owner.serverPort &&
        (host === owner.serverAddr || host === '0.0.0.0' || owner.serverAddr === '0.0.0.0' || host === '::' || owner.serverAddr === '::')) throw Object.assign(new Error('Native TCP and WebSocket listeners need separate TCP ports'), {code:'ERR_LISTENER_PORT_CONFLICT'});
    var tlsOptions = Object.assign({}, tls);
    if (secure) {
        var fs = require('fs');
        if (tls.certFile) tlsOptions.cert = fs.readFileSync(tls.certFile);
        if (tls.keyFile) tlsOptions.key = fs.readFileSync(tls.keyFile);
        if (!tlsOptions.cert || !tlsOptions.key) throw new TypeError('Secure WebSocket listener requires TLS cert/key or certFile/keyFile');
    }
    var http = secure ? require('https') : require('http');
    var server = secure ? http.createServer(tlsOptions) : http.createServer();
    server.maxConnections = opts.maxConnections || 1024;
    server.maxHeadersCount = 64;
    server.headersTimeout = owner.handshakeTimeout > 0 ? owner.handshakeTimeout : 5000;
    server.requestTimeout = server.headersTimeout;
    server.on('request', function(req, res) { res.writeHead(404); res.end(); });
    var wss = new wsModule.WebSocketServer({noServer:true, perMessageDeflate:false,
        maxPayload: opts.maxPendingBytes || 4 * 1024 * 1024,
        handleProtocols:function(protocols) { return protocols.has('pdg-net-v1') ? 'pdg-net-v1' : false; }});
    var peers = new Map();
    var originPeers = new Map();
    var attempts = new Map();
    var closed = false;
    var pingTimer;
    function reject(socket, status) { socket.end('HTTP/1.1 ' + status + '\r\nConnection: close\r\nContent-Length: 0\r\n\r\n'); }
    server.on('upgrade', function(req, socket, head) {
        var ip = socket.remoteAddress;
        var origin = req.headers.origin;
        var protocols = (req.headers['sec-websocket-protocol'] || '').split(',').map(function(s) { return s.trim(); });
        if (closed || req.url.split('?')[0] !== path) return reject(socket, '404 Not Found');
        if (origins.indexOf(origin) === -1 && origins.indexOf('*') === -1) return reject(socket, '403 Forbidden');
        if (protocols.indexOf('pdg-net-v1') === -1) return reject(socket, '400 Bad Request');
        if (!owner._checkClientIP(ip)) return reject(socket, '403 Forbidden');
        var now = Date.now();
        // Bound the rate table as well as the admitted sessions.
        attempts.forEach(function(value, key) { if (now - value.start > 60000) attempts.delete(key); });
        if (!attempts.has(ip) && attempts.size >= 4096) return reject(socket, '429 Too Many Requests');
        var rate = attempts.get(ip) || {start:now, count:0};
        rate.count++; attempts.set(ip, rate);
        if (rate.count > (opts.maxConnectionsPerMinute || 120) ||
            wss.clients.size >= (opts.maxConnections || 1024) ||
            (peers.get(ip) || 0) >= (opts.maxConnectionsPerIP || 32) ||
            (originPeers.get(origin) || 0) >= (opts.maxConnectionsPerOrigin || 1024) ||
            owner._pendingConnections.size >= (opts.maxIncompleteHandshakes || 128)) return reject(socket, '429 Too Many Requests');
        wss.handleUpgrade(req, socket, head, function(ws) {
            peers.set(ip, (peers.get(ip) || 0) + 1);
            originPeers.set(origin, (originPeers.get(origin) || 0) + 1);
            ws._pdgPong = true;
            ws.on('pong', function() { ws._pdgPong = true; });
            ws.on('close', function() {
                var count = (peers.get(ip) || 1) - 1;
                if (count) peers.set(ip, count); else peers.delete(ip);
                var originCount = (originPeers.get(origin) || 1) - 1;
                if (originCount) originPeers.set(origin, originCount); else originPeers.delete(origin);
            });
            owner._handleConnect(new Transport(ws, Object.assign({}, opts, {secure:secure}), socket));
        });
    });
    var ready = new Promise(function(resolve, rejectReady) {
        server.once('error', rejectReady);
        server.listen(port, host, function() {
            server.removeListener('error', rejectReady);
            if (closed) { server.close(); rejectReady(Object.assign(new Error('Listener startup cancelled'), {code:'ERR_LISTEN_CANCELLED'})); return; }
            pingTimer = setInterval(function() {
                wss.clients.forEach(function(ws) {
                    if (!ws._pdgPong) return ws.terminate();
                    ws._pdgPong = false; ws.ping();
                });
            }, opts.idleTimeout || 30000);
            if (pingTimer.unref) pingTimer.unref();
            resolve(Object.assign({transport:'websocket', secure:secure, path:path}, server.address()));
        });
    });
    server.on('error', function(error) {
        if (server.listening) owner._handleError(Object.assign(error, {transport:'websocket', host:host, port:port}));
    });
    return {ready:ready, close:function() {
        if (closed) return;
        closed = true; clearInterval(pingTimer);
        server.close(); wss.close();
    }};
};
