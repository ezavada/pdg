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
#include "pdg/sys/animationcontroller.h"
#include <stdexcept>
#include <map>
#include <algorithm>
#include "pdg/sys/animationphysics.h"

#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/particle.h"
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
namespace {
// One contiguous snapshot avoids allocating a shared_ptr control block for
// every Sprite on every tick, while retaining objects across helper callbacks.
template<class T> struct RetainedFrame {
    std::vector<T*> items;
    void add(T* value) { items.push_back(value); value->addRef(); }
    ~RetainedFrame() { for (auto* value : items) value->release(); }
};

// Event and draw helpers may request layer removal during traversal. Keep all
// traversed layers alive until the outermost update/draw returns, with or
// without physics enabled. Nested dispatch cannot clear an outer guard.
struct LayerTraversalScope {
    SpriteManager& manager;
    explicit LayerTraversalScope(SpriteManager& value) : manager(value) {
        ++manager.mLayerUpdateDepth;
    }
    ~LayerTraversalScope() { manager.finishLayerTraversal(); }
};
}
void SpriteManager::finishLayerTraversal() {
    if (--mLayerUpdateDepth) return;
    auto pending = std::move(mDeferredLayerCleanup);
    mDeferredLayerCleanup.clear();
    for (auto* doomed : pending) {
        // Releasing one layer can also remove a later queued layer.
        auto* alive = mFirstLayer;
        while (alive && alive != doomed) alive = alive->mNextLayer;
        if (alive) cleanupLayer(alive);
    }
}

	

#ifdef PDG_USE_CHIPMUNK_PHYSICS

