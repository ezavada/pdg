// -----------------------------------------------
// Simple.js
//
// Written by Ed Zavada, 2012
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

var pdg = require('pdg');
var path = require('path');

var drawBalls = false;
var drawSpinner = false;
var drawWalkingHero = false;
var drawStandingHero = true;
var drawGlobe = false;

var gBackgroundColor = new Color("white");  // was teal

var kWindowWidth  = 800;
var kWindowHeight =  600;
var kFullscreen   = (global.process.ios) ? true : false;

var kNumSprites         = 20; 
var kMaxSpriteMoveDelta =  300;

// see if we were launched from the pdg/test directory or the pdg directory
// this is mainly necessary because of the multiple locations we can be launched
// from when we are in a C++ debugger verses launching from the command line
var launchedFromTest = /[\/\\]test$/.test(global.process.cwd());
var testDir = launchedFromTest ? "" : "test/";

// samples directory doesn't need to be adjusted the same way because relative paths
// are considered to be relative to the Application Directory
var samplesDir = "../"; //launchedFromTest ? "../../" : "../";
if (global.process.ios) {
	testDir = "";  // doesn't have test directory
	samplesDir = process.cwd();
}
samplesDir += "deps/scml-pp/samples/";

var gSpriteFilename = testDir + "yinyang.png";
var gEarthFilename = testDir + "earthmap2.png";
var gHeroFilename = samplesDir + "hero/Hero.SCML";
var gHeroFilename = samplesDir + "wonkyskeleton/wonkyskeleton.scml";
//var gHeroFilename = samplesDir + "greyguy/player.scml";
//var gHeroFilename = samplesDir + "simple/simple.scml";
var gStepFilename = "step.wav";
var gClink1Filename = "clink1.mp3";
var gClink2Filename = "clink2.mp3";
var gHitFilename = "hit.wav";
var gMusicFilename = "Peppy_The-Firing-Squad_YMXB.mp3";

var gCollisions = true;


var gPort;
var gSpriteLayer;
var gMasterBallSprite;
var gBallImage;
var gEarthImage;

var gCollisionCount = 0;

var gStartingMs = 0;

var gMusic = 0;
var gClink1;
var gClink2;

///--------------------------------------------------------------------------------------
// main
///--------------------------------------------------------------------------------------



function main()
{
	console.log("in test/main.js main()");
	console.log("argv[0]: " + global.process.argv[0]);
	console.log("cwd: " + global.process.cwd());
 	var logMgr = pdg.getLogManager();
 	logMgr.setLogLevel(10);
// 	logMgr.initialize("simple", logMgr.init_OverwriteExisting);

    Randomize();
    
    SetUpSpriteWorld();
    
    AddSprites();
    
//    pdg.startRepl();	// go into interactive mode
    
    RunAnimation();
    
    pdg.onShutdown( CleanUp );
//	pdg.on(pdg.eventType_Sound, function(evt) { return true; });

}

///--------------------------------------------------------------------------------------
//  Randomize
///--------------------------------------------------------------------------------------

function Randomize() {
	console.log("in Randomize()");
	pdg.srand( pdg.tm.getMilliseconds() );
}

///--------------------------------------------------------------------------------------
//  SetUpSpriteWorld
///--------------------------------------------------------------------------------------

