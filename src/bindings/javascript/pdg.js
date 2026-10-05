// -----------------------------------------------
// pdg.js
//
// main include file for Javascript version of PDG
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

// Set up debug logging
_debug_log = function() {};
if (typeof process === 'object' && process.env && process.env.NODE_DEBUG && /pdg/.test(process.env.NODE_DEBUG)) {
  _debug_log = function(x) {
    console.error(x);
  };
}
_debug_log('[PDG] pdg.js: Module loaded');

var bindings;
var coordinates;
var embedded_pdg = (typeof process == "object") && (typeof process.pdg == "object");
var jsc = (typeof process == "object") && (typeof process.versions['jsc'] != "undefined");
var inbrowser = (typeof document != "undefined");
var netclient;
var netconnection;
var netserver;
var color;
var Module;

//console.log('[PDG] pdg.js: Starting - process.pdg available?', !!process.pdg);
//console.log('[PDG] pdg.js: process.pdg object identity:', process.pdg ? (void 0) : 'undefined');

if (embedded_pdg || jsc) {
	// special case for pdg embedded directly into custom standalone application
	// unfortunately, since we are using a linked binding, we can't use require here
	// for actual node.js modules.
	_debug_log('[PDG] pdg.js: Using embedded process.pdg');
	bindings = process.pdg;
	//console.log('[PDG] pdg.js: bindings === process.pdg?', bindings === process.pdg);
	methodSignature = require('dump').methodSignature;
	coordinates = require('coordinates');
	_debug_log('[PDG] pdg.js: Coordinates module loaded: ' + typeof coordinates);
	_debug_log('[PDG] pdg.js: coordinates.Quad: ' + typeof coordinates.Quad);
	color = require('color');
	_debug_log('[PDG] pdg.js: Color module loaded: ' + typeof color);
	_debug_log('[PDG] pdg.js: color.Color: ' + typeof color.Color);
    if (!jsc) {  // these don't work on JavaScriptCore/iOS yet
        netconnection = require('netconnection');
        netclient = require('netclient');
        netserver = require('netserver');
    }
	// DON'T delete process.pdg - we want to keep using it as our single source of truth
	Module = global.module; // || publicRequire('module');
} else if (inbrowser) {

    // running in a browser via emscripten
    // everything is crammed into a single binding called pdg_bind
    
    bindings = pdg_bind;
    coordinates = require('coordinates');
    color = require('color');
    
    // dump.js is embedded in our simulated file system
	methodSignature = require('dump').methodSignature;
	Module = require('module');
} else {
	// normal case, for pdg as a node JS add-on
	_debug_log('[PDG] pdg.js: Using normal node.js add-on approach');
	bindings = require('../build/Release/pdg');
	methodSignature = require('./dump').methodSignature;
	coordinates = require('./coordinates');
	color = require('./color');
	netconnection = require('./netconnection');
	netclient = require('./netclient');
	netserver = require('./netserver');
	Module = require('module');
}
_debug_log('[PDG] pdg.js: modules require complete');

// Browser builds provide a minimal process shim; initialize their shared
// binding namespace after environment detection so they are not mistaken
// for an embedded native runtime.
if (inbrowser) {
    process.pdg = bindings;
} else {
    process.pdg = process.pdg || {};
}

// Use process.pdg as our single source of truth
_debug_log('[PDG] pdg.js: process.pdg has getResourceManager? ' + typeof bindings.getResourceManager);

// Make sure process.pdg has all the bindings
if (bindings !== process.pdg) {
    _debug_log('[PDG] pdg.js: bindings !== process.pdg, copying properties');
    for (var key in bindings) {
        if (bindings.hasOwnProperty(key)) {
            process.pdg[key] = bindings[key];
        }
    }
} else {
    _debug_log('[PDG] pdg.js: bindings === process.pdg, no copying needed');
}

// Set global pdg to point to process.pdg
global.pdg = process.pdg;
_debug_log('[PDG] pdg.js: Set global.pdg to process.pdg');
_debug_log('[PDG] pdg.js: global.pdg === process.pdg? ' + (global.pdg === process.pdg));

// For debugging
bindings._debug_log = _debug_log;

// setup class hierarchy
bindings.EventManager.superclass = bindings.EventEmitter;
if (typeof bindings.Sound != "undefined") {  // might be non-gui build
	bindings.Sound.superclass = bindings.EventEmitter;
}
bindings.EventManager.superclass = bindings.EventEmitter;
bindings.TimerManager.superclass = bindings.EventEmitter;
if (bindings.Particle) bindings.Particle.superclass = [bindings.Animated, bindings.EventEmitter];
if (bindings.ParticleEmitter) bindings.ParticleEmitter.superclass = bindings.Animated;
bindings.Sprite.superclass = new Array( bindings.Animated, bindings.EventEmitter, bindings.ISerializable );
bindings.SpriteLayer.superclass = new Array( bindings.Animated, bindings.EventEmitter, bindings.ISerializable );
bindings.TileLayer.superclass = bindings.SpriteLayer;
bindings.ImageStrip.superclass = bindings.Image;


bindings.running = false;
bindings.quitting = false;

// Add a flag to track when pdg.run() is actively running
bindings._pdgRunLoopActive = false;
var performanceRunChannel = null;

bindings.quit = function() {
	var _sig = methodSignature("", arguments, "undefined", 0, "()"); if (_sig != null) return _sig;
	pdg._debug_log("bindings.quit");
	bindings.quitting = true;
	// Clear the run loop active flag when quitting
	bindings._pdgRunLoopActive = false;
}

bindings.run = function() {
	var _sig = methodSignature("", arguments, "undefined", 0, "()"); if (_sig != null) return _sig;
	if (!bindings.running) {
		bindings.__run();
	}
	bindings.running = true;
	// Set the run loop active flag
	bindings._pdgRunLoopActive = true;
}

bindings.__run = function() {
	if (!bindings.quitting && !bindings._isQuitting() ) {
		bindings.idle();
		if (inbrowser) {
			if (process.env.PDG_PERF_UNCAPPED === '1' && typeof MessageChannel === 'function') {
				// Quick benchmarks must not inherit the browser's nested-timer delay.
				// Yield between frames so input, painting and browser controls still run.
				if (!performanceRunChannel) {
					performanceRunChannel = new MessageChannel();
					performanceRunChannel.port1.onmessage = bindings.__run;
				}
				performanceRunChannel.port2.postMessage(null);
			} else {
				setTimeout(bindings.__run, 0);
			}
		} else {
			setImmediate(bindings.__run);
		}
	} else {
		if (performanceRunChannel) {
			performanceRunChannel.port1.close();
			performanceRunChannel.port2.close();
			performanceRunChannel = null;
		}
		bindings._quit();
		// Clear the run loop active flag when stopping
		bindings._pdgRunLoopActive = false;
		if (!inbrowser) {
			process.nextTick(process.exit);
		}
	}
}

bindings.idle = function() {
	var _sig = methodSignature("", arguments, "undefined", 0, "()"); if (_sig != null) return _sig;
//	pdg._debug_log("bindings.idle");
	bindings._idle();
}

if (!jsc && !inbrowser) {
    
    // debugger support
    var _debuggerRunning = false;
    //var exec = require('child_process').exec;
	//var path = require('path');
    
    bindings.openDebugger = function() {
		var exec = require('child_process').exec;
		var path = require('path');
		var _sig = methodSignature("start node-inspector and open a debugger window in your browser", 
                                   arguments, "undefined", 0, "()"); if (_sig != null) return _sig;
        if (!_debuggerRunning) {
            _debuggerRunning = true;
            process._debugProcess(process.pid);
            var child = exec('node-inspector --web-port=5859',
			  function (error, stdout, stderr) {
				pdg._debug_log('stdout: ' + stdout);
				pdg._debug_log('stderr: ' + stderr);
				if (error !== null) {
				  console.error('exec error: ' + error);
				}
				_debuggerRunning = false;
			  });
            var dir = path.dirname(process.execPath);
            var openCmd = 'open ';
            if (process.platform == 'win32') {
                openCmd = 'start ';
            }
            var openChild = exec(openCmd + path.join(dir, 'debug.html'), 
			  function (error, stdout, stderr) {
				pdg._debug_log('stdout: ' + stdout);
				pdg._debug_log('stderr: ' + stderr);
				if (error !== null) {
				  console.error('exec error: ' + error);
				}
			  });
        }
    }
    
    bindings._commandPort = 0;

    // console support
    bindings.openConsole = function() {
		var exec = require('child_process').exec;
		var path = require('path');
		var _sig = methodSignature("open a pdg console window", 
                arguments, "undefined", 0, "()"); if (_sig != null) return _sig;
                
        if (!bindings._commandPort) {
        	bindings.openCommandPort();
        }
		var dir = path.dirname(process.execPath);
		var pdg_dir = process.env['PDG_ROOT'];
		if (pdg_dir) {
			pdg_dir = path.join(pdg_dir, 'tools');
		}
		var repl_script;
		if (pdg_dir) {
			repl_script = path.join(pdg_dir, 'repl');
		}
		var nodeCmd = path.join(pdg_dir, 'node');
		nodeCmd += ' ' + repl_script + ' ' + bindings._commandPort;
		var openCmd;
		if (process.platform == 'darwin') {
			openCmd = 'osascript -e \'tell app "Terminal" to do script "'+nodeCmd+'"\'';
		} else if (process.platform == 'win32') {
			openCmd = 'start '+nodeCmd;
		} else {
			openCmd = 'xterm '+nodeCmd;
		}
		var openChild = exec(openCmd, 
		  function (error, stdout, stderr) {
			pdg._debug_log('stdout: ' + stdout);
			pdg._debug_log('stderr: ' + stderr);
			if (error !== null) {
			  console.error('exec error: ' + error);
			}
		  });
    }
    
    // net/stream stuff not working on JSC yet
	bindings.openCommandPort = function (port) {
        var _sig = methodSignature("start a REPL server on a TCP port", 
                arguments, "undefined", 0, "([number int] port = 5757)"); if (_sig != null) return _sig;

		if (typeof(port) == 'undefined') {
			port = 5757;
		}

		var opts = { prompt: 'pdg '+process.versions['pdg']+'> ', useGlobal: true, ignoreUndefined: true, terminal: true};
		var repl = require('net-repl');
		var srv = repl.createServer(opts).listen(port);
		// TODO: emit pdg welcome; expose same globals as running pdg to repl
		bindings._commandPort = port;
	}
} // end !jsc && !inbrowser

if (!inbrowser) {

// save the original version of require
bindings._base_require = require;

// The standalone JSC runtime loads the application's main script from the
// bundle after pdg.js has initialized. Compile that source through the JSC
// CommonJS module implementation so relative require() calls keep working.
if (jsc) {
	var JSCModule = bindings._base_require('module');

	bindings._loadScript = function(contents, file) {
		var loadedModule = new JSCModule(file, module);
		JSCModule._cache[file] = loadedModule;
		loadedModule.require = bindings._custom_require;
		try {
			loadedModule._compile(contents, file);
			if (file === 'main.js') {
				process.mainModule = loadedModule;
				loadedModule.id = '.';
			}
		} catch (error) {
			delete JSCModule._cache[file];
			throw error;
		}
		return loadedModule.exports;
	};

	bindings._custom_require = function(file) {
		var extensionIndex = file.lastIndexOf('.');
		var extension = extensionIndex >= 0 ? file.substring(extensionIndex) : '';
		var resourceManager = bindings.getResourceManager();
		var scriptSize = resourceManager.getResourceSize(file);
		if ((extension === '.js' || extension === '.jsi') && scriptSize > 0) {
			var cachedModule = JSCModule._cache[file];
			if (cachedModule) return cachedModule.exports;
			return bindings._loadScript(resourceManager.getResource(file), file);
		}

		var relativeModule = new JSCModule(file, module);
		try {
			return relativeModule.require(file);
		} catch (error) {
			return relativeModule.require('./' + file);
		}
	};
}

}  // end !inbrowser


console.binaryDump = function(buf, len, bytesPerLine) {
	var dumpStr;
	if (typeof bytesPerLine == "undefined") {
		dumpStr = bindings.getLogManager().binaryDump(buf, len);
	} else {
		dumpStr = bindings.getLogManager().binaryDump(buf, len, bytesPerLine);
	}
	console.log(dumpStr);
}

if (inbrowser && typeof bindings.LogManager !== "undefined" &&
        typeof bindings.LogManager.prototype.binaryDump !== "function") {
    bindings.LogManager.prototype.binaryDump = function(buf, len, bytesPerLine) {
        bytesPerLine = bytesPerLine || 20;
        len = Math.min(typeof len === "number" ? len : buf.length, buf.length);
        var lines = [];
        for (var offset = 0; offset < len; offset += bytesPerLine) {
            var bytes = [];
            for (var i = offset; i < Math.min(offset + bytesPerLine, len); ++i) {
                bytes.push((buf.charCodeAt(i) & 0xff).toString(16).padStart(2, "0"));
            }
            lines.push(offset.toString(16).padStart(6, "0") + ": " + bytes.join(" "));
        }
        return lines.join("\n");
    };
}

// basic coordinates - add to process.pdg
bindings.Point = coordinates.Point;
bindings.Offset = coordinates.Offset;
bindings.Vector = coordinates.Vector;
bindings.Rect = coordinates.Rect;
bindings.Quad = coordinates.Quad;
bindings.RotatedRect = coordinates.RotatedRect;

bindings.lftTop = coordinates.lftTop;
bindings.rgtTop = coordinates.rgtTop;
bindings.rgtBot = coordinates.rgtBot;
bindings.lftBot = coordinates.lftBot;
Object.defineProperty(bindings, 'lftTop', { writable: false });
Object.defineProperty(bindings, 'rgtTop', { writable: false });
Object.defineProperty(bindings, 'rgtBot', { writable: false });
Object.defineProperty(bindings, 'lftBot', { writable: false });

// color
bindings.Color = color.Color;

if (!inbrowser) {

// save off the pdg items that are pure JavaScript so they
// can be assigned as prototypes for newly created Javascript Objects when necessary
process._pdgScriptClasses = [];
process._pdgScriptClasses['Color'] = (new color.Color).__proto__;
process._pdgScriptClasses['Offset'] = (new coordinates.Offset).__proto__;
process._pdgScriptClasses['Point'] = (new coordinates.Point).__proto__;
process._pdgScriptClasses['Vector'] = (new coordinates.Vector).__proto__;
process._pdgScriptClasses['Rect'] = (new coordinates.Rect).__proto__;
process._pdgScriptClasses['Quad'] = (new coordinates.Quad).__proto__;
process._pdgScriptClasses['RotatedRect'] = (new coordinates.RotatedRect).__proto__;
process._pdgScriptClasses['MemBlock'] = bindings.MemBlock.prototype;

} // !inbrowser

function constructorSignature(name, paramcount, paramdoc) {
	return methodSignature(name, [null], "undefined", paramcount, paramdoc);
}

bindings._getRotatedRectConstructorSignature = function() {
	return constructorSignature("create a new RotatedRect", 1, "([object Rect] rect = Rect(0,0), number rotationRadians = 0.0, [object Offset] cpOffset = null)");
}

bindings._getRotatedRectConstructorSignature = function() {
	return constructorSignature("create a new RotatedRect", 1, "([object Rect] rect = Rect(0,0), number rotationRadians = 0.0, [object Offset] cpOffset = null)");
}

bindings._getQuadConstructorSignature = function() {
	return constructorSignature("create a new Quad", 4, "({|[object Quad] q|[object Rect] r|[object RotatedRect] r|[object Point] p1, [object Point] p2, [object Point] p3, [object Point] p4|[object Point[]] p})");
}

bindings._getRectConstructorSignature = function() {
	return constructorSignature("create a new Rect", 4, "({|number w, number h|[object Point] topLeft, number w, number h|[object Point] leftTop, [object Point] rightBottom|number left, number top, number right, number bottom})");
}

bindings._getOffsetConstructorSignature = function() {
	return constructorSignature("create and set x & y values", 2, "({|number x, number y|number[] xy|object xy})");
}

bindings._getPointConstructorSignature = function() {
	return constructorSignature("create and set x & y values", 2, "({|number x, number y|number[] xy|object xy})");
}

bindings._getVectorConstructorSignature = function() {
	return constructorSignature("create and set x & y values", 2, "({|number x, number y|number[] xy|object xy})");
}

bindings._getColorConstructorSignature = function() {
	return constructorSignature("create and color and set rgb values", 2, "({|number c|string colorstr|number r, number g, number b, number alpha = 1})");
}

bindings._getNetConnectionConstructorSignature = function() {
	return constructorSignature("create a NetConnection to manage a socket", 1, "(object socket)");
}

bindings._getNetClientConstructorSignature = function() {
	return constructorSignature("create a network client", 0, "(object opts = null)");
}

bindings._getNetServerConstructorSignature = function() {
	return constructorSignature("create a network server", 0, "(object opts = null)");
}

// network

if (!jsc && !inbrowser) { // not supported on iOS/JavaScriptCore currently

	bindings.NetConnection = netconnection.NetConnection;
	bindings.NetClient = netclient.NetClient;
	bindings.NetServer = netserver.NetServer;

	process._pdgScriptClasses['NetConnection'] = (new netconnection.NetConnection).__proto__;
	process._pdgScriptClasses['NetClient'] = (new netclient.NetClient).__proto__;
	process._pdgScriptClasses['NetServer'] = (new netserver.NetServer).__proto__;

	bindings.MemBlock.prototype.toBuffer = function() {
		var _sig = methodSignature("", arguments, "[object Buffer]", 0, "()"); if (_sig != null) return _sig;
		return Buffer.from(this.getData(), 'binary');
	}

	bindings.openCommandPort = bindings.openCommandPort;
	bindings.hasNetwork = true;
} else {
	bindings.hasNetwork = false;
}	

var _nativeGetFileManager = bindings.getFileManager;
var _nativeGetEventManager = bindings.getEventManager;
var _nativeGetTimerManager = bindings.getTimerManager;
var _nativeGetResourceManager = bindings.getResourceManager;
var _nativeGetConfigManager = bindings.getConfigManager;
var _nativeGetLogManager = bindings.getLogManager;

bindings.fs = _nativeGetFileManager();
bindings.evt = _nativeGetEventManager();
bindings.tm = _nativeGetTimerManager();
bindings.res = _nativeGetResourceManager();
bindings.cfg = _nativeGetConfigManager();
bindings.lm = _nativeGetLogManager();

// Embind creates a fresh JavaScript handle each time a singleton pointer is
// returned. Preserve the public API's singleton identity by returning the
// canonical handles initialized above.
function singletonGetter(nativeGetter, singleton) {
	var getter = function() {
		// Native functions return their documentation signature when probed with
		// a single null argument. Preserve that behavior through this wrapper.
		if (arguments.length === 1 && arguments[0] === null) {
			return nativeGetter.call(bindings, null);
		}
		return singleton;
	};
	getter._pdgNativeWrapper = true;
	return getter;
}

bindings.getFileManager = singletonGetter(_nativeGetFileManager, bindings.fs);
bindings.getEventManager = singletonGetter(_nativeGetEventManager, bindings.evt);
bindings.getTimerManager = singletonGetter(_nativeGetTimerManager, bindings.tm);
bindings.getResourceManager = singletonGetter(_nativeGetResourceManager, bindings.res);
bindings.getConfigManager = singletonGetter(_nativeGetConfigManager, bindings.cfg);
bindings.getLogManager = singletonGetter(_nativeGetLogManager, bindings.lm);