namespace { std::map<cpBody*,Sprite*> rootBodyOwners; }
void SpriteManager::registerBody(cpBody* body,Sprite* sprite){if(sprite)rootBodyOwners[body]=sprite;else rootBodyOwners.erase(body);}
Sprite* SpriteManager::bodyOwner(cpBody* body){
    if(auto* rig=AnimationPhysicsRig::find(body))return static_cast<Sprite*>(rig->owner);
    auto found=rootBodyOwners.find(body);return found==rootBodyOwners.end()?nullptr:found->second;
}
void SpriteManager::stepAnimationPhysics(ms_delta elapsed) {
    LayerTraversalScope traversal(*this);
#ifdef PDG_SPRITER_SUPPORT
    const auto hasDynamicRigBodies=[](const Sprite* sprite) {
        if(!sprite->mAnimationPhysics)return false;
        // Assembly queries intentionally exclude removed limbs and accessories.
        // Those bodies still share this physics world and need the same stable
        // steps/iterations after the animated skeleton returns to Kinematic.
        return std::any_of(sprite->mParts.begin(),sprite->mParts.end(),[](const Part* part) {
            return part->physics.getMode()==physicsBody_Dynamic;
        });
    };
    // Articulated drives and contacts need small steps, including when the
    // animation timer is late. Advance the whole shared space together with the
    // sampled animation targets; subdividing only the solver would hold stale
    // drive forces and kinematic targets throughout the catch-up interval.
    ms_delta maxRigStep=SPRITE_TIMER_INTERVAL_MS;
    bool articulated=false;
    if(elapsed>1) {
        for(auto* layer=mFirstLayer;layer;layer=layer->mNextLayer)
            if(layer->mUseChipmunkPhysics)
                for(auto* sprite=layer->mFirstSprite;sprite;sprite=sprite->mNextSprite)
                    if(hasDynamicRigBodies(sprite)) {
                        articulated=true;
                        if(sprite->mAnimationPhysics->definition().bodies.size()>8)maxRigStep=std::min(maxRigStep,ms_delta(5));
                        // A fast chain can rotate through a large angle even
                        // in 5 ms. Keep angular travel near one degree per solve
                        // so curved pivot paths do not pull the links apart.
                        for(auto* part:sprite->mParts)if(part->physics.isPresent()) {
                            const double speed=std::abs(part->physics.getAngularVelocity());
                            if(speed>0)maxRigStep=std::min(maxRigStep,
                                ms_delta(std::max(1.0,std::min(double(maxRigStep),std::floor(20.0/speed)))));
                        }
                    }
    }
    if(articulated && elapsed>maxRigStep) {
        const ms_delta count=1+(elapsed-1)/maxRigStep;
        const ms_delta step=elapsed/count,remainder=elapsed%count;
        for(ms_delta n=0;n<count;++n)stepAnimationPhysics(step+(n<remainder?1:0));
        return;
    }
#endif
    RetainedFrame<Sprite> sprites;
    RetainedFrame<Particle> particles;
    RetainedFrame<PhysicsBody> bodies;
    for (auto* layer=mFirstLayer; layer; layer=layer->mNextLayer) {
        if (!layer->mUseChipmunkPhysics) continue;
        for (auto* sprite=layer->mFirstSprite; sprite; sprite=sprite->mNextSprite) {
            sprites.add(sprite);
            auto capture = [&](PhysicsBody& body) {
                if (body == PhysicsBody::NoPhysics) return;
                bodies.add(&body);
                body.beginKinematicStep();
            };
            capture(sprite->physics);
            for (auto* part : sprite->mParts) { part->syncPhysicsSolver(); if (!part->mAnimationPhysicsBody) capture(part->physics); }
        }
    }
    for (auto* layer=mFirstLayer; layer; layer=layer->mNextLayer) {
        if (!layer->mUseChipmunkPhysics) continue;
        for (auto* particle : layer->mParticles) {
            particles.add(particle); particle->syncPhysicsSolver();
            if (particle->physics.isPresent()) { bodies.add(particle->physics.operator->()); particle->physics->beginKinematicStep(); }
        }
    }
    const double seconds=double(elapsed)/1000.0;
    for (auto* layer=mFirstLayer; layer; layer=layer->mNextLayer)
        if (layer->mUseChipmunkPhysics) layer->advanceParticles(seconds);
    for (auto* sprite : sprites.items) {
        if (!sprite->mLayer) continue;
        if (sprite->mLayer->mAnimating) {
            sprite->advanceAnimation(elapsed);
            sprite->mAnimationPrepared=sprite->mLayer != nullptr;
        }
#if defined(PDG_SPRITER_SUPPORT)
        try { sprite->prepareAnimationPhysics(elapsed); }
        catch (const std::exception& error) { sprite->mAnimationRigError=error.what(); sprite->releaseAnimationPhysics(); }
#endif
    }
    // Resolve all mounts after independent clips, before collecting world targets.
    for (auto* sprite : sprites.items)
        if (sprite->mLayer && !sprite->mAttachmentPart) sprite->updatePartAttachments();
    for (auto* body : bodies.items) body->prepareKinematicStep(seconds);
    if (seconds>0) {
        std::vector<PhysicsBody*> constraintBodies;
        for (auto* layer=mFirstLayer; layer; layer=layer->mNextLayer)
            for (auto* sprite=layer->mFirstSprite; sprite; sprite=sprite->mNextSprite) {
                if (sprite->physics != PhysicsBody::NoPhysics) {
                    sprite->physics->prepareWorldStep(seconds);
                    constraintBodies.push_back(sprite->physics.operator->());
                }
                for (auto* part : sprite->mParts) {
                    part->syncPhysicsSolver();
                    if (part->physics != PhysicsBody::NoPhysics) {
                        part->physics->prepareWorldStep(seconds);
                        constraintBodies.push_back(part->physics.operator->());
                    }
                }
            }
        for (auto* particle : particles.items) if (particle->mLayer && particle->physics.isPresent()) {
            particle->physics->prepareWorldStep(seconds);
            constraintBodies.push_back(particle->physics.operator->());
        }
        for(auto* layer=mFirstLayer;layer;layer=layer->mNextLayer)
            layer->prepareColliders(layer->mUseChipmunkPhysics ? mSpace : nullptr);
        PhysicsBody::prepareConstraints(constraintBodies);
        const int savedIterations=cpSpaceGetIterations(mSpace);
#ifdef PDG_SPRITER_SUPPORT
        // Long articulated chains need enough solver passes to propagate the
        // contact and motor impulses through their pivots in the same step.
        int iterations=savedIterations;
        for(auto* sprite:sprites.items)
            if(sprite->mLayer && hasDynamicRigBodies(sprite))
                iterations=std::max(iterations,std::min(64,8+2*int(sprite->mAnimationPhysics->definition().bodies.size())));
        cpSpaceSetIterations(mSpace,iterations);
#endif
        cpSpaceStep(mSpace,seconds);
        cpSpaceSetIterations(mSpace,savedIterations);
    }
    // Observe solved velocities before restoring temporary kinematic sweep rates.
    // Break callbacks run outside cpSpaceStep, where topology edits are safe.
    if (seconds > 0) {
        std::vector<PhysicsBody*> monitored;
        for (auto* sprite : sprites.items) if (sprite->mLayer) {
            if (sprite->physics.getBreakAngularSpeed() > 0) monitored.push_back(sprite->physics.operator->());
            for (auto* part : sprite->mParts) if (part->physics.getBreakAngularSpeed() > 0) monitored.push_back(part->physics.operator->());
        }
        for (auto* particle : particles.items) if (particle->mLayer && particle->physics.getBreakAngularSpeed() > 0)
            monitored.push_back(particle->physics.operator->());
        PhysicsBody::checkBreakAngularSpeeds(monitored);
    }
    for (auto* body : bodies.items) body->finishKinematicStep();
    for (auto* particle : particles.items)
        if (particle->mLayer && particle->physics.isPresent()) particle->physics->publishWorldStep();
    for (auto* sprite : sprites.items) {
        if (!sprite->mLayer) continue;
        if (sprite->physics != PhysicsBody::NoPhysics) sprite->physics->publishWorldStep();
#if defined(PDG_SPRITER_SUPPORT)
        try { sprite->publishAnimationPhysics(); }
        catch (const std::exception& error) { sprite->mAnimationRigError=error.what(); sprite->releaseAnimationPhysics(); }
#endif
        sprite->refreshPartPhysics();
#if defined(PDG_SPRITER_SUPPORT)
        sprite->finishAnimationPhysics();
#endif
    }
    for (auto* sprite : sprites.items)
        if (sprite->mLayer && !sprite->mAttachmentPart) sprite->updatePartAttachments();
}

