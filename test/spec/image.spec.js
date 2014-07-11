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

  it("exists", function() {
	console.log('* Testing Image...');
	expect(pdg.Image).toBeDefined();
  });

  var gBallImage;
  var gBallHalf;

  it("can load an image from a file", function() {
	gBallImage = new pdg.Image('./yinyang.png');
	expect(gBallImage).toBeDefined();
  });
 
  it("has height and width", function() {
	expect(gBallImage.getHeight()).toEqual(64);
	expect(gBallImage.getWidth()).toEqual(64);
  });

  it("can read pixels", function() {
	var c1 = gBallImage.getPixel(16, 16);
	var c2 = gBallImage.getPixel(48, 48);
	expect(c1.red).toEqual(1);
	expect(c1.green).toEqual(1);
	expect(c1.blue).toEqual(1);
	expect(c1.alpha).toEqual(1);
	expect(c2.red).toEqual(0);
	expect(c2.green).toEqual(0);
	expect(c2.blue).toEqual(0);
	expect(c2.alpha).toEqual(1);
	expect(gBallImage.getAlphaValue(0,0)).toEqual(0);
	expect(gBallImage.getAlphaValue(16,16)).toEqual(255);
  });

  it("can create an image from a subsection of another", function() {
  	var r = new pdg.Rect(32, 64);
  	gBallHalf = gBallImage.getSubsection(r);
	expect(gBallHalf).toBeDefined();
	
	var c1 = gBallImage.getPixel(16, 16);
	var c2 = gBallImage.getPixel(48, 48);
	expect(c1.red).toEqual(1);
	expect(c1.green).toEqual(1);
	expect(c1.blue).toEqual(1);
	expect(c1.alpha).toEqual(1);
	expect(c2.red).toEqual(0);
	expect(c2.green).toEqual(0);
	expect(c2.blue).toEqual(0);
	expect(c2.alpha).toEqual(1);

	expect(gBallHalf.getHeight()).toEqual(64);
	expect(gBallHalf.getWidth()).toEqual(32);
  });

});