if ((inbrowser || jsc) && typeof bindings.MemBlock !== "undefined") {
    bindings.MemBlock.prototype.toBuffer = function() {
        var data = this.getData();
        var bytes = new Uint8Array(data.length);
        for (var i = 0; i < data.length; i++) bytes[i] = data.charCodeAt(i) & 0xff;
        return bytes;
    };
}

if (inbrowser && bindings.cfg) {
    ["setConfigString", "setConfigLong", "setConfigFloat", "setConfigBool"].forEach(function(name) {
        var original = bindings.ConfigManager.prototype[name];
        bindings.ConfigManager.prototype[name] = function(key, value) {
            if (value === null || typeof value === "undefined") {
                throw new TypeError(name + " requires a value");
            }
            return original.call(this, key, value);
        };
    });
}

if (inbrowser && typeof bindings.Spline !== "undefined") {
    var NativeSpline = bindings.Spline;
    var nativeSplineGetFirstOrder = NativeSpline.prototype.getFirstOrder;
    var nativeSplineGetSecondOrder = NativeSpline.prototype.getSecondOrder;
    var nativeSplineGetPoint = NativeSpline.prototype.getPoint;
    var nativeSplineGetBounds = NativeSpline.prototype.getBounds;

    bindings.Spline = function Spline(type) {
        return new NativeSpline(typeof type === "undefined" ? bindings.spline_CubicBezier : type);
    };
    bindings.Spline.prototype = NativeSpline.prototype;
    NativeSpline.prototype.getFirstOrder = function(u) { return new bindings.Point(nativeSplineGetFirstOrder.call(this, u)); };
    NativeSpline.prototype.getSecondOrder = function(u) { return new bindings.Point(nativeSplineGetSecondOrder.call(this, u)); };
    NativeSpline.prototype.getPoint = function(index) { return new bindings.Point(nativeSplineGetPoint.call(this, index)); };
    NativeSpline.prototype.getBounds = function() { return new bindings.Rect(nativeSplineGetBounds.call(this)); };
}

if (inbrowser && typeof bindings.Polygon !== "undefined") {
    var NativePolygon = bindings.Polygon;
    var nativePolygonGetPoint = NativePolygon.prototype.getPoint;
    var nativePolygonGetBounds = NativePolygon.prototype.getBounds;
    var nativePolygonCenterPoint = NativePolygon.prototype.centerPoint;
    var nativePolygonAddSpline = NativePolygon.prototype.addSpline;

    bindings.Polygon = function Polygon() {
        var polygon = new NativePolygon();
        var points = (arguments.length === 1 && Array.isArray(arguments[0]))
            ? arguments[0] : Array.prototype.slice.call(arguments);
        for (var i = 0; i < points.length; i++) polygon.addPoint(points[i]);
        return polygon;
    };
    bindings.Polygon.prototype = NativePolygon.prototype;
    NativePolygon.prototype.getPoint = function(index) { return new bindings.Point(nativePolygonGetPoint.call(this, index)); };
    NativePolygon.prototype.getBounds = function() { return new bindings.Rect(nativePolygonGetBounds.call(this)); };
    NativePolygon.prototype.centerPoint = function() { return new bindings.Point(nativePolygonCenterPoint.call(this)); };
    NativePolygon.prototype.addSpline = function(spline, step) {
        return nativePolygonAddSpline.call(this, spline, typeof step === "undefined" ? 0.01 : step);
    };
    NativePolygon.prototype.moveTo = function(first, second) {
        return arguments.length === 1 ? this._moveToPoint(first) : this._moveToXY(first, second);
    };
    NativePolygon.prototype.center = function(target) {
        return typeof target.left === "number" ? this._centerRect(target) : this._centerPoint(target);
    };
}

if (inbrowser && typeof bindings.Animated !== "undefined") {
    (function(Animated) {
        const proto = Animated.prototype;
        function finite(value) {
            if (typeof value !== "number" || !Number.isFinite(value)) throw new TypeError("Expected a finite number");
            return value;
        }
        function xy(value, y) {
            if (typeof value === "number") return { x: finite(value), y: finite(y) };
            if (!value) throw new TypeError("Expected a coordinate value");
            return { x: finite(Array.isArray(value) ? value[0] : value.x), y: finite(Array.isArray(value) ? value[1] : value.y) };
        }
        function chain(self, method, args) { self[method].apply(self, args); return self; }
        function timing(value) {
            finite(value);
            if (value < 0) throw new RangeError("Duration must be nonnegative seconds");
            return value;
        }
        function easing(value, fallback) {
            if (value === undefined) return fallback;
            if (!Number.isInteger(value)) throw new TypeError("Expected an easing constant");
            return value;
        }
        function vectorMethod(name, timed, optional, rate) {
            proto[name] = function(...args) {
                const count = typeof args[0] === "number" ? 2 : 1;
                const value = xy(args[0], args[1]);
                if (!timed || (optional && args.length === count)) {
                    if (args.length !== count) throw new TypeError("Immediate setters do not accept a duration");
                    return chain(this, "_" + name, name === "setSize" ? [value.x, value.y] : [value]);
                }
                return chain(this, "_" + name + (optional ? "Timed" : ""),
                    [value, timing(args[count]), easing(args[count + 1], rate ? bindings.linearTween : bindings.easeInOutQuad)]);
            };
        }
        function numberMethod(name, count, timed, optional, rate, rotation) {
            proto[name] = function(...args) {
                const values = Array.from({ length: count }, (_, i) => finite(args[i]));
                if (!timed || (optional && args.length === count)) {
                    if (args.length !== count) throw new TypeError("Immediate setters do not accept a duration");
                    return chain(this, "_" + name, values);
                }
                values.push(timing(args[count]), easing(args[count + 1], rate ? bindings.linearTween : bindings.easeInOutQuad));
                if (rotation) {
                    const direction = args[count + 2] === undefined ? bindings.rotationDirection_AsSpecified : args[count + 2];
                    if (!Number.isInteger(direction) || direction < 0 || direction > 3) throw new TypeError("Invalid rotation direction constant");
                    values.push(direction);
                }
                return chain(this, "_" + name + (optional ? "Timed" : ""), values);
            };
        }
        vectorMethod("setLocation", false);
        vectorMethod("setSize", false);
        vectorMethod("setMovement", false);
        vectorMethod("setCenterOffset", false);
        vectorMethod("moveTo", true, true, false);
        vectorMethod("moveBy", true, true, false);
        vectorMethod("changeMovementTo", true, false, true);
        vectorMethod("changeMovementBy", true, false, true);
        vectorMethod("changeCenterOffsetTo", true, false, false);
        vectorMethod("changeCenterOffsetBy", true, false, false);
        numberMethod("setWidth", 1, false);
        numberMethod("setHeight", 1, false);
        numberMethod("setRotation", 1, false);
        numberMethod("setSpin", 1, false);
        numberMethod("setGrowing", 1, false);
        numberMethod("setStretching", 2, false);
        numberMethod("grow", 1, true, true, false, false);
        numberMethod("rotateTo", 1, true, true, false, true);
        numberMethod("rotateBy", 1, true, true, false, true);
        numberMethod("changeSpinTo", 1, true, false, true, false);
        numberMethod("changeSpinBy", 1, true, false, true, false);
        numberMethod("changeGrowingTo", 1, true, false, true, false);
        numberMethod("changeGrowingBy", 1, true, false, true, false);
        numberMethod("stretch", 2, true, true, false, false);
        numberMethod("resizeTo", 2, true, false, false, false);
        numberMethod("resizeBy", 2, true, true, false, false);
        numberMethod("changeScaleTo", 2, true, false, false, false);
        numberMethod("changeScaleBy", 2, true, false, false, false);
        numberMethod("changeStretchingTo", 2, true, false, true, false);
        numberMethod("changeStretchingBy", 2, true, false, true, false);
        proto.setScale = function(x, y = x) { return chain(this, "_setScale", [finite(x), finite(y)]); };
        proto.getBoundingBox = function() { return new bindings.Rect(this._getBoundingBox()); };
        proto.getRotatedBounds = function() {
            const b = this._getRotatedBounds(); return new bindings.RotatedRect(b, b.radians, b.centerOffset);
        };
        proto.getLocation = function() { return new bindings.Point(this._getLocation()); };
        ["getSize", "getMovement", "getScale", "getStretching", "getCenterOffset"].forEach(function(name) {
            proto[name] = function() { return new bindings.Offset(this["_" + name]()); };
        });
        ["stopMovement", "stopSpinning", "stopGrowing", "stopStretching", "pauseSchedule", "resumeSchedule", "cancelSchedule", "flipX", "flipY", "andThen"].forEach(function(name) {
            proto[name] = function() { return chain(this, "_" + name, []); };
        });
        proto.setFlipX = function(flip) { return chain(this, "_setFlipX", [flip]); };
        proto.setFlipY = function(flip) { return chain(this, "_setFlipY", [flip]); };
        proto.wait = function(seconds) { return chain(this, "_wait", [timing(seconds)]); };
    })(bindings.Animated);
}

Object.defineProperties(bindings, {
    CopyPixels: {value: true, enumerable: true, writable: false, configurable: false},
    SharedSurface: {value: false, enumerable: true, writable: false, configurable: false}
});

if (bindings.Image) {
    (function(NativeImage) {
        function Image(source, copyPixels = bindings.CopyPixels) {
            if (!new.target) throw new TypeError("Image requires new");
            var image;
            if (bindings.Port && source instanceof bindings.Port) {
                if (arguments.length > 2) throw new TypeError("Expected a Port and optional copyPixels flag");
                if (typeof copyPixels !== 'boolean') throw new TypeError("copyPixels must be a boolean");
                image = inbrowser ? NativeImage._createImageFromOffscreenPort(source, copyPixels) :
                    bindings.gfx._createImageFromOffscreenPort(source, copyPixels);
                if (!image) throw new Error("Image requires an open offscreen Port");
            } else {
                // Preserve filename construction and the native null introspection sentinel.
                image = Reflect.construct(NativeImage, Array.prototype.slice.call(arguments));
            }
            if (new.target !== Image) Object.setPrototypeOf(image, new.target.prototype);
            return image;
        }
        // Native images and ImageStrips keep their existing prototypes/instanceof behavior.
        Image.prototype = NativeImage.prototype;
        Object.setPrototypeOf(Image, NativeImage);
        bindings.Image = Image;
    })(bindings.Image);
}

if (inbrowser && typeof bindings.Image !== "undefined") {
    (function(Image) {
        var proto = Image.prototype;

        function pointValue(first, second) {
            if (first === null || typeof first === "undefined") return { x: 0, y: 0 };
            if (typeof first === "number") return { x: first, y: second };
            return { x: first.x, y: first.y };
        }

        function colorValue(value) {
            return new bindings.Color(value.red, value.green, value.blue, value.alpha);
        }

        proto.getImageBounds = function(point) {
            var bounds = arguments.length === 0 || point === null
                ? this._getImageBounds()
                : this._getImageBoundsAt(pointValue(point));
            return new bindings.Rect(bounds);
        };
        proto.getSubsection = function(section) {
            var rect = (section && typeof section.getBounds === "function")
                ? section.getBounds() : section;
            return this._getSubsection(rect);
        };
        proto.setTransparentColor = function(value) {
            this._setTransparentColor(value);
            return this;
        };
        proto.getTransparentColor = function() {
            return colorValue(this._getTransparentColor());
        };
        proto.setOpacity = function(value) {
            var opacity = Number(value);
            if (!isFinite(opacity)) opacity = 0;
            if (opacity <= 1) opacity = Math.floor(255 * opacity);
            opacity = Math.max(0, Math.min(255, Math.round(opacity)));
            this._setOpacity(opacity);
        };
        proto.getOpacity = function() {
            return this._getOpacity() / 255;
        };
        proto.getAlphaValue = function(first, second) {
            var point = pointValue(first, second);
            return this._getAlphaValue(point.x || 0, point.y || 0);
        };
        proto.getPixel = function(first, second) {
            var point = pointValue(first, second);
            return colorValue(this._getPixel(point.x || 0, point.y || 0));
        };
    })(bindings.Image);
}

if (inbrowser && typeof bindings.ImageStrip !== "undefined") {
    bindings.ImageStrip.prototype.setFrameWidth = function(width) {
        this._setFrameWidth(width);
        return this;
    };
    bindings.ImageStrip.prototype.setNumFrames = function(count) {
        this._setNumFrames(count);
        return this;
    };
}

if (inbrowser && typeof bindings.Attributes !== "undefined") {
    (function(proto) {
        function chain(self, nativeName, args) {
            self[nativeName].apply(self, args);
            return self;
        }
        function point(value) {
            if (value === null || typeof value === "undefined") return { x: 0, y: 0 };
            return { x: value.x, y: value.y };
        }
        function nativeColor(value) {
            var converted = typeof value === "string" || typeof value === "number"
                ? new bindings.Color(value) : value;
            return {
                red: converted.red,
                green: converted.green,
                blue: converted.blue,
                alpha: converted.alpha
            };
        }
        function publicColor(value) {
            return new bindings.Color(value.red, value.green, value.blue, value.alpha);
        }

        proto.lineColor = function(value) { return chain(this, "_lineColor", [nativeColor(value)]); };
        proto.lineThickness = function(value) { return chain(this, "_lineThickness", [value]); };
        proto.lineOpacity = function(value) { return chain(this, "_lineOpacity", [value]); };
        proto.lineStyle = function(value) { return chain(this, "_lineStyle", [value]); };
        proto.fillColor = function(value) { return chain(this, "_fillColor", [nativeColor(value)]); };
        proto.fillOpacity = function(value) { return chain(this, "_fillOpacity", [value]); };
        proto.fillGradient = function(start, startColor, end, endColor) {
            return chain(this, "_fillGradient", [point(start), nativeColor(startColor), point(end), nativeColor(endColor)]);
        };
        proto.fillRadialGradient = function(center, centerColor, radius, endColor) {
            return chain(this, "_fillRadialGradient", [point(center), nativeColor(centerColor), radius, nativeColor(endColor)]);
        };
        proto.texture = function(value) { return chain(this, "_texture", [value]); };
        proto.fitType = function(value) { return chain(this, "_fitType", [value]); };
        proto.font = function(value) { return chain(this,"_font",[value]); };
        proto.withAppearance = function(overrides, textOnly) { return this._withAppearance(browserAttributes(overrides), !!textOnly); };
        proto.clipOverflow = function(value) { return chain(this, "_clipOverflow", [value]); };
        proto.roundedCorners = function(value) { return chain(this, "_roundedCorners", [value]); };
        proto.translation = function(value) { return chain(this, "_translation", [point(value)]); };
        proto.rotation = function(radians, center) { return chain(this, "_rotation", [radians, point(center)]); };
        proto.scale = function(xFactor, yFactor, center) {
            if (typeof yFactor !== "number") {
                center = yFactor;
                yFactor = xFactor;
            }
            return chain(this, "_scale", [xFactor, yFactor, point(center)]);
        };
        proto.skew = function(xSkew, ySkew, center) {
            return chain(this, "_skew", [xSkew, ySkew, point(center)]);
        };
        proto.transform = function(matrix) {
            if (!Array.isArray(matrix) || matrix.length !== 9 || matrix.some(function(value) {
                return typeof value !== "number";
            })) {
                throw new TypeError("Attributes.transform requires an array of 9 numbers");
            }
            return chain(this, "_transform", [matrix]);
        };
        proto.setTransform = function(matrix) { return chain(this, "_setTransform", [matrix]); };
        proto.blendMode = function(value) { return chain(this, "_blendMode", [value]); };
        proto.textSize = function(value) { return chain(this, "_textSize", [value]); };
        proto.textStyle = function(value) { return chain(this, "_textStyle", [value]); };
        proto.frame = function(value) { return chain(this, "_frame", [value]); };
        proto.subsection = function(value) { return chain(this, "_subsection", [value]); };
        proto.sphereRotation = function(value) { return chain(this, "_sphereRotation", [value]); };
        proto.polarOffset = function(value) { return chain(this, "_polarOffset", [point(value)]); };
        proto.lightOffset = function(value) { return chain(this, "_lightOffset", [point(value)]); };
        proto.ambientLight = function(value) { return chain(this, "_ambientLight", [nativeColor(value)]); };

        proto.getLineColor = function() { return publicColor(this._getLineColor()); };
        proto.getFillColor = function() { return publicColor(this._getFillColor()); };
        proto.getGradientStart = function() { return new bindings.Point(this._getGradientStart()); };
        proto.getGradientEnd = function() { return new bindings.Point(this._getGradientEnd()); };
        proto.getGradientStartColor = function() { return publicColor(this._getGradientStartColor()); };
        proto.getGradientEndColor = function() { return publicColor(this._getGradientEndColor()); };
        proto.getRadialGradientCenter = function() { return new bindings.Point(this._getRadialGradientCenter()); };
        proto.getRadialGradientCenterColor = function() { return publicColor(this._getRadialGradientCenterColor()); };
        proto.getRadialGradientEndColor = function() { return publicColor(this._getRadialGradientEndColor()); };
        proto.getSubsection = function() { return new bindings.Rect(this._getSubsection()); };
        proto.getPolarOffset = function() { return new bindings.Offset(this._getPolarOffset()); };
        proto.getLightOffset = function() { return new bindings.Offset(this._getLightOffset()); };
        proto.getAmbientLight = function() { return publicColor(this._getAmbientLight()); };
    })(bindings.Attributes.prototype);
}

// Embind supports one native base: AnimatedAttributes inherits Animated there.
// Attribute calls borrow its adjusted second-base pointer for the duration of
// the call; no copied state and no independently owned Attributes allocation.
function browserAttributes(value) {
    if (bindings.AnimatedAttributes && value instanceof bindings.AnimatedAttributes) {
        if (value.isDeleted()) throw new Error("AnimatedAttributes has been deleted");
        return value._attributes();
    }
    if (value instanceof bindings.Attributes) return value;
    throw new TypeError("Expected Attributes or AnimatedAttributes");
}

