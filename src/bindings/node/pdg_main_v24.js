// pdg_main_v24.js
//
// Improved version using Node.js v24's built-in capabilities
// instead of custom _loadScript approach
// Uses standard Node.js require() and vm.runInNewContext() instead of ES modules
//
// AUTO-EXIT FEATURE:
// This version automatically detects when scripts complete execution and exits gracefully
// if no active handles (timers, servers, etc.) are keeping the event loop alive.
// To disable auto-exit: set global._pdgNoAutoExit = true or env var PDG_NO_AUTO_EXIT=1
// For timeout-based exit: set env var PDG_AUTO_EXIT_TIMEOUT=<seconds>
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
_debug_log('[PDG] pdg_main.js: Module loaded');

// Get PDG bindings directly from linked binding system
// In the linked binding context, process.pdg may not be available
let pdg;
try {
    // First try to get from process.pdg (if available)
    pdg = process.pdg;
    if (!pdg) {
        throw new Error('process.pdg not available');
    }
} catch (e) {
    // Fallback: get PDG bindings directly from linked binding
    _debug_log('[PDG] pdg_main.js: process.pdg not available, getting PDG from linked binding...');
    pdg = process._linkedBinding('pdg');
    if (!pdg) {
        throw new Error('[PDG] pdg_main.js: Cannot access PDG bindings!');
    }
}
pdg._debug_log = _debug_log;

// Get original arguments from environment variable (set by C++ code)
// This allows PDG to handle scripts that Node.js would otherwise execute directly
if (process.env.PDG_ORIGINAL_ARGS) {
    pdg.argv = process.env.PDG_ORIGINAL_ARGS.split('\n');
    pdg._debug_log('[PDG] pdg_main.js: Using original args from environment:', pdg.argv.length, 'arguments');
} else {
    pdg.argv = process.argv;  // fallback to process.argv
    pdg._debug_log('[PDG] pdg_main.js: Using process.argv:', pdg.argv.length, 'arguments');
}

// Also set pdg.argv on global.pdg so it's accessible from required modules
if (typeof global !== 'undefined' && global.pdg) {
    global.pdg.argv = pdg.argv;
    pdg._debug_log('[PDG] pdg_main.js: Set global.pdg.argv for required modules');
}

// Load required Node.js modules
const path = require('path');
const fs = require('fs');
const vm = require('node:vm');
const Module = require('module');
const { SourceTextModule } = require('node:vm');

// Set up REPL functionality
pdg.startRepl = function() {
	var _sig = methodSignature("", arguments, "undefined", 0, "()"); if (_sig != null) return _sig;

    console.log("PDG terminal v" + process.versions['pdg']);
    
    const repl = require('repl');
    const opts = {
        useGlobal: true,
        ignoreUndefined: true,
        // Enable proper exit on Ctrl+C
        breakEvalOnSigint: true
    };
    if (parseInt(process.env['NODE_NO_READLINE'], 10)) {
        opts.terminal = false;
    }
    if (parseInt(process.env['NODE_DISABLE_COLORS'], 10)) {
        opts.useColors = false;
    }
    
    // Start the REPL
    const replServer = repl.start(opts);
    global.pdg = pdg;
    
    // Set up proper exit handling
    replServer.on('exit', () => {
        console.log('\n[PDG] REPL exiting...');
        process.exit(0);
    });
    
    // Handle the REPL close event
    replServer.on('close', () => {
        console.log('\n[PDG] REPL closed');
        process.exit(0);
    });
    
    // Add a custom .exit command for clarity
    replServer.defineCommand('exit', {
        help: 'Exit the PDG REPL',
        action() {
            console.log('[PDG] Goodbye!');
            this.close();
        }
    });
    
    // Set up a simple SIGINT handler that works with the REPL
    let sigintCount = 0;
    process.on('SIGINT', () => {
        sigintCount++;
        if (sigintCount === 1) {
            console.log('\n[PDG] (To exit, press Ctrl+C again or use .exit)');
            replServer.displayPrompt();
        } else {
            console.log('\n[PDG] Exiting REPL...');
            process.exit(0);
        }
        
        // Reset counter after 2 seconds
        setTimeout(() => {
            sigintCount = 0;
        }, 2000);
    });
};

