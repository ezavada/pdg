// -----------------------------------------------
// color.spec.js
//
// test suite for Color
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

describe("Color", function() {

  it("can be created with no params", function() {
	console.log('* Testing Color...');
  	var color = new Color();
	expect(color.alpha).toEqual(1.0);
	expect(color.red).toBeDefined();
	expect(color.red).toEqual(0);
	expect(color.green).toBeDefined();
	expect(color.green).toEqual(0);
	expect(color.blue).toBeDefined();
	expect(color.blue).toEqual(0);
  });

  it("can be created with css color names", function() {
  	var names = ["aqua", "black", "blue", "fuchsia", 
		"gray", "grey", "green", "lime", "maroon", "navy", "olive", "purple", 
		"red", "silver", "teal", "white", "yellow"];
	for (var i = 0; i < names.length; i++) {
		var color = new Color(names[i]);
		expect(color.alpha).toEqual(1.0);
		expect(color.red).toBeDefined();
		expect(color.green).toBeDefined();
		expect(color.blue).toBeDefined();
	}
  });

  it("can be created with css #rgb values", function() {
  	var csscolors = ["#333", "#333333", "#aaa", "#AAA", 
		"#aaaaaa", "#AaAaAA"];
	for (var i = 0; i < csscolors.length; i++) {
		var color = new Color(csscolors[i]);
		expect(color.alpha).not.toEqual(0);
		expect(color.red).toBeDefined();
		expect(color.red).not.toEqual(0);
		expect(color.green).toBeDefined();
		expect(color.green).not.toEqual(0);
		expect(color.blue).toBeDefined();
		expect(color.blue).not.toEqual(0);
	}
  });

  it("can be created from 32 bit RGB color values", function() {
  	var colors = [0x7f303030, 92344532];
	for (var i = 0; i < colors.length; i++) {
		var color = new Color(colors[i]);
		expect(color.alpha).not.toEqual(0);
		expect(color.red).toBeDefined();
		expect(color.red).not.toEqual(0);
		expect(color.green).toBeDefined();
		expect(color.green).not.toEqual(0);
		expect(color.blue).toBeDefined();
		expect(color.blue).not.toEqual(0);
	}
  });

  it("can be tested for equal to another color", function() {
  	var colors = ["#ff0000", "red", "#000000", "black"];
	var red1 = new Color("#ff0000");
	var red2 = new Color("red");
	var black1 = new Color("#000000");
	var black2 = new Color("black");
	var green1 = new Color("#00ff00");
	var green2 = new Color("lime");
	var blue1 = new Color("#0000ff");
	var blue2 = new Color("blue");
	expect(red1.equals(red2)).toBeTruthy();
	expect(black1.equals(black2)).toBeTruthy();
	expect(green1.equals(green2)).toBeTruthy();
	expect(blue1.equals(blue2)).toBeTruthy();
	expect(blue1.equals(green1)).toBeFalsy();
	expect(red1.equals(black1)).toBeFalsy();
  });

});