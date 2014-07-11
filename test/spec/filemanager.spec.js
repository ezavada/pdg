// -----------------------------------------------
// filemanager.spec.js
//
// test suite for FileManager
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

function getFilesByExtension(path, ext) {
	var files = fs.readdirSync(path);
//	console.log('CHECKING: '+ files);
	var result = [];
	for (var i = 0; i < files.length; i++) {
		if (files[i].substr(-ext.length) == ext) {
			result.push( files[i] );
		}
	}
//	console.log('FOUND: '+ result);
	return result;
}


describe("FileManager", function() {

  it("is a singleton accessed by pdg.fs", function() {
	console.log('* Testing FileManager...');
  	var fs = pdg.fs;
	expect(fs).toBeDefined();
	var fs2 = pdg.getFileManager();
	expect(fs2).toBe(fs);
  });

  it("locates key directories (app, data, resource)", function() {
	expect(pdg.fs.getApplicationDirectory()).toBeDefined();
	expect(pdg.fs.getApplicationDataDirectory()).toBeDefined();
	expect(pdg.fs.getApplicationResourceDirectory()).toBeDefined();
  });

  it("can find files", function() {
	var files = pdg.fs.findFiles('spec/*.js');  // search with method we are testing
	var files2 = getFilesByExtension('spec', '.js');  // search using node built-in stuff
	expect(files2.length).toEqual(files.length); // check that they both find the same thing
	files = pdg.fs.findFiles('spec/net*.spec.js');
	expect(files.length).toEqual(3);
	expect(files[0]).toBe('netclient.spec.js');
	expect(files[1]).toBe('netconnection.spec.js');
	expect(files[2]).toBe('netserver.spec.js');
  });

  it("can find directories", function() {
	var dirs = pdg.fs.findDirs('*');
	expect(dirs.length).toEqual(4);
	expect(dirs[0]).toBe('cxx');
	expect(dirs[1]).toBe('data');
	expect(dirs[2]).toBe('js');
	expect(dirs[3]).toBe('spec');
  });

  it("can search files from absolute path", function() {
	var files = pdg.fs.findFiles('//*');  // FIXME, should be ('/*')
	expect(files.length).toBeGreaterThan(0);
	var dirs = pdg.fs.findDirs('//*');  // FIXME, should be ('/*')
	expect(dirs.length).toBeGreaterThan(0);
  });

  it("can do single character wildcards", function() {
	var dirs = pdg.fs.findDirs('./d?t?');
	expect(dirs.length).toEqual(1);
	expect(dirs[0]).toBe('data');
  });


});
