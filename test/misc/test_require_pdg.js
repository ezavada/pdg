// Test script to verify that require('pdg') works
console.log('Testing require("pdg")...');

try {
    var pdg = require('pdg');
    console.log('SUCCESS: require("pdg") worked!');
    console.log('pdg type:', typeof pdg);
    console.log('pdg keys:', Object.keys(pdg).slice(0, 10)); // Show first 10 keys
} catch (error) {
    console.log('ERROR: require("pdg") failed:', error.message);
}

console.log('Test completed.'); 