// Simple test to debug serialization issues
console.log("Testing simple serialization...");

try {
    // Create a simple serializable object
    var TestClass = function() {
        var serializable = new pdg.ISerializable(
            function(serializer) {
                return serializer.sizeof_uint(42);
            },
            function(serializer) {
                serializer.serialize_uint(42);
            },
            function(deserializer) {
                this.value = deserializer.deserialize_uint();
            },
            function() {
                return 0x12345678;
            }
        );
        
        serializable.getMyClassTag = function() {
            return 0x12345678;
        };
        
        return serializable;
    };
    
    console.log("About to register class...");
    pdg.registerSerializableClass(TestClass);
    console.log("Class registered successfully!");
    
    var testObj = new TestClass();
    console.log("Object created successfully!");
    
    var serializer = new pdg.Serializer();
    console.log("About to serialize object...");
    serializer.serialize_obj(testObj);
    console.log("Object serialized successfully!");
    
} catch (e) {
    console.log("Caught exception:", e.message);
    console.log("Stack:", e.stack);
}

console.log("Test completed.");
