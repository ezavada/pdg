console.log("Testing serialization load...");

try {
    console.log("Checking if pdg.registerSerializableClass exists...");
    console.log("Type:", typeof pdg.registerSerializableClass);
    console.log("Is function:", typeof pdg.registerSerializableClass === 'function');
    
    if (typeof pdg.registerSerializableClass === 'function') {
        console.log("SUCCESS: pdg.registerSerializableClass is available");
    } else {
        console.log("ERROR: pdg.registerSerializableClass is not a function");
    }
} catch (e) {
    console.log("ERROR: Exception occurred:", e.message);
}

console.log("Test completed.");
