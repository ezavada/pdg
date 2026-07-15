// Minimal test to debug the issue
console.log("Starting minimal test...");

try {
    console.log("About to call registerSerializableClass with a non-function...");
    pdg.registerSerializableClass("not a function");
    console.log("ERROR: Should have thrown!");
} catch (e) {
    console.log("SUCCESS: Caught exception:", e.message);
}

console.log("Test completed.");
