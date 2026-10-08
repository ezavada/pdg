// Reliable byte transport facade. Native TCP sockets already implement this
// contract: on(data/error/close/drain), write(bytes), end(), destroy(), address().
// WebSocket uses the same facade so PDG framing never depends on message boundaries.
'use strict';
function positiveLimit(value, fallback, name) {
    if (value === undefined) return fallback;
    if (!Number.isSafeInteger(value) || value <= 0 || value > 0xffffffff) throw new RangeError(name + ' must be a positive integer no greater than 4294967295');
    return value;
}
exports.positiveLimit = positiveLimit;
function WebSocketTransport(ws, options, endpoint) {
    options = options || {};
    this.ws = ws;
    this.transport = 'websocket';
    this.secure = !!options.secure;
    this.maxFrameSize = positiveLimit(options.maxFrameSize, 1024 * 1024, 'maxFrameSize');
    this.maxPendingBytes = positiveLimit(options.maxPendingBytes, 4 * 1024 * 1024, 'maxPendingBytes');
    this.remoteAddress = endpoint && endpoint.remoteAddress || '';
    this.remotePort = endpoint && endpoint.remotePort || 0;
    this._address = endpoint && endpoint.address ? endpoint.address() : {address:'', port:0};
    this._handlers = Object.create(null);
    this.destroyed = false;
    this._failed = false;
    ws.binaryType = 'arraybuffer';
    var message = function(data, binary) {
        if (this.destroyed) return;
        if (binary === false || typeof data === 'string') {
            this.fail('ERR_WEBSOCKET_TEXT', 'PDG WebSocket requires binary messages', 1003); return;
        }
        try {
            var bytes = data instanceof ArrayBuffer ? new Uint8Array(data) : data;
            if (!(bytes instanceof Uint8Array)) throw new TypeError('Expected WebSocket binary data');
            if (bytes.byteLength > this.maxPendingBytes) {
                this.fail('ERR_FRAME_TOO_LARGE', 'WebSocket message exceeds pending byte limit', 1009); return;
            }
            this.emit('data', bytes);
        } catch (error) { this.fail(error.code || 'ERR_WEBSOCKET_DATA', error.message, 1002); }
    }.bind(this);
    if (typeof ws.on === 'function') {
        ws.on('message', message);
        ws.on('error', function(error) { this.fail(error.code || 'ERR_WEBSOCKET', error.message); }.bind(this));
        ws.on('close', this._closed.bind(this));
    } else {
        ws.addEventListener('message', function(event) { message(event.data); });
        ws.addEventListener('error', function() { this.fail('ERR_WEBSOCKET', 'WebSocket connection failed'); }.bind(this));
        ws.addEventListener('close', this._closed.bind(this));
    }
}
WebSocketTransport.prototype.on = function(name, callback) {
    (this._handlers[name] || (this._handlers[name] = [])).push(callback); return this;
};
WebSocketTransport.prototype.emit = function(name, value) {
    (this._handlers[name] || []).slice().forEach(function(cb) { cb(value); });
};
WebSocketTransport.prototype.address = function() { return this._address; };
WebSocketTransport.prototype.setKeepAlive = function() {};
WebSocketTransport.prototype.write = function(bytes) {
    if (this.destroyed || this.ws.readyState !== 1) throw Object.assign(new Error('WebSocket is closed'), {code:'ERR_CONNECTION_CLOSED'});
    if (bytes.length + this.ws.bufferedAmount > this.maxPendingBytes) {
        this.fail('ERR_BACKPRESSURE', 'WebSocket pending byte limit exceeded', 1009); return false;
    }
    this.ws.send(bytes);
    return true;
};
WebSocketTransport.prototype.fail = function(code, message, closeCode) {
    if (this._failed || this.destroyed) return;
    this._failed = true;
    this.end(closeCode || 1011);
    this.emit('error', Object.assign(new Error(message), {code:code, transport:'websocket'}));
};
WebSocketTransport.prototype.end = function(code) {
    if (this.ws.readyState < 2) this.ws.close(code || 1000);
};
WebSocketTransport.prototype.destroy = function() {
    if (typeof this.ws.terminate === 'function') this.ws.terminate(); else this.end();
};
WebSocketTransport.prototype._closed = function() {
    if (this.destroyed) return;
    this.destroyed = true;
    this.emit('close', this._failed);
};
exports.WebSocketTransport = WebSocketTransport;
