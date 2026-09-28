'use strict';

// Lightweight Node-compatible EventEmitter for the iOS JavaScriptCore host.
// This deliberately has no dependency on Node internals such as primordials,
// async_hooks, domains, or internal/errors.

function EventEmitter() {
  EventEmitter.init.call(this);
}

module.exports = EventEmitter;
module.exports.EventEmitter = EventEmitter;

EventEmitter.defaultMaxListeners = 10;

EventEmitter.init = function() {
  this._events = Object.create(null);
  this._eventsCount = 0;
  this._maxListeners = undefined;
};

EventEmitter.prototype.setMaxListeners = function(n) {
  if (typeof n !== 'number' || n < 0 || isNaN(n)) {
    throw new TypeError('n must be a non-negative number');
  }
  this._maxListeners = n;
  return this;
};

EventEmitter.prototype.getMaxListeners = function() {
  return this._maxListeners === undefined ?
    EventEmitter.defaultMaxListeners : this._maxListeners;
};

function addListener(emitter, type, listener, prepend) {
  if (typeof listener !== 'function') {
    throw new TypeError('listener must be a function');
  }

  if (!emitter._events) EventEmitter.init.call(emitter);
  if (emitter._events.newListener) {
    emitter.emit('newListener', type, listener.listener || listener);
  }

  var existing = emitter._events[type];
  if (!existing) {
    emitter._events[type] = listener;
    emitter._eventsCount++;
  } else if (typeof existing === 'function') {
    emitter._events[type] = prepend ? [listener, existing] : [existing, listener];
  } else if (prepend) {
    existing.unshift(listener);
  } else {
    existing.push(listener);
  }
  return emitter;
}

EventEmitter.prototype.addListener = function(type, listener) {
  return addListener(this, type, listener, false);
};
EventEmitter.prototype.on = EventEmitter.prototype.addListener;

EventEmitter.prototype.prependListener = function(type, listener) {
  return addListener(this, type, listener, true);
};

function onceWrapper() {
  if (!this.fired) {
    this.target.removeListener(this.type, this.wrapFn);
    this.fired = true;
    return this.listener.apply(this.target, arguments);
  }
}

function once(emitter, type, listener, prepend) {
  if (typeof listener !== 'function') {
    throw new TypeError('listener must be a function');
  }
  var state = { fired: false, target: emitter, type: type, listener: listener };
  var wrapped = onceWrapper.bind(state);
  wrapped.listener = listener;
  state.wrapFn = wrapped;
  return addListener(emitter, type, wrapped, prepend);
}

EventEmitter.prototype.once = function(type, listener) {
  return once(this, type, listener, false);
};

EventEmitter.prototype.prependOnceListener = function(type, listener) {
  return once(this, type, listener, true);
};

EventEmitter.prototype.emit = function(type) {
  var events = this._events;
  var handler = events && events[type];
  if (!handler) {
    if (type === 'error') {
      var error = arguments[1];
      throw error instanceof Error ? error : new Error('Unhandled error event: ' + error);
    }
    return false;
  }

  var args = Array.prototype.slice.call(arguments, 1);
  if (typeof handler === 'function') {
    handler.apply(this, args);
  } else {
    var listeners = handler.slice();
    for (var i = 0; i < listeners.length; i++) listeners[i].apply(this, args);
  }
  return true;
};

EventEmitter.prototype.removeListener = function(type, listener) {
  var events = this._events;
  if (!events) return this;
  var existing = events[type];
  if (!existing) return this;

  if (existing === listener || existing.listener === listener) {
    delete events[type];
    this._eventsCount--;
  } else if (typeof existing !== 'function') {
    for (var i = existing.length - 1; i >= 0; i--) {
      if (existing[i] === listener || existing[i].listener === listener) {
        existing.splice(i, 1);
        break;
      }
    }
    if (existing.length === 1) events[type] = existing[0];
    else if (existing.length === 0) {
      delete events[type];
      this._eventsCount--;
    }
  }

  if (events.removeListener) this.emit('removeListener', type, listener);
  return this;
};
EventEmitter.prototype.off = EventEmitter.prototype.removeListener;

EventEmitter.prototype.removeAllListeners = function(type) {
  if (!this._events) return this;
  if (arguments.length === 0) {
    this._events = Object.create(null);
    this._eventsCount = 0;
  } else if (this._events[type]) {
    delete this._events[type];
    this._eventsCount--;
  }
  return this;
};

EventEmitter.prototype.listeners = function(type) {
  var existing = this._events && this._events[type];
  if (!existing) return [];
  var list = typeof existing === 'function' ? [existing] : existing.slice();
  return list.map(function(listener) { return listener.listener || listener; });
};

EventEmitter.prototype.rawListeners = function(type) {
  var existing = this._events && this._events[type];
  if (!existing) return [];
  return typeof existing === 'function' ? [existing] : existing.slice();
};

EventEmitter.prototype.listenerCount = function(type) {
  var existing = this._events && this._events[type];
  return !existing ? 0 : (typeof existing === 'function' ? 1 : existing.length);
};

EventEmitter.listenerCount = function(emitter, type) {
  return emitter.listenerCount(type);
};

EventEmitter.prototype.eventNames = function() {
  return this._events ? Object.keys(this._events) : [];
};
