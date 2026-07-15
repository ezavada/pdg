// -----------------------------------------------
// sprite.cpp
//
// Implementation file for Sprite bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "../core/core_impl_macros.h"
#include "../data/data_impl_macros.h"
#include "animation_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    
// ========================================================================================
//MARK: ISpriteCollideHelper
// ========================================================================================

BINDING_INITIALIZER_IMPL(ISpriteCollideHelper) 
    EXPORT_CLASS_SYMBOLS("ISpriteCollideHelper", ISpriteCollideHelper, , , );
	END

CLEANUP_IMPL(ISpriteCollideHelper)


%#ifndef PDG_NO_GUI
// ========================================================================================
//MARK: ISpriteDrawHelper
// ========================================================================================

BINDING_INITIALIZER_IMPL(ISpriteDrawHelper) 
    EXPORT_CLASS_SYMBOLS("ISpriteDrawHelper", ISpriteDrawHelper, , , );
	END

CLEANUP_IMPL(ISpriteDrawHelper)

%#endif // !PDG_NO_GUI


// ========================================================================================
//MARK: Sprite
// ========================================================================================

static const char* sPinJointStr = "PinJoint";
static const char* sSlideJointStr = "SlideJoint";
static const char* sPivotJointStr = "PivotJoint";
static const char* sGrooveJointStr = "GrooveJoint";
static const char* sSpringJointStr = "SpringJoint";
static const char* sRotarySpringStr = "RotarySpring";
static const char* sRotaryLimitStr = "RotaryLimit";
static const char* sRatchetStr = "Ratchet";
static const char* sGearStr = "Gear";
static const char* sMotorStr = "Motor";

