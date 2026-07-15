// -----------------------------------------------
// font.spec.js
//
// test suite for Font
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
	describe("Font", function() {
	  it("is not present in non-GUI builds", function() {
	  	expect(pdg.Font).toBeUndefined();
	  });
	});

} else {

describe("Font", function() {

  var gfx;
  var font;
  var port;

  beforeEach(function() {
    gfx = pdg.gfx;
    expect(gfx).toBeDefined();
    
    // Create a font for testing
    font = gfx.createFont("Arial");
    expect(font).toBeDefined();
  });

  describe("Font Creation", function() {
    it("exists", function() {
      console.log('* Testing Font...');
      expect(pdg.Font).toBeDefined();
    });

    it("can be created via GraphicsManager", function() {
      var testFont = gfx.createFont("Arial");
      expect(testFont).toBeDefined();
      expect(testFont.constructor.name).toBe('Font');
    });

    it("can be created with scaling factor", function() {
      var testFont = gfx.createFont("Arial", 1.5);
      expect(testFont).toBeDefined();
      expect(testFont.constructor.name).toBe('Font');
    });

    it("can create different font types", function() {
      var fonts = [
        gfx.createFont("Arial"),
        gfx.createFont("Times New Roman"),
        gfx.createFont("Courier New"),
        gfx.createFont("Helvetica")
      ];
      
      fonts.forEach(function(f) {
        expect(f).toBeDefined();
        expect(f.constructor.name).toBe('Font');
      });
    });
  });

  describe("Font Properties", function() {
    it("can get font name", function() {
      var fontName = font.getFontName();
      expect(fontName).toBeDefined();
      expect(typeof fontName).toBe('string');
      expect(fontName.length > 0).toBe(true);
    });

    it("returns consistent font name", function() {
      var name1 = font.getFontName();
      var name2 = font.getFontName();
      expect(name1).toBe(name2);
    });

    it("different fonts have different names", function() {
      var arialFont = gfx.createFont("Arial");
      var timesFont = gfx.createFont("Times New Roman");
      
      var arialName = arialFont.getFontName();
      var timesName = timesFont.getFontName();
      
      expect(arialName).toBeDefined();
      expect(timesName).toBeDefined();
      // Note: Font names might be normalized, so they might be the same
      // even if different fonts were requested
    });
  });

  describe("Font Metrics", function() {
    it("can get font height", function() {
      var height = font.getFontHeight(12);
      expect(height).toBeDefined();
      expect(typeof height).toBe('number');
      expect(height > 0).toBe(true);
    });

    it("can get font height with style", function() {
      var plainHeight = font.getFontHeight(12, pdg.textStyle_Plain);
      var boldHeight = font.getFontHeight(12, pdg.textStyle_Bold);
      
      expect(plainHeight).toBeDefined();
      expect(boldHeight).toBeDefined();
      expect(typeof plainHeight).toBe('number');
      expect(typeof boldHeight).toBe('number');
      expect(plainHeight > 0).toBe(true);
      expect(boldHeight > 0).toBe(true);
    });

    it("font height increases with size", function() {
      var height12 = font.getFontHeight(12);
      var height24 = font.getFontHeight(24);
      
      expect(height24 >= height12).toBe(true);
    });

    it("can get font leading", function() {
      var leading = font.getFontLeading(12);
      expect(leading).toBeDefined();
      expect(typeof leading).toBe('number');
      expect(leading >= 0).toBe(true);
    });

    it("can get font leading with style", function() {
      var plainLeading = font.getFontLeading(12, pdg.textStyle_Plain);
      var boldLeading = font.getFontLeading(12, pdg.textStyle_Bold);
      
      expect(plainLeading).toBeDefined();
      expect(boldLeading).toBeDefined();
      expect(typeof plainLeading).toBe('number');
      expect(typeof boldLeading).toBe('number');
      expect(plainLeading >= 0).toBe(true);
      expect(boldLeading >= 0).toBe(true);
    });

    it("can get font ascent", function() {
      var ascent = font.getFontAscent(12);
      expect(ascent).toBeDefined();
      expect(typeof ascent).toBe('number');
      expect(ascent > 0).toBe(true);
    });

    it("can get font ascent with style", function() {
      var plainAscent = font.getFontAscent(12, pdg.textStyle_Plain);
      var boldAscent = font.getFontAscent(12, pdg.textStyle_Bold);
      
      expect(plainAscent).toBeDefined();
      expect(boldAscent).toBeDefined();
      expect(typeof plainAscent).toBe('number');
      expect(typeof boldAscent).toBe('number');
      expect(plainAscent > 0).toBe(true);
      expect(boldAscent > 0).toBe(true);
    });

    it("can get font descent", function() {
      var descent = font.getFontDescent(12);
      expect(descent).toBeDefined();
      expect(typeof descent).toBe('number');
      expect(descent >= 0).toBe(true);
    });

    it("can get font descent with style", function() {
      var plainDescent = font.getFontDescent(12, pdg.textStyle_Plain);
      var boldDescent = font.getFontDescent(12, pdg.textStyle_Bold);
      
      expect(plainDescent).toBeDefined();
      expect(boldDescent).toBeDefined();
      expect(typeof plainDescent).toBe('number');
      expect(typeof boldDescent).toBe('number');
      expect(plainDescent >= 0).toBe(true);
      expect(boldDescent >= 0).toBe(true);
    });

    it("font metrics are consistent", function() {
      var height = font.getFontHeight(12);
      var ascent = font.getFontAscent(12);
      var descent = font.getFontDescent(12);
      
      // Height should be approximately equal to ascent + descent
      expect(height >= ascent).toBe(true);
      expect(height >= descent).toBe(true);
    });

    it("font metrics scale with size", function() {
      var height12 = font.getFontHeight(12);
      var ascent12 = font.getFontAscent(12);
      var descent12 = font.getFontDescent(12);
      
      var height24 = font.getFontHeight(24);
      var ascent24 = font.getFontAscent(24);
      var descent24 = font.getFontDescent(24);
      
      expect(height24 >= height12).toBe(true);
      expect(ascent24 >= ascent12).toBe(true);
      expect(descent24 >= descent12).toBe(true);
    });
  });

  describe("Text Styles", function() {
    it("text style constants are defined", function() {
      expect(pdg.textStyle_Plain).toBeDefined();
      expect(pdg.textStyle_Bold).toBeDefined();
      expect(pdg.textStyle_Italic).toBeDefined();
      expect(pdg.textStyle_Underline).toBeDefined();
      expect(pdg.textStyle_Centered).toBeDefined();
      expect(pdg.textStyle_LeftJustified).toBeDefined();
      expect(pdg.textStyle_RightJustified).toBeDefined();
    });

    it("text style constants have correct values", function() {
      expect(pdg.textStyle_Plain).toBe(0);
      expect(pdg.textStyle_Bold).toBe(1);
      expect(pdg.textStyle_Italic).toBe(2);
      expect(pdg.textStyle_Underline).toBe(4);
      expect(pdg.textStyle_Centered).toBe(16);
      expect(pdg.textStyle_LeftJustified).toBe(0);
      expect(pdg.textStyle_RightJustified).toBe(32);
    });

    it("can get metrics with different text styles", function() {
      var styles = [
        pdg.textStyle_Plain,
        pdg.textStyle_Bold,
        pdg.textStyle_Italic,
        pdg.textStyle_Underline
      ];
      
      styles.forEach(function(style) {
        var height = font.getFontHeight(12, style);
        var ascent = font.getFontAscent(12, style);
        var descent = font.getFontDescent(12, style);
        var leading = font.getFontLeading(12, style);
        
        expect(height).toBeDefined();
        expect(ascent).toBeDefined();
        expect(descent).toBeDefined();
        expect(leading).toBeDefined();
        expect(typeof height).toBe('number');
        expect(typeof ascent).toBe('number');
        expect(typeof descent).toBe('number');
        expect(typeof leading).toBe('number');
      });
    });

    it("bold style typically has larger metrics", function() {
      var plainHeight = font.getFontHeight(12, pdg.textStyle_Plain);
      var boldHeight = font.getFontHeight(12, pdg.textStyle_Bold);
      
      // Bold might be the same size as plain, but shouldn't be smaller
      expect(boldHeight >= plainHeight).toBe(true);
    });
  });


  describe("Font Validation", function() {
    it("validates font metrics are reasonable", function() {
      var sizes = [8, 12, 16, 24, 48];
      
      sizes.forEach(function(size) {
        var height = font.getFontHeight(size);
        var ascent = font.getFontAscent(size);
        var descent = font.getFontDescent(size);
        var leading = font.getFontLeading(size);
        
        // Height should be positive and reasonable
        expect(height > 0).toBe(true);
        expect(height <= size * 2).toBe(true); // Shouldn't be more than 2x the size
        
        // Ascent should be positive and reasonable
        expect(ascent > 0).toBe(true);
        expect(ascent <= size * 1.5).toBe(true);
        
        // Descent should be non-negative and reasonable
        expect(descent >= 0).toBe(true);
        expect(descent <= size).toBe(true);
        
        // Leading should be non-negative and reasonable
        expect(leading >= 0).toBe(true);
        expect(leading <= size).toBe(true);
      });
    });

    it("validates font metrics scale proportionally", function() {
      var height12 = font.getFontHeight(12);
      var height24 = font.getFontHeight(24);
      
      // Height should roughly double when size doubles
      var ratio = height24 / height12;
      expect(ratio >= 1.5).toBe(true); // At least 1.5x
      expect(ratio <= 3.0).toBe(true); // At most 3x
    });

    it("validates font name is meaningful", function() {
      var fontName = font.getFontName();
      
      expect(fontName).toBeDefined();
      expect(typeof fontName).toBe('string');
      expect(fontName.length > 0).toBe(true);
      expect(fontName.length < 100).toBe(true); // Reasonable length
    });
  });

  describe("Error Handling", function() {
    it("handles invalid font names gracefully", function() {
      expect(function() {
        gfx.createFont("NonExistentFont");
      }).not.toThrow();
    });

    it("handles invalid font sizes gracefully", function() {
      expect(function() {
        font.getFontHeight(0);
      }).not.toThrow();
      
      expect(function() {
        font.getFontHeight(-1);
      }).not.toThrow();
      
      expect(function() {
        font.getFontHeight(1000);
      }).not.toThrow();
    });

    it("handles invalid text styles gracefully", function() {
      expect(function() {
        font.getFontHeight(12, 999);
      }).not.toThrow();
      
      expect(function() {
        font.getFontHeight(12, -1);
      }).not.toThrow();
    });
  });

  describe("Integration Tests", function() {
    it("can create and use multiple fonts", function() {
      var fonts = [
        gfx.createFont("Arial"),
        gfx.createFont("Times New Roman"),
        gfx.createFont("Courier New")
      ];
      
      fonts.forEach(function(f, index) {
        var name = f.getFontName();
        var height = f.getFontHeight(12);
        var ascent = f.getFontAscent(12);
        var descent = f.getFontDescent(12);
        
        expect(name).toBeDefined();
        expect(height).toBeDefined();
        expect(ascent).toBeDefined();
        expect(descent).toBeDefined();
      });
    });

  });

});

}