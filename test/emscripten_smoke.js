'use strict';

const assert = require('node:assert/strict');

// Exercise the browser initialization path while Node provides a deterministic
// command-line WebAssembly host for CI and local builds.
global.window = global;
global.document = {};

const pdg = require('../libpdg.js');
const deadline = Date.now() + 5000;

const timer = setInterval(() => {
    if (!pdg.pdgReady) {
        if (Date.now() > deadline) {
            clearInterval(timer);
            throw new Error('PDG WebAssembly initialization timed out');
        }
        return;
    }

    clearInterval(timer);
    assert.equal(global.pdg, pdg);
    assert.equal(typeof pdg.rand, 'function');
    assert.equal(typeof pdg.getEventManager, 'function');
    assert.equal(typeof pdg.getTimerManager, 'function');
    assert.ok(pdg.evt);
    assert.ok(pdg.tm);
    assert.equal(pdg.hasGraphics, false);
    assert.equal(pdg.hasSound, false);
    assert.equal(typeof pdg.rand(), 'number');
    assert.equal(pdg._isQuitting(), false);
    pdg.idle();

    console.log('PDG Emscripten smoke test passed');
}, 10);