cpBool 
SpriteManager::ChipmunkSpriteCollisionBeginFunc(cpArbiter *arb, struct cpSpace *space, void *data) {
    // TODO: deal with Sensors, which will never generate the PostSolve callback
    //     if (cpShapeGetSensor())
    
    // Get pointers to the two bodies in the collision pair and define local variables for them.
    // Their order matches the order of the collision types passed
    // to the collision handler this function was defined for
    CP_ARBITER_GET_BODIES(arb, sprite1, sprite2);
    Sprite* s1 = bodyOwner(sprite1);
    if(!s1)return false;
    Sprite* s2 = bodyOwner(sprite2);
    if (!s2) return false;
	if (!s2 || !s1->mLayer || !s2->mLayer) {
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
    return canCollide;
}

void 
SpriteManager::ChipmunkSpriteCollisionPostSolveFunc(cpArbiter *arb, cpSpace *space, void *data) {
    // this is only called if we have approved the collision
    CP_ARBITER_GET_BODIES(arb, sprite1, sprite2);
    Sprite* s1 = bodyOwner(sprite1);
    if(!s1)return;
    Sprite* s2 = bodyOwner(sprite2);
	if (!s2 || !s1->mLayer || !s2->mLayer) {
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
    const cpFloat dt = cpSpaceGetCurrentTimeStep(space);
    const cpFloat force = dt > 0 ? impulse.vectorLength() / dt : 0;
	CHIPMUNK_DEBUG_ONLY(OS::_DOUT("SpriteManager::ChipmunkSpriteCollisionPostSolveFunc calling notifyCollisionAction sprite"));
    s1->mLayer->notifyCollisionAction(Sprite::action_CollideSprite, s1, normal, impulse, force, kineticEnergy, arb, 
		#ifdef PDG_SPRITER_SUPPORT
            AnimationPhysicsRig::find(sprite1) && s1->getAnimationRig() ? s1->getAnimationRig()->getBone(AnimationPhysicsRig::find(sprite1)->definition().bodies[AnimationPhysicsRig::find(sprite1)->bodyIndex(sprite1)].bone).name.c_str() : nullptr,
            AnimationPhysicsRig::find(sprite2) && s2->getAnimationRig() ? s2->getAnimationRig()->getBone(AnimationPhysicsRig::find(sprite2)->definition().bodies[AnimationPhysicsRig::find(sprite2)->bodyIndex(sprite2)].bone).name.c_str() : nullptr,
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
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Layer membership cannot change inside an animation modifier");
    if(!layer)return;
    auto* manager=SpriteManager::getSingletonInstance();
    if(manager->mLayerUpdateDepth){
        auto& queue=manager->mDeferredLayerCleanup;
        if(std::find(queue.begin(),queue.end(),layer)==queue.end())queue.push_back(layer);
        return;
    }
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(cpSpaceIsLocked(manager->mSpace)){
        cpSpaceAddPostStepCallback(manager->mSpace,[](cpSpace*,void* key,void*){cleanupLayer(static_cast<SpriteLayer*>(key));},layer,nullptr);
        return;
    }
#endif
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
    // Imported physical rigs still own their capsule primitives. Route their
    // contacts with shared Collider shapes through the rig event adapter too.
    auto* rigToCollider = cpSpaceAddCollisionHandler(mSpace, CP_COLLIDE_TYPE_SPRITE, 0x434f4c4c);
    rigToCollider->beginFunc = ChipmunkSpriteCollisionBeginFunc;
    rigToCollider->postSolveFunc = ChipmunkSpriteCollisionPostSolveFunc;

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
bool SpriteManager::handleEvent(EventEmitter* inEmitter, long inEventType, void* inEventData) noexcept {
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
            LayerTraversalScope traversal(*this);
			evntInfo.actingLayer = mFirstLayer;
			evntInfo.action = SpriteLayer::action_AnimationStart;
			evntInfo.millisec = infoP->millisec;
			mFirstLayer->postEvent(eventType_SpriteLayer, &evntInfo);

            // Pre-animation handlers may choose this tick's IK/kinematic
            // targets. Deliver them before evaluating or solving any layer.
            for (auto* preparing=mFirstLayer; preparing; preparing=preparing->mNextLayer) {
                SpriteLayerInfo pre;
                pre.actingLayer=preparing; pre.action=SpriteLayer::action_PreAnimateLayer;
                preparing->postEvent(eventType_SpriteLayer, &pre);
            }

          #ifdef PDG_USE_CHIPMUNK_PHYSICS
            // Chipmunk docs say it is highly recommended we use a regular step amount, 
            // but when we force the amount to a regular step that doesn't correspond 
            // to the time it actually took, we get erratic movement. Instead we
            // try to do a lot of simulations with a small step decoupled from the
            // drawing loop and that seems to work well
            stepAnimationPhysics(elapsedMs);
          #endif

			layer=mFirstLayer;
			while (layer) {
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
            if(mLastLayer)mLastLayer->postEvent(eventType_SpriteLayer, &evntInfo4);

			
			return true;
		}
	}

	if (mFirstLayer == nullptr) return false;  // we can't do anything further if we don't have any sprite layers

#ifndef PDG_NO_GUI
	if (inEventType == eventType_PortDraw) {
		pdg::PortDrawInfo* infoP = static_cast<PortDrawInfo*>(inEventData);
		Port* mainPort = GraphicsManager::instance().getMainPort();
		auto belongsToPort = [infoP, mainPort](SpriteLayer* layer) {
			return layer && (layer->mPort ? layer->mPort == infoP->port
			                                : infoP->port == mainPort);
		};
		SpriteLayer* firstLayerForPort = nullptr;
		SpriteLayer* lastLayerForPort = nullptr;
		for (SpriteLayer* layer = mFirstLayer; layer; layer = layer->mNextLayer) {
			if (belongsToPort(layer)) {
				if (!firstLayerForPort) firstLayerForPort = layer;
				lastLayerForPort = layer;
			}
		}

		if (firstLayerForPort) {
            LayerTraversalScope traversal(*this);
			SpriteLayerInfo evntInfo;
			evntInfo.actingLayer = firstLayerForPort;
			evntInfo.action = SpriteLayer::action_ErasePort;
			evntInfo.millisec = OS::getMilliseconds();
			bool handled = firstLayerForPort->postEvent(eventType_SpriteLayer, &evntInfo);
			if (!handled && firstLayerForPort->mPort) {
				// erase the port to black
//					firstLayerForPort->mPort->fillRect(firstLayerForPort->mPort->getDrawingArea(), PDG_BLACK_COLOR );
			}

			SpriteLayer* layer = mFirstLayer;

			while (layer) {
				if (belongsToPort(layer)) {
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
			evntInfo4.actingLayer = lastLayerForPort;
			evntInfo4.action = SpriteLayer::action_DrawPortComplete;
			lastLayerForPort->postEvent(eventType_SpriteLayer, &evntInfo4);
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
                        bool didCollide = sprite->hitTest(clickPt);
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
