// Test script to verify resource file loading issue
// Tests the FIXME in spritelayer.cpp line 1354 regarding resource file loading

var pdg = require('pdg');

console.log("Testing resource file loading...");

// Test different file path scenarios
var testPaths = [
    "test/data/test_collision_boxes.scml",
    "data/spriter-samples/greyguy/player.scml",
    "data/spriter-samples/wonkyskeleton/wonkyskeleton.scml",
    "../test/data/test_collision_boxes.scml",
    "./test/data/test_collision_boxes.scml"
];

// Create a sprite layer
var layer = pdg.createSpriteLayer();

testPaths.forEach(function(testPath) {
    console.log("\nTesting path:", testPath);
    
    try {
        // Test if the file exists using resource manager
        var resourceManager = pdg.getResourceManager();
        if (resourceManager) {
            console.log("  Resource manager available");
            
            // Try to get resource size to check if file exists
            var size = resourceManager.getResourceSize(testPath);
            console.log("  Resource size:", size);
            
            if (size > 0) {
                console.log("  File found via resource manager");
            } else {
                console.log("  File not found via resource manager");
            }
        } else {
            console.log("  WARNING: Resource manager not available");
        }
        
        // Test sprite creation from file
        var sprite = layer.createSpriteFromSpriterFile(testPath);
        if (sprite) {
            console.log("  SUCCESS: Sprite created from", testPath);
            
            // Test sprite properties
            console.log("    Sprite ID:", sprite.id);
            console.log("    Sprite dimensions:", sprite.getWidth(), "x", sprite.getHeight());
            
            // Test collision box count
            if (typeof sprite.getSpriterCollisionBoxCount === 'function') {
                var boxCount = sprite.getSpriterCollisionBoxCount();
                console.log("    Collision boxes:", boxCount);
            }
            
            // Clean up the sprite
            layer.removeSprite(sprite);
            
        } else {
            console.log("  FAILED: Could not create sprite from", testPath);
        }
        
    } catch (error) {
        console.log("  ERROR:", error.message);
    }
});

// Test resource file loading with different approaches
console.log("\nTesting different resource loading approaches...");

// Test 1: Direct file loading
try {
    var directPath = "test/data/test_collision_boxes.scml";
    console.log("Testing direct file loading:", directPath);
    
    var sprite1 = layer.createSpriteFromSpriterFile(directPath);
    if (sprite1) {
        console.log("  Direct loading successful");
        layer.removeSprite(sprite1);
    } else {
        console.log("  Direct loading failed");
    }
} catch (error) {
    console.log("  Direct loading error:", error.message);
}

// Test 2: Resource file loading
try {
    var resourceManager = pdg.getResourceManager();
    if (resourceManager) {
        console.log("Testing resource file loading...");
        
        // Try to open resource file
        var refNum = resourceManager.openResourceFile("test/data");
        console.log("  Resource file reference:", refNum);
        
        if (refNum > 0) {
            // Try to get resource paths
            var paths = resourceManager.getResourcePaths();
            console.log("  Resource paths:", paths);
            
            // Try to create sprite from resource
            var sprite2 = layer.createSpriteFromSpriterFile("test_collision_boxes.scml");
            if (sprite2) {
                console.log("  Resource-based loading successful");
                layer.removeSprite(sprite2);
            } else {
                console.log("  Resource-based loading failed");
            }
            
            // Close resource file
            resourceManager.closeResourceFile(refNum);
        }
    }
} catch (error) {
    console.log("  Resource loading error:", error.message);
}

// Test 3: File manager approach
try {
    var fileManager = pdg.getFileManager();
    if (fileManager) {
        console.log("Testing file manager approach...");
        
        // Get application directory
        var appDir = fileManager.getApplicationDirectory();
        console.log("  Application directory:", appDir);
        
        // Try to find SCML files
        var scmlFiles = fileManager.findFiles("**/*.scml");
        console.log("  Found SCML files:", scmlFiles);
        
        if (scmlFiles.length > 0) {
            // Try to create sprite from found file
            var testFile = scmlFiles[0];
            console.log("  Testing with file:", testFile);
            
            var sprite3 = layer.createSpriteFromSpriterFile(testFile);
            if (sprite3) {
                console.log("  File manager-based loading successful");
                layer.removeSprite(sprite3);
            } else {
                console.log("  File manager-based loading failed");
            }
        }
    }
} catch (error) {
    console.log("  File manager error:", error.message);
}

// Test 4: Absolute path loading
try {
    console.log("Testing absolute path loading...");
    
    var fileManager = pdg.getFileManager();
    if (fileManager) {
        var appDir = fileManager.getApplicationDirectory();
        var absolutePath = appDir + "/test/data/test_collision_boxes.scml";
        console.log("  Absolute path:", absolutePath);
        
        var sprite4 = layer.createSpriteFromSpriterFile(absolutePath);
        if (sprite4) {
            console.log("  Absolute path loading successful");
            layer.removeSprite(sprite4);
        } else {
            console.log("  Absolute path loading failed");
        }
    }
} catch (error) {
    console.log("  Absolute path loading error:", error.message);
}

pdg.cleanupLayer(layer);

console.log("\nResource file loading test completed");
