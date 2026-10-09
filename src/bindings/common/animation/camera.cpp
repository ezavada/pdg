// -----------------------------------------------
// camera.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "animation_impl_macros.h"
#include "../core/core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include <cmath>
%#include <limits>

namespace pdg {

%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Camera_finalize(JSObjectRef object) {
    auto* value=static_cast<Camera*>(JSObjectGetPrivate(object)); if (!value) return;
    value->mCameraScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mEventEmitterScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr); value->release();
}
%#define CAMERA_SAVE(cppObj,obj) cppObj->mCameraScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mEventEmitterScriptObj=obj
%#else
%#define CAMERA_SAVE(cppObj,obj) cppObj->mCameraScriptObj.Reset(isolate,obj); cppObj->mCameraScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mEventEmitterScriptObj.Reset(isolate,obj); cppObj->mEventEmitterScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Camera, CAMERA_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Camera", Camera, AnimatedBase, Camera_finalize, , ,
        HAS_ANIMATED_METHODS(Camera)
        HAS_EMITTER_METHODS(Camera)
        HAS_PROPERTY(Camera, Zoom)
        HAS_PROPERTY(Camera, PixelSnapping)
        HAS_METHOD(Camera, "zoom", Zoom)
        HAS_METHOD(Camera, "zoomTo", ZoomTo)
        HAS_METHOD(Camera, "animate", Animate)
        HAS_METHOD(Camera, "follow", Follow)
        HAS_METHOD(Camera, "stopFollowing", StopFollowing)
        HAS_METHOD(Camera, "isFollowing", IsFollowing)
        HAS_METHOD(Camera, "setSmoothing", SetSmoothing)
        HAS_METHOD(Camera, "getSmoothing", GetSmoothing)
        HAS_METHOD(Camera, "setLookAhead", SetLookAhead)
        HAS_METHOD(Camera, "getLookAhead", GetLookAhead)
        HAS_METHOD(Camera, "setDeadzone", SetDeadzone)
        HAS_METHOD(Camera, "getDeadzone", GetDeadzone)
        HAS_METHOD(Camera, "setFollowOffset", SetFollowOffset)
        HAS_METHOD(Camera, "getFollowOffset", GetFollowOffset)
        HAS_METHOD(Camera, "setViewBounds", SetViewBounds)
        HAS_METHOD(Camera, "clearViewBounds", ClearViewBounds)
        HAS_METHOD(Camera, "hasViewBounds", HasViewBounds)
        HAS_METHOD(Camera, "getViewBounds", GetViewBounds)
        HAS_METHOD(Camera, "setViewport", SetViewport)
        HAS_METHOD(Camera, "getViewport", GetViewport)
        HAS_METHOD(Camera, "worldToView", WorldToView)
        HAS_METHOD(Camera, "viewToWorld", ViewToWorld)
        HAS_METHOD(Camera, "getEffects", GetEffects)
        HAS_METHOD(Camera, "flash", Flash)
        HAS_METHOD(Camera, "getFlashOpacity", GetFlashOpacity)
        HAS_METHOD(Camera, "show", Show)
        HAS_METHOD(Camera, "hide", Hide)
        HAS_METHOD(Camera, "isHidden", IsHidden)
        HAS_METHOD(Camera, "setOpacity", SetOpacity)
        HAS_METHOD(Camera, "getOpacity", GetOpacity)
        HAS_METHOD(Camera, "fadeTo", FadeTo)
        HAS_METHOD(Camera, "fadeIn", FadeIn)
        HAS_METHOD(Camera, "fadeOut", FadeOut)
        HAS_METHOD(Camera, "cutTo", CutTo)
        HAS_METHOD(Camera, "matchCutTo", MatchCutTo)
        HAS_METHOD(Camera, "matchFadeTo", MatchFadeTo)
        HAS_METHOD(Camera, "transitionTo", TransitionTo)
        HAS_METHOD(Camera, "lumaFadeTo", LumaFadeTo)
        HAS_METHOD(Camera, "whipPanTo", WhipPanTo)
    );
    END
