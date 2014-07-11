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

var path = require('path');
var pdg = require('pdg');

if( !process.env.NODE_ENV ) process.env.NODE_ENV = 'test';

if( !process.env.PDG_ROOT ) {
	console.error('PDG_ROOT is not defined in the environment variables. Define it and try again.');
	process.exit(1);
} else {
	console.log('PDG_ROOT = '+process.env.PDG_ROOT);
}

var target = './spec';

var debug = false;
var help = false;

for (var i = 1; i<process.argv.length; i++) {
	if (process.argv[i] == '--debug') {
		debug = true;
	} else if (process.argv[i] == '--help') {
		help = true;
	} else if (process.argv[i] == '-h') {
		help = true;
	} else if (process.argv[i] == '/?') {
		help = true;
	} else if (process.argv[i].match(/^spec/)) {
		target = process.argv[i];
		console.log('Test Target: '+target); 
	}
}

if (help) {
	if (process.platform == 'win32') {
		console.log('Usage: test\\client [--debug] [testfile]\n');
	} else {
		console.log('Usage: test/client [--debug] [testfile]\n');
	}
	console.log('Runs tests against the pdg client app\n');
	console.log('Options:');
	console.log('  -h, /?        this help message');
	console.log('  --debug       launch the debugger');
	if (process.platform == 'win32') {
		console.log('  [testfile]    must be spec\\{filename}.spec.js - single test to run');
	} else {
		console.log('  [testfile]    must be spec/{filename}.spec.js - single test to run');
	}
	process.exit(0);
}

process.argv[2] = "--verbose";
process.argv[3] = "--forceexit";
process.argv[4] = target;

var delay;
if (debug) {
	pdg.openDebugger();
	delay = 10000;
} else {
	delay = 1;
}

pdg.tm.onTimeout(function() {
	try {
		require(process.env.PDG_ROOT+'/node_modules/jasmine-node/lib/jasmine-node/cli.js');
	} catch(e) {
		console.error(e);
	}
}, delay);
pdg.run();
