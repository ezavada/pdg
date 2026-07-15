#!/usr/bin/env node

// Test to understand differences between singleton instances and new instances
const pdg = require('pdg');

console.log('=== Singleton vs New Instance Comparison ===');

// Test 1: Basic object identity
console.log('\n--- Object Identity ---');
const newTM = new pdg.TimerManager();
console.log('pdg.tm === new TimerManager():', pdg.tm === newTM);
console.log('pdg.tm constructor:', pdg.tm.constructor.name);
console.log('newTM constructor:', newTM.constructor.name);

// Test 2: Method availability
console.log('\n--- Method Availability ---');
const methods = ['addHandler', 'removeHandler', 'startTimer', 'cancelTimer', 'onTimeout', 'onInterval'];
methods.forEach(method => {
    console.log(`${method}:`);
    console.log(`  pdg.tm.${method}:`, typeof pdg.tm[method]);
    console.log(`  newTM.${method}:`, typeof newTM[method]);
});

// Test 3: Internal state inspection
console.log('\n--- Internal State ---');
console.log('pdg.tm toString():', pdg.tm.toString());
console.log('newTM toString():', newTM.toString());

// Test 4: Try calling methods and see what happens
console.log('\n--- Method Behavior ---');

try {
    console.log('Testing pdg.tm.getMilliseconds():');
    const tmTime = pdg.tm.getMilliseconds();
    console.log('  Success - returned:', tmTime);
} catch (e) {
    console.log('  Error:', e.message);
}

try {
    console.log('Testing newTM.getMilliseconds():');
    const newTime = newTM.getMilliseconds();
    console.log('  Success - returned:', newTime);
} catch (e) {
    console.log('  Error:', e.message);
}

// Test 5: Test timer creation
console.log('\n--- Timer Creation Test ---');

try {
    console.log('Testing pdg.tm.startTimer():');
    pdg.tm.startTimer(12345, 1000, true);
    console.log('  Success - timer started');
    pdg.tm.cancelTimer(12345);
    console.log('  Success - timer cancelled');
} catch (e) {
    console.log('  Error:', e.message);
}

try {
    console.log('Testing newTM.startTimer():');
    newTM.startTimer(12346, 1000, true);
    console.log('  Success - timer started');
    newTM.cancelTimer(12346);
    console.log('  Success - timer cancelled');
} catch (e) {
    console.log('  Error:', e.message);
}

// Test 6: Event handling
console.log('\n--- Event Handling Test ---');

try {
    console.log('Testing pdg.tm event handler addition:');
    const handler = new pdg.IEventHandler(function(evt) {
        console.log('Handler called');
        return true;
    });
    pdg.tm.addHandler(handler, pdg.eventType_Timer);
    console.log('  Success - handler added to pdg.tm');
    pdg.tm.removeHandler(handler, pdg.eventType_Timer);
    console.log('  Success - handler removed from pdg.tm');
} catch (e) {
    console.log('  Error:', e.message);
}

try {
    console.log('Testing newTM event handler addition:');
    const handler2 = new pdg.IEventHandler(function(evt) {
        console.log('Handler called');
        return true;
    });
    newTM.addHandler(handler2, pdg.eventType_Timer);
    console.log('  Success - handler added to newTM');
    newTM.removeHandler(handler2, pdg.eventType_Timer);
    console.log('  Success - handler removed from newTM');
} catch (e) {
    console.log('  Error:', e.message);
}

// Test 7: Check internal properties/state
console.log('\n--- Internal Property Inspection ---');
console.log('pdg.tm own properties:', Object.getOwnPropertyNames(pdg.tm));
console.log('newTM own properties:', Object.getOwnPropertyNames(newTM));

// Test 8: Check if they point to the same underlying C++ object
console.log('\n--- C++ Object Identity ---');
// Try to see if they have the same internal pointer or representation
console.log('pdg.tm === pdg.getTimerManager():', pdg.tm === pdg.getTimerManager());

if (typeof newTM._cppPointer !== 'undefined' && typeof pdg.tm._cppPointer !== 'undefined') {
    console.log('C++ pointer comparison:');
    console.log('  pdg.tm._cppPointer:', pdg.tm._cppPointer);
    console.log('  newTM._cppPointer:', newTM._cppPointer);
    console.log('  Same pointer?:', pdg.tm._cppPointer === newTM._cppPointer);
}

console.log('\n=== Test Complete ==='); 