// Simple test to debug double precision serialization
console.log("Testing double precision serialization...");

function testDouble(value) {
  console.log("\nTesting value:", value);
  
  var serializer = new pdg.Serializer();
  serializer.serialize_d(value);
  
  var memBlock = serializer.getDataPtr();
  var deserializer = new pdg.Deserializer();
  deserializer.setDataPtr(memBlock);
  
  var deserializedValue = deserializer.deserialize_d();
  console.log("Deserialized value:", deserializedValue);
  console.log("Is NaN?", isNaN(deserializedValue));
  if (!isNaN(deserializedValue)) {
    console.log("Difference:", Math.abs(value - deserializedValue));
  }
  
  return deserializedValue;
}

// Test various values
testDouble(1.5);
testDouble(2.0);
testDouble(3.14159);
testDouble(2.71828182846);
testDouble(1.0);
testDouble(0.0);
testDouble(-1.0);
testDouble(1e-10);
testDouble(1e10);

// Test the exact sequence from the failing test
console.log("\n=== Testing exact sequence from failing test ===");
var serializer = new pdg.Serializer();
serializer.serialize_str("start");
serializer.serialize_uint(42);
serializer.serialize_uint(1000);
serializer.serialize_uint(1000000);
serializer.serialize_str("middle");
serializer.serialize_str("");
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_1(42);
serializer.serialize_2(1000);
serializer.serialize_4(1000000);
serializer.serialize_f(3.14159);
serializer.serialize_d(2.71828182846);
serializer.serialize_str("end");

var memBlock = serializer.getDataPtr();
var deserializer = new pdg.Deserializer();
deserializer.setDataPtr(memBlock);

// Skip to the double value
deserializer.deserialize_str(); // "start"
deserializer.deserialize_uint(); // 42
deserializer.deserialize_uint(); // 1000
deserializer.deserialize_uint(); // 1000000
deserializer.deserialize_str(); // "middle"
deserializer.deserialize_str(); // ""
deserializer.deserialize_bool(); // true
deserializer.deserialize_bool(); // false
deserializer.deserialize_1(); // 42
deserializer.deserialize_2(); // 1000
deserializer.deserialize_4(); // 1000000
deserializer.deserialize_f(); // 3.14159

var doubleValue = deserializer.deserialize_d();
console.log("Double value from sequence:", doubleValue);
console.log("Is NaN?", isNaN(doubleValue));

// Test with boolean compaction specifically
console.log("\n=== Testing boolean compaction effect ===");
serializer = new pdg.Serializer();
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_d(2.71828182846);

memBlock = serializer.getDataPtr();
deserializer = new pdg.Deserializer();
deserializer.setDataPtr(memBlock);

// Skip the booleans
deserializer.deserialize_bool(); // true
deserializer.deserialize_bool(); // false
deserializer.deserialize_bool(); // true
deserializer.deserialize_bool(); // false
deserializer.deserialize_bool(); // true
deserializer.deserialize_bool(); // false
deserializer.deserialize_bool(); // true
deserializer.deserialize_bool(); // false

doubleValue = deserializer.deserialize_d();
console.log("Double value after boolean compaction:", doubleValue);
console.log("Is NaN?", isNaN(doubleValue));

// Test the exact failing sequence
console.log("\n=== Testing exact failing sequence ===");
serializer = new pdg.Serializer();
serializer.serialize_str("start");
serializer.serialize_uint(42);
serializer.serialize_uint(1000);
serializer.serialize_uint(1000000);
serializer.serialize_str("middle");
serializer.serialize_str("");
serializer.serialize_bool(true);
serializer.serialize_bool(false);
serializer.serialize_1(42);
serializer.serialize_2(1000);
serializer.serialize_4(1000000);
serializer.serialize_f(3.14159);
serializer.serialize_d(2.71828182846);
serializer.serialize_str("end");

memBlock = serializer.getDataPtr();
deserializer = new pdg.Deserializer();
deserializer.setDataPtr(memBlock);

// Deserialize everything in order
console.log("Deserializing in order:");
console.log("str:", deserializer.deserialize_str());
console.log("uint:", deserializer.deserialize_uint());
console.log("uint:", deserializer.deserialize_uint());
console.log("uint:", deserializer.deserialize_uint());
console.log("str:", deserializer.deserialize_str());
console.log("str:", deserializer.deserialize_str());
console.log("bool:", deserializer.deserialize_bool());
console.log("bool:", deserializer.deserialize_bool());
console.log("1:", deserializer.deserialize_1());
console.log("2:", deserializer.deserialize_2());
console.log("4:", deserializer.deserialize_4());
console.log("f:", deserializer.deserialize_f());
console.log("d:", deserializer.deserialize_d());
console.log("str:", deserializer.deserialize_str());
