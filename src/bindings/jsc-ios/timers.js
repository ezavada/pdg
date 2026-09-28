// -----------------------------------------------
// timers.js
//
// Modified version of Node.js' timers module for use with JavaScriptCore
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// Copyright Joyent, Inc. and other Node contributors.
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

// js2c embeds native modules by basename, so this source is registered as
// "linkedlist" rather than Node's filesystem-style "internal/linkedlist".
var L = require('linkedlist');
var assert = require('assert').ok;

// Timeout values > TIMEOUT_MAX are set to 1.
var TIMEOUT_MAX = 2147483647; // 2^31-1

var debug;
if (process.env.NODE_DEBUG && /timer/.test(process.env.NODE_DEBUG)) {
  debug = function(msg) { console.error(msg); };
} else {
  debug = function(msg) { };
}
debug("== TIMER LOADED ==");

var pdg = require('pdg');

// Kept separate from application-created PDG timer IDs so public bulk timer
// operations cannot cancel or pause the JavaScript runtime scheduler itself.
var nextRuntimeTimerId = 0x7e000000;
var runtimeTimers = Object.create(null);

// Route every runtime timer through one native event handler. Creating one
// IEventHandler per short-lived setTimeout permanently protected thousands of
// callback functions during long Jasmine runs and eventually destabilized JSC
// garbage collection.
var runtimeTimerHandler = pdg.onTimer(function(evt) {
	var timer = runtimeTimers[evt.id];
	if (!timer) return false;
	timer._OnTimeout();
	return true;
});

var Timer = function() {
	this._tid = nextRuntimeTimerId++;
	runtimeTimers[this._tid] = this;
};

Timer.prototype._OnTimeout = function() {
    this.ontimeout();
}

Timer.prototype.close = function() {
	this.stop();
	delete runtimeTimers[this._tid];
}

Timer.prototype.ref = function() {
    debug("node Timer.ref() for timer "+this._tid + (this._repeat ? " (repeating)" : ""));
}

Timer.prototype.start = function(timeout, repeat) {
	this._repeat = !!repeat;
    this._timeout = timeout;
	pdg.tm.startTimer(this._tid, timeout, !this._repeat);
    debug("Started Node Timer "+this._tid + (this._repeat ? " (repeating)" : ""));
    pdg.run(); // it is safe to call this multiple times
}

Timer.prototype.stop = function() {
    debug("Stopping Node Timer "+this._tid + (this._repeat ? " (repeating)" : ""));
    pdg.tm.cancelTimer(this._tid);
}

Timer.prototype.setRepeat = function(repeat) {
    debug("node Timer.setRepeat() for timer "+this._tid + (this._repeat ? " (repeating)" : ""));
    if (this._tid) {
        if (this._repeat != repeat) {
            pdg.tm.cancelTimer(this._tid);
        }
        this.start(this._timeout, repeat);
    }
}

Timer.prototype.getRepeat = function() {
    return this._repeat;
}

Timer.prototype.unref = function() {
    debug("node Timer.unref() for timer "+this._tid + (this._repeat ? " (repeating)" : ""));
}

Timer.prototype.again = function() {
    debug("node Timer.again() for timer "+this._tid + (this._repeat ? " (repeating)" : ""));
    if (!this._repeat) {
        this.start(this._timeout, false);
    }
}

// IDLE TIMEOUTS
//
// Because often many sockets will have the same idle timeout we will not
// use one timeout watcher per item. It is too much overhead.  Instead
// we'll use a single watcher for all sockets with the same timeout value
// and a linked list. This technique is described in the libev manual:
// http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod#Be_smart_about_timeouts

// Object containing all lists, timers
// key = time in milliseconds
// value = list
var lists = {};

// the main function - creates lists on demand and the watchers associated
// with them.
function insert(item, msecs) {
  item._idleStart = Date.now();
  item._idleTimeout = msecs;

  if (msecs < 0) return;

  var list;

  if (lists[msecs]) {
    list = lists[msecs];
  } else {
    list = new Timer();
    list.start(msecs, 0);

    L.init(list);

    lists[msecs] = list;
    list.msecs = msecs;
    list.ontimeout = listOnTimeout;
  }

  L.append(list, item);
  assert(!L.isEmpty(list)); // list is not empty
}