// Improved script loading using Node.js v24's VM module
function loadAndRunScript(scriptContent, filename) {
    try {
        // Create a proper process.argv for the script context
        // Include the script filename and any additional arguments
        const scriptArgv = [process.argv[0], filename];
        
        // Add any arguments that come after the script filename
        const scriptIndex = pdg.argv.indexOf(filename);
        if (scriptIndex >= 0 && scriptIndex + 1 < pdg.argv.length) {
            // Script was explicitly passed on command line, include args after it
            scriptArgv.push(...pdg.argv.slice(scriptIndex + 1));
        } else {
            // Script was auto-loaded (e.g., main.js), include all non-executable args
            // that aren't .js files (those are data files/arguments for the app)
            for (let i = 1; i < pdg.argv.length; i++) {
                const arg = pdg.argv[i];
                // Skip .js files as they are scripts, not arguments
                if (!arg.endsWith('.js')) {
                    scriptArgv.push(arg);
                }
            }
        }
        
        // Create a per-file require function that resolves paths relative to the script's location
        // This is essential for relative requires (e.g., require('./mymodule.js')) to work correctly
        const standardRequire = Module.createRequire(path.resolve(filename));
        
        // Create a hybrid require that checks PDG native modules first, then falls back to standard require
        const fileRequire = function(moduleName) {
            // Try PDG native modules first (dump, coordinates, color, etc.)
            try {
                const nativeModule = process._linkedBinding(moduleName);
                if (nativeModule) {
                    return nativeModule;
                }
            } catch (e) {
                // Not a PDG native module, continue to standard require
            }
            
            // Fall back to standard Node.js require for file system and npm modules
            return standardRequire(moduleName);
        };
        
        // Copy over the resolve and cache properties from standard require
        fileRequire.resolve = standardRequire.resolve.bind(standardRequire);
        fileRequire.cache = standardRequire.cache;
        fileRequire.extensions = standardRequire.extensions;
        fileRequire.main = standardRequire.main;
        
        // Create a context with PDG bindings and standard globals
        const context = vm.createContext({
            pdg: pdg,
            console: console,
            process: {
                ...process,
                argv: scriptArgv
            },
            global: global,
            Buffer: Buffer,
            setTimeout: setTimeout,
            setInterval: setInterval,
            clearTimeout: clearTimeout,
            clearInterval: clearInterval,
            setImmediate: setImmediate,
            clearImmediate: clearImmediate,
            require: fileRequire, // Use per-file require for proper relative path resolution
            module: module,
            exports: exports,
            __filename: filename,
            __dirname: path.dirname(filename),
            // Add other globals as needed
        });

        // Run the script in the context
        const result = vm.runInContext(scriptContent, context, {
            filename: filename,
            displayErrors: true
        });
        
        pdg._debug_log(`[PDG] pdg_main.js: Successfully loaded and executed: ${filename}`);
        
        // Schedule automatic exit detection after script execution
        // This prevents hanging when scripts don't call process.exit()
        scheduleAutoExit(filename);
        
        return result;
    } catch (error) {
        console.error(`[PDG] Error loading script ${filename}:`, error);
        throw error;
    }
}

// Function to detect if the script is complete and schedule automatic exit
function scheduleAutoExit(scriptName) {
    // Allow script to opt out of auto-exit by setting a global flag
    if (global._pdgNoAutoExit || process.env.PDG_NO_AUTO_EXIT) {
        pdg._debug_log(`[PDG] pdg_main.js: Auto-exit disabled for ${scriptName}`);
        return;
    }
    
    // Use setImmediate to check after all current synchronous operations complete
    setImmediate(() => {
        // Check again after one more tick to ensure all immediate callbacks are processed
        setImmediate(() => {
            checkAndExit(scriptName);
        });
    });
}

