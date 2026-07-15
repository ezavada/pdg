// -----------------------------------------------
// spritemanager.cpp
// 
// sprite manager functionality
//
// Written by Ed Zavada, 2009-2012
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


#include "pdg_project.h"

#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/tilelayer.h"
#include "pdg/sys/os.h"

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_interface.h"
#endif

#ifndef PDG_NO_GUI
#include "pdg/sys/port.h"
#include "pdg/sys/graphicsmanager.h"
#endif

#include "spritemanager.h"

//#define PDG_DEBUG_CHIPMUNK

#ifdef PDG_DEBUG_CHIPMUNK
#define CHIPMUNK_DEBUG_ONLY(_expression) _expression
#else
#define CHIPMUNK_DEBUG_ONLY(_expression)
#endif

#define SPRITE_LAYER_TIMER_ID -1234031
#define SPRITE_TIMER_INTERVAL_MS 10  // 100 fps for sprite animation

//#define SPRITE_IGNORE_ANIMATION_TIMER_DRIFT

namespace pdg {
	

#ifdef PDG_USE_CHIPMUNK_PHYSICS

cpBool 
SpriteManager::ChipmunkSpriteCollisionBeginFunc(cpArbiter *arb, struct cpSpace *space, void *data) {
    // TODO: deal with Sensors, which will never generate the PostSolve callback
    //     if (cpShapeGetSensor())
    
    // Get pointers to the two bodies in the collision pair and define local variables for them.
    // Their order matches the order of the collision types passed
    // to the collision handler this function was defined for
    CP_ARBITER_GET_BODIES(arb, sprite1, sprite2);
    Sprite* s1 = static_cast<Sprite*>(cpBodyGetUserData(sprite1));
    if (!s1->mDoCollisions) return false;
    Sprite* s2 = static_cast<Sprite*>(cpBodyGetUserData(sprite2));
    if (!s2->mDoCollisions) return false;
	if (!s1->mLayer || !s2->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionBeginFunc s1->mLayer or s2->mLayer is null, skipping"));
		return false;
	}
	if (SpriteLayer::getLayer(s1->mLayer->layerId) != s1->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionBeginFunc s1->mLayer is invalid, skipping"));
		return false;
	}
	if (SpriteLayer::getLayer(s2->mLayer->layerId) != s2->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionBeginFunc s2->mLayer is invalid, skipping"));
		return false;
	}
    // same layer, okay to collide
	bool canCollide =  (s1->mLayer == s2->mLayer);
	if (!canCollide) {
		// layer to layer collisions, only between layers specifically marked    
		for (std::vector<SpriteLayer*>::iterator itr = s1->mLayer->mCollideLayers.begin(); itr != s1->mLayer->mCollideLayers.end(); itr++) {
			if (s2->mLayer == *itr) {
				canCollide = true;
				break;
			}
		}
    }
	if (!canCollide) {
    	for (std::vector<SpriteLayer*>::iterator itr = s2->mLayer->mCollideLayers.begin(); itr != s2->mLayer->mCollideLayers.end(); itr++) {
       	 	if (s1->mLayer == *itr) {
				canCollide = true;
				break;
			}
		}
    }
    // if we have a collision helper for either of the sprites, check it
    if (canCollide && s1->mCollisionHelper) {
    	canCollide = s1->mCollisionHelper->allowCollision(s1, s2);
    }
    if (canCollide && s2->mCollisionHelper) {
    	canCollide = s2->mCollisionHelper->allowCollision(s1, s2);
    }
    return canCollide;
}

void 
SpriteManager::ChipmunkSpriteCollisionPostSolveFunc(cpArbiter *arb, cpSpace *space, void *data) {
    // this is only called if we have approved the collision
    CP_ARBITER_GET_BODIES(arb, sprite1, sprite2);
    Sprite* s1 = static_cast<Sprite*>(cpBodyGetUserData(sprite1));
   	Sprite* s2 = static_cast<Sprite*>(cpBodyGetUserData(sprite2));
	if (!s1->mLayer || !s2->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionPostSolveFunc s1->mLayer or s2->mLayer is null, skipping"));
		return;
	}
	if (SpriteLayer::getLayer(s1->mLayer->layerId) != s1->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionPostSolveFunc s1->mLayer is invalid, skipping"));
		return;
	}
	if (SpriteLayer::getLayer(s2->mLayer->layerId) != s2->mLayer) {
		CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionPostSolveFunc s2->mLayer is invalid, skipping"));
		return;
	}
    cpVect norm = cpArbiterGetNormal(arb);
    cpVect imp = cpArbiterTotalImpulse(arb);
    Vector normal(norm.x, norm.y);
    Vector impulse(imp.x, imp.y);
    cpFloat kineticEnergy = cpArbiterTotalKE(arb);
    cpFloat dt = ((float)SPRITE_TIMER_INTERVAL_MS)/1000.0f;
    cpFloat force = impulse.vectorLength() / dt;
	CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionPostSolveFunc calling notifyCollisionAction sprite"));
    s1->mLayer->notifyCollisionAction(Sprite::action_CollideSprite, s1, normal, impulse, force, kineticEnergy, arb, 
		#ifdef PDG_SPRITER_SUPPORT
			nullptr,
			nullptr,
			cpArbiterIsFirstContact(arb),
		#endif // PDG_SPRITER_SUPPORT
		s2);
}

cpBool 
SpriteManager::ChipmunkWallCollisionBeginFunc(cpArbiter *arb, struct cpSpace *space, void *data) {
    // Get pointers to the two bodies in the collision pair and define local variables for them.
    // Their order matches the order of the collision types passed
    // to the collision handler this function was defined for
    CP_ARBITER_GET_BODIES(arb, sprite, wall);
    
    return true; // if we want this collision to happen
}

void 
SpriteManager::ChipmunkWallCollisionPostSolveFunc(cpArbiter *arb, cpSpace *space, void *data) {
}

#endif  // PDG_USE_CHIPMUNK_PHYSICS
    
#ifndef PDG_NO_GUI
SpriteLayer* 
SpriteManager::createSpriteLayer(Port* port) {
    return new SpriteLayer(port);
}

TileLayer* 
SpriteManager::createTileLayer(Port* port) {
    return new TileLayer(port);
}
#endif // ! PDG_NO_GUI

SpriteLayer* 
SpriteManager::createSpriteLayer() {
    return new SpriteLayer();
}

TileLayer* 
SpriteManager::createTileLayer() {
    return new TileLayer();
}

void
SpriteManager::cleanupLayer(SpriteLayer* layer) {
    delete layer;
}

// add a layer to the end
void SpriteManager::addLayer(SpriteLayer* layer) {
	if (!layer) return;
	layer->mNextLayer = nullptr;
	if (mFirstLayer == nullptr) {
		mFirstLayer = layer;
		layer->mPrevLayer = nullptr;
		mTimerMgr->unpauseTimer(SPRITE_LAYER_TIMER_ID);
	} else {
		layer->mPrevLayer = mLastLayer;
		mLastLayer->mNextLayer = layer;
	}
	mLastLayer = layer;  // we are always the new last layer
}

void SpriteManager::removeLayer(SpriteLayer* layer) {
	// update our first and last layers
	if (layer == mFirstLayer) {
		mFirstLayer = layer->mNextLayer;
	}
	if (layer == mLastLayer) {
		mLastLayer = layer->mPrevLayer;
	}
	// now update the previous and next layers to point to one another
	if (layer->mPrevLayer) {
		layer->mPrevLayer->mNextLayer = layer->mNextLayer;
	}
	if (layer->mNextLayer) {
		layer->mNextLayer->mPrevLayer = layer->mPrevLayer;
	}
	// finally clear our prev and next layers
	layer->mNextLayer = nullptr;
	layer->mPrevLayer = nullptr;
	if (nullptr == mFirstLayer) {
		mTimerMgr->pauseTimer(SPRITE_LAYER_TIMER_ID);
	}
}

SpriteManager::SpriteManager(EventManager* eventMgr, TimerManager* timerMgr): 
	mEventMgr(eventMgr), 
	mTimerMgr(timerMgr),
	mFirstLayer(nullptr),
	mLastLayer(nullptr)
{	
	// for now we need these
	DEBUG_ASSERT(mEventMgr, "must have a pdg::EventManager");
	DEBUG_ASSERT(mTimerMgr, "must have a pdg::TimerManager");
	
	eventMgr->addHandler(this, eventType_Timer);
	eventMgr->addHandler(this, eventType_PortDraw);
	eventMgr->addHandler(this, eventType_MouseDown);
	eventMgr->addHandler(this, eventType_MouseUp);
	eventMgr->addHandler(this, eventType_MouseMove);
	
	timerMgr->startTimer(SPRITE_LAYER_TIMER_ID, SPRITE_TIMER_INTERVAL_MS,
						 timer_Repeating, UserData::makeUserDataFromPointer(this, data_DoNothing) );
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    mSpace = cpSpaceNew();
    cpCollisionHandler* spriteToSpriteHdlr = cpSpaceAddCollisionHandler(mSpace, CP_COLLIDE_TYPE_SPRITE, CP_COLLIDE_TYPE_SPRITE);
    spriteToSpriteHdlr->beginFunc = ChipmunkSpriteCollisionBeginFunc;
    spriteToSpriteHdlr->postSolveFunc = ChipmunkSpriteCollisionPostSolveFunc;

    cpCollisionHandler* spriteToWallHdlr = cpSpaceAddCollisionHandler(mSpace, CP_COLLIDE_TYPE_SPRITE, CP_COLLIDE_TYPE_WALL);
    spriteToWallHdlr->beginFunc = ChipmunkWallCollisionBeginFunc;
    spriteToWallHdlr->postSolveFunc = ChipmunkWallCollisionPostSolveFunc;
#endif
    
}

SpriteManager::~SpriteManager() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    cpSpaceFree(mSpace);
    mSpace = 0;
#endif
}

