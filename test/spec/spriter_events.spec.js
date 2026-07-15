// Tests the new spriter events system functionality

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter Event System', function() {
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
        
        // Spriter support is already checked in beforeAll
        
        // Try to create a Spriter sprite for character map testing
        var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
        if (hasSpriterSupport) {
            spriterSprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
        }
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
    
    describe('Event System Functionality', function() {
        it('should detect Spriter support correctly', function() {
            // This test verifies that Spriter support detection works
            expect(typeof hasSpriterSupport).toBe('boolean');
            if (hasSpriterSupport) {
                expect(typeof spriteLayer.createSpriteFromSpriterFile).toBe('function');
            } else {
                expect(typeof spriteLayer.createSpriteFromSpriterFile).toBe('undefined');
            }
        });
        
        describe('Sprite Event System', function() {
            it('should enable Spriter events on sprite', function() {
                expect(typeof sprite.enableSpriterEvents).toBe('function');
                expect(typeof sprite.areSpriterEventsEnabled).toBe('function');
                
                // Initially events should be disabled
                expect(sprite.areSpriterEventsEnabled()).toBe(false);
                
                // Enable events
                sprite.enableSpriterEvents(true);
                expect(sprite.areSpriterEventsEnabled()).toBe(true);
            });
            
            it('should disable Spriter events on sprite', function() {
                // Enable events first
                sprite.enableSpriterEvents(true);
                expect(sprite.areSpriterEventsEnabled()).toBe(true);
                
                // Disable events
                sprite.enableSpriterEvents(false);
                expect(sprite.areSpriterEventsEnabled()).toBe(false);
            });
            
            it('should enable Spriter events by default when no parameter provided', function() {
                // Enable events without parameter (should default to true)
                sprite.enableSpriterEvents();
                expect(sprite.areSpriterEventsEnabled()).toBe(true);
            });
            
            it('should handle multiple enable/disable calls', function() {
                // Test multiple enable/disable cycles
                sprite.enableSpriterEvents(true);
                expect(sprite.areSpriterEventsEnabled()).toBe(true);
                
                sprite.enableSpriterEvents(false);
                expect(sprite.areSpriterEventsEnabled()).toBe(false);
                
                sprite.enableSpriterEvents(true);
                expect(sprite.areSpriterEventsEnabled()).toBe(true);
                
                sprite.enableSpriterEvents(false);
                expect(sprite.areSpriterEventsEnabled()).toBe(false);
            });
        });
        
        describe('SpriteLayer Event System' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
            it('should enable Spriter events on all Spriter sprites in layer', function() {
                // Check if Spriter support is available
                if (!hasSpriterSupport) {
                    // Skip test if Spriter support is not available
                    return;
                }
                
                // Create multiple Spriter sprites (only these will be affected)
                var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
                var spriterSprite1 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                var spriterSprite2 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                var spriterSprite3 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                
                // Test should fail if Spriter sprites couldn't be created
                expect(spriterSprite1).not.toBeNull("First Spriter sprite should be created successfully");
                expect(spriterSprite2).not.toBeNull("Second Spriter sprite should be created successfully");
                expect(spriterSprite3).not.toBeNull("Third Spriter sprite should be created successfully");
                
                // Initially events should be disabled on all Spriter sprites
                expect(spriterSprite1.areSpriterEventsEnabled()).toBe(false);
                expect(spriterSprite2.areSpriterEventsEnabled()).toBe(false);
                expect(spriterSprite3.areSpriterEventsEnabled()).toBe(false);
                
                // Enable events on all Spriter sprites
                spriteLayer.enableSpriterEvents(true);
                
                // Verify all Spriter sprites have events enabled
                expect(spriterSprite1.areSpriterEventsEnabled()).toBe(true);
                expect(spriterSprite2.areSpriterEventsEnabled()).toBe(true);
                expect(spriterSprite3.areSpriterEventsEnabled()).toBe(true);
            });
            
            it('should disable Spriter events on all Spriter sprites in layer', function() {
                // Check if Spriter support is available
                if (!hasSpriterSupport) {
                    // Skip test if Spriter support is not available
                    return;
                }
                
                // Create multiple Spriter sprites (only these will be affected)
                var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
                var spriterSprite1 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                var spriterSprite2 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                var spriterSprite3 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                
                // Test should fail if Spriter sprites couldn't be created
                expect(spriterSprite1).not.toBeNull("First Spriter sprite should be created successfully");
                expect(spriterSprite2).not.toBeNull("Second Spriter sprite should be created successfully");
                expect(spriterSprite3).not.toBeNull("Third Spriter sprite should be created successfully");
                
                // Enable events on all Spriter sprites first
                spriteLayer.enableSpriterEvents(true);
                expect(spriterSprite1.areSpriterEventsEnabled()).toBe(true);
                expect(spriterSprite2.areSpriterEventsEnabled()).toBe(true);
                expect(spriterSprite3.areSpriterEventsEnabled()).toBe(true);
                
                // Disable events on all Spriter sprites
                spriteLayer.enableSpriterEvents(false);
                
                // Verify all Spriter sprites have events disabled
                expect(spriterSprite1.areSpriterEventsEnabled()).toBe(false);
                expect(spriterSprite2.areSpriterEventsEnabled()).toBe(false);
                expect(spriterSprite3.areSpriterEventsEnabled()).toBe(false);
            });
            
            it('should not affect regular sprites when enabling Spriter events', function() {
                // Create regular sprites (these should NOT be affected)
                var regularSprite1 = spriteLayer.createSprite();
                var regularSprite2 = spriteLayer.createSprite();
                
                // Initially events should be disabled on regular sprites
                expect(regularSprite1.areSpriterEventsEnabled()).toBe(false);
                expect(regularSprite2.areSpriterEventsEnabled()).toBe(false);
                
                // Enable Spriter events on layer (should not affect regular sprites)
                spriteLayer.enableSpriterEvents(true);
                
                // Verify regular sprites are still disabled (not affected)
                expect(regularSprite1.areSpriterEventsEnabled()).toBe(false);
                expect(regularSprite2.areSpriterEventsEnabled()).toBe(false);
                
                // Manually enable events on regular sprites to verify they work individually
                regularSprite1.enableSpriterEvents(true);
                regularSprite2.enableSpriterEvents(true);
                expect(regularSprite1.areSpriterEventsEnabled()).toBe(true);
                expect(regularSprite2.areSpriterEventsEnabled()).toBe(true);
            });
            
            it('should handle empty sprite layer for events', function() {
                // Create empty layer
                var emptyLayer = pdg.createSpriteLayer();
                
                // Enable/disable events on empty layer (should not crash)
                emptyLayer.enableSpriterEvents(true);
                emptyLayer.enableSpriterEvents(false);
                
                // Test should pass if no exceptions are thrown
                expect(true).toBe(true);
                pdg.cleanupLayer(emptyLayer);
                emptyLayer = null;
            });
        });
    });
   
    describe('Integration Tests' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
        it('should handle events on mixed sprite types correctly', function() {
            // Check if Spriter support is available
            if (!hasSpriterSupport) {
                // Skip test if Spriter support is not available
                return;
            }
            
            // Create a mix of regular and Spriter sprites
            var regularSprites = [];
            var spriterSprites = [];
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            
            // Create 3 regular sprites
            for (var i = 0; i < 3; i++) {
                regularSprites.push(spriteLayer.createSprite());
            }
            
            // Create 2 Spriter sprites
            for (var i = 0; i < 2; i++) {
                var spriterSprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                expect(spriterSprite).not.toBeNull("Spriter sprite " + (i + 1) + " should be created successfully");
                spriterSprites.push(spriterSprite);
            }
            
            // Initially all sprites should have events disabled
            for (var i = 0; i < regularSprites.length; i++) {
                expect(regularSprites[i].areSpriterEventsEnabled()).toBe(false);
            }
            for (var i = 0; i < spriterSprites.length; i++) {
                expect(spriterSprites[i].areSpriterEventsEnabled()).toBe(false);
            }
            
            // Enable events on layer (should only affect Spriter sprites)
            spriteLayer.enableSpriterEvents(true);
            
            // Verify regular sprites are still disabled (not affected)
            for (var i = 0; i < regularSprites.length; i++) {
                expect(regularSprites[i].areSpriterEventsEnabled()).toBe(false);
            }
            
            // Verify Spriter sprites have events enabled
            for (var i = 0; i < spriterSprites.length; i++) {
                expect(spriterSprites[i].areSpriterEventsEnabled()).toBe(true);
            }
            
            // Disable events on layer (should only affect Spriter sprites)
            spriteLayer.enableSpriterEvents(false);
            
            // Verify regular sprites are still disabled (still not affected)
            for (var i = 0; i < regularSprites.length; i++) {
                expect(regularSprites[i].areSpriterEventsEnabled()).toBe(false);
            }
            
            // Verify Spriter sprites have events disabled
            for (var i = 0; i < spriterSprites.length; i++) {
                expect(spriterSprites[i].areSpriterEventsEnabled()).toBe(false);
            }
            
            // Test that individual sprite control still works
            regularSprites[0].enableSpriterEvents(true);
            spriterSprites[0].enableSpriterEvents(true);
            expect(regularSprites[0].areSpriterEventsEnabled()).toBe(true);
            expect(spriterSprites[0].areSpriterEventsEnabled()).toBe(true);
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
        it('should have all Spriter event methods available on Sprite', function() {
            expect(typeof sprite.enableSpriterEvents).toBe('function');
            expect(typeof sprite.areSpriterEventsEnabled).toBe('function');
        });
        
        it('should have all Spriter event methods available on SpriteLayer', function() {
            expect(typeof spriteLayer.enableSpriterEvents).toBe('function');
        });
    });
    
});
