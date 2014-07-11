// -----------------------------------------------
// test.cpp
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
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

#include "pdg_project.h"

#include "test.h"
#include "pdg/framework.h"

#include <string>

MyHandler* gMyHandler;

// =========================  initializers =============================
namespace pdg {

bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool haveMainResourceFile) throw() { return "pdg"; }
const char* Initializer::getMainResourceFileName() throw() {return NULL;}

bool Initializer::installGlobalHandlers() throw() {
    gMyHandler = new MyHandler();
    pdg::EventManager::instance().addHandler(gMyHandler);
    return true;
}

bool Initializer::getGraphicsEnvironmentDimensions(Rect maxWindowDim, Rect maxFullScreenDim,
	long& ioWidth, long& ioHeight, uint8& ioDepth) throw()
{
  ioWidth = 640;
  ioHeight = 480;
  ioDepth = 32;
  return false;
}

} // end namespace pdg


const int  kWindowWidth  = 800;
const int  kWindowHeight =  600;
const bool kFullscreen   = false;

const int  kNumSprites         = 500; 
const int  kMaxSpriteMoveDelta =  300;

const char* gSpriteFilename = "yinyang.png";
const char* gEarthTextureFilename = "earthmap2.jpg";

const bool  gCollisions = true;

pdg::Color gBackgroundColor = PDG_CSS_MAROON_COLOR; 

pdg::Port* gPort;
pdg::SpriteLayer* gSpriteLayer;
pdg::Sprite* gMasterBallSprite;
pdg::Image* gBallImage;
pdg::Image* gEarthTextureImage;

int gCollisionCount = 0;

float gWorldRot = 0.0f;

///--------------------------------------------------------------------------------------
// main
///--------------------------------------------------------------------------------------

bool 
MyHandler::handleEvent(pdg::EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
    if (inEventType == pdg::eventType_Startup) {
        do_Init();
        return true;
    }
    if (inEventType == pdg::eventType_SpriteLayer) {
        pdg::SpriteLayerInfo* sli = static_cast<pdg::SpriteLayerInfo*>(inEventData);
        if (sli->action == pdg::SpriteLayer::action_ErasePort) {
            return do_ErasePort();
        };
    }
    if (inEventType == pdg::eventType_NetConnect) {
        pdg::NetConnect* ni = static_cast<pdg::NetConnect*>(inEventData);
        if (ni->id < 0) {
            // this was a listener
        } else {
            
        }
       
    }
    if (inEventType == pdg::eventType_NetDisconnect) {
        pdg::NetDisconnect* ni = static_cast<pdg::NetDisconnect*>(inEventData);
        if (ni->id < 0) {
            // this was a listener
        } else {
            
        }
        
    }
    if (inEventType == pdg::eventType_NetData) {
        pdg::NetData* ni = static_cast<pdg::NetData*>(inEventData);
        if (ni->id < 0) {
            // this was a listener
        } else {
            
        }
        
    }
    if (inEventType == pdg::eventType_NetError) {
        pdg::NetError* ni = static_cast<pdg::NetError*>(inEventData);
        if (ni->id < 0) {
            // this was a listener
        } else {
            
        }
        
    }
    if (inEventType == pdg::eventType_PortDraw) {
        pdg::Offset lightOffset( (gWorldRot / 365.242)*40.0 + M_PI_2, 0 ); // remove *40.0 for correct day/year ratio
        pdg::Offset polarOffset(0, -23.5*M_PI/180.0 );
        gPort->drawTexturedSphere(gEarthTextureImage, gPort->getDrawingArea().centerPoint(), 300.0f, gWorldRot, polarOffset, lightOffset );
        gWorldRot -= (M_PI/180.0f)/4.0; // rotate counterclockwise
    }
    return false; // we didn't handle this
}

void Randomize();
void SetUpSpriteWorld();
pdg::Sprite&  CreateBallSprite();
void AddSprites();
void RunAnimation();
void CleanUp();


void do_Init()
{
    pdg::LogManager& logMgr = pdg::LogManager::instance();
 	logMgr.setLogLevel(10);
// 	logMgr.initialize("simple", logMgr.init_OverwriteExisting);

    Randomize();
    
    SetUpSpriteWorld();
                
    AddSprites();
    
    
//    RunAnimation();
//    CleanUp();
}