if (inbrowser && bindings.AnimatedAttributes) {
    (function(NativeAnimatedAttributes) {
        var proto = Object.create(NativeAnimatedAttributes.prototype);
        function AnimatedAttributes(source) {
            if (!new.target) throw new TypeError("AnimatedAttributes requires new");
            if (arguments.length > 1) throw new TypeError("Expected an optional Attributes snapshot");
            var native = source != null ? new NativeAnimatedAttributes(browserAttributes(source))
                : new NativeAnimatedAttributes();
            // Embind returns a native handle from its constructor. Restore the
            // actual JS subclass (View, Button, etc.) after super() constructs it.
            Object.setPrototypeOf(native, new.target.prototype);
            return native;
        }
        AnimatedAttributes.prototype = proto;
        Object.defineProperty(proto, "constructor", { value: AnimatedAttributes, writable: true, configurable: true });
        Object.setPrototypeOf(AnimatedAttributes, NativeAnimatedAttributes);
        bindings.AnimatedAttributes = AnimatedAttributes;

        Object.getOwnPropertyNames(bindings.Attributes.prototype).forEach(function(name) {
            if (name === "constructor" || name.charAt(0) === "_") return;
            var method = bindings.Attributes.prototype[name];
            if (typeof method !== "function") return;
            proto[name] = function() {
                var attributes = browserAttributes(this);
                var result = method.apply(attributes, arguments);
                return result === attributes ? this : result;
            };
        });

        function finite(value, name) {
            if (typeof value !== "number" || !Number.isFinite(value))
                throw new TypeError(name + " must be a finite number");
            return value;
        }
        function integer(value, name) {
            finite(value, name);
            if (!Number.isInteger(value) || value < -2147483648 || value > 2147483647)
                throw new TypeError(name + " must be an integer");
            return value;
        }
        function seconds(value) {
            finite(value, "duration");
            if (value < 0) throw new RangeError("Duration must be nonnegative seconds");
            return value;
        }
        function easing(value) {
            return value === undefined ? bindings.linearTween : integer(value, "easing");
        }
        function direction(value) {
            return value === undefined ? bindings.rotationDirection_AsSpecified : integer(value, "direction");
        }
        function point(value) { return { x: finite(value.x, "x"), y: finite(value.y, "y") }; }
        function color(value) {
            if (typeof value === "string" || typeof value === "number") value = new bindings.Color(value);
            return { red: finite(value.red, "red"), green: finite(value.green, "green"),
                blue: finite(value.blue, "blue"), alpha: finite(value.alpha, "alpha") };
        }
        function rect(value) {
            return { left: finite(value.left, "left"), top: finite(value.top, "top"),
                right: finite(value.right, "right"), bottom: finite(value.bottom, "bottom") };
        }
        var channels = {
            changeLineColor: color, changeLineThickness: finite, changeLineOpacity: finite,
            changeFillColor: color, changeFillOpacity: finite, changeRoundedCorners: finite, changeTextSize: finite,
            changeSubsection: rect, changePolarOffset: point, changeLightOffset: point, changeAmbientLight: color
        };
        Object.keys(channels).forEach(function(name) {
            proto[name] = function(target, duration, curve) {
                this["_" + name](channels[name](target, name), seconds(duration), easing(curve));
                return this;
            };
        });
        proto.changeSkew = function(x, y, duration, curve) {
            this._changeSkew(finite(x, "x"), finite(y, "y"), seconds(duration), easing(curve));
            return this;
        };
        proto.changeSphereRotation = function(radians, duration, curve, travel) {
            this._changeSphereRotation(finite(radians, "radians"), seconds(duration), easing(curve), direction(travel));
            return this;
        };
        proto.changeFrames = function(first, last, duration, curve) {
            this._changeFrames(integer(first, "first frame"), integer(last, "last frame"), seconds(duration), easing(curve));
            return this;
        };
        proto.changeFillGradient = function(start, startColor, end, endColor, duration, curve) {
            this._changeFillGradient(point(start), color(startColor), point(end), color(endColor), seconds(duration), easing(curve));
            return this;
        };
        proto.changeFillRadialGradient = function(center, centerColor, radius, endColor, duration, curve) {
            this._changeFillRadialGradient(point(center), color(centerColor), finite(radius, "radius"), color(endColor), seconds(duration), easing(curve));
            return this;
        };
        proto.changeTransform = function(matrix, duration, curve) {
            this._changeTransform(matrix, seconds(duration), easing(curve));
            return this;
        };
    })(bindings.AnimatedAttributes);

    // Attribute-consuming native methods receive the correctly adjusted base.
    function acceptsBrowserAttributes(proto, name) {
        var native = proto[name];
        proto[name] = function() {
            var args = Array.prototype.slice.call(arguments);
            args[args.length - 1] = browserAttributes(args[args.length - 1]);
            return native.apply(this, args);
        };
    }
    ["addLine", "addSpline", "addArc", "addRect", "addQuad", "addPolygon", "addEllipse",
     "addImage", "addImageStrip", "addDrawing"].forEach(function(name) {
        acceptsBrowserAttributes(bindings.Drawing.prototype, name);
    });
    acceptsBrowserAttributes(bindings.ElementRef.prototype, "setAttributes");
    acceptsBrowserAttributes(bindings.ElementRef.prototype, "setLiveAttributes");
    ["drawLine", "drawRect", "drawQuad", "drawPolygon", "drawSpline", "drawCircle",
     "drawEllipse", "drawArc", "drawImage", "drawDrawing", "drawText", "drawSphere"].forEach(function(name) {
        acceptsBrowserAttributes(bindings.Port.prototype, name);
    });
}

if (inbrowser && typeof bindings.Drawing !== "undefined") {
    bindings.Drawing.prototype.getBounds = function() {
        return new bindings.Rect(this._getBounds());
    };
    bindings.Drawing.prototype.centerPoint = function() {
        return new bindings.Point(this._centerPoint());
    };
    bindings.ElementRef.prototype.getControlPoints = function() {
        return this._getControlPoints().map(function(value) { return new bindings.Point(value); });
    };
    bindings.ElementRef.prototype.getControlPoint = function(index) {
        return new bindings.Point(this._getControlPoint(index));
    };
}

if (inbrowser && typeof bindings.SpriteLayer !== "undefined") {
    (function() {
        var layerSprites = new WeakMap();
        var nativeObjects = new Map();
        var weakObjects = typeof WeakRef === 'function';
        function remember(object) {
            if (object) nativeObjects.set(object._getNativeIdentity(),
                weakObjects ? new WeakRef(object) : object);
            return object;
        }
        bindings._emscriptenRememberObject = remember;
        bindings._emscriptenObjectForIdentity = function(identity) {
            var entry = nativeObjects.get(identity);
            var object = weakObjects && entry ? entry.deref() : entry;
            if (!object) nativeObjects.delete(identity);
            return object || null;
        };
        var nativeCleanupLayer = bindings.cleanupLayer;
        bindings.cleanupLayer = function(layer) {
            if (!layer) return nativeCleanupLayer(layer);
            var identity = layer._getNativeIdentity();
            var sprites = layerSprites.get(layer) || [];
            var spriteIdentities = sprites.filter(function(sprite) { return sprite && !sprite.isDeleted(); })
                .map(function(sprite) { return sprite._getNativeIdentity(); });
            nativeCleanupLayer(layer);
            nativeObjects.delete(identity);
            spriteIdentities.forEach(function(id) { nativeObjects.delete(id); });
            layerSprites.delete(layer);
        };
        var layerProto = bindings.SpriteLayer.prototype;
        layerProto.zoomTo = function(zoom, seconds, easing, keepInRect, centerOn) {
            this._zoomTo(zoom, seconds, easing === undefined ? bindings.easeInOutQuad : easing,
                keepInRect === undefined ? {left: 0, top: 0, right: 0, bottom: 0} : keepInRect,
                centerOn === undefined ? null : centerOn);
            return this;
        };
        layerProto.zoom = function(factor, seconds, easing, keepInRect, centerOn) {
            return this.zoomTo(this.getZoom() * factor, seconds, easing, keepInRect, centerOn);
        };
        layerProto.getOrigin = function() {
            var p = this._getOrigin();
            return new bindings.Point(p.x, p.y);
        };
        ['layerToPort', 'portToLayer'].forEach(function(direction) {
            ['Point', 'Offset', 'Vector'].forEach(function(kind) {
                layerProto[direction + kind] = function(value) {
                    return new bindings[kind](this['_' + direction + kind](value));
                };
            });
            layerProto[direction + 'Rect'] = function(rect) {
                var value = this['_' + direction + 'Rect'](rect,
                    rect.radians === undefined ? 0 : rect.radians,
                    rect.centerOffset || {x: 0, y: 0});
                return new bindings.RotatedRect(value, value.radians, value.centerOffset);
            };
        });
        var spriteProto = bindings.Sprite.prototype;
        spriteProto.addFramesImage = function(image, first, count) {
            this._addFramesImage(image, first === undefined ? -1 : first, count === undefined ? 0 : count);
        };
        spriteProto.startFrameAnimation = function(fps, first, count, flags) {
            this._startFrameAnimation(fps, first === undefined ? -1 : first,
                count === undefined ? 0 : count, flags === undefined ? 4 : flags);
        };
        spriteProto.getFrameRotatedBounds = function(frame) {
            var bounds = this._getFrameRotatedBounds(frame === undefined ? -1 : frame);
            return new bindings.RotatedRect(bounds, bounds.radians, bounds.centerOffset);
        };


        layerProto.createSprite = function() {
            remember(this);
            var sprite = remember(this._createSprite());
            var sprites = layerSprites.get(this);
            if (!sprites) {
                sprites = [];
                layerSprites.set(this, sprites);
            }
            sprites.push(sprite);
            return sprite;
        };
        layerProto.getNthSprite = function(index) {
            // Layer order and membership may change through a mounted host.
            // Query native order, then reuse a retained handle by identity.
            var sprite = this._getNthSprite(index);
            if (!sprite) return null;
            if (bindings._canonicalPhysicsOwner) return bindings._canonicalPhysicsOwner(sprite);
            var existing = bindings._emscriptenObjectForIdentity(sprite._getNativeIdentity());
            if (existing && !existing.isDeleted()) { sprite.delete(); return existing; }
            return remember(sprite);
        };
        if (typeof layerProto._createSpriteFromSpriterFile === "function") {
            layerProto.createSpriteFromSpriterFile = function(path, entity) {
                remember(this);
                var sprite = remember(this._createSpriteFromSpriterFile(path,
                    typeof entity === "undefined" || entity === null ? "" : entity));
                if (sprite) {
                    var sprites = layerSprites.get(this) || [];
                    if (!layerSprites.has(this)) layerSprites.set(this, sprites);
                    sprites.push(sprite);
                }
                return sprite;
            };

            var nativeCreateFromEntity = layerProto.createSpriteFromSpriterEntity;
            layerProto.createSpriteFromSpriterEntity = function(name) {
                remember(this);
                var sprite = remember(nativeCreateFromEntity.call(this, name));
                if (sprite) {
                    var sprites = layerSprites.get(this) || [];
                    if (!layerSprites.has(this)) layerSprites.set(this, sprites);
                    sprites.push(sprite);
                }
                return sprite;
            };

            spriteProto.setAnimationDebugDraw = function(flags) {
                if (typeof flags !== "number" || !isFinite(flags) || Math.floor(flags) !== flags ||
                    flags < bindings.animationDebug_None || flags > bindings.animationDebug_All) {
                    throw new RangeError("Expected animationDebug integer flag bits");
                }
                this._setAnimationDebugDraw(flags);
            };
            var nativeSampleAnimationPose = spriteProto.sampleAnimationPose;
            spriteProto.sampleAnimationPose = function(clip, timeSeconds) {
                if (typeof timeSeconds !== "number") throw new TypeError("Sample time must be floating-point seconds");
                return nativeSampleAnimationPose.call(this, clip, timeSeconds);
            };
            ["Bone", "Binding"].forEach(function(kind) {
                spriteProto["getAnimation" + kind + "Transform"] = function(name, space) {
                    if (typeof space === "undefined") space = bindings.animationSpace_Local;
                    if (typeof space !== "number" || (space !== bindings.animationSpace_Local &&
                        space !== bindings.animationSpace_Rig && space !== bindings.animationSpace_World)) {
                        throw new RangeError("Expected an animationSpace integer constant");
                    }
                    return this["_getAnimation" + kind + "Transform"](name, space);
                };
            });

            var nativeGetSpriterCollisionBox = spriteProto.getSpriterCollisionBox;
            var nativeHasAttachPoint = spriteProto.hasAttachPoint;
            var nativeAttachSprite = spriteProto.attachSprite;
            var nativeActivateSubEntity = spriteProto.activateSubEntity;
            spriteProto.getSpriterCollisionBox = function(name) {
                var value = nativeGetSpriterCollisionBox.call(this, name);
                return new bindings.RotatedRect(new bindings.Rect(value), value.radians,
                    new bindings.Offset(value.centerOffset));
            };
            spriteProto.hasAttachPoint = function(name) {
                if (typeof name === "undefined") throw new TypeError("AttachPoint name is required");
                return nativeHasAttachPoint.call(this, name === null ? "" : name);
            };
            spriteProto.attachSprite = function(sprite, name) {
                if (typeof name === "undefined" || name === null) {
                    throw new TypeError("AttachPoint name is required");
                }
                nativeAttachSprite.call(this, sprite, name);
            };
            spriteProto.activateSubEntity = function(entity, animation) {
                if (typeof entity === "undefined" || animation === null) {
                    throw new TypeError("Sub-entity and animation names are required");
                }
                nativeActivateSubEntity.call(this, entity,
                    typeof animation === "undefined" ? "idle" : animation);
            };
        }
        if(typeof layerProto._setGravity==='function')layerProto.setGravity=function(gravity,keepItDownward){
            if(typeof gravity!=='number'||!isFinite(gravity))throw new TypeError('Gravity must be finite');
            this._setGravity(gravity,typeof keepItDownward==='undefined'?true:!!keepItDownward);return this;
        };
        layerProto.setUseChipmunkPhysics = function(useIt) {
            if (typeof this._setUseChipmunkPhysics === "function") {
                this._setUseChipmunkPhysics(useIt !== false);
            }
            return this;
        };
        var nativeSetWantsCollideWallEvents = spriteProto.setWantsCollideWallEvents;
        spriteProto.setWantsCollideWallEvents = function(wantsThem) {
            nativeSetWantsCollideWallEvents.call(this, wantsThem !== false);
            return this;
        };
    })();
}

if (inbrowser && typeof bindings.TileLayer !== "undefined") {
    bindings.TileLayer.prototype.defineTileSet = function(tileWidth, tileHeight, image) {
        this._defineTileSet(tileWidth, tileHeight, image);
        return this;
    };
    bindings.TileLayer.prototype.setWorldSize = function(width, height) {
        this._setWorldSize(width, height);
        return this;
    };
    bindings.TileLayer.prototype.getWorldSize = function() {
        return new bindings.Rect(this._getWorldSize());
    };
    bindings.TileLayer.prototype.getTileSize = function() {
        return new bindings.Point(this._getTileSize());
    };
}

