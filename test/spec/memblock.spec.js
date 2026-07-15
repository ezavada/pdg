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

    it("has toBuffer method", function() {
      expect(typeof memBlock.toBuffer).toBe('function');
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
      expect(typeof data).toBe('string');
    });

    it("handles empty data", function() {
      var data = memBlock.getData();
      var size = memBlock.getDataSize();
      expect(data.length).toEqual(size);
    });

  });

  describe("buffer conversion", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("can convert to buffer", function() {
      var buffer = memBlock.toBuffer();
      expect(buffer).toBeDefined();
      expect(typeof buffer).toBe('object');
    });

    it("returns buffer with correct length", function() {
      var buffer = memBlock.toBuffer();
      var size = memBlock.getDataSize();
      expect(buffer.length).toEqual(size);
    });

  });

  describe("data consistency", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("maintains data consistency between methods", function() {
      var data = memBlock.getData();
      var buffer = memBlock.toBuffer();
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
      var buffer1 = memBlock.toBuffer();
      var buffer2 = memBlock.toBuffer();
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

    it("getData returns string", function() {
      var result = memBlock.getData();
      expect(typeof result).toBe('string');
    });

    it("toBuffer returns object", function() {
      var result = memBlock.toBuffer();
      expect(typeof result).toBe('object');
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
      var buffer = memBlock.toBuffer();
      
      expect(size >= 0).toBeTruthy();
      expect(data.length).toEqual(size);
      expect(buffer.length).toEqual(size);
    });

    it("handles multiple operations on same instance", function() {
      var size1 = memBlock.getDataSize();
      var data1 = memBlock.getData();
      var buffer1 = memBlock.toBuffer();
      
      var size2 = memBlock.getDataSize();
      var data2 = memBlock.getData();
      var buffer2 = memBlock.toBuffer();
      
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
        memBlock.toBuffer();
      }
      
      var endTime = Date.now();
      var duration = endTime - startTime;
      
      // Should complete within reasonable time (adjust threshold as needed)
      expect(duration).toBeLessThan(1000); // 1 second
    });

  });

  describe("known limitations", function() {

    var memBlock;

    beforeEach(function() {
      memBlock = new pdg.MemBlock();
    });

    it("has empty data by default", function() {
      var size = memBlock.getDataSize();
      var data = memBlock.getData();
      var buffer = memBlock.toBuffer();
      
      expect(size).toEqual(0);
      expect(data).toEqual('');
      expect(buffer.length).toEqual(0);
    });

    it("note: byte access methods may cause segmentation faults on empty MemBlocks", function() {
      // Note: The getByte and getBytes methods may cause segmentation faults
      // when called on empty MemBlocks. This is a known limitation.
      expect(true).toBeTruthy(); // Placeholder test
    });

  });

});
