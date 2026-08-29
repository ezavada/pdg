// -----------------------------------------------
// pdg_emscripten.js
// 
// part of the emscripten bindings
// sets up everything needed for pdg.js to load in
// a fully setup emscripten environment with 
// class and function bindings already created
//
// Written by Ed Zavada, 2015
// Copyright (c) 2015, Dream Rock Studios, LLC
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

var pdgPreviousRuntimeInitialized = Module.onRuntimeInitialized;

Module.onRuntimeInitialized = function() {
    if (pdgPreviousRuntimeInitialized) {
        pdgPreviousRuntimeInitialized();
    }

    // Supply the small amount of Node-like global state expected by the
    // shared JavaScript wrapper when it runs in a browser.
    window.global = window;
    window.process = window.process || { env: {}, versions: {} };
    window.process.env = window.process.env || {};
    window.process.versions = window.process.versions || {};

    // pdg.js expects a module system and the Embind API under pdg_bind.
    window.module = Module;
    window.pdg_bind = Module;
    window.require.cache[window.require.resolve('pdg')] = Module;
    window.require.cache[window.require.resolve('module')] = Module;

    Module._initialize();

    var pdgDefs = window.require('pdg-defs');
    for (var prop in pdgDefs) {
        if (Object.prototype.hasOwnProperty.call(pdgDefs, prop)) {
            Module[prop] = pdgDefs[prop];
        }
    }

    window.require('pdg-wrapper');
    Module.pdgReady = true;
};
