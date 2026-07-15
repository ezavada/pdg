// -----------------------------------------------
// offset.spec.js
//
// test suite for Offset
//
// Written by Ed Zavada, 2012
// Copyright (c) 2012, Dream Rock Studios, LLC
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

describe("Offset", function() {

  describe("construction", function() {

    it("can be created with no params", function() {
      console.log('* Testing Offset...');
      var offset = new Offset();
      expect(offset.x).toBeDefined();
      expect(offset.x).toEqual(0);
      expect(offset.y).toBeDefined();
      expect(offset.y).toEqual(0);
    });

    it("is an object, an instance of Offset", function() {
      var offset = new Offset();
      expect(typeof offset).toBe('object');
      expect(offset.constructor.name).toBe('Offset');
      expect(offset instanceof Offset).toBe(true);
    });

    it("can be created with x and y coordinates", function() {
      var offset = new Offset(10, 20);
      expect(offset.x).toEqual(10);
      expect(offset.y).toEqual(20);
    });

    it("can be created with negative coordinates", function() {
      var offset = new Offset(-5, -15);
      expect(offset.x).toEqual(-5);
      expect(offset.y).toEqual(-15);
    });

    it("can be created with floating point coordinates", function() {
      var offset = new Offset(3.14, 2.718);
      expect(offset.x).toEqual(3.14);
      expect(offset.y).toEqual(2.718);
    });

    it("can be created with array parameter [x, y]", function() {
      var offset = new Offset([7, 11]);
      expect(offset.x).toEqual(7);
      expect(offset.y).toEqual(11);
    });

    it("can be created with another Offset object", function() {
      var originalOffset = new Offset(25, 30);
      var newOffset = new Offset(originalOffset);
      expect(newOffset.x).toEqual(25);
      expect(newOffset.y).toEqual(30);
    });

    it("can be created with object parameter {x: val, y: val}", function() {
      var offset = new Offset({x: 100, y: 200});
      expect(offset.x).toEqual(100);
      expect(offset.y).toEqual(200);
    });

  });

  describe("equality operations", function() {

    it("can test equality with equals method", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(5, 10);
      var offset3 = new Offset(5, 11);
      expect(offset1.equals(offset2)).toBeTruthy();
      expect(offset1.equals(offset3)).toBeFalsy();
    });

    it("can test inequality with notEquals method", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(5, 10);
      var offset3 = new Offset(5, 11);
      expect(offset1.notEquals(offset2)).toBeFalsy();
      expect(offset1.notEquals(offset3)).toBeTruthy();
    });

    it("handles equality with zero coordinates", function() {
      var offset1 = new Offset(0, 0);
      var offset2 = new Offset(0, 0);
      expect(offset1.equals(offset2)).toBeTruthy();
    });

  });

  describe("assignment operations", function() {

    it("can assign from another offset", function() {
      var offset1 = new Offset(1, 2);
      var offset2 = new Offset(10, 20);
      var result = offset1.assign(offset2);
      expect(offset1.x).toEqual(10);
      expect(offset1.y).toEqual(20);
      expect(result).toBe(offset1); // should return self
    });

  });

  describe("in-place arithmetic operations", function() {

    it("can add another offset in-place", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(3, 7);
      var result = offset1.add(offset2);
      expect(offset1.x).toEqual(8);
      expect(offset1.y).toEqual(17);
      expect(result).toBe(offset1); // should return self
    });

    it("can subtract another offset in-place", function() {
      var offset1 = new Offset(10, 20);
      var offset2 = new Offset(3, 7);
      var result = offset1.sub(offset2);
      expect(offset1.x).toEqual(7);
      expect(offset1.y).toEqual(13);
      expect(result).toBe(offset1); // should return self
    });

    it("can multiply by another offset in-place", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(2, 3);
      var result = offset1.mul(offset2);
      expect(offset1.x).toEqual(10);
      expect(offset1.y).toEqual(30);
      expect(result).toBe(offset1); // should return self
    });

    it("can divide by another offset in-place", function() {
      var offset1 = new Offset(10, 30);
      var offset2 = new Offset(2, 3);
      var result = offset1.div(offset2);
      expect(offset1.x).toEqual(5);
      expect(offset1.y).toEqual(10);
      expect(result).toBe(offset1); // should return self
    });

    it("handles negative values in arithmetic", function() {
      var offset1 = new Offset(-5, -10);
      var offset2 = new Offset(3, 7);
      var result = offset1.add(offset2);
      expect(offset1.x).toEqual(-2);
      expect(offset1.y).toEqual(-3);
    });

    it("handles floating point arithmetic", function() {
      var offset1 = new Offset(1.5, 2.5);
      var offset2 = new Offset(0.5, 1.5);
      var result = offset1.add(offset2);
      expect(offset1.x).toEqual(2.0);
      expect(offset1.y).toEqual(4.0);
    });

  });

  describe("non-destructive arithmetic operations", function() {

    it("can add another offset and return new offset", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(3, 7);
      var result = offset1.plus(offset2);
      expect(result.x).toEqual(8);
      expect(result.y).toEqual(17);
      expect(offset1.x).toEqual(5); // original unchanged
      expect(offset1.y).toEqual(10);
      expect(result).not.toBe(offset1); // should be new object
    });

    it("can subtract another offset and return new offset", function() {
      var offset1 = new Offset(10, 20);
      var offset2 = new Offset(3, 7);
      var result = offset1.minus(offset2);
      expect(result.x).toEqual(7);
      expect(result.y).toEqual(13);
      expect(offset1.x).toEqual(10); // original unchanged
      expect(offset1.y).toEqual(20);
    });

    it("can multiply by another offset and return new offset", function() {
      var offset1 = new Offset(5, 10);
      var offset2 = new Offset(2, 3);
      var result = offset1.times(offset2);
      expect(result.x).toEqual(10);
      expect(result.y).toEqual(30);
      expect(offset1.x).toEqual(5); // original unchanged
      expect(offset1.y).toEqual(10);
    });

    it("can divide by another offset and return new offset", function() {
      var offset1 = new Offset(10, 30);
      var offset2 = new Offset(2, 3);
      var result = offset1.dividedby(offset2);
      expect(result.x).toEqual(5);
      expect(result.y).toEqual(10);
      expect(offset1.x).toEqual(10); // original unchanged
      expect(offset1.y).toEqual(30);
    });

  });

  describe("edge cases", function() {

    it("handles very large coordinates", function() {
      var offset = new Offset(1000000, 2000000);
      expect(offset.x).toEqual(1000000);
      expect(offset.y).toEqual(2000000);
    });

    it("handles very small coordinates", function() {
      var offset = new Offset(0.000001, 0.000002);
      expect(offset.x).toEqual(0.000001);
      expect(offset.y).toEqual(0.000002);
    });

    it("handles zero coordinates", function() {
      var offset = new Offset(0, 0);
      expect(offset.x).toEqual(0);
      expect(offset.y).toEqual(0);
    });

    it("handles division by zero coordinates", function() {
      var offset1 = new Offset(10, 20);
      var offset2 = new Offset(0, 5);
      // This should handle division by zero gracefully
      var result = offset1.div(offset2);
      expect(result).toBeDefined();
    });

  });

  describe("vector conversion", function() {

    it("can convert to vector", function() {
      var offset = new Offset(3, 4);
      var vector = offset.vector();
      expect(vector.x).toEqual(3);
      expect(vector.y).toEqual(4);
      expect(vector.constructor.name).toBe('Vector');
    });

    it("can convert negative offset to vector", function() {
      var offset = new Offset(-2, -5);
      var vector = offset.vector();
      expect(vector.x).toEqual(-2);
      expect(vector.y).toEqual(-5);
      expect(vector.constructor.name).toBe('Vector');
    });

    it("can convert zero offset to vector", function() {
      var offset = new Offset(0, 0);
      var vector = offset.vector();
      expect(vector.x).toEqual(0);
      expect(vector.y).toEqual(0);
      expect(vector.constructor.name).toBe('Vector');
    });

    it("can convert floating point offset to vector", function() {
      var offset = new Offset(1.5, 2.7);
      var vector = offset.vector();
      expect(vector.x).toEqual(1.5);
      expect(vector.y).toEqual(2.7);
      expect(vector.constructor.name).toBe('Vector');
    });

    it("returns new vector object", function() {
      var offset = new Offset(10, 20);
      var vector1 = offset.vector();
      var vector2 = offset.vector();
      expect(vector1).not.toBe(vector2); // should be different objects
      expect(vector1.x).toEqual(vector2.x);
      expect(vector1.y).toEqual(vector2.y);
    });

  });

});
