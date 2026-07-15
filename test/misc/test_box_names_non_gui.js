// Test script to verify box names support in non-GUI mode
// Tests the FIXME in sprite.cpp line 3177 regarding box names in non-GUI mode

var pdg = require('pdg');

console.log("Testing box names support in non-GUI mode...");

// Check if we're in GUI mode or not
var isGuiMode = pdg.hasGraphics;
console.log("Graphics mode available:", isGuiMode);

// Create a sprite layer
var layer = pdg.createSpriteLayer();

// Try to create a sprite from a Spriter file with collision boxes
var scmlPath = process.cwd() + "/test/data/test_collision_boxes.scml";
var spriterSprite = layer.createSpriteFromSpriterFile(scmlPath);

if (!spriterSprite) {
    console.log("Could not create Spriter sprite - trying alternative path");
    // Try alternative path
    scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
    spriterSprite = layer.createSpriteFromSpriterFile(scmlPath);
}

if (spriterSprite) {
    console.log("Spriter sprite created successfully");
    
    // Test collision box methods
    if (typeof spriterSprite.getSpriterCollisionBoxCount === 'function') {
        var boxCount = spriterSprite.getSpriterCollisionBoxCount();
        console.log("Number of collision boxes:", boxCount);
        
        if (boxCount > 0) {
            console.log("Testing box name collection...");
            
            // Test getting box names
            for (var i = 0; i < boxCount; i++) {
                try {
                    var boxName = spriterSprite.getSpriterCollisionBoxName(i);
                    console.log("Box", i, "name:", boxName);
                    
                    // Test if the box is active
                    if (typeof spriterSprite.isSpriterCollisionActive === 'function') {
                        var isActive = spriterSprite.isSpriterCollisionActive(boxName);
                        console.log("  Box", boxName, "is active:", isActive);
                    }
                    
                    // Test getting box bounds
                    if (typeof spriterSprite.getSpriterCollisionBox === 'function') {
                        var boxBounds = spriterSprite.getSpriterCollisionBox(boxName);
                        if (boxBounds) {
                            console.log("  Box bounds: width=" + boxBounds.getWidth() + ", height=" + boxBounds.getHeight());
                        } else {
                            console.log("  WARNING: Could not get box bounds for", boxName);
                        }
                    }
                    
                } catch (error) {
                    console.log("ERROR getting box", i, ":", error.message);
                    console.log("This may indicate the FIXME issue with box names in non-GUI mode");
                }
            }
        } else {
            console.log("No collision boxes found in sprite");
        }
    } else {
        console.log("WARNING: getSpriterCollisionBoxCount method not available");
    }
    
    // Test collision type support
    if (typeof spriterSprite.enableCollisions === 'function') {
        console.log("Testing collision type support...");
        
        try {
            spriterSprite.enableCollisions(pdg.collide_SpriterCollisionBox);
            console.log("Successfully enabled Spriter collision boxes");
            
            var collisionType = spriterSprite.getCollisionType();
            console.log("Current collision type:", collisionType);
            
            if (collisionType === pdg.collide_SpriterCollisionBox) {
                console.log("Collision type correctly set to Spriter collision box");
            } else {
                console.log("WARNING: Collision type not properly set");
            }
            
        } catch (error) {
            console.log("ERROR enabling Spriter collisions:", error.message);
            console.log("This may indicate the FIXME issue with box names in non-GUI mode");
        }
    }
    
    // Test box name iteration methods
    if (typeof spriterSprite.getSpriterCollisionBoxNames === 'function') {
        console.log("Testing getSpriterCollisionBoxNames method...");
        try {
            var boxNames = spriterSprite.getSpriterCollisionBoxNames();
            console.log("All box names:", boxNames);
        } catch (error) {
            console.log("ERROR getting box names:", error.message);
        }
    }
    
} else {
    console.log("ERROR: Could not create Spriter sprite from any available file");
}

// Test non-GUI mode specific functionality
if (!isGuiMode) {
    console.log("Running in non-GUI mode - testing box name functionality...");
    
    // In non-GUI mode, box names should still work for collision detection
    // even if they can't be visually rendered
    if (spriterSprite) {
        console.log("Non-GUI mode: Testing collision box name resolution...");
        
        // Test that we can still get box names and use them for collision detection
        // even without GUI rendering capabilities
        var boxCount = spriterSprite.getSpriterCollisionBoxCount();
        if (boxCount > 0) {
            console.log("Non-GUI mode: Successfully retrieved", boxCount, "collision boxes");
            
            // Test that box names are available for collision detection
            for (var i = 0; i < Math.min(boxCount, 3); i++) {
                var boxName = spriterSprite.getSpriterCollisionBoxName(i);
                console.log("Non-GUI mode: Box", i, "name available:", boxName);
            }
        }
    }
} else {
    console.log("Running in GUI mode - box names should work normally");
}

pdg.cleanupLayer(layer);

console.log("Box names non-GUI mode test completed");