// Check if the event loop has active handles and exit if not
function checkAndExit(scriptName) {
    try {
        // Check if PDG's run loop is active - if so, don't auto-exit
        if (pdg._pdgRunLoopActive) {
            pdg._debug_log(`[PDG] pdg_main.js: PDG run loop is active. Continuing event loop...`);
            return;
        }
        
        // Get the active handles and requests
        const activeHandles = process._getActiveHandles();
        const activeRequests = process._getActiveRequests();
        
        pdg._debug_log(`[PDG] pdg_main.js: Post-execution check for ${scriptName}:`);
        pdg._debug_log(`[PDG] pdg_main.js:   Active handles: ${activeHandles.length}`);
        pdg._debug_log(`[PDG] pdg_main.js:   Active requests: ${activeRequests.length}`);
        
        // Enhanced filter for handles that shouldn't prevent exit
        const userHandles = activeHandles.filter(handle => {
            // Filter out common internal handles that shouldn't prevent exit
            if (!handle || typeof handle !== 'object') return false;
            
            // Check handle constructor name
            const constructorName = handle.constructor ? handle.constructor.name : '';
            
            // Enhanced filtering for Node.js internal handles
            if (constructorName === 'TTYWrap' || constructorName === 'WriteWrap') {
                // These are typically stdin/stdout/stderr handles
                return false;
            }
            
            if (constructorName === 'ProcessWrap') {
                // Process-related internal handles
                return false;
            }
            
            // Enhanced ReadStream filtering for PDG scripts
            if (constructorName === 'ReadStream') {
                // Filter out stdin and other system ReadStreams
                if (handle === process.stdin || handle.fd === 0) {
                    return false;
                }
                // Filter out ReadStreams that look like system streams
                if (handle.path === '/dev/stdin' || handle.path === '/dev/tty') {
                    return false;
                }
                // Filter out ReadStreams without readable state (likely internal)
                if (!handle.readable && !handle.readableEnded) {
                    return false;
                }
                return false; // For PDG scripts, most ReadStreams are internal
            }
            
            if (constructorName === 'WriteStream') {
                // Filter out stdout/stderr WriteStream handles
                if (handle === process.stdout || handle === process.stderr || handle === process.stdin) {
                    return false;
                }
                // Also check for streams that look like standard streams
                if (handle.fd === 1 || handle.fd === 2 || handle.fd === 0) {
                    return false;
                }
            }
            
            if (constructorName === 'PipeWrap') {
                // Filter out stdout/stderr pipe handles
                if (handle._handle && handle._handle.owner === process.stdout) {
                    return false;
                }
                if (handle._handle && handle._handle.owner === process.stderr) {
                    return false;
                }
                // Filter out pipes that don't have active async operations
                if (!handle._handle || !handle._handle.pending) {
                    return false;
                }
            }
            
            // Enhanced filtering for PDG-specific handles
            if (constructorName === 'Socket') {
                // Filter out sockets that are not actively connected or listening
                if (handle.destroyed || handle.readyState === 'closed') {
                    return false;
                }
            }
            
            if (constructorName === 'FSWatcher') {
                // Filter out file system watchers (often internal)
                return false;
            }
            
            // Filter handles associated with the current process
            if (handle.pid && handle.pid === process.pid) {
                return false;
            }
            
            // Filter handles that are clearly internal (have _handle property but no user-facing interface)
            if (handle._handle && !handle.readable && !handle.writable && !handle.listening) {
                return false;
            }
            
            // Keep handles that look like user code (timers, servers, active connections, etc.)
            return true;
        });
        
        const hasUserHandles = userHandles.length > 0;
        const hasActiveRequests = activeRequests.length > 0;
        
        pdg._debug_log(`[PDG] pdg_main.js:   User handles (after enhanced filtering): ${userHandles.length}`);
        
        // Debug: Log handle types if any remain
        if (userHandles.length > 0) {
            pdg._debug_log(`[PDG] pdg_main.js:   Remaining handle types: ${userHandles.map(h => h.constructor ? h.constructor.name : 'unknown').join(', ')}`);
            // Additional debug info for remaining handles
            userHandles.forEach((h, i) => {
                const info = [];
                if (h.fd !== undefined) info.push(`fd:${h.fd}`);
                if (h.readable !== undefined) info.push(`readable:${h.readable}`);
                if (h.writable !== undefined) info.push(`writable:${h.writable}`);
                if (h.listening !== undefined) info.push(`listening:${h.listening}`);
                if (h.destroyed !== undefined) info.push(`destroyed:${h.destroyed}`);
                pdg._debug_log(`[PDG] pdg_main.js:     Handle ${i}: ${h.constructor.name} ${info.join(' ')}`);
            });
        }
        
        if (!hasUserHandles && !hasActiveRequests) {
            pdg._debug_log(`[PDG] pdg_main.js: No user handles or requests detected after ${scriptName} execution.`);
            pdg._debug_log(`[PDG] pdg_main.js: Script appears to be complete. Exiting gracefully...`);
            pdg._debug_log(`[PDG] pdg_main.js: (To disable auto-exit, set global._pdgNoAutoExit = true or PDG_NO_AUTO_EXIT=1)`);
            
            // Use setImmediate to allow any final cleanup
            setImmediate(() => {
                process.exit(0);
            });
        } else {
            pdg._debug_log(`[PDG] pdg_main.js: Active user handles/requests detected. Continuing event loop...`);
            
            // Optional: Set up periodic checks for long-running scripts
            if (process.env.PDG_AUTO_EXIT_TIMEOUT) {
                const timeout = parseInt(process.env.PDG_AUTO_EXIT_TIMEOUT) * 1000;
                pdg._debug_log(`[PDG] pdg_main.js: Setting auto-exit timeout: ${timeout}ms`);
                
                setTimeout(() => {
                    pdg._debug_log(`[PDG] pdg_main.js: Auto-exit timeout reached. Exiting...`);
                    process.exit(0);
                }, timeout);
            }
        }
    } catch (error) {
        pdg._debug_log(`[PDG] pdg_main.js: Error during auto-exit check: ${error.message}`);
        pdg._debug_log(`[PDG] pdg_main.js: Continuing normal execution...`);
    }
}

