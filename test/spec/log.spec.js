// -----------------------------------------------
// log.spec.js
//
// test suite for LogManager
//
// Written by Ed Zavada, 2014
// Copyright (c) 2014, Dream Rock Studios, LLC
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

var fs = require('fs');
var exec = require('child_process').exec;

function getLogFiles() {
	var files = fs.readdirSync('.');
//	console.log('CHECKING: '+ files);
	var result = [];
	for (var i = 0; i < files.length; i++) {
		if (files[i].substr(-4) == '.log') {
			result.push( files[i] );
		}
	}
//	console.log('FOUND: '+ result);
	return result;
}

function countLogFileLines(filename) {
	var count = 0;
	fs.readFileSync(filename).toString().split(/\r?\n/).forEach(function(line) {
  		count++;
	});
	return (count - 1);
}

function deleteLogFile(filename) {
  	pdg.lm.setLogLevel(-1);
	fs.unlinkSync(filename);
}

function cleanUp() {
	var logs = getLogFiles();
	for (var i = 0; i < logs.length; i++) {
		deleteLogFile(logs[i]);
	}
}

function writeAllLogMessageTypes() {
	pdg.fatal("test fatal message");
	pdg.error("test error message");
	pdg.warn("test warn message");
	pdg.log("test log message");
	pdg.info("test info message");
	pdg.debug("test debug message");
	pdg.trace("test trace message");
}

cleanUp();

describe("LogManager", function() {

  it("is a singleton accessed by pdg.lm", function() {
	console.log('* Testing LogManager...');
  	var lm = pdg.lm;
	expect(lm).toBeDefined();
	var lm2 = pdg.getLogManager();
	expect(lm2).toBe(lm);
  });

  it("supports log levels", function() {
  	var level = pdg.lm.getLogLevel();
	expect(level).toEqual(-1);
	pdg.lm.setLogLevel(10);
	level = pdg.lm.getLogLevel();
	expect(level).toEqual(10);	
  });

  it("write to stdout", function() {
	pdg.lm.initialize("pdg_test", pdg.lm.init_StdOut);
	writeAllLogMessageTypes();
	var logs = getLogFiles();
	expect(logs.length).toEqual(0);
  });

  it("write to stderr", function() {
	pdg.lm.initialize("pdg_test", pdg.lm.init_StdErr);
	writeAllLogMessageTypes();
	var logs = getLogFiles();
	expect(logs.length).toEqual(0);
  });

  it("write to a new file", function() {
	pdg.lm.initialize("pdg_test", pdg.lm.init_OverwriteExisting);
	var logs = getLogFiles();
	expect(logs.length).toEqual(1);
	expect(logs[0]).toBe('pdg_test.log');
	var lc = countLogFileLines(logs[0]);
	expect(lc).toEqual(2);
	writeAllLogMessageTypes();
	var lc2 = countLogFileLines(logs[0]);
	expect(lc2).toEqual(lc+7);
  });

  it("write to an existing file", function() {
	pdg.lm.initialize("pdg_test", pdg.lm.init_AppendToExisting);
	var logs = getLogFiles();
	expect(logs.length).toEqual(1);
	expect(logs[0]).toBe('pdg_test.log');
	var lc = countLogFileLines(logs[0]);
	expect(lc).toEqual(11);
	writeAllLogMessageTypes();
	var lc2 = countLogFileLines(logs[0]);
	expect(lc2).toEqual(lc+7);
  });

  it("write to an unique file", function() {
	pdg.lm.initialize("pdg_test", pdg.lm.init_CreateUniqueNewFile);
	pdg.lm.initialize("pdg_test", pdg.lm.init_CreateUniqueNewFile); // this should produce 2 new log files
	var logs = getLogFiles();
	expect(logs.length).toEqual(3);
	expect(logs[0]).toBe('pdg_test.log');
	expect(logs[2].substr(0, 9)).toBe('pdg_test_');
	expect(logs[1].substr(0, 20)).toBe(logs[2].substr(0,20));
	expect(logs[2].substr(-4)).toBe('.log');
	var lc = countLogFileLines(logs[2]);
	expect(lc).toEqual(2);
	writeAllLogMessageTypes();
	var lc2 = countLogFileLines(logs[2]);
	expect(lc2).toEqual(lc+7);
  });

  it("only writes line that at or above the priority level", function() {
    cleanUp();
	pdg.lm.initialize("pdg_test", pdg.lm.init_AppendToExisting);
  	pdg.lm.setLogLevel(0);
  	pdg.lm.setLogLevel(-1);
	var logs = getLogFiles();
	var file = logs[0];
	expect(logs.length).toEqual(1);
	for (var i = 0; i < 11; i++) {
  		var lc = countLogFileLines(file);
  		pdg.lm.writeLogEntry(i, 'TEST', "this shouldn't be written at level "+(i-1));
  		var unchanged = countLogFileLines(file);
  		expect(lc).toEqual(unchanged);
  		pdg.lm.setLogLevel(i);
  		lc = countLogFileLines(file);
  		pdg.lm.writeLogEntry(i, 'TEST', "this should be written at level "+i);
  		var lc2 = countLogFileLines(file);
  		expect(lc2).toEqual(lc+1);
	}
  });

  it("ignores levels > 10", function() {
  	pdg.lm.setLogLevel(100);
	var level = pdg.lm.getLogLevel();
  	expect(level).toEqual(10);
	var logs = getLogFiles();
	var file = logs[0];
	expect(logs.length).toEqual(1);
  	var lc = countLogFileLines(file);
  	pdg.lm.writeLogEntry(12, 'TEST', "this shouldn't be written at any level ever");
  	var lc2 = countLogFileLines(file);
  	expect(lc).toEqual(lc2);
    cleanUp();
  });


});
