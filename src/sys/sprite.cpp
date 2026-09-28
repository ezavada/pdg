// -----------------------------------------------
// sprite.cpp
// 
// sprite functionality
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
#include <numbers>
#include "snapshot-codec.h"
#include "physics-scaling.h"

#include "pdg/sys/sprite.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/spritelayer.h"
#include "pdg/sys/os.h"
#include "pdg/sys/events.h"
#include "pdg/sys/image.h"
#include "pdg/sys/imagestrip.h"
#include "pdg/sys/iserializer.h"
#include "pdg/sys/ideserializer.h"

#include "image-impl.h"

#ifndef PDG_NO_GUI
  #include "pdg/sys/port.h"
#ifdef PDG_SPRITER_SUPPORT
  #include "spriter/pdg_image_file.h"
#endif
#endif

#include "collisiondetection.h"
#include "spritemanager.h"
#include "layer-snapshot-scope.h"
#include "physics-graph-snapshot.h"
#ifndef PDG_NO_GUI
#include "drawing-snapshot.h"
#endif

#ifdef PDG_SPRITER_SUPPORT
    #include "spriter/pdg_box_instance_info.h"
#endif

// Spriter includes
#ifdef PDG_SPRITER_SUPPORT
  #include "spriterengine/objectinfo/boxinstanceinfo.h"
  #include "spriterengine/global/settings.h"
  #include "spriter/pdg_spriter_transform.h"
  #include "spriter/pdg_spriter_pose.h"
  #include "spriter/pdg_file_factory.h"
  #include <stdexcept>
#endif // PDG_SPRITER_SUPPORT

#include <cmath>
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

#ifdef PDG_USE_CHIPMUNK_PHYSICS
  #define USE_CHIPMUNK (mBody && mLayer && mLayer->mUseChipmunkPhysics)
  #define CONSTRAINT_IS_CLASS(constraint, _klass)  cpConstraintIs##_klass(constraint)
#else
  #define USE_CHIPMUNK false
#endif

// #ifdef DEBUG
//   #define SPRITE_INTERNAL_DEBUG 1
//   #define SPRITE_MOTION_DEBUG 1
//   #define SPRITE_DEBUG_COLLISIONS 1
//	 #define DEBUG_SPRITE_ANIMATE 1
// #endif

#ifndef DEBUG_SPRITE_ANIMATE
  #define SPRITEANIMATE_DEBUG_ONLY( ops )
#else
  #define SPRITEANIMATE_DEBUG_ONLY( ops ) ops
#endif

#ifndef DEBUG_EVENTS
  #define EVENTS_DEBUG_ONLY( ops )
#else
  #define EVENTS_DEBUG_ONLY( ops ) ops
#endif

#ifndef PDG_DEBUG_SPRITER_COLLISIONS
  #define SPRITER_COLLISION_DEBUG_ONLY( ops )
#else
  // Spriter collision tracing is opt-in so debug/test builds stay quiet by default.
  #define SPRITER_COLLISION_DEBUG_ONLY( ops ) DEBUG_ONLY( ops )
#endif

#ifndef MIN_INT16
#define MIN_INT16 -32767
#endif
#ifndef MAX_INT16
#define MAX_INT16 32767
#endif

#define BREAK_COEFFICIENT  0.9f  // multiplier to get breaking force from max force on a joint

#define PDG_SPRITE_MAGIC_NUMBER    		0x45258805

#ifndef PDG_UNSAFE_SERIALIZATION
#define PDG_TAG_SERIALIZED_DATA
#endif


namespace pdg {

// list of variables in a sprite that can be animated
enum {
	var_None = 0,
	var_LocX, var_LocY,
	var_DeltaX, var_DeltaY,
	var_Width, var_Height,
	var_Facing,
	var_CenterOffsetX, var_CenterOffsetY,
	var_Opacity, var_Spin, var_ScaleX, var_ScaleY, var_StretchX, var_StretchY
};

static uint32 sUniqueSpriteId = 1;

// Joint type IDs - defined outside #ifdef so serialization can work with/without Chipmunk
enum { 
	PinJointId = 1, SlideJointId = 2, PivotJointId = 3, GrooveJointId = 4, DampedSpringId = 5,
	DampedRotarySpringId = 6, RotaryLimitJointId = 7, RatchetJointId = 8, GearJointId = 9, 
	SimpleMotorId = 10
};

// cpFloat type - defined for serialization compatibility even without Chipmunk
#ifndef PDG_USE_CHIPMUNK_PHYSICS
typedef double cpFloat;  // Chipmunk uses double by default
#endif

#ifdef PDG_USE_CHIPMUNK_PHYSICS
uint8 getJointTypeId(cpConstraint* constraint);
cpConstraint* allocConstraintByJointTypeId(uint8 jointTypeId);
Point convertPoint(const cpVect& v);
cpVect convertPoint(const Point& p);
	
uint8 getJointTypeId(cpConstraint* constraint) {
	if (CONSTRAINT_IS_CLASS(constraint, PinJoint) ) {
		return PinJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, SlideJoint) ) {
		return SlideJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, PivotJoint) ) {
		return PivotJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, GrooveJoint) ) {
		return GrooveJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, DampedSpring) ) {
		return DampedSpringId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, DampedRotarySpring) ) {
		return DampedRotarySpringId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, RotaryLimitJoint) ) {
		return RotaryLimitJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, RatchetJoint) ) {
		return RatchetJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, GearJoint) ) {
		return GearJointId;
	}
	if (CONSTRAINT_IS_CLASS(constraint, SimpleMotor) ) {
		return SimpleMotorId;
	}
	return 0;
}
cpConstraint* allocConstraintByJointTypeId(uint8 jointTypeId) {
	if (jointTypeId == PinJointId) {
		return (cpConstraint*)cpPinJointAlloc();
	}
	if (jointTypeId == SlideJointId) {
		return (cpConstraint*)cpSlideJointAlloc();
	}
	if (jointTypeId == PivotJointId) {
		return (cpConstraint*)cpPivotJointAlloc();
	}
	if (jointTypeId == GrooveJointId) {
		return (cpConstraint*)cpGrooveJointAlloc();
	}
	if (jointTypeId == DampedSpringId) {
		return (cpConstraint*)cpDampedSpringAlloc();
	}
	if (jointTypeId == DampedRotarySpringId) {
		return (cpConstraint*)cpDampedRotarySpringAlloc();
	}
	if (jointTypeId == RotaryLimitJointId) {
		return (cpConstraint*)cpRotaryLimitJointAlloc();
	}
	if (jointTypeId == RatchetJointId) {
		return (cpConstraint*)cpRatchetJointAlloc();
	}
	if (jointTypeId == GearJointId) {
		return (cpConstraint*)cpGearJointAlloc();
	}
	if (jointTypeId == SimpleMotorId) {
		return (cpConstraint*)cpSimpleMotorAlloc();
	}
	return 0;
}

inline Point convertPoint(const cpVect& v) {
	return Point(v.x, v.y);
}

inline cpVect convertPoint(const Point& p) {
	return cpv(p.x, p.y);
}

#endif // PDG_USE_CHIPMUNK_PHYSICS

// Initial records must not silently discard graph state whose restore path is
// not implemented. Incremental updates intentionally select only their flags.
#include "sprite-animation-snapshot.inc"

void Sprite::validateInitialSnapshot(bool layerGraph) const {
    SpriteAnimationSnapshot::validate(*this);
    if (mAttachmentPart && !layerGraph)
        throw std::runtime_error("Save mounted Sprite relationships through a SpriteLayer snapshot");
    for (auto* part : mParts) part->validateSnapshot(layerGraph);
    if (!mHelpers.empty())
        throw std::runtime_error("Sprite snapshots cannot save callback helpers");
#ifndef PDG_NO_GUI
    if (mDrawHelper || mPostDrawHelper)
        throw std::runtime_error("Sprite snapshots cannot save drawing callbacks");
#endif
#ifdef PDG_SPRITER_SUPPORT

#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mNumBreakableJoints)
        throw std::runtime_error("Sprite snapshots require a graph restore for physical constraints");
#endif
    for (const auto& animation : mAnimations) {
        if (std::find(gEasingFunctions, gEasingFunctions + NUM_BUILTIN_EASINGS, animation.easing)
                == gEasingFunctions + NUM_BUILTIN_EASINGS)
            throw std::runtime_error("Sprite snapshots cannot save custom easing callbacks");
    }
}

#include "physics-graph-snapshot.inc"
#include "sprite-part-snapshot.inc"

