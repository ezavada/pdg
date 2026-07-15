// Test script for debug serialization flag
console.log("Testing debug serialization...");

// Test WITHOUT debug mode first
console.log("=== Testing WITHOUT debug mode ===");
const serializer1 = new pdg.Serializer();
serializer1.serialize_4u(12345);
serializer1.serialize_2u(6789);
serializer1.serialize_1u(255);
console.log("Serialization without debug mode completed.");

// Now test WITH debug mode
console.log("\n=== Testing WITH debug mode ===");
pdg.setSerializationDebugMode(true);
console.log("Debug serialization mode enabled via setSerializationDebugMode(true)");

const serializer2 = new pdg.Serializer();
serializer2.serialize_4u(12345);
serializer2.serialize_2u(6789);
serializer2.serialize_1u(255);

console.log("Serialization test completed. Check output above for debug messages.");
