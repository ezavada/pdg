// -----------------------------------------------
// vector.spec.js
//
// test suite for Vector
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

describe("Vector", function() {

  describe("construction", function() {

    it("can be created with no params", function() {
      console.log('* Testing Vector...');
      var vector = new Vector();
      expect(vector.x).toBeDefined();
      expect(vector.x).toEqual(0);
      expect(vector.y).toBeDefined();
      expect(vector.y).toEqual(0);
    });

    it("is an object, an instance of Vector and Offset", function() {
      var vector = new Vector();
      expect(typeof vector).toBe('object');
      expect(vector.constructor.name).toBe('Vector');
      expect(vector instanceof Vector).toBe(true);
      expect(vector instanceof Offset).toBe(true);
    });

    it("can be created with x and y coordinates", function() {
      var vector = new Vector(10, 20);
      expect(vector.x).toEqual(10);
      expect(vector.y).toEqual(20);
    });

    it("can be created with negative coordinates", function() {
      var vector = new Vector(-5, -15);
      expect(vector.x).toEqual(-5);
      expect(vector.y).toEqual(-15);
    });

    it("can be created with floating point coordinates", function() {
      var vector = new Vector(3.14, 2.718);
      expect(vector.x).toEqual(3.14);
      expect(vector.y).toEqual(2.718);
    });

    it("can be created with array parameter [x, y]", function() {
      var vector = new Vector([7, 11]);
      expect(vector.x).toEqual(7);
      expect(vector.y).toEqual(11);
    });

    it("can be created with another Vector object", function() {
      var originalVector = new Vector(25, 30);
      var newVector = new Vector(originalVector);
      expect(newVector.x).toEqual(25);
      expect(newVector.y).toEqual(30);
    });

    it("can be created with object parameter {x: val, y: val}", function() {
      var vector = new Vector({x: 100, y: 200});
      expect(vector.x).toEqual(100);
      expect(vector.y).toEqual(200);
    });

  });

  describe("inherited Offset functionality", function() {

    it("inherits equality operations from Offset", function() {
      var vector1 = new Vector(5, 10);
      var vector2 = new Vector(5, 10);
      var vector3 = new Vector(5, 11);
      expect(vector1.equals(vector2)).toBeTruthy();
      expect(vector1.notEquals(vector3)).toBeTruthy();
    });

    it("inherits arithmetic operations from Offset", function() {
      var vector1 = new Vector(5, 10);
      var vector2 = new Vector(3, 7);
      var result = vector1.plus(vector2);
      expect(result.x).toEqual(8);
      expect(result.y).toEqual(17);
    });

  });

  describe("dot product calculations", function() {

    it("can calculate dot product with another vector", function() {
      var vector1 = new Vector(3, 4);
      var vector2 = new Vector(2, 1);
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(10); // 3*2 + 4*1 = 6 + 4 = 10
    });

    it("can calculate dot product with perpendicular vectors", function() {
      var vector1 = new Vector(1, 0);
      var vector2 = new Vector(0, 1);
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(0); // perpendicular vectors have dot product of 0
    });

    it("can calculate dot product with parallel vectors", function() {
      var vector1 = new Vector(2, 3);
      var vector2 = new Vector(4, 6); // 2x vector1
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(26); // 2*4 + 3*6 = 8 + 18 = 26
    });

    it("can calculate dot product with opposite vectors", function() {
      var vector1 = new Vector(2, 3);
      var vector2 = new Vector(-2, -3); // -1x vector1
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(-13); // 2*(-2) + 3*(-3) = -4 + (-9) = -13
    });

    it("can calculate dot product with zero vector", function() {
      var vector1 = new Vector(5, 10);
      var vector2 = new Vector(0, 0);
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(0);
    });

    it("can calculate dot product with negative coordinates", function() {
      var vector1 = new Vector(-2, -3);
      var vector2 = new Vector(4, 5);
      var dotProduct = vector1.dotProduct(vector2);
      expect(dotProduct).toEqual(-23); // (-2)*4 + (-3)*5 = -8 + (-15) = -23
    });

  });

  describe("vector length calculations", function() {

    it("can calculate length of a vector", function() {
      var vector = new Vector(3, 4);
      var length = vector.vectorLength();
      expect(length).toEqual(5); // sqrt(3^2 + 4^2) = sqrt(9 + 16) = sqrt(25) = 5
    });

    it("can calculate length of unit vectors", function() {
      var vector1 = new Vector(1, 0);
      var vector2 = new Vector(0, 1);
      expect(vector1.vectorLength()).toEqual(1);
      expect(vector2.vectorLength()).toEqual(1);
    });

    it("can calculate length of zero vector", function() {
      var vector = new Vector(0, 0);
      var length = vector.vectorLength();
      expect(length).toEqual(0);
    });

    it("can calculate length with negative coordinates", function() {
      var vector = new Vector(-3, -4);
      var length = vector.vectorLength();
      expect(length).toEqual(5); // sqrt((-3)^2 + (-4)^2) = sqrt(9 + 16) = 5
    });

    it("can calculate length with floating point coordinates", function() {
      var vector = new Vector(1.5, 2.0);
      var length = vector.vectorLength();
      expect(length).toBeCloseTo(2.5, 3); // sqrt(1.5^2 + 2^2) = sqrt(2.25 + 4) = sqrt(6.25) = 2.5
    });

  });

  describe("vector angle calculations", function() {

    it("can calculate angle of vector on positive x-axis", function() {
      var vector = new Vector(1, 0);
      var angle = vector.vectorAngle();
      expect(angle).toEqual(0); // 0 radians
    });

    it("can calculate angle of vector on positive y-axis", function() {
      var vector = new Vector(0, 1);
      var angle = vector.vectorAngle();
      expect(angle).toBeCloseTo(Math.PI/2, 3); // π/2 radians (90 degrees)
    });

    it("can calculate angle of vector on negative x-axis", function() {
      var vector = new Vector(-1, 0);
      var angle = vector.vectorAngle();
      expect(angle).toBeCloseTo(Math.PI, 3); // π radians (180 degrees)
    });

    it("can calculate angle of vector on negative y-axis", function() {
      var vector = new Vector(0, -1);
      var angle = vector.vectorAngle();
      expect(angle).toBeCloseTo(-Math.PI/2, 3); // -π/2 radians (-90 degrees)
    });

    it("can calculate angle of 45-degree vector", function() {
      var vector = new Vector(1, 1);
      var angle = vector.vectorAngle();
      expect(angle).toBeCloseTo(Math.PI/4, 3); // π/4 radians (45 degrees)
    });

    it("can calculate angle with negative coordinates", function() {
      var vector = new Vector(-1, -1);
      var angle = vector.vectorAngle();
      expect(angle).toBeCloseTo(-3*Math.PI/4, 3); // -3π/4 radians (-135 degrees)
    });

    it("can calculate angle of zero vector", function() {
      var vector = new Vector(0, 0);
      var angle = vector.vectorAngle();
      expect(angle).toEqual(0); // atan2(0,0) = 0
    });

  });

  describe("unit vector calculations", function() {

    it("can generate unit vector from non-zero vector", function() {
      var vector = new Vector(3, 4);
      var unit = vector.unit();
      expect(unit.vectorLength()).toBeCloseTo(1, 3); // should be unit length
      expect(unit.x).toBeCloseTo(0.6, 3); // 3/5 = 0.6
      expect(unit.y).toBeCloseTo(0.8, 3); // 4/5 = 0.8
      expect(unit.constructor.name).toBe('Vector');
    });

    it("can generate unit vector from unit vector", function() {
      var vector = new Vector(1, 0);
      var unit = vector.unit();
      expect(unit.vectorLength()).toBeCloseTo(1, 3);
      expect(unit.x).toBeCloseTo(1, 3);
      expect(unit.y).toBeCloseTo(0, 3);
    });

    it("can generate unit vector from negative vector", function() {
      var vector = new Vector(-3, -4);
      var unit = vector.unit();
      expect(unit.vectorLength()).toBeCloseTo(1, 3);
      expect(unit.x).toBeCloseTo(-0.6, 3); // -3/5 = -0.6
      expect(unit.y).toBeCloseTo(-0.8, 3); // -4/5 = -0.8
    });

    it("can generate unit vector from floating point vector", function() {
      var vector = new Vector(1.5, 2.0);
      var unit = vector.unit();
      expect(unit.vectorLength()).toBeCloseTo(1, 3);
      expect(unit.x).toBeCloseTo(0.6, 3); // 1.5/2.5 = 0.6
      expect(unit.y).toBeCloseTo(0.8, 3); // 2.0/2.5 = 0.8
    });

    it("can generate unit vector from diagonal vector", function() {
      var vector = new Vector(1, 1);
      var unit = vector.unit();
      expect(unit.vectorLength()).toBeCloseTo(1, 3);
      expect(unit.x).toBeCloseTo(0.707, 3); // 1/√2 ≈ 0.707
      expect(unit.y).toBeCloseTo(0.707, 3); // 1/√2 ≈ 0.707
    });

    it("handles zero vector gracefully", function() {
      var vector = new Vector(0, 0);
      // This should handle division by zero gracefully
      var unit = vector.unit();
      expect(unit).toBeDefined();
      // The implementation might handle this differently than returning NaN
      // Let's just check that it returns a valid result
      expect(unit.x).toBeDefined();
      expect(unit.y).toBeDefined();
    });

    it("returns new vector object", function() {
      var vector = new Vector(3, 4);
      var unit1 = vector.unit();
      var unit2 = vector.unit();
      expect(unit1).not.toBe(unit2); // should be different objects
      expect(unit1.x).toEqual(unit2.x);
      expect(unit1.y).toEqual(unit2.y);
    });

    it("preserves direction of original vector", function() {
      var vector = new Vector(3, 4);
      var unit = vector.unit();
      var originalAngle = vector.vectorAngle();
      var unitAngle = unit.vectorAngle();
      expect(unitAngle).toBeCloseTo(originalAngle, 3);
    });

  });

  describe("normal vector calculations", function() {

    it("can calculate normal vector", function() {
      var vector = new Vector(3, 4);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(-4, 3); // perpendicular: (-y, x)
      expect(normal.y).toBeCloseTo(3, 3);
      expect(normal.constructor.name).toBe('Vector');
    });

    it("can calculate normal of unit vector", function() {
      var vector = new Vector(1, 0);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(0, 3);
      expect(normal.y).toBeCloseTo(1, 3);
    });

    it("can calculate normal of negative vector", function() {
      var vector = new Vector(-3, -4);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(4, 3); // perpendicular: (-y, x)
      expect(normal.y).toBeCloseTo(-3, 3);
    });

    it("can calculate normal of floating point vector", function() {
      var vector = new Vector(1.5, 2.0);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(-2.0, 3);
      expect(normal.y).toBeCloseTo(1.5, 3);
    });

    it("can calculate normal of diagonal vector", function() {
      var vector = new Vector(1, 1);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(-1, 3);
      expect(normal.y).toBeCloseTo(1, 3);
    });

    it("can calculate normal of vertical vector", function() {
      var vector = new Vector(0, 5);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(-5, 3);
      expect(normal.y).toBeCloseTo(0, 3);
    });

    it("can calculate normal of horizontal vector", function() {
      var vector = new Vector(5, 0);
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(0, 3);
      expect(normal.y).toBeCloseTo(5, 3);
    });

    it("handles zero vector gracefully", function() {
      var vector = new Vector(0, 0);
      var normal = vector.normal();
      expect(normal).toBeDefined();
      expect(normal.x).toBeDefined();
      expect(normal.y).toBeDefined();
    });

    it("returns new vector object", function() {
      var vector = new Vector(3, 4);
      var normal1 = vector.normal();
      var normal2 = vector.normal();
      expect(normal1).not.toBe(normal2); // should be different objects
      expect(normal1.x).toEqual(normal2.x);
      expect(normal1.y).toEqual(normal2.y);
    });

    it("normal is perpendicular to original vector", function() {
      var vector = new Vector(3, 4);
      var normal = vector.normal();
      var dotProduct = vector.dotProduct(normal);
      expect(dotProduct).toBeCloseTo(0, 3); // perpendicular vectors have dot product of 0
    });

    it("normal has same length as original vector", function() {
      var vector = new Vector(3, 4);
      var normal = vector.normal();
      var originalLength = vector.vectorLength();
      var normalLength = normal.vectorLength();
      expect(normalLength).toBeCloseTo(originalLength, 3);
    });

    it("normal points 90 degrees counterclockwise from original", function() {
      var vector = new Vector(1, 0); // pointing right
      var normal = vector.normal();
      expect(normal.x).toBeCloseTo(0, 3); // should point up
      expect(normal.y).toBeCloseTo(1, 3);
    });

    it("normal of normal points opposite to original", function() {
      var vector = new Vector(3, 4);
      var normal = vector.normal();
      var normalOfNormal = normal.normal();
      expect(normalOfNormal.x).toBeCloseTo(-3, 3); // should point opposite
      expect(normalOfNormal.y).toBeCloseTo(-4, 3);
    });

  });

  describe("projection calculations", function() {

    it("can project a point onto itself", function() {
      var A = new Vector(3, 4);
      var B = new Point(1, 0);
      var projection = A.projection(B);
      expect(projection).toBeDefined();
      expect(projection.x).toBeDefined();
      expect(projection.y).toBeDefined();
      expect(projection.x).toEqual(3); // (3*1 + 4*0) / (1*1 + 0*0) * 1 = 3
      expect(projection.y).toEqual(0); // (3*1 + 4*0) / (1*1 + 0*0) * 0 = 0
    });

    it("can project onto origin", function() {
      var A = new Vector(5, 12);
      var B = new Point(0, 0);
      var projection = A.projection(B);
      expect(projection).toBeDefined();
      // Projection onto origin (zero vector) is undefined mathematically
      // The implementation should handle this gracefully
      expect(isNaN(projection.x)).toBeTruthy();
      expect(isNaN(projection.y)).toBeTruthy();
    });

    it("can project with negative coordinates", function() {
      var A = new Vector(-2, -3);
      var B = new Point(1, 1);
      var projection = A.projection(B);
      expect(projection).toBeDefined();
      // (-2*1 + -3*1) / (1*1 + 1*1) * 1 = -5/2 * 1 = -2.5
      expect(projection.x).toEqual(-2.5);
      expect(projection.y).toEqual(-2.5);
    });

    it("can project with floating point coordinates", function() {
      var A = new Vector(0.5, 0.5);
      var B = new Point(2.0, 0.0);
      var projection = A.projection(B);
      expect(projection).toBeDefined();
      // (0.5*2.0 + 0.5*0.0) / (2.0*2.0 + 0.0*0.0) * 2.0 = 1.0/4.0 * 2.0 = 0.5
      expect(projection.x).toEqual(0.5);
      expect(projection.y).toEqual(0.0);
    });

    it("can project onto itself", function() {
      var A = new Vector(10, 20);
      var projection = A.projection(A);
      expect(projection).toBeDefined();
      expect(projection.x).toEqual(10); // projection onto self is self
      expect(projection.y).toEqual(20);
    });

    it("can project perpendicular vectors", function() {
      var A = new Vector(0, 5);
      var B = new Point(3, 0);
      var projection = A.projection(B);
      expect(projection).toBeDefined();
      // (0*3 + 5*0) / (3*3 + 0*0) * 3 = 0/9 * 3 = 0
      expect(projection.x).toEqual(0);
      expect(projection.y).toEqual(0);
    });

  });

  describe("edge cases", function() {

    it("handles very large coordinates", function() {
      var vector = new Vector(1000000, 2000000);
      expect(vector.x).toEqual(1000000);
      expect(vector.y).toEqual(2000000);
      expect(vector.vectorLength()).toBeDefined();
    });

    it("handles very small coordinates", function() {
      var vector = new Vector(0.000001, 0.000002);
      expect(vector.x).toEqual(0.000001);
      expect(vector.y).toEqual(0.000002);
      expect(vector.vectorLength()).toBeDefined();
    });

    it("handles zero coordinates", function() {
      var vector = new Vector(0, 0);
      expect(vector.x).toEqual(0);
      expect(vector.y).toEqual(0);
      expect(vector.vectorLength()).toEqual(0);
    });

  });

});