///--------------------------------------------------------------------------------------
//  Randomize
///--------------------------------------------------------------------------------------

void  Randomize() {
    pdg::OS::srand( pdg::OS::getMilliseconds() );
}

///--------------------------------------------------------------------------------------
//  SetUpSpriteWorld
///--------------------------------------------------------------------------------------

void  SetUpSpriteWorld() {

    pdg::GraphicsManager& gfx = pdg::GraphicsManager::instance();
#ifndef PDG_NO_NETWORK
    pdg::NetworkManager& net = pdg::NetworkManager::instance();
    
    net.createServerPort(4000);
#endif
        // Create the SpriteWorld
    gfx.setTargetFPS(50.0);

// don't do any of this, pdg_main already created it as a fullscreen window
//    if (kFullscreen) {
//    	console.dump(pdg.gfx.getCurrentScreenMode(0));
//    	pdg.gfx.setScreenMode(0, kWindowWidth, kWindowHeight, 32);
//		gPort = gfx.createFullScreenPort( pdg::Rect(kWindowWidth, kWindowHeight) );
//	} else {
//		gPort = gfx.createWindowPort( pdg::Rect(kWindowWidth, kWindowHeight), "PDG Simple Sprite Test" );
//	}
    gPort = gfx.getMainPort();

        // Create the Sprite Layers
	gSpriteLayer = pdg::createSpriteLayer(gPort);
    gSpriteLayer->setUseChipmunkPhysics();
	gSpriteLayer->zoomTo(0.25, 10);
    
    	// Set the background color
    gSpriteLayer->addHandler(gMyHandler, pdg::eventType_SpriteLayer);

    std::string spritePath = pdg::OS::getApplicationDataDirectory();
    spritePath += "/";
    spritePath += gSpriteFilename;
	gBallImage = pdg::Image::createImageFromFile(spritePath.c_str());
    std::string earthPath = pdg::OS::getApplicationDataDirectory();
    earthPath += "/";
    earthPath += gEarthTextureFilename;
    gEarthTextureImage = pdg::Image::createImageFromFile(earthPath.c_str());
}

bool do_ErasePort() {
    static char s[256];
    pdg::Rect portRect = gPort->getDrawingArea();
//    gPort->fillRect( portRect, gBackgroundColor );
    std::string fps = "FPS: ";
    std::sprintf(s, "%i", (int)pdg::GraphicsManager::instance().getFPS());
    fps += s;
    pdg::Point where(9, 19);
    gPort->drawText( fps.c_str(), where, 14);
    where.x += 2;
    gPort->drawText( fps.c_str(), where, 14);
    where.y += 2;
    gPort->drawText( fps.c_str(), where, 14);
    where.x -= 2;
    gPort->drawText( fps.c_str(), where, 14);
    where.x += 1;
    where.y -= 1;
    gPort->drawText( fps.c_str(), where, 14, 0, PDG_WHITE_COLOR);
//    gPort->drawTexturedSphere(gEarthTextureImage, gPort->getDrawingArea().centerPoint(), 300.0f);
    return true; // completely handled
}



// a helper object that keeps an animated object within bounds and causes it to 
// bounce if it goes out of bounds

 bool 
 BoundsHelper::animate(pdg::Animated* whatP, uint32 msElapsed) {
     pdg::Animated& what = *whatP;
     pdg::Rect boundsRect = gPort->getDrawingArea();
	 boundsRect.scale(4.0);
	 pdg::Rect spriteRect = what.getBoundingBox();
     pdg::Vector moveVector = what.getVelocity();
	if (boundsRect.right < spriteRect.right && moveVector.x > 0) {
		// reverse direction of horizontal movement
		moveVector.x = -moveVector.x;
		what.setVelocity(moveVector);
	} else if (boundsRect.left > spriteRect.left && moveVector.x < 0) {
		// reverse direction of horizontal movement
		moveVector.x = -moveVector.x;
		what.setVelocity(moveVector);
	}
	if (boundsRect.bottom < spriteRect.bottom && moveVector.y > 0) {
		// reverse direction of vertical movement
		moveVector.y = -moveVector.y;
		what.setVelocity(moveVector);
	} else if (boundsRect.top > spriteRect.top && moveVector.y < 0) {
		// reverse direction of vertical movement
		moveVector.y = -moveVector.y;
		what.setVelocity(moveVector);
	}
	return true; // keep helping
}

