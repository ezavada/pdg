#!/usr/bin/env node

// Test to reproduce the make-idl issue with method signature detection
const pdg = require('pdg');

console.log('=== Testing make-idl Method Signature Detection Issue ===');

function testMethodSignatureDetection(ConstructorClass, instanceObj, className) {
    console.log(`\n--- Testing ${className} ---`);
    
    console.log('Constructor has methods:');
    console.log('  addHandler on constructor:', typeof ConstructorClass.addHandler);
    console.log('  removeHandler on constructor:', typeof ConstructorClass.removeHandler);
    
    console.log('Instance has methods:');
    console.log('  addHandler on instance:', typeof instanceObj.addHandler);
    console.log('  removeHandler on instance:', typeof instanceObj.removeHandler);
    
    console.log('Prototype chain:');
    console.log('  Constructor.prototype === instance.__proto__:', ConstructorClass.prototype === instanceObj.__proto__);
    console.log('  Constructor.prototype === Object.getPrototypeOf(instance):', ConstructorClass.prototype === Object.getPrototypeOf(instanceObj));
    
    // Test what make-idl.js tries to do - call method on constructor with null
    console.log('\nTesting make-idl signature detection (calling constructor methods with null):');
    
    try {
        console.log('  Calling ConstructorClass.addHandler(null)...');
        const sig = ConstructorClass.addHandler(null);
        console.log('  SUCCESS: Got signature:', sig);
    } catch (e) {
        console.log('  ERROR:', e.message);
    }
    
    try {
        console.log('  Calling ConstructorClass.removeHandler(null)...');
        const sig = ConstructorClass.removeHandler(null);
        console.log('  SUCCESS: Got signature:', sig);
    } catch (e) {
        console.log('  ERROR:', e.message);
    }
    
    // Test calling on instance for comparison
    console.log('\nTesting signature detection on instance:');
    
    try {
        console.log('  Calling instance.addHandler(null)...');
        const sig = instanceObj.addHandler(null);
        console.log('  SUCCESS: Got signature:', sig);
    } catch (e) {
        console.log('  ERROR:', e.message);
    }
    
    try {
        console.log('  Calling instance.removeHandler(null)...');
        const sig = instanceObj.removeHandler(null);
        console.log('  SUCCESS: Got signature:', sig);
    } catch (e) {
        console.log('  ERROR:', e.message);
    }
}

// Test TimerManager specifically since that's where we saw the error
testMethodSignatureDetection(pdg.TimerManager, pdg.tm, 'TimerManager');

// Test another manager for comparison
testMethodSignatureDetection(pdg.EventManager, pdg.evt, 'EventManager');

console.log('\n=== Test Complete ===');

// Exit immediately to avoid hanging
setTimeout(() => {
    process.exit(0);
}, 100); 