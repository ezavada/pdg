// -----------------------------------------------
// port.spec.js
//
// test suite for Port
//
// Written by Ed Zavada, 2014
// Copyright (c) 2014, Dream Rock Studios, LLC
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

describe("Port", function() {

  describe("availability", function() {

    it("checks if Port is available", function() {
      console.log('* Testing Port...');
      console.log('pdg.hasGraphics:', pdg.hasGraphics);
      console.log('pdg.Port:', typeof pdg.Port);
      
      if (pdg.hasGraphics) {
        expect(pdg.Port).toBeDefined();
        expect(typeof pdg.Port).toBe('function');
      } else {
        expect(pdg.Port).toBeUndefined();
      }
    });

  });

  if (pdg.hasGraphics) {

    describe("construction", function() {

      it("can be created", function() {
        expect(pdg.Port).toBeDefined();
        expect(typeof pdg.Port).toBe('function');
      });

      it("can be instantiated through GraphicsManager", function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        var port = pdg.gfx.createWindowPort(rect, "Test Window");
        expect(port).toBeDefined();
        expect(typeof port).toBe('object');
        expect(port.constructor.name).toBe('Port');
        // Clean up
        pdg.gfx.closeGraphicsPort(port);
      });

    });

    describe("basic properties", function() {

      var port;

      beforeEach(function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(rect, "Test Window");
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("has getClipRect method", function() {
        expect(typeof port.getClipRect).toBe('function');
      });

      it("has setClipRect method", function() {
        expect(typeof port.setClipRect).toBe('function');
      });

      it("has getDrawingArea method", function() {
        expect(typeof port.getDrawingArea).toBe('function');
      });

      it("has drawRect method", function() {
        expect(typeof port.drawRect).toBe('function');
      });

      it("has drawQuad method", function() {
        expect(typeof port.drawQuad).toBe('function');
      });

      it("has drawLine method", function() {
        expect(typeof port.drawLine).toBe('function');
      });

      it("has drawPolygon method", function() {
        expect(typeof port.drawPolygon).toBe('function');
      });

      it("has drawEllipse method", function() {
        expect(typeof port.drawEllipse).toBe('function');
      });

      it("has drawArc method", function() {
        expect(typeof port.drawArc).toBe('function');
      });


      it("has drawSpline method", function() {
        expect(typeof port.drawSpline).toBe('function');
      });

      it("has drawText method", function() {
        expect(typeof port.drawText).toBe('function');
      });

      it("has drawImage method", function() {
        expect(typeof port.drawImage).toBe('function');
      });

      it("has drawDrawing method", function() {
        expect(typeof port.drawDrawing).toBe('function');
      });

      it("has drawSphere method", function() {
        expect(typeof port.drawSphere).toBe('function');
      });

      it("has getTextWidth method", function() {
        expect(typeof port.getTextWidth).toBe('function');
      });

      it("has getCurrentFont method", function() {
        expect(typeof port.getCurrentFont).toBe('function');
      });

      it("has setFont method", function() {
        expect(typeof port.setFont).toBe('function');
      });

      it("has setFontForStyle method", function() {
        expect(typeof port.setFontForStyle).toBe('function');
      });

      it("has setFontScalingFactor method", function() {
        expect(typeof port.setFontScalingFactor).toBe('function');
      });

      it("has startTrackingMouse method", function() {
        expect(typeof port.startTrackingMouse).toBe('function');
      });

      it("has stopTrackingMouse method", function() {
        expect(typeof port.stopTrackingMouse).toBe('function');
      });

      it("has resetCursor method", function() {
        expect(typeof port.resetCursor).toBe('function');
      });

    });

    describe("clip rectangle operations", function() {

      var port;

      beforeEach(function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(rect, "Test Window");
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can get clip rectangle", function() {
        var clipRect = port.getClipRect();
        expect(clipRect).toBeDefined();
        expect(typeof clipRect).toBe('object');
      });

      it("can set clip rectangle", function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        var result = port.setClipRect(rect);
        expect(result).toBeDefined();
        expect(typeof result).toBe('object');
      });

      it("returns port for chaining when setting clip rectangle", function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        var result = port.setClipRect(rect);
        expect(result).toBe(port);
      });

    });

    describe("drawing area operations", function() {

      var port;

      beforeEach(function() {
        var rect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(rect, "Test Window");
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can get drawing area", function() {
        var drawingArea = port.getDrawingArea();
        expect(drawingArea).toBeDefined();
        expect(typeof drawingArea).toBe('object');
      });

    });

    describe("rectangle drawing operations", function() {

      var port;
      var rect;
      var color;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
        rect = new pdg.Rect(10, 20, 110, 120);
        color = new pdg.Color(1.0, 0.0, 0.0, 1.0);
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can draw filled rectangle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().fillColor(color);
          port.drawRect(rect, attrs);
        }).not.toThrow();
      });

      it("can draw framed rectangle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawRect(rect, attrs);
        }).not.toThrow();
      });

      it("can draw filled and framed rectangle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().fillColor(color).lineColor(new pdg.Color(1.0, 1.0, 1.0, 1.0)).lineThickness(2.0);
          port.drawRect(rect, attrs);
        }).not.toThrow();
      });

      it("can draw rounded rectangle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().fillColor(color).roundedCorners(5);
          port.drawRect(rect, attrs);
        }).not.toThrow();
      });

    });

    describe("line drawing operations", function() {

      var port;
      var fromPoint;
      var toPoint;
      var color;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
        fromPoint = new pdg.Point(10, 20);
        toPoint = new pdg.Point(110, 120);
        color = new pdg.Color(0.0, 1.0, 0.0, 1.0);
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can draw line", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawLine(fromPoint, toPoint, attrs);
        }).not.toThrow();
      });

    });

    describe("spline drawing operations", function() {

      var port;
      var spline;
      var p1, p2, p3, p4;
      var color;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Spline Test Window");
        
        // Create test spline
        spline = new pdg.Spline(pdg.spline_Hermite);
        p1 = new pdg.Point(10, 10);
        p2 = new pdg.Point(30, 80);
        p3 = new pdg.Point(70, 20);
        p4 = new pdg.Point(90, 90);
        spline.addSegment(p1, p2, p3, p4);
        
        color = new pdg.Color(255, 0, 0, 255); // Red
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can draw spline with default parameters", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor("black").lineThickness(1.0);
          port.drawSpline(spline, attrs);
        }).not.toThrow();
      });

      it("can draw spline with custom segments", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor("black").lineThickness(1.0);
          port.drawSpline(spline, attrs);
        }).not.toThrow();
      });

      it("can draw spline with color", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawSpline(spline, attrs);
        }).not.toThrow();
      });

      it("can draw spline with all parameters", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawSpline(spline, attrs);
        }).not.toThrow();
      });

      it("can draw spline with thickness", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(2);
          port.drawSpline(spline, attrs);
        }).not.toThrow();
      });

      it("can draw different spline types", function() {
        var splineTypes = [
          pdg.spline_Hermite,
          pdg.spline_Cardinal,
          pdg.spline_UniformB,
          pdg.spline_CubicBezier,
          pdg.spline_TCB,
          pdg.spline_NaturalCubic,
        ];

        splineTypes.forEach(function(splineType) {
          var testSpline = new pdg.Spline(splineType);
          testSpline.addSegment(p1, p2, p3, p4);
          
          expect(function() {
            var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
            port.drawSpline(testSpline, attrs);
          }).not.toThrow();
          
          expect(function() {
            var attrs = new pdg.Attributes().lineColor(color).lineThickness(1);
            port.drawSpline(testSpline, attrs);
          }).not.toThrow();
        });
      });

      xit("throws error with invalid segment count", function() {
        expect(function() {
          port.drawSpline(spline, "black", 1.0, -1);
        }).toThrow();
      });

      xit("throws error with invalid thickness", function() {
        expect(function() {
          port.drawSpline(spline, color, -1);
        }).toThrow();
      });

    });

    describe("circle and oval drawing operations", function() {

      var port;
      var centerPoint;
      var color;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
        centerPoint = new pdg.Point(50, 50);
        color = new pdg.Color(0.0, 0.0, 1.0, 1.0);
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can draw framed circle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawEllipse(centerPoint, 25, 25, attrs);
        }).not.toThrow();
      });

      it("can draw filled circle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().fillColor(color);
          port.drawEllipse(centerPoint, 25, 25, attrs);
        }).not.toThrow();
      });

      it("can draw framed oval", function() {
        expect(function() {
          var attrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
          port.drawEllipse(centerPoint, 30, 20, attrs);
        }).not.toThrow();
      });

      it("can draw filled oval", function() {
        expect(function() {
          var attrs = new pdg.Attributes().fillColor(color);
          port.drawEllipse(centerPoint, 30, 20, attrs);
        }).not.toThrow();
      });

    });

    describe("text operations", function() {

      var port;
      var location;
      var rect;
      var color;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
        location = new pdg.Point(10, 20);
        rect = new pdg.Rect(10, 20, 200, 100);
        color = new pdg.Color(0.0, 0.0, 0.0, 1.0);
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can draw text at location", function() {
        expect(function() {
          var attrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor(color);
          port.drawText("Hello World", location, attrs);
        }).not.toThrow();
      });

      it("can draw text in rectangle", function() {
        expect(function() {
          var attrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor(color);
          port.drawText("Hello World", rect, attrs);
        }).not.toThrow();
      });

      it("can get text width", function() {
        var width = port.getTextWidth("Hello World", 12, pdg.textStyle_Plain, 11);
        expect(typeof width).toBe('number');
        expect(width >= 0).toBeTruthy();
      });

      it("can get current font", function() {
        var font = port.getCurrentFont(pdg.textStyle_Plain);
        expect(font).toBeDefined();
        expect(typeof font).toBe('object');
      });

      it("can set font", function() {
        var font = port.getCurrentFont(pdg.textStyle_Plain);
        expect(function() {
          port.setFont(font);
        }).not.toThrow();
      });

      it("can set font for style", function() {
        var font = port.getCurrentFont(pdg.textStyle_Plain);
        expect(function() {
          port.setFontForStyle(pdg.textStyle_Bold, font);
        }).not.toThrow();
      });

      it("can set font scaling factor", function() {
        expect(function() {
          port.setFontScalingFactor(1.5);
        }).not.toThrow();
      });

    });

    describe("mouse tracking operations", function() {

      var port;
      var rect;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
        rect = new pdg.Rect(0, 0, 100, 100);
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can start tracking mouse", function() {
        var trackingRef = port.startTrackingMouse(rect);
        expect(typeof trackingRef).toBe('number');
        expect(trackingRef >= 0).toBeTruthy();
      });

      it("can stop tracking mouse", function() {
        var trackingRef = port.startTrackingMouse(rect);
        expect(function() {
          port.stopTrackingMouse(trackingRef);
        }).not.toThrow();
      });

    });

    describe("cursor operations", function() {

      var port;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      // FIXME: this segfaults
      xit("can get cursor", function() {
        var cursor = port.getCursor();
        expect(cursor).toBeDefined();
        expect(typeof cursor).toBe('object');
      });

      // FIXME: this segfaults
      xit("can set cursor", function() {
        var cursor = port.getCursor();
        var hotSpot = new pdg.Point(0, 0);
        expect(function() {
          port.setCursor(cursor, hotSpot);
        }).not.toThrow();
      });

      it("can reset cursor", function() {
        expect(function() {
          port.resetCursor();
        }).not.toThrow();
      });

    });

    describe("integration tests", function() {

      var port;

      beforeEach(function() {
        var portRect = new pdg.Rect(0, 0, 100, 100);
        port = pdg.gfx.createWindowPort(portRect, "Test Window");
      });

      afterEach(function() {
        if (port) {
          pdg.gfx.closeGraphicsPort(port);
        }
      });

      it("can perform complete drawing workflow", function() {
        var rect = new pdg.Rect(10, 20, 110, 120);
        var color = new pdg.Color(1.0, 0.0, 0.0, 1.0);
        var point = new pdg.Point(50, 50);

        // Set clip rectangle
        port.setClipRect(rect);

        // Draw some shapes
        var fillAttrs = new pdg.Attributes().fillColor(color);
        port.drawRect(rect, fillAttrs);
        var frameAttrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
        port.drawRect(rect, frameAttrs);
        var lineAttrs = new pdg.Attributes().lineColor(color).lineThickness(1.0);
        port.drawLine(point, new pdg.Point(100, 100), lineAttrs);

        // Draw text
        var textAttrs = new pdg.Attributes().textSize(12).textStyle(pdg.textStyle_Plain).fillColor(color);
        port.drawText("Test", point, textAttrs);

        // Verify methods completed without throwing
        expect(true).toBeTruthy();
      });

      it("can chain operations", function() {
        var rect = new pdg.Rect(10, 20, 110, 120);
        var color = new pdg.Color(1.0, 0.0, 0.0, 1.0);

        var result = port.setClipRect(rect);
        expect(result).toBe(port);
      });

    });

  } else {

    describe("non-GUI build behavior", function() {

      it("Port is not available in non-GUI builds", function() {
        expect(pdg.Port).toBeUndefined();
      });

      it("hasGraphics is false in non-GUI builds", function() {
        expect(pdg.hasGraphics).toBeFalsy();
      });

    });

  }

});
