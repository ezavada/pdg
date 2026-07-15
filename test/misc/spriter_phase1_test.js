// Simple test for Phase 1 Spriter enhancements
// Tests character maps and basic event system

var pdg = require('pdg');

console.log("Testing Phase 1 Spriter enhancements...");

// Test character map functionality
function testCharacterMaps() {
    console.log("Testing character maps...");
    
    // Create a sprite layer
    var layer = new pdg.SpriteLayer();
    
    // Test applying character map to all sprites
    layer.applyCharacterMapToAll("test_map");
    console.log("✓ applyCharacterMapToAll() called successfully");
    
    // Test removing character map from all sprites
    layer.removeCharacterMapFromAll("test_map");
    console.log("✓ removeCharacterMapFromAll() called successfully");
    
    // Test enabling Spriter events
    layer.enableSpriterEvents(true);
    console.log("✓ enableSpriterEvents() called successfully");
}

// Test individual sprite functionality
function testSpriteMethods() {
    console.log("Testing sprite methods...");
    
    // Create a sprite layer
    var layer = new pdg.SpriteLayer();
    
    // Create a sprite (this will be a regular sprite, not Spriter for now)
    var sprite = layer.createSprite();
    
    // Test character map methods
    sprite.applyCharacterMap("test_map");
    console.log("✓ applyCharacterMap() called successfully");
    
    sprite.removeCharacterMap("test_map");
    console.log("✓ removeCharacterMap() called successfully");
    
    sprite.removeAllCharacterMaps();
    console.log("✓ removeAllCharacterMaps() called successfully");
    
    var maps = sprite.getAppliedCharacterMaps();
    console.log("✓ getAppliedCharacterMaps() returned:", maps);
    
    // Test event system methods
    sprite.enableSpriterEvents(true);
    console.log("✓ enableSpriterEvents() called successfully");
    
    var enabled = sprite.areSpriterEventsEnabled();
    console.log("✓ areSpriterEventsEnabled() returned:", enabled);
}

// Run tests
try {
    testCharacterMaps();
    testSpriteMethods();
    console.log("All Phase 1 tests passed!");
} catch (error) {
    console.error("Test failed:", error);
    process.exit(1);
}

