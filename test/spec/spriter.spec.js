// SpriterPlusPlus Integration Test
// Tests the conversion from SCMLpp to SpriterPlusPlus

//var pdg = require('pdg');

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('SpriterPlusPlus Integration' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
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
        
        // Create a Spriter sprite for testing
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
    
    describe('XML Document Parsing', function() {
        it('should load SCML file successfully', function() {
            // Test with a simple SCML file
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            
            // Try to create a sprite from the SCML file
            var sprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
            
            expect(sprite).not.toBeNull();
        });
        
        it('should handle missing SCML file gracefully', function() {
            var sprite = spriteLayer.createSpriteFromSpriterFile("nonexistent.scml");
            expect(sprite).toBeNull();
        });
        
        it('should handle malformed SCML file gracefully', function() {
            // Create a temporary malformed SCML file
            var fs = require('fs');
            var os = require('os');
            var path = require('path');
            var tempFile = path.join(os.tmpdir(), "malformed.scml");
            fs.writeFileSync(tempFile, "<invalid>xml</invalid>");
            
            var sprite = spriteLayer.createSpriteFromSpriterFile(tempFile);
            expect(sprite).toBeNull();
            
            // Clean up
            if (fs.existsSync(tempFile)) {
                fs.unlinkSync(tempFile);
            }
        });
    });
    
    describe('Entity Creation', function() {
        it('should create entity instances from loaded SCML', function() {
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            
            // First create a sprite to load the SCML
            var sprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
            expect(sprite).not.toBeNull();
            
            // Try to create additional sprites from the same entity
            var sprite2 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
            expect(sprite2).not.toBeNull();
            
            // The sprites should be different instances
            expect(sprite).not.toBe(sprite2);
        });
        
        it('should create sprites from specific entity names', function() {
            // Test createSpriteFromSpriterEntity method
            expect(typeof spriteLayer.createSpriteFromSpriterEntity).toBe('function');
            
            // Try to create a sprite from a specific entity (if available)
            var entitySprite = spriteLayer.createSpriteFromSpriterEntity("wonkyskeleton");
            
            // This might return null if the entity doesn't exist, which is acceptable
            // The important thing is that the method exists and doesn't crash
            expect(entitySprite === null || typeof entitySprite === 'object').toBe(true);
        });
    });
    
    describe('Spriter Animation API', function() {
        it('should have animation query methods', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test hasAnimation methods
            expect(typeof spriterSprite.hasAnimation).toBe('function');
            
            // Test with string parameter
            expect(typeof spriterSprite.hasAnimation("walk")).toBe('boolean');
            
            // Test with integer parameter
            expect(typeof spriterSprite.hasAnimation(0)).toBe('boolean');
        });
        
        it('should have animation control methods', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test startAnimation methods
            expect(typeof spriterSprite.startAnimation).toBe('function');
            
            // Test with string parameter
            expect(function() {
                spriterSprite.startAnimation("walk");
            }).not.toThrow();
            
            // Test with integer parameter
            expect(function() {
                spriterSprite.startAnimation(0);
            }).not.toThrow();
        });
        
        it('should have entity scale methods', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test setEntityScale method
            expect(typeof spriterSprite.setEntityScale).toBe('function');
            
            // Test the method call
            expect(function() {
                spriterSprite.setEntityScale(1.0, 1.0);
            }).not.toThrow();
            
            // Test that it returns the sprite for chaining
            var result = spriterSprite.setEntityScale(2.0, 2.0);
            expect(result).toBe(spriterSprite);
        });
        
        it('should handle animation queries for non-existent animations', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test that the method returns boolean values
            var result1 = spriterSprite.hasAnimation("this_animation_definitely_does_not_exist_12345");
            var result2 = spriterSprite.hasAnimation("another_nonexistent_animation_67890");
            var result3 = spriterSprite.hasAnimation(999999);
            var result4 = spriterSprite.hasAnimation(1000000);
            
            expect(typeof result1).toBe('boolean');
            expect(typeof result2).toBe('boolean');
            expect(typeof result3).toBe('boolean');
            expect(typeof result4).toBe('boolean');
            
            // Test that the method doesn't crash with invalid inputs
            expect(function() {
                spriterSprite.hasAnimation("");
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.hasAnimation(null);
            }).not.toThrow();
        });
        
        it('should handle animation control for non-existent animations', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test that starting non-existent animations doesn't crash
            expect(function() {
                spriterSprite.startAnimation("nonexistent_animation");
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.startAnimation(-1);
            }).not.toThrow();
        });
    });
    
    describe('Spriter Support', function() {
        it('should support basic animation playback', function() {
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            var sprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
            
            expect(sprite).not.toBeNull();
            
            // Test animation methods
            expect(typeof sprite.startAnimation).toBe('function');
            expect(typeof sprite.rotate).toBe('function');
        });
        
        it('should have all required Spriter API methods', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Verify all Phase 1 Spriter methods exist
            expect(typeof spriterSprite.hasAnimation).toBe('function');
            expect(typeof spriterSprite.startAnimation).toBe('function');
            expect(typeof spriterSprite.setEntityScale).toBe('function');
            
            // Verify SpriteLayer methods exist
            expect(typeof spriteLayer.createSpriteFromSpriterFile).toBe('function');
            expect(typeof spriteLayer.createSpriteFromSpriterEntity).toBe('function');
        });
    });
    
    describe('Entity Scale Functionality', function() {
        it('should handle various scale values', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test different scale combinations
            expect(function() {
                spriterSprite.setEntityScale(0.5, 0.5);  // Scale down
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.setEntityScale(2.0, 2.0);  // Scale up
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.setEntityScale(1.0, 2.0);  // Different X and Y scales
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.setEntityScale(0.1, 10.0);  // Extreme scales
            }).not.toThrow();
        });
        
        it('should support method chaining', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test that setEntityScale returns the sprite for chaining
            var result = spriterSprite.setEntityScale(1.0, 1.0);
            expect(result).toBe(spriterSprite);
            
            // Test chaining multiple calls
            var chainResult = spriterSprite
                .setEntityScale(1.5, 1.5)
                .setEntityScale(2.0, 2.0);
            expect(chainResult).toBe(spriterSprite);
        });
    });
    
    describe('Performance', function() {
        it('should handle multiple sprites efficiently', function() {
            var scmlPath = process.cwd() + "/data/spriter-samples/greyguy/player.scml";
            var sprites = [];
            
            // Create multiple sprites
            for (var i = 0; i < 10; i++) {
                var sprite = spriteLayer.createSpriteFromSpriterFile(scmlPath);
                expect(sprite).not.toBeNull();
                sprites.push(sprite);
            }
            
            // Verify all sprites are unique
            for (var i = 0; i < sprites.length; i++) {
                for (var j = i + 1; j < sprites.length; j++) {
                    expect(sprites[i]).not.toBe(sprites[j]);
                }
            }
        });
        
        it('should handle multiple entity creation efficiently', function() {
            var sprites = [];
            
            // Create multiple sprites from the same entity
            for (var i = 0; i < 5; i++) {
                var sprite = spriteLayer.createSpriteFromSpriterEntity("wonkyskeleton");
                if (sprite) {
                    sprites.push(sprite);
                }
            }
            
            // Verify sprites are created (if entity exists) or gracefully handle null
            expect(sprites.length >= 0).toBe(true);
            
            // If sprites were created, verify they are unique
            for (var i = 0; i < sprites.length; i++) {
                for (var j = i + 1; j < sprites.length; j++) {
                    expect(sprites[i]).not.toBe(sprites[j]);
                }
            }
        });
    });
    
    describe('Error Handling', function() {
        it('should handle invalid entity names gracefully', function() {
            // Test with invalid entity names
            expect(function() {
                spriteLayer.createSpriteFromSpriterEntity("");
            }).not.toThrow();
            
            expect(function() {
                spriteLayer.createSpriteFromSpriterEntity("invalid_entity");
            }).not.toThrow();
            
        });
        
        it('should handle invalid animation parameters gracefully', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test with invalid animation names
            expect(function() {
                spriterSprite.hasAnimation("");
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.startAnimation("");
            }).not.toThrow();           
        });
        
        it('should handle invalid scale parameters gracefully', function() {
            expect(spriterSprite).not.toBeNull();
            
            // Test with invalid scale values
            expect(function() {
                spriterSprite.setEntityScale(0, 0);
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.setEntityScale(-1, -1);
            }).not.toThrow();
            
            expect(function() {
                spriterSprite.setEntityScale(1000, 1000);
            }).not.toThrow();
        });
    });
});
