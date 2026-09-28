// -----------------------------------------------
// spriter_collisions.spec.js
//
// test suite for Spriter Collision Box functionality
//
// Tests authored box queries and the shared animation collider source
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
    
    var spriteLayer;
    var spriterSprite1;
    var spriterSprite2;
    var regularSprite;

    beforeEach(function() {
        // These API tests do not require a dedicated graphics port.
        spriteLayer = pdg.createSpriteLayer();
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
        if (spriteLayer) {
            pdg.cleanupLayer(spriteLayer);
            spriteLayer = null;
        }
        spriterSprite1 = null;
        spriterSprite2 = null;
        regularSprite = null;
    });
    
    describe('Shared Collider artwork adapters', function() {
        it('uses the same read-only collider association and preserves configuration', function() {
            const c=spriterSprite1.setupCollider().setSensor(true).setGroup(17);
            expect(spriterSprite1.setupAnimationCollider()).toBe(c);
            expect(c.getGeometrySource()).toBe(pdg.colliderSource_Animation);
            expect(c.isSensor()).toBe(true);expect(c.getGroup()).toBe(17);
        });
        it('rejects an animation source on a frame-only Sprite without creating a collider', function() {
            expect(()=>regularSprite.setupAnimationCollider()).toThrow();
            expect(regularSprite.collider).toBe(pdg.Collider.NoCollider);
        });
        it('retains additive geometry and source IDs as animation advances', function() {
            const sprite=spriteLayer.createSpriteFromSpriterFile(process.cwd()+'/data/spriter-regression/arm.scml');
            sprite.pauseAnimation();expect(sprite.enableAnimationPose('reference')).toBe(true);
            const c=sprite.setupAnimationCollider();
            expect(c.getShapeCount()).toBe(1);
            const source=c.getShapeId(0), before=c.getBounds();
            expect(c.getShapeName(source)).toBe('hitbox');
            const id=c.addCircle(3,new pdg.Point(1000,0));
            sprite.seekAnimation('reach',.25);
            expect(c.getGeometrySource()).toBe(pdg.colliderSource_Animation);
            expect(c.getCircleRadius(id)).toBe(3);
            expect(c.getShapeCount()).toBe(2);expect(c.getShapeId(0)).toBe(source);
            expect(()=>c.removeShape(source)).toThrow();
            expect(c.removeShape(id)).toBe(true);
            const after=c.getBounds();
            expect(Math.abs(after.left-before.left)+Math.abs(after.top-before.top)).toBeGreaterThan(1);
            const center=sprite.getSpriterCollisionBox('hitbox').getQuad().centerPoint();
            expect(c.contains(center)).toBe(true);
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
                    expect(typeof box.centerPoint).toBe('function');
                    expect(typeof box.width).toBe('function');
                    expect(typeof box.height).toBe('function');
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
    
    it('queries authored box geometry and keeps manual additions through source changes in pose', function() {
        const c=spriterSprite1.setupAnimationCollider();
        const id=c.addBox(new pdg.Rect(2000,2000,2004,2004));
        expect(c.getShapeType(id)).toBe(pdg.collisionShape_Convex);
        spriterSprite1.setLocation(20,30);
        expect(c.getGeometrySource()).toBe(pdg.colliderSource_Animation);
        expect(c.removeShape(id)).toBe(true);
        c.setCircle(2);
        expect(c.getGeometrySource()).toBe(pdg.colliderSource_Explicit);
        expect(c.getShapeCount()).toBe(1);
        expect(c.contains(new pdg.Point(20,30))).toBe(true);
    });
});
