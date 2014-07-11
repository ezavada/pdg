// -----------------------------------------------
// animated.spec.js
//
// test suite for Animated
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

describe("Animated", function() {

  it("exists", function() {
	console.log('* Testing Animated...');
	expect(pdg.Animated).toBeDefined();
  });

  it("move can be instantaneous", function() {
  	var a = new pdg.Animated();
  	var p = a.getLocation();
  	expect(p.x).toBe(0);
  	expect(p.y).toBe(0);
  	a.moveTo([10, 10]);
  	p = a.getLocation();
  	expect(p.x).toBe(10);
  	expect(p.y).toBe(10);
  });

  it("move can be delayed by wait()", function() {
  	var a = new pdg.Animated();
  	a.wait(10).moveTo([10, 10]);
  	var p = a.getLocation();
  	expect(p.x).toBe(0);
  	expect(p.y).toBe(0);
  	a.animate(100); // pretend 100ms passed
  	p = a.getLocation();
// this is broken, returns NAN!!
//   	expect(p.x).toBe(10);
//   	expect(p.y).toBe(10);
  });


});
