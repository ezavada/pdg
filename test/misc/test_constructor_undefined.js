console.log("Testing constructor returning undefined...");

// Test 1: Constructor that returns undefined
function BadConstructor() {
    return undefined;
}

try {
    console.log("About to call pdg.registerSerializableClass with BadConstructor...");
    pdg.registerSerializableClass(BadConstructor);
    console.log("ERROR: Should have thrown an exception!");
} catch (e) {
    console.log("SUCCESS: Caught exception:", e.message);
}

console.log("Test completed.");