function SetUpSpriteWorld() {
	console.log("in SetupSpriteWorld()");

        // Create the SpriteWorld
    pdg.gfx.setTargetFPS(50.0);
    var r = new Rect(kWindowWidth, kWindowHeight);
    if (kFullscreen) {
//    	console.log(pdg.gfx.getCurrentScreenMode(0));
//    	pdg.gfx.setScreenMode(0, kWindowWidth, kWindowHeight, 32);
        console.log("  creating full screen port "+r);
		gPort = pdg.gfx.createFullScreenPort(r);
	} else {
        console.log("  creating window port "+r);
		gPort = pdg.gfx.createWindowPort(r, "PDG Simple Sprite Test");
	}

        // Create the Sprite Layers
	console.log("  creating spritelayer");
	gSpriteLayer = pdg.createSpriteLayer(gPort);
	gSpriteLayer.setUseChipmunkPhysics();
	gSpriteLayer.zoomTo(0.25, 10000);
    
    	// Set the background color
	console.log("  setup spritelayer erase callback");
    gSpriteLayer.onErasePort( function(evt) {
 		var portRect = gPort.getDrawingArea();
		gPort.fillRect( portRect, gBackgroundColor );
        var loc = portRect.centerPoint();
        if (!gStartingMs) gStartingMs = evt.millisec;
        var t = (evt.millisec - gStartingMs);
        var rotation = t / 5000;
        var scale = t/10;
        if (scale > 400.0) scale = 400;
        if (drawGlobe) {
        	gPort.drawTexturedSphere( gEarthImage, loc, scale, rotation);
    	}
		var fps = "FPS: " + pdg.gfx.getFPS() + ".0";
		var where = new Point(10, kWindowHeight - 20);
		gPort.drawText( fps.substring(0,9), where, 14, 0, "white");
		return true; // completely handled
	});

	console.log("  creating ball image");
	gBallImage = new pdg.Image(gSpriteFilename);
    gEarthImage = new pdg.Image(gEarthFilename);
}

// a helper object that keeps an animated object within bounds and causes it to 
// bounce if it goes out of bounds
var BoundsHelper = new pdg.IAnimationHelper( function(what, msElapsed) {
	var boundsRect = gPort.getDrawingArea();
	boundsRect.scale(4.0);
	var spriteRect = what.getBoundingBox();
	var moveVector = what.getVelocity();
	if (boundsRect.right < spriteRect.right && moveVector.x > 0) {
		// reverse direction of horizontal movement
		moveVector.x = -moveVector.x;
		what.setVelocity(moveVector);
	} else if (boundsRect.left > spriteRect.left && moveVector.x < 0) {
		// reverse direction of horizontal movement
		moveVector = what.getVelocity();
		moveVector.x = -moveVector.x;
		what.setVelocity(moveVector);
	}
	if (boundsRect.bottom < spriteRect.bottom && moveVector.y > 0) {
		// reverse direction of vertical movement
		moveVector = what.getVelocity();
		moveVector.y = -moveVector.y;
		what.setVelocity(moveVector);
	} else if (boundsRect.top > spriteRect.top && moveVector.y < 0) {
		// reverse direction of vertical movement
		moveVector = what.getVelocity();
		moveVector.y = -moveVector.y;
		what.setVelocity(moveVector);
	}
	return true; // keep helping
});

var echoed = false;

function BallCollideFunc(evt) {
	if (evt.arbiter && evt.arbiter.isFirstContact()) {
		if (!echoed) {
			console.log(evt);
			echoed = true;
		}
		var xloc = evt.inLayer.layerToPortPoint(evt.actingSprite.getLocation()).x;
		var xoffset = xloc - gPort.getDrawingArea().width()/2;
		gCollisionCount++;
		keVol = evt.kineticEnergy / 100000;
		if (keVol >= 0.01) {
			if (gCollisionCount % 2 == 1) {
				gClink1.play(keVol/4, xoffset);
			} else {
				gClink2.play(keVol/4, xoffset);
			}
		}
	}
	return true;
}

function WallCollideFunc(evt) {
	return true;
}

///--------------------------------------------------------------------------------------
//  CreateBallSprite - load the master ball sprite and prepare it for cloning later
///--------------------------------------------------------------------------------------

function CreateBallSprite() {
	var ballSprite = gSpriteLayer.createSprite();
	ballSprite.addFramesImage(gBallImage);
	ballSprite.setSize(gBallImage.getWidth(), gBallImage.getHeight());
	var ballRadius = gBallImage.getWidth()/2;
 	ballSprite.setCollisionRadius( ballRadius );

	ballSprite.onCollideSprite(BallCollideFunc);
// 	ballSprite.onCollideWall(WallCollideFunc);

	ballSprite.addAnimationHelper(BoundsHelper);

	return ballSprite;
}


