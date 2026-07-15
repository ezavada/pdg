// -----------------------------------------------
// color.js
//
// Definitions for rgb color
//
// Written by Ed Zavada, 2004-2012
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

// this is one of the few javascript files that are built-in
// to the pdg standalone app but also part of the pure 
// javascript implementation


var colorNames = new Array(
	"aliceblue", "antiquewhite", "aqua", "aquamarine", "azure", "beige", "bisque", "black",
	"blanchedalmond", "blue", "blueviolet", "brown", "burlywood", "cadetblue", "chartreuse",
	"chocolate", "coral", "cornflowerblue", "cornsilk", "crimson", "cyan", "darkblue",
	"darkcyan", "darkgoldenrod", "darkgray", "darkgreen", "darkgrey", "darkkhaki",
	"darkmagenta", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon",
	"darkseagreen", "darkslateblue", "darkslategray", "darkslategrey", "darkturquoise",
	"darkviolet", "deeppink", "deepskyblue", "dimgray", "dimgrey", "dodgerblue",
	"firebrick", "floralwhite", "forestgreen", "fuchsia", "gainsboro", "ghostwhite",
	"gold", "goldenrod", "gray", "green", "greenyellow", "grey", "honeydew", "hotpink",
	"indianred", "indigo", "ivory", "khaki", "lavender", "lavenderblush", "lawngreen",
	"lemonchiffon", "lightblue", "lightcoral", "lightcyan", "lightgoldenrodyellow",
	"lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen",
	"lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow",
	"lime", "limegreen", "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue",
	"mediumorchid", "mediumpurple", "mediumseagreen", "mediumslateblue", "mediumspringgreen",
	"mediumturquoise", "mediumvioletred", "midnightblue", "mintcream", "mistyrose",
	"moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange",
	"orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred",
	"papayawhip", "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red",
	"rosybrown", "royalblue", "saddlebrown", "salmon", "sandybrown", "seagreen",
	"seashell", "sienna", "silver", "skyblue", "slateblue", "slategray", "slategrey",
	"snow", "springgreen", "steelblue", "tan", "teal", "thistle", "tomato", "turquoise",
	"violet", "wheat", "white", "whitesmoke", "yellow", "yellowgreen"
);
var colorValues = new Array(
	0xf0f8ff, 0xfaebd7, 0x00ffff, 0x7fffd4, 0xf0ffff, 0xf5f5dc, 0xffe4c4, 0x000000,
	0xffebcd, 0x0000ff, 0x8a2be2, 0xa52a2a, 0xdeb887, 0x5f9ea0, 0x7fff00, 0xd2691e,
	0xff7f50, 0x6495ed, 0xfff8dc, 0xdc143c, 0x00ffff, 0x00008b, 0x008b8b, 0xb8860b,
	0xa9a9a9, 0x006400, 0xa9a9a9, 0xbdb76b, 0x8b008b, 0x556b2f, 0xff8c00, 0x9932cc,
	0x8b0000, 0xe9967a, 0x8fbc8f, 0x483d8b, 0x2f4f4f, 0x2f4f4f, 0x00ced1, 0x9400d3,
	0xff1493, 0x00bfff, 0x696969, 0x696969, 0x1e90ff, 0xb22222, 0xfffaf0, 0x228b22,
	0xff00ff, 0xdcdcdc, 0xf8f8ff, 0xffd700, 0xdaa520, 0x808080, 0x008000, 0xadff2f,
	0x808080, 0xf0fff0, 0xff69b4, 0xcd5c5c, 0x4b0082, 0xfffff0, 0xf0e68c, 0xe6e6fa,
	0xfff0f5, 0x7cfc00, 0xfffacd, 0xadd8e6, 0xf08080, 0xe0ffff, 0xfafad2, 0xd3d3d3,
	0x90ee90, 0xd3d3d3, 0xffb6c1, 0xffa07a, 0x20b2aa, 0x87cefa, 0x778899, 0x778899,
	0xb0c4de, 0xffffe0, 0x00ff00, 0x32cd32, 0xfaf0e6, 0xff00ff, 0x800000, 0x66cdaa,
	0x0000cd, 0xba55d3, 0x9370db, 0x3cb371, 0x7b68ee, 0x00fa9a, 0x48d1cc, 0xc71585,
	0x000080, 0xf5fffa, 0xffe4e1, 0xffe4b5, 0xffdead, 0x000080, 0xfdf5e6, 0x808000,
	0x6b8e23, 0xffa500, 0xff4500, 0xda70d6, 0xeee8aa, 0x98fb98, 0xafeeee, 0xdb7093,
	0xffefd5, 0xffdab9, 0xcd853f, 0xffc0cb, 0xdda0dd, 0xb0e0e6, 0x800080, 0xff0000,
	0xbc8f8f, 0x4169e1, 0x8b4513, 0xfa8072, 0xf4a460, 0x2e8b57, 0xfff5ee, 0xa0522d,
	0xc0c0c0, 0x87ceeb, 0x6a5acd, 0x708090, 0x708090, 0xfffafa, 0x00ff7f, 0x4682b4,
	0xd2b48c, 0x008080, 0xd8bfd8, 0xff6347, 0x40e0d0, 0xee82ee, 0xf5deb3, 0xffffff,
	0xf5f5f5, 0xffff00, 0x9acd32
);

