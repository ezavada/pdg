// -----------------------------------------------
// polygon.spec.js
//
// test suite for Polygon class
//
// Written by AI Assistant, 2024
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

describe("Polygon", function() {

  describe("availability", function() {

    it("checks if Polygon is available", function() {
      console.log('* Testing Polygon...');
      console.log('pdg.Polygon:', typeof pdg.Polygon);
      
      expect(pdg.Polygon).toBeDefined();
      expect(typeof pdg.Polygon).toBe('function');
    });

  });

  describe("construction", function() {

    it("can be created with default constructor", function() {
      var poly = new pdg.Polygon();
      expect(poly).toBeDefined();
      expect(typeof poly).toBe('object');
      expect(poly.constructor.name).toBe('Polygon');
      expect(poly.getPointCount()).toBe(0);
      expect(poly.empty()).toBe(true);
    });

    it("can be created with individual point arguments", function() {
      var p1 = new pdg.Point(0, 0);
      var p2 = new pdg.Point(100, 0);
      var p3 = new pdg.Point(50, 100);
      
      var poly = new pdg.Polygon(p1, p2, p3);
      expect(poly).toBeDefined();
      expect(poly.getPointCount()).toBe(3);
      expect(poly.empty()).toBe(false);
    });

    it("can be created with array of points", function() {
      var points = [
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      ];
      
      var poly = new pdg.Polygon(points);
      expect(poly).toBeDefined();
      expect(poly.getPointCount()).toBe(3);
    });

    it("can be created with single point", function() {
      var p1 = new pdg.Point(50, 50);
      var poly = new pdg.Polygon(p1);
      expect(poly).toBeDefined();
      expect(poly.getPointCount()).toBe(1);
    });

  });

  describe("point management", function() {

    var poly;

    beforeEach(function() {
      poly = new pdg.Polygon();
    });

    it("can add points", function() {
      var p1 = new pdg.Point(0, 0);
      var p2 = new pdg.Point(100, 0);
      
      poly.addPoint(p1);
      expect(poly.getPointCount()).toBe(1);
      
      poly.addPoint(p2);
      expect(poly.getPointCount()).toBe(2);
    });

    it("can get points by index", function() {
      var p1 = new pdg.Point(10, 20);
      var p2 = new pdg.Point(30, 40);
      
      poly.addPoint(p1);
      poly.addPoint(p2);
      
      var retrievedP1 = poly.getPoint(0);
      var retrievedP2 = poly.getPoint(1);
      
      expect(retrievedP1.x).toBe(10);
      expect(retrievedP1.y).toBe(20);
      expect(retrievedP2.x).toBe(30);
      expect(retrievedP2.y).toBe(40);
    });

    it("can set points by index", function() {
      var p1 = new pdg.Point(10, 20);
      var p2 = new pdg.Point(30, 40);
      var p3 = new pdg.Point(50, 60);
      
      poly.addPoint(p1);
      poly.addPoint(p2);
      
      poly.setPoint(1, p3);
      
      var retrieved = poly.getPoint(1);
      expect(retrieved.x).toBe(50);
      expect(retrieved.y).toBe(60);
    });

    it("can insert points at specific index", function() {
      var p1 = new pdg.Point(10, 20);
      var p2 = new pdg.Point(30, 40);
      var p3 = new pdg.Point(50, 60);
      
      poly.addPoint(p1);
      poly.addPoint(p2);
      
      poly.insertPoint(1, p3);
      
      expect(poly.getPointCount()).toBe(3);
      expect(poly.getPoint(1).x).toBe(50);
      expect(poly.getPoint(1).y).toBe(60);
      expect(poly.getPoint(2).x).toBe(30);
      expect(poly.getPoint(2).y).toBe(40);
    });

    it("can remove points by index", function() {
      var p1 = new pdg.Point(10, 20);
      var p2 = new pdg.Point(30, 40);
      var p3 = new pdg.Point(50, 60);
      
      poly.addPoint(p1);
      poly.addPoint(p2);
      poly.addPoint(p3);
      
      poly.removePoint(1);
      
      expect(poly.getPointCount()).toBe(2);
      expect(poly.getPoint(0).x).toBe(10);
      expect(poly.getPoint(1).x).toBe(50);
    });

    it("can clear all points", function() {
      var p1 = new pdg.Point(10, 20);
      var p2 = new pdg.Point(30, 40);
      
      poly.addPoint(p1);
      poly.addPoint(p2);
      
      expect(poly.getPointCount()).toBe(2);
      
      poly.clearPoints();
      
      expect(poly.getPointCount()).toBe(0);
      expect(poly.empty()).toBe(true);
    });

    it("throws error for invalid index operations", function() {
      var p1 = new pdg.Point(10, 20);
      poly.addPoint(p1);
      
      expect(function() {
        poly.getPoint(5);
      }).toThrow();
      
      expect(function() {
        poly.setPoint(5, p1);
      }).toThrow();
      
      expect(function() {
        poly.removePoint(5);
      }).toThrow();
    });

  });

  describe("geometric operations", function() {

    var poly;

    beforeEach(function() {
      // Create a triangle
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
    });

    it("can calculate bounding box", function() {
      var bounds = poly.getBounds();
      
      expect(bounds.left).toBe(0);
      expect(bounds.top).toBe(0);
      expect(bounds.right).toBe(100);
      expect(bounds.bottom).toBe(100);
    });

    it("can calculate center point", function() {
      var center = poly.centerPoint();
      
      expect(center.x).toBeCloseTo(50, 1);
      expect(center.y).toBeCloseTo(33.33, 1);
    });

    it("can test point containment", function() {
      // Point inside triangle
      var insidePoint = new pdg.Point(50, 50);
      expect(poly.contains(insidePoint)).toBe(true);
      
      // Point outside triangle
      var outsidePoint = new pdg.Point(150, 150);
      expect(poly.contains(outsidePoint)).toBe(false);
      
      // Point on edge (may or may not be considered inside depending on implementation)
      var edgePoint = new pdg.Point(25, 50);
      expect(typeof poly.contains(edgePoint)).toBe('boolean');
    });

    it("returns correct empty status", function() {
      expect(poly.empty()).toBe(false);
      
      var emptyPoly = new pdg.Polygon();
      expect(emptyPoly.empty()).toBe(true);
      
      emptyPoly.addPoint(new pdg.Point(0, 0));
      expect(emptyPoly.empty()).toBe(true); // Still empty with only 1 point
      
      emptyPoly.addPoint(new pdg.Point(100, 0));
      expect(emptyPoly.empty()).toBe(true); // Still empty with only 2 points
      
      emptyPoly.addPoint(new pdg.Point(50, 100));
      expect(emptyPoly.empty()).toBe(false); // Not empty with 3 points
    });

  });

  describe("movement transformations", function() {

    var poly;

    beforeEach(function() {
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
    });

    it("can move left", function() {
      poly.moveLeft(10);
      
      expect(poly.getPoint(0).x).toBe(-10);
      expect(poly.getPoint(1).x).toBe(90);
      expect(poly.getPoint(2).x).toBe(40);
    });

    it("can move right", function() {
      poly.moveRight(10);
      
      expect(poly.getPoint(0).x).toBe(10);
      expect(poly.getPoint(1).x).toBe(110);
      expect(poly.getPoint(2).x).toBe(60);
    });

    it("can move up", function() {
      poly.moveUp(10);
      
      expect(poly.getPoint(0).y).toBe(-10);
      expect(poly.getPoint(1).y).toBe(-10);
      expect(poly.getPoint(2).y).toBe(90);
    });

    it("can move down", function() {
      poly.moveDown(10);
      
      expect(poly.getPoint(0).y).toBe(10);
      expect(poly.getPoint(1).y).toBe(10);
      expect(poly.getPoint(2).y).toBe(110);
    });

    it("can move to specific x coordinate", function() {
      poly.moveXTo(50);
      
      var bounds = poly.getBounds();
      expect(bounds.left).toBe(50);
      expect(bounds.right).toBe(150);
    });

    it("can move to specific y coordinate", function() {
      poly.moveYTo(50);
      
      var bounds = poly.getBounds();
      expect(bounds.top).toBe(50);
      expect(bounds.bottom).toBe(150);
    });

    it("can move to specific point", function() {
      poly.moveTo(200, 300);
      
      var bounds = poly.getBounds();
      expect(bounds.left).toBe(200);
      expect(bounds.top).toBe(300);
      expect(bounds.right).toBe(300);
      expect(bounds.bottom).toBe(400);
    });

    it("can center on a point", function() {
      var targetPoint = new pdg.Point(100, 100);
      poly.center(targetPoint);
      
      var center = poly.centerPoint();
      expect(center.x).toBeCloseTo(100, 1);
      expect(center.y).toBeCloseTo(100, 1);
    });

  });

  describe("scaling transformations", function() {

    var poly;

    beforeEach(function() {
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
    });

    it("can scale uniformly", function() {
      poly.scale(2.0);
      
      expect(poly.getPoint(0).x).toBe(0);
      expect(poly.getPoint(1).x).toBe(200);
      expect(poly.getPoint(2).x).toBe(100);
      expect(poly.getPoint(0).y).toBe(0);
      expect(poly.getPoint(1).y).toBe(0);
      expect(poly.getPoint(2).y).toBe(200);
    });

    it("can scale horizontally", function() {
      poly.horzScale(2.0);
      
      expect(poly.getPoint(0).x).toBe(0);
      expect(poly.getPoint(1).x).toBe(200);
      expect(poly.getPoint(2).x).toBe(100);
      // Y coordinates should remain unchanged
      expect(poly.getPoint(0).y).toBe(0);
      expect(poly.getPoint(1).y).toBe(0);
      expect(poly.getPoint(2).y).toBe(100);
    });

    it("can scale vertically", function() {
      poly.vertScale(2.0);
      
      expect(poly.getPoint(0).y).toBe(0);
      expect(poly.getPoint(1).y).toBe(0);
      expect(poly.getPoint(2).y).toBe(200);
      // X coordinates should remain unchanged
      expect(poly.getPoint(0).x).toBe(0);
      expect(poly.getPoint(1).x).toBe(100);
      expect(poly.getPoint(2).x).toBe(50);
    });

    it("can scale around a center point", function() {
      var centerPoint = new pdg.Point(50, 50);
      poly.scaleAround(2.0, centerPoint);
      
      // The polygon should be larger
      var bounds = poly.getBounds();
      expect(bounds.width()).toBeCloseTo(200, 1);
      expect(bounds.height()).toBeCloseTo(200, 1);
      
      // After scaling around (50,50), the new geometric center should be (50, 16.67)
      var newCenter = poly.centerPoint();
      expect(newCenter.x).toBeCloseTo(50, 1);
      expect(newCenter.y).toBeCloseTo(16.67, 1);
    });

  });

  describe("rotation transformations", function() {

    var poly;

    beforeEach(function() {
      // Create a square for easier testing
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(100, 100),
        new pdg.Point(0, 100)
      );
    });

    it("can rotate around its center", function() {
      var originalCenter = poly.centerPoint();
      poly.rotate(Math.PI / 2); // 90 degrees
      
      var newCenter = poly.centerPoint();
      expect(newCenter.x).toBeCloseTo(originalCenter.x, 1);
      expect(newCenter.y).toBeCloseTo(originalCenter.y, 1);
    });

    it("can rotate around a specific point", function() {
      var rotationCenter = new pdg.Point(50, 50);
      poly.rotateAround(Math.PI / 4, rotationCenter); // 45 degrees
      
      // The rotation center should remain unchanged
      var center = poly.centerPoint();
      expect(center.x).toBeCloseTo(rotationCenter.x, 1);
      expect(center.y).toBeCloseTo(rotationCenter.y, 1);
    });

  });

  describe("operators", function() {

    var poly;

    beforeEach(function() {
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
    });

    it("can use move with offset", function() {
      var offset = new pdg.Offset(10, 20);
      poly.move(offset);
      
      expect(poly.getPoint(0).x).toBe(10);
      expect(poly.getPoint(0).y).toBe(20);
      expect(poly.getPoint(1).x).toBe(110);
      expect(poly.getPoint(1).y).toBe(20);
      expect(poly.getPoint(2).x).toBe(60);
      expect(poly.getPoint(2).y).toBe(120);
    });

  });

  describe("equality", function() {

    it("can test equality with identical polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      expect(poly1.equals(poly2)).toBe(true);
      expect(!poly1.equals(poly2)).toBe(false);
    });

    it("can test equality with different polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(200, 0),
        new pdg.Point(100, 100)
      );
      
      expect(poly1.equals(poly2)).toBe(false);
      expect(!poly1.equals(poly2)).toBe(true);
    });

  });

  describe("error handling", function() {

    var poly;

    beforeEach(function() {
      poly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
    });

    it("handles empty polygon operations gracefully", function() {
      var emptyPoly = new pdg.Polygon();
      
      expect(emptyPoly.getPointCount()).toBe(0);
      expect(emptyPoly.empty()).toBe(true);
      
      var bounds = emptyPoly.getBounds();
      expect(bounds.empty()).toBe(true);
      
      var center = emptyPoly.centerPoint();
      expect(center.x).toBe(0);
      expect(center.y).toBe(0);
    });

    it("handles invalid point operations", function() {
      var invalidPoint = "not a point";
      
      expect(function() {
        poly.addPoint(invalidPoint);
      }).toThrow();
    });

  });

  describe("boolean operations", function() {

    it("can perform intersection of overlapping triangles", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(50, 0),
        new pdg.Point(150, 0),
        new pdg.Point(100, 100)
      );
      
      var result = poly1.intersection(poly2);
      expect(result).toBeDefined();
      expect(typeof result).toBe('object');
      expect(result.constructor.name).toBe('Polygon');
    });

    it("can perform union of overlapping triangles", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(50, 0),
        new pdg.Point(150, 0),
        new pdg.Point(100, 100)
      );
      
      var result = poly1.unionWith(poly2);
      expect(result).toBeDefined();
      expect(typeof result).toBe('object');
      expect(result.constructor.name).toBe('Polygon');
    });

    it("handles intersection of non-overlapping polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(50, 0),
        new pdg.Point(25, 50)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(100, 0),
        new pdg.Point(150, 0),
        new pdg.Point(125, 50)
      );
      
      var result = poly1.intersection(poly2);
      expect(result).toBeDefined();
      expect(result.empty()).toBe(true); // Should be empty for non-overlapping polygons
    });

    it("handles union of non-overlapping polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(50, 0),
        new pdg.Point(25, 50)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(100, 0),
        new pdg.Point(150, 0),
        new pdg.Point(125, 50)
      );
      
      var result = poly1.unionWith(poly2);
      expect(result).toBeDefined();
      expect(result.constructor.name).toBe('Polygon');
      // For non-overlapping polygons, union should return one of the polygons
    });

    it("handles intersection with empty polygon", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var emptyPoly = new pdg.Polygon();
      
      var result = poly1.intersection(emptyPoly);
      expect(result).toBeDefined();
      expect(result.empty()).toBe(true);
    });

    it("handles union with empty polygon", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(100, 0),
        new pdg.Point(50, 100)
      );
      
      var emptyPoly = new pdg.Polygon();
      
      var result = poly1.unionWith(emptyPoly);
      expect(result).toBeDefined();
      expect(result.getPointCount()).toBe(poly1.getPointCount());
    });

    it("handles intersection with completely contained polygon", function() {
      var outerPoly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(200, 0),
        new pdg.Point(200, 200),
        new pdg.Point(0, 200)
      );
      
      var innerPoly = new pdg.Polygon(
        new pdg.Point(50, 50),
        new pdg.Point(150, 50),
        new pdg.Point(150, 150),
        new pdg.Point(50, 150)
      );
      
      var result = outerPoly.intersection(innerPoly);
      expect(result).toBeDefined();
      expect(result.constructor.name).toBe('Polygon');
    });

    it("handles union with completely contained polygon", function() {
      var outerPoly = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(200, 0),
        new pdg.Point(200, 200),
        new pdg.Point(0, 200)
      );
      
      var innerPoly = new pdg.Polygon(
        new pdg.Point(50, 50),
        new pdg.Point(150, 50),
        new pdg.Point(150, 150),
        new pdg.Point(50, 150)
      );
      
      var result = outerPoly.unionWith(innerPoly);
      expect(result).toBeDefined();
      expect(result.constructor.name).toBe('Polygon');
    });

    it("handles intersection with touching polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(50, 0),
        new pdg.Point(50, 50),
        new pdg.Point(0, 50)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(50, 0),
        new pdg.Point(100, 0),
        new pdg.Point(100, 50),
        new pdg.Point(50, 50)
      );
      
      var result = poly1.intersection(poly2);
      expect(result).toBeDefined();
      expect(result.constructor.name).toBe('Polygon');
    });

    it("handles union with touching polygons", function() {
      var poly1 = new pdg.Polygon(
        new pdg.Point(0, 0),
        new pdg.Point(50, 0),
        new pdg.Point(50, 50),
        new pdg.Point(0, 50)
      );
      
      var poly2 = new pdg.Polygon(
        new pdg.Point(50, 0),
        new pdg.Point(100, 0),
        new pdg.Point(100, 50),
        new pdg.Point(50, 50)
      );
      
      var result = poly1.unionWith(poly2);
      expect(result).toBeDefined();
      expect(result.constructor.name).toBe('Polygon');
    });

    // Note: Invalid argument testing is not included because the current binding system
    // crashes when invalid arguments are passed to methods that expect objects.
    // This is a limitation of the current REQUIRE_OBJECT_ARG macro implementation.

  });

  describe("addSpline", function() {

    it("adds points from a simple spline with default step", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      var poly = new pdg.Polygon();
      poly.addSpline(spline);
      
      expect(poly.getPointCount()).toBeGreaterThan(0);
      // With default step of 0.01 and filtering, we should get a reasonable number of points
      expect(poly.getPointCount()).toBeGreaterThan(10);
      expect(poly.getPointCount()).toBeLessThan(150);
      
      // First point should be at the start of the spline
      var firstPoint = poly.getPoint(0);
      expect(firstPoint.x).toBeCloseTo(0, 0.1);
      expect(firstPoint.y).toBeCloseTo(0, 0.1);
    });

    it("adds points from a spline with custom step", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      var poly = new pdg.Polygon();
      poly.addSpline(spline, 0.1);
      
      // With step of 0.1, we should get approximately 11 points (0.0, 0.1, 0.2, ... 1.0)
      // But filtering might remove some that are too close
      expect(poly.getPointCount()).toBeGreaterThan(5);
      expect(poly.getPointCount()).toBeLessThan(15);
    });

    it("uses correct step values for different uStep parameters", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      // Test with step 0.2
      var poly1 = new pdg.Polygon();
      poly1.addSpline(spline, 0.2);
      var count1 = poly1.getPointCount();
      expect(count1).toBeGreaterThan(3);
      expect(count1).toBeLessThan(10);

      // Test with step 0.5
      var poly2 = new pdg.Polygon();
      poly2.addSpline(spline, 0.5);
      var count2 = poly2.getPointCount();
      expect(count2).toBeGreaterThan(1);
      expect(count2).toBeLessThan(5);

      // Larger step should produce fewer points
      expect(count2).toBeLessThan(count1);
    });

    it("falls back to default step for invalid uStep values", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      // Test with invalid step (> 1.0)
      var poly1 = new pdg.Polygon();
      poly1.addSpline(spline, 2.0);

      // Test with default step
      var poly2 = new pdg.Polygon();
      poly2.addSpline(spline);

      // Both should have similar point counts since invalid step falls back to default
      expect(poly1.getPointCount()).toBeCloseTo(poly2.getPointCount(), 10);
    });

    it("filters points that are too close together", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      // Create a nearly horizontal line where filtering will matter
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(0.1, 0.1),
        new pdg.Point(0.2, 0.1),
        new pdg.Point(0.3, 0)
      );

      var poly = new pdg.Polygon();
      poly.addSpline(spline, 0.01);
      
      // Very small spline with tiny steps should still filter most points
      // because they're too close (< 0.4 in both x and y)
      expect(poly.getPointCount()).toBeLessThan(20);
    });

    it("appends to existing polygon points", function() {
      var poly = new pdg.Polygon();
      poly.addPoint(new pdg.Point(-10, -10));
      poly.addPoint(new pdg.Point(-5, -5));
      
      var initialCount = poly.getPointCount();
      expect(initialCount).toBe(2);

      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      poly.addSpline(spline, 0.1);
      
      // Should have initial points plus spline points
      expect(poly.getPointCount()).toBeGreaterThan(initialCount);
      
      // First two points should still be the original ones
      var p0 = poly.getPoint(0);
      var p1 = poly.getPoint(1);
      expect(p0.x).toBe(-10);
      expect(p0.y).toBe(-10);
      expect(p1.x).toBe(-5);
      expect(p1.y).toBe(-5);
    });

    it("continues from last polygon point when appending", function() {
      var poly = new pdg.Polygon();
      poly.addPoint(new pdg.Point(10, 10));
      
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addSegment(
        new pdg.Point(10, 10),  // Exactly at last point
        new pdg.Point(20, 40),
        new pdg.Point(60, 40),
        new pdg.Point(80, 0)
      );

      var initialCount = poly.getPointCount();
      poly.addSpline(spline, 0.1);
      
      // Should add spline points, filtering uses the last existing polygon point
      expect(poly.getPointCount()).toBeGreaterThan(initialCount);
      
      // First polygon point should still be at (10, 10)
      var p0 = poly.getPoint(0);
      expect(p0.x).toBe(10);
      expect(p0.y).toBe(10);
    });

    it("works with multi-segment splines", function() {
      // Use low-level API to create a proper 2-segment Bezier spline
      // First segment: 4 points, additional segments: 3 points each
      // Total for 2 segments: 4 + 3 = 7 points
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      spline.addPoint(new pdg.Point(0, 0));
      spline.addPoint(new pdg.Point(10, 20));
      spline.addPoint(new pdg.Point(30, 20));
      spline.addPoint(new pdg.Point(40, 0));
      spline.addPoint(new pdg.Point(50, -20));
      spline.addPoint(new pdg.Point(70, -20));
      spline.addPoint(new pdg.Point(80, 0));

      expect(spline.getMaxU()).toBe(2);
      expect(spline.getPointCount()).toBe(7);

      var poly = new pdg.Polygon();
      poly.addSpline(spline, 0.1);
      
      // With 2 segments and step 0.1, we should get more points
      // Each segment gets evaluated at u increments of 0.1 from 0 to maxU (2.0)
      // So we'd evaluate at 0.0, 0.1, 0.2, ... 2.0 = 21 evaluations
      // But filtering will reduce this
      expect(poly.getPointCount()).toBeGreaterThan(10);
      expect(poly.getPointCount()).toBeLessThan(30);
    });

    it("handles Cardinal splines", function() {
      var spline = new pdg.Spline(pdg.spline_Cardinal);
      spline.addPoint(new pdg.Point(0, 0));
      spline.addPoint(new pdg.Point(20, 40));
      spline.addPoint(new pdg.Point(60, 40));
      spline.addPoint(new pdg.Point(80, 0));

      var poly = new pdg.Polygon();
      poly.addSpline(spline, 0.1);
      
      expect(poly.getPointCount()).toBeGreaterThan(0);
    });

    it("handles empty spline gracefully", function() {
      var spline = new pdg.Spline(pdg.spline_CubicBezier);
      // No points added

      var poly = new pdg.Polygon();
      poly.addSpline(spline);
      
      // Should not add any points from empty spline
      expect(poly.getPointCount()).toBe(0);
    });

  });

});