if (inbrowser && typeof bindings.Serializer !== "undefined") {
    (function(proto) {
        function requireNumber(value, name) {
            if (typeof value !== "number") throw new TypeError(name + " requires a number");
            return value;
        }
        function rangedInteger(value, min, max, name) {
            requireNumber(value, name);
            if (!Number.isInteger(value) || value < min || value > max) {
                throw new RangeError(name + " value is outside its supported range");
            }
            return value;
        }
        function fixedSize(size) {
            return function(value) {
                requireNumber(value, "sizeof");
                return size;
            };
        }

        proto.serialize_1 = function(value) { return this._serialize_1(rangedInteger(value, -128, 127, "serialize_1")); };
        proto.serialize_1u = function(value) { return this._serialize_1u(rangedInteger(value, 0, 255, "serialize_1u")); };
        proto.serialize_2 = function(value) { return this._serialize_2(rangedInteger(value, -32768, 32767, "serialize_2")); };
        proto.serialize_2u = function(value) { return this._serialize_2u(rangedInteger(value, 0, 65535, "serialize_2u")); };
        proto.serialize_3u = function(value) { return this._serialize_3u(rangedInteger(value, 0, 16777215, "serialize_3u")); };
        proto.serialize_4 = function(value) { return this._serialize_4(rangedInteger(value, -2147483648, 2147483647, "serialize_4")); };
        proto.serialize_4u = function(value) { return this._serialize_4u(rangedInteger(value, 0, 4294967295, "serialize_4u")); };
        proto.serialize_8 = function(value) { return this._serialize_8(requireNumber(value, "serialize_8")); };
        proto.serialize_f = function(value) { return this._serialize_f(requireNumber(value, "serialize_f")); };
        proto.serialize_d = function(value) { return this._serialize_d(requireNumber(value, "serialize_d")); };
        proto.serialize_uint = function(value) {
            if (typeof value === "undefined") throw new TypeError("serialize_uint requires a number");
            if (value === null || !Number.isFinite(value)) value = 0;
            return this._serialize_uint(value);
        };
        proto.serialize_str = function(value) {
            if (value === null) return;
            if (typeof value !== "string") throw new TypeError("serialize_str requires a string");
            return this._serialize_str(value);
        };
        proto.serialize_mem = function(value) {
            if (typeof value !== "string") throw new TypeError("serialize_mem requires a binary string");
            return this._serialize_mem(value);
        };
        proto.serialize_rotr = function(value) { return this._serialize_rotr(value); };
        proto.serialize_quad = function(value) { return this._serialize_quad(value); };

        proto.setResourceMode = function(mode) {
            if (!Number.isInteger(mode)) throw new TypeError("Expected an integer serialization resource mode");
            if (this._pdgSerializedObjects && this._pdgSerializedObjects.length && mode !== this.getResourceMode())
                throw new Error("Set the resource mode before serializing objects");
            this._setResourceMode(mode);
            this._pdgSizedObjects = [];
            return this;
        };
        proto.sizeof_1 = proto.sizeof_1u = fixedSize(1);
        proto.sizeof_2 = proto.sizeof_2u = fixedSize(2);
        proto.sizeof_3u = fixedSize(3);
        proto.sizeof_4 = proto.sizeof_4u = proto.sizeof_f = fixedSize(4);
        proto.sizeof_8 = proto.sizeof_8u = proto.sizeof_d = fixedSize(8);
        proto.sizeof_str = function(value) { return this._sizeof_str(value); };
        proto.sizeof_mem = function(value) { return this._sizeof_mem(value); };
        proto.sizeof_rotr = function(value) { return this._sizeof_rotr(value); };
        proto.sizeof_quad = function(value) { return this._sizeof_quad(value); };
    })(bindings.Serializer.prototype);

    (function(proto) {
        var nativeColor = proto.deserialize_color;
        var nativeOffset = proto.deserialize_offset;
        var nativePoint = proto.deserialize_point;
        var nativeVector = proto.deserialize_vector;
        var nativeRect = proto.deserialize_rect;

        proto.deserialize_color = function() {
            var value = nativeColor.call(this);
            return new bindings.Color(value.red, value.green, value.blue, value.alpha);
        };
        proto.deserialize_offset = function() { return new bindings.Offset(nativeOffset.call(this)); };
        proto.deserialize_point = function() { return new bindings.Point(nativePoint.call(this)); };
        proto.deserialize_vector = function() { return new bindings.Vector(nativeVector.call(this)); };
        proto.deserialize_rect = function() { return new bindings.Rect(nativeRect.call(this)); };
        proto.deserialize_rotr = function() {
            var value = this._deserialize_rotr();
            return new bindings.RotatedRect(new bindings.Rect(value), value.radians,
                new bindings.Offset(value.centerOffset));
        };
        proto.deserialize_quad = function() {
            var value = this._deserialize_quad();
            return new bindings.Quad(value.points);
        };
    })(bindings.Deserializer.prototype);

    // Embind cannot directly instantiate the V8-specific ScriptSerializable
    // implementation. Keep the native byte stream, but bridge JavaScript-owned
    // serializable objects and their constructor registry in JavaScript.
    (function() {
        var serializableClasses = Object.create(null);
        var tagObject = 0x6f626a;
        var tagObjectNil = 0x6e696c;
        var tagObjectRef = 0x726566;

        function BrowserSerializable(getSize, serialize, deserialize, getTag) {
            if (!(this instanceof BrowserSerializable)) {
                throw new TypeError("ISerializable must be constructed with new");
            }
            if (typeof getSize !== "function" || typeof serialize !== "function" ||
                    typeof deserialize !== "function" || typeof getTag !== "function") {
                throw new TypeError("ISerializable requires four function arguments");
            }
            Object.defineProperties(this, {
                _pdgSizeCallback: { value: getSize },
                _pdgSerializeCallback: { value: serialize },
                _pdgDeserializeCallback: { value: deserialize },
                _pdgTagCallback: { value: getTag }
            });
        }
        BrowserSerializable.prototype.getSerializedSize = function(serializer) {
            return this._pdgSizeCallback.call(this, serializer);
        };
        BrowserSerializable.prototype.serialize = function(serializer) {
            return this._pdgSerializeCallback.call(this, serializer);
        };
        BrowserSerializable.prototype.deserialize = function(deserializer) {
            return this._pdgDeserializeCallback.call(this, deserializer);
        };
        BrowserSerializable.prototype._pdgGetClassTag = function() {
            return this._pdgTagCallback.call(this);
        };
        bindings.ISerializable = BrowserSerializable;

        function classTagOf(obj) {
            var tag;
            if (obj && typeof obj._pdgGetClassTag === "function") tag = obj._pdgGetClassTag();
            else if (obj && typeof obj.getMyClassTag === "function") tag = obj.getMyClassTag();
            else throw new TypeError("Serializable object must provide getMyClassTag");
            if (!Number.isInteger(tag) || tag < 0 || tag > 0xffffffff) {
                throw new RangeError("Serializable class tag must be a 32-bit unsigned integer");
            }
            return tag;
        }
        function getSizeOf(obj, serializer) {
            if (!obj || typeof obj.getSerializedSize !== "function") {
                throw new TypeError("Serializable object must provide getSerializedSize");
            }
            return obj.getSerializedSize(serializer);
        }
        function serializeObjectData(obj, serializer) {
            if (!obj || typeof obj.serialize !== "function") {
                throw new TypeError("Serializable object must provide serialize");
            }
            return obj.serialize(serializer);
        }
        function deserializeObjectData(obj, deserializer) {
            if (!obj || typeof obj.deserialize !== "function") {
                throw new TypeError("Serializable object must provide deserialize");
            }
            return obj.deserialize(deserializer);
        }

        bindings.registerSerializableClass = function(constructor) {
            if (typeof constructor !== "function") throw new TypeError("Serializable constructor must be a function");
            var instance = new constructor();
            if (!instance) throw new TypeError("Serializable constructor must return an object");
            var tag = classTagOf(instance);
            if (typeof instance.getSerializedSize !== "function" ||
                    typeof instance.serialize !== "function" || typeof instance.deserialize !== "function") {
                throw new TypeError("Serializable object is missing required methods");
            }
            if (instance._pdgRequiresExplicitRegistration) instance._pdgRegistered = true;
            serializableClasses[tag] = constructor;
        };

        // Images are native resources and share a single class tag. Restore a
        // strip-capable image so saved frame layout remains directly accessible.
        if (bindings._createSnapshotImage) {
            serializableClasses[0xffffff08] = function() { return bindings._createSnapshotImage(); };
        }

        if (bindings.Sprite) {
            serializableClasses[0xffffff01] = function() { return new bindings.Sprite(); };
        }

        var serializerProto = bindings.Serializer.prototype;
        serializerProto.sizeof_obj = function(obj) {
            if (obj === null) return 3;
            classTagOf(obj);
            this._pdgSizedObjects = this._pdgSizedObjects || [];
            var referenceIndex = this._pdgSizedObjects.indexOf(obj);
            if (referenceIndex >= 0) return 3 + this.sizeof_uint(referenceIndex);
            this._pdgSizedObjects.push(obj);
            var objectSize = getSizeOf(obj, this);
            return 3 + 4 + 2 + this.sizeof_uint(objectSize) + objectSize;
        };
        serializerProto.serialize_obj = function(obj) {
            if (obj === null) {
                this.serialize_3u(tagObjectNil);
                return;
            }
            classTagOf(obj);
            this._pdgSerializedObjects = this._pdgSerializedObjects || [];
            var referenceIndex = this._pdgSerializedObjects.indexOf(obj);
            if (referenceIndex >= 0) {
                this.serialize_3u(tagObjectRef);
                this.serialize_uint(referenceIndex);
                return;
            }
            this._pdgSerializedObjects.push(obj);
            this.serialize_3u(tagObject);
            this.serialize_4u(classTagOf(obj));
            this.serialize_2u(obj._pdgRequiresExplicitRegistration && !obj._pdgRegistered
                ? 0 : this._pdgSerializedObjects.length);
            var writer = this, priorSized = this._pdgSizedObjects, objectSize;
            this._pdgSizedObjects = this._pdgSerializedObjects.slice();
            try {
                objectSize = this._measureObjectBody(function() { return getSizeOf(obj, writer); });
            } finally {
                this._pdgSizedObjects = priorSized;
            }
            this.serialize_uint(objectSize);
            serializeObjectData(obj, this);
        };

        var deserializerProto = bindings.Deserializer.prototype;
        var nativeSetDataPtr = deserializerProto.setDataPtr;
        deserializerProto.setDataPtr = function(data) {
            this._pdgDeserializedObjects = [];
            return nativeSetDataPtr.call(this, data);
        };
        deserializerProto.deserialize_obj = function() {
            var serializationType = this.deserialize_3u();
            if (serializationType === tagObjectNil) return null;
            this._pdgDeserializedObjects = this._pdgDeserializedObjects || [];
            if (serializationType === tagObjectRef) {
                var referenceIndex = this.deserialize_uint();
                if (referenceIndex < 0 || referenceIndex >= this._pdgDeserializedObjects.length) {
                    throw new Error("Invalid serialized object reference");
                }
                return this._pdgDeserializedObjects[referenceIndex];
            }
            if (serializationType !== tagObject) throw new Error("Serialized data does not contain an object");
            var classTag = this.deserialize_4u();
            var serializedClassCount = this.deserialize_2u();
            this.deserialize_uint();
            if (serializedClassCount === 0) throw new Error("Unregistered serializable class tag " + classTag);
            var constructor = serializableClasses[classTag];
            if (!constructor) throw new Error("Unregistered serializable class tag " + classTag);
            var obj = new constructor();
            if (!obj) throw new TypeError("Serializable constructor must return an object");
            this._pdgDeserializedObjects.push(obj);
            deserializeObjectData(obj, this);
            return obj;
        };
    })();
}

if (typeof bindings.GraphicsManager != "undefined") {  // might be non-gui build
	bindings.gfx = bindings.getGraphicsManager();
	bindings.hasGraphics = true;
} else {
	bindings.hasGraphics = false;
}
if (typeof bindings.SoundManager != "undefined") {  // might be non-gui build
	bindings.snd = bindings.getSoundManager();
	bindings.hasSound = true;
} else {
	bindings.hasSound = false;
}

// Note: Get these AFTER fixing prototype chains so we get the correct prototypes
//var fileManagerProto;
//var timerManagerProto;

// Fix constructor relationships and toString() behavior for instanceof checks and make-idl.js
// This approach preserves native method bindings while fixing type identification

function fixManagerConstructorAndToString(instance, ConstructorClass, className) {
    // Fix the constructor property on the instance to point to the correct constructor
    Object.defineProperty(instance, 'constructor', {
        value: ConstructorClass,
        writable: true,
        configurable: true
    });
    
    // Set Symbol.toStringTag for proper toString() behavior
    if (typeof Symbol !== 'undefined' && Symbol.toStringTag) {
        // Set it on the actual prototype that the instance uses
        var instanceProto = Object.getPrototypeOf(instance);
        if (instanceProto && !instanceProto.hasOwnProperty(Symbol.toStringTag)) {
            Object.defineProperty(instanceProto, Symbol.toStringTag, {
                value: className,
                configurable: true
            });
        }
        
        // Also set it on the public constructor's prototype for new instances
        if (ConstructorClass.prototype && !ConstructorClass.prototype.hasOwnProperty(Symbol.toStringTag)) {
            Object.defineProperty(ConstructorClass.prototype, Symbol.toStringTag, {
                value: className,
                configurable: true
            });
        }
    }
    
    // Fix instanceof by making the public constructor's prototype the same object
    // as the instance's prototype. This ensures instanceof works properly.
    var instanceProto = Object.getPrototypeOf(instance);
    var publicProto = ConstructorClass.prototype;
    
    if (instanceProto && publicProto && instanceProto !== publicProto) {
        // Replace the public constructor's prototype with the instance's prototype
        // This makes instanceof work: instance instanceof Constructor
        ConstructorClass.prototype = instanceProto;
        
        // Ensure the constructor property on the prototype points back to the constructor
        if (!instanceProto.hasOwnProperty('constructor')) {
            Object.defineProperty(instanceProto, 'constructor', {
                value: ConstructorClass,
                writable: true,
                configurable: true
            });
        }
    }
}

// Fix all manager instances  
fixManagerConstructorAndToString(bindings.fs, bindings.FileManager, 'FileManager');
fixManagerConstructorAndToString(bindings.tm, bindings.TimerManager, 'TimerManager');
fixManagerConstructorAndToString(bindings.evt, bindings.EventManager, 'EventManager');
fixManagerConstructorAndToString(bindings.res, bindings.ResourceManager, 'ResourceManager');
fixManagerConstructorAndToString(bindings.cfg, bindings.ConfigManager, 'ConfigManager');
fixManagerConstructorAndToString(bindings.lm, bindings.LogManager, 'LogManager');

bindings.lm.init_CreateUniqueNewFile = bindings.init_CreateUniqueNewFile;
bindings.lm.init_OverwriteExisting = bindings.init_OverwriteExisting;
bindings.lm.init_AppendToExisting = bindings.init_AppendToExisting;
bindings.lm.init_StdOut = bindings.init_StdOut;
bindings.lm.init_StdErr = bindings.init_StdErr;

if (inbrowser) {
    (function(proto) {
        proto.setLanguage = function(language) {
            if (language === null) return this;
            if (typeof language === "undefined") throw new TypeError("language is required");
            this._setLanguage(language);
            return this;
        };
        proto.openResourceFile = function(filename) {
            if (filename === null) return 0;
            if (typeof filename === "undefined") throw new TypeError("filename is required");
            return this._openResourceFile(filename);
        };
        proto.getString = function(id, substring) {
            return this._getString(id, typeof substring === "undefined" ? -1 : substring);
        };
        proto.getResourceSize = function(resourceName) {
            return this._getResourceSize(resourceName);
        };
        proto.getResource = function(resourceName, maxSize) {
            return this._getResource(resourceName, typeof maxSize === "undefined" ? -1 : maxSize);
        };
        proto.getImage = function(imageName) {
            return this._getImage(imageName);
        };
        proto.getImageStrip = function(imageName) {
            return this._getImageStrip(imageName);
        };
        if (typeof proto._getSound === "function") {
            proto.getSound = function(soundName) { return this._getSound(soundName); };
        }
    })(bindings.ResourceManager.prototype);
}

if (bindings.hasGraphics) {
    fixManagerConstructorAndToString(bindings.gfx, bindings.GraphicsManager, 'GraphicsManager');

    if (inbrowser) {
        (function() {
            bindings._emscriptenPortsById = new Map();
            function rememberPort(port) {
                if (port && typeof port._getNativeIdentity === "function") {
                    bindings._emscriptenPortsById.set(port._getNativeIdentity(), port);
                }
                return port;
            }
            var graphicsProto = bindings.GraphicsManager.prototype;
            var nativeCreateWindowPort = graphicsProto._createWindowPort;
            var nativeCreateFont = graphicsProto._createFont;
            var nativeGetCurrentScreenMode = graphicsProto.getCurrentScreenMode;
            var nativeGetScreenBounds = graphicsProto.getScreenBounds;
            var nativeGetNumSupportedScreenModes = graphicsProto.getNumSupportedScreenModes;
            var nativeGetNthSupportedScreenMode = graphicsProto.getNthSupportedScreenMode;
            var nativeGetMouse = graphicsProto.getMouse;
            var nativeSetTargetFPS = graphicsProto.setTargetFPS;
            graphicsProto.createWindowPort = function(rect, name, bpp) {
                return rememberPort(nativeCreateWindowPort.call(this, rect,
                    typeof name === "undefined" ? "" : name,
                    typeof bpp === "undefined" ? 0 : bpp));
            };
            graphicsProto.createFont = function(name, scalingFactor) {
                return nativeCreateFont.call(this, name,
                    typeof scalingFactor === "undefined" ? 1.0 : scalingFactor);
            };
            graphicsProto.getCurrentScreenMode = function(screenNum) {
                return nativeGetCurrentScreenMode.call(this,
                    typeof screenNum === "undefined" ? -1 : screenNum);
            };
            graphicsProto.getScreenBounds = function(screenNum) {
                return new bindings.Rect(nativeGetScreenBounds.call(this,
                    typeof screenNum === "undefined" ? -1 : screenNum));
            };
            graphicsProto.getNumSupportedScreenModes = function(screenNum) {
                return nativeGetNumSupportedScreenModes.call(this,
                    typeof screenNum === "undefined" ? -1 : screenNum);
            };
            graphicsProto.getNthSupportedScreenMode = function(n, screenNum) {
                return nativeGetNthSupportedScreenMode.call(this, n,
                    typeof screenNum === "undefined" ? -1 : screenNum);
            };
            graphicsProto.getMouse = function(mouseNumber) {
                return new bindings.Point(nativeGetMouse.call(this,
                    typeof mouseNumber === "undefined" ? 0 : mouseNumber));
            };
            graphicsProto.setTargetFPS = function(fps) {
                nativeSetTargetFPS.call(this, fps);
                return this;
            };

            var portProto = bindings.Port.prototype;
            portProto.clear = function(color) { this._clear(color || new bindings.Color(0,0,0,0)); };
            portProto.setDrawingOrigin = function(origin) { this._setDrawingOrigin(origin); };
            var nativeGetDrawingArea = portProto.getDrawingArea;
            var nativeGetClipRect = portProto.getClipRect;
            var nativeGetTextWidth = portProto._getTextWidth;
            var nativeSetClipRect = portProto.setClipRect;
            var nativeGetCurrentFont = portProto.getCurrentFont;
            var nativeSetFontForStyle = portProto.setFontForStyle;
            var nativeSetFont = portProto.setFont;
            portProto.getDrawingArea = function() {
                return new bindings.Rect(nativeGetDrawingArea.call(this));
            };
            portProto.getClipRect = function() {
                return new bindings.Rect(nativeGetClipRect.call(this));
            };
            portProto.getTextWidth = function(text, size, style, len) {
                return nativeGetTextWidth.call(this, text, size,
                    typeof style === "undefined" ? bindings.textStyle_Plain : style,
                    typeof len === "undefined" ? -1 : len);
            };
            portProto.getCurrentFont = function(style) {
                return nativeGetCurrentFont.call(this,
                    typeof style === "undefined" ? bindings.textStyle_Plain : style);
            };
            portProto.setFontForStyle = function(style, font) {
                nativeSetFontForStyle.call(this, font, style);
                return this;
            };
            portProto.setFont = function(font) {
                nativeSetFont.call(this, typeof font === "undefined" ? null : font);
                return this;
            };
            portProto.setClipRect = function(rect) {
                nativeSetClipRect.call(this, rect);
                return this;
            };
            ["drawLine", "drawRect", "drawQuad", "drawPolygon", "drawSpline",
             "drawCircle", "drawEllipse", "drawArc", "drawImage", "drawDrawing",
             "drawText", "drawSphere"].forEach(function(method) {
                var nativeDraw = portProto[method];
                portProto[method] = function() {
                    nativeDraw.apply(this, arguments);
                    return this;
                };
            });

            var fontProto = bindings.Font.prototype;
            ["Height", "Leading", "Ascent", "Descent", "CapHeight"].forEach(function(metric) {
                var nativeMetric = fontProto["_getFont" + metric];
                fontProto["getFont" + metric] = function(size, style) {
                    return nativeMetric.call(this, size,
                        typeof style === "undefined" ? bindings.textStyle_Plain : style);
                };
            });
        })();
        bindings.getGraphicsManager = function() { return bindings.gfx; };
        var nativeCreateSpriteLayer = bindings.createSpriteLayer;
        bindings.createSpriteLayer = function(port) {
            return typeof port === "undefined"
                ? nativeCreateSpriteLayer()
                : bindings._createSpriteLayerForPort(port);
        };
        var nativeCreateTileLayer = bindings.createTileLayer;
        bindings.createTileLayer = function(port) {
            return typeof port === "undefined"
                ? nativeCreateTileLayer()
                : bindings._createTileLayerForPort(port);
        };
    }
}
if (bindings.hasSound) {
    fixManagerConstructorAndToString(bindings.snd, bindings.SoundManager, 'SoundManager');
    if (inbrowser) {
        bindings.getSoundManager = function() { return bindings.snd; };
        bindings.Sound.prototype.play = function(volume, offsetX, pitch, fromMs, lengthMs) {
            this._play(typeof volume === "undefined" ? 1.0 : volume,
                typeof offsetX === "undefined" ? 0 : offsetX,
                typeof pitch === "undefined" ? 0.0 : pitch,
                typeof fromMs === "undefined" ? 0 : fromMs,
                typeof lengthMs === "undefined" ? -1 : lengthMs);
        };
    }
}

// Now get the prototype references (after fixing, these should be the same objects)
var fileManagerProto = bindings.FileManager.prototype;
var timerManagerProto = bindings.TimerManager.prototype;

