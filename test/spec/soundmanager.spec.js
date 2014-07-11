// -----------------------------------------------
// soundmanager.spec.js
//
// test suite for SoundManager
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

if (pdg.hasSound == false) {

	// non-graphics build (ie: node plugin)
	describe("SoundManager", function() {
	  it("is not present in this build", function() {
	  	expect(pdg.snd).toBeUndefined();
	  	expect(pdg.getSoundManager).toBeUndefined();
	  });
	});

} else {

describe("SoundManager", function() {

  it("is a singleton accessed by pdg.snd", function() {
	console.log('* Testing SoundManager...');
  	var snd = pdg.snd;
	expect(snd).toBeDefined();
	var snd2 = pdg.getSoundManager();
	expect(snd2).toBe(snd);
  });



});

}