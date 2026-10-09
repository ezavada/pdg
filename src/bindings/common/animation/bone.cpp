// -----------------------------------------------
// bone.cpp
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

%#ifdef PDG_SPRITER_SUPPORT
namespace pdg {

// A wrapper owns one native reference, independently of the Sprite reference.
// Native caches are weak, so they neither pin wrappers nor keep inactive Bones alive.

%#ifdef PDG_USING_JAVASCRIPT_CORE
Bone* New_Bone(SCRIPT_ARGS) { return nullptr; }
static void Bone_finalize(JSObjectRef object) {
    auto* bone = static_cast<Bone*>(JSObjectGetPrivate(object));
    if (!bone) return;
    bone->mBoneScriptObj = nullptr;
    bone->mAnimatedScriptObj = nullptr;
    JSObjectSetPrivate(object, nullptr);
    bone->release();
}
%#define BONE_SAVE_WEAK(cppObj, obj) cppObj->mBoneScriptObj = obj; cppObj->mAnimatedScriptObj = obj
%#else
%#define BONE_SAVE_WEAK(cppObj, obj) cppObj->mBoneScriptObj.Reset(isolate,obj); cppObj->mBoneScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak()
BoneWrap::BoneWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
BoneWrap::~BoneWrap() {
    if (cppPtr_) {
        cppPtr_->mBoneScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset();
        cppPtr_->release(); cppPtr_ = nullptr;
    }
}
%#endif

WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(Bone, "Sprite.getBone",
    BONE_SAVE_WEAK(cppObj, obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Bone", Bone, AnimatedBase, Bone_finalize, , ,
        HAS_ANIMATED_METHODS(Bone)
        HAS_METHOD(Bone, "diminish", DiminishInfluence)
        HAS_METHOD(Bone, "animate", Animate)
        HAS_METHOD(Bone, "getId", GetId)
        HAS_METHOD(Bone, "getName", GetName)
        HAS_METHOD(Bone, "getSprite", GetSprite)
        HAS_METHOD(Bone, "isAttached", IsAttached)
        HAS_METHOD(Bone, "getInfluence", GetInfluence)
        HAS_METHOD(Bone, "setIKLimits", SetIKLimits)
        HAS_METHOD(Bone, "clearIKLimits", ClearIKLimits)
        HAS_METHOD(Bone, "hasIKLimits", HasIKLimits)
        HAS_METHOD(Bone, "getIKMinAngle", GetIKMinAngle)
        HAS_METHOD(Bone, "getIKMaxAngle", GetIKMaxAngle)
    );
    END
%#undef BONE_SAVE_WEAK

ANIMATED_BASE_CLASS_IMPL(Bone)
METHOD_IMPL(Bone, Animate)
    METHOD_SIGNATURE("Advance bone controls in seconds; Sprite updates owned bones automatically.", boolean, 1, (number seconds));
    REQUIRE_ARG_COUNT(1);REQUIRE_NUMBER_ARG(1,seconds);
    try { RETURN_BOOL(self->animate(seconds)); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, DiminishInfluence)
    METHOD_SIGNATURE("Ease scripted bone influence back toward the running animation.", [this], 2, (number influence, number seconds, [number int] easing = linearTween));
    REQUIRE_NUMBER_ARG(1,influence);REQUIRE_NUMBER_ARG(2,seconds);OPTIONAL_INT32_ARG(3,easing,static_cast<int>(EasingFuncRef::linearTween));
    if(easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->diminish(influence,seconds,gEasingFunctions[easing]);RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetId)
    METHOD_SIGNATURE("", [number uint], 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_UINT32(self->getId()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetName)
    METHOD_SIGNATURE("", string, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_STRING(self->getName().c_str()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetSprite)
    METHOD_SIGNATURE("Read the owning Sprite.", [object Sprite*], 0, ()); REQUIRE_ARG_COUNT(0);
    try { auto* sprite=self->getSprite();RETURN_CPP_OBJECT(sprite,Sprite); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, IsAttached)
    METHOD_SIGNATURE("", boolean, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_BOOL(self->isAttached()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetInfluence)
    METHOD_SIGNATURE("", number, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_NUMBER(self->getInfluence()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, ClearIKLimits)
    METHOD_SIGNATURE("", [this], 0, ()); REQUIRE_ARG_COUNT(0);
    try { self->clearIKLimits(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, HasIKLimits)
    METHOD_SIGNATURE("", boolean, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_BOOL(self->hasIKLimits()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetIKMinAngle)
    METHOD_SIGNATURE("", number, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_NUMBER(self->getIKMinAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, GetIKMaxAngle)
    METHOD_SIGNATURE("", number, 0, ()); REQUIRE_ARG_COUNT(0);
    try { RETURN_NUMBER(self->getIKMaxAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Bone, SetIKLimits)
    METHOD_SIGNATURE("Share a live physical rotary limit with this IK joint.", [this], 1, ({ number minAngle, number maxAngle | [object PhysicsConstraint&] constraint }));
    try {
        if (ARGC==1) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsObjectOfClass(ctx,ARGV[0],PhysicsConstraint_class())) { THROW_TYPE_ERR("Expected a PhysicsConstraint"); RETURN_NULL; }
%#else
            if (!PhysicsConstraintWrap::GetTemplate(isolate)->HasInstance(ARGV[0])) { THROW_TYPE_ERR("Expected a PhysicsConstraint"); RETURN_NULL; }
%#endif
            REQUIRE_CPP_OBJECT_ARG(1,constraint,PhysicsConstraint); self->setIKLimits(*constraint);
        } else { REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,lo); REQUIRE_NUMBER_ARG(2,hi); self->setIKLimits(lo,hi); }
        RETURN_THIS;
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
}
// @pdg-class {"name":"Bone","construction":{"kind":"factory","factory":"Sprite.getBone"},"native_binding":{"ownership":"retained","browser":{"generate":true,"base":"AnimatedBase","guard":"PDG_SPRITER_SUPPORT"}}}
// @pdg-member {"name":"Bone.setIKLimits","native_binding":{"adapter":"Bone.setIKLimits"}}

%#endif // PDG_SPRITER_SUPPORT