if (inbrowser) {
    (function() {
        var emitterStates = new WeakMap();
        var emitterTypes = [
            bindings.EventEmitter,
            bindings.EventManager,
            bindings.TimerManager,
            bindings.Sprite,
            bindings.Particle,
            bindings.SpriteLayer,
            bindings.TileLayer
        ];

        if (typeof bindings.Sound !== "undefined") {
            emitterTypes.push(bindings.Sound);
        }

        function BrowserEventHandler(callback) {
            if (!(this instanceof BrowserEventHandler)) {
                return new BrowserEventHandler(callback);
            }
            if (typeof callback !== "function") {
                throw new TypeError("IEventHandler requires a callback function");
            }
            this.callback = callback;
        }

        BrowserEventHandler.prototype.handleEvent = function(event) {
            var handled = this.callback.call(this, event);
            if (typeof handled !== "boolean") {
                throw new TypeError("event handlers must return true or false");
            }
            return handled;
        };

        function getEmitterState(emitter) {
            var state = emitterStates.get(emitter);
            if (!state) {
                state = {
                    handlers: Object.create(null),
                    blocked: Object.create(null),
                    nativeBridges: Object.create(null)
                };
                emitterStates.set(emitter, state);
            }
            return state;
        }

        function addHandler(handler, eventType) {
            if (!handler || typeof handler.handleEvent !== "function") {
                throw new TypeError("addHandler requires an IEventHandler");
            }
            if (typeof eventType === "undefined") eventType = bindings.all_events;
            var state = getEmitterState(this);
            var handlers = state.handlers;
            var list = handlers[eventType] || (handlers[eventType] = []);
            if (!state.nativeBridges[eventType] && typeof this._addNativeEventBridge === "function") {
                this._addNativeEventBridge(eventType, this);
                state.nativeBridges[eventType] = true;
            }
            list.push(handler);
        }

        function removeHandler(handler, eventType) {
            var handlers = getEmitterState(this).handlers;
            var types = (typeof eventType === "undefined") ? Object.keys(handlers) : [String(eventType)];
            types.forEach(function(type) {
                var list = handlers[type];
                if (!list) return;
                handlers[type] = list.filter(function(candidate) {
                    return candidate !== handler;
                });
                if (handlers[type].length === 0) delete handlers[type];
            });
        }

        function clearHandlers() {
            getEmitterState(this).handlers = Object.create(null);
        }

        function blockEvent(eventType) {
            getEmitterState(this).blocked[eventType] = true;
        }

        function unblockEvent(eventType) {
            delete getEmitterState(this).blocked[eventType];
        }

        function dispatchHandlers(list, event) {
            if (!list) return false;
            // Work on a snapshot so callbacks may safely add or remove handlers.
            list = list.slice();
            for (var i = 0; i < list.length; i++) {
                if (list[i].handleEvent(event)) return true;
            }
            return false;
        }

function postEvent(eventType, event) {
    if (!event || typeof event !== "object") {
        event = {};
    }
    event.eventType = eventType;
    if (event && typeof event.portIdentity !== "undefined" &&
        bindings._emscriptenPortsById) {
        event.port = bindings._emscriptenPortsById.get(event.portIdentity) || null;
    }
            ['inLayer', 'targetSprite'].forEach(function(field) {
                if (typeof event[field + 'Identity'] !== 'undefined')
                    event[field] = bindings._emscriptenObjectForIdentity(event[field + 'Identity']);
            });
            if (eventType === bindings.eventType_SpriteCollide) {
                if (event.normal) event.normal = new bindings.Vector(event.normal.x, event.normal.y);
                if (event.impulse) event.impulse = new bindings.Vector(event.impulse.x, event.impulse.y);
            }
            var state = getEmitterState(this);
            if (state.blocked[eventType]) return false;
            if (dispatchHandlers(state.handlers[eventType], event)) return true;
            if (eventType !== bindings.all_events) {
                return dispatchHandlers(state.handlers[bindings.all_events], event);
            }
            return false;
        }

        bindings.IEventHandler = BrowserEventHandler;
        emitterTypes.forEach(function(EmitterType) {
            if (!EmitterType || !EmitterType.prototype) return;
            EmitterType.prototype.addHandler = addHandler;
            EmitterType.prototype.removeHandler = removeHandler;
            EmitterType.prototype.clear = clearHandlers;
            EmitterType.prototype.blockEvent = blockEvent;
            EmitterType.prototype.unblockEvent = unblockEvent;
            EmitterType.prototype.postEvent = postEvent;
            EmitterType.prototype.__dispatchNativeEvent = postEvent;
        });

        function installConvenienceHandler(proto, name, eventType, discriminator, expectedValue) {
            proto[name] = function(callback) {
                if (typeof callback !== "function") throw new TypeError(name + " requires a callback");
                var emitter = this;
                var handler = new BrowserEventHandler(function(event) {
                    if (event && typeof event[discriminator] !== "undefined" && event[discriminator] !== expectedValue) {
                        return false;
                    }
                    return callback.call(emitter, event);
                });
                emitter.addHandler(handler, eventType);
                handler.cancel = function() { emitter.removeHandler(handler, eventType); };
                return handler;
            };
        }

        var spriteActions = {
            onCollideSprite: [bindings.eventType_SpriteCollide, 0],
            onCollideWall: [bindings.eventType_SpriteCollide, 1],
            onOffscreen: [bindings.eventType_SpriteAnimate, 2],
            onOnscreen: [bindings.eventType_SpriteAnimate, 3],
            onExitLayer: [bindings.eventType_SpriteAnimate, 4],
            onAnimationLoop: [bindings.eventType_SpriteAnimate, 8],
            onAnimationEnd: [bindings.eventType_SpriteAnimate, 9],
            onFadeComplete: [bindings.eventType_SpriteAnimate, 10],
            onFadeInComplete: [bindings.eventType_SpriteAnimate, 11],
            onFadeOutComplete: [bindings.eventType_SpriteAnimate, 12],
            onAnimationBlendComplete: [bindings.eventType_SpriteAnimate, 15],
            onAnimationPhysicsRecoveryComplete: [bindings.eventType_SpriteAnimate, 17]
        };
        var touchActions = {
            onMouseEnter: 20,
            onMouseLeave: 21,
            onMouseDown: 22,
            onMouseUp: 23,
            onMouseClick: 24
        };
        var layerActions = {
            onErasePort: 40,
            onPreDrawLayer: 41,
            onPostDrawLayer: 42,
            onDrawPortComplete: 43,
            onAnimationStart: 44,
            onPreAnimateLayer: 45,
            onPostAnimateLayer: 46,
            onAnimationComplete: 47,
            onZoomComplete: 48,
            onLayerFadeInComplete: 49,
            onLayerFadeOutComplete: 50
        };

        [bindings.Sprite.prototype, bindings.SpriteLayer.prototype].forEach(function(proto) {
            Object.keys(spriteActions).forEach(function(name) {
                installConvenienceHandler(proto, name, spriteActions[name][0], "action", spriteActions[name][1]);
            });
            Object.keys(touchActions).forEach(function(name) {
                installConvenienceHandler(proto, name, bindings.eventType_SpriteTouch, "touchType", touchActions[name]);
            });
        });
        Object.keys(layerActions).forEach(function(name) {
            installConvenienceHandler(bindings.SpriteLayer.prototype, name,
                bindings.eventType_SpriteLayer, "action", layerActions[name]);
        });

        var spriterEventStates = new WeakMap();
        var nativeSpriteEnableSpriterEvents = bindings.Sprite.prototype.enableSpriterEvents;
        var nativeSpriteAreSpriterEventsEnabled = bindings.Sprite.prototype.areSpriterEventsEnabled;
        var nativeLayerEnableSpriterEvents = bindings.SpriteLayer.prototype.enableSpriterEvents;
        bindings.Sprite.prototype.enableSpriterEvents = function(enable) {
            var enabled = enable !== false;
            if (typeof nativeSpriteEnableSpriterEvents === "function") {
                nativeSpriteEnableSpriterEvents.call(this, enabled);
            }
            spriterEventStates.set(this, enabled);
            return this;
        };
        bindings.Sprite.prototype.areSpriterEventsEnabled = function() {
            if (typeof nativeSpriteAreSpriterEventsEnabled === "function") {
                return nativeSpriteAreSpriterEventsEnabled.call(this);
            }
            return spriterEventStates.get(this) === true;
        };
        bindings.SpriteLayer.prototype.enableSpriterEvents = function(enable) {
            if (typeof nativeLayerEnableSpriterEvents === "function") {
                nativeLayerEnableSpriterEvents.call(this, enable !== false);
            }
            return this;
        };

        bindings.EventManager.prototype.getDeviceOrientation = function() {
            return { roll: 0, pitch: 0, yaw: 0 };
        };
        bindings.EventManager.prototype.isButtonDown = function() { return false; };
        bindings.EventManager.prototype.isKeyDown = function() { return false; };
        bindings.EventManager.prototype.isRawKeyDown = function() { return false; };
    })();
}

// add methods to the file manager prototypes

function compareFoundNodeNames(left, right) {
	if (left < right) {
		return -1;
	}
	if (left > right) {
		return 1;
	}
	return 0;
}

// file system manager
fileManagerProto.findFiles = function(name) {
	var _sig = methodSignature("", arguments, "string[]", 0, "(string name)"); if (_sig != null) return _sig;
	var files = new Array;
	var fileMgr = bindings.getFileManager();
	var findInfo = fileMgr.findFirst(name);
	if (findInfo && findInfo.found) {
		do {
			if (findInfo.isDirectory == false) {
				files.push(findInfo.nodeName);
			}
		} while (fileMgr.findNext(findInfo));
		fileMgr.findClose(findInfo);
	}
	// Keep results deterministic across platforms for the high-level helpers.
	return files.sort(compareFoundNodeNames);
}
bindings.FileManager.prototype.findFiles = fileManagerProto.findFiles;

fileManagerProto.findDirs = function(name) {
	var _sig = methodSignature("", arguments, "string[]", 0, "(string name)"); if (_sig != null) return _sig;
	var dirs = new Array; 
	var fileMgr = bindings.getFileManager();
	var findInfo = fileMgr.findFirst(name);
	if (findInfo && findInfo.found) {
		do {
			if ( (findInfo.isDirectory == true)
			   && (findInfo.nodeName != '.') 
			   && (findInfo.nodeName != '..') ) {
				dirs.push(findInfo.nodeName);
			}
		} while (fileMgr.findNext(findInfo));
		fileMgr.findClose(findInfo);
	}
	return dirs.sort(compareFoundNodeNames);
}
bindings.FileManager.prototype.findDirs = fileManagerProto.findDirs;

// simple log writer
bindings.log = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(4, "LOG", msg);
}
bindings.info = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(5, "INFO", msg);
}
bindings.warn = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(3, "WARN", msg);
}
bindings.fatal = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(0, "FATAL", msg);
}
bindings.error = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(1, "ERROR", msg);
}
bindings.debug = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(7, "DEBUG", msg);
}
bindings.trace = function(msg) {
	var _sig = methodSignature("", arguments, "undefined", 1, "(string msg)"); if (_sig != null) return _sig;
	bindings.getLogManager().writeLogEntry(9, "TRACE", msg);
}

// replace console log
bindings.captureConsole = function() {
	var _sig = methodSignature("", arguments, "undefined", 1, "()"); if (_sig != null) return _sig;
	console.log = bindings.log
	console.info = bindings.info
	console.warn = bindings.warn
	console.error = bindings.error
}

// serialization utilities

// createSerializableObject(obj, classTag)
// Creates a pdg.ISerializable object from a JavaScript object with serialization methods
// 
// Parameters:
//   obj - JavaScript object with getSerializedSize, serialize, and deserialize methods
//   classTag - uint32 class tag for the serializable object
//
// Returns:
//   pdg.ISerializable object that can be registered with pdg.registerSerializableClass
//
// Example:
//   var obj = {
//     data: "hello",
//     getSerializedSize: function(serializer) { return serializer.sizeof_str(this.data); },
//     serialize: function(serializer) { serializer.serialize_str(this.data); },
//     deserialize: function(deserializer) { this.data = deserializer.deserialize_str(); }
//   };
//   var serializable = pdg.createSerializableObject(obj, 0x12345678);
//   pdg.registerSerializableClass(function() { return serializable; });
bindings.createSerializableObject = function(obj, classTag) {
	var _sig = methodSignature("Creates a pdg.ISerializable object from a JavaScript object with serialization methods", arguments, "[object ISerializable]", 2, "(object obj, [number uint] classTag)"); if (_sig != null) return _sig;
	
	// Validate the object parameter
	if (obj === null || typeof obj !== 'object') {
		throw new Error("First parameter must be an object");
	}
	
	// Check if the object has the required function properties
	if (typeof obj.getSerializedSize !== 'function' ||
		typeof obj.serialize !== 'function' ||
		typeof obj.deserialize !== 'function') {
		throw new Error("Object must have getSerializedSize, serialize, and deserialize function properties");
	}
	
	// Validate the classTag parameter
	if (typeof classTag !== 'number') {
		throw new Error("Class tag must be a number");
	}
	
	if (!Number.isInteger(classTag)) {
		throw new Error("Class tag must be an integer");
	}
	
	if (classTag < 0) {
		throw new Error("Class tag must be a non-negative integer");
	}
	
	if (classTag > 0xFFFFFFFF) {
		throw new Error("Class tag must be a 32-bit unsigned integer (0 to 4294967295)");
	}
	
	// Create the underlying ISerializable object
	var serializable = new bindings.ISerializable(
		obj.getSerializedSize.bind(obj),
		obj.serialize.bind(obj),
		obj.deserialize.bind(obj),
		function() { return classTag; }
	);
	if (inbrowser) {
		Object.defineProperty(serializable, "_pdgRequiresExplicitRegistration", {
			value: true,
			writable: true
		});
	}
	
	// Add the getMyClassTag method as a property
	serializable.getMyClassTag = function() {
		return classTag;
	};
	
	// Copy all properties from the original object
	for (var prop in obj) {
		if (obj.hasOwnProperty(prop)) {
			serializable[prop] = obj[prop];
		}
	}
	
	return serializable;
}


// event manager

// create an IEventHandler with the function and add it to the Event Manager
bindings.on = function(eventType, func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 2, "([number int] eventType, function func)"); if (_sig != null) return _sig;
	var handler = new bindings.IEventHandler(func);
	bindings.getEventManager().addHandler(handler, eventType);
	handler.cancel = function() {
		bindings.getEventManager().removeHandler(handler, eventType);
	};
	return handler;
}

// onStartup(function)
// module.exports.onStartup = function(func) {
// 	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
// 	return this.on(bindings.eventType_Startup, func);
// }
// onShutdown(function)
bindings.onShutdown = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_Shutdown, func);
}
// onTimer(function)
bindings.onTimer = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_Timer, func);
}
// onKeyDown(function)
bindings.onKeyDown = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_KeyDown, func);
}
// onKeyUp(function)
bindings.onKeyUp = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_KeyUp, func);
}
// onKeyPress(function)
bindings.onKeyPress = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_KeyPress, func);
}
// onMouseDown(function)
bindings.onMouseDown = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_MouseDown, func);
}
// onMouseUp(function)
bindings.onMouseUp = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_MouseUp, func);
}
// onMouseMove(function)
bindings.onMouseMove = function(func) {
	var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
	return bindings.on(bindings.eventType_MouseMove, func);
}


var _lastAutoTimerId = 0x7000000;
var _autoTimerHandlers = Object.create(null);

function removeAutoTimerHandler(timerManager, timerId) {
	var handler = _autoTimerHandlers[timerId];
	if (!handler) return;
	timerManager.removeHandler(handler, bindings.eventType_Timer);
	delete _autoTimerHandlers[timerId];
}

var _nativeCancelTimer = timerManagerProto.cancelTimer;
var _nativeCancelAllTimers = timerManagerProto.cancelAllTimers;

timerManagerProto.cancelTimer = function(timerId) {
	removeAutoTimerHandler(this, timerId);
	return _nativeCancelTimer.call(this, timerId);
};
timerManagerProto.cancelTimer._pdgNativeWrapper = true;

timerManagerProto.cancelAllTimers = function() {
	if (arguments.length === 1 && arguments[0] === null) {
		return _nativeCancelAllTimers.call(this, null);
	}
	var timerManager = this;
	Object.keys(_autoTimerHandlers).forEach(function(timerId) {
		removeAutoTimerHandler(timerManager, timerId);
	});
	return _nativeCancelAllTimers.call(this);
};
timerManagerProto.cancelAllTimers._pdgNativeWrapper = true;

// add methods to the timer manager prototypes
// TimerManager.onTimeout(function, delayMs)
timerManagerProto.onTimeout = function(func, delay) {
	var _sig = methodSignature("setup handler to be called once after delay ms", arguments, "[object IEventHandler]", 2, "(function func, [number int] delay)"); if (_sig != null) return _sig;
	var timerId = _lastAutoTimerId++;
	this.startTimer(timerId, delay, bindings.timer_OneShot);
	var handler = new bindings.IEventHandler(function(event) {
		if (event.id != timerId) return false; // timer event was not for us
		try {
			func(event);
		} finally {
			removeAutoTimerHandler(this, timerId);
		}
		return true;  // we are the only handler to handle this event
	}.bind(this));
	_autoTimerHandlers[timerId] = handler;
	this.addHandler(handler, bindings.eventType_Timer);
	handler.cancel = function() {
		this.cancelTimer(timerId);
	}.bind(this);
	handler.timer = timerId;  // so we can pass it to timer manager functions
	return handler;
}
bindings.TimerManager.prototype.onTimeout = timerManagerProto.onTimeout;

// TimerManager.onInterval(function, intervalMs)
timerManagerProto.onInterval = function(func, interval) {
	var _sig = methodSignature("setup handler to be called regularly at interval ms", arguments, "[object IEventHandler]", 2, "(function func, [number int] interval)"); if (_sig != null) return _sig;
	var timerId = _lastAutoTimerId++;
	this.startTimer(timerId, interval, bindings.timer_Repeating);
	var handler = new bindings.IEventHandler(function(event) {
		if (event.id != timerId) return false; // timer event was not for us
		func(event);
		return true; // we are the only handler to handle this event
	}.bind(this));
	_autoTimerHandlers[timerId] = handler;
	this.addHandler(handler, bindings.eventType_Timer);
	handler.cancel = function() {
		this.cancelTimer(timerId);
	}.bind(this);
	handler.timer = timerId;  // so we can pass it to timer manager functions
	return handler;
}
bindings.TimerManager.prototype.onInterval = timerManagerProto.onInterval;

if (inbrowser) {
    (function(timerManager) {
        var timers = Object.create(null);
        var managerPaused = false;

        function now() {
            return Date.now();
        }

        function clearScheduled(timer) {
            if (timer.handle !== null) {
                clearTimeout(timer.handle);
                timer.handle = null;
            }
        }

        function schedule(timer, delay) {
            clearScheduled(timer);
            timer.remaining = Math.max(0, delay);
            timer.nextFire = now() + timer.remaining;
            timer.generation++;
            if (timer.paused || managerPaused) return;
            timer.handle = setTimeout(function() { fire(timer.id); }, timer.remaining);
        }

        function fire(id) {
            var timer = timers[id];
            if (!timer || timer.paused || managerPaused) return;
            timer.handle = null;
            var firedAt = now();
            var elapsed = Math.max(1, firedAt - timer.lastFire);
            timer.lastFire = firedAt;
            var generation = timer.generation;
            timer.firing = true;
            if (timer.callback) {
                timer.callback({ id: timer.id, millisec: firedAt, msElapsed: elapsed });
            }
            timer.firing = false;
            if (timers[id] !== timer) return;
            if (timer.generation !== generation) return;
            if (timer.oneShot) {
                delete timers[id];
            } else {
                schedule(timer, timer.delay);
            }
        }

        timerManager.getMilliseconds = now;

        timerManager.startTimer = function(id, delay, oneShot) {
            var timer = timers[id];
            if (!timer) {
                timer = timers[id] = {
                    id: id,
                    callback: null,
                    handle: null,
                    generation: 0,
                    paused: false,
                    firing: false,
                    lastFire: now(),
                    remaining: delay,
                    nextFire: 0
                };
            }
            timer.delay = Math.max(0, delay);
            timer.oneShot = oneShot !== false && oneShot !== bindings.timer_Repeating;
            timer.paused = false;
            timer.lastFire = now();
            schedule(timer, timer.delay);
        };

        timerManager.cancelTimer = function(id) {
            var timer = timers[id];
            if (!timer) return;
            clearScheduled(timer);
            delete timers[id];
        };

        timerManager.cancelAllTimers = function() {
            Object.keys(timers).forEach(function(id) { timerManager.cancelTimer(id); });
            managerPaused = false;
        };

        timerManager.delayTimer = function(id, additionalDelay) {
            var timer = timers[id];
            if (!timer) return;
            var baseDelay = timer.handle !== null
                ? Math.max(0, timer.nextFire - now())
                : timer.delay;
            schedule(timer, baseDelay + Math.max(0, additionalDelay));
        };

        timerManager.delayTimerUntil = function(id, fireTime) {
            var timer = timers[id];
            if (!timer) return;
            schedule(timer, Math.max(0, fireTime - now()));
            timer.nextFire = fireTime;
        };

        timerManager.pauseTimer = function(id) {
            var timer = timers[id];
            if (!timer || timer.paused) return;
            timer.remaining = Math.max(0, timer.nextFire - now());
            timer.paused = true;
            timer.generation++;
            clearScheduled(timer);
        };

        timerManager.unpauseTimer = function(id) {
            var timer = timers[id];
            if (!timer || !timer.paused) return;
            timer.paused = false;
            schedule(timer, timer.remaining);
        };

        timerManager.isTimerPaused = function(id) {
            var timer = timers[id];
            return !!timer && (timer.paused || managerPaused);
        };

        timerManager.pause = function() {
            if (managerPaused) return;
            managerPaused = true;
            Object.keys(timers).forEach(function(id) {
                var timer = timers[id];
                timer.remaining = Math.max(0, timer.nextFire - now());
                timer.generation++;
                clearScheduled(timer);
            });
        };

        timerManager.unpause = function() {
            if (!managerPaused) return;
            managerPaused = false;
            Object.keys(timers).forEach(function(id) {
                var timer = timers[id];
                if (!timer.paused) schedule(timer, timer.remaining);
            });
        };

        timerManager.isPaused = function() {
            return managerPaused;
        };

        timerManager.getWhenTimerFiresNext = function(id) {
            var timer = timers[id];
            return (!timer || timer.paused || managerPaused) ? bindings.timer_Never : timer.nextFire;
        };

        timerManager.onTimeout = function(callback, delay) {
            var id = _lastAutoTimerId++;
            timerManager.startTimer(id, delay, true);
            timers[id].callback = callback;
            return {
                timer: id,
                cancel: function() { timerManager.cancelTimer(id); }
            };
        };

        timerManager.onInterval = function(callback, delay) {
            var id = _lastAutoTimerId++;
            timerManager.startTimer(id, delay, false);
            timers[id].callback = callback;
            return {
                timer: id,
                cancel: function() { timerManager.cancelTimer(id); }
            };
        };
    })(bindings.tm);
}

