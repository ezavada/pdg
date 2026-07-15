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

// GC Monitoring
const GCMonitor = require('./test/js/gc-monitor.js');
let gcMonitor = null;

var drawBalls = true;
var drawSpinner = true;
var drawWalkingHero = true;
var drawStandingHero = true;
var drawGlobe = true;
var playMusic = true;
var playSounds = true;

var gBackgroundColor = new pdg.Color("teal");  // was teal

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

// Use absolute path to avoid canonicalization issues
var samplesDir = process.cwd() + "/test/data/spriter-samples/";
if (global.process.ios) {
	testDir = "";  // doesn't have test directory
	samplesDir = process.cwd();
}

var gSpriteFilename = testDir + "yinyang.png";
var gEarthFilename = testDir + "earthmap2.png";
var gHeroFilename = samplesDir + "wonkyskeleton/wonkyskeleton.scml";
var gGreyGuyFilename = samplesDir + "greyguy/player.scml";
var gStepFilename = process.cwd() + "/" + testDir + "step.wav";
var gClink1Filename = process.cwd() + "/" + testDir + "clink1.mp3";
var gClink2Filename = process.cwd() + "/" + testDir + "clink2.mp3";
var gHitFilename = process.cwd() + "/" + testDir + "hit.wav";
var gMusicFilename = process.cwd() + "/" + testDir + "Peppy_The-Firing-Squad_YMXB.mp3";

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

    // Start GC monitoring
    gcMonitor = new GCMonitor({
        logToConsole: true,
        trackMemoryUsage: true,
        trackFrameRate: true,
        gcThreshold: 10, // Log GC events longer than 10ms
		pdg: pdg
    });
    gcMonitor.start();
    console.log("GC monitoring started");

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
    var r = new pdg.Rect(kWindowWidth, kWindowHeight);
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
		//var backgroundAttrs = new pdg.Attributes().fillColor(gBackgroundColor);
		//gPort.drawRect(portRect, backgroundAttrs);
        var loc = portRect.centerPoint();
        if (!gStartingMs) gStartingMs = evt.millisec;
        var t = (evt.millisec - gStartingMs);
        var rotation = t / 5000;
        var scale = t/10;
        if (scale > 400.0) scale = 400;
        if (drawGlobe) {
			var earthAttrs = new pdg.Attributes().sphereRotation(rotation).texture(gEarthImage).lightOffset(new pdg.Offset(1, 0));
			gPort.drawSphere(loc, scale, earthAttrs);
        	//gPort.drawTexturedSphere( gEarthImage, loc, scale, rotation);
    	}
		var fps = "FPS: " + pdg.gfx.getFPS() + ".0";
		var where = new pdg.Point(10, kWindowHeight - 20);
		var fpsAttrs = new pdg.Attributes().textSize(14).fillColor("white");
		gPort.drawText(fps.substring(0,9), where, fpsAttrs);
		
		// Track frame rate for GC monitoring
		if (gcMonitor) {
		    gcMonitor.onFrame();
		}
		
		return true; // completely handled
	});

	console.log("  creating ball image");
	gBallImage = new pdg.Image(gSpriteFilename);
	console.log("  ball image created, size: " + gBallImage.getWidth() + "x" + gBallImage.getHeight());
    console.log("  creating earth image from: " + gEarthFilename);
    gEarthImage = new pdg.Image(gEarthFilename);
    console.log("  earth image created, size: " + gEarthImage.getWidth() + "x" + gEarthImage.getHeight());
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
			console.log("BallCollideFunc");
			console.log(evt);
			echoed = true;
		}
		var xloc = evt.inLayer.layerToPortPoint(evt.actingSprite.getLocation()).x;
		var xoffset = xloc - gPort.getDrawingArea().width()/2;
		gCollisionCount++;
		keVol = evt.kineticEnergy / 100000;
		// Use a much lower threshold or minimum volume for testing
		var soundVol = Math.max(keVol/4, 0.1); // minimum volume of 0.1 for testing
		if (playSounds) {
			if (gCollisionCount % 2 == 1) {
				if (gClink1) gClink1.play(soundVol, xoffset);
			} else {
				if (gClink2) gClink2.play(soundVol, xoffset);
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
    var newSprite;
	var greyGuySprite;

	if (drawBalls) {
		console.log("Creating " + kNumSprites + " ball sprites...");
		for (spriteNum = 0; spriteNum < kNumSprites; spriteNum++) {
			newSprite = CreateBallSprite();
			newSprite.id = spriteNum;
			var screenCenter = gPort.getDrawingArea().scale(4.0).centerPoint();
			var max_x = screenCenter.x - gBallImage.getWidth()/2;
			var max_y = screenCenter.y - gBallImage.getHeight()/2;
			var loc = new pdg.Point((pdg.rand() % max_x * 2), pdg.rand() % max_y * 2);
			newSprite.setLocation(loc);
			console.log("Created ball sprite " + spriteNum + " at position " + loc.x + "," + loc.y);

			if (gCollisions) {
				newSprite.enableCollisions();
			} else {
				newSprite.disableCollisions();
			}

			do {	// make sure we get movement in both axis
				var v = new pdg.Vector(pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta, pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta);
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
			var bounds = sprite.getRotatedBounds(); // this gets a rotated rect: unrotated size plus centerpoint and rotation
			var r = sprite.getLayer().layerToPortRect(bounds);
			var center = sprite.getLayer().layerToPortPoint(bounds.centerPoint());
			var frameAttrs = new pdg.Attributes().lineColor("white").lineThickness(1.0).rotation(bounds.radians, center);
			port.drawRect(r, frameAttrs.fillColor("black"));
			
			// Debug: Draw the actual collision bounds
			if (false && sprite.getCollisionType() == pdg.collide_BoundingBox) {
				var collisionBounds = sprite.getRotatedBounds();
				var collisionRect = sprite.getLayer().layerToPortRect(collisionBounds);
				var collisionFrameAttrs = new pdg.Attributes().lineColor("red").lineThickness(1.0);
				port.drawRect(collisionRect, collisionFrameAttrs);
			}
			
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
		console.log("AddSprites: createSpriteFromSpriterFile ["+gHeroFilename+"]");
		newSprite = gSpriteLayer.createSpriteFromSpriterFile(gHeroFilename);
		if (newSprite) {
			newSprite.setLocation(new pdg.Point(200,600) );
			newSprite.setEntityScale(4.0, 4.0);
			newSprite.enableCollisions(pdg.collide_SpriterCollisionBox);
			if (newSprite.hasAnimation('walk')) {
				console.log("sprite has walk animation");
				newSprite.startAnimation('walk');
			}
			pdg.tm.onInterval(function() {
				newSprite.flipX();
			}, 4000);
		}
	}

	if (drawStandingHero) {
		console.log("AddSprites: createSpriteFromSpriterFile ["+gGreyGuyFilename+"]");
		greyGuySprite = gSpriteLayer.createSpriteFromSpriterFile(gGreyGuyFilename);
		if (greyGuySprite) {
			greyGuySprite.setLocation(new pdg.Point(400,600) );
			greyGuySprite.setEntityScale(4.0, 4.0);
			if (greyGuySprite.hasAnimation('Idle')) {
				console.log("sprite has Idle animation");
				greyGuySprite.startAnimation('Idle');
			}
		}
	}
}


///--------------------------------------------------------------------------------------
//  RunAnimation
///--------------------------------------------------------------------------------------

function RunAnimation() {
	console.log("in RunAnimation()");
	if (playMusic) {
		gMusic = new pdg.Sound(gMusicFilename);
		gMusic.setVolume(0.3);
		gMusic.start();
	}
	if (playSounds) {
		gClink1 = new pdg.Sound(gClink1Filename);
		gClink2 = new pdg.Sound(gClink2Filename);
	}
	pdg.run();
}


///--------------------------------------------------------------------------------------
//  CleanUp - This function is not really necessary, since the system will dispose
//  everything automatically when the program quits.
///--------------------------------------------------------------------------------------

function CleanUp() {
	
    // Stop GC monitoring and print final report
	try {
		if (gcMonitor) {
			console.log("\n=== Final GC Report ===");
			gcMonitor.stop();
			gcMonitor.printReport();
		}
	} catch (e) {
		console.log("No GC report available");
	}
    
    pdg.cleanupLayer(gSpriteLayer);

    return true;
}

    
main();
