// Binary APIs use byte views, never JavaScript strings.
describe('Uint8Array binary interfaces', function() {
    function values(bytes) { return Array.prototype.slice.call(bytes); }
    function roundTrip(bytes) {
        var writer = new pdg.Serializer();
        writer.serialize_mem(bytes);
        var reader = new pdg.Deserializer();
        reader.setDataPtr(writer.getDataPtr().getData());
        return reader.deserialize_mem().getData();
    }
    it('round-trips all byte values and empty arrays', function() {
        var bytes = new Uint8Array(256);
        for (var i = 0; i < 256; i++) bytes[i] = i;
        expect(values(roundTrip(bytes))).toEqual(values(bytes));
        expect(roundTrip(new Uint8Array(0)).length).toBe(0);
    });
    it('honors subarray offsets and lengths', function() {
        var bytes = new Uint8Array([99, 0, 128, 255, 77]).subarray(1, 4);
        expect(values(roundTrip(bytes))).toEqual([0, 128, 255]);
        var writer = new pdg.Serializer();
        expect(writer.sizeof_mem(bytes)).toBe(writer.sizeof_mem(new Uint8Array([0, 128, 255])));
    });
    it('copies serialized bytes and owns deserializer array input', function() {
        var writer = new pdg.Serializer();
        var bytes = new Uint8Array([0, 128, 255]);
        writer.serialize_mem(bytes);
        bytes.fill(7);
        var stream = writer.getDataPtr().getData();
        var padded = new Uint8Array(stream.length + 4);
        padded.set(stream, 2);
        var reader = new pdg.Deserializer();
        reader.setDataPtr(padded.subarray(2, 2 + stream.length));
        padded.fill(0);
        expect(values(reader.deserialize_mem().getData())).toEqual([0, 128, 255]);
        reader.setDataPtr(writer.getDataPtr());
        expect(values(reader.deserialize_mem().getData())).toEqual([0, 128, 255]);
    });
    it('returns independent byte snapshots from MemBlock', function() {
        var writer = new pdg.Serializer(); writer.serialize_1u(255);
        var block = writer.getDataPtr(), bytes = block.getData(), before = block.getByte(0);
        expect(typeof block.toBuffer).toBe('undefined');
        expect(typeof block.toUint8).toBe('undefined');
        expect(Object.getPrototypeOf(bytes)).toBe(Uint8Array.prototype);
        bytes[0] ^= 255;
        expect(block.getByte(0)).toBe(before);
        var slice = block.getBytes(0, 1); slice[0] ^= 255;
        expect(block.getByte(0)).toBe(before);
    });
    it('rejects strings and other array element types', function() {
        var writer = new pdg.Serializer(), reader = new pdg.Deserializer();
        ['abc', new Uint16Array([1, 2]), new ArrayBuffer(4), [1, 2]].forEach(function(value) {
            expect(function() { writer.serialize_mem(value); }).toThrow();
            expect(function() { writer.sizeof_mem(value); }).toThrow();
            expect(function() { reader.setDataPtr(value); }).toThrow();
        });
    });
    it('formats byte views and rejects invalid dump bounds', function() {
        var dump = pdg.LogManager.binaryDump || pdg.lm.binaryDump;
        var text = dump.call(pdg.lm, new Uint8Array([99, 0, 255, 77]).subarray(1, 3));
        expect(text.toLowerCase()).toContain('ff');
        expect(function() { dump.call(pdg.lm, 'abc'); }).toThrow();
        expect(function() { dump.call(pdg.lm, new Uint8Array(2), 3); }).toThrow();
        expect(function() { dump.call(pdg.lm, new Uint8Array(2), 0, 0); }).toThrow();
    });
    it('loads resource bytes as independent Uint8Array snapshots', function() {
        var ref = pdg.res.openResourceFile('data');
        try {
            var bytes = pdg.res.getResource('jupitermap.jpg', 2);
            expect(Object.getPrototypeOf(bytes)).toBe(Uint8Array.prototype);
            expect(values(bytes)).toEqual([255, 216]);
            bytes.fill(0);
            expect(values(pdg.res.getResource('jupitermap.jpg', 2))).toEqual([255, 216]);
        } finally { pdg.res.closeResourceFile(ref); }
    });
    it('loads tile data from a byte view', function() {
        var layer = pdg.createTileLayer();
        layer.setWorldSize(2, 2);
        var bytes = new Uint8Array([99, 1, 2, 3, 4, 77]);
        layer.loadMapData(bytes.subarray(1, 5), 2, 2);
        bytes.fill(0);
        expect(layer.getTileTypeAt(0, 0)).toBe(1);
        expect(layer.getTileTypeAt(1, 1)).toBe(4);
        expect(function() { layer.loadMapData('1234', 2, 2); }).toThrow();
        expect(function() { layer.loadMapData(new Uint8Array(3), 2, 2); }).toThrow();
    });
    if (typeof Buffer !== 'undefined') {
        it('shares snapshot storage only with the explicit Buffer view conversion', function() {
            var writer = new pdg.Serializer();
            writer.serialize_1u(255);
            var block = writer.getDataPtr();
            var bytes = block.getData();
            var view = bytes.subarray(1, 2);
            var original = view[0];
            var shared = Buffer.from(view.buffer, view.byteOffset, view.byteLength);
            var copied = Buffer.from(view);
            expect(shared.buffer).toBe(bytes.buffer);
            expect(shared.length).toBe(1);
            shared[0] = original ^ 255;
            expect(bytes[1]).toBe(original ^ 255);
            expect(copied[0]).toBe(original);
            expect(block.getByte(1)).toBe(original);
        });
        it('accepts Node Buffer views without string conversion', function() {
            expect(values(roundTrip(Buffer.from([99, 0, 128, 255, 77]).subarray(1, 4)))).toEqual([0, 128, 255]);
        });
    }
    if (pdg.NetConnection) {
        it('frames and decodes Uint8Array network messages', function() {
            var connection = new pdg.NetConnection();
            var bytes = new Uint8Array([99, 0, 128, 255, 77]).subarray(1, 4);
            var packet = connection._serializeMessage(bytes);
            expect(packet instanceof Uint8Array).toBe(true);
            var framed = connection._frameTcpData(packet);
            expect(new DataView(framed.buffer, framed.byteOffset, framed.byteLength).getUint32(1)).toBe(packet.length);
            var received = connection._deserializeMessage(framed.subarray(5));
            expect(received instanceof Uint8Array).toBe(true);
            if (typeof Buffer !== 'undefined') expect(Buffer.isBuffer(received)).toBe(true);
            expect(values(received)).toEqual([0, 128, 255]);
        });
    }
    if (typeof SharedArrayBuffer === 'function') {
        it('rejects shared storage', function() {
            expect(function() { new pdg.Serializer().serialize_mem(new Uint8Array(new SharedArrayBuffer(4))); }).toThrow();
        });
    }
    if (typeof structuredClone === 'function') {
        it('rejects detached input views', function() {
            var bytes = new Uint8Array(4);
            structuredClone(bytes, {transfer: [bytes.buffer]});
            expect(function() { new pdg.Serializer().serialize_mem(bytes); }).toThrow();
        });
    }
});
