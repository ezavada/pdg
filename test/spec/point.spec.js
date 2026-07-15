// -----------------------------------------------
// point.spec.js
//
// test suite for Point
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

describe("Point", function() {

  describe("construction", function() {

    it("can be created with no params", function() {
      console.log('* Testing Point...');
      var point = new Point();
      expect(point.x).toBeDefined();
      expect(point.x).toEqual(0);
      expect(point.y).toBeDefined();
      expect(point.y).toEqual(0);
    });

    if("is an object, an instance of Point and Offset", function() {
      var point = new Point();
      expect(typeof point).toBe('object');
      expect(point.constructor.name).toBe('Point');
      expect(point instanceof Point).toBe(true);
      expect(point instanceof Offset).toBe(true);
    });

    it("can be created with x and y coordinates", function() {
      var point = new Point(10, 20);
      expect(point.x).toEqual(10);
      expect(point.y).toEqual(20);
    });

    it("can be created with negative coordinates", function() {
      var point = new Point(-5, -15);
      expect(point.x).toEqual(-5);
      expect(point.y).toEqual(-15);
    });

    it("can be created with floating point coordinates", function() {
      var point = new Point(3.14, 2.718);
      expect(point.x).toEqual(3.14);
      expect(point.y).toEqual(2.718);
    });

    it("can be created with array parameter [x, y]", function() {
      var point = new Point([7, 11]);
      expect(point.x).toEqual(7);
      expect(point.y).toEqual(11);
    });

    it("can be created with another Point object", function() {
      var originalPoint = new Point(25, 30);
      var newPoint = new Point(originalPoint);
      expect(newPoint.x).toEqual(25);
      expect(newPoint.y).toEqual(30);
    });

    it("can be created with object parameter {x: val, y: val}", function() {
      var point = new Point({x: 100, y: 200});
      expect(point.x).toEqual(100);
      expect(point.y).toEqual(200);
    });

  });

  describe("distance calculations", function() {

    it("can calculate distance to another point", function() {
      var point1 = new Point(0, 0);
      var point2 = new Point(3, 4);
      var distance = point1.distance(point2);
      expect(distance).toEqual(5); // 3-4-5 triangle
    });

    it("can calculate distance to origin", function() {
      var point = new Point(5, 12);
      var origin = new Point(0, 0);
      var distance = point.distance(origin);
      expect(distance).toEqual(13); // 5-12-13 triangle
    });

    it("can calculate distance between two arbitrary points", function() {
      var point1 = new Point(1, 1);
      var point2 = new Point(4, 5);
      var distance = point1.distance(point2);
      expect(distance).toEqual(5); // sqrt((4-1)^2 + (5-1)^2) = sqrt(9 + 16) = 5
    });

    it("can calculate distance with negative coordinates", function() {
      var point1 = new Point(-2, -3);
      var point2 = new Point(1, 1);
      var distance = point1.distance(point2);
      expect(distance).toEqual(5); // sqrt((1-(-2))^2 + (1-(-3))^2) = sqrt(9 + 16) = 5
    });

    it("can calculate distance with floating point coordinates", function() {
      var point1 = new Point(0.5, 0.5);
      var point2 = new Point(2.5, 2.5);
      var distance = point1.distance(point2);
      expect(distance).toBeCloseTo(2.828, 3); // sqrt(2^2 + 2^2) = sqrt(8) ≈ 2.828
    });

    it("returns zero distance to itself", function() {
      var point = new Point(10, 20);
      var distance = point.distance(point);
      expect(distance).toEqual(0);
    });

  });

  describe("offset calculations", function() {

    it("can calculate offset from another point", function() {
      var point1 = new Point(1, 2);
      var point2 = new Point(4, 6);
      var offset = point1.offset(point2);
      expect(offset.x).toEqual(3); // 4 - 1
      expect(offset.y).toEqual(4); // 6 - 2
      expect(offset.constructor.name).toBe('Offset');
    });

    it("can calculate offset to origin", function() {
      var point = new Point(5, 12);
      var origin = new Point(0, 0);
      var offset = point.offset(origin);
      expect(offset.x).toEqual(-5); // 0 - 5
      expect(offset.y).toEqual(-12); // 0 - 12
    });

    it("can calculate offset with negative coordinates", function() {
      var point1 = new Point(-2, -3);
      var point2 = new Point(1, 1);
      var offset = point1.offset(point2);
      expect(offset.x).toEqual(3); // 1 - (-2)
      expect(offset.y).toEqual(4); // 1 - (-3)
    });

    it("can calculate offset with floating point coordinates", function() {
      var point1 = new Point(0.5, 0.5);
      var point2 = new Point(2.5, 2.5);
      var offset = point1.offset(point2);
      expect(offset.x).toEqual(2.0); // 2.5 - 0.5
      expect(offset.y).toEqual(2.0); // 2.5 - 0.5
    });

    it("returns zero offset to itself", function() {
      var point = new Point(10, 20);
      var offset = point.offset(point);
      expect(offset.x).toEqual(0);
      expect(offset.y).toEqual(0);
    });

  });


  describe("edge cases", function() {

    it("handles very large coordinates", function() {
      var point = new Point(1000000, 2000000);
      expect(point.x).toEqual(1000000);
      expect(point.y).toEqual(2000000);
    });

    it("handles very small coordinates", function() {
      var point = new Point(0.000001, 0.000002);
      expect(point.x).toEqual(0.000001);
      expect(point.y).toEqual(0.000002);
    });

    it("handles zero coordinates", function() {
      var point = new Point(0, 0);
      expect(point.x).toEqual(0);
      expect(point.y).toEqual(0);
    });

  });

});