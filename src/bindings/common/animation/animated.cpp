// -----------------------------------------------
// animated.cpp
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
%#include "pdg/sys/animationrecorder.h"
%#include "../../common/animation/particle_trail_options.h"

namespace pdg {

// ========================================================================================
//MARK: Custom Easing Functions
// ========================================================================================

#define SETUP_CUSTOM_EASING(n) CR \
  float customEasing##n(double ut, float b, float c, double ud) {	CR \
	return CallScriptEasingFunc(n, ut, b, c, ud);					    CR \
  }

SETUP_CUSTOM_EASING(0)
SETUP_CUSTOM_EASING(1)
SETUP_CUSTOM_EASING(2)
SETUP_CUSTOM_EASING(3)
SETUP_CUSTOM_EASING(4)
SETUP_CUSTOM_EASING(5)
SETUP_CUSTOM_EASING(6)
SETUP_CUSTOM_EASING(7)
SETUP_CUSTOM_EASING(8)
SETUP_CUSTOM_EASING(9)

// EasingFunc gEasingFunctions[NUM_EASING_FUNCTIONS] = {
// 	EASING_FUNC_LIST
// };
//
// int gNumCustomEasings = 0;

// ========================================================================================
//MARK: IAnimationHelper
//MARK: AnimatedBase
// ========================================================================================


