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
bindings.Sprite.superclass = new Array( bindings.Animated, bindings.EventEmitter, bindings.ISerializable );
bindings.SpriteLayer.superclass = new Array( bindings.Animated, bindings.EventEmitter, bindings.ISerializable );
bindings.TileLayer.superclass = bindings.SpriteLayer;
bindings.ImageStrip.superclass = bindings.Image;


bindings.running = false;
bindings.quitting = false;

// Add a flag to track when pdg.run() is actively running
bindings._pdgRunLoopActive = false;

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
			setTimeout(bindings.__run, 0);
		} else {
			setImmediate(bindings.__run);
		}
	} else {
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

bindings.fs = bindings.getFileManager();
bindings.evt = bindings.getEventManager();
bindings.tm = bindings.getTimerManager();
bindings.res = bindings.getResourceManager();
bindings.cfg = bindings.getConfigManager();
bindings.lm = bindings.getLogManager();

// Embind creates a fresh JavaScript handle each time a singleton pointer is
// returned. Preserve the public API's singleton identity by returning the
// canonical handles initialized above.
bindings.getFileManager = function() { return bindings.fs; };
bindings.getEventManager = function() { return bindings.evt; };
bindings.getTimerManager = function() { return bindings.tm; };
bindings.getResourceManager = function() { return bindings.res; };
bindings.getConfigManager = function() { return bindings.cfg; };
bindings.getLogManager = function() { return bindings.lm; };

if (inbrowser && typeof bindings.MemBlock !== "undefined") {
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
        var proto = Animated.prototype;

        function xyValue(value, y) {
            if (value === null || typeof value === "undefined") return null;
            if (typeof value === "number") return { x: value, y: y };
            if (Array.isArray(value)) return { x: value[0], y: value[1] };
            return { x: value.x, y: value.y };
        }

        function easingOrDefault(easing) {
            return typeof easing === "undefined" ? bindings.easeInOutQuad : easing;
        }

        function chain(nativeMethod, self, args) {
            nativeMethod.apply(self, args);
            return self;
        }

        proto.getBoundingBox = function() {
            return new bindings.Rect(this._getBoundingBox());
        };
        proto.getRotatedBounds = function() {
            var bounds = this._getRotatedBounds();
            return new bindings.RotatedRect(bounds, bounds.radians, bounds.centerOffset);
        };
        proto.setLocation = function(location) {
            var value = xyValue(location);
            return value ? chain(this._setLocation, this, [value]) : this;
        };
        proto.getLocation = function() {
            return new bindings.Point(this._getLocation());
        };
        proto.moveTo = function(where, duration, easing) {
            var value;
            if (typeof where === "number") {
                value = xyValue(where, duration);
                duration = arguments[2];
                easing = arguments[3];
            } else {
                value = xyValue(where);
            }
            if (!value) return this;
            return duration
                ? chain(this._moveToTimed, this, [value, duration, easingOrDefault(easing)])
                : chain(this._moveTo, this, [value]);
        };
        proto.move = function(offset, duration, easing) {
            var value;
            if (typeof offset === "number") {
                value = xyValue(offset, duration);
                duration = arguments[2];
                easing = arguments[3];
            } else {
                value = xyValue(offset);
            }
            if (!value) return this;
            return duration
                ? chain(this._moveTimed, this, [value, duration, easingOrDefault(easing)])
                : chain(this._move, this, [value]);
        };
        proto.setVelocity = function(velocity, y) {
            var value = xyValue(velocity, y);
            return value ? chain(this._setVelocity, this, [value]) : this;
        };
        proto.getVelocity = function() {
            return new bindings.Vector(this._getVelocity());
        };
        proto.setSpeed = function(speed) { return chain(this._setSpeed, this, [speed]); };
        proto.setVelocityInRadians = function(speed, direction) {
            return chain(this._setVelocityInRadians, this, [speed, direction]);
        };
        proto.stopMoving = function() { return chain(this._stopMoving, this, []); };
        proto.setSize = function(width, height) { return chain(this._setSize, this, [width, height]); };
        proto.setWidth = function(width) { return chain(this._setWidth, this, [width]); };
        proto.setHeight = function(height) { return chain(this._setHeight, this, [height]); };
        proto.grow = function(factor, duration, easing) {
            return duration
                ? chain(this._growTimed, this, [factor, duration, easingOrDefault(easing)])
                : chain(this._grow, this, [factor]);
        };
        proto.stretch = function(width, height, duration, easing) {
            return duration
                ? chain(this._stretchTimed, this, [width, height, duration, easingOrDefault(easing)])
                : chain(this._stretch, this, [width, height]);
        };
        proto.startGrowing = function(amount) { return chain(this._startGrowing, this, [amount]); };
        proto.stopGrowing = function() { return chain(this._stopGrowing, this, []); };
        proto.startStretching = function(width, height) {
            return chain(this._startStretching, this, [width, height]);
        };
        proto.stopStretching = function() { return chain(this._stopStretching, this, []); };
        proto.resize = function(width, height, duration, easing) {
            return chain(this._resize, this, [width, height, duration || 0, easingOrDefault(easing)]);
        };
        proto.resizeTo = function(width, height, duration, easing) {
            return chain(this._resizeTo, this, [width, height, duration || 0, easingOrDefault(easing)]);
        };
        proto.setRotation = function(radians) { return chain(this._setRotation, this, [radians]); };
        proto.rotate = function(radians, duration, easing) {
            return duration
                ? chain(this._rotateTimed, this, [radians, duration, easingOrDefault(easing)])
                : chain(this._rotate, this, [radians]);
        };
        proto.rotateTo = function(radians, duration, easing) {
            return duration
                ? chain(this._rotateToTimed, this, [radians, duration, easingOrDefault(easing)])
                : chain(this._rotateTo, this, [radians]);
        };
        proto.setFlipX = function(flip) { return chain(this._setFlipX, this, [flip]); };
        proto.setFlipY = function(flip) { return chain(this._setFlipY, this, [flip]); };
        proto.flipX = function() { return chain(this._flipX, this, []); };
        proto.flipY = function() { return chain(this._flipY, this, []); };
        proto.setSpin = function(spin) { return chain(this._setSpin, this, [spin]); };
        proto.stopSpinning = function() { return chain(this._stopSpinning, this, []); };
        proto.setCenterOffset = function(offset) {
            var value = xyValue(offset);
            return value ? chain(this._setCenterOffset, this, [value]) : this;
        };
        proto.getCenterOffset = function() {
            return new bindings.Offset(this._getCenterOffset());
        };
        proto.changeCenter = function(offset, duration, easing) {
            var value;
            if (typeof offset === "number") {
                value = xyValue(offset, duration);
                duration = arguments[2];
                easing = arguments[3];
            } else {
                value = xyValue(offset);
            }
            if (!value) return this;
            return chain(this._changeCenter, this, [value, duration || 0, easingOrDefault(easing)]);
        };
        proto.changeCenterTo = function(offset, duration, easing) {
            var value;
            if (typeof offset === "number") {
                value = xyValue(offset, duration);
                duration = arguments[2];
                easing = arguments[3];
            } else {
                value = xyValue(offset);
            }
            if (!value) return this;
            return chain(this._changeCenterTo, this, [value, duration || 0, easingOrDefault(easing)]);
        };
        proto.wait = function(duration) { return chain(this._wait, this, [duration]); };
        proto.setMass = function(mass) { return chain(this._setMass, this, [mass]); };
        proto.setFriction = function(value) { return chain(this._setFriction, this, [value]); };
        proto.setMoveFriction = function(value) { return chain(this._setMoveFriction, this, [value]); };
        proto.setSpinFriction = function(value) { return chain(this._setSpinFriction, this, [value]); };
        proto.setSizeFriction = function(value) { return chain(this._setSizeFriction, this, [value]); };
        proto.applyForce = function(force, duration) {
            var value = xyValue(force);
            return value ? chain(this._applyForce, this, [value, duration || 0]) : this;
        };
        proto.applyTorque = function(force, duration) {
            return chain(this._applyTorque, this, [force, duration || 0]);
        };
        proto.stopAllForces = function() { return chain(this._stopAllForces, this, []); };
    })(bindings.Animated);
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
        var layerProto = bindings.SpriteLayer.prototype;
        var spriteProto = bindings.Sprite.prototype;

        layerProto.createSprite = function() {
            var sprite = this._createSprite();
            var sprites = layerSprites.get(this);
            if (!sprites) {
                sprites = [];
                layerSprites.set(this, sprites);
            }
            sprites.push(sprite);
            return sprite;
        };
        layerProto.getNthSprite = function(index) {
            var sprites = layerSprites.get(this);
            if (sprites && sprites[index]) return sprites[index];
            return this._getNthSprite(index);
        };
        if (typeof layerProto._createSpriteFromSpriterFile === "function") {
            layerProto.createSpriteFromSpriterFile = function(path, entity) {
                var sprite = this._createSpriteFromSpriterFile(path,
                    typeof entity === "undefined" || entity === null ? "" : entity);
                if (sprite) {
                    var sprites = layerSprites.get(this) || [];
                    if (!layerSprites.has(this)) layerSprites.set(this, sprites);
                    sprites.push(sprite);
                }
                return sprite;
            };

            var nativeSetEntityScale = spriteProto.setEntityScale;
            var nativeGetSpriterCollisionBox = spriteProto.getSpriterCollisionBox;
            var nativeHasAttachPoint = spriteProto.hasAttachPoint;
            var nativeAttachSprite = spriteProto.attachSprite;
            var nativeActivateSubEntity = spriteProto.activateSubEntity;
            spriteProto.setEntityScale = function(x, y) {
                nativeSetEntityScale.call(this, x, y);
                return this;
            };
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
        layerProto.setUseChipmunkPhysics = function(useIt) {
            if (typeof this._setUseChipmunkPhysics === "function") {
                this._setUseChipmunkPhysics(useIt !== false);
            }
            return this;
        };
        spriteProto.enableCollisions = function(collisionType) {
            this._enableCollisions(typeof collisionType === "undefined" ? bindings.collide_AlphaChannel : collisionType);
            return this;
        };
        var nativeSetWantsCollideWallEvents = spriteProto.setWantsCollideWallEvents;
        spriteProto.setWantsCollideWallEvents = function(wantsThem) {
            nativeSetWantsCollideWallEvents.call(this, wantsThem !== false);
            return this;
        };
        spriteProto.setElasticity = function(value) {
            this._setElasticity(value);
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
            this.serialize_uint(getSizeOf(obj, this));
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
            ["Height", "Leading", "Ascent", "Descent"].forEach(function(metric) {
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
            if (event && typeof event.portIdentity !== "undefined" &&
                bindings._emscriptenPortsById) {
                event.port = bindings._emscriptenPortsById.get(event.portIdentity) || null;
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
            onAnimationBlendComplete: [bindings.eventType_SpriteAnimate, 15]
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

// add methods to the timer manager prototypes
// TimerManager.onTimeout(function, delayMs)
timerManagerProto.onTimeout = function(func, delay) {
	var _sig = methodSignature("setup handler to be called once after delay ms", arguments, "[object IEventHandler]", 2, "(function func, [number int] delay)"); if (_sig != null) return _sig;
	var timerId = _lastAutoTimerId++;
	this.startTimer(timerId, delay, bindings.timer_OneShot);
	var handler = new bindings.IEventHandler(function(event) {
		if (event.id != timerId) return false; // timer event was not for us
		func(event);
//		this.removeHandler(handler, eventType); // this was a one-shot, so remove the handler too
		return true;  // we are the only handler to handle this event
	}.bind(this));
	this.addHandler(handler, bindings.eventType_Timer);
	handler.cancel = function() {
		this.removeHandler(handler, eventType);
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
	this.addHandler(handler, bindings.eventType_Timer);
	handler.cancel = function() {
		this.removeHandler(handler, eventType);
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
    _debug_log('[PDG] pdg.js: Copied ' + Object.keys(process.pdg).length + ' properties to module.exports');
    _debug_log('[PDG] pdg.js: module.exports has tm? ' + typeof module.exports.tm);
	_debug_log('[PDG] pdg.js: typeof tm.onTimeout is ' + typeof module.exports.tm.onTimeout);
}

// Call scriptSetupCompleted after all JavaScript modules are loaded and prototypes are set up
_debug_log('[PDG] pdg.js: About to call _finishedScriptSetup, bindings._finishedScriptSetup is ' + typeof bindings._finishedScriptSetup);
if (typeof bindings._finishedScriptSetup === 'function') {
    _debug_log('[PDG] pdg.js: Calling _finishedScriptSetup after modules loaded...');
    bindings._finishedScriptSetup();
    _debug_log('[PDG] pdg.js: _finishedScriptSetup completed');
} else {
    _debug_log('[PDG] pdg.js: _finishedScriptSetup is not available');
}
