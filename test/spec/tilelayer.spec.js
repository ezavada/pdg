// -----------------------------------------------
// tilelayer.spec.js
//
// test suite for TileLayer
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

describe("TileLayer", function() {

  var tl;

  it("exists", function() {
	console.log('* Testing TileLayer...');
	expect(pdg.TileLayer).toBeDefined();
  });

  it("can have a tile set defined", function() {
  	var tiles = new pdg.Image("tiles.png");
  	expect(tiles).toBeDefined();
  	expect(tiles.getWidth()).toBe(512);
  	expect(tiles.getHeight()).toBe(512);
  	tl = pdg.createTileLayer();
  	tl.defineTileSet(64, 64, tiles);
  	var s = tl.getTileSize();
  	expect(s.x).toBe(64);
  	expect(s.y).toBe(64);
  });

  it("can have a world size and data defined", function() {
	tl.setWorldSize(4, 4);
	var r = tl.getWorldSize();
	expect(r.width()).toBe(4);
	expect(r.height()).toBe(4);
	var tileType = [
		59,58,41,13, 
		4,0,0,21, 
		54,0,0,37,
		1,2,10,61
	];
	var tileFacing = [
		pdg.facing_South, pdg.facing_South, pdg.facing_South, pdg.facing_West,
		pdg.facing_East,  pdg.facing_North, pdg.facing_North, pdg.facing_West,
		pdg.facing_East,  pdg.facing_North, pdg.facing_North, pdg.facing_West,
		pdg.facing_North, pdg.facing_North, pdg.facing_North, pdg.facing_North
	];
	for (var y = 0; y<4; y++) {
		for (var x = 0; x<4; x++) {
			tl.setTileTypeAt(x, y, tileType[y*4+x], tileFacing[y*4+x]);
		}
	}
	for (var y = 0; y<4; y++) {
		for (var x = 0; x<4; x++) {
			var expectedTT = tileType[y*4+x];
			var expectedTF = tileFacing[y*4+x];
			var tt = tl.getTileTypeAt(x, y);
			var ttf = tl.getTileTypeAndFacingAt(x, y);
			expect(tt).toEqual(expectedTT + expectedTF);
			expect(ttf.tileType).toEqual(expectedTT);
			expect(ttf.facing).toEqual(expectedTF);
		}
	}
  });

  xit("can draw", function() {
	var gPort = pdg.gfx.createWindowPort([256, 256], "Tile Layer Test");
	tl.setSpritePort(gPort);
	waitsFor(function() {
		return pdg.quitting;
	}, "the window to close", 20000);
	runs(function() {
		pdg.gfx.closeGraphicsPort(gPort);
	});
  });

});
