// -----------------------------------------------
// spritelayer.cpp
// 
// sprite layer functionality
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


#include "pdg/sys/events.h"
#include "particletrail.h"
#include <numbers>
#include "pdg_project.h"
#include <format>
#include "snapshot-codec.h"
#include "pdg/sys/animationcontroller.h"
#ifdef PDG_SPRITER_SUPPORT
#include "spriter/pdg_spriter_pose.h"
#endif
#include <stdexcept>

#include "pdg/sys/global_types.h"
#include "pdg/sys/os.h"
#include "pdg/sys/sprite.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/particle.h"
#include "pdg/sys/particleemitter.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"
#include "pdg/sys/eventmanager.h"
#include "pdg/sys/resource.h"

#include "spritemanager.h"
#include "pdg/sys/scene.h"
#include "layer-snapshot-scope.h"
#include "physics-graph-snapshot.h"
#include "internals.h"

// define this here to get debug rendering of spriter elements
#define PDG_DEBUG_SPRITER

#ifdef PDG_SPRITER_SUPPORT
  #ifdef PDG_DEBUG_SPRITER
    #include "spriterengine/global/settings.h"
  #endif // PDG_DEBUG_SPRITER
#endif // PDG_SPRITER_SUPPORT

#include <algorithm>
#include <unordered_set>
#include <limits>

// define the following in your build environment, or uncomment it here to get
// debug output for the core events and timers
//#define PDG_DEBUG_SPRITELAYER
//#define PDG_DEBUG_SERIALIZATION
//#define PDG_DEBUG_EVENTS

#ifndef PDG_DEBUG_SPRITELAYER
  #define SPRITELAYER_DEBUG_ONLY(_expression)
#else
  #define SPRITELAYER_DEBUG_ONLY(_expression) _expression
  #define SPRITELAYER_INTERNAL_DEBUG   // does some extra drawing to show layers
#endif
#ifndef PDG_DEBUG_SERIALIZATION
  #define SERIALIZATION_DEBUG_ONLY(_expression)
#else
  #define SERIALIZATION_DEBUG_ONLY(_expression) _expression
#endif
#ifndef PDG_DEBUG_EVENTS
  #define EVENTS_DEBUG_ONLY(_expression)
#else
  #define EVENTS_DEBUG_ONLY(_expression) _expression
#endif


#ifdef PDG_DESERIALIZER_NO_THROW
	// we can't throw, so we report errors but don't exit
	#define STREAM_SAFETY_CHECK(_cond, _msg, _except) if (!(_cond)) { char buf[1024]; buf[0] = 0;\
		std::snprintf(buf, sizeof(buf), "%s: %s at %s (%s:%d)", #_except, _msg, __FUNCTION__, __FILE__, __LINE__); \
		DEBUG_PRINT(buf); }
#else
	// we throw exceptions on errors
	#define STREAM_SAFETY_CHECK(_cond, _msg, _except) if (!(_cond)) { char buf[1024]; buf[0] = 0;\
		std::snprintf(buf, sizeof(buf), "%s: %s at %s (%s:%d)", #_except, _msg, __FUNCTION__, __FILE__, __LINE__); \
		throw _except(buf); }
#endif

#define PDG_SPRITE_LAYER_MAGIC_NUMBER   0x31008971
#define PDG_SPRITE_LAYER_STREAM_V_1		0
// add new versions here
#define PDG_SPRITE_LAYER_STREAM_VERSION	6

#ifndef PDG_UNSAFE_SERIALIZATION
#define PDG_TAG_SERIALIZED_DATA
#endif

