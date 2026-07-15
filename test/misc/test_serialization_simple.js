// Simple test to isolate the serialization issue
var pdg = require('pdg');

console.log('Testing serialize_1u method...');

// Debug the charCodeAt call
console.log('Debug charCodeAt:');
console.log('  "b".charCodeAt(0):', 'b'.charCodeAt(0));
console.log('  "b".charCodeAt():', 'b'.charCodeAt());
console.log('  "b".charCodeAt(1):', 'b'.charCodeAt(1));

// Test 1: Serialize the 'b' character directly
var ser1 = new pdg.Serializer();
var charCode = 'b'.charCodeAt(0);
console.log('  Using charCode:', charCode);
ser1.serialize_1u(charCode);
var data1 = ser1.getDataPtr();
var raw1 = data1.getData(); // Use getData() instead of toString()
console.log('Test 1 - Serialized "b":');
console.log('  Data size:', data1.getDataSize());
console.log('  Raw data length:', raw1.length);
console.log('  First byte:', raw1.charCodeAt(0));
console.log('  Expected: 98, Got:', raw1.charCodeAt(0));

// Let's examine the raw data more closely
console.log('  Raw data bytes:');
for (var i = 0; i < Math.min(raw1.length, 10); i++) {
    console.log('    [' + i + ']:', raw1.charCodeAt(i), '(', String.fromCharCode(raw1.charCodeAt(i)), ')');
}

// Test 2: Try with a different character
var ser2 = new pdg.Serializer();
ser2.serialize_1u('s'.charCodeAt(0));
var data2 = ser2.getDataPtr();
var raw2 = data2.getData(); // Use getData() instead of toString()
console.log('\nTest 2 - Serialized "s":');
console.log('  Data size:', data2.getDataSize());
console.log('  Raw data length:', raw2.length);
console.log('  First byte:', raw2.charCodeAt(0));
console.log('  Expected: 115, Got:', raw2.charCodeAt(0));

// Test 3: Try with a number directly
var ser3 = new pdg.Serializer();
ser3.serialize_1u(98);
var data3 = ser3.getDataPtr();
var raw3 = data3.getData(); // Use getData() instead of toString()
console.log('\nTest 3 - Serialized 98 directly:');
console.log('  Data size:', data3.getDataSize());
console.log('  Raw data length:', raw3.length);
console.log('  First byte:', raw3.charCodeAt(0));
console.log('  Expected: 98, Got:', raw3.charCodeAt(0));

// Test 4: Serialize a Buffer using the same logic as NetConnection
var testBuffer = new Buffer('test');
var ser4 = new pdg.Serializer();
ser4.serialize_1u('b'.charCodeAt(0));
ser4.serialize_mem(testBuffer.toString('binary'));
var data4 = ser4.getDataPtr();
var raw4 = data4.getData(); // Use getData() instead of toString()
console.log('\nTest 4 - Serialized Buffer:');
console.log('  Data size:', data4.getDataSize());
console.log('  Raw data length:', raw4.length);
console.log('  First byte:', raw4.charCodeAt(0));
console.log('  Expected: 98, Got:', raw4.charCodeAt(0));

// Test 5: Test deserialization
var deser = new pdg.Deserializer();
deser.setDataPtr(data4.getData()); // Use getData() instead of toString()
var dataType = String.fromCharCode(deser.deserialize_1u());
console.log('\nTest 5 - Deserialization:');
console.log('  Data type:', dataType);
console.log('  Expected: b, Got:', dataType); 