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

  it("can be created by pdg", function() {
	console.log('* Testing Sprite...');
  	var layer = pdg.createSpriteLayer();
	expect(layer).toBeDefined();
	var sprite = layer.createSprite();
	expect(sprite).toBeDefined();
	pdg.cleanupSpriteLayer(layer);
//	console.dump(sprite);
  });

  describe("can move", function() {

	var layer;
	var sprite;
	
    beforeEach(function() {
      layer = pdg.createSpriteLayer();
	  sprite = layer.createSprite();
    });
    
    afterEach(function() {
		pdg.cleanupSpriteLayer(layer);
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
		waitsFor(function() {
			return (sprite.getLocation().x >= 200);
		}, "enough time to pass", 110);
		runs(function() {
			loc = sprite.getLocation();
			expect(loc.x).not.toBe(0);
			expect(loc.y).not.toBe(0);
			expect(loc.x).toBe(200);
			expect(loc.y).toBe(200);
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
	var msTarget;
	var msAllowed;
	
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
	  	gotCollide = true;
	  	collide1 = true;
// 	  	console.log("COLLIDE 1");
// 	  	console.log(evt);
	  	return true;
	  });
	  sprite1.setSize(20, 20);
	  sprite1.moveTo(0, 100);
	  sprite1.setElasticity(0.8);
	  // init sprite 2
	  sprite2 = layer.createSprite();
	  sprite2.onCollideSprite(function(evt) {
	  	gotCollide = true;
	  	collide2 = true;
// 	  	console.log("COLLIDE 2");
// 	  	console.log(evt);
	  	return true;
	  });
	  sprite2.setSize(20, 20);
	  sprite2.moveTo(0, -100);
	  sprite2.setElasticity(0.8);
	  sprite1.setVelocity(0, -200);  // sprite 1 moves up 2 pixels/ms
	  sprite2.setVelocity(0, 200);  // sprite 2 moves down 2 pixels/ms
    });

    afterEach(function() {
		pdg.cleanupSpriteLayer(layer);
    });

	  it("by moving through one another without colliding", function() {
	    msAllowed = 1110;
	    runs(function() {
	  	  msTarget = pdg.tm.getMilliseconds() + msAllowed;
//	  	  console.time("time for animation");
	    });
		waitsFor(function() {
			return (pdg.tm.getMilliseconds() > msTarget);
		}, "enough time to pass", msAllowed + 100);
		runs(function() {
//	  	    console.timeEnd("time for animation");
			loc = sprite1.getLocation();
			expect(loc.y).not.toBe(0);
			expect(loc.y).toBeLessThan(-99);
			loc = sprite2.getLocation();
			expect(loc.y).not.toBe(0);
			expect(loc.y).toBeGreaterThan(99);
			// check that velocity is unchanged
			vel = sprite1.getVelocity();
			expect(vel.y).toBe(-200);
			vel = sprite2.getVelocity();
			expect(vel.y).toBe(200);
		});
 	  });

	  it("by colliding", function() {
	    msAllowed = 1110;
	    sprite1.enableCollisions(pdg.collide_BoundingBox);
	    sprite2.enableCollisions(pdg.collide_BoundingBox);
	    runs(function() {
	  	  msTarget = pdg.tm.getMilliseconds() + msAllowed;
//	  	  console.time("time for animation");
	    });
		waitsFor(function() {
//			console.log(pdg.tm.getMilliseconds());
			return (pdg.tm.getMilliseconds() > msTarget);
		}, "enough time to pass", msAllowed + 100);
		runs(function() {
//	  	    console.timeEnd("time for animation");
			loc = sprite1.getLocation();
			expect(loc.y).not.toBe(0);
			expect(loc.y).toBeGreaterThan(50);
			loc = sprite2.getLocation();
			expect(loc.y).not.toBe(0);
			expect(loc.y).toBeLessThan(-50);
			vel = sprite1.getVelocity();
			// check that velocity is changed, at least 50% original velocity in opposite direction
			vel = sprite1.getVelocity();
			expect(vel.y).toBeGreaterThan(-200 * -0.5);
			vel = sprite2.getVelocity();
			expect(vel.y).toBeLessThan(200 * -0.5);
		});
 	  });
	
  });

  describe("can interact with layer boundaries", function() {

	var layer;
	var sprite1;
	var gotCollide;
	var gotExitLayer;
	var msTarget;
	var msAllowed;
	
    beforeEach(function() {
	  gotCollide = false;
	  gotExitLayer = false;
      layer = pdg.createSpriteLayer();
      layer.setSize(100, 100);
	  // init sprite 1
	  sprite1 = layer.createSprite();
	  sprite1.onCollideWall(function(evt) {
	  	gotCollide = true;
// 	  	console.log("COLLIDE 1");
// 	  	console.log(evt);
	  	return true;
	  });
	  sprite1.onExitLayer(function(evt) {
	  	gotExitLayer = true;
// 	  	console.log("EXIT LAYER 1");
// 	  	console.log(evt);
	  	return true;
	  });
	  sprite1.setSize(20, 20).moveTo(0, 0);
	  sprite1.setVelocity(-2000, 0);  // sprite 1 moves left 2 pixels/ms
//	  console.log('Sprite 1 reset');
    });

    afterEach(function() {
		pdg.cleanupSpriteLayer(layer);
    });

	  it("by moving out of bounds without getting events", function() {
	    msAllowed = 100;
	    runs(function() {
	  	  msTarget = pdg.tm.getMilliseconds() + msAllowed;
//	  	  console.time("time for animation");
	    });
		waitsFor(function() {
			var ms = pdg.tm.getMilliseconds();
			var loc = sprite1.getLocation();
			var vel = sprite1.getVelocity();
//			console.log(loc + ' @ ' + ms + ' - ' + vel);
			return (ms > msTarget);
		}, "enough time to pass", msAllowed + 100);
		runs(function() {
//	  	    console.timeEnd("time for animation");
			var loc = sprite1.getLocation();
			expect(loc.x).not.toEqual(0);
			expect(loc.x).toBeLessThan(-70);
			expect(loc.y).toEqual(0);
			expect(gotCollide).toBeFalsy();
			expect(gotExitLayer).toBeFalsy();
		});
 	  });
	
	if (pdg.hasGraphics) {
	  it("by getting boundary events", function() {
	    msAllowed = 100;
	    sprite1.setWantsCollideWallEvents(true).setWantsOffscreenEvents(true);
	    runs(function() {
	  	  msTarget = pdg.tm.getMilliseconds() + msAllowed;
//	  	  console.time("time for animation");
	    });
		waitsFor(function() {
			var ms = pdg.tm.getMilliseconds();
			var loc = sprite1.getLocation();
			var vel = sprite1.getVelocity();
//			console.log(loc + ' @ ' + ms + ' - ' + vel);
			return (ms > msTarget);
		}, "enough time to pass", msAllowed + 100);
		runs(function() {
//	  	    console.timeEnd("time for animation");
			var loc = sprite1.getLocation();
			expect(loc.x).not.toEqual(0);
			expect(loc.x).toBeLessThan(-70);
			expect(loc.y).toEqual(0);
			expect(gotCollide).toBeTruthy();
			expect(gotExitLayer).toBeTruthy();
		});
 	  });
	}  // end hasGraphics


  });

});