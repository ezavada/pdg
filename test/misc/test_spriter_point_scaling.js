// Test script to verify Spriter point scaling issue
// Tests the FIXME in pdg_point_instance_info.cpp line 55 regarding flipped box scaling for points

var pdg = require('pdg');

console.log("Testing Spriter point scaling issue...");

// Check if Spriter support is available
var hasSpriterSupport = typeof pdg.createSpriteLayer === 'function';

if (!hasSpriterSupport) {
    console.log("Spriter support not available - skipping test");
    process.exit(0);
}

// Create a sprite layer
var layer = pdg.createSpriteLayer();

// Try to create a sprite from a Spriter file
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
    
    // Test point-related functionality
    console.log("Testing point-related functionality...");
    
    // Test point count
    if (typeof spriterSprite.getPointCount === 'function') {
        var pointCount = spriterSprite.getPointCount();
        console.log("Number of points:", pointCount);
        
        if (pointCount > 0) {
            console.log("Testing point access and scaling...");
            
            for (var i = 0; i < pointCount; i++) {
                try {
                    var pointName = spriterSprite.getPointName(i);
                    console.log("Point", i, "name:", pointName);
                    
                    // Test point position
                    if (typeof spriterSprite.getPointPosition === 'function') {
                        var position = spriterSprite.getPointPosition(pointName);
                        if (position) {
                            console.log("  Point position:", position.x, position.y);
                        }
                    }
                    
                    // Test point visibility
                    if (typeof spriterSprite.isPointVisible === 'function') {
                        var isVisible = spriterSprite.isPointVisible(pointName);
                        console.log("  Point visible:", isVisible);
                    }
                    
                } catch (error) {
                    console.log("ERROR accessing point", i, ":", error.message);
                }
            }
        } else {
            console.log("No points found in sprite");
        }
    } else {
        console.log("WARNING: getPointCount method not available");
    }
    
    // Test scaling effects on points
    console.log("Testing scaling effects on points...");
    
    if (typeof spriterSprite.setEntityScale === 'function') {
        // Test normal scaling
        console.log("Testing normal scaling (1x, 1x)...");
        spriterSprite.setEntityScale(1.0, 1.0);
        
        if (typeof spriterSprite.getPointCount === 'function') {
            var pointCount = spriterSprite.getPointCount();
            if (pointCount > 0) {
                var pointName = spriterSprite.getPointName(0);
                var normalPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Normal position:", normalPosition ? normalPosition.x + ", " + normalPosition.y : "null");
            }
        }
        
        // Test uniform scaling
        console.log("Testing uniform scaling (2x, 2x)...");
        spriterSprite.setEntityScale(2.0, 2.0);
        
        if (typeof spriterSprite.getPointCount === 'function') {
            var pointCount = spriterSprite.getPointCount();
            if (pointCount > 0) {
                var pointName = spriterSprite.getPointName(0);
                var scaledPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Scaled position:", scaledPosition ? scaledPosition.x + ", " + scaledPosition.y : "null");
            }
        }
        
        // Test flipped scaling (this is where the FIXME issue occurs)
        console.log("Testing flipped scaling (-1x, 1x) - FIXME test...");
        spriterSprite.setEntityScale(-1.0, 1.0);
        
        if (typeof spriterSprite.getPointCount === 'function') {
            var pointCount = spriterSprite.getPointCount();
            if (pointCount > 0) {
                var pointName = spriterSprite.getPointName(0);
                var flippedPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Flipped position:", flippedPosition ? flippedPosition.x + ", " + flippedPosition.y : "null");
                
                // This is where the FIXME issue would manifest
                // Points should be properly flipped when the sprite is flipped
                if (flippedPosition && normalPosition) {
                    var expectedX = -normalPosition.x;
                    var actualX = flippedPosition.x;
                    console.log("  Expected flipped X:", expectedX);
                    console.log("  Actual flipped X:", actualX);
                    
                    if (Math.abs(expectedX - actualX) < 0.1) {
                        console.log("  SUCCESS: Point scaling correctly handles flipping");
                    } else {
                        console.log("  FIXME ISSUE: Point scaling does not correctly handle flipping");
                        console.log("  This confirms the FIXME in pdg_point_instance_info.cpp line 55");
                    }
                }
            }
        }
        
        // Test asymmetric scaling
        console.log("Testing asymmetric scaling (1.5x, 0.5x)...");
        spriterSprite.setEntityScale(1.5, 0.5);
        
        if (typeof spriterSprite.getPointCount === 'function') {
            var pointCount = spriterSprite.getPointCount();
            if (pointCount > 0) {
                var pointName = spriterSprite.getPointName(0);
                var asymPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Asymmetric position:", asymPosition ? asymPosition.x + ", " + asymPosition.y : "null");
            }
        }
    }
    
    // Test sprite flipping methods
    if (typeof spriterSprite.flipX === 'function') {
        console.log("Testing sprite flipX method...");
        
        // Reset to normal scaling
        spriterSprite.setEntityScale(1.0, 1.0);
        
        if (typeof spriterSprite.getPointCount === 'function') {
            var pointCount = spriterSprite.getPointCount();
            if (pointCount > 0) {
                var pointName = spriterSprite.getPointName(0);
                var normalPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Normal position before flip:", normalPosition ? normalPosition.x + ", " + normalPosition.y : "null");
                
                // Flip the sprite
                spriterSprite.flipX();
                
                var flippedPosition = spriterSprite.getPointPosition(pointName);
                console.log("  Position after flipX:", flippedPosition ? flippedPosition.x + ", " + flippedPosition.y : "null");
                
                // Test if points are properly flipped
                if (flippedPosition && normalPosition) {
                    var expectedX = -normalPosition.x;
                    var actualX = flippedPosition.x;
                    
                    if (Math.abs(expectedX - actualX) < 0.1) {
                        console.log("  SUCCESS: flipX correctly flips points");
                    } else {
                        console.log("  FIXME ISSUE: flipX does not correctly flip points");
                    }
                }
            }
        }
    }
    
    // Test animation with point scaling
    if (typeof spriterSprite.startAnimation === 'function') {
        console.log("Testing animation with point scaling...");
        
        if (spriterSprite.hasAnimation && spriterSprite.hasAnimation('idle')) {
            spriterSprite.startAnimation('idle');
            console.log("Started idle animation");
            
            // Test point positions during animation
            if (typeof spriterSprite.getPointCount === 'function') {
                var pointCount = spriterSprite.getPointCount();
                if (pointCount > 0) {
                    var pointName = spriterSprite.getPointName(0);
                    var animPosition = spriterSprite.getPointPosition(pointName);
                    console.log("  Point position during animation:", animPosition ? animPosition.x + ", " + animPosition.y : "null");
                }
            }
            
            // Test scaling during animation
            spriterSprite.setEntityScale(-1.0, 1.0);
            console.log("Applied flipped scaling during animation");
            
            if (typeof spriterSprite.getPointCount === 'function') {
                var pointCount = spriterSprite.getPointCount();
                if (pointCount > 0) {
                    var pointName = spriterSprite.getPointName(0);
                    var animFlippedPosition = spriterSprite.getPointPosition(pointName);
                    console.log("  Point position during animation with flipped scaling:", animFlippedPosition ? animFlippedPosition.x + ", " + animFlippedPosition.y : "null");
                }
            }
        } else {
            console.log("No idle animation available for testing");
        }
    }
    
} else {
    console.log("ERROR: Could not create Spriter sprite from any available file");
}

pdg.cleanupLayer(layer);

console.log("Spriter point scaling test completed");
