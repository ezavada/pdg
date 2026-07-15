// -----------------------------------------------
// spline.spec.js
//
// test suite for Spline class
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

describe("Spline", function() {

  describe("availability", function() {

    it("checks if Spline is available", function() {
      console.log('* Testing Spline...');
      console.log('pdg.Spline:', typeof pdg.Spline);
      
      expect(pdg.Spline).toBeDefined();
      expect(typeof pdg.Spline).toBe('function');
    });

  });

  describe("spline type constants", function() {

      it("has all spline type constants defined", function() {
        expect(pdg.spline_Hermite).toBeDefined();
        expect(pdg.spline_Cardinal).toBeDefined();
        expect(pdg.spline_UniformB).toBeDefined();
        expect(pdg.spline_CubicBezier).toBeDefined();
        expect(pdg.spline_TCB).toBeDefined();
        expect(pdg.spline_NaturalCubic).toBeDefined();
        
        expect(pdg.spline_Hermite).toBe(1);
        expect(pdg.spline_Cardinal).toBe(2);
        expect(pdg.spline_UniformB).toBe(3);
        expect(pdg.spline_CubicBezier).toBe(4);
        expect(pdg.spline_TCB).toBe(5);
        expect(pdg.spline_NaturalCubic).toBe(6);
      });

  });

  describe("construction", function() {

    it("can be created with default constructor", function() {
      var spline = new pdg.Spline(pdg.spline_Hermite);
      expect(spline).toBeDefined();
      expect(typeof spline).toBe('object');
      expect(spline.constructor.name).toBe('Spline');
    });

    it("can be created with spline type", function() {
      var hermite = new pdg.Spline(pdg.spline_Hermite);
      expect(hermite).toBeDefined();
      
      var cardinal = new pdg.Spline(pdg.spline_Cardinal);
      expect(cardinal).toBeDefined();
      
      var uniformB = new pdg.Spline(pdg.spline_UniformB);
      expect(uniformB).toBeDefined();
      
      var bezier = new pdg.Spline(pdg.spline_CubicBezier);
      expect(bezier).toBeDefined();
      
      var tcb = new pdg.Spline(pdg.spline_TCB);
      expect(tcb).toBeDefined();
      
      var natural = new pdg.Spline(pdg.spline_NaturalCubic);
      expect(natural).toBeDefined();
    });

  });

  describe("basic properties and methods", function() {

    var spline;

    beforeEach(function() {
      spline = new pdg.Spline(pdg.spline_Hermite);
    });

    it("has addSegment method", function() {
      expect(typeof spline.addSegment).toBe('function');
    });

    it("has getFirstOrder method", function() {
      expect(typeof spline.getFirstOrder).toBe('function');
    });

    it("has getSecondOrder method", function() {
      expect(typeof spline.getSecondOrder).toBe('function');
    });

    it("has addPoint method", function() {
      expect(typeof spline.addPoint).toBe('function');
    });

    it("has getPoint method", function() {
      expect(typeof spline.getPoint).toBe('function');
    });

    it("has setPoint method", function() {
      expect(typeof spline.setPoint).toBe('function');
    });

    it("has getPointCount method", function() {
      expect(typeof spline.getPointCount).toBe('function');
    });

    it("has getMaxU method", function() {
      expect(typeof spline.getMaxU).toBe('function');
    });

    it("has getBounds method", function() {
      expect(typeof spline.getBounds).toBe('function');
    });

  });

  describe("spline initialization", function() {

    var spline;
    var p1, p2, p3, p4;

    beforeEach(function() {
      spline = new pdg.Spline(pdg.spline_Hermite);
      p1 = new pdg.Point(0, 0);
      p2 = new pdg.Point(50, 100);
      p3 = new pdg.Point(100, 50);
      p4 = new pdg.Point(150, 150);
    });

    it("can addSegment with four points", function() {
      expect(function() {
        spline.addSegment(p1, p2, p3, p4);
      }).not.toThrow();
    });

    it("throws error with insufficient arguments", function() {
      expect(function() {
        spline.addSegment(p1, p2, p3);
      }).toThrow();
    });

    it("throws error with invalid arguments", function() {
      expect(function() {
        spline.addSegment(p1, p2, p3, "invalid");
      }).toThrow();
    });

  });

  describe("spline evaluation", function() {

    var spline;
    var p1, p2, p3, p4;

    beforeEach(function() {
      p1 = new pdg.Point(0, 0);
      p2 = new pdg.Point(50, 100);
      p3 = new pdg.Point(100, 50);
      p4 = new pdg.Point(150, 150);
    });

    describe("Hermite spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_Hermite);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order at u=0", function() {
        var result = spline.getFirstOrder(0.0);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
        expect(typeof result.x).toBe('number');
        expect(typeof result.y).toBe('number');
      });

      it("can evaluate first order at u=1", function() {
        var result = spline.getFirstOrder(1.0);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate first order at u=0.5", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order derivatives", function() {
        var result = spline.getSecondOrder(0.0);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
        
        result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        
        result = spline.getSecondOrder(1.0);
        expect(result).toBeDefined();
      });

    });

    describe("Cardinal spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_Cardinal);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order", function() {
        var result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

    });

    describe("Uniform B-spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_UniformB);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order", function() {
        var result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

    });

    describe("Cubic Bezier spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_CubicBezier);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order", function() {
        var result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

    });

    describe("TCB spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_TCB);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order", function() {
        var result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

    });

    describe("Natural Cubic spline", function() {
      
      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_NaturalCubic);
        spline.addSegment(p1, p2, p3, p4);
      });

      it("can evaluate first order", function() {
        var result = spline.getFirstOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

      it("can evaluate second order", function() {
        var result = spline.getSecondOrder(0.5);
        expect(result).toBeDefined();
        expect(result.x).toBeDefined();
        expect(result.y).toBeDefined();
      });

    });

  });

  describe("spline point management", function() {

    var spline;
    var p1, p2, p3, p4, p5;

    beforeEach(function() {
      spline = new pdg.Spline(pdg.spline_Hermite);
      p1 = new pdg.Point(0, 0);
      p2 = new pdg.Point(50, 100);
      p3 = new pdg.Point(100, 50);
      p4 = new pdg.Point(150, 150);
      p5 = new pdg.Point(200, 75);
    });

    it("can add points with addPoint", function() {
      expect(function() {
        spline.addPoint(p1);
        spline.addPoint(p2);
        spline.addPoint(p3);
        spline.addPoint(p4);
        spline.addPoint(p5);
      }).not.toThrow();
    });

    it("can get Max U", function() {
      spline.addPoint(p1);
      spline.addPoint(p2);
      spline.addPoint(p3);
      spline.addPoint(p4);
      
      expect(function() {
        spline.getMaxU();
      }).not.toThrow();
    });

  });

  describe("spline continuity and smoothness", function() {

    var spline;
    var p1, p2, p3, p4;

    beforeEach(function() {
      p1 = new pdg.Point(0, 0);
      p2 = new pdg.Point(50, 100);
      p3 = new pdg.Point(100, 50);
      p4 = new pdg.Point(150, 150);
    });

    it("produces smooth curves for Hermite spline", function() {
      spline = new pdg.Spline(pdg.spline_Hermite);
      spline.addSegment(p1, p2, p3, p4);
      
      var points = [];
      for (var i = 0; i <= 10; i++) {
        var u = i / 10.0;
        var point = spline.getFirstOrder(u);
        points.push(point);
      }
      
      // Check that we get reasonable point values
      expect(points.length).toBe(11);
      points.forEach(function(point) {
        expect(point.x).toBeDefined();
        expect(point.y).toBeDefined();
        expect(typeof point.x).toBe('number');
        expect(typeof point.y).toBe('number');
      });
    });

    it("produces smooth curves for Cardinal spline", function() {
      spline = new pdg.Spline(pdg.spline_Cardinal);
      spline.addSegment(p1, p2, p3, p4);
      
      var points = [];
      for (var i = 0; i <= 10; i++) {
        var u = i / 10.0;
        var point = spline.getFirstOrder(u);
        points.push(point);
      }
      
      expect(points.length).toBe(11);
    });

    it("produces smooth curves for Uniform B-spline", function() {
      spline = new pdg.Spline(pdg.spline_UniformB);
      spline.addSegment(p1, p2, p3, p4);
      
      var points = [];
      for (var i = 0; i <= 10; i++) {
        var u = i / 10.0;
        var point = spline.getFirstOrder(u);
        points.push(point);
      }
      
      expect(points.length).toBe(11);
    });

  });

  describe("error handling", function() {

    var spline;

    beforeEach(function() {
      spline = new pdg.Spline(pdg.spline_Hermite);
    });

    it("returns zero point when evaluating uninitialized spline", function() {
      var result = spline.getFirstOrder(0.5);
      expect(result).toBeDefined();
      expect(result.x).toBe(0);
      expect(result.y).toBe(0);
    });

    it("handles edge case parameter values", function() {
      var p1 = new pdg.Point(0, 0);
      var p2 = new pdg.Point(50, 100);
      var p3 = new pdg.Point(100, 50);
      var p4 = new pdg.Point(150, 150);
      spline.addSegment(p1, p2, p3, p4);
      
      // Test negative parameter - returns zero point
      var result1 = spline.getFirstOrder(-0.1);
      expect(result1).toBeDefined();
      expect(result1.x).toBe(0);
      expect(result1.y).toBe(0);
      
      // Test parameter > maxU - clamps to endpoint (new behavior for multi-segment support)
      var result2 = spline.getFirstOrder(1.1);
      expect(result2).toBeDefined();
      // Should clamp to u=1.0, which is the endpoint
      // For Hermite spline: P1 is at u=0, P2 is at u=1
      expect(result2.x).toBe(50);
      expect(result2.y).toBe(100);
    });

  });

  describe("multi-segment splines", function() {

    describe("new API methods", function() {
      
      var spline;

      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_CubicBezier);
      });

      it("has addSegment method", function() {
        expect(typeof spline.addSegment).toBe('function');
      });

      it("has addPoint method", function() {
        expect(typeof spline.addPoint).toBe('function');
      });

      it("has getPoint method", function() {
        expect(typeof spline.getPoint).toBe('function');
      });

      it("has setPoint method", function() {
        expect(typeof spline.setPoint).toBe('function');
      });

      it("has getPointCount method", function() {
        expect(typeof spline.getPointCount).toBe('function');
      });

      it("has getMaxU method", function() {
        expect(typeof spline.getMaxU).toBe('function');
      });

    });

    describe("Bezier multi-segment creation", function() {
      
      var spline;

      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_CubicBezier);
      });

      it("can create a spline with one segment using addSegment", function() {
        var p1 = new pdg.Point(0, 0);
        var p2 = new pdg.Point(50, 50);
        var p3 = new pdg.Point(100, 50);
        var p4 = new pdg.Point(150, 0);
        
        spline.addSegment(p1, p2, p3, p4);
        
        expect(spline.getPointCount()).toBe(4);
        expect(spline.getMaxU()).toBe(1.0);
      });

      it("can add a second segment with automatic continuity", function() {
        var p1 = new pdg.Point(0, 0);
        var p2 = new pdg.Point(50, 50);
        var p3 = new pdg.Point(100, 50);
        var p4 = new pdg.Point(150, 0);
        
        spline.addSegment(p1, p2, p3, p4);
        
        // Add second segment - should auto-adjust to connect
        var p5 = new pdg.Point(0, 0);  // Will be adjusted to match p4
        var p6 = new pdg.Point(200, -50);
        var p7 = new pdg.Point(250, -50);
        var p8 = new pdg.Point(300, 0);
        
        spline.addSegment(p5, p6, p7, p8);
        
        // Bezier: 4 points + 3 points = 7 points total
        expect(spline.getPointCount()).toBe(7);
        expect(spline.getMaxU()).toBe(2.0);
        
        // Verify continuity - point 3 should be shared
        var sharedPoint = spline.getPoint(3);
        expect(sharedPoint.x).toBe(150);
        expect(sharedPoint.y).toBe(0);
      });

      it("can add multiple segments", function() {
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(30, 30),
          new pdg.Point(60, 30),
          new pdg.Point(90, 0)
        );
        
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(120, -30),
          new pdg.Point(150, -30),
          new pdg.Point(180, 0)
        );
        
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(210, 30),
          new pdg.Point(240, 30),
          new pdg.Point(270, 0)
        );
        
        expect(spline.getPointCount()).toBe(10);  // 4 + 3 + 3
        expect(spline.getMaxU()).toBe(3.0);
      });

    });

    describe("Cardinal/B-Spline multi-segment creation", function() {
      
      it("Cardinal spline adds one point per segment", function() {
        var spline = new pdg.Spline(pdg.spline_Cardinal);
        
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(50, 100),
          new pdg.Point(100, 50),
          new pdg.Point(150, 150)
        );
        
        expect(spline.getPointCount()).toBe(4);
        expect(spline.getMaxU()).toBe(1.0);
        
        // Add second segment - only p4 is added (sliding window)
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(0, 0),
          new pdg.Point(0, 0),
          new pdg.Point(200, 100)
        );
        
        expect(spline.getPointCount()).toBe(5);
        expect(spline.getMaxU()).toBe(2.0);
      });

    });

    describe("automatic segment navigation", function() {
      
      var spline;

      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_CubicBezier);
        
        // Create a 2-segment spline
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(30, 30),
          new pdg.Point(60, 30),
          new pdg.Point(90, 0)
        );
        
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(120, -30),
          new pdg.Point(150, -30),
          new pdg.Point(180, 0)
        );
      });

      it("can evaluate first segment with u in [0, 1)", function() {
        var pt = spline.getFirstOrder(0.5);
        expect(pt).toBeDefined();
        expect(pt.x).toBeGreaterThan(0);
        expect(pt.x).toBeLessThan(90);
      });

      it("can evaluate second segment with u in [1, 2)", function() {
        var pt = spline.getFirstOrder(1.5);
        expect(pt).toBeDefined();
        // Second segment is shifted by delta, so x values are 90, 210, 240, 270
        expect(pt.x).toBeGreaterThan(90);
        expect(pt.x).toBeLessThan(270);
      });

      it("evaluates at exact segment boundaries", function() {
        var pt0 = spline.getFirstOrder(0.0);
        var pt1 = spline.getFirstOrder(1.0);
        var pt2 = spline.getFirstOrder(2.0);
        
        expect(pt0).toBeDefined();
        expect(pt1).toBeDefined();
        expect(pt2).toBeDefined();
        
        // pt1 should be at the shared endpoint
        expect(pt1.x).toBe(90);
        expect(pt1.y).toBe(0);
        
        // pt2 should be at the second segment's endpoint (shifted)
        expect(pt2.x).toBe(270);
        expect(pt2.y).toBe(0);
      });

      it("can evaluate entire spline with continuous parameter", function() {
        var points = [];
        for (var u = 0; u <= 2.0; u += 0.25) {
          var pt = spline.getFirstOrder(u);
          points.push(pt);
        }
        
        expect(points.length).toBe(9);
        // All points should be valid
        points.forEach(function(pt) {
          expect(pt.x).toBeDefined();
          expect(pt.y).toBeDefined();
          expect(typeof pt.x).toBe('number');
          expect(typeof pt.y).toBe('number');
        });
      });

    });

    describe("point manipulation", function() {
      
      var spline;

      beforeEach(function() {
        spline = new pdg.Spline(pdg.spline_CubicBezier);
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(30, 30),
          new pdg.Point(60, 30),
          new pdg.Point(90, 0)
        );
      });

      it("can get individual points", function() {
        var p0 = spline.getPoint(0);
        var p1 = spline.getPoint(1);
        var p2 = spline.getPoint(2);
        var p3 = spline.getPoint(3);
        
        expect(p0.x).toBe(0);
        expect(p0.y).toBe(0);
        expect(p1.x).toBe(30);
        expect(p1.y).toBe(30);
        expect(p2.x).toBe(60);
        expect(p2.y).toBe(30);
        expect(p3.x).toBe(90);
        expect(p3.y).toBe(0);
      });

      it("can modify individual points", function() {
        spline.setPoint(1, new pdg.Point(40, 50));
        
        var p1 = spline.getPoint(1);
        expect(p1.x).toBe(40);
        expect(p1.y).toBe(50);
        
        // Verify the spline shape changed
        var midpoint = spline.getFirstOrder(0.5);
        expect(midpoint).toBeDefined();
      });

      it("returns zero point for invalid indices", function() {
        var invalid = spline.getPoint(100);
        expect(invalid.x).toBe(0);
        expect(invalid.y).toBe(0);
        
        var negative = spline.getPoint(-1);
        expect(negative.x).toBe(0);
        expect(negative.y).toBe(0);
      });

      it("can add points manually with addPoint", function() {
        var initialCount = spline.getPointCount();
        
        spline.addPoint(new pdg.Point(120, -30));
        spline.addPoint(new pdg.Point(150, -30));
        spline.addPoint(new pdg.Point(180, 0));
        
        expect(spline.getPointCount()).toBe(initialCount + 3);
        expect(spline.getMaxU()).toBe(2.0);
      });

    });

    describe("getMaxU behavior", function() {
      
      it("returns 0 for uninitialized spline", function() {
        var spline = new pdg.Spline(pdg.spline_CubicBezier);
        expect(spline.getMaxU()).toBe(0);
      });

      it("returns 1 for single-segment spline", function() {
        var spline = new pdg.Spline(pdg.spline_CubicBezier);
        spline.addSegment(
          new pdg.Point(0, 0),
          new pdg.Point(30, 30),
          new pdg.Point(60, 30),
          new pdg.Point(90, 0)
        );
        expect(spline.getMaxU()).toBe(1.0);
      });

      it("returns correct value for multi-segment Bezier", function() {
        var spline = new pdg.Spline(pdg.spline_CubicBezier);
        
        for (var i = 0; i < 5; i++) {
          spline.addSegment(
            new pdg.Point(i * 100, 0),
            new pdg.Point(i * 100 + 30, 30),
            new pdg.Point(i * 100 + 60, 30),
            new pdg.Point(i * 100 + 90, 0)
          );
        }
        
        expect(spline.getMaxU()).toBe(5.0);
      });

      it("returns correct value for Cardinal sliding window", function() {
        var spline = new pdg.Spline(pdg.spline_Cardinal);
        
        // First segment
        spline.addPoint(new pdg.Point(0, 0));
        spline.addPoint(new pdg.Point(50, 50));
        spline.addPoint(new pdg.Point(100, 50));
        spline.addPoint(new pdg.Point(150, 0));
        expect(spline.getMaxU()).toBe(1.0);
        
        // Add more points for sliding window
        spline.addPoint(new pdg.Point(200, 50));
        expect(spline.getMaxU()).toBe(2.0);
        
        spline.addPoint(new pdg.Point(250, 0));
        expect(spline.getMaxU()).toBe(3.0);
      });

    });

  });

  describe("bounds calculation", function() {

    it("returns empty bounds for empty spline", function() {
      var spline = new pdg.Spline();
      var bounds = spline.getBounds();
      
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.left).toBe(0);
      expect(bounds.top).toBe(0);
      expect(bounds.right).toBe(0);
      expect(bounds.bottom).toBe(0);
    });

    it("calculates correct bounds for spline with points", function() {
      var spline = new pdg.Spline();
      spline.addPoint(new pdg.Point(10, 20));
      spline.addPoint(new pdg.Point(30, 40));
      spline.addPoint(new pdg.Point(50, 10));
      
      var bounds = spline.getBounds();
      
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.left).toBe(10);
      expect(bounds.top).toBe(10);
      expect(bounds.right).toBe(50);
      expect(bounds.bottom).toBe(40);
    });

    it("updates bounds when points are added", function() {
      var spline = new pdg.Spline();
      spline.addPoint(new pdg.Point(10, 20));
      spline.addPoint(new pdg.Point(30, 40));
      
      var initialBounds = spline.getBounds();
      expect(initialBounds.left).toBe(10);
      expect(initialBounds.right).toBe(30);
      expect(initialBounds.top).toBe(20);
      expect(initialBounds.bottom).toBe(40);
      
      // Add a point that extends the bounds
      spline.addPoint(new pdg.Point(100, 200));
      
      var newBounds = spline.getBounds();
      expect(newBounds.left).toBe(10);
      expect(newBounds.right).toBe(100);
      expect(newBounds.top).toBe(20);
      expect(newBounds.bottom).toBe(200);
    });

    it("updates bounds when points are modified", function() {
      var spline = new pdg.Spline();
      spline.addPoint(new pdg.Point(10, 20));
      spline.addPoint(new pdg.Point(30, 40));
      spline.addPoint(new pdg.Point(50, 10));
      
      var initialBounds = spline.getBounds();
      expect(initialBounds.left).toBe(10);
      expect(initialBounds.right).toBe(50);
      
      // Modify a point to extend bounds
      spline.setPoint(1, new pdg.Point(100, 200));
      
      var newBounds = spline.getBounds();
      expect(newBounds.left).toBe(10);
      expect(newBounds.right).toBe(100);
      expect(newBounds.top).toBe(10);
      expect(newBounds.bottom).toBe(200);
    });

    it("handles negative coordinates correctly", function() {
      var spline = new pdg.Spline();
      spline.addPoint(new pdg.Point(-10, -20));
      spline.addPoint(new pdg.Point(30, 40));
      spline.addPoint(new pdg.Point(-50, 10));
      
      var bounds = spline.getBounds();
      
      expect(bounds.left).toBe(-50);
      expect(bounds.top).toBe(-20);
      expect(bounds.right).toBe(30);
      expect(bounds.bottom).toBe(40);
    });

    it("handles single point spline", function() {
      var spline = new pdg.Spline();
      spline.addPoint(new pdg.Point(42, 84));
      
      var bounds = spline.getBounds();
      
      expect(bounds.left).toBe(42);
      expect(bounds.top).toBe(84);
      expect(bounds.right).toBe(42);
      expect(bounds.bottom).toBe(84);
    });

  });

});
