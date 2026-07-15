// Test script to verify Buffer serialization/deserialization
var pdg = require('pdg');

// Create a test Buffer
var testBuffer = new Buffer('A test of the Buffer sending');

console.log('Original buffer:', testBuffer);
console.log('Original buffer length:', testBuffer.length);
console.log('Original buffer inspect:', testBuffer.inspect());
console.log('Is Buffer:', Buffer.isBuffer(testBuffer));
console.log('Buffer constructor:', testBuffer.constructor.name);

// Test the serialization/deserialization process
var netConnection = new pdg.NetConnection();

// Let's manually test the serialization logic
console.log('\n--- Testing serialization logic ---');
if (typeof testBuffer == 'string') {
    console.log('Message is string');
} else if (typeof testBuffer == 'object') {
    console.log('Message is object');
    if (testBuffer instanceof pdg.ISerializable) {
        console.log('Message is ISerializable');
    } else if (testBuffer instanceof pdg.MemBlock) {
        console.log('Message is MemBlock');
    } else if (Buffer.isBuffer(testBuffer)) {
        console.log('Message is Buffer - this should be the case');
    } else {
        console.log('Message is other object type');
    }
} else {
    console.log('Message is neither string nor object');
}

// Check if toBuffer method is available on MemBlock
console.log('\n--- Checking MemBlock toBuffer method ---');
console.log('pdg.MemBlock.prototype.toBuffer:', typeof pdg.MemBlock.prototype.toBuffer);
console.log('pdg.MemBlock.prototype methods:', Object.getOwnPropertyNames(pdg.MemBlock.prototype));

// Simulate the serialization process
var data = netConnection._serializeMessage(testBuffer);
console.log('Serialized data size:', data.getDataSize());

// Let's examine the raw serialized data
var rawData = data.getData(); // Use getData() instead of toString()
console.log('Raw serialized data length:', rawData.length);
console.log('First few bytes:', rawData.charCodeAt(0), rawData.charCodeAt(1), rawData.charCodeAt(2), rawData.charCodeAt(3), rawData.charCodeAt(4));

// Let's examine what happens in the deserialization process
var ser = new pdg.Deserializer();
ser.setDataPtr(data.getData()); // Use getData() instead of toString()
var dataType = String.fromCharCode(ser.deserialize_1u());
console.log('Data type:', dataType);
console.log('Data type char code:', dataType.charCodeAt(0));

if (dataType == 'b') {
    var tmp = ser.deserialize_mem();
    console.log('Deserialized mem block:', tmp);
    console.log('MemBlock type:', typeof tmp);
    console.log('MemBlock constructor:', tmp.constructor.name);
    console.log('MemBlock methods:', Object.getOwnPropertyNames(tmp));
    console.log('MemBlock prototype methods:', Object.getOwnPropertyNames(Object.getPrototypeOf(tmp)));
    console.log('MemBlock prototype constructor:', Object.getPrototypeOf(tmp).constructor.name);
    
    if (tmp && typeof tmp.toBuffer === 'function') {
        var message = tmp.toBuffer();
        console.log('toBuffer result:', message);
    } else {
        console.log('toBuffer method not found!');
        // Try alternative approach
        if (tmp && typeof tmp.getData === 'function') {
            var memData = tmp.getData();
            console.log('MemBlock data:', memData);
            console.log('MemBlock data type:', typeof memData);
            if (typeof memData === 'string') {
                var message = new Buffer(memData, 'binary');
                console.log('Created buffer from string:', message);
            }
        }
    }
}

// Simulate the deserialization process
var deserializedMessage = netConnection._deserializeMessage(data);
console.log('Deserialized message:', deserializedMessage);
console.log('Deserialized message type:', typeof deserializedMessage);
console.log('Is Buffer:', Buffer.isBuffer(deserializedMessage));
if (deserializedMessage) {
    console.log('Deserialized buffer length:', deserializedMessage.length);
    console.log('Deserialized buffer inspect:', deserializedMessage.inspect());
    console.log('Buffers are equal:', testBuffer.equals(deserializedMessage));
} 