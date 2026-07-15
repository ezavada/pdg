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
	var firedAtMs;
	var previousFiredAtMs;
	
	var fired = function(evt) {
		previousFiredAtMs = firedAtMs;
		firedAtMs = evt.millisec;
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
		firedAtMs = 0;
		previousFiredAtMs = 0;
	});

  it("can create a one-shot timer", function() {
  	var t = pdg.tm.onTimeout(fired, 1);
  	expect(t.timer).toBeDefined();
  	expect(t.timer).not.toBe(0);

	waitsFor(function() {
		return (fireCount > 0);
	}, "the timer to fire", 1000);
  	
	runs(function() {
		var deltaMs = firedAtMs - startMs;
  		expect(fireCount).toEqual(1);
  		expect(firedId).toEqual(t.timer);
  		expect(elapsedMs).toBeGreaterThan(0);
  		expect(Math.abs(deltaMs - elapsedMs)).toBeLessThan(20);
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
		var intervalMs = firedAtMs - previousFiredAtMs;
  		expect(fireCount).toBeGreaterThan(5);
  		expect(firedId).toEqual(t.timer);
  		expect(elapsedMs).toBeGreaterThan(0);
  		expect(intervalMs).toBeGreaterThan(0);
  		expect(Math.abs(intervalMs - elapsedMs)).toBeLessThan(5);
  	});

  });

  // ============================================================================
  // Tests for TimerManager functionality from within timer event handlers
  // ============================================================================

  describe("TimerManager functionality from within timer handlers", function() {

    beforeEach(function() {
      pdg.tm.cancelAllTimers();
      pdg.idle(); // Allow any pending timer cancellations to process
      startMs = pdg.tm.getMilliseconds();
      fireCount = 0;
      firedId = 0;
      elapsedMs = 0;
    });

    it("can cancel itself from within its own handler", function() {
      var selfCancelCount = 0;
      var t = pdg.tm.onInterval(function(evt) {
        selfCancelCount++;
        if (selfCancelCount === 1) {
          // Cancel this timer from within its own handler
          pdg.tm.cancelTimer(evt.id);
        }
      }, 10);

      waitsFor(function() {
        return (selfCancelCount >= 1);
      }, "the timer to fire and cancel itself", 1000);

      runs(function() {
        expect(selfCancelCount).toEqual(1);
        // Verify the timer was actually canceled by waiting a bit longer
        // It should not fire again
        var countAfterCancel = selfCancelCount;
        setTimeout(function() {
          expect(selfCancelCount).toEqual(countAfterCancel);
        }, 100);
      });
    });

    it("can delay itself from within its own handler", function() {
      var delayCount = 0;
      var originalFireTime = 0;
      var delayedFireTime = 0;
      
      var t = pdg.tm.onInterval(function(evt) {
        delayCount++;
        if (delayCount === 1) {
          originalFireTime = pdg.tm.getMilliseconds();
          // Delay this timer by 50ms from within its own handler
          pdg.tm.delayTimer(evt.id, 50);
        } else if (delayCount === 2) {
          delayedFireTime = pdg.tm.getMilliseconds();
        }
      }, 20);

      waitsFor(function() {
        return (delayCount >= 2);
      }, "the timer to fire, delay itself, and fire again", 2000);

      runs(function() {
        expect(delayCount).toBeGreaterThan(1);
        expect(delayedFireTime - originalFireTime).toBeGreaterThan(50);
      });
    });

    it("can delay itself until a specific time from within its own handler", function() {
      var delayUntilCount = 0;
      var originalFireTime = 0;
      var delayedFireTime = 0;
	  var targetFireTime = 0;
      
      var t = pdg.tm.onInterval(function(evt) {
        delayUntilCount++;
        if (delayUntilCount === 1) {
          originalFireTime = pdg.tm.getMilliseconds();
          // Delay this timer until 100ms from now
		  targetFireTime = pdg.tm.getMilliseconds() + 100;
          pdg.tm.delayTimerUntil(evt.id, targetFireTime);
        } else if (delayUntilCount === 2) {
          delayedFireTime = pdg.tm.getMilliseconds();
        }
      }, 20);

      waitsFor(function() {
        return (delayUntilCount >= 2);
      }, "the timer to fire, delay itself until specific time, and fire again", 2000);

      runs(function() {
        expect(delayUntilCount).toBeGreaterThan(1);
		expect(targetFireTime).toBe(originalFireTime + 100);
        // The timer should fire at or after the target time
        expect(delayedFireTime).toBeGreaterThan(targetFireTime - 1);
      });
    });

    it("can pause itself from within its own handler", function() {
      var pauseCount = 0;
      var t = pdg.tm.onInterval(function(evt) {
        pauseCount++;
        if (pauseCount === 1) {
          // Pause this timer from within its own handler
          pdg.tm.pauseTimer(evt.id);
        }
      }, 10);

      waitsFor(function() {
        return (pauseCount >= 1);
      }, "the timer to fire and pause itself", 1000);

      runs(function() {
        expect(pauseCount).toEqual(1);
        expect(pdg.tm.isTimerPaused(t.timer)).toBe(true);
        
        // Unpause and verify it fires again
        pdg.tm.unpauseTimer(t.timer);
        
        waitsFor(function() {
          return (pauseCount >= 2);
        }, "the timer to fire again after unpausing", 1000);
        
        runs(function() {
          expect(pauseCount).toBeGreaterThan(1);
        });
      });
    });

    it("can restart itself from within its own handler", function() {
      var restartCount = 0;
      var t = pdg.tm.onInterval(function(evt) {
        restartCount++;
        if (restartCount === 1) {
          // Restart this timer with a different interval from within its own handler
          pdg.tm.startTimer(evt.id, 50, false); // 50ms interval instead of original
        }
      }, 10);

      waitsFor(function() {
        return (restartCount >= 2);
      }, "the timer to fire, restart itself, and fire again", 2000);

      runs(function() {
        expect(restartCount).toBeGreaterThan(1);
        // The second fire should have a longer interval due to the restart
      });
    });

    it("can cancel other timers from within a timer handler", function() {
      var mainTimerCount = 0;
      var otherTimerCount = 0;
      
      // Create a timer that will cancel another timer
      var mainTimer = pdg.tm.onInterval(function(evt) {
        mainTimerCount++;
        if (mainTimerCount === 1) {
          // Cancel the other timer from within this timer's handler
          pdg.tm.cancelTimer(otherTimer.timer);
        }
      }, 30);

      // Create another timer that should be canceled
      var otherTimer = pdg.tm.onInterval(function(evt) {
        otherTimerCount++;
      }, 10);

      waitsFor(function() {
        return (mainTimerCount >= 1);
      }, "the main timer to fire and cancel the other timer", 1000);

      runs(function() {
        expect(mainTimerCount).toBeGreaterThan(0);
        // The other timer might fire a few times before being canceled
        expect(otherTimerCount).toBeLessThan(5);
        
        // Wait a bit more to ensure the other timer doesn't fire again
        setTimeout(function() {
          pdg.idle(); // Process any remaining events
          expect(otherTimerCount).toBeLessThan(5);
        }, 100);
      });
    });

    it("can delay other timers from within a timer handler", function() {
      var mainTimerCount = 0;
      var otherTimerCount = 0;
      var otherTimerOriginalTime = 0;
      var otherTimerDelayedTime = 0;
      
      // Create a timer that will delay another timer
      var mainTimer = pdg.tm.onInterval(function(evt) {
        mainTimerCount++;
        if (mainTimerCount === 1) {
          // Delay the other timer from within this timer's handler
          pdg.tm.delayTimer(otherTimer.timer, 100);
        }
      }, 30);

      // Create another timer that should be delayed
      var otherTimer = pdg.tm.onInterval(function(evt) {
        otherTimerCount++;
        if (otherTimerCount === 1) {
          otherTimerOriginalTime = pdg.tm.getMilliseconds();
        } else if (otherTimerCount === 2) {
          otherTimerDelayedTime = pdg.tm.getMilliseconds();
        }
      }, 20);

      waitsFor(function() {
        return (otherTimerCount >= 2);
      }, "the other timer to fire, be delayed, and fire again", 2000);

      runs(function() {
        expect(mainTimerCount).toBeGreaterThan(0);
        expect(otherTimerCount).toBeGreaterThan(1);
        expect(otherTimerDelayedTime - otherTimerOriginalTime).toBeGreaterThan(100);
      });
    });

    it("can pause all timers from within a timer handler", function() {
      var timer1Count = 0;
      var timer2Count = 0;
      
      // Create a timer that will pause all timers
      var timer1 = pdg.tm.onInterval(function(evt) {
        timer1Count++;
        if (timer1Count === 1) {
          // Pause all timers from within this timer's handler
          pdg.tm.pause();
        }
      }, 20);

      // Create another timer that should be paused
      var timer2 = pdg.tm.onInterval(function(evt) {
        timer2Count++;
      }, 20);

      waitsFor(function() {
        return (timer1Count >= 1);
      }, "the first timer to fire and pause all timers", 1000);

      runs(function() {
        expect(timer1Count).toBeGreaterThan(0);
        expect(pdg.tm.isPaused()).toBe(true);
        expect(pdg.tm.isTimerPaused(timer1.timer)).toBe(true);
        expect(pdg.tm.isTimerPaused(timer2.timer)).toBe(true);
        
        // Unpause and verify timers fire again
        pdg.tm.unpause();
        
        waitsFor(function() {
          return (timer1Count >= 2 || timer2Count >= 2);
        }, "timers to fire again after unpausing", 1000);
        
        runs(function() {
          expect(timer1Count + timer2Count).toBeGreaterThan(2);
        });
      });
    });

    it("can cancel all timers from within a timer handler", function() {
      var timer1Count = 0;
      var timer2Count = 0;
      
      // Create a timer that will cancel all timers
      var timer1 = pdg.tm.onInterval(function(evt) {
        timer1Count++;
        if (timer1Count === 1) {
          // Cancel all timers from within this timer's handler
          pdg.tm.cancelAllTimers();
        }
      }, 20);

      // Create another timer that should be canceled
      var timer2 = pdg.tm.onInterval(function(evt) {
        timer2Count++;
      }, 20);

      waitsFor(function() {
        return (timer1Count >= 1);
      }, "the first timer to fire and cancel all timers", 1000);

      runs(function() {
        expect(timer1Count).toBeGreaterThan(0);
        // The other timer might fire a few times before being canceled
        expect(timer2Count).toBeLessThan(5);
        
        // Wait a bit more to ensure no timers fire again
        setTimeout(function() {
          pdg.idle(); // Process any remaining events
          expect(timer1Count + timer2Count).toBeLessThan(7);
        }, 100);
      });
    });

    it("can create new timers from within a timer handler", function() {
      var originalTimerCount = 0;
      var newTimerCount = 0;
      
      // Create a timer that will create another timer
      var originalTimer = pdg.tm.onInterval(function(evt) {
        originalTimerCount++;
        if (originalTimerCount === 1) {
          // Create a new timer from within this timer's handler
          var newTimer = pdg.tm.onInterval(function(newEvt) {
            newTimerCount++;
          }, 10);
        }
      }, 30);

      waitsFor(function() {
        return (newTimerCount >= 2);
      }, "the original timer to fire, create a new timer, and the new timer to fire multiple times", 2000);

      runs(function() {
        expect(originalTimerCount).toBeGreaterThan(0);
        expect(newTimerCount).toBeGreaterThan(1);
      });
    });

    it("can modify timer properties from within its own handler", function() {
      var modifyCount = 0;
      var originalInterval = 20;
      var modifiedInterval = 50;
      
      var t = pdg.tm.onInterval(function(evt) {
        modifyCount++;
        if (modifyCount === 1) {
          // Modify this timer's interval from within its own handler
          pdg.tm.startTimer(evt.id, modifiedInterval, false);
        }
      }, originalInterval);

      waitsFor(function() {
        return (modifyCount >= 2);
      }, "the timer to fire, modify itself, and fire again with new interval", 2000);

      runs(function() {
        expect(modifyCount).toBeGreaterThan(1);
        // The second fire should have the modified interval
      });
    });

    it("can chain multiple timer operations from within a handler", function() {
      var chainCount = 0;
      var otherTimerCount = 0;
      
      var otherTimer = pdg.tm.onInterval(function(evt) {
        otherTimerCount++;
      }, 20);
      
      var chainTimer = pdg.tm.onInterval(function(evt) {
        chainCount++;
        if (chainCount === 1) {
          // Perform multiple operations from within this timer's handler
          pdg.tm.delayTimer(evt.id, 30);        // Delay self
          pdg.tm.pauseTimer(otherTimer.timer);  // Pause other timer
          pdg.tm.startTimer(999, 40, true);     // Create new one-shot timer
        }
      }, 25);

      waitsFor(function() {
        return (chainCount >= 2);
      }, "the chain timer to fire, perform multiple operations, and fire again", 2000);

      runs(function() {
        expect(chainCount).toBeGreaterThan(1);
        expect(pdg.tm.isTimerPaused(otherTimer.timer)).toBe(true);
      });
    });

  });

  // ============================================================================
  // Tests for getWhenTimerFiresNext functionality
  // ============================================================================

  describe("getWhenTimerFiresNext functionality", function() {
    
    beforeEach(function() {
      pdg.tm.cancelAllTimers();
      pdg.idle(); // Advance time to ensure clean state
    });

    it("returns correct fire time for one-shot timers", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var delay = 50;
      var expectedFireTime = currentTime + delay;
      
      var t = pdg.tm.onTimeout(function(evt) {
        // Timer fired
      }, delay);
      
      var predictedFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Verify the predicted time is reasonable
      expect(predictedFireTime).toBeGreaterThan(currentTime);
      expect(predictedFireTime).toBeLessThan(currentTime + delay + 10); // Allow small variance
      expect(predictedFireTime).toBeGreaterThan(expectedFireTime - 10); // Allow small variance
      
    });

    it("returns correct fire time for interval timers", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var interval = 30;
      var expectedFireTime = currentTime + interval;
      
      var t = pdg.tm.onInterval(function(evt) {
        // Timer fired
      }, interval);
      
      var predictedFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Verify the predicted time is reasonable
      expect(predictedFireTime).toBeGreaterThan(currentTime);
      expect(predictedFireTime).toBeLessThan(currentTime + interval + 10);
      expect(predictedFireTime).toBeGreaterThan(expectedFireTime - 10);
      
    });

    it("returns updated fire time after delayTimer", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var originalDelay = 20;
      var additionalDelay = 30;
      
      var t = pdg.tm.onTimeout(function(evt) {
        // Timer fired
      }, originalDelay);
      
      var originalFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Delay the timer
      pdg.tm.delayTimer(t.timer, additionalDelay);
      
      var newFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Verify the new fire time is later
      expect(newFireTime).toBeGreaterThan(originalFireTime);
      expect(newFireTime).toBeGreaterThan(originalFireTime + additionalDelay - 5); // Allow small variance
    });

    it("returns updated fire time after delayTimerUntil", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var originalDelay = 20;
      var targetTime = currentTime + 100; // Target 100ms from now
      
      var t = pdg.tm.onTimeout(function(evt) {
        // Timer fired
      }, originalDelay);
      
      var originalFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Delay the timer until specific time
      pdg.tm.delayTimerUntil(t.timer, targetTime);
      
      var newFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Verify the new fire time matches the target time
      expect(newFireTime).toBe(targetTime);
    });

    it("returns timer_Never for non-existent timers", function() {
      var fireTime = pdg.tm.getWhenTimerFiresNext(99999); // Non-existent timer ID
      expect(fireTime).toBe(pdg.timer_Never);
    });

    it("returns correct fire time that matches actual firing time", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var delay = 40;
      var actualFireTime = 0;
      var predictedFireTime = 0;
      
      var t = pdg.tm.onTimeout(function(evt) {
        actualFireTime = pdg.tm.getMilliseconds();
      }, delay);
      
      predictedFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Wait for timer to fire
      waitsFor(function() {
        return (actualFireTime > 0);
      }, "the timer to fire", 1000);
      
      runs(function() {
        // Verify the predicted time is close to the actual fire time
        var timeDifference = Math.abs(actualFireTime - predictedFireTime);
        expect(timeDifference).toBeLessThan(20); // Allow some variance for timing
      });
    });

    it("handles large time values correctly (64-bit)", function() {
      var currentTime = pdg.tm.getMilliseconds();
      
      // Create a timer with a large delay to test 64-bit handling
      var largeDelay = 1000000; // 1 million milliseconds
      var t = pdg.tm.onTimeout(function(evt) {
        // Timer fired
      }, largeDelay);
      
      var predictedFireTime = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Verify the predicted time is much larger than current time
      expect(predictedFireTime).toBeGreaterThan(currentTime + largeDelay - 10);
      expect(predictedFireTime).toBeLessThan(currentTime + largeDelay + 10);
      
      // Cancel the timer to avoid long waits
      pdg.tm.cancelTimer(t.timer);
    });

    it("returns consistent values for paused timers", function() {
      var currentTime = pdg.tm.getMilliseconds();
      var interval = 25;
      
      var t = pdg.tm.onInterval(function(evt) {
        // Timer fired
      }, interval);
      
      var fireTime1 = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Pause the timer
      pdg.tm.pauseTimer(t.timer);
      
      var fireTime2 = pdg.tm.getWhenTimerFiresNext(t.timer);
      
      // Unpause the timer
      pdg.tm.unpauseTimer(t.timer);
      
      var fireTime3 = pdg.tm.getWhenTimerFiresNext(t.timer);
          
      // Verify paused timer returns timer_Never
      expect(fireTime2).toBe(pdg.timer_Never);
      
      // Verify the fire time doesn't change significantly during pause/unpause
      expect(Math.abs(fireTime1 - fireTime3)).toBeLessThan(50);
    });

  });

});
