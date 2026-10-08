// -----------------------------------------------
// memblock.spec.js
//
// test suite for MemBlock
//
// Written by Ed Zavada, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

describe("MemBlock", function() {

  describe("construction", function() {

    it("can be created", function() {
      console.log('* Testing MemBlock...');
      expect(pdg.MemBlock).toBeDefined();
      expect(typeof pdg.MemBlock).toBe('function');
    });

    it("can be instantiated", function() {
      var memBlock = new pdg.MemBlock();
      expect(memBlock).toBeDefined();
      expect(typeof memBlock).toBe('object');
    });

  });

  describe("basic properties", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("has getDataSize method", function() {
      expect(typeof memBlock.getDataSize).toBe('function');
    });

    it("has getData method", function() {
      expect(typeof memBlock.getData).toBe('function');
    });

    it("has getByte method", function() {
      expect(typeof memBlock.getByte).toBe('function');
    });

    it("has getBytes method", function() {
      expect(typeof memBlock.getBytes).toBe('function');
    });

  });

  describe("data size operations", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can get data size", function() {
      var size = memBlock.getDataSize();
      expect(typeof size).toBe('number');
      expect(size >= 0).toBeTruthy();
    });

    it("returns consistent data size", function() {
      var size1 = memBlock.getDataSize();
      var size2 = memBlock.getDataSize();
      expect(size1).toEqual(size2);
    });

  });

  describe("data retrieval operations", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can get data", function() {
      var data = memBlock.getData();
      expect(data instanceof Uint8Array).toBe(true);
    });

    it("handles empty data", function() {
      var data = memBlock.getData();
      var size = memBlock.getDataSize();
      expect(data.length).toEqual(size);
    });

  });

  describe("byte array conversion", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can convert to a byte array", function() {
      var buffer = memBlock.getData();
      expect(buffer).toBeDefined();
      expect(typeof buffer).toBe('object');
    });

    it("returns buffer with correct length", function() {
      var buffer = memBlock.getData();
      var size = memBlock.getDataSize();
      expect(buffer.length).toEqual(size);
    });

  });

  describe("Uint8Array conversion", function() {

    it("returns a plain empty Uint8Array for an empty block", function() {
      var bytes = new pdg.MemBlock().getData();
      expect(Object.getPrototypeOf(bytes)).toBe(Uint8Array.prototype);
      expect(bytes.length).toBe(0);
    });

    it("preserves every byte value, including zero and high-bit bytes", function() {
      var serializer = new pdg.Serializer();
      for (var i = 0; i < 256; i++) serializer.serialize_1u(i);
      var block = serializer.getDataPtr();
      var bytes = block.getData();
      expect(Object.getPrototypeOf(bytes)).toBe(Uint8Array.prototype);
      expect(bytes.length).toBe(block.getDataSize());
      for (var j = 0; j < bytes.length; j++) {
        expect(bytes[j]).toBe(block.getByte(j));
      }
    });

    it("returns independent copies with standard Uint8Array slice behavior", function() {
      var serializer = new pdg.Serializer();
      serializer.serialize_1u(255);
      var block = serializer.getDataPtr();
      var first = block.getData();
      var second = block.getData();
      var original = block.getByte(0);
      expect(first.buffer === second.buffer).toBe(false);
      first[0] = original ^ 255;
      expect(block.getByte(0)).toBe(original);
      expect(second[0]).toBe(original);
      var slice = second.slice();
      slice[0] = original ^ 255;
      expect(second[0]).toBe(original);
    });

  });

  describe("data consistency", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("maintains data consistency between methods", function() {
      var data = memBlock.getData();
      var buffer = memBlock.getData();
      var size = memBlock.getDataSize();
      
      expect(data.length).toEqual(size);
      expect(buffer.length).toEqual(size);
    });

    it("returns consistent data across multiple calls", function() {
      var data1 = memBlock.getData();
      var data2 = memBlock.getData();
      expect(data1).toEqual(data2);
    });

    it("returns consistent buffer across multiple calls", function() {
      var buffer1 = memBlock.getData();
      var buffer2 = memBlock.getData();
      expect(buffer1).toEqual(buffer2);
    });

  });

  describe("method return types", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("getDataSize returns number", function() {
      var result = memBlock.getDataSize();
      expect(typeof result).toBe('number');
    });

    it("getData returns Uint8Array", function() {
      var result = memBlock.getData();
      expect(result instanceof Uint8Array).toBe(true);
    });

  });

  describe("integration tests", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can perform complete data access workflow", function() {
      var size = memBlock.getDataSize();
      var data = memBlock.getData();
      var buffer = memBlock.getData();
      
      expect(size >= 0).toBeTruthy();
      expect(data.length).toEqual(size);
      expect(buffer.length).toEqual(size);
    });

    it("handles multiple operations on same instance", function() {
      var size1 = memBlock.getDataSize();
      var data1 = memBlock.getData();
      var buffer1 = memBlock.getData();
      
      var size2 = memBlock.getDataSize();
      var data2 = memBlock.getData();
      var buffer2 = memBlock.getData();
      
      expect(size1).toEqual(size2);
      expect(data1).toEqual(data2);
      expect(buffer1).toEqual(buffer2);
    });

  });

  describe("performance characteristics", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can handle multiple rapid calls", function() {
      var startTime = Date.now();
      
      for (var i = 0; i < 100; i++) {
        memBlock.getDataSize();
        memBlock.getData();
        memBlock.getData();
      }
      
      var endTime = Date.now();
      var duration = endTime - startTime;
      
      // Should complete within reasonable time (adjust threshold as needed)
      expect(duration).toBeLessThan(1000); // 1 second
    });

  });

  describe("bounded access", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("has empty data by default", function() {
      var size = memBlock.getDataSize();
      var data = memBlock.getData();
      var buffer = memBlock.getData();
      
      expect(size).toEqual(0);
      expect(data.length).toBe(0);
      expect(buffer.length).toEqual(0);
    });

    it("safely reads an empty block", function() {
      expect(memBlock.getByte(0)).toBe(0);
      expect(memBlock.getBytes(0, 100).length).toBe(0);
    });

    it("clamps reads to the available bytes", function() {
      var serializer = new pdg.Serializer();
      serializer.serialize_str('bounds');
      var block = serializer.getDataPtr();
      var bytes = block.getData();
      expect(block.getBytes(bytes.length - 1, 100)).toEqual(bytes.slice(-1));
      expect(block.getBytes(bytes.length, 1).length).toBe(0);
      expect(block.getBytes(0, 0xffffffff)).toEqual(bytes);
      expect(block.getByte(bytes.length)).toBe(0);
    });

  });

});
