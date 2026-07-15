describe('Sprite Layer Event Filtering', function() {
    
    describe('SpriteLayer Event Handlers', function() {
        
        it('should use ScriptLayerEventHandler for OnErasePort', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onErasePort(function(evt) { 
                console.log("EARLY TEST OnErasePort handler called, returning false");
                return false; 
            });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnPreDrawLayer', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onPreDrawLayer(function(evt) { 
                console.log("EARLY TEST OnPreDrawLayer handler called, returning false");
                return false; 
            });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnPostDrawLayer', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onPostDrawLayer(function(evt) { 
                console.log("EARLY TEST OnPostDrawLayer handler called, returning false");
                return false; 
            });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnDrawPortComplete', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onDrawPortComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnAnimationStart', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onAnimationStart(function(evt) { 
                console.log("EARLY TEST OnAnimationStart handler called, returning false");
                return false; 
            });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnPreAnimateLayer', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onPreAnimateLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnPostAnimateLayer', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onPostAnimateLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnAnimationComplete', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onAnimationComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnZoomComplete', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onZoomComplete(function() {});
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnLayerFadeInComplete', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onLayerFadeInComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for OnLayerFadeOutComplete', function() {
            var layer = pdg.createSpriteLayer();
            var handler = layer.onLayerFadeOutComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
    });
    
    describe('TileLayer Event Handlers', function() {
        
        it('should use ScriptLayerEventHandler for TileLayer OnErasePort', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onErasePort(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnPreDrawLayer', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onPreDrawLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnPostDrawLayer', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onPostDrawLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnDrawPortComplete', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onDrawPortComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnAnimationStart', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onAnimationStart(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnPreAnimateLayer', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onPreAnimateLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnPostAnimateLayer', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onPostAnimateLayer(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnAnimationComplete', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onAnimationComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnZoomComplete', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onZoomComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnLayerFadeInComplete', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onLayerFadeInComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
        it('should use ScriptLayerEventHandler for TileLayer OnLayerFadeOutComplete', function() {
            var layer = pdg.createTileLayer();
            var handler = layer.onLayerFadeOutComplete(function() { return false; });
            expect(handler).toBeDefined();
            expect(typeof handler).toBe('object');
            pdg.cleanupLayer(layer);
        });
        
    });
    
    describe('Event Functionality Integration Tests', function() {
        
        var port;
        var spriteLayer;
        var sprite;
        
        beforeEach(function() {            
            // Create a port and sprite layer for testing
            // Use a unique port name to ensure this is completely separate from early tests
            if (pdg.hasGraphics) {
                port = pdg.gfx.createWindowPort({left: 0, top: 0, right: 800, bottom: 600}, "Integration Test Window " + Date.now());
                spriteLayer = pdg.createSpriteLayer(port);
            } else {
                spriteLayer = pdg.createSpriteLayer();
            }
            console.log("Integration test: Created NEW sprite layer:", spriteLayer);
            
            // Create a sprite to trigger events
            sprite = spriteLayer.createSprite();
            sprite.setSize(50, 50);
            sprite.moveTo(100, 100);
            sprite.setVelocity(50, 0); // Make it move to trigger events
        });
        
        afterEach(function() {
            if (sprite) {
                delete sprite;
            }
            if (spriteLayer) {
                pdg.cleanupLayer(spriteLayer);
                spriteLayer = null;
            }
            if (port) {
                delete port;
            }
        });
        
        it('should actually call onErasePort callbacks when port draw events occur', function() {
            if (!pdg.hasGraphics) {
                // Skip this test if graphics are not available
                expect(true).toBe(true);
                return;
            }
            
            var callbackCalled = false;
            var callbackCount = 0;
            var validEventData = false;
            
            spriteLayer.onErasePort(function(evt) {
                callbackCalled = true;
                callbackCount++;
                // Don't use expect() in event callbacks as they can throw exceptions
                // Just verify the event data exists and is valid
                if (evt && evt.millisec && typeof evt.millisec === 'number') {
                    // Event data is valid
                    validEventData = true;
                }
                return true;
            });
            
            // Start event loop to generate port draw events
            
            // Wait for events to be processed
            waitsFor(function() {
                return callbackCalled;
            }, "onErasePort callback to be called", 300);
            
            runs(function() {
                expect(callbackCalled).toBe(true);
                expect(callbackCount).toBeGreaterThan(0);
                expect(validEventData).toBe(true);
            });
        });
        
        it('should actually call onPreDrawLayer callbacks when layer draw events occur', function() {
            if (!pdg.hasGraphics) {
                // Skip this test if graphics are not available
                expect(true).toBe(true);
                return;
            }
            
            var callbackCalled = false;
            var callbackCount = 0;
            var validEventData = false;
            
            spriteLayer.onPreDrawLayer(function(evt) {
                callbackCalled = true;
                callbackCount++;
                // Don't use expect() in event callbacks as they can throw exceptions
                if (evt && evt.actingLayer) {
                    // Event data is valid
                    validEventData = true;
                }
                return true;
            });
            
            // Start event loop to generate layer draw events
            
            // Wait for events to be processed
            waitsFor(function() {
                return callbackCalled;
            }, "onPreDrawLayer callback to be called", 300);
            
            runs(function() {
                expect(callbackCalled).toBe(true);
                expect(callbackCount).toBeGreaterThan(0);
                expect(validEventData).toBe(true);
            });
        });
        
        it('should actually call onPostDrawLayer callbacks when layer draw events occur', function() {
            if (!pdg.hasGraphics) {
                // Skip this test if graphics are not available
                expect(true).toBe(true);
                return;
            }
            
            var callbackCalled = false;
            var callbackCount = 0;
            var validEventData = false;
            
            spriteLayer.onPostDrawLayer(function(evt) {
                callbackCalled = true;
                callbackCount++;
                // Don't use expect() in event callbacks as they can throw exceptions
                if (evt && evt.actingLayer) {
                    // Event data is valid
                    validEventData = true;
                }
                return true;
            });
            
            // Start event loop to generate layer draw events
            
            // Wait for events to be processed
            waitsFor(function() {
                return callbackCalled;
            }, "onPostDrawLayer callback to be called", 300);
            
            runs(function() {
                expect(callbackCalled).toBe(true);
                expect(callbackCount).toBeGreaterThan(0);
                expect(validEventData).toBe(true);
            });
        });
        
        it('should actually call onAnimationStart callbacks when animation events occur', function() {
            if (!pdg.hasGraphics) {
                // Skip this test if graphics are not available
                expect(true).toBe(true);
                return;
            }
            
            var callbackCalled = false;
            var callbackCount = 0;
            var validEventData = false;
            
            // Use the existing sprite layer from beforeEach
            
            spriteLayer.onAnimationStart(function(evt) {
                callbackCalled = true;
                callbackCount++;
                // Don't use expect() in event callbacks as they can throw exceptions
                if (evt && evt.actingLayer) {
                    // Event data is valid
                    validEventData = true;
                }
                return true;
            });
            
            // Start event loop to generate animation events
            
            // Wait for events to be processed
            waitsFor(function() {
                return callbackCalled;
            }, "onAnimationStart callback to be called", 300);
            
            runs(function() {
                expect(callbackCalled).toBe(true);
                expect(callbackCount).toBeGreaterThan(0);   
                expect(validEventData).toBe(true);
            });
        });
        
        it('should handle multiple event callbacks simultaneously', function() {
            if (!pdg.hasGraphics) {
                // Skip this test if graphics are not available
                expect(true).toBe(true);
                return;
            }
            
            var eraseCallbackCalled = false;
            var preDrawCallbackCalled = false;
            var postDrawCallbackCalled = false;
            
            // Use the existing sprite layer from beforeEach
            
            spriteLayer.onErasePort(function(evt) {
                eraseCallbackCalled = true;
                return true;
            });
            
            spriteLayer.onPreDrawLayer(function(evt) {
                preDrawCallbackCalled = true;
                return true;
            });
            
            spriteLayer.onPostDrawLayer(function(evt) {
                postDrawCallbackCalled = true;
                return true;
            });
            
            // Start event loop to generate events
            
            // Wait for events to be processed
            waitsFor(function() {
                return eraseCallbackCalled && preDrawCallbackCalled && postDrawCallbackCalled;
            }, "all callbacks to be called", 300);
            
            runs(function() {
                expect(eraseCallbackCalled).toBe(true);
                expect(preDrawCallbackCalled).toBe(true);
                expect(postDrawCallbackCalled).toBe(true);
            });
        });
                
    });
    
});
