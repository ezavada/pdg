// -----------------------------------------------
// child_process.js
//
// Modified version of Node.js' child_process module for use with JavaScriptCore
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
//
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

var EventEmitter = require('events').EventEmitter;
var util = require('util');

exports.fork = function(modulePath /*, args, options*/) {
};


exports.exec = function(command /*, options, callback */) {
};


exports.execFile = function(file /* args, options, callback */) {
};


exports.spawn = function(file, args, options) {
  var child = new ChildProcess();
  return child;
};


function ChildProcess() {
}
util.inherits(ChildProcess, EventEmitter);


ChildProcess.prototype.spawn = function(options) {
};

ChildProcess.prototype.kill = function(sig) {
};

