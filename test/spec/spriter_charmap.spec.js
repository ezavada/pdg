// Tests the new character map functionality

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter Character Map' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
    // Skip all tests if Spriter support is not available
    if (!hasSpriterSupport) {
        it('Spriter support is not available - skipping all tests', function() {
            expect(true).toBe(true);
        });
        return;
    }
    
    var port;
    var spriteLayer;
    var sprite;
    var spriterSprite;
    
    beforeEach(function() {
        // Create a port and sprite layer for testing
        if (pdg.hasGraphics) {
            port = new pdg.Port(800, 600);
            spriteLayer = pdg.createSpriteLayer(port);
        } else {
            spriteLayer = pdg.createSpriteLayer();
        }
        
        // Create a regular sprite for testing event system (works on any sprite)
        sprite = spriteLayer.createSprite();
        
        // Try to create a Spriter sprite for character map testing
        // Use the working sample files from test/data/spriter-samples/
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
        if (sprite) {
            delete sprite;
        }
        if (spriterSprite) {
            delete spriterSprite;
        }
    });
    
    describe('Character Map Functionality', function() {
        describe('Sprite Character Maps', function() {
            it('should have character map methods available', function() {
                expect(typeof sprite.applyCharacterMap).toBe('function');
                expect(typeof sprite.removeCharacterMap).toBe('function');
                expect(typeof sprite.removeAllCharacterMaps).toBe('function');
                expect(typeof sprite.getAppliedCharacterMaps).toBe('function');
            });
            
            it('should return empty array when no character maps are applied', function() {
                var appliedMaps = sprite.getAppliedCharacterMaps();
                expect(Array.isArray(appliedMaps)).toBe(true);
                expect(appliedMaps.length).toBe(0);
            });
            
            it('should handle empty string character map names', function() {
                // Test with empty string
                sprite.applyCharacterMap("");
                var appliedMaps = sprite.getAppliedCharacterMaps();
                expect(appliedMaps.length).toBe(0);
            });
            
            it('should handle removing non-existent character map', function() {
                // Try to remove a map that wasn't applied
                sprite.removeCharacterMap("non_existent_map");
                
                // Verify no error occurred and no maps are applied
                var appliedMaps = sprite.getAppliedCharacterMaps();
                expect(appliedMaps.length).toBe(0);
            });
        });
        
        describe('SpriteLayer Character Maps', function() {
            it('should have character map methods available', function() {
                expect(typeof spriteLayer.applyCharacterMapToAll).toBe('function');
                expect(typeof spriteLayer.removeCharacterMapFromAll).toBe('function');
            });
            
            it('should handle empty sprite layer', function() {
                // Create empty layer
                var emptyLayer = pdg.createSpriteLayer();
                
                // Apply character map to empty layer (should not crash)
                emptyLayer.applyCharacterMapToAll("test_map");
                emptyLayer.removeCharacterMapFromAll("test_map");
                
                // Test should pass if no exceptions are thrown
                expect(true).toBe(true);
                pdg.cleanupLayer(emptyLayer);
                emptyLayer = null;
            });
        });
    });
    
    describe('Error Handling and Edge Cases', function() {
        it('should handle rapid event enable/disable operations', function() {
            // Enable and disable events rapidly
            for (var i = 0; i < 10; i++) {
                sprite.enableSpriterEvents(true);
                sprite.enableSpriterEvents(false);
            }
            
            // Verify final state
            expect(sprite.areSpriterEventsEnabled()).toBe(false);
        });
    });
    
    describe('Method Availability', function() {
        it('should have all Spriter character map methods available on Sprite', function() {
            expect(typeof sprite.applyCharacterMap).toBe('function');
            expect(typeof sprite.removeCharacterMap).toBe('function');
            expect(typeof sprite.removeAllCharacterMaps).toBe('function');
            expect(typeof sprite.getAppliedCharacterMaps).toBe('function');
            expect(typeof sprite.enableSpriterEvents).toBe('function');
            expect(typeof sprite.areSpriterEventsEnabled).toBe('function');
        });
        
        it('should have all Spriter character map methods available on SpriteLayer', function() {
            expect(typeof spriteLayer.applyCharacterMapToAll).toBe('function');
            expect(typeof spriteLayer.removeCharacterMapFromAll).toBe('function');
            expect(typeof spriteLayer.enableSpriterEvents).toBe('function');
        });
    });
    
    describe('Character Map Integration (Spriter Sprites)', function() {
        it('should apply character map to Spriter sprite', function() {
            spriterSprite.applyCharacterMap("test_map");
            var appliedMaps = spriterSprite.getAppliedCharacterMaps();
            expect(Array.isArray(appliedMaps)).toBe(true);
            expect(appliedMaps).toContain("test_map");
        });
        
        it('should remove character map from Spriter sprite', function() {
            spriterSprite.applyCharacterMap("test_map");
            spriterSprite.removeCharacterMap("test_map");
            var appliedMaps = spriterSprite.getAppliedCharacterMaps();
            expect(appliedMaps).not.toContain("test_map");
        });
        
        it('should handle multiple character maps on Spriter sprite', function() {
            spriterSprite.applyCharacterMap("map1");
            spriterSprite.applyCharacterMap("map2");
            spriterSprite.applyCharacterMap("map3");
            
            var appliedMaps = spriterSprite.getAppliedCharacterMaps();
            expect(appliedMaps).toContain("map1");
            expect(appliedMaps).toContain("map2");
            expect(appliedMaps).toContain("map3");
            
            spriterSprite.removeAllCharacterMaps();
            expect(spriterSprite.getAppliedCharacterMaps().length).toBe(0);
        });
    });
});