// Alternative approach using vm.runInContext for simpler scripts
function runScriptInContext(scriptContent, filename) {
    try {
        // Create a context with PDG bindings
        const context = vm.createContext({
            pdg: pdg,
            console: console,
            process: process,
            global: global,
            // Add other necessary globals
        });

        // Run the script in the context
        const result = vm.runInContext(scriptContent, context, {
            filename: filename,
            importModuleDynamically: vm.constants.USE_MAIN_CONTEXT_DEFAULT_LOADER
        });

        pdg._debug_log(`[PDG] pdg_main.js: Successfully executed: ${filename}`);
        return result;
    } catch (error) {
        console.error(`Error executing script ${filename}:`, error);
        throw error;
    }
}

// Resource manager for loading from embedded resources
const resMgr = pdg.getResourceManager();

// Find and load the main script
function findAndLoadMainScript() {
    let foundMain = false;
    let mainScript;
    let mainFile;
    let mainFilename = 'main.js';

    // Check command line arguments for script name
    for (let i = 1; i < pdg.argv.length; i++) {
        if (pdg.argv[i] == 'main.js') {
            break; // artificially added, ignore it
        }
        if (pdg.argv[i].substr(-3) == '.js') {
            pdg._debug_log("[PDG] pdg_main.js: Found script name on command line: " + pdg.argv[i]);
            mainFilename = pdg.argv[i];
            foundMain = true;
            break;
        } else if ((pdg.argv[i] == '-e') && (pdg.argv.length > i + 1)) {
            pdg._debug_log("[PDG] pdg_main.js: Found [-e " + pdg.argv[i + 1] + "] on command line");
            // Handle -e flag for direct evaluation
            const evalCode = pdg.argv[i + 1];
            try {
                console.log('[PDG] Evaluating: ' + evalCode);
                const result = eval(evalCode);
                if (result !== undefined) {
                    console.log(result);
                }
                // For -e evaluation, exit immediately since it's a one-time command
                process.exit(0);
            } catch (error) {
                console.error('Error evaluating expression:', error);
                process.exit(1);
            }
            return; // Exit early for -e evaluation
        } else if (pdg.argv[i] == '--debug-serialization') {
            pdg._debug_log("[PDG] pdg_main.js: Found --debug-serialization flag after -- separator");
            // Enable debug serialization using the existing API
            pdg.setSerializationDebugMode(true);
            console.log("Debug serialization mode enabled via --debug-serialization flag");
        }
    }

    // Load from filesystem if found
    if (foundMain) {
        if (fs.existsSync(mainFilename)) {
            foundMain = true;
            mainScript = fs.readFileSync(mainFilename, 'utf8');
            mainFile = path.resolve(mainFilename);
        } else {
            console.error("Could not find file to execute: " + mainFilename + " (cwd: " + process.cwd() + ")");
            foundMain = false;
            process.exit(1);
        }
    }

    // Check embedded resources
    const binPath = path.resolve(path.dirname(process.execPath));
    const execName = path.basename(process.argv[0]);
    const defaultResourceFile = binPath + "/" + execName + ".dat";
    
    if (fs.existsSync(defaultResourceFile)) {
        resMgr.openResourceFile(defaultResourceFile);
        pdg._debug_log("[PDG] pdg_main.js: Found default resource file " + defaultResourceFile);
    } else if (fs.existsSync(binPath + "/main.dat")) {
        resMgr.openResourceFile(binPath + "/main.dat");
        pdg._debug_log("[PDG] pdg_main.js: Found resource file " + binPath + "/main.dat");
    }

    if (!foundMain) {
        if (resMgr.getResourceSize(mainFilename) > 0) {
            foundMain = true;
            mainScript = resMgr.getResource(mainFilename);
            mainFile = "(resources):" + mainFilename;
        }
    }

    // Update working directory for Mac OS X bundle
    const cwd = process.cwd();
    if (cwd == "" || cwd == "/") {
        const bundleSubstr = binPath.substring(binPath.length - 19);
        if (bundleSubstr == ".app/Contents/MacOS") {
            const newPath = path.resolve(binPath, "../../../");
            pdg._debug_log("[PDG] pdg_main.js: Changing Working directory to: " + newPath);
            process.chdir(newPath);
        }
    }

    // Search common paths
    const paths = [];
    if (!foundMain) {
        paths.push(binPath);
        paths.push(binPath + "/js");
        
        const execPath = path.resolve(path.dirname(process.argv[0]));
        if (execPath != binPath) {
            paths.push(execPath);
            paths.push(execPath + "/js");
        }
        
        if ((execPath != cwd) && (binPath != cwd)) {
            paths.push(cwd);
            paths.push(cwd + "/js");
        }
        
        for (let i = 0; i < paths.length; i++) {
            const file = paths[i] + "/" + mainFilename;
            pdg._debug_log("[PDG] pdg_main.js: checking: " + file);
            if (fs.existsSync(file)) {
                foundMain = true;
                mainScript = fs.readFileSync(file, 'utf8');
                mainFile = file;
                break;
            }
        }
    }

    if (foundMain) {
        pdg._debug_log("[PDG] pdg_main.js: found main file: " + mainFile);
        
        // Use the improved script loading approach
        try {
            loadAndRunScript(mainScript, mainFile);
        } catch (error) {
            console.error("Failed to load main script:", error);
            process.exit(1);
        }
    } else {
        console.log("Couldn't find script " + mainFilename + " in resources (" + defaultResourceFile + ";" +
            binPath + "/main.dat;" + resMgr.getResourcePaths() + ") or the common paths (" +
            paths.join(";") + ")\n\n");
        
        // Disable auto-exit for REPL mode
        global._pdgNoAutoExit = true;
        pdg.startRepl();
    }
}

// Start the application
process.nextTick(() => {
    try {
        findAndLoadMainScript();
    } catch (error) {
        console.error("Failed to start PDG application:", error);
        process.exit(1);
    }
});
