// -----------------------------------------------
// pdg_main.js
//
// override the normal loading of script specified on command line
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// Major portions taken from node.js
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
//
// -----------------------------------------------
// jsminify this file, js2c: jsmin
//
// this file largely duplicates what is in the node.js file for Node.js,
// bootstrapping something that looks like the Node.js core, or at least
// as much of it as we want for PDG on iOS. Once that is done, it initializes
// the PDG engine and runs the app's main.js.


(function(process) {
    this.global = this;

    function startup() {
 
		var EventEmitter = NativeModule.require('events').EventEmitter;

		process.__proto__ = Object.create(EventEmitter.prototype, {
		  constructor: {
			value: process.constructor
		  }
		});
		EventEmitter.call(process);

        // do this good and early, since it handles errors.
        startup.processFatal();

        startup.globalVariables();
        startup.globalTimeouts();
        startup.globalConsole();

        startup.processAssert();
        startup.processConfig();
        startup.processNextTick();
        startup.processStdio();
        startup.processKillAndExit();
        startup.processSignalHandlers();

        startup.processChannel();

        startup.resolveArgv0();

        // There are various modes that Node can run in. We ignore
        // them all and just run PDG
        startup.globalPDG();
        startup.runMainJS();
    }
 
    startup.globalVariables = function() {
        global.process = process;
        global.global = global;
        global.GLOBAL = global;
        global.root = global;
        // we don't use node's Buffer or domains, so they have been removed
        process._exiting = false;
    };

    startup.globalTimeouts = function() {
		global.setTimeout = function() {
		  var t = NativeModule.require('timers');
		  return t.setTimeout.apply(this, arguments);
		};

		global.setInterval = function() {
		  var t = NativeModule.require('timers');
		  return t.setInterval.apply(this, arguments);
		};

		global.clearTimeout = function() {
		  var t = NativeModule.require('timers');
		  return t.clearTimeout.apply(this, arguments);
		};

		global.clearInterval = function() {
		  var t = NativeModule.require('timers');
		  return t.clearInterval.apply(this, arguments);
		};

		global.setImmediate = function() {
		  var t = NativeModule.require('timers');
		  return t.setImmediate.apply(this, arguments);
		};

		global.clearImmediate = function() {
		  var t = NativeModule.require('timers');
		  return t.clearImmediate.apply(this, arguments);
		};
    };

    startup.globalConsole = function() {
        global.__defineGetter__('console', function() {
            return NativeModule.require('console');
        });
    };

    startup._lazyConstants = null;

    startup.lazyConstants = function() {
        if (!startup._lazyConstants) {
            startup._lazyConstants = process.binding('constants');
        }
        return startup._lazyConstants;
    };
 
    startup.processFatal = function() {
        // emit uncaughtException,
        // and exit if there are no listeners.
        process._fatalException = function(er) {
            var caught = false;
            caught = process.emit('uncaughtException', er);
            // if someone handled it, then great.  otherwise, die in C++ land
            // since that means that we'll exit the process, emit the 'exit' event
            if (!caught) {
                try {
                    if (!process._exiting) {
                        process._exiting = true;
                        process.emit('exit', 1);
                    }
                } catch (er) {
                     // nothing to be done about it at this point.
                }
            }
            // if we handled an error, then make sure any ticks get processed
            if (caught) {
                process._needTickCallback();
            }
            return caught;
        };
    };

    var assert;
    startup.processAssert = function() {
        // Note that calls to assert() are pre-processed out by JS2C for the
        // normal build of node. They persist only in the node_g build.
        // Similarly for debug().
        assert = process.assert = function(x, msg) {
            if (!x) throw new Error(msg || 'assertion error');
        };
    };

    startup.processConfig = function() {
        // TODO: create a config object that has build params
    };

    startup.processNextTick = function() {
        // setup a nextTick call that will invoke
        // a JavaScript function the very next time
        // PDG begins execution.
        // For now we will just use setImmediate()
		process.nextTick = global.setImmediate;
    };

//    function evalScript(name) {
//        var Module = NativeModule.require('module');
//        var path = NativeModule.require('path');
//        var cwd = process.cwd();
//
//        var module = new Module(name);
//        module.filename = path.join(cwd, name);
//        module.paths = Module._nodeModulePaths(cwd);
//        var script = process._eval;
//        if (!Module._contextLoad) {
//            var body = script;
//            script = 'global.__filename = ' + JSON.stringify(name) + ';\n' +
//            'global.exports = exports;\n' +
//            'global.module = module;\n' +
//            'global.__dirname = __dirname;\n' +
//            'global.require = require;\n' +
//            'return require("vm").runInThisContext(' +
//            JSON.stringify(body) + ', ' +
//            JSON.stringify(name) + ', true);\n';
//        }
//        var result = module._compile(script, name + '-wrapper');
//        if (process._print_eval) console.log(result);
//    }
//
    startup.processStdio = function() {
    };

    startup.processKillAndExit = function() {
        process.exit = function(code) {
            if (!process._exiting) {
                process._exiting = true;
                process.emit('exit', code || 0);
            }
            process.reallyExit(code || 0);
        };

        process.kill = function(pid, sig) {
            // we aren't going to support kill
            return false;
        };
    };

    startup.processSignalHandlers = function() {
        // we aren't going to worry about signal handlers
    };


    startup.processChannel = function() {
        // we aren't going to support forking processing
        // and channels seem to be entire related to that
    }

    startup.resolveArgv0 = function() {
        // Native startup already captured UIApplicationMain's arguments. Keep
        // them so simulator runs can select suites/specs from the command line.
        if (!process.argv || !process.argv.length) {
            process.argv = [process.execPath];
        } else {
            process.argv[0] = process.execPath;
        }
        process.argc = process.argv.length;
    };

    startup.globalPDG = function() {

        if (!Function.prototype.bind) {
          Function.prototype.bind = function (oThis) {
            if (typeof this !== "function") {
              // closest thing possible to the ECMAScript 5 internal IsCallable function
              throw new TypeError("Function.prototype.bind - what is trying to be bound is not callable");
            }

            var aArgs = Array.prototype.slice.call(arguments, 1), 
                fToBind = this, 
                fNOP = function () {},
                fBound = function () {
                  return fToBind.apply(this instanceof fNOP && oThis
                                         ? this
                                         : oThis,
                                       aArgs.concat(Array.prototype.slice.call(arguments)));
                };

            fNOP.prototype = this.prototype;
            fBound.prototype = new fNOP();
            fBound.name = oThis.name;

            return fBound;
          };
        }
        var pdg = NativeModule.require('pdg');
        global.pdg = pdg;
		pdg._finishedScriptSetup();  // let C++ finish initializing now that JS is all set up
    };

    startup.runMainJS = function() {
		pdg.argv = process.argv;  // save the arguments

 		var resMgr = pdg.getResourceManager();
		var foundMain = false;
		
		var resFile = 0;
		var mainScript;
		var mainFile;

		var path = NativeModule.require('path');
		var fs = NativeModule.require('fs');
		
		// figure out our possible paths for main.js
		// get where binary resides and look there
		var binPath = path.resolve(path.dirname(process.execPath));
		var execName = path.basename(process.argv[0]);
		var defaultResourceFile = binPath + "/" + execName + ".dat";
// 		console.log('binPath: '+binPath);
// 		console.log('execName: '+execName);
// 		console.log('defaultResFile: '+defaultResourceFile);
		if (fs.existsSync(defaultResourceFile)) {
			resFile = resMgr.openResourceFile(defaultResourceFile);
			console.log("Found default resource file "+defaultResourceFile);
		} else if (fs.existsSync(binPath + "/main.dat")) {
			resFile = resMgr.openResourceFile(binPath+"/main.dat");
			console.log("Found resource file "+binPath+"/main.dat");
		}
		if (resMgr.getResourceSize("main.js") > 0) {
			foundMain = true;
			mainScript = resMgr.getResource('main.js');
			mainFile = "(resources):main.js";
		}

		// update current working directory if needed for Mac OS X bundle
		var cwd = process.cwd();
		if (cwd == "" || cwd == "/") {
			// for blank or root cwd, check to see if this is a Mac Bundle
			var bundleSubstr = binPath.substring(binPath.length - 19);
		//	console.log("Checking for Mac Bundle [" + binPath + "] [" + bundleSubstr + "]");
			if (bundleSubstr == ".app/Contents/MacOS") {
				var newPath = path.resolve(binPath, "../../../");
				console.log("Changing Working directory to: " + newPath);
				process.chdir(newPath);
				cwd = process.cwd();
			}
		}

		var paths = new Array();
		if (!foundMain) {
			paths.push(binPath);
			paths.push(binPath+"/js");
			// if it was invoked from somewhere different, maybe a symbolic link, look there too
			var execPath = path.resolve(path.dirname(process.argv[0])); 
			if (execPath != binPath) {
				paths.push(execPath);
				paths.push(execPath+"/js");
			}
			// if one of the above wasn't the working directory, look in working directory too
			if ((execPath != cwd) && (binPath != cwd)) {
				paths.push(cwd);
				paths.push(cwd+"/js");
			}
			console.log(paths);
			for (var i = 0; i < paths.length; i++) {
				var file = paths[i] + "/main.js";
				console.log("checking: "+ file);
				if (fs.existsSync(file)) {
					foundMain = true;
					console.log("Found, will read: "+ file);
					mainScript = fs.readFileSync(file, 'utf8');
					mainFile = file;
					break;
				}
			}
		}

		// if we were able to load a main.js from one of the many places we looked, then
		// go ahead and run it on the next tick.
		if (foundMain) {
			console.log("pdg_main: found main.js: " + mainFile);

			// setup a unix socket for live interactive commands
		// 	connections = 0;
		// 	net.createServer(function (socket) {
		// 	  connections += 1;
		// 	  repl.start({
		// 		prompt: "pdg> ",
		// 		input: socket,
		// 		output: socket,
		// 		terminal: true,
		// 		useGlobal: true
		// 	  }).on('exit', function() {
		// 		socket.end();
		// 	  })
		// 	}).listen("/tmp/pdg-cmd-sock");

//				pdg._loadScript(mainScript, "main.js");

			// run main.js next time we go through the event loop
			process.nextTick(function() {
				pdg._loadScript(mainScript, "main.js");
			});
		} else {
			console.log("Couldn't find script main.js in resources ("+defaultResourceFile+";"
				+ binPath + "/main.dat;" + resMgr.getResourcePaths() + ") or the common paths ("
				+ paths.join(";") + ")\n\n");

			pdg.startRepl();
		}

    };

    // Below you find a minimal module system, which is used to load the node
    // core modules found in lib/*.js. All core modules are compiled into the
    // node binary, so they can be loaded faster.

    var runInThisContext = process._jsc_runInThisContext;

    function NativeModule(id) {
        this.filename = id + '.js';
        this.id = id;
        this.exports = {};
        this.loaded = false;
    }

    NativeModule._source = process.binding('natives');
    NativeModule._cache = {};

    NativeModule.require = function(id) {
        if (id == 'native_module') {
            return NativeModule;
        }

        var cached = NativeModule.getCached(id);
        if (cached) {
            return cached.exports;
        }

        if (!NativeModule.exists(id)) {
            throw new Error('No such native module ' + id);
        }

//        process.moduleLoadList.push('NativeModule ' + id);

        var nativeModule = new NativeModule(id);

        nativeModule.cache();
        nativeModule.compile();

        return nativeModule.exports;
    };

    NativeModule.getCached = function(id) {
        return NativeModule._cache[id];
    }

    NativeModule.exists = function(id) {
        return NativeModule._source.hasOwnProperty(id);
    }

    NativeModule.getSource = function(id) {
        return NativeModule._source[id];
    }

    NativeModule.wrap = function(script) {
        return NativeModule.wrapper[0] + script.trim() + NativeModule.wrapper[1];
    };

    NativeModule.wrapper = [
                         '(function (exports, require, module, __filename, __dirname) { ',
                         '\n});'
                         ];

    NativeModule.prototype.compile = function() {
        var source = NativeModule.getSource(this.id);
        source = NativeModule.wrap(source);

//        process._jsc_write_stdout("about to compile " + this.filename + '\n');
        var fn = runInThisContext(source, this.filename, true);
//        process._jsc_write_stdout("done compiling " + this.filename + '\n\n');
        fn(this.exports, NativeModule.require, this, this.filename);
//        process._jsc_write_stdout("\n\ndone executing " + this.filename + '\n');

        this.loaded = true;
    };

    NativeModule.prototype.cache = function() {
        NativeModule._cache[this.id] = this;
    };

    startup();
});