uint32 Sprite::getSerializedSize(ISerializer* serializer) const {
    PhysicsGraphSnapshot scene(*this);
    PhysicsSnapshotScope physicsScope(serializer, scene.bodies());
	uint32 totalSize = 0;
	uint32 serFlags = (mLayer) ? mLayer->mSerFlags : (uint32)ser_Full;
    if (serFlags & ser_InitialData) {
        validateInitialSnapshot(LayerSnapshotScope::contains(serializer, mLayer));
        if (!LayerSnapshotScope::contains(serializer, mLayer)) scene.validate();
        totalSize += 2 + serializer->sizeof_uint(serFlags);
    }

	if ( (serFlags == ser_Micro) || (serFlags == ser_Positions) ) {

		// special case, smallest possible update
		totalSize += 9; // pos as 2x 2 byte shorts, facing as 4 byte float, frame number as uint8

	} else {

	  #ifdef PDG_TAG_SERIALIZED_DATA
		totalSize += 4;  // size of sprite magic number
	  #endif
		totalSize += 2; // size of spriteFlags
		if (serFlags & ser_InitialData) {
			totalSize += serializer->sizeof_uint(iid);
			totalSize += serializer->sizeof_uint((uint32)spriteId);
			totalSize += serializer->sizeof_uint(mMouseDetectMode);
		}
		if (serFlags & (ser_InitialData | ser_Animations) ) {
			totalSize += 1;		
		}
		SIZE_FLOAT_LIST_START(2, 14);
		if (serFlags & ser_Positions) {
			SIZE_NON_ZERO_F(mLocation.x, 0);
			SIZE_NON_ZERO_F(mLocation.y, 1);
			SIZE_NON_ZERO_F(mFacing, 2);
		}
		if (serFlags & ser_Sizes) {
			SIZE_NON_ZERO_F(mHeight, 3);
			SIZE_NON_ZERO_F(mWidth, 4);
		}
		if (serFlags & (ser_Animations | ser_Motion) ) {
			SIZE_NON_ZERO_F(mCenterOffset.x, 5);
			SIZE_NON_ZERO_F(mCenterOffset.y, 6);
		}
		if (serFlags & ser_Motion) {
			SIZE_NON_ZERO_F(mDeltaXPerMs, 7);
			SIZE_NON_ZERO_F(mDeltaYPerMs, 8);
			SIZE_NON_ZERO_F(mDeltaWidthPerMs, 9);
			SIZE_NON_ZERO_F(mDeltaHeightPerMs, 10);
			SIZE_NON_ZERO_F(mDeltaFacingPerMs, 11);
		}
		if (serFlags & ser_Sizes) {
            SIZE_NON_ZERO_F((mScaleX - 1), 12);
            SIZE_NON_ZERO_F((mScaleY - 1), 13);
        }
		SIZE_FLOAT_LIST_END(totalSize);
		if (serFlags & ser_Animations) {
			if (serFlags & ser_InitialData) {
                totalSize += 4 + serializer->sizeof_uint(mNumFrames);
                for (int i = 0; i < mNumFrames; i++) {
                    if (serFlags & (ser_ImageRefs | ser_ImageData)) {
                        totalSize += serializer->sizeof_obj(mFrames[i].image);
                        SnapshotWriter optional(serializer,false);optional.object(mFrames[i].collisionMask);totalSize+=optional.size();
                    }
					totalSize += 8; // mFrames[i].center;
					totalSize += serializer->sizeof_uint(mFrames[i].imageFrameNum);
					totalSize += 4; // mFrames[i].centerOffsetX, mFrames[i].centerOffsetY);
				}
			}
			totalSize += 4; // 1 byte each for mCurrFrame, mFirstFrame, mLastFrame, mFadeCompleteAction
            if (serFlags & ser_InitialData) { SnapshotWriter out(serializer,false);out.floating(mCurrFramePrecise,mCurrFrame);totalSize+=out.size(); }
			size_t numAnims = mAnimations.size();
			totalSize += serializer->sizeof_uint(UINT32_MAX) + 1 + serializer->sizeof_uint((uint32)numAnims);
            const bool hasWait = mWaitPending || mDelaySeconds > 0;
            totalSize += serializer->sizeof_bool(mSchedulePaused);
            totalSize += serializer->sizeof_bool(hasWait);
            totalSize += serializer->sizeof_bool(mAppendAnimation);
            if (hasWait) totalSize += serializer->sizeof_d(mDelaySeconds);
			for (uint32 i = 0; i < numAnims; i++) {
                const auto& anim=mAnimations[i];SnapshotWriter out(serializer,false);
                out.real(anim.delaySeconds);out.floating(anim.targetVal);out.real(anim.durationSeconds);
                if(anim.delaySeconds<=0){out.real(anim.elapsedSeconds);out.floating(anim.beginVal);out.floating(anim.deltaVal);}
                totalSize+=4+out.size();
			}
		}
//   #ifdef PDG_SCML_SUPPORT
// 	SCML_pdg::Entity*		mEntity;
// 	float					mEntityScaleX;
// 	float					mEntityScaleY;
//   #endif // PDG_SCML_SUPPORT
		if (serFlags & (ser_Forces | ser_Physics)) {
            totalSize += serializer->sizeof_uint(UINT32_MAX) + 1 + physics->getSerializedSize(serializer);
		}
		if (serFlags & ser_Physics) {
			if (serFlags & ser_InitialData) {
			  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				totalSize += serializer->sizeof_uint(mCollideGroup);
			  #else
				totalSize += serializer->sizeof_uint(0); // dummy collide group
			  #endif
			}

          #ifndef PDG_USE_CHIPMUNK_PHYSICS
          	totalSize += serializer->sizeof_uint(0);
          #else
          	totalSize += serializer->sizeof_uint(mNumBreakableJoints);
			for (int i = 0; i < mNumBreakableJoints; i++) {
				cpConstraint* constraint = mBreakableJoints[i];
				uint8 jti = getJointTypeId(constraint);
				cpBody* b = cpConstraintGetBodyB(constraint);
                Sprite* otherSprite = (Sprite*) cpBodyGetUserData(b);
                uint32 siid = otherSprite->iid;
				cpFloat maxForce = cpConstraintGetMaxForce(constraint);  // inf
				cpFloat errorBias = cpConstraintGetErrorBias(constraint);  // 0.1
				cpFloat maxBias = cpConstraintGetMaxBias(constraint); // inf
				bool hasMaxForce = (maxForce != (cpFloat)INFINITY);
				bool hasErrorBias = (errorBias != (cpFloat)0.1f);
				bool hasMaxBias = (maxBias != (cpFloat)INFINITY);		
				totalSize += 1 + serializer->sizeof_uint(siid);  // joint type id
				totalSize += serializer->sizeof_bool(hasMaxForce);
				totalSize += serializer->sizeof_bool(hasErrorBias);
				totalSize += serializer->sizeof_bool(hasMaxBias);
				if (hasMaxForce) {
					totalSize += 4; // maxForce)
				}
				if (hasErrorBias) {
					totalSize += 4; // errorBias)
				}
				if (hasMaxBias) {
					totalSize += 4; // maxBias
				}
				if ( jti == PinJointId ) {
					totalSize += serializer->sizeof_point(convertPoint(cpPinJointGetAnchorA(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpPinJointGetAnchorB(constraint)));
					totalSize += 4; // Dist
				}
				if ( jti == SlideJointId ) {
					totalSize += serializer->sizeof_point(convertPoint(cpSlideJointGetAnchorA(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpSlideJointGetAnchorB(constraint)));
					totalSize += 8; // Min, Max
				}
				if ( jti == PivotJointId ) {
					totalSize += serializer->sizeof_point(convertPoint(cpPivotJointGetAnchorA(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpPivotJointGetAnchorB(constraint)));
				}
				if ( jti == GrooveJointId ) {
					totalSize += serializer->sizeof_point(convertPoint(cpGrooveJointGetAnchorB(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpGrooveJointGetGrooveA(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpGrooveJointGetGrooveB(constraint)));
				}
				if ( jti == DampedSpringId ) {
					totalSize += serializer->sizeof_point(convertPoint(cpDampedSpringGetAnchorA(constraint)));
					totalSize += serializer->sizeof_point(convertPoint(cpDampedSpringGetAnchorB(constraint)));
					totalSize += 12; // RestLength, Stiffness, Damping
				}
				if ( jti == DampedRotarySpringId ) {
					totalSize += 12; // RestAngle, Stiffness, Damping
				}
				if ( jti == RotaryLimitJointId ) {
					totalSize += 8; // Min, Max
				}
				if ( jti == RatchetJointId ) {
					totalSize += 12; // Angle, Phase, Ratchet
				}
				if ( jti == GearJointId ) {
					totalSize += 8; // Phase, Ratio
				}
				if ( jti == SimpleMotorId ) {
					totalSize += 4; // Rate
				}
			}
          #endif // PDG_USE_CHIPMUNK_PHYSICS
		}

	}
	if (serFlags & ser_InitialData) {
        totalSize += SpriteAnimationSnapshot::size(*this,serializer);
        totalSize += partSnapshotSize(serializer);
        totalSize += SpriteAnimationSnapshot::physicsRecord(*this,serializer,false);
        if (!LayerSnapshotScope::contains(serializer, mLayer)) totalSize += scene.size(serializer);
    } else if(serFlags & ser_Animations) totalSize+=partMotionSize(serializer);
	return totalSize;
}

void Sprite::serialize(ISerializer* serializer) const {
    PhysicsGraphSnapshot scene(*this);
    PhysicsSnapshotScope physicsScope(serializer, scene.bodies());
	uint32 serFlags = (mLayer) ? mLayer->mSerFlags : (uint32)ser_Full;
    if (serFlags & ser_InitialData) {
        validateInitialSnapshot(LayerSnapshotScope::contains(serializer, mLayer));
        if (!LayerSnapshotScope::contains(serializer, mLayer)) scene.validate();
        serializer->serialize_1u(10); serializer->serialize_uint(serFlags);
        serializer->serialize_1u((mFlipX ? 1 : 0) | (mFlipY ? 2 : 0) | (LayerSnapshotScope::contains(serializer, mLayer) ? 4 : 0));
    }

	if ( (serFlags == ser_Micro) || (serFlags == ser_Positions) ) {

		// special case, smallest possible update
		int16 x = (mLocation.x < MIN_INT16) ? MIN_INT16 : ((mLocation.x > MAX_INT16) ? MAX_INT16 : (int16)mLocation.x);
		int16 y = (mLocation.y < MIN_INT16) ? MIN_INT16 : ((mLocation.y > MAX_INT16) ? MAX_INT16 : (int16)mLocation.y);
		serializer->serialize_2(x);
		serializer->serialize_2(y);
		serializer->serialize_f(mFacing);
		serializer->serialize_1u(mCurrFrame);

	} else {

	  #ifdef PDG_TAG_SERIALIZED_DATA
		serializer->serialize_4(PDG_SPRITE_MAGIC_NUMBER);
	  #endif
	  	uint32 spriteFlags = 
			(wantsOffscreen ? 		1 << 0 : 0) |
			(mAnimating ? 			1 << 1 : 0) |   // from AnimatedBase
			(wantsWallCollide ? 	1 << 2 : 0) |
			(wantsMouseOver ?		1 << 3 : 0) |
			(wantsClicks ? 			1 << 4 : 0) |
			(wantsAnimLoop ? 		1 << 5 : 0) |
			(wantsAnimEnd ? 		1 << 6 : 0) |
			(mLoopAnim ? 			1 << 7 : 0) |
			(mBackToFrontAnim ? 	1 << 8 : 0) |
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
			(mStatic ? 				1 << 9 : 0) |
	  #endif
			(mBidirectionalAnim ? 	1 << 10 : 0) |
			(mSpriteAnimating ? 	1 << 11 : 0) |
			(mSpriteAnimatingBackwardsNow ? 1 << 12 : 0) |
			(mOnscreen ? 			1 << 13 : 0) |
			(mInBounds ? 			1 << 14 : 0) |
			(mCompletelyInBounds ? 	1 << 15 : 0) |
			0;
	  	serializer->serialize_2u(spriteFlags);
		if (serFlags & ser_InitialData) {
			serializer->serialize_uint(iid);
			serializer->serialize_uint((uint32)spriteId);
			serializer->serialize_uint(mMouseDetectMode);
		}
		if (serFlags & (ser_InitialData | ser_Animations) ) {
			uint8 opacity = (mOpacity * 255);
			serializer->serialize_1u(opacity);		
		}
		SERIALIZE_FLOAT_LIST_START(2, 14);
		if (serFlags & ser_Positions) {
			SERIALIZE_NON_ZERO_F(mLocation.x, 0);
			SERIALIZE_NON_ZERO_F(mLocation.y, 1);
			SERIALIZE_NON_ZERO_F(mFacing, 2);
		}
		if (serFlags & ser_Sizes) {
			SERIALIZE_NON_ZERO_F(mHeight, 3);
			SERIALIZE_NON_ZERO_F(mWidth, 4);
		}
		if (serFlags & (ser_Animations | ser_Motion) ) {
			SERIALIZE_NON_ZERO_F(mCenterOffset.x, 5);
			SERIALIZE_NON_ZERO_F(mCenterOffset.y, 6);
		}
		if (serFlags & ser_Motion) {
			SERIALIZE_NON_ZERO_F(mDeltaXPerMs, 7);
			SERIALIZE_NON_ZERO_F(mDeltaYPerMs, 8);
			SERIALIZE_NON_ZERO_F(mDeltaWidthPerMs, 9);
			SERIALIZE_NON_ZERO_F(mDeltaHeightPerMs, 10);
			SERIALIZE_NON_ZERO_F(mDeltaFacingPerMs, 11);
		}
		if (serFlags & ser_Sizes) {
            SERIALIZE_NON_ZERO_F((mScaleX - 1), 12);
            SERIALIZE_NON_ZERO_F((mScaleY - 1), 13);
        }
		SERIALIZE_FLOAT_LIST_END(2);
		if (serFlags & ser_Animations) {
			if (serFlags & ser_InitialData) {
				serializer->serialize_f(mFps);
				serializer->serialize_uint(mNumFrames);
				for (int i = 0; i < mNumFrames; i++) {
                    if (serFlags & (ser_ImageRefs | ser_ImageData)) {
                        serializer->serialize_obj(mFrames[i].image);
                        SnapshotWriter(serializer,true).object(mFrames[i].collisionMask);
                    }
					serializer->serialize_f(mFrames[i].center.x);
					serializer->serialize_f(mFrames[i].center.y);
					serializer->serialize_uint(mFrames[i].imageFrameNum);
					serializer->serialize_2(mFrames[i].centerOffsetX);
					serializer->serialize_2(mFrames[i].centerOffsetY);
				}
			}
			serializer->serialize_1u(mCurrFrame);
			serializer->serialize_1u(mFirstFrame);
			serializer->serialize_1u(mLastFrame);
			serializer->serialize_1(mFadeCompleteAction);
            if (serFlags & ser_InitialData) SnapshotWriter(serializer,true).floating(mCurrFramePrecise,mCurrFrame);
			uint32 numAnims = (uint32)mAnimations.size();
			// Revision 7 also carries sampled Part motion in incremental updates.
            serializer->serialize_uint(UINT32_MAX);
            serializer->serialize_1u(7);
            const bool hasWait = mWaitPending || mDelaySeconds > 0;
            serializer->serialize_bool(mSchedulePaused);
            serializer->serialize_bool(hasWait);
            serializer->serialize_bool(mAppendAnimation);
            if (hasWait) serializer->serialize_d(mDelaySeconds);
            serializer->serialize_uint(numAnims);
			for (uint32 i = 0; i < numAnims; i++) {
				Animation anim = mAnimations[i];
				uint8 easingId = easingFuncToId(anim.easing);
				uint8 variableId = 0; // figure out which variable base on what value* is pointing at and convert to an id
				if (anim.value == &mLocation.x) {
					variableId = var_LocX;
				} else if (anim.value == &mLocation.y) {
					variableId = var_LocY;
				} else if (anim.value == &mDeltaXPerMs) {
					variableId = var_DeltaX;
				} else if (anim.value == &mDeltaYPerMs) {
					variableId = var_DeltaY;
				} else if (anim.value == &mWidth) {
					variableId = var_Width;
				} else if (anim.value == &mHeight) {
					variableId = var_Height;
				} else if (anim.value == &mFacing) {
					variableId = var_Facing;
				} else if (anim.value == &mCenterOffset.x) {
					variableId = var_CenterOffsetX;
				} else if (anim.value == &mCenterOffset.y) {
					variableId = var_CenterOffsetY;
				} else if (anim.value == &mDeltaFacingPerMs) {
                    variableId = var_Spin;
                } else if (anim.value == &mScaleX) {
                    variableId = var_ScaleX;
                } else if (anim.value == &mScaleY) {
                    variableId = var_ScaleY;
                } else if (anim.value == &mDeltaWidthPerMs) {
                    variableId = var_StretchX;
                } else if (anim.value == &mDeltaHeightPerMs) {
                    variableId = var_StretchY;
                } else if (anim.value == &mOpacity) {
					variableId = var_Opacity;
				}
				SnapshotWriter out(serializer,true);out.real(anim.delaySeconds);
				serializer->serialize_1u(easingId);
				serializer->serialize_1u(variableId);
                serializer->serialize_1u(anim.rotationDirection);
                serializer->serialize_1u(animationFlags(anim));
				out.floating(anim.targetVal);
				out.real(anim.durationSeconds);
				if (anim.delaySeconds <= 0) {
					// only send these if animation is actually running, they will be sent at start
					out.real(anim.elapsedSeconds);  // this is time within animation, not sys timestamp
					out.floating(anim.beginVal);
					out.floating(anim.deltaVal);
				}
			}

		}
//   #ifdef PDG_SCML_SUPPORT
// 	SCML_pdg::Entity*		mEntity;
// 	float					mEntityScaleX;
// 	float					mEntityScaleY;
//   #endif // PDG_SCML_SUPPORT
		if (serFlags & (ser_Forces | ser_Physics)) {
            serializer->serialize_uint(UINT32_MAX); serializer->serialize_1u(3);
            physics->serialize(serializer);
		}
		if (serFlags & ser_Physics) {
			if (serFlags & ser_InitialData) {
			  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				serializer->serialize_uint(mCollideGroup);
			  #else
				serializer->serialize_uint(0);  // dummy collide group
			  #endif
			}

          #ifndef PDG_USE_CHIPMUNK_PHYSICS
          	serializer->serialize_uint(0);    // serialize a value indicating no breakable joints
          #else
          	serializer->serialize_uint(mNumBreakableJoints);
			for (int i = 0; i < mNumBreakableJoints; i++) {
				cpConstraint* constraint = mBreakableJoints[i];
				uint8 jti = getJointTypeId(constraint);
				cpBody* b = cpConstraintGetBodyB(constraint);
                Sprite* otherSprite = (Sprite*) cpBodyGetUserData(b);
                uint32 siid = otherSprite->iid;
				cpFloat maxForce = cpConstraintGetMaxForce(constraint);  // inf
				cpFloat errorBias = cpConstraintGetErrorBias(constraint);  // 0.1
				cpFloat maxBias = cpConstraintGetMaxBias(constraint); // inf
				bool hasMaxForce = (maxForce != (cpFloat)INFINITY);
				bool hasErrorBias = (errorBias != (cpFloat)0.1f);
				bool hasMaxBias = (maxBias != (cpFloat)INFINITY);
				serializer->serialize_1u(jti);
				serializer->serialize_uint(siid);
				serializer->serialize_bool(hasMaxForce);
				serializer->serialize_bool(hasErrorBias);
				serializer->serialize_bool(hasMaxBias);
				if (hasMaxForce) {
					serializer->serialize_f(maxForce);
				}
				if (hasErrorBias) {
					serializer->serialize_f(errorBias);
				}
				if (hasMaxBias) {
					serializer->serialize_f(maxBias);
				}
				if ( jti == PinJointId ) {
					serializer->serialize_point(convertPoint(cpPinJointGetAnchorA(constraint)));
					serializer->serialize_point(convertPoint(cpPinJointGetAnchorB(constraint)));
					serializer->serialize_f(cpPinJointGetDist(constraint));
				}
				if ( jti == SlideJointId ) {
					serializer->serialize_point(convertPoint(cpSlideJointGetAnchorA(constraint)));
					serializer->serialize_point(convertPoint(cpSlideJointGetAnchorB(constraint)));
					serializer->serialize_f(cpSlideJointGetMin(constraint));
					serializer->serialize_f(cpSlideJointGetMax(constraint));
				}
				if ( jti == PivotJointId ) {
					serializer->serialize_point(convertPoint(cpPivotJointGetAnchorA(constraint)));
					serializer->serialize_point(convertPoint(cpPivotJointGetAnchorB(constraint)));
				}
				if ( jti == GrooveJointId ) {
					serializer->serialize_point(convertPoint(cpGrooveJointGetAnchorB(constraint)));
					serializer->serialize_point(convertPoint(cpGrooveJointGetGrooveA(constraint)));
					serializer->serialize_point(convertPoint(cpGrooveJointGetGrooveB(constraint)));
				}
				if ( jti == DampedSpringId ) {
					serializer->serialize_point(convertPoint(cpDampedSpringGetAnchorA(constraint)));
					serializer->serialize_point(convertPoint(cpDampedSpringGetAnchorB(constraint)));
					serializer->serialize_f(cpDampedSpringGetRestLength(constraint));
					serializer->serialize_f(cpDampedSpringGetStiffness(constraint));
					serializer->serialize_f(cpDampedSpringGetDamping(constraint));
				}
				if ( jti == DampedRotarySpringId ) {
					serializer->serialize_f(cpDampedRotarySpringGetRestAngle(constraint));
					serializer->serialize_f(cpDampedRotarySpringGetStiffness(constraint));
					serializer->serialize_f(cpDampedRotarySpringGetDamping(constraint));
				}
				if ( jti == RotaryLimitJointId ) {
					serializer->serialize_f(cpRotaryLimitJointGetMin(constraint));
					serializer->serialize_f(cpRotaryLimitJointGetMax(constraint));
				}
				if ( jti == RatchetJointId ) {
					serializer->serialize_f(cpRatchetJointGetAngle(constraint));
					serializer->serialize_f(cpRatchetJointGetPhase(constraint));
					serializer->serialize_f(cpRatchetJointGetRatchet(constraint));
				}
				if ( jti == GearJointId ) {
					serializer->serialize_f(cpGearJointGetPhase(constraint));
					serializer->serialize_f(cpGearJointGetRatio(constraint));
				}
				if ( jti == SimpleMotorId ) {
					serializer->serialize_f(cpSimpleMotorGetRate(constraint));
				}
//				cpConstraint* allocConstraintByJointTypeId(uint8 jointTypeId);
			}
          #endif // PDG_USE_CHIPMUNK_PHYSICS
		}

	}

    if (serFlags & ser_InitialData) {
        SpriteAnimationSnapshot::write(*this,serializer);
        serializeParts(serializer);
        SpriteAnimationSnapshot::physicsRecord(*this,serializer,true);
        if (!LayerSnapshotScope::contains(serializer, mLayer)) scene.write(serializer);
    } else if(serFlags & ser_Animations) serializePartMotion(serializer);

		// stuff from animated
	

		// forces 
	

		// animation helpers
//	std::vector<IAnimationHelper*> mHelpers;
	
		// stuff from sprite
	

// animation
// 
// 
//   #ifndef PDG_NO_GUI
//     Port* mPort;
//   #endif
// 
// 	SpriteLayer* mLayer;
// 	Sprite* mNextSprite;
// 	Sprite* mPrevSprite;
//     
// 	
//   #ifndef PDG_NO_GUI
// 	ISpriteDrawHelper*	mDrawHelper;
// 	ISpriteDrawHelper*	mPostDrawHelper;
//   #endif	
// 
// 

}


void Sprite::deserialize(IDeserializer* deserializer) {
	uint32 serFlags = (mLayer) ? mLayer->mSerFlags : (uint32)ser_Full;
    uint8 initialRevision=0;
    if (serFlags & ser_InitialData) {
        initialRevision=deserializer->deserialize_1u();
        if (initialRevision != 9 && initialRevision != 10) throw std::runtime_error("Unsupported initial Sprite record");
        serFlags = deserializer->deserialize_uint();
        if (!(serFlags & ser_InitialData) || (serFlags & ~uint32(0x7fff)))
            throw std::runtime_error("Invalid initial Sprite serialization flags");
        const auto flip = deserializer->deserialize_1u();
        if (flip > 7 || bool(flip & 4) != PhysicsGraphReadScope::contains(deserializer))
            throw std::runtime_error("Invalid Sprite graph/reflection flags");
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
        if(getSpace() && cpSpaceIsLocked(getSpace()))throw std::logic_error("Restore rigs outside physics callbacks");
        releaseAnimationPhysics();
#endif
        mFlipX = (flip & 1) != 0; mFlipY = (flip & 2) != 0;
    }

    bool receivedBodyState = false;
    uint8 receivedAnimationRevision=0;
	if ( (serFlags == ser_Micro) || (serFlags == ser_Positions) ) {

		// special case, smallest possible update
		mLocation.x = deserializer->deserialize_2();
		mLocation.y = deserializer->deserialize_2();
		mFacing = deserializer->deserialize_f();
		mCurrFrame = deserializer->deserialize_1u();
		mCurrFramePrecise = mCurrFrame;

	} else {

	  #ifdef PDG_TAG_SERIALIZED_DATA
		uint32 tag = deserializer->deserialize_4();
        if (tag != PDG_SPRITE_MAGIC_NUMBER) throw std::runtime_error("Invalid Sprite record tag");
	  #endif
		uint32 spriteFlags = deserializer->deserialize_2u();
		wantsOffscreen = 	((spriteFlags & 1 << 0) != 0);
		mAnimating = 		((spriteFlags & 1 << 1) != 0);
		wantsWallCollide = 	((spriteFlags & 1 << 2) != 0);
		wantsMouseOver = 	((spriteFlags & 1 << 3) != 0);
		wantsClicks = 		((spriteFlags & 1 << 4) != 0);
		wantsAnimLoop = 	((spriteFlags & 1 << 5) != 0);
		wantsAnimEnd = 		((spriteFlags & 1 << 6) != 0);
		mLoopAnim = 		((spriteFlags & 1 << 7) != 0);
		mBackToFrontAnim = 	((spriteFlags & 1 << 8) != 0);
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
		mStatic = 			((spriteFlags & 1 << 9) != 0);
	  #endif
		mBidirectionalAnim = 	((spriteFlags & 1 << 10) != 0);
		mSpriteAnimating = 		((spriteFlags & 1 << 11) != 0);
		mSpriteAnimatingBackwardsNow = 	((spriteFlags & 1 << 12) != 0);
		// better to recalculate these rather than read them from the flags so
		// they will generate the proper events
		if (serFlags & ser_InitialData) {
			mOnscreen = 			((spriteFlags & 1 << 13) != 0);
			mInBounds = 			((spriteFlags & 1 << 14) != 0);
			mCompletelyInBounds = 	((spriteFlags & 1 << 15) != 0);
		}
		if (serFlags & ser_InitialData) {
			iid = deserializer->deserialize_uint();
			spriteId = deserializer->deserialize_uint();
            if (iid == 0 || iid == UINT32_MAX) throw std::runtime_error("Invalid Sprite identity");
            sUniqueSpriteId = std::max(sUniqueSpriteId, iid + 1);
			mMouseDetectMode = (int)deserializer->deserialize_uint();
		}
		if (serFlags & (ser_InitialData | ser_Animations) ) {
			uint8 opacity = deserializer->deserialize_1u();
			mOpacity = (float)opacity / 255.0f;
		}
		DESERIALIZE_FLOAT_LIST_START(2, 14);
		if (serFlags & ser_Positions) {
			mLocation.x = DESERIALIZE_NON_ZERO_F(0);
			mLocation.y = DESERIALIZE_NON_ZERO_F(1);
			mFacing = DESERIALIZE_NON_ZERO_F(2);
		}
		if (serFlags & ser_Sizes) {
			mHeight = DESERIALIZE_NON_ZERO_F(3);
			mWidth = DESERIALIZE_NON_ZERO_F(4);
		}
		if (serFlags & (ser_Animations | ser_Motion) ) {
			mCenterOffset.x = DESERIALIZE_NON_ZERO_F(5);
			mCenterOffset.y = DESERIALIZE_NON_ZERO_F(6);
		}
		if (serFlags & ser_Motion) {
			mDeltaXPerMs = DESERIALIZE_NON_ZERO_F(7);
			mDeltaYPerMs = DESERIALIZE_NON_ZERO_F(8);
			mDeltaWidthPerMs = DESERIALIZE_NON_ZERO_F(9);
			mDeltaHeightPerMs = DESERIALIZE_NON_ZERO_F(10);
			mDeltaFacingPerMs = DESERIALIZE_NON_ZERO_F(11);
		}
        if (serFlags & ser_Sizes) {
            mScaleX = DESERIALIZE_NON_ZERO_F(12); mScaleX += 1;
            mScaleY = DESERIALIZE_NON_ZERO_F(13); mScaleY += 1;
        }
		DESERIALIZE_FLOAT_LIST_END(2);
		if (serFlags & ser_Animations) {
			if (serFlags & ser_InitialData) {
                const float fps = deserializer->deserialize_f();
                const auto count = deserializer->deserialize_uint();
                if (!std::isfinite(fps) || count > MAX_FRAMES_PER_SPRITE)
                    throw std::runtime_error("Invalid Sprite frame layout");
                const bool readImages = (serFlags & (ser_ImageRefs | ser_ImageData)) != 0;
                if (!readImages && count > static_cast<uint32>(mNumFrames))
                    throw std::runtime_error("Initial Sprite frames require image records");
                std::vector<FrameInfoT> frames(count);
                struct ReleaseFrames {
                    std::vector<FrameInfoT>& frames;
                    ~ReleaseFrames() { for (auto& frame : frames) {
                        if (frame.image) frame.image->release();
                        if (frame.collisionMask) frame.collisionMask->release();
                    } }
                } releaseFrames{frames};
                auto readImage = [&]() -> ImageImpl* {
                    auto* object = deserializer->deserialize_obj();
                    auto* image = dynamic_cast<ImageImpl*>(object);
                    if (object && !image) { object->release(); throw std::runtime_error("Expected Sprite frame image"); }
                    return image;
                };
                for (uint32 i = 0; i < count; ++i) {
                    auto& frame = frames[i];
                    if (readImages) { frame.image = readImage(); frame.collisionMask = deserializer->deserialize_bool() ? readImage() : nullptr; }
                    else {
                        frame.image=mFrames[i].image; frame.collisionMask=mFrames[i].collisionMask;
                        if (frame.image) frame.image->addRef();
                        if (frame.collisionMask) frame.collisionMask->addRef();
                    }
                    if (!frame.image) throw std::runtime_error("Sprite frame image is missing");
                    frame.center.x=deserializer->deserialize_f(); frame.center.y=deserializer->deserialize_f();
                    const auto imageFrame=deserializer->deserialize_uint();
                    if (imageFrame >= static_cast<uint32>(std::max(1,frame.image->getNumFrames())) ||
                        !std::isfinite(frame.center.x) || !std::isfinite(frame.center.y))
                        throw std::runtime_error("Invalid Sprite image frame");
                    frame.imageFrameNum=imageFrame;
                    frame.centerOffsetX=deserializer->deserialize_2(); frame.centerOffsetY=deserializer->deserialize_2();
                }
                for (int i=0; i<mNumFrames; ++i) {
                    if (mFrames[i].image) mFrames[i].image->release();
                    if (mFrames[i].collisionMask) mFrames[i].collisionMask->release();
                }
                mNumFrames=count; mFps=fps;
                for (uint32 i=0; i<count; ++i) {
                    mFrames[i]=frames[i]; frames[i].image=nullptr; frames[i].collisionMask=nullptr;
                }
            }

			mCurrFrame = deserializer->deserialize_1u();
			mCurrFramePrecise = mCurrFrame;
			mFirstFrame = deserializer->deserialize_1u();
			mLastFrame = deserializer->deserialize_1u();
			mFadeCompleteAction = deserializer->deserialize_1();
            if (serFlags & ser_InitialData) {
                const float cursor=SnapshotReader(deserializer).floating(mCurrFrame);
                if (!std::isfinite(cursor) || (mNumFrames > 0 && (mFirstFrame > mLastFrame ||
                    mLastFrame >= mNumFrames || mCurrFrame >= mNumFrames ||
                    cursor < 0 || cursor >= mNumFrames)))
                    throw std::runtime_error("Invalid Sprite frame cursor");
                mCurrFramePrecise=cursor;
            }
			mDelaySeconds = 0;  // Unmarked records have no pending-wait field.
			uint32 numAnims = deserializer->deserialize_uint();
            const bool secondsFormat = numAnims == UINT32_MAX;
            uint8 animationRevision = 0;
            if (secondsFormat) {
                animationRevision = deserializer->deserialize_1u();
                receivedAnimationRevision=animationRevision;
                if (animationRevision < 1 || animationRevision > 7)
                    throw std::runtime_error("Unsupported Sprite animation record revision");
                mSchedulePaused = false; mDelaySeconds = 0; mAppendAnimation = false; mWaitPending = false; mAnimationOperation = 1;
                if (animationRevision >= 4) {
                    const bool paused = deserializer->deserialize_bool();
                    const bool hasWait = deserializer->deserialize_bool();
                    mAppendAnimation = animationRevision >= 5 && deserializer->deserialize_bool();
                    mWaitPending = hasWait && !mAppendAnimation;
                    const double delay = hasWait ? deserializer->deserialize_d() : 0;
                    if (!std::isfinite(delay) || delay < 0)
                        throw std::runtime_error("Invalid serialized tween state");
                    mSchedulePaused = paused; mDelaySeconds = delay;
                } else if (animationRevision >= 3) {
                    const auto paused = deserializer->deserialize_1u();
                    mDelaySeconds = deserializer->deserialize_d();
                    if (paused > 1 || !std::isfinite(mDelaySeconds) || mDelaySeconds < 0)
                        throw std::runtime_error("Invalid serialized tween state");
                    mSchedulePaused = paused != 0;
                }
                numAnims = deserializer->deserialize_uint();
            }
            if (numAnims > 1000000) throw std::runtime_error("Invalid Sprite animation count");
			// mismatching mAnimations.size()
			if (numAnims != mAnimations.size()) {
				Animation a;
				mAnimations.assign(numAnims, a);
			}
			for (uint32 i = 0; i < numAnims; i++) {
				Animation anim;
				SnapshotReader in(deserializer);
                anim.delaySeconds = animationRevision>=6 ? in.real() : secondsFormat ? deserializer->deserialize_d() : deserializer->deserialize_uint() / 1000.0;
				uint8 easingId = deserializer->deserialize_1u();
				anim.easing = easingIdToFunc(easingId);
				uint8 variableId = deserializer->deserialize_1u();
                if (animationRevision >= 2) {
                    anim.rotationDirection = deserializer->deserialize_1u();
                    const uint8 flags = deserializer->deserialize_1u();
                    readAnimationFlags(anim, flags, animationRevision >= 5);
                    if (anim.rotationDirection > rotationDirection_CounterClockwise)
                        throw std::runtime_error("Invalid serialized rotation route");
                }
				if (variableId == var_LocX){
					anim.value = &mLocation.x;
				} else if (variableId == var_LocY) {
					anim.value = &mLocation.y;
				} else if (variableId == var_DeltaX) {
					anim.value = &mDeltaXPerMs;
				} else if (variableId == var_DeltaY) {
					anim.value = &mDeltaYPerMs;
				} else if (variableId == var_Width) {
					anim.value = &mWidth;
				} else if (variableId == var_Height) {
					anim.value = &mHeight;
				} else if (variableId == var_Facing) {
					anim.value = &mFacing;
				} else if (variableId == var_CenterOffsetX) {
					anim.value = &mCenterOffset.x;
				} else if (variableId == var_CenterOffsetY) {
					anim.value = &mCenterOffset.y;
				} else if (variableId == var_Spin) {
                    anim.value = &mDeltaFacingPerMs;
                } else if (variableId == var_ScaleX) {
                    anim.value = &mScaleX;
                } else if (variableId == var_ScaleY) {
                    anim.value = &mScaleY;
                } else if (variableId == var_StretchX) {
                    anim.value = &mDeltaWidthPerMs;
                } else if (variableId == var_StretchY) {
                    anim.value = &mDeltaHeightPerMs;
                } else if (variableId == var_Opacity) {
					anim.value = &mOpacity;
				} else {
					throw std::runtime_error("Unknown serialized animation channel");
				}
				anim.targetVal = animationRevision>=6 ? in.floating() : deserializer->deserialize_f();
				anim.durationSeconds = animationRevision>=6 ? in.real() : secondsFormat ? deserializer->deserialize_d() : deserializer->deserialize_uint() / 1000.0;
				if (anim.delaySeconds <= 0) {
					// these were only sent if animation was actually running
					anim.elapsedSeconds = animationRevision>=6 ? in.real() : secondsFormat ? deserializer->deserialize_d() : deserializer->deserialize_uint() / 1000.0;
					anim.beginVal = animationRevision>=6 ? in.floating() : deserializer->deserialize_f();
					anim.deltaVal = animationRevision>=6 ? in.floating() : deserializer->deserialize_f();
				}
				if (!std::isfinite(anim.delaySeconds) || anim.delaySeconds < 0 ||
                    !std::isfinite(anim.durationSeconds) || anim.durationSeconds < 0 ||
                    !std::isfinite(anim.elapsedSeconds) || anim.elapsedSeconds < 0 || !anim.easing)
                    throw std::runtime_error("Invalid serialized animation timing");
                mAnimations[i] = anim;
			}

		}
//   #ifdef PDG_SCML_SUPPORT
// 	SCML_pdg::Entity*		mEntity;
// 	float					mEntityScaleX;
// 	float					mEntityScaleY;
//   #endif // PDG_SCML_SUPPORT
        if (serFlags & (ser_Forces | ser_Physics)) {
            // Only the current PhysicsBody format is supported. Physics state
            // has one authoritative record, including settings-only snapshots.
            if (deserializer->deserialize_uint() != UINT32_MAX || deserializer->deserialize_1u() != 3)
                throw std::runtime_error("Unsupported PhysicsBody record format");
            const int mode = deserializer->deserialize_1u();
            receivedBodyState = true;
            if (mode == physicsBody_None) removePhysicsBody();
            else {
                auto& body = (physics != PhysicsBody::NoPhysics)
                    ? static_cast<PhysicsBody&>(physics) : setupPhysicsBody();
                body.deserialize(deserializer, mode);
            }
        }
		if (serFlags & ser_Physics) {
			if (serFlags & ser_InitialData) {
			  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				mCollideGroup = deserializer->deserialize_uint();
			  #else
				deserializer->deserialize_uint();  // read and discard collide group
			  #endif
			}

			// even if this isn't a Chipmunk build, read the data and just drop it
			// so we can still work with the Sprite
          	int numJoints = (int)deserializer->deserialize_uint();
			for (int i = 0; i < numJoints; i++) {
				uint8 jti = deserializer->deserialize_1u();
				[[maybe_unused]] uint32 siid = deserializer->deserialize_uint();
              #ifdef PDG_USE_CHIPMUNK_PHYSICS
				Sprite* otherSprite;
				// get all the info about the existing constraint
				cpConstraint* constraint = 0;
				if (i < mNumBreakableJoints) {
					uint8 curr_jti = 0;
					uint32 curr_siid = 0;
					constraint = mBreakableJoints[i];
					curr_jti = getJointTypeId(constraint);
					cpBody* b = cpConstraintGetBodyB(constraint);
                	otherSprite = (Sprite*) cpBodyGetUserData(b);
                	curr_siid = otherSprite->iid;
                	if ((siid != curr_siid) || (jti != curr_jti)) {
                		// existing constraint doesn't match with what's on the stream
                		// remove it and start over
                		removeJoint(constraint);
                	}
                	otherSprite = (mLayer) ? mLayer->findSpriteByInternalId(siid) : 0;
					if (serFlags & ser_InitialData) {
						// FIXME: if the other sprite comes after this one in the streaming order
						// and it doesn't exist yet, we are screwed -- we don't have any information
						// about it. This should only be an issue when we are streaming with
						// the ser_InitialData flag.
						// Possible solution would be to create the sprite immediately
						// and assign it the siid, then it would be updated with the new data when
						// it arrived.
                	} else {
						DEBUG_ASSERT(otherSprite != 0, "OUT OF SYNC: expected to find existing Sprite");
                	}
                	constraint = 0;
				}
              #endif  // PDG_USE_CHIPMUNK_PHYSICS
				bool hasMaxForce = deserializer->deserialize_bool();
				bool hasErrorBias = deserializer->deserialize_bool();
				bool hasMaxBias = deserializer->deserialize_bool();
				// Non-physics builds consume these fields to keep the stream aligned.
				[[maybe_unused]] cpFloat maxForce, errorBias, maxBias;
				[[maybe_unused]] float f1, f2, f3;
				Point p1, p2, p3;
				if (hasMaxForce) {
					maxForce = deserializer->deserialize_f();
				}
				if (hasErrorBias) {
					errorBias = deserializer->deserialize_f();
				}
				if (hasMaxBias) {
					maxBias = deserializer->deserialize_f();
				}
				if ( jti == PinJointId ) {
					p1 = deserializer->deserialize_point(); // Anchr1
					p2 = deserializer->deserialize_point(); // Anchr2
					f1 = deserializer->deserialize_f();     // Dist
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = pinJoint(p1, otherSprite, p2);
					}
					cpPinJointSetAnchorA(constraint, convertPoint(p1));
					cpPinJointSetAnchorB(constraint, convertPoint(p2));
					cpPinJointSetDist(constraint, f1);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == SlideJointId ) {
					p1 = deserializer->deserialize_point(); // Anchr1
					p2 = deserializer->deserialize_point(); // Anchr2
					f1 = deserializer->deserialize_f();     // Min
					f2 = deserializer->deserialize_f();     // Max
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = slideJoint(p1, otherSprite, p2, f1, f2);
					}
					cpSlideJointSetAnchorA(constraint, convertPoint(p1));
					cpSlideJointSetAnchorB(constraint, convertPoint(p2));
					cpSlideJointSetMin(constraint, f1);
					cpSlideJointSetMax(constraint, f2);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == PivotJointId ) {
					p1 = deserializer->deserialize_point(); // Anchr1
					p2 = deserializer->deserialize_point(); // Anchr2
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = pivotJoint(otherSprite, p1);
					}
					cpPivotJointSetAnchorA(constraint, convertPoint(p1));
					cpPivotJointSetAnchorB(constraint, convertPoint(p2));
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == GrooveJointId ) {
					p1 = deserializer->deserialize_point(); // Anchr2
					p2 = deserializer->deserialize_point(); // GrooveA
					p3 = deserializer->deserialize_point(); // GrooveB
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = grooveJoint(p2, p3, otherSprite, p1);
				  	}
					cpGrooveJointSetAnchorB(constraint, convertPoint(p1));
					cpGrooveJointSetGrooveA(constraint, convertPoint(p2));
					cpGrooveJointSetGrooveB(constraint, convertPoint(p3));
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == DampedSpringId ) {
					p1 = deserializer->deserialize_point(); // Anchr1
					p2 = deserializer->deserialize_point(); // Anchr2
					f1 = deserializer->deserialize_f(); // RestLength
					f2 = deserializer->deserialize_f(); // Stiffness
					f3 = deserializer->deserialize_f(); // Damping
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = springJoint(p1, otherSprite, p2, f1, f2, f3);
					}
					cpDampedSpringSetAnchorA(constraint, convertPoint(p1));
					cpDampedSpringSetAnchorB(constraint, convertPoint(p2));
					cpDampedSpringSetRestLength(constraint, f1);
					cpDampedSpringSetStiffness(constraint, f2);
					cpDampedSpringSetDamping(constraint, f3);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == DampedRotarySpringId ) {
					f1 = deserializer->deserialize_f(); // RestAngle
					f2 = deserializer->deserialize_f(); // Stiffness
					f3 = deserializer->deserialize_f(); // Damping
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = rotarySpring(otherSprite, f1, f2, f3);
					}
					cpDampedRotarySpringSetRestAngle(constraint, f1);
					cpDampedRotarySpringSetStiffness(constraint, f2);
					cpDampedRotarySpringSetDamping(constraint, f3);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == RotaryLimitJointId ) {
					f1 = deserializer->deserialize_f();     // Min
					f2 = deserializer->deserialize_f();     // Max
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = rotaryLimit(otherSprite, f1, f2);
					}
					cpRotaryLimitJointSetMin(constraint, f1);
					cpRotaryLimitJointSetMax(constraint, f2);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == RatchetJointId ) {
					f1 = deserializer->deserialize_f(); // Angle
					f2 = deserializer->deserialize_f(); // Phase
					f3 = deserializer->deserialize_f(); // Ratchet
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = ratchet(otherSprite, f3);
					}
					cpRatchetJointSetAngle(constraint, f1);
					cpRatchetJointSetPhase(constraint, f2);
					cpRatchetJointSetRatchet(constraint, f3);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == GearJointId ) {
					f1 = deserializer->deserialize_f(); // Phase
					f2 = deserializer->deserialize_f(); // Ratio
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = gear(otherSprite, f2);
					}
					cpGearJointSetPhase(constraint, f1);
					cpGearJointSetRatio(constraint, f2);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
				if ( jti == SimpleMotorId ) {
					f1 = deserializer->deserialize_f(); // Rate
				  #ifdef PDG_USE_CHIPMUNK_PHYSICS
				  	if (!constraint) {
						constraint = motor(otherSprite, f1);
					}
					cpSimpleMotorSetRate(constraint, f1);
				  #endif  // PDG_USE_CHIPMUNK_PHYSICS
				}
              #ifdef PDG_USE_CHIPMUNK_PHYSICS
                if (constraint) {
					if (hasMaxForce) {
						cpConstraintSetMaxForce(constraint, maxForce);
					}
					if (hasErrorBias) {
						cpConstraintSetErrorBias(constraint, errorBias);
					}
					if (hasMaxBias) {
						cpConstraintSetMaxBias(constraint, maxBias);
					}
				}
              #endif  // PDG_USE_CHIPMUNK_PHYSICS
			}
          #ifdef PDG_USE_CHIPMUNK_PHYSICS
			for (int i = numJoints; i < mNumBreakableJoints; i++) {
				// these are extra, remove them
				cpConstraint* constraint = mBreakableJoints[i];
				removeJoint(constraint);
			}
         	mNumBreakableJoints = numJoints; 
          #endif
		}

	}
    if (serFlags & ser_InitialData) {
        SpriteAnimationSnapshot::read(*this,deserializer);
        deserializeParts(deserializer);
        if(initialRevision>=10)SpriteAnimationSnapshot::readPhysics(*this,deserializer);
        if (!PhysicsGraphReadScope::contains(deserializer)) PhysicsGraphSnapshot(*this).read(deserializer);
    } else if(receivedAnimationRevision>=7) deserializePartMotion(deserializer);
    // A position update teleports the existing solver. Otherwise its next step
    // would restore the previous pose. A full body record already owns the pose.
    if (!receivedBodyState && (serFlags & ser_Positions) && physics != PhysicsBody::NoPhysics)
        physics->setOwnerTransform(mLocation + mCenterOffset, mFacing);
}

