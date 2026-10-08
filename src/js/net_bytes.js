// Byte operations shared by native and browser PDG networking.
// No Node dependencies: preserve serializer-owned Uint8Array snapshots.
'use strict';
exports.bytes = function(value) {
    if (value instanceof Uint8Array) return value;
    if (value instanceof ArrayBuffer) return new Uint8Array(value);
    if (ArrayBuffer.isView(value)) return new Uint8Array(value.buffer, value.byteOffset, value.byteLength);
    throw new TypeError('Expected binary network data');
};
exports.alloc = function(size) { return new Uint8Array(size); };
exports.concat = function(a, b) {
    var out = new Uint8Array(a.length + b.length); out.set(a); out.set(b, a.length); return out;
};
exports.read = function(bytes, offset, size) {
    var view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
    return size === 4 ? view.getUint32(offset) : view.getUint16(offset);
};
exports.write = function(bytes, offset, size, value) {
    var view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
    if (size === 4) view.setUint32(offset, value); else view.setUint16(offset, value);
};
exports.encode = function(text) {
    if (typeof Buffer !== 'undefined') return new Uint8Array(Buffer.from(text, 'utf8'));
    if (typeof TextEncoder !== 'undefined') return new TextEncoder().encode(text);
    var out = [];
    for (var i = 0; i < text.length; i++) {
        var c = text.charCodeAt(i);
        if (c >= 0xd800 && c <= 0xdbff) {
            var next = text.charCodeAt(i + 1);
            if (next >= 0xdc00 && next <= 0xdfff) { c = 0x10000 + ((c - 0xd800) << 10) + next - 0xdc00; i++; }
            else c = 0xfffd;
        } else if (c >= 0xdc00 && c <= 0xdfff) c = 0xfffd;
        if (c < 0x80) out.push(c);
        else if (c < 0x800) out.push(0xc0 | (c >> 6), 0x80 | (c & 63));
        else if (c < 0x10000) out.push(0xe0 | (c >> 12), 0x80 | ((c >> 6) & 63), 0x80 | (c & 63));
        else out.push(0xf0 | (c >> 18), 0x80 | ((c >> 12) & 63), 0x80 | ((c >> 6) & 63), 0x80 | (c & 63));
    }
    return new Uint8Array(out);
};
exports.decode = function(bytes) {
    if (typeof Buffer !== 'undefined') return Buffer.from(bytes.buffer, bytes.byteOffset, bytes.byteLength).toString('utf8');
    if (typeof TextDecoder !== 'undefined') return new TextDecoder().decode(bytes);
    var out = '';
    for (var i = 0; i < bytes.length;) {
        var first = bytes[i++], c = first, remaining = 0, low = 0x80, high = 0xbf;
        if (first >= 0xc2 && first <= 0xdf) { c &= 31; remaining = 1; }
        else if (first >= 0xe0 && first <= 0xef) {
            c &= 15; remaining = 2;
            if (first === 0xe0) low = 0xa0;
            if (first === 0xed) high = 0x9f;
        } else if (first >= 0xf0 && first <= 0xf4) {
            c &= 7; remaining = 3;
            if (first === 0xf0) low = 0x90;
            if (first === 0xf4) high = 0x8f;
        } else if (first >= 0x80) { out += '\ufffd'; continue; }
        while (remaining) {
            if (i === bytes.length || bytes[i] < low || bytes[i] > high) { c = 0xfffd; break; }
            c = (c << 6) | (bytes[i++] & 63); remaining--; low = 0x80; high = 0xbf;
        }
        if (c < 0x10000) out += String.fromCharCode(c);
        else { c -= 0x10000; out += String.fromCharCode(0xd800 + (c >> 10), 0xdc00 + (c & 1023)); }
    }
    return out;
};