if (typeof bindings.Sound != "undefined") {  // might be non-gui build

	// add methods to the sound manager prototypes
	var soundManagerProto = bindings.snd.constructor.prototype;

    // Sound.on(eventCode, function)
    //
    // creates an IEventHander for the sound events with the function
    // and add it to the sound.
    soundManagerProto.on = function(eventCode, func) {
        var _sig = methodSignature("", arguments, "[object IEventHandler]", 2, "([number int] eventCode, function func)"); if (_sig != null) return _sig;
        var handler = new bindings.IEventHandler(function(event) {
                                                 if (event.eventCode != eventCode) return false;
                                                 return func(event);
                                                 }.bind(this));
        this.addHandler(handler, bindings.eventType_SoundEvent);
        handler.cancel = function() {
            this.removeHandler(handler, eventType);
        }.bind(this);
        return handler;
    }
	bindings.Sound.prototype.on = soundManagerProto.on;
    
    // Sound.onDonePlaying(function)
    soundManagerProto.onDonePlaying = function(func) {
        var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
        return this.on(bindings.soundEvent_DonePlaying, func);
    }
	bindings.Sound.prototype.onDonePlaying = soundManagerProto.onDonePlaying;

    // Sound.onLooping(function)
    soundManagerProto.onLooping = function(func) {
        var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
        return this.on(bindings.soundEvent_Looping, func);
    }
	bindings.Sound.prototype.onLooping = soundManagerProto.onLooping;

    // Sound.onFailedToPlay(function)
    soundManagerProto.onFailedToPlay = function(func) {
        var _sig = methodSignature("", arguments, "[object IEventHandler]", 1, "(function func)"); if (_sig != null) return _sig;
        return this.on(bindings.soundEvent_FailedToPlay, func);
    }
	bindings.Sound.prototype.onFailedToPlay = soundManagerProto.onFailedToPlay;
    
} // !sound undefined


// debugger support

if (!jsc && !inbrowser) {
    bindings.onKeyPress(function(evt) {
        if (evt.ctrl && evt.unicode == bindings.key_Delete) {
            // start the debugger
            bindings.openDebugger();
            return true; // we handled this event, don't pass it on
        } else if (evt.alt && evt.unicode == bindings.key_Escape) {
            // open up a console
            bindings.openConsole();
            return true; // we handled this event, don't pass it on
        }
        return false;
    });
}

// Copy everything from process.pdg to module.exports for compatibility
_debug_log('[PDG] pdg.js: Final step - copying from bindings to module.exports');
_debug_log('[PDG] pdg.js: process.pdg has ' + Object.keys(process.pdg).length + ' properties before copy');
_debug_log('[PDG] pdg.js: bindings has ' + Object.keys(bindings).length + ' properties before copy');
// console.log('[PDG] pdg.js: process.pdg has tm?', typeof bindings.tm);
// console.log('[PDG] pdg.js: process.pdg has getResourceManager?', typeof bindings.getResourceManager);