void Sprite::setUserData(UserData* inUserData) {
	userData = inUserData;
}

void Sprite::freeUserData() {
//	SPRITE_DEBUG_ONLY( OS::_DOUT("Timer [%p] id [%ld] freeUserData: userData [%p]", this, id, userData); )
	if (userData) {
		userData->release();
	}
	userData = 0;
}


// sets current frame of Sprite to a given frame number
Sprite&    Sprite::setFrame(int frame) {
	mSpriteAnimatingBackwardsNow = false;
	DEBUG_ASSERT(frame >= 0 && frame < MAX_FRAMES_PER_SPRITE, "invalid frame number passed to sprite setFrame");
	if (frame < 0) {
		frame = 0;
	}
	if (frame >= MAX_FRAMES_PER_SPRITE) {
		frame = MAX_FRAMES_PER_SPRITE - 1;
	}
	if ((frame == start_FromLastFrame) || (frame >= mNumFrames)) {
		mCurrFrame = mNumFrames - 1;
		if (mBidirectionalAnim) {
			mSpriteAnimatingBackwardsNow = true;
		}
	} else if (frame < 0) {
		mCurrFrame = 0;
	} else {
		mCurrFrame = frame;
	}
	mCurrFramePrecise = mCurrFrame;
	return *this;
}


int		Sprite::getCurrentFrame() {
	return mCurrFrame;
}



// set how fast we animate through the frames
// startingFrame and number of frames can be used to only animate through a subset of the
// Sprite's frames.
void	Sprite::startFrameAnimation(float fps, int startingFrame, int numFrames, int animateFlags) {
	mFps = fps;
    if (mNumFrames == 0) {
        mSpriteAnimating = false;
        mFirstFrame = mLastFrame = mCurrFrame = 0;
        mCurrFramePrecise = 0;
        return;
    }
	if (startingFrame == start_FromFirstFrame) {
		startingFrame = 0;
	} else if (startingFrame == start_FromLastFrame) {
		startingFrame = mNumFrames - 1;
	}
	mFirstFrame = std::max(0, std::min(startingFrame, mNumFrames - 1));
    mLastFrame = numFrames == all_Frames ? mNumFrames - 1
        : mFirstFrame + std::max(1, std::min(numFrames, mNumFrames - mFirstFrame)) - 1;
	if (mFirstFrame < 0) {
		mFirstFrame = 0;
	}
	if (mLastFrame < 0) {
		mLastFrame = 0;
	}
	if (mFirstFrame >= mNumFrames) {
		mFirstFrame = mNumFrames - 1;
	}
	if (mLastFrame >= mNumFrames) {
		mLastFrame = mNumFrames - 1;
	}
	mLoopAnim = (animateFlags & animate_Looping);
	mBackToFrontAnim = (animateFlags & animate_EndToStart);
	mBidirectionalAnim = (animateFlags & animate_Bidirectional);
	mSpriteAnimating = mFirstFrame < mLastFrame;
	if (mBackToFrontAnim) {
		mCurrFrame = mLastFrame;
		mSpriteAnimatingBackwardsNow = true;
	} else {
		mCurrFrame = mFirstFrame;
		mSpriteAnimatingBackwardsNow = false;
	}
	mCurrFramePrecise = mCurrFrame;
}



// stops all frame animation, the current frame becomes the sprite's image
// does not send action_AnimationEnd sprite events
void	Sprite::stopFrameAnimation() {
	mSpriteAnimating = false;
}

// adds an image that is used for one or more frames
// since an image itself can have multiple frames, all frames of the image are added
// to the Sprite, unless startingFrame and/or numFrames is passed in.
// the frames are added to the end of the frame list 
void	Sprite::addFramesImage(Image* image, int startingFrame, int numFrames) {
	if (image == 0) return;
	if (startingFrame == start_FromFirstFrame) {
		startingFrame = 0;
	}
	do {
		if (mNumFrames >= MAX_FRAMES_PER_SPRITE) break;  // stop if we run out of space
		ImageImpl* img = dynamic_cast<ImageImpl*>(image);
		numFrames--; // goes negative and loop continues if numFrames was all_frames (0)
		mFrames[mNumFrames].image = img;
		img->addRef();
		mFrames[mNumFrames].collisionMask = 0;
		mFrames[mNumFrames].imageFrameNum = startingFrame;
		mFrames[mNumFrames].centerOffsetX = 0;
		mFrames[mNumFrames].centerOffsetY = 0;
		mFrames[mNumFrames].center = Rect( (img->frames) ? img->frameWidth : img->width, img->height).centerPoint();
		mNumFrames++;
		startingFrame++;
		if (startingFrame >= img->frames) break; // stop if we run out of frames in the image
	} while (numFrames != 0);
}


#ifdef PDG_SPRITER_SUPPORT
void Sprite::selectAnimationTime(const char* clip, double normalizedSeconds) {
    mEntityInstance->setCurrentAnimation(clip);
    mEntityInstance->setCurrentTime(normalizedSeconds*1000.0);
    if(mIsAnimationPaused) mEntityInstance->pausePlayback();
    mIsAnimationFinished=mEntityInstance->getTimeRatio()>=1;
    mIsBlending=false;mBlendTargetName.clear();mBlendDurationMs=mBlendElapsedMs=0;mBlendProgress=0;
    invalidateSpriterPose();
}
void Sprite::seekAnimation(const char* clip, double timeSeconds) {
    if(AnimationPipeline::isInsideCallback()) throw std::logic_error("Seek must occur outside a modifier");
    if(!mAnimationPoseAdapter || !mAnimationRigSchema || !clip) throw std::logic_error("Seek requires an enabled pose and clip");
    const double time=SpriterPoseAdapter::normalizedTime(*mEntityInstance,*mAnimationRigSchema,clip,timeSeconds);
    const auto candidate=sampleAnimationPose(clip,timeSeconds);
    for(AnimationBoneId id=0;id<candidate.getRig()->getBoneCount();++id)candidate.getWorldTransform(id,spriterRootTransform());
    for(AnimationBindingId id=0;id<candidate.getRig()->getBindingCount();++id)candidate.getWorldBindingTransform(id,spriterRootTransform());
    mAnimationPoseAdapter->cancelTransition();selectAnimationTime(clip,time);refreshSpriterPose();
}
void Sprite::transitionToAnimation(const char* clip,double timeSeconds,double durationSeconds) {
    if(AnimationPipeline::isInsideCallback()) throw std::logic_error("Transition must occur outside a modifier");
    if(!std::isfinite(durationSeconds) || durationSeconds<0) throw std::invalid_argument("Transition duration must be finite nonnegative seconds");
    if(!mAnimationPoseAdapter || !mAnimationRigSchema || !clip) throw std::logic_error("Transition requires an enabled pose and clip");
    const double time=SpriterPoseAdapter::normalizedTime(*mEntityInstance,*mAnimationRigSchema,clip,timeSeconds);
    const auto candidate=sampleAnimationPose(clip,timeSeconds); // Validate without mutating live selection.
    for(AnimationBoneId id=0;id<candidate.getRig()->getBoneCount();++id)candidate.getWorldTransform(id,spriterRootTransform());
    for(AnimationBindingId id=0;id<candidate.getRig()->getBindingCount();++id)candidate.getWorldBindingTransform(id,spriterRootTransform());
    if(durationSeconds==0) {
        seekAnimation(clip,timeSeconds);mAnimationPoseAdapter->completeInstantTransition();
        if(mLayer)mLayer->notifyAnimationAction(action_AnimationBlendComplete,this);return;
    }
    getAnimationPose(); // Capture the current base, including an interrupted blend.
    mAnimationPoseAdapter->beginTransition(*mSpriterModel,mEntityInstance->currentAnimationName(),mEntityInstance->getCurrentTime()/1000.0,durationSeconds,mIsBlending);
    selectAnimationTime(clip,time);mIsAnimationFinished=false;refreshSpriterPose();
}
bool Sprite::isAnimationTransitioning() const {return mAnimationPoseAdapter && mAnimationPoseAdapter->isTransitioning();}
double Sprite::getAnimationTransitionProgress() const {return mAnimationPoseAdapter?mAnimationPoseAdapter->transitionProgress():0;}

AnimationModifierId Sprite::addAnimationIK(const AnimationTwoBoneIK& config, int order) {
    auto candidate = getAnimationPose();
    auto state = std::make_shared<AnimationIKState>(); state->config = config;
    state->result = solveAnimationTwoBoneIK(candidate, config, spriterRootTransform());
    const auto id = addAnimationModifier([state](AnimationPoseView view, const AnimationModifierContext& context) {
        auto pose = view.copy();
        state->result = solveAnimationTwoBoneIK(pose, state->config, context.root);
        view.setLocalTransform(state->config.root, pose.getLocalTransform(state->config.root));
        view.setLocalTransform(state->config.middle, pose.getLocalTransform(state->config.middle));
        view.setLocalTransform(state->config.tip, pose.getLocalTransform(state->config.tip));
    }, animationStage_Constraint, order);
    mAnimationIK.emplace(id,state); return id;
}
void Sprite::setAnimationIKTarget(AnimationModifierId id, double x, double y, int space) {
    if (!std::isfinite(x) || !std::isfinite(y) || space < animationSpace_Local || space > animationSpace_World)
        throw std::invalid_argument("Invalid IK target or coordinate space");
    const auto found=mAnimationIK.find(id);
    if(found==mAnimationIK.end()) throw std::out_of_range("Unknown IK constraint ID");
    found->second->config.targetX=x; found->second->config.targetY=y; found->second->config.space=space;
    invalidateSpriterPose();
}
AnimationIKResult Sprite::getAnimationIKResult(AnimationModifierId id) const {
    getAnimationPose();
    const auto found=mAnimationIK.find(id);
    if(found==mAnimationIK.end()) throw std::out_of_range("Unknown IK constraint ID");
    const auto error=mAnimationPipeline->getModifierError(id);
    if(!error.empty()) throw std::logic_error(error);
    return found->second->result;
}

AnimationModifierId Sprite::addAnimationModifier(AnimationPipeline::Modifier callback, int stage, int order) {
    if (!mAnimationPoseAdapter || !mAnimationPipeline) throw std::logic_error("Enable animation pose before registering modifiers");
    const auto id = mAnimationPipeline->addModifier(std::move(callback), stage, order);
    invalidateSpriterPose(); return id;
}
void Sprite::removeAnimationModifier(AnimationModifierId id) {
    mAnimationIK.erase(id);
    if (mAnimationPipeline) { mAnimationPipeline->removeModifier(id); invalidateSpriterPose(); }
}
void Sprite::clearAnimationModifiers() {
    mAnimationIK.clear();
    if (mAnimationPipeline) { mAnimationPipeline->clearModifiers(); invalidateSpriterPose(); }
}
std::string Sprite::getAnimationModifierError(AnimationModifierId id) const {
    if (!mAnimationPipeline) throw std::logic_error("Animation pose is disabled");
    return mAnimationPipeline->getModifierError(id);
}
void Sprite::setAnimationSource(int source) {
    if (!mAnimationPipeline) throw std::logic_error("Enable animation pose before selecting a source");
    mAnimationPipeline->setSource(source); invalidateSpriterPose();
}
int Sprite::getAnimationSource() const { return mAnimationPipeline ? mAnimationPipeline->getSource() : animationSource_Clip; }
bool Sprite::isAnimationDrawingSupported() const {
#ifdef PDG_NO_GUI
    return false;
#else
    return true;
#endif
}
void Sprite::setAnimationDebugDraw(int flags) {
    if (flags < animationDebug_None || flags > animationDebug_All)
        throw std::invalid_argument("Unknown animationDebug flag bits");
    if (flags && (!isAnimationDrawingSupported() || !mAnimationPoseAdapter))
        throw std::logic_error("Animation debug drawing requires GUI support and an enabled pose");
    mAnimationDebugDraw = flags;
}
int Sprite::getAnimationDebugDraw() const { return mAnimationDebugDraw; }
void Sprite::drawAnimationDebug() const {
#ifndef PDG_NO_GUI
    if (!mAnimationDebugDraw || !mAnimationPoseAdapter || !mLayer) return;
    Port* port = mLayer->getSpritePort();
    if (!port) return;
    const auto& pose = mAnimationPoseAdapter->pose();
    const auto& rig = pose.getRig();
    const auto root = spriterRootTransform();
    const auto point = [&](const AnimationTransform& transform) {
        return mLayer->layerToPort(Point(transform.x, transform.y));
    };
    const auto attributes = [](const Color& color, double alpha) {
        return Attributes().lineColor(color).lineThickness(1).lineOpacity(alpha)
            .lineStyle(lineStyle_Solid).fillOpacity(0);
    };
    const auto cross = [&](const Point& center, const Attributes& style) {
        // Markers and line width are explicitly in port pixels.
        port->drawLine(Point(center.x - 3, center.y), Point(center.x + 3, center.y), style);
        port->drawLine(Point(center.x, center.y - 3), Point(center.x, center.y + 3), style);
    };
    if (mAnimationDebugDraw & animationDebug_Bones) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        std::vector<PhysicsBody*> boneBodies(rig->getBoneCount(), nullptr);
        for (auto* part : mAnimationPhysicsParts)
            boneBodies[part->getBoneId()] = part->physics.operator->();
        const auto connectedToParent = [&](AnimationBoneId id) {
            auto* body = boneBodies[id];
            if (!body) return true;
            auto parent = rig->getBone(id).parent;
            // Generated rigs skip helper bones that have no physical length.
            while (parent != animation_NoBone && !boneBodies[parent])
                parent = rig->getBone(parent).parent;
            if (parent == animation_NoBone) return true;
            for (uint32_t i = 0; i < body->getConstraintCount(); ++i) {
                const auto& joint = body->getConstraint(i);
                // Angular-only constraints do not hold the bones together.
                if (!joint.isActive() || joint.getType() < constraint_Pin ||
                    joint.getType() > constraint_Spring) continue;
                if (&joint.getBodyA() == boneBodies[parent] ||
                    &joint.getBodyB() == boneBodies[parent]) return true;
            }
            return false;
        };
#endif
        for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) {
            const auto& bone = rig->getBone(id);
            const auto world = pose.getWorldTransform(id, root);
            const auto style = attributes(Color(0.1f, 1.0f, 0.2f), world.alpha);
            const auto origin = point(world);
            if (bone.parent != animation_NoBone
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                && connectedToParent(id)
#endif
            )
                port->drawLine(point(pose.getWorldTransform(bone.parent, root)), origin, style);
            cross(origin, style);
            if (bone.length > 0) {
                AnimationTransform tip; tip.x = bone.length;
                port->drawLine(origin, point(AnimationTransform::compose(world, tip)), style);
            }
        }
    }
    if (mAnimationDebugDraw & animationDebug_Sockets) {
        for (AnimationSocketId id = 0; id < rig->getSocketCount(); ++id) {
            const auto world = pose.getWorldSocketTransform(id, root);
            const auto style = attributes(Color(0.2f, 0.6f, 1.0f), world.alpha);
            const auto origin = point(world);
            cross(origin, style);
            AnimationTransform tip; tip.x = 8;
            port->drawLine(origin, point(AnimationTransform::compose(world, tip)), style);
        }
    }
    if (mAnimationDebugDraw & animationDebug_Boxes) {
        for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id) {
            const auto& binding = rig->getBinding(id);
            if (binding.kind != animationBinding_Box || !isSpriterCollisionActive(binding.name.c_str())) continue;
            const auto world = pose.getWorldBindingTransform(id, root);
            port->drawQuad(mLayer->layerToPort(getSpriterCollisionBox(binding.name.c_str()).getQuad()),
                attributes(Color(1.0f, 0.5f, 0.1f), world.alpha));
        }
    }
#endif
}
AnimationTransform Sprite::spriterRootTransform() const {
    return {mLocation.x, mLocation.y, mFacing, mEntityScaleX * mScaleX, mEntityScaleY * mScaleY, mOpacity};
}
AnimationDrawableId Sprite::addAnimationDrawable(const AnimationDrawableOptions& options, const Drawing& drawing) {
    auto retained = drawing.share();
    const auto id=addAnimationDrawable(options, [retained](AnimationDrawingContext) { return retained; });
    mAnimationDrawings.find(id)->constantDrawing=retained;
    return id;
}
AnimationDrawableId Sprite::addAnimationDrawable(const AnimationDrawableOptions& options,AnimationDrawings::Callback callback){
    auto rig=getAnimationRig();if(!rig)throw std::logic_error("Enable animation pose before registering drawing callbacks");
    return mAnimationDrawings.add(options,std::move(callback),*rig);
}
void Sprite::removeAnimationDrawable(AnimationDrawableId id){mAnimationDrawings.remove(id);}
void Sprite::clearAnimationDrawables(){mAnimationDrawings.clear();}
void Sprite::setAnimationDrawableEnabled(AnimationDrawableId id,bool enabled){mAnimationDrawings.setEnabled(id,enabled);}
std::string Sprite::getAnimationDrawableError(AnimationDrawableId id)const{return mAnimationDrawings.error(id);}
AnimationDrawBounds Sprite::getAnimationDrawBounds()const{
    const auto pose = getAnimationPose();
    AnimationDrawBounds bounds;
#ifndef PDG_NO_GUI
    const auto root = spriterRootTransform();
    bool havePoint=false;bounds.uncullable=mAnimationDebugDraw!=animationDebug_None;
    auto include=[&](const Point& p){if(!havePoint){bounds.left=bounds.right=p.x;bounds.top=bounds.bottom=p.y;havePoint=true;}else{bounds.left=std::min(bounds.left,double(p.x));bounds.right=std::max(bounds.right,double(p.x));bounds.top=std::min(bounds.top,double(p.y));bounds.bottom=std::max(bounds.bottom,double(p.y));}};
    auto quadFor=[&](const AnimationTransform& t,const AnimationDrawBounds& b){Quad q(Rect(b.left,b.top,b.right,b.bottom));for(auto& p:q.points){const double x=p.x*t.scaleX,y=p.y*t.scaleY,c=std::cos(t.rotation),s=std::sin(t.rotation);p=Point(t.x+c*x-s*y,t.y+s*x+c*y);}return q;};
    for(AnimationBindingId id=0;id<pose.getRig()->getBindingCount();++id){const auto& binding=pose.getRig()->getBinding(id);if(binding.kind!=animationBinding_Image)continue;
        auto* object=mEntityInstance->objectIfExistsOnCurrentFrame(binding.name);auto* image=object?dynamic_cast<PDGImageFile*>(object->getImage()):nullptr;
        if(!image||!image->getPDGImage()){bounds.uncullable=true;continue;}
        const auto imageBounds=image->getPDGImage()->getImageBounds();const auto pivot=object->getPivot();
        const auto q=quadFor(pose.getWorldBindingTransform(id,root),{-pivot.x*imageBounds.width(),-pivot.y*imageBounds.height(),(1-pivot.x)*imageBounds.width(),(1-pivot.y)*imageBounds.height(),false});
        for(const auto& point:q.points)include(point);
    }
    for(const auto& option:mAnimationDrawings.options()){
        bounds.uncullable=bounds.uncullable||option.bounds.uncullable;
        const auto q=quadFor(pose.getWorldTransform(option.bone,root),option.bounds);for(const auto& point:q.points)include(point);
    }
    if(!havePoint)bounds.uncullable=true;
#endif
    return bounds;
}
void Sprite::drawAnimationArt(){
#ifndef PDG_NO_GUI
    if(!mLayer || !mLayer->getSpritePort() || !mAnimationPoseAdapter)return;
    if(mAnimationDrawings.empty()){mEntityInstance->render();return;}
    auto* port=mLayer->getSpritePort();const auto pose=mAnimationPoseAdapter->pose().copy();const auto root=spriterRootTransform();
    mAnimationDrawings.beginFrame();
    struct EndFrame{AnimationDrawings& drawings;~EndFrame(){drawings.endFrame();}} frame{mAnimationDrawings};
    auto render=[&](int placement,const std::string& slot){
        const auto commands=mAnimationDrawings.collect(placement,slot,pose,root);
        for(const auto& command:commands){if(!mAnimationDrawings.isEnabled(command.drawable))continue;
            try{
                auto point=[&](double x,double y){const auto& t=command.world;const double c=std::cos(t.rotation),s=std::sin(t.rotation);return mLayer->layerToPort(Point(t.x+x*t.scaleX*c-y*t.scaleY*s,t.y+x*t.scaleX*s+y*t.scaleY*c));};
                const auto origin=point(0,0), x=point(1,0), y=point(0,1);
                glm::mat3 matrix(1);
                matrix[0]=glm::vec3(x.x-origin.x,x.y-origin.y,0);
                matrix[1]=glm::vec3(y.x-origin.x,y.y-origin.y,0);
                matrix[2]=glm::vec3(origin.x,origin.y,1);
                Attributes attributes;
                attributes.setTransform(matrix).lineOpacity(command.world.alpha).fillOpacity(command.world.alpha);
                command.drawing->drawTransformed(port,attributes,command.strokeSpace==animationStroke_Local);
            }catch(const std::exception& error){mAnimationDrawings.fail(command.drawable,error.what());}
            catch(...){mAnimationDrawings.fail(command.drawable,"Animation drawing failed");}
        }
    };
    render(animationDraw_BeforeAll,"");
    auto* order=mEntityInstance->getZOrder();if(order)for(auto* object:*order){
        std::string slot;
        for(AnimationBindingId id=0;id<pose.getRig()->getBindingCount();++id){const auto& b=pose.getRig()->getBinding(id);if(b.kind==animationBinding_Image&&mEntityInstance->getObjectInstance(b.name)==object){slot=b.name;break;}}
        if(!slot.empty())render(animationDraw_BeforeSlot,slot);
        if(!slot.empty())render(animationDraw_ReplaceSlot,slot);
        bool replaced=false;for(const auto& option:mAnimationDrawings.options())if(option.placement==animationDraw_ReplaceSlot&&option.slot==slot)replaced=true;
        if(!replaced)object->render();
        if(!slot.empty())render(animationDraw_AfterSlot,slot);
    }
    render(animationDraw_AfterAll,"");
#endif
}

bool Sprite::supportsAnimationPhysics() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    return true;
#else
    return false;
#endif
}
Sprite& Sprite::setupPhysicsFromAnimationRig(double totalMass, double unitsPerMeter) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Physical rig changes must occur outside modifiers");
    if (!std::isfinite(totalMass) || totalMass <= 0 || !std::isfinite(unitsPerMeter) || unitsPerMeter <= 0)
        throw std::invalid_argument("Total mass and unitsPerMeter must be finite positive numbers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mLayer && mLayer->mUseChipmunkPhysics && cpSpaceIsLocked(mLayer->getSpace())) throw std::logic_error("Set up physical rigs outside collision callbacks");
    if (mAnimationPhysics) {
        if (!mAnimationPhysics->definition().generated || unitsPerMeter != mAnimationPhysicsUnitsPerMeter)
            throw std::logic_error("Disable the physical rig before changing its generation configuration");
        const auto& definitions = mAnimationPhysics->definition().bodies;
        if(mAnimationPhysicsMembers.size()!=definitions.size() ||
            std::any_of(mAnimationPhysicsParts.begin(),mAnimationPhysicsParts.end(),[this](auto* part){return !isAnimationPhysicsPartAttached(part);}))
            throw std::logic_error("Membership changed; use physics.setMass() or restore the original rig before repeating setup");
        long double originalTotal = 0; for (const auto& body : definitions) originalTotal += body.mass;
        std::vector<double> masses;
        for (const auto& body : definitions) masses.push_back(scaledPhysicalValue(totalMass,body.mass,double(originalTotal)));
        physics->configureAssemblyMasses(masses);
        return *this;
    }
    std::vector<std::string> diagnostics;
    auto definition = generateAnimationPhysicsDefinition(getAnimationPose(), spriterRootTransform(),
        totalMass, mAnimationPhysicsRootOverride, unitsPerMeter, diagnostics);
    setupAnimationPhysics(definition);
    mAnimationPhysicsUnitsPerMeter = unitsPerMeter;
    mAnimationPhysicsSetupWarnings = std::move(diagnostics);
    return *this;
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
}
AnimationBoneId Sprite::getAnimationPhysicsRoot() const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mAnimationPhysics) { const auto& def=mAnimationPhysics->definition();return def.bodies[def.rootBody].bone; }
#endif
    auto rig=getAnimationRig();if (!rig) throw std::logic_error("Enable an animation pose before selecting its physical root");
    return selectAnimationPhysicsRoot(*rig,mAnimationPhysicsRootOverride);
}
Sprite& Sprite::setAnimationPhysicsRoot(const char* name) {
    auto rig=getAnimationRig();
    if (!rig || !name) throw std::invalid_argument("Physical root requires a bone in the enabled rig");
    const auto id=rig->findBone(name);
    if (id==animation_NoBone) throw std::invalid_argument("Unknown physical root bone");
    return setAnimationPhysicsRoot(id);
}
Sprite& Sprite::setAnimationPhysicsRoot(AnimationBoneId bone) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Physical root changes must occur outside modifiers");
    auto rig=getAnimationRig();
    if (!rig || bone>=rig->getBoneCount()) throw std::invalid_argument("Unknown physical root bone");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mAnimationPhysics) {
        if ((getSpace() && cpSpaceIsLocked(getSpace()))) throw std::logic_error("Change physical roots outside collision callbacks");
        const auto& def=mAnimationPhysics->definition();

        auto found=std::find_if(def.bodies.begin(),def.bodies.end(),[bone](const auto& body){return body.bone==bone;});
        if (found==def.bodies.end()) throw std::logic_error("Disable the rig before selecting a previously skipped bone as root");
        const auto index=uint32_t(found-def.bodies.begin());
        if(!mAnimationPhysics->isBodyAttached(index))throw std::logic_error("A detached component cannot be the physical root");
        mAnimationPhysics->setRootBody(index);physics->mAssemblyRoot=mAnimationPhysicsParts[index]->physics.operator->();
    }
