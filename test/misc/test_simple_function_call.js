console.log("Testing simple function call...");

// Test 1: Function that returns null
function BadFunction() {
    return null;
}

try {
    console.log("About to call BadFunction...");
    var result = BadFunction();
    console.log("Result:", result);
    console.log("Result type:", typeof result);
    console.log("Result is null:", result === null);
} catch (e) {
    console.log("ERROR: Should not have thrown an exception:", e.message);
}

console.log("Test completed.");
