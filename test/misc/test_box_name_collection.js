// Test script to verify box name collection from Spriter files
// This script demonstrates how the PDG Object Factory now tracks box names

var pdg = require('pdg');

// Create a sprite layer
var layer = pdg.createSpriteLayer();

// Create a sprite from a Spriter file (this will trigger box name collection)
var sprite = layer.createSpriteFromSpriterFile('test/data/test_collision_boxes.scml');

if (sprite) {
    console.log("Sprite created successfully");
    
    // Enable Spriter collision boxes
    sprite.enableCollisions(pdg.collide_SpriterCollisionBox);
    
    // Get the collision box count
    var collisionCount = sprite.getSpriterCollisionBoxCount();
    console.log("Number of collision boxes:", collisionCount);
    
    // List all collision box names
    for (var i = 0; i < collisionCount; i++) {
        var boxName = sprite.getSpriterCollisionBoxName(i);
        console.log("Collision box", i, ":", boxName);
        
        // Check if the box is active
        var isActive = sprite.isSpriterCollisionActive(boxName);
        console.log("  Active:", isActive);
        
        // Get the collision box bounds
        var bounds = sprite.getSpriterCollisionBox(boxName);
        if (bounds) {
            console.log("  Bounds: width=" + bounds.getWidth() + ", height=" + bounds.getHeight());
        }
    }
} else {
    console.log("Failed to create sprite from Spriter file");
}

console.log("Box name collection test completed");