#endif
    mAnimationPhysicsRootOverride=bone;return *this;
}
Sprite& Sprite::clearAnimationPhysicsRoot() {
    auto rig=getAnimationRig();if (!rig) throw std::logic_error("Enable an animation pose before selecting its physical root");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mAnimationPhysics)
        setAnimationPhysicsRoot(mAnimationPhysics->definition().bodies[selectAnimationPhysicsMemberRoot(mAnimationPhysicsMembers)].bone);
    else
#endif
        setAnimationPhysicsRoot(selectAnimationPhysicsRoot(*rig));
    mAnimationPhysicsRootOverride=animation_NoBone;return *this;
}
bool Sprite::isAnimationPhysicsEnabled() const {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    return mAnimationPhysics!=nullptr;
#else
    return false;
#endif
}
void Sprite::setupAnimationPhysics(const AnimationPhysicsDefinition& definition) {
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Physical rig changes must occur outside modifiers");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(!mLayer || !mLayer->mUseChipmunkPhysics || !mAnimationPoseAdapter)throw std::logic_error("Physical animation requires an enabled pose and physics layer");
    if(mAnimationPhysics)throw std::logic_error("Disable the current physical rig before replacing it");
    if (mAttachmentPart) throw std::logic_error("Detach the mounted Sprite before creating a physical rig");
    {
        long double total = 0;
        for (const auto& body : definition.bodies) {
            total += body.mass;
            const Point start(-body.length/2,0), end(body.length/2,0);
            if (!std::isfinite(start.x) || !std::isfinite(end.x) || (definition.generated && start == end))
                throw std::invalid_argument("Physical capsule endpoints are not representable");
        }
        if (!std::isfinite(double(total)) || total <= 0)
            throw std::invalid_argument("Assembly total mass is not representable");
    }
    int joints=0;if(mBody)cpBodyEachConstraint(mBody,[](cpBody*,cpConstraint*,void* data){++*static_cast<int*>(data);},&joints);
    if(joints || physics.getConstraintCount())throw std::logic_error("Detach Sprite root joints before assigning physical root ownership");
    const auto pose=getAnimationPose();const auto velocity=physics.getVelocity();
    auto rig=std::make_unique<AnimationPhysicsRig>(mLayer->getSpace(),definition,pose,spriterRootTransform(),velocity.x,velocity.y,physics.getAngularVelocity(),true);
    auto desired=std::make_unique<AnimationPose>(pose);
    std::vector<Part*> parts;
    std::vector<std::unique_ptr<PhysicsBody>> bodies;
    parts.reserve(definition.bodies.size());bodies.reserve(definition.bodies.size());
    for (size_t i=0; i<definition.bodies.size(); ++i) {
        const auto& def=definition.bodies[i];
        auto* part=findPart(pose.getRig()->getBone(def.bone).name);
        if (part && (part->physics != PhysicsBody::NoPhysics || part->collider != Collider::NoCollider || part->getBoneId()!=def.bone ||
            part->mParent || part->mBinding!=animation_NoBinding || part->mSocket!=animation_NoSocket ||
            part->mLocation!=Point(def.offsetX,def.offsetY) || part->mFacing!=float(def.offsetRotation) ||
            part->mScaleX!=1 || part->mScaleY!=1 || part->mFlipX || part->mFlipY))
            throw std::logic_error("Physical rig Part name conflicts with an existing Part: " + pose.getRig()->getBone(def.bone).name);
        parts.push_back(part);
        const double moment=definition.generated ? cpBodyGetMoment(rig->body(i)) : cpMomentForSegment(def.mass,cpv(-def.length/2,0),cpv(def.length/2,0),def.radius);
        auto body=std::make_unique<PhysicsBody>(def.mass,moment);
        const auto state=rig->getBodyState(i);
        body->setMode(def.mode==animationBody_Kinematic?physicsBody_Kinematic:physicsBody_Dynamic);
        body->teleport(Point(state.x,state.y),state.rotation);
        body->setVelocity(state.velocityX,state.velocityY).setAngularVelocity(state.angularVelocity);
        body->setFriction(def.friction).setRestitution(def.elasticity);
        body->attachSolver(rig->createBodySolver(i,[this] { invalidateSpriterPose(); }));
        bodies.push_back(std::move(body));
    }
    {
        for (const auto& joint : definition.joints) {
            const double aSign=definition.generated?1:rig->bodyReflection(joint.parent);
            const double bSign=definition.generated?1:rig->bodyReflection(joint.child);
            auto& link=bodies[joint.parent]->createPivotJoint(*bodies[joint.child],
                Point(joint.parentX,aSign*joint.parentY),Point(joint.childX,bSign*joint.childY));
            link.setMaxForce(joint.maxForce).setCollideBodies(joint.collide);
            if (!definition.generated) bodies[joint.parent]->createRotaryLimit(*bodies[joint.child],
                aSign<0?-joint.maxAngle:joint.minAngle,aSign<0?-joint.minAngle:joint.maxAngle)
                .setMaxForce(joint.maxForce).setCollideBodies(joint.collide);
        }
    }
    std::vector<PhysicsBody*> assembly;
    { assembly.reserve(bodies.size());for (auto& body : bodies) assembly.push_back(body.get()); }
    // Validate and allocate before modifying caller-owned associations.
    std::vector<PartId> created;created.reserve(parts.size());
    std::map<Part*,Part*> members;
    try {
        for (size_t i=0; i<parts.size(); ++i) if (!parts[i]) {
            const auto& def=definition.bodies[i];
            auto* part=createPart(pose.getRig()->getBone(def.bone).name);
            created.push_back(part->getId());parts[i]=part;
            part->bindToBone(def.bone);
            part->setLocation(Point(def.offsetX,def.offsetY));part->setRotation(def.offsetRotation);
        }
        {
            for(auto* part:parts)members.emplace(part,nullptr);
            for(auto* part:parts)for(auto ancestor=pose.getRig()->getBone(part->getBoneId()).parent;ancestor!=animation_NoBone;ancestor=pose.getRig()->getBone(ancestor).parent) {
                auto found=std::find_if(parts.begin(),parts.end(),[ancestor](Part* p){return p->getBoneId()==ancestor;});
                if(found!=parts.end()){members.at(part)=*found;break;}
            }
        }
        if (physics == PhysicsBody::NoPhysics) setupPhysicsBody();
        else if (!mBody) initCpBody();
        for (size_t i=0;i<parts.size();++i) {
            const auto& def=definition.bodies[i];
            auto& shape=parts[i]->setupCollider();
            if(def.length>0)shape.setCapsule(Point(-def.length/2,0),Point(def.length/2,0),def.radius);
            else shape.setCircle(def.radius);
            shape.setGroup(definition.selfCollisions ? 0 : iid).setCategory(def.categories).setCollisionMask(def.mask);
        }
    } catch (...) { for (auto id:created) removePart(id); throw; }
    for (size_t i=0; i<parts.size(); ++i) {
        parts[i]->initializeAnimationPhysicsBody(*bodies[i]);bodies[i].release();
    }
    mAnimationPhysicsParts=std::move(parts);
    mAnimationPhysicsMembers=std::move(members);
    rig->owner=this;
    mAnimationSavedBodyType=cpBodyGetType(mBody);mAnimationSavedMass=cpBodyGetMass(mBody);mAnimationSavedMoment=cpBodyGetMoment(mBody);
    if(mCollideShape){mAnimationSavedFilter=cpShapeGetFilter(mCollideShape);cpShapeSetFilter(mCollideShape,CP_SHAPE_FILTER_NONE);}
    physics.setMode(physicsBody_Kinematic);cpBodySetVelocity(mBody,cpvzero);cpBodySetAngularVelocity(mBody,0);
    {
        physics->mAssemblyBodies=std::move(assembly);
        physics->mAssemblyRoot=physics->mAssemblyBodies[definition.rootBody];
        for (auto* body : physics->mAssemblyBodies) body->mAssemblyOwner=physics.operator->();
        collider->syncNative(nullptr);
    }
    mAnimationDesired=std::move(desired);mAnimationPhysics=std::move(rig);
    std::vector<PhysicsBody*> controlBodies;
    for(auto* part:mAnimationPhysicsParts)controlBodies.push_back(part->physics.operator->());
    mAnimationPhysics->attachBodies(controlBodies);
    mAnimationPhysics->frameChanged(spriterRootTransform());
    for(size_t i=0;i<mAnimationPhysicsParts.size();++i) {
        const auto bone=definition.bodies[i].bone;
        mAnimationPhysicsParts[i]->physics->mCoordinateMode=[this,bone](int mode) {
            if(mode==physicsBody_Static)throw std::invalid_argument("Mapped animation bodies cannot be Static");
            setAnimationPhysicsMode(mode==physicsBody_Dynamic?animationPhysics_Dynamic:animationPhysics_Kinematic,bone);
        };
    }
#else
    throw std::logic_error("Physical animation is unavailable in this build");
#endif
}
void Sprite::releaseAnimationPhysics() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(!mAnimationPhysics)return;
    // GC can destroy an unrelated, rigless Sprite during a script modifier.
    // Only an actual physical rig teardown mutates the animation/physics state.
    if(AnimationPipeline::isInsideCallback())throw std::logic_error("Physical rig changes must occur outside modifiers");
    if((getSpace() && cpSpaceIsLocked(getSpace()))){
        // Retain this Sprite until its pending teardown can safely change root type.
        struct Request{Sprite* sprite;};auto* request=new Request{this};addRef();
        cpSpaceAddPostStepCallback(getSpace(),[](cpSpace*,void* key,void*){auto* r=static_cast<Request*>(key);r->sprite->releaseAnimationPhysics();r->sprite->release();delete r;},request,nullptr);return;
    }
    try{publishAnimationPhysics();}catch(const std::exception& error){mAnimationRigError=error.what();}
    const auto state=mAnimationPhysics->getBodyState(mAnimationPhysics->definition().rootBody);
    const double total=physics.getMass();
    // Returning to different geometry keeps the explicitly configured single
    // body's inertia. Do not pretend its value is a pose-independent rig inertia.
    const double inertia=physics->mInertia;
    physics->mAssemblyRoot=nullptr;physics->mAssemblyBodies.clear();
    for(const auto& member:mAnimationPhysicsMembers)member.first->physics->mAssemblyOwner=nullptr;
    mAnimationPhysicsMembers.clear();
    mAnimationPhysics->releaseControls();
    // Borrowed solver references must detach before rig storage is destroyed.
    for (auto* part : mAnimationPhysicsParts) {
        part->mAnimationPhysicsBody = false;
        part->physics->mAssemblyOwner=nullptr;
        part->removeCollider();
        part->removePhysicsBody();
    }
    mAnimationPhysicsParts.clear();
    mAnimationPhysics.reset();mAnimationDesired.reset();
    physics->configureMass(total,inertia);
    physics.setMode(mAnimationSavedBodyType==CP_BODY_TYPE_DYNAMIC?physicsBody_Dynamic:mAnimationSavedBodyType==CP_BODY_TYPE_STATIC?physicsBody_Static:physicsBody_Kinematic);
    physics.setVelocity(state.velocityX,state.velocityY).setAngularVelocity(state.angularVelocity);
    if(mBody){
        cpBodySetVelocity(mBody,cpv(state.velocityX,state.velocityY));cpBodySetAngularVelocity(mBody,state.angularVelocity);
        if(mCollideShape)cpShapeSetFilter(mCollideShape,mAnimationSavedFilter);
    }
    if(mAnimationPoseAdapter)mAnimationPoseAdapter->recover(0);
    invalidateSpriterPose();
#endif
}
#ifdef PDG_USE_CHIPMUNK_PHYSICS
void Sprite::prepareAnimationPhysics(ms_delta elapsed){
    if(!mAnimationPhysics || !mAnimationPoseAdapter || !mAnimationDesired)return;
    mAnimationPhysics->prepare(*mAnimationDesired,spriterRootTransform(),double(elapsed)/1000.0);
}
void Sprite::publishAnimationPhysics(){
    if(!mAnimationPhysics || !mAnimationDesired || !mAnimationPoseAdapter)return;
    const auto root=mAnimationPhysics->followingRoot(*mAnimationDesired,spriterRootTransform());
    // Passive root transfer moves the Sprite frame to the simulated root. It
    // never moves a dynamic segment to an animation target.
    mLocation.x=root.x;mLocation.y=root.y;
    if(mBody){cpBodySetPosition(mBody,cpv(mLocation.x+mCenterOffset.x,mLocation.y+mCenterOffset.y));cpBodySetVelocity(mBody,cpvzero);cpBodySetAngularVelocity(mBody,0);}
    syncSpriterRoot();
    mAnimationPhysics->publishedRoot(root);
    mAnimationPoseAdapter->publish(mAnimationPhysics->publish(*mAnimationDesired,root),root);
    mSpriterPoseDirty=false;mColliderBoundsValid=false;mSpriterCollisionBoxCacheValid=false;updateAttachedSprites();
}
#endif

#include "sprite-animation-control.inc"
#include "sprite-animation-membership.inc"

bool Sprite::enableAnimationPose(const char* referenceAnimation) {
    if (AnimationPipeline::isInsideCallback()) { mAnimationRigError = "Rig replacement is not allowed inside a modifier"; return false; }
    try {
        if (isAnimationPhysicsEnabled()) throw std::logic_error("Disable physical animation before replacing its rig");
        if (!mSpriterModel || !mEntityInstance) throw std::invalid_argument("Sprite has no Spriter entity");
        if (!referenceAnimation) throw std::invalid_argument("Choose a reference animation explicitly");
        auto* factory = dynamic_cast<PDGFileFactory*>(mSpriterModel->getFileFactory());
        if (!factory) throw std::invalid_argument("Model has no PDG rig metadata");
        const auto catalog = factory->rigCatalog();
        const auto found = catalog->entities.find(mEntityInstance->currentEntityName());
        if (found == catalog->entities.end()) throw std::invalid_argument("Entity has no SCML rig metadata");
        auto schema = found->second;
        auto rig = schema->referenceRig(*mSpriterModel, referenceAnimation);
        auto adapter = std::make_unique<SpriterPoseAdapter>(*mEntityInstance, schema, rig);
        adapter->evaluate(mIsBlending ? mBlendTargetName : "", mBlendProgress, spriterRootTransform());
        mAnimationDrawings.clear();
        mAnimationRigSchema = std::move(schema);
        mAnimationPoseAdapter = std::move(adapter);
        mAnimationPhysicsRootOverride=animation_NoBone;mAnimationPhysicsSetupWarnings.clear();
        mAnimationPipeline = std::make_shared<AnimationPipeline>();
        mAnimationIK.clear();
        mAnimationRigError.clear();
        mAnimationDebugDraw = animationDebug_None;
        invalidateSpriterPose();
        refreshSpriterPose();
        return true;
    } catch (const std::exception& error) {
        mAnimationRigError = error.what();
        // A failed attempt does not discard a previously enabled pose or clock.
        invalidateSpriterPose();
        refreshSpriterPose();
        return false;
    }
}
void Sprite::disableAnimationPose() {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mAnimationPhysics && (getSpace() && cpSpaceIsLocked(getSpace())))
        throw std::logic_error("Disable animation poses outside locked physics callbacks");
#endif
    releaseAnimationPhysics();
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Rig replacement is not allowed inside a modifier");
    mAnimationPipeline.reset();
    mAnimationIK.clear();
    mAnimationDrawings.clear();
    mAnimationPoseAdapter.reset();
    for (auto* part : mParts) part->unbindFromBone(); mAnimationRigSchema.reset(); mAnimationRigError.clear();
    mAnimationDebugDraw = animationDebug_None;
    invalidateSpriterPose(); refreshSpriterPose();
}
bool Sprite::isAnimationPoseEnabled() const { return mAnimationPoseAdapter != nullptr; }
std::string Sprite::getAnimationRigError() const { return mAnimationRigError; }
std::shared_ptr<const AnimationRig> Sprite::getAnimationRig() const {
    return mAnimationPoseAdapter ? mAnimationPoseAdapter->pose().getRig() : nullptr;
}
AnimationPose Sprite::getAnimationPose() const {
    if (mAnimationPipeline && mAnimationPipeline->isEvaluating()) throw std::logic_error("Use the borrowed pose view inside a modifier");
    refreshSpriterPose();
    if (!mAnimationPoseAdapter) throw std::logic_error("Animation pose is not enabled: " + mAnimationRigError);
    return mAnimationPoseAdapter->pose().copy();
}
AnimationPose Sprite::sampleAnimationPose(const char* clip, double timeSeconds) const {
    if (!mAnimationPoseAdapter || !mAnimationRigSchema) throw std::logic_error("Animation pose is not enabled");
    if (!clip) throw std::invalid_argument("Missing sample clip");
    return SpriterPoseAdapter::sample(*mSpriterModel, *mAnimationRigSchema, getAnimationRig(), clip, timeSeconds);
}
std::vector<std::string> Sprite::getAnimationBoneNames() const {
    std::vector<std::string> names;
    const auto rig = getAnimationRig();
    if (rig) for (AnimationBoneId id = 0; id < rig->getBoneCount(); ++id) names.push_back(rig->getBone(id).name);
    return names;
}
std::vector<std::string> Sprite::getAnimationBindingNames() const {
    std::vector<std::string> names;
    const auto rig = getAnimationRig();
    if (rig) for (AnimationBindingId id = 0; id < rig->getBindingCount(); ++id) names.push_back(rig->getBinding(id).name);
    return names;
}
AnimationTransform Sprite::getAnimationBoneTransform(const char* name, int space) const {
    const auto pose = getAnimationPose();
    const auto id = pose.getRig()->findBone(name ? name : "");
    if (space == animationSpace_Local) return pose.getLocalTransform(id);
    if (space == animationSpace_Rig) return pose.getGlobalTransform(id);
    if (space == animationSpace_World) return pose.getWorldTransform(id, spriterRootTransform());
    throw std::invalid_argument("Invalid animation coordinate space");
}
AnimationTransform Sprite::getAnimationBindingTransform(const char* name, int space) const {
    const auto pose = getAnimationPose();
    const auto id = pose.getRig()->findBinding(name ? name : "");
    if (space == animationSpace_Local) return pose.getBindingLocalTransform(id);
    if (space == animationSpace_Rig) return pose.getBindingTransform(id);
    if (space == animationSpace_World) return pose.getWorldBindingTransform(id, spriterRootTransform());
    throw std::invalid_argument("Invalid animation coordinate space");
}
void Sprite::setAnimationBoneTransform(const char* name, const AnimationTransform& transform) {
    const auto pose = getAnimationPose();
    const auto id = pose.getRig()->findBone(name ? name : "");
    mAnimationPoseAdapter->setBoneOverride(id, transform, spriterRootTransform());
    invalidateSpriterPose(); refreshSpriterPose();
}
void Sprite::clearAnimationBoneTransforms() {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Use the borrowed pose view inside a modifier");
    if (!mAnimationPoseAdapter) return;
    mAnimationPoseAdapter->clearBoneOverrides();
    invalidateSpriterPose(); refreshSpriterPose();
}
void Sprite::publishSpriterPose(double deltaSeconds) const {
    if (!mAnimationPoseAdapter) return;
    try {
        mAnimationPoseAdapter->evaluate(mIsBlending ? mBlendTargetName : "", mBlendProgress, spriterRootTransform(), mAnimationPipeline.get(), deltaSeconds);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(mAnimationPhysics && mAnimationDesired)*mAnimationDesired=mAnimationPoseAdapter->pose().copy();
#endif
    }
    catch (const std::exception& error) {
        mAnimationRigError = error.what();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        if(mAnimationPhysics)const_cast<Sprite*>(this)->releaseAnimationPhysics();
#endif
        const_cast<Sprite*>(this)->mAnimationDrawings.clear();
        mAnimationPoseAdapter.reset();
    for (auto* part : mParts) part->unbindFromBone();
        mAnimationPipeline.reset();
    mAnimationIK.clear();
        mAnimationDebugDraw = animationDebug_None;
        // Restore the normal evaluator path after a failed publication.
        if (mIsBlending) mEntityInstance->blend(mBlendProgress, mEntityInstance->getTimeRatio());
        else mEntityInstance->reprocessCurrentTime();
    }
}

void Sprite::cacheSpriterAnimationNames() {
	mSpriterAnimationNames.clear();
	if (!mEntityInstance) return;
	// The evaluator exposes names through selection only. Enumerate at entity
	// setup, preserving the selected clip; queries then have no playback effects.
	const std::string selected = mEntityInstance->currentAnimationName();
	for (int id = 0; id < mEntityInstance->animationCount(); ++id) {
		mEntityInstance->setCurrentAnimation(id);
		mSpriterAnimationNames.push_back(mEntityInstance->currentAnimationName());
	}
	if (hasAnimation(selected.c_str())) mEntityInstance->setCurrentAnimation(selected);
	else if (!mSpriterAnimationNames.empty()) mEntityInstance->setCurrentAnimation(mSpriterAnimationNames.front());
}

bool Sprite::hasAnimation(const char* animationName) {
	return animationName && std::find(mSpriterAnimationNames.begin(),
		mSpriterAnimationNames.end(), animationName) != mSpriterAnimationNames.end();
}

bool Sprite::hasAnimation(int animationId) {
	return animationId >= 0 && static_cast<size_t>(animationId) < mSpriterAnimationNames.size();
}

void Sprite::startAnimation(const char* animationName) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback/rig changes must occur outside a modifier");
	if (!hasAnimation(animationName)) return;
	if(mAnimationPoseAdapter)mAnimationPoseAdapter->cancelTransition();
	mEntityInstance->setCurrentAnimation(animationName);
	mIsAnimationPaused = false;
	mIsAnimationFinished = false;
	mIsBlending = false;
	mBlendTargetName.clear();
	mBlendDurationMs = mBlendElapsedMs = 0.0;
	mBlendProgress = 0.0f;
	invalidateSpriterPose();
}

void Sprite::startAnimation(int animationId) {
	if (hasAnimation(animationId)) startAnimation(mSpriterAnimationNames[animationId].c_str());
}

// Character Maps
void Sprite::applyCharacterMap(const char* mapName) {
	if (mEntityInstance && mapName) {
		// Apply character map to the entity instance using SpriterPlusPlus
		mEntityInstance->applyCharacterMap(mapName);
		// Track the applied map in our list
		mAppliedCharacterMaps.push_back(std::string(mapName));
	}
}

void Sprite::removeCharacterMap(const char* mapName) {
	if (mEntityInstance && mapName) {
		// Remove character map from the entity instance using SpriterPlusPlus
		mEntityInstance->removeCharacterMap(mapName);
		// Remove from our tracking list
		std::string mapNameStr(mapName);
		auto it = std::find(mAppliedCharacterMaps.begin(), mAppliedCharacterMaps.end(), mapNameStr);
		if (it != mAppliedCharacterMaps.end()) {
			mAppliedCharacterMaps.erase(it);
		}
	}
}

void Sprite::removeAllCharacterMaps() {
	if (mEntityInstance) {
		// Remove all character maps from the entity instance using SpriterPlusPlus
		mEntityInstance->removeAllCharacterMaps();
	}
	// Clear our tracking list
	mAppliedCharacterMaps.clear();
}

std::vector<std::string> Sprite::getAppliedCharacterMaps() const {
	return mAppliedCharacterMaps;
}

// Event System (basic, triggers only)
namespace {
void releaseSpriterTrigger(void* data){
    auto* event=static_cast<SpriteTriggerEventInfo*>(data);
    free(const_cast<char*>(event->triggerName));free(const_cast<char*>(event->clipName));free(const_cast<char*>(event->entityName));
    if(event->actingSprite)event->actingSprite->release();
}
}
void Sprite::dispatchSpriterTriggers(double deltaSeconds){
    if(!mSpriterEventsEnabled || mIsAnimationPaused || mIsAnimationFinished || !mLayer || deltaSeconds<=0 || !mSpriterModel)return;
    auto* factory=dynamic_cast<PDGFileFactory*>(mSpriterModel->getFileFactory());if(!factory)return;
    auto catalog=factory->rigCatalog();auto found=catalog->entities.find(mEntityInstance->currentEntityName());if(found==catalog->entities.end())return;
    const auto clipName=mEntityInstance->currentAnimationName(),entityName=mEntityInstance->currentEntityName();
    auto authored=found->second->triggers.find(clipName);if(authored==found->second->triggers.end())return;
    const auto& clip=authored->second;if(clip.keys.empty())return;
    const double start=mEntityInstance->getCurrentTime()/1000.0,end=clip.looping?start+deltaSeconds:std::min(clip.duration,start+deltaSeconds);
    const uint64_t lastCycle=clip.looping?static_cast<uint64_t>(std::floor(end/clip.duration)):0;
    for(uint64_t cycle=0;cycle<=lastCycle;++cycle)for(const auto& key:clip.keys){
        const double occurrence=double(cycle)*clip.duration+key.seconds;
        if(occurrence<=start || occurrence>end)continue; // half-open (start,end], time zero fires only on wrap
        SpriteTriggerEventInfo event{};event.actingSprite=this;event.inLayer=mLayer;event.id=gNextSpriteEventId++;
        event.timeSeconds=key.seconds;event.offsetSeconds=occurrence-start;
        // Preserve a declared compatibility field without exposing it in new script payloads.
        event.frameTime=key.seconds<=2147483.647?static_cast<int>(key.seconds*1000.0):2147483647;
#ifndef PDG_NO_EVENT_QUEUE
        event.triggerName=strdup(key.name.c_str());event.clipName=strdup(clipName.c_str());event.entityName=strdup(entityName.c_str());addRef();
        EventManager::getSingletonInstance()->enqueueEvent(eventType_SpriteTriggerEvent,UserData::makeUserDataViaCopy(&event,sizeof(event),releaseSpriterTrigger),this);
#else
        event.triggerName=key.name.c_str();event.clipName=clipName.c_str();event.entityName=entityName.c_str();
        postEvent(eventType_SpriteTriggerEvent,&event);
#endif
    }
}

void Sprite::enableSpriterEvents(bool enable) {
	mSpriterEventsEnabled = enable;
}

bool Sprite::areSpriterEventsEnabled() const {
	return mSpriterEventsEnabled;
}

