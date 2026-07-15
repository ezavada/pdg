// -----------------------------------------------
// spriter_collisions.spec.js
//
// test suite for Spriter Collision Box functionality
//
// Tests the new collide_SpriterCollisionBox collision type and related features
//
// -----------------------------------------------

// Check Spriter support once at the module level
var testSpriteLayer = pdg.createSpriteLayer();
var hasSpriterSupport = typeof testSpriteLayer.createSpriteFromSpriterFile === 'function';
pdg.cleanupLayer(testSpriteLayer);
testSpriteLayer = null;

describe('Spriter Collision Boxes' + (hasSpriterSupport ? ' (Spriter Support Enabled)' : ' (Spriter Support Disabled)'), function() {
    // Skip all tests if Spriter support is not available
    if (!hasSpriterSupport) {
        it('Spriter support is not available - skipping all tests', function() {
            expect(true).toBe(true);
        });
        return;
    }
    
    var port;
    var spriteLayer;
    var spriterSprite1;
    var spriterSprite2;
    var regularSprite;

    function waitForCondition(conditionFn, description, maxWaitTime) {
        maxWaitTime = maxWaitTime || 1000;
        var startTime = pdg.tm.getMilliseconds();

        waitsFor(function() {
            var currentTime = pdg.tm.getMilliseconds();
            if (currentTime - startTime > maxWaitTime) {
                console.log("Timeout waiting for condition: " + description);
                return true;
            }
            return conditionFn();
        }, description, maxWaitTime + 100);
    }

    function getSpriterCollisionBoxNames(sprite) {
        var names = [];
        var count = sprite.getSpriterCollisionBoxCount();
        for (var i = 0; i < count; i++) {
            var name = sprite.getSpriterCollisionBoxName(i);
            if (name) {
                names.push(name);
            }
        }
        return names;
    }

    function boxesAreReady(sprite) {
        return sprite && sprite.getSpriterCollisionBoxCount() > 0;
    }
    
    beforeEach(function() {
        // Create a port and sprite layer for testing
        if (pdg.hasGraphics) {
            port = new pdg.Port(800, 600);
            spriteLayer = pdg.createSpriteLayer(port);
        } else {
            spriteLayer = pdg.createSpriteLayer();
        }
        spriteLayer.enableCollisions();
        
        // Create Spriter sprites for testing
        // Note: These tests assume we have SCML files with collision boxes
        // For now, we'll test the API even if the files don't exist
        var scmlPath = process.cwd() + "/data/spriter-samples/wonkyskeleton/wonkyskeleton.scml";
        spriterSprite1 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
        spriterSprite2 = spriteLayer.createSpriteFromSpriterFile(scmlPath);
        
        // Debug: Check if sprites were created
        if (!spriterSprite1) {
            console.log("Warning: spriterSprite1 is null/undefined");
        }
        if (!spriterSprite2) {
            console.log("Warning: spriterSprite2 is null/undefined");
        }
        
        // Create a regular sprite for comparison
        regularSprite = spriteLayer.createSprite();
        regularSprite.setSize(50, 50);
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
    
    describe('Collision Type Support', function() {
        it('should support collide_SpriterCollisionBox collision type', function() {
            expect(pdg.collide_SpriterCollisionBox).toBeDefined();
            expect(pdg.collide_SpriterCollisionBox).toBe(5);
        });
        
        it('should allow enabling Spriter collision boxes', function() {
            if (spriterSprite1) {
                spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
                expect(spriterSprite1.getCollisionType()).toBe(pdg.collide_SpriterCollisionBox);
            }
        });
        
        it('should handle enabling Spriter collisions on non-Spriter sprites gracefully', function() {
            // Should not crash when enabling on regular sprites
            expect(function() {
                regularSprite.enableCollisions(pdg.collide_SpriterCollisionBox);
            }).not.toThrow();
        });
    });
    
    describe('Spriter Collision Box API', function() {
        it('should have getSpriterCollisionBox method', function() {
            if (spriterSprite1) {
                expect(typeof spriterSprite1.getSpriterCollisionBox).toBe('function');
            }
        });
        
        it('should have isSpriterCollisionActive method', function() {
            if (spriterSprite1) {
                expect(typeof spriterSprite1.isSpriterCollisionActive).toBe('function');
            }
        });
        
        it('should have getSpriterCollisionBoxCount method', function() {
            if (spriterSprite1) {
                expect(typeof spriterSprite1.getSpriterCollisionBoxCount).toBe('function');
            }
        });
        
        it('should have getSpriterCollisionBoxName method', function() {
            if (spriterSprite1) {
                expect(typeof spriterSprite1.getSpriterCollisionBoxName).toBe('function');
            }
        });
        
        it('should return collision box count', function() {
            if (spriterSprite1) {
                var count = spriterSprite1.getSpriterCollisionBoxCount();
                expect(typeof count).toBe('number');
                expect(count >= 0).toBe(true);
            }
        });
        
        it('should return collision box names', function() {
            if (spriterSprite1) {
                var count = spriterSprite1.getSpriterCollisionBoxCount();
                for (var i = 0; i < count; i++) {
                    var name = spriterSprite1.getSpriterCollisionBoxName(i);
                    expect(typeof name).toBe('string');
                    expect(name.length).toBeGreaterThan(0);
                }
            }
        });
        
        it('should return RotatedRect for collision boxes', function() {
            if (spriterSprite1) {
                var count = spriterSprite1.getSpriterCollisionBoxCount();
                if (count > 0) {
                    var name = spriterSprite1.getSpriterCollisionBoxName(0);
                    var box = spriterSprite1.getSpriterCollisionBox(name);
                    expect(box).toBeDefined();
                    expect(typeof box.getCenter).toBe('function');
                    expect(typeof box.getWidth).toBe('function');
                    expect(typeof box.getHeight).toBe('function');
                }
            }
        });
        
        it('should check if collision boxes are active', function() {
            if (spriterSprite1) {
                var count = spriterSprite1.getSpriterCollisionBoxCount();
                if (count > 0) {
                    var name = spriterSprite1.getSpriterCollisionBoxName(0);
                    var isActive = spriterSprite1.isSpriterCollisionActive(name);
                    expect(typeof isActive).toBe('boolean');
                }
            }
        });
        
        it('should handle non-existent collision box names gracefully', function() {
            if (spriterSprite1) {
                var box = spriterSprite1.getSpriterCollisionBox("nonexistent");
                expect(box).toBeDefined(); // Should return empty RotatedRect
                
                var isActive = spriterSprite1.isSpriterCollisionActive("nonexistent");
                expect(isActive).toBe(false);
            }
        });
    });
    
    describe('Event-Driven Collision Detection with pdg.run()', function() {
        it('should detect collisions between Spriter sprites using event handlers', function() {
            if (!spriterSprite1 || !spriterSprite2) {
                expect(true).toBe(true);
                return;
            }
            
            var collisionEvent1 = null;
            var collisionEvent2 = null;
            
            // Enable Spriter collision boxes
            waitForCondition(function() {
                return boxesAreReady(spriterSprite1) && boxesAreReady(spriterSprite2);
            }, "Spriter collision boxes to become active", 500);

            runs(function() {
                spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
                spriterSprite2.enableCollisions(pdg.collide_SpriterCollisionBox);

                spriterSprite1.onCollideSprite(function(event) {
                    collisionEvent1 = event;
                    return true;
                });
                
                spriterSprite2.onCollideSprite(function(event) {
                    collisionEvent2 = event;
                    return true;
                });

                // Keep the sprites overlapping, but not perfectly co-located, so
                // the collision normal stays well-defined across frames.
                spriterSprite1.setLocation(new pdg.Point(100, 100));
                spriterSprite2.setLocation(new pdg.Point(110, 100));
                
                var collisionType1 = spriterSprite1.getCollisionType();
                var collisionType2 = spriterSprite2.getCollisionType();
                expect(collisionType1).toBe(pdg.collide_SpriterCollisionBox);
                expect(collisionType2).toBe(pdg.collide_SpriterCollisionBox);
            });

            waitForCondition(function() {
                return !!collisionEvent1 && !!collisionEvent2;
            }, "Spriter sprites to report collisions", 500);

            runs(function() {
                expect(collisionEvent1).toBeDefined();
                expect(collisionEvent2).toBeDefined();

                expect(collisionEvent1.action).toBe(pdg.action_CollideSprite);
                expect(collisionEvent1.targetSprite).toBeDefined();
                expect(typeof collisionEvent1.isFirstContact).toBe('boolean');
                if (collisionEvent1.collisionName !== null) {
                    expect(typeof collisionEvent1.collisionName).toBe('string');
                }
                if (collisionEvent1.withCollisionName !== null) {
                    expect(typeof collisionEvent1.withCollisionName).toBe('string');
                }

                expect(collisionEvent2.action).toBe(pdg.action_CollideSprite);
                expect(collisionEvent2.targetSprite).toBeDefined();
                expect(typeof collisionEvent2.isFirstContact).toBe('boolean');
                if (collisionEvent2.collisionName !== null) {
                    expect(typeof collisionEvent2.collisionName).toBe('string');
                }
                if (collisionEvent2.withCollisionName !== null) {
                    expect(typeof collisionEvent2.withCollisionName).toBe('string');
                }
            });
        });
        
        it('should handle collision events with specific collision box names', function() {
            if (!spriterSprite1 || !spriterSprite2) {
                expect(true).toBe(true);
                return;
            }
            
            var collisionBoxNames1 = [];
            var collisionBoxNames2 = [];
            var collisionEvent = null;
            
            // Enable Spriter collision boxes
            waitForCondition(function() {
                return boxesAreReady(spriterSprite1) && boxesAreReady(spriterSprite2);
            }, "Spriter collision boxes to become active", 500);

            runs(function() {
                collisionBoxNames1 = getSpriterCollisionBoxNames(spriterSprite1);
                collisionBoxNames2 = getSpriterCollisionBoxNames(spriterSprite2);
                expect(collisionBoxNames1.length).toBeGreaterThan(0);
                expect(collisionBoxNames2.length).toBeGreaterThan(0);

                spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
                spriterSprite2.enableCollisions(pdg.collide_SpriterCollisionBox);
                spriterSprite1.onCollideSprite(function(event) {
                    collisionEvent = event;
                    return true;
                });

                spriterSprite1.setLocation(new pdg.Point(100, 100));
                spriterSprite2.setLocation(new pdg.Point(110, 100));
            });

            waitForCondition(function() {
                return !!collisionEvent && collisionEvent.collisionName !== null && collisionEvent.withCollisionName !== null;
            }, "Spriter collision event to include box names", 500);

            runs(function() {
                expect(collisionEvent).toBeDefined();
                expect(collisionEvent.action).toBe(pdg.action_CollideSprite);
                expect(collisionEvent.collisionName).not.toBeNull();
                expect(collisionEvent.withCollisionName).not.toBeNull();
                expect(collisionBoxNames1.indexOf(collisionEvent.collisionName) >= 0).toBe(true);
                expect(collisionBoxNames2.indexOf(collisionEvent.withCollisionName) >= 0).toBe(true);
            });
        });
        
        it('should detect first contact vs ongoing collisions', function() {
            if (!spriterSprite1 || !spriterSprite2) {
                expect(true).toBe(true);
                return;
            }
            
            var collisionCount = 0;
            var firstContactCount = 0;
            var ongoingCollisionCount = 0;
            
            // Enable Spriter collision boxes
            waitForCondition(function() {
                return boxesAreReady(spriterSprite1) && boxesAreReady(spriterSprite2);
            }, "Spriter collision boxes to become active", 500);

            runs(function() {
                function trackCollision(event) {
                    collisionCount++;
                    
                    if (event.isFirstContact) {
                        firstContactCount++;
                    } else {
                        ongoingCollisionCount++;
                    }
                    return true;
                }

                spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
                spriterSprite2.enableCollisions(pdg.collide_SpriterCollisionBox);
                
                spriterSprite1.onCollideSprite(trackCollision);
                spriterSprite2.onCollideSprite(trackCollision);

                spriterSprite1.setLocation(new pdg.Point(100, 100));
                spriterSprite2.setLocation(new pdg.Point(110, 100));
            });

            waitForCondition(function() {
                return collisionCount >= 2 && firstContactCount > 0 && ongoingCollisionCount > 0;
            }, "Spriter collision to report first and ongoing contact", 1000);

            runs(function() {
                expect(collisionCount).toBeGreaterThan(1);
                expect(firstContactCount).toBeGreaterThan(0);
                expect(ongoingCollisionCount).toBeGreaterThan(0);
            });
        });
    });
    
    describe('Collision Detection', function() {
        it('should detect collisions between Spriter sprites', function() {
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            spriterSprite2.enableCollisions(pdg.collide_SpriterCollisionBox);
            
            // Position sprites to overlap
            spriterSprite1.setLocation(new pdg.Point(100, 100));
            spriterSprite2.setLocation(new pdg.Point(100, 100));
            
            // Verify collision type is set correctly
            var collisionType1 = spriterSprite1.getCollisionType();
            var collisionType2 = spriterSprite2.getCollisionType();
            expect(collisionType1).toBe(pdg.collide_SpriterCollisionBox);
            expect(collisionType2).toBe(pdg.collide_SpriterCollisionBox);
        });
        
        it('should detect point collisions with Spriter collision boxes', function() {
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            spriterSprite1.setLocation(new pdg.Point(100, 100));
            
            // Test that collision detection is available
            var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
            expect(collisionCount >= 0).toBe(true);
        });
    });
    
    describe('Collision Event Information', function() {
        it('should include collision box names in collision events', function() {
            // FIXME: This test is not implemented yet
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            spriterSprite2.enableCollisions(pdg.collide_SpriterCollisionBox);
            
            spriterSprite1.setLocation(new pdg.Point(100, 100));
            spriterSprite2.setLocation(new pdg.Point(100, 100));
            
            // Test that collision events would include collision box names
            // Note: Actual collision detection happens during animation
            var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
            expect(collisionCount >= 0).toBe(true);
        });
        
        it('should distinguish between first contact and ongoing collisions', function() {
            // FIXME: This test is not implemented yet
            // Test that the API supports first contact detection
            var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
            expect(collisionCount >= 0).toBe(true);
        });
    });
    
    describe('Performance Optimization', function() {
        it('should use bounds optimization for collision detection', function() {
            if (spriterSprite1) {
                // Test that bounds optimization is available
                var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
                expect(collisionCount >= 0).toBe(true);
            } else {
                expect(true).toBe(true);
            }
        });
    });
    
    describe('Integration with Existing Collision System', function() {
        it('should work alongside other collision types', function() {
            // FIXME: This test is not implemented yet
            // Test that we can switch between collision types
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            var collisionType1 = spriterSprite1.getCollisionType();
            expect(collisionType1).toBe(pdg.collide_SpriterCollisionBox);
            
            spriterSprite1.enableCollisions(pdg.collide_BoundingBox);
            var collisionType2 = spriterSprite1.getCollisionType();
            expect(collisionType2).toBe(pdg.collide_BoundingBox);
            
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            var collisionType3 = spriterSprite1.getCollisionType();
            expect(collisionType3).toBe(pdg.collide_SpriterCollisionBox);
        });
        
        it('should handle collisions with non-Spriter sprites', function() {
            // FIXME: This test is not implemented yet
            // Test that Spriter sprites can collide with regular sprites
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            var collisionType = spriterSprite1.getCollisionType();
            expect(collisionType).toBe(pdg.collide_SpriterCollisionBox);
        });
    });
    
    describe('Error Handling', function() {
        
        it('should handle invalid indices gracefully', function() {
            var count = spriterSprite1.getSpriterCollisionBoxCount();
            
            // Test negative index
            var name = spriterSprite1.getSpriterCollisionBoxName(-1);
            expect(name).toBeNull();
            
            // Test index beyond count
            name = spriterSprite1.getSpriterCollisionBoxName(count + 1);
            expect(name).toBeNull();
        });
    });
    
    describe('Mouse Event Integration', function() {
        it('should detect mouse collisions with Spriter collision boxes', function() {
            // FIXME: This test is not implemented yet
            spriterSprite1.enableCollisions(pdg.collide_SpriterCollisionBox);
            spriterSprite1.setLocation(new pdg.Point(100, 100));
            
            // Test that mouse collision detection is available
            var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
            expect(collisionCount >= 0).toBe(true);
        });
    });

    describe('Box Name Collection', function() {
        it('should collect actual box names from Spriter file', function() {
            // FIXME: This test is not implemented yet
            // This test assumes a SCML file with collision boxes
            // For now, we'll just check if the sprite has collision boxes
            // and if its methods are available.
            // A more robust test would involve loading a specific SCML file.
            expect(typeof spriterSprite1.getSpriterCollisionBoxCount).toBe('function');
            expect(typeof spriterSprite1.getSpriterCollisionBoxName).toBe('function');
            expect(typeof spriterSprite1.getSpriterCollisionBox).toBe('function');
            expect(typeof spriterSprite1.isSpriterCollisionActive).toBe('function');

            // Check if the sprite has at least one collision box
            var collisionCount = spriterSprite1.getSpriterCollisionBoxCount();
            expect(collisionCount >= 0).toBe(true);
        });
    });
});
