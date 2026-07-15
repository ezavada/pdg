// Test script to verify sprite streaming order issue
// Tests the FIXME in sprite.cpp line 896 regarding sprite references during serialization

var pdg = require('pdg');

console.log("Testing sprite streaming order issue...");

// Create a sprite layer
var layer = pdg.createSpriteLayer();
console.log("Original layer methods:", Object.getOwnPropertyNames(layer));
console.log("Original layer prototype methods:", Object.getOwnPropertyNames(Object.getPrototypeOf(layer)));

// Create sprites with references to each other
var sprite1 = layer.createSprite();
var sprite2 = layer.createSprite();

console.log("Created sprites:", sprite1, sprite2);

sprite1.id = 1;
sprite2.id = 2;

// Set up references (this would be done through sprite properties in real usage)
sprite1.referencedSpriteId = sprite2.id;
sprite2.referencedSpriteId = sprite1.id;

console.log("Created sprites with cross-references");

// Test serialization with ser_InitialData flag
layer.setSerializationFlags(pdg.ser_InitialData);

var serializer = new pdg.Serializer();
var size = layer.getSerializedSize(serializer);
console.log("Serialized size:", size);

// Check if sprites are being counted in the serialization
console.log("Sprites in original layer before serialization:");
var originalCount = 0;
var originalSprite = layer.getNthSprite(originalCount);
while (originalSprite) {
    console.log("Original sprite", originalCount, ":", originalSprite.id);
    originalCount++;
    originalSprite = layer.getNthSprite(originalCount);
}
console.log("Total original sprites:", originalCount);

try {
    layer.serialize(serializer);
    console.log("Serialization completed successfully");
    
    // Test deserialization
    var buffer = serializer.getDataPtr();
    var deserializer = new pdg.Deserializer();
    deserializer.setDataPtr(buffer);
    
    // Create a new layer for deserialization
    var newLayer = pdg.createSpriteLayer();
    newLayer.setSerializationFlags(pdg.ser_InitialData);
    
    newLayer.deserialize(deserializer);
    console.log("Deserialization completed successfully");
    
    // Check if sprites were properly deserialized
    console.log("Checking deserialized sprites...");
    console.log("Available methods on layer:", Object.getOwnPropertyNames(newLayer));
    console.log("New layer prototype methods:", Object.getOwnPropertyNames(Object.getPrototypeOf(newLayer)));
    
    // Try to get sprites - let's see what methods are available
    var deserializedSprite1 = null;
    var deserializedSprite2 = null;
    
    // Check if there are any sprites at all
    console.log("Checking for sprites in deserialized layer...");
    try {
        var firstSprite = newLayer.getNthSprite(0);
        console.log("First sprite (index 0):", firstSprite);
        
        var secondSprite = newLayer.getNthSprite(1);
        console.log("Second sprite (index 1):", secondSprite);
        
        // Try to iterate through sprites
        var spriteCount = 0;
        var currentSprite = newLayer.getNthSprite(spriteCount);
        while (currentSprite) {
            console.log("Found sprite at index", spriteCount, ":", currentSprite);
            spriteCount++;
            currentSprite = newLayer.getNthSprite(spriteCount);
        }
        console.log("Total sprites found:", spriteCount);
        
        deserializedSprite1 = firstSprite;
        deserializedSprite2 = secondSprite;
    } catch (e) {
        console.log("Error getting sprites:", e.message);
        console.log("Stack:", e.stack);
    }
    
    console.log("deserializedSprite1:", deserializedSprite1);
    console.log("deserializedSprite2:", deserializedSprite2);
    
    if (deserializedSprite1 && deserializedSprite2) {
        console.log("Both sprites deserialized successfully");
        console.log("Sprite 1 ID:", deserializedSprite1.id);
        console.log("Sprite 2 ID:", deserializedSprite2.id);
        
        // This is where the FIXME issue would manifest - if sprite1 references sprite2
        // but sprite2 hasn't been deserialized yet when sprite1 is processed
        if (deserializedSprite1.referencedSpriteId && deserializedSprite2.referencedSpriteId) {
            console.log("Cross-references preserved during deserialization");
        } else {
            console.log("WARNING: Cross-references may not be properly handled");
        }
    } else {
        console.log("ERROR: Sprites were not properly deserialized");
    }
    
    pdg.cleanupLayer(newLayer);
    
} catch (error) {
    console.log("ERROR during serialization/deserialization:", error.message);
}

pdg.cleanupLayer(layer);

console.log("Sprite streaming order test completed");
