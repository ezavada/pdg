console.log("Testing new operator...");

// Test 1: Constructor that returns null
function BadConstructor() {
    return null;
}

try {
    console.log("About to call new BadConstructor()...");
    var result = new BadConstructor();
    console.log("Result:", result);
    console.log("Result type:", typeof result);
    console.log("Result is null:", result === null);
    console.log("Result instanceof BadConstructor:", result instanceof BadConstructor);
} catch (e) {
    console.log("ERROR: Should not have thrown an exception:", e.message);
}

console.log("Test completed.");
