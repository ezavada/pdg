// Test script to verify Spriter image file port setting issue
// Tests the FIXME in pdg_spriter_wrapper.cpp line 105 regarding setting ports on PDGImageFile objects

var pdg = require('pdg');

console.log("Testing Spriter image file port setting...");

// Check if Spriter support is available
var hasSpriterSupport = typeof pdg.createSpriteLayer === 'function';

if (!hasSpriterSupport) {
    console.log("Spriter support not available - skipping test");
    process.exit(0);
}

// Create a port and sprite layer
var port = null;
var layer = null;

if (pdg.hasGraphics) {
    port = new pdg.Port(800, 600);
    layer = pdg.createSpriteLayer(port);
    console.log("Created port and sprite layer with graphics");
} else {
    layer = pdg.createSpriteLayer();
    console.log("Created sprite layer without graphics (non-GUI mode)");
}

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
    
    // Test if the sprite has image-related methods
    console.log("Testing image-related functionality...");
    
    // Test image file access
    if (typeof spriterSprite.getImageFileCount === 'function') {
        var imageCount = spriterSprite.getImageFileCount();
        console.log("Number of image files:", imageCount);
        
        if (imageCount > 0) {
            console.log("Testing image file port access...");
            
            for (var i = 0; i < imageCount; i++) {
                try {
                    var imageFile = spriterSprite.getImageFile(i);
                    if (imageFile) {
                        console.log("Image file", i, ":", imageFile);
                        
                        // Test if the image file has a port
                        if (typeof imageFile.getPort === 'function') {
                            var imagePort = imageFile.getPort();
                            console.log("  Image file", i, "has port:", imagePort ? "yes" : "no");
                            
                            if (imagePort) {
                                console.log("  Image port dimensions:", imagePort.getWidth(), "x", imagePort.getHeight());
                            }
                        } else {
                            console.log("  WARNING: Image file", i, "does not have getPort method");
                        }
                        
                        // Test setting port on image file
                        if (typeof imageFile.setPort === 'function' && port) {
                            try {
                                imageFile.setPort(port);
                                console.log("  Successfully set port on image file", i);
                            } catch (error) {
                                console.log("  ERROR setting port on image file", i, ":", error.message);
                            }
                        } else if (!port) {
                            console.log("  No port available to set on image file", i);
                        }
                    } else {
                        console.log("  Image file", i, "is null");
                    }
                } catch (error) {
                    console.log("ERROR accessing image file", i, ":", error.message);
                    console.log("This may indicate the FIXME issue with image file port setting");
                }
            }
        } else {
            console.log("No image files found in sprite");
        }
    } else {
        console.log("WARNING: getImageFileCount method not available");
    }
    
    // Test sprite rendering to see if image ports are properly set
    if (port && typeof spriterSprite.draw === 'function') {
        console.log("Testing sprite rendering with image ports...");
        
        try {
            // Set sprite location
            spriterSprite.setLocation(400, 300);
            
            // Try to draw the sprite
            spriterSprite.draw(port);
            console.log("Successfully drew Spriter sprite");
            
            // Test animation rendering
            if (typeof spriterSprite.startAnimation === 'function') {
                if (spriterSprite.hasAnimation && spriterSprite.hasAnimation('idle')) {
                    spriterSprite.startAnimation('idle');
                    console.log("Started idle animation");
                    
                    // Draw animated sprite
                    spriterSprite.draw(port);
                    console.log("Successfully drew animated Spriter sprite");
                } else {
                    console.log("No idle animation available for testing");
                }
            }
            
        } catch (error) {
            console.log("ERROR drawing Spriter sprite:", error.message);
            console.log("This may indicate the FIXME issue with image file port setting");
        }
    } else if (!port) {
        console.log("No port available for rendering test");
    }
    
    // Test image file port management
    if (typeof spriterSprite.setImageFilePorts === 'function') {
        console.log("Testing setImageFilePorts method...");
        
        if (port) {
            try {
                spriterSprite.setImageFilePorts(port);
                console.log("Successfully set image file ports");
            } catch (error) {
                console.log("ERROR setting image file ports:", error.message);
            }
        } else {
            console.log("No port available for setImageFilePorts test");
        }
    } else {
        console.log("WARNING: setImageFilePorts method not available");
        console.log("This may indicate the FIXME issue is not yet implemented");
    }
    
} else {
    console.log("ERROR: Could not create Spriter sprite from any available file");
}

// Clean up
if (port) {
    delete port;
}
if (layer) {
    pdg.cleanupLayer(layer);
}

console.log("Spriter image file port setting test completed");
