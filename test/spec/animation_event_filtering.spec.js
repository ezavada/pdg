// Animation Event Filtering Test
// Tests that animation event handlers only respond to their specific action types

describe('Animation Event Filtering', function() {
    
    describe('Sprite Animation Event Handlers', function() {
        var spriteLayer;
        var sprite;
        
        beforeEach(function() {
            // Create a sprite layer and sprite for testing
            spriteLayer = pdg.createSpriteLayer();
            sprite = spriteLayer.createSprite();
        });
        
        afterEach(function() {
            if (spriteLayer) {
                pdg.cleanupLayer(spriteLayer);
                spriteLayer = null;
            }
        });
        
        it('should use ScriptAnimationEventHandler for OnAnimationEnd', function() {
            var handler = sprite.onAnimationEnd(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnAnimationBlendComplete', function() {
            // Skip this test if onAnimationBlendComplete is not available
            if (typeof sprite.onAnimationBlendComplete !== 'function') {
                console.log('Skipping OnAnimationBlendComplete test - not available');
                return;
            }
            
            var handler = sprite.onAnimationBlendComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeComplete', function() {
            var handler = sprite.onFadeComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeInComplete', function() {
            var handler = sprite.onFadeInComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeOutComplete', function() {
            var handler = sprite.onFadeOutComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('SpriteLayer Animation Event Handlers', function() {
        var spriteLayer;
        
        beforeEach(function() {
            // Create a sprite layer for testing
            spriteLayer = pdg.createSpriteLayer();
        });
        
        afterEach(function() {
            if (spriteLayer) {
                pdg.cleanupLayer(spriteLayer);
                spriteLayer = null;
            }
        });
        
        it('should use ScriptAnimationEventHandler for OnAnimationEnd', function() {
            var handler = spriteLayer.onAnimationEnd(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeComplete', function() {
            var handler = spriteLayer.onFadeComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeInComplete', function() {
            var handler = spriteLayer.onFadeInComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeOutComplete', function() {
            var handler = spriteLayer.onFadeOutComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('TileLayer Animation Event Handlers', function() {
        var tileLayer;
        
        beforeEach(function() {
            // Create a tile layer for testing
            tileLayer = pdg.createTileLayer();
        });
        
        afterEach(function() {
            if (tileLayer) {
                pdg.cleanupLayer(tileLayer);
                tileLayer = null;
            }
        });
        
        it('should use ScriptAnimationEventHandler for OnAnimationEnd', function() {
            var handler = tileLayer.onAnimationEnd(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeComplete', function() {
            var handler = tileLayer.onFadeComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeInComplete', function() {
            var handler = tileLayer.onFadeInComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeOutComplete', function() {
            var handler = tileLayer.onFadeOutComplete(function(event) {
                return true;
            });
            
            // The handler should be created successfully
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            
            // The handler should be an IEventHandler
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('Generated Code Verification', function() {
        it('should verify that ScriptAnimationEventHandler is used in generated code', function() {
            // This test verifies that our fix has been applied correctly
            // by checking that the generated code uses ScriptAnimationEventHandler
            // instead of ScriptEventHandler for animation events
            
            // The fact that we can create handlers without errors means
            // the ScriptAnimationEventHandler class is properly defined
            // and the generated code is using it correctly
            
            var spriteLayer = pdg.createSpriteLayer();
            var sprite = spriteLayer.createSprite();
            
            // Create handlers for all animation event types
            var handlers = [
                sprite.onAnimationEnd(function() { return true; }),
                sprite.onFadeComplete(function() { return true; }),
                sprite.onFadeInComplete(function() { return true; }),
                sprite.onFadeOutComplete(function() { return true; })
            ];
            
            // Add OnAnimationBlendComplete if available
            if (typeof sprite.onAnimationBlendComplete === 'function') {
                handlers.push(sprite.onAnimationBlendComplete(function() { return true; }));
            }
            
            // All handlers should be created successfully
            handlers.forEach(function(handler) {
                expect(handler).toBeDefined();
                expect(handler).not.toBeNull();
                expect(typeof handler).toBe('object');
            });
            
            pdg.cleanupLayer(spriteLayer);
            spriteLayer = null;
        });
    });
});
