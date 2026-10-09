// -----------------------------------------------
/* @pdg-contract
{
  "name": "AnimationContactTarget.update",
  "value": {
    "returns": {
      "ownership": "owned"
    },
    "params": {
      "frame": {
        "condition": "Required and validated only while a platform lock remains active; otherwise ignored."
      }
    }
  }
}
*/
// @pdg-contract {"name":"AnimationContactTarget.getState","value":{"returns":{"ownership":"owned"}}}
// @pdg-contract {"name":"AnimationSpringTarget.update","value":{"returns":{"ownership":"owned"}}}
// @pdg-contract {"name":"AnimationSpringTarget.getState","value":{"returns":{"ownership":"owned"}}}
// @pdg-member {"name":"pdg.argv","type":"string[]"}
// @pdg-member {"name":"pdg.SharedSurface","type":"boolean","readonly":true}
// @pdg-member {"name":"pdg.CopyPixels","type":"boolean","readonly":true}
/* @pdg-member
{
  "name": "AnimationContactTarget.update",
  "type": "function",
  "brief": "update a contact lock or fade its influence",
  "returns": "object AnimationContactState",
  "params": [
    {
      "name": "deltaSeconds",
      "type": "number"
    },
    {
      "name": "contactActive",
      "type": "boolean"
    },
    {
      "name": "withinReach",
      "type": "boolean"
    },
    {
      "name": "support",
      "type": "number",
      "optional": true,
      "default_value": "0"
    },
    {
      "name": "frame",
      "type": "object AnimationTransform",
      "optional": true,
      "default_value": "undefined"
    },
    {
      "name": "releaseSeconds",
      "type": "number",
      "optional": true,
      "default_value": "0"
    }
  ]
}
*/
// @pdg-member {"name":"AnimationContactTarget.release","type":"function","brief":"release a contact with an optional fade","params":[{"name":"fadeSeconds","type":"number","optional":true,"default_value":"0"}]}
/* @pdg-member
{
  "name": "AnimationContactTarget.lockPlatform",
  "type": "function",
  "brief": "lock a contact to a moving platform",
  "params": [
    {
      "name": "x",
      "type": "number"
    },
    {
      "name": "y",
      "type": "number"
    },
    {
      "name": "support",
      "type": "number"
    },
    {
      "name": "frame",
      "type": "object AnimationTransform"
    }
  ]
}
*/
// @pdg-member {"name":"AnimationContactTarget.lockWorld","type":"function","brief":"lock a contact in world coordinates","params":[{"name":"x","type":"number"},{"name":"y","type":"number"}]}
// @pdg-member {"name":"AnimationContactTarget.getState","type":"function","brief":"copy contact position and influence","returns":"object AnimationContactState","params":[]}
/* @pdg-member
{
  "name": "AnimationSpringTarget.update",
  "type": "function",
  "brief": "advance the spring toward a target",
  "returns": "object AnimationSpringState",
  "params": [
    {
      "name": "targetX",
      "type": "number"
    },
    {
      "name": "targetY",
      "type": "number"
    },
    {
      "name": "deltaSeconds",
      "type": "number"
    }
  ]
}
*/
// @pdg-member {"name":"AnimationSpringTarget.setState","type":"function","brief":"replace spring position and velocity","params":[{"name":"state","type":"object AnimationSpringState"}]}
// @pdg-member {"name":"AnimationSpringTarget.getState","type":"function","brief":"copy spring position and velocity","returns":"object AnimationSpringState","params":[]}
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
	require('dump');
	coordinates = require('coordinates');
	_debug_log('[PDG] pdg.js: Coordinates module loaded: ' + typeof coordinates);
	_debug_log('[PDG] pdg.js: coordinates.Quad: ' + typeof coordinates.Quad);
	color = require('color');
	_debug_log('[PDG] pdg.js: Color module loaded: ' + typeof color);
	_debug_log('[PDG] pdg.js: color.Color: ' + typeof color.Color);
    netconnection = require('netconnection');
    netclient = require('netclient');
    if (!jsc) netserver = require('netserver');
	// DON'T delete process.pdg - we want to keep using it as our single source of truth
	Module = global.module; // || publicRequire('module');
} else if (inbrowser) {

    // running in a browser via emscripten
    // everything is crammed into a single binding called pdg_bind
    
    bindings = pdg_bind;
    netconnection = require('netconnection');
    netclient = require('netclient');
    coordinates = require('coordinates');
    color = require('color');
    
    // dump.js installs console.dump from our simulated file system.
    require('dump');
	Module = require('module');
} else {
	// normal case, for pdg as a node JS add-on
	_debug_log('[PDG] pdg.js: Using normal node.js add-on approach');
	bindings = require('../build/Release/pdg');
	require('./dump');
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
bindings.SpriteLayer.superclass = new Array( bindings.EventEmitter, bindings.ISerializable );
if (bindings._defineAnimationScript) {
// @pdg-contract {"name":"Animated.defineScript","value":{"returns":{"type":"object AnimationScript","ownership":"library"}}}
// @pdg-member {"name":"Animated.defineScript","type":"function","native":false,"static":true,"brief":"create a library-owned named animation recorder","returns":"object AnimationScript","params":[{"name":"name","type":"string"}]}
    bindings.Animated.defineScript = function(name) { return bindings._defineAnimationScript(name); };
// @pdg-member {"name":"Animated.deleteScript","type":"function","native":false,"static":true,"brief":"remove a named definition; running copies continue","returns":"boolean","params":[{"name":"name","type":"string"}]}
    bindings.Animated.deleteScript = function(name) { return bindings._deleteAnimationScript(name); };
    for (const className of ['AnimationScript','Camera','Sprite','Bone','Part','Particle','ParticleEmitter','AnimatedAttributes','Troupe']) {
        if (bindings[className]) {
            bindings[className].defineScript = bindings.Animated.defineScript;
            bindings[className].deleteScript = bindings.Animated.deleteScript;
        }
    }
    bindings.AnimationScript.superclass = bindings.Animated;
}
if (bindings.Camera) bindings.Camera.superclass = [bindings.Animated, bindings.EventEmitter];
if (bindings.Bone) bindings.Bone.superclass = bindings.Animated;

bindings.TileLayer.superclass = bindings.SpriteLayer;
bindings.ImageStrip.superclass = bindings.Image;


// @pdg-member {"name":"pdg.running","type":"boolean"}
bindings.running = false;
// @pdg-member {"name":"pdg.quitting","type":"boolean"}
bindings.quitting = false;

// Add a flag to track when pdg.run() is actively running
bindings._pdgRunLoopActive = false;
var performanceRunChannel = null;

// @pdg-member {"name":"pdg.quit","type":"function","brief":"","params":[],"native_binding":{"adapter":"pdg.quit","browser":{"generate":true},"binding_name":"_quit"}}
bindings.quit = function() {
	pdg._debug_log("bindings.quit");
	bindings.quitting = true;
	// Clear the run loop active flag when quitting
	bindings._pdgRunLoopActive = false;
}

// @pdg-member {"name":"pdg.run","type":"function","brief":"","params":[]}
bindings.run = function() {
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

// @pdg-member {"name":"pdg.idle","type":"function","brief":"","params":[],"native_binding":{"adapter":"pdg.idle","browser":{"generate":true},"binding_name":"_idle"}}
bindings.idle = function() {
//	pdg._debug_log("bindings.idle");
	bindings._idle();
}

if (!jsc && !inbrowser) {
    
    // debugger support
    var _debuggerRunning = false;
    //var exec = require('child_process').exec;
	//var path = require('path');
    
// @pdg-member {"name":"pdg.openDebugger","type":"function","brief":"start node-inspector and open a debugger window in your browser","params":[]}
    bindings.openDebugger = function() {
		var exec = require('child_process').exec;
		var path = require('path');
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
// @pdg-member {"name":"pdg.openConsole","type":"function","brief":"open a pdg console window","params":[]}
    bindings.openConsole = function() {
		var exec = require('child_process').exec;
		var path = require('path');
                
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
// @pdg-member {"name":"pdg.openCommandPort","type":"function","brief":"start a REPL server on a TCP port","params":[{"name":"port","type":"number int","optional":true,"default_value":"5757"}]}
	bindings.openCommandPort = function (port) {

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
			return bindings._loadScript(decodeURIComponent(Array.prototype.map.call(resourceManager.getResource(file), function(byte) {
                return "%" + byte.toString(16).padStart(2, "0");
            }).join("")), file);
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
        if (buf instanceof bindings.MemBlock) buf = buf.getData();
        if (!(buf instanceof Uint8Array)) throw new TypeError("binaryDump requires Uint8Array or MemBlock");
        bytesPerLine = bytesPerLine === undefined ? 20 : bytesPerLine;
        if (!Number.isInteger(bytesPerLine) || bytesPerLine <= 0) throw new RangeError("invalid bytesPerLine");
        len = len === undefined || len === 0 ? buf.length : len;
        if (!Number.isInteger(len) || len < 0 || len > buf.length) throw new RangeError("invalid length");
        var lines = [];
        for (var offset = 0; offset < len; offset += bytesPerLine) {
            var bytes = [];
            for (var i = offset; i < Math.min(offset + bytesPerLine, len); ++i) {
                bytes.push(buf[i].toString(16).padStart(2, "0"));
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

// @pdg-member {"name":"pdg.lftTop","type":"number","readonly":true}
bindings.lftTop = coordinates.lftTop;
// @pdg-member {"name":"pdg.rgtTop","type":"number","readonly":true}
bindings.rgtTop = coordinates.rgtTop;
// @pdg-member {"name":"pdg.rgtBot","type":"number","readonly":true}
bindings.rgtBot = coordinates.rgtBot;
// @pdg-member {"name":"pdg.lftBot","type":"number","readonly":true}
bindings.lftBot = coordinates.lftBot;
Object.defineProperty(bindings, 'lftTop', { writable: false });
Object.defineProperty(bindings, 'rgtTop', { writable: false });
Object.defineProperty(bindings, 'rgtBot', { writable: false });
Object.defineProperty(bindings, 'lftBot', { writable: false });

// color
bindings.Color = color.Color;

// Type-level IDL rules supply public values and borrowed argument views before
// browser adapters and mixins capture these methods. Policies are finalized below.
var browserGeneratedBindings = inbrowser ? require('pdg_em_generated') : null;
if (inbrowser) browserGeneratedBindings.installReturns(bindings);

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


bindings._getRotatedRectConstructorSignature = function() {
    return bindings.describeInterface("RotatedRect", "RotatedRect");
}

bindings._getRotatedRectConstructorSignature = function() {
    return bindings.describeInterface("RotatedRect", "RotatedRect");
}

bindings._getQuadConstructorSignature = function() {
    return bindings.describeInterface("Quad", "Quad");
}

bindings._getRectConstructorSignature = function() {
    return bindings.describeInterface("Rect", "Rect");
}

bindings._getOffsetConstructorSignature = function() {
    return bindings.describeInterface("Offset", "Offset");
}

bindings._getPointConstructorSignature = function() {
    return bindings.describeInterface("Point", "Point");
}

bindings._getVectorConstructorSignature = function() {
    return bindings.describeInterface("Vector", "Vector");
}

bindings._getColorConstructorSignature = function() {
    return bindings.describeInterface("Color", "Color");
}

bindings._getNetConnectionConstructorSignature = function() {
    return bindings.describeInterface("NetConnection", "NetConnection");
}

bindings._getNetClientConstructorSignature = function() {
    return bindings.describeInterface("NetClient", "NetClient");
}

bindings._getNetServerConstructorSignature = function() {
    return bindings.describeInterface("NetServer", "NetServer");
}

// network

if (!jsc && !inbrowser) {

	bindings.NetConnection = netconnection.NetConnection;
	bindings.NetClient = netclient.NetClient;
	bindings.NetServer = netserver.NetServer;

	process._pdgScriptClasses['NetConnection'] = (new netconnection.NetConnection).__proto__;
	process._pdgScriptClasses['NetClient'] = (new netclient.NetClient).__proto__;
	process._pdgScriptClasses['NetServer'] = (new netserver.NetServer).__proto__;


	bindings.openCommandPort = bindings.openCommandPort;
// @pdg-member {"name":"pdg.hasNetwork","type":"boolean"}
	bindings.hasNetwork = true;
} else if (inbrowser || jsc) {
    bindings.NetConnection = netconnection.NetConnection;
    bindings.NetClient = netclient.NetClient;
    bindings.hasNetwork = true;
} else {
    bindings.hasNetwork = false;
}
// @pdg-member {"name":"pdg.hasNetworkClient","type":"boolean"}
bindings.hasNetworkClient = !!bindings.NetClient;
// @pdg-member {"name":"pdg.hasNetworkServer","type":"boolean"}
bindings.hasNetworkServer = !!bindings.NetServer;

var _nativeGetFileManager = bindings.getFileManager;
var _nativeGetEventManager = bindings.getEventManager;
var _nativeGetTimerManager = bindings.getTimerManager;
var _nativeGetResourceManager = bindings.getResourceManager;
var _nativeGetConfigManager = bindings.getConfigManager;
var _nativeGetLogManager = bindings.getLogManager;

// @pdg-member {"name":"pdg.fs","type":"object FileManager"}
bindings.fs = _nativeGetFileManager();
// @pdg-member {"name":"pdg.evt","type":"object EventManager"}
bindings.evt = _nativeGetEventManager();
// @pdg-member {"name":"pdg.tm","type":"object TimerManager"}
bindings.tm = _nativeGetTimerManager();
// @pdg-member {"name":"pdg.res","type":"object ResourceManager"}
bindings.res = _nativeGetResourceManager();
// @pdg-member {"name":"pdg.cfg","type":"object ConfigManager"}
bindings.cfg = _nativeGetConfigManager();
// @pdg-member {"name":"pdg.lm","type":"object LogManager"}
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


if (inbrowser && typeof bindings.Spline !== "undefined") {
    var NativeSpline = bindings.Spline;


    bindings.Spline = function Spline(type) {
        return new NativeSpline(typeof type === "undefined" ? bindings.spline_CubicBezier : type);
    };
    bindings.Spline.prototype = NativeSpline.prototype;
}

if (inbrowser && typeof bindings.Polygon !== "undefined") {
    var NativePolygon = bindings.Polygon;

    var nativePolygonAddSpline = NativePolygon.prototype.addSpline;

    bindings.Polygon = function Polygon() {
        var polygon = new NativePolygon();
        var points = (arguments.length === 1 && Array.isArray(arguments[0]))
            ? arguments[0] : Array.prototype.slice.call(arguments);
        for (var i = 0; i < points.length; i++) polygon.addPoint(points[i]);
        return polygon;
    };
    bindings.Polygon.prototype = NativePolygon.prototype;
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
            if (first === null || typeof first === "undefined") throw new TypeError("Expected a Point or numeric coordinates");
            if (typeof first === "number") return { x: first, y: second };
            return { x: first.x, y: first.y };
        }


        proto.getImageBounds = function(point) {
            var bounds = arguments.length === 0
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
        proto.setOpacity = function(value) {
            var opacity = Number(value);
            if (!isFinite(opacity)) opacity = 0;
            if (opacity <= 1) opacity = Math.floor(255 * opacity);
            opacity = Math.max(0, Math.min(255, Math.round(opacity)));
            this._setOpacity(opacity);
            return this;
        };
        proto.getOpacity = function() {
            return this._getOpacity() / 255;
        };
        proto.getAlphaValue = function(first, second) {
            var point = pointValue(first, second);
            return this._getAlphaValue(point.x || 0, point.y || 0);
        };
        var nativeGetPixel = proto.getPixel;
        proto.getPixel = function(first, second) {
            var point = pointValue(first, second);
            return nativeGetPixel.call(this, point.x || 0, point.y || 0);
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

    })(bindings.Attributes.prototype);
}

// Embind supports one native base: AnimatedAttributes inherits Animated there.
// Attribute calls borrow its adjusted second-base pointer for the duration of
// the call; no copied state and no independently owned Attributes allocation.
function browserAttributes(value) {
    return browserGeneratedBindings.adaptArgument(bindings, 'Attributes', value);
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
}

if (inbrowser && typeof bindings.Drawing !== "undefined") {

    bindings.ElementRef.prototype.getControlPoints = function() {
        return this._getControlPoints().map(function(value) { return new bindings.Point(value); });
    };

}

if (inbrowser && typeof bindings.SpriteLayer !== "undefined") {
    (function() {
        var layerSprites = new WeakMap();
        const handles = require('pdg_em_runtime');
        function remember(object) { return handles.rememberObject(bindings, object); }
        bindings._emscriptenRememberObject = remember;
        bindings._emscriptenObjectForIdentity = function(identity) {
            return handles.objectForIdentity(bindings, identity);
        };
        var nativeCleanupLayer = bindings.cleanupLayer;
        bindings.cleanupLayer = function(layer) {
            if (!layer) return nativeCleanupLayer(layer);
            var identity = layer._getNativeIdentity();
            var sprites = layerSprites.get(layer) || [];
            var spriteIdentities = sprites.filter(function(sprite) { return sprite && !sprite.isDeleted(); })
                .map(function(sprite) { return sprite._getNativeIdentity(); });
            nativeCleanupLayer(layer);
            handles.forgetObject(bindings, identity);
            spriteIdentities.forEach(function(id) { handles.forgetObject(bindings, id); });
            layerSprites.delete(layer);
        };
        var layerProto = bindings.SpriteLayer.prototype;
        var spriteProto = bindings.Sprite.prototype;
        spriteProto.addFramesImage = function(image, first, count) {
            this._addFramesImage(image, first === undefined ? -1 : first, count === undefined ? 0 : count);
        };
        spriteProto.startFrameAnimation = function(fps, first, count, flags) {
            this._startFrameAnimation(fps, first === undefined ? -1 : first,
                count === undefined ? 0 : count, flags === undefined ? 4 : flags);
        };
        var nativeGetFrameRotatedBounds = spriteProto.getFrameRotatedBounds;
        spriteProto.getFrameRotatedBounds = function(frame) {
            return nativeGetFrameRotatedBounds.call(this, frame === undefined ? -1 : frame);
        };


        var createSprite = layerProto.createSprite;
        layerProto.createSprite = function() {
            var sprite = createSprite.call(this);
            var sprites = layerSprites.get(this);
            if (!sprites) {
                sprites = [];
                layerSprites.set(this, sprites);
            }
            sprites.push(sprite);
            return sprite;
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

            var nativeHasAttachPoint = spriteProto.hasAttachPoint;
            var nativeAttachSprite = spriteProto.attachSprite;
            var nativeActivateSubEntity = spriteProto.activateSubEntity;
            spriteProto.hasAttachPoint = function(name) {
                if (typeof name !== "string") throw new TypeError("AttachPoint name must be a string");
                return nativeHasAttachPoint.call(this, name);
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
            this._setGravity(gravity);return this;
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
    bindings.TileLayer.prototype.defineTileSet = function(tileWidth, tileHeight, image, hasTransparency, flipTiles) {
        this._defineTileSet(tileWidth, tileHeight, image, hasTransparency===undefined?true:hasTransparency, flipTiles===undefined?false:flipTiles);
        return this;
    };
    bindings.TileLayer.prototype.setWorldSize = function(width, height, repeatingX, repeatingY) {
        this._setWorldSize(width, height, repeatingX===undefined?false:repeatingX, repeatingY===undefined?false:repeatingY);
        return this;
    };

}

if (inbrowser && typeof bindings.Serializer !== "undefined") {
    (function(proto) {
        function requireNumber(value, name) {
            if (typeof value !== "number") throw new TypeError(name + " requires a number");
            return value;
        }
        function fixedSize(size) {
            return function(value) {
                requireNumber(value, "sizeof");
                return size;
            };
        }

        proto.serialize_str = function(value) {
            if (typeof value !== "string") throw new TypeError("serialize_str requires a string");
            return this._serialize_str(value);
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
        proto.sizeof_8 = proto.sizeof_8u = fixedSize(8);
        proto.sizeof_str = function(value) { return this._sizeof_str(value); };
        proto.sizeof_rotr = function(value) { return this._sizeof_rotr(value); };
        proto.sizeof_quad = function(value) { return this._sizeof_quad(value); };
    })(bindings.Serializer.prototype);


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
// @pdg-member {"name":"AnimationContactTarget.AnimationContactTarget","type":"constructor","brief":"create an unlocked contact target","returns":"object AnimationContactTarget","params":[]}
/* @pdg-member
{
  "name": "AnimationSpringTarget.AnimationSpringTarget",
  "type": "constructor",
  "brief": "create a damped spring target",
  "returns": "object AnimationSpringTarget",
  "params": [
    {
      "name": "mass",
      "type": "number",
      "optional": true,
      "default_value": "1"
    },
    {
      "name": "stiffness",
      "type": "number",
      "optional": true,
      "default_value": "100"
    },
    {
      "name": "damping",
      "type": "number",
      "optional": true,
      "default_value": "20"
    }
  ]
}
*/
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

        if (bindings.Animated) {
            serializableClasses[0xffffff04] = function() { return new bindings.Animated(); };
        }
        if (bindings.Sprite) {
            serializableClasses[0xffffff01] = function() { return new bindings.Sprite(); };
        }

        function snapshotIndex(objects, value) {
            for(var i=0;i<objects.length;++i) {
                var candidate=objects[i];
                if(candidate===value || (candidate && value && candidate.$$ && value.$$ && candidate.isAliasOf(value))) return i;
            }
            return -1;
        }
        function mergeSnapshotObjects(known, nativeObjects) {
            for(var i=0;i<nativeObjects.length;++i) if(!known[i]) known[i]=nativeObjects[i];
            return known;
        }
        if(bindings.Troupe) serializableClasses[0xffffff0c]=function(){return new bindings.Troupe();};
        [bindings.SpriteLayer,bindings.TileLayer].forEach(function(type) {
            if(!type) return;
            ['serialize','deserialize','getSerializedSize'].forEach(function(name) {
                if(!Object.prototype.hasOwnProperty.call(type.prototype,name)) return;
                var native=type.prototype[name];
                type.prototype[name]=function(stream) {
                    var reading=name==='deserialize', sizing=name==='getSerializedSize';
                    var key=reading?'_pdgDeserializedObjects':sizing?'_pdgSizedObjects':'_pdgSerializedObjects';
                    var objects=stream[key] || (stream[key]=[]);
                    if(reading) stream._syncSnapshotObjects(objects); else stream._syncSnapshotObjects(objects,sizing);
                    var result=native.call(this,stream);
                    mergeSnapshotObjects(objects,reading?stream._snapshotObjects():stream._snapshotObjects(sizing));
                    return result;
                };
            });
        });
        var serializerProto = bindings.Serializer.prototype;
        serializerProto.sizeof_obj = function(obj) {
            if (obj === null) return 3;
            classTagOf(obj);
            this._pdgSizedObjects = this._pdgSizedObjects || [];
            var referenceIndex = snapshotIndex(this._pdgSizedObjects,obj);
            if (referenceIndex >= 0) return 3 + this.sizeof_uint(referenceIndex);
            this._pdgSizedObjects.push(obj);
            this._syncSnapshotObjects(this._pdgSizedObjects,true);
            var objectSize = getSizeOf(obj, this);
            mergeSnapshotObjects(this._pdgSizedObjects,this._snapshotObjects(true));
            return 3 + 4 + 2 + this.sizeof_uint(objectSize) + objectSize;
        };
        serializerProto.serialize_obj = function(obj) {
            if (obj === null) {
                this.serialize_3u(tagObjectNil);
                return;
            }
            classTagOf(obj);
            this._pdgSerializedObjects = this._pdgSerializedObjects || [];
            var referenceIndex = snapshotIndex(this._pdgSerializedObjects,obj);
            if (referenceIndex >= 0) {
                this.serialize_3u(tagObjectRef);
                this.serialize_uint(referenceIndex);
                return;
            }
            this._pdgSerializedObjects.push(obj);
            this._syncSnapshotObjects(this._pdgSerializedObjects,false);
            this.serialize_3u(tagObject);
            this.serialize_4u(classTagOf(obj));
            this.serialize_2u(obj._pdgRequiresExplicitRegistration && !obj._pdgRegistered
                ? 0 : this._pdgSerializedObjects.length);
            var writer = this, priorSized = this._pdgSizedObjects, objectSize;
            this._pdgSizedObjects = this._pdgSerializedObjects.slice();
            this._syncSnapshotObjects(this._pdgSizedObjects,true);
            try {
                objectSize = this._measureObjectBody(function() { return getSizeOf(obj, writer); });
            } finally {
                this._pdgSizedObjects = priorSized;
            }
            this.serialize_uint(objectSize);
            serializeObjectData(obj, this);
            mergeSnapshotObjects(this._pdgSerializedObjects,this._snapshotObjects(false));
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
            this._syncSnapshotObjects(this._pdgDeserializedObjects);
            deserializeObjectData(obj, this);
            mergeSnapshotObjects(this._pdgDeserializedObjects,this._snapshotObjects());
            return obj;
        };
    })();
}

if (typeof bindings.GraphicsManager != "undefined") {  // might be non-gui build
// @pdg-member {"name":"pdg.gfx","type":"object GraphicsManager"}
	bindings.gfx = bindings.getGraphicsManager();
// @pdg-member {"name":"pdg.hasGraphics","type":"boolean"}
	bindings.hasGraphics = true;
} else {
	bindings.hasGraphics = false;
}
if (typeof bindings.SoundManager != "undefined") {  // might be non-gui build
// @pdg-member {"name":"pdg.snd","type":"object SoundManager"}
	bindings.snd = bindings.getSoundManager();
// @pdg-member {"name":"pdg.hasSound","type":"boolean"}
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

// @pdg-member {"name":"LogManager.init_CreateUniqueNewFile","type":"number","readonly":true,"value":0}
bindings.lm.init_CreateUniqueNewFile = bindings.init_CreateUniqueNewFile;
// @pdg-member {"name":"LogManager.init_OverwriteExisting","type":"number","readonly":true,"value":1}
bindings.lm.init_OverwriteExisting = bindings.init_OverwriteExisting;
// @pdg-member {"name":"LogManager.init_AppendToExisting","type":"number","readonly":true,"value":2}
bindings.lm.init_AppendToExisting = bindings.init_AppendToExisting;
// @pdg-member {"name":"LogManager.init_StdOut","type":"number","readonly":true,"value":3}
bindings.lm.init_StdOut = bindings.init_StdOut;
// @pdg-member {"name":"LogManager.init_StdErr","type":"number","readonly":true,"value":4}
bindings.lm.init_StdErr = bindings.init_StdErr;

if (inbrowser) {
    (function(proto) {
        proto.setLanguage = function(language) {
            if (typeof language !== "string") throw new TypeError("language must be a string");
            this._setLanguage(language);
            return this;
        };
        proto.openResourceFile = function(filename) {
            if (typeof filename !== "string") throw new TypeError("filename must be a string");
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
                return nativeGetScreenBounds.call(this,
                    typeof screenNum === "undefined" ? -1 : screenNum);
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
                return nativeGetMouse.call(this,
                    typeof mouseNumber === "undefined" ? 0 : mouseNumber);
            };
            graphicsProto.setTargetFPS = function(fps) {
                nativeSetTargetFPS.call(this, fps);
                return this;
            };

            var portProto = bindings.Port.prototype;
            portProto.clear = function(color) { this._clear(color || new bindings.Color(0,0,0,0)); };
            portProto.setDrawingOrigin = function(origin) { this._setDrawingOrigin(origin); };

            var nativeGetTextWidth = portProto._getTextWidth;
            var nativeSetClipRect = portProto.setClipRect;
            var nativeGetCurrentFont = portProto.getCurrentFont;
            var nativeSetFontForStyle = portProto.setFontForStyle;
            var nativeSetFont = portProto.setFont;

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
            bindings.Camera,
            bindings.Scene,
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

        browserGeneratedBindings.installEvents(bindings);

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
// @pdg-member {"name":"FileManager.findFiles","type":"function","brief":"","returns":"string[]","params":[{"name":"name","type":"string"}]}
fileManagerProto.findFiles = function(name) {
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

// @pdg-member {"name":"FileManager.findDirs","type":"function","brief":"","returns":"string[]","params":[{"name":"name","type":"string"}]}
fileManagerProto.findDirs = function(name) {
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
// @pdg-member {"name":"pdg.log","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.log = function(msg) {
	bindings.getLogManager().writeLogEntry(4, "LOG", msg);
}
// @pdg-member {"name":"pdg.info","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.info = function(msg) {
	bindings.getLogManager().writeLogEntry(5, "INFO", msg);
}
// @pdg-member {"name":"pdg.warn","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.warn = function(msg) {
	bindings.getLogManager().writeLogEntry(3, "WARN", msg);
}
// @pdg-member {"name":"pdg.fatal","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.fatal = function(msg) {
	bindings.getLogManager().writeLogEntry(0, "FATAL", msg);
}
// @pdg-member {"name":"pdg.error","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.error = function(msg) {
	bindings.getLogManager().writeLogEntry(1, "ERROR", msg);
}
// @pdg-member {"name":"pdg.debug","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.debug = function(msg) {
	bindings.getLogManager().writeLogEntry(7, "DEBUG", msg);
}
// @pdg-member {"name":"pdg.trace","type":"function","brief":"","params":[{"name":"msg","type":"string"}]}
bindings.trace = function(msg) {
	bindings.getLogManager().writeLogEntry(9, "TRACE", msg);
}

// replace console log
// @pdg-member {"name":"pdg.captureConsole","type":"function","brief":"","params":[]}
bindings.captureConsole = function() {
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
/* @pdg-member
{
  "name": "pdg.createSerializableObject",
  "type": "function",
  "brief": "Creates a pdg.ISerializable object from a JavaScript object with serialization methods",
  "returns": "object ISerializable",
  "params": [
    {
      "name": "obj",
      "type": "object"
    },
    {
      "name": "classTag",
      "type": "number uint"
    }
  ]
}
*/
bindings.createSerializableObject = function(obj, classTag) {
	
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
/* @pdg-member
{
  "name": "pdg.on",
  "type": "function",
  "brief": "",
  "returns": "object IEventHandler",
  "params": [
    {
      "name": "eventType",
      "type": "number int"
    },
    {
      "name": "func",
      "type": "function"
    }
  ],
  "event_map": {
    "schema": "EventMap",
    "selector": "eventType",
    "callback": "func",
    "returns": {
      "type": "boolean"
    },
    "fallback": {
      "schema": "Event"
    }
  }
}
*/
// @pdg-member {"name":"SoundManager.on","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"eventCode","type":"number int"},{"name":"func","type":"function"}]}
// @pdg-member {"name":"Sound.on","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"eventCode","type":"number int"},{"name":"func","type":"function"}]}
bindings.on = function(eventType, func) {
	var handler = new bindings.IEventHandler(func);
	bindings.getEventManager().addHandler(handler, eventType);
	handler.cancel = function() {
		bindings.getEventManager().removeHandler(handler, eventType);
	};
	return handler;
}

// onStartup(function)
// module.exports.onStartup = function(func) {
// 	return this.on(bindings.eventType_Startup, func);
// }
// onShutdown(function)
// @pdg-member {"name":"pdg.onShutdown","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onShutdown = function(func) {
	return bindings.on(bindings.eventType_Shutdown, func);
}
// onTimer(function)
// @pdg-member {"name":"pdg.onTimer","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onTimer = function(func) {
	return bindings.on(bindings.eventType_Timer, func);
}
// onKeyDown(function)
// @pdg-member {"name":"pdg.onKeyDown","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onKeyDown = function(func) {
	return bindings.on(bindings.eventType_KeyDown, func);
}
// onKeyUp(function)
// @pdg-member {"name":"pdg.onKeyUp","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onKeyUp = function(func) {
	return bindings.on(bindings.eventType_KeyUp, func);
}
// onKeyPress(function)
// @pdg-member {"name":"pdg.onKeyPress","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onKeyPress = function(func) {
	return bindings.on(bindings.eventType_KeyPress, func);
}
// onMouseDown(function)
// @pdg-member {"name":"pdg.onMouseDown","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onMouseDown = function(func) {
	return bindings.on(bindings.eventType_MouseDown, func);
}
// onMouseUp(function)
// @pdg-member {"name":"pdg.onMouseUp","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onMouseUp = function(func) {
	return bindings.on(bindings.eventType_MouseUp, func);
}
// onMouseMove(function)
// @pdg-member {"name":"pdg.onMouseMove","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
bindings.onMouseMove = function(func) {
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
// @pdg-member {"name":"TimerManager.onTimeout","type":"function","brief":"setup handler to be called once after delay ms","returns":"object IEventHandler","params":[{"name":"func","type":"function"},{"name":"delay","type":"number int"}]}
timerManagerProto.onTimeout = function(func, delay) {
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
/* @pdg-member
{
  "name": "TimerManager.onInterval",
  "type": "function",
  "brief": "setup handler to be called regularly at interval ms",
  "returns": "object IEventHandler",
  "params": [
    {
      "name": "func",
      "type": "function"
    },
    {
      "name": "interval",
      "type": "number int"
    }
  ]
}
*/
timerManagerProto.onInterval = function(func, interval) {
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

// Scene helpers register native logical timers, never host-time timers.
if (bindings.Scene) {
    (function(proto) {
        var nextTimer = 1000000;
        if (inbrowser) {
            var browserStartTimer=proto.startTimer;
            proto.startTimer=function(id,delayMs,oneShot) {
                if (!Number.isInteger(id) || !id || !Number.isFinite(delayMs) || delayMs<0 || (oneShot!==undefined && typeof oneShot!=='boolean')) throw new TypeError('Expected timer ID, finite delay and optional boolean');
                browserStartTimer.call(this,id,delayMs,oneShot===undefined?true:oneShot);
            };
        }
        var nativeCancel = proto.cancelTimer, nativeCancelAll = proto.cancelAllTimers;
        var nativeDispose = proto.dispose;
        function removeTimerHandler(scene, id) {
            var handlers = scene._sceneTimerHandlers;
            if (handlers && handlers[id]) {
                scene.removeHandler(handlers[id], bindings.eventType_Timer);
                delete handlers[id];
            }
        }
        proto.cancelTimer = function(id) { nativeCancel.call(this, id); removeTimerHandler(this, id); };
        proto.cancelAllTimers = function() {
            nativeCancelAll.call(this);
            var scene = this;
            Object.keys(this._sceneTimerHandlers || {}).forEach(function(id) { removeTimerHandler(scene, id); });
        };
        function timer(scene, callback, delay, once) {
            if (typeof callback !== 'function') throw new TypeError('Expected timer callback');
            var id = ++nextTimer;
            scene.startTimer(id, delay, once);
            var handler = new bindings.IEventHandler(function(event) {
                if (event.id !== id || scene.isDisposed()) return false;
                try { callback(event); }
                finally { if (once) removeTimerHandler(scene, id); }
                return true;
            });
            if (!scene._sceneTimerHandlers) scene._sceneTimerHandlers = Object.create(null);
            scene._sceneTimerHandlers[id] = handler;
            scene.addHandler(handler, bindings.eventType_Timer);
            handler.timer = id;
            handler.cancel = function() { scene.cancelTimer(id); };
            return handler;
        }
// @pdg-member {"name":"Scene.onTimeout","type":"function","native":false,"brief":"Create a scene-owned one-shot timer; pause and scale follow the scene.","returns":"object IEventHandler","params":[{"name":"callback","type":"function"},{"name":"delayMs","type":"number"}]}
        proto.onTimeout = function(callback, delayMs) { return timer(this, callback, delayMs, true); };
// @pdg-member {"name":"Scene.onInterval","type":"function","native":false,"brief":"Create a scene-owned repeating timer, cancelled on scene disposal.","returns":"object IEventHandler","params":[{"name":"callback","type":"function"},{"name":"intervalMs","type":"number"}]}
        proto.onInterval = function(callback, intervalMs) { return timer(this, callback, intervalMs, false); };
// @pdg-member {"name":"Scene.on","type":"function","native":false,"brief":"Subscribe to scene events with an idempotent cancellation handle.","returns":"object IEventHandler","params":[{"name":"eventType","type":"number int"},{"name":"callback","type":"function"}]}
        proto.on = function(eventType, callback) {
            if (this.isDisposed()) throw new Error('Scene is disposed');
            var scene = this, cancelled = false;
            var handler = new bindings.IEventHandler(function(event) {
                return !cancelled && !scene.isDisposed() && !!callback(event);
            });
            this.addHandler(handler, eventType);
            handler.cancel = function() { if (!cancelled) { cancelled = true; scene.removeHandler(handler, eventType); } };
            return handler;
        };
// @pdg-member {"name":"Scene.subscribe","type":"function","native":false,"brief":"Own an exact subscription to an external emitter; raw events can run while paused.","returns":"object IEventHandler","params":[{"name":"emitter","type":"object EventEmitter"},{"name":"eventType","type":"number int"},{"name":"callback","type":"function"}]}
        proto.subscribe = function(emitter, eventType, callback) {
            if (this.isDisposed()) throw new Error('Scene is disposed');
            var scene = this, cancelled = false;
            var handler = new bindings.IEventHandler(function(event) {
                return !cancelled && !scene.isDisposed() && !!callback(event);
            });
            emitter.addHandler(handler, eventType);
            handler.cancel = function() { if (!cancelled) { cancelled = true; emitter.removeHandler(handler, eventType); } };
            if (!this._sceneSubscriptions) this._sceneSubscriptions = [];
            this._sceneSubscriptions.push(handler);
            return handler;
        };
        proto.dispose = function() {
            var subscriptions = this._sceneSubscriptions || [];
            this._sceneSubscriptions = [];
            try { nativeDispose.call(this); }
            finally {
                this._sceneTimerHandlers = Object.create(null);
                subscriptions.forEach(function(handler) { handler.cancel(); });
            }
        };
    }(bindings.Scene.prototype));
}
// @pdg-contract {"name":"Scene.onTimeout","value":{"params":{"callback":{"schema":"TimerNotification"}},"returns":{"schema":"TimerSubscription"}}}
// @pdg-contract {"name":"Scene.onInterval","value":{"params":{"callback":{"schema":"TimerNotification"}},"returns":{"schema":"TimerSubscription"}}}
// @pdg-contract {"name":"Scene.on","value":{"params":{"callback":{"schema":"EventCallback"}},"returns":{"schema":"EventSubscription"}}}
// @pdg-contract {"name":"Scene.subscribe","value":{"params":{"callback":{"schema":"EventCallback"}},"returns":{"schema":"EventSubscription"}}}

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
                timer.callback({ emitter: timerManager, eventType: bindings.eventType_Timer,
                    id: timer.id, millisec: firedAt, msElapsed: elapsed });
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
// @pdg-member {"name":"SoundManager.onDonePlaying","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
// @pdg-member {"name":"Sound.onDonePlaying","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
    soundManagerProto.onDonePlaying = function(func) {
        return this.on(bindings.soundEvent_DonePlaying, func);
    }
	bindings.Sound.prototype.onDonePlaying = soundManagerProto.onDonePlaying;

    // Sound.onLooping(function)
// @pdg-member {"name":"SoundManager.onLooping","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
// @pdg-member {"name":"Sound.onLooping","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
    soundManagerProto.onLooping = function(func) {
        return this.on(bindings.soundEvent_Looping, func);
    }
	bindings.Sound.prototype.onLooping = soundManagerProto.onLooping;

    // Sound.onFailedToPlay(function)
// @pdg-member {"name":"SoundManager.onFailedToPlay","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
// @pdg-member {"name":"Sound.onFailedToPlay","type":"function","brief":"","returns":"object IEventHandler","params":[{"name":"func","type":"function"}]}
    soundManagerProto.onFailedToPlay = function(func) {
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
// @pdg-class {"name":"AnimationSpringTarget"}
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
// @pdg-class {"name":"AnimationContactTarget"}
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
/* @pdg-member
{
  "name": "pdg.animationHasTag",
  "type": "function",
  "brief": "test an authored tag in an owned pose snapshot",
  "returns": "boolean",
  "params": [
    {
      "name": "pose",
      "type": "object"
    },
    {
      "name": "object",
      "type": "string"
    },
    {
      "name": "tag",
      "type": "string"
    }
  ]
}
*/
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
            this._clearAnimationHelpers();
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
        function canonical(value) { return require('pdg_em_runtime').canonicalRetained(bindings, value); }
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
        const getPart = sprite.getPart;
        sprite.getPart = function(value) { return getPart.call(this, id(value)); };

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

        [sprite, part, bindings.Particle && bindings.Particle.prototype].filter(Boolean).forEach(function(proto) {
            const read = proto._readPhysics;
            proto._readPhysics = function() { return canonical(read.call(this)); };
        });

        body.setMode = function(mode) { this._setMode(integer(mode, 1, 3, 'body mode')); return this; };

        body.setVelocity = function(x, y) { this._setVelocity(typeof x === 'number' ? { x: x, y: y } : x); return this; };
// @pdg-member {"name":"AnimationSpringTarget.applyImpulse","type":"function","brief":"apply an impulse to the spring target","params":[{"name":"x","type":"number"},{"name":"y","type":"number"}]}
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
    });
    ["setCategory", "setCollisionMask", "setGroup", "setPolygon"].forEach(function(name) {
        collider[name] = function() { this['_' + name].apply(this, arguments); return this; };
    });
    ['setCircle','addCircle'].forEach(function(name) {
        collider[name] = function(radius, center) { const result = this['_' + name](radius, center === undefined ? {x:0,y:0} : center); return name === 'setCircle' ? this : result; };
    });
    ["addPolygon", "removeShape", "getShapeId"].forEach(function(name) {
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
    bindings.Sprite.prototype.setFrameCollisionMask=function(image,mask) { this._setFrameCollisionMask(image,mask);return this; };
    collider.setContactHandler=function(callback) {
        if(callback!==null && typeof callback!=='function') throw new TypeError('Expected a function or null');
        this._setContactHandler(callback===null?null:function(event) {
// @pdg-member {"name":"Sprite.collider","type":"object Collider","readonly":true}
// @pdg-member {"name":"Particle.collider","type":"object Collider","readonly":true}
// @pdg-member {"name":"Part.collider","type":"object Collider","readonly":true}
            event.collider=canonical(event.collider);event.other=canonical(event.other);callback(event);
        });return this;
    };
    collider.setCollisionFilter=function(callback) {
        if(callback!==null && typeof callback!=='function') throw new TypeError('Expected a function or null');
        this._setCollisionFilter(callback===null?null:function(a,b) {return callback(canonical(a),canonical(b));});return this;
    };


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
    const body = bindings.PhysicsBody.prototype;
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
        });
        const particle = bindings.Particle.prototype, emitter = bindings.ParticleEmitter.prototype;


        emitter.setSeed = function(seed) { this._setSeed(uint(seed)); return this; };
        emitter.setParticleSpeed = function(min, max) { this._setParticleSpeed(min, max === undefined ? min : max); return this; };
        emitter.emit = function(count) { return this._emit(uint(count === undefined ? 1 : count)); };
        const layer = bindings.SpriteLayer.prototype;
        const getNthParticle = layer.getNthParticle;
        layer.getNthParticle = function(index) { return getNthParticle.call(this, uint(index)); };
        layer.setMaxParticles = function(count) { this._setMaxParticles(uint(count)); return this; };
    }
// @pdg-member {"name":"Particle.emitter","type":"object ParticleEmitter","readonly":true}
    Object.defineProperty(bindings.Particle.prototype, 'emitter', {
        get: function() { return this.getParticleEmitter(); }, enumerable: true
    });
}

// Collision ownership is optional and read-only, like body ownership.
if (bindings.Collider && bindings.Sprite) {
    const noCollider = new bindings.Sprite()._readCollider();
// @pdg-member {"name":"Collider.NoCollider","type":"object Collider","readonly":true,"static":true}
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
// @pdg-member {"name":"PhysicsBody.NoPhysics","type":"object PhysicsBody","readonly":true,"static":true}
    Object.defineProperty(bindings.PhysicsBody, 'NoPhysics', {
        value: noPhysics, enumerable: true
    });
    Object.defineProperty(bindings, 'NoPhysics', { value: noPhysics, enumerable: true });
    [bindings.Sprite, bindings.Part, bindings.Particle].filter(Boolean).forEach(function(type) {
        if (!type) return;
        const read = type.prototype._readPhysics;
// @pdg-member {"name":"Sprite.physics","type":"object PhysicsBody","readonly":true}
// @pdg-member {"name":"Particle.physics","type":"object PhysicsBody","readonly":true}
// @pdg-member {"name":"Part.physics","type":"object PhysicsBody","readonly":true}
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

// Camera browser handles share native identity across port attachments.
if (inbrowser && bindings.Camera) {
    (function() {
        const Native = bindings.Camera;
        function canonical(handle) { return require('pdg_em_runtime').canonicalRetained(bindings, handle); }
        function Camera() { return canonical(new Native()); }
        Camera.prototype=Native.prototype; Object.setPrototypeOf(Camera,Native); bindings.Camera=Camera;

        Camera.prototype.cutTo=function(destination) {
            if (arguments.length!==1 || !(destination instanceof Camera)) throw new TypeError('Expected one destination Camera');
            this._cutTo(destination);return this;
        };
        Camera.prototype.matchCutTo=function(destination,options) {
            if (!(destination instanceof Camera) || !options || typeof options!=='object') throw new TypeError('Expected destination Camera and matching options');
            if (!(options.matchSource instanceof bindings.Sprite) || !(options.matchTarget instanceof bindings.Sprite)) throw new TypeError('Expected matchSource and matchTarget Sprites');
            function number(name,fallback) {var value=options[name]===undefined?fallback:options[name];if(typeof value!=='number' || !Number.isFinite(value))throw new TypeError('Expected finite '+name);return value;}
            function boolean(name) {var value=options[name]===undefined?false:options[name];if(typeof value!=='boolean')throw new TypeError('Expected boolean '+name);return value;}
            var mode=number('mode',bindings.matchSource);
            if (!Number.isInteger(mode) || mode<bindings.matchSource || mode>bindings.matchTargetAndSize) throw new TypeError('Invalid camera match mode');
            var approach=number('approachEasing',bindings.easeInQuad),settle=number('settleEasing',bindings.easeOutQuad);
            if (!Number.isInteger(approach) || !Number.isInteger(settle)) throw new TypeError('Expected integer easing identifiers');
            this._matchCutTo(destination,options.matchSource,options.matchTarget,mode,number('approachSeconds',.4),number('settleSeconds',.4),boolean('settleReturnsCamera'),approach,settle);return this;
        };
        Camera.prototype.matchFadeTo=function(destination,options) {
            if (!(destination instanceof Camera) || !options || typeof options!=='object') throw new TypeError('Expected destination Camera and matching options');
            if (!(options.matchSource instanceof bindings.Sprite) || !(options.matchTarget instanceof bindings.Sprite)) throw new TypeError('Expected matchSource and matchTarget Sprites');
            function number(name,fallback) {var value=options[name]===undefined?fallback:options[name];if(typeof value!=='number' || !Number.isFinite(value))throw new TypeError('Expected finite '+name);return value;}
            function boolean(name) {var value=options[name]===undefined?false:options[name];if(typeof value!=='boolean')throw new TypeError('Expected boolean '+name);return value;}
            var mode=number('mode',bindings.matchSource);
            if (!Number.isInteger(mode) || mode<bindings.matchSource || mode>bindings.matchTargetAndSize) throw new TypeError('Invalid camera match mode');
            var approach=number('approachEasing',bindings.easeInQuad),settle=number('settleEasing',bindings.easeOutQuad);
            if (!Number.isInteger(approach) || !Number.isInteger(settle)) throw new TypeError('Expected integer easing identifiers');
            var fade=number('fadeEasing',bindings.linearTween);if (!Number.isInteger(fade)) throw new TypeError('Expected integer fadeEasing');
            this._matchFadeTo(destination,options.matchSource,options.matchTarget,mode,number('approachSeconds',.4),number('settleSeconds',.4),boolean('settleReturnsCamera'),approach,settle,number('fadeSeconds',.4),fade);return this;
        };
        Camera.prototype.transitionTo=function(destination,seconds,style,easing) {
            if (!(destination instanceof Camera)) throw new TypeError('Expected a destination Camera');
            if (typeof seconds!=='number') throw new TypeError('Expected numeric seconds');
            style=style===undefined?bindings.camera_Crossfade:style;
            easing=easing===undefined?bindings.easeInOutQuad:easing;
            if (!Number.isInteger(style) || !Number.isInteger(easing)) throw new TypeError('Expected integer style and easing');
            this._transitionTo(destination,seconds,style,easing);return this;
        };
        Camera.prototype.lumaFadeTo=function(destination,seconds,mask,softness,darkFirst,easing) {
            if (!(destination instanceof Camera)) throw new TypeError('Expected a destination Camera');
            mask=mask===undefined?null:mask; softness=softness===undefined?.1:softness; darkFirst=darkFirst===undefined?false:darkFirst; easing=easing===undefined?bindings.easeInOutQuad:easing;
            if (typeof seconds!=='number' || typeof softness!=='number' || typeof darkFirst!=='boolean' || !Number.isInteger(easing)) throw new TypeError('Invalid luma arguments');
            this._lumaFadeTo(destination,seconds,mask,softness,darkFirst,easing);return this;
        };
        Camera.prototype.whipPanTo=function(destination,seconds,style,blur,easing) {
            if (!(destination instanceof Camera)) throw new TypeError('Expected a destination Camera');
            style=style===undefined?bindings.camera_WhipLeft:style; blur=blur===undefined?0:blur; easing=easing===undefined?bindings.easeInOutQuad:easing;
            if (typeof seconds!=='number' || typeof blur!=='number' || !Number.isInteger(style) || !Number.isInteger(easing)) throw new TypeError('Invalid whip arguments');
            this._whipPanTo(destination,seconds,style,blur,easing);return this;
        };
        Camera.prototype.stopIt=function() {this._cameraStopIt();return this;};
        Camera.prototype.restartIt=function() {this._cameraRestartIt();return this;};
        Camera.prototype.setPixelSnapping=function(snap) {
            snap=snap===undefined?true:snap;
            if (typeof snap!=='boolean') throw new TypeError('Expected boolean pixel snapping');
            this._setPixelSnapping(snap); return this;
        };

        const setLayerCamera = bindings.SpriteLayer.prototype.setCamera;
        bindings.SpriteLayer.prototype.setCamera=function(camera) {
            if (camera!=null && !(camera instanceof Camera)) throw new TypeError('Expected a Camera or null');
            setLayerCamera.call(this, camera || null);
        };
        ['setCameraAnchor','setCameraDrawingEnabled'].forEach(function(name) {
            const native=bindings.Port.prototype[name];
            bindings.Port.prototype[name]=function(value) { native.call(this,value); return this; };
        });

        bindings.registerSerializableClass(Camera);
    })();
}

if (bindings.Camera) {
// @pdg-member {"name":"Camera.onZoomComplete","type":"function","brief":"listen for completion of camera zoom operations","returns":"object IEventHandler","params":[{"name":"callback","type":"function"}]}
    bindings.Camera.prototype.onZoomComplete = function(callback) {
        if (typeof callback !== 'function') throw new TypeError('onZoomComplete requires a callback');
        var camera = this;
        var handler = new bindings.IEventHandler(function(event) { return callback.call(camera, event); });
        camera.addHandler(handler, bindings.eventType_ZoomComplete);
        handler.cancel = function() { camera.removeHandler(handler, bindings.eventType_ZoomComplete); };
        return handler;
    };
}

// Named definitions and collective recorders share the native command inventory.
// Argument values are captured by C++ before a graph is modified. No live target
// is manufactured merely to validate or record a subclass operation.
if (bindings.AnimationScript && bindings.Troupe) {
    const commands = require((embedded_pdg || jsc || inbrowser) ? 'interface_metadata_data' : './interface_metadata_data').animation_commands;
    function acceptsRecorderArgument(value, param) {
        if (value === null) return param.type.includes('*');
        if (param.kind === 'number' || param.kind === 'EasingFunc') return typeof value === 'number' && Number.isFinite(value);
        if (param.kind === 'boolean' || param.kind === 'string') return typeof value === param.kind;
        if (param.kind === 'Color' && (typeof value === 'string' || typeof value === 'number')) return true;
        if (['AffineTransform','CameraMatchOptions','AnimationPhysicsDriveSettings','ParticleTrailOptions'].includes(param.kind)) return typeof value === 'object' && value !== null;
        return typeof bindings[param.kind] === 'function' && value instanceof bindings[param.kind];
    }
    for (const Type of [bindings.AnimationScript, bindings.Troupe]) {
        for (const name of new Set(commands.map(command => command.name))) {
            if (typeof Type.prototype[name] === 'function') continue;
            const variants = commands.filter(command => command.name === name);
            Type.prototype[name] = function() {
                const args=Array.from(arguments);
                // Omitted trailing optionals keep each playback target's native defaults.
                while(args.length && args[args.length-1] === undefined) args.pop();
                const command=variants.find(command => args.length <= command.params.length &&
                    command.params.every((param,index) => index < args.length
                        ? acceptsRecorderArgument(args[index],param) : !!param.default));
                if (!command) throw new TypeError(name + ': arguments do not match a recorder overload');
                if (inbrowser) {
                    const values=args.map((value,i)=>command.params[i].kind==='Color' && (typeof value==='string' || typeof value==='number') ? new bindings.Color(value) : value);
                    bindings._recordAnimationCommand(this,command.id,values);
                } else this._recordAnimationCommand.apply(this,[command.id].concat(args));
                return this;
            };
        }
    }
}

// Browser scripts bind the same native graph executor as the native runtimes.
if (inbrowser && bindings.AnimationScript) {
    (function() {
        var prototype=bindings.Animated.prototype;
        var remember=require('pdg_em_runtime').rememberAnimationOwner;
        prototype.playScript=function(name) { remember(this)._playScript(name); return this; };
        ['batch','endBatch','series','endSeries','andAlso','otherwise','endWhen','endOtherwise','yoyo',
         'stopIt','restartIt','pauseIt','resumeIt'].forEach(function(name) {
            prototype[name]=function() { remember(this)['_' + name](); return this; };
        });
        ['mark','jumpToMark'].forEach(function(name) {
            prototype[name]=function(label, state) {
                if (arguments.length<1 || arguments.length>2 || typeof label!=='string' || (arguments.length===2 && typeof state!=='boolean'))
                    throw new TypeError(name+' requires a name and an optional boolean');
                remember(this)['_'+name](label, arguments.length===1?true:state); return this;
            };
        });
        if(bindings.Troupe) {
            var add=bindings.Troupe.prototype.add;
            bindings.Troupe.prototype.add=function(member) {
                var result=add.apply(this,arguments);
                remember(this); remember(member); return result;
            };
        }
        prototype.repeat=function(count) {
            if (arguments.length>1 || (arguments.length && (!Number.isInteger(count) || count<0 || count>2147483647))) throw new TypeError('repeat count must be a nonnegative integer');
            this._repeat(arguments.length?count:-1); return this;
        };
        ['getLocation','getBoundingBox','getRotatedBounds','getSize','getWidth','getHeight','getScale','getRotation','getCenterOffset','getMovement','getStretching','getSpin','isFlippedX','isFlippedY','isSchedulePaused','hasScheduledAnimations'].forEach(function(name) {
            bindings.AnimationScript.prototype[name]=function() { throw new Error('Animation definitions have no live target state'); };
        });

    })();
}

// Apply IDL-generated browser defaults, overload checks and receiver returns.
if (inbrowser) browserGeneratedBindings.install(bindings);
if (inbrowser && bindings.Bone) {
    bindings.Bone.prototype.setIKLimits=function(first,second){
        if(arguments.length!==1 && arguments.length!==2)throw new TypeError('Expected a rotary limit or minimum and maximum angles');
        if(arguments.length===1 && !(first instanceof bindings.PhysicsConstraint))throw new TypeError('Expected a PhysicsConstraint');
        this._setIKLimits(first,second);return this;
    };
}

// Install after all helpers and wrappers have registered their public exports.
var interfaceMetadata = require((embedded_pdg || jsc || inbrowser) ? 'interface_metadata' : './interface_metadata');
var interfaceMetadataData = require((embedded_pdg || jsc || inbrowser) ? 'interface_metadata_data' : './interface_metadata_data');
interfaceMetadata.install(bindings, interfaceMetadataData, {
    runtime: inbrowser ? 'browser' : jsc ? 'ios' : embedded_pdg ? 'native' : 'node',
    capabilities: {graphics: bindings.hasGraphics, sound: bindings.hasSound, network: bindings.hasNetwork},
    scope: 'Root exports and build capabilities of the runtime generating this inventory; instance members are declared contracts.'
});
if (typeof module !== 'undefined' && module.exports && module.exports !== bindings) {
    module.exports.getInterfaceMetadata = bindings.getInterfaceMetadata;
    module.exports.describeInterface = bindings.describeInterface;
}

/* @pdg-schema
{
  "name": "EventSubscription",
  "value": {
    "kind": "record",
    "fields": {},
    "extends": [
      "object IEventHandler"
    ],
    "methods": {
      "cancel": {
        "params": [],
        "returns": {
          "type": "void"
        },
        "description": "Unregister this handler."
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "TimerSubscription",
  "value": {
    "kind": "record",
    "fields": {
      "timer": {
        "type": "number"
      }
    },
    "extends": [
      "EventSubscription"
    ]
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.on",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "EventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onShutdown",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "ShutdownEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onTimer",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "TimerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onKeyDown",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "KeyEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onKeyUp",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "KeyEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onKeyPress",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "KeyPressEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onMouseDown",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "MouseEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onMouseUp",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "MouseEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.onMouseMove",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "func": {
        "schema": "MouseEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "TimerManager.onTimeout",
  "value": {
    "returns": {
      "schema": "TimerSubscription"
    },
    "params": {
      "func": {
        "schema": "TimerNotification"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "TimerManager.onInterval",
  "value": {
    "returns": {
      "schema": "TimerSubscription"
    },
    "params": {
      "func": {
        "schema": "TimerNotification"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sound.on",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sound.onDonePlaying",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sound.onFailedToPlay",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sound.onLooping",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SoundManager.on",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SoundManager.onDonePlaying",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SoundManager.onFailedToPlay",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SoundManager.onLooping",
  "value": {
    "params": {
      "func": {
        "schema": "SoundEventCallback"
      }
    }
  }
}
*/

/* @pdg-member
{
  "name": "Sprite.on",
  "type": "function",
  "brief": "Register a numeric Sprite event or a string animation lifecycle event.",
  "returns": "object IEventHandler",
  "returns_contract": {
    "one_of": [
      {
        "type": "object IEventHandler"
      },
      {
        "type": "this"
      }
    ],
    "by_parameter": {
      "eventCode": {
        "type": "object IEventHandler"
      },
      "event": {
        "type": "this"
      }
    }
  }
}
*/
/* @pdg-contract
{
  "name": "Sprite.on",
  "value": {
    "params": {
      "func": {
        "schema": "EventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onAnimationBlendComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onAnimationEnd",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onAnimationLoop",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onAnimationPhysicsRecoveryComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteRecoveryEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onCollideSprite",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteCollisionEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onCollideWall",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteCollisionEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onExitLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onFadeComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onFadeInComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onFadeOutComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onMouseClick",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onMouseDown",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onMouseEnter",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onMouseLeave",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onMouseUp",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onOffscreen",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.onOnscreen",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.on",
  "value": {
    "params": {
      "func": {
        "schema": "EventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onAnimationComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onAnimationEnd",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onAnimationLoop",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onAnimationStart",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onCollideSprite",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteCollisionEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onCollideWall",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteCollisionEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onDrawPortComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onErasePort",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onExitLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onFadeComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onFadeInComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onFadeOutComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onLayerFadeInComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onLayerFadeOutComplete",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onMouseClick",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onMouseDown",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onMouseEnter",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onMouseLeave",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onMouseUp",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteTouchNotificationCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onOffscreen",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onOnscreen",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteAnimationEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onPostAnimateLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onPostDrawLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onPreAnimateLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "SpriteLayer.onPreDrawLayer",
  "value": {
    "params": {
      "func": {
        "schema": "SpriteLayerEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Camera.onZoomComplete",
  "value": {
    "returns": {
      "schema": "EventSubscription"
    },
    "params": {
      "callback": {
        "schema": "CameraZoomEventCallback"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.animationHasTag",
  "value": {
    "params": {
      "pose": {
        "schema": "AnimationPose"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.setAnimationBoneTransform",
  "value": {
    "params": {
      "transform": {
        "schema": "AnimationTransform"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationIKOptions",
  "value": {
    "kind": "record",
    "fields": {
      "root": {
        "one_of": [
          {
            "type": "string"
          },
          {
            "type": "number"
          }
        ]
      },
      "middle": {
        "one_of": [
          {
            "type": "string"
          },
          {
            "type": "number"
          }
        ]
      },
      "tip": {
        "one_of": [
          {
            "type": "string"
          },
          {
            "type": "number"
          }
        ]
      },
      "rootLength": {
        "type": "number",
        "optional": true
      },
      "middleLength": {
        "type": "number",
        "optional": true
      },
      "targetX": {
        "type": "number",
        "optional": true
      },
      "targetY": {
        "type": "number",
        "optional": true
      },
      "influence": {
        "type": "number",
        "optional": true
      },
      "space": {
        "type": "number",
        "optional": true
      },
      "bendDirection": {
        "type": "number",
        "optional": true
      },
      "stretch": {
        "type": "number",
        "optional": true
      },
      "targetRotation": {
        "type": "number",
        "optional": true
      },
      "rootMin": {
        "type": "number",
        "optional": true
      },
      "rootMax": {
        "type": "number",
        "optional": true
      },
      "middleMin": {
        "type": "number",
        "optional": true
      },
      "middleMax": {
        "type": "number",
        "optional": true
      },
      "matchOrientation": {
        "type": "boolean",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.addAnimationIK",
  "value": {
    "params": {
      "config": {
        "schema": "AnimationIKOptions"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationModifierContext",
  "value": {
    "kind": "record",
    "fields": {
      "simulationDeltaSeconds": {"type": "number"},
      "deltaSeconds": {
        "type": "number"
      },
      "root": {
        "schema": "AnimationTransform"
      },
      "revision": {
        "type": "string"
      }
    },
    "lifetime": "Borrowed and frozen for the duration of the synchronous callback."
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPoseView",
  "value": {
    "kind": "context",
    "fields": {},
    "lifetime": "Valid only during the modifier callback. Retain copy() instead.",
    "methods": {
      "copy": {
        "params": [],
        "returns": {
          "schema": "AnimationPose"
        }
      },
      "getLocalTransform": {
        "params": [
          {
            "name": "id",
            "one_of": [
              {
                "type": "string"
              },
              {
                "type": "number"
              }
            ]
          }
        ],
        "returns": {
          "schema": "AnimationTransform"
        }
      },
      "setLocalTransform": {
        "params": [
          {
            "name": "id",
            "one_of": [
              {
                "type": "string"
              },
              {
                "type": "number"
              }
            ]
          },
          {
            "name": "transform",
            "schema": "AnimationTransform"
          }
        ],
        "returns": {
          "type": "void"
        }
      },
      "rotateLocal": {
        "params": [
          {
            "name": "id",
            "one_of": [
              {
                "type": "string"
              },
              {
                "type": "number"
              }
            ]
          },
          {
            "name": "angle",
            "type": "number"
          }
        ],
        "returns": {
          "type": "void"
        }
      },
      "getTransform": {
        "params": [
          {
            "name": "id",
            "one_of": [
              {
                "type": "string"
              },
              {
                "type": "number"
              }
            ]
          },
          {
            "name": "space",
            "type": "number",
            "optional": true
          }
        ],
        "returns": {
          "schema": "AnimationTransform"
        }
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationModifierCallback",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "pose",
        "schema": "AnimationPoseView"
      },
      {
        "name": "context",
        "schema": "AnimationModifierContext"
      }
    ],
    "returns": {
      "type": "undefined"
    },
    "synchronous": true
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.addAnimationModifier",
  "value": {
    "params": {
      "callback": {
        "schema": "AnimationModifierCallback"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPhysicsBodyDefinition",
  "value": {
    "kind": "record",
    "fields": {
      "bone": {
        "one_of": [
          {
            "type": "string"
          },
          {
            "type": "number"
          }
        ]
      },
      "mass": {
        "type": "number"
      },
      "length": {
        "type": "number"
      },
      "radius": {
        "type": "number"
      },
      "mode": {
        "type": "number",
        "optional": true
      },
      "offsetX": {
        "type": "number",
        "optional": true
      },
      "offsetY": {
        "type": "number",
        "optional": true
      },
      "offsetRotation": {
        "type": "number",
        "optional": true
      },
      "friction": {
        "type": "number",
        "optional": true
      },
      "elasticity": {
        "type": "number",
        "optional": true
      },
      "categories": {
        "type": "number",
        "optional": true
      },
      "mask": {
        "type": "number",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPhysicsJointDefinition",
  "value": {
    "kind": "record",
    "fields": {
      "parent": {
        "type": "number"
      },
      "child": {
        "type": "number"
      },
      "parentX": {
        "type": "number",
        "optional": true
      },
      "parentY": {
        "type": "number",
        "optional": true
      },
      "childX": {
        "type": "number",
        "optional": true
      },
      "childY": {
        "type": "number",
        "optional": true
      },
      "minAngle": {
        "type": "number",
        "optional": true
      },
      "maxAngle": {
        "type": "number",
        "optional": true
      },
      "maxForce": {
        "type": "number",
        "optional": true
      },
      "collide": {
        "type": "boolean",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPhysicsDefinition",
  "value": {
    "kind": "record",
    "fields": {
      "version": {
        "literal": 1,
        "optional": true
      },
      "rootMode": {
        "type": "number",
        "optional": true
      },
      "rootBody": {
        "type": "number",
        "optional": true
      },
      "selfCollisions": {
        "type": "boolean",
        "optional": true
      },
      "bodies": {
        "items": {
          "schema": "AnimationPhysicsBodyDefinition"
        }
      },
      "joints": {
        "items": {
          "schema": "AnimationPhysicsJointDefinition"
        },
        "optional": true
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.setupAnimationPhysics",
  "value": {
    "params": {
      "definition": {
        "schema": "AnimationPhysicsDefinition"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPhysicsDriveOptions",
  "value": {
    "kind": "record",
    "fields": {
      "maxForce": {
        "type": "number"
      },
      "maxTorque": {
        "type": "number"
      },
      "frequency": {
        "type": "number",
        "optional": true
      },
      "dampingRatio": {
        "type": "number",
        "optional": true
      },
      "direction": {
        "type": "number",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "AnimationPhysicsDriveSettings",
  "value": {
    "kind": "record",
    "fields": {
      "maxForce": {
        "type": "number"
      },
      "maxTorque": {
        "type": "number"
      },
      "frequency": {
        "type": "number"
      },
      "dampingRatio": {
        "type": "number"
      },
      "direction": {
        "type": "number"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.setAnimationPhysicsDriveSettings",
  "value": {
    "params": {
      "settings": {
        "schema": "AnimationPhysicsDriveOptions"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Sprite.getAnimationPhysicsDriveSettings",
  "value": {
    "returns": {
      "schema": "AnimationPhysicsDriveSettings",
      "nullable": true
    }
  }
}
*/

/* @pdg-schema
{
  "name": "SerializableImplementation",
  "value": {
    "kind": "record",
    "fields": {},
    "methods": {
      "getSerializedSize": {
        "params": [
          {
            "name": "serializer",
            "type": "object Serializer"
          }
        ],
        "returns": {
          "type": "number"
        }
      },
      "serialize": {
        "params": [
          {
            "name": "serializer",
            "type": "object Serializer"
          }
        ],
        "returns": {
          "type": "void"
        }
      },
      "deserialize": {
        "params": [
          {
            "name": "deserializer",
            "type": "object Deserializer"
          }
        ],
        "returns": {
          "type": "void"
        }
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "pdg.createSerializableObject",
  "value": {
    "params": {
      "obj": {
        "schema": "SerializableImplementation"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "TimerNotification",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "event",
        "schema": "TimerEvent"
      }
    ],
    "returns": {
      "type": "void"
    }
  }
}
*/

// Each scene reuses one result array and a pool of hit records.
if (bindings.Scene && bindings.CollisionQueryBuffer) {
    (function() {
        var NativeBuffer = bindings.CollisionQueryBuffer, states = new WeakMap(), ALL = 4294967295;
        function mask(value, fallback) {
            if (value === undefined) return fallback;
            if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > ALL)
                throw new RangeError('Expected an unsigned 32-bit query mask');
            return value;
        }
        function reset(state) {
            for (var i = 0; i < state.active; ++i) state.pool[i].collider = null;
            state.active = 0; state.hits.length = 0; state.buffer.clear();
        }
        function prepare(scene, capacity) {
            var state = states.get(scene);
            if (!state) {
                state = {buffer: new NativeBuffer(capacity), capacity: capacity, pool: [], hits: [], active: 0, busy: false};
                states.set(scene, state);
            }
            if (state.busy) throw new Error('Cannot query a scene from a query predicate');
            reset(state);
            if (capacity > state.capacity) {
                if (inbrowser) state.buffer.delete();
                state.buffer = new NativeBuffer(capacity); state.capacity = capacity;
            }
            while (state.pool.length < capacity) state.pool.push({collider: null, shapeId: 0,
                point: new bindings.Point(), normal: new bindings.Vector(), fraction: 0, distance: 0, initialOverlap: false});
            return state;
        }
        var methods = {raycast: ['raycast', 2, true], sweepCircle: ['sweepCircle', 3, true],
            overlapPoint: ['overlapPoint', 1, false], overlapCircle: ['overlapCircle', 2, false],
            overlapBox: ['overlapBox', 1, false], overlapCapsule: ['overlapCapsule', 3, false],
            nearestPoint: ['nearestPoint', 2, true]};
        Object.keys(methods).forEach(function(name) {
            var entry = methods[name], nativeQuery = bindings.Scene.prototype['_' + entry[0]], arity = entry[1];
            bindings.Scene.prototype[name] = function() {
                var cast = name === 'raycast' || name === 'sweepCircle';
                var multiple = cast && typeof arguments[arity] === 'number';
                var single = entry[2] && !multiple;
                if (arguments.length < arity || arguments.length > arity + (multiple ? 2 : 1))
                    throw new TypeError('Expected geometry, optional maxHits for casts, and optional query options');
                var options = arguments[arity + (multiple ? 1 : 0)];
                if (options === undefined) options = {};
                if (!options || typeof options !== 'object' || Array.isArray(options) || options instanceof NativeBuffer)
                    throw new TypeError('Expected query options');
                var maxHits = multiple ? arguments[arity] : (single ? 1 : (options.maxHits === undefined ? 16 : options.maxHits));
                if (!Number.isInteger(maxHits) || maxHits < 0 || maxHits > 1048576) throw new RangeError('maxHits must be an integer from 0 to 1048576');
                var sensors = options.includeSensors === undefined ? true : options.includeSensors;
                if (typeof sensors !== 'boolean') throw new TypeError('includeSensors must be boolean');
                var layerMask = mask(options.layerMask, ALL), categoryMask = mask(options.categoryMask, ALL);
                var state = prepare(this, single ? 1 : maxHits), results = state.buffer;
                results.configure(layerMask, categoryMask, sensors); state.busy = true;
                var predicateFailure;
                try {
                    if (options.layers !== undefined) {
                        if (!Array.isArray(options.layers)) throw new TypeError('layers must be an array');
                        results.selectLayers(); options.layers.forEach(function(layer) { results.addLayer(layer); });
                    }
                    [['excludedColliders','excludeCollider'],['excludedBodies','excludeBody']].forEach(function(pair) {
                        var values = options[pair[0]];
                        if (values === undefined) return;
                        if (!Array.isArray(values)) throw new TypeError(pair[0] + ' must be an array');
                        values.forEach(function(value) { results[pair[1]](value); });
                    });
                    if (options.predicate !== undefined) {
                        if (typeof options.predicate !== 'function') throw new TypeError('predicate must be a function');
                        results.setPredicate(function(collider) {
                            if (predicateFailure) return false;
                            try {
                                if (inbrowser) collider = require('pdg_em_runtime').canonicalRetained(bindings, collider);
                                var accepted = options.predicate(collider);
                                if (typeof accepted !== 'boolean') throw new TypeError('Query predicate must return a boolean');
                                return accepted;
                            } catch (error) { predicateFailure = error; return false; }
                        });
                    }
                    var args = Array.prototype.slice.call(arguments, 0, arity); args.push(results);
                    var count = nativeQuery.apply(this, args);
                    if (predicateFailure) throw predicateFailure;
                    count = Math.min(count, single ? 1 : maxHits);
                    for (var i = 0; i < count; ++i) {
                        var hit = state.pool[i], collider = results.getCollider(i);
                        if (inbrowser) collider = require('pdg_em_runtime').canonicalRetained(bindings, collider);
                        hit.collider = collider; hit.shapeId = results.getShapeId(i);
                        hit.point.x = results.getPointX(i); hit.point.y = results.getPointY(i);
                        hit.normal.x = results.getNormalX(i); hit.normal.y = results.getNormalY(i);
                        hit.fraction = results.getFraction(i); hit.distance = results.getDistance(i);
                        hit.initialOverlap = results.getInitialOverlap(i); state.hits.push(hit); state.active++;
                    }
                    return single ? (count ? state.pool[0] : null) : state.hits;
                } catch (error) { reset(state); throw error; }
                finally { results.configure(ALL, ALL, true); results.clear(); state.busy = false; }
            };
        });
        var nativeDispose = bindings.Scene.prototype.dispose;
        bindings.Scene.prototype.dispose = function() {
            nativeDispose.call(this);
            var state = states.get(this);
            if (state) {
                reset(state);
                if (inbrowser) state.buffer.delete();
                states.delete(this);
            }
        };
        delete bindings.CollisionQueryBuffer;
        if (typeof module !== 'undefined' && module.exports) delete module.exports.CollisionQueryBuffer;
    }());
}
// @pdg-member {"name":"Scene.raycast","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit","params":[[{"name":"start","type":"object Point"},{"name":"end","type":"object Point"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],[{"name":"start","type":"object Point"},{"name":"end","type":"object Point"},{"name":"maxHits","type":"number uint"},{"name":"options","type":"object CollisionQueryOptions","optional":true}]],"returns_contract":{"schema":"CollisionQueryHit","nullable":true,"by_parameter":{"maxHits":{"type":"array","items":{"schema":"CollisionQueryHit"}}}}}
// @pdg-contract {"name":"Scene.raycast","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.sweepCircle","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit","params":[[{"name":"center","type":"object Point"},{"name":"radius","type":"number"},{"name":"delta","type":"object Vector"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],[{"name":"center","type":"object Point"},{"name":"radius","type":"number"},{"name":"delta","type":"object Vector"},{"name":"maxHits","type":"number uint"},{"name":"options","type":"object CollisionQueryOptions","optional":true}]],"returns_contract":{"schema":"CollisionQueryHit","nullable":true,"by_parameter":{"maxHits":{"type":"array","items":{"schema":"CollisionQueryHit"}}}}}
// @pdg-contract {"name":"Scene.sweepCircle","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.overlapPoint","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit[]","params":[{"name":"point","type":"object Point"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],"returns_contract":{"type":"array","items":{"schema":"CollisionQueryHit"}}}
// @pdg-contract {"name":"Scene.overlapPoint","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.overlapCircle","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit[]","params":[{"name":"center","type":"object Point"},{"name":"radius","type":"number"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],"returns_contract":{"type":"array","items":{"schema":"CollisionQueryHit"}}}
// @pdg-contract {"name":"Scene.overlapCircle","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.overlapBox","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit[]","params":[{"name":"box","type":"object RotatedRect"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],"returns_contract":{"type":"array","items":{"schema":"CollisionQueryHit"}}}
// @pdg-contract {"name":"Scene.overlapBox","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.overlapCapsule","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit[]","params":[{"name":"start","type":"object Point"},{"name":"end","type":"object Point"},{"name":"radius","type":"number"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],"returns_contract":{"type":"array","items":{"schema":"CollisionQueryHit"}}}
// @pdg-contract {"name":"Scene.overlapCapsule","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}
// @pdg-member {"name":"Scene.nearestPoint","type":"function","native":false,"brief":"Return scene-owned query results, valid until the next query or disposal.","returns":"object CollisionQueryHit","params":[{"name":"point","type":"object Point"},{"name":"maxDistance","type":"number"},{"name":"options","type":"object CollisionQueryOptions","optional":true}],"returns_contract":{"schema":"CollisionQueryHit","nullable":true}}
// @pdg-contract {"name":"Scene.nearestPoint","value":{"params":{"options":{"schema":"CollisionQueryOptions"}}}}

/* @pdg-schema
{
  "name": "CollisionQueryOptions",
  "value": {
    "kind": "record",
    "fields": {
      "maxHits": {"type":"number uint","optional":true,"default_value":16},
      "layerMask": {
        "type": "number uint",
        "optional": true
      },
      "categoryMask": {
        "type": "number uint",
        "optional": true
      },
      "includeSensors": {
        "type": "boolean",
        "optional": true
      },
      "layers": {
        "items": {
          "type": "object SpriteLayer"
        },
        "optional": true
      },
      "excludedColliders": {
        "items": {
          "type": "object Collider"
        },
        "optional": true
      },
      "excludedBodies": {
        "items": {
          "type": "object PhysicsBody"
        },
        "optional": true
      },
      "predicate": {
        "schema": "CollisionQueryPredicate",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "CollisionQueryPredicate",
  "value": {
    "kind": "callback",
    "params": [
      {
        "name": "collider",
        "type": "object Collider"
      }
    ],
    "returns": {
      "type": "boolean"
    },
    "lifetime": "Synchronous; do not mutate geometry or scene membership, advance scenes, or recursively query."
  }
}
*/

/* @pdg-schema
{
  "name": "CollisionQueryHit",
  "value": {
    "kind": "record",
    "fields": {
      "collider": {
        "type": "object Collider"
      },
      "shapeId": {
        "type": "number uint"
      },
      "point": {
        "type": "object Point"
      },
      "normal": {
        "type": "object Vector"
      },
      "fraction": {
        "type": "number"
      },
      "distance": {
        "type": "number"
      },
      "initialOverlap": {
        "type": "boolean"
      }
    }
  }
}
*/

// Native procedural animation: public records stay portable across V8, JSC and Wasm.
(function() {
    'use strict';
    var jiggleKeys=['frequency','dampingRatio','influence','inertia','maxAngle','length','gravityX','gravityY','maxDistance','maxSpeed','maxAngularSpeed','maxStepSeconds','teleportDistance','teleportAngle','maxSubsteps','enabled','resetOnSeek','resetOnTeleport'];
    var jiggleDefaults=[3,.4,1,.5,Math.PI/3,0,0,0,32,1000,20,1/120,128,Math.PI/2,16,true,true,true];
    bindings.jiggleMode_Chain=0;bindings.jiggleMode_IKTarget=1;
    if(typeof module!=="undefined"&&module.exports){module.exports.jiggleMode_Chain=0;module.exports.jiggleMode_IKTarget=1;}
    function number(v, fallback){if(v===undefined)v=fallback;if(typeof v!=='number'||!isFinite(v))throw new TypeError('Expected finite procedural number');return v;}
    function integer(v, fallback){v=number(v,fallback);if(!Number.isInteger(v)||v<0||v>4294967295)throw new RangeError('Expected procedural ID');return v;}
    function boolean(v,fallback){if(v===undefined)v=fallback;if(typeof v!=='boolean')throw new TypeError('Expected boolean');return v?1:0;}
    function members(owner,chain,part){if(!Array.isArray(chain))throw new TypeError('Expected chain array');return chain.map(function(item){if(part){if(!(item instanceof bindings.Part)||item.getSprite()!==owner.getSprite())throw new TypeError('Expected Part from same Sprite');return item.getId();}var names=owner.getAnimationBoneNames();if(typeof item==='string')item=names.indexOf(item);return integer(item);});}
    var jointKeys=['length','frequency','dampingRatio','inertia','maxAngle','maxAngularSpeed','gravityX','gravityY'];
    function encodeJ(owner,c,part){if(!c||typeof c!=='object')throw new TypeError('Jiggle options required');Object.keys(c).forEach(function(k){if(jiggleKeys.indexOf(k)<0&&['mode','ik','chain','joints'].indexOf(k)<0)throw new TypeError('Unknown jiggle option '+k);});var mode=integer(c.mode);if(mode>1)throw new RangeError('Invalid jiggle mode');var ids=members(owner,c.chain===undefined?[]:c.chain,part);var data=[mode,integer(c.ik,0),ids.length].concat(ids);jiggleKeys.forEach(function(k,i){data.push(i>=15?boolean(c[k],jiggleDefaults[i]):number(c[k],jiggleDefaults[i]));});var joints=c.joints||[];if(!Array.isArray(joints))throw new TypeError("Expected joint overrides array");data.push(joints.length);joints.forEach(function(j){if(part&&j.part!==undefined&&(!(j.part instanceof bindings.Part)||j.part.getSprite()!==owner.getSprite()))throw new TypeError('Override must use a Part from the same Sprite');Object.keys(j).forEach(function(k){if(jointKeys.indexOf(k)<0&&k!=='bone'&&k!=='part')throw new TypeError('Unknown joint setting '+k);});var id=part?(j.part instanceof bindings.Part?j.part.getId():integer(j.bone)):members(owner,[j.bone],false)[0];data.push(id);jointKeys.forEach(function(k){data.push(j[k]===undefined?0:1);if(j[k]!==undefined)data.push(number(j[k]));});});return data;}
    function decodeJ(data){var c={mode:data[0],ik:data[1]},n=data[2];c.chain=data.slice(3,3+n);jiggleKeys.forEach(function(k,i){c[k]=i>=15?!!data[3+n+i]:data[3+n+i];});var at=3+n+jiggleKeys.length,count=data[at++];c.joints=[];for(var i=0;i<count;++i){var j={bone:data[at++]};jointKeys.forEach(function(k){if(data[at++])j[k]=data[at++];});c.joints.push(j);}return c;}
    function encodeF(owner,c,part){if(!c||typeof c!=='object')throw new TypeError('FABRIK options required');Object.keys(c).forEach(function(k){if(['chain','targetX','targetY','space','influence','tolerance','maxIterations','bendDirection'].indexOf(k)<0&&(part||['minimum','maximum'].indexOf(k)<0))throw new TypeError('Unknown FABRIK option '+k);});var ids=members(owner,c.chain,part),lo=c.minimum||[],hi=c.maximum||[];if(!Array.isArray(lo)||!Array.isArray(hi)||lo.length!==hi.length)throw new TypeError('FABRIK limits must be matching arrays');return [number(c.targetX,0),number(c.targetY,0),number(c.influence,1),number(c.tolerance,.01),integer(c.space,part?2:1),integer(c.maxIterations,16),number(c.bendDirection,1),ids.length].concat(ids,[lo.length],lo.map(function(x){return number(x);}),hi.map(function(x){return number(x);}));}
    function fabrikResult(v){return {solveError:v[0],reachError:v[1],iterations:v[2],converged:!!v[3],reached:!!v[4],limited:!!v[5],withinGeometricReach:!!v[6]};}
    function jiggleResult(v){return {lagDistance:v[0],influence:v[1],simulatedSeconds:v[2],desiredTarget:{x:v[3],y:v[4]},filteredTarget:{x:v[5],y:v[6]},effectiveTarget:{x:v[7],y:v[8]},substeps:v[9],limited:!!v[10],reset:!!v[11]};}
    var stateKeys=['angle','velocity','desired','pivotX','pivotY','pivotVelocityX','pivotVelocityY'];
    function decodeState(v){var state={version:1,initialized:!!v[0],x:v[1],y:v[2],velocityX:v[3],velocityY:v[4],joints:[]};for(var i=0;i<v[5];++i){var j={};stateKeys.forEach(function(k,n){j[k]=v[6+i*7+n];});state.joints.push(j);}return state;}
    function stateIdentity(owner,c,part){return {mode:c.mode,chain:(part?[owner.getId()].concat(c.chain):c.chain).slice(),ik:c.ik,rigRevision:part?'0':owner.getAnimationPose().rigRevision};}
    function ownedState(owner,c,v,part){return Object.assign(decodeState(v),stateIdentity(owner,c,part));}
    function checkedState(owner,c,s,part){var identity=stateIdentity(owner,c,part);if(!s||s.mode!==identity.mode||s.ik!==identity.ik||s.rigRevision!==identity.rigRevision||!Array.isArray(s.chain)||s.chain.length!==identity.chain.length||s.chain.some(function(id,i){return id!==identity.chain[i];}))throw new TypeError('Jiggle state topology mismatch');return encodeState(s);}
    function encodeState(s){if(!s||s.version!==1||!Array.isArray(s.joints))throw new TypeError('Unsupported jiggle state');var v=[boolean(s.initialized),number(s.x),number(s.y),number(s.velocityX),number(s.velocityY),s.joints.length];s.joints.forEach(function(j){stateKeys.forEach(function(k){v.push(number(j[k]));});});return v;}
    function patchJ(owner,old,patch,part){if(!patch||typeof patch!=='object')throw new TypeError('Jiggle settings required');Object.keys(patch).forEach(function(k){if(jiggleKeys.indexOf(k)<0&&k!=="joints")throw new TypeError('Unknown or immutable jiggle setting '+k);});var next=Object.assign({},old,patch);if(part)next.chain=next.chain.map(function(id){return owner.getSprite().getPart(id);});return encodeJ(owner,next,part);}
    if(bindings.Sprite&&bindings.Sprite.prototype._procedural){var s=bindings.Sprite.prototype;
        s.addAnimationFABRIK=function(c,order){return this._procedural(1,encodeF(this,c,false).concat(number(order,0)))[0];};
        s.getAnimationFABRIKResult=function(id){return fabrikResult(this._procedural(2,[integer(id)]));};
        s.addAnimationJiggle=function(c,order){return this._procedural(3,encodeJ(this,c,false).concat(number(order,0)))[0];};
        s.getAnimationJiggleOptions=function(id){return decodeJ(this._procedural(4,[integer(id)]));};
        s.setAnimationJiggleSettings=function(id,patch){this._procedural(5,[integer(id)].concat(patchJ(this,this.getAnimationJiggleOptions(id),patch,false)));};
        s.setAnimationJiggleEnabled=function(id,enabled){this._procedural(6,[integer(id),boolean(enabled)]);};
        s.isAnimationJiggleEnabled=function(id){return !!this._procedural(7,[integer(id)])[0];};
        s.setAnimationJiggleInfluence=function(id,influence,seconds){this._procedural(8,[integer(id),number(influence),number(seconds,0)]);};
        s.resetAnimationJiggle=function(id){this._procedural(9,[integer(id)]);};
        s.kickAnimationJiggle=function(id,kick){var c=this.getAnimationJiggleOptions(id),joint=-1,x,y;if(c.mode===0){var bone=kick.joint;if(typeof bone==='string')bone=this.getAnimationBoneNames().indexOf(bone);joint=c.chain.indexOf(integer(bone));if(joint<0)throw new RangeError('Unknown jiggle joint');x=number(kick.angularVelocity);y=0;}else{x=number(kick.velocityX,0);y=number(kick.velocityY,0);}this._procedural(10,[integer(id),x,y,joint]);};
        s.getAnimationJiggleResult=function(id){return jiggleResult(this._procedural(11,[integer(id)]));};
        s.getAnimationJiggleState=function(id){return ownedState(this,this.getAnimationJiggleOptions(id),this._procedural(12,[integer(id)]),false);};
        s.setAnimationJiggleState=function(id,state){this._procedural(13,[integer(id)].concat(checkedState(this,this.getAnimationJiggleOptions(id),state,false)));};
        s.removeAnimationJiggle=function(id){this._procedural(14,[integer(id)]);};
    }
    if(bindings.Part&&bindings.Part.prototype._procedural){var p=bindings.Part.prototype;
        p.solveFABRIK=function(chain,target,options){return fabrikResult(this._procedural(1,encodeF(this,Object.assign({},options,{chain:chain,targetX:target.x,targetY:target.y}),true)));};
        p.setFABRIKTarget=function(chain,target,options){this._procedural(2,encodeF(this,Object.assign({},options,{chain:chain,targetX:target.x,targetY:target.y}),true));return this;};
        p.getFABRIKResult=function(){return fabrikResult(this._procedural(3,[]));};
        p.setJiggle=function(c){this._procedural(4,encodeJ(this,c,true));return this;};
        p.clearJiggle=function(){this._procedural(5,[]);return this;};
        p.hasJiggle=function(){return !!this._procedural(6,[])[0];};
        p.getJiggleOptions=function(){return decodeJ(this._procedural(7,[]));};
        p.setJiggleSettings=function(patch){this._procedural(8,patchJ(this,this.getJiggleOptions(),patch,true));return this;};
        p.setJiggleEnabled=function(enabled){this._procedural(9,[boolean(enabled)]);return this;};
        p.isJiggleEnabled=function(){return !!this._procedural(10,[])[0];};
        p.setJiggleInfluence=function(influence,seconds){this._procedural(11,[number(influence),number(seconds,0)]);return this;};
        p.resetJiggle=function(){this._procedural(12,[]);return this;};
        p.kickJiggle=function(kick){var c=this.getJiggleOptions(),joint=0,x,y;if(c.mode===0){var ids=[this.getId()].concat(c.chain);joint=kick.joint===undefined?0:ids.indexOf(kick.joint.getId());if(joint<0)throw new RangeError('Unknown jiggle joint');x=number(kick.angularVelocity);y=0;}else{x=number(kick.velocityX,0);y=number(kick.velocityY,0);}this._procedural(13,[x,y,joint]);return this;};
        p.getJiggleResult=function(){return jiggleResult(this._procedural(14,[]));};
        p.getJiggleState=function(){return ownedState(this,this.getJiggleOptions(),this._procedural(15,[]),true);};
        p.setJiggleState=function(state){this._procedural(16,checkedState(this,this.getJiggleOptions(),state,true));return this;};
    }
})();

// Procedural animation contracts (consumed by IDL and TypeScript generation).
// @pdg-schema {"name":"AnimationJiggleJointOptions","value":{"kind":"record","fields":{"length":{"type":"number","optional":true},"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"bone":{"one_of":[{"type":"string"},{"type":"number uint"}],"optional":true}}}}
// @pdg-schema {"name":"AnimationJiggleSettings","value":{"kind":"record","fields":{"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"influence":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"length":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"maxDistance":{"type":"number","optional":true},"maxSpeed":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"maxStepSeconds":{"type":"number","optional":true},"teleportDistance":{"type":"number","optional":true},"teleportAngle":{"type":"number","optional":true},"maxSubsteps":{"type":"number","optional":true},"enabled":{"type":"boolean","optional":true},"resetOnSeek":{"type":"boolean","optional":true},"resetOnTeleport":{"type":"boolean","optional":true},"joints":{"items":{"schema":"AnimationJiggleJointOptions"},"optional":true}}}}
// @pdg-schema {"name":"AnimationJiggleOptions","value":{"kind":"record","fields":{"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"influence":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"length":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"maxDistance":{"type":"number","optional":true},"maxSpeed":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"maxStepSeconds":{"type":"number","optional":true},"teleportDistance":{"type":"number","optional":true},"teleportAngle":{"type":"number","optional":true},"maxSubsteps":{"type":"number","optional":true},"enabled":{"type":"boolean","optional":true},"resetOnSeek":{"type":"boolean","optional":true},"resetOnTeleport":{"type":"boolean","optional":true},"joints":{"items":{"schema":"AnimationJiggleJointOptions"},"optional":true},"mode":{"type":"number uint"},"chain":{"items":{"one_of":[{"type":"string"},{"type":"number uint"}]},"optional":true},"ik":{"type":"number uint","optional":true}}}}
// @pdg-schema {"name":"AnimationJiggleKick","value":{"kind":"record","fields":{"angularVelocity":{"type":"number","optional":true},"velocityX":{"type":"number","optional":true},"velocityY":{"type":"number","optional":true},"joint":{"one_of":[{"type":"string"},{"type":"number uint"}],"optional":true}}}}
// @pdg-schema {"name":"AnimationFABRIKOptions","value":{"kind":"record","fields":{"influence":{"type":"number","optional":true},"tolerance":{"type":"number","optional":true},"space":{"type":"number","optional":true},"maxIterations":{"type":"number","optional":true},"bendDirection":{"type":"number","optional":true},"chain":{"items":{"one_of":[{"type":"string"},{"type":"number uint"}]}},"targetX":{"type":"number","optional":true},"targetY":{"type":"number","optional":true},"minimum":{"items":{"type":"number"},"optional":true},"maximum":{"items":{"type":"number"},"optional":true}}}}
// @pdg-schema {"name":"PartJiggleJointOptions","value":{"kind":"record","fields":{"length":{"type":"number","optional":true},"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"bone":{"type":"number uint","optional":true},"part":{"type":"object Part","optional":true}}}}
// @pdg-schema {"name":"PartJiggleSettings","value":{"kind":"record","fields":{"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"influence":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"length":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"maxDistance":{"type":"number","optional":true},"maxSpeed":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"maxStepSeconds":{"type":"number","optional":true},"teleportDistance":{"type":"number","optional":true},"teleportAngle":{"type":"number","optional":true},"maxSubsteps":{"type":"number","optional":true},"enabled":{"type":"boolean","optional":true},"resetOnSeek":{"type":"boolean","optional":true},"resetOnTeleport":{"type":"boolean","optional":true},"joints":{"items":{"schema":"PartJiggleJointOptions"},"optional":true}}}}
// @pdg-schema {"name":"PartJiggleOptions","value":{"kind":"record","fields":{"frequency":{"type":"number","optional":true},"dampingRatio":{"type":"number","optional":true},"influence":{"type":"number","optional":true},"inertia":{"type":"number","optional":true},"maxAngle":{"type":"number","optional":true},"length":{"type":"number","optional":true},"gravityX":{"type":"number","optional":true},"gravityY":{"type":"number","optional":true},"maxDistance":{"type":"number","optional":true},"maxSpeed":{"type":"number","optional":true},"maxAngularSpeed":{"type":"number","optional":true},"maxStepSeconds":{"type":"number","optional":true},"teleportDistance":{"type":"number","optional":true},"teleportAngle":{"type":"number","optional":true},"maxSubsteps":{"type":"number","optional":true},"enabled":{"type":"boolean","optional":true},"resetOnSeek":{"type":"boolean","optional":true},"resetOnTeleport":{"type":"boolean","optional":true},"joints":{"items":{"schema":"PartJiggleJointOptions"},"optional":true},"mode":{"type":"number uint"},"chain":{"items":{"type":"object Part"},"optional":true}}}}
// @pdg-schema {"name":"PartJiggleKick","value":{"kind":"record","fields":{"angularVelocity":{"type":"number","optional":true},"velocityX":{"type":"number","optional":true},"velocityY":{"type":"number","optional":true},"joint":{"type":"object Part","optional":true}}}}
// @pdg-schema {"name":"PartFABRIKOptions","value":{"kind":"record","fields":{"influence":{"type":"number","optional":true},"tolerance":{"type":"number","optional":true},"space":{"type":"number","optional":true},"maxIterations":{"type":"number","optional":true},"bendDirection":{"type":"number","optional":true}}}}
// @pdg-schema {"name":"FABRIKResult","value":{"kind":"record","fields":{"solveError":{"type":"number"},"reachError":{"type":"number"},"iterations":{"type":"number"},"converged":{"type":"boolean"},"reached":{"type":"boolean"},"limited":{"type":"boolean"},"withinGeometricReach":{"type":"boolean"}}}}
// @pdg-schema {"name":"JiggleTarget","value":{"kind":"record","fields":{"x":{"type":"number"},"y":{"type":"number"}}}}
// @pdg-schema {"name":"JiggleResult","value":{"kind":"record","fields":{"lagDistance":{"type":"number"},"influence":{"type":"number"},"simulatedSeconds":{"type":"number"},"substeps":{"type":"number"},"desiredTarget":{"schema":"JiggleTarget"},"filteredTarget":{"schema":"JiggleTarget"},"effectiveTarget":{"schema":"JiggleTarget"},"limited":{"type":"boolean"},"reset":{"type":"boolean"}}}}
// @pdg-schema {"name":"JiggleJointState","value":{"kind":"record","fields":{"angle":{"type":"number"},"velocity":{"type":"number"},"desired":{"type":"number"},"pivotX":{"type":"number"},"pivotY":{"type":"number"},"pivotVelocityX":{"type":"number"},"pivotVelocityY":{"type":"number"}}}}
// @pdg-schema {"name":"JiggleState","value":{"kind":"record","fields":{"version":{"literal":1},"initialized":{"type":"boolean"},"x":{"type":"number"},"y":{"type":"number"},"velocityX":{"type":"number"},"velocityY":{"type":"number"},"joints":{"items":{"schema":"JiggleJointState"}},"mode":{"type":"number uint"},"chain":{"items":{"type":"number uint"}},"ik":{"type":"number uint"},"rigRevision":{"type":"string"}}}}
// @pdg-member {"name":"Sprite.addAnimationFABRIK","type":"function","native":false,"returns":"number uint","params":[{"name":"options","type":"AnimationFABRIKOptions"},{"name":"order","type":"number","optional":true}],"brief":"Register a procedural pose modifier; requires an enabled animation pose."}
// @pdg-member {"name":"Sprite.addAnimationJiggle","type":"function","native":false,"returns":"number uint","params":[{"name":"options","type":"AnimationJiggleOptions"},{"name":"order","type":"number","optional":true}],"brief":"Register a procedural pose modifier; requires an enabled animation pose."}
// @pdg-member {"name":"Sprite.getAnimationFABRIKResult","type":"function","native":false,"returns":"FABRIKResult","params":[{"name":"id","type":"number uint"}],"brief":"Return the latest FABRIK solve diagnostics."}
// @pdg-member {"name":"Sprite.getAnimationJiggleOptions","type":"function","native":false,"returns":"AnimationJiggleOptions","params":[{"name":"id","type":"number uint"}],"brief":"Return an independent configuration record."}
// @pdg-member {"name":"Sprite.setAnimationJiggleSettings","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"},{"name":"settings","type":"AnimationJiggleSettings"}],"brief":"Patch tuning without changing topology."}
// @pdg-member {"name":"Sprite.setAnimationJiggleEnabled","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"},{"name":"enabled","type":"boolean"}],"brief":"Enable or freeze jiggle; reenabling reseeds from the current pose."}
// @pdg-member {"name":"Sprite.isAnimationJiggleEnabled","type":"function","native":false,"returns":"boolean","params":[{"name":"id","type":"number uint"}],"brief":"Return whether jiggle is enabled."}
// @pdg-member {"name":"Sprite.setAnimationJiggleInfluence","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"},{"name":"influence","type":"number"},{"name":"seconds","type":"number","optional":true}],"brief":"Set or linearly fade influence using simulation seconds."}
// @pdg-member {"name":"Sprite.resetAnimationJiggle","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"}],"brief":"Reseed jiggle from the desired pose or target."}
// @pdg-member {"name":"Sprite.kickAnimationJiggle","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"},{"name":"kick","type":"AnimationJiggleKick"}],"brief":"Add angular or target velocity."}
// @pdg-member {"name":"Sprite.getAnimationJiggleResult","type":"function","native":false,"returns":"JiggleResult","params":[{"name":"id","type":"number uint"}],"brief":"Return the most recently evaluated jiggle diagnostics."}
// @pdg-member {"name":"Sprite.getAnimationJiggleState","type":"function","native":false,"returns":"JiggleState","params":[{"name":"id","type":"number uint"}],"brief":"Return an independent numerical state snapshot."}
// @pdg-member {"name":"Sprite.setAnimationJiggleState","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"},{"name":"state","type":"JiggleState"}],"brief":"Restore validated numerical state on the same topology."}
// @pdg-member {"name":"Sprite.removeAnimationJiggle","type":"function","native":false,"returns":"void","params":[{"name":"id","type":"number uint"}],"brief":"Remove a jiggle controller."}
// @pdg-member {"name":"Part.solveFABRIK","type":"function","native":false,"returns":"FABRIKResult","params":[{"name":"chain","type":"object Part[]","contract":{"items":{"type":"object Part"}}},{"name":"target","type":"object Point"},{"name":"options","type":"PartFABRIKOptions","optional":true}],"brief":"Solve or schedule a contiguous independent Part chain; chain excludes the receiver."}
// @pdg-member {"name":"Part.setFABRIKTarget","type":"function","native":false,"returns":"this","params":[{"name":"chain","type":"object Part[]","contract":{"items":{"type":"object Part"}}},{"name":"target","type":"object Point"},{"name":"options","type":"PartFABRIKOptions","optional":true}],"brief":"Solve or schedule a contiguous independent Part chain; chain excludes the receiver."}
// @pdg-member {"name":"Part.getFABRIKResult","type":"function","native":false,"returns":"FABRIKResult","params":[],"brief":"Return the latest scheduled FABRIK diagnostics."}
// @pdg-member {"name":"Part.setJiggle","type":"function","native":false,"returns":"this","params":[{"name":"options","type":"PartJiggleOptions"}],"brief":"Install chain jiggle or decorate an existing Part IK target."}
// @pdg-member {"name":"Part.clearJiggle","type":"function","native":false,"returns":"this","params":[],"brief":"Remove jiggle and restore the underlying programmed rotations."}
// @pdg-member {"name":"Part.hasJiggle","type":"function","native":false,"returns":"boolean","params":[],"brief":"Return whether this Part owns a jiggle controller."}
// @pdg-member {"name":"Part.getJiggleOptions","type":"function","native":false,"returns":"PartJiggleOptions","params":[],"brief":"Return an independent configuration record."}
// @pdg-member {"name":"Part.setJiggleSettings","type":"function","native":false,"returns":"this","params":[{"name":"settings","type":"PartJiggleSettings"}],"brief":"Patch tuning without changing topology."}
// @pdg-member {"name":"Part.setJiggleEnabled","type":"function","native":false,"returns":"this","params":[{"name":"enabled","type":"boolean"}],"brief":"Enable or freeze jiggle; reenabling reseeds from the current pose."}
// @pdg-member {"name":"Part.isJiggleEnabled","type":"function","native":false,"returns":"boolean","params":[],"brief":"Return whether jiggle is enabled."}
// @pdg-member {"name":"Part.setJiggleInfluence","type":"function","native":false,"returns":"this","params":[{"name":"influence","type":"number"},{"name":"seconds","type":"number","optional":true}],"brief":"Set or linearly fade influence using simulation seconds."}
// @pdg-member {"name":"Part.resetJiggle","type":"function","native":false,"returns":"this","params":[],"brief":"Reseed jiggle from the desired pose or target."}
// @pdg-member {"name":"Part.kickJiggle","type":"function","native":false,"returns":"this","params":[{"name":"kick","type":"PartJiggleKick"}],"brief":"Add angular or target velocity."}
// @pdg-member {"name":"Part.getJiggleResult","type":"function","native":false,"returns":"JiggleResult","params":[],"brief":"Return the most recently evaluated jiggle diagnostics."}
// @pdg-member {"name":"Part.getJiggleState","type":"function","native":false,"returns":"JiggleState","params":[],"brief":"Return an independent numerical state snapshot."}
// @pdg-member {"name":"Part.setJiggleState","type":"function","native":false,"returns":"this","params":[{"name":"state","type":"JiggleState"}],"brief":"Restore validated numerical state on the same topology."}

// @pdg-member {"name":"Part.getJiggleError","native_binding":{"method":"getJiggleError","browser":{"generate":true}}}
// @pdg-member {"name":"pdg.jiggleMode_Chain","type":"number int","native":false,"readonly":true}
// @pdg-member {"name":"pdg.jiggleMode_IKTarget","type":"number int","native":false,"readonly":true}