bool 
MyDrawHelper::draw(pdg::Sprite* sprite, pdg::Port* port) {
    pdg::RotatedRect bounds = sprite->getRotatedBounds();
    pdg::RotatedRect r = sprite->getLayer()->layerToPort(bounds);
    port->fillRect(r, PDG_BLACK_COLOR);
    port->frameRect(r, PDG_WHITE_COLOR);
    return false; // don't let sprite draw itself (ignored for post draw)
}

bool 
MyCollideHelper::allowCollision(pdg::Sprite* sprite, pdg::Sprite* withSprite) {
    return true;
}

bool 
MyCollisionHandler::handleEvent(pdg::EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
    if (inEventType == pdg::eventType_SpriteCollide) {
        pdg::SpriteCollideInfo* sci = static_cast<pdg::SpriteCollideInfo*>(inEventData);
        gCollisionCount++;
    }
    return true;
}
/*

bool  WallCollideFunc() {
	return true;
}
 
*/

///--------------------------------------------------------------------------------------
//  CreateBallSprite - load the master ball sprite and prepare it for cloning later
///--------------------------------------------------------------------------------------

pdg::Sprite&  CreateBallSprite() {
    pdg::Sprite& ballSprite = *gSpriteLayer->createSprite();
	ballSprite.addFramesImage(gBallImage);
	ballSprite.setSize(gBallImage->width, gBallImage->height);
	float ballRadius = gBallImage->width/2;
 	ballSprite.setCollisionRadius( ballRadius );

	ballSprite.addHandler(new MyCollisionHandler(), pdg::eventType_SpriteCollide);
// 	ballSprite.onCollideWall(WallCollideFunc);
    ballSprite.setCollisionHelper(new MyCollideHelper());

    static BoundsHelper* sBoundsHelper = new BoundsHelper();
	ballSprite.addAnimationHelper(sBoundsHelper);

	return ballSprite;
}


///--------------------------------------------------------------------------------------
//  AddSprites - clone the master sprite, and add the clones to the SpriteWorld
///--------------------------------------------------------------------------------------

void AddSprites() {
    for (int spriteNum = 0; spriteNum < kNumSprites; spriteNum++) {
        pdg::Sprite& newSprite = CreateBallSprite();
		newSprite.spriteId = spriteNum;
        pdg::Point screenCenter = pdg::Rect(gPort->getDrawingArea()).scale(4.0).centerPoint();

		long max_x = screenCenter.x - gBallImage->width/2;
		long max_y = screenCenter.y - gBallImage->height/2;
        pdg::Point loc( pdg::OS::rand() % max_x * 2, pdg::OS::rand() % max_y * 2);
        newSprite.setLocation(loc);

        if (gCollisions) {
        	newSprite.enableCollisions();
        } else {
        	newSprite.disableCollisions();
        }

        pdg::Vector v;
        do {	// make sure we get movement in both axis
            v.x = pdg::OS::rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta;
            v.y = pdg::OS::rand() % (kMaxSpriteMoveDelta*2+1) - kMaxSpriteMoveDelta;
        	newSprite.setVelocity(v);
        } while (v.x == 0 || v.y == 0);
    }
    pdg::Sprite& newSprite = CreateBallSprite();
    newSprite.setLocation(gPort->getDrawingArea().centerPoint());
    newSprite.grow(2.0);
    newSprite.setMass(10);
    
    
    MyDrawHelper* myHelper = new MyDrawHelper;

    // FIXME: this should be setVelocity(x, y), but that isn't working
    newSprite.setVelocityInRadians(10.0f, 10.0f);
	if (gCollisions) {
		newSprite.enableCollisions(pdg::Sprite::collide_BoundingBox);
	} else {
		newSprite.disableCollisions();
	}
    newSprite.applyTorque(5000.0);
	newSprite.setDrawHelper(myHelper);

}


///--------------------------------------------------------------------------------------
//  RunAnimation
///--------------------------------------------------------------------------------------

void RunAnimation() { 
}


///--------------------------------------------------------------------------------------
//  CleanUp - This function is not really necessary, since the system will dispose
//  everything automatically when the program quits.
///--------------------------------------------------------------------------------------

void CleanUp() {
}

