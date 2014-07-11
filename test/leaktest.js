// -----------------------------------------------
// leaktest.js
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

var pdg = require('pdg');

console.log("Leaktest.js\n");

if (typeof(gc) != 'function') {
	console.error("You must run with --expose-gc on the command line to expose V8's garbage collection");
	console.error("You can use --trace-gc option as well to display what the garbage collection is doing");
	process.exit(1);
}

// setup for leak testing

var startMem;
var rss = [];
var heap = [];
var infos = [];
for (var i = 0; i<100; i++) {
	rss[i] = 0;
	heap[i] = 0;
	infos[i] = " xxxx xxxx xxxx xxxx";
}
var memIdx = 0;
function mem(note) {
	gc();
	rss[memIdx] = process.memoryUsage().rss;
	heap[memIdx] = process.memoryUsage().heapUsed;
	infos[memIdx] = note;
	memIdx++;
}
function dumpMem() {
	var rss_last = rss[0];
	var heap_last = heap[0];
	for (var i = 0; i<memIdx; i++) {
		console.log(infos[i] + ".." + (rss[i] - rss_last) + "\t"+(heap[i] - heap_last));
		rss_last = rss[i];
	}
}

var port = pdg.gfx.createWindowPort([400, 400], "Test Window");

// begin the test
gc();
mem("START...............");
var arr1 = [];
var arr2 = [];

function alloc(use_array) {
	var arr = use_array;
	if (typeof arr == "undefined") {
		arr = [];
	}
	for (var i = 0; i<10000; i++) {
		arr[i] = pdg.gfx.getMainPort().getDrawingArea();
//		arr[i] = new pdg.Rect(0, 0, i, i);
	}
}

alloc();
mem("alloc out of scope..");

alloc();
mem("alloc out of scope..");

alloc(arr1);
mem("alloc out of scope..");

// alloc(arr2);
// mem("alloc out of scope..");
// 
mem("END.................");

dumpMem();
