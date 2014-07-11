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

var kWindowWidth  = 1024;
var kWindowHeight =  768;
var kFullscreen   = false;

var kNumSprites         = 50; 
var kMaxSpriteMoveDelta =  300;

var gSpriteFilename = "yinyang.png";
var gCollisions = true;

var gBackgroundColor = new Color("teal"); 

var gPort;
var gSpriteLayer;
var gMasterBallSprite;
var gBallImage;

var gCollisionCount = 0;

///--------------------------------------------------------------------------------------
// main
///--------------------------------------------------------------------------------------



function main()
{
    console.log("in framework/main.js main()");
    var logMgr = pdg.getLogManager();
    logMgr.setLogLevel(10);
//     logMgr.initialize("simple", logMgr.init_OverwriteExisting);

    Randomize();
    
    SetUpSpriteWorld();
                
    AddSprites();
    
//    pdg.startRepl();    // go into interactive mode
    
    RunAnimation();
    CleanUp();
}

///--------------------------------------------------------------------------------------
//  Randomize
///--------------------------------------------------------------------------------------

function Randomize() {
    pdg.srand( pdg.getTimerManager().getMilliseconds() );
}

///--------------------------------------------------------------------------------------
//  SetUpSpriteWorld
///--------------------------------------------------------------------------------------

function SetUpSpriteWorld() {

    // Create the SpriteWorld
    if (kFullscreen) {
        gPort = pdg.getGraphicsManager().createFullScreenPort(new Rect(kWindowWidth, kWindowHeight));
    } else {
        gPort = pdg.getGraphicsManager().createWindowPort(new Rect(kWindowWidth, kWindowHeight), "PDG Simple Sprite Test");
    }

    // Create the Sprite Layers
    gSpriteLayer = pdg.createSpriteLayer(gPort);
    
    // Set the background color
    gSpriteLayer.onErasePort( function(evt) {
        var portRect = gPort.getDrawingArea();
        gPort.fillRect( portRect, gBackgroundColor );
        return true; // completely handled
    });

    gBallImage = new pdg.Image(gSpriteFilename);
}

// a helper object that keeps an animated object within bounds and causes it to 
// bounce if it goes out of bounds
var BoundsHelper = new pdg.IAnimationHelper( function(what, msElapsed) {
    var boundsRect = gPort.getDrawingArea();
    var spriteRect = what.getBoundingBox();
    var moveVector;
    if (boundsRect.right < spriteRect.right) {
        // reverse direction of horizontal movement
        moveVector = what.getVelocity();
        moveVector.x = -moveVector.x;
        what.setVelocity(moveVector);
    } else if (boundsRect.left > spriteRect.left) {
        // reverse direction of horizontal movement
        moveVector = what.getVelocity();
        moveVector.x = -moveVector.x;
        what.setVelocity(moveVector);
    }
    if (boundsRect.bottom < spriteRect.bottom) {
        // reverse direction of vertical movement
        moveVector = what.getVelocity();
        moveVector.y = -moveVector.y;
        what.setVelocity(moveVector);
    } else if (boundsRect.top > spriteRect.top) {
        // reverse direction of vertical movement
        moveVector = what.getVelocity();
        moveVector.y = -moveVector.y;
        what.setVelocity(moveVector);
    }
    return true; // keep helping
});

function BallCollideFunc(evt) {
//    if (evt.arbiter.isFirstContact()) {
//        console.log("New collision!");
//    }
    gCollisionCount++;
    if (gCollisionCount == 2000) {
//        console.log("2000 collisions, quitting");
//        pdg.quit();
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
//  ballSprite.onCollideWall(WallCollideFunc);

    ballSprite.addAnimationHelper(BoundsHelper);

    return ballSprite;
}


///--------------------------------------------------------------------------------------
//  AddSprites - clone the master sprite, and add the clones to the SpriteWorld
///--------------------------------------------------------------------------------------

function AddSprites() {
    var   newSprite;

    for (spriteNum = 0; spriteNum < kNumSprites; spriteNum++) {
        newSprite = CreateBallSprite();
        newSprite.id = spriteNum;
        var screenCenter = new Rect(gPort.getDrawingArea()).centerPoint();
        var max_x = screenCenter.x - gBallImage.getWidth()/2;
        var max_y = screenCenter.y - gBallImage.getHeight()/2;
        var loc = new pdg.Point(pdg.rand() % max_x + screenCenter.x, pdg.rand() % max_y + screenCenter.y);
        newSprite.setLocation(loc);

        if (gCollisions) {
            newSprite.enableCollisions();
        } else {
            newSprite.disableCollisions();
        }

        do {    // make sure we get movement in both axis
            var v = new Vector(pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta,
                               pdg.rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta);
            newSprite.setVelocity(v);
        } while (v.x == 0 || v.y == 0);
    }
    
    newSprite = CreateBallSprite();
    newSprite.setLocation(new pdg.Rect(gPort.getDrawingArea()).centerPoint());
    
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
    newSprite.applyTorque(100.0);
    newSprite.setDrawHelper(myHelper);

}


///--------------------------------------------------------------------------------------
//  RunAnimation
///--------------------------------------------------------------------------------------

function RunAnimation() { 
    pdg.run();
}


///--------------------------------------------------------------------------------------
//  CleanUp - This function is not really necessary, since the system will dispose
//  everything automatically when the program quits.
///--------------------------------------------------------------------------------------

function CleanUp() {
    
}

    
main();
