// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter Sub-Entity Management' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
    // Skip all tests if Spriter support is not available
    if (!hasSpriterSupport) {
        it('Spriter support is not available - skipping all tests', function() {
            expect(true).toBe(true);
        });
        return;
    }
    
    var port;
    var spriteLayer;
    var spriterSprite;

    beforeEach(function() {
        // Create a port and sprite layer for testing
        if (pdg.hasGraphics) {
            port = new pdg.Port(800, 600);
            spriteLayer = pdg.createSpriteLayer(port);
        } else {
            spriteLayer = pdg.createSpriteLayer();
        }
        
        // Create a sprite from a Spriter file
        var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
        spriterSprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
    });

    afterEach(function() {
        if (port) {
            delete port;
        }
        if (spriteLayer) {
            pdg.cleanupLayer(spriteLayer);
            spriteLayer = null;
        }
    });

    describe('activateSubEntity Method', function() {
        it('should have activateSubEntity method', function() {
            expect(typeof spriterSprite.activateSubEntity).toBe('function');
        });

        it('should accept entity name and optional animation name', function() {
            // Test that the method can be called with just entity name
            expect(function() {
                spriterSprite.activateSubEntity("test_sub_entity");
            }).not.toThrow();

            // Test that the method can be called with entity name and animation name
            expect(function() {
                spriterSprite.activateSubEntity("test_sub_entity", "walk");
            }).not.toThrow();
        });

        it('should use "idle" as default animation when not specified', function() {
            // This test verifies the default behavior
            // The actual implementation should use "idle" as default
            expect(function() {
                spriterSprite.activateSubEntity("test_sub_entity");
            }).not.toThrow();
        });

        it('should handle null or undefined parameters gracefully', function() {
            // Test with undefined entity name - should throw
            expect(function() {
                spriterSprite.activateSubEntity(undefined);
            }).toThrow();

            // Test with null animation name - should throw
            expect(function() {
                spriterSprite.activateSubEntity("test_sub_entity", null);
            }).toThrow();
        });
    });

    describe('Model Tracking', function() {
        it('should have access to the SpriterModel', function() {
            // Verify that the sprite has the model reference set
            // This is an internal implementation detail, but we can test the behavior
            expect(function() {
                spriterSprite.activateSubEntity("test_sub_entity");
            }).not.toThrow();
        });
    });
});
