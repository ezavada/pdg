// Simple test for SpriterPlusPlus XML parsing
// This tests the basic functionality without requiring a full test framework

var pdg = require('pdg');

console.log("Testing SpriterPlusPlus XML parsing...");

// Create a port and sprite layer
var port = new pdg.Port(800, 600);
var spriteLayer = new pdg.SpriteLayer(port);

// Test 1: Try to load a SCML file
console.log("Test 1: Loading SCML file...");
var scmlPath = process.cwd() + "/deps/SpriterPlusPlus/Release/GreyGuy/player.scml";

try {
    var sprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
    if (sprite) {
        console.log("✓ Successfully loaded SCML file and created sprite");
        console.log("  Sprite type:", typeof sprite);
    } else {
        console.log("✗ Failed to create sprite from SCML file");
    }
} catch (error) {
    console.log("✗ Exception while loading SCML file:", error.message);
}

// Test 2: Try to load a non-existent file
console.log("\nTest 2: Loading non-existent file...");
try {
    var sprite2 = spriteLayer.createSpriteFromSpriterFile("nonexistent.scml");
    if (sprite2 === null) {
        console.log("✓ Correctly returned null for non-existent file");
    } else {
        console.log("✗ Should have returned null for non-existent file");
    }
} catch (error) {
    console.log("✗ Exception while loading non-existent file:", error.message);
}

// Test 3: Try to load a malformed XML file
console.log("\nTest 3: Loading malformed XML file...");
var fs = require('fs');
var tempFile = process.cwd() + "/test/misc/malformed.scml";
fs.writeFileSync(tempFile, "<invalid>xml</invalid>");

try {
    var sprite3 = spriteLayer.createSpriteFromSpriterFile(tempFile);
    if (sprite3 === null) {
        console.log("✓ Correctly returned null for malformed XML file");
    } else {
        console.log("✗ Should have returned null for malformed XML file");
    }
} catch (error) {
    console.log("✗ Exception while loading malformed XML file:", error.message);
}

// Clean up
fs.unlinkSync(tempFile);

// Test 4: Create multiple sprites from the same file
console.log("\nTest 4: Creating multiple sprites...");
try {
    var sprite4a = spriteLayer.createSpriteFromSpriterFile(scmlPath);
    var sprite4b = spriteLayer.createSpriteFromSpriterFile(scmlPath);
    
    if (sprite4a && sprite4b && sprite4a !== sprite4b) {
        console.log("✓ Successfully created multiple unique sprites");
    } else {
        console.log("✗ Failed to create multiple unique sprites");
    }
} catch (error) {
    console.log("✗ Exception while creating multiple sprites:", error.message);
}

console.log("\nSpriterPlusPlus XML parsing test completed.");

// Close the port
port.close();
