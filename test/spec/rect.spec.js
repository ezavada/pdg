// -----------------------------------------------
// rect.spec.js
//
// test suite for Rect
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

describe("Rect", function() {

  it("can be created with no params", function() {
  	var rect = new Rect();
	expect(rect.left).toBeDefined();
	expect(rect.left).toEqual(0);
	expect(rect.top).toBeDefined();
	expect(rect.top).toEqual(0);
	expect(rect.right).toBeDefined();
	expect(rect.right).toEqual(0);
	expect(rect.bottom).toBeDefined();
	expect(rect.bottom).toEqual(0);
	expect(rect.height()).toEqual(0);
	expect(rect.width()).toEqual(0);
	expect(rect.empty()).toEqual(true);
  });

});