// Shared borrowed-pose facade for V8, JSC and WebAssembly.
(function() {
var proto = bindings.Sprite && bindings.Sprite.prototype;
if (!proto || typeof proto.addAnimationModifier !== 'function') return;
var depth = 0;
function integer(value, low, high, label) {
    if (typeof value !== 'number' || !isFinite(value) || Math.floor(value) !== value ||
        value < low || value > high)
        throw new RangeError('Invalid ' + label);
    return value;
}
function transform(value) {
    var result = {};
    ['x', 'y', 'rotation', 'scaleX', 'scaleY', 'alpha'].forEach(function(key) {
        if (!value || typeof value[key] !== 'number' || !isFinite(value[key]))
            throw new TypeError('Invalid transform ' + key);
        result[key] = value[key];
    });
    if (result.alpha < 0 || result.alpha > 1) throw new RangeError('Invalid transform alpha');
    return result;
}
function compose(parent, local) {
    var c = Math.cos(parent.rotation), s = Math.sin(parent.rotation);
    return transform({
        x: parent.x + local.x * parent.scaleX * c - local.y * parent.scaleY * s,
        y: parent.y + local.x * parent.scaleX * s + local.y * parent.scaleY * c,
        rotation: parent.rotation +
            (parent.scaleX * parent.scaleY < 0 ? -local.rotation : local.rotation),
        scaleX: parent.scaleX * local.scaleX,
        scaleY: parent.scaleY * local.scaleY,
        alpha: parent.alpha * local.alpha
    });
}


['seekAnimation', 'transitionToAnimation'].forEach(function(name) {
    var original = proto[name];
    proto[name] = function(clip, seconds, duration) {
        if (arguments.length === 1 && clip === null) return original.call(this, null);
        if (depth) throw new Error(name + ' must occur outside an animation modifier');
        if (typeof clip !== 'string' || typeof seconds !== 'number' || !isFinite(seconds))
            throw new TypeError('Animation clip and finite seconds are required');
        if (name === 'transitionToAnimation') {
            if (typeof duration !== 'number' || !isFinite(duration) || duration < 0)
                throw new TypeError('Transition duration must be nonnegative seconds');
            return original.call(this, clip, seconds, duration);
        }
        return original.call(this, clip, seconds);
    };
});


function finiteTarget(value, label) {
    if (typeof value !== 'number' || !isFinite(value)) throw new TypeError('Invalid ' + label);
    return value;
}
function positiveTime(value) {
    finiteTarget(value, 'seconds');
    if (value < 0) throw new RangeError('Seconds must be nonnegative');
    return value;
}
bindings.AnimationSpringTarget = function AnimationSpringTarget(mass, stiffness, damping) {
    if (!(this instanceof bindings.AnimationSpringTarget))
        return new bindings.AnimationSpringTarget(mass, stiffness, damping);
    if (arguments.length === 1 && mass === null)
        mass = undefined;  // runtime API metadata inspection
    mass = typeof mass === 'undefined' ? 1 : finiteTarget(mass, 'mass');
    stiffness = typeof stiffness === 'undefined' ? 100 : finiteTarget(stiffness, 'stiffness');
    damping = typeof damping === 'undefined' ? 20 : finiteTarget(damping, 'damping');
    if (mass <= 0 || stiffness < 0 || damping < 0 || !isFinite(stiffness / mass) ||
        !isFinite(damping / mass) || !isFinite(Math.pow(damping / (2 * mass), 2)))
        throw new RangeError('Invalid spring coefficients');
    var state = {x: 0, y: 0, velocityX: 0, velocityY: 0};
    function copy() {
        return {x: state.x, y: state.y, velocityX: state.velocityX, velocityY: state.velocityY};
    }
    function setState(value) {
        var next = {};
        Object.keys(state).forEach(function(key) {
            next[key] = finiteTarget(value[key], 'spring ' + key);
        });
        state = next;
    }
    function step(position, velocity, target, dt) {
        var a = damping / (2 * mass), w2 = stiffness / mass, disc = a * a - w2,
            y = position - target, v = velocity, nextY, nextV;
        if (stiffness === 0) {
            if (damping === 0) {
                nextY = y + v * dt;
                nextV = v;
            } else {
                var factor = Math.exp(-damping / mass * dt);
                nextY = y + v * (-Math.expm1(-damping / mass * dt)) / (damping / mass);
                nextV = v * factor;
            }
        } else if (Math.abs(disc) <= 1e-12 * Math.max(1, w2)) {
            var b = v + a * y, e = Math.exp(-a * dt);
            nextY = e * (y + b * dt);
            nextV = e * (v - a * b * dt);
        } else if (disc < 0) {
            var w = Math.sqrt(-disc), c = Math.cos(w * dt), s = Math.sin(w * dt),
                e = Math.exp(-a * dt);
            nextY = e * (y * c + (v + a * y) * s / w);
            nextV = e * (v * c - (a * v + w2 * y) * s / w);
        } else {
            var d = Math.sqrt(disc), r1 = -w2 / (a + d), r2 = -a - d, c1 = (v - r2 * y) / (r1 - r2),
                c2 = y - c1, e1 = Math.exp(r1 * dt), e2 = Math.exp(r2 * dt);
            nextY = c1 * e1 + c2 * e2;
            nextV = r1 * c1 * e1 + r2 * c2 * e2;
        }
        return [target + nextY, nextV];
    }
    Object.assign(this, {
        getState: copy,
        setState: setState,
        applyImpulse: function(x, y) {
            finiteTarget(x, 'impulse');
            finiteTarget(y, 'impulse');
            var next = copy();
            next.velocityX += x / mass;
            next.velocityY += y / mass;
            setState(next);
        },
        update: function(x, y, deltaSeconds) {
            finiteTarget(x, 'target');
            finiteTarget(y, 'target');
            positiveTime(deltaSeconds);
            if (deltaSeconds === 0) return copy();
            var px = step(state.x, state.velocityX, x, deltaSeconds),
                py = step(state.y, state.velocityY, y, deltaSeconds);
            setState({x: px[0], y: py[0], velocityX: px[1], velocityY: py[1]});
            return copy();
        }
    });
};
bindings.AnimationContactTarget = function AnimationContactTarget() {
    if (!(this instanceof bindings.AnimationContactTarget))
        return new bindings.AnimationContactTarget();
    var state = {x: 0, y: 0, influence: 0, locked: false}, support = 0, localX = 0, localY = 0,
        remaining = 0, duration = 0;
    function copy() {
        return {x: state.x, y: state.y, influence: state.influence, locked: state.locked};
    }
    function world(x, y) {
        finiteTarget(x, 'contact');
        finiteTarget(y, 'contact');
        state = {x: x, y: y, influence: 1, locked: true};
        support = 0;
        remaining = duration = 0;
    }
    function release(seconds) {
        seconds = typeof seconds === 'undefined' ? 0 : positiveTime(seconds);
        if (!state.locked) return;
        state.locked = false;
        support = 0;
        remaining = duration = seconds;
        if (seconds === 0) state.influence = 0;
    }
    Object.assign(this, {
        getState: copy,
        lockWorld: world,
        lockPlatform: function(x, y, id, frame) {
            integer(id, 1, 9007199254740991, 'support ID');
            frame = transform(frame);
            if (!frame.scaleX || !frame.scaleY) throw new RangeError('Singular platform frame');
            finiteTarget(x, 'contact');
            finiteTarget(y, 'contact');
            var dx = x - frame.x, dy = y - frame.y, c = Math.cos(frame.rotation),
                s = Math.sin(frame.rotation);
            var lx = finiteTarget((c * dx + s * dy) / frame.scaleX, 'platform x'),
                ly = finiteTarget((-s * dx + c * dy) / frame.scaleY, 'platform y');
            world(x, y);
            support = id;
            localX = lx;
            localY = ly;
        },
        release: release,
        update: function(deltaSeconds, contactActive, withinReach, id, frame, releaseSeconds) {
            positiveTime(deltaSeconds);
            releaseSeconds =
                typeof releaseSeconds === 'undefined' ? 0 : positiveTime(releaseSeconds);
            if (typeof contactActive !== 'boolean' || typeof withinReach !== 'boolean')
                throw new TypeError('Contact and reach flags must be boolean');
            id = typeof id === 'undefined' ? 0 : integer(id, 0, 9007199254740991, 'support ID');
            if (state.locked && (!contactActive || !withinReach || (support && support !== id)))
                release(releaseSeconds);
            if (state.locked && support) {
                frame = transform(frame);
                if (!frame.scaleX || !frame.scaleY) throw new RangeError('Singular platform frame');
                var point = compose(
                    frame, {x: localX, y: localY, rotation: 0, scaleX: 1, scaleY: 1, alpha: 1});
                state.x = point.x;
                state.y = point.y;
            }
            if (!state.locked && duration > 0) {
                remaining = Math.max(0, remaining - deltaSeconds);
                state.influence = remaining / duration;
            }
            return copy();
        }
    });
};
bindings.animationHasTag = function(pose, object, tag) {
    if (!pose || !Array.isArray(pose.tags) || typeof object !== 'string' || typeof tag !== 'string')
        throw new TypeError('Expected owned pose metadata and tag names');
    return pose.tags.some(function(group) {
        return group.object === object && group.tags.indexOf(tag) >= 0;
    });
};

var nativeDrawing = proto.addAnimationDrawable;
proto.addAnimationDrawable = function(callback, options) {
    if (arguments.length === 1 && callback === null) return nativeDrawing.call(this, null);
    if ((typeof callback !== 'function' && !(bindings.Drawing && callback instanceof bindings.Drawing)) || !options || typeof options !== 'object')
        throw new TypeError('Drawing or callback and options are required');
    var names = this.getAnimationBoneNames(),
        bone = typeof options.bone === 'string' ? names.indexOf(options.bone) : options.bone;
    integer(bone, 0, names.length - 1, 'drawing bone');
    var placement = typeof options.placement === 'undefined' ?
        bindings.animationDraw_AfterAll :
        integer(options.placement, 0, 4, 'drawing placement');
    var order = typeof options.order === 'undefined' ?
        0 :
        integer(options.order, -2147483648, 2147483647, 'drawing order');
    var slot = typeof options.slot === 'undefined' ? '' : options.slot;
    if (typeof slot !== 'string') throw new TypeError('Drawing slot must be a name');
    var bounds = options.bounds,
        uncullable = typeof options.uncullable === 'undefined' ? !bounds : options.uncullable;
    if (typeof uncullable !== 'boolean')
        throw new TypeError('Drawing uncullable flag must be boolean');
    var data = [bone, placement, order, uncullable ? 1 : 0];
    ['left', 'top', 'right', 'bottom'].forEach(function(key) {
        data.push(bounds ? finiteTarget(bounds[key], 'drawing bounds') : 0);
    });
    data.push(typeof options.strokeSpace === 'undefined' ? bindings.animationStroke_PortPixels :
        integer(options.strokeSpace, 0, 1, 'drawing stroke space'));
    if (typeof callback !== 'function') return nativeDrawing.call(this, callback, data, slot);
    function bridge(snapshot, local, rig, world) {
        var active = true;
        function check() {
            if (!active) throw new Error('Animation drawing context has expired');
        }
        var context = Object.freeze({
            getTransform: function(space) {
                check();
                space = typeof space === 'undefined' ? bindings.animationSpace_World :
                    integer(space, 0, 2, 'drawing coordinate space');
                return transform([local, rig, world][space]);
            },
            copyPose: function() { check(); return JSON.parse(JSON.stringify(snapshot)); }
        });
        ++depth;
        try {
            var result = callback(context);
            if (result && typeof result.then === 'function') {
                if (typeof result.catch === 'function') result.catch(function() {});
                throw new Error('Animation drawing callbacks must be synchronous');
            }
            if (result !== null && !(bindings.Drawing && result instanceof bindings.Drawing))
                throw new TypeError('Animation drawing callback must return a Drawing or null');
            return result;
        } catch (error) {
            return String(error && error.message ? error.message : error);
        } finally {
            active = false;
            --depth;
        }
    }
    return nativeDrawing.call(this, bridge, data, slot);
};
['removeAnimationDrawable', 'getAnimationDrawableError'].forEach(function(name) {
    var original = proto[name];
    proto[name] = function(id) {
        if (arguments.length === 1 && id === null) return original.call(this, null);
        return original.call(this, integer(id, 1, 4294967295, 'drawable ID'));
    };
});
var nativeDrawingEnabled = proto.setAnimationDrawableEnabled;
proto.setAnimationDrawableEnabled = function(id, enabled) {
    if (arguments.length === 1 && id === null) return nativeDrawingEnabled.call(this, null);
    integer(id, 1, 4294967295, 'drawable ID');
    if (typeof enabled !== 'boolean') throw new TypeError('Drawable enabled flag must be boolean');
    return nativeDrawingEnabled.call(this, id, enabled);
};

var nativePhysical = proto.setupAnimationPhysics;
var nativeGeneratedPhysical = proto.setupPhysicsFromAnimationRig;
proto.setupPhysicsFromAnimationRig = function(totalMass, unitsPerMeter) {
    if (arguments.length === 1 && totalMass === null) return nativeGeneratedPhysical.call(this, null);
    unitsPerMeter = typeof unitsPerMeter === 'undefined' ? 1 : unitsPerMeter;
    if (typeof totalMass !== 'number' || !isFinite(totalMass) || totalMass <= 0 ||
        typeof unitsPerMeter !== 'number' || !isFinite(unitsPerMeter) || unitsPerMeter <= 0)
        throw new TypeError('Total mass and unitsPerMeter must be finite positive numbers');
    if (depth) throw new Error('Physical rig changes must occur outside modifiers');
    nativeGeneratedPhysical.call(this,totalMass,unitsPerMeter); return this;
};
var nativePhysicalRoot = proto.setAnimationPhysicsRoot;
var nativeAttachPhysicalPart=proto.attachAnimationPhysicsPart;
proto.attachAnimationPhysicsPart=function(part,parent) {
    if(arguments.length===1 && part===null)return nativeAttachPhysicalPart.call(this,null);
    if(!(part instanceof bindings.Part) || (parent!=null && !(parent instanceof bindings.Part)))throw new TypeError('Expected Part objects');
    if(depth)throw new Error('Change rig membership outside modifiers');
    nativeAttachPhysicalPart.call(this,part,parent==null?null:parent);return this;
};
var nativeDetachPhysicalPart=proto.detachAnimationPhysicsPart;
proto.detachAnimationPhysicsPart=function(part,includeDescendants) {
    if(arguments.length===1 && part===null)return nativeDetachPhysicalPart.call(this,null);
    if(!(part instanceof bindings.Part))throw new TypeError('Expected a Part');
    if(typeof includeDescendants==='undefined')includeDescendants=true;
    if(typeof includeDescendants!=='boolean')throw new TypeError('includeDescendants must be boolean');
    if(depth)throw new Error('Change rig membership outside modifiers');
    nativeDetachPhysicalPart.call(this,part,includeDescendants);return this;
};
var nativeIsPhysicalPartAttached=proto.isAnimationPhysicsPartAttached;
proto.isAnimationPhysicsPartAttached=function(part) {
    if(arguments.length===1 && part===null)return nativeIsPhysicalPartAttached.call(this,null);
    if(!(part instanceof bindings.Part))throw new TypeError('Expected a Part');
    return nativeIsPhysicalPartAttached.call(this,part);
};
proto.setAnimationPhysicsRoot = function(bone) {
    if (arguments.length === 1 && bone === null) return nativePhysicalRoot.call(this,null);
    var names = this.getAnimationBoneNames();
    if (typeof bone === 'string') bone = names.indexOf(bone);
    integer(bone,0,names.length-1,'physical root bone');
    if (depth) throw new Error('Physical root changes must occur outside modifiers');
    nativePhysicalRoot.call(this,bone); return this;
};
var nativeClearPhysicalRoot = proto.clearAnimationPhysicsRoot;
proto.clearAnimationPhysicsRoot = function() {
    if (arguments.length === 1 && arguments[0] === null) return nativeClearPhysicalRoot.call(this,null);
    if (depth) throw new Error('Physical root changes must occur outside modifiers');
    nativeClearPhysicalRoot.call(this); return this;
};
proto.setupAnimationPhysics = function(config) {
    if (config === null) return nativePhysical.call(this, null);
    if (!config || typeof config !== 'object')
        throw new TypeError('Physical rig definition is required');
    if (!Array.isArray(config.bodies) || !config.bodies.length || config.bodies.length > 65536)
        throw new RangeError('Physical rig needs bodies');
    var names = this.getAnimationBoneNames();
    function number(value, fallback) {
        if (typeof value === 'undefined') value = fallback;
        if (typeof value !== 'number' || !isFinite(value))
            throw new TypeError('Physical values must be finite numbers');
        return value;
    }
    function flag(value) {
        if (typeof value === 'undefined') return 0;
        if (typeof value !== 'boolean') throw new TypeError('Physical flags must be boolean');
        return value ? 1 : 0;
    }
    var data = [
        integer(number(config.version, 1), 1, 1, 'physical version'),
        integer(number(config.rootMode, 0), 0, 1, 'physical root mode'),
        integer(number(config.rootBody, 0), 0, config.bodies.length - 1, 'physical root body'),
        flag(config.selfCollisions), config.bodies.length
    ];
    config.bodies.forEach(function(body) {
        if (!body || typeof body !== 'object')
            throw new TypeError('Physical body definition required');
        var bone = typeof body.bone === 'string' ? names.indexOf(body.bone) : body.bone;
        data.push(
            integer(bone, 0, names.length - 1, 'physical bone'),
            integer(number(body.mode, 0), 0, 1, 'physical body mode'));
        // Shape dimensions are authored explicitly; bone display widths never supply them.
        ['mass', 'length', 'radius'].forEach(function(key) {
            data.push(number(body[key]));
        });
        ['offsetX', 'offsetY', 'offsetRotation', 'friction', 'elasticity'].forEach(function(key) {
            data.push(number(body[key], key === 'friction' ? .7 : 0));
        });
        data.push(
            integer(number(body.categories, 4294967295), 0, 4294967295, 'categories'),
            integer(number(body.mask, 4294967295), 0, 4294967295, 'mask'));
    });
    var joints = typeof config.joints === 'undefined' ? [] : config.joints;
    if (!Array.isArray(joints) || joints.length > 65536)
        throw new TypeError('Physical joints must be an array');
    data.push(joints.length);
    joints.forEach(function(joint) {
        if (!joint || typeof joint !== 'object')
            throw new TypeError('Physical joint definition required');
        data.push(
            integer(joint.parent, 0, config.bodies.length - 1, 'joint parent'),
            integer(joint.child, 0, config.bodies.length - 1, 'joint child'));
        ['parentX', 'parentY', 'childX', 'childY'].forEach(function(key) {
            data.push(number(joint[key], 0));
        });
        data.push(
            number(joint.minAngle, -Math.PI), number(joint.maxAngle, Math.PI),
            number(joint.maxForce, 1e6), flag(joint.collide));
    });
    if (depth) throw new Error('Physical rig changes must occur outside modifiers');
    return nativePhysical.call(this, data);
};
function physicalNumber(value, fallback) {
    if(value===undefined)value=fallback;
    if(typeof value!=='number'||!isFinite(value))throw new TypeError('Physical values must be finite numbers');
    return value;
}
function physicalSelection(sprite, bone, descendants, required) {
    if (typeof descendants !== 'undefined' && typeof descendants !== 'boolean') throw new TypeError('includeDescendants must be boolean');
    if (bone === undefined && !required) return -1;
    var names=sprite.getAnimationBoneNames();
    if (typeof bone === 'string') bone=names.indexOf(bone);
    return integer(bone,0,names.length-1,'physical animation bone');
}
var nativePhysicalMode=proto.setAnimationPhysicsMode;
proto.setAnimationPhysicsMode=function(mode,bone,descendants,seconds,direction) {
    if(arguments.length===1 && mode===null)return nativePhysicalMode.call(this,null);
    integer(mode,0,2,'animation physics mode');
    bone=physicalSelection(this,bone,descendants,false);
    seconds=seconds===undefined?0.5:physicalNumber(seconds);
    if(seconds<0)throw new TypeError('Recovery duration must be nonnegative seconds');
    direction=direction===undefined?bindings.rotationDirection_AsSpecified:integer(direction,0,3,'rotation direction');
    if(depth)throw new Error('Physical control changes must occur outside modifiers');
    nativePhysicalMode.call(this,mode,bone,descendants===true,seconds,direction);return this;
};
var nativeGetPhysicalMode=proto.getAnimationPhysicsMode;
proto.getAnimationPhysicsMode=function(bone,descendants) {
    if(arguments.length===1 && bone===null)return nativeGetPhysicalMode.call(this,null);
    return nativeGetPhysicalMode.call(this,physicalSelection(this,bone,descendants,false),descendants===true);
};
var nativeDriveSettings=proto.setAnimationPhysicsDriveSettings;
proto.setAnimationPhysicsDriveSettings=function(settings,bone,descendants) {
    if(arguments.length===1 && settings===null)return nativeDriveSettings.call(this,null);
    if(!settings || typeof settings!=='object' || Array.isArray(settings))throw new TypeError('Drive settings object required');
    bone=physicalSelection(this,bone,descendants,false);
    var force=physicalNumber(settings.maxForce),torque=physicalNumber(settings.maxTorque),frequency=physicalNumber(settings.frequency,4),damping=physicalNumber(settings.dampingRatio,1);
    if(force<0 || torque<0 || frequency<=0 || damping<0)throw new TypeError('Invalid drive settings');
    var direction=settings.direction===undefined?bindings.rotationDirection_Shortest:integer(settings.direction,0,3,'rotation direction');
    if(depth)throw new Error('Physical control changes must occur outside modifiers');
    nativeDriveSettings.call(this,force,torque,frequency,damping,direction,bone,descendants===true);return this;
};
var nativeGetDriveSettings=proto.getAnimationPhysicsDriveSettings;
proto.getAnimationPhysicsDriveSettings=function(bone) {
    if(arguments.length===1 && bone===null)return nativeGetDriveSettings.call(this,null);
    var values=nativeGetDriveSettings.call(this,physicalSelection(this,bone,undefined,true));
    return values===null?null:{maxForce:values[0],maxTorque:values[1],frequency:values[2],dampingRatio:values[3],direction:values[4]};
};
var nativeDisablePhysical = proto.disableAnimationPhysics;
proto.disableAnimationPhysics = function(seconds,direction) {
    if (arguments.length===1 && seconds === null) return nativeDisablePhysical.call(this, null);
    seconds = typeof seconds === 'undefined' ? 0.5 : seconds;
    if (typeof seconds !== 'number' || !isFinite(seconds) || seconds < 0)
        throw new TypeError('Recovery duration must be nonnegative seconds');
    direction=direction===undefined?bindings.rotationDirection_AsSpecified:integer(direction,0,3,'rotation direction');
    if (depth) throw new Error('Physical rig changes must occur outside modifiers');
    return nativeDisablePhysical.call(this, seconds,direction);
};
var nativeIK = proto.addAnimationIK;
proto.addAnimationIK = function(config, order) {
    if (arguments.length === 1 && config === null) return nativeIK.call(this, null);
    if (!config || typeof config !== 'object') throw new TypeError('IK configuration is required');
    var names = this.getAnimationBoneNames(), normalized = {};
    ['root', 'middle', 'tip'].forEach(function(key) {
        var value = config[key];
        if (typeof value === 'string') value = names.indexOf(value);
        normalized[key] = integer(value, 0, names.length - 1, 'IK ' + key);
    });
    var defaults = {
        rootLength: 0,
        middleLength: 0,
        targetX: 0,
        targetY: 0,
        influence: 1,
        space: bindings.animationSpace_Rig,
        bendDirection: 1,
        stretch: bindings.animationIK_NoStretch,
        targetRotation: 0,
        rootMin: -Math.PI,
        rootMax: Math.PI,
        middleMin: -Math.PI,
        middleMax: Math.PI
    };
    Object.keys(defaults).forEach(function(key) {
        var value = config[key];
        if (typeof value === 'undefined') value = defaults[key];
        if (typeof value !== 'number' || !isFinite(value)) throw new TypeError('Invalid IK ' + key);
        normalized[key] = value;
    });
    integer(normalized.space, 0, 2, 'IK space');
    integer(normalized.bendDirection, -1, 1, 'IK bend direction');
    if (normalized.bendDirection === 0) throw new RangeError('IK bend direction must be -1 or 1');
    integer(normalized.stretch, 0, 1, 'IK stretch policy');
    var orientation = config.matchOrientation;
    if (typeof orientation !== 'undefined' && typeof orientation !== 'boolean')
        throw new TypeError('Invalid IK orientation flag');
    normalized.matchOrientation = orientation ? 1 : 0;
    order = typeof order === 'undefined' ? 0 : integer(order, -2147483648, 2147483647, 'IK order');
    return nativeIK.call(this, normalized, order);
};
var nativeTarget = proto.setAnimationIKTarget;
proto.setAnimationIKTarget = function(id, x, y, space) {
    if (arguments.length === 1 && id === null) return nativeTarget.call(this, null);
    integer(id, 1, 4294967295, 'IK ID');
    if (typeof x !== 'number' || !isFinite(x) || typeof y !== 'number' || !isFinite(y))
        throw new TypeError('Invalid IK target');
    space = typeof space === 'undefined' ? bindings.animationSpace_Rig :
                                           integer(space, 0, 2, 'IK space');
    return nativeTarget.call(this, id, x, y, space);
};
var nativeIKResult = proto.getAnimationIKResult;
proto.getAnimationIKResult = function(id) {
    if (arguments.length === 1 && id === null) return nativeIKResult.call(this, null);
    return nativeIKResult.call(this, integer(id, 1, 4294967295, 'IK ID'));
};

var nativeAdd = proto.addAnimationModifier;
proto.addAnimationModifier = function(callback, stage, order) {
    if (arguments.length === 1 && callback === null) return nativeAdd.call(this, null);
    if (typeof callback !== 'function') throw new TypeError('A modifier callback is required');
    stage = typeof stage === 'undefined' ? bindings.animationStage_PreConstraint :
                                           integer(stage, 0, 2, 'modifier stage');
    order = typeof order === 'undefined' ?
        0 :
        integer(order, -2147483648, 2147483647, 'modifier order');
    return nativeAdd.call(this, function(snapshot, context) {
        var active = true;
        function valid() {
            if (!active) throw new Error('Animation pose view has expired; retain copy() instead');
        }
        function boneId(id) {
            valid();
            if (typeof id === 'string') {
                for (var i = 0; i < snapshot.bones.length; ++i)
                    if (snapshot.bones[i].name === id) return i;
                throw new RangeError('Unknown bone ' + id);
            }
            return integer(id, 0, snapshot.bones.length - 1, 'bone ID');
        }
        var view = {
            copy: function() {
                valid();
                return JSON.parse(JSON.stringify(snapshot));
            },
            getLocalTransform: function(id) {
                return transform(snapshot.bones[boneId(id)]);
            },
            setLocalTransform: function(id, value) {
                id = boneId(id);
                var next = transform(value);
                Object.keys(next).forEach(function(key) {
                    snapshot.bones[id][key] = next[key];
                });
            },
            rotateLocal: function(id, angle) {
                if (typeof angle !== 'number' || !isFinite(angle))
                    throw new TypeError('Invalid angle');
                var value = this.getLocalTransform(id);
                value.rotation += angle;
                this.setLocalTransform(id, value);
            },
            getTransform: function(id, space) {
                id = boneId(id);
                space = typeof space === 'undefined' ? bindings.animationSpace_Local :
                                                       integer(space, 0, 2, 'animation space');
                if (space === bindings.animationSpace_Local) return transform(snapshot.bones[id]);
                var chain = [], parent = id;
                while (parent !== null) {
                    chain.push(snapshot.bones[parent]);
                    parent = snapshot.bones[parent].parent;
                }
                var result = space === bindings.animationSpace_World ?
                    transform(context.root) :
                    {x: 0, y: 0, rotation: 0, scaleX: 1, scaleY: 1, alpha: 1};
                for (var i = chain.length - 1; i >= 0; --i) result = compose(result, chain[i]);
                return result;
            }
        };
        Object.freeze(context.root);
        Object.freeze(context);
        Object.freeze(view);
        ++depth;
        try {
            var result = callback(view, context);
            if (result && typeof result.then === 'function') {
                if (typeof result.catch === 'function') result.catch(function() {});
                throw new TypeError('Animation modifiers must be synchronous');
            }
            return snapshot.bones;
        } catch (error) {
            // Catch before crossing the WebAssembly import boundary so native
            // rollback and RAII always run, even when JavaScript throws.
            try {
                return String(error && error.message || error);
            } catch (ignored) {
                return 'Animation modifier script failed';
            }
        } finally {
            active = false;
            --depth;
        }
    }, stage, order);
};
// Destructive owner/playback changes cannot invalidate an executing callback.
// Registration and source changes use the native deferred mutation queue.
function guard(owner, names) {
    names.forEach(function(name) {
        var original = owner[name];
        if (typeof original !== 'function') return;
        owner[name] = function() {
            if (depth) throw new Error(name + ' must occur outside an animation modifier');
            return original.apply(this, arguments);
        };
    });
}
guard(bindings, ['cleanupLayer']);
guard(bindings.SpriteLayer.prototype, [
    'addSprite', 'addSpriteInFrontOf', 'removeSprite', 'removeAllSprites', 'createSprite',
    'createSpriteFromSpriterFile', 'createSpriteFromSpriterEntity'
]);
guard(proto, [
    'enableAnimationPose', 'disableAnimationPose', 'activateSubEntity', 'startAnimation',
    'blendToAnimation', 'pauseAnimation', 'resumeAnimation', 'stopAnimation',
    'setAnimationBoneTransform', 'clearAnimationBoneTransforms', 'getAttachPoint', 'hasAttachPoint',
    'getSpriterCollisionBox', 'isSpriterCollisionActive', 'checkSpriterCollisionBoxPointCollision'
]);
var nativeSource = proto.setAnimationSource;
proto.setAnimationSource = function(source) {
    if (arguments.length === 1 && source === null) return nativeSource.call(this, null);
    return nativeSource.call(this, integer(source, 0, 2, 'animation source'));
};
['removeAnimationModifier', 'getAnimationModifierError'].forEach(function(name) {
    var original = proto[name];
    proto[name] = function(id) {
        if (arguments.length === 1 && id === null) return original.call(this, null);
        return original.call(this, integer(id, 1, 4294967295, 'modifier ID'));
    };
});
})();

if (inbrowser && bindings.Animated) {
    (function() {
        const registrations = new WeakMap();
        function IAnimationHelper(callback) {
            if (!new.target || typeof callback !== 'function')
                throw new TypeError('IAnimationHelper requires an animation callback');
            this.animate = callback;
        }
        bindings.IAnimationHelper = IAnimationHelper;
        const proto = bindings.Animated.prototype;
        proto.addAnimationHelper = function(helper) {
            if (!(helper instanceof IAnimationHelper)) throw new TypeError('Expected IAnimationHelper');
            let active = registrations.get(this);
            if (!active) { active = new Map(); registrations.set(this, active); }
            if (active.has(helper)) return this;
            const owner = this;
            const id = this._addBrowserAnimationHelper(function(seconds) {
                let keep = false;
                try { keep = Boolean(helper.animate.call(helper, owner, seconds)); }
                catch (error) { console.error('Animation helper failed:', error); }
                if (!keep && active.get(helper) === id) active.delete(helper);
                return keep;
            });
            active.set(helper, id);
            return this;
        };
        proto.removeAnimationHelper = function(helper) {
            const active = registrations.get(this), id = active && active.get(helper);
            if (id !== undefined) { this._removeBrowserAnimationHelper(id); active.delete(helper); }
            return this;
        };
        proto.clearAnimationHelpers = function() {
            this._clearBrowserAnimationHelpers();
            const active = registrations.get(this);
            if (active) active.clear();
            return this;
        };
        const easingIds = new Map();
        bindings.registerEasingFunction = function(callback) {
            if (typeof callback !== 'function') throw new TypeError('Expected an easing callback');
            if (easingIds.has(callback)) return easingIds.get(callback);
            const id = bindings._registerBrowserEasing(function(t, begin, change, duration) {
                try {
                    const result = callback(t, begin, change, duration);
                    if (typeof result === 'number' && Number.isFinite(result)) return result;
                    throw new TypeError('Easing callback must return a finite number');
                } catch (error) {
                    console.error('Easing callback failed:', error);
                    return duration > 0 ? begin + change * t / duration : begin + change;
                }
            });
            easingIds.set(callback, id);
            return id;
        };
    })();
}