WRAPPER_INITIALIZER_IMPL_CUSTOM(Sprite, 
  OBJECT_SAVE(cppObj->mEventEmitterScriptObj, obj); 
  OBJECT_SAVE(cppObj->mAnimatedScriptObj, obj);
  OBJECT_SAVE(cppObj->mSpriteScriptObj, obj);
  OBJECT_SAVE(cppObj->mISerializableScriptObj, obj);
  cppObj->addRef() )
    EXPORT_CLASS_SYMBOLS("Sprite", Sprite, , ,
    	// method section
		HAS_EMITTER_METHODS(Sprite)
		HAS_ANIMATED_METHODS(Sprite)
		HAS_SERIALIZABLE_METHODS(Sprite)
		HAS_METHOD(Sprite, "getFrameRotatedBounds", GetFrameRotatedBounds)
		HAS_METHOD(Sprite, "setFrame", SetFrame)
		HAS_METHOD(Sprite, "getCurrentFrame", GetCurrentFrame)
		HAS_METHOD(Sprite, "getFrameCount", GetFrameCount)
		HAS_METHOD(Sprite, "startFrameAnimation", StartFrameAnimation)
		HAS_METHOD(Sprite, "stopFrameAnimation", StopFrameAnimation)
		HAS_PROPERTY(Sprite, WantsAnimLoopEvents)
		HAS_PROPERTY(Sprite, WantsAnimEndEvents)
		HAS_PROPERTY(Sprite, WantsCollideWallEvents)
		HAS_METHOD(Sprite, "addFramesImage", AddFramesImage)
	%#ifdef PDG_SPRITER_SUPPORT CR
		HAS_METHOD(Sprite, "hasAnimation", HasAnimation)
		HAS_METHOD(Sprite, "startAnimation", StartAnimation)
		HAS_METHOD(Sprite, "setEntityScale", SetEntityScale)
		HAS_METHOD(Sprite, "applyCharacterMap", ApplyCharacterMap)
		HAS_METHOD(Sprite, "removeCharacterMap", RemoveCharacterMap)
		HAS_METHOD(Sprite, "removeAllCharacterMaps", RemoveAllCharacterMaps)
		HAS_METHOD(Sprite, "getAppliedCharacterMaps", GetAppliedCharacterMaps)
		HAS_METHOD(Sprite, "enableSpriterEvents", EnableSpriterEvents)
		HAS_METHOD(Sprite, "areSpriterEventsEnabled", AreSpriterEventsEnabled)
		HAS_METHOD(Sprite, "blendToAnimation", BlendToAnimation)
		HAS_METHOD(Sprite, "isBlending", IsBlending)
		HAS_METHOD(Sprite, "getBlendProgress", GetBlendProgress)
		HAS_METHOD(Sprite, "pauseAnimation", PauseAnimation)
		HAS_METHOD(Sprite, "resumeAnimation", ResumeAnimation)
		HAS_METHOD(Sprite, "stopAnimation", StopAnimation)
		HAS_METHOD(Sprite, "isAnimationPlaying", IsAnimationPlaying)
		HAS_METHOD(Sprite, "isAnimationPaused", IsAnimationPaused)
		HAS_METHOD(Sprite, "getAnimationProgress", GetAnimationProgress)
		HAS_METHOD(Sprite, "hasAttachPoint", HasAttachPoint)
		HAS_METHOD(Sprite, "getAttachPoint", GetAttachPoint)
		HAS_METHOD(Sprite, "attachSprite", AttachSprite)
		HAS_METHOD(Sprite, "activateSubEntity", ActivateSubEntity)
		HAS_METHOD(Sprite, "detachSprite", DetachSprite)
		HAS_METHOD(Sprite, "getAttachedSprite", GetAttachedSprite)
		HAS_METHOD(Sprite, "getSpriterCollisionBox", GetSpriterCollisionBox)
		HAS_METHOD(Sprite, "isSpriterCollisionActive", IsSpriterCollisionActive)
		HAS_METHOD(Sprite, "getSpriterCollisionBoxCount", GetSpriterCollisionBoxCount)
		HAS_METHOD(Sprite, "getSpriterCollisionBoxName", GetSpriterCollisionBoxName)
	%#endif CR
		HAS_METHOD(Sprite, "changeFramesImage", ChangeFramesImage)
		HAS_METHOD(Sprite, "offsetFrameCenters", OffsetFrameCenters)
		HAS_METHOD(Sprite, "getFrameCenterOffset", GetFrameCenterOffset)
		HAS_PROPERTY(Sprite, Opacity)
		HAS_METHOD(Sprite, "fadeTo", FadeTo)
		HAS_METHOD(Sprite, "fadeIn", FadeIn)
		HAS_METHOD(Sprite, "fadeOut", FadeOut)
		HAS_METHOD(Sprite, "isBehind", IsBehind)
		HAS_METHOD(Sprite, "getZOrder", GetZOrder)
		HAS_METHOD(Sprite, "moveBehind", MoveBehind)
		HAS_METHOD(Sprite, "moveInFrontOf", MoveInFrontOf)
		HAS_METHOD(Sprite, "moveToFront", MoveToFront)
		HAS_METHOD(Sprite, "moveToBack", MoveToBack)
		HAS_METHOD(Sprite, "enableCollisions", EnableCollisions)
		HAS_METHOD(Sprite, "disableCollisions", DisableCollisions)
		HAS_METHOD(Sprite, "getCollisionType", GetCollisionType)
		HAS_PROPERTY(Sprite, CollisionRadius)
		HAS_METHOD(Sprite, "useCollisionMask", UseCollisionMask)
		HAS_METHOD(Sprite, "setCollisionHelper", SetCollisionHelper)
		HAS_PROPERTY(Sprite, Elasticity)
		HAS_METHOD(Sprite, "getLayer", GetLayer)
	%#ifndef PDG_NO_GUI  CR
		HAS_METHOD(Sprite, "setDrawHelper", SetDrawHelper)
		HAS_METHOD(Sprite, "setPostDrawHelper", SetPostDrawHelper)
		HAS_PROPERTY(Sprite, WantsMouseOverEvents)
		HAS_PROPERTY(Sprite, WantsClickEvents)
		HAS_PROPERTY(Sprite, MouseDetectMode)
		HAS_PROPERTY(Sprite, WantsOffscreenEvents)
	%#endif  CR // !PDG_NO_GUI
	  %#ifdef PDG_USE_CHIPMUNK_PHYSICS CR
		HAS_METHOD(Sprite, "makeStatic", MakeStatic)
		HAS_METHOD(Sprite, "getFriction", GetFriction)
		HAS_METHOD(Sprite, "setCollideGroup", SetCollideGroup)
		HAS_METHOD(Sprite, "getCollideGroup", GetCollideGroup)
		HAS_METHOD(Sprite, "pinJoint", PinJoint)
		HAS_METHOD(Sprite, "slideJoint", SlideJoint)
		HAS_METHOD(Sprite, "pivotJoint", PivotJoint)
		HAS_METHOD(Sprite, "grooveJoint", GrooveJoint)
		HAS_METHOD(Sprite, "springJoint", SpringJoint)
		HAS_METHOD(Sprite, "rotarySpring", RotarySpring)
		HAS_METHOD(Sprite, "rotaryLimit", RotaryLimit)
		HAS_METHOD(Sprite, "ratchet", Ratchet)
		HAS_METHOD(Sprite, "gear", Gear)
		HAS_METHOD(Sprite, "motor", Motor)
		HAS_METHOD(Sprite, "removeJoint", RemoveJoint)
		HAS_METHOD(Sprite, "disconnect", Disconnect)
		HAS_METHOD(Sprite, "makeJointBreakable", MakeJointBreakable)
		HAS_METHOD(Sprite, "makeJointUnbreakable", MakeJointUnbreakable)
	  %#endif  CR // PDG_USE_CHIPMUNK_PHYSICS
		HAS_METHOD(Sprite, "on", On)
		HAS_METHOD(Sprite, "onCollideSprite", OnCollideSprite)
		HAS_METHOD(Sprite, "onCollideWall", OnCollideWall)
		HAS_METHOD(Sprite, "onOffscreen", OnOffscreen)
		HAS_METHOD(Sprite, "onOnscreen", OnOnscreen)
		HAS_METHOD(Sprite, "onExitLayer", OnExitLayer)
		HAS_METHOD(Sprite, "onAnimationLoop", OnAnimationLoop)
		HAS_METHOD(Sprite, "onAnimationEnd", OnAnimationEnd)
		HAS_METHOD(Sprite, "onAnimationBlendComplete", OnAnimationBlendComplete)
		HAS_METHOD(Sprite, "onFadeComplete", OnFadeComplete)
		HAS_METHOD(Sprite, "onFadeInComplete", OnFadeInComplete)
		HAS_METHOD(Sprite, "onFadeOutComplete", OnFadeOutComplete)
		HAS_METHOD(Sprite, "onMouseEnter", OnMouseEnter)
		HAS_METHOD(Sprite, "onMouseLeave", OnMouseLeave)
		HAS_METHOD(Sprite, "onMouseDown", OnMouseDown)
		HAS_METHOD(Sprite, "onMouseUp", OnMouseUp)
		HAS_METHOD(Sprite, "onMouseClick", OnMouseClick)
    );
	END