// Animation blending
void Sprite::blendToAnimation(const char* animationName, float blendTime) {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback changes must occur outside a modifier");
	if (!hasAnimation(animationName) || !std::isfinite(blendTime)) return;
	if(mAnimationPoseAdapter)mAnimationPoseAdapter->cancelTransition();
	mIsBlending = true;
	mBlendTargetName = animationName;
	mIsAnimationPaused = false;
	mIsAnimationFinished = false;
	mBlendDurationMs = std::max(0.0, static_cast<double>(blendTime) * 1000.0);
	mBlendElapsedMs = 0.0;
	mBlendProgress = 0.0f;
	// Public animation time is floating-point seconds; convert at the evaluator boundary.
	// A nonpositive duration completes on the next animation update.
	mEntityInstance->setCurrentAnimation(animationName, mBlendDurationMs);
	invalidateSpriterPose();
}

void Sprite::blendToAnimation(int animationId, float blendTime) {
	if (hasAnimation(animationId)) {
		blendToAnimation(mSpriterAnimationNames[animationId].c_str(), blendTime);
	}
}

bool Sprite::isBlending() const {
	return mIsBlending;
}

float Sprite::getBlendProgress() const {
	return mBlendProgress;
}

void Sprite::pauseAnimation() {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback changes must occur outside a modifier");
	if (mEntityInstance) {
		mEntityInstance->pausePlayback();
		mIsAnimationPaused = true;
	}
}

void Sprite::resumeSpriterBlend() {
	// Spriter stops its player when a nonlooping source ends, even during a
	// longer blend. Keep the transition running without rewinding that source.
	const double time = mEntityInstance->getCurrentTime();
	mEntityInstance->startResumePlayback();
	if (mEntityInstance->getCurrentTime() != time) mEntityInstance->setCurrentTime(time);
}

void Sprite::resumeAnimation() {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback changes must occur outside a modifier");
	if (mEntityInstance) {
		if (mIsBlending) resumeSpriterBlend();
		else mEntityInstance->startResumePlayback();
		mIsAnimationPaused = false;
		mIsAnimationFinished = false;
		invalidateSpriterPose();
	}
}

void Sprite::stopAnimation() {
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback changes must occur outside a modifier");
	if (mEntityInstance) {
		mEntityInstance->pausePlayback();
		mIsAnimationPaused = true;
	}
}

bool Sprite::isAnimationPlaying() const {
	return mEntityInstance && !mIsAnimationPaused && !mIsAnimationFinished;
}

bool Sprite::isAnimationPaused() const {
	return mIsAnimationPaused;
}

float Sprite::getAnimationProgress() const {
	if (mEntityInstance) {
		return mEntityInstance->getTimeRatio();
	}
	return 0.0f;
}

bool Sprite::hasAttachPoint(const char* attachPointName) const {
	if (mEntityInstance && attachPointName) {
		// Check if the AttachPoint exists by trying to get the object instance
		SpriterEngine::UniversalObjectInterface* obj = mEntityInstance->getObjectInstance(attachPointName);
		return obj != nullptr;
	}
	return false;
}

Offset Sprite::getAttachPoint(const char* attachPointName) const {
	if (mEntityInstance && attachPointName) {
		refreshSpriterPose();
		auto* obj = mEntityInstance->objectIfExistsOnCurrentFrame(attachPointName);
		if (obj) {
			const auto pos = obj->getPosition();
			return Offset(pos.x - mLocation.x, pos.y - mLocation.y);
		}
	}
	return Offset(NAN, NAN);
}


void Sprite::attachSprite(Sprite* sprite, const char* attachPointName) {
	if (!sprite || sprite->mAttachmentPart || !hasAttachPoint(attachPointName) || sprite->attachmentReaches(this)) return;
	// Layer coordinates are only comparable within one layer.
	if (sprite->mLayer != mLayer) return;
	auto it = mAttachedSprites.find(attachPointName);
	if (it != mAttachedSprites.end() && it->second == sprite) return;
    if (sprite->mSpriterAttachmentOwner) return;
	sprite->addRef(); // retain before releasing a replaced attachment's subtree
	Sprite* previous = it == mAttachedSprites.end() ? nullptr : it->second;
	mAttachedSprites[attachPointName] = sprite;
    sprite->mSpriterAttachmentOwner = this;
	if (previous) { previous->mSpriterAttachmentOwner = nullptr; previous->release(); }
}

void Sprite::detachSprite(Sprite* sprite) {
	if (!sprite) return;
	for (auto it = mAttachedSprites.begin(); it != mAttachedSprites.end();) {
		if (it->second == sprite) {
			it = mAttachedSprites.erase(it);
            sprite->mSpriterAttachmentOwner = nullptr;
			sprite->release();
		} else {
			++it;
		}
	}
}

void Sprite::clearAttachedSprites() {
	std::map<std::string, Sprite*> attached;
	attached.swap(mAttachedSprites);
	for (const auto& item : attached) {
		if (item.second) { item.second->mSpriterAttachmentOwner = nullptr; item.second->release(); }
	}
}

void Sprite::invalidateSpriterPose() const {
	mSpriterPoseDirty = true;
	mColliderBoundsValid = false;
	mSpriterCollisionBoxCacheValid = false;
}

void Sprite::syncSpriterRoot() const {
	mEntityInstance->setPosition(SpriterEngine::point(mLocation.x, mLocation.y));
	mEntityInstance->setAngle(mFacing);
	mEntityInstance->setScale(SpriterEngine::point(mEntityScaleX * mScaleX, mEntityScaleY * mScaleY));
	mEntityInstance->setAlpha(mOpacity);
}

void Sprite::refreshSpriterPose() const {
    if (mAnimationPipeline && mAnimationPipeline->isEvaluating()) return; // callbacks use their borrowed view
	if (mEntityInstance && mEntityInstance->getAlpha() != mOpacity) invalidateSpriterPose();
	if (!mEntityInstance || !mSpriterPoseDirty) return;
	syncSpriterRoot();
	if (mIsBlending) {
		mEntityInstance->blend(mBlendProgress, mEntityInstance->getTimeRatio());
	} else {
		mEntityInstance->reprocessCurrentTime();
	}
	publishSpriterPose();
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mAnimationPhysics)const_cast<Sprite*>(this)->publishAnimationPhysics();
#endif
	mSpriterPoseDirty = false;
	updateAttachedSprites();
    const_cast<Sprite*>(this)->refreshPartPhysics();
    const_cast<Sprite*>(this)->updatePartAttachments();
}

void Sprite::updateAttachedSprites() const {
	for (auto& attachPair : mAttachedSprites) {
		if (attachPair.second) {
			// Get the AttachPoint position and update the attached sprite
			SpriterEngine::UniversalObjectInterface* obj = mEntityInstance->objectIfExistsOnCurrentFrame(attachPair.first);
			if (obj) {
				float angle = obj->getAngle();
				Sprite* attachedSprite = attachPair.second;
				const auto pos = obj->getPosition();
				attachedSprite->setLocation(Point(pos.x, pos.y));
				attachedSprite->rotateTo(angle);
			}
		}
	}
}

void Sprite::activateSubEntity(const char* entityName, const char* animationName) {
    if(isAnimationPhysicsEnabled())throw std::logic_error("Disable physical animation before changing entity");
    if (AnimationPipeline::isInsideCallback()) throw std::logic_error("Playback/rig changes must occur outside a modifier");
	if (mEntityInstance && mSpriterModel && entityName) {
		const std::string oldEntity = mEntityInstance->currentEntityName();
        const std::string requestedClip = animationName ? animationName : "idle";
        if (oldEntity == entityName) {
            if (!hasAnimation(requestedClip.c_str())) return;
        } else {
            // Validate against an independent instance before changing the live
            // entity. Spriter otherwise retains the old clip on an invalid name.
            std::unique_ptr<SpriterEngine::EntityInstance> candidate(mSpriterModel->getNewEntityInstance(entityName));
            if (!candidate) return;
            bool found = false;
            for (int id = 0; id < candidate->animationCount(); ++id) {
                candidate->setCurrentAnimation(id);
                if (candidate->currentAnimationName() == requestedClip) { found = true; break; }
            }
            if (!found) return;
        }
		// Use the sprite's model for auto-append functionality
		mEntityInstance->setCurrentEntity(entityName, animationName ? animationName : "idle", mSpriterModel);
		if (mEntityInstance->currentEntityName() != entityName) return;
		if (mEntityInstance->currentEntityName() != oldEntity) {
			clearAttachedSprites();
            mAnimationDrawings.clear();
			mAnimationPoseAdapter.reset();
    for (auto* part : mParts) part->unbindFromBone();
            mAnimationPipeline.reset();
    mAnimationIK.clear();
            mAnimationDebugDraw = animationDebug_None;
			mAnimationRigSchema.reset();
			mAnimationRigError = "Entity changed; enable the new rig explicitly";
		}
		cacheSpriterAnimationNames();
		const std::string selected = mEntityInstance->currentAnimationName();
		startAnimation(selected.c_str());
	}
}

Sprite* Sprite::getAttachedSprite(const char* attachPointName) const {
	if (attachPointName) {
		std::string attachPointStr(attachPointName);
		auto it = mAttachedSprites.find(attachPointStr);
		if (it != mAttachedSprites.end()) {
			return it->second;
		}
	}
	return nullptr;
}

#endif // PDG_SPRITER_SUPPORT


#ifndef PDG_NO_GUI
// set a drawing helper that will be called before the sprite is drawn
// it can do whatever drawing it likes, then return true if it wants to let the
// sprite draw itself, or false if the sprite should skip it's normal drawing
// if a post draw helper is set, it will always be called, even if false is returned
void    Sprite::setDrawHelper(ISpriteDrawHelper* helper) {
	if (mDrawHelper && mDrawHelper->ownedBySprite()) {
		delete mDrawHelper;
		mDrawHelper = 0;
	}
	mDrawHelper = helper;

}

// set a drawing helper that will be called after a sprite is drawn
// it can do whatever drawing it likes. The return value is ignored since
// the sprite has already drawn. If set, it is called even if the primary draw 
// helper tells the Sprite to skip normal drawing.
void    Sprite::setPostDrawHelper(ISpriteDrawHelper* helper) {
	if (mPostDrawHelper && mPostDrawHelper->ownedBySprite()) {
		delete mPostDrawHelper;
		mPostDrawHelper = 0;
	}
	mPostDrawHelper = helper;
}	
#endif

// replace an image with another one for all the frames that reference that image
void	Sprite::changeFramesImage(Image* oldImage, Image* newImage) {
	ImageImpl* img = dynamic_cast<ImageImpl*>(newImage);
	for (int i = 0; i< mNumFrames; i++) {
		if (mFrames[i].image == oldImage) {
			mFrames[i].image = img;
			oldImage->release();
			newImage->addRef();
		}
	}
}

RotatedRect
Sprite::getFrameRotatedBounds(int frameNum) {
	if ( (frameNum <= 0) || (frameNum > mNumFrames) ) {
		frameNum = mCurrFrame;
	}
    Rect r = mFrames[frameNum].image->getImageBounds();
    r.setWidth(r.width() * std::abs(mScaleX)).setHeight(r.height() * std::abs(mScaleY));
    r.center(mLocation);
    Offset coff(mFrames[frameNum].centerOffsetX, mFrames[frameNum].centerOffsetY);
    RotatedRect rr(r, mFacing, coff);
    return rr;
}


// set offset of centerpoint of sprite (rotation and location are all relative to centerpoint)
// this can be set for the whole sprite, if image, or for an individual frame or group of
// frames by specifying the image or by specifying the range of frames
// if image is 0, the startingFrame and numFrames parameters are frame numbers for the Sprite
// if image is specified, the startingFrame and numFrames paramaters are Image frame numbers
// this offset is relative to the absolute center of the image or frame
void	Sprite::offsetFrameCenters(int offsetX, int offsetY, Image* image, int startingFrame, int numFrames) {
	if (startingFrame < 0) startingFrame = 0;
	if (numFrames >= 0) {
		if (image == 0) {
			for (int i = startingFrame; i< mNumFrames; i++) {
				mFrames[i].centerOffsetX = offsetX;
				mFrames[i].centerOffsetY = offsetY;
				numFrames--;
				if (numFrames == 0) break;
			}
		} else {
			bool found = false;
			for (int i = 0; i< mNumFrames; i++) {
				if (mFrames[i].image == image) {
					if (!found) {
						if (startingFrame == 0) {
							found = true;
						} else {
							startingFrame--;
						}
					}
					if (found) {
						mFrames[i].centerOffsetX = offsetX;
						mFrames[i].centerOffsetY = offsetY;
						numFrames--;
						if (numFrames == 0) break;
					}
				} else if (found) {
					break;
				}
			}
		}
	}
}


// fetch the offsets set above, but only for a single frame
Offset	Sprite::getFrameCenterOffset(Image* image, int frameNum) {
	int offsetX = 0;
	int offsetY = 0;
	if (frameNum >= 0) {
		if (image == 0) {
			if (frameNum < mNumFrames) {
				offsetX = mFrames[frameNum].centerOffsetX;
				offsetY = mFrames[frameNum].centerOffsetY;
			}
		} else {
			for (int i = 0; i< mNumFrames; i++) {
				if (mFrames[i].image == image) {
					int fn = frameNum + i;
					if ( (fn < mNumFrames) && (mFrames[fn].image == image)) {
						offsetX = mFrames[fn].centerOffsetX;
						offsetY = mFrames[fn].centerOffsetY;
					}
					break;
				}
			}
		}
	}
	return Offset(offsetX, offsetY);
}



// arrange sprites within layer
Sprite& Sprite::moveBehind(Sprite* sprite) {
    if (mLayer && sprite && sprite != this && sprite->mLayer == mLayer)
        mLayer->reorderSprite(this, sprite->mPrevSprite);
    return *this;
}

Sprite& Sprite::moveInFrontOf(Sprite* sprite) {
    if (mLayer && sprite && sprite != this && sprite->mLayer == mLayer)
        mLayer->reorderSprite(this, sprite);
    return *this;
}

int Sprite::getZOrder() {
	if (mLayer == 0) return -1;
	return mLayer->getSpriteZOrder(this);
}

bool Sprite::isBehind(Sprite* sprite) {
	if (mLayer == 0) return false;
	return mLayer->isSpriteBehind(this, sprite);
}


// fading, with 1.0 being complete opaque and 0.0 being completely transparent
Sprite& Sprite::setOpacity(float opacity) {
	mOpacity = opacity;
	if (mOpacity > 1.0) {
		mOpacity = 1.0;
	} else if (mOpacity < 0.0) {
		mOpacity = 0.0;
	}
	return *this;
}

float Sprite::getOpacity() {
	return mOpacity;
}

void Sprite::fadeTo(float targetOpacity, double durationSeconds, EasingFunc easing) {
	if (targetOpacity > 1.0) {
		targetOpacity = 1.0;
	} else if (targetOpacity < 0.0) {
		targetOpacity = 0.0;
	}
    validateAnimationDuration(durationSeconds);
    if (!std::isfinite(targetOpacity) || !easing) throw std::invalid_argument("Invalid fade target or easing");
    beginAnimationRequest();
    Animation a(&mOpacity,targetOpacity,easing,mDelaySeconds,durationSeconds);
    a.operation=mAnimationOperation; a.chained=mAppendAnimation; a.completion=1;
    prepareAnimation(&mOpacity);
    mAnimations.push_back(a);
	mFadeCompleteAction = action_FadeComplete;
    finishAnimationRequest();
}

void Sprite::fadeIn(double durationSeconds, EasingFunc easing)  {
    validateAnimationDuration(durationSeconds);
	if (!mAppendAnimation && mOpacity == 1.0) {  // if we are at our default full opacity, then set to transparent
		mOpacity = 0.0;     // this handles common case where we create a new sprite and want it
	}                       // to fade in, but don't want to manually set opacity to 0 first
	fadeTo(1.0, durationSeconds, easing);
	mFadeCompleteAction = action_FadeInComplete;
    mAnimations.back().completion = 2;
}

void Sprite::fadeOut(double durationSeconds, EasingFunc easing) {
	fadeTo(0.0, durationSeconds, easing);
	mFadeCompleteAction = action_FadeOutComplete;
    mAnimations.back().completion = 3;
}


// collisions









Sprite& Sprite::setFrameCollisionMask(Image* frameImage, Image* maskImage) {
	ImageImpl* img = dynamic_cast<ImageImpl*>(maskImage);
	for (int i = 0; i< mNumFrames; i++) {
		if (mFrames[i].image == frameImage) {
            if(maskImage) maskImage->addRef();
			Image* oldMask = mFrames[i].collisionMask;
			if (oldMask) {
				oldMask->release();
			}
			mFrames[i].collisionMask = img;

		}
	}	
    return *this;
}




	
#ifndef PDG_NO_GUI
Sprite& Sprite::setWantsMouseOverEvents(bool wantsThem) { 
	wantsMouseOver = wantsThem; 
	if (wantsThem) {
		mLayer->wantMouseOverEvents();
	} else {
		mLayer->checkIfMouseOverEventsStillWanted();
	}
	return *this; 
}
	
Sprite& Sprite::setWantsClickEvents(bool wantsThem) { 
	wantsClicks = wantsThem;
	if (wantsThem) {
		mLayer->wantClickEvents();
	} else {
		mLayer->checkIfClickEventsStillWanted();
	}
	return *this; 
}

Sprite& Sprite::setMouseDetectMode(int collisionType) {
	mMouseDetectMode = collisionType;
	return *this;
}
#endif // ! PDG_NO_GUI




bool Sprite::hitTest(const Point& p) {
	if (!mMouseDetectMode) return false;
	
	if (mMouseDetectMode == collide_CollisionRadius) {
		return collider.contains(p);
	}
	
	else if (mMouseDetectMode == collide_BoundingBox) {
		// local sprite bounding rect
        RotatedRect rectA = mNumFrames>0 ? getFrameRotatedBounds(mCurrFrame) : getRotatedBounds();
		
		// unit rect to represent the point
		RotatedRect rectB;
		rectB.setSize(1);
		rectB.moveTo(p);
		
		return CollisionDetection::detectBoundingBoxCollision(rectA, rectB);
	}
	
	// per pixel collision based on alpha channel of sprite or collision mask
	else if (mMouseDetectMode == collide_AlphaChannel) {
		// local sprite bounding rect
        RotatedRect rectA = mNumFrames>0 ? getFrameRotatedBounds(mCurrFrame) : getRotatedBounds();
		// argument sprite bounding rect

		RotatedRect rectB;
		rectB.setSize(1);
		rectB.moveTo(p);
		
        if(mNumFrames<=0) return false;
		ImageImpl* imageA = mFrames[mCurrFrame].collisionMask;
		if (imageA == 0) {
			imageA = mFrames[mCurrFrame].image;
		}
        if(!imageA) return false;
        imageA->requireSnapshotPixels();
		Rect imageBoundsA = imageA->getImageBounds();
		imageBoundsA.moveRight(mFrames[mCurrFrame].imageFrameNum * imageA->frameWidth);
		Rect imageBoundsB(p, 1, 1);
		return CollisionDetection::detectPixelCollision(rectA, rectB, imageA, 0, imageBoundsA, imageBoundsB);
	}

  #ifdef PDG_SPRITER_SUPPORT
	// Spriter collision box collision detection
	else if (mMouseDetectMode == collide_SpriterCollisionBox) {
		return checkSpriterCollisionBoxPointCollision(p);
	}
  #endif // PDG_SPRITER_SUPPORT
	
	return false;
}

	


	
void	Sprite::draw() {
#ifndef PDG_NO_GUI
	bool shouldDraw = true;
	if (mDrawHelper) {
		shouldDraw = mDrawHelper->draw(this, mPort);
	}

  #ifdef PDG_SPRITER_SUPPORT
  	if (mEntityInstance) {
		if (mEntityInstance->getAlpha() != mOpacity) invalidateSpriterPose();
		refreshSpriterPose();
        PDGImageFile::LayerScope imageLayer(mLayer);
        if(shouldDraw && mAnimationPoseAdapter && !mAnimationDrawings.empty() && !mDrawHelper && !mPostDrawHelper && mParts.empty() && mLayer && mLayer->getSpritePort()){
            const auto bounds=getAnimationDrawBounds();
            if(!bounds.uncullable)shouldDraw=mLayer->getSpritePort()->getDrawingArea().overlaps(mLayer->layerToPort(Rect(bounds.left,bounds.top,bounds.right,bounds.bottom)).getBounds());
        }
        if (shouldDraw) {
            if (mAnimationPoseAdapter) {
                // Spriter settings are global. Supported pose sprites suppress
                // those debug renderers and use per-instance final-pose drawing.
                struct RestoreDebug {
                    bool bones, points, boxes;
                    ~RestoreDebug() {
                        SpriterEngine::Settings::renderDebugBones = bones;
                        SpriterEngine::Settings::renderDebugPoints = points;
                        SpriterEngine::Settings::renderDebugBoxes = boxes;
                    }
                } restore{SpriterEngine::Settings::renderDebugBones,
                    SpriterEngine::Settings::renderDebugPoints, SpriterEngine::Settings::renderDebugBoxes};
                SpriterEngine::Settings::renderDebugBones = false;
                SpriterEngine::Settings::renderDebugPoints = false;
                SpriterEngine::Settings::renderDebugBoxes = false;
                drawAnimationArt();
                drawAnimationDebug();
            } else mEntityInstance->render();
        }
	} else
  #endif
	if (shouldDraw && mNumFrames > 0) {
        ImageImpl* image = mFrames[mCurrFrame].image;
        if (image == 0) return;
        int opacitySave = image->getOpacity();
        if (mOpacity < 1.0) { 
            image->setOpacity((uint8)((float)255 * mOpacity));
        }
        Port* oldPort = image->setPort(mPort);

        Point p = mLocation - mFrames[mCurrFrame].center;
        Quad q(image->getImageBounds(p));
        const Point pivot = mLocation + Offset(mFrames[mCurrFrame].centerOffsetX, mFrames[mCurrFrame].centerOffsetY);
        const float c = std::cos(mFacing), s = std::sin(mFacing);
        for (Point& point : q.points) {
            const float x = (point.x - mLocation.x) * mScaleX * (mFlipX ? -1 : 1) - (pivot.x - mLocation.x);
            const float y = (point.y - mLocation.y) * mScaleY * (mFlipY ? -1 : 1) - (pivot.y - mLocation.y);
            point = pivot + Offset(c*x-s*y, s*x+c*y);
        }
        Quad pr = mLayer->layerToPort(q);
       
        if (image->frames > 1) {
            image->drawFrame(pr, mFrames[mCurrFrame].imageFrameNum );
        } else {
            mPort->drawImage(image, pr, Attributes());
        }
        image->setOpacity(opacitySave);
        image->setPort(oldPort);
      #ifdef SPRITE_INTERNAL_DEBUG
        mPort->frameRect(pr.getBounds(), Color(1.0f, 0.0f, 1.0f, 0.5f));
      #endif
    }
    if (shouldDraw) for (auto* part : mParts) part->drawContent();
    if (mPostDrawHelper) {
    	mPostDrawHelper->draw(this, mPort);
    }

  #ifdef SPRITE_DEBUG_COLLISIONS
    if(collider!=Collider::NoCollider) mPort->frameRect(mLayer->layerToPort(collider.getBounds()),PDG_RED_COLOR);
  #endif
  #ifdef SPRITE_MOTION_DEBUG
	Point a = mLocation - mCenterOffset;
    Vector delta(mDeltaXPerMs * 1000.0f, mDeltaYPerMs * 1000.0f);
    Point b = a + mLayer->layerToPort(delta);
	mPort->drawLine(a, b, Color(1.0f,0.0f,0.0f,0.5f));
  #endif
  #endif //!PDG_NO_GUI
}


void Sprite::animationStarting(Animation& a) {
    // A queued fade-in must leave the preceding fade untouched until it starts.
    if (a.value == &mOpacity && a.completion == 2 && mOpacity == 1) mOpacity = 0;
}

void Sprite::easingCompleted(const Animation& a) {
    if (a.value == &mOpacity) {
        const int action = a.completion ? action_FadeComplete + a.completion - 1 : mFadeCompleteAction;
        if (action && mLayer) mLayer->notifyAnimationAction(action, this);
        if (a.operation == mAnimationOperation || !a.completion) mFadeCompleteAction = 0;
    }
}


void
Sprite::doAnimate(ms_delta msElapsed, bool layerDoCollisions) {
    const bool retained = refs > 0;
    if (retained) addRef();
    struct Release { Sprite* sprite; ~Release() { if (sprite) sprite->release(); } } release{retained ? this : nullptr};
    if (mAnimationPrepared) mAnimationPrepared = false;
    else advanceAnimation(msElapsed);
    finishAnimation(msElapsed, layerDoCollisions);
}