// return true if completely handled
bool SpriteManager::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) throw() {
	if (inEventType == eventType_Timer) {
		//SpriteLayer* layer = dynamic_cast<SpriteLayer*>(mFirstLayer);
		pdg::TimerInfo* infoP = static_cast<TimerInfo*>(inEventData);
		if ((infoP->id == SPRITE_LAYER_TIMER_ID) && (infoP->userData == (void*) this)) {
			if (mFirstLayer == nullptr) return true;  // this is our timer, but we don't have any sprite layers so fully handled
			
			// time passed since we last animated
          #ifdef SPRITE_IGNORE_ANIMATION_TIMER_DRIFT
			uint32 elapsedMs = SPRITE_TIMER_INTERVAL_MS; // this is how long we told it to take
          #else
			ms_delta elapsedMs = infoP->msElapsed;  // this is the actual time it took
			if (elapsedMs > 100) { 
				// 1/10 of a second is more than timer drift. We were probably
				// paused or in the debugger or something. So use the normal timer interval
				elapsedMs = SPRITE_TIMER_INTERVAL_MS;
			}
          #endif
  
			SpriteLayerInfo evntInfo;
			// Animate all the layers to their position at the next draw loop
			SpriteLayer* layer = mFirstLayer;
			evntInfo.actingLayer = mFirstLayer;
			evntInfo.action = SpriteLayer::action_AnimationStart;
			evntInfo.millisec = infoP->millisec;
			mFirstLayer->postEvent(eventType_SpriteLayer, &evntInfo);

          #ifdef PDG_USE_CHIPMUNK_PHYSICS
            // Chipmunk docs say it is highly recommended we use a regular step amount, 
            // but when we force the amount to a regular step that doesn't correspond 
            // to the time it actually took, we get erratic movement. Instead we
            // try to do a lot of simulations with a small step decoupled from the
            // drawing loop and that seems to work well
            cpFloat dt = (float) elapsedMs / 1000.0f;
            cpSpaceStep(mSpace, dt);
          #endif

			while (layer) {
				SpriteLayerInfo evntInfo2;
				evntInfo2.actingLayer = layer;
				evntInfo2.action = SpriteLayer::action_PreAnimateLayer;
				layer->postEvent(eventType_SpriteLayer, &evntInfo2);
				layer->animateLayer(elapsedMs);
				SpriteLayerInfo evntInfo3;
				evntInfo3.actingLayer = layer;
				evntInfo3.action = SpriteLayer::action_PostAnimateLayer;
				layer->postEvent(eventType_SpriteLayer, &evntInfo3);
				layer = layer->mNextLayer;
			}
			SpriteLayerInfo evntInfo4;
			evntInfo4.actingLayer = mLastLayer;
			evntInfo4.action = SpriteLayer::action_AnimationComplete;
			mLastLayer->postEvent(eventType_SpriteLayer, &evntInfo4);
			
			return true;
		}
	}

	if (mFirstLayer == nullptr) return false;  // we can't do anything further if we don't have any sprite layers

#ifndef PDG_NO_GUI
	if (inEventType == eventType_PortDraw) {
		pdg::PortDrawInfo* infoP = static_cast<PortDrawInfo*>(inEventData);
		
		// Check if we should fire layer events for this port
		bool shouldFireEvents = false;
		if (mFirstLayer) {
			if (mFirstLayer->mPort) {
				// Layer has a specific port, only fire if it matches
				shouldFireEvents = (infoP->port == mFirstLayer->mPort);
			} else {
				// Layer doesn't have a port, fire for main port
				Port* mainPort = GraphicsManager::instance().getMainPort();
				shouldFireEvents = (infoP->port == mainPort);
			}
		}
		
		if (shouldFireEvents) {
			SpriteLayerInfo evntInfo;
			evntInfo.actingLayer = mFirstLayer;
			evntInfo.action = SpriteLayer::action_ErasePort;
			evntInfo.millisec = OS::getMilliseconds();
			// UserData* userData = UserData::makeUserDataViaCopy(&evntInfo, sizeof(SpriteLayerInfo));
			bool handled = mFirstLayer->postEvent(eventType_SpriteLayer, &evntInfo);
			//userData->release();
			if (!handled && mFirstLayer->mPort) {
				// erase the port to black
//					mFirstLayer->mPort->fillRect(mFirstLayer->mPort->getDrawingArea(), PDG_BLACK_COLOR );
			}

			SpriteLayer* layer = mFirstLayer;
			while (layer) {
				if (layer->mPort) {
					SpriteLayerInfo evntInfo2;
					evntInfo2.actingLayer = layer;
					evntInfo2.action = SpriteLayer::action_PreDrawLayer;
					layer->postEvent(eventType_SpriteLayer, &evntInfo2);
					layer->drawLayer();
					SpriteLayerInfo evntInfo3;
					evntInfo3.actingLayer = layer;
					evntInfo3.action = SpriteLayer::action_PostDrawLayer;
					layer->postEvent(eventType_SpriteLayer, &evntInfo3);
				}
				layer = layer->mNextLayer;
			}
			SpriteLayerInfo evntInfo4;
			evntInfo4.actingLayer = mLastLayer;
			evntInfo4.action = SpriteLayer::action_DrawPortComplete;
			if (mLastLayer->mPort) {
				mLastLayer->postEvent(eventType_SpriteLayer, &evntInfo4);
			}		
			return false; // we didn't completely handle this, others may want to draw
		}
	}
#endif // !PDG_NO_GUI

	if ( (inEventType == eventType_MouseDown) || (inEventType == eventType_MouseUp)) {
		Sprite* hitSprite = nullptr;
		MouseInfo* mi = static_cast<MouseInfo*>(inEventData);
 		SpriteLayer* layer = mLastLayer;
		while (layer) {
			if (!layer->mHidden && layer->mWantsClicks) {
				Sprite* sprite = layer->mLastSprite;
			  #ifndef PDG_NO_GUI
                Point clickPt = layer->portToLayer(mi->mousePos);
			  #else 
                Point clickPt = mi->mousePos;
			  #endif
				while (sprite) {
					if (sprite->wantsClicks) {
						int collideMode = sprite->mDoCollisions;
						sprite->mDoCollisions = sprite->mMouseDetectMode;
						bool didCollide = sprite->collidesWith(clickPt);
						sprite->mDoCollisions = collideMode;
						if (didCollide) {
							hitSprite = sprite;
							break;
						}
					}
					sprite = sprite->mPrevSprite;
				}
				if (hitSprite) {
					break;
				}
			}
			layer = layer->mPrevLayer;
		}
		if (hitSprite) {
			static Sprite* sLastHitSprite = nullptr;
			SpriteTouchInfo* sti = new SpriteTouchInfo();
			std::memcpy((void*)sti, mi, sizeof(MouseInfo)); // copy the mouse info to the sprite touch info
			if (inEventType == eventType_MouseDown) {
				sti->touchType = Sprite::touch_MouseDown;
				sLastHitSprite = hitSprite;
			} else {
				sti->touchType = Sprite::touch_MouseUp;
			}
			sti->touchedSprite = hitSprite;
			sti->inLayer = layer;
			hitSprite->postEvent(eventType_SpriteTouch, sti);
			delete sti; // Clean up the allocated memory
			if ((inEventType == eventType_MouseUp) && (hitSprite == sLastHitSprite)) {
				SpriteTouchInfo* sti2 = new SpriteTouchInfo();
				std::memcpy((void*)sti2, mi, sizeof(MouseInfo)); // copy the mouse info to the sprite touch info
				sti2->touchType = Sprite::touch_MouseClick;
				sti2->touchedSprite = hitSprite;
				sti2->inLayer = layer;
				hitSprite->postEvent(eventType_SpriteTouch, sti2);
				delete sti2; // Clean up the allocated memory
			}
			return true;
		}
	}
	return false;
}
	
	

SpriteManager* SpriteManager::createSingletonInstance() {
	EventManager* evtMgr = EventManager::getSingletonInstance();
	TimerManager* tmrMgr = TimerManager::getSingletonInstance();
	return new SpriteManager(evtMgr, tmrMgr);
}

	
} // end namespace pdg
