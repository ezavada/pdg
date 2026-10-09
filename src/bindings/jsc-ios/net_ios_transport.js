// Socket facade for the iOS Network.framework bridge. All events arrive on the PDG thread.
'use strict';
var EventEmitter = require('events').EventEmitter;
function Socket(options, callback) {
    EventEmitter.call(this);
    this.transport = options.webSocketUrl ? 'websocket' : 'native';
    this.secure = !!options.webSocketUrl && options.webSocketUrl.indexOf('wss:') === 0;
    this.destroyed = false;
    this.ios = true;
    var positiveLimit = require('net_transport').positiveLimit;
    this.maxPendingBytes = positiveLimit(options.maxPendingBytes, 4 * 1024 * 1024, 'maxPendingBytes');
    this.maxFrameSize = positiveLimit(options.maxFrameSize, 1024 * 1024, 'maxFrameSize');
    this._local = {address:'', port:0};
    this._udp = null;
    var self = this;
    this._id = process._iosNetwork.open(options.host || 'localhost', options.port, function(type, value) {
        if (type === 'connect') {
            self._local = value.local;
            self.remoteAddress = value.remote.address;
            self.remotePort = value.remote.port;
            callback();
        } else if (type === 'udpReady') {
            if (self._udp) self._udp.emit('listening');
        } else if (type === 'datagram') {
            if (self._udp) self._udp.emit('message', value, {address:self.remoteAddress, port:self.remotePort});
        } else if (type === 'udpError') {
            if (self._udp) self._udp.emit('error', value);
        } else if (type === 'close') {
            self.destroyed = true;
            self.emit('close', false);
        } else {
            self.emit(type, value);
        }
    }, this.maxPendingBytes, positiveLimit(options.timeout, 5000, 'timeout'), options.webSocketUrl);
}
Socket.prototype = Object.create(EventEmitter.prototype);
Socket.prototype.address = function() { return this._local; };
Socket.prototype.setKeepAlive = function() { return this; }; // Configured by the native bridge.
Socket.prototype.write = function(bytes) {
    return !this.destroyed && process._iosNetwork.write(this._id, bytes, false);
};
Socket.prototype.end = function() {
    if (!this.destroyed) process._iosNetwork.close(this._id, false);
};
Socket.prototype.destroy = function() {
    if (!this.destroyed) process._iosNetwork.close(this._id, true);
};
Socket.prototype.createDatagramSocket = function() {
    var socket = this;
    var udp = new EventEmitter();
    this._udp = udp;
    udp.bind = function() { process._iosNetwork.udp(socket._id); };
    udp.address = function() { return socket.address(); };
    udp.close = function() {
        if (udp.closed) return;
        udp.closed = true;
        socket._udp = null;
        process._iosNetwork.closeUDP(socket._id);
    };
    udp.send = function(bytes, offset, length, port, host, callback) {
        var ok = process._iosNetwork.write(socket._id, bytes.subarray(offset, offset + length), true);
        if (callback) callback(ok ? null : {code:'ERR_UDP_SEND', message:'Datagram send unavailable'}, ok ? length : 0);
    };
    return udp;
};
exports.connect = function(options, callback) {
    return new Socket(options, callback);
};

exports.connectWebSocket = function(info, onOpen, onError) {
    var limit = require('net_transport').positiveLimit;
    ['maxFrameSize','maxPendingBytes','timeout','handshakeTimeout'].forEach(function(name) { if (info[name] !== undefined) limit(info[name], 1, name); });
    var url = info.webSocketUrl;
    if (!url) {
        if (!info.host) throw new TypeError('WebSocket host or webSocketUrl required');
        var host = info.host.indexOf(':') >= 0 && info.host[0] !== '[' ? '[' + info.host + ']' : info.host;
        url = (info.secure === false ? 'ws://' : 'wss://') + host + ':' + (info.webPort === undefined ? 5443 : info.webPort) + (info.webPath || '/pdg');
    }
    if (typeof url !== 'string' || !/^wss?:\/\//.test(url)) throw new TypeError('Expected ws: or wss: URL');
    if (url.indexOf('ws:') === 0 && info.secure !== false) throw new TypeError('Insecure WebSocket requires secure:false');
    if (info.tls) throw new TypeError('iOS WebSockets use platform TLS trust; custom tls options are unsupported');
    var finished = false;
    var socket = new Socket(Object.assign({}, info, {webSocketUrl:url, port:1}), function() {
        finished = true; onOpen(socket);
    });
    socket.on('error', function(error) { if (!finished) { finished = true; onError(error); } });
    socket.on('close', function() {
        if (!finished) { finished = true; onError({code:'ERR_CONNECT_CLOSED', transport:'websocket', message:'WebSocket closed before connecting'}); }
    });
    return socket;
};