namespace pdg {

long gNextLayerId = 1;
static uint32 sUniqueLayerId = 1;

long gNextSpriteEventId = 1;

void SpriteAnimateInfo_ReleaseActingSprite(void* ptr);
void SpriteCollideInfo_ReleaseSpritesAndFreeStrings(void* ptr);

void SpriteAnimateInfo_ReleaseActingSprite(void* ptr) {
	if (!ptr) return;
	SpriteAnimateInfo* sai = static_cast<SpriteAnimateInfo*>(ptr);
	if (sai->actingSprite) {
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteAnimateInfo_ReleaseActingSprite id: %d actingSprite: %p", sai->id, sai->actingSprite));
		sai->actingSprite->release();
		sai->actingSprite = 0;
	}
}
	
void SpriteCollideInfo_ReleaseSpritesAndFreeStrings(void* ptr) {
    EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo_ReleaseSpritesAndFreeStrings ptr: %p", ptr));
	if (!ptr) return;
	SpriteAnimateInfo_ReleaseActingSprite(ptr);
	SpriteCollideInfo* sci = static_cast<SpriteCollideInfo*>(ptr);
	if (sci->targetSprite) {
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo_ReleaseSpritesAndFreeStrings id: %d targetSprite: %p", sci->id, sci->targetSprite));
		sci->targetSprite->release();
		sci->targetSprite = 0;
	}
#ifdef PDG_SPRITER_SUPPORT
	// Free collision name strings if they were allocated for enqueued events
	if (sci->collisionName) {
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo_ReleaseSpritesAndFreeStrings id: %d collisionName: %s", sci->id, sci->collisionName));
		free(const_cast<char*>(sci->collisionName));
		sci->collisionName = 0;
	}
	if (sci->withCollisionName) {
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteCollideInfo_ReleaseSpritesAndFreeStrings id: %d withCollisionName: %s", sci->id, sci->withCollisionName));
		free(const_cast<char*>(sci->withCollisionName));
		sci->withCollisionName = 0;
	}
#endif // PDG_SPRITER_SUPPORT
}


// -----------------------------------------------------------------------------------
// Sprite Layer
// Used to create and track sets of sprites
// -----------------------------------------------------------------------------------

void SpriteLayer::setCamera(Camera* camera) {
    if (camera==mCamera) return;
#ifndef PDG_NO_GUI
    if (camera && mPort) camera->ensureViewport(*mPort);
#endif
    Scene::claimCamera(camera,mManager?mManager->mScene:nullptr);
    if (camera) camera->attach();
    auto* previous=mCamera; mCamera=camera;
    if (previous) {Scene::releaseCamera(previous,mManager?mManager->mScene:nullptr);previous->detach();}
}
Camera* SpriteLayer::getEffectiveCamera() const {
#ifndef PDG_NO_GUI
#endif
    if (mCamera) return mCamera;
    if (mManager && mManager->mScene) return mManager->mScene->getCamera();
#ifndef PDG_NO_GUI
    if (mPort) return mPort->getCamera();
#endif
    return nullptr;
}
void SpriteLayer::setCameraParallax(float movementRatio,float zoomRatio) {
    if (!std::isfinite(movementRatio)||!std::isfinite(zoomRatio)) throw std::invalid_argument("Camera parallax ratios must be finite");
    mCameraMoveRatio=movementRatio; mCameraZoomRatio=zoomRatio;
}
void SpriteLayer::setWorldBounds(const Rect& bounds) {
    if (!std::isfinite(bounds.left)||!std::isfinite(bounds.top)||!std::isfinite(bounds.right)||!std::isfinite(bounds.bottom)||bounds.right<bounds.left||bounds.bottom<bounds.top)
        throw std::invalid_argument("Layer world bounds must be finite and ordered");
    mWorldBounds=bounds;
}

void SpriteLayer::setSerializationFlags(uint32 flags) {
	mSerFlags = flags;
}

void SpriteLayer::validateInitialSnapshot() const {
    if (!mCollideLayers.empty()) throw std::runtime_error("Layer snapshots do not yet support collision links to other layers");
    for (auto* sprite = mFirstSprite; sprite; sprite = sprite->mNextSprite)
        sprite->validateInitialSnapshot(true);
}

#include "layer-mount-snapshot.inc"

uint32 SpriteLayer::getSerializedSize(ISerializer* serializer) const {
    PhysicsGraphSnapshot scene(*this);
    PhysicsSnapshotScope physicsScope(serializer, scene.bodies());
    if (mSerFlags & ser_InitialData) scene.validate();
    LayerSnapshotScope graph(serializer, this);
    if (mSerFlags & ser_InitialData) validateInitialSnapshot();
	if ( (mSerFlags == ser_Micro) || (mSerFlags == ser_Positions) ) {
        serializer->setSendTags(false);  // we don't want to send any unnecessary data
    }
	uint32 totalSize = 0;
	Sprite* sprite = 0;
	uint32 count = 0;
	totalSize += 1;  // size of PDG_SPRITE_LAYER_STREAM_VERSION
	totalSize += serializer->sizeof_uint(mSerFlags); // size of serializable flags
	if ( (mSerFlags == ser_Micro) || (mSerFlags == ser_Positions) ) {
		// special case, smallest possible update, basically just the sprites
		sprite = mFirstSprite;
		while (sprite) {
			count++;
			if (mSerFlags & ser_ZOrder) {
				totalSize += serializer->sizeof_uint(sprite->iid);
			}
			// normally we would call serializer->sizeof_obj(sprite), but
			// that adds a bunch of overhead for object tags and such that we don't want
			// this only gives us the size of the data
			totalSize += sprite->getSerializedSize(serializer);
			sprite = sprite->mNextSprite;
		}
		totalSize += serializer->sizeof_uint(count);
	} else {
	  #ifdef PDG_TAG_SERIALIZED_DATA
		totalSize += 4;  // size of request magic number
	  #endif
		totalSize += 2; // size layerFlags
		if (mSerFlags & ser_InitialData) {
			totalSize += serializer->sizeof_uint(iid);
			totalSize += serializer->sizeof_uint(layerId);
            for (auto deadline : {mDoneFadingInAt,mDoneFadingOutAt}) {
                totalSize+=serializer->sizeof_bool(deadline!=0);
                if(deadline)totalSize+=8;
            }
            SnapshotWriter out(serializer,false);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            out.floating(mGravity);
#else
            out.floating(0);
#endif
            totalSize+=out.size();
		}
        if (mSerFlags & ser_LayerDraw) {
            totalSize+=serializer->sizeof_obj(mCamera);
            SnapshotWriter out(serializer,false); out.floating(mCameraMoveRatio,1); out.floating(mCameraZoomRatio,1); totalSize+=out.size();
        }
        if (mSerFlags & ser_Sizes) { SnapshotWriter out(serializer,false); for (float value : {mWorldBounds.left,mWorldBounds.top,mWorldBounds.right,mWorldBounds.bottom}) out.floating(value); totalSize+=out.size(); }



		if (mSerFlags & ser_Forces) {
//			totalSize += 4;  // 1 float: mGravity
		}
		if (mSerFlags & ser_Physics) {
		}

		sprite = mFirstSprite;
		count = 0;
		while (sprite) {
			count++;
			if (mSerFlags & ser_ZOrder) {
				totalSize += serializer->sizeof_uint(sprite->iid);
			}
		  	if (mSerFlags & ser_InitialData) {
				totalSize += serializer->sizeof_obj(sprite);
			} else {
				totalSize += sprite->getSerializedSize(serializer);
			}
			sprite = sprite->mNextSprite;
		}
		totalSize += serializer->sizeof_uint(count); // for count

	}
    if (mSerFlags & ser_InitialData) { totalSize+=mountSnapshotSize(serializer);totalSize+=scene.size(serializer); }
	return totalSize;
}


void SpriteLayer::serialize(ISerializer* serializer) const {
    PhysicsGraphSnapshot scene(*this);
    PhysicsSnapshotScope physicsScope(serializer, scene.bodies());
    if (mSerFlags & ser_InitialData) scene.validate();
    LayerSnapshotScope graph(serializer, this);
    if (mSerFlags & ser_InitialData) validateInitialSnapshot();
	if ( (mSerFlags == ser_Micro) || (mSerFlags == ser_Positions) ) {
        serializer->setSendTags(false);  // we don't want to send any unnecessary data
    }
	Sprite* sprite = 0;
	uint32 count = 0;
	serializer->serialize_1u(PDG_SPRITE_LAYER_STREAM_VERSION);
	serializer->serialize_uint(mSerFlags);
	SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer [%p] vers [%d] flags [%p]", this, PDG_SPRITE_LAYER_STREAM_VERSION, mSerFlags); )
	if ( (mSerFlags == ser_Micro) || (mSerFlags == ser_Positions) ) {
		SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer [%p] writing Micro update", this); )
		// special case, smallest possible update, basically just the sprites
		// get and write the count
		sprite = mFirstSprite;
		while (sprite) {
			count++;
			sprite = sprite->mNextSprite;
		}
		serializer->serialize_uint(count);
		SERIALIZATION_DEBUG_ONLY( int i = 0; DEBUG_PRINT("  sprite count: %d", count); )
		// now write the minimal position data for the sprites
		sprite = mFirstSprite;
		while (sprite) {
			SERIALIZATION_DEBUG_ONLY( i++; DEBUG_PRINT("  %d: ", i); )
			if (mSerFlags & ser_ZOrder) {
				serializer->serialize_uint(sprite->iid);
				SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    iid : %d ", sprite->iid); )
			}
			sprite->serialize(serializer);
			sprite = sprite->mNextSprite;
		}
	} else {
		uint16 layerFlags = 
			(mHidden ? 			1 << 0 : 0) |
			(mAnimating ? 		1 << 1 : 0) |
			(mDoCollisions ? 	1 << 2 : 0) |
			(mWantsMouseOver ?	1 << 3 : 0) |
			(mWantsClicks ? 	1 << 4 : 0) |
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
			(mUseChipmunkPhysics ? 	1 << 8 : 0) |
			(mIsStaticLayer ? 		1 << 9 : 0) |
	  #endif
            0;
	  #ifdef PDG_TAG_SERIALIZED_DATA
		serializer->serialize_4(PDG_SPRITE_LAYER_MAGIC_NUMBER);
	  #endif
		serializer->serialize_2u(layerFlags);
		if (mSerFlags & ser_InitialData) {
			serializer->serialize_uint(iid);
			serializer->serialize_uint(layerId);
            const auto now = animationMilliseconds();
            for (auto deadline : {mDoneFadingInAt, mDoneFadingOutAt}) {
                serializer->serialize_bool(deadline!=0);
                if(deadline)serializer->serialize_d(std::max(0.0, (deadline-now)/1000.0));
            }
            SnapshotWriter out(serializer,true);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            out.floating(mGravity);
#else
            out.floating(0);
#endif
		}
        if (mSerFlags & ser_LayerDraw) {
            serializer->serialize_obj(mCamera);
            SnapshotWriter out(serializer,true); out.floating(mCameraMoveRatio,1); out.floating(mCameraZoomRatio,1);
        }
        if (mSerFlags & ser_Sizes) { SnapshotWriter out(serializer,true); for (float value : {mWorldBounds.left,mWorldBounds.top,mWorldBounds.right,mWorldBounds.bottom}) out.floating(value); }

		


		if (mSerFlags & ser_Forces) {
		  #ifdef PDG_USE_CHIPMUNK_PHYSICS
// 			serializer->serialize_f(mGravity);
		  #else
// 			serializer->serialize_f(0.0f);  // write zero so this stream will be readable by process built with Chipmunk Physics
		  #endif
		}
		sprite = mFirstSprite;
		while (sprite) {
			count++;
			sprite = sprite->mNextSprite;
		}
		serializer->serialize_uint(count);
		SERIALIZATION_DEBUG_ONLY( int i = 0; DEBUG_PRINT("  sprite count: %d", count); )
		// now write the update data for the sprites
		sprite = mFirstSprite;
		while (sprite) {
			SERIALIZATION_DEBUG_ONLY( i++; DEBUG_PRINT("  %d: ", i); )
			if (mSerFlags & ser_ZOrder) {
				serializer->serialize_uint(sprite->iid);
				SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    iid : %d ", sprite->iid); )
			}
		  	if (mSerFlags & ser_InitialData) {
				serializer->serialize_obj(sprite);
			} else {
				sprite->serialize(serializer);
			}
			sprite = sprite->mNextSprite;
		}

	}
    if (mSerFlags & ser_InitialData) { serializeMounts(serializer); scene.write(serializer); }
}


void SpriteLayer::deserialize(IDeserializer* deserializer) {
    if (AnimationPipeline::isInsideCallback())
        throw std::logic_error("Layer snapshots must load outside animation modifiers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto* space = getSpace();
    if (space && cpSpaceIsLocked(space)) throw std::logic_error("Layer snapshots must load outside the physical solve");
#endif
    const auto version = deserializer->deserialize_1u();
    const auto flags = deserializer->deserialize_uint();
    if (version != PDG_SPRITE_LAYER_STREAM_VERSION || (flags & ~uint32(0x7fff)))
        throw std::runtime_error("Unsupported SpriteLayer record");
    if (flags & ser_InitialData) {
        if (version != PDG_SPRITE_LAYER_STREAM_VERSION)
            throw std::runtime_error("Unsupported initial SpriteLayer record");
        SpriteLayer staged;
        PhysicsGraphReadScope graphScope(deserializer);
        staged.readSerializedState(deserializer, flags);
        adoptInitialSnapshot(staged);
    } else readSerializedState(deserializer, flags);
}

void SpriteLayer::adoptInitialSnapshot(SpriteLayer& staged) {
    removeAllParticleEmitters();
    removeAllParticles();
    removeAllSprites();
    mWorldBounds = staged.mWorldBounds;
    setCamera(staged.mCamera); setCameraParallax(staged.mCameraMoveRatio,staged.mCameraZoomRatio);
    mHidden = staged.mHidden; mAnimating = staged.mAnimating; mDoCollisions = staged.mDoCollisions;
    mWantsMouseOver = staged.mWantsMouseOver; mWantsClicks = staged.mWantsClicks;
    iid = staged.iid; layerId = staged.layerId;
    mDoneFadingInAt = staged.mDoneFadingInAt; mDoneFadingOutAt = staged.mDoneFadingOutAt;
    rebaseFadeClock(staged.animationMilliseconds(),animationMilliseconds());
#ifndef PDG_NO_GUI

#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    mGravity = staged.mGravity;
    mUseChipmunkPhysics = staged.mUseChipmunkPhysics; mIsStaticLayer = staged.mIsStaticLayer;
#endif
    while (auto* sprite = staged.mFirstSprite) {
        staged.unlinkSprite(sprite); sprite->mLayer = nullptr;
        insertSprite(sprite, mLastSprite);
        sprite->release(); // transfer the staging layer's owning reference
    }
}

void SpriteLayer::readSerializedState(IDeserializer* deserializer, uint32 flags) {
    struct RestoreFlags {
        uint32& value;
        uint32 saved;
        ~RestoreFlags() { value = saved; }
    } restore{mSerFlags, mSerFlags};
    mSerFlags = flags;

	Sprite* sprite = 0;
	uint32 count = 0;
	if ( (mSerFlags == ser_Micro) || (mSerFlags == ser_Positions) ) {
		SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer [%p] reading Micro update", this); )
		// special case, smallest possible update, basically just the sprites
		// get and write the count
		count = deserializer->deserialize_uint();
		// now write the minimal position data for the sprites
		SERIALIZATION_DEBUG_ONLY( int i = 0; DEBUG_PRINT("  sprite count: %d", count); )
		sprite = mFirstSprite;
		while (sprite && count) {
			SERIALIZATION_DEBUG_ONLY( i++; DEBUG_PRINT("  %d: (rem: %d)", i, count); )
			if (mSerFlags & ser_ZOrder) {
				uint32 siid = deserializer->deserialize_uint(); // get the sprite's internal id
				SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    iid : %d ", siid); )
				if (sprite->iid != siid) {
					SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    ** mismatch ** - swapping z-order with sprite %d", sprite->iid); )
					// they don't match, find the correct sprite and swap Z order
					Sprite* targetSprite = findSpriteByInternalId(siid);
					STREAM_SAFETY_CHECK(targetSprite != 0, "OUT OF SYNC: missing target sprite when changing z-order", unknown_object);
					if (targetSprite) {
						quickSwapSprites(sprite, targetSprite);
						sprite = targetSprite;
					}
				}
			}
			sprite->deserialize(deserializer);
			sprite = sprite->mNextSprite;
			count--;
		}
		STREAM_SAFETY_CHECK(sprite == 0, "OUT OF SYNC: more sprites in layer than were targeted", sync_error);
		STREAM_SAFETY_CHECK(count == 0, "OUT OF SYNC: more sprites in stream than in targeted layer", sync_error);
	} else {
	  #ifdef PDG_TAG_SERIALIZED_DATA
		uint32 tag = deserializer->deserialize_4();
		STREAM_SAFETY_CHECK(tag == PDG_SPRITE_LAYER_MAGIC_NUMBER, "OUT OF SYNC: expected tag for Sprite Layer object", bad_tag);
	  #endif
		uint32 layerFlags = deserializer->deserialize_2u();
		mHidden = ((layerFlags & 1 << 0) != 0);
		mAnimating = ((layerFlags & 1 << 1) != 0);
		mDoCollisions = ((layerFlags & 1 << 2) != 0);
		mWantsMouseOver = ((layerFlags & 1 << 3) != 0);
		mWantsClicks = ((layerFlags & 1 << 4) != 0);
	  #ifndef PDG_NO_GUI
	  #endif
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
		mUseChipmunkPhysics = ((layerFlags & 1 << 8) != 0);
		mIsStaticLayer = ((layerFlags & 1 << 9) != 0);
	  #endif
        if (mSerFlags & ser_InitialData) {
            iid = deserializer->deserialize_uint();
            layerId = deserializer->deserialize_uint();
            if (iid == 0 || iid == UINT32_MAX) throw std::runtime_error("Invalid Layer identity");
            sUniqueLayerId = std::max(sUniqueLayerId, iid + 1);
            if (layerId < std::numeric_limits<long>::max()) gNextLayerId = std::max(gNextLayerId, layerId + 1);
            const auto now = animationMilliseconds();
            for (auto* deadline : {&mDoneFadingInAt, &mDoneFadingOutAt}) {
                const double seconds = deserializer->deserialize_bool() ? deserializer->deserialize_d() : -1;
                if (!std::isfinite(seconds) || (seconds < 0 && seconds != -1) ||
                    seconds > (std::numeric_limits<ms_time>::max()-now)/1000.0)
                    throw std::runtime_error("Invalid Layer fade completion delay");
                *deadline = seconds == -1 ? 0 : now + static_cast<ms_time>(std::ceil(seconds*1000));
            }
            const float gravity = SnapshotReader(deserializer).floating();
            if (!std::isfinite(gravity)) throw std::runtime_error("Invalid Layer gravity setting");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
            mGravity = gravity;
#endif
        }
        if (mSerFlags & ser_LayerDraw) {
            auto* object=deserializer->deserialize_obj();
            struct Release { ISerializable* object; ~Release() { if(object) object->release(); } } release{object};
            auto* camera=dynamic_cast<Camera*>(object);
            if (object && !camera) throw std::runtime_error("Layer camera record must contain a Camera");
            SnapshotReader in(deserializer); float movement=in.floating(1), zoom=in.floating(1);
            setCameraParallax(movement,zoom); setCamera(camera);
        }
        if (mSerFlags & ser_Sizes) { SnapshotReader in(deserializer); float v[4]; for(auto& value:v) value=in.floating(); mWorldBounds=Rect(v[0],v[1],v[2],v[3]); }
        setWorldBounds(mWorldBounds);
        count = deserializer->deserialize_uint();
        if (mSerFlags & ser_InitialData) {
            if (count > 1000000) throw std::runtime_error("Too many sprites in Layer snapshot");
            std::unordered_set<uint32> identities;
            while (count--) {
                const auto expectedId = (mSerFlags & ser_ZOrder) ? deserializer->deserialize_uint() : 0;
                auto* object = deserializer->deserialize_obj();
                auto* incoming = dynamic_cast<Sprite*>(object);
                if (!incoming || incoming->mLayer || !identities.insert(incoming->iid).second ||
                    ((mSerFlags & ser_ZOrder) && incoming->iid != expectedId)) {
                    if (object) object->release();
                    throw std::runtime_error("Invalid or duplicate Sprite in initial Layer record");
                }
                // Stage ownership and order without joining the shared solver.
                incoming->mLayer = this;
                incoming->mPrevSprite = mLastSprite;
                incoming->mNextSprite = nullptr;
                if (mLastSprite) mLastSprite->mNextSprite = incoming;
                else mFirstSprite = incoming;
                mLastSprite = incoming;
            }
            deserializeMounts(deserializer);
            PhysicsGraphSnapshot(*this).read(deserializer);
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
            if(!mUseChipmunkPhysics)for(auto* item=mFirstSprite;item;item=item->mNextSprite)
                if(item->mAnimationPhysics)throw std::runtime_error("Physical rig snapshot requires a Chipmunk layer");
#endif
            return;
        }

		// now read the data for the sprites
		SERIALIZATION_DEBUG_ONLY( int i = 0; DEBUG_PRINT("  sprite count: %d", count); )

		sprite = mFirstSprite;
		while (sprite && count) {
			SERIALIZATION_DEBUG_ONLY( i++; DEBUG_PRINT("  %d: (rem: %d)", i, count); )
			if (mSerFlags & ser_ZOrder) {
				uint32 siid = deserializer->deserialize_uint(); // get the sprite's internal id
				SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    iid : %d ", siid); )
				if (sprite->iid != siid) {
					SERIALIZATION_DEBUG_ONLY( DEBUG_PRINT("    ** mismatch ** - swapping z-order with sprite %d", sprite->iid); )
					// they don't match, find the correct sprite and swap Z order
					Sprite* targetSprite = findSpriteByInternalId(siid);
					STREAM_SAFETY_CHECK(targetSprite != 0, "OUT OF SYNC: missing target sprite when changing z-order", unknown_object);
					if (targetSprite) {
						quickSwapSprites(sprite, targetSprite);
						sprite = targetSprite;
					}
				}
			}
            sprite->deserialize(deserializer);
			sprite = sprite->mNextSprite;
			count--;
		}
		STREAM_SAFETY_CHECK(sprite == 0, "OUT OF SYNC: more sprites in layer than were targeted", sync_error);
		STREAM_SAFETY_CHECK(count == 0, "OUT OF SYNC: more sprites in stream than in targeted layer", sync_error);

	}
}

// start and stop animating all sprites
void	SpriteLayer::startAnimations() {
	mAnimating = true;
}


void	SpriteLayer::stopAnimations() {
	mAnimating = false;
}

// hide and show (make the layer visible or invisible within the port)
// if the layer is hidden it will not get any mouseover or click events
void	SpriteLayer::hide() {
	mHidden = true;
}


void	SpriteLayer::show() {
	mHidden = false;
}

bool	SpriteLayer::isHidden() {
	return mHidden;
}

void	SpriteLayer::fadeIn(double durationSeconds, EasingFunc easing) {
	for (auto* particle : mParticles) particle->fadeTo(1, durationSeconds, easing);
	mDoneFadingInAt = animationMilliseconds() + static_cast<ms_time>(std::ceil(durationSeconds * 1000.0));
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		sprite->fadeIn(durationSeconds, easing);
		sprite = sprite->mNextSprite;
	}
}

void	SpriteLayer::fadeOut(double durationSeconds, EasingFunc easing) {
	for (auto* particle : mParticles) particle->fadeTo(0, durationSeconds, easing);
	mDoneFadingOutAt = animationMilliseconds() + static_cast<ms_time>(std::ceil(durationSeconds * 1000.0));
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		sprite->fadeOut(durationSeconds, easing);
		sprite = sprite->mNextSprite;
	}
}

