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
	  pdg.cleanupSpriteLayer(layer);
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
  		expect(size).toEqual(103); // 10 bytes per sprite for first 254 sprites, + 3 bytes layer overhead
  		buffer = ser.getDataPtr();
  		expect(buffer.getDataSize()).toEqual(size);
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
	  pdg.cleanupSpriteLayer(layer);
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
		  sprite.moveTo(100, i*10, 100);
		  sprite.wait(150).rotate(Math.PI, 50);
	    }
  		layer.setSerializationFlags(pdg.ser_Update);
  		var ser = new pdg.Serializer();
  		var size = layer.getSerializedSize(ser);
  		layer.serialize(ser);
  		expect(size).toEqual(557); // 11 bytes for layer, + data for 10 sprites
  		buffer = ser.getDataPtr();
  		expect(buffer.getDataSize()).toEqual(size);
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
	  	pdg.cleanupSpriteLayer(layer);
      });
  	});

  });  // end normal updates

 
});
