// Test to debug deserialization issue
console.log("Testing deserialization debug...");

try {
    // Create a bad deserializable object
    var BadDeserializableObject = function() {
        var serializable = new pdg.ISerializable(
            function(serializer) {
                return 4;
            },
            function(serializer) {
                serializer.serialize_uint(42);
            },
            function(deserializer) {
                // Intentionally cause an error during deserialization
                throw new Error("Deserialization failed");
            },
            function() {
                return 0xDEADBEEF;
            }
        );
        
        serializable.getMyClassTag = function() {
            return 0xDEADBEEF;
        };
        
        return serializable;
    };
    
    pdg.registerSerializableClass(BadDeserializableObject);
    
    var badObj = new BadDeserializableObject();
    var serializer = new pdg.Serializer();
    
    console.log("About to serialize...");
    serializer.serialize_obj(badObj);
    console.log("Serialization completed");
    
    var deserializer = new pdg.Deserializer();
    deserializer.setDataPtr(serializer.getDataPtr());
    
    console.log("About to deserialize...");
    deserializer.deserialize_obj();
    console.log("Deserialization completed without throwing!");
} catch (e) {
    console.log("Caught exception:", e.message);
}

console.log("Test completed.");