///--------------------------------------------------------------------------------------
//  AddSprites - clone the master sprite, and add the clones to the SpriteWorld
///--------------------------------------------------------------------------------------

function AddSprites() {
	console.log("in AddSprites()");
    var   newSprite;

	if (drawBalls) {
		for (spriteNum = 0; spriteNum < kNumSprites; spriteNum++) {
			newSprite = CreateBallSprite();
			newSprite.id = spriteNum;
			var screenCenter = gPort.getDrawingArea().scale(4.0).centerPoint();
			var max_x = screenCenter.x - gBallImage.getWidth()/2;
			var max_y = screenCenter.y - gBallImage.getHeight()/2;
			var loc = new pdg.Point((pdg.rand() % max_x * 2), pdg.rand() % max_y * 2);
			newSprite.setLocation(loc);

			if (gCollisions) {
				newSprite.enableCollisions();
			} else {
				newSprite.disableCollisions();
			}

			do {	// make sure we get movement in both axis
				var v = new Vector(pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta, pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta);
				newSprite.setVelocity(v);
			} while (v.x == 0 || v.y == 0);
		}
    }
    
	if (drawSpinner) {
		newSprite = CreateBallSprite();
		newSprite.setLocation(gPort.getDrawingArea().centerPoint());
		newSprite.grow(2.0);
		newSprite.setMass(10);
	
		var myHelper = new pdg.ISpriteDrawHelper(function(sprite, port) {
			var bounds = sprite.getRotatedBounds();
			var r = sprite.getLayer().layerToPortRect(bounds);
			port.fillRect(r, "black");
			port.frameRect(r, "white");
			return false; // don't let sprite draw itself (ignored for post draw)
		});
		newSprite.setVelocity([10, 10]);
		if (gCollisions) {
			newSprite.enableCollisions(pdg.collide_BoundingBox);
		} else {
			newSprite.disableCollisions();
		}
		newSprite.applyTorque(5000.0);
		newSprite.setDrawHelper(myHelper);
	}

	if (drawWalkingHero) {
		console.log("AddSprites: createSpriteFromSCMLFile ["+gHeroFilename+"]");
		newSprite = gSpriteLayer.createSpriteFromSCMLFile(gHeroFilename);
		if (newSprite) {
			newSprite.setLocation(new pdg.Point(200,600) );
			newSprite.setEntityScale(4.0, 4.0);
			if (newSprite.hasAnimation('walk')) {
				console.log("sprite has walk animation");
				newSprite.startAnimation('walk');
			}
		}
	}

	if (drawStandingHero) {
		console.log("AddSprites: createSpriteFromSCMLFile ["+gHeroFilename+"]");
		newSprite = gSpriteLayer.createSpriteFromSCMLFile(gHeroFilename);
		if (newSprite) {
			newSprite.setLocation(new pdg.Point(800,1200) );
			newSprite.setEntityScale(4.0, 4.0);
			if (newSprite.hasAnimation('Idle')) {
				console.log("sprite has Idle animation");
				newSprite.startAnimation('Idle');
			}
		}
	}
}


///--------------------------------------------------------------------------------------
//  RunAnimation
///--------------------------------------------------------------------------------------

function RunAnimation() {
	console.log("in RunAnimation()");
	gMusic = new pdg.Sound(gMusicFilename);
	gMusic.setVolume(0.3);
	gMusic.start();
	gClink1 = new pdg.Sound(gClink1Filename);
	gClink2 = new pdg.Sound(gClink2Filename);
	pdg.run();
}


///--------------------------------------------------------------------------------------
//  CleanUp - This function is not really necessary, since the system will dispose
//  everything automatically when the program quits.
///--------------------------------------------------------------------------------------

function CleanUp() {
	
    pdg.cleanupSpriteLayer(gSpriteLayer);

        // Dispose the master sprite, since it isn't included in the SpriteWorld
//     SWDisposeSprite(&gMasterBallSpriteP);
// 
//         // Dispose the SpriteWorld, including all sprites and layers currently in it
//     SWDisposeSpriteWorld(&gSpriteWorldP);
//     SWExitSpriteWorld();

    return true;
}

    
main();