ms_time SpriteLayer::animationMilliseconds() const {
    if(mManager && mManager->mScene)return static_cast<ms_time>(mManager->mScene->getSimulationTime()*1000);
    return mClockDetached?mDetachedClock:OS::getMilliseconds();
}
void SpriteLayer::rebaseFadeClock(ms_time oldTime,ms_time newTime) {
    for(auto* deadline:{&mDoneFadingInAt,&mDoneFadingOutAt})if(*deadline)*deadline=newTime+std::max<ms_time>(0,*deadline-oldTime);
}

// Reorder within the same manager without detaching physics or scene ownership.
void SpriteLayer::moveBehind(SpriteLayer* other) {
    if (!mManager || other==this || (!other && !mPrevLayer && !mNextLayer)) return;
    if (other && other->mManager!=mManager) throw std::logic_error("Layer order is local to its scene");
    auto* manager=mManager;
    manager->removeLayer(this);
    if (!other) other=manager->mFirstLayer;
    mManager=manager; mNextLayer=other; mPrevLayer=other?other->mPrevLayer:manager->mLastLayer;
    if(mPrevLayer)mPrevLayer->mNextLayer=this;else manager->mFirstLayer=this;
    if(other)other->mPrevLayer=this;else manager->mLastLayer=this;
}
void SpriteLayer::moveInFrontOf(SpriteLayer* other) {
    if (!mManager || other==this || (!other && !mPrevLayer && !mNextLayer)) return;
    if (other && other->mManager!=mManager) throw std::logic_error("Layer order is local to its scene");
    auto* manager=mManager;
    manager->removeLayer(this);
    if (!other) other=manager->mLastLayer;
    mManager=manager; mPrevLayer=other; mNextLayer=other?other->mNextLayer:manager->mFirstLayer;
    if(mNextLayer)mNextLayer->mPrevLayer=this;else manager->mLastLayer=this;
    if(other)other->mNextLayer=this;else manager->mFirstLayer=this;
}
int SpriteLayer::getZOrder() {
    int z=0;
    for(auto* layer=mManager?mManager->mFirstLayer:nullptr;layer;layer=layer->mNextLayer,++z)if(layer==this)return z;
    return -1;
}

