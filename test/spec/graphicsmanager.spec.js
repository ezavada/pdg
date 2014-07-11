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

  it("is a singleton accessed by pdg.gfx", function() {
	console.log('* Testing GraphicsManager...');
  	var gfx = pdg.gfx;
	expect(gfx).toBeDefined();
	var gfx2 = pdg.getGraphicsManager();
	expect(gfx2).toBe(gfx);
  });


});

}