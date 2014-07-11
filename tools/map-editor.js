// -----------------------------------------------
// map-editor.js
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

var pdg = require('pdg');

var pdg_dir = process.env['PDG_ROOT'];
var verbose = (parseInt(process.env['VERBOSE']) == 1);

var mode = pdg.gfx.getCurrentScreenMode();
var gPort = pdg.gfx.createWindowPort(mode.maxWindowRect, "Map Editor");

var gBackgroundLayer = pdg.createTileLayer(gPort);
var gUILayer = pdg.createSpriteLayer(gPort);
var gCheckerboardImage = new pdg.Image("tools/checkerboard.png");
gBackgroundLayer.defineTileSet(72, 72, gCheckerboardImage, false, false);
gBackgroundLayer.setWorldSize(2,2, false, false);
gBackgroundLayer.setTileTypeAt(0,0,0);
gBackgroundLayer.setTileTypeAt(1,0,1);
gBackgroundLayer.setTileTypeAt(0,1,1);
gBackgroundLayer.setTileTypeAt(1,1,0);

var gLayers = [ gBackgroundLayer ];

gBackgroundLayer.onErasePort( function(evt) {
	var r = gPort.getDrawingArea();
	gPort.fillRect(r, "blue");
	var wr = gBackgroundLayer.getWorldBounds();
	wpr = gBackgroundLayer.layerToPortRect(wr);
	gPort.setClipRect(wpr);
	return true;
});

gUILayer.onDrawPortComplete( function(evt) {
	var r = gPort.getDrawingArea();
	gPort.setClipRect(r);
	r.left = r.right - 100;
	gPort.fillRect(r, "white");
	gPort.drawLine(r.leftTop(), r.leftBottom());
	return true;
});

pdg.onKeyPress( function(evt) {
	var chr = String.fromCharCode(evt.unicode);
	var p = gBackgroundLayer.getOrigin();
	if ( (chr == '+') || (chr == '=') ) {
		if (gBackgroundLayer.getZoom() < 32.0) {
			gBackgroundLayer.zoom(2.0, 10);
		}
	} else if (chr == '-') {
		if (gBackgroundLayer.getZoom() > 0.25) {
			gBackgroundLayer.zoom(0.5, 10);
		}
	} else if (evt.unicode == pdg.key_UpArrow) {
		p.y -= (4 * gBackgroundLayer.getZoom());
		gBackgroundLayer.setOrigin(p);
	} else if (evt.unicode == pdg.key_DownArrow) {
		p.y += (4 * gBackgroundLayer.getZoom());
		gBackgroundLayer.setOrigin(p);
	} else if (evt.unicode == pdg.key_LeftArrow) {
		p.x -= (4 * gBackgroundLayer.getZoom());
		gBackgroundLayer.setOrigin(p);
	} else if (evt.unicode == pdg.key_RightArrow) {
		p.x += (4 * gBackgroundLayer.getZoom());
		gBackgroundLayer.setOrigin(p);
	} else {
		console.log(evt);
	}
	return true;
});
pdg.run();