// add and remove sprites from the manager

// find a sprite in the layer by id. Be sure to addRef() the sprite if you hang onto the reference
Sprite*	SpriteLayer::findSprite(long id) {
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		if (sprite->spriteId == id) {
			return sprite;
		}
		sprite = sprite->mNextSprite;
	}
	return 0;
}

// find a sprite in the layer by internal id (PROTECTED)
Sprite*	SpriteLayer::findSpriteByInternalId(uint32 iid) const {
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		if (sprite->iid == iid) {
			return sprite;
		}
		sprite = sprite->mNextSprite;
	}
	return 0;
}

// get the nth sprite in the layer by z-order, 0 is the one furthest back
Sprite* SpriteLayer::getNthSprite(int index) {
	if (index < 0) return 0;
	Sprite* sprite = mFirstSprite;
	while (sprite && index) {
		sprite = sprite->mNextSprite;
		index--;
	}
	return sprite;
}

// z-order 0 is furthest back, increment from there
// return -1 if not in this layer
int SpriteLayer::getSpriteZOrder(Sprite* sprite) {
	int z = 0;
	Sprite* s = mFirstSprite;
	while (s) {
		if (s == sprite) {
			return z;
		} else {
			z++;
			s = s->mNextSprite;
		}
	}
	return -1;
}

// does otherSprite have higher z-order than sprite?
bool SpriteLayer::isSpriteBehind(Sprite* sprite, Sprite* otherSprite) {
	while (sprite) {
		if (sprite->mNextSprite == otherSprite) {
			return true;
		} else {
			sprite = sprite->mNextSprite;
		}
	}
	return false;
}

// see if a sprite is in this layer
bool SpriteLayer::hasSprite(Sprite* inSprite) {
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		if (inSprite == sprite) {
			return true;
		}
		sprite = sprite->mNextSprite;
	}
	return false;
}
	
// Layer membership follows the rigid mounting tree. Retention during removal
// is independent of draw order: an attached child may precede its host.
std::vector<Sprite*> SpriteLayer::attachmentGroup(Sprite* root) {
    std::vector<Sprite*> group{root};
    for (size_t i = 0; i < group.size(); ++i) {
        for (auto* part : group[i]->mParts) {
            if (auto* child = part->getAttachedSprite()) group.push_back(child);
        }
    }
    return group;
}

void SpriteLayer::insertSprite(Sprite* sprite, Sprite* after) {
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    if(sprite->mAnimationPhysics && !mUseChipmunkPhysics)throw std::logic_error("Restored physical rigs require a Chipmunk layer");
#endif
    sprite->mPrevSprite = after;
    sprite->mNextSprite = after ? after->mNextSprite : mFirstSprite;
    if (sprite->mNextSprite) sprite->mNextSprite->mPrevSprite = sprite;
    else mLastSprite = sprite;
    if (after) after->mNextSprite = sprite;
    else mFirstSprite = sprite;
    sprite->mLayer = this;
    sprite->addRef();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mUseChipmunkPhysics && sprite->physics != PhysicsBody::NoPhysics) {
        sprite->initCpBody();
    }
#ifdef PDG_SPRITER_SUPPORT
    if(sprite->mAnimationPhysics) sprite->mAnimationPhysics->moveToSpace(getSpace());
#endif
    for (auto* part : sprite->mParts) part->syncPhysicsSolver();
#endif
#ifndef PDG_NO_GUI
    sprite->setPort(mPort);
#endif
}

void SpriteLayer::unlinkSprite(Sprite* sprite) {
    if (sprite->mPrevSprite) sprite->mPrevSprite->mNextSprite = sprite->mNextSprite;
    else mFirstSprite = sprite->mNextSprite;
    if (sprite->mNextSprite) sprite->mNextSprite->mPrevSprite = sprite->mPrevSprite;
    else mLastSprite = sprite->mPrevSprite;
    sprite->mNextSprite = sprite->mPrevSprite = nullptr;
}

void SpriteLayer::reorderSprite(Sprite* sprite, Sprite* after) {
    if (AnimationPipeline::isInsideCallback())
        throw std::logic_error("Layer order cannot change inside an animation modifier");
    if (!sprite || sprite->mLayer != this || (after && after->mLayer != this) || sprite == after) return;
    if (sprite->mPrevSprite == after) return;
    unlinkSprite(sprite);
    sprite->mPrevSprite = after;
    sprite->mNextSprite = after ? after->mNextSprite : mFirstSprite;
    if (sprite->mNextSprite) sprite->mNextSprite->mPrevSprite = sprite;
    else mLastSprite = sprite;
    if (after) after->mNextSprite = sprite;
    else mFirstSprite = sprite;
}

void SpriteLayer::addSprite(Sprite* sprite) {
    addSpriteInFrontOf(sprite, mLastSprite);
}

// PROTECTED: swap z order of 2 sprites that are known to be in the same layer
void SpriteLayer::quickSwapSprites(Sprite* s1, Sprite* s2) {
	Sprite* tmp = s1->mNextSprite;
	s1->mNextSprite = s2->mNextSprite;
	s2->mNextSprite = tmp;
	tmp = s1->mPrevSprite;
	s1->mPrevSprite = s2->mPrevSprite;
	s2->mPrevSprite = tmp;
	if (s1->mPrevSprite == 0) {
		mFirstSprite = s1;
	} else {
		s1->mPrevSprite->mNextSprite = s1;
	}
	if (s2->mPrevSprite == 0) {
		mFirstSprite = s2;
	} else {
		s2->mPrevSprite->mNextSprite = s2;
	}
	if (s1->mNextSprite == 0) {
		mLastSprite = s1;
	} else {
		s1->mNextSprite->mPrevSprite = s1;
	}
	if (s2->mNextSprite == 0) {
		mLastSprite = s2;
	} else {
		s2->mNextSprite->mPrevSprite = s2;
	}
}

// A new group is inserted contiguously, host first. Reordering a member already
// in this layer is separate and does not tear down bodies or relationships.
void SpriteLayer::addSpriteInFrontOf(Sprite* sprite, Sprite* target) {
    if (AnimationPipeline::isInsideCallback())
        throw std::logic_error("Layer membership cannot change inside an animation modifier");
    if (!sprite || sprite->mLayer == this || (target && target->mLayer != this)) return;
    if (sprite->mAttachmentPart)
        throw std::logic_error("Detach the mounted Sprite before moving it independently; move its host to transfer the group");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if ((mUseChipmunkPhysics && cpSpaceIsLocked(getSpace())) ||
        (sprite->mLayer && sprite->mLayer->mUseChipmunkPhysics && cpSpaceIsLocked(sprite->mLayer->getSpace())))
        throw std::logic_error("Transfer sprites outside locked physics callbacks");
#endif
    const auto group = attachmentGroup(sprite);
    std::vector<bool> prepared;
    for (auto* member : group) prepared.push_back(member->mAnimationPrepared);
    // Keep the root alive across removal even if the old layer owns its only ref.
    sprite->addRef();
    try {
        if (sprite->mLayer) sprite->mLayer->removeSprite(sprite);
        for (size_t i=0; i<group.size(); ++i) {
            auto* member=group[i];
            insertSprite(member, target);
            member->mAnimationPrepared=prepared[i];
            target = member;
        }
        sprite->updatePartAttachments();
    } catch (...) { sprite->release(); throw; }
    sprite->release();
}

void SpriteLayer::removeSprite(Sprite* sprite) {
    if (AnimationPipeline::isInsideCallback())
        throw std::logic_error("Layer membership cannot change inside an animation modifier");
    if (!sprite || sprite->mLayer != this) return;
    if (sprite->mAttachmentPart)
        throw std::logic_error("Detach the mounted Sprite before removing it independently; remove its host to remove the group");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mUseChipmunkPhysics && cpSpaceIsLocked(getSpace())) {
        if (cpSpaceAddPostStepCallback(getSpace(), [](cpSpace*, void* key, void*) {
            auto* retained = static_cast<Sprite*>(key);
            if (retained->mLayer) retained->mLayer->removeSprite(retained);
            retained->release();
        }, sprite, nullptr)) sprite->addRef();
        return;
    }
#endif
    const auto group = attachmentGroup(sprite);
    for (auto* member : group) member->addRef();
    for (auto* member : group) {
        member->physics.disconnect();
        for (auto* part : member->mParts) part->physics.disconnect();
        member->collider->syncNative(nullptr);
        for(auto* part:member->mParts)part->collider->syncNative(nullptr);
#ifdef PDG_SPRITER_SUPPORT
        member->releaseAnimationPhysics();
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if (member->mBody) { member->disconnect(); member->freeCpBody(); }
        for (auto* part : member->mParts)
            if (part->physics != PhysicsBody::NoPhysics) part->physics->detachSolver();
#endif
        unlinkSprite(member);
        member->mLayer = nullptr;
        member->mAnimationPrepared = false;
#ifndef PDG_NO_GUI
        member->setPort(nullptr);
#endif
        member->release(); // layer's ownership; the group snapshot still retains it
    }
    for (auto* member : group) member->release();
}

