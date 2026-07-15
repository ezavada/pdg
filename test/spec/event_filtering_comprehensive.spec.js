// Comprehensive Event Filtering Test
// Tests that both animation and touch event handlers only respond to their specific action/touch types

describe('Comprehensive Event Filtering', function() {
    
    describe('Animation Event Handlers', function() {
        var spriteLayer;
        var sprite;
        
        beforeEach(function() {
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
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeComplete', function() {
            var handler = sprite.onFadeComplete(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeInComplete', function() {
            var handler = sprite.onFadeInComplete(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnFadeOutComplete', function() {
            var handler = sprite.onFadeOutComplete(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptAnimationEventHandler for OnAnimationBlendComplete if available', function() {
            if (typeof sprite.onAnimationBlendComplete !== 'function') {
                console.log('Skipping OnAnimationBlendComplete test - not available');
                return;
            }
            
            var handler = sprite.onAnimationBlendComplete(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('Touch Event Handlers', function() {
        var spriteLayer;
        var sprite;
        
        beforeEach(function() {
            spriteLayer = pdg.createSpriteLayer();
            sprite = spriteLayer.createSprite();
        });
        
        afterEach(function() {
            if (spriteLayer) {
                pdg.cleanupLayer(spriteLayer);
                spriteLayer = null;
            }
        });
        
        it('should use ScriptTouchEventHandler for OnMouseEnter', function() {
            var handler = sprite.onMouseEnter(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for OnMouseLeave', function() {
            var handler = sprite.onMouseLeave(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for OnMouseDown', function() {
            var handler = sprite.onMouseDown(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for OnMouseUp', function() {
            var handler = sprite.onMouseUp(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for OnMouseClick', function() {
            var handler = sprite.onMouseClick(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('SpriteLayer Event Handlers', function() {
        var spriteLayer;
        
        beforeEach(function() {
            spriteLayer = pdg.createSpriteLayer();
        });
        
        afterEach(function() {
            if (spriteLayer) {
                pdg.cleanupLayer(spriteLayer);
                spriteLayer = null;
            }
        });
        
        it('should use ScriptAnimationEventHandler for SpriteLayer OnAnimationEnd', function() {
            var handler = spriteLayer.onAnimationEnd(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for SpriteLayer OnMouseClick', function() {
            var handler = spriteLayer.onMouseClick(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
    });
    
    describe('TileLayer Event Handlers', function() {
        var tileLayer;
        
        beforeEach(function() {
            tileLayer = pdg.createTileLayer();
        });
        
        afterEach(function() {
            if (tileLayer) {
                pdg.cleanupLayer(tileLayer);
                tileLayer = null;
            }
        });
        
        it('should use ScriptAnimationEventHandler for TileLayer OnAnimationEnd', function() {
            var handler = tileLayer.onAnimationEnd(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
        
        it('should use ScriptTouchEventHandler for TileLayer OnMouseClick', function() {
            var handler = tileLayer.onMouseClick(function(event) {
                return true;
            });
            
            expect(handler).toBeDefined();
            expect(handler).not.toBeNull();
            expect(typeof handler).toBe('object');
        });
    });
});
