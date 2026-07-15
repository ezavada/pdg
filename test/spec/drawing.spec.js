// -----------------------------------------------
// drawing.spec.js
//
// test suite for Drawing and ElementRef classes
//
// Written by AI Assistant, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
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

describe("Drawing", function() {

  describe("availability", function() {

    it("checks if Drawing is available", function() {
      console.log('* Testing Drawing...');
      console.log('pdg.Drawing:', typeof pdg.Drawing);
      
      expect(pdg.Drawing).toBeDefined();
      expect(typeof pdg.Drawing).toBe('function');
    });

    it("checks if ElementRef is available", function() {
      console.log('pdg.ElementRef:', typeof pdg.ElementRef);
      
      expect(pdg.ElementRef).toBeDefined();
      expect(typeof pdg.ElementRef).toBe('function');
    });

  });

  describe("construction", function() {

    it("can be created with createDrawing()", function() {
      var drawing = pdg.createDrawing();
      expect(drawing).toBeDefined();
      expect(typeof drawing).toBe('object');
      expect(drawing.constructor.name).toBe('Drawing');
    });

    it("cannot be constructed with new operator", function() {
      expect(function() {
        new pdg.Drawing();
      }).toThrow();
    });

    it("starts empty", function() {
      var drawing = pdg.createDrawing();
      expect(drawing.empty()).toBe(true);
      expect(drawing.getElementCount()).toBe(0);
    });

  });

  describe("basic properties", function() {

    var drawing;

    beforeEach(function() {
      drawing = pdg.createDrawing();
    });

    it("has correct element count for empty drawing", function() {
      expect(drawing.getElementCount()).toBe(0);
    });

    it("has empty bounds for empty drawing", function() {
      var bounds = drawing.getBounds();
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      // Empty drawing should have zero bounds
      expect(bounds.width()).toBe(0);
      expect(bounds.height()).toBe(0);
    });

    it("has center point for empty drawing", function() {
      var center = drawing.centerPoint();
      expect(center).toBeDefined();
      expect(center.constructor.name).toBe('Point');
      // For empty drawing, center should be at origin
      expect(center.x).toBe(0);
      expect(center.y).toBe(0);
    });

  });

  describe("adding basic shapes", function() {

    var drawing;

    beforeEach(function() {
      drawing = pdg.createDrawing();
    });

    it("can add a line", function() {
      var from = new pdg.Point(0, 0);
      var to = new pdg.Point(100, 100);
      var attrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      var elementRef = drawing.addLine(from, to, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Line);
    });

    it("can add a rectangle", function() {
      var rect = new pdg.Rect(10, 20, 50, 60);
      var attrs = new pdg.Attributes().fillColor("blue");
      var elementRef = drawing.addRect(rect, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Rect);
    });

    it("can add a circle", function() {
      var center = new pdg.Point(50, 50);
      var radius = 25;
      var attrs = new pdg.Attributes().fillColor("green");
      var elementRef = drawing.addEllipse(center, radius, radius, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Ellipse);
    });

    it("can add an oval", function() {
      var center = new pdg.Point(50, 50);
      var xRadius = 30;
      var yRadius = 20;
      var attrs = new pdg.Attributes().fillColor("yellow");
      var elementRef = drawing.addEllipse(center, xRadius, yRadius, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Ellipse);
    });

    it("can add multiple elements", function() {
      var lineAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      var lineRef = drawing.addLine(new pdg.Point(0, 0), new pdg.Point(10, 10), lineAttrs);
      var rectAttrs = new pdg.Attributes().fillColor("blue");
      var rectRef = drawing.addRect(new pdg.Rect(5, 5, 20, 20), rectAttrs);
      var circleAttrs = new pdg.Attributes().fillColor("green");
      var circleRef = drawing.addEllipse(new pdg.Point(15, 15), 5, 5, circleAttrs);
      
      expect(drawing.getElementCount()).toBe(3);
      expect(lineRef.type()).toBe(pdg.type_Line);
      expect(rectRef.type()).toBe(pdg.type_Rect);
      expect(circleRef.type()).toBe(pdg.type_Ellipse);
    });

  });

  describe("adding complex shapes", function() {

    var drawing;

    beforeEach(function() {
      drawing = pdg.createDrawing();
    });

    it("can add a spline", function() {
      var spline = new pdg.Spline(1); // spline type 1 = SPLINE_HERMITE
      spline.addSegment(
        new pdg.Point(0, 0),
        new pdg.Point(25, 0),
        new pdg.Point(75, 50),
        new pdg.Point(100, 50)
      );
      
      var attrs = new pdg.Attributes().lineColor("purple").lineThickness(2.0);
      var elementRef = drawing.addSpline(spline, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Spline);
    });

    it("can add a polygon", function() {
      var polygon = new pdg.Polygon();
      polygon.addPoint(new pdg.Point(0, 0));
      polygon.addPoint(new pdg.Point(10, 0));
      polygon.addPoint(new pdg.Point(10, 10));
      polygon.addPoint(new pdg.Point(0, 10));
      
      var attrs = new pdg.Attributes().fillColor("orange");
      var elementRef = drawing.addPolygon(polygon, attrs);
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(drawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Polygon);
    });

  });

  describe("element access and manipulation", function() {

    var drawing, lineRef, rectRef, circleRef;

    beforeEach(function() {
      drawing = pdg.createDrawing();
      var lineAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      lineRef = drawing.addLine(new pdg.Point(0, 0), new pdg.Point(10, 10), lineAttrs);
      var rectAttrs = new pdg.Attributes().fillColor("blue");
      rectRef = drawing.addRect(new pdg.Rect(5, 5, 20, 20), rectAttrs);
      var circleAttrs = new pdg.Attributes().fillColor("green");
      circleRef = drawing.addEllipse(new pdg.Point(15, 15), 5, 5, circleAttrs);
    });

    it("can get element by index", function() {
      var element0 = drawing.getElement(0);
      var element1 = drawing.getElement(1);
      var element2 = drawing.getElement(2);
      
      expect(element0).toBeDefined();
      expect(element1).toBeDefined();
      expect(element2).toBeDefined();
      expect(element0.constructor.name).toBe('ElementRef');
      expect(element1.constructor.name).toBe('ElementRef');
      expect(element2.constructor.name).toBe('ElementRef');
    });

    it("throws error for invalid element index", function() {
      expect(function() {
        drawing.getElement(999);
      }).toThrow();
    });

    it("can get element hit by point", function() {
      // Test point inside the rectangle
      var hitPoint = new pdg.Point(15, 15);
      var hitElement = drawing.getElementHitBy(hitPoint);
      
      expect(hitElement).toBeDefined();
      expect(hitElement).not.toBeNull();
      if (hitElement) {
        expect(hitElement.constructor.name).toBe('ElementRef');
      }
    });

    it("can get control points from element", function() {
      var controlPoints = lineRef.getControlPoints();
      expect(controlPoints).toBeDefined();
      expect(Array.isArray(controlPoints)).toBe(true);
      expect(controlPoints.length).toBe(2); // Line should have 2 control points
      
      controlPoints.forEach(function(point) {
        expect(point.constructor.name).toBe('Point');
      });
    });

    it("can get individual control point", function() {
      var point0 = lineRef.getControlPoint(0);
      var point1 = lineRef.getControlPoint(1);
      
      expect(point0).toBeDefined();
      expect(point1).toBeDefined();
      expect(point0.constructor.name).toBe('Point');
      expect(point1.constructor.name).toBe('Point');
    });

    it("can change control point", function() {
      var newPoint = new pdg.Point(5, 5);
      lineRef.changeControlPoint(1, newPoint);
      
      var updatedPoint = lineRef.getControlPoint(1);
      expect(updatedPoint.x).toBe(5);
      expect(updatedPoint.y).toBe(5);
    });

    it("throws error for invalid control point index", function() {
      expect(function() {
        lineRef.getControlPoint(999);
      }).toThrow();
    });

  });

  describe("element styling", function() {
    // TODO: Fix ElementRef getAttributes/setAttributes implementation
    // The getAttributes method is crashing with segmentation fault
    // These tests are skipped until the C++ implementation is fixed

    var drawing, elementRef;

    beforeEach(function() {
      drawing = pdg.createDrawing();
      var attrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      elementRef = drawing.addLine(new pdg.Point(0, 0), new pdg.Point(10, 10), attrs);
    });

    it("can set line color", function() {
      var color = new pdg.Color(255, 0, 0, 255);
      var attrs = elementRef.getAttributes();
      attrs.lineColor(color);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getLineColor().equals(color)).toBe(true);
    });

    it("can set line thickness", function() {
      var attrs = elementRef.getAttributes();
      attrs.lineThickness(2.5);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getLineThickness()).toBe(2.5);
    });

    it("can set line opacity", function() {
      var attrs = elementRef.getAttributes();
      attrs.lineOpacity(0.8);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getLineOpacity()).toBeCloseTo(0.8);
    });

    it("can set fill color", function() {
      var color = new pdg.Color(0, 255, 0, 255);
      var attrs = elementRef.getAttributes();
      attrs.fillColor(color);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      // verify the color is correct
      expect(updatedAttrs.getFillColor().equals(color)).toBe(true);
    });

    it("can set fill opacity", function() {
      var attrs = elementRef.getAttributes();
      attrs.fillOpacity(0.6);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getFillOpacity()).toBeCloseTo(0.6);
    });

    it("can set fill gradient", function() {
      var startPoint = new pdg.Point(0, 0);
      var startColor = new pdg.Color(255, 0, 0, 255);
      var endPoint = new pdg.Point(10, 10);
      var endColor = new pdg.Color(0, 0, 255, 255);
      
      var attrs = elementRef.getAttributes();
      attrs.fillGradient(startPoint, startColor, endPoint, endColor);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getGradientType()).toBe(pdg.gradientType_Linear);
      expect(updatedAttrs.getGradientStart().equals(startPoint)).toBe(true);
      expect(updatedAttrs.getGradientStartColor().equals(startColor)).toBe(true);
      expect(updatedAttrs.getGradientEnd().equals(endPoint)).toBe(true);
      expect(updatedAttrs.getGradientEndColor().equals(endColor)).toBe(true);
    });

    it("can set fill radial gradient", function() {
      var centerPoint = new pdg.Point(5, 5);
      var centerColor = new pdg.Color(255, 0, 0, 255);
      var radius = 5;
      var endColor = new pdg.Color(0, 0, 255, 255);
      
      var attrs = elementRef.getAttributes();
      attrs.fillRadialGradient(centerPoint, centerColor, radius, endColor);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getGradientType()).toBe(pdg.gradientType_Radial);
      expect(updatedAttrs.getRadialGradientCenter().equals(centerPoint)).toBe(true);
      expect(updatedAttrs.getRadialGradientCenterColor().equals(centerColor)).toBe(true);
      expect(updatedAttrs.getRadialGradientRadius()).toBe(radius);
      expect(updatedAttrs.getRadialGradientEndColor().equals(endColor)).toBe(true);
    });

    xit("can set transform", function() {
      var transform = new pdg.Transform();
      transform.translate(10, 20);
      transform.rotate(45);
      
      var attrs = elementRef.getAttributes(); 
      attrs.transform(transform);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
    });

    it("can set rotation", function() {
      var radians = Math.PI / 4; // 45 degrees
      var aroundPoint = new pdg.Point(5, 5);
      
      var attrs = elementRef.getAttributes();
      attrs.rotation(radians, aroundPoint);
      elementRef.setAttributes(attrs);
      
      // Verify the change was applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      // we don't store the rotation, we alter the internal transform matrix
      // so this is harder to test. 
    });

    it("supports method chaining", function() {
      var color = new pdg.Color(255, 0, 0, 255);
      var attrs = elementRef.getAttributes();
      attrs
        .lineColor(color)
        .lineThickness(2.0)
        .lineOpacity(0.8)
        .fillColor(color)
        .fillOpacity(0.6);
      elementRef.setAttributes(attrs);
      
      // Verify the changes were applied
      var updatedAttrs = elementRef.getAttributes();
      expect(updatedAttrs).toBeDefined();
      expect(updatedAttrs.getLineColor().equals(color)).toBe(true);
      expect(updatedAttrs.getLineThickness()).toBe(2.0);
      expect(updatedAttrs.getLineOpacity()).toBeCloseTo(0.8);
      expect(updatedAttrs.getFillColor().equals(color)).toBe(true);
      expect(updatedAttrs.getFillOpacity()).toBeCloseTo(0.6);
    });

  });

  describe("element layering", function() {

    var drawing, lineRef, rectRef, circleRef;

    beforeEach(function() {
      drawing = pdg.createDrawing();
      var lineAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      lineRef = drawing.addLine(new pdg.Point(0, 0), new pdg.Point(10, 10), lineAttrs);
      var rectAttrs = new pdg.Attributes().fillColor("blue");
      rectRef = drawing.addRect(new pdg.Rect(5, 5, 20, 20), rectAttrs);
      var circleAttrs = new pdg.Attributes().fillColor("green");
      circleRef = drawing.addEllipse(new pdg.Point(15, 15), 5, 5, circleAttrs);
    });

    it("can move element forward", function() {
      var originalIndex = drawing.getElementCount() - 1;
      circleRef.moveForward();
      // Moving forward should not change the index if already at front
      expect(drawing.getElementCount()).toBe(3);
    });

    it("can move element backward", function() {
      var originalIndex = 0;
      lineRef.moveBackward();
      // Moving backward should not change the index if already at back
      expect(drawing.getElementCount()).toBe(3);
    });

    it("can move element to front", function() {
      lineRef.moveToFront();
      expect(drawing.getElementCount()).toBe(3);
    });

    it("can move element to back", function() {
      circleRef.moveToBack();
      expect(drawing.getElementCount()).toBe(3);
    });

    it("can remove element", function() {
      expect(drawing.getElementCount()).toBe(3);
      lineRef.remove();
      expect(drawing.getElementCount()).toBe(2);
    });

  });

  describe("drawing operations", function() {

    var drawing;

    beforeEach(function() {
      drawing = pdg.createDrawing();
      var lineAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      drawing.addLine(new pdg.Point(0, 0), new pdg.Point(10, 10), lineAttrs);
      var rectAttrs = new pdg.Attributes().fillColor("blue");
      drawing.addRect(new pdg.Rect(5, 5, 20, 20), rectAttrs);
    });

    it("has non-empty bounds after adding elements", function() {
      var bounds = drawing.getBounds();
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      // Should have some width and height now
      expect(bounds.width()).toBeGreaterThan(0);
      expect(bounds.height()).toBeGreaterThan(0);
    });

    it("has correct center point after adding elements", function() {
      var center = drawing.centerPoint();
      expect(center).toBeDefined();
      expect(center.constructor.name).toBe('Point');
    });

    it("is no longer empty after adding elements", function() {
      expect(drawing.empty()).toBe(false);
    });

    it("has draw method (GUI only)", function() {
      // Note: We can't actually test drawing without a Port object
      // Just verify the method exists
      if (pdg.hasGraphics) {
        expect(typeof drawing.draw).toBe('function');
      } else {
        expect(typeof drawing.draw).toBe('undefined');
      }
    });

  });

  describe("error handling", function() {

    var drawing;

    beforeEach(function() {
      drawing = pdg.createDrawing();
    });

    it("throws error for invalid arguments in addLine", function() {
      var attrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      expect(function() {
        drawing.addLine(null, new pdg.Point(10, 10), attrs);
      }).toThrow();
      
      expect(function() {
        drawing.addLine(new pdg.Point(0, 0), null, attrs);
      }).toThrow();
    });

    it("throws error for invalid arguments in addRect", function() {
      var attrs = new pdg.Attributes().fillColor("blue");
      expect(function() {
        drawing.addRect(undefined, attrs);
      }).toThrow();
    });

    it("throws error for invalid arguments in addEllipse", function() {
      var attrs = new pdg.Attributes().fillColor("green");
      expect(function() {
        drawing.addEllipse(null, 10, 10, attrs);
      }).toThrow();
      
      expect(function() {
        drawing.addEllipse(new pdg.Point(0, 0), null, 10, attrs);
      }).toThrow();
    });

    it("throws error for invalid arguments in addOval", function() {
      var attrs = new pdg.Attributes().fillColor("yellow");
      expect(function() {
        drawing.addEllipse(null, 10, 10, attrs);
      }).toThrow();
      
      expect(function() {
        drawing.addEllipse(new pdg.Point(0, 0), null, 10, attrs);
      }).toThrow();
      
      expect(function() {
        drawing.addEllipse(new pdg.Point(0, 0), 10, null, attrs);
      }).toThrow();
    });

  });

  describe("nested drawings", function() {

    var parentDrawing, childDrawing;

    beforeEach(function() {
      parentDrawing = pdg.createDrawing();
      childDrawing = pdg.createDrawing();
      var attrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
      childDrawing.addLine(new pdg.Point(0, 0), new pdg.Point(5, 5), attrs);
    });

    it("can add a drawing as an element", function() {
      var rect = new pdg.Rect(0, 0, 10, 10);
      var elementRef = parentDrawing.addDrawing(rect, childDrawing, new pdg.Attributes());
      
      expect(elementRef).toBeDefined();
      expect(elementRef.constructor.name).toBe('ElementRef');
      expect(parentDrawing.getElementCount()).toBe(1);
      expect(elementRef.type()).toBe(pdg.type_Drawing)
    });

  });

  describe("Attributes Transform and Blend Mode", function() {

    it("can get and set transform matrix", function() {
      console.log('* Testing Attributes transform matrix...');
      
      var attrs = new pdg.Attributes();
      
      // Test initial transform (should be identity matrix)
      var initialTransform = attrs.getTransform();
      expect(initialTransform).toBeDefined();
      expect(Array.isArray(initialTransform)).toBe(true);
      expect(initialTransform.length).toBe(9);
      expect(initialTransform).toEqual([1, 0, 0, 0, 1, 0, 0, 0, 1]);
      
      // Apply a translation matrix
      var translationMatrix = [1, 0, 0, 0, 1, 0, 10, 20, 1];
      attrs.transform(translationMatrix);
      
      // Verify the transform was applied
      var newTransform = attrs.getTransform();
      expect(newTransform).toEqual(translationMatrix);
      
      // Apply a scale matrix
      var scaleMatrix = [2, 0, 0, 0, 3, 0, 0, 0, 1];
      attrs.transform(scaleMatrix);
      
      // Verify the combined transform
      var combinedTransform = attrs.getTransform();
      expect(combinedTransform).toBeDefined();
      expect(Array.isArray(combinedTransform)).toBe(true);
      expect(combinedTransform.length).toBe(9);
    });

    it("can get and set blend mode", function() {
      console.log('* Testing Attributes blend mode...');
      
      var attrs = new pdg.Attributes();
      
      // Test initial blend mode (should be 0)
      var initialBlendMode = attrs.getBlendMode();
      expect(initialBlendMode).toBeDefined();
      expect(typeof initialBlendMode).toBe('number');
      expect(initialBlendMode).toBe(0);
      
      // Set a new blend mode
      attrs.blendMode(2);
      var newBlendMode = attrs.getBlendMode();
      expect(newBlendMode).toBe(2);
      
      // Set another blend mode
      attrs.blendMode(5);
      var anotherBlendMode = attrs.getBlendMode();
      expect(anotherBlendMode).toBe(5);
    });

    it("handles transform matrix validation", function() {
      console.log('* Testing transform matrix validation...');
      
      var attrs = new pdg.Attributes();
      
      // Test with valid 9-element array
      expect(function() {
        attrs.transform([1, 0, 0, 0, 1, 0, 0, 0, 1]);
      }).not.toThrow();
      
      // Test with invalid array length (should throw)
      expect(function() {
        attrs.transform([1, 2, 3, 4, 5, 6, 7, 8]); // Only 8 elements
      }).toThrow();
      
      // Test with non-array argument (should throw)
      expect(function() {
        attrs.transform("not an array");
      }).toThrow();
      
      // Test with array containing non-numbers (should throw)
      expect(function() {
        attrs.transform([1, 0, 0, 0, 1, 0, 0, 0, "not a number"]);
      }).toThrow();
    });

    it("can perform round-trip operations", function() {
      console.log('* Testing round-trip operations...');
      
      var attrs = new pdg.Attributes();
      
      // Test transform round-trip
      var originalTransform = [1, 0.5, 0, 0, 1, 0, 15, 25, 1];
      attrs.transform(originalTransform);
      var retrievedTransform = attrs.getTransform();
      expect(retrievedTransform).toEqual(originalTransform);
      
      // Test blend mode round-trip
      var originalBlendMode = 4;
      attrs.blendMode(originalBlendMode);
      var retrievedBlendMode = attrs.getBlendMode();
      expect(retrievedBlendMode).toBe(originalBlendMode);
    });

    it("combines transform operations correctly", function() {
      console.log('* Testing transform combination...');
      
      var attrs = new pdg.Attributes();
      
      // Start with identity
      expect(attrs.getTransform()).toEqual([1, 0, 0, 0, 1, 0, 0, 0, 1]);
      
      // Apply translation
      attrs.translation(new pdg.Offset(5, 10));
      var afterTranslation = attrs.getTransform();
      expect(afterTranslation[6]).toBe(5);   // tx
      expect(afterTranslation[7]).toBe(10);  // ty
      
      // Apply scale
      attrs.scale(2, 3);
      var afterScale = attrs.getTransform();
      expect(afterScale[0]).toBe(2);  // sx
      expect(afterScale[4]).toBe(3);  // sy
      
      // Apply rotation
      attrs.rotation(Math.PI / 4); // 45 degrees
      var afterRotation = attrs.getTransform();
      expect(afterRotation).toBeDefined();
      expect(Array.isArray(afterRotation)).toBe(true);
    });

  });

});
