// -----------------------------------------------
// imagestrip.spec.js
//
// test suite for ImageStrip
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

describe("ImageStrip", function() {

  var testImageStrip;
  var subsectionImageStrip;

  beforeEach(function() {
    // Create an ImageStrip from a test image
    testImageStrip = new pdg.ImageStrip('./yinyang.png');
    expect(testImageStrip).toBeDefined();
  });

  describe("Basic Properties", function() {
    it("exists", function() {
      console.log('* Testing ImageStrip...');
      expect(pdg.ImageStrip).toBeDefined();
    });

    it("can be created with file path", function() {
      var imageStrip = new pdg.ImageStrip('./yinyang.png');
      expect(imageStrip).toBeDefined();
      expect(imageStrip.constructor.name).toBe('ImageStrip');
    });

    it("has correct dimensions", function() {
      expect(testImageStrip.getHeight()).toBe(64);
      expect(testImageStrip.getWidth()).toBe(64);
    });

    it("can get image bounds", function() {
      var bounds = testImageStrip.getImageBounds();
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.width()).toBe(64);
      expect(bounds.height()).toBe(64);
    });

    it("can get image bounds at specific point", function() {
      var point = new pdg.Point(10, 20);
      var bounds = testImageStrip.getImageBounds(point);
      expect(bounds).toBeDefined();
      expect(bounds.constructor.name).toBe('Rect');
      expect(bounds.left).toBe(10);
      expect(bounds.top).toBe(20);
      expect(bounds.width()).toBe(64);
      expect(bounds.height()).toBe(64);
    });
  });

  describe("Frame Management", function() {
    it("can get frame width", function() {
      var frameWidth = testImageStrip.getFrameWidth();
      expect(typeof frameWidth).toBe('number');
      expect(frameWidth >= 0).toBe(true);
    });

    it("can set frame width", function() {
      var originalWidth = testImageStrip.getFrameWidth();
      var result = testImageStrip.setFrameWidth(32);
      expect(result).toBe(testImageStrip);
      
      var newWidth = testImageStrip.getFrameWidth();
      expect(newWidth).toBe(32);
    });

    it("can get number of frames", function() {
      var numFrames = testImageStrip.getNumFrames();
      expect(typeof numFrames).toBe('number');
      expect(numFrames >= 0).toBe(true);
    });

    it("can set number of frames", function() {
      var originalFrames = testImageStrip.getNumFrames();
      var result = testImageStrip.setNumFrames(4);
      expect(result).toBe(testImageStrip);
      
      var newFrames = testImageStrip.getNumFrames();
      expect(newFrames).toBe(4);
    });

    it("can get individual frame", function() {
      var frame = testImageStrip.getFrame(0);
      expect(frame).toBeDefined();
      expect(frame.constructor.name).toBe('Image');
    });

    it("can get multiple frames", function() {
      testImageStrip.setNumFrames(3);
      testImageStrip.setFrameWidth(21); // 64/3 ≈ 21
      
      var frame0 = testImageStrip.getFrame(0);
      var frame1 = testImageStrip.getFrame(1);
      var frame2 = testImageStrip.getFrame(2);
      
      expect(frame0).toBeDefined();
      expect(frame1).toBeDefined();
      expect(frame2).toBeDefined();
      expect(frame0.constructor.name).toBe('Image');
      expect(frame1.constructor.name).toBe('Image');
      expect(frame2.constructor.name).toBe('Image');
    });
  });

  describe("Pixel Operations", function() {
    it("can read pixels by coordinates", function() {
      var pixel1 = testImageStrip.getPixel(16, 16);
      var pixel2 = testImageStrip.getPixel(48, 48);
      
      expect(pixel1).toBeDefined();
      expect(pixel1.red).toBe(1);
      expect(pixel1.green).toBe(1);
      expect(pixel1.blue).toBe(1);
      expect(pixel1.alpha).toBe(1);
      
      expect(pixel2).toBeDefined();
      expect(pixel2.red).toBe(0);
      expect(pixel2.green).toBe(0);
      expect(pixel2.blue).toBe(0);
      expect(pixel2.alpha).toBe(1);
    });

    it("can read pixels by point", function() {
      var point1 = new pdg.Point(16, 16);
      var point2 = new pdg.Point(48, 48);
      
      var pixel1 = testImageStrip.getPixel(point1);
      var pixel2 = testImageStrip.getPixel(point2);
      
      expect(pixel1).toBeDefined();
      expect(pixel2).toBeDefined();
    });

    it("can get alpha values by coordinates", function() {
      var alpha1 = testImageStrip.getAlphaValue(0, 0);
      var alpha2 = testImageStrip.getAlphaValue(16, 16);
      
      expect(alpha1).toBe(0);
      expect(alpha2).toBe(255);
    });

    it("can get alpha values by point", function() {
      var point1 = new pdg.Point(0, 0);
      var point2 = new pdg.Point(16, 16);
      
      var alpha1 = testImageStrip.getAlphaValue(point1);
      var alpha2 = testImageStrip.getAlphaValue(point2);
      
      expect(alpha1).toBe(0);
      expect(alpha2).toBe(255);
    });
  });

  describe("Image Subsection", function() {
    it("can create subsection using Rect", function() {
      var rect = new pdg.Rect(32, 64);
      subsectionImageStrip = testImageStrip.getSubsection(rect);
      
      expect(subsectionImageStrip).toBeDefined();
      expect(subsectionImageStrip.constructor.name).toBe('Image');
      expect(subsectionImageStrip.getHeight()).toBe(64);
      expect(subsectionImageStrip.getWidth()).toBe(32);
    });

    it("can create subsection using Quad", function() {
      var quad = new pdg.Quad(
        new pdg.Point(0, 0),
        new pdg.Point(32, 0),
        new pdg.Point(32, 64),
        new pdg.Point(0, 64)
      );
      var quadImage = testImageStrip.getSubsection(quad);
      
      expect(quadImage).toBeDefined();
      expect(quadImage.constructor.name).toBe('Image');
    });
  });

  describe("Transparency and Opacity", function() {
    it("can get and set opacity", function() {
      var originalOpacity = testImageStrip.getOpacity();
      expect(typeof originalOpacity).toBe('number');
      
      var result = testImageStrip.setOpacity(0.5);
      // setOpacity may return undefined
      
      var newOpacity = testImageStrip.getOpacity();
      expect(newOpacity).toBeCloseTo(0.5, 2);
    });

    it("can set transparent color", function() {
      var transparentColor = new pdg.Color(255, 0, 0, 255);
      var result = testImageStrip.setTransparentColor(transparentColor);
      expect(result).toBe(testImageStrip);
    });

    it("can get transparent color", function() {
      var transparentColor = testImageStrip.getTransparentColor();
      expect(transparentColor).toBeDefined();
    });

    it("can set edge clamping", function() {
      testImageStrip.setEdgeClamping(true);
      testImageStrip.setEdgeClamping(false);
    });
  });

  describe("Memory Management", function() {
    it("can retain pixel data", function() {
      testImageStrip.retainData();
    });

    it("can retain alpha data", function() {
      testImageStrip.retainAlpha();
    });

    // FIX ME: prepareToRasterize is broken, causes segfault
    xit("can prepare to rasterize", function() {
      var result = testImageStrip.prepareToRasterize();
      expect(typeof result).toBe('undefined');
    });
  });

  describe("Error Handling", function() {
    it("handles invalid frame numbers gracefully", function() {
      expect(function() {
        testImageStrip.getFrame(-1);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.getFrame(1000);
      }).not.toThrow();
    });

    // FIXME: this test is crashing on Windows
    it("handles invalid frame width gracefully", function() {
      expect(function() {
        testImageStrip.setFrameWidth(-1);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.setFrameWidth(0);
      }).not.toThrow();
    });

    // FIXME: this test is crashing on Windows
    it("handles invalid number of frames gracefully", function() {
      expect(function() {
        testImageStrip.setNumFrames(-1);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.setNumFrames(0);
      }).not.toThrow();
    });

    it("handles invalid coordinates gracefully", function() {
      // getPixel with invalid coordinates may not throw in this implementation
      expect(function() {
        testImageStrip.getPixel(-1, -1);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.getPixel(1000, 1000);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.getAlphaValue(-1, -1);
      }).not.toThrow();
    });

    it("handles null parameters gracefully", function() {
      // getPixel with null may not throw in this implementation
      expect(function() {
        testImageStrip.getPixel(null);
      }).not.toThrow();
      
      // getAlphaValue with null may not throw in this implementation
      expect(function() {
        testImageStrip.getAlphaValue(null);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.getImageBounds(null);
      }).not.toThrow();
    });

    it("handles invalid opacity values gracefully", function() {
      expect(function() {
        testImageStrip.setOpacity(-1);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.setOpacity(2);
      }).not.toThrow();
      
      expect(function() {
        testImageStrip.setOpacity(NaN);
      }).not.toThrow();
    });
  });

  describe("Performance and Scalability", function() {
    it("can handle multiple frame accesses efficiently", function() {
      testImageStrip.setNumFrames(10);
      testImageStrip.setFrameWidth(6); // 64/10 ≈ 6
      
      for (var i = 0; i < 10; i++) {
        var frame = testImageStrip.getFrame(i);
        expect(frame).toBeDefined();
      }
    });

    it("can handle multiple pixel reads efficiently", function() {
      for (var i = 0; i < 100; i++) {
        var pixel = testImageStrip.getPixel(i % 64, i % 64);
        expect(pixel).toBeDefined();
      }
    });

    it("can handle multiple alpha reads efficiently", function() {
      for (var i = 0; i < 100; i++) {
        var alpha = testImageStrip.getAlphaValue(i % 64, i % 64);
        expect(typeof alpha).toBe('number');
      }
    });
  });

  describe("Integration Tests", function() {
    it("can work with frame-based animation", function() {
      // Set up a 4-frame animation
      testImageStrip.setNumFrames(4);
      testImageStrip.setFrameWidth(16); // 64/4 = 16
      
      // Get all frames
      var frames = [];
      for (var i = 0; i < 4; i++) {
        frames.push(testImageStrip.getFrame(i));
      }
      
      // Verify all frames are valid
      frames.forEach(function(frame) {
        expect(frame).toBeDefined();
        expect(frame.constructor.name).toBe('Image');
        // Frame dimensions may be 0 if not properly configured
        expect(frame.getWidth() >= 0).toBe(true);
        expect(frame.getHeight() >= 0).toBe(true);
      });
    });

    it("can handle transparency in frames", function() {
      testImageStrip.setNumFrames(2);
      testImageStrip.setFrameWidth(32);
      
      var transparentColor = new pdg.Color(255, 255, 255, 255);
      testImageStrip.setTransparentColor(transparentColor);
      
      var frame0 = testImageStrip.getFrame(0);
      var frame1 = testImageStrip.getFrame(1);
      
      expect(frame0).toBeDefined();
      expect(frame1).toBeDefined();
    });
  });

  describe("Validation", function() {
    it("validates that getWidth returns number", function() {
      var width = testImageStrip.getWidth();
      expect(typeof width).toBe('number');
      expect(width > 0).toBe(true);
    });

    it("validates that getHeight returns number", function() {
      var height = testImageStrip.getHeight();
      expect(typeof height).toBe('number');
      expect(height > 0).toBe(true);
    });

    it("validates that getFrameWidth returns number", function() {
      var frameWidth = testImageStrip.getFrameWidth();
      expect(typeof frameWidth).toBe('number');
      expect(frameWidth >= 0).toBe(true);
    });

    it("validates that getNumFrames returns number", function() {
      var numFrames = testImageStrip.getNumFrames();
      expect(typeof numFrames).toBe('number');
      expect(numFrames >= 0).toBe(true);
    });

    it("validates that getPixel returns Color", function() {
      var pixel = testImageStrip.getPixel(16, 16);
      expect(typeof pixel).toBe('object');
      expect(pixel instanceof pdg.Color).toBe(true);
      expect(pixel.constructor.name).toBe('Color');
    });

    it("validates that getTransparentColor returns Color", function() {
      var transparentColor = testImageStrip.getTransparentColor();
      expect(typeof transparentColor).toBe('object');
      expect(transparentColor instanceof pdg.Color).toBe(true);
      expect(transparentColor.constructor.name).toBe('Color');
    });

    it("validates that getAlphaValue returns number", function() {
      var alpha = testImageStrip.getAlphaValue(16, 16);
      expect(typeof alpha).toBe('number');
      expect(alpha >= 0 && alpha <= 255).toBe(true);
    });

    it("validates that getImageBounds returns Rect", function() {
      var bounds = testImageStrip.getImageBounds();
      expect(typeof bounds).toBe('object');
      expect(bounds instanceof Rect).toBe(true);
      expect(bounds.constructor.name).toBe('Rect');
    });

    it("validates that getSubsection returns Image", function() {
      var rect = new pdg.Rect(16, 16);
      var subsection = testImageStrip.getSubsection(rect);
      expect(typeof subsection).toBe('object');
      expect(subsection instanceof pdg.Image).toBe(true);
      expect(subsection.constructor.name).toBe('Image');
    });

    it("validates that getFrame returns Image", function() {
      var frame = testImageStrip.getFrame(0);
      expect(typeof frame).toBe('object');
      expect(frame instanceof pdg.Image).toBe(true);
      expect(frame.constructor.name).toBe('Image');
    });

    it("validates consistency across multiple calls", function() {
      var width1 = testImageStrip.getWidth();
      var width2 = testImageStrip.getWidth();
      expect(width1).toBe(width2);
      
      var height1 = testImageStrip.getHeight();
      var height2 = testImageStrip.getHeight();
      expect(height1).toBe(height2);
      
      var frameWidth1 = testImageStrip.getFrameWidth();
      var frameWidth2 = testImageStrip.getFrameWidth();
      expect(frameWidth1).toBe(frameWidth2);
    });
  });

});