%#ifdef PDG_USING_JAVASCRIPT_CORE
static void AnimatedBase_finalize(JSObjectRef object) {
    auto* value=static_cast<AnimatedBase*>(JSObjectGetPrivate(object));
    if(value) { value->mAnimatedScriptObj=nullptr; value->release(); }
    JSObjectSetPrivate(object,nullptr);
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(AnimatedBase,
  OBJECT_SAVE_WEAK(cppObj->mAnimatedScriptObj, obj); cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("Animated", AnimatedBase, AnimatedBase_finalize, , ,
		HAS_ANIMATED_METHODS(AnimatedBase)
		HAS_METHOD(AnimatedBase, "animate", Animate)
    );
	END

ANIMATED_BASE_CLASS_IMPL(AnimatedBase)
METHOD_IMPL(AnimatedBase, Animate)
    OBJECT_SAVE_WEAK(self->mAnimatedScriptObj, THIS);
	METHOD_SIGNATURE("", boolean, 1, (number deltaSeconds));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, deltaSeconds);
	try {
        bool result = self->animate(deltaSeconds);
        RETURN_BOOL(result);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
	END

CLEANUP_IMPL(AnimatedBase)

%#ifdef PDG_USING_JAVASCRIPT_CORE
CPP_UNMANAGED_CONSTRUCTOR_IMPL(AnimatedBase, )
%#else
AnimatedBaseWrap::AnimatedBaseWrap(SCRIPT_ARGS) : cppPtr_(New_AnimatedBase(args)) {}
AnimatedBaseWrap::~AnimatedBaseWrap() { if(cppPtr_) { cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
AnimatedBase* New_AnimatedBase(SCRIPT_ARGS) {
    if(s_AnimatedBase_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate();
%#endif
    auto* value=new AnimatedBase();
    %#ifdef PDG_USING_V8
    value->addRef(); OBJECT_SAVE_WEAK(value->mAnimatedScriptObj,THIS);
    %#endif
    return value;
	END

%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Troupe_finalize(JSObjectRef object) {
    auto* value=static_cast<Troupe*>(JSObjectGetPrivate(object));
    if(value) { value->mAnimatedScriptObj=nullptr; value->release(); }
    JSObjectSetPrivate(object,nullptr);
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Troupe, OBJECT_SAVE_WEAK(cppObj->mAnimatedScriptObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Troupe", Troupe, AnimatedBase, Troupe_finalize, , ,
        HAS_ANIMATED_METHODS(Troupe)
        HAS_METHOD(Troupe, "_recordAnimationCommand", RecordCommand)
        HAS_METHOD(Troupe, "animate", Animate)
        HAS_METHOD(Troupe, "add", Add)
        HAS_METHOD(Troupe, "remove", Remove)
        HAS_METHOD(Troupe, "clear", Clear)
        HAS_METHOD(Troupe, "contains", Contains)
        HAS_METHOD(Troupe, "getMemberCount", GetMemberCount)
    );
    END
%#ifdef PDG_USING_JAVASCRIPT_CORE
CPP_UNMANAGED_CONSTRUCTOR_IMPL(Troupe, )
%#else
TroupeWrap::TroupeWrap(SCRIPT_ARGS) : cppPtr_(New_Troupe(args)) {}
TroupeWrap::~TroupeWrap() { if(cppPtr_) { cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
Troupe* New_Troupe(SCRIPT_ARGS) {
    if(s_Troupe_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate();
%#endif
    SETUP_NON_SCRIPT_CALL;
    if(ARGC) { SAVE_TYPE_ERR("Troupe accepts no constructor arguments"); return nullptr; }
    auto* value=new Troupe();
    %#ifdef PDG_USING_V8
    value->addRef(); OBJECT_SAVE_WEAK(value->mAnimatedScriptObj,THIS);
    %#endif
    return value;
    END
ANIMATED_BASE_CLASS_IMPL(Troupe)
METHOD_IMPL(Troupe, RecordCommand)
#include "animation_recorder_body.inc"
END
METHOD_IMPL(Troupe, Animate)
    OBJECT_SAVE_WEAK(self->mAnimatedScriptObj, THIS);
    METHOD_SIGNATURE("Advance the collective animation clock in seconds.", boolean, 1, (number deltaSeconds));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, deltaSeconds);
    try { RETURN_BOOL(self->animate(deltaSeconds)); }
    catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Troupe, Add)
    METHOD_SIGNATURE("Add a borrowed animation target or nested Troupe.", [this], 1, ([object Animated&] member));
    REQUIRE_ARG_COUNT(1);
%#ifdef PDG_USING_V8
    auto* member=V8_GetAnimationTarget(isolate,ARGV[0]);
%#else
    auto* member=JSC_GetAnimationTarget(ctx,ARGV[0]);
%#endif
    if(!member) { THROW_TYPE_ERR("Expected an Animated target"); RETURN_NULL; }
    try { self->add(*member); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Troupe, Remove)
    METHOD_SIGNATURE("Remove a direct member from the collection.", [this], 1, ([object Animated&] member));
    REQUIRE_ARG_COUNT(1);
%#ifdef PDG_USING_V8
    auto* member=V8_GetAnimationTarget(isolate,ARGV[0]);
%#else
    auto* member=JSC_GetAnimationTarget(ctx,ARGV[0]);
%#endif
    if(!member) { THROW_TYPE_ERR("Expected an Animated target"); RETURN_NULL; }
    try { self->remove(*member); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Troupe, Clear)
    METHOD_SIGNATURE("Remove every direct member.", [this], 0, ());
    REQUIRE_ARG_COUNT(0);
    try { self->clear(); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END
METHOD_IMPL(Troupe, Contains)
    METHOD_SIGNATURE("Test direct or nested membership.", boolean, 1, ([object Animated const&] member));
    REQUIRE_ARG_COUNT(1);
%#ifdef PDG_USING_V8
    auto* member=V8_GetAnimationTarget(isolate,ARGV[0]);
%#else
    auto* member=JSC_GetAnimationTarget(ctx,ARGV[0]);
%#endif
    if(!member) { THROW_TYPE_ERR("Expected an Animated target"); RETURN_NULL; }
    RETURN_BOOL(self->contains(*member));
    END
METHOD_IMPL(Troupe, GetMemberCount)
    METHOD_SIGNATURE("Return the number of live direct members.", [number int], 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_UINT32(self->getMemberCount());
    END
CLEANUP_IMPL(Troupe)

} // namespace pdg

/* @pdg-schema
{
  "name": "AnimationContactState",
  "value": {
    "kind": "record",
    "description": "An independent contact position and influence sample.",
    "fields": {
      "x": {
        "type": "number",
        "description": "Horizontal position in owning-layer coordinates."
      },
      "y": {
        "type": "number",
        "description": "Vertical position in owning-layer coordinates."
      },
      "influence": {
        "type": "number",
        "description": "Remaining influence, from zero to one."
      },
      "locked": {
        "type": "boolean",
        "description": "Whether the target currently holds a contact lock."
      }
    }
  }
}
*/

/* @pdg-member
{
  "name": "Animated.Animated",
  "type": "constructor",
  "params": [],
  "returns": "object Animated",
  "brief": "Create a Animated instance."
}
*/

// @pdg-class {"name":"Animated","native_binding":{"ownership":"owned","browser":{"base":null,"generate":true,"constructors":[{"types":[]}],"support_bindings":[{"name":"_addBrowserAnimationHelper","symbol":"pdg::browserAddHelper"},{"name":"_removeBrowserAnimationHelper","symbol":"pdg::browserRemoveHelper"},{"name":"getMyClassTag","symbol":"pdg::AnimatedBase::getMyClassTag"},{"name":"_animationIdentity","symbol":"pdg::browserAnimationIdentity"},{"name":"_moveToTimed","symbol":"pdg::AnimatedBase::moveTo","signature":"pdg::AnimatedBase&(const pdg::Point&, double, pdg::EasingFunc)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_moveByTimed","symbol":"pdg::AnimatedBase::moveBy","signature":"pdg::AnimatedBase&(const pdg::Offset&, double, pdg::EasingFunc)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_growTimed","symbol":"pdg::AnimatedBase::grow","signature":"pdg::AnimatedBase&(float, double, pdg::EasingFunc)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_rotateToTimed","symbol":"pdg::AnimatedBase::rotateTo","signature":"pdg::AnimatedBase&(float, double, pdg::EasingFunc, int)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_rotateByTimed","symbol":"pdg::AnimatedBase::rotateBy","signature":"pdg::AnimatedBase&(float, double, pdg::EasingFunc, int)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_stretchTimed","symbol":"pdg::AnimatedBase::stretch","signature":"pdg::AnimatedBase&(float, float, double, pdg::EasingFunc)","return_policy":"reference","browser":{"exceptions":"javascript"}},{"name":"_resizeByTimed","symbol":"pdg::AnimatedBase::resizeBy","signature":"pdg::AnimatedBase&(float, float, double, pdg::EasingFunc)","return_policy":"reference","browser":{"exceptions":"javascript"}}],"defaults":{"exceptions":"javascript"}}}}

// @pdg-member {"name":"Animated.setLocation","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Point&)"}}

// @pdg-member {"name":"Animated.setSize","native_binding":{"signature":"pdg::AnimatedBase&(float, float)"}}

// @pdg-member {"name":"Animated.setMovement","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Vector&)"}}

// @pdg-member {"name":"Animated.setScale","native_binding":{"signature":"pdg::AnimatedBase&(float, float)"}}

// @pdg-member {"name":"Animated.moveTo","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Point&)"}}

// @pdg-member {"name":"Animated.moveBy","native_binding":{"signature":"pdg::AnimatedBase&(const pdg::Offset&)"}}

// @pdg-member {"name":"Animated.resizeBy","native_binding":{"signature":"pdg::AnimatedBase&(float, float)"}}

// @pdg-member {"name":"Animated.grow","native_binding":{"signature":"pdg::AnimatedBase&(float)"}}

// @pdg-member {"name":"Animated.stretch","native_binding":{"signature":"pdg::AnimatedBase&(float, float)"}}

// @pdg-member {"name":"Animated.rotateTo","native_binding":{"signature":"pdg::AnimatedBase&(float)"}}

// @pdg-member {"name":"Animated.rotateBy","native_binding":{"signature":"pdg::AnimatedBase&(float)"}}

// @pdg-member {"name":"Animated.addAnimationHelper","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"Animated.removeAnimationHelper","native_binding":{"browser":{"generate":false}}}

// @pdg-schema {"name":"EasingFunction","value":{"kind":"alias","value":{"type":"number int"},"description":"A PDG easing constant identifying a built-in easing function.","native_binding":{"type":"pdg::EasingFunc","browser":{"argument":"native"}}}}

// @pdg-class {"name":"Troupe","native_binding":{"ownership":"retained","browser":{"base":"pdg::AnimatedBase","generate":true,"constructors":[{"types":[]}],"defaults":{"exceptions":"javascript"}}}}
// @pdg-member {"name":"Troupe.Troupe","type":"constructor","params":[],"returns":"object Troupe","brief":"Create an empty animation collection."}
