#!/usr/bin/env pdg
const assert = require('node:assert/strict');
const path = require('node:path');
const pdg = require('pdg');
var entryLocal = 42;
assert.equal(globalThis.entryLocal, undefined);
assert.equal(process, require('node:process'));
assert.equal(require.main, module);
assert.equal(module, process.mainModule);
assert.equal(module.filename, __filename);
assert.equal(__dirname, path.dirname(__filename));
assert.equal(path.resolve(process.argv[1]), __filename);
assert.equal(require.resolve('./entry-module.js'), __filename);
exports.marker = entryLocal;
assert.equal(require('./entry-module.js').marker, 42);
assert.equal(global.pdg.Animated, pdg.Animated);
setImmediate(function() {
    assert.equal(require('node:process').argv[1], process.argv[1]);
    console.log('PASS: CommonJS entry scope, identity, cache, arguments and async globals');
    pdg.quit();
});
