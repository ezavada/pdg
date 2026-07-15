// -----------------------------------------------
// sprite.spec.js
//
// test suite for Sprite
//
// Written by Ed Zavada, 2013
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------

describe("Sprite", function() {

  // Helper function to wait for sprite to reach a target position with tolerance
  function waitForSpritePosition(sprite, targetX, targetY, tolerance, maxWaitTime) {
    tolerance = tolerance || 5; // Default 5 pixel tolerance
    maxWaitTime = maxWaitTime || 2000; // Default 2 second timeout
    
    var startTime = pdg.tm.getMilliseconds();
    var lastX = sprite.getLocation().x;
    var lastY = sprite.getLocation().y;
    var stableCount = 0;
    var requiredStableFrames = 3; // Wait for position to be stable for 3 frames
    
    waitsFor(function() {
      var currentTime = pdg.tm.getMilliseconds();
      var loc = sprite.getLocation();
      var currentX = loc.x;
      var currentY = loc.y;
      
      // Check if we've exceeded max wait time
      if (currentTime - startTime > maxWaitTime) {
        console.log("Timeout waiting for sprite position. Current: (" + currentX + ", " + currentY + "), Target: (" + targetX + ", " + targetY + ")");
        return true; // Force timeout
      }
      
      // Check if position is within tolerance
      var xDiff = Math.abs(currentX - targetX);
      var yDiff = Math.abs(currentY - targetY);
      
      if (xDiff <= tolerance && yDiff <= tolerance) {
        // Check if position has been stable for a few frames
        if (Math.abs(currentX - lastX) < 1 && Math.abs(currentY - lastY) < 1) {
          stableCount++;
          if (stableCount >= requiredStableFrames) {
            return true;
          }
        } else {
          stableCount = 0;
        }
      } else {
        stableCount = 0;
      }
      
      lastX = currentX;
      lastY = currentY;
      
      return false;
    }, "sprite to reach position (" + targetX + ", " + targetY + ") within tolerance " + tolerance, maxWaitTime + 100);
  }

  // Helper function to wait for sprite velocity to change (for collision detection)
  function waitForVelocityChange(sprite, originalVelocity, maxWaitTime) {
    maxWaitTime = maxWaitTime || 2000;
    var startTime = pdg.tm.getMilliseconds();
    var tolerance = 10; // Allow small floating point differences
    
    waitsFor(function() {
      var currentTime = pdg.tm.getMilliseconds();
      var currentVel = sprite.getVelocity();
      
      if (currentTime - startTime > maxWaitTime) {
        console.log("Timeout waiting for velocity change. Original: (" + originalVelocity.x + ", " + originalVelocity.y + "), Current: (" + currentVel.x + ", " + currentVel.y + ")");
        return true; // Force timeout
      }
      
      var xDiff = Math.abs(currentVel.x - originalVelocity.x);
      var yDiff = Math.abs(currentVel.y - originalVelocity.y);
      
      return xDiff > tolerance || yDiff > tolerance;
    }, "sprite velocity to change from (" + originalVelocity.x + ", " + originalVelocity.y + ")", maxWaitTime + 100);
  }

  // Helper function to wait for a condition with better error reporting
  function waitForCondition(conditionFn, description, maxWaitTime) {
    maxWaitTime = maxWaitTime || 2000;
    var startTime = pdg.tm.getMilliseconds();
    
    waitsFor(function() {
      var currentTime = pdg.tm.getMilliseconds();
      
      if (currentTime - startTime > maxWaitTime) {
        console.log("Timeout waiting for condition: " + description);
        return true; // Force timeout
      }
      
      return conditionFn();
    }, description, maxWaitTime + 100);
  }

  it("can be created by pdg", function() {
    console.log('* Testing Sprite...');
    var layer = pdg.createSpriteLayer();
    expect(layer).toBeDefined();
    var sprite = layer.createSprite();
    expect(sprite).toBeDefined();
    pdg.cleanupLayer(layer);
  });

  describe("can move", function() {

    var layer;
    var sprite;
    
    beforeEach(function() {
      layer = pdg.createSpriteLayer();
      sprite = layer.createSprite();
    });
    
    afterEach(function() {
      pdg.cleanupLayer(layer);
    });

    it("starting from initial location of (0,0)", function() {
      var loc = sprite.getLocation();
      expect(loc.x).toBe(0);
      expect(loc.y).toBe(0);		
    });

    it("to a specific location", function() {
      sprite.moveTo(90, -100);
      var loc = sprite.getLocation();
      expect(loc.x).toBe(90);
      expect(loc.y).toBe(-100);		
    });

    it("by offsets", function() {
      sprite.move(20, 20);
      var loc = sprite.getLocation();
      expect(loc.x).toBe(20);
      expect(loc.y).toBe(20);		
      sprite.move(20, -20);
      loc = sprite.getLocation();
      expect(loc.x).toBe(40);
      expect(loc.y).toBe(0);
    });

    it("over time", function() {
      sprite.move(200, 200, 100);
      var loc = sprite.getLocation();
      expect(loc.x).toBe(0);
      expect(loc.y).toBe(0);
      
      // Wait for movement to complete with tolerance
      waitForSpritePosition(sprite, 200, 200, 10, 150);
      
      runs(function() {
        loc = sprite.getLocation();
        expect(loc.x).not.toBe(0);
        expect(loc.y).not.toBe(0);
        expect(loc.x).toBeCloseTo(200, 0); // Allow 1 pixel tolerance
        expect(loc.y).toBeCloseTo(200, 0); // Allow 1 pixel tolerance
      });
    });
  });

  describe("can handle interact with other sprites", function() {

    var layer;
    var sprite1;
    var sprite2;
    var gotCollide;
    var collide1;
    var collide2;
    
    beforeEach(function() {
      gotCollide = false;
      collide1 = false;
      collide2 = false;
      layer = pdg.createSpriteLayer();
      layer.setUseChipmunkPhysics();
      layer.enableCollisions();
      
      // init sprite 1
      sprite1 = layer.createSprite();
      sprite1.onCollideSprite(function(evt) {
        console.log("sprite1.onCollideSprite got collide event (1)");
        gotCollide = true;
        collide1 = true;
        return true;
      });
      sprite1.setSize(20, 20);
      sprite1.moveTo(0, 100);
      sprite1.setElasticity(0.8);
      expect(gotCollide).toBe(false);
      expect(collide1).toBe(false);
      
      // init sprite 2
      sprite2 = layer.createSprite();
      sprite2.onCollideSprite(function(evt) {
        console.log("sprite2.onCollideSprite got collide event (2)");
        gotCollide = true;
        collide2 = true;
        return true;
      });
      sprite2.setSize(20, 20);
      sprite2.moveTo(0, -100);
      sprite2.setElasticity(0.8);
      expect(gotCollide).toBe(false);
      expect(collide2).toBe(false);
      
      sprite1.setVelocity(0, -200);  // sprite 1 moves up
      sprite2.setVelocity(0, 200);   // sprite 2 moves down
    });

    afterEach(function() {
      pdg.cleanupLayer(layer);
    });

    it("by moving through one another without colliding", function() {
      console.log("**moving through");
      var originalVel1 = sprite1.getVelocity();
      var originalVel2 = sprite2.getVelocity();
      
      // Wait for sprites to move past each other
      waitForCondition(function() {
        var loc1 = sprite1.getLocation();
        var loc2 = sprite2.getLocation();
        // Check if sprites have moved significantly in opposite directions
        return loc1.y < 50 && loc2.y > -50;
      }, "sprites to move past each other", 1500);
      
      runs(function() {
        var loc1 = sprite1.getLocation();
        var loc2 = sprite2.getLocation();
        
        // Check that sprites moved in opposite directions
        expect(loc1.y).toBeLessThan(50);
        expect(loc2.y).toBeGreaterThan(-50);
        
        // Check that velocity is unchanged (no collision occurred)
        var vel1 = sprite1.getVelocity();
        var vel2 = sprite2.getVelocity();
        expect(vel1.y).toBeCloseTo(originalVel1.y, 0);
        expect(vel2.y).toBeCloseTo(originalVel2.y, 0);
      });
    });

    it("by colliding", function() {
      console.log("**colliding");
      sprite1.enableCollisions(pdg.collide_BoundingBox);
      sprite2.enableCollisions(pdg.collide_BoundingBox);
      
      var originalVel1 = sprite1.getVelocity();
      var originalVel2 = sprite2.getVelocity();
      
      // Wait for collision to occur and velocity to change
      waitForVelocityChange(sprite1, originalVel1, 1500);
      
      runs(function() {
        var loc1 = sprite1.getLocation();
        var loc2 = sprite2.getLocation();
        
        // Check that sprites are in reasonable positions after collision
        expect(loc1.y).toBeGreaterThan(-100); // Shouldn't have moved too far
        expect(loc2.y).toBeLessThan(100);     // Shouldn't have moved too far
        
        // Check that velocities changed due to collision
        var vel1 = sprite1.getVelocity();
        var vel2 = sprite2.getVelocity();
        
        // Velocities should have changed significantly (at least 25% of original)
        var vel1Changed = Math.abs(vel1.y - originalVel1.y) > Math.abs(originalVel1.y) * 0.25;
        var vel2Changed = Math.abs(vel2.y - originalVel2.y) > Math.abs(originalVel2.y) * 0.25;
        
        expect(vel1Changed || vel2Changed).toBeTruthy();
      });
    });
  });

  describe("can interact with layer boundaries", function() {

    var layer;
    var sprite1;
    var gotCollide;
    var gotExitLayer;
    
    beforeEach(function() {
      gotCollide = false;
      gotExitLayer = false;
      layer = pdg.createSpriteLayer();
      layer.setSize(100, 100);
      
      // init sprite 1
      sprite1 = layer.createSprite();
      sprite1.onCollideWall(function(evt) {
        console.log("got collide wall event");
        gotCollide = true;
        return true;
      });
      sprite1.onExitLayer(function(evt) {
        console.log("got exit layer event");
        gotExitLayer = true;
        return true;
      });
      sprite1.setSize(20, 20).moveTo(0, 0);
      sprite1.setVelocity(-250, 0);  // move slowly enough to trigger wall and exit events on separate frames
    });

    afterEach(function() {
      pdg.cleanupLayer(layer);
    });

    it("by moving out of bounds without getting events", function() {
      console.log("**moving out of bounds");
      // Wait for sprite to move significantly left
      waitForCondition(function() {
        var loc = sprite1.getLocation();
        return loc.x < -50;
      }, "sprite to move out of bounds", 500);
      
      runs(function() {
        var loc = sprite1.getLocation();
        expect(loc.x).toBeLessThan(-50);
        expect(loc.y).toBeCloseTo(0, 0);
        expect(gotCollide).toBeFalsy();
        expect(gotExitLayer).toBeFalsy();
      });
    });
	
    if (pdg.hasGraphics) {
      it("by getting boundary events", function() {
        console.log("**getting boundary events");
        sprite1.setWantsCollideWallEvents(true).setWantsOffscreenEvents(true);

        waitForCondition(function() {
          return gotCollide;
        }, "collide wall event to fire", 1000);

        waitForCondition(function() {
          return gotExitLayer;
        }, "exit layer event to fire", 1500);
        
        runs(function() {
          var loc = sprite1.getLocation();
          expect(loc.x).toBeLessThan(-50);
          expect(loc.y).toBeCloseTo(0, 0);
          expect(gotCollide).toBeTruthy();
          expect(gotExitLayer).toBeTruthy();
        });
      });
    }
  });

  describe("convenience event methods", function() {
    
    var layer;
    var sprite;
    
    beforeEach(function() {
      layer = pdg.createSpriteLayer();
      sprite = layer.createSprite();
    });
    
    afterEach(function() {
      pdg.cleanupLayer(layer);
    });

    it("should have all expected convenience methods available", function() {
      // Test that all the convenience methods exist
      expect(typeof sprite.onCollideSprite).toBe('function');
      expect(typeof sprite.onCollideWall).toBe('function');
      expect(typeof sprite.onOffscreen).toBe('function');
      expect(typeof sprite.onOnscreen).toBe('function');
      expect(typeof sprite.onExitLayer).toBe('function');
      expect(typeof sprite.onAnimationLoop).toBe('function');
      expect(typeof sprite.onAnimationEnd).toBe('function');
      expect(typeof sprite.onFadeComplete).toBe('function');
      expect(typeof sprite.onFadeInComplete).toBe('function');
      expect(typeof sprite.onFadeOutComplete).toBe('function');
      expect(typeof sprite.onMouseEnter).toBe('function');
      expect(typeof sprite.onMouseLeave).toBe('function');
      expect(typeof sprite.onMouseDown).toBe('function');
      expect(typeof sprite.onMouseUp).toBe('function');
      expect(typeof sprite.onMouseClick).toBe('function');
    });

    it("should return handler objects from convenience methods", function() {
      // Test that the convenience methods return handlers
      var handler = sprite.onCollideSprite(function(event) {
        return true;
      });
      expect(handler).toBeDefined();
      expect(typeof handler).toBe('object');
      
      var mouseHandler = sprite.onMouseClick(function(event) {
        return true;
      });
      expect(mouseHandler).toBeDefined();
      expect(typeof mouseHandler).toBe('object');
      
      var fadeHandler = sprite.onFadeComplete(function(event) {
        return true;
      });
      expect(fadeHandler).toBeDefined();
      expect(typeof fadeHandler).toBe('object');
    });
  });
});
