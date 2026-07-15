// Test Spriter loading with actual SCML file in resources
console.log("Testing Spriter with SCML file in resources...");

var pdg = require('pdg');

try {
    // Get the ResourceManager singleton
    var rm = pdg.res;
    console.log("ResourceManager singleton:", typeof rm);
    
    // Open the test directory as a resource (should already be open from previous test)
    var testDir = process.cwd() + "/test";
    console.log("Opening test directory as resource:", testDir);
    
    var refNum = rm.openResourceFile(testDir);
    console.log("Opened resource file, ref num:", refNum);
    
    if (refNum > 0) {
        // Check paths
        var paths = rm.getResourcePaths();
        console.log("Resource paths:", paths);
        
        // Try to get the size of the SCML file
        var size = rm.getResourceSize("player.scml");
        console.log("Size of player.scml:", size);
        
        if (size > 0) {
            // Now test Spriter loading with the SCML file
            console.log("\nTesting Spriter loading with SCML file...");
            var port = new pdg.Port(800, 600);
            var spriteLayer = pdg.createSpriteLayer(port);
            
            // Test with relative path (should find it in resources)
            console.log("Test: Loading player.scml as relative path...");
            try {
                var sprite = spriteLayer.createSpriteFromSpriterFile("player.scml");
                if (sprite) {
                    console.log("✓ SUCCESS! Loaded SCML file from resources");
                    console.log("  Sprite type:", typeof sprite);
                } else {
                    console.log("✗ Failed to create sprite from SCML file");
                }
            } catch (error) {
                console.log("✗ Error loading SCML file:", error.message);
            }
            
            // Clean up
            pdg.cleanupLayer(spriteLayer);
            
        } else {
            console.log("SCML file not found in resources");
        }
        
    } else {
        console.log("Failed to open test directory as resource");
    }
    
} catch (error) {
    console.log("Error:", error.message);
}
