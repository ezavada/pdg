// -----------------------------------------------
// resourcemanager.spec.js
//
// test suite for ResourceManager
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

describe("ResourceManager", function() {

  var testRefNum;
  var toolsRefNum;
  
  it("is a singleton accessed by pdg.res", function() {
	console.log('* Testing ResourceManager...');
  	var res = pdg.res;
	expect(res).toBeDefined();
  	var res2 = pdg.getResourceManager();
	expect(res).toBe(res2);
  });

  it("can add folders", function() {
  	testRefNum = pdg.res.openResourceFile('data');
  	toolsRefNum = pdg.res.openResourceFile('tools');
  	var resList = pdg.res.getResourcePaths();
  	expect(testRefNum).not.toEqual(0);
  	expect(toolsRefNum).not.toEqual(0);
  	expect(toolsRefNum).not.toEqual(testRefNum);
  	expect(resList).toContain('/data/');
  	expect(resList).toContain('/tools/');
  });

  it("can removed added folders", function() {
  	pdg.res.closeResourceFile(toolsRefNum);
  	var resList = pdg.res.getResourcePaths();
  	expect(resList).toContain('/data/');
  	expect(resList).not.toContain('/tools/');
  });

  it("can added zip files", function() {
  	pdg.res.openResourceFile('data/test.dat');
  	var resList = pdg.res.getResourcePaths();
  	expect(resList).toContain('/data/test.dat');
  });

  it("can get strings from the various files", function() {
  	var str200 = pdg.res.getString(200);
  	var str500 = pdg.res.getString(500);
  	expect(str200).toContain('Grain|grain.png');
  	expect(str500).toContain('There is no zip version of this string');
  });

  it("can get localized strings from the various files", function() {
  	pdg.res.setLanguage('es');
  	var str200 = pdg.res.getString(200);
  	var str500 = pdg.res.getString(500);
  	var str501 = pdg.res.getString(501);
  	expect(str200).toContain('Granos|grain.png');
  	expect(str500).toContain('No hay versión zip de este mensaje');
  	expect(str501).toContain('There is no Spanish or zip version of this string');
  });

});