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
#define PDG_SPRITE_LAYER_STREAM_VERSION	5

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

void SpriteLayer::setSerializationFlags(uint32 flags) {
	mSerFlags = flags;
}

void SpriteLayer::validateInitialSnapshot() const {
    if (mControlledBy || !mLinkedLayers.empty() || !mCollideLayers.empty())
        throw std::runtime_error("Layer snapshots do not yet support links to other layers");
    if (!mHelpers.empty()) throw std::runtime_error("Layer snapshots cannot save callback helpers");
    for (const auto& animation : mAnimations) {
        if (std::find(gEasingFunctions, gEasingFunctions + NUM_BUILTIN_EASINGS, animation.easing)
                == gEasingFunctions + NUM_BUILTIN_EASINGS)
            throw std::runtime_error("Layer snapshots cannot save custom easing callbacks");
    }
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
		SIZE_FLOAT_LIST_START(2, 15);
		if (mSerFlags & ser_Positions) {
			SIZE_NON_ZERO_F(mLocation.x, 0);
			SIZE_NON_ZERO_F(mLocation.y, 1);
			SIZE_NON_ZERO_F(mFacing, 2);
		}
		if (mSerFlags & ser_Sizes) {
			SIZE_NON_ZERO_F(mHeight, 3);
			SIZE_NON_ZERO_F(mWidth, 4);
		}
		if (mSerFlags & ser_LayerDraw) {
		  #ifndef PDG_NO_GUI
			SIZE_NON_ZERO_F(mOrigin.x, 5);
			SIZE_NON_ZERO_F(mOrigin.y, 6);
			SIZE_NON_ZERO_F(mZoom, 7);
		  #endif
		}
		if (mSerFlags & (ser_Animations | ser_Motion) ) {
			SIZE_NON_ZERO_F(mCenterOffset.x, 8);
			SIZE_NON_ZERO_F(mCenterOffset.y, 9);
		}
		if (mSerFlags & ser_Motion) {
			SIZE_NON_ZERO_F(mDeltaXPerMs, 10);
			SIZE_NON_ZERO_F(mDeltaYPerMs, 11);
			SIZE_NON_ZERO_F(mDeltaWidthPerMs, 12);
			SIZE_NON_ZERO_F(mDeltaHeightPerMs, 13);
			SIZE_NON_ZERO_F(mDeltaFacingPerMs, 14);
		}
		SIZE_FLOAT_LIST_END(totalSize);
        if (mSerFlags & ser_Sizes) {
            SnapshotWriter out(serializer,false);out.floating(mScaleX,1);out.floating(mScaleY,1);totalSize+=out.size();
        }

		if (mSerFlags & ser_Animations) totalSize += tweenSerializedSize(serializer);

		if (mSerFlags & ser_Forces) {
//			totalSize += 4;  // 1 float: mGravity
		}
		if (mSerFlags & ser_Physics) {
		}

		if (mSerFlags & ser_InitialData) {
	//		mNextLayer(0), mPrevLayer(0), mFirstSprite(0), mLastSprite(0),
	//		mControlledBy(0),
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
	  #ifndef PDG_NO_GUI
			(mAutoCenter ? 		1 << 5 : 0) |
			(mFixedMoveAxis ? 	1 << 6 : 0) |
	  #endif
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
			(mKeepGravityDownward ? 1 << 7 : 0) |
			(mUseChipmunkPhysics ? 	1 << 8 : 0) |
			(mIsStaticLayer ? 		1 << 9 : 0) |
	  #endif
            (1 << 10) | (mSchedulePaused ? 1 << 11 : 0) |
            (mFlipX ? 1 << 12 : 0) | (mFlipY ? 1 << 13 : 0) | (1 << 14);
	  #ifdef PDG_TAG_SERIALIZED_DATA
		serializer->serialize_4(PDG_SPRITE_LAYER_MAGIC_NUMBER);
	  #endif
		serializer->serialize_2u(layerFlags);
		if (mSerFlags & ser_InitialData) {
			serializer->serialize_uint(iid);
			serializer->serialize_uint(layerId);
            const auto now = OS::getMilliseconds();
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
		SERIALIZE_FLOAT_LIST_START(2, 15);
		if (mSerFlags & ser_Positions) {
			SERIALIZE_NON_ZERO_F(mLocation.x, 0);
			SERIALIZE_NON_ZERO_F(mLocation.y, 1);
			SERIALIZE_NON_ZERO_F(mFacing, 2);
		}
		if (mSerFlags & ser_Sizes) {
			SERIALIZE_NON_ZERO_F(mHeight, 3);
			SERIALIZE_NON_ZERO_F(mWidth, 4);
		}
		if (mSerFlags & ser_LayerDraw) {
		  #ifndef PDG_NO_GUI
			SERIALIZE_NON_ZERO_F(mOrigin.x, 5);
			SERIALIZE_NON_ZERO_F(mOrigin.y, 6);
			SERIALIZE_NON_ZERO_F(mZoom, 7);
		  #else
			SERIALIZE_NON_ZERO_F(0.0f, 5);  // write zeroes so this stream will be readable by non-gui builds
			SERIALIZE_NON_ZERO_F(0.0f, 6);
			SERIALIZE_NON_ZERO_F(0.0f, 7);
		  #endif
		}
		if (mSerFlags & (ser_Animations | ser_Motion) ) {
			SERIALIZE_NON_ZERO_F(mCenterOffset.x, 8);
			SERIALIZE_NON_ZERO_F(mCenterOffset.y, 9);
		}
		if (mSerFlags & ser_Motion) {
			SERIALIZE_NON_ZERO_F(mDeltaXPerMs, 10);
			SERIALIZE_NON_ZERO_F(mDeltaYPerMs, 11);
			SERIALIZE_NON_ZERO_F(mDeltaWidthPerMs, 12);
			SERIALIZE_NON_ZERO_F(mDeltaHeightPerMs, 13);
			SERIALIZE_NON_ZERO_F(mDeltaFacingPerMs, 14);
		}
		SERIALIZE_FLOAT_LIST_END(2);
        if (mSerFlags & ser_Sizes) { SnapshotWriter out(serializer,true);out.floating(mScaleX,1);out.floating(mScaleY,1); }
		
		if (mSerFlags & ser_Animations) serializeTweens(serializer);

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
    auto* space = SpriteManager::getSingletonInstance()->mSpace;
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
    // Rebase tween pointers before replacing live state. The staging layer has
    // no bodies in the shared solver and no application callbacks.
    const auto from = staged.tweenFields(), to = tweenFields();
    if (from.size() != to.size()) throw std::runtime_error("Incompatible Layer tween fields");
    auto animations = staged.mAnimations;
    for (auto& animation : animations) {
        const auto field = std::find(from.begin(), from.end(), animation.value);
        if (field == from.end()) throw std::runtime_error("Invalid Layer tween target");
        animation.value = const_cast<float*>(to[field - from.begin()]);
    }
    removeAllParticleEmitters();
    removeAllParticles();
    removeAllSprites();
    for (size_t i = 0; i < from.size(); ++i)
        if (from[i] && to[i]) *const_cast<float*>(to[i]) = *from[i];
    mAnimations = std::move(animations);
    mDelaySeconds = staged.mDelaySeconds; mSchedulePaused = staged.mSchedulePaused;
    mAppendAnimation = staged.mAppendAnimation; mAnimationOperation = staged.mAnimationOperation; mWaitPending = staged.mWaitPending;
    mFlipX = staged.mFlipX; mFlipY = staged.mFlipY;
    mHidden = staged.mHidden; mAnimating = staged.mAnimating; mDoCollisions = staged.mDoCollisions;
    mWantsMouseOver = staged.mWantsMouseOver; mWantsClicks = staged.mWantsClicks;
    iid = staged.iid; layerId = staged.layerId;
    mDoneFadingInAt = staged.mDoneFadingInAt; mDoneFadingOutAt = staged.mDoneFadingOutAt;
    mFacingCos = std::cos(mFacing); mFacingSin = std::sin(mFacing);
#ifndef PDG_NO_GUI
    mOrigin = staged.mOrigin; mAutoCenter = staged.mAutoCenter; mFixedMoveAxis = staged.mFixedMoveAxis;
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    mKeepGravityDownward = staged.mKeepGravityDownward; mGravity = staged.mGravity;
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
        mSchedulePaused = (layerFlags & (1 << 11)) != 0;
        mFlipX = (layerFlags & (1 << 12)) != 0;
        mFlipY = (layerFlags & (1 << 13)) != 0;
		mAnimating = ((layerFlags & 1 << 1) != 0);
		mDoCollisions = ((layerFlags & 1 << 2) != 0);
		mWantsMouseOver = ((layerFlags & 1 << 3) != 0);
		mWantsClicks = ((layerFlags & 1 << 4) != 0);
	  #ifndef PDG_NO_GUI
		mAutoCenter = ((layerFlags & 1 << 5) != 0);
		mFixedMoveAxis = ((layerFlags & 1 << 6) != 0);
	  #endif
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
		mKeepGravityDownward = ((layerFlags & 1 << 7) != 0);
		mUseChipmunkPhysics = ((layerFlags & 1 << 8) != 0);
		mIsStaticLayer = ((layerFlags & 1 << 9) != 0);
	  #endif
        if (mSerFlags & ser_InitialData) {
            iid = deserializer->deserialize_uint();
            layerId = deserializer->deserialize_uint();
            if (iid == 0 || iid == UINT32_MAX) throw std::runtime_error("Invalid Layer identity");
            sUniqueLayerId = std::max(sUniqueLayerId, iid + 1);
            if (layerId < std::numeric_limits<long>::max()) gNextLayerId = std::max(gNextLayerId, layerId + 1);
            const auto now = OS::getMilliseconds();
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
		DESERIALIZE_FLOAT_LIST_START(2, 15);
		if (mSerFlags & ser_Positions) {
			mLocation.x = DESERIALIZE_NON_ZERO_F(0);
			mLocation.y = DESERIALIZE_NON_ZERO_F(1);
			mFacing = DESERIALIZE_NON_ZERO_F(2);
		}
		if (mSerFlags & ser_Sizes) {
			mHeight = DESERIALIZE_NON_ZERO_F(3);
			mWidth = DESERIALIZE_NON_ZERO_F(4);
		}
		if (mSerFlags & ser_LayerDraw) {
		  #ifndef PDG_NO_GUI
			mOrigin.x = DESERIALIZE_NON_ZERO_F(5);
			mOrigin.y = DESERIALIZE_NON_ZERO_F(6);
			mZoom = DESERIALIZE_NON_ZERO_F(7);
		  #else
			DESERIALIZE_NON_ZERO_F(5);  // mOrigin.x,  read in the values but ignore them
			DESERIALIZE_NON_ZERO_F(6);  // mOrigin.y
			DESERIALIZE_NON_ZERO_F(7);  // mZoom
		  #endif
		}
		if (mSerFlags & (ser_Animations | ser_Motion) ) {
			mCenterOffset.x = DESERIALIZE_NON_ZERO_F(8);
			mCenterOffset.y = DESERIALIZE_NON_ZERO_F(9);
		}
		if (mSerFlags & ser_Motion) {
			mDeltaXPerMs = DESERIALIZE_NON_ZERO_F(10);
			mDeltaYPerMs = DESERIALIZE_NON_ZERO_F(11);
			mDeltaWidthPerMs = DESERIALIZE_NON_ZERO_F(12);
			mDeltaHeightPerMs = DESERIALIZE_NON_ZERO_F(13);
			mDeltaFacingPerMs = DESERIALIZE_NON_ZERO_F(14);
		}
		DESERIALIZE_FLOAT_LIST_END(2);
        if (mSerFlags & ser_Sizes) {
            mScaleX = (layerFlags & (1 << 10)) ? SnapshotReader(deserializer).floating(1) : 1;
            mScaleY = (layerFlags & (1 << 10)) ? SnapshotReader(deserializer).floating(1) : 1;
        }

        if (mSerFlags & ser_Animations) {
            if (layerFlags & (1 << 14)) deserializeTweens(deserializer);
            else { mAnimations.clear(); mDelaySeconds = 0; }
        }

        for (const auto* field : tweenFields())
            if (field && !std::isfinite(*field)) throw std::runtime_error("Non-finite Layer transform or rate");
        mFacingCos = std::cos(mFacing); mFacingSin = std::sin(mFacing);
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
	mDoneFadingInAt = OS::getMilliseconds() + static_cast<ms_time>(std::ceil(durationSeconds * 1000.0));
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		sprite->fadeIn(durationSeconds, easing);
		sprite = sprite->mNextSprite;
	}
}

void	SpriteLayer::fadeOut(double durationSeconds, EasingFunc easing) {
	for (auto* particle : mParticles) particle->fadeTo(0, durationSeconds, easing);
	mDoneFadingOutAt = OS::getMilliseconds() + static_cast<ms_time>(std::ceil(durationSeconds * 1000.0));
	Sprite* sprite = mFirstSprite;
	while (sprite) {
		sprite->fadeOut(durationSeconds, easing);
		sprite = sprite->mNextSprite;
	}
}

// arrange layers
void	SpriteLayer::moveBehind( SpriteLayer* inLayer) {
	SpriteLayer* layer = inLayer;
	SpriteManager::getSingletonInstance()->removeLayer(this);
	if (layer == 0) {
		// behind everything = in front of list
		layer = SpriteManager::getSingletonInstance()->mFirstLayer;
	}
	// update the layer before to point to us
	if (layer && layer->mPrevLayer) {
		layer->mPrevLayer->mNextLayer = this;
		this->mPrevLayer = layer->mPrevLayer;
	} else {
		SpriteManager::getSingletonInstance()->mFirstLayer = this;
		this->mPrevLayer = 0;
	}
	// update the layer after to point to us
	if (layer) {
		layer->mPrevLayer = this;
	} else {
		SpriteManager::getSingletonInstance()->mLastLayer = this;
	}
	mNextLayer = layer;
}


void	SpriteLayer::moveInFrontOf( SpriteLayer* inLayer) {
	SpriteLayer* layer = inLayer;
	SpriteManager::getSingletonInstance()->removeLayer(this);
	if (layer == 0) {
		// put after last layer
		layer = SpriteManager::getSingletonInstance()->mLastLayer;
	}
	// update the layer after to point to us
	if (layer && layer->mNextLayer) {
		layer->mNextLayer->mPrevLayer = this;
		this->mNextLayer = layer->mNextLayer;
	} else {
		SpriteManager::getSingletonInstance()->mLastLayer = this;
		this->mNextLayer = 0;
	}
	// update the layer before to point to us
	if (layer) {
		layer->mNextLayer = this;
	} else {
		SpriteManager::getSingletonInstance()->mFirstLayer = this;
	}
}

int SpriteLayer::getZOrder() {
	int z = 0;
	SpriteLayer* layer = SpriteManager::getSingletonInstance()->mFirstLayer;
	while (layer) {
		if (layer == this) {
			return z;
		} else {
			z++;
			layer = layer->mNextLayer;
		}
	}
	return -1; // this shouldn't ever happen, all layers should be in the SpriteManager
}

void	SpriteLayer::moveWith(SpriteLayer* layer, float moveRatio, float zoomRatio) {
	if (mControlledBy || (layer == 0) ) {
		return;	// already controlled
	}
	mControlledBy = layer;
	LinkedLayerInfo info;
	info.moveRatio = moveRatio;
	info.zoomRatio = zoomRatio;
	info.linkedLayer = this;
	layer->mLinkedLayers.push_back(info);
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

void SpriteLayer::zoomChanged(float deltaZoom) {
    // move any layers we are controlling
    if (mLinkedLayers.size() > 0) {
		for (std::vector<LinkedLayerInfo>::iterator itr = mLinkedLayers.begin(); itr != mLinkedLayers.end(); itr++) {
			float targetZoom = (itr->linkedLayer->mZoom + deltaZoom) * itr->zoomRatio;
			itr->linkedLayer->setZoom(targetZoom);
		}
    }
}

// this is the port that the sprites in this manager will render into
// multiple managers can render into same port creating layers, drawn in order of creation
void    SpriteLayer::setSpritePort(Port* port) {
	mPort = port;
}

// zooming
void
SpriteLayer::setZoom(float zoomLevel) {
    float deltaZoom = zoomLevel - mZoom;
	mZoom = zoomLevel;
    zoomChanged(deltaZoom);
}

void
SpriteLayer::zoomTo(float zoomLevel, double durationSeconds, EasingFunc easing, 
					Rect keepInRect, const Point* centerOn) 
{
    validateAnimationDuration(durationSeconds);
    if (!std::isfinite(zoomLevel) || !easing) throw std::invalid_argument("Invalid zoom target or easing");
    double saveDelay = mDelaySeconds;
    const bool append = mAppendAnimation, waiting = mWaitPending;
    if (centerOn != 0) {
        moveTo(*centerOn, durationSeconds, (zoomLevel < mZoom) ? easeOutExpo : easeInOutQuad);
    }
    mDelaySeconds = saveDelay; mAppendAnimation = append; mWaitPending = waiting;
    if (!centerOn) beginAnimationRequest();
    scheduleAnimation(&mZoom, zoomLevel, durationSeconds, easing);
    finishAnimationRequest();
}


// coordinate conversions, adjusting for offset, zoom and rotation of layer
Point
SpriteLayer::layerToPort(const Point& p) const {
    Point a = layerToPort(Offset(p - mCenterOffset));  // rotate and zoom point to match layer
    // add in offset for layer's location
    a += (mLocation + mCenterOffset)*mZoom + mOrigin;
    return a;
}

Offset
SpriteLayer::layerToPort(const Offset& o) const {
    // rotate about layer center (0,0)
    const float x = o.x * mScaleX * (mFlipX ? -1 : 1);
    const float y = o.y * mScaleY * (mFlipY ? -1 : 1);
    Offset a(x*mFacingCos - y*mFacingSin, x*mFacingSin + y*mFacingCos);
    a *= mZoom;
    return a;
}

RotatedRect
SpriteLayer::layerToPort(const Rect& r) const {
    if (mScaleX != 1 || mScaleY != 1 || mFlipX || mFlipY)
        return RotatedRect(layerToPort(Quad(r)).getBounds());
    RotatedRect rr(r);
    Point cp = layerToPort(r.centerPoint());
    rr.center(Point(0,0));
    rr.top *= mZoom;
    rr.left *= mZoom;
    rr.right *= mZoom;
    rr.bottom *= mZoom;
    rr.center(cp);
    rr.radians = mFacing;
    return rr;
}

RotatedRect
SpriteLayer::layerToPort(const RotatedRect& r) const {
    if (mScaleX != 1 || mScaleY != 1 || mFlipX || mFlipY)
        return RotatedRect(layerToPort(Quad(r)).getBounds());
    RotatedRect rr = layerToPort(static_cast<const Rect&>(r));
    rr.centerOffset = layerToPort(r.centerOffset);
    rr.radians = r.radians + mFacing;
    return rr;
}

Quad
SpriteLayer::layerToPort(const Quad& q) const {
    Quad nq;
    for (int i = 0; i<4; i++) {
        nq.points[i] = layerToPort(q.points[i]);
    }
    return nq;
}


Point
SpriteLayer::portToLayer(const Point& p) const {
    Point a = p - mOrigin;
    a -= (mLocation + mCenterOffset)*mZoom;
    Point b = portToLayer(Offset(a)) + mCenterOffset;
    return b;
}

Offset
SpriteLayer::portToLayer(const Offset& o) const {
    if (mZoom == 0 || mScaleX == 0 || mScaleY == 0)
        throw std::domain_error("Cannot invert a zero-scale layer transform");
    Offset a = o / mZoom;
    Point b(a.x*cos(-mFacing) - a.y*sin(-mFacing), a.x*sin(-mFacing) + a.y*cos(-mFacing));
    return Offset(b.x / (mScaleX * (mFlipX ? -1 : 1)), b.y / (mScaleY * (mFlipY ? -1 : 1)));
}
    
RotatedRect
SpriteLayer::portToLayer(const Rect& r) const {
    if (mScaleX != 1 || mScaleY != 1 || mFlipX || mFlipY)
        return RotatedRect(portToLayer(Quad(r)).getBounds());
    RotatedRect rr(r);
    Point cp = portToLayer(r.centerPoint());
    rr.center(Point(0,0));
    rr.top /= mZoom;
    rr.left /= mZoom;
    rr.right /= mZoom;
    rr.bottom /= mZoom;
    rr.center(cp);
    rr.radians = -mFacing;
    return rr;
}

RotatedRect
SpriteLayer::portToLayer(const RotatedRect& r) const {
    if (mScaleX != 1 || mScaleY != 1 || mFlipX || mFlipY)
        return RotatedRect(portToLayer(Quad(r)).getBounds());
    RotatedRect rr = portToLayer(static_cast<const Rect&>(r));
    rr.centerOffset = portToLayer(r.centerOffset);
    rr.radians = r.radians - mFacing;
    return rr;
}

Quad
SpriteLayer::portToLayer(const Quad& q) const {
    Quad nq;
    for (int i = 0; i<4; i++) {
        nq.points[i] = portToLayer(q.points[i]);
    }
    return nq;
}

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

	Sprite* sprite = mFirstSprite;
	while (sprite && !mHidden) {
		sprite->draw();
		sprite = sprite->mNextSprite;
	}

    if (!mHidden) for (auto* particle : mParticles) particle->draw();
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
        r.center(mCenterOffset);
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

// Zoom keeps a stable channel ID even in headless readers.
std::vector<const float*> SpriteLayer::tweenFields() const {
    auto fields = AnimatedBase::tweenFields();
#ifndef PDG_NO_GUI
    fields.push_back(&mZoom);
#else
    fields.push_back(nullptr);
#endif
    return fields;
}

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
    particle->mLayer = nullptr; particle->syncPhysicsSolver();
    if (particle->getParticleEmitter()) particle->getParticleEmitter()->stopEmitting();
    mParticles.erase(std::find(mParticles.begin(), mParticles.end(), particle)); particle->release();
}
void SpriteLayer::removeAllParticles() { while (!mParticles.empty()) removeParticle(mParticles.back()); }
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
void SpriteLayer::prepareColliders(void* space) {
    bool enabled=mDoCollisions || !mCollideLayers.empty();
    if(!enabled)for(auto* layer=SpriteManager::getSingletonInstance()->mFirstLayer;layer;layer=layer->mNextLayer)
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
    for(auto* other=SpriteManager::getSingletonInstance()->mFirstLayer;other;other=other->mNextLayer)
        if(other!=this && iid<other->iid && allowsColliderWorld(other))collect(other);
    if(colliders.empty()&&!mCollisionWorld)return;
    if(!mCollisionWorld)mCollisionWorld=std::make_unique<CollisionWorld>();
    mCollisionWorld->step(colliders,seconds,[this](const Collider& a,const Collider& b) {
        return a.world()==this || b.world()==this;
    });
}

void
SpriteLayer::animateLayer(ms_delta msElapsed) {
    // Contacts may request layer cleanup even when a native caller steps a layer directly.
    struct Traversal {
        SpriteManager* manager = SpriteManager::getSingletonInstance();
        Traversal() { ++manager->mLayerUpdateDepth; }
        ~Traversal() { manager->finishLayerTraversal(); }
    } traversal;
	AnimatedBase::animate(static_cast<double>(msElapsed) / 1000.0);

	mFacingCos = cos(mFacing); // cache these frequently used values
	mFacingSin = sin(mFacing);
	
	SpriteLayerInfo evntInfo;
	ms_time currMs = OS::getMilliseconds();
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

void
SpriteLayer::locationChanged(const Offset& delta) {
  #ifndef PDG_NO_GUI
	if (!mControlledBy) {
		if (mAutoCenter) {
			if (mFixedMoveAxis) {
				Offset a(delta.x*cos(-mFacing) - delta.y*sin(-mFacing), delta.x*sin(-mFacing) + delta.y*cos(-mFacing));
				mLocation -= delta;
				mLocation += a;
				mCenterOffset -= a;
			} else {
				mCenterOffset -= delta;
			}
		} else if (mFixedMoveAxis) {
			// TODO This mode is broken, fix it
	        Offset a(delta.x*mFacingCos - delta.y*mFacingSin, delta.x*mFacingSin + delta.y*mFacingCos);
	        mLocation -= delta;
	        mLocation += a;
		}
    }
  #endif // !PDG_NO_GUI
    // move any layers we are controlling
    if (mLinkedLayers.size() > 0) {
		for (std::vector<LinkedLayerInfo>::iterator itr = mLinkedLayers.begin(); itr != mLinkedLayers.end(); itr++) {
			Offset targetDelta = delta * itr->moveRatio;
			itr->linkedLayer->moveBy(targetDelta);
		}
    }
}

    
#ifndef PDG_NO_GUI
void    
SpriteLayer::easingCompleted(const Animation& a) {
	SpriteLayerInfo evntInfo;
    if (a.value == &mZoom) {
        // this is a zoom operation, so send the proper notification
        evntInfo.actingLayer = this;
        evntInfo.action = SpriteLayer::action_ZoomComplete;
        evntInfo.millisec = OS::getMilliseconds();
        postEvent(eventType_SpriteLayer, &evntInfo);
    }
}

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
    return SpriteManager::getSingletonInstance()->mSpace;
}

void
SpriteLayer::setGravity(float gravity, bool keepItDownward) {
	if (!mUseChipmunkPhysics) return;
    mGravity = gravity;
    mKeepGravityDownward = keepItDownward;
    if (mKeepGravityDownward) {
        cpSpaceSetGravity(getSpace(), cpv(mGravity * mFacingSin, mGravity * mFacingCos));
    } else {
        cpSpaceSetGravity(getSpace(), cpv(0, mGravity));
    }
}

void
SpriteLayer::setKeepGravityDownward(bool keepItDownward) {
	if (!mUseChipmunkPhysics) return;
    setGravity(mGravity, keepItDownward);
}

void
SpriteLayer::setDamping(float damping) {
	if (!mUseChipmunkPhysics) return;
    cpSpaceSetDamping(getSpace(), damping);
}
#endif // PDG_USE_CHIPMUNK_PHYSICS

void	
SpriteLayer::rotationChanged(float deltaRadians) {
    mFacingCos = cos(mFacing);
    mFacingSin = sin(mFacing);
    // rotate any layers we are controlling
    if (mLinkedLayers.size() > 0) {
		for (std::vector<LinkedLayerInfo>::iterator itr = mLinkedLayers.begin(); itr != mLinkedLayers.end(); itr++) {
			itr->linkedLayer->rotateBy(deltaRadians);
		}
    }
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    // do this anytime we change rotation
    if (mUseChipmunkPhysics && mKeepGravityDownward) {
        cpSpaceSetGravity(getSpace(), cpv(mGravity * mFacingSin, mGravity * mFacingCos));
    }
  #endif //PDG_USE_CHIPMUNK_PHYSICS
}

#ifndef PDG_NO_GUI
SpriteLayer::SpriteLayer(Port* port): 
    noZoom(1.0f),
	mPort(port), mOrigin(0,0), 
	mHidden(false), mAnimating(true), mDoCollisions(false), 
	mWantsMouseOver(false), mWantsClicks(false),
	mZoom(1.0), // mTargetZoom(1.0), mDeltaZoomPerMs(0.0),
    mAutoCenter(false), mFixedMoveAxis(true), 
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    mGravity(0.0), mKeepGravityDownward(false), mUseChipmunkPhysics(false), mIsStaticLayer(false),
  #endif
	mNextLayer(0), mPrevLayer(0), mFirstSprite(0), mLastSprite(0),
	mControlledBy(0),
	mFacingCos(1.0), mFacingSin(0.0),
	mSerFlags(ser_Full),
	iid(sUniqueLayerId++)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSpriteLayerScriptObj);
#endif
    layerId = gNextLayerId++;
}
#endif // ! PDG_NO_GUI

