console.log("Testing constructor exception...");

// Test 1: Constructor that throws an exception
function BadConstructor() {
    throw new Error("Constructor failed");
}

try {
    console.log("About to call pdg.registerSerializableClass with BadConstructor...");
    pdg.registerSerializableClass(BadConstructor);
    console.log("ERROR: Should have thrown an exception!");
} catch (e) {
    console.log("SUCCESS: Caught exception:", e.message);
}

console.log("Test completed.");