// -----------------------------------------------------------------------------------
// Color
// -----------------------------------------------------------------------------------
// An RGB Color with alpha

class Color {
	//! new Color() create black
	//! new Color(c): create a color from a single 32 bit value
	//! new Color(name): create a color from a css color name
	//! new Color(r, g, b): create a color
	//! new Color(r, g, b, a): create a color with alpha
	constructor(ir, ig, ib, ia) {
			if (arguments.length == 1) {
				var c = ir;
				if (ir instanceof String || typeof(ir) == "string") {
					if (ir[0] == '#') {
						// convert string with #hhhhhh or #hhh (css style) value
						var red = 0, green = 0, blue = 0;
						if (ir.length == 4) {  // 4 char str
							red = parseInt(ir[1], 16);
							green = parseInt(ir[2], 16);
							blue = parseInt(ir[3], 16);
							red = (red << 4) | red;
							green = (green << 4) | green;
							blue = (blue << 4) | blue;
						} else if (ir.length == 7) { // 7 char str
							red = parseInt(ir.substr(1, 2), 16);
							green = parseInt(ir.substr(3, 2), 16);
							blue = parseInt(ir.substr(5, 2), 16);
						} else {
							throw("Color from String must be: '#rgb', '#rrggbb', or css color name" );
						}
						c = (red << 16) | (green << 8) | blue | 0xff000000;
					} else {
						//look up the color from the name
						c = 0;
						var found = false;
						for (var i = 0; i < colorNames.length; i++) {
							if (ir == colorNames[i]) {
								c = colorValues[i] | 0xff000000;
								found = true;
								break;
							}
						}
						if (!found) {
							throw("Invalid color name \"" + ir + "\". Valid names are: " + colorNames);
						}
					}
				}
				this.alpha = ((c>>24)&0xff)/255.0;
				this.red = ((c>>16)&0xff)/255.0; 
				this.green = ((c>>8)&0xff)/255.0; 
				this.blue = (c&0xff)/255.0; 
			} else {
				// Check if all RGB values are integers and any are above 1
				// If so, normalize all values from 0-255 range to 0.0-1.0 range
				var isInteger = function(val) {
					return val === Math.floor(val);
				};
				
				var shouldNormalize = isInteger(ir) && isInteger(ig) && isInteger(ib) && 
					(ir > 1 || ig > 1 || ib > 1);
				
				var normalize = function(val) {
					if (val === undefined || val === null) return 0;
					return shouldNormalize ? val / 255.0 : val;
				};
				
				this.red = normalize(ir);
				this.green = normalize(ig);
				this.blue = normalize(ib);
				// Alpha defaults to 1.0 if not provided
				this.alpha = (ia !== undefined && ia !== null) ? normalize(ia) : 1.0;
			}
		}
	// operators
	//! return true if this point is equal to the other
	equals(color) {
			if ((arguments.length == 1) && (arguments[0] == null)) { 
				return methodSignature("return true if this color is equal to the other (ignoring alpha)", arguments, "boolean", 1, "([object Color] color)");
			}
			return ((this.red == color.red) && (this.green == color.green) && (this.blue == color.blue));
		}
	notEquals(color) {
			if ((arguments.length == 1) && (arguments[0] == null)) { 
				return methodSignature("return true if this color is not equal to the other (ignoring alpha)", arguments, "boolean", 1, "([object Color] color)");
			}
			return ((this.red != color.red) || (this.green != color.green) || (this.blue != color.blue));
		}
	assign(color) {
			if ((arguments.length == 1) && (arguments[0] == null)) { 
				return methodSignature("set this color equal to the given color", arguments, "[object Color]", 1, "([object Color] color)");
			}
			this.alpha = color.alpha; 
			this.red = color.red; 
			this.green = color.green;
			this.blue = color.blue;
			return this;
		}
	convertToGrayscale() {
			if ((arguments.length == 1) && (arguments[0] == null)) { 
				return methodSignature("convert this color to a matching shade of grey", arguments, "undefined", 0, "()");
			}
			var v = (this.red + this.green + this.blue)/3; 
			this.red = v;
			this.green = v;
			this.blue = v;
		}
	toString() {
			return "Color("+this.red+","+this.green+","+this.blue+")";
		}
}


if(!(typeof exports === 'undefined')) {
    exports.Color = Color;
}