void SpriteLayer::removeAllSprites() {
    std::vector<Sprite*> roots;
    for (auto* sprite = mFirstSprite; sprite; sprite = sprite->mNextSprite) {
        if (!sprite->mAttachmentPart) { sprite->addRef(); roots.push_back(sprite); }
    }
    for (auto* root : roots) { removeSprite(root); root->release(); }
}

#ifndef PDG_NO_GUI

void SpriteLayer::setSpritePort(Port* port) {
    if (mCamera && port) mCamera->ensureViewport(*port);
    if (mPort==port) return;
    if (mPort) std::erase(mPort->mLayers,this);
    mPort = port;
    if (mPort) mPort->mLayers.push_back(this);
    for (auto* sprite=mFirstSprite; sprite; sprite=sprite->mNextSprite) sprite->setPort(port);
}

namespace {
RotatedRect transformRotatedRect(const SpatialTransform& t,const RotatedRect& r) {
    const double scale=std::hypot(t.a,t.b), other=std::hypot(t.c,t.d);
    if (t.a*t.d-t.b*t.c<=0 || std::abs(scale-other)>0.00001 || std::abs(t.a*t.c+t.b*t.d)>0.00001) {
        Quad q=r.getQuad(); for(auto& p:q.points)p=t.transformPoint(p); return RotatedRect(q.getBounds());
    }
    RotatedRect out=r;
    const Point center=t.transformPoint(r.centerPoint());
    const Offset offset(t.a*r.centerOffset.x+t.c*r.centerOffset.y,t.b*r.centerOffset.x+t.d*r.centerOffset.y);
    const double angle=r.radians+std::atan2(t.b,t.a);
    const double c=std::cos(r.radians), sn=std::sin(r.radians);
    const Offset rotated(c*r.centerOffset.x-sn*r.centerOffset.y,sn*r.centerOffset.x+c*r.centerOffset.y);
    const Offset mapped(t.a*rotated.x+t.c*rotated.y,t.b*rotated.x+t.d*rotated.y);
    out.top*=scale;out.left*=scale;out.right*=scale;out.bottom*=scale;
    out.center(Point(center.x-mapped.x+std::cos(angle)*offset.x-std::sin(angle)*offset.y,
                     center.y-mapped.y+std::sin(angle)*offset.x+std::cos(angle)*offset.y));
    out.radians=angle;out.centerOffset=offset;return out;
}
}
// Coordinate conversion uses exactly one effective camera.
SpatialTransform SpriteLayer::getViewTransform() const {
    auto* camera=getEffectiveCamera();
    if (!camera) return {};
    if (mPort) camera->ensureViewport(*mPort);
    auto result=camera->viewportTransform(mCameraMoveRatio,mCameraZoomRatio);
    if(mManager && mManager->mScene && mManager->mScene->mDrawingSprite)result=SpatialTransform::compose(result,mManager->mScene->presentationTransform(mManager->mScene->mDrawingSprite));
    return result;
}
Point SpriteLayer::layerToPort(const Point& p) const { return getViewTransform().transformPoint(p); }
Offset SpriteLayer::layerToPort(const Offset& o) const { auto t=getViewTransform(); return Offset(t.a*o.x+t.c*o.y,t.b*o.x+t.d*o.y); }
Quad SpriteLayer::layerToPort(const Quad& q) const { Quad result=q; for(auto& p:result.points) p=layerToPort(p); return result; }
RotatedRect SpriteLayer::layerToPort(const Rect& r) const { return transformRotatedRect(getViewTransform(),RotatedRect(r)); }
RotatedRect SpriteLayer::layerToPort(const RotatedRect& r) const { return transformRotatedRect(getViewTransform(),r); }
Point SpriteLayer::portToLayer(const Point& p) const { return getViewTransform().inverse().transformPoint(p); }
Offset SpriteLayer::portToLayer(const Offset& o) const { auto t=getViewTransform().inverse(); return Offset(t.a*o.x+t.c*o.y,t.b*o.x+t.d*o.y); }
Quad SpriteLayer::portToLayer(const Quad& q) const { Quad result=q; for(auto& p:result.points) p=portToLayer(p); return result; }
RotatedRect SpriteLayer::portToLayer(const Rect& r) const { return transformRotatedRect(getViewTransform().inverse(),RotatedRect(r)); }
RotatedRect SpriteLayer::portToLayer(const RotatedRect& r) const { return transformRotatedRect(getViewTransform().inverse(),r); }

#endif // ! PDG_NO_GUI



	
// collisions
void	SpriteLayer::enableCollisions() {
	mDoCollisions = true;
}


void	SpriteLayer::disableCollisions() {
	mDoCollisions = false;
}


#ifndef PDG_NO_GUI
void	SpriteLayer::drawLayer() {
	if (!mPort) return;	// can't draw without a port
    auto* previousCamera=mPort->mLayerDrawingCamera;
    mPort->mLayerDrawingCamera=getEffectiveCamera();
    struct RestoreCamera {Port& port;Camera* previous;~RestoreCamera(){port.mLayerDrawingCamera=previous;}} restoreCamera{*mPort,previousCamera};
    if (mPort->mLayerDrawingCamera && mPort->mLayerDrawingCamera->isHidden()) return;
    const auto previousClip=mPort->getClipRect();
    struct RestoreClip { Port& port; Rect clip; ~RestoreClip(){port.setClipRect(clip);} } restoreClip{*mPort,previousClip};
    if (auto* camera=getEffectiveCamera()) {
        camera->ensureViewport(*mPort);
        mPort->setClipRect(previousClip.intersection(camera->getViewport()));
        mPort->queueCameraEffects(camera);
    }
    Port::ScreenDrawingScope screenDrawing(*mPort);

	Sprite* sprite = mFirstSprite;
	while (sprite && !mHidden) {
        auto* scene=mManager?mManager->mScene:nullptr;
        struct Drawing {Scene* scene;Sprite* previous;~Drawing(){if(scene)scene->mDrawingSprite=previous;}} drawing{scene,scene?scene->mDrawingSprite:nullptr};
        if(scene)scene->mDrawingSprite=sprite;
        sprite->draw();
		sprite = sprite->mNextSprite;
	}

    if (!mHidden) {
        for(const auto& trail:mParticleTrails)drawParticleTrail(*mPort,*trail,getViewTransform());
        for (auto* particle : mParticles) particle->draw();
    }
#ifdef SPRITELAYER_INTERNAL_DEBUG
    if (!mHidden) {
        Rect r(30, 30);
        r.center(Point(0,0));
        RotatedRect rr = layerToPort(r);
        rr.radians += std::numbers::pi/4;
        Quad q = rr.getQuad();
        mPort->drawLine(q.points[0], q.points[2], PDG_BLUE_COLOR);
        mPort->drawLine(q.points[1], q.points[3], PDG_BLUE_COLOR);
        r.setSize(20);
        r.center(Point());
        rr = layerToPort(r);
        q = rr.getQuad();
        mPort->drawLine(q.points[0], q.points[2], PDG_RED_COLOR);
        mPort->drawLine(q.points[1], q.points[3], PDG_RED_COLOR);
        rr.radians += std::numbers::pi/4;
        q = rr.getQuad();
        mPort->drawLine(q.points[0], q.points[2], PDG_RED_COLOR);
        mPort->drawLine(q.points[1], q.points[3], PDG_RED_COLOR);
    }
#endif // SPRITELAYER_INTERNAL_DEBUG
}
#endif // ! PDG_NO_GUI

namespace {
template<class T> struct ParticleFrame {
    std::vector<T*> items;
    explicit ParticleFrame(const std::vector<T*>& source) : items(source) { for (auto* p : items) p->addRef(); }
    ~ParticleFrame() { for (auto* p : items) p->release(); }
};
}
Particle* SpriteLayer::createParticle() {
    if (getParticleCount() >= mMaxParticles) return nullptr;
    auto particle = std::make_unique<Particle>(); addParticle(particle.get()); return particle.release();
}
void SpriteLayer::addParticle(Particle* particle) {
    if (!particle) throw std::invalid_argument("Expected a Particle");
    if (particle->mLayer == this) return;
    if (particle->mLayer || !particle->isAlive()) throw std::logic_error("Add a live detached particle");
    if (getParticleCount() >= mMaxParticles) throw std::length_error("Layer particle budget is full");
    mParticles.push_back(particle); particle->mLayer = this;
    try { particle->syncPhysicsSolver(); }
    catch (...) { particle->mLayer = nullptr; mParticles.pop_back(); throw; }
    particle->addRef();
}
Particle* SpriteLayer::getNthParticle(uint32 index) const {
    return index < mParticles.size() ? mParticles[index] : nullptr;
}
void SpriteLayer::removeParticle(Particle* particle) {
    if (!particle || particle->mLayer != this) return;
    if (particle->physics.isPresent()) particle->physics.disconnect();
    if (particle->collider.isPresent()) particle->collider->syncNative(nullptr);
    if(particle->mTrail)particle->mTrail->reset(particle->getLocation(),particle->getOpacity());
    particle->mLayer = nullptr; particle->syncPhysicsSolver();
    if (particle->getParticleEmitter()) particle->getParticleEmitter()->stopEmitting();
    mParticles.erase(std::find(mParticles.begin(), mParticles.end(), particle)); particle->release();
}
void SpriteLayer::removeAllParticles() { while (!mParticles.empty()) removeParticle(mParticles.back()); mParticleTrails.clear(); }
void SpriteLayer::retireParticleTrail(std::unique_ptr<ParticleTrail> trail) {
    if(!trail || trail->empty() || trail->samples().size()<2)return;
    // Bound retained tails independently of emission rate. Discard oldest first.
    size_t points=trail->ring.size();
    for(const auto& old:mParticleTrails)points+=old->ring.size();
    while(!mParticleTrails.empty() && (points>65536 || mParticleTrails.size()>=mMaxParticles)) {
        points-=mParticleTrails.front()->ring.size();mParticleTrails.erase(mParticleTrails.begin());
    }
    if(mMaxParticles)mParticleTrails.push_back(std::move(trail));
}
uint32 SpriteLayer::getParticleTrailCount() const {
    size_t count=mParticleTrails.size();
    for(const auto* p:mParticles)if(p->mTrail && !p->mTrail->empty())++count;
    return static_cast<uint32>(count);
}
ParticleEmitter* SpriteLayer::createParticleEmitter() {
    auto emitter = std::make_unique<ParticleEmitter>(); mParticleEmitters.push_back(emitter.get());
    emitter->mLayer = this; emitter->addRef(); return emitter.release();
}
void SpriteLayer::removeParticleEmitter(ParticleEmitter* emitter) {
    if (!emitter || emitter->mLayer != this || emitter->mParticle) return;
    mParticleEmitters.erase(std::find(mParticleEmitters.begin(), mParticleEmitters.end(), emitter));
    emitter->mLayer = nullptr; emitter->stopEmitting(); emitter->release();
}
void SpriteLayer::removeAllParticleEmitters() { while (!mParticleEmitters.empty()) removeParticleEmitter(mParticleEmitters.back()); }
void SpriteLayer::advanceParticles(double seconds) {
    // Snapshot before any helper can create/remove particles. New emissions start next tick.
    for (auto* p : mParticleStep) p->release();
    mParticleStep = mParticles;
    for (auto* p : mParticleStep) p->addRef();
    mParticlesPrepared = true;
    if(mAnimating) {
        for(auto& trail:mParticleTrails)trail->age(seconds);
        std::erase_if(mParticleTrails,[](const auto& trail){return trail->empty();});
    }
    if (mAnimating) for (auto* p : mParticleStep) if (p->mLayer == this) p->advance(seconds);
}
void SpriteLayer::finishParticles(double seconds) {
    ParticleFrame<Particle> particles(mParticleStep);
    for (auto* p : mParticleStep) p->release();
    mParticleStep.clear(); mParticlesPrepared = false;
    ParticleFrame<ParticleEmitter> emitters(mParticleEmitters);
    if (!mAnimating) return;
    for (auto* p : particles.items) if (p->mLayer == this) p->finish();
    for (auto* emitter : emitters.items) if (emitter->mLayer == this) emitter->advance(seconds);
}

