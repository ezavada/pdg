// Test to verify that SpriteLayer constructor protection is working
console.log("Testing SpriteLayer constructor protection...");

// Load pdg module for node.js testing
var pdg;
try {
    pdg = require('pdg');
} catch (e) {
    // If require fails, assume we're in the embedded environment where pdg is global
    pdg = global.pdg;
}

// Test 1: Factory function should work
console.log("\n=== Test 1: Factory function should work ===");
try {
    var layer1 = pdg.createSpriteLayer();
    if (layer1 && typeof layer1 === 'object') {
        console.log("✓ pdg.createSpriteLayer() works correctly");
        console.log("  - Type:", typeof layer1);
        console.log("  - Constructor:", layer1.constructor.name);
        console.log("  - Instanceof SpriteLayer:", layer1 instanceof pdg.SpriteLayer);
    } else {
        console.log("✗ pdg.createSpriteLayer() returned invalid object");
    }
} catch (e) {
    console.log("✗ pdg.createSpriteLayer() failed:", e.message);
}

// Test 2: new SpriteLayer() should be blocked
console.log("\n=== Test 2: new SpriteLayer() should be blocked ===");
try {
    var layer2 = new pdg.SpriteLayer();
    console.log("✗ ERROR: new pdg.SpriteLayer() should have been blocked!");
    console.log("  - Returned:", layer2);
} catch (e) {
    if (e.message.includes("cannot be instantiated with 'new'") && 
        e.message.includes("Use the factory function: pdg.createSpriteLayer()")) {
        console.log("✓ new pdg.SpriteLayer() correctly blocked");
        console.log("  - Error message:", e.message);
    } else {
        console.log("✗ Unexpected error for new pdg.SpriteLayer():", e.message);
    }
}

// Test 3: Factory function with port should work
console.log("\n=== Test 3: Factory function with port should work ===");
try {
    var port = pdg.gfx.getMainPort();
    var layer3 = pdg.createSpriteLayer(port);
    if (layer3 && typeof layer3 === 'object') {
        console.log("✓ pdg.createSpriteLayer(port) works correctly");
        console.log("  - Type:", typeof layer3);
        console.log("  - Constructor:", layer3.constructor.name);
        console.log("  - Instanceof SpriteLayer:", layer3 instanceof pdg.SpriteLayer);
    } else {
        console.log("✗ pdg.createSpriteLayer(port) returned invalid object");
    }
} catch (e) {
    console.log("✗ pdg.createSpriteLayer(port) failed:", e.message);
}

// Test 4: Verify instanceof still works
console.log("\n=== Test 4: Verify instanceof still works ===");
try {
    var layer4 = pdg.createSpriteLayer();
    if (layer4 instanceof pdg.SpriteLayer) {
        console.log("✓ instanceof pdg.SpriteLayer works correctly");
    } else {
        console.log("✗ instanceof pdg.SpriteLayer failed");
    }
} catch (e) {
    console.log("✗ Test failed:", e.message);
}

console.log("\n=== Test completed ===");