function listOnTimeout() {
  var msecs = this.msecs;
  var list = this;

  debug('timeout callback ' + msecs);

  var now = Date.now();
  debug('now: ' + now);

  var first;
  while (first = L.peek(list)) {
    var diff = now - first._idleStart;
    if (diff < msecs) {
      // A callback can append the next timeout to this same list. Its
      // _idleStart is newer than the `now` captured above, producing a
      // negative diff; that means it is newly scheduled, not overdue.
      var remaining = diff < 0 ? msecs : msecs - diff;
      list.start(remaining, 0);
      debug(msecs + ' list wait because diff is ' + diff);
      return;
    } else {
      L.remove(first);
      assert(first !== L.peek(list));

      if (!first._onTimeout) continue;

      // v0.4 compatibility: if the timer callback throws and the
      // domain or uncaughtException handler ignore the exception,
      // other timers that expire on this tick should still run.
      //
      // https://github.com/joyent/node/issues/2631
//      var domain = first.domain;
//      if (domain && domain._disposed) continue;
      try {
//        if (domain)
//          domain.enter();
        var threw = true;
        first._onTimeout();
//        if (domain)
//          domain.exit();
        threw = false;
      } finally {
        if (threw) {
          process.nextTick(function() {
            list.ontimeout();
          });
        }
      }
    }
  }

  debug(msecs + ' list empty');
  assert(L.isEmpty(list));
  list.close();
  delete lists[msecs];
}


var unenroll = exports.unenroll = function(item) {
  L.remove(item);

  var list = lists[item._idleTimeout];
  // if empty then stop the watcher
  debug('unenroll');
  if (list && L.isEmpty(list)) {
    debug('unenroll: list empty');
    list.close();
    delete lists[item._idleTimeout];
  }
  // if active is called later, then we want to make sure not to insert again
  item._idleTimeout = -1;
};


// Does not start the time, just sets up the members needed.
exports.enroll = function(item, msecs) {
  // if this item was already in a list somewhere
  // then we should unenroll it from that
  if (item._idleNext) unenroll(item);

  // Ensure that msecs fits into signed int32
  if (msecs > 0x7fffffff) {
    msecs = 0x7fffffff;
  }

  item._idleTimeout = msecs;
  L.init(item);
};


// call this whenever the item is active (not idle)
// it will reset its timeout.
exports.active = function(item) {
  var msecs = item._idleTimeout;
  if (msecs >= 0) {

    var list = lists[msecs];
    if (!list || L.isEmpty(list)) {
      insert(item, msecs);
    } else {
      item._idleStart = Date.now();
      L.append(list, item);
    }
  }
};


//
// * DOM-style timers
//


exports.setTimeout = function(callback, after) {
  var timer;

  after *= 1; // coalesce to number or NaN

  if (!(after >= 1 && after <= TIMEOUT_MAX)) {
    after = 1; // schedule on next tick, follows browser behaviour
  }

  timer = new Timeout(after);

  if (arguments.length <= 2) {
    timer._onTimeout = callback;
  } else {
    //
//      * Sometimes setTimeout is called with arguments, EG
//      *
//      *   setTimeout(callback, 2000, "hello", "world")
//      *
//      * If that's the case we need to call the callback with
//      * those args. The overhead of an extra closure is not
//      * desired in the normal case.
     //
    var args = Array.prototype.slice.call(arguments, 2);
    timer._onTimeout = function() {
      callback.apply(timer, args);
    }
  }

//  if (process.domain) timer.domain = process.domain;

  exports.active(timer);

  return timer;
};


exports.clearTimeout = function(timer) {
  if (timer && (timer.ontimeout || timer._onTimeout)) {
    timer.ontimeout = timer._onTimeout = null;
    if (timer instanceof Timeout) {
      timer.close(); // for after === 0
    } else {
      exports.unenroll(timer);
    }
  }
};

exports.setInterval = function(callback, repeat) {
  repeat *= 1; // coalesce to number or NaN

  if (!(repeat >= 1 && repeat <= TIMEOUT_MAX)) {
    repeat = 1; // schedule on next tick, follows browser behaviour
  }

  var timer = new Timeout(repeat);
  var args = Array.prototype.slice.call(arguments, 2);
  timer._onTimeout = wrapper;
  timer._repeat = true;

//  if (process.domain) timer.domain = process.domain;
  exports.active(timer);

  return timer;

  function wrapper() {
    callback.apply(this, args);
    // If callback called clearInterval().
    if (timer._repeat === false) return;
    // If timer is unref'd (or was - it's permanently removed from the list.)
    if (this._handle) {
      this._handle.start(repeat, 0);
    } else {
      timer._idleTimeout = repeat;
      exports.active(timer);
    }
  }
};


exports.clearInterval = function(timer) {
  if (timer && timer._repeat) {
    timer._repeat = false;
    clearTimeout(timer);
  }
};


var Timeout = function(after) {
  this._idleTimeout = after;
  this._idlePrev = this;
  this._idleNext = this;
  this._idleStart = null;
  this._onTimeout = null;
  this._repeat = false;
};

