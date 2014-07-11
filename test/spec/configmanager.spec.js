// -----------------------------------------------
// point.spec.js
//
// test suite for Point
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

describe("ConfigManager", function() {

  it("is a singleton accessed by pdg.cfg", function() {
	console.log('* Testing ConfigManager...');
  	var cfg = pdg.cfg;
	expect(cfg).toBeDefined();
	var cfg2 = pdg.getConfigManager();
	expect(cfg2).toBe(cfg);
  });

  it("can write config data", function() {
	pdg.cfg.useConfig('pdgtestsuite-cfgmgrtest');
	pdg.cfg.setConfigLong('myLong', 81832493);
	pdg.cfg.setConfigFloat('myFloat', -31.3131);
	pdg.cfg.setConfigString('myString', 'test string Value');
	pdg.cfg.setConfigBool('myBool', true);
  });

  it("can read config data", function() {
	pdg.cfg.useConfig('pdgtestsuite-cfgmgrtest');
	var myLong = pdg.cfg.getConfigLong('myLong');
	var myFloat = pdg.cfg.getConfigFloat('myFloat');
	var myString = pdg.cfg.getConfigString('myString');
	var myBool = pdg.cfg.getConfigBool('myBool');
	expect(myLong).toEqual(81832493);
	expect(myFloat).toBeCloseTo(-31.3131);
	expect(myString).toBe('test string Value');
	expect(myBool).toBeTruthy();
  });

  it("can returns undefined for config data that was never set", function() {
	pdg.cfg.useConfig('pdgtestsuite-cfgmgrtest');
	var myLong = pdg.cfg.getConfigLong('myBadLong');
	var myFloat = pdg.cfg.getConfigFloat('myBadFloat');
	var myString = pdg.cfg.getConfigString('myBadString');
	var myBool = pdg.cfg.getConfigBool('myBadBool');
	expect(myLong).toBeUndefined();
	expect(myFloat).toBeUndefined();
	expect(myString).toBeUndefined();
	expect(myBool).toBeUndefined();
  });

});