SpriteLayer::SpriteLayer(): 
    noZoom(1.0f),
  #ifndef PDG_NO_GUI
	mPort(0), mOrigin(0,0), 
  #endif // ! PDG_NO_GUI
	mHidden(false), mAnimating(true), mDoCollisions(false), 
	mWantsMouseOver(false), mWantsClicks(false),
  #ifndef PDG_NO_GUI
	mZoom(1.0), // mTargetZoom(1.0), mDeltaZoomPerMs(0.0),
    mAutoCenter(false), mFixedMoveAxis(true), 
  #endif // ! PDG_NO_GUI
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    mGravity(0.0), mKeepGravityDownward(false), mUseChipmunkPhysics(false), mIsStaticLayer(false),
  #endif
	mNextLayer(0), mPrevLayer(0), mFirstSprite(0), mLastSprite(0),
	mControlledBy(0),
	mFacingCos(1.0), mFacingSin(0.0),
	mSerFlags(ser_Full),
	iid(sUniqueLayerId++)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSpriteLayerScriptObj);
#endif
    layerId = gNextLayerId++;
}

SpriteLayer::~SpriteLayer() {
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
    for(auto* layer=SpriteManager::getSingletonInstance()->mFirstLayer;layer;layer=layer->mNextLayer) {
        auto& links=layer->mCollideLayers;
        std::erase(links, this);
    }
#ifdef PDG_SPRITER_SUPPORT
    mModels.clear();
#endif
	SpriteManager::getSingletonInstance()->removeLayer(this);
  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupSpriteLayerScriptObject(mSpriteLayerScriptObj);
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
	return layer;
}

	
} // end namespace pdg