EMITTER_BASE_CLASS_IMPL(Sprite)
ANIMATED_BASE_CLASS_IMPL(Sprite)
SERIALIZABLE_BASE_CLASS_IMPL(Sprite)
GETTER_IMPL(Sprite, WantsAnimLoopEvents, BOOL)
GETTER_IMPL(Sprite, WantsAnimEndEvents, BOOL)
GETTER_IMPL(Sprite, WantsCollideWallEvents, BOOL)
%#ifndef PDG_NO_GUI  CR
  GETTER_IMPL(Sprite, WantsMouseOverEvents, BOOL)
  GETTER_IMPL(Sprite, WantsClickEvents, BOOL)
  GETTER_IMPL(Sprite, MouseDetectMode, INTEGER)
  GETTER_IMPL(Sprite, WantsOffscreenEvents, BOOL)
%#endif  CR // !PDG_NO_GUI
METHOD_IMPL(Sprite, GetFrameRotatedBounds)
	METHOD_SIGNATURE("", [object RotatedRect], 0, ([number int] frameNum = -1));
    OPTIONAL_INT32_ARG(1, frameNum, -1);
    pdg::RotatedRect r = self->getFrameRotatedBounds(frameNum);
	RETURN( RECT2VAL(r) );
	END
METHOD_IMPL(Sprite, SetFrame)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] frame));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, frame);
	self->setFrame(frame);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetCurrentFrame)
	METHOD_SIGNATURE("which frame of animation the sprite is currently showing", 
		number, 0, ());
    REQUIRE_ARG_COUNT(0);
	int frame = self->getCurrentFrame();
	RETURN_INTEGER(frame);
	END
METHOD_IMPL(Sprite, GetFrameCount)
	METHOD_SIGNATURE("total number of frames of animation for this sprite", 
		number, 0, ());
    REQUIRE_ARG_COUNT(0);
	int count = self->getFrameCount();
	RETURN_INTEGER(count);
	END
METHOD_IMPL(Sprite, StartFrameAnimation)
	METHOD_SIGNATURE("", undefined, 4, (number fps, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames, [number int] animateFlags = animate_Looping));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_NUMBER_ARG(1, fps);
    OPTIONAL_INT32_ARG(2, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(3, numFrames, Sprite::all_Frames);
    OPTIONAL_INT32_ARG(4, animateFlags, Sprite::animate_Looping);
	self->startFrameAnimation(fps, startingFrame, numFrames, animateFlags);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, StopFrameAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
	self->stopFrameAnimation();
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetWantsAnimLoopEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsAnimLoopEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsAnimEndEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsAnimEndEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsCollideWallEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsCollideWallEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, AddFramesImage)
	METHOD_SIGNATURE("", undefined, 3, ([object Image] image, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, image, Image);
    OPTIONAL_INT32_ARG(2, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(3, numFrames, Sprite::all_Frames);
	self->addFramesImage(image, startingFrame, numFrames);
	NO_RETURN;
	END
%#ifdef PDG_SPRITER_SUPPORT
METHOD_IMPL(Sprite, HasAnimation)
	METHOD_SIGNATURE("", boolean, 1, ({ [number int] animationId | string animationName }) );
	REQUIRE_ARG_COUNT(1);
	bool hasIt = false;
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		hasIt = self->hasAnimation(animationName);
	} else {
		REQUIRE_UINT32_ARG(1, animationId);
		hasIt = self->hasAnimation(animationId);
	}
	RETURN_BOOL(hasIt);
	END
METHOD_IMPL(Sprite, StartAnimation)
	METHOD_SIGNATURE("", undefined, 1, ({ [number int] animationId | string animationName }) );
	REQUIRE_ARG_COUNT(1);
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		self->startAnimation(animationName);
	} else {
		REQUIRE_UINT32_ARG(1, animationId);
		self->startAnimation(animationId);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetEntityScale)
	METHOD_SIGNATURE("", [object Sprite], 1, (number xScale, number yScale) );
	REQUIRE_ARG_COUNT(2);
	REQUIRE_NUMBER_ARG(1, xScale);
	REQUIRE_NUMBER_ARG(2, yScale);
	self->setEntityScale(xScale, yScale);
	RETURN_THIS;
	END