bool SpriteLayer::allowsColliderWorld(const void* world) const {
    auto* other=static_cast<const SpriteLayer*>(world);
    if(!other)return false;
    if(other==this)return mDoCollisions;
    return std::find(mCollideLayers.begin(),mCollideLayers.end(),other)!=mCollideLayers.end() ||
        std::find(other->mCollideLayers.begin(),other->mCollideLayers.end(),this)!=other->mCollideLayers.end();
}
void SpriteLayer::collectQueryColliders(std::vector<Collider*>& out) const {
    auto add = [&](const auto& association) {
        if (association.isPresent()) out.push_back(association.operator->());
    };
    for (auto* sprite=mFirstSprite; sprite; sprite=sprite->mNextSprite) {
        add(sprite->collider);
        for (auto* part:sprite->mParts) add(part->collider);
    }
    for (auto* particle:mParticles) add(particle->collider);
}
void SpriteLayer::prepareColliders(void* space) {
    bool enabled=mDoCollisions || !mCollideLayers.empty();
    if(!enabled)for(auto* layer=(mManager ? mManager->mFirstLayer : nullptr);layer;layer=layer->mNextLayer)
        if(allowsColliderWorld(layer)) { enabled=true; break; }
    auto prepare=[&](Collider& collider) {
        collider.setWorldFilter([this](const void* other){return allowsColliderWorld(other);});
        collider.syncNative(enabled ? space : nullptr,this);
    };
    for(auto* sprite=mFirstSprite;sprite;sprite=sprite->mNextSprite) {
#ifdef PDG_SPRITER_SUPPORT
        if (sprite->isAnimationPhysicsEnabled()) sprite->collider->syncNative(nullptr);
        else
#endif
        prepare(sprite->collider);
        for(auto* part:sprite->mParts)prepare(part->collider);
    }
    for (auto* particle : mParticles) prepare(particle->collider);
}
void SpriteLayer::solveColliders(double seconds) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(!mUseChipmunkPhysics)
#endif
        prepareColliders(nullptr);
    std::vector<PhysicsBody*> bodies;
    for(auto* sprite=mFirstSprite;sprite;sprite=sprite->mNextSprite) {
        if(sprite->physics!=PhysicsBody::NoPhysics)bodies.push_back(sprite->physics.operator->());
        for(auto* part:sprite->mParts)if(part->physics!=PhysicsBody::NoPhysics)bodies.push_back(part->physics.operator->());
    }
    for (auto* particle : mParticles)
        if (particle->physics.isPresent()) bodies.push_back(particle->physics.operator->());
    PhysicsBody::solveConstraints(bodies,seconds);
    std::vector<Collider*> colliders;
    auto collect=[&](SpriteLayer* layer) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(!layer->mUseChipmunkPhysics)
#endif
            layer->prepareColliders(nullptr);
        for(auto* sprite=layer->mFirstSprite;sprite;sprite=sprite->mNextSprite) {
            if(sprite->collider!=Collider::NoCollider)colliders.push_back(sprite->collider.operator->());
            for(auto* part:sprite->mParts)if(part->collider!=Collider::NoCollider)colliders.push_back(part->collider.operator->());
        }
        for (auto* particle : layer->mParticles)
            if (particle->collider.isPresent()) colliders.push_back(particle->collider.operator->());
    };
    collect(this);
    for(auto* other=(mManager ? mManager->mFirstLayer : nullptr);other;other=other->mNextLayer)
        if(other!=this && iid<other->iid && allowsColliderWorld(other))collect(other);
    if(colliders.empty()&&!mCollisionWorld)return;
    if(!mCollisionWorld)mCollisionWorld=std::make_unique<CollisionWorld>();
    mCollisionWorld->step(colliders,seconds,[this](const Collider& a,const Collider& b) {
        return a.world()==this || b.world()==this;
    });
}

void
SpriteLayer::animateLayer(double msElapsed) {
    // Contacts may request layer cleanup even when a native caller steps a layer directly.
    struct Traversal {
        SpriteManager* manager;
        explicit Traversal(SpriteManager* value) : manager(value) { if(manager) ++manager->mLayerUpdateDepth; }
        ~Traversal() { if(manager) manager->finishLayerTraversal(); }
    } traversal(mManager);



	
	SpriteLayerInfo evntInfo;
	ms_time currMs = animationMilliseconds();
	SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("%s", std::format("Animating layer [{}] @ {}", static_cast<const void*>(this), msElapsed).c_str()); )

	if (mDoneFadingInAt && (currMs > mDoneFadingInAt)) {
		mDoneFadingInAt = 0;
		evntInfo.actingLayer = this;
		evntInfo.action = SpriteLayer::action_FadeInComplete;
		evntInfo.millisec = currMs;
		postEvent(eventType_SpriteLayer, &evntInfo);		
	}
	if (mDoneFadingOutAt && (currMs > mDoneFadingOutAt)) {
		mDoneFadingOutAt = 0;
		evntInfo.actingLayer = this;
		evntInfo.action = SpriteLayer::action_FadeOutComplete;
		evntInfo.millisec = currMs;
		postEvent(eventType_SpriteLayer, &evntInfo);		
	}
	Sprite* sprite = mFirstSprite;
	while (sprite && mAnimating) {
		sprite->doAnimate(msElapsed, mDoCollisions);
		sprite = sprite->mNextSprite;
	}
    // Resolve rigid mounts after every Sprite has evaluated its independent clip.
    for (auto* attached=mFirstSprite;attached;attached=attached->mNextSprite)
        if (!attached->mAttachmentPart) attached->updatePartAttachments();
    if (!mParticlesPrepared) advanceParticles(double(msElapsed)/1000.0);
    solveColliders(double(msElapsed)/1000.0);
    if (msElapsed > 0) {
        std::vector<PhysicsBody*> monitored;
        for (auto* owner=mFirstSprite; owner; owner=owner->mNextSprite) {
            auto collect=[&](PhysicsBody& body) {
                if (body.getBreakAngularSpeed() > 0 && body.getSolver()==physicsSolver_Basic) monitored.push_back(&body);
            };
            collect(owner->physics);
            for (auto* part:owner->mParts) collect(part->physics);
        }
        for (auto* particle : mParticles)
            if (particle->physics.getBreakAngularSpeed() > 0 && particle->physics.getSolver() == physicsSolver_Basic)
                monitored.push_back(particle->physics.operator->());
        PhysicsBody::checkBreakAngularSpeeds(monitored);
    }
    finishParticles(double(msElapsed)/1000.0);
}

#ifndef PDG_NO_GUI
void SpriteLayer::wantMouseOverEvents() {
	mWantsMouseOver = true;
}

void SpriteLayer::checkIfMouseOverEventsStillWanted() {
	Sprite* sprite = mFirstSprite;
	mWantsMouseOver = false;
	while (sprite) {
		if (sprite->wantsMouseOver) {
			mWantsMouseOver = true;
			break;
		}
		sprite = sprite->mNextSprite;
	}
}

void SpriteLayer::wantClickEvents() {
	mWantsClicks = true;
}

void SpriteLayer::checkIfClickEventsStillWanted() {
	Sprite* sprite = mFirstSprite;
	mWantsClicks = false;
	while (sprite) {
		if (sprite->wantsClicks) {
			mWantsClicks = true;
			break;
		}
		sprite = sprite->mNextSprite;
	}
}
#endif // ! PDG_NO_GUI

