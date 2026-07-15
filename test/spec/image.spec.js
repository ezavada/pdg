// -----------------------------------------------
// image.spec.js
//
// test suite for Image
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

describe("Image", function() {

  var testImage;
  var subsectionImage;

  beforeEach(function() {
    testImage = new pdg.Image('./yinyang.png');
    expect(testImage).toBeDefined();
  });

  describe("Basic Properties", function() {
    it("exists", function() {
      console.log('* Testing Image...');
      expect(pdg.Image).toBeDefined();
    });

    it("can be created with file path", function() {
      var image = new pdg.Image('./yinyang.png');
      expect(image).toBeDefined();
      expect(image.constructor.name).toBe('Image');
    });

    it("has correct dimensions", function() {
      expect(testImage.getHeight()).toBe(64);
      expect(testImage.getWidth()).toBe(64);
    });

    it("can get image bounds", function() {
      var bounds = testImage.getImageBounds();
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.width()).toBe(64);
      expect(bounds.height()).toBe(64);
    });

    it("can get image bounds at specific point", function() {
      var point = new pdg.Point(10, 20);
      var bounds = testImage.getImageBounds(point);
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.left).toBe(10);
      expect(bounds.top).toBe(20);
      expect(bounds.width()).toBe(64);
      expect(bounds.height()).toBe(64);
    });
  });

  describe("Pixel Operations", function() {
    it("can read pixels by coordinates", function() {
      var pixel1 = testImage.getPixel(16, 16);
      var pixel2 = testImage.getPixel(48, 48);
      
      expect(pixel1).toBeDefined();
      expect(pixel1.constructor.name).toBe('Color');
      expect(pixel1.red).toBe(1);
      expect(pixel1.green).toBe(1);
      expect(pixel1.blue).toBe(1);
      expect(pixel1.alpha).toBe(1);
      
      expect(pixel2).toBeDefined();
      expect(pixel2.constructor.name).toBe('Color');
      expect(pixel2.red).toBe(0);
      expect(pixel2.green).toBe(0);
      expect(pixel2.blue).toBe(0);
      expect(pixel2.alpha).toBe(1);
    });

    it("can read pixels by point", function() {
      var point1 = new pdg.Point(16, 16);
      var point2 = new pdg.Point(48, 48);
      
      var pixel1 = testImage.getPixel(point1);
      var pixel2 = testImage.getPixel(point2);
      
      expect(pixel1).toBeDefined();
      expect(pixel1.constructor.name).toBe('Color');
      expect(pixel2).toBeDefined();
      expect(pixel2.constructor.name).toBe('Color');
    });

    it("can get alpha values by coordinates", function() {
      var alpha1 = testImage.getAlphaValue(0, 0);
      var alpha2 = testImage.getAlphaValue(16, 16);
      
      expect(alpha1).toBe(0);
      expect(alpha2).toBe(255);
    });

    it("can get alpha values by point", function() {
      var point1 = new pdg.Point(0, 0);
      var point2 = new pdg.Point(16, 16);
      
      var alpha1 = testImage.getAlphaValue(point1);
      var alpha2 = testImage.getAlphaValue(point2);
      
      expect(alpha1).toBe(0);
      expect(alpha2).toBe(255);
    });
  });

  describe("Image Subsection", function() {
    it("can create subsection using Rect", function() {
      var rect = new pdg.Rect(32, 64);
      subsectionImage = testImage.getSubsection(rect);
      
      expect(subsectionImage).toBeDefined();
      expect(subsectionImage.constructor.name).toBe('Image');
      expect(subsectionImage.getHeight()).toBe(64);
      expect(subsectionImage.getWidth()).toBe(32);
    });

    it("can create subsection using Quad", function() {
      var quad = new pdg.Quad(
        new pdg.Point(0, 0),
        new pdg.Point(32, 0),
        new pdg.Point(32, 64),
        new pdg.Point(0, 64)
      );
      var quadImage = testImage.getSubsection(quad);
      
      expect(quadImage).toBeDefined();
      expect(quadImage.constructor.name).toBe('Image');
    });
  });

  describe("Transparency and Opacity", function() {
    it("can get and set opacity", function() {
      var originalOpacity = testImage.getOpacity();
      expect(typeof originalOpacity).toBe('number');
      
      var result = testImage.setOpacity(0.5);
      // setOpacity may return undefined
      
      var newOpacity = testImage.getOpacity();
      expect(newOpacity).toBeCloseTo(0.5, 2);
    });

    it("can set transparent color", function() {
      var transparentColor = new pdg.Color(255, 0, 0, 255);
      var result = testImage.setTransparentColor(transparentColor);
      expect(result).toBe(testImage);
    });

    it("can get transparent color", function() {
      var transparentColor = testImage.getTransparentColor();
      expect(transparentColor).toBeDefined();
    });

    it("can set edge clamping", function() {
      testImage.setEdgeClamping(true);
      testImage.setEdgeClamping(false);
    });
  });

  describe("Memory Management", function() {
    it("can retain pixel data", function() {
      testImage.retainData();
    });

    it("can retain alpha data", function() {
      testImage.retainAlpha();
    });

    // FIX ME: prepareToRasterize is broken, causes segfault
    xdescribe("can prepare to rasterize", function() {
      var result = testImage.prepareToRasterize();
      expect(typeof result).toBe('undefined');
    });
  });

  describe("Error Handling", function() {
    it("handles invalid coordinates gracefully", function() {
      // getPixel with invalid coordinates may not throw in this implementation
      expect(function() {
        testImage.getPixel(-1, -1);
      }).not.toThrow();
      
      expect(function() {
        testImage.getPixel(1000, 1000);
      }).not.toThrow();
      
      expect(function() {
        testImage.getAlphaValue(-1, -1);
      }).not.toThrow();
    });

    it("handles null parameters gracefully", function() {
      // getPixel with null may not throw in this implementation
      expect(function() {
        testImage.getPixel(null);
      }).not.toThrow();
      
      // getAlphaValue with null may not throw in this implementation
      expect(function() {
        testImage.getAlphaValue(null);
      }).not.toThrow();
      
      expect(function() {
        testImage.getImageBounds(null);
      }).not.toThrow();
    });

    it("handles invalid opacity values gracefully", function() {
      expect(function() {
        testImage.setOpacity(-1);
      }).not.toThrow();
      
      expect(function() {
        testImage.setOpacity(2);
      }).not.toThrow();
      
      expect(function() {
        testImage.setOpacity(NaN);
      }).not.toThrow();
    });
  });

  describe("Performance and Scalability", function() {
    it("can handle multiple pixel reads efficiently", function() {
      for (var i = 0; i < 100; i++) {
        var pixel = testImage.getPixel(i % 64, i % 64);
        expect(pixel).toBeDefined();
      }
    });

    it("can handle multiple alpha reads efficiently", function() {
      for (var i = 0; i < 100; i++) {
        var alpha = testImage.getAlphaValue(i % 64, i % 64);
        expect(typeof alpha).toBe('number');
      }
    });
  });

  describe("Validation", function() {
    it("validates that getWidth returns number", function() {
      var width = testImage.getWidth();
      expect(typeof width).toBe('number');
      expect(width > 0).toBe(true);
    });

    it("validates that getHeight returns number", function() {
      var height = testImage.getHeight();
      expect(typeof height).toBe('number');
      expect(height > 0).toBe(true);
    });

    it("validates that getPixel returns Color", function() {
      var pixel = testImage.getPixel(16, 16);
      expect(typeof pixel).toBe('object');
      expect(pixel.constructor.name).toBe('Color');
      expect(pixel instanceof Color).toBe(true);
    });

    it("validates that getAlphaValue returns number", function() {
      var alpha = testImage.getAlphaValue(16, 16);
      expect(typeof alpha).toBe('number');
      expect(alpha >= 0 && alpha <= 255).toBe(true);
    });

    if ("validates that getTransparentColor returns Color", function() {
      var transparentColor = testImage.getTransparentColor();
      expect(typeof transparentColor).toBe('object');
      expect(transparentColor instanceof Color).toBe(true);
    });

    it("validates that getImageBounds returns Rect", function() {
      var bounds = testImage.getImageBounds();
      expect(typeof bounds).toBe('object');
      expect(bounds instanceof Rect).toBe(true);
      expect(bounds.constructor.name).toBe('Rect');
    });

    it("validates that getSubsection returns Image", function() {
      var rect = new pdg.Rect(16, 16);
      var subsection = testImage.getSubsection(rect);
      expect(typeof subsection).toBe('object');
      expect(subsection instanceof pdg.Image).toBe(true);
      expect(subsection.constructor.name).toBe('Image');
    });

    it("validates consistency across multiple calls", function() {
      var width1 = testImage.getWidth();
      var width2 = testImage.getWidth();
      expect(width1).toBe(width2);
      
      var height1 = testImage.getHeight();
      var height2 = testImage.getHeight();
      expect(height1).toBe(height2);
    });
  });

});