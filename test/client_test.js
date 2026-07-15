// -----------------------------------------------
// client_test/main.js
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
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

var pdg = require('pdg');
var fs = require('fs');
var specRunner = require('./lib/spec_runner');

if( !process.env.NODE_ENV ) process.env.NODE_ENV = 'test';

if( !process.env.PDG_ROOT && process.ios ) {
    console.log('Defining PDG_ROOT for iOS');
    process.env.PDG_ROOT = process.cwd();
    process.env.PDG_DEBUG = "VERBOSE";
}

var envInfo = specRunner.ensureTestEnvironment(process, fs);
var runConfig = specRunner.parseRunnerArgs(process.argv, envInfo.specDir, fs);

console.log('PDG_ROOT = ' + envInfo.repoRoot);
console.log('PDG_TEST_ARTIFACTS_DIR = ' + envInfo.artifactsDir);

if (runConfig.help) {
	specRunner.printClientHelp(process.platform);
	process.exit(0);
}

var delay;
if (runConfig.debug) {
	pdg.openDebugger();
	delay = 10000;
} else {
	delay = 1;
}

pdg.tm.onTimeout(function() {
	try {
		console.log('Running jasmine-node on:', envInfo.specDir);
		if (runConfig.requestedTarget) {
			console.log('Target spec:', runConfig.requestedTarget);
		}
		specRunner.runJasmineSpecs(envInfo, runConfig, process);
	} catch(e) {
		console.error('Error running jasmine-node:', e);
		process.exit(1);
	}
}, delay);
pdg.run();