void Sprite::advanceAnimation(ms_delta msElapsed) {
    
  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (USE_CHIPMUNK && !cpBodyIsSleeping(mBody)) {
        cpVect v = cpBodyGetPosition(mBody);
        cpFloat angle = cpBodyGetAngle(mBody);
        mLocation.x = v.x - mCenterOffset.x;
        mLocation.y = v.y - mCenterOffset.y;
        mFacing = angle;
    }
    Point saveLoc = mLocation;
    Offset saveOffset = mCenterOffset;
  #endif

    // do all the primary animation
  	SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] animate @ %ld", this, msElapsed); )
    AnimatedBase::animate(static_cast<double>(msElapsed) / 1000.0);
    if (physics != PhysicsBody::NoPhysics && physics.getSolver()==physicsSolver_Basic) {
        physics.step(static_cast<double>(msElapsed)/1000.0);
    }

	// select the appropriate frame of the animation
	float elapsed = (float)msElapsed / 1000.0;


  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (USE_CHIPMUNK && (mLocation != saveLoc || mCenterOffset != saveOffset)) {
  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] fixing chipmunk pos", this); )
        // animate() call changed the location or center offset, so update the physics engine
        cpVect v;
        v.x = mLocation.x + mCenterOffset.x; v.y = mLocation.y + mCenterOffset.y;
        cpBodySetPosition(mBody, v);
        cpSpaceReindexShapesForBody(getSpace(), mBody);
        // TODO: do something other than cpSpaceReindexShapesForBody for static sprites;

    }
  #endif

  #ifdef PDG_SPRITER_SUPPORT
  	if (mEntityInstance) {
  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] doing SpriterPlusPlus animation", this); )
		dispatchSpriterTriggers(static_cast<double>(msElapsed)/1000.0);
		syncSpriterRoot();
		if (mIsBlending && !mIsAnimationPaused) resumeSpriterBlend();
		if (mIsAnimationPaused && mIsBlending) {
			// The evaluator's paused update reprocesses only the source clip.
			// Rebuild the same blended pose so root changes still propagate.
			mEntityInstance->blend(mBlendProgress, mEntityInstance->getTimeRatio());
		} else {
			mEntityInstance->setTimeElapsed(static_cast<double>(msElapsed));
		}

		if (mIsBlending && !mIsAnimationPaused) {
			mBlendElapsedMs += msElapsed;
			mBlendProgress = mBlendDurationMs > 0.0
				? static_cast<float>(std::min(1.0, mBlendElapsedMs / mBlendDurationMs)) : 1.0f;
			if (mBlendElapsedMs >= mBlendDurationMs) {
				mIsBlending = false;
				// A source ending on this step must not leave the destination paused.
				if (!mEntityInstance->animationJustFinished() || mEntityInstance->getTimeRatio() < 1.0) {
					resumeSpriterBlend();
				}
				if (mLayer) mLayer->notifyAnimationAction(action_AnimationBlendComplete, this);
			}
		}

		if (!mIsBlending && !mIsAnimationPaused && mEntityInstance->animationJustFinished()
			&& mEntityInstance->getTimeRatio() >= 1.0) mIsAnimationFinished = true;
        const bool wasTransitioning=isAnimationTransitioning();
		publishSpriterPose(mIsAnimationPaused ? 0.0 : static_cast<double>(msElapsed) / 1000.0);
        if(isAnimationTransitioning())mIsAnimationFinished=false;
        else if(wasTransitioning && mAnimationPoseAdapter) {
            mIsAnimationFinished=mEntityInstance->getTimeRatio()>=1;
            if(mLayer)mLayer->notifyAnimationAction(action_AnimationBlendComplete,this);
        }
		mSpriterPoseDirty = false;
		updateAttachedSprites();

  		// Invalidate collision bounds each frame since animation may change them
  		mColliderBoundsValid = false;
  		mSpriterCollisionBoxCacheValid = false;

  	}
  #endif

	if (mSpriteAnimating) {
  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] doing frame animation", this); )
		if (!mSpriteAnimatingBackwardsNow) {
			// animating foward
			mCurrFramePrecise += (elapsed * mFps);
			mCurrFrame = mCurrFramePrecise;
			if ( mCurrFrame >= mLastFrame ) {	 
				if (!mLoopAnim && (!mBidirectionalAnim || mBackToFrontAnim)) {
					mCurrFramePrecise = mLastFrame;
					if (wantsAnimEnd) {
						mLayer->notifyAnimationAction(action_AnimationEnd, this);
					}
				} else {
					float excess = mCurrFramePrecise - (float)mLastFrame;
					if (mBidirectionalAnim) {
						mCurrFramePrecise = (float)mLastFrame - excess;
						mSpriteAnimatingBackwardsNow = true; // reverse direction
					} else {
						mCurrFramePrecise = (float)mFirstFrame + excess;
					}
					if (wantsAnimLoop) {
						mLayer->notifyAnimationAction(action_AnimationLoop, this);
					}
				}
				mCurrFrame = mCurrFramePrecise;
			}
		} else {
			// animating backwards
			mCurrFramePrecise -= (elapsed * mFps);
			mCurrFrame = mCurrFramePrecise;
			if ( mCurrFrame < mFirstFrame ) {
				if (!mLoopAnim && (!mBidirectionalAnim || !mBackToFrontAnim)) {
					mCurrFramePrecise = mFirstFrame;
					if (wantsAnimEnd) {
						mLayer->notifyAnimationAction(action_AnimationEnd, this);
					}
				} else {
					float excess = (float)mFirstFrame - mCurrFramePrecise;
					if (mBidirectionalAnim) {
						mCurrFramePrecise = (float)mFirstFrame + excess;
						mSpriteAnimatingBackwardsNow = false; // reverse direction
					} else {
						mCurrFramePrecise = (float)mLastFrame - excess;
					}
					if (wantsAnimLoop) {
						mLayer->notifyAnimationAction(action_AnimationLoop, this);
					}
				}
				mCurrFrame = mCurrFramePrecise;
			}
		}
		// final anim bounds check
		if (mCurrFrame < mFirstFrame) {
			mCurrFrame = mFirstFrame;
			mCurrFramePrecise = mFirstFrame;
		} else if (mCurrFrame > mLastFrame) {
			mCurrFrame = mLastFrame;
			mCurrFramePrecise = mLastFrame;
		}
		DEBUG_ASSERT((mCurrFrame >= 0) && (mCurrFrame < MAX_FRAMES_PER_SPRITE), "invalid frame number in Sprite::animate()");
		if (mCurrFrame < 0) {
			mCurrFrame = 0;
			mCurrFramePrecise = mFirstFrame;
		}
		if (mCurrFrame >= MAX_FRAMES_PER_SPRITE) {
			mCurrFrame = MAX_FRAMES_PER_SPRITE - 1;
			mCurrFramePrecise = mLastFrame;
		}
	}

    // Parts consume this tick's final authored pose, then publish parent before child.
    animateParts(static_cast<double>(msElapsed) / 1000.0);

}

void Sprite::publishBodyBreak(Part* part, const PhysicsBodyBreakInfo& info) {
    // Native callers may use a stack Sprite (refs == 0). Retain managed owners
    // and Parts so removing them from inside the callback is safe.
    const bool retained = refs > 0;
    if (retained) addRef();
    if (part) part->addRef();
    struct Release {
        Sprite* sprite; Part* part;
        ~Release() { if (part) part->release(); if (sprite) sprite->release(); }
    } release{retained ? this : nullptr, part};
    SpriteJointBreakInfo event{};
    event.action = action_BodyBreak; event.actingSprite = this; event.inLayer = mLayer;
    event.reason = physicsBreak_AngularSpeed; event.body = info.body; event.part = part;
    event.referenceBody = info.referenceBody; event.angularSpeed = info.angularSpeed;
    event.breakAngularSpeed = info.breakAngularSpeed;
    postEvent(eventType_SpriteBreak, &event);
}

void Sprite::finishAnimation(ms_delta /*msElapsed*/, bool /*layerDoCollisions*/) {
	bool dead = false;

  #ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mNumBreakableJoints > 0) {
  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] checking joints", this); )
        addRef();
        for (int i = 0; i < mNumBreakableJoints; i++) {
            cpFloat impulse = cpConstraintGetImpulse(mBreakableJoints[i]);
            const cpFloat solvedSeconds=cpSpaceGetCurrentTimeStep(getSpace());
            cpFloat force = solvedSeconds>0?impulse/solvedSeconds:0;
            cpFloat maxForce = cpConstraintGetMaxForce(mBreakableJoints[i]);
            cpFloat breakingForce = BREAK_COEFFICIENT * maxForce;
            // If the force is almost as big as the joint's max force, break it.
            if (force > breakingForce) {
                cpBody* b = cpConstraintGetBodyB(mBreakableJoints[i]);
                Sprite* otherSprite = (Sprite*) cpBodyGetUserData(b);
                SpriteJointBreakInfo si{};
                si.action = action_JointBreak;
                si.actingSprite = this;
                si.targetSprite = otherSprite;
                si.impulse = impulse;
                si.force = force;
                si.breakForce = breakingForce;
                si.joint = mBreakableJoints[i];   // the joint that broke
                si.inLayer = this->mLayer;
                if (postEvent(eventType_SpriteBreak, &si) == false) {
                    // "unhandled" means go ahead and break it
                    disconnect(otherSprite);
                }
            }
        }
		if (refs == 1) dead = true;
		release();
		if (dead) return;
    }
  #endif  // PDG_USE_CHIPMUNK_PHYSICS
  	if (wantsWallCollide || wantsOffscreen) {
  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] checking layer bounds", this); )
  	  #ifndef PDG_NO_GUI
  		bool oldOnscreen = mOnscreen;
	  #endif // !PDG_NO_GUI
  		bool oldInBounds = mInBounds;
  		bool oldCompletelyInBounds = mCompletelyInBounds;
  		recalcOnscreenAndInBounds();
  	  #ifndef PDG_NO_GUI
		if (wantsOffscreen && mPort) {
			uint16 action = 0;
			if (oldOnscreen && !mOnscreen) {
				action = action_Offscreen;
			} else if (!oldOnscreen && mOnscreen) {
				action = action_Onscreen;
			}
			if (action) {
				addRef();
				mLayer->notifyAnimationAction(action, this);
				if (refs == 1) dead = true;
				release();
				if (dead) return;
			} 
		}
	  #endif // !PDG_NO_GUI
		if (wantsWallCollide) {
//  			SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] wall collide %d %d %d %d", this, oldInBounds, mInBounds, oldCompletelyInBounds, mCompletelyInBounds); )
			if (oldInBounds && !mInBounds) {
				addRef();
				mLayer->notifyAnimationAction(Sprite::action_ExitLayer, this);
				if (refs == 1) dead = true;
				release();
			} else if (oldCompletelyInBounds && !mCompletelyInBounds) {
				addRef();
				Vector normal = physics.getVelocity().normal();
				// TODO: calculate real values for these things, but don't apply them
				Vector impulse;
				float kineticEnergy = 0;
				float force = impulse.vectorLength(); // / elapsed;  // TODO: not sure why we divide by elapsed, collision force is instantaneous
				EVENTS_DEBUG_ONLY(OS::_DOUT("Sprite::doAnimate calling notifyCollisionAction wall"));
				mLayer->notifyCollisionAction(Sprite::action_CollideWall, this, normal, impulse, force, kineticEnergy, 
						#ifdef PDG_USE_CHIPMUNK_PHYSICS
							0,  // need to pass in something for cpArbiter param
						#endif
						#ifdef PDG_SPRITER_SUPPORT
							nullptr,
							nullptr,
							true,
						#endif // PDG_SPRITER_SUPPORT
							0,
							false // queue up all the collision events for later
						); // no other sprite
				if (refs == 1) dead = true;
				release();
			}
			if (dead) return;
		}
    }

    updatePartAttachments();

}

bool 
Sprite::postEvent(long inEventType, void* inEventData, EventEmitter* fromEmitter) {
	// simplier version just tries to emit the event locally and cleanup afterwards if not
	if (fromEmitter == 0) {
		fromEmitter = this;
	}
	EVENTS_DEBUG_ONLY(
		if (inEventType == eventType_SpriteCollide) {
			SpriteCollideInfo* si = static_cast<SpriteCollideInfo*>(inEventData);
			OS::_DOUT("Sprite::postEvent sending unhandled collision event id: %d to layer", si->id);
		}
	)
	bool wasHandled = emitEvent(fromEmitter, inEventType, inEventData);
	EVENTS_DEBUG_ONLY(
	if (inEventType == eventType_SpriteCollide) {
		SpriteCollideInfo* si = static_cast<SpriteCollideInfo*>(inEventData);
		OS::_DOUT("Sprite::postEvent  id: %d inEventType: %d wasHandled: %d", si->id, inEventType, wasHandled);
		}
	)
	cleanupRemovedHandlers();
	// special case for collision events because we want to give both objects in the
	// collision a chance to respond
	if (inEventType == eventType_SpriteCollide) {
		SpriteCollideInfo* si = static_cast<SpriteCollideInfo*>(inEventData);
		EVENTS_DEBUG_ONLY(OS::_DOUT("Sprite::postEvent id: %d targetSprite: %p this: %p", si->id, si->targetSprite, this));
		if (this == si->targetSprite) {
			// nothing more to do if we are the target sprite
			// we don't want to pass this message on to the layer
			// since the acting sprite will do that
			return wasHandled;
		} else if (si->targetSprite) {
			EVENTS_DEBUG_ONLY(OS::_DOUT("Sprite::postEvent sending unhandled collision event id: %d to target sprite", si->id));
			// not the target sprite, give the target a chance do something
			wasHandled |= si->targetSprite->postEvent(inEventType, inEventData);
		}
	}
	if (!wasHandled) {
		// not handled locally, try the sprite layer, which will pass it on to
		// the event manager if needed
		if (mLayer) {
			EVENTS_DEBUG_ONLY(
				if (inEventType == eventType_SpriteCollide) {
					SpriteCollideInfo* si = static_cast<SpriteCollideInfo*>(inEventData);
					OS::_DOUT("Sprite::postEvent sending unhandled collision event id: %d to layer", si->id);
				}
			)
			wasHandled = mLayer->postEvent(inEventType, inEventData, fromEmitter);
		}
	}
	return wasHandled;
}

void Sprite::locationChanged(const Offset& delta) {
#if defined(PDG_USE_CHIPMUNK_PHYSICS) && defined(PDG_SPRITER_SUPPORT)
    if(mAnimationPhysics && !mPublishingPhysics)mAnimationPhysics->frameChanged(spriterRootTransform());
#endif
    if (physics != PhysicsBody::NoPhysics && !mPublishingPhysics)
        physics->setOwnerTransform(mLocation + mCenterOffset, mFacing);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (USE_CHIPMUNK && !mAnimating && !mPublishingPhysics) {
        cpBodySetPosition(mBody, cpv(mLocation.x + mCenterOffset.x, mLocation.y + mCenterOffset.y));
        if (mStatic) cpSpaceReindexStatic(getSpace());
        else cpSpaceReindexShapesForBody(getSpace(), mBody);
    }
#endif
#ifdef PDG_SPRITER_SUPPORT
    invalidateSpriterPose();
#endif
    refreshPartPhysics();
    updatePartAttachments();
}

void Sprite::sizeChanged(float deltaW, float deltaH) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (USE_CHIPMUNK) {
    }
#endif
#ifdef PDG_SPRITER_SUPPORT
    if (mWidth - deltaW != 0) mEntityScaleX *= mWidth / (mWidth - deltaW);
    if (mHeight - deltaH != 0) mEntityScaleY *= mHeight / (mHeight - deltaH);
    invalidateSpriterPose();
#endif
}

void Sprite::scaleChanged(const Offset&) {
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#endif
#ifdef PDG_SPRITER_SUPPORT
    invalidateSpriterPose();
#endif
    refreshPartPhysics();
    updatePartAttachments();
}

void Sprite::rotationChanged(float deltaRadians) {
#if defined(PDG_USE_CHIPMUNK_PHYSICS) && defined(PDG_SPRITER_SUPPORT)
    if(mAnimationPhysics && !mPublishingPhysics)mAnimationPhysics->frameChanged(spriterRootTransform());
#endif
    if (physics != PhysicsBody::NoPhysics && !mPublishingPhysics)
        physics->setOwnerTransform(mLocation + mCenterOffset, mFacing);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (USE_CHIPMUNK && !mPublishingPhysics) {
        cpBodySetAngle(mBody, mFacing);
        if (mStatic) cpSpaceReindexStatic(getSpace());
        else cpSpaceReindexShapesForBody(getSpace(), mBody);
    }
#endif
#ifdef PDG_SPRITER_SUPPORT
    invalidateSpriterPose();
#endif
    refreshPartPhysics();
    updatePartAttachments();
}

void Sprite::flipChanged(bool xFlipped, bool yFlipped) {
#ifdef PDG_SPRITER_SUPPORT
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mAnimationPhysics) {
        if(AnimationPipeline::isInsideCallback())throw std::logic_error("Flip physical rigs outside pose callbacks");
        mAnimationPhysics->reflect(spriterRootTransform(),xFlipped,yFlipped,physics->mAssemblyBodies);
    }
#endif
    if (xFlipped) mEntityScaleX = -mEntityScaleX;
    if (yFlipped) mEntityScaleY = -mEntityScaleY;
    invalidateSpriterPose();
#endif
    refreshPartPhysics();
    updatePartAttachments();
}

    void	
    Sprite::centerChanged(const Offset& delta) {
        if (physics != PhysicsBody::NoPhysics && !mPublishingPhysics)
            physics->setOwnerTransform(mLocation + mCenterOffset, mFacing);
    }

#ifdef PDG_USE_CHIPMUNK_PHYSICS
namespace {
class SpriteBodySolver final : public PhysicsBody::Solver {
    Sprite& sprite;
public:
    explicit SpriteBodySolver(Sprite& owner) : sprite(owner) {}
    void* nativeBody() const override { return sprite.mBody; }
    PhysicsBodyState readState() const override {
        const auto p=cpBodyGetPosition(sprite.mBody),v=cpBodyGetVelocity(sprite.mBody);
        return {p.x,p.y,cpBodyGetAngle(sprite.mBody),v.x,v.y,cpBodyGetAngularVelocity(sprite.mBody)};
    }
    void writeState(const PhysicsBodyState& state) override {
        const auto before = readState();
        const bool moved = before.x != state.x || before.y != state.y;
        const bool rotated = before.rotation != state.rotation;
        if (moved) cpBodySetPosition(sprite.mBody, cpv(state.x, state.y));
        if (rotated) cpBodySetAngle(sprite.mBody, state.rotation);
        if (cpBodyGetType(sprite.mBody) != CP_BODY_TYPE_STATIC) {
            if (before.velocityX != state.velocityX || before.velocityY != state.velocityY)
                cpBodySetVelocity(sprite.mBody, cpv(state.velocityX, state.velocityY));
            if (before.angularVelocity != state.angularVelocity)
                cpBodySetAngularVelocity(sprite.mBody, state.angularVelocity);
        }
        // Unchanged bodies must remain eligible for Chipmunk sleeping.
        if (moved || rotated) {
            if (auto* space = cpBodyGetSpace(sprite.mBody))
                if (!cpSpaceIsLocked(space)) cpSpaceReindexShapesForBody(space, sprite.mBody);
        }
    }
    void addForce(double x, double y, double torque) override {
        if (x != 0 || y != 0) cpBodySetForce(sprite.mBody, cpvadd(cpBodyGetForce(sprite.mBody), cpv(x, y)));
        if (torque != 0) cpBodySetTorque(sprite.mBody, cpBodyGetTorque(sprite.mBody)+torque);
    }
    void configure(const PhysicsBody& body) override {
        const auto type=body.getMode()==physicsBody_Static?CP_BODY_TYPE_STATIC:
            body.getMode()==physicsBody_Kinematic?CP_BODY_TYPE_KINEMATIC:CP_BODY_TYPE_DYNAMIC;
        if(cpBodyGetType(sprite.mBody)!=type) {
            auto* space=cpBodyGetSpace(sprite.mBody);
            if(space && cpSpaceIsLocked(space)) throw std::logic_error("Change body mode outside collision callbacks");
            cpBodySetType(sprite.mBody,type);
        }
        sprite.mStatic=(type==CP_BODY_TYPE_STATIC);
        if(type==CP_BODY_TYPE_DYNAMIC) {
            cpBodySetMass(sprite.mBody,body.getMass());
            cpBodySetMoment(sprite.mBody,body.getMomentOfInertia());
        }
        if(sprite.mCollideShape) {
            cpShapeSetFriction(sprite.mCollideShape,body.getFriction());
            cpShapeSetElasticity(sprite.mCollideShape,body.getRestitution());
        }
    }
};
}
#endif

#ifdef PDG_USE_CHIPMUNK_PHYSICS
    void
    Sprite::setupCollideGroup(Sprite* otherSprite) {
    	if (!USE_CHIPMUNK) return;
        // try to get a valid collideGroup
        if (!mCollideGroup) mCollideGroup = otherSprite->mCollideGroup; // maybe the other sprite has it set?
        if (!mCollideGroup) mCollideGroup = spriteId;               // grab a possibly usable value
        if (!mCollideGroup) mCollideGroup = otherSprite->spriteId;
        if (!mCollideGroup) mCollideGroup = iid;  // this should always be set
        DEBUG_ONLY(
            if (mCollideShape && otherSprite->mCollideShape) {
                DEBUG_ASSERT(mCollideGroup != 0, "Must have a collideGroup (or spriteId) assigned to use joints with collisions enabled!!");
            }
        )
        if (mCollideGroup) {
            otherSprite->mCollideGroup = mCollideGroup; // make sure both sprites agree on the collide group
            cpShapeFilter filter = cpShapeFilterNew(mCollideGroup, CP_ALL_CATEGORIES, CP_ALL_CATEGORIES);
            if (mCollideShape) {
                cpShapeSetFilter(mCollideShape, filter);
            }
            if (otherSprite->mCollideShape) {
                cpShapeSetFilter(otherSprite->mCollideShape, filter); // use our spriteId
            }
        }
    }

    void
    Sprite::makeJointBreakable(cpConstraint* joint, float breakingForce, Sound* breakSound) {
    	if (!USE_CHIPMUNK) return;
        DEBUG_ASSERT(breakingForce > 0, "Breaking Force must be > 0");
        DEBUG_ASSERT(mNumBreakableJoints < MAX_BREAKABLE_JOINTS_PER_SPRITE, "Too many breakable joints!!");
        if ((breakingForce > 0) && (mNumBreakableJoints < MAX_BREAKABLE_JOINTS_PER_SPRITE)) {
            cpConstraintSetMaxForce(joint, breakingForce / BREAK_COEFFICIENT);
            mBreakableJoints[mNumBreakableJoints] = joint;
            mNumBreakableJoints++;
        }
    }

    void
    Sprite::makeJointUnbreakable(cpConstraint* joint) {
    	if (!USE_CHIPMUNK) return;
        bool found = false;
        for (int i = 0; i < mNumBreakableJoints; i++) {
            // remove from the breakable joints array
            if (mBreakableJoints[i] == joint) {
                found = true;
                mNumBreakableJoints--;
            }
            if (found && (i < mNumBreakableJoints-1) ) {
                mBreakableJoints[i] = mBreakableJoints[i+1];
            }
        }
    }

    // pin sprites together, at a particular anchor point (offset from center) on each
    cpConstraint*            
    Sprite::pinJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpPinJointNew(mBody, otherSprite->mBody, 
                                          cpv(anchor.x, anchor.y), cpv(otherAnchor.x, otherAnchor.y));
        cpPinJointSetDist(con, 0);  // no distance between anchor points
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // join sprites together via a slider between anchor points that has a min/max distance
    cpConstraint*            
    Sprite::slideJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float minDist, float maxDist, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpSlideJointNew(mBody, otherSprite->mBody, 
                                            cpv(anchor.x, anchor.y), cpv(otherAnchor.x, otherAnchor.y), 
                                            minDist, maxDist);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // join sprites together at a particular location in layer coordinates
    cpConstraint*            
    Sprite::pivotJoint(Sprite* otherSprite, Point pivot, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpPivotJointNew(mBody, otherSprite->mBody, cpv(pivot.x, pivot.y));
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
//        cpFloat errorBias = pow(1.0 - 0.25, 60.0);  // 25% correction every 1/60th of a second
//        cpConstraintSetErrorBias(con, errorBias);
        return con;
    }

    // join sprites together via a groove on this sprite to an anchor point on another
    cpConstraint*            
    Sprite::grooveJoint(Offset grooveStart, Offset grooveEnd, Sprite* otherSprite, Offset otherAnchor, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpGrooveJointNew(mBody, otherSprite->mBody, 
                                             cpv(grooveStart.x, grooveStart.y), cpv(grooveEnd.x, grooveEnd.y), 
                                             cpv(otherAnchor.x, otherAnchor.y));    
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // join sprites together via a spring between anchor points
    cpConstraint*            
    Sprite::springJoint(Offset anchor, Sprite* otherSprite, Offset otherAnchor, float restLength, float stiffness, float damping, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpDampedSpringNew(mBody, otherSprite->mBody, 
                                              cpv(anchor.x, anchor.y), cpv(otherAnchor.x, otherAnchor.y), 
                                              restLength, stiffness, damping);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // keep sprites at a particular angle relative to one another via a rotary spring
    cpConstraint*            
    Sprite::rotarySpring(Sprite* otherSprite, float restAngle, float stiffness, float damping, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpDampedRotarySpringNew(mBody, otherSprite->mBody, restAngle, stiffness, damping);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // limit the angle another sprite can have relative to this one
    cpConstraint*            
    Sprite::rotaryLimit(Sprite* otherSprite, float minAngle, float maxAngle, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpRotaryLimitJointNew(mBody, otherSprite->mBody, minAngle, maxAngle);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // like a socket wrench. ratchetInterval is the distance between "clicks", phase is the initial 
    // angular offset to use when deciding where the ratchet angles are.
    cpConstraint*            
    Sprite::ratchet(Sprite* otherSprite, float rachetInterval, float phase, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpRatchetJointNew(mBody, otherSprite->mBody, phase, rachetInterval);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // keep another sprite's rotation relative to this one at a particular gear ratio
    cpConstraint*            
    Sprite::gear(Sprite* otherSprite, float gearRatio, float initialAngle, float breakingForce) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpGearJointNew(mBody, otherSprite->mBody, initialAngle, gearRatio);
        cpSpaceAddConstraint(getSpace(), con);
        if (breakingForce > 0) {
            makeJointBreakable(con, breakingForce);
        }
        return con;
    }

    // keep spin of another sprite at a constant rate compared to this one
    cpConstraint*            
    Sprite::motor(Sprite* otherSprite, float spin, float maxTorque) {
    	if (!USE_CHIPMUNK) return 0;
        setupCollideGroup(otherSprite);
        cpConstraint* con = cpSimpleMotorNew(mBody, otherSprite->mBody, spin);
        if (maxTorque != std::numeric_limits<float>::infinity()) {
            cpConstraintSetMaxForce(con, maxTorque);
        }
        cpSpaceAddConstraint(getSpace(), con);
        return con;
    }
    
    static void RemoveConstraint(cpBody* body, cpConstraint* constraint, void* data);
    static void RemoveConstraint(cpBody* body, cpConstraint* constraint, void* data) {
        cpBody* a = cpConstraintGetBodyA(constraint);
        cpBody* b = cpConstraintGetBodyB(constraint);
        if (data && (b != ((Sprite*)data)->mBody)) {
            return;
        }
        Sprite* sprite = (Sprite*)cpBodyGetUserData(a);
        sprite->removeJoint(constraint);
    }
    
    void 
    Sprite::removeJoint(cpConstraint* joint) {
    	if (!USE_CHIPMUNK) return;
        makeJointUnbreakable(joint);
        cpSpaceRemoveConstraint(cpConstraintGetSpace(joint), joint);
        cpConstraintFree(joint);
    }
    
    // remove all connections, or if otherSprite != 0 remove all connections to other sprites
    void            
    Sprite::disconnect(Sprite* otherSprite) {
    	if (!USE_CHIPMUNK) return;
        if (!otherSprite) {
            mNumBreakableJoints = 0; // this saves us having to do a lot of manipulation of the mBreakableJoints array
        }
        cpBodyEachConstraint(mBody, RemoveConstraint, otherSprite);
    }


    cpSpace*
    Sprite::getSpace() {
    	if (!USE_CHIPMUNK) return 0;
        cpSpace* space = cpBodyGetSpace(mBody);
        if (!space) {
            space = mLayer->getSpace();
        }
        return space;
    }

    void
    Sprite::initCpBody() {
        if (!(physics != PhysicsBody::NoPhysics)) return;
    	if (!mBody) {
    		if (!mLayer->mIsStaticLayer) {
				mBody = cpBodyNew(1, 1);
			} else {
				mBody = cpBodyNewStatic(); // initialize as a static
				mStatic = true;		
			}
            cpSpaceAddBody(getSpace(), mBody);
			cpBodySetUserData(mBody, this);
            SpriteManager::registerBody(mBody,this);
            if(mLayer->mIsStaticLayer) physics.setMode(physicsBody_Static);
            physics->attachSolver(std::make_unique<SpriteBodySolver>(*this));
		}
    }
    
    void
    Sprite::freeCpBody() {
        collider->syncNative(nullptr);
        if (physics != PhysicsBody::NoPhysics) physics->detachSolver();
		if (mCollideShape) {
			cpSpaceRemoveShape(getSpace(), mCollideShape);
			cpShapeFree(mCollideShape);
		}
		if (mBody) {
			cpSpaceRemoveBody(getSpace(), mBody);
			SpriteManager::registerBody(mBody,nullptr);
            cpBodyFree(mBody);
    	}
		mCollideShape = 0;
		mBody = 0;
    }


#endif // PDG_USE_CHIPMUNK_PHYSICS

void
Sprite::recalcOnscreenAndInBounds() {
	RotatedRect srb = getRotatedBounds();
//  	SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("Sprite [%p] recalc inbounds [%0.2f,%0.2f,%0.2f,%0.2f r %0.2f]", this, srb.left, srb.top, srb.right, srb.bottom, srb.radians); )
  #ifndef PDG_NO_GUI
	if (wantsOffscreen && mPort) {
		Rect portBounds = mPort->getDrawingArea();
		Rect portSb = mLayer->layerToPort(srb).getBounds();
		mOnscreen = portSb.overlaps(portBounds);
	}
  #endif
	if (wantsWallCollide) {
		Rect lb = mLayer->getRotatedBounds();
		Rect sb = srb.getBounds();
//  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("  lb [%0.2f,%0.2f,%0.2f,%0.2f] sb [%0.2f,%0.2f,%0.2f,%0.2f]", lb.left, lb.top, lb.right, lb.bottom, sb.left, sb.top, sb.right, sb.bottom ); )
		mInBounds = lb.overlaps(sb);
		mCompletelyInBounds = lb.contains(sb);
//  		SPRITEANIMATE_DEBUG_ONLY( OS::_DOUT("  ib: %d  cib: %d", mInBounds, mCompletelyInBounds ); )
	}
}

#ifdef PDG_SPRITER_SUPPORT
Sprite::Sprite(SpriterEngine::EntityInstance* entity, const std::shared_ptr<SpriterEngine::SpriterModel>& model)
    : Sprite(entity, model.get()) {
    mSpriterModelOwner = model;
}
Sprite::Sprite() : Sprite(nullptr, nullptr) {
}
Sprite::Sprite(SpriterEngine::EntityInstance* entityInstance, SpriterEngine::SpriterModel* spriterModel) : 
#else
Sprite::Sprite() : 
#endif // PDG_SPRITER_SUPPORT
    spriteId(0), 
    wantsMouseOver(false), 
    wantsClicks(false), 
    wantsAnimLoop(false), 
    wantsAnimEnd(false), 
	wantsOffscreen(false),
	wantsWallCollide(false),
    userData(0),	
    mNumFrames(0), 
	mFps(1.0),
	mCurrFramePrecise(0),
	mCurrFrame(0),
	mFirstFrame(0),
	mLastFrame(0),
	mLoopAnim(false),
	mBackToFrontAnim(false),
	mBidirectionalAnim(false),
	mSpriteAnimating(false),
	mSpriteAnimatingBackwardsNow(false),
	mMouseDetectMode(collide_BoundingBox),
  #ifdef PDG_SPRITER_SUPPORT
    mEntityInstance(entityInstance),
	mSpriterModel(spriterModel),
	mEntityScaleX(1.0f),
	mEntityScaleY(1.0f),
	mSpriterEventsEnabled(false),
	mIsBlending(false),
	mBlendDurationMs(0.0),
	mBlendElapsedMs(0.0),
	mBlendProgress(0.0f),
	mIsAnimationPaused(false),
	mIsAnimationFinished(false),
	mSpriterCollisionBoxCacheValid(false),
	mColliderBoundsValid(false),
	mSpriterPoseDirty(true),
  #endif
  #ifndef PDG_NO_GUI
	mPort(0),
  #endif
	mLayer(0), 
	mNextSprite(0),
	mPrevSprite(0),
	mOpacity(1.0),
	mFadeCompleteAction(0),
  #ifndef PDG_NO_GUI
	mDrawHelper(0),
	mPostDrawHelper(0),
  #endif
  	mOnscreen(true),
  	mInBounds(true),
  	mCompletelyInBounds(true),
	iid(sUniqueSpriteId++)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSpriteScriptObj);
#endif
	mLocation = PointT<float>(0.0, 0.0);
#ifdef PDG_SPRITER_SUPPORT
	cacheSpriterAnimationNames();
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
	mBody = 0;
    mHeight = 1;    // make sure we've got some height and width
    mWidth = 1;
    mCollideShape = 0; // only create this when we set collisions
    mNumBreakableJoints = 0;
    mStatic = false;
#endif
//	mBounds = Rect(20, 20);
//	DEBUG_PRINT("Constructed Sprite [%p]", this);
}

//Sprite::Sprite(const Sprite* sprite) : mLayer(0) {
//	TODO("Copy over state from sprite");
//	DEBUG_PRINT("ERROR! Copy constructed Sprite [%p]", this);
//	DEBUG_BREAK("Unimplemented call!");
//}
//
// PhysicsBody owns physical state. Sprites and Parts only associate a body and
// publish its result into their transform.
PhysicsBody& Sprite::setupPhysicsBody(double mass, double inertia) {
    if (physics != PhysicsBody::NoPhysics) {
        physics->configureMass(mass, inertia);
        return physics;
    }
    auto body = std::make_unique<PhysicsBody>(mass, inertia);
    body->setRestitution(1); // Sprite default; the body owns restitution
    initializePhysicsBody(*body);
    return *body.release();
}
void Sprite::initializePhysicsBody(PhysicsBody& body) {
    if (mAttachmentPart) throw std::logic_error("Detach the Sprite mounting Part before creating a body");
    if (physics == body) return;
    if (body == PhysicsBody::NoPhysics) { removePhysicsBody(); return; }
    if (body.isAttached() || body.getSolver() != physicsSolver_Basic)
        throw std::logic_error("Assign a detached physics body; remove it from its previous owner first");
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if (mLayer && mLayer->mUseChipmunkPhysics && cpSpaceIsLocked(mLayer->getSpace()))
        throw std::logic_error("Assign physics bodies outside collision callbacks");
#endif
    std::function<void(const PhysicsBodyState&)> publish = [this](const PhysicsBodyState& state) {
        if (physics.getMode() == physicsBody_Dynamic) cancelProgrammedMotion();
        const auto oldLocation=mLocation;const float oldFacing=mFacing;
        mLocation=Point(state.x-mCenterOffset.x,state.y-mCenterOffset.y);mFacing=state.rotation;
        mPublishingPhysics=true;
        struct Reset { bool& value; ~Reset() { value=false; } } reset{mPublishingPhysics};
        if (mLocation != oldLocation) locationChanged(mLocation-oldLocation);
        if (mFacing != oldFacing) rotationChanged(mFacing-oldFacing);
    };
    removePhysicsBody();
    cancelProgrammedMotion();
    body.teleport(mLocation+mCenterOffset,mFacing);
    body.setOwnerPolicy([this](int mode) {
#ifdef PDG_SPRITER_SUPPORT
        if (isAnimationPhysicsEnabled() && mode != physicsBody_Kinematic)
            throw std::logic_error("The coordinating Sprite body must remain kinematic while a physical rig is active");
#endif
        if (mAttachmentPart && mode != physicsBody_Kinematic)
            throw std::logic_error("Detach the mounted Sprite before changing its body from kinematic mode");
    }, [this] { validateTransformEdit(); });
    body.setPublisher(std::move(publish));
    body.setWorldProvider([this] { return mLayer; });
    body.mBreakPublisher = [this](const PhysicsBodyBreakInfo& info) { publishBodyBreak(nullptr, info); };
    body.addRef();physics.mBody=&body;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mLayer && mLayer->mUseChipmunkPhysics) {
        initCpBody();
    }
#endif
}
void Sprite::removePhysicsBody() {
    if(physics == PhysicsBody::NoPhysics) return;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mBody && (getSpace() && cpSpaceIsLocked(getSpace()))) throw std::logic_error("Remove physics bodies outside collision callbacks");
#endif
    collider->syncNative(nullptr);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mBody) {
#ifdef PDG_SPRITER_SUPPORT
        releaseAnimationPhysics();
#endif
        disconnect();freeCpBody();
    }
