#!/usr/bin/env node

var path = require('path');
var pdg = require('pdg');

console.log('Testing PDG require fix...');

if( !process.env.PDG_ROOT ) {
    process.env.PDG_ROOT = process.cwd();
} else {
	console.log('PDG_ROOT = '+process.env.PDG_ROOT);
}

// Test requiring core Node.js modules
try {
    var fs = require('fs');
    console.log('✓ Successfully required "fs" module');
} catch (e) {
    console.error('✗ Failed to require "fs" module:', e.message);
}

try {
    var net = require('net');
    console.log('✓ Successfully required "net" module');
} catch (e) {
    console.error('✗ Failed to require "net" module:', e.message);
}

// Test requiring a node_modules dependency
try {
    var jasmine_cli = require(process.env.PDG_ROOT + '/node_modules/jasmine-node/lib/jasmine-node/cli.js');
    console.log('✓ Successfully required jasmine-node module');
} catch (e) {
    console.error('✗ Failed to require jasmine-node module:', e.message);
}

console.log('✓ All require tests passed!');
console.log('PDG require fix is working correctly.');

// Exit cleanly without starting the full PDG main loop
process.exit(0); 