Timeout.prototype.unref = function() {
  if (!this._handle) {
    var now = Date.now();
    if (!this._idleStart) this._idleStart = now;
    var delay = this._idleStart + this._idleTimeout - now;
    if (delay < 0) delay = 0;
    exports.unenroll(this);
    this._handle = new Timer();
    this._handle.ontimeout = this._onTimeout;
    this._handle.start(delay, 0);
    this._handle.domain = this.domain;
    this._handle.unref();
  } else {
    this._handle.unref();
  }
};

Timeout.prototype.ref = function() {
  if (this._handle)
    this._handle.ref();
};

Timeout.prototype.close = function() {
  this._onTimeout = null;
  if (this._handle) {
    this._handle.ontimeout = null;
    this._handle.close();
  } else {
    exports.unenroll(this);
  }
};


var immediateQueue = {};
L.init(immediateQueue);


function processImmediate() {
  var immediate = L.shift(immediateQueue);

  if (L.isEmpty(immediateQueue)) {
    process._needImmediateCallback = false;
  }

  if (immediate._onImmediate) {
//    if (immediate.domain) immediate.domain.enter();

    immediate._onImmediate();

//    if (immediate.domain) immediate.domain.exit();
  }
}


exports.setImmediate = function(callback) {
  var immediate = {}, args;

  L.init(immediate);

  immediate._onImmediate = callback;

  if (arguments.length > 1) {
    args = Array.prototype.slice.call(arguments, 1);

    immediate._onImmediate = function() {
      callback.apply(immediate, args);
    };
  }

  if (!process._needImmediateCallback) {
    process._needImmediateCallback = true;
    process._immediateCallback = processImmediate;
  }

//  if (process.domain) immediate.domain = process.domain;

  L.append(immediateQueue, immediate);

  return immediate;
};


exports.clearImmediate = function(immediate) {
  if (!immediate) return;

  immediate._onImmediate = undefined;

  L.remove(immediate);

  if (L.isEmpty(immediateQueue)) {
    process._needImmediateCallback = false;
  }
};


// Internal APIs that need timeouts should use timers._unrefActive instead of
// timers.active as internal timeouts shouldn't hold the loop open

var unrefList, unrefTimer;


function unrefTimeout() {
  var now = Date.now();

  debug('unrefTimer fired');

  var first;
  while (first = L.peek(unrefList)) {
    var diff = now - first._idleStart;

    if (diff < first._idleTimeout) {
      diff = first._idleTimeout - diff;
      unrefTimer.start(diff, 0);
      unrefTimer.when = now + diff;
      debug('unrefTimer rescheudling for later');
      return;
    }

    L.remove(first);

//    var domain = first.domain;

    if (!first._onTimeout) continue;
//    if (domain && domain._disposed) continue;

    try {
//      if (domain) domain.enter();
      var threw = true;
      debug('unreftimer firing timeout');
      first._onTimeout();
      threw = false;
//      if (domain) domain.exit();
    } finally {
      if (threw) process.nextTick(unrefTimeout);
    }
  }

  debug('unrefList is empty');
  unrefTimer.when = -1;
}


exports._unrefActive = function(item) {
  var msecs = item._idleTimeout;
  if (!msecs || msecs < 0) return;
  assert(msecs >= 0);

  L.remove(item);

  if (!unrefList) {
    debug('unrefList initialized');
    unrefList = {};
    L.init(unrefList);

    debug('unrefTimer initialized');
    unrefTimer = new Timer();
    unrefTimer.unref();
    unrefTimer.when = -1;
    unrefTimer.ontimeout = unrefTimeout;
  }

  var now = Date.now();
  item._idleStart = now;

  if (L.isEmpty(unrefList)) {
    debug('unrefList empty');
    L.append(unrefList, item);

    unrefTimer.start(msecs, 0);
    unrefTimer.when = now + msecs;
    debug('unrefTimer scheduled');
    return;
  }

  var when = now + msecs;

  debug('unrefList find where we can insert');

  var cur, them;

  for (cur = unrefList._idlePrev; cur != unrefList; cur = cur._idlePrev) {
    them = cur._idleStart + cur._idleTimeout;

    if (when < them) {
      debug('unrefList inserting into middle of list');

      L.append(cur, item);

      if (unrefTimer.when > when) {
        debug('unrefTimer is scheduled to fire too late, reschedule');
        unrefTimer.start(msecs, 0);
        unrefTimer.when = when;
      }

      return;
    }
  }

  debug('unrefList append to end');
  L.append(unrefList, item);
};
