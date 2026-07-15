// Test script to verify Spriter entity scaling issue
// Tests the FIXME in sprite.cpp line 2494 regarding proper scaling of Spriter entities

var pdg = require('pdg');

console.log("Testing Spriter entity scaling...");

// Check if Spriter support is available
var hasSpriterSupport = typeof pdg.createSpriteLayer === 'function';

if (!hasSpriterSupport) {
    console.log("Spriter support not available - skipping test");
    process.exit(0);
}

// Create a sprite layer
var layer = pdg.createSpriteLayer();

// Try to create a sprite from a Spriter file
var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
var spriterSprite = layer.createSpriteFromSpriterFile(scmlPath);

if (!spriterSprite) {
    console.log("Could not create Spriter sprite - trying alternative path");
    // Try alternative path
    scmlPath = process.cwd() + "/test/data/test_collision_boxes.scml";
    spriterSprite = layer.createSpriteFromSpriterFile(scmlPath);
}

if (spriterSprite) {
    console.log("Spriter sprite created successfully");
    
    // Test initial scaling
    var initialWidth = spriterSprite.getWidth();
    var initialHeight = spriterSprite.getHeight();
    console.log("Initial dimensions:", initialWidth, "x", initialHeight);
    
    // Test entity scaling methods
    if (typeof spriterSprite.setEntityScale === 'function') {
        console.log("Testing setEntityScale method...");
        
        // Test scaling up
        spriterSprite.setEntityScale(2.0, 2.0);
        var scaledWidth = spriterSprite.getWidth();
        var scaledHeight = spriterSprite.getHeight();
        console.log("After 2x scaling:", scaledWidth, "x", scaledHeight);
        
        // Test scaling down
        spriterSprite.setEntityScale(0.5, 0.5);
        var scaledDownWidth = spriterSprite.getWidth();
        var scaledDownHeight = spriterSprite.getHeight();
        console.log("After 0.5x scaling:", scaledDownWidth, "x", scaledDownHeight);
        
        // Test asymmetric scaling
        spriterSprite.setEntityScale(2.0, 1.0);
        var asymWidth = spriterSprite.getWidth();
        var asymHeight = spriterSprite.getHeight();
        console.log("After asymmetric scaling (2x, 1x):", asymWidth, "x", asymHeight);
        
        // Test sprite scaling vs entity scaling
        console.log("Testing sprite scaling vs entity scaling...");
        
        // Reset to 1x scaling
        spriterSprite.setEntityScale(1.0, 1.0);
        var resetWidth = spriterSprite.getWidth();
        var resetHeight = spriterSprite.getHeight();
        console.log("After reset to 1x:", resetWidth, "x", resetHeight);
        
        // Test sprite scaling
        spriterSprite.setSize(100, 150);
        var spriteScaledWidth = spriterSprite.getWidth();
        var spriteScaledHeight = spriterSprite.getHeight();
        console.log("After sprite.setSize(100, 150):", spriteScaledWidth, "x", spriteScaledHeight);
        
        // Test entity scaling on top of sprite scaling
        spriterSprite.setEntityScale(1.5, 1.5);
        var combinedWidth = spriterSprite.getWidth();
        var combinedHeight = spriterSprite.getHeight();
        console.log("After entity scaling on sprite-scaled sprite:", combinedWidth, "x", combinedHeight);
        
    } else {
        console.log("WARNING: setEntityScale method not available");
    }
    
    // Test animation scaling
    if (typeof spriterSprite.startAnimation === 'function') {
        console.log("Testing scaling during animation...");
        
        if (spriterSprite.hasAnimation && spriterSprite.hasAnimation('walk')) {
            spriterSprite.startAnimation('walk');
            console.log("Started walk animation");
            
            // Test scaling during animation
            spriterSprite.setEntityScale(2.0, 2.0);
            var animScaledWidth = spriterSprite.getWidth();
            var animScaledHeight = spriterSprite.getHeight();
            console.log("Scaled during animation:", animScaledWidth, "x", animScaledHeight);
        } else {
            console.log("No walk animation available for testing");
        }
    }
    
} else {
    console.log("ERROR: Could not create Spriter sprite from any available file");
    console.log("This may indicate the FIXME issue with scaling is preventing proper sprite creation");
}

pdg.cleanupLayer(layer);

console.log("Spriter entity scaling test completed");
