// -----------------------------------------------
// spritelayer.spec.js
//
// test suite for SpriteLayer
//
// Written by Ed Zavada, 2014
// Copyright (c) 2014, Dream Rock Studios, LLC
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

describe("SpriteLayer", function() {

  if (pdg.hasGraphics) {
    it("zooms and converts layer coordinates through the public view API", function() {
      var layer = pdg.createSpriteLayer();
      try {
        layer.setZoom(2);
        expect(layer.getZoom()).toBe(2);
        ['Point', 'Offset', 'Vector'].forEach(function(kind) {
          var projected = layer['layerToPort' + kind](new pdg[kind](3, 5));
          expect(projected instanceof pdg[kind]).toBe(true);
          expect(projected.x).toBeCloseTo(6, 5);
          expect(projected.y).toBeCloseTo(10, 5);
          var restored = layer['portToLayer' + kind](projected);
          expect(restored.x).toBeCloseTo(3, 5);
          expect(restored.y).toBeCloseTo(5, 5);
        });
        var rect = new pdg.RotatedRect(new pdg.Rect(1, 2, 3, 4), .2, new pdg.Offset(.5, .75));
        var restored = layer.portToLayerRect(layer.layerToPortRect(rect));
        expect(restored instanceof pdg.RotatedRect).toBe(true);
        ['left', 'top', 'right', 'bottom', 'radians'].forEach(function(key) {
          expect(restored[key]).toBeCloseTo(rect[key], 5);
        });
        expect(restored.centerOffset.x).toBeCloseTo(.5, 5);
        expect(restored.centerOffset.y).toBeCloseTo(.75, 5);
        expect(layer.zoomTo(4, .1, pdg.linearTween, new pdg.Rect(0, 0), new pdg.Point(0, 0))).toBe(layer);
        layer.animate(.1);
        expect(layer.getZoom()).toBeCloseTo(4, 5);
        expect(layer.zoom(.5, .1)).toBe(layer);
        layer.animate(.1);
        expect(layer.getZoom()).toBeCloseTo(2, 5);
      } finally {
        pdg.cleanupLayer(layer);
      }
    });
  }


  it("exists", function() {
	console.log('* Testing SpriteLayer...');
	expect(pdg.SpriteLayer).toBeDefined();
  });

  it("can create sprites", function() {
    var layer = pdg.createSpriteLayer();
	expect(pdg.SpriteLayer).toBeDefined();
    var sprite1 = layer.createSprite();
    var sprite2 = layer.createSprite();
	expect(sprite1).toBeDefined();
	expect(sprite2).toBeDefined();
	expect(sprite1).not.toBe(sprite2);
	pdg.cleanupLayer(layer);
  });

  it("can iterate through sprites", function() {
      layer = pdg.createSpriteLayer();
      for (var i = 0; i<10; i++) {
        var sprite = layer.createSprite();
      	sprite.id = i + 1;
      	sprite.setLocation([0, i * 10]);
      }
      for (var i = 0; i<10; i++) {
      	var sprite = layer.getNthSprite(i);
  		expect(sprite).toBeDefined();
  		expect(sprite.id).toEqual(i+1);
  		var p = new Point(0, i*10);
  		var same = sprite.getLocation().equals(p);
  		expect(same).toBeTruthy();
  	  }
	  pdg.cleanupLayer(layer);
  });

  describe("can serialize and deserialize position micro updates", function() {

	var layer;
	var buffer;

    beforeEach(function() {
    });

    afterEach(function() {
    });

  	it("by writing to a stream", function() {
	    layer = pdg.createSpriteLayer();
	    for (var i = 0; i<10; i++) {
		  var sprite = layer.createSprite();
		  sprite.id = i + 1;
		  sprite.setLocation([0, i * 10]);
	    }
  		layer.setSerializationFlags(pdg.ser_Micro);
  		var ser = new pdg.Serializer();
  		var size = layer.getSerializedSize(ser);
  		layer.serialize(ser);
  		buffer = ser.getDataPtr();
  		expect(buffer.getDataSize()).toEqual(size);
        // Z-order uses variable-length internal IDs; their width depends on how
        // many Sprites earlier suites created. Check the fixed position payload
        // separately, keeping the full micro stream for the round-trip below.
        layer.setSerializationFlags(pdg.ser_Positions);
        var positions = new pdg.Serializer();
        layer.serialize(positions);
        expect(positions.getDataSize()).toEqual(93); // 9 bytes per Sprite + 3-byte header
        layer.setSerializationFlags(pdg.ser_Micro);
		console.log('Micro Stream Out:');
		console.binaryDump(buffer.getData(), buffer.getDataSize(), 16);
  	});

  	it("by reading from a stream", function() {
      for (var i = 0; i<10; i++) {
        var sprite = layer.getNthSprite(i);
      	sprite.setLocation([ i * 10, 200]);
      }
	  console.log('Micro Stream In:');
	  console.binaryDump(buffer.getData(), buffer.getDataSize(), 16);
 	  var des = new pdg.Deserializer();
 	  des.setDataPtr(buffer);
      layer.deserialize(des);
      for (var i = 0; i<10; i++) {
      	var sprite = layer.getNthSprite(i);
  		expect(sprite).toBeDefined();
  		expect(sprite.id).toEqual(i+1);
  		var p = new Point(0, i*10);
  		var same = sprite.getLocation().equals(p);
  		expect(same).toBeTruthy();
  	  }
	  pdg.cleanupLayer(layer);
  	});

  }); // end micro updates


  describe("can serialize and deserialize normal layer updates", function() {

	var layer;
	var buffer;

    beforeEach(function() {
    });

    afterEach(function() {
    });

  	it("by writing to a stream", function() {
	    layer = pdg.createSpriteLayer();
	    for (var i = 0; i<10; i++) {
		  var sprite = layer.createSprite();
		  sprite.id = i + 1;
		  sprite.setLocation([0, i * 10]);
		  sprite.moveTo(100, i*10, 0.1);
		  sprite.wait(0.15).rotateBy(Math.PI, 0.05);
	    }
  		layer.setSerializationFlags(pdg.ser_Update);
  		var ser = new pdg.Serializer();
  		var size = layer.getSerializedSize(ser);
  		layer.serialize(ser);
		// Internal Sprite IDs use variable-length encoding, so their Z-order
		// bytes depend on how many Sprites earlier specs created. Check the
		// fixed payload independently; the full stream still includes IDs.
		layer.setSerializationFlags(pdg.ser_Update & ~pdg.ser_ZOrder);
		expect(layer.getSerializedSize(new pdg.Serializer())).toEqual(1066);
		layer.setSerializationFlags(pdg.ser_Update);
  		buffer = ser.getDataPtr();
  		expect(buffer.getDataSize()).toEqual(size + 3);  // + 3 bytes for stream header
		console.log('Update Stream Out: '+buffer.getDataSize()+' bytes');
		console.binaryDump(buffer.getData(), buffer.getDataSize(), 16);
  	});

  	it("by reading from a stream", function() {
	  for (var i = 0; i<10; i++) {
		var sprite = layer.getNthSprite(i);
		sprite.setLocation([ i * 10, 200]);
	  }
	  console.log('Update Stream In:');
	  console.binaryDump(buffer.getData(), buffer.getDataSize(), 16);
	  var des = new pdg.Deserializer();
	  des.setDataPtr(buffer);
	  layer.deserialize(des);
	  for (var i = 0; i<10; i++) {
		var sprite = layer.getNthSprite(i);
		expect(sprite).toBeDefined();
		expect(sprite.id).toEqual(i+1);
		var p = new Point(0, i*10);
		var same = sprite.getLocation().equals(p);
		expect(same).toBeTruthy();
		var r = sprite.getRotation();
		expect(r).toEqual(0);
	  }
	  msAllowed = 300;
	  msTarget = pdg.tm.getMilliseconds() + msAllowed;
//      console.time("time for animation");
	  waitsFor(function() {
		return (pdg.tm.getMilliseconds() > msTarget);
	  }, "enough time to pass", msAllowed + 100);
	  runs(function() {
//	  	console.timeEnd("time for animation");
		for (var i = 0; i<10; i++) {
			var sprite = layer.getNthSprite(i);
			expect(sprite).toBeDefined();
			expect(sprite.id).toEqual(i+1);
			var p = new Point(100, i*10);
			var same = sprite.getLocation().equals(p);
			expect(same).toBeTruthy();
			var r = sprite.getRotation();
			expect(r).toBeCloseTo(Math.PI);
		}
	  	pdg.cleanupLayer(layer);
      });
  	});

  });  // end normal updates

  describe("convenience event methods", function() {
    
    var layer;
    
    beforeEach(function() {
      layer = pdg.createSpriteLayer();
    });
    
    afterEach(function() {
      pdg.cleanupLayer(layer);
    });

    it("should have all expected convenience methods available", function() {
      // Test that all the convenience methods exist
      expect(typeof layer.onCollideSprite).toBe('function');
      expect(typeof layer.onCollideWall).toBe('function');
      expect(typeof layer.onOffscreen).toBe('function');
      expect(typeof layer.onOnscreen).toBe('function');
      expect(typeof layer.onExitLayer).toBe('function');
      expect(typeof layer.onAnimationLoop).toBe('function');
      expect(typeof layer.onAnimationEnd).toBe('function');
      expect(typeof layer.onFadeComplete).toBe('function');
      expect(typeof layer.onFadeInComplete).toBe('function');
      expect(typeof layer.onFadeOutComplete).toBe('function');
      expect(typeof layer.onMouseEnter).toBe('function');
      expect(typeof layer.onMouseLeave).toBe('function');
      expect(typeof layer.onMouseDown).toBe('function');
      expect(typeof layer.onMouseUp).toBe('function');
      expect(typeof layer.onMouseClick).toBe('function');
      expect(typeof layer.onErasePort).toBe('function');
      expect(typeof layer.onPreDrawLayer).toBe('function');
      expect(typeof layer.onPostDrawLayer).toBe('function');
      expect(typeof layer.onDrawPortComplete).toBe('function');
      expect(typeof layer.onAnimationStart).toBe('function');
      expect(typeof layer.onPreAnimateLayer).toBe('function');
      expect(typeof layer.onPostAnimateLayer).toBe('function');
      expect(typeof layer.onAnimationComplete).toBe('function');
      expect(typeof layer.onZoomComplete).toBe('function');
      expect(typeof layer.onLayerFadeInComplete).toBe('function');
      expect(typeof layer.onLayerFadeOutComplete).toBe('function');
    });

  });

 
});
