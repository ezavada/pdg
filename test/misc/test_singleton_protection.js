#!/usr/bin/env node

// Test singleton protection for TimerManager
var pdg = require('pdg');

console.log("Testing TimerManager singleton protection...");

// Test 1: Verify the singleton instance works normally
console.log("1. Testing normal singleton access...");
try {
    var tm = pdg.tm;
    console.log("✓ pdg.tm accessible:", typeof tm);
    console.log("✓ tm.getMilliseconds():", tm.getMilliseconds());
    console.log("✓ Singleton access works!");
} catch (e) {
    console.log("✗ Singleton access failed:", e.message);
}

// Test 2: Try to instantiate TimerManager with new (should fail)
console.log("\n2. Testing new TimerManager() protection...");
try {
    var newTm = new pdg.TimerManager();
    console.log("✗ ERROR: new TimerManager() should have failed but succeeded!");
} catch (e) {
    console.log("✓ Successfully blocked new TimerManager():", e.message);
}

// Test 3: Test that instanceof still works correctly
console.log("\n3. Testing instanceof checks...");
try {
    var tm = pdg.tm;
    console.log("✓ pdg.tm instanceof pdg.TimerManager:", tm instanceof pdg.TimerManager);
    console.log("✓ pdg.tm.constructor === pdg.TimerManager:", tm.constructor === pdg.TimerManager);
} catch (e) {
    console.log("✗ instanceof checks failed:", e.message);
}

// Test 4: Test other managers still work normally (they don't have protection yet)
console.log("\n4. Testing other managers still work...");
try {
    var cfg = new pdg.ConfigManager();
    console.log("✓ new ConfigManager() still works (no protection yet)");
} catch (e) {
    console.log("✗ ConfigManager failed:", e.message);
}

console.log("\nAll tests completed!"); 