ANIMATED_BASE_CLASS_IMPL(Camera)
EMITTER_BASE_CLASS_IMPL(Camera)
GETTER_IMPL(Camera, Zoom, NUMBER)
METHOD_IMPL(Camera, SetZoom)
    METHOD_SIGNATURE("Set view magnification immediately.", [this], 1, (number zoom));
    try { REQUIRE_NUMBER_ARG(1, zoom); self->setZoom(zoom); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
GETTER_IMPL(Camera, PixelSnapping, BOOL)
METHOD_IMPL(Camera, SetPixelSnapping)
    METHOD_SIGNATURE("Round final view translation without rounding persistent camera pose.", [this], 0, (boolean snap = true));
    OPTIONAL_BOOL_ARG(1, snap, true); self->setPixelSnapping(snap); RETURN_THIS;
    END
METHOD_IMPL(Camera, ZoomTo)
    METHOD_SIGNATURE("Animate view magnification.", [this], 3, (number zoom, number seconds, [number int] easing = easeInOutQuad));
    try { REQUIRE_NUMBER_ARG(1, zoom); REQUIRE_NUMBER_ARG(2, seconds); OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad));
        if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; }
        const int easing=static_cast<int>(easingValue);
        if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
        self->zoomTo(zoom,seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Camera, Zoom)
    METHOD_SIGNATURE("Animate magnification by a positive multiplier.", [this], 3, (number factor, number seconds, [number int] easing = easeInOutQuad));
    try { REQUIRE_NUMBER_ARG(1, factor); REQUIRE_NUMBER_ARG(2, seconds); OPTIONAL_NUMBER_ARG(3, easingValue, static_cast<int>(EasingFuncRef::easeInOutQuad));
        if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS) { THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL; }
        const int easing=static_cast<int>(easingValue);
        if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
        self->zoom(factor,seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Camera, Animate)
    METHOD_SIGNATURE("", boolean, 1, (number seconds));
    try { REQUIRE_NUMBER_ARG(1, seconds); RETURN_BOOL(self->animate(seconds)); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
%#ifdef PDG_USING_JAVASCRIPT_CORE
Camera* New_Camera(SCRIPT_ARGS) { return new Camera(); }
%#else
CameraWrap::CameraWrap(SCRIPT_ARGS) : cppPtr_(New_Camera(args)) {}
CameraWrap::~CameraWrap() { if (cppPtr_) { cppPtr_->mCameraScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
Camera* New_Camera(SCRIPT_ARGS) {
    if (s_Camera_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate(); auto* cppObj=new Camera(); cppObj->addRef();
    CAMERA_SAVE(cppObj,args.This()); return cppObj;
}
%#endif
%#undef CAMERA_SAVE
METHOD_IMPL(Camera, Follow)
    METHOD_SIGNATURE("Follow an Animated target in world coordinates.", [this], 1, ([object Animated&] target));
    try {
        REQUIRE_ARG_COUNT(1);AnimatedBase* target=nullptr;
        if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0],Sprite)) {EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],value,Sprite);target=value;}
        else if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0],Camera)) {EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],value,Camera);target=value;}
        else if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0],Particle)) {EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],value,Particle);target=value;}
        else if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0],ParticleEmitter)) {EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],value,ParticleEmitter);target=value;}
        else if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0],AnimatedBase)) {EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(ARGV[0],value,AnimatedBase);target=value;}
        if (!target) throw std::invalid_argument("Expected an Animated target");
        self->follow(*target);RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, StopFollowing)
    METHOD_SIGNATURE("Release the following controller and retain the current pose.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->stopFollowing(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, ClearViewBounds)
    METHOD_SIGNATURE("Disable visible-world bounds.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearViewBounds(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, IsFollowing)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isFollowing()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, HasViewBounds)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasViewBounds()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetSmoothing)
    METHOD_SIGNATURE("Set the following smoothing time constant.", [this], 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); self->setSmoothing(seconds); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetSmoothing)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSmoothing()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetLookAhead)
    METHOD_SIGNATURE("Set velocity-based following prediction.", [this], 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); self->setLookAhead(seconds); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetLookAhead)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getLookAhead()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetDeadzone)
    METHOD_SIGNATURE("Set the following deadzone relative to camera focus.", [this], 1, ([object Rect const&] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); self->setDeadzone(bounds); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetDeadzone)
    METHOD_SIGNATURE("", [object Rect], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto value=self->getDeadzone(); RETURN_RECT(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetViewBounds)
    METHOD_SIGNATURE("Constrain the visible world footprint for each viewport.", [this], 1, ([object Rect const&] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); self->setViewBounds(bounds); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetViewBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto value=self->getViewBounds(); RETURN_RECT(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetFollowOffset)
    METHOD_SIGNATURE("Offset the world-space point tracked by following.", [this], 1, ([object Offset const&] offset));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_OFFSET_ARG(1,offset); self->setFollowOffset(offset); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetFollowOffset)
    METHOD_SIGNATURE("", [object Offset], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto value=self->getFollowOffset(); RETURN_OFFSET(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, SetViewport)
    METHOD_SIGNATURE("Set this Camera's destination rectangle within its Port.", [this], 1, ([object Rect const&] viewport));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,viewport); self->setViewport(viewport); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetViewport)
    METHOD_SIGNATURE("", [object Rect], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto value=self->getViewport(); RETURN_RECT(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, WorldToView)
    METHOD_SIGNATURE("", [object Point], 1, ([object Point const&] point));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_POINT_ARG(1,point); auto value=self->worldToView(point); RETURN_POINT(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, ViewToWorld)
    METHOD_SIGNATURE("", [object Point], 1, ([object Point const&] point));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_POINT_ARG(1,point); auto value=self->viewToWorld(point); RETURN_POINT(value); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetEffects)
    METHOD_SIGNATURE("", [object Camera&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* effects=&self->getEffects(); RETURN_CPP_OBJECT(effects, Camera); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetFlashOpacity)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getFlashOpacity()); } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, Flash)
    METHOD_SIGNATURE("Flash white at the requested opacity, then fade to zero.", [this], 2, (number opacity, number seconds, [number int] easing = easeOutQuad));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>3) { REQUIRE_ARG_COUNT(3); } REQUIRE_NUMBER_ARG(1,opacity); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_INT32_ARG(3,easing,easingFuncToId(easeOutQuad));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid flash easing");
        self->flash(opacity,seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, Show)
    METHOD_SIGNATURE("Show this camera's composed scene.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->show(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, Hide)
    METHOD_SIGNATURE("Hide output and picking without stopping animation.", [this], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->hide(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, IsHidden)
    METHOD_SIGNATURE("", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isHidden());
END
METHOD_IMPL(Camera, SetOpacity)
    METHOD_SIGNATURE("Set composed output opacity without changing sprite opacity.", [this], 1, (number opacity));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,opacity); self->setOpacity(opacity); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, GetOpacity)
    METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getOpacity());
