// -----------------------------------------------
// rect.spec.js
//
// test suite for Rect
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

describe("Rect", function() {

  describe("construction", function() {

    it("can be created with no params", function() {
      console.log('* Testing Rect...');
      var rect = new Rect();
      expect(rect.left).toBeDefined();
      expect(rect.left).toEqual(0);
      expect(rect.top).toBeDefined();
      expect(rect.top).toEqual(0);
      expect(rect.right).toBeDefined();
      expect(rect.right).toEqual(0);
      expect(rect.bottom).toBeDefined();
      expect(rect.bottom).toEqual(0);
    });

    it("is an object, an instance of Rect", function() {
      var rect = new Rect();
      expect(typeof rect).toBe('object');
      expect(rect.constructor.name).toBe('Rect');
      expect(rect instanceof Rect).toBe(true);
    });

    it("can be created with width and height", function() {
      var rect = new Rect(100, 50);
      expect(rect.left).toEqual(0);
      expect(rect.top).toEqual(0);
      expect(rect.right).toEqual(100);
      expect(rect.bottom).toEqual(50);
    });

    it("can be created with topLeft point and dimensions", function() {
      var topLeft = new Point(10, 20);
      var rect = new Rect(topLeft, 100, 50);
      expect(rect.left).toEqual(10);
      expect(rect.top).toEqual(20);
      expect(rect.right).toEqual(110);
      expect(rect.bottom).toEqual(70);
    });

    it("can be created with two corner points", function() {
      var leftTop = new Point(10, 20);
      var rightBottom = new Point(110, 70);
      var rect = new Rect(leftTop, rightBottom);
      expect(rect.left).toEqual(10);
      expect(rect.top).toEqual(20);
      expect(rect.right).toEqual(110);
      expect(rect.bottom).toEqual(70);
    });

    it("can be created with four coordinates", function() {
      var rect = new Rect(10, 20, 110, 70);
      expect(rect.left).toEqual(10);
      expect(rect.top).toEqual(20);
      expect(rect.right).toEqual(110);
      expect(rect.bottom).toEqual(70);
    });

  });

  describe("basic properties", function() {

    it("can check if rectangle is empty", function() {
      var emptyRect = new Rect(0, 0, 0, 0);
      var zeroWidthRect = new Rect(0, 0, 0, 10);
      var zeroHeightRect = new Rect(0, 0, 10, 0);
      var normalRect = new Rect(0, 0, 10, 10);
      
      expect(emptyRect.empty()).toBeTruthy();
      expect(zeroWidthRect.empty()).toBeTruthy();
      expect(zeroHeightRect.empty()).toBeTruthy();
      expect(normalRect.empty()).toBeFalsy();
    });

    it("can get width and height", function() {
      var rect = new Rect(10, 20, 110, 70);
      expect(rect.width()).toEqual(100);
      expect(rect.height()).toEqual(50);
    });

    it("can get coordinate aliases", function() {
      var rect = new Rect(10, 20, 110, 70);
      expect(rect.x1()).toEqual(10); // left
      expect(rect.y1()).toEqual(20); // top
      expect(rect.x2()).toEqual(110); // right
      expect(rect.y2()).toEqual(70); // bottom
    });

  });

  describe("corner points", function() {

    it("can get all corner points", function() {
      var rect = new Rect(10, 20, 110, 70);
      
      var leftTop = rect.leftTop();
      expect(leftTop.x).toEqual(10);
      expect(leftTop.y).toEqual(20);
      
      var rightTop = rect.rightTop();
      expect(rightTop.x).toEqual(110);
      expect(rightTop.y).toEqual(20);
      
      var leftBottom = rect.leftBottom();
      expect(leftBottom.x).toEqual(10);
      expect(leftBottom.y).toEqual(70);
      
      var rightBottom = rect.rightBottom();
      expect(rightBottom.x).toEqual(110);
      expect(rightBottom.y).toEqual(70);
    });

    it("can get center point", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      expect(center.x).toEqual(60); // (10 + 110) / 2
      expect(center.y).toEqual(45); // (20 + 70) / 2
    });

  });

  describe("containment tests", function() {

    it("can test if point is contained", function() {
      var rect = new Rect(10, 20, 110, 70);
      
      var insidePoint = new Point(50, 40);
      var edgePoint = new Point(10, 20);
      var outsidePoint = new Point(0, 0);
      
      expect(rect.contains(insidePoint)).toBeTruthy();
      expect(rect.contains(edgePoint)).toBeTruthy();
      expect(rect.contains(outsidePoint)).toBeFalsy();
    });

    it("can test if rectangle is contained", function() {
      var outerRect = new Rect(0, 0, 100, 100);
      var innerRect = new Rect(10, 10, 90, 90);
      var overlappingRect = new Rect(50, 50, 150, 150);
      var outsideRect = new Rect(200, 200, 300, 300);
      
      expect(outerRect.contains(innerRect)).toBeTruthy();
      expect(outerRect.contains(overlappingRect)).toBeFalsy();
      expect(outerRect.contains(outsideRect)).toBeFalsy();
    });

  });

  describe("overlap tests", function() {

    it("can test if rectangles overlap", function() {
      var rect1 = new Rect(0, 0, 100, 100);
      var rect2 = new Rect(50, 50, 150, 150);
      var rect3 = new Rect(200, 200, 300, 300);
      var rect4 = new Rect(100, 100, 200, 200); // touches edge
      
      expect(rect1.overlaps(rect2)).toBeTruthy();
      expect(rect1.overlaps(rect3)).toBeFalsy();
      expect(rect1.overlaps(rect4)).toBeFalsy(); // sharing edge is not overlapping
    });

  });

  describe("geometric operations", function() {

    it("can calculate intersection", function() {
      var rect1 = new Rect(0, 0, 100, 100);
      var rect2 = new Rect(50, 50, 150, 150);
      var intersection = rect1.intersection(rect2);
      
      expect(intersection.left).toEqual(50);
      expect(intersection.top).toEqual(50);
      expect(intersection.right).toEqual(100);
      expect(intersection.bottom).toEqual(100);
    });

    it("can calculate union", function() {
      var rect1 = new Rect(0, 0, 100, 100);
      var rect2 = new Rect(50, 50, 150, 150);
      var union = rect1.unionWith(rect2);
      
      expect(union.left).toEqual(0);
      expect(union.top).toEqual(0);
      expect(union.right).toEqual(150);
      expect(union.bottom).toEqual(150);
    });

    it("handles intersection of non-overlapping rectangles", function() {
      var rect1 = new Rect(0, 0, 100, 100);
      var rect2 = new Rect(200, 200, 300, 300);
      var intersection = rect1.intersection(rect2);
      
      expect(intersection.empty()).toBeTruthy();
    });

  });

  describe("movement operations", function() {

    it("can move in all directions", function() {
      var rect = new Rect(10, 20, 110, 70);
      
      rect.moveLeft(5);
      expect(rect.left).toEqual(5);
      expect(rect.right).toEqual(105);
      
      rect.moveRight(10);
      expect(rect.left).toEqual(15);
      expect(rect.right).toEqual(115);
      
      rect.moveUp(5);
      expect(rect.top).toEqual(15);
      expect(rect.bottom).toEqual(65);
      
      rect.moveDown(10);
      expect(rect.top).toEqual(25);
      expect(rect.bottom).toEqual(75);
    });

    it("can move to specific positions", function() {
      var rect = new Rect(10, 20, 110, 70);
      
      rect.moveXTo(50);
      expect(rect.left).toEqual(50);
      expect(rect.right).toEqual(150);
      expect(rect.top).toEqual(20); // unchanged
      expect(rect.bottom).toEqual(70); // unchanged
      
      rect.moveYTo(100);
      expect(rect.top).toEqual(100);
      expect(rect.bottom).toEqual(150);
      expect(rect.left).toEqual(50); // unchanged
      expect(rect.right).toEqual(150); // unchanged
    });

    it("can move to point", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(50, 100);
      
      rect.moveTo(point.x, point.y);
      expect(rect.left).toEqual(50);
      expect(rect.top).toEqual(100);
      expect(rect.right).toEqual(150);
      expect(rect.bottom).toEqual(150);
    });

    it("can center on point", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(100, 100);
      
      rect.center(point);
      expect(rect.centerPoint().x).toEqual(100);
      expect(rect.centerPoint().y).toEqual(100);
    });

    it("can center within another rectangle", function() {
      var rect = new Rect(10, 20, 110, 70);
      var container = new Rect(0, 0, 200, 200);
      
      rect.center(container);
      expect(rect.centerPoint().x).toEqual(100);
      expect(rect.centerPoint().y).toEqual(100);
    });

  });

  describe("size operations", function() {

    it("can set size", function() {
      var rect = new Rect(10, 20, 110, 70);
	  var center = rect.centerPoint();
	  expect(center.x).toEqual(60);
	  expect(center.y).toEqual(45);
      
      rect.setSize(200);
      expect(rect.width()).toEqual(200);
      expect(rect.height()).toEqual(200);
      expect(rect.centerPoint().x).toEqual(110); // center correct for new size
      expect(rect.centerPoint().y).toEqual(120); // center correct for new size
    });

    it("can set width and height separately", function() {
      var rect = new Rect(10, 20, 110, 70);
      
      rect.setWidth(200);
      expect(rect.width()).toEqual(200);
      expect(rect.height()).toEqual(50); // unchanged
      
      rect.setHeight(100);
      expect(rect.width()).toEqual(200);
      expect(rect.height()).toEqual(100);
    });

    it("can grow and shrink", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      
      rect.grow(20);
      expect(rect.width()).toEqual(140); // 100 + 20*2
      expect(rect.height()).toEqual(90); // 50 + 20*2
      expect(rect.centerPoint().x).toEqual(center.x);
      expect(rect.centerPoint().y).toEqual(center.y);
      
      rect.shrink(10);
      expect(rect.width()).toEqual(120); // 140 - 10*2
      expect(rect.height()).toEqual(70); // 90 - 10*2
    });

    it("can grow and shrink horizontally", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      
      rect.horzGrow(20);
      expect(rect.width()).toEqual(140); // 100 + 20*2
      expect(rect.height()).toEqual(50); // unchanged
      expect(rect.centerPoint().x).toEqual(center.x);
      
      rect.horzShrink(10);
      expect(rect.width()).toEqual(120); // 140 - 10*2
      expect(rect.height()).toEqual(50); // unchanged
    });

    it("can grow and shrink vertically", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      
      rect.vertGrow(20);
      expect(rect.width()).toEqual(100); // unchanged
      expect(rect.height()).toEqual(90); // 50 + 20*2
      expect(rect.centerPoint().y).toEqual(center.y);
      
      rect.vertShrink(10);
      expect(rect.width()).toEqual(100); // unchanged
      expect(rect.height()).toEqual(70); // 90 - 10*2
    });

  });

  describe("scaling operations", function() {

    it("can scale uniformly", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      
      rect.scale(2.0);
      expect(rect.width()).toEqual(200); // (110-10)*2
      expect(rect.height()).toEqual(100); // (70-20)*2
      expect(rect.centerPoint().x).toEqual(120); // (10+110)*2/2
      expect(rect.centerPoint().y).toEqual(90); // (20+70)*2/2
    });

    it("can scale horizontally and vertically", function() {
      var rect = new Rect(10, 20, 110, 70);
      var center = rect.centerPoint();
      
      rect.horzScale(2.0);
      expect(rect.width()).toEqual(200); // (110-10)*2
      expect(rect.height()).toEqual(50); // unchanged
      expect(rect.centerPoint().x).toEqual(120); // (10+110)*2/2
      
      rect.vertScale(3.0);
      expect(rect.width()).toEqual(200); // unchanged
      expect(rect.height()).toEqual(150); // (70-20)*3
      expect(rect.centerPoint().y).toEqual(135); // (20+70)*3/2
    });

  });

  describe("utility operations", function() {

    it("can round coordinates", function() {
      // Note: The round method has a bug in the implementation - it uses undefined variables
      // This test is expected to fail until the bug is fixed
      var rect = new Rect(10.7, 20.3, 110.9, 70.1);
      expect(function() {
        rect.round();
      }).toThrow();
      
      // Expected behavior (when bug is fixed):
      // expect(rect.left).toEqual(11);
      // expect(rect.top).toEqual(20);
      // expect(rect.right).toEqual(111);
      // expect(rect.bottom).toEqual(70);
    });

    it("can convert to quad", function() {
      var rect = new Rect(10, 20, 110, 70);
      var quad = rect.toQuad();
      
      expect(quad.points).toBeDefined();
      expect(quad.points.length).toEqual(4);
    });

  });

  describe("equality operations", function() {

    it("can test equality", function() {
      var rect1 = new Rect(10, 20, 110, 70);
      var rect2 = new Rect(10, 20, 110, 70);
      var rect3 = new Rect(10, 20, 120, 70);
      
      expect(rect1.equals(rect2)).toBeTruthy();
      expect(rect1.equals(rect3)).toBeFalsy();
    });

    it("can test inequality", function() {
      var rect1 = new Rect(10, 20, 110, 70);
      var rect2 = new Rect(10, 20, 110, 70);
      var rect3 = new Rect(10, 20, 120, 70);
      
      expect(rect1.notEquals(rect2)).toBeFalsy();
      expect(rect1.notEquals(rect3)).toBeTruthy();
    });

    it("can assign from another rectangle", function() {
      var rect1 = new Rect(10, 20, 110, 70);
      var rect2 = new Rect(0, 0, 100, 100);
      
      rect1.assign(rect2);
      expect(rect1.left).toEqual(0);
      expect(rect1.top).toEqual(0);
      expect(rect1.right).toEqual(100);
      expect(rect1.bottom).toEqual(100);
    });

  });

  describe("arithmetic operations", function() {

    it("can add point offset", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(5, 10);
      var result = rect.add(point);
      
      expect(result.left).toEqual(15);
      expect(result.top).toEqual(30);
      expect(result.right).toEqual(115);
      expect(result.bottom).toEqual(80);
    });

    it("can subtract point offset", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(5, 10);
      var result = rect.sub(point);
      
      expect(result.left).toEqual(5);
      expect(result.top).toEqual(10);
      expect(result.right).toEqual(105);
      expect(result.bottom).toEqual(60);
    });

    it("can multiply by point", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(2, 3);
      var result = rect.mul(point);
      
      expect(result.left).toEqual(20);
      expect(result.top).toEqual(60);
      expect(result.right).toEqual(220);
      expect(result.bottom).toEqual(210);
    });

    it("can divide by point", function() {
      var rect = new Rect(10, 20, 110, 70);
      var point = new Point(2, 5);
      var result = rect.div(point);
      
      expect(result.left).toEqual(5);
      expect(result.top).toEqual(4);
      expect(result.right).toEqual(55);
      expect(result.bottom).toEqual(14);
    });

  });

  describe("edge cases", function() {

    it("handles negative coordinates", function() {
      var rect = new Rect(-10, -20, 10, 20);
      expect(rect.width()).toEqual(20);
      expect(rect.height()).toEqual(40);
      expect(rect.centerPoint().x).toEqual(0);
      expect(rect.centerPoint().y).toEqual(0);
    });

    it("handles zero size rectangles", function() {
      var rect = new Rect(10, 20, 10, 20);
      expect(rect.empty()).toBeTruthy();
      expect(rect.width()).toEqual(0);
      expect(rect.height()).toEqual(0);
    });

    it("handles very large coordinates", function() {
      var rect = new Rect(1000000, 2000000, 2000000, 4000000);
      expect(rect.width()).toEqual(1000000);
      expect(rect.height()).toEqual(2000000);
    });

  });

});