METHOD_IMPL(Sprite, ApplyCharacterMap)
	METHOD_SIGNATURE("", undefined, 1, (string mapName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, mapName);
	self->applyCharacterMap(mapName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, RemoveCharacterMap)
	METHOD_SIGNATURE("", undefined, 1, (string mapName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, mapName);
	self->removeCharacterMap(mapName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, RemoveAllCharacterMaps)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->removeAllCharacterMaps();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, GetAppliedCharacterMaps)
	METHOD_SIGNATURE("", [object Array], 0, ());
	REQUIRE_ARG_COUNT(0);
	std::vector<std::string> maps = self->getAppliedCharacterMaps();
	// Convert std::vector<std::string> to JavaScript array
	v8::Local<v8::Array> arr = v8::Array::New(isolate);
	for (size_t i = 0; i < maps.size(); i++) {
		arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i), 
			v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked()).ToChecked();
	}
	RETURN(arr);
	END

METHOD_IMPL(Sprite, EnableSpriterEvents)
	METHOD_SIGNATURE("", undefined, 1, (boolean enable = true));
	OPTIONAL_BOOL_ARG(1, enable, true);
	self->enableSpriterEvents(enable);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, AreSpriterEventsEnabled)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool enabled = self->areSpriterEventsEnabled();
	RETURN_BOOL(enabled);
	END

METHOD_IMPL(Sprite, BlendToAnimation)
	METHOD_SIGNATURE("", undefined, 2, ({ [number int] animationId | string animationName }, number blendTime));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_NUMBER_ARG(2, blendTime);
	if (VALUE_IS_STRING(ARGV[0])) {
		REQUIRE_STRING_ARG(1, animationName);
		self->blendToAnimation(animationName, blendTime);
	} else {
		REQUIRE_UINT32_ARG(1, animationId);
		self->blendToAnimation(animationId, blendTime);
	}
	NO_RETURN;
	END

METHOD_IMPL(Sprite, IsBlending)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool blending = self->isBlending();
	RETURN_BOOL(blending);
	END

METHOD_IMPL(Sprite, GetBlendProgress)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	float progress = self->getBlendProgress();
	RETURN_NUMBER(progress);
	END

METHOD_IMPL(Sprite, PauseAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->pauseAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, ResumeAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->resumeAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, StopAnimation)
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	self->stopAnimation();
	NO_RETURN;
	END

METHOD_IMPL(Sprite, IsAnimationPlaying)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool playing = self->isAnimationPlaying();
	RETURN_BOOL(playing);
	END

METHOD_IMPL(Sprite, IsAnimationPaused)
	METHOD_SIGNATURE("", boolean, 0, ());
	REQUIRE_ARG_COUNT(0);
	bool paused = self->isAnimationPaused();
	RETURN_BOOL(paused);
	END

METHOD_IMPL(Sprite, GetAnimationProgress)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	float progress = self->getAnimationProgress();
	RETURN_NUMBER(progress);
	END

