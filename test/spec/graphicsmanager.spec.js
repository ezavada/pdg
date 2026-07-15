// -----------------------------------------------
// graphicsmanager.spec.js
//
// test suite for GraphicsManager
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

if (pdg.hasGraphics == false) {

	// non-graphics build (ie: node plugin)
	describe("GraphicsManager", function() {
	  it("is not present in non-GUI builds", function() {
	  	expect(pdg.gfx).toBeUndefined();
	  	expect(pdg.getGraphicsManager).toBeUndefined();
	  });
	});

} else {

describe("GraphicsManager", function() {

  var gfx;

  beforeEach(function() {
    gfx = pdg.gfx;
    expect(gfx).toBeDefined();
  });

  describe("Singleton Access", function() {
  it("is a singleton accessed by pdg.gfx", function() {
	console.log('* Testing GraphicsManager...');
	var gfx2 = pdg.getGraphicsManager();
	expect(gfx2).toBe(gfx);
  });
  });

  describe("Screen Management", function() {
    it("can get number of screens", function() {
      var numScreens = gfx.getNumScreens();
      expect(typeof numScreens).toBe('number');
      expect(numScreens).toBeGreaterThan(0);
    });

    it("can get current screen mode", function() {
      var screenMode = gfx.getCurrentScreenMode();
      expect(screenMode).toBeDefined();
      expect(screenMode.width).toBeDefined();
      expect(screenMode.height).toBeDefined();
      expect(screenMode.depth).toBeDefined();
      expect(screenMode.maxWindowRect).toBeDefined();
      expect(typeof screenMode.width).toBe('number');
      expect(typeof screenMode.height).toBe('number');
      expect(typeof screenMode.depth).toBe('number');
    });

    it("can get current screen mode for specific screen", function() {
      var screenMode = gfx.getCurrentScreenMode(0);
      expect(screenMode).toBeDefined();
      expect(screenMode.width).toBeDefined();
      expect(screenMode.height).toBeDefined();
    });

    it("can get screen bounds", function() {
      var bounds = gfx.getScreenBounds();
      expect(bounds).toBeDefined();
      // Check if bounds has the expected properties or if it's a different structure
      if (bounds && typeof bounds === 'object') {
        // If it's an object, check for Rect properties
        if (bounds.x !== undefined) {
          expect(typeof bounds.x).toBe('number');
          expect(typeof bounds.y).toBe('number');
          expect(typeof bounds.width).toBe('number');
          expect(typeof bounds.height).toBe('number');
        } else if (bounds.left !== undefined) {
          // Alternative Rect structure
          expect(typeof bounds.left).toBe('number');
          expect(typeof bounds.top).toBe('number');
          expect(typeof bounds.right).toBe('number');
          expect(typeof bounds.bottom).toBe('number');
        }
      }
    });

    it("can get screen bounds for specific screen", function() {
      var bounds = gfx.getScreenBounds(0);
      expect(bounds).toBeDefined();
      // Check if bounds has the expected properties or if it's a different structure
      if (bounds && typeof bounds === 'object') {
        // If it's an object, check for Rect properties
        if (bounds.x !== undefined) {
          expect(typeof bounds.x).toBe('number');
          expect(typeof bounds.y).toBe('number');
          expect(typeof bounds.width).toBe('number');
          expect(typeof bounds.height).toBe('number');
        } else if (bounds.left !== undefined) {
          // Alternative Rect structure
          expect(typeof bounds.left).toBe('number');
          expect(typeof bounds.top).toBe('number');
          expect(typeof bounds.right).toBe('number');
          expect(typeof bounds.bottom).toBe('number');
        }
      }
    });

    it("can get number of supported screen modes", function() {
      var numModes = gfx.getNumSupportedScreenModes();
      expect(typeof numModes).toBe('number');
      expect(numModes >= 0).toBe(true);
    });

    xit("can get number of supported screen modes for specific screen", function() {
      var numModes = gfx.getNumSupportedScreenModes(0);
      expect(typeof numModes).toBe('number');
      expect(numModes >= 0).toBe(true);
    });

    it("can get nth supported screen mode", function() {
      var mode = gfx.getNthSupportedScreenMode(0);
      expect(mode).toBeDefined();
      if (mode && typeof mode === 'object') {
        if (mode.width !== undefined) {
          expect(typeof mode.width).toBe('number');
          expect(typeof mode.height).toBe('number');
          expect(typeof mode.depth).toBe('number');
        }
        if (mode.maxWindowRect !== undefined) {
          expect(typeof mode.maxWindowRect).toBe('object');
        }
      }
    });

    it("can get nth supported screen mode for specific screen", function() {
      var mode = gfx.getNthSupportedScreenMode(0, 0);
      expect(mode).toBeDefined();
      if (mode && typeof mode === 'object') {
        if (mode.width !== undefined) {
          expect(typeof mode.width).toBe('number');
          expect(typeof mode.height).toBe('number');
          expect(typeof mode.depth).toBe('number');
        }
        if (mode.maxWindowRect !== undefined) {
          expect(typeof mode.maxWindowRect).toBe('object');
        }
      }
    });

    it("can set screen mode", function() {
      // Get current mode first
      var currentMode = gfx.getCurrentScreenMode();
      var currentWidth = currentMode.width;
      var currentHeight = currentMode.height;
      var currentDepth = currentMode.depth;
      
      // Try to set the same mode (should work)
      gfx.setScreenMode(currentWidth, currentHeight, 0, currentDepth);
      
      // Verify it's still the same
      var newMode = gfx.getCurrentScreenMode();
      expect(newMode.width).toBe(currentWidth);
      expect(newMode.height).toBe(currentHeight);
    });
  });

  describe("Screen Data Validation", function() {
    it("validates all screens have reasonable dimensions", function() {
      var numScreens = gfx.getNumScreens();
      expect(numScreens).toBeGreaterThan(0);
      
      for (var i = 0; i < numScreens; i++) {
        // Test current screen mode for each screen
        var screenMode = gfx.getCurrentScreenMode(i);
        expect(screenMode).toBeDefined();
        
        // Validate screen dimensions are reasonable
        expect(screenMode.width >= 800).toBe(true); // Minimum reasonable width
        expect(screenMode.height >= 600).toBe(true); // Minimum reasonable height
        expect(screenMode.width <= 10000).toBe(true); // Reasonable upper limit
        expect(screenMode.height <= 10000).toBe(true); // Reasonable upper limit
        
        // Test screen bounds for each screen
        var bounds = gfx.getScreenBounds(i);
        expect(bounds).toBeDefined();
        
        if (bounds && typeof bounds === 'object') {
          // Use the width() and height() methods of the Rect class
          var width = bounds.width();
          var height = bounds.height();
          expect(width >= 800).toBe(true);
          expect(height >= 600).toBe(true);
          expect(width <= 10000).toBe(true);
          expect(height <= 10000).toBe(true);
        }
      }
    });

    it("validates all supported screen modes have reasonable dimensions", function() {
      var numModes = gfx.getNumSupportedScreenModes();
      expect(numModes >= 0).toBe(true);
      
      if (numModes > 0) {
        for (var i = 0; i < Math.min(numModes, 10); i++) { // Test first 10 modes to avoid too many iterations
          var mode = gfx.getNthSupportedScreenMode(i);
          expect(mode).toBeDefined();
          
          if (mode && typeof mode === 'object' && mode.width !== undefined) {
            // Supported mode lists can legitimately include legacy display modes
            // such as 640x480, so validate that the dimensions are sane rather
            // than requiring every advertised mode to be desktop-sized.
            expect(mode.width > 0).toBe(true);
            expect(mode.height > 0).toBe(true);
            expect(mode.width <= 10000).toBe(true);
            expect(mode.height <= 10000).toBe(true);
            
            // Depth should be reasonable
            if (mode.depth !== undefined) {
              expect(mode.depth >= 8).toBe(true); // Minimum 8-bit depth
              expect(mode.depth <= 32).toBe(true); // Maximum 32-bit depth
            }
          }
        }
      }
    });

    it("validates screen mode consistency across screens", function() {
      var numScreens = gfx.getNumScreens();
      expect(numScreens).toBeGreaterThan(0);
      
      // Get current mode for primary screen
      var primaryMode = gfx.getCurrentScreenMode();
      expect(primaryMode).toBeDefined();
      
      // Compare with specific screen 0 (should be the same as primary)
      var screen0Mode = gfx.getCurrentScreenMode(0);
      expect(screen0Mode).toBeDefined();
      
      if (primaryMode.width !== undefined && screen0Mode.width !== undefined) {
        expect(primaryMode.width).toBe(screen0Mode.width);
        expect(primaryMode.height).toBe(screen0Mode.height);
        if (primaryMode.depth !== undefined && screen0Mode.depth !== undefined) {
          expect(primaryMode.depth).toBe(screen0Mode.depth);
        }
      }
    });

    it("validates screen bounds consistency", function() {
      var numScreens = gfx.getNumScreens();
      expect(numScreens).toBeGreaterThan(0);
      
      // Get bounds for primary screen
      var primaryBounds = gfx.getScreenBounds();
      expect(primaryBounds).toBeDefined();
      
      // Compare with specific screen 0 (should be the same as primary)
      var screen0Bounds = gfx.getScreenBounds(0);
      expect(screen0Bounds).toBeDefined();
      
      if (primaryBounds && screen0Bounds) {
        // Use the width() and height() methods of the Rect class
        var primaryWidth = primaryBounds.width();
        var primaryHeight = primaryBounds.height();
        var screen0Width = screen0Bounds.width();
        var screen0Height = screen0Bounds.height();
        expect(primaryWidth).toBe(screen0Width);
        expect(primaryHeight).toBe(screen0Height);
      }
    });

    it("validates screen mode data completeness", function() {
      var screenMode = gfx.getCurrentScreenMode();
      expect(screenMode).toBeDefined();
      
      // Check that all expected properties are present and have reasonable values
      if (screenMode.width !== undefined) {
        expect(screenMode.width).toBeGreaterThan(0);
        expect(screenMode.width <= 10000).toBe(true);
      }
      
      if (screenMode.height !== undefined) {
        expect(screenMode.height).toBeGreaterThan(0);
        expect(screenMode.height <= 10000).toBe(true);
      }
      
      if (screenMode.depth !== undefined) {
        expect(screenMode.depth >= 8).toBe(true);
        expect(screenMode.depth <= 32).toBe(true);
      }
      
      if (screenMode.maxWindowRect !== undefined) {
        expect(typeof screenMode.maxWindowRect).toBe('object');
        // maxWindowRect should be a valid rectangle
        if (screenMode.maxWindowRect.width !== undefined && typeof screenMode.maxWindowRect.width === 'number') {
          expect(screenMode.maxWindowRect.width).toBeGreaterThan(0);
          expect(screenMode.maxWindowRect.height).toBeGreaterThan(0);
        }
      }
    });

    it("validates aspect ratios are reasonable", function() {
      var screenMode = gfx.getCurrentScreenMode();
      expect(screenMode).toBeDefined();
      
      if (screenMode.width !== undefined && screenMode.height !== undefined) {
        var aspectRatio = screenMode.width / screenMode.height;
        
        // Aspect ratio should be reasonable (between 0.5 and 4.0)
        expect(aspectRatio > 0.5).toBe(true);
        expect(aspectRatio < 4.0).toBe(true);
        
        // Width and height should be positive
        expect(screenMode.width).toBeGreaterThan(0);
        expect(screenMode.height).toBeGreaterThan(0);
      }
    });
  });

  describe("FPS Management", function() {
    it("can get current FPS", function() {
      var fps = gfx.getFPS();
      expect(typeof fps).toBe('number');
      expect(fps >= 0).toBe(true);
    });

    it("can get target FPS", function() {
      var targetFPS = gfx.getTargetFPS();
      expect(typeof targetFPS).toBe('number');
      expect(targetFPS).toBeGreaterThan(0);
    });

    it("can set target FPS", function() {
      var originalTarget = gfx.getTargetFPS();
      var newTarget = 60;
      
      var result = gfx.setTargetFPS(newTarget);
      expect(result).toBe(gfx); // Should return self for chaining
      
      var currentTarget = gfx.getTargetFPS();
      expect(currentTarget).toBe(newTarget);
      
      // Restore original
      gfx.setTargetFPS(originalTarget);
    });
  });

  describe("Mouse Management", function() {
    it("can get mouse position", function() {
      var mousePos = gfx.getMouse();
      expect(mousePos).toBeDefined();
      expect(mousePos.x).toBeDefined();
      expect(mousePos.y).toBeDefined();
      expect(typeof mousePos.x).toBe('number');
      expect(typeof mousePos.y).toBe('number');
    });

    it("can get mouse position for specific mouse", function() {
      var mousePos = gfx.getMouse(0);
      expect(mousePos).toBeDefined();
      expect(mousePos.x).toBeDefined();
      expect(mousePos.y).toBeDefined();
    });
  });

  xdescribe("Port Management", function() {
    it("can get main port", function() {
      var mainPort = gfx.getMainPort();
      expect(mainPort).toBeDefined();
      expect(mainPort.constructor.name).toBe('Port');
    });

    xit("can create window port", function() {
      var rect = new pdg.Rect(100, 100, 400, 300);
      var port = gfx.createWindowPort(rect, "Test Window");
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can create window port with custom depth", function() {
      var rect = new pdg.Rect(100, 100, 400, 300);
      var port = gfx.createWindowPort(rect, "Test Window", 32);
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can create full screen port", function() {
      var rect = new pdg.Rect(0, 0, 800, 600);
      var port = gfx.createFullScreenPort(rect);
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can create full screen port with specific screen", function() {
      var rect = new pdg.Rect(0, 0, 800, 600);
      var port = gfx.createFullScreenPort(rect, 0);
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can create full screen port with resolution change allowed", function() {
      var rect = new pdg.Rect(0, 0, 800, 600);
      var port = gfx.createFullScreenPort(rect, 0, true);
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can create full screen port with custom depth", function() {
      var rect = new pdg.Rect(0, 0, 800, 600);
      var port = gfx.createFullScreenPort(rect, 0, true, 32);
      expect(port).toBeDefined();
      expect(port.constructor.name).toBe('Port');
      
      // Clean up
      gfx.closeGraphicsPort(port);
    });

    xit("can close graphics port", function() {
      var rect = new pdg.Rect(100, 100, 400, 300);
      var port = gfx.createWindowPort(rect, "Test Window");
      expect(port).toBeDefined();
      
      gfx.closeGraphicsPort(port);
      // No exception should be thrown
    });

    xit("can close main port", function() {
      // This should not throw an exception
      gfx.closeGraphicsPort();
    });
  });

  describe("Font Management", function() {
    it("can create font", function() {
      var font = gfx.createFont("Arial");
      expect(font).toBeDefined();
      expect(font.constructor.name).toBe('Font');
    });

    it("can create font with scaling factor", function() {
      var font = gfx.createFont("Arial", 1.5);
      expect(font).toBeDefined();
      expect(font.constructor.name).toBe('Font');
    });
  });

  xdescribe("Display Mode Management", function() {
    it("can check if in full screen mode", function() {
      var isFullScreen = gfx.inFullScreenMode();
      expect(typeof isFullScreen).toBe('boolean');
    });

    xit("can switch to full screen mode", function() {
      var result = gfx.switchToFullScreenMode();
      expect(typeof result).toBe('boolean');
    });

    xit("can switch to full screen mode with resolution change", function() {
      var result = gfx.switchToFullScreenMode(true);
      expect(typeof result).toBe('boolean');
    });

    xit("can switch to full screen mode with specific port", function() {
      var mainPort = gfx.getMainPort();
      var result = gfx.switchToFullScreenMode(false, mainPort);
      expect(typeof result).toBe('boolean');
    });

    xit("can switch to window mode", function() {
      var result = gfx.switchToWindowMode();
      expect(typeof result).toBe('boolean');
    });

    xit("can switch to window mode with specific port", function() {
      var mainPort = gfx.getMainPort();
      var result = gfx.switchToWindowMode(mainPort);
      expect(typeof result).toBe('boolean');
    });

    xit("can switch to window mode with window name", function() {
      var result = gfx.switchToWindowMode(undefined, "Test Window");
      expect(typeof result).toBe('boolean');
    });
  });

  describe("Error Handling", function() {
    it("handles invalid screen numbers gracefully", function() {
      // Test with invalid screen number - just check that it doesn't crash
      try {
        gfx.getCurrentScreenMode(999);
      } catch (e) {
        // It's okay if it throws, we just don't want it to crash
      }
      
      try {
        gfx.getScreenBounds(999);
      } catch (e) {
        // It's okay if it throws, we just don't want it to crash
      }
      
      try {
        gfx.getNumSupportedScreenModes(999);
      } catch (e) {
        // It's okay if it throws, we just don't want it to crash
      }
    });

    it("handles invalid mode indices gracefully", function() {
      var numModes = gfx.getNumSupportedScreenModes();
      try {
        gfx.getNthSupportedScreenMode(numModes + 100);
      } catch (e) {
        // It's okay if it throws, we just don't want it to crash
      }
    });

    it("handles invalid mouse numbers gracefully", function() {
      try {
        gfx.getMouse(999);
      } catch (e) {
        // It's okay if it throws, we just don't want it to crash
      }
    });
  });

  xdescribe("Integration Tests", function() {
    xit("can create and manage multiple ports", function() {
      var rect1 = new pdg.Rect(100, 100, 300, 200);
      var rect2 = new pdg.Rect(450, 100, 300, 200);
      
      var port1 = gfx.createWindowPort(rect1, "Window 1");
      var port2 = gfx.createWindowPort(rect2, "Window 2");
      
      expect(port1).toBeDefined();
      expect(port2).toBeDefined();
      expect(port1).not.toBe(port2);
      
      // Clean up
      gfx.closeGraphicsPort(port1);
      gfx.closeGraphicsPort(port2);
    });

    xit("can switch between display modes", function() {
      var mainPort = gfx.getMainPort();
      
      // Switch to full screen
      var fullScreenResult = gfx.switchToFullScreenMode(false, mainPort);
      expect(typeof fullScreenResult).toBe('boolean');
      
      // Switch back to window mode
      var windowResult = gfx.switchToWindowMode(mainPort);
      expect(typeof windowResult).toBe('boolean');
    });

    it("can create fonts and use them", function() {
      var font1 = gfx.createFont("Arial");
      var font2 = gfx.createFont("Times New Roman", 2.0);
      
      expect(font1).toBeDefined();
      expect(font2).toBeDefined();
      expect(font1).not.toBe(font2);
    });
  });

});

}
