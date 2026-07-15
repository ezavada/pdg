// -----------------------------------------------
// rotatedrect.spec.js
//
// test suite for RotatedRect
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

describe("RotatedRect", function() {

  describe("construction", function() {

    it("can be created with no params", function() {
      console.log('* Testing RotatedRect...');
      var rotRect = new RotatedRect();
      expect(rotRect.left).toBeDefined();
      expect(rotRect.left).toEqual(0);
      expect(rotRect.top).toBeDefined();
      expect(rotRect.top).toEqual(0);
      expect(rotRect.right).toBeDefined();
      expect(rotRect.right).toEqual(0);
      expect(rotRect.bottom).toBeDefined();
      expect(rotRect.bottom).toEqual(0);
      expect(rotRect.centerOffset).toBeDefined();
      expect(rotRect.centerOffset.x).toEqual(0);
      expect(rotRect.centerOffset.y).toEqual(0);
    });

    it("can be created with rect and rotation", function() {
      var rect = new Rect(10, 20, 110, 70);
      var rotRect = new RotatedRect(rect, Math.PI / 4); // 45 degrees
      
      expect(rotRect.left).toEqual(10);
      expect(rotRect.top).toEqual(20);
      expect(rotRect.right).toEqual(110);
      expect(rotRect.bottom).toEqual(70);
      expect(rotRect.centerOffset.x).toEqual(0);
      expect(rotRect.centerOffset.y).toEqual(0);
    });

    it("can be created with rect, rotation, and center offset", function() {
      var rect = new Rect(10, 20, 110, 70);
      var centerOffset = new Point(5, 10);
      var rotRect = new RotatedRect(rect, Math.PI / 2, centerOffset); // 90 degrees
      
      expect(rotRect.left).toEqual(10);
      expect(rotRect.top).toEqual(20);
      expect(rotRect.right).toEqual(110);
      expect(rotRect.bottom).toEqual(70);
      expect(rotRect.centerOffset.x).toEqual(5);
      expect(rotRect.centerOffset.y).toEqual(10);
    });

  });

  describe("inherited Rect functionality", function() {

    it("inherits basic Rect properties", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      
      expect(rotRect.width()).toEqual(100);
      expect(rotRect.height()).toEqual(50);
      expect(rotRect.empty()).toBeFalsy();
      expect(rotRect.centerPoint().x).toEqual(60);
      expect(rotRect.centerPoint().y).toEqual(45);
    });

    it("inherits Rect movement operations", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      
      rotRect.moveTo(50, 100);
      expect(rotRect.left).toEqual(50);
      expect(rotRect.top).toEqual(100);
      expect(rotRect.right).toEqual(150);
      expect(rotRect.bottom).toEqual(150);
    });

    it("inherits Rect containment tests", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      var point = new Point(50, 40);
      
      expect(rotRect.contains(point)).toBeTruthy();
    });

  });

  describe("rotation operations", function() {

    it("can set rotation", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      
      rotRect.setRotation(Math.PI / 4); // 45 degrees
      // Note: The actual rotation value is stored internally and not exposed
      // We can only test that the method doesn't throw
      expect(rotRect).toBeDefined();
    });

    it("can set rotation with center offset", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      var centerOffset = new Point(5, 10);
      
      rotRect.setRotation(Math.PI / 2, centerOffset); // 90 degrees
      expect(rotRect.centerOffset.x).toEqual(5);
      expect(rotRect.centerOffset.y).toEqual(10);
    });

    it("can rotate by increment", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      
      rotRect.rotate(Math.PI / 4); // Add 45 degrees
      // Note: The actual rotation value is stored internally and not exposed
      // We can only test that the method doesn't throw
      expect(rotRect).toBeDefined();
    });

    it("can set center offset", function() {
      var rotRect = new RotatedRect(new Rect(10, 20, 110, 70));
      var centerOffset = new Point(15, 25);
      
      rotRect.setCenterOffset(centerOffset);
      expect(rotRect.centerOffset.x).toEqual(15);
      expect(rotRect.centerOffset.y).toEqual(25);
    });

  });

  describe("quad conversion", function() {

    it("can convert to quad with no rotation", function() {
      var rect = new Rect(10, 20, 110, 70);
      var rotRect = new RotatedRect(rect, 0); // No rotation
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
      expect(quad.points[0].x).toEqual(10); // leftTop
      expect(quad.points[0].y).toEqual(20);
      expect(quad.points[1].x).toEqual(110); // rightTop
      expect(quad.points[1].y).toEqual(20);
      expect(quad.points[2].x).toEqual(110); // rightBottom
      expect(quad.points[2].y).toEqual(70);
      expect(quad.points[3].x).toEqual(10); // leftBottom
      expect(quad.points[3].y).toEqual(70);
    });

    it("can convert to quad with rotation", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, Math.PI / 4); // 45 degrees
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
      expect(quad.points[0].x).toBeDefined();
      expect(quad.points[0].y).toBeDefined();
      expect(quad.points[1].x).toBeDefined();
      expect(quad.points[1].y).toBeDefined();
      expect(quad.points[2].x).toBeDefined();
      expect(quad.points[2].y).toBeDefined();
      expect(quad.points[3].x).toBeDefined();
      expect(quad.points[3].y).toBeDefined();
    });

    it("can convert to quad with center offset", function() {
      var rect = new Rect(0, 0, 100, 50);
      var centerOffset = new Point(25, 25);
      var rotRect = new RotatedRect(rect, Math.PI / 4, centerOffset); // 45 degrees
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
      expect(quad.points[0].x).toBeDefined();
      expect(quad.points[0].y).toBeDefined();
      expect(quad.points[1].x).toBeDefined();
      expect(quad.points[1].y).toBeDefined();
      expect(quad.points[2].x).toBeDefined();
      expect(quad.points[2].y).toBeDefined();
      expect(quad.points[3].x).toBeDefined();
      expect(quad.points[3].y).toBeDefined();
    });

  });

  describe("complex rotation scenarios", function() {

    it("handles multiple rotations", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, 0);
      
      rotRect.rotate(Math.PI / 4); // Add 45 degrees
      rotRect.rotate(Math.PI / 4); // Add another 45 degrees (total 90)
      rotRect.rotate(-Math.PI / 2); // Subtract 90 degrees (back to 0)
      
      var quad = rotRect.getQuad();
      expect(quad.points[0].x).toBeCloseTo(0, 1);
      expect(quad.points[0].y).toBeCloseTo(0, 1);
      expect(quad.points[1].x).toBeCloseTo(100, 1);
      expect(quad.points[1].y).toBeCloseTo(0, 1);
    });

    it("handles rotation with different center offsets", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, 0);
      
      rotRect.setCenterOffset(new Point(50, 25)); // Center of rectangle
      rotRect.setRotation(Math.PI / 2); // 90 degrees around center
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
    });

  });

  describe("edge cases", function() {

    it("handles zero size rectangle", function() {
      var rect = new Rect(10, 20, 10, 20); // Zero width and height
      var rotRect = new RotatedRect(rect, Math.PI / 4);
      
      expect(rotRect.empty()).toBeTruthy();
      expect(rotRect.width()).toEqual(0);
      expect(rotRect.height()).toEqual(0);
    });

    it("handles very large rotations", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, 0);
      
      rotRect.rotate(Math.PI * 10); // 10 full rotations
      rotRect.rotate(-Math.PI * 10); // 10 full rotations back
      
      var quad = rotRect.getQuad();
      expect(quad.points[0].x).toBeCloseTo(0, 1);
      expect(quad.points[0].y).toBeCloseTo(0, 1);
    });

    it("handles negative rotations", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, 0);
      
      rotRect.rotate(-Math.PI / 2); // -90 degrees
      rotRect.rotate(Math.PI / 2); // +90 degrees
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
      expect(quad.points[0].x).toBeCloseTo(0, 1);
      expect(quad.points[0].y).toBeCloseTo(0, 1);
    });

  });

  describe("integration with Rect operations", function() {

    it("can be moved and rotated", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, Math.PI / 4);
      
      rotRect.moveTo(50, 100);
      expect(rotRect.left).toEqual(50);
      expect(rotRect.top).toEqual(100);
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
    });

    it("can be resized and rotated", function() {
      var rect = new Rect(0, 0, 100, 50);
      var rotRect = new RotatedRect(rect, Math.PI / 6);
      
      rotRect.setSize(200);
      expect(rotRect.width()).toEqual(200);
      expect(rotRect.height()).toEqual(200);
      
      var quad = rotRect.getQuad();
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
    });

  });

});
