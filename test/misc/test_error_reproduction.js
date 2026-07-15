// Test to reproduce the segmentation fault
console.log("Testing error reproduction...");

try {
    // Test 1: Try to register a bad constructor
    console.log("Test 1: Bad constructor");
    var BadConstructor = function() {
        // This constructor throws an error
        throw new Error("Constructor error");
    };
    
    try {
        pdg.registerSerializableClass(BadConstructor);
        console.log("ERROR: Should have thrown an exception!");
    } catch (e) {
        console.log("SUCCESS: Caught expected exception:", e.message);
    }
    
    // Test 2: Try to register a constructor that returns null
    console.log("Test 2: Constructor returns null");
    var NullConstructor = function() {
        return null;
    };
    
    try {
        pdg.registerSerializableClass(NullConstructor);
        console.log("ERROR: Should have thrown an exception!");
    } catch (e) {
        console.log("SUCCESS: Caught expected exception:", e.message);
    }
    
    // Test 3: Try to register a constructor that returns undefined
    console.log("Test 3: Constructor returns undefined");
    var UndefinedConstructor = function() {
        return undefined;
    };
    
    try {
        pdg.registerSerializableClass(UndefinedConstructor);
        console.log("ERROR: Should have thrown an exception!");
    } catch (e) {
        console.log("SUCCESS: Caught expected exception:", e.message);
    }
    
    // Test 4: Try to register a constructor with missing getMyClassTag
    console.log("Test 4: Missing getMyClassTag");
    var MissingTagConstructor = function() {
        var serializable = new pdg.ISerializable(
            function(serializer) { return serializer.sizeof_uint(42); },
            function(serializer) { serializer.serialize_uint(42); },
            function(deserializer) { this.value = deserializer.deserialize_uint(); },
            function() { return 0x12345678; }
        );
        // Don't add getMyClassTag method
        return serializable;
    };
    
    try {
        pdg.registerSerializableClass(MissingTagConstructor);
        console.log("ERROR: Should have thrown an exception!");
    } catch (e) {
        console.log("SUCCESS: Caught expected exception:", e.message);
    }
    
    // Test 5: Try to register a constructor with invalid getMyClassTag
    console.log("Test 5: Invalid getMyClassTag");
    var InvalidTagConstructor = function() {
        var serializable = new pdg.ISerializable(
            function(serializer) { return serializer.sizeof_uint(42); },
            function(serializer) { serializer.serialize_uint(42); },
            function(deserializer) { this.value = deserializer.deserialize_uint(); },
            function() { return 0x12345678; }
        );
        serializable.getMyClassTag = "not a function"; // Not a function
        return serializable;
    };
    
    try {
        pdg.registerSerializableClass(InvalidTagConstructor);
        console.log("ERROR: Should have thrown an exception!");
    } catch (e) {
        console.log("SUCCESS: Caught expected exception:", e.message);
    }
    
    console.log("All tests completed successfully!");
    
} catch (e) {
    console.log("FATAL ERROR:", e.message);
    console.log("Stack:", e.stack);
}

console.log("Test completed.");