// some animation actions happen as callbacks from chipmunk during simulation, so we enqueue them
// to be handled outside of the chipmunk simulation loop.
// This and notifyCollisionAction are the only two methods that will enqueue events.
void SpriteLayer::notifyAnimationAction(int action, Sprite* actingSprite, bool sendImmediately) {
	// Create SpriteAnimateInfo on the stack
	SpriteAnimateInfo si;
	si.action = action;
	si.id = gNextSpriteEventId++;
	si.actingSprite = actingSprite;
	si.inLayer = this;
	SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("Sprite [%p] -> anim event %d", actingSprite, action); )
  #ifndef PDG_NO_EVENT_QUEUE
	if (sendImmediately) {
  #endif
  		// For immediate events, use UserData to manage the data lifecycle
  		actingSprite->postEvent(eventType_SpriteAnimate, &si);
  #ifndef PDG_NO_EVENT_QUEUE
	} else {
		// if the events are to be deferred, then we will be retaining copies of the Sprite pointers in the SpriteAnimateInfo within the queue. 
		// We need to increment the refcount and make the User Data object call our custom SpriteAnimateInfo_ReleaseSprites function when
		// it goes to free the SpriteAnimateInfo object
		if (actingSprite) {
			actingSprite->addRef();
		}
		EventManager::getSingletonInstance()->enqueueEvent(eventType_SpriteAnimate, 
			UserData::makeUserDataViaCopy(&si, sizeof(SpriteAnimateInfo), 
			&SpriteAnimateInfo_ReleaseActingSprite),
			actingSprite);
	}
  #endif
}

// some collision actions happen as callbacks from chipmunk during simulation, so we enqueue them
// to be handled outside of the chipmunk simulation loop
void SpriteLayer::notifyCollisionAction(int action, Sprite* actingSprite, Vector normal, 
										Vector impulse, float force, float kineticEnergy, 
                                    #ifdef PDG_USE_CHIPMUNK_PHYSICS
                                        cpArbiter* arbiter,
                                    #endif
                                    #ifdef PDG_SPRITER_SUPPORT
                                        const char* collisionName,
                                        const char* withCollisionName,
                                        bool isFirstContact,
                                    #endif // PDG_SPRITER_SUPPORT
                                        Sprite* targetSprite, bool sendImmediately) {
	// Create SpriteCollideInfo on the stack
	SpriteCollideInfo si;
	si.action = action;
	si.id = gNextSpriteEventId++;
	si.actingSprite = actingSprite;
	si.targetSprite = targetSprite;
    si.normal = normal;
    si.impulse = impulse;
    si.force = force;
    si.kineticEnergy = kineticEnergy;
	si.inLayer = this;
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
	si.arbiter = arbiter;
  #endif
  #ifdef PDG_SPRITER_SUPPORT
	si.collisionName = collisionName;
	si.withCollisionName = withCollisionName;
	si.isFirstContact = isFirstContact;
  #endif // PDG_SPRITER_SUPPORT
  #ifndef PDG_NO_EVENT_QUEUE
	SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("Sprite [%p] -> collide event %d", actingSprite, action); )
	if (sendImmediately) {
  #endif
  		// For immediate events, use UserData to manage the data lifecycle
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::notifyCollisionAction calling postEvent id: %d data: %p", si.id, &si));
  		actingSprite->postEvent(eventType_SpriteCollide,  &si);
  #ifndef PDG_NO_EVENT_QUEUE
	} else {
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::notifyCollisionAction calling enqueueEvent id: %d", si.id));
		// if the events are to be deferred, then we will be retaining copies of the Sprite pointers in the SpriteCollideInfo within the queue. 
		// We need to increment the refcount and make the User Data object call our custom SpriteCollideInfo_ReleaseSprites function when
		// it goes to free the SpriteCollideInfo object
		if (actingSprite) {
			actingSprite->addRef();
		}
		if (targetSprite) {
			targetSprite->addRef();
		}
		
		// For enqueued events, we need to make copies of the collision name strings
		// since they point to data that might be destroyed before the event is processed
#ifdef PDG_SPRITER_SUPPORT
		if (si.collisionName && strlen(si.collisionName) > 0) {
			si.collisionName = strdup(si.collisionName);
		} else {
			si.collisionName = nullptr; // make sure a zero length string is treated as a null pointer
		}
		if (si.withCollisionName && strlen(si.withCollisionName) > 0) {
			si.withCollisionName = strdup(si.withCollisionName);
		} else {
			si.withCollisionName = nullptr; // make sure a zero length string is treated as a null pointer
		}
#endif // PDG_SPRITER_SUPPORT
		
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        si.arbiter=nullptr; // borrowed Chipmunk arbiters are valid only during the callback
#endif
		EventManager::getSingletonInstance()->enqueueEvent(eventType_SpriteCollide, 
			UserData::makeUserDataViaCopy(&si, sizeof(SpriteCollideInfo), 
			&SpriteCollideInfo_ReleaseSpritesAndFreeStrings),
			actingSprite);
	}
  #endif
}

void    
SpriteLayer::enableCollisionsWithLayer(SpriteLayer* otherLayer) {
    mCollideLayers.push_back(otherLayer);
}

void    
SpriteLayer::disableCollisionsWithLayer(SpriteLayer* otherLayer) {
    std::vector<SpriteLayer*>::iterator position = std::find(mCollideLayers.begin(), mCollideLayers.end(), otherLayer);
    if (position != mCollideLayers.end()) {
        mCollideLayers.erase(position);
    }
}

// create sprites
Sprite* SpriteLayer::createSprite() {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Sprite creation must occur outside a modifier");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mUseChipmunkPhysics && cpSpaceIsLocked(getSpace()))throw std::logic_error("Create sprites outside locked physics callbacks");
#endif
	Sprite* sprite = new Sprite();
	addSprite(sprite);
	return sprite;
}


Sprite* SpriteLayer::cloneSprite(const Sprite* originalSprite) {
//	Sprite* sprite =  new Sprite(originalSprite);
//	addSprite(sprite);
//	return sprite;
    return 0;
}

#ifdef PDG_SPRITER_SUPPORT

// create a sprite from a Spriter file, optionally specifying which entity if there are several
Sprite* SpriteLayer::createSpriteFromSpriterFile(const char* inFileName, const char* inEntityName) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Sprite creation must occur outside a modifier");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mUseChipmunkPhysics && cpSpaceIsLocked(getSpace()))throw std::logic_error("Create sprites outside locked physics callbacks");
#endif

// TODO: have a way to enable/disable debug drawing at runtime in debug builds
#ifdef PDG_DEBUG_SPRITER
	SpriterEngine::Settings::renderDebugBoxes = true;
	SpriterEngine::Settings::renderDebugBones = true;
	SpriterEngine::Settings::renderDebugPoints = true;
	SpriterEngine::Settings::enableDebugBones = true;
#endif // PDG_DEBUG_SPRITER

	// Check ResourceManager first for relative paths
	std::string fullPath;
	bool isResourceFile = false;
	
	if (os_isAbsolutePath(inFileName)) {
		fullPath = inFileName;
	} else {
		// For relative paths, check if the file exists in ResourceManager first
		ResourceManager* resMgr = ResourceManager::getSingletonInstance();
		if (resMgr && !resMgr->getResourcePaths().empty()) {
			size_t resourceSize = resMgr->getResourceSize(inFileName);
			if (resourceSize > 0) {
				// File exists in ResourceManager, use the relative path directly
				fullPath = inFileName;
				isResourceFile = true;
				SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer::createSpriteFromSpriterFile found in resources [%s]", inFileName); )
			}
		}
		
		// If not found in resources, fall back to file system path resolution
		if (!isResourceFile) {
			fullPath = OS::getApplicationResourceDirectory();
			fullPath += inFileName;
			fullPath = OS::makeCanonicalPath(fullPath.c_str());
		#ifndef PLATFORM_WIN32
			DEBUG_ASSERT(fullPath[0] == '/', "Full path doesn't start with '/'!");
		#endif
		}
	}
	SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer::createSpriteFromSpriterFile [%s] [%s]", inFileName, fullPath.c_str()); )

	bool needLoad = true;
	std::shared_ptr<SpriterEngine::SpriterModel> spriterModel;
	// check if we already have this Spriter data cached
	for (auto itr = mModels.begin(); itr != mModels.end(); ++itr) {
		const auto& pair = *itr;
		if (pair.first == fullPath) {
			needLoad = false;
			spriterModel = pair.second;
			SPRITELAYER_DEBUG_ONLY( DEBUG_PRINT("SpriteLayer::createSpriteFromSpriterFile [%s] [%s] found in cache", inFileName, fullPath.c_str()); )
			break;
		}
	}
	// load the Spriter file if we don't have it cached
	if (needLoad) {
		// Create new factories for this SpriterModel - each SpriterModel owns its factories
		PDGFileFactory* fileFactory = new PDGFileFactory();
		PDGObjectFactory* objectFactory = new PDGObjectFactory();
		spriterModel = std::make_shared<SpriterEngine::SpriterModel>(fullPath, fileFactory, objectFactory);
		mModels.push_back(std::make_pair(fullPath, spriterModel));
	}
	// create a sprite for the specified entity (or the first entity if no name given)
	Sprite* result = nullptr;
	SpriterEngine::EntityInstance* entityInstance = nullptr;
	if (inEntityName) {
		entityInstance = spriterModel->getNewEntityInstance(inEntityName);
	} else {
		// Create first entity
		entityInstance = spriterModel->getNewEntityInstance(0);
	}
	if (entityInstance) {
		result = new Sprite(entityInstance, spriterModel);
		addSprite(result);
	}
	return result;
}

