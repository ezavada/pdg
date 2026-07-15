console.log("Testing constructor returning number...");

// Test 1: Constructor that returns a number
function BadConstructor() {
    return 42;
}

try {
    console.log("About to call pdg.registerSerializableClass with BadConstructor...");
    pdg.registerSerializableClass(BadConstructor);
    console.log("ERROR: Should have thrown an exception!");
} catch (e) {
    console.log("SUCCESS: Caught exception:", e.message);
}

console.log("Test completed.");