#endif
    auto* body=physics.mBody;physics.mBody=&PhysicsBody::NoPhysics;
    body->disconnect();body->setPublisher({});body->setOwnerPolicy({},{});body->release();
}
void Sprite::validateTransformEdit() const {
    if (mAttachmentPart) throw std::logic_error("Animate the mounting Part while a Sprite is attached");
}
void Sprite::validateProgrammedTransform() const {
    validateTransformEdit();
    if(physics != PhysicsBody::NoPhysics && physics.getMode()==physicsBody_Dynamic)
        throw std::logic_error("Dynamic motion belongs to PhysicsBody; use physics velocity/forces or change its mode before programming movement/spin");
}

#ifdef PDG_USE_CHIPMUNK_PHYSICS
namespace {
// A Part may participate in the shared solver without a skeleton or root body.
// Collision shape/constraint associations are configured separately.
class PartBodySolver final : public PhysicsBody::Solver {
    cpBody* body;
public:
    PartBodySolver(Sprite* owner, cpSpace* space) : body(cpBodyNew(1,1)) {
        if(cpSpaceIsLocked(space)) {cpBodyFree(body);throw std::logic_error("Create Part bodies outside collision callbacks");}
        cpSpaceAddBody(space,body);cpBodySetUserData(body,owner);SpriteManager::registerBody(body,owner);
    }
    void changeOwner(Sprite* owner) {
        cpBodySetUserData(body,owner);SpriteManager::registerBody(body,owner);
    }
    void* nativeBody() const override { return body; }
    ~PartBodySolver() override {
        SpriteManager::registerBody(body,nullptr);
        auto* space=cpBodyGetSpace(body);
        if(space && cpSpaceIsLocked(space)) {
            cpSpaceAddPostStepCallback(space,[](cpSpace* world,void* key,void*) {
                auto* released=static_cast<cpBody*>(key);cpSpaceRemoveBody(world,released);cpBodyFree(released);
            },body,nullptr);
        } else {if(space)cpSpaceRemoveBody(space,body);cpBodyFree(body);}
    }
    PhysicsBodyState readState() const override {
        const auto p=cpBodyGetPosition(body),v=cpBodyGetVelocity(body);
        return {p.x,p.y,cpBodyGetAngle(body),v.x,v.y,cpBodyGetAngularVelocity(body)};
    }
    void writeState(const PhysicsBodyState& state) override {
        const auto before=readState();
        const bool moved = before.x != state.x || before.y != state.y;
        const bool rotated = before.rotation != state.rotation;
        if(moved)cpBodySetPosition(body,cpv(state.x,state.y));
        if(rotated)cpBodySetAngle(body,state.rotation);
        if(cpBodyGetType(body)!=CP_BODY_TYPE_STATIC) {
            if(before.velocityX!=state.velocityX || before.velocityY!=state.velocityY)cpBodySetVelocity(body,cpv(state.velocityX,state.velocityY));
            if(before.angularVelocity!=state.angularVelocity)cpBodySetAngularVelocity(body,state.angularVelocity);
        }
        // Explicit Part moves must reindex static shapes, as Sprite moves do.
        if (moved || rotated) {
            if (auto* space = cpBodyGetSpace(body))
                if (!cpSpaceIsLocked(space)) cpSpaceReindexShapesForBody(space, body);
        }
    }
    void addForce(double x, double y, double torque) override {
        if (x != 0 || y != 0) cpBodySetForce(body, cpvadd(cpBodyGetForce(body), cpv(x, y)));
        if (torque != 0) cpBodySetTorque(body, cpBodyGetTorque(body)+torque);
    }
    void configure(const PhysicsBody& settings) override {
        const auto type=settings.getMode()==physicsBody_Static?CP_BODY_TYPE_STATIC:
            settings.getMode()==physicsBody_Kinematic?CP_BODY_TYPE_KINEMATIC:CP_BODY_TYPE_DYNAMIC;
        if(cpBodyGetType(body)!=type) {
            if(cpSpaceIsLocked(cpBodyGetSpace(body)))throw std::logic_error("Change Part body mode outside collision callbacks");
            cpBodySetType(body,type);
        }
        if(type==CP_BODY_TYPE_DYNAMIC) {cpBodySetMass(body,settings.getMass());cpBodySetMoment(body,settings.getMomentOfInertia());}
    }
};
}
#endif
void Part::syncPhysicsSolver() {
    if(physics==PhysicsBody::NoPhysics || mAnimationPhysicsBody)return;
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    auto* layer=mSprite?mSprite->mLayer:nullptr;
    if(layer && layer->mUseChipmunkPhysics) {
        if(physics.getSolver()!=physicsSolver_Chipmunk)
            physics->attachSolver(std::make_unique<PartBodySolver>(mSprite,layer->getSpace()));
    } else if(physics.getSolver()==physicsSolver_Chipmunk)physics->detachSolver();
#endif
}

#include "part-artwork-collider.inc"

Collider& Sprite::setupFrameCollider(int mode, int threshold) {
    if(mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask)
        throw std::invalid_argument("Unknown frame collider mode");
    if(threshold<1 || threshold>255) throw std::invalid_argument("Alpha threshold must be from 1 to 255");
    auto provider=[this,mode,threshold,last=std::vector<double>(),lastImage=static_cast<Image*>(nullptr),lastMask=static_cast<Image*>(nullptr)](std::vector<Collider::Shape>& shapes) mutable {
        const bool hasFrame=mNumFrames>0 && mCurrFrame>=0 && mCurrFrame<mNumFrames && mFrames[mCurrFrame].image;
        auto* image=hasFrame?mFrames[mCurrFrame].image:nullptr;
        auto* mask=hasFrame&&mFrames[mCurrFrame].collisionMask?mFrames[mCurrFrame].collisionMask:image;
        const auto center=hasFrame?mFrames[mCurrFrame].center:Point(mWidth*.5f,mHeight*.5f);
        const double width=image?(image->frames?image->frameWidth:image->width):mWidth,height=image?image->height:mHeight;
        const double px=hasFrame?mFrames[mCurrFrame].centerOffsetX:0,py=hasFrame?mFrames[mCurrFrame].centerOffsetY:0;
        const int frame=hasFrame?mFrames[mCurrFrame].imageFrameNum:0;
        const double sx=mScaleX*(mFlipX?-1:1),sy=mScaleY*(mFlipY?-1:1);
        std::vector<double> key{double(frame),width,height,center.x,center.y,px,py,mFacing,sx,sy};
        if(image==lastImage && mask==lastMask && key==last) return false;
        // Frame artwork rotates around its per-frame pivot; express that in the
        // same owner-local frame used by explicit additive shapes.
        if(width>0 && height>0 && std::abs(sx)>1e-12 && std::abs(sy)>1e-12) {
            const double c=std::cos(mFacing),s=std::sin(mFacing);
            const float dx=(c*px+s*py-px)/sx,dy=(-s*px+c*py-py)/sy;
            Rect local(-center.x+dx,-center.y+dy,width-center.x+dx,height-center.y+dy);
            Collider::Shape shape{0,collisionShape_Convex,Point(),0,{}, {},"frame",true};
            if(mode==frameCollider_AlphaMask && mask) {
                const int maskFrame=mask->frames>1?frame:0;
                if(mask->frames>0 && maskFrame>=mask->frames) throw std::invalid_argument("Frame collision mask is missing an image frame");
                const int maskWidth=mask->frames?mask->frameWidth:mask->width;
                shape=Collider::imageMaskShape(*mask,Rect(maskFrame*maskWidth,0,(maskFrame+1)*maskWidth,mask->height),local,threshold);
                shape.name="frame";
            } else shape.vertices={Point(local.left,local.top),Point(local.right,local.top),Point(local.right,local.bottom),Point(local.left,local.bottom)};
            shapes.push_back(std::move(shape));
        }
        last=std::move(key);lastImage=image;lastMask=mask;return true;
    };
    // Source setup is transactional even when this is the first collider.
    const bool created=collider==Collider::NoCollider;
    auto &result=setupCollider();
    try { result.useGeometrySource(colliderSource_Frame,std::move(provider));
        result.mFrameMode=mode; result.mAlphaThreshold=threshold; }
    catch(...) { if(created)removeCollider();throw; }
    return result;
}
Collider& Sprite::setupAnimationCollider() {
#ifndef PDG_SPRITER_SUPPORT
    throw std::logic_error("Animation collider sources require Spriter support");
#else
    if(!mEntityInstance) throw std::logic_error("Sprite has no authored animation collision boxes");
    auto provider=[this](std::vector<Collider::Shape>& shapes) {
        refreshSpriterPose();
        const auto root=partRootTransform();
        if(std::abs(root.a*root.d-root.b*root.c)<1e-12) return true;
        const auto inverse=root.inverse();
        for(int i=0;i<getSpriterCollisionBoxCount();++i) {
            const char* name=getSpriterCollisionBoxName(i);if(!name)continue;
            const auto rect=getSpriterCollisionBox(name);if(rect.width()<=0||rect.height()<=0)continue;
            Collider::Shape shape{0,collisionShape_Convex,Point(),0,{}, {},name,true};
            for(const auto &point:rect.getQuad().points) shape.vertices.push_back(inverse.transformPoint(point));
            shapes.push_back(std::move(shape));
        }
        return true;
    };
    const bool created=collider==Collider::NoCollider;
    auto &result=setupCollider();
    try { result.useGeometrySource(colliderSource_Animation,std::move(provider)); }
    catch(...) { if(created)removeCollider();throw; }
    return result;
#endif
}
Collider& Sprite::setupCollider() {
    if (collider != Collider::NoCollider) return collider;
    auto result = std::make_unique<Collider>();
    result->attach([this] { return partRootTransform(); }, [this]() -> PhysicsBody& { return physics; },
                   [this]() -> const void* { return mLayer; });
    result->setEventSink([this](const ColliderContact& contact) {
        addRef();
        const std::unique_ptr<Sprite, void(*)(Sprite*)> retained(this, [](Sprite* p) { p->release(); });
        postEvent(eventType_ColliderContact, const_cast<ColliderContact*>(&contact));
    });
    result->addRef(); collider.mCollider = result.release();
    return collider;
}
void Sprite::removeCollider() {
    if (collider == Collider::NoCollider) return;
    auto* old = collider.mCollider; collider.mCollider = &Collider::NoCollider;
    old->detach(); old->release();
}
Collider& Part::setupCollider() {
    if (collider != Collider::NoCollider) return collider;
    auto result = std::make_unique<Collider>();
    result->attach([this] { return getTransform(partSpace_World); }, [this]() -> PhysicsBody& { return physics; },
                   [this]() -> const void* { return mSprite ? mSprite->mLayer : nullptr; });
    result->setEventSink([this](const ColliderContact& contact) {
        if (!mSprite) return;
        auto* sprite = mSprite;
        sprite->addRef();
        const std::unique_ptr<Sprite, void(*)(Sprite*)> retained(sprite, [](Sprite* p) { p->release(); });
        sprite->postEvent(eventType_ColliderContact, const_cast<ColliderContact*>(&contact));
    });
    result->addRef(); collider.mCollider = result.release();
    return collider;
}
void Part::removeCollider() {
    if (collider == Collider::NoCollider) return;
    auto* old = collider.mCollider; collider.mCollider = &Collider::NoCollider;
    old->detach(); old->release();
}

Part::~Part() { clearIKLimits(); removeCollider(); detachSprite(); removePhysicsBody(); }
SpatialTransform Part::sourceFrame() const {
    SpatialTransform result;
#ifdef PDG_SPRITER_SUPPORT
    if (hasCurrentRig()) {
        const auto pose = mSprite->getAnimationPose();
        AnimationTransform frame;
        if (mBinding != animation_NoBinding) frame = pose.getBindingTransform(mBinding);
        else if (mSocket != animation_NoSocket) frame = pose.getSocketTransform(mSocket);
        else if (mBone != boneId_None) frame = pose.getGlobalTransform(mBone);
        result = SpatialTransform::fromTRS(frame.x, frame.y, frame.rotation, frame.scaleX, frame.scaleY);
    }
#endif
    return result;
}
SpatialTransform Part::physicsFrame() const {
    if (mParent) return mParent->getTransform(partSpace_World);
    return SpatialTransform::compose(mSprite ? mSprite->partRootTransform() : SpatialTransform(), sourceFrame());
}
PhysicsBody& Part::setupPhysicsBody(double mass, double inertia) {
    if (physics != PhysicsBody::NoPhysics) {
        physics->configureMass(mass, inertia);
        return physics;
    }
    auto body = std::make_unique<PhysicsBody>(mass, inertia);
    initializePhysicsBody(*body);
    return *body.release();
}
void Part::initializePhysicsBody(PhysicsBody& body, bool restoring) {
    if (physics == body) return;
    if (body == PhysicsBody::NoPhysics) { removePhysicsBody(); return; }
    if (body.isAttached() || body.getSolver() != physicsSolver_Basic)
        throw std::logic_error("Assign a detached physics body; remove it from its previous owner first");
    const auto frame=physicsFrame();frame.inverse();
    const auto origin = frame.transformPoint(mLocation);
    const double sign = (mFlipX ? -mScaleX : mScaleX) < 0 ? -1 : 1;
    const double x = std::cos(mFacing) * sign, y = std::sin(mFacing) * sign;
    const double angle = std::atan2(frame.b*x + frame.d*y, frame.a*x + frame.c*y);
    removePhysicsBody();
    if (!restoring) cancelProgrammedMotion();
    body.teleport(origin, angle);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    if(mSprite && mSprite->mLayer && mSprite->mLayer->mUseChipmunkPhysics)
        body.attachSolver(std::make_unique<PartBodySolver>(mSprite,mSprite->mLayer->getSpace()));
#endif
    installPhysicsPublisher(body);
    body.addRef();physics.mBody=&body;
}
void Part::installPhysicsPublisher(PhysicsBody& body) {
    body.setPublisher([this](const PhysicsBodyState& state) {
        if (physics.getMode() == physicsBody_Dynamic) cancelProgrammedMotion();
        const auto inverse=physicsFrame().inverse();
        mLocation=inverse.transformPoint(Point(state.x,state.y));
        const double x=std::cos(state.rotation),y=std::sin(state.rotation);
        mFacing=std::atan2(inverse.b*x+inverse.d*y,inverse.a*x+inverse.c*y);
        if((mFlipX ? -mScaleX : mScaleX)<0) mFacing-=std::numbers::pi;
        refreshDependents();
    });
    body.setWorldProvider([this] { return mSprite ? mSprite->mLayer : nullptr; });
    body.mBreakPublisher = [this](const PhysicsBodyBreakInfo& info) { if (mSprite) mSprite->publishBodyBreak(this, info); };
}
// Installed only by Sprite after validating every named rig Part. As with
// initializePhysicsBody(), the owner holds one reference; script references may
// retain the body independently. Disable detaches its solver before rig teardown.
void Part::initializeAnimationPhysicsBody(PhysicsBody& body) {
    cancelProgrammedMotion();
    body.setOwnerPolicy({}, {});
    // The solved bone plus capsule offset supplies the Part transform already.
    body.setPublisher([](const PhysicsBodyState&) {});
    body.setWorldProvider([this] { return mSprite ? mSprite->mLayer : nullptr; });
    body.mBreakPublisher = [this](const PhysicsBodyBreakInfo& info) { if (mSprite) mSprite->publishBodyBreak(this, info); };
    body.addRef();physics.mBody = &body;mAnimationPhysicsBody = true;
}
void Part::validateTransformEdit() const {
    if (mAnimationPhysicsBody)
        throw std::logic_error("Mapped Part transforms belong to the physical rig; use Part.physics or disable the rig first");
}
void Part::removePhysicsBody() {
    validateTransformEdit();
    if(physics == PhysicsBody::NoPhysics) return;
#ifdef PDG_SPRITER_SUPPORT
    if(mSprite && mSprite->isAnimationPhysicsPartAttached(this))mSprite->detachAnimationPhysicsPart(this,false);
#endif
    if (auto* controller=physics->mRigDrive ? nullptr : static_cast<Part*>(physics->mDriveController)) {
        controller->mIKTarget->stopDrives();
        controller->mIKError="Physical IK body was removed; install a new target after replacing it";
    }
    collider->syncNative(nullptr);
    physics->detachSolver();
    auto* body=physics.mBody;physics.mBody=&PhysicsBody::NoPhysics;
    body->disconnect();body->setPublisher({});body->setOwnerPolicy({},{});body->release();
}
void Part::validateProgrammedTransform() const {
    validateTransformEdit();
    if(physics != PhysicsBody::NoPhysics && physics.getMode()==physicsBody_Dynamic)
        throw std::logic_error("Dynamic Part motion belongs to PhysicsBody; use physics velocity/forces or change its mode");
}
void Part::syncPhysicsTransform() {
    if(physics == PhysicsBody::NoPhysics || mPublishingPhysics || mAnimationPhysicsBody) return;
    const auto frame = physicsFrame();
    const double sign = (mFlipX ? -mScaleX : mScaleX) < 0 ? -1 : 1;
    const double x = std::cos(mFacing) * sign, y = std::sin(mFacing) * sign;
    physics->setOwnerTransform(frame.transformPoint(mLocation), std::atan2(frame.b*x + frame.d*y, frame.a*x + frame.c*y));
}
void Part::setParentLink(Part* parent) {
    if (mParent == parent) return;
    if (mParent) --mParent->mChildCount;
    mParent = parent;
    if (mParent) ++mParent->mChildCount;
}
void Part::refreshDependents() {
    if (!mSprite || mSprite->mRefreshingPartPhysics) return;
    // Independent Parts do not change sibling frames. Avoid refreshing the
    // entire host (and every attachment) once for each body's publication.
    if (mChildCount) mSprite->refreshPartPhysics();
    else updateAttachment();
}
void Part::locationChanged(const Offset&) { syncPhysicsTransform(); refreshDependents(); }
void Part::rotationChanged(float) { syncPhysicsTransform(); refreshDependents(); }
void Part::scaleChanged(const Offset&) { syncPhysicsTransform(); refreshDependents(); }
void Part::flipChanged(bool, bool) { scaleChanged(Offset()); }
void Part::stepPhysics(double seconds) {
    if (physics == PhysicsBody::NoPhysics) return;
    syncPhysicsSolver();
    if (physics.getSolver() == physicsSolver_Chipmunk) physics->publishWorldStep();
    else physics.step(seconds);
}
bool Part::animate(double seconds) {
    addRef();
    struct Release { Part* part; ~Release() { part->release(); } } release{this};
    const bool animated = AnimatedBase::animate(seconds);
    const bool solved = applyIKTarget();
    stepPhysics(seconds);
    return animated || solved || physics != PhysicsBody::NoPhysics;
}

// Independent parts are available with or without Spriter/Chipmunk.
Part::Part(Sprite* sprite, PartId id, const std::string& name)
    : mSprite(sprite), mId(id), mName(name) {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    INIT_SCRIPT_OBJECT(mPartScriptObj);
#endif
}
void Part::detach() {
    clearIKTarget();
    detachSprite();
    removePhysicsBody();
    setParentLink(nullptr);
    mSprite = nullptr;
    unbindFromBone();
}
bool Part::hasCurrentRig() const {
#ifdef PDG_SPRITER_SUPPORT
    return mSprite && mRig && mRig == mSprite->getAnimationRig();
#else
    return false;
#endif
}
BoneId Part::getBoneId() const { return hasCurrentRig() ? mBone : boneId_None; }