// create a sprite from a previously loaded Spriter file(s)
// createSpriteLayerFromSpriterFile() and createSpriteFromSpriterFile() both
// cache their data for later use by this call
Sprite* SpriteLayer::createSpriteFromSpriterEntity(const char* inEntityName) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Sprite creation must occur outside a modifier");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mUseChipmunkPhysics && cpSpaceIsLocked(getSpace()))throw std::logic_error("Create sprites outside locked physics callbacks");
#endif
	Sprite* result = nullptr;
	for (auto itr = mModels.begin(); itr != mModels.end(); ++itr) {
		const auto& spriterModel = itr->second;
		SpriterEngine::EntityInstance* entityInstance = spriterModel->getNewEntityInstance(inEntityName);
		if (entityInstance) {
			result = new Sprite(entityInstance, spriterModel);
			addSprite(result);
			return result;
		}
	}
	return nullptr;
}

// Character map management
void SpriteLayer::applyCharacterMapToAll(const char* mapName) {
	if (mapName) {
		Sprite* sprite = mFirstSprite;
		while (sprite) {
			if (sprite->isSpriterSprite()) {
			sprite->applyCharacterMap(mapName);
			}
			sprite = sprite->mNextSprite;
		}
	}
}

void SpriteLayer::removeCharacterMapFromAll(const char* mapName) {
	if (mapName) {
		Sprite* sprite = mFirstSprite;
		while (sprite) {
			if (sprite->isSpriterSprite()) {
				sprite->removeCharacterMap(mapName);
			}
			sprite = sprite->mNextSprite;
		}
	}
}

// Event system (basic, triggers only)
void SpriteLayer::enableSpriterEvents(bool enable) {
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		if (sprite->isSpriterSprite()) {
			sprite->enableSpriterEvents(enable);
		}
		sprite = sprite->mNextSprite;
	}
}

#endif // PDG_SPRITER_SUPPORT

    
#ifdef PDG_USE_CHIPMUNK_PHYSICS
cpSpace*
SpriteLayer::getSpace() {
	if (!mUseChipmunkPhysics) return 0;
    if (mManager) return mManager->mSpace;
    if (!mDetachedSpace) mDetachedSpace=cpSpaceNew();
    return mDetachedSpace;
}

void SpriteLayer::setGravity(float gravity) {
    if (!std::isfinite(gravity)) throw std::invalid_argument("Gravity must be finite");
    mGravity=gravity;
    if (mUseChipmunkPhysics) cpSpaceSetGravity(getSpace(),cpv(0,gravity));
}

void
SpriteLayer::setDamping(float damping) {
	if (!mUseChipmunkPhysics) return;
    cpSpaceSetDamping(getSpace(), damping);
}
#endif // PDG_USE_CHIPMUNK_PHYSICS

#ifndef PDG_NO_GUI
SpriteLayer::SpriteLayer(Port* port): 
	mPort(nullptr),
	mHidden(false), mAnimating(true), mDoCollisions(false), 
	mWantsMouseOver(false), mWantsClicks(false),
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    mGravity(0.0), mUseChipmunkPhysics(false), mIsStaticLayer(false),
  #endif
	mNextLayer(0), mPrevLayer(0), mFirstSprite(0), mLastSprite(0),
	mSerFlags(ser_Full),
	iid(sUniqueLayerId++)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSpriteLayerScriptObj);
#endif
    layerId = gNextLayerId++;
    setSpritePort(port);
}
#endif // ! PDG_NO_GUI

SpriteLayer::SpriteLayer(): 
  #ifndef PDG_NO_GUI
	mPort(0),
  #endif // ! PDG_NO_GUI
	mHidden(false), mAnimating(true), mDoCollisions(false), 
	mWantsMouseOver(false), mWantsClicks(false),
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    mGravity(0.0), mUseChipmunkPhysics(false), mIsStaticLayer(false),
  #endif
	mNextLayer(0), mPrevLayer(0), mFirstSprite(0), mLastSprite(0),
	mSerFlags(ser_Full),
	iid(sUniqueLayerId++)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSpriteLayerScriptObj);
#endif
    layerId = gNextLayerId++;
}

SpriteLayer::~SpriteLayer() {
    setCamera(nullptr);
#ifndef PDG_NO_GUI
    setSpritePort(nullptr);
#endif
    removeAllParticleEmitters();
    removeAllParticles();
    for (auto* particle : mParticleStep) particle->release();
	SPRITELAYER_DEBUG_ONLY( OS::_DOUT("dt SpriteLayer %p", this); )
  #ifndef PDG_NO_EVENT_QUEUE
	EventManager* eventMgr = EventManager::getSingletonInstance();
	if (eventMgr) {
		// remove all enqueued events that are from or reference this layer
		EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::~SpriteLayer removing enqueued events for layer %p", this));
		eventMgr->RemoveEnqueuedEvents([this](EventManager::EventQueueEntry entry) {
			if (entry.emitter == this) {
				EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::~SpriteLayer removing event for layer %p type: %d", this, entry.eventType));
				return true;
			}
			if (entry.eventType == eventType_SpriteLayer) {
				SpriteLayerInfo* sli = static_cast<SpriteLayerInfo*>(entry.userData->getData());
				if (sli->actingLayer == this) {
					EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::~SpriteLayer removing SpriteLayerInfo event for layer %p eventType_SpriteLayer", this));
					return true;
				}
			}
			if (entry.eventType == eventType_SpriteCollide) {
				SpriteCollideInfo* sci = static_cast<SpriteCollideInfo*>(entry.userData->getData());
				if (sci->inLayer == this) {
					EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::~SpriteLayer removing SpriteCollideInfo event for layer %p id: %d", this, sci->id));
					return true;
				}
			}
			if (entry.eventType == eventType_SpriteAnimate || entry.eventType == eventType_SpriteTriggerEvent) {
				SpriteAnimateInfo* sli = static_cast<SpriteAnimateInfo*>(entry.userData->getData());
				if (sli->inLayer == this) {
					EVENTS_DEBUG_ONLY(OS::_DOUT("SpriteLayer::~SpriteLayer removing SpriteAnimateInfo event for layer %p id: %d", this, sli->id));
					return true;
				}
			}
			return false;
		});
	}
  #endif // ! PDG_NO_EVENT_QUEUE
    // Sprites retain their imported model independently of this cache. Removed
    // or transferred sprites keep playback, bindings, modifiers and artwork.
    removeAllSprites();
    for(auto* layer=(mManager ? mManager->mFirstLayer : nullptr);layer;layer=layer->mNextLayer) {
        auto& links=layer->mCollideLayers;
        std::erase(links, this);
    }
#ifdef PDG_SPRITER_SUPPORT
    mModels.clear();
#endif
	if (mManager) mManager->removeLayer(this);
  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupSpriteLayerScriptObject(mSpriteLayerScriptObj);
  #endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mDetachedSpace)cpSpaceFree(mDetachedSpace);
#endif
    SPRITELAYER_DEBUG_ONLY(OS::_DOUT("DONE SpriteLayer::~SpriteLayer %p", this));
}

#ifndef PDG_NO_GUI
SpriteLayer* createSpriteLayer(Port* port) {
	// create sprite manager singleton instance if necessary
	SpriteLayer* layer = SpriteManager::createSpriteLayer(port);
	SpriteManager::getSingletonInstance()->addLayer(layer);
	return layer;
}
#else
SpriteLayer* createSpriteLayer() {
	// create sprite manager singleton instance if necessary
	SpriteLayer* layer = SpriteManager::createSpriteLayer();
	SpriteManager::getSingletonInstance()->addLayer(layer);
	return layer;
}
#endif // ! PDG_NO_GUI

#ifdef PDG_SPRITER_SUPPORT
#ifndef PDG_NO_GUI
SpriteLayer* createSpriteLayerFromSpriterFile(const char* layerSpriterFile, bool addSprites, Port* port) 
#else
SpriteLayer* createSpriteLayerFromSpriterFile(const char* layerSpriterFile, bool addSprites)
#endif
{
	// create sprite manager singleton instance if necessary
	#ifndef PDG_NO_GUI
		SpriteLayer* layer = SpriteManager::createSpriteLayer(port);
	#else
		SpriteLayer* layer = SpriteManager::createSpriteLayer();
	#endif
	SpriteManager::getSingletonInstance()->addLayer(layer);
	std::string fullPath;
	if (layerSpriterFile[0] == '/') {
		fullPath = layerSpriterFile;
	} else {
		fullPath = OS::getApplicationResourceDirectory();
		fullPath += layerSpriterFile;
        fullPath = OS::makeCanonicalPath(fullPath.c_str());

		DEBUG_ASSERT(fullPath[0] == '/', "Full path doesn't start with '/'!");
	}

	// Create factories for this SpriterModel - the SpriterModel will take ownership
	PDGFileFactory* fileFactory = new PDGFileFactory();
	PDGObjectFactory* objectFactory = new PDGObjectFactory();
	
	// this can't possibly be cached already, we just created the sprite layer
	auto spriterModel = std::make_shared<SpriterEngine::SpriterModel>(fullPath, fileFactory, objectFactory);
    layer->mModels.push_back(std::make_pair(fullPath, spriterModel));
	if (addSprites) {
		// Loop through all the entities in the model and create a sprite for each one
		// SpriterEngine::EntityInstance* entityInstance = spriterModel->getNewEntityInstance(0);
		// while (entityInstance) {
		//	layer->createSpriterSprite(spriterModel, entityInstance->getName().c_str());
		// }
	}
	return layer;
}
#endif // PDG_SPRITER_SUPPORT

void cleanupLayer(SpriteLayer* layer) {
	SPRITELAYER_DEBUG_ONLY( OS::_DOUT("cleanupLayer %p", layer); )
	if (layer) {
		SpriteManager::cleanupLayer(layer);
	}
}

SpriteLayer* SpriteLayer::getLayer(long id) {
	SpriteLayer* layer = SpriteManager::getSingletonInstance()->mFirstLayer;
	while (layer && (id != layer->layerId)) {
		layer = layer->mNextLayer;
	}
	return layer ? layer : Scene::findLayer(id);
}

	
} // end namespace pdg
