console.log("Testing incomplete object...");

try {
    var IncompleteObject = function() {
        console.log("IncompleteObject constructor called");
        var obj = {
            value: 42,
            getSerializedSize: function() { return 4; },
            serialize: function() { },
            deserialize: function() { }
            // Note: getMyClassTag is intentionally missing
        };
        console.log("IncompleteObject returning:", obj);
        return obj;
    };
    
    console.log("About to call pdg.registerSerializableClass with IncompleteObject...");
    pdg.registerSerializableClass(IncompleteObject);
    console.log("ERROR: Should have thrown an exception!");
} catch (e) {
    console.log("SUCCESS: Caught exception:", e.message);
}

console.log("Test completed.");
