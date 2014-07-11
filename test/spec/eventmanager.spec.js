// -----------------------------------------------
// eventmanager.spec.js
//
// test suite for EventManager
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

describe("EventManager", function() {

  it("is a singleton accessed by pdg.evt", function() {
	console.log('* Testing EventManager...');
  	var evt = pdg.evt;
	expect(evt).toBeDefined();
	var evt2 = pdg.getEventManager();
	expect(evt2).toBe(evt);
  });

  it("has getDeviceOrientation call", function() {
	expect(pdg.evt.getDeviceOrientation).toBeDefined();
	var orientation = pdg.evt.getDeviceOrientation();
	expect(orientation.roll).toBeDefined();
	expect(orientation.roll).toEqual(0);
	expect(orientation.pitch).toBeDefined();
	expect(orientation.pitch).toEqual(0);
	expect(orientation.yaw).toBeDefined();
	expect(orientation.yaw).toEqual(0);
  });

  it("has isButtonDown call", function() {
	expect(pdg.evt.isButtonDown).toBeDefined();
	var isDown = pdg.evt.isButtonDown();
	expect(isDown).toBe(false);
  });

  it("has isKeyDown call", function() {
	expect(pdg.evt.isKeyDown).toBeDefined();
	var isDown = pdg.evt.isKeyDown('a');
	expect(isDown).toBe(false);
	var isDown = pdg.evt.isKeyDown(pdg.key_Escape);
	expect(isDown).toBe(false);
  });

  it("has isRawKeyDown call", function() {
	expect(pdg.evt.isRawKeyDown).toBeDefined();
	var isDown = pdg.evt.isRawKeyDown(33);  // no idea what key this represents
	expect(isDown).toBe(false);
  });



});
