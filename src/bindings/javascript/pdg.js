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
if (process.env.NODE_DEBUG && /pdg/.test(process.env.NODE_DEBUG)) {
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
    coordinates = pdg_bind;
    color = pdg_bind;
    
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
		setImmediate(bindings.__run);
	} else {
		bindings._quit();
		// Clear the run loop active flag when stopping
		bindings._pdgRunLoopActive = false;
		process.nextTick(process.exit);
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

if (bindings.hasGraphics) {
    fixManagerConstructorAndToString(bindings.gfx, bindings.GraphicsManager, 'GraphicsManager');
}
if (bindings.hasSound) {
    fixManagerConstructorAndToString(bindings.snd, bindings.SoundManager, 'SoundManager');
}

// Now get the prototype references (after fixing, these should be the same objects)
var fileManagerProto = bindings.FileManager.prototype;
var timerManagerProto = bindings.TimerManager.prototype;

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


