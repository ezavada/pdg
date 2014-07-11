// -----------------------------------------------
// timermanager.spec.js
//
// test suite for TimerManager
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

describe("TimerManager", function() {

  it("is a singleton accessed by pdg.tm", function() {
	console.log('* Testing TimerManager...');
  	var tm = pdg.tm;
	expect(tm).toBeDefined();
	var tm2 = pdg.getTimerManager();
	expect(tm2).toBe(tm);
  });

	var fireCount;
	var firedId;
	var startMs;
	var elapsedMs;
	
	var fired = function(evt) {
		fireCount++;
		firedId = evt.id;
		elapsedMs = evt.msElapsed;
	}

	beforeEach(function() {
		pdg.tm.cancelAllTimers();
		startMs = pdg.tm.getMilliseconds();
		fireCount = 0;
		firedId = 0;
		elapsedMs = 0;
	});

  it("can create a one-shot timer", function() {
  	var t = pdg.tm.onTimeout(fired, 1);
  	expect(t.timer).toBeDefined();
  	expect(t.timer).not.toBe(0);

	waitsFor(function() {
		return (fireCount > 0);
	}, "the timer to fire", 1000);
  	
	runs(function() {
		var deltaMs = pdg.tm.getMilliseconds() - startMs;
  		expect(fireCount).toEqual(1);
  		expect(firedId).toEqual(t.timer);
  		expect(elapsedMs).toBeLessThan(5);
  		expect(elapsedMs).toBeGreaterThan(0);
  	});

  });

  it("can create a repeating timer", function() {
  	var t = pdg.tm.onInterval(fired, 1);
  	expect(t.timer).toBeDefined();
  	expect(t.timer).not.toBe(0);

	waitsFor(function() {
		return (fireCount > 5);
	}, "the timer to fire", 1000);
  	
	runs(function() {
		var deltaMs = pdg.tm.getMilliseconds() - startMs;
  		expect(fireCount).toBeGreaterThan(5);
  		expect(firedId).toEqual(t.timer);
  		expect(elapsedMs).toBeLessThan(5);
  		expect(elapsedMs).toBeGreaterThan(0);
  	});

  });

});
