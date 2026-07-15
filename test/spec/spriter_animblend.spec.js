// Spriter Animation Blending Test
// Tests the animation blending functionality

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter Animation Blending' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
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
    
    describe('Animation Blending Methods', function() {
        it('should have animation blending methods', function() {
            expect(typeof spriterSprite.blendToAnimation).toBe('function');
            expect(typeof spriterSprite.isBlending).toBe('function');
            expect(typeof spriterSprite.getBlendProgress).toBe('function');
            expect(typeof spriterSprite.pauseAnimation).toBe('function');
            expect(typeof spriterSprite.resumeAnimation).toBe('function');
            expect(typeof spriterSprite.stopAnimation).toBe('function');
            expect(typeof spriterSprite.isAnimationPlaying).toBe('function');
            expect(typeof spriterSprite.isAnimationPaused).toBe('function');
            expect(typeof spriterSprite.getAnimationProgress).toBe('function');
        });
        
        it('should handle blendToAnimation with string animation name', function() {
            // Test blending to an animation by name
            expect(function() {
                spriterSprite.blendToAnimation("idle", 0.5);
            }).not.toThrow();
        });
        
        it('should handle blendToAnimation with animation ID', function() {
            // Test blending to an animation by ID
            expect(function() {
                spriterSprite.blendToAnimation(0, 0.5);
            }).not.toThrow();
        });
        
        it('should return blending state', function() {
            // Initially should not be blending
            expect(spriterSprite.isBlending()).toBe(false);
            
            // Start blending
            spriterSprite.blendToAnimation("idle", 0.5);
            
            // Should now be blending
            expect(spriterSprite.isBlending()).toBe(true);
        });
        
        it('should return blend progress', function() {
            // Initially progress should be 0
            expect(spriterSprite.getBlendProgress()).toBe(0);
            
            // Start blending
            spriterSprite.blendToAnimation("idle", 1.0);
            
            // Progress should be greater than or equal to 0
            expect(spriterSprite.getBlendProgress() >= 0).toBe(true);
        });
        
        it('should handle animation state management', function() {
            // Initially should be playing
            expect(spriterSprite.isAnimationPlaying()).toBe(true);
            expect(spriterSprite.isAnimationPaused()).toBe(false);
            
            // Pause animation
            spriterSprite.pauseAnimation();
            expect(spriterSprite.isAnimationPlaying()).toBe(false);
            expect(spriterSprite.isAnimationPaused()).toBe(true);
            
            // Resume animation
            spriterSprite.resumeAnimation();
            expect(spriterSprite.isAnimationPlaying()).toBe(true);
            expect(spriterSprite.isAnimationPaused()).toBe(false);
            
            // Stop animation
            spriterSprite.stopAnimation();
            expect(spriterSprite.isAnimationPlaying()).toBe(false);
            expect(spriterSprite.isAnimationPaused()).toBe(true);
        });
        
        it('should return animation progress', function() {
            // Animation progress should be a number between 0 and 1
            var progress = spriterSprite.getAnimationProgress();
            expect(typeof progress).toBe('number');
            expect(progress >= 0).toBe(true);
            expect(progress <= 1).toBe(true);
        });
    });
    
    describe('Animation Blending Events', function() {
        it('should trigger animation blend complete event', function(done) {
            // Set up event handler
            spriterSprite.onAnimationBlendComplete(function() {
                console.log("Animation blend complete event fired!");
                done(); // Call done() when event fires
                return true; // Event handled
            });
            
            console.log("before animation start");
            spriterSprite.startAnimation("idle");
            console.log("after animation start");
            console.log("before blendToAnimation");
            // Start blending
            spriterSprite.blendToAnimation("walk", 0.1);
            console.log("after blendToAnimation");

            // Wait for blend to complete
            setTimeout(function() {
                // If done() wasn't called, the test will timeout
            }, 200);
        });
    });
    
    describe('Error Handling', function() {
        it('should handle invalid animation names gracefully', function() {
            expect(function() {
                spriterSprite.blendToAnimation("nonexistent_animation", 0.5);
            }).not.toThrow();
        });
        
        it('should handle invalid animation IDs gracefully', function() {
            expect(function() {
                spriterSprite.blendToAnimation(999, 0.5);
            }).not.toThrow();
        });
        
        it('should handle negative blend times gracefully', function() {
            expect(function() {
                spriterSprite.blendToAnimation("idle", -0.5);
            }).not.toThrow();
        });
    });
});
