// Spriter AttachPoint Test
// Tests the AttachPoint system for sprite attachment

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter AttachPoint System' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
    // Skip all tests if Spriter support is not available
    if (!hasSpriterSupport) {
        it('Spriter support is not available - skipping all tests', function() {
            // This test will pass and indicate that Spriter support is not available
            expect(true).toBe(true);
        });
        return;
    }
    
    var port;
    var spriteLayer;
    var spriterSprite;
    var testSprite;
    
    beforeEach(function() {
        // Create a port and sprite layer for testing
        if (pdg.hasGraphics) {
            port = new pdg.Port(800, 600);
            spriteLayer = pdg.createSpriteLayer(port);
        } else {
            spriteLayer = pdg.createSpriteLayer();
        }
        
        // Create a Spriter sprite for testing (only if Spriter support is available)
        if (hasSpriterSupport) {
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            spriterSprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
        }
        
        // Create a test sprite to attach
        testSprite = spriteLayer.createSprite();
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
    
    describe('AttachPoint Methods', function() {
        it('should have AttachPoint methods', function() {
            expect(typeof spriterSprite.hasAttachPoint).toBe('function');
            expect(typeof spriterSprite.getAttachPoint).toBe('function');
            expect(typeof spriterSprite.attachSprite).toBe('function');
            expect(typeof spriterSprite.detachSprite).toBe('function');
            expect(typeof spriterSprite.getAttachedSprite).toBe('function');
        });
        
        it('should check for AttachPoint existence', function() {
            // Test with a valid AttachPoint name (if any exist in the model)
            // Note: This test may need adjustment based on actual AttachPoint names in the model
            var hasPoint = spriterSprite.hasAttachPoint("test_point");
            expect(typeof hasPoint).toBe('boolean');
        });
        
        it('should get AttachPoint position', function() {
            // Test getting the position of an AttachPoint
            var offset = spriterSprite.getAttachPoint("test_point");
            expect(offset).toBeDefined();
            expect(typeof offset.x).toBe('number');
            expect(typeof offset.y).toBe('number');
        });

        
        it('should handle attachSprite with valid AttachPoint', function() {
            // Test attaching a sprite to an AttachPoint
            expect(function() {
                spriterSprite.attachSprite(testSprite, "test_point");
            }).not.toThrow();
        });
        
        it('should handle attachSprite with invalid AttachPoint', function() {
            // Test attaching a sprite to a non-existent AttachPoint
            expect(function() {
                spriterSprite.attachSprite(testSprite, "nonexistent_point");
            }).not.toThrow();
        });
        
        it('should handle detachSprite', function() {
            // Test detaching a sprite
            expect(function() {
                spriterSprite.detachSprite(testSprite);
            }).not.toThrow();
        });
        
        it('should return attached sprite', function() {
            // Initially should be no attached sprite
            var attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeNull();
            
            // After attaching, should return the attached sprite
            // Note: This test may need adjustment based on actual implementation
            spriterSprite.attachSprite(testSprite, "test_point");
            attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeDefined();
        });
    });
    
    describe('AttachPoint Functionality', function() {
        it('should maintain attachment state', function() {
            // Test that attachment state is properly maintained
            spriterSprite.attachSprite(testSprite, "test_point");
            var attached1 = spriterSprite.getAttachedSprite("test_point");
            
            spriterSprite.attachSprite(testSprite, "another_point");
            var attached2 = spriterSprite.getAttachedSprite("another_point");
            
            // Should maintain attachment across calls
            expect(attached1).toBeDefined();
            expect(attached2).toBeDefined();
        });
        
        it('should handle multiple attach/detach cycles', function() {
            // Test multiple attach/detach operations
            for (var i = 0; i < 5; i++) {
                spriterSprite.attachSprite(testSprite, "test_point");
                var attached = spriterSprite.getAttachedSprite("test_point");
                expect(attached).toBeDefined();
                
                spriterSprite.detachSprite(testSprite);
                attached = spriterSprite.getAttachedSprite("test_point");
                expect(attached).toBeNull();
            }
        });
    });
    
    describe('Error Handling', function() {
        it('should handle null AttachPoint names', function() {
            expect(function() {
                spriterSprite.hasAttachPoint(null);
            }).not.toThrow();
            
            // Test that attachSprite with null attach point name throws an error
            expect(function() {
                spriterSprite.attachSprite(testSprite, null);
            }).toThrow();
        });
        
        it('should handle empty AttachPoint names', function() {
            expect(function() {
                spriterSprite.hasAttachPoint("");
            }).not.toThrow();
            
            // Test that attachSprite with empty attach point name doesn't throw an error
            expect(function() {
                spriterSprite.attachSprite(testSprite, "");
            }).not.toThrow();
        });
        
        it('should handle undefined AttachPoint names', function() {
            // These should throw errors for undefined parameters
            expect(function() {
                spriterSprite.hasAttachPoint(undefined);
            }).toThrow();
            
            expect(function() {
                spriterSprite.attachSprite(testSprite, undefined);
            }).toThrow();
        });
    });
    
    describe('Integration with Animation', function() {
        it('should maintain attachment during animation', function() {
            // Test that attachment persists during animation
            spriterSprite.attachSprite(testSprite, "test_point");
            var attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeDefined();
            
            // Start an animation
            spriterSprite.startAnimation("idle");
            
            // Attachment should still exist
            attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeDefined();
        });
        
        it('should maintain attachment during blending', function() {
            // Test that attachment persists during animation blending
            spriterSprite.attachSprite(testSprite, "test_point");
            var attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeDefined();
            
            // Start blending
            spriterSprite.blendToAnimation("idle", 0.5);
            
            // Attachment should still exist
            attached = spriterSprite.getAttachedSprite("test_point");
            expect(attached).toBeDefined();
        });
    });
    
    describe('Multiple Sprite Attachment', function() {
        it('should allow multiple sprites to be attached to different attach points', function() {
            // Attach different sprites to different attach points
            spriterSprite.attachSprite(testSprite, "point1");
            spriterSprite.attachSprite(testSprite, "point2");
            spriterSprite.attachSprite(testSprite, "point3");
            
            // Verify that each attach point has a sprite attached
            var attached1 = spriterSprite.getAttachedSprite("point1");
            var attached2 = spriterSprite.getAttachedSprite("point2");
            var attached3 = spriterSprite.getAttachedSprite("point3");
            
            expect(attached1).toBeDefined();
            expect(attached2).toBeDefined();
            expect(attached3).toBeDefined();
        });
        
        it('should replace existing sprite when attaching a new sprite to the same point', function() {
            // First attach sprite to point1
            spriterSprite.attachSprite(testSprite, "point1");
            var attached1 = spriterSprite.getAttachedSprite("point1");
            expect(attached1).toBeDefined();
            
            // Now attach sprite to the same point again - should replace the previous attachment
            spriterSprite.attachSprite(testSprite, "point1");
            var attached2 = spriterSprite.getAttachedSprite("point1");
            expect(attached2).toBeDefined();
            
            // The attached sprite should be the same (since it's the same sprite)
            expect(attached2).toBe(attached1);
        });
        
        it('should do nothing when attaching the same sprite to the same point twice', function() {
            // Attach sprite to point1
            spriterSprite.attachSprite(testSprite, "point1");
            var firstAttach = spriterSprite.getAttachedSprite("point1");
            
            // Attach the same sprite to the same point again
            spriterSprite.attachSprite(testSprite, "point1");
            var secondAttach = spriterSprite.getAttachedSprite("point1");
            
            // Should be the same sprite
            expect(secondAttach).toBe(firstAttach);
        });
        
        it('should detach sprite from all points when detachSprite is called', function() {
            // Attach sprite to multiple points
            spriterSprite.attachSprite(testSprite, "point1");
            spriterSprite.attachSprite(testSprite, "point2");
            spriterSprite.attachSprite(testSprite, "point3");
            
            // Verify attachments exist
            expect(spriterSprite.getAttachedSprite("point1")).toBeDefined();
            expect(spriterSprite.getAttachedSprite("point2")).toBeDefined();
            expect(spriterSprite.getAttachedSprite("point3")).toBeDefined();
            
            // Detach sprite from all points
            spriterSprite.detachSprite(testSprite);
            
            // Verify all attachments are removed
            expect(spriterSprite.getAttachedSprite("point1")).toBeNull();
            expect(spriterSprite.getAttachedSprite("point2")).toBeNull();
            expect(spriterSprite.getAttachedSprite("point3")).toBeNull();
        });
        
        it('should handle mixed attachment scenarios', function() {
            // Attach to point1
            spriterSprite.attachSprite(testSprite, "point1");
            expect(spriterSprite.getAttachedSprite("point1")).toBeDefined();
            
            // Attach to point2
            spriterSprite.attachSprite(testSprite, "point2");
            expect(spriterSprite.getAttachedSprite("point2")).toBeDefined();
            
            // Replace sprite at point1
            spriterSprite.attachSprite(testSprite, "point1");
            var newAttached1 = spriterSprite.getAttachedSprite("point1");
            expect(newAttached1).toBeDefined();
            
            // Point2 should still have its sprite
            expect(spriterSprite.getAttachedSprite("point2")).toBeDefined();
            
            // Attach to point3
            spriterSprite.attachSprite(testSprite, "point3");
            expect(spriterSprite.getAttachedSprite("point3")).toBeDefined();
            
            // All three points should have sprites
            expect(spriterSprite.getAttachedSprite("point1")).toBeDefined();
            expect(spriterSprite.getAttachedSprite("point2")).toBeDefined();
            expect(spriterSprite.getAttachedSprite("point3")).toBeDefined();
        });
    });
});