// Retain one JavaScript identity for each native Part/body. Factories hand back
// retained handles; discard duplicate handles, never the owner's reference.
if (inbrowser && bindings.Part && bindings.PhysicsBody) {
    (function() {
        const handles = new Map();
        function canonical(value) {
            if (!value) return null;
            const id = value._getNativeIdentity();
            const entry = handles.get(id);
            let existing = entry && entry.deref();
            if (existing && existing.isDeleted()) existing = null;
            if (!existing && bindings._emscriptenObjectForIdentity)
                existing = bindings._emscriptenObjectForIdentity(id);
            if (existing && !existing.isDeleted()) {
                if (existing !== value) value.delete();
                return existing;
            }
            handles.set(id, new WeakRef(value));
            return value;
        }
        bindings._canonicalPhysicsOwner = canonical;
        const NativeSprite = bindings.Sprite;
        function Sprite() {
            if (!new.target) throw new TypeError('Sprite requires new');
            return canonical(new NativeSprite());
        }
        Sprite.prototype = NativeSprite.prototype;
        Object.setPrototypeOf(Sprite, NativeSprite);
        bindings.Sprite = Sprite;
        function integer(value, min, max, label) {
            if (!Number.isInteger(value) || value < min || value > max)
                throw new RangeError('Expected ' + label + ' integer');
            return value;
        }
        function space(value) { return integer(value === undefined ? 0 : value, 0, 2, 'partSpace'); }
        function id(value) { return integer(value, 0, 4294967295, 'ID'); }
        const sprite = Sprite.prototype, part = bindings.Part.prototype, body = bindings.PhysicsBody.prototype;
        const getAttachedSprite = sprite.getAttachedSprite;
        if (getAttachedSprite) sprite.getAttachedSprite = function(name) {
            return canonical(getAttachedSprite.call(this, name));
        };
        body.setBreakAngularSpeed = function(speed, reference) {
            if (arguments.length < 1 || arguments.length > 2 || typeof speed !== 'number' || !Number.isFinite(speed))
                throw new TypeError('Expected an angular speed and optional PhysicsBody');
            if (reference != null && !(reference instanceof bindings.PhysicsBody)) throw new TypeError('Expected PhysicsBody reference');
            this._setBreakAngularSpeed(speed, reference == null ? null : reference);
            return this;
        };
        body.getBreakAngularSpeedReference = function() { return canonical(this._getBreakAngularSpeedReference()); };
        body.setDriveTarget = function(point, radians, maxForce, maxTorque, frequency, dampingRatio, direction) {
            if (arguments.length < 4) throw new TypeError('setDriveTarget requires position, angle and both force limits');
            [radians, maxForce, maxTorque, frequency === undefined ? 4 : frequency, dampingRatio === undefined ? 1 : dampingRatio].forEach(function(value) {
                if (typeof value !== 'number' || !Number.isFinite(value)) throw new TypeError('Expected finite drive numbers');
            });
            this._setDriveTarget(point,radians,maxForce,maxTorque,frequency === undefined ? 4 : frequency,
                dampingRatio === undefined ? 1 : dampingRatio,integer(direction === undefined ? 1 : direction,0,3,'rotationDirection'));
            return this;
        };
        const removePart = sprite.removePart, removeForce = body.removeForce;
        sprite.transferPart = function(value, descendants) {
            if (!(value instanceof bindings.Part)) throw new TypeError('Expected a Part');
            if (descendants !== undefined && typeof descendants !== 'boolean') throw new TypeError('Expected includeDescendants boolean');
            return canonical(this._transferPart(value, descendants === undefined ? true : descendants));
        };
        sprite.removePart = function(value) { return removePart.call(this, id(value)); };
        body.removeForce = function(value) { return removeForce.call(this, id(value)); };
        ['createPart', 'getPart', 'findPart', 'getAttachmentPart'].forEach(function(name) {
            sprite[name] = function(value) { return canonical(name === 'getAttachmentPart' ? this['_' + name]() : this['_' + name](name === 'getPart' ? id(value) : value)); };
        });
        ['getSprite', 'getAttachedSprite', 'getParentPart'].forEach(function(name) {
            part[name] = function() { return canonical(this['_' + name]()); };
        });
        ['bindToAnimationBinding', 'bindToAnimationSocket', 'setDrawing', 'setImage', 'unbindFromBone', 'clearContent', 'detachSprite'].forEach(function(name) {
            part[name] = function() { this['_' + name].apply(this, arguments); return this; };
        });
        part.bindToBone = function(value) { this._bindToBone(id(value)); return this; };
        part.setParentPart = function(parent) { this._setParentPart(parent || null); return this; };
        part.getTransform = function(value) { return this._getTransform(space(value)); };
        part.getContentBounds = function(value) { return new bindings.Rect(this._getContentBounds(space(value))); };
        part.attachSprite = function(child, placement, mount) {
            return canonical(this._attachSprite(child, integer(placement === undefined ? 0 : placement, 0, 1, 'placement'), mount || null));
        };
        part.solveIK = function(middle, tip, target, targetSpace, bend, influence) {
            return this._solveIK(middle, tip, target, space(targetSpace === undefined ? 2 : targetSpace),
                integer(bend === undefined ? 1 : bend, -1, 1, 'bend direction'), influence === undefined ? 1 : influence);
        };
        part.setIKTarget = function(middle, tip, target, targetSpace, bend, influence) {
            this._setIKTarget(middle, tip, target, space(targetSpace === undefined ? 2 : targetSpace),
                integer(bend === undefined ? 1 : bend, -1, 1, 'bend direction'), influence === undefined ? 1 : influence);
            return this;
        };
        part.setIKLimits = function(lo,hi) {
            if(arguments.length===1 && lo instanceof bindings.PhysicsConstraint) { this._setIKConstraint(lo);return this; }
            if(arguments.length!==2) throw new TypeError('Expected a PhysicsConstraint or two limit angles');
            if(typeof lo!=='number' || typeof hi!=='number' || !Number.isFinite(lo) || !Number.isFinite(hi))
                throw new TypeError('Expected finite IK limit angles');
            this._setIKLimits(lo,hi); return this;
        };
        part.clearIKLimits = function() { this._clearIKLimits(); return this; };
        part.setIKDriveTarget = function(middle,tip,target,force,torque,targetSpace,bend,influence,frequency,damping) {
            if(arguments.length<5) throw new TypeError('setIKDriveTarget requires a chain, target and both force limits');
            [force,torque,influence===undefined?1:influence,frequency===undefined?4:frequency,damping===undefined?1:damping].forEach(function(value) {
                if(typeof value!=='number' || !Number.isFinite(value)) throw new TypeError('Expected finite IK drive numbers');
            });
            this._setIKDriveTarget(middle,tip,target,force,torque,space(targetSpace===undefined?2:targetSpace),
                integer(bend===undefined?1:bend,-1,1,'bend direction'),influence===undefined?1:influence,
                frequency===undefined?4:frequency,damping===undefined?1:damping);
            return this;
        };
        part.clearIKTarget = function() { this._clearIKTarget(); return this; };
        [sprite, part, bindings.Particle && bindings.Particle.prototype].filter(Boolean).forEach(function(proto) {
            const read = proto._readPhysics;
            proto._readPhysics = function() { return canonical(read.call(this)); };
            proto.setupPhysicsBody = function(mass, inertia) {
                return canonical(this._setupPhysicsBody(mass === undefined ? 1 : mass, inertia === undefined ? 1 : inertia));
            };
        });
        ['setMass', 'setMomentOfInertia', 'setSpeed', 'setAngularVelocity', 'setLinearDamping', 'setAngularDamping',
         'setFriction', 'setRestitution', 'applyAngularImpulse', 'stopMoving', 'stopSpinning', 'stopAllForces', 'clearDrive',
         'setVelocityInRadians', 'teleport'].forEach(function(name) {
            body[name] = function() { this['_' + name].apply(this, arguments); return this; };
        });
        body.setMode = function(mode) { this._setMode(integer(mode, 1, 3, 'body mode')); return this; };
        body.getVelocity = function() { return new bindings.Vector(this._getVelocity()); };
        body.setVelocity = function(x, y) { this._setVelocity(typeof x === 'number' ? { x: x, y: y } : x); return this; };
        body.applyImpulse = function(value, point) {
            if (point === undefined) this._applyImpulse(value); else this._applyImpulseAt(value, point);
            return this;
        };
        body.applyForce = function(value, seconds, delay, point) {
            return point === undefined ? this._applyForce(value, seconds, delay === undefined ? 0 : delay)
                : this._applyForceAt(value, seconds, delay === undefined ? 0 : delay, point);
        };
        body.applyTorque = function(value, seconds, delay) { return this._applyTorque(value, seconds, delay === undefined ? 0 : delay); };
    })();
}

if (inbrowser && bindings.Collider) {
    const canonical = bindings._canonicalPhysicsOwner;
    const collider = bindings.Collider.prototype, constraint = bindings.PhysicsConstraint.prototype;
    function unsigned(value) {
        if (!Number.isInteger(value) || value < 0 || value > 4294967295)
            throw new RangeError('Expected an unsigned 32-bit integer');
        return value;
    }
    [bindings.Sprite, bindings.Part, bindings.Particle].filter(Boolean).forEach(function(type) {
        const read = type.prototype._readCollider;
        type.prototype._readCollider = function() { return canonical(read.call(this)); };
        type.prototype.setupCollider = function() { return canonical(this._setupCollider()); };
    });
    ['setFriction','setRestitution','useBodyMaterial','setEnabled','setSensor','setWantsContactEvents','setCategory','setCollisionMask','setGroup',
     'setCapsule','setBox','setPolygon','clearShapes','setPhysicsBody','useOwnerPhysics'].forEach(function(name) {
        collider[name] = function() { this['_' + name].apply(this, arguments); return this; };
    });
    ['setCircle','addCircle'].forEach(function(name) {
        collider[name] = function(radius, center) { const result = this['_' + name](radius, center === undefined ? {x:0,y:0} : center); return name === 'setCircle' ? this : result; };
    });
    ['addCapsule','addBox','addPolygon','removeShape','getShapeId','contains','overlaps'].forEach(function(name) {
        collider[name] = function() { return this['_' + name].apply(this, arguments); };
    });
    ['setCategory','setCollisionMask','setGroup'].forEach(function(name) {
        collider[name] = function(value) { this['_' + name](unsigned(value)); return this; };
    });
    ['getShapeId','removeShape','isSourceShape','getShapeName','getShapeType','getCircleRadius','getCapsuleRadius'].forEach(function(name) {
        collider[name] = function(value) { return this['_' + name](unsigned(value)); };
    });
    ['getCapsuleStart','getCapsuleEnd'].forEach(function(name) {
        collider[name] = function(value) { return new bindings.Point(this['_' + name](unsigned(value))); };
    });
    collider.addPolygon = function(vertices) {
        if (!Array.isArray(vertices)) throw new TypeError('Expected an array of Points');
        return this._addPolygon(vertices);
    };
    function alphaThreshold(value) {
        if(value===undefined)return 128;
        if(!Number.isInteger(value)||value<1||value>255)throw new RangeError('Expected an integer alpha threshold from 1 to 255');
        return value;
    }
    ['setImageMask','addImageMask'].forEach(function(name) {
        collider[name]=function(image,bounds,threshold) {
            const result=this['_'+name](image,bounds,alphaThreshold(threshold));
            return name==='setImageMask'?this:result;
        };
    });
    bindings.Part.prototype.setupFrameCollider=bindings.Sprite.prototype.setupFrameCollider=function(mode,threshold) {
        return canonical(this._setupFrameCollider(mode===undefined?1:unsigned(mode),alphaThreshold(threshold)));
    };
    bindings.Part.prototype.setupAnimationCollider=function(name) {
        if(typeof name!=='string')throw new TypeError('Expected a collision box name');
        return canonical(this._setupAnimationCollider(name));
    };
    bindings.Sprite.prototype.setupAnimationCollider=function() { return canonical(this._setupAnimationCollider()); };
    bindings.Sprite.prototype.setFrameCollisionMask=function(image,mask) { this._setFrameCollisionMask(image,mask);return this; };
    collider.setContactHandler=function(callback) {
        if(callback!==null && typeof callback!=='function') throw new TypeError('Expected a function or null');
        this._setContactHandler(callback===null?null:function(event) {
            event.collider=canonical(event.collider);event.other=canonical(event.other);callback(event);
        });return this;
    };
    collider.setCollisionFilter=function(callback) {
        if(callback!==null && typeof callback!=='function') throw new TypeError('Expected a function or null');
        this._setCollisionFilter(callback===null?null:function(a,b) {return callback(canonical(a),canonical(b));});return this;
    };
    collider.getBounds = function() { return new bindings.Rect(this._getBounds()); };
    collider.getPhysicsBody = function() { return canonical(this._getPhysicsBody()); };
    ['setMaxForce','setBreakForce','setCollideBodies'].forEach(function(name) {
        constraint[name] = function(value) { this['_' + name](value); return this; };
    });
    ['getAnchorA','getAnchorB','getGrooveStart','getGrooveEnd'].forEach(function(name) {
        constraint[name] = function() {
            if(arguments.length!==0) throw new TypeError('Expected no arguments');
            return new bindings.Point(this['_'+name]());
        };
    });
    ['setAnchorA','setAnchorB','setAnchors','setGroove'].forEach(function(name) {
        constraint[name] = function() {
            const count=(name==='setAnchors'||name==='setGroove')?2:1;
            if(arguments.length!==count) throw new TypeError('Expected '+count+' Points');
            for(const p of arguments) {
                if(!p || typeof p.x!=='number' || typeof p.y!=='number' || !Number.isFinite(p.x) || !Number.isFinite(p.y))
                    throw new TypeError('Expected finite Point coordinates');
            }
            this['_'+name].apply(this,arguments);return this;
        };
    });
    constraint.setAngleLimits = function(lo,hi) {
        if(arguments.length!==2 || typeof lo!=='number' || typeof hi!=='number' || !Number.isFinite(lo) || !Number.isFinite(hi))
            throw new TypeError('Expected two finite angle limits');
        this._setAngleLimits(lo,hi);return this;
    };
    ['getBodyA','getBodyB'].forEach(function(name) { constraint[name] = function() { return canonical(this['_' + name]()); }; });
    const body = bindings.PhysicsBody.prototype;
    ['createPinJoint','createPivotJoint'].forEach(function(name) {
        body[name] = function(other, a, b) { return canonical(this['_' + name](other, a === undefined ? {x:0,y:0} : a, b === undefined ? {x:0,y:0} : b)); };
    });
    ['createSlideJoint','createGrooveJoint','createSpring','createRotarySpring','createRotaryLimit','createMotor','getConstraint'].forEach(function(name) {
        body[name] = function() { return canonical(this['_' + name].apply(this, arguments)); };
    });
    ['createRatchet','createGear'].forEach(function(name) { body[name] = function(other, value, phase) { return canonical(this['_' + name](other, value, phase === undefined ? 0 : phase)); }; });
    body.getConstraint = function(index) { return canonical(this._getConstraint(unsigned(index))); };
    body.disconnect = function(other) { this._disconnect(other || null); return this; };
}

// Particle constructors and factories preserve one identity per live native object.
if (bindings.Particle && bindings.ParticleEmitter) {
    if (inbrowser) {
        const canonical = bindings._canonicalPhysicsOwner;
        function uint(value) {
            if (!Number.isInteger(value) || value < 0 || value > 4294967295) throw new RangeError('Expected uint32');
            return value;
        }
        ['Particle', 'ParticleEmitter'].forEach(function(name) {
            const Native = bindings[name];
            const Construct = function() {
                if (!new.target) throw new TypeError(name + ' requires new');
                return canonical(new Native());
            };
            Construct.prototype = Native.prototype; Object.setPrototypeOf(Construct, Native); bindings[name] = Construct;
            Native.prototype.getLayer = function() { return bindings._emscriptenObjectForIdentity(this._getLayerIdentity()); };
        });
        const particle = bindings.Particle.prototype, emitter = bindings.ParticleEmitter.prototype;
        ['setOpacity','setLifetime','setImage','setDrawing','clearContent'].forEach(function(name) {
            if (particle['_' + name]) particle[name] = function() { this['_' + name].apply(this, arguments); return this; };
        });
        particle.fadeTo = function(opacity, seconds, easing) {
            this._fadeTo(opacity, seconds, uint(easing === undefined ? bindings.linearTween : easing)); return this;
        };
        ['setupParticleEmitter','getParticleEmitter'].forEach(function(name) {
            particle[name] = function() { return canonical(this['_' + name]()); };
        });
        ['setParticleTemplate','setEmissionRate','setSpread','setVelocityInheritance','startEmitting','stopEmitting'].forEach(function(name) {
            emitter[name] = function() { this['_' + name].apply(this, arguments); return this; };
        });
        emitter.setSeed = function(seed) { this._setSeed(uint(seed)); return this; };
        emitter.setParticleSpeed = function(min, max) { this._setParticleSpeed(min, max === undefined ? min : max); return this; };
        emitter.emit = function(count) { return this._emit(uint(count === undefined ? 1 : count)); };
        emitter.getParticle = function() { return canonical(this._getParticle()); };
        const layer = bindings.SpriteLayer.prototype;
        ['createParticle','createParticleEmitter'].forEach(function(name) {
            layer[name] = function() { bindings._emscriptenRememberObject(this); return canonical(this['_' + name]()); };
        });
        ['addParticle','removeParticle','removeParticleEmitter'].forEach(function(name) {
            layer[name] = function(value) { bindings._emscriptenRememberObject(this); return this['_' + name](value); };
        });
        layer.getNthParticle = function(index) { return canonical(this._getNthParticle(uint(index))); };
        layer.setMaxParticles = function(count) { this._setMaxParticles(uint(count)); return this; };
    }
    Object.defineProperty(bindings.Particle.prototype, 'emitter', {
        get: function() { return this.getParticleEmitter(); }, enumerable: true
    });
}

// Collision ownership is optional and read-only, like body ownership.
if (bindings.Collider && bindings.Sprite) {
    const noCollider = new bindings.Sprite()._readCollider();
    Object.defineProperty(bindings.Collider, 'NoCollider', { value: noCollider, enumerable: true });
    [bindings.Sprite, bindings.Part, bindings.Particle].filter(Boolean).forEach(function(type) {
        if (!type) return;
        Object.defineProperty(type.prototype, 'collider', {
            get: function() { return this._readCollider(); }, enumerable: true
        });
    });
}
// Body ownership is deliberately absent from Animated and SpriteLayer.
if (bindings.PhysicsBody && bindings.Sprite) {
    const noPhysics = new bindings.Sprite()._readPhysics();
    Object.defineProperty(bindings.PhysicsBody, 'NoPhysics', {
        value: noPhysics, enumerable: true
    });
    Object.defineProperty(bindings, 'NoPhysics', { value: noPhysics, enumerable: true });
    [bindings.Sprite, bindings.Part, bindings.Particle].filter(Boolean).forEach(function(type) {
        if (!type) return;
        const read = type.prototype._readPhysics;
        Object.defineProperty(type.prototype, 'physics', {
            get: function() { return read.call(this); },
            enumerable: true
        });
    });
}

if (typeof module !== 'undefined' && module.exports) {
    for (var key in process.pdg) {
        if (bindings.hasOwnProperty(key)) {
            // Copy property descriptor to preserve readonly/writable attributes
            var descriptor = Object.getOwnPropertyDescriptor(bindings, key);
            if (descriptor) {
                Object.defineProperty(module.exports, key, descriptor);
            } else {
                // Fallback to simple assignment if descriptor not available
                module.exports[key] = process.pdg[key];
            }
        }
    }
    _debug_log(
        '[PDG] pdg.js: Copied ' + Object.keys(process.pdg).length +
        ' properties to module.exports');
    _debug_log('[PDG] pdg.js: module.exports has tm? ' + typeof module.exports.tm);
    _debug_log('[PDG] pdg.js: typeof tm.onTimeout is ' + typeof module.exports.tm.onTimeout);
}

// Call scriptSetupCompleted after all JavaScript modules are loaded and prototypes are set up
_debug_log(
    '[PDG] pdg.js: About to call _finishedScriptSetup, bindings._finishedScriptSetup is ' +
    typeof bindings._finishedScriptSetup);
if (typeof bindings._finishedScriptSetup === 'function') {
    _debug_log('[PDG] pdg.js: Calling _finishedScriptSetup after modules loaded...');
    bindings._finishedScriptSetup();
    _debug_log('[PDG] pdg.js: _finishedScriptSetup completed');
} else {
    _debug_log('[PDG] pdg.js: _finishedScriptSetup is not available');
}

if(bindings.Collider) {
    ['addPolygon','setPolygon'].forEach(function(name) {
        const native=bindings.Collider.prototype[name];
        bindings.Collider.prototype[name]=function(polygon) {
            if(bindings.Polygon && polygon instanceof bindings.Polygon) {
                const points=[];for(let i=0;i<polygon.getPointCount();++i)points.push(polygon.getPoint(i));
                return native.call(this,points);
            }
            return native.apply(this,arguments);
        };
    });
}
