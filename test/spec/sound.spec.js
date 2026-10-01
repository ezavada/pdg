// -----------------------------------------------
// sound.spec.js
//
// test suite for Sound
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
	describe("Sound", function() {
	  it("is not present in this build", function() {
	  	expect(pdg.Sound).toBeUndefined();
	  });
	});

} else {

describe("Sound", function() {

  it("exists", function() {
	console.log('* Testing Sound...');
	expect(pdg.Sound).toBeDefined();
  });


  it("retains a constructed sound across stop and replay", function() {
    var filename = 'data/clink1.mp3';
    expect(fs.existsSync(filename)).toBe(true);
    var sound;
    try {
      sound = new pdg.Sound(filename);
    } catch (error) {
      // DirectShow depends on optional system codecs. Keep the lifecycle test
      // meaningful where decoding is available without failing codec-less hosts.
      if (typeof process != 'undefined' && process.platform == 'win32' &&
          /could not create Sound from file/.test(String(error))) {
        jasmine.getEnv().currentSpec.results_.skipped = true;
        return;
      }
      throw error;
    }
    sound.start();
    sound.stop();
    sound.volume = 0.25;
    expect(sound.volume).toBeCloseTo(0.25, 3);
    sound.start();
    sound.stop();
    sound.setLooping(true);
    expect(sound.isLooping()).toBe(true);
  });



});

}