METHOD_IMPL(Sprite, HasAttachPoint)
	METHOD_SIGNATURE("", boolean, 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	bool hasPoint = self->hasAttachPoint(attachPointName);
	RETURN_BOOL(hasPoint);
	END

METHOD_IMPL(Sprite, GetAttachPoint)
	METHOD_SIGNATURE("", [object Offset], 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	pdg::Offset offset = self->getAttachPoint(attachPointName);
	RETURN_OFFSET(offset);
	END

METHOD_IMPL(Sprite, AttachSprite)
	METHOD_SIGNATURE("", undefined, 2, ([object Sprite] sprite, string attachPointName));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	REQUIRE_STRING_ARG(2, attachPointName);
	self->attachSprite(sprite, attachPointName);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, DetachSprite)
	METHOD_SIGNATURE("", undefined, 1, ([object Sprite] sprite));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->detachSprite(sprite);
	NO_RETURN;
	END

METHOD_IMPL(Sprite, GetAttachedSprite)
	METHOD_SIGNATURE("", [object Sprite], 1, (string attachPointName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, attachPointName);
	pdg::Sprite* attached = self->getAttachedSprite(attachPointName);
	if (attached) {
		RETURN_NEW_CPP_OBJECT(attached, Sprite);
	} else {
		RETURN_NULL;
	}
	END

METHOD_IMPL(Sprite, ActivateSubEntity)
	METHOD_SIGNATURE("", undefined, 2, (string entityName, string animationName = "idle"));
	REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_STRING_ARG(1, entityName);
	OPTIONAL_STRING_ARG(2, animationName, "idle");
	self->activateSubEntity(entityName, animationName);
	NO_RETURN;
	END

%#endif
%#ifndef PDG_NO_GUI
METHOD_IMPL(Sprite, SetWantsOffscreenEvents)
	METHOD_SIGNATURE("", [object Sprite], 0, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsOffscreenEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetDrawHelper)
	METHOD_SIGNATURE("", undefined, 1, ([object ISpriteDrawHelper] helper));
	OBJECT_SAVE(self->mSpriteScriptObj, THIS);
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISpriteDrawHelper)	
    self->setDrawHelper(helper);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetPostDrawHelper)
	METHOD_SIGNATURE("", undefined, 1, ([object ISpriteDrawHelper] helper));
	OBJECT_SAVE(self->mSpriteScriptObj, THIS);
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISpriteDrawHelper)	
    self->setPostDrawHelper(helper);
	NO_RETURN;
	END
%#endif // !PDG_NO_GUI
METHOD_IMPL(Sprite, ChangeFramesImage)
	METHOD_SIGNATURE("", undefined, 2, ([object Image] oldImage, [object Image] newImage));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, oldImage, Image);
    REQUIRE_CPP_OBJECT_ARG(2, newImage, Image);
	self->changeFramesImage(oldImage, newImage);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, OffsetFrameCenters)
	METHOD_SIGNATURE("", undefined, 5, ([number int] offsetX, [number int] offsetY, [object Image] image = null, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, offsetX);
    REQUIRE_INT32_ARG(2, offsetY);
    OPTIONAL_CPP_OBJECT_ARG(3, image, Image, 0);
    OPTIONAL_INT32_ARG(4, startingFrame, Sprite::start_FromFirstFrame);
    OPTIONAL_INT32_ARG(5, numFrames, Sprite::all_Frames);
	self->offsetFrameCenters(offsetX, offsetY, image, startingFrame, numFrames);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, GetFrameCenterOffset)
	METHOD_SIGNATURE("", [object Offset], 2, ([object Image] image = null, [number int] frameNum = 0));
    OPTIONAL_CPP_OBJECT_ARG(1, image, Image, 0);
    OPTIONAL_INT32_ARG(2, frameNum, 0);
	pdg::Offset offset = self->getFrameCenterOffset(image, frameNum);
	RETURN_OFFSET(offset);
	END
METHOD_IMPL(Sprite, SetOpacity)
	METHOD_SIGNATURE("", [object Sprite], 1, (number opacity));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, opacity);
	self->setOpacity(opacity);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetOpacity)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	float opacity = self->getOpacity();
	RETURN_NUMBER(opacity);
	END
METHOD_IMPL(Sprite, FadeTo)
	METHOD_SIGNATURE("", undefined, 3, (number targetOpacity, [number int] msDuration, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_NUMBER_ARG(1, targetOpacity);
	REQUIRE_INT32_ARG(2, msDuration);
	OPTIONAL_INT32_ARG(3, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeTo(targetOpacity, msDuration, gEasingFunctions[easing]);
    } else {
		self->fadeTo(targetOpacity, msDuration);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, FadeIn)
	METHOD_SIGNATURE("", undefined, 2, ([number int] msDuration, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_INT32_ARG(1, msDuration);
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeIn(msDuration, gEasingFunctions[easing]);
    } else {
		self->fadeIn(msDuration);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, FadeOut)
	METHOD_SIGNATURE("", undefined, 2, ([number int] msDuration, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_INT32_ARG(1, msDuration);
	OPTIONAL_INT32_ARG(2, easing, EasingFuncRef::linearTween);
   	if (easing >= 0 && easing < NUM_EASING_FUNCTIONS) {
    	self->fadeOut(msDuration, gEasingFunctions[easing]);
    } else {
		self->fadeOut(msDuration);
	}
	NO_RETURN;
	END
METHOD_IMPL(Sprite, IsBehind)
	METHOD_SIGNATURE("", boolean, 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	bool behind = self->isBehind(sprite);
	RETURN_BOOL(behind);
	END
METHOD_IMPL(Sprite, GetZOrder)
	METHOD_SIGNATURE("", [number int], 0, ());
    REQUIRE_ARG_COUNT(0);
	int zorder = self->getZOrder();
	RETURN_INTEGER(zorder);
	END
METHOD_IMPL(Sprite, MoveBehind)
	METHOD_SIGNATURE("", [object Sprite], 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->moveBehind(sprite);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveInFrontOf)
	METHOD_SIGNATURE("", [object Sprite], 1, ([object Sprite] sprite));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
	self->moveInFrontOf(sprite);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveToFront)
	METHOD_SIGNATURE("put this sprite in front of all others in its layer", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
	self->moveToFront();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, MoveToBack)
	METHOD_SIGNATURE("put this sprite behind all others in its layer", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
	self->moveToBack();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, EnableCollisions)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] collisionType = collide_AlphaChannel));
    OPTIONAL_INT32_ARG(1, collisionType, Sprite::collide_AlphaChannel);
	self->enableCollisions(collisionType);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, DisableCollisions)
	METHOD_SIGNATURE("", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0);
	self->disableCollisions();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetCollisionType)
	METHOD_SIGNATURE("get the current collision type", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	int collisionType = self->getCollisionType();
	RETURN_INTEGER(collisionType);
	END
METHOD_IMPL(Sprite, SetCollisionRadius)
	METHOD_SIGNATURE("", [object Sprite], 1, (number pixelRadius));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, pixelRadius);
	self->setCollisionRadius(pixelRadius);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetCollisionRadius)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	float radius = self->getCollisionRadius();
	RETURN_NUMBER(radius);
	END