END
METHOD_IMPL(Camera, FadeTo)
    METHOD_SIGNATURE("Animate composed output opacity.", [this], 2, (number opacity, number seconds, [number int] easing = linearTween));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>3) {REQUIRE_ARG_COUNT(3);} REQUIRE_NUMBER_ARG(1,opacity); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_INT32_ARG(3,easing,easingFuncToId(linearTween));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
        self->fadeTo(opacity,seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, FadeIn)
    METHOD_SIGNATURE("Fade composed output to full opacity.", [this], 1, (number seconds, [number int] easing = linearTween));
    try { REQUIRE_ARG_MIN_COUNT(1); if (ARGC>2) {REQUIRE_ARG_COUNT(2);} REQUIRE_NUMBER_ARG(1,seconds); OPTIONAL_INT32_ARG(2,easing,easingFuncToId(linearTween));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
        self->fadeIn(seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, FadeOut)
    METHOD_SIGNATURE("Fade composed output to zero opacity.", [this], 1, (number seconds, [number int] easing = linearTween));
    try { REQUIRE_ARG_MIN_COUNT(1); if (ARGC>2) {REQUIRE_ARG_COUNT(2);} REQUIRE_NUMBER_ARG(1,seconds); OPTIONAL_INT32_ARG(2,easing,easingFuncToId(linearTween));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
        self->fadeOut(seconds,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, CutTo)
    METHOD_SIGNATURE("Schedule an atomic camera visibility and picking handoff.", [this], 1, ([object Camera&] destination));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); if (!destination) throw std::invalid_argument("Expected destination Camera"); self->cutTo(*destination); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
DECLARE_SYMBOL(matchSource);
DECLARE_SYMBOL(matchTarget);
DECLARE_SYMBOL(mode);
DECLARE_SYMBOL(approachSeconds);
DECLARE_SYMBOL(settleSeconds);
DECLARE_SYMBOL(settleReturnsCamera);
DECLARE_SYMBOL(approachEasing);
DECLARE_SYMBOL(settleEasing);
DECLARE_SYMBOL(fadeSeconds);
DECLARE_SYMBOL(fadeEasing);
METHOD_IMPL(Camera, MatchCutTo)
    METHOD_SIGNATURE("Align Sprites and preserve apparent motion across a camera cut.", [this], 2, ([object Camera&] destination, object options));
    try {
        REQUIRE_ARG_COUNT(2);
        if (!VALUE_IS_OBJECT_OF_CLASS(ARGV[0],Camera)) throw std::invalid_argument("Expected destination Camera");
        REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); REQUIRE_OBJECT_ARG(2,options);
        auto read=[&](auto key) {
            auto value=OBJECT_GET_PROPERTY(options,key);
            %#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) throw std::invalid_argument("Unable to read matching option");
            %#else
            if (value.IsEmpty()) throw std::invalid_argument("Unable to read matching option");
            %#endif
            return value;
        };
        if (!destination) throw std::invalid_argument("Expected destination Camera");
        CameraMatchOptions settings;
        auto sourceValue=read(SYMBOL(matchSource));
        auto targetValue=read(SYMBOL(matchTarget));
        if (!VALUE_IS_OBJECT_OF_CLASS(sourceValue,Sprite) || !VALUE_IS_OBJECT_OF_CLASS(targetValue,Sprite))
            throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
        EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(sourceValue,source,Sprite);
        EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(targetValue,target,Sprite);
        if (!source || !target) throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
        settings.matchSource=source;settings.matchTarget=target;
        auto mode=read(SYMBOL(mode));
        if (!VALUE_IS_UNDEFINED(mode)) {
            if (!VALUE_IS_NUMBER(mode)) throw std::invalid_argument("Expected camera match mode");
            const double id=VAL2NUM(mode);
            if (!std::isfinite(id) || std::floor(id)!=id || id<static_cast<int>(matchSource) || id>static_cast<int>(matchTargetAndSize))
                throw std::invalid_argument("Invalid camera match mode");
            settings.mode=static_cast<CameraMatchMode>(static_cast<int>(id));
        }
        auto approach=read(SYMBOL(approachSeconds));
        if (!VALUE_IS_UNDEFINED(approach)) {if (!VALUE_IS_NUMBER(approach)) throw std::invalid_argument("Expected numeric approachSeconds");settings.approachSeconds=VAL2NUM(approach);}
        auto settle=read(SYMBOL(settleSeconds));
        if (!VALUE_IS_UNDEFINED(settle)) {if (!VALUE_IS_NUMBER(settle)) throw std::invalid_argument("Expected numeric settleSeconds");settings.settleSeconds=VAL2NUM(settle);}
        auto restore=read(SYMBOL(settleReturnsCamera));
        if (!VALUE_IS_UNDEFINED(restore)) {if (!VALUE_IS_BOOL(restore)) throw std::invalid_argument("Expected boolean settleReturnsCamera");settings.settleReturnsCamera=VAL2BOOL(restore);}
        auto approachEase=read(SYMBOL(approachEasing));
        if (!VALUE_IS_UNDEFINED(approachEase)) {
            if (!VALUE_IS_NUMBER(approachEase)) throw std::invalid_argument("Invalid approachEasing");
            const double id=VAL2NUM(approachEase);
            if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid approachEasing");
            settings.approachEasing=gEasingFunctions[static_cast<int>(id)];
        }
        auto settleEase=read(SYMBOL(settleEasing));
        if (!VALUE_IS_UNDEFINED(settleEase)) {
            if (!VALUE_IS_NUMBER(settleEase)) throw std::invalid_argument("Invalid settleEasing");
            const double id=VAL2NUM(settleEase);
            if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid settleEasing");
            settings.settleEasing=gEasingFunctions[static_cast<int>(id)];
        }
        self->matchCutTo(*destination,settings);RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, MatchFadeTo)
    METHOD_SIGNATURE("Align Sprites and preserve apparent motion through a synchronized camera fade.", [this], 2, ([object Camera&] destination, object options));
    try {
        REQUIRE_ARG_COUNT(2);
        if (!VALUE_IS_OBJECT_OF_CLASS(ARGV[0],Camera)) throw std::invalid_argument("Expected destination Camera");
        REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); REQUIRE_OBJECT_ARG(2,options);
        auto read=[&](auto key) {
            auto value=OBJECT_GET_PROPERTY(options,key);
            %#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!value || (exception && *exception)) throw std::invalid_argument("Unable to read matching option");
            %#else
            if (value.IsEmpty()) throw std::invalid_argument("Unable to read matching option");
            %#endif
            return value;
        };
        if (!destination) throw std::invalid_argument("Expected destination Camera");
        CameraMatchOptions settings;
        auto sourceValue=read(SYMBOL(matchSource));
        auto targetValue=read(SYMBOL(matchTarget));
        if (!VALUE_IS_OBJECT_OF_CLASS(sourceValue,Sprite) || !VALUE_IS_OBJECT_OF_CLASS(targetValue,Sprite))
            throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
        EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(sourceValue,source,Sprite);
        EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(targetValue,target,Sprite);
        if (!source || !target) throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
        settings.matchSource=source;settings.matchTarget=target;
        auto mode=read(SYMBOL(mode));
        if (!VALUE_IS_UNDEFINED(mode)) {
            if (!VALUE_IS_NUMBER(mode)) throw std::invalid_argument("Expected camera match mode");
            const double id=VAL2NUM(mode);
            if (!std::isfinite(id) || std::floor(id)!=id || id<static_cast<int>(matchSource) || id>static_cast<int>(matchTargetAndSize))
                throw std::invalid_argument("Invalid camera match mode");
            settings.mode=static_cast<CameraMatchMode>(static_cast<int>(id));
        }
        auto approach=read(SYMBOL(approachSeconds));
        if (!VALUE_IS_UNDEFINED(approach)) {if (!VALUE_IS_NUMBER(approach)) throw std::invalid_argument("Expected numeric approachSeconds");settings.approachSeconds=VAL2NUM(approach);}
        auto settle=read(SYMBOL(settleSeconds));
        if (!VALUE_IS_UNDEFINED(settle)) {if (!VALUE_IS_NUMBER(settle)) throw std::invalid_argument("Expected numeric settleSeconds");settings.settleSeconds=VAL2NUM(settle);}
        auto restore=read(SYMBOL(settleReturnsCamera));
        if (!VALUE_IS_UNDEFINED(restore)) {if (!VALUE_IS_BOOL(restore)) throw std::invalid_argument("Expected boolean settleReturnsCamera");settings.settleReturnsCamera=VAL2BOOL(restore);}
        auto approachEase=read(SYMBOL(approachEasing));
        if (!VALUE_IS_UNDEFINED(approachEase)) {
            if (!VALUE_IS_NUMBER(approachEase)) throw std::invalid_argument("Invalid approachEasing");
            const double id=VAL2NUM(approachEase);
            if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid approachEasing");
            settings.approachEasing=gEasingFunctions[static_cast<int>(id)];
        }
        auto settleEase=read(SYMBOL(settleEasing));
        if (!VALUE_IS_UNDEFINED(settleEase)) {
            if (!VALUE_IS_NUMBER(settleEase)) throw std::invalid_argument("Invalid settleEasing");
            const double id=VAL2NUM(settleEase);
            if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid settleEasing");
            settings.settleEasing=gEasingFunctions[static_cast<int>(id)];
        }
        auto fade=read(SYMBOL(fadeSeconds));
        if (!VALUE_IS_UNDEFINED(fade)) {if (!VALUE_IS_NUMBER(fade)) throw std::invalid_argument("Expected numeric fadeSeconds");settings.fadeSeconds=VAL2NUM(fade);}
        auto fadeEase=read(SYMBOL(fadeEasing));
        if (!VALUE_IS_UNDEFINED(fadeEase)) {
            if (!VALUE_IS_NUMBER(fadeEase)) throw std::invalid_argument("Invalid fadeEasing");
            const double id=VAL2NUM(fadeEase);
            if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid fadeEasing");
            settings.fadeEasing=gEasingFunctions[static_cast<int>(id)];
        }
        self->matchFadeTo(*destination,settings);RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, TransitionTo)
    METHOD_SIGNATURE("Transition between live camera scenes sharing a Port and viewport.", [this], 2, ([object Camera&] destination, number seconds, [number int] style = camera_Crossfade, [number int] easing = easeInOutQuad));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>4) {REQUIRE_ARG_COUNT(4);} REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_INT32_ARG(3,style,camera_Crossfade); OPTIONAL_INT32_ARG(4,easing,easingFuncToId(easeInOutQuad));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid transition easing");
        self->transitionTo(*destination,seconds,style,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, LumaFadeTo)
    METHOD_SIGNATURE("Reveal a live destination using a frozen luminance mask.", [this], 2, ([object Camera&] destination, number seconds, [object Image*] mask = null, number softness = 0.1, boolean darkFirst = false, [number int] easing = easeInOutQuad));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>6) {REQUIRE_ARG_COUNT(6);} REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); REQUIRE_NUMBER_ARG(2,seconds);
        Image* mask=nullptr; if (ARGC>2 && !VALUE_IS_NULL(ARGV[2]) && !VALUE_IS_UNDEFINED(ARGV[2])) {REQUIRE_CPP_OBJECT_ARG(3,value,Image);mask=value;}
        OPTIONAL_NUMBER_ARG(4,softness,.1); OPTIONAL_BOOL_ARG(5,darkFirst,false); OPTIONAL_INT32_ARG(6,easing,easingFuncToId(easeInOutQuad));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid luma easing");
        self->lumaFadeTo(*destination,seconds,mask,softness,darkFirst,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END
METHOD_IMPL(Camera, WhipPanTo)
    METHOD_SIGNATURE("Slide live camera outputs with optional directional blur.", [this], 2, ([object Camera&] destination, number seconds, [number int] style = camera_WhipLeft, number blur = 0, [number int] easing = easeInOutQuad));
    try { REQUIRE_ARG_MIN_COUNT(2); if (ARGC>5) {REQUIRE_ARG_COUNT(5);} REQUIRE_CPP_OBJECT_ARG(1,destination,Camera); REQUIRE_NUMBER_ARG(2,seconds);
        OPTIONAL_INT32_ARG(3,style,camera_WhipLeft); OPTIONAL_NUMBER_ARG(4,blur,0); OPTIONAL_INT32_ARG(5,easing,easingFuncToId(easeInOutQuad));
        if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid whip easing");
        self->whipPanTo(*destination,seconds,style,blur,gEasingFunctions[easing]); RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END

} // namespace pdg

// @pdg-member {"name":"Camera.Camera","type":"constructor","native":true,"brief":"create an animated camera with an identity view","returns":"object Camera","params":[]}

/* @pdg-contract
{
  "name": "Camera.matchCutTo",
  "value": {
    "params": {
      "options": {
        "schema": "CameraMatchCutOptions"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "CameraMatchCutOptions",
  "value": {
    "kind": "record",
    "fields": {
      "matchSource": {
        "type": "object Sprite"
      },
      "matchTarget": {
        "type": "object Sprite"
      },
      "mode": {
        "type": "number",
        "optional": true
      },
      "approachSeconds": {
        "type": "number",
        "optional": true
      },
      "settleSeconds": {
        "type": "number",
        "optional": true
      },
      "approachEasing": {
        "type": "number",
        "optional": true
      },
      "settleEasing": {
        "type": "number",
        "optional": true
      },
      "settleReturnsCamera": {
        "type": "boolean",
        "optional": true
      }
    }
  }
}
*/

/* @pdg-contract
{"name":"Camera.matchFadeTo","value":{"params":{"options":{"schema":"CameraMatchFadeOptions"}}}}
*/
/* @pdg-schema
{"name":"CameraMatchFadeOptions","value":{"kind":"record","extends":["CameraMatchCutOptions"],"fields":{"fadeSeconds":{"type":"number","optional":true},"fadeEasing":{"type":"number","optional":true}}}}
*/
