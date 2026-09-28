'use strict';

// Small, self-contained subset of Node's util module used by the iOS host.
// It intentionally avoids Node internal bindings and primordials.

exports.format = function(format) {
  if (typeof format !== 'string') {
    return Array.prototype.map.call(arguments, exports.inspect).join(' ');
  }

  var index = 1;
  var args = arguments;
  var result = format.replace(/%[sdj%]/g, function(token) {
    if (token === '%%') return '%';
    if (index >= args.length) return token;
    var value = args[index++];
    if (token === '%s') return String(value);
    if (token === '%d') return Number(value);
    try {
      return JSON.stringify(value);
    } catch (error) {
      return '[Circular]';
    }
  });

  while (index < args.length) {
    var value = args[index++];
    result += ' ' + (value !== null && typeof value === 'object' ?
      exports.inspect(value) : String(value));
  }
  return result;
};

exports.inspect = function(value) {
  var seen = [];

  function render(item, depth) {
    if (item === null) return 'null';
    if (typeof item === 'string') return "'" + item + "'";
    if (typeof item !== 'object') return String(item);
    if (seen.indexOf(item) !== -1) return '[Circular]';
    if (depth > 3) return Array.isArray(item) ? '[Array]' : '[Object]';

    seen.push(item);
    var keys = Object.keys(item);
    var parts = keys.map(function(key) {
      return key + ': ' + render(item[key], depth + 1);
    });
    seen.pop();
    return Array.isArray(item) ? '[ ' + parts.join(', ') + ' ]' :
      '{ ' + parts.join(', ') + ' }';
  }

  return render(value, 0);
};

exports.inherits = function(ctor, superCtor) {
  ctor.super_ = superCtor;
  ctor.prototype = Object.create(superCtor.prototype, {
    constructor: {
      value: ctor,
      enumerable: false,
      writable: true,
      configurable: true
    }
  });
};

exports._extend = function(target, source) {
  if (!source || typeof source !== 'object') return target;
  Object.keys(source).forEach(function(key) { target[key] = source[key]; });
  return target;
};