METHOD_IMPL(Sprite, UseCollisionMask)
	METHOD_SIGNATURE("", undefined, 2, ([object Image] frameImage, [object Image] maskImage));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, frameImage, Image);
    REQUIRE_CPP_OBJECT_ARG(2, maskImage, Image);
	self->useCollisionMask(frameImage, maskImage);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetCollisionHelper)
	METHOD_SIGNATURE("", undefined, 1, ([object ISpriteCollideHelper] helper));
	OBJECT_SAVE(self->mSpriteScriptObj, THIS);
    DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISpriteCollideHelper);
    REQUIRE_ARG_COUNT(1);
	REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, ISpriteCollideHelper);
	self->setCollisionHelper(helper);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, SetElasticity)
	METHOD_SIGNATURE("", [object Sprite], 1, (number elasticity));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, elasticity);
	self->setElasticity(elasticity);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetElasticity)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	float elasticity = self->getElasticity();
	RETURN_NUMBER(elasticity);
	END
%#ifndef PDG_NO_GUI
METHOD_IMPL(Sprite, SetWantsMouseOverEvents)
	METHOD_SIGNATURE("", [object Sprite], 1, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsMouseOverEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetWantsClickEvents)
	METHOD_SIGNATURE("", [object Sprite], 1, (boolean wantsThem = true));
    OPTIONAL_BOOL_ARG(1, wantsThem, true);
	self->setWantsClickEvents(wantsThem);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, SetMouseDetectMode)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] collisionType = collide_BoundingBox));
    OPTIONAL_INT32_ARG(1, collisionType, Sprite::collide_BoundingBox);
	self->setMouseDetectMode(collisionType);
	RETURN_THIS;
	END
%#endif // !PDG_NO_GUI
METHOD_IMPL(Sprite, GetLayer)
	METHOD_SIGNATURE("get the layer that contains this sprite", [object SpriteLayer], 0, ());
    REQUIRE_ARG_COUNT(0);
	SpriteLayer* layer = self->getLayer();
	RETURN_CPP_OBJECT(layer, SpriteLayer);
	END
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
METHOD_IMPL(Sprite, MakeStatic)
	METHOD_SIGNATURE("", [object Sprite], 0, ());
	REQUIRE_ARG_COUNT(0);
	self->makeStatic();
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetFriction)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	float friction = self->getFriction();
	RETURN_NUMBER(friction);
	END
METHOD_IMPL(Sprite, SetCollideGroup)
	METHOD_SIGNATURE("", [object Sprite], 1, ([number int] group));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, group);
	self->setCollideGroup(group);
	RETURN_THIS;
	END
