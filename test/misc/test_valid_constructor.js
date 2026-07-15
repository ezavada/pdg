console.log("Testing valid constructor...");

// Test 1: Valid constructor that creates an object
function ValidConstructor() {
    this.getMyClassTag = function() {
        return 42;
    };
}

try {
    console.log("About to call pdg.registerSerializableClass with ValidConstructor...");
    pdg.registerSerializableClass(ValidConstructor);
    console.log("SUCCESS: Valid constructor registered successfully!");
} catch (e) {
    console.log("ERROR: Should not have thrown an exception:", e.message);
}

console.log("Test completed.");