Part& Part::bindToBone(BoneId bone) {
    if (bone == boneId_None) return unbindFromBone();
#ifdef PDG_SPRITER_SUPPORT
    const auto rig = mSprite ? mSprite->getAnimationRig() : nullptr;
    if (!rig || bone >= rig->getBoneCount())
        throw std::invalid_argument("Part bone binding requires a valid bone in its Sprite's enabled rig");
    validateProgrammedTransform();
    unbindFromBone();
    mRig = rig; mBone = bone; setParentLink(nullptr);
    syncPhysicsTransform();
    return *this;
#else
    throw std::logic_error("No skeletal rig is available for this Part");
#endif
}
Part& Part::unbindFromBone() {
    validateTransformEdit();
    mBone = boneId_None; mBinding = mSocket = std::numeric_limits<uint32_t>::max();
    mRig.reset();
    if (physics != PhysicsBody::NoPhysics) {
        if (physics.getMode() == physicsBody_Kinematic) syncPhysicsTransform();
        else physics->publishWorldStep();
    }
    if (mSprite) { mSprite->refreshPartPhysics(); mSprite->updatePartAttachments(); }
    return *this;
}
Part& Part::bindToAnimationBinding(const std::string& name) {
#ifdef PDG_SPRITER_SUPPORT
    const auto rig = mSprite ? mSprite->getAnimationRig() : nullptr;
    const auto id = rig ? rig->findBinding(name) : animation_NoBinding;
    if (id == animation_NoBinding) throw std::invalid_argument("Unknown binding in the Part owner's enabled rig");
    validateProgrammedTransform();
    unbindFromBone();mRig=rig;mBinding=id;mBone=rig->getBinding(id).bone;setParentLink(nullptr);
    syncPhysicsTransform();return *this;
#else
    throw std::logic_error("No authored animation bindings are available for this Part");
#endif
}
Part& Part::bindToAnimationSocket(const std::string& name) {
#ifdef PDG_SPRITER_SUPPORT
    const auto rig = mSprite ? mSprite->getAnimationRig() : nullptr;
    const auto id = rig ? rig->findSocket(name) : animation_NoSocket;
    if (id == animation_NoSocket) throw std::invalid_argument("Unknown socket in the Part owner's enabled rig");
    validateProgrammedTransform();
    unbindFromBone();mRig=rig;mSocket=id;mBone=rig->getSocket(id).bone;setParentLink(nullptr);
    syncPhysicsTransform();return *this;
#else
    throw std::logic_error("No authored animation sockets are available for this Part");
#endif
}
std::string Part::getAnimationBindingName() const {
#ifdef PDG_SPRITER_SUPPORT
    if (hasCurrentRig() && mBinding != animation_NoBinding) return mRig->getBinding(mBinding).name;
#endif
    return {};
}
std::string Part::getAnimationSocketName() const {
#ifdef PDG_SPRITER_SUPPORT
    if (hasCurrentRig() && mSocket != animation_NoSocket) return mRig->getSocket(mSocket).name;
#endif
    return {};
}
Part& Part::setDrawing(const Drawing& drawing) { mDrawing=drawing.share(); return *this; }
Part& Part::setImage(const Image& image, const Rect& bounds) {
#ifndef PDG_NO_GUI
    if (!std::isfinite(bounds.left) || !std::isfinite(bounds.top) ||
        !std::isfinite(bounds.right) || !std::isfinite(bounds.bottom))
        throw std::invalid_argument("Part image bounds must be finite");
    auto content=std::shared_ptr<Drawing>(Drawing::create());
    std::unique_ptr<ElementRef> element(content->addImage(bounds,image,Attributes()));
    mDrawing=std::move(content);return *this;
#else
    throw std::logic_error("Part image content requires a GUI build");
#endif
}
Part& Part::clearContent() { mDrawing.reset();return *this; }
Rect Part::getContentBounds(int space) const {
    const auto transform=getTransform(space); // validate space even when empty
    if (!mDrawing) return Rect();
    const auto bounds=mDrawing->getBounds();
    if (space == partSpace_Local) return bounds;
    Quad quad(bounds);for(auto& point:quad.points)point=transform.transformPoint(point);
    return quad.getBounds();
}
void Part::drawContent() {
#ifndef PDG_NO_GUI
    if (!mDrawing || !mSprite || !mSprite->mLayer || !mSprite->mPort) return;
    const auto transform=getTransform(partSpace_World);
    auto point=[&](float x,float y) {return mSprite->mLayer->layerToPort(transform.transformPoint(Point(x,y)));};
    const auto origin=point(0,0), x=point(1,0), y=point(0,1);
    glm::mat3 matrix(1);matrix[0]=glm::vec3(x.x-origin.x,x.y-origin.y,0);
    matrix[1]=glm::vec3(y.x-origin.x,y.y-origin.y,0);matrix[2]=glm::vec3(origin.x,origin.y,1);
    Attributes attributes;attributes.setTransform(matrix).lineOpacity(mSprite->mOpacity).fillOpacity(mSprite->mOpacity);
    mDrawing->drawTransformed(mSprite->mPort,attributes,true);
#endif
}
Part& Part::setParentPart(Part* parent) {
    validateProgrammedTransform();
    if (parent && (!mSprite || parent->mSprite != mSprite))
        throw std::invalid_argument("Part parent must belong to the same Sprite");
    for (Part* ancestor = parent; ancestor; ancestor = ancestor->mParent)
        if (ancestor == this) throw std::invalid_argument("Part parenting would create a cycle");
    if (physics != PhysicsBody::NoPhysics) {
        const auto frame = parent ? parent->getTransform(partSpace_World) : (mSprite ? mSprite->partRootTransform() : SpatialTransform());
        frame.inverse(); // validate before replacing the existing parent
    }
    setParentLink(parent);
    unbindFromBone();
    syncPhysicsTransform();
    if (mSprite) { mSprite->refreshPartPhysics(); mSprite->updatePartAttachments(); }
    return *this;
}
SpatialTransform Part::getTransform(int space) const {
    if (space < partSpace_Local || space > partSpace_World)
        throw std::invalid_argument("Invalid integer Part coordinate space");
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    if (mAnimationPhysicsBody && mSprite && mSprite->mAnimationPhysics) {
        // Generated geometry is expressed in physical body units, independently
        // of imported bone display/stretch scales. Resolve all three spaces from
        // that same rigid frame, including mounts below this Part.
        const auto state=physics.getState();
        const auto index=mSprite->mAnimationPhysics->bodyIndex(static_cast<cpBody*>(physics->nativeBody()));
        auto world=SpatialTransform::fromTRS(state.x,state.y,state.rotation,1,mSprite->mAnimationPhysics->bodyReflection(index));
        if (space==partSpace_World) return world;
        const auto parent=space==partSpace_Sprite ? mSprite->partRootTransform() : physicsFrame();
        return SpatialTransform::compose(parent.inverse(),world);
    }
#endif
    SpatialTransform result = SpatialTransform::fromTRS(mLocation.x, mLocation.y, mFacing,
                                                       mScaleX * (mFlipX ? -1 : 1), mScaleY * (mFlipY ? -1 : 1));
    if (space == partSpace_Local) return result;
    // Compose iteratively so a long valid Part chain does not overflow the stack.
    const Part* part = this;
    while (part->mParent) {
        part = part->mParent;
        result = SpatialTransform::compose(part->getTransform(partSpace_Local), result);
    }
    result = SpatialTransform::compose(part->sourceFrame(), result);
    if (space == partSpace_World && mSprite)
        result = SpatialTransform::compose(mSprite->partRootTransform(), result);
    return result;
}
SpatialTransform Sprite::partRootTransform() const {
#ifdef PDG_SPRITER_SUPPORT
    if (mEntityInstance) {
        const auto root = spriterRootTransform();
        return SpatialTransform::fromTRS(root.x, root.y, root.rotation, root.scaleX, root.scaleY);
    }
#endif
    return SpatialTransform::fromTRS(mLocation.x, mLocation.y, mFacing,
                                    mScaleX * (mFlipX ? -1 : 1), mScaleY * (mFlipY ? -1 : 1));
}
bool Sprite::attachmentReaches(const Sprite* target) const {
	std::vector<const Sprite*> pending{this};
	std::set<const Sprite*> visited;
	while (!pending.empty()) {
		const auto* next = pending.back();
		pending.pop_back();
		if (next == target) return true;
		if (!visited.insert(next).second) continue;
#ifdef PDG_SPRITER_SUPPORT
		for (const auto& item : next->mAttachedSprites) {
			if (item.second) pending.push_back(item.second);
		}
#endif
        for (auto* part : next->mParts) if (part->mAttachedSprite) pending.push_back(part->mAttachedSprite);
	}
	return false;
}

Part* Sprite::createPart(const std::string& name) {
    if (name.empty() || findPart(name)) throw std::invalid_argument("Part names must be nonempty and unique within a Sprite");
    if (mNextPartId == partId_None) throw std::overflow_error("Part ID space exhausted");
    std::unique_ptr<Part, void(*)(Part*)> part(new Part(this, mNextPartId, name),
                                             [](Part* p) { delete p; });
    mParts.push_back(part.get());
    ++mNextPartId;
    part->addRef();
    return part.release();
}
#include "sprite-part-transfer.inc"
Part* Sprite::getPart(PartId id) const {
    for (auto* part : mParts) if (part->getId() == id) return part;
    return nullptr;
}
Part* Sprite::findPart(const std::string& name) const {
    for (auto* part : mParts) if (part->getName() == name) return part;
    return nullptr;
}
std::vector<std::string> Sprite::getPartNames() const {
    std::vector<std::string> names;
    for (auto* part : mParts) names.push_back(part->getName());
    return names;
}
bool Sprite::removePart(PartId id) {
    const auto found = std::find_if(mParts.begin(), mParts.end(),
                                  [id](Part* p) { return p->getId() == id; });
    if (found == mParts.end()) return false;
    Part* part = *found;
    part->validateTransformEdit();
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    if(isAnimationPhysicsPartAttached(part))detachAnimationPhysicsPart(part,false);
#endif
    for (auto* candidate : mParts) {
        for (auto* ancestor=candidate;ancestor;ancestor=ancestor->mParent)
            if(ancestor==part) {candidate->detachSprite();break;}
    }
    for (auto* child : mParts) if (child->mParent == part) child->setParentLink(nullptr);
    mParts.erase(found);
    part->detach();
    part->release();
    return true;
}
void Sprite::clearParts() {
    for (auto* part : mParts) part->validateTransformEdit();
    std::vector<Part*> parts;
    parts.swap(mParts);
    // Unlink while every parent is alive; creation order need not be tree order.
    for (auto* part : parts) part->setParentLink(nullptr);
    for (auto* part : parts) { part->detach(); part->release(); }
}
#include "part-ik.inc"

void Part::decomposeMount(const SpatialTransform& t, Point& location, float& angle, Offset& scale) {
    for (double value : {t.a,t.b,t.c,t.d,t.tx,t.ty})
        if(!std::isfinite(value)) throw std::invalid_argument("Attachment transforms must be finite");
    const double x=std::hypot(t.a,t.b), y=std::hypot(t.c,t.d);
    if (x == 0 || y == 0) throw std::invalid_argument("Attachment transform is singular");
    if (std::abs(t.a*t.c+t.b*t.d) > 1e-6*x*y)
        throw std::invalid_argument("Attached Sprite roots cannot represent shear; use uniform ancestor scale or aligned axes");
    location=Point(t.tx,t.ty);angle=std::atan2(t.b,t.a);
    scale=Offset(x,(t.a*t.d-t.b*t.c)/x);
}
Part* Part::attachSprite(Sprite* child, int placement, Part* childMount) {
    if (!mSprite || !child || child->mLayer != mSprite->mLayer)
        throw std::invalid_argument("Attachments require an owned Part and a child in the same layer");
    if (placement != partPlacement_Snap && placement != partPlacement_PreserveWorld)
        throw std::invalid_argument("Expected a partPlacement integer constant");
    if (child->mAttachmentPart || child->attachmentReaches(mSprite))
        throw std::invalid_argument("Sprite already attached or attachment would create a cycle");
    if (child->physics != PhysicsBody::NoPhysics && child->physics.getMode() != physicsBody_Kinematic)
        throw std::logic_error("Rigid mounting requires a nonphysical or kinematic Sprite; dynamic holding requires a constraint");
    if (childMount && childMount->mSprite != child)
        throw std::invalid_argument("Child mounting frame must belong to the child Sprite");
    // Reject mixing the compatibility Spriter attachment graph with a second root writer.
#ifdef PDG_SPRITER_SUPPORT
    if (child->mSpriterAttachmentOwner)
        throw std::logic_error("Detach the existing Spriter attachment before mounting through a Part");
#endif
    const auto childFrame=childMount?childMount->getTransform(partSpace_Sprite):SpatialTransform();
    const auto inverseMount=childFrame.inverse();
    const auto host=getTransform(partSpace_World);
    const auto offset=placement==partPlacement_PreserveWorld?
        SpatialTransform::compose(SpatialTransform::compose(host.inverse(),child->partRootTransform()),childFrame):SpatialTransform();
    Point location;float angle;Offset scale;decomposeMount(offset,location,angle,scale);
    Point targetLocation;float targetAngle;Offset targetScale;
    decomposeMount(SpatialTransform::compose(SpatialTransform::compose(host,offset),inverseMount),targetLocation,targetAngle,targetScale);
    auto root=child->partRootTransform();root.inverse();
    std::string name="attachment_"+std::to_string(mSprite->mNextPartId);
    while(mSprite->findPart(name))name+="_";
    auto* mount=mSprite->createPart(name);mount->setParentPart(this);
    mount->setLocation(location);mount->setRotation(angle);mount->setScale(scale.x,scale.y);
    mount->mChildMountInverse=inverseMount;
    for (float* field : {&child->mLocation.x,&child->mLocation.y,&child->mFacing,
        &child->mWidth,&child->mHeight,&child->mScaleX,&child->mScaleY,&child->mCenterOffset.x,&child->mCenterOffset.y,
        &child->mDeltaXPerMs,&child->mDeltaYPerMs,&child->mDeltaFacingPerMs,&child->mDeltaWidthPerMs,&child->mDeltaHeightPerMs}) child->cancelAnimation(field);
    child->mDeltaXPerMs=child->mDeltaYPerMs=child->mDeltaFacingPerMs=child->mDeltaWidthPerMs=child->mDeltaHeightPerMs=0;
    if (child->physics != PhysicsBody::NoPhysics) child->physics.stopMoving().stopSpinning();
    child->addRef();mount->mAttachedSprite=child;child->mAttachmentPart=mount;
    mount->updateAttachment();return mount;
}
Part& Part::detachSprite() {
    auto* child=mAttachedSprite;mAttachedSprite=nullptr;mAttachmentError.clear();
    if(child) {child->mAttachmentPart=nullptr;child->release();}
    return *this;
}
void Part::updateAttachment() {
    if(!mAttachedSprite)return;
    auto* child=mAttachedSprite;
    if (!mSprite) return; // group membership can be changing during layer transfer
    try {
        const auto target=SpatialTransform::compose(getTransform(partSpace_World),mChildMountInverse);
        Point location;float angle;Offset scale;decomposeMount(target,location,angle,scale);
        float normX=child->mFlipX?-1:1,normY=child->mFlipY?-1:1;
#ifdef PDG_SPRITER_SUPPORT
        if(child->mEntityInstance){normX=child->mEntityScaleX;normY=child->mEntityScaleY;}
#endif
        if(normX==0 || normY==0)throw std::invalid_argument("Attached Sprite has singular asset normalization");
        const auto delta=location-child->mLocation;const float rotation=angle-child->mFacing;
        const Offset scaleDelta(scale.x/normX-child->mScaleX,scale.y/normY-child->mScaleY);
        child->mLocation=location;child->mFacing=angle;child->mScaleX=scale.x/normX;child->mScaleY=scale.y/normY;
        child->locationChanged(delta);child->rotationChanged(rotation);child->scaleChanged(scaleDelta);
        child->updatePartAttachments();mAttachmentError.clear();
    } catch(const std::exception& error) {mAttachmentError=error.what();}
}
void Sprite::updatePartAttachments() {
    if(mUpdatingPartAttachments)return;
    mUpdatingPartAttachments=true;
    struct Reset {bool& flag;~Reset(){flag=false;}} reset{mUpdatingPartAttachments};
    const auto parts = mParts;
    for (auto* part : parts) part->addRef();
    try {
        for (auto* part : parts) if (part->mSprite == this) part->updateAttachment();
    } catch (...) { for (auto* part : parts) part->release(); throw; }
    for (auto* part : parts) part->release();
}

std::vector<Part*> Sprite::orderedParts() const {
    auto parts = mParts;
    auto depth = [](const Part* part) {
        size_t result = 0;
        while ((part = part->mParent)) ++result;
        return result;
    };
    std::stable_sort(parts.begin(), parts.end(), [&](const Part* a, const Part* b) { return depth(a) < depth(b); });
    return parts;
}

void Sprite::refreshPartPhysics() {
    if (mRefreshingPartPhysics) return;
    mRefreshingPartPhysics = true;
    struct Reset { bool& flag; ~Reset() { flag = false; } } reset{mRefreshingPartPhysics};
    const auto parts = orderedParts();
    for (auto* part : parts) part->addRef();
    try {
        for (auto* part : parts) {
            if (part->mSprite != this || part->physics == PhysicsBody::NoPhysics) continue;
            if (part->physics.getMode() == physicsBody_Kinematic) part->syncPhysicsTransform();
            else part->physics->publishWorldStep();
        }
        updatePartAttachments();
    } catch (...) { for (auto* part : parts) part->release(); throw; }
    for (auto* part : parts) part->release();
}

void Sprite::animateParts(double seconds) {
    // Helpers can remove/reparent Parts. Retain a stable update snapshot and
    // publish again in current hierarchy order after every helper has run.
    const auto parts = orderedParts();
    for (auto* part : parts) part->addRef();
    try {
        for (auto* part : parts) if (part->mSprite == this) part->AnimatedBase::animate(seconds);
        // Every helper has supplied this step's local pose before ordered IK.
        // Controllers use stable Part IDs and tolerate removal/reparenting by helpers.
        const auto controllers = orderedParts();
        for (auto* part : controllers) part->applyIKTarget();
        for (auto* part : parts) if (part->mSprite == this) part->stepPhysics(seconds);
        refreshPartPhysics();
    } catch (...) { for (auto* part : parts) part->release(); throw; }
    for (auto* part : parts) part->release();
}

Sprite::~Sprite() {
    removeCollider();
    for (int i=0; i<mNumFrames; ++i) {
        if (mFrames[i].image) mFrames[i].image->release();
        if (mFrames[i].collisionMask) mFrames[i].collisionMask->release();
    }
    mNumFrames=0;
#if defined(PDG_SPRITER_SUPPORT) && defined(PDG_USE_CHIPMUNK_PHYSICS)
    releaseAnimationPhysics();
#endif
    for(auto* part:mParts)part->mAnimationPhysicsBody=false; // Also permits cleanup of an incomplete staged record.
    clearParts();
    removePhysicsBody();
#ifdef PDG_SPRITER_SUPPORT
#ifdef PDG_USE_CHIPMUNK_PHYSICS
    mAnimationPhysics.reset();mAnimationDesired.reset();
#endif
    mAnimationDrawings.clear();
    mAnimationPipeline.reset(); mAnimationIK.clear();
#endif
    //                DEBUG_ONLY( OS::_DOUT("dt Sprite %p", this) = 0; )
    if(collider!=Collider::NoCollider) collider.setEnabled(false);
  #ifndef PDG_NO_EVENT_QUEUE
	EventManager* eventMgr = EventManager::getSingletonInstance();
	if (eventMgr) {
		// make sure we don't have any events queued up for this sprite
		eventMgr->RemoveEnqueuedEventsForEmitter(this);
	}
  #endif // ! PDG_NO_EVENT_QUEUE
  #ifndef PDG_NO_GUI
	if (mDrawHelper && mDrawHelper->ownedBySprite()) {
		delete mDrawHelper;
		mDrawHelper = 0;
	}
	if (mPostDrawHelper && mPostDrawHelper->ownedBySprite()) {
		delete mPostDrawHelper;
		mPostDrawHelper = 0;
	}
  #endif
    if (userData) {
        userData->release();
        userData = 0;
    }
	if (mLayer) {
	  #ifdef PDG_USE_CHIPMUNK_PHYSICS
		if (mLayer && USE_CHIPMUNK) {
			disconnect();   // remove all constraints
			freeCpBody();
		}
		// this will do another release() on this sprite, but the refcount
		// should already be 0 so it won't get deleted again
		// and it ensures that the layer and other sprites don't have
		// references to this sprite
		mLayer->removeSprite(this);
		mLayer = 0; // remove the reference to the layer
	  #endif
	}
  #ifdef PDG_SPRITER_SUPPORT
	clearAttachedSprites();
	if (mEntityInstance) {
		delete mEntityInstance;
		mEntityInstance = nullptr;
	}
  #endif
  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupSpriteScriptObject(mSpriteScriptObj);
  #endif
//	DEBUG_PRINT("Destroyed Sprite [%p]", this);
}

#ifdef PDG_SPRITER_SUPPORT
void Sprite::calcColliderBounds() const {
	refreshSpriterPose();
	mColliderBounds = Rect();
	bool haveBox = false;
	auto* order = mEntityInstance ? mEntityInstance->getZOrder() : nullptr;
	if (order) for (auto* obj : *order) {
		if (!dynamic_cast<SpriterEngine::BoxInstanceInfo*>(obj)) continue;
		const Rect bounds = spriterBoxRect(*obj).getBounds();
		if (!haveBox) { mColliderBounds = bounds; haveBox = true; }
		else {
			mColliderBounds.left = std::min(mColliderBounds.left, bounds.left);
			mColliderBounds.top = std::min(mColliderBounds.top, bounds.top);
			mColliderBounds.right = std::max(mColliderBounds.right, bounds.right);
			mColliderBounds.bottom = std::max(mColliderBounds.bottom, bounds.bottom);
		}
	}
	mColliderBoundsValid = true;
}

RotatedRect Sprite::getSpriterCollisionBox(const char* boxName) const {
	if (!mEntityInstance || !boxName) return RotatedRect();
	refreshSpriterPose();
	auto* obj = mEntityInstance->objectIfExistsOnCurrentFrame(boxName);
	if (!obj && strncmp(boxName, "collision_box_", 14) == 0) {
		char* end = nullptr;
		const long index = strtol(boxName + 14, &end, 10);
		if (end != boxName + 14 && *end == '\0' && index >= 0) {
			auto* order = mEntityInstance->getZOrder();
			long current = 0;
			if (order) for (auto* item : *order) {
				if (!dynamic_cast<SpriterEngine::BoxInstanceInfo*>(item)) continue;
				if (current++ == index) { obj = item; break; }
			}
		}
	}
	return dynamic_cast<SpriterEngine::BoxInstanceInfo*>(obj) ? spriterBoxRect(*obj) : RotatedRect();
}

bool Sprite::isSpriterCollisionActive(const char* boxName) const {
	// Zero-area boxes cannot collide; named non-box objects are not hitboxes.
	const auto rect = getSpriterCollisionBox(boxName);
	return rect.width() > 0 && rect.height() > 0;
}

int Sprite::getSpriterCollisionBoxCount() const {
	if (!mEntityInstance) {
		return 0;
	}
	
	refreshSpriterPose();
	// Get all active objects from the current frame
	auto zOrder = mEntityInstance->getZOrder();
	if (!zOrder) {
		return 0;
	}
	
	// Count collision boxes
	int count = 0;
	for (auto obj : *zOrder) {
		if (obj && dynamic_cast<SpriterEngine::BoxInstanceInfo*>(obj)) {
			count++;
		}
	}
	
	return count;
}

const char* Sprite::getSpriterCollisionBoxName(int index) const {
	if (!mEntityInstance || index < 0) {
		return nullptr;
	}
	
	refreshSpriterPose();
	// Get all active objects from the current frame
	auto zOrder = mEntityInstance->getZOrder();
	if (!zOrder) {
		return nullptr;
	}
	
	// Find collision box at the specified index
	int currentIndex = 0;
	for (auto obj : *zOrder) {
		if (!obj) {
			continue;
		}
		// Support box names in both GUI and non-GUI modes
		auto boxObj = dynamic_cast<SpriterEngine::BoxInstanceInfo*>(obj);
		if (!boxObj) {
			continue;
		}
		if (currentIndex == index) {
			// Try to return the authored box name first, but preserve a stable
			// fallback identifier when the source file leaves the name blank.
			auto pdgBoxObj = dynamic_cast<pdg::PDGBoxInstanceInfo*>(boxObj);
			if (pdgBoxObj) {
				const std::string& boxName = pdgBoxObj->getBoxName();
				if (!boxName.empty()) {
					return boxName.c_str();
				}
			}
            if (auto* factory=mSpriterModel?dynamic_cast<PDGFileFactory*>(mSpriterModel->getFileFactory()):nullptr) {
                const auto catalog=factory->rigCatalog();
                const auto schema=catalog->entities.find(mEntityInstance->currentEntityName());
                if (schema!=catalog->entities.end()) for (const auto& name:schema->second->boxNames) {
                    if (mEntityInstance->getObjectInstance(name)!=obj) continue;
                    if (pdgBoxObj) { pdgBoxObj->setBoxName(name);return pdgBoxObj->getBoxName().c_str(); }
                    mFallbackCollisionBoxName=name;return mFallbackCollisionBoxName.c_str();
                }
            }
			mFallbackCollisionBoxName = "collision_box_" + std::to_string(index);
			return mFallbackCollisionBoxName.c_str();
		}
		currentIndex++;
	}
	
	return nullptr;
}



bool Sprite::checkSpriterCollisionBoxPointCollision(const Point& p) {
	if (!mEntityInstance) {
		return false;
	}
	
	// Step 1: Quick bounds check
	if (!mColliderBoundsValid) {
		calcColliderBounds();
	}
	
	// If point is outside bounds, no collision possible
	if (!mColliderBounds.contains(p)) {
		return false;
	}
	
	// Step 2: Detailed collision box check (only if point is within bounds)
	auto zOrder = mEntityInstance->getZOrder();
	if (!zOrder) {
		return false;
	}
	
	// Check if point is inside any collision box
	for (auto obj : *zOrder) {
		if (dynamic_cast<SpriterEngine::BoxInstanceInfo*>(obj)) {
			// Check if this object has size and position (indicating it's a collision box)
			SpriterEngine::point size = obj->getSize();
			if (size.x > 0 && size.y > 0) {
				
				// Convert to PDG RotatedRect
				RotatedRect rect = spriterBoxRect(*obj);
				
				if (rect.width() > 0 && rect.height() > 0 && rect.getQuad().contains(p)) {
					return true;
				}
			}
		}
	}
	return false;
}
#endif // PDG_SPRITER_SUPPORT


	
} // end namespace pdg