METHOD_IMPL(Sprite, GetCollideGroup)
	METHOD_SIGNATURE("", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	long group = self->getCollideGroup();
	RETURN_INTEGER(group);
	END
METHOD_IMPL(Sprite, PinJoint)
	METHOD_SIGNATURE("", [object CpConstraint], 4, ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(3);
	REQUIRE_OFFSET_ARG(1, anchor);
	REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
	REQUIRE_OFFSET_ARG(3, otherAnchor);
	OPTIONAL_NUMBER_ARG(4, breakingForce, 0.0f);
	cpConstraint* joint = self->pinJoint(anchor, otherSprite, otherAnchor, breakingForce);
	cpConstraintSetUserData(joint, (void*)sPinJointStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, SlideJoint)
	METHOD_SIGNATURE("", [object CpConstraint], 6, ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number minDist, number maxDist, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(5);
	REQUIRE_OFFSET_ARG(1, anchor);
	REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
	REQUIRE_OFFSET_ARG(3, otherAnchor);
	REQUIRE_NUMBER_ARG(4, minDist);
	REQUIRE_NUMBER_ARG(5, maxDist);
	OPTIONAL_NUMBER_ARG(6, breakingForce, 0.0f);
	cpConstraint* joint = self->slideJoint(anchor, otherSprite, otherAnchor, minDist, maxDist, breakingForce);
	cpConstraintSetUserData(joint, (void*)sSlideJointStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, PivotJoint)
	METHOD_SIGNATURE("", [object CpConstraint], 3, ([object Sprite] otherSprite, [object Point] pivot, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_POINT_ARG(2, pivot);
	OPTIONAL_NUMBER_ARG(3, breakingForce, 0.0f);
	cpConstraint* joint = self->pivotJoint(otherSprite, pivot, breakingForce);
	cpConstraintSetUserData(joint, (void*)sPivotJointStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, GrooveJoint)
	METHOD_SIGNATURE("", [object CpConstraint], 5, ([object Offset] grooveStart, [object Offset] grooveEnd, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(4);
	REQUIRE_OFFSET_ARG(1, grooveStart);
	REQUIRE_OFFSET_ARG(2, grooveEnd);
	REQUIRE_CPP_OBJECT_ARG(3, otherSprite, Sprite);
	REQUIRE_OFFSET_ARG(4, otherAnchor);
	OPTIONAL_NUMBER_ARG(5, breakingForce, 0.0f);
	cpConstraint* joint = self->grooveJoint(grooveStart, grooveEnd, otherSprite, otherAnchor, breakingForce);
	cpConstraintSetUserData(joint, (void*)sGrooveJointStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, SpringJoint)
	METHOD_SIGNATURE("", [object CpConstraint], 7, ([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number restLength, number stiffness, number damping, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(6);
	REQUIRE_OFFSET_ARG(1, anchor);
	REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
	REQUIRE_OFFSET_ARG(3, otherAnchor);
	REQUIRE_NUMBER_ARG(4, restLength);
	REQUIRE_NUMBER_ARG(5, stiffness);
	REQUIRE_NUMBER_ARG(6, damping);
	OPTIONAL_NUMBER_ARG(7, breakingForce, 0.0f);
	cpConstraint* joint = self->springJoint(anchor, otherSprite, otherAnchor, restLength, stiffness, damping, breakingForce);
	cpConstraintSetUserData(joint, (void*)sSpringJointStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, RotarySpring)
	METHOD_SIGNATURE("", [object CpConstraint], 5, ([object Sprite] otherSprite, number restAngle, number stiffness, number damping, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(4);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_NUMBER_ARG(2, restAngle);
	REQUIRE_NUMBER_ARG(3, stiffness);
	REQUIRE_NUMBER_ARG(4, damping);
	OPTIONAL_NUMBER_ARG(5, breakingForce, 0.0f);
	cpConstraint* joint = self->rotarySpring(otherSprite, restAngle, stiffness, damping, breakingForce);
	cpConstraintSetUserData(joint, (void*)sRotarySpringStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, RotaryLimit)
	METHOD_SIGNATURE("", [object CpConstraint], 4, ([object Sprite] otherSprite, number minAngle, number maxAngle, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(3);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_NUMBER_ARG(2, minAngle);
	REQUIRE_NUMBER_ARG(3, maxAngle);
	OPTIONAL_NUMBER_ARG(4, breakingForce, 0.0f);
	cpConstraint* joint = self->rotaryLimit(otherSprite, minAngle, maxAngle, breakingForce);
	cpConstraintSetUserData(joint, (void*)sRotaryLimitStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, Ratchet)
	METHOD_SIGNATURE("", [object CpConstraint], 4, ([object Sprite] otherSprite, number rachetInterval, number phase, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_NUMBER_ARG(2, rachetInterval);
	OPTIONAL_NUMBER_ARG(3, phase, 0.0f);
	OPTIONAL_NUMBER_ARG(4, breakingForce, 0.0f);
	cpConstraint* joint = self->ratchet(otherSprite, rachetInterval, phase, breakingForce);
	cpConstraintSetUserData(joint, (void*)sRatchetStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, Gear)
	METHOD_SIGNATURE("", [object CpConstraint], 4, ([object Sprite] otherSprite, number gearRatio, number initialAngle = 0, number breakingForce = 0));
	REQUIRE_ARG_MIN_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_NUMBER_ARG(2, gearRatio);
	OPTIONAL_NUMBER_ARG(3, initialAngle, 0.0f);
	OPTIONAL_NUMBER_ARG(4, breakingForce, 0.0f);
	cpConstraint* joint = self->gear(otherSprite, gearRatio, initialAngle, breakingForce);
	cpConstraintSetUserData(joint, (void*)sGearStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, Motor)
	METHOD_SIGNATURE("", [object CpConstraint], 3, ([object Sprite] otherSprite, number spin, number maxTorque = INFINITY));
	REQUIRE_ARG_MIN_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
	REQUIRE_NUMBER_ARG(2, spin);
	OPTIONAL_NUMBER_ARG(3, maxTorque, std::numeric_limits<float>::infinity());
	cpConstraint* joint = self->motor(otherSprite, spin, maxTorque);
	cpConstraintSetUserData(joint, (void*)sMotorStr);
	RETURN_NEW_CPP_OBJECT(joint, cpConstraint);  // has no mcpConstraintScriptObj member
	END
METHOD_IMPL(Sprite, RemoveJoint)
	METHOD_SIGNATURE("", undefined, 1, ([object CpConstraint] joint));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
	self->removeJoint(joint);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, Disconnect)
	METHOD_SIGNATURE("", undefined, 0, ([object Sprite] otherSprite = ALL_SPRITES));
	OPTIONAL_CPP_OBJECT_ARG(1, otherSprite, Sprite, 0);
	self->disconnect(otherSprite);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, MakeJointBreakable)
	METHOD_SIGNATURE("", undefined, 2, ([object CpConstraint] joint, number breakingForce));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
	REQUIRE_NUMBER_ARG(2, breakingForce);
	self->makeJointBreakable(joint, breakingForce);
	NO_RETURN;
	END
METHOD_IMPL(Sprite, MakeJointUnbreakable)
	METHOD_SIGNATURE("", undefined, 1, ([object CpConstraint] joint));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
	self->makeJointUnbreakable(joint);
	NO_RETURN;
	END
%#endif
METHOD_IMPL(Sprite, On)
	METHOD_SIGNATURE("", [object IEventHandler], 2, ([number int] eventCode, function func));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_INT32_ARG(1, eventCode);
	REQUIRE_FUNCTION_ARG(2, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	long evtCode;
	if (eventCode <= pdg::Sprite::action_CollideWall) {
		evtCode = pdg::eventType_SpriteCollide;
	} else if (eventCode <= pdg::Sprite::action_FadeOutComplete) {
		evtCode = pdg::eventType_SpriteAnimate;
	} else {
		evtCode = pdg::eventType_SpriteTouch;
	}
	self->addHandler(handler, evtCode);	
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

// Sprite convenience event methods
METHOD_IMPL(Sprite, OnCollideSprite)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) {
		DEBUG_ONLY( OS::_DOUT("OnCollideSprite: failed to create handler"); )
		RETURN_NULL;
	}
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnCollideWall)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnOffscreen)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnOnscreen)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnExitLayer)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationLoop)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationEnd)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnAnimationBlendComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationBlendComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeInComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnFadeOutComplete)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseEnter)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseLeave)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseDown)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseUp)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(Sprite, OnMouseClick)
	METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

%#ifdef PDG_SPRITER_SUPPORT
METHOD_IMPL(Sprite, GetSpriterCollisionBox)
	METHOD_SIGNATURE("get a Spriter collision box by name", [object RotatedRect], 1, (string boxName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, boxName);
	pdg::RotatedRect rect = self->getSpriterCollisionBox(boxName);
	RETURN( RECT2VAL(rect) );
	END

METHOD_IMPL(Sprite, IsSpriterCollisionActive)
	METHOD_SIGNATURE("check if a Spriter collision box is active", boolean, 1, (string boxName));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, boxName);
	bool active = self->isSpriterCollisionActive(boxName);
	RETURN_BOOL(active);
	END

METHOD_IMPL(Sprite, GetSpriterCollisionBoxCount)
	METHOD_SIGNATURE("get the number of active Spriter collision boxes", number, 0, ());
	REQUIRE_ARG_COUNT(0);
	int count = self->getSpriterCollisionBoxCount();
	RETURN_INTEGER(count);
	END

METHOD_IMPL(Sprite, GetSpriterCollisionBoxName)
	METHOD_SIGNATURE("get the name of a Spriter collision box by index", string, 1, (number index));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, index);
	const char* name = self->getSpriterCollisionBoxName(index);
	if (name) {
		RETURN_STRING(name);
	} else {
		RETURN_NULL;
	}
	END


%#endif // PDG_SPRITER_SUPPORT

CLEANUP_IMPL(Sprite)

CPP_MANAGED_CONSTRUCTOR_IMPL(Sprite)
	return new Sprite();
	END


} // pdg namespace
