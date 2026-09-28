// -----------------------------------------------
// animated.cpp
//
// Implementation file for AnimatedBase bindings
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
// ========================================================================================

// The wrapper owns a reference independently of each AnimatedBase registration.
// Its callback is a JS property so inactive wrapper/callback cycles can be collected.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void IAnimationHelper_finalize(JSObjectRef object) {
    auto* helper = static_cast<IAnimationHelper*>(JSObjectGetPrivate(object));
    if (!helper) return;
    helper->mIAnimationHelperScriptObj = nullptr;
    JSObjectSetPrivate(object, nullptr);
    helper->release();
}
%#else
IAnimationHelper* New_IAnimationHelper(SCRIPT_ARGS);
IAnimationHelperWrap::IAnimationHelperWrap(SCRIPT_ARGS) : cppPtr_(New_IAnimationHelper(args)) {}
IAnimationHelperWrap::~IAnimationHelperWrap() {
    if (cppPtr_) {
        cppPtr_->mIAnimationHelperScriptObj.Reset();
        cppPtr_->release();
    }
}
%#endif
BINDING_INITIALIZER_IMPL_REFCOUNTED(IAnimationHelper,
    OBJECT_SAVE_WEAK(cppObj->mIAnimationHelperScriptObj, obj); cppObj->addRef();
    if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject())
    EXPORT_FINALIZED_CLASS_SYMBOLS("IAnimationHelper", IAnimationHelper, IAnimationHelper_finalize, , , );
	END

CLEANUP_IMPL(IAnimationHelper)


// ========================================================================================
//MARK: AnimatedBase
// ========================================================================================


WRAPPER_INITIALIZER_IMPL_CUSTOM(AnimatedBase,
  OBJECT_SAVE(cppObj->mAnimatedScriptObj, obj) )
    EXPORT_CLASS_SYMBOLS("Animated", AnimatedBase, , ,
		HAS_ANIMATED_METHODS(AnimatedBase)
		HAS_METHOD(AnimatedBase, "animate", Animate)
    );
	END

ANIMATED_BASE_CLASS_IMPL(AnimatedBase)
METHOD_IMPL(AnimatedBase, Animate)
	METHOD_SIGNATURE("", boolean, 1, (number deltaSeconds));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, deltaSeconds);
	try {
        bool result = self->animate(deltaSeconds);
        RETURN_BOOL(result);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
	END

CLEANUP_IMPL(AnimatedBase)

CPP_MANAGED_CONSTRUCTOR_IMPL(AnimatedBase)
    return new AnimatedBase();
	END


// A wrapper owns one native reference, independently of the Sprite reference.
// Native caches are weak, so they neither pin wrappers nor keep removed Parts alive.
%#ifdef PDG_USING_JAVASCRIPT_CORE
Part* New_Part(SCRIPT_ARGS) { return nullptr; }
static void Part_finalize(JSObjectRef object) {
    auto* part = static_cast<Part*>(JSObjectGetPrivate(object));
    if (!part) return;
    part->mPartScriptObj = nullptr;
    part->mAnimatedScriptObj = nullptr;
    JSObjectSetPrivate(object, nullptr);
    part->release();
}
%#define PART_SAVE_WEAK(cppObj, obj) cppObj->mPartScriptObj = obj; cppObj->mAnimatedScriptObj = obj
%#else
%#define PART_SAVE_WEAK(cppObj, obj) cppObj->mPartScriptObj.Reset(isolate,obj); cppObj->mPartScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak()
PartWrap::PartWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
PartWrap::~PartWrap() {
    if (cppPtr_) {
        cppPtr_->mPartScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset();
        cppPtr_->release(); cppPtr_ = nullptr;
    }
}
%#endif

WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(Part, "Sprite.createPart",
    PART_SAVE_WEAK(cppObj, obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Part", Part, AnimatedBase, Part_finalize, , ,
        HAS_ANIMATED_METHODS(Part)
        HAS_METHOD(Part, "_readCollider", ReadCollider)
        HAS_METHOD(Part, "setupCollider", SetupCollider)
        HAS_METHOD(Part, "setupFrameCollider", SetupFrameCollider)
        HAS_METHOD(Part, "setupAnimationCollider", SetupAnimationCollider)
        HAS_METHOD(Part, "removeCollider", RemoveCollider)
        HAS_METHOD(Part, "_readPhysics", ReadPhysics)
        HAS_METHOD(Part, "setupPhysicsBody", SetupPhysicsBody)
        HAS_METHOD(Part, "removePhysicsBody", RemovePhysicsBody)

        HAS_METHOD(Part, "animate", Animate)
        HAS_METHOD(Part, "getId", GetId)
        HAS_METHOD(Part, "getName", GetName)
        HAS_METHOD(Part, "getSprite", GetSprite)
        HAS_METHOD(Part, "isAttached", IsAttached)
        HAS_METHOD(Part, "getBoneId", GetBoneId)
        HAS_METHOD(Part, "isBoundToBone", IsBoundToBone)
        HAS_METHOD(Part, "bindToBone", BindToBone)
        HAS_METHOD(Part, "unbindFromBone", UnbindFromBone)
        HAS_METHOD(Part, "getParentPart", GetParentPart)
        HAS_METHOD(Part, "setParentPart", SetParentPart)
        HAS_METHOD(Part, "solveIK", SolveIK)
        HAS_METHOD(Part, "setIKTarget", SetIKTarget)
        HAS_METHOD(Part, "clearIKTarget", ClearIKTarget)
        HAS_METHOD(Part, "hasIKTarget", HasIKTarget)
        HAS_METHOD(Part, "isIKTargetReached", IsIKTargetReached)
        HAS_METHOD(Part, "getIKError", GetIKError)
        HAS_METHOD(Part, "setIKLimits", SetIKLimits)
        HAS_METHOD(Part, "clearIKLimits", ClearIKLimits)
        HAS_METHOD(Part, "hasIKLimits", HasIKLimits)
        HAS_METHOD(Part, "getIKMinAngle", GetIKMinAngle)
        HAS_METHOD(Part, "getIKMaxAngle", GetIKMaxAngle)
        HAS_METHOD(Part, "setIKDriveTarget", SetIKDriveTarget)
        HAS_METHOD(Part, "isIKDriven", IsIKDriven)
        HAS_METHOD(Part, "attachSprite", AttachSprite)
        HAS_METHOD(Part, "getAttachedSprite", GetAttachedSprite)
        HAS_METHOD(Part, "detachSprite", DetachSprite)
        HAS_METHOD(Part, "getAttachmentError", GetAttachmentError)
        HAS_METHOD(Part, "getTransform", GetTransform)
        HAS_METHOD(Part, "bindToAnimationBinding", BindToAnimationBinding)
        HAS_METHOD(Part, "bindToAnimationSocket", BindToAnimationSocket)
        HAS_METHOD(Part, "getAnimationBindingName", GetAnimationBindingName)
        HAS_METHOD(Part, "getAnimationSocketName", GetAnimationSocketName)
        HAS_METHOD(Part, "clearContent", ClearContent)
        HAS_METHOD(Part, "hasContent", HasContent)
        HAS_METHOD(Part, "getContentBounds", GetContentBounds)
%#ifndef PDG_NO_GUI CR
        HAS_METHOD(Part, "setDrawing", SetDrawing)
        HAS_METHOD(Part, "setImage", SetImage)
%#endif CR
    );
    END
%#undef PART_SAVE_WEAK

ANIMATED_BASE_CLASS_IMPL(Part)
METHOD_IMPL(Part, Animate)
    METHOD_SIGNATURE("advance local programming in seconds; owned Parts already step with their Sprite", boolean, 1, (number deltaSeconds));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, deltaSeconds);
    try { RETURN_BOOL(self->animate(deltaSeconds)); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetId)
    METHOD_SIGNATURE("stable per-Sprite Part ID", [number uint], 0, ()); REQUIRE_ARG_COUNT(0);
    RETURN_UINT32(self->getId());
    END
METHOD_IMPL(Part, GetName)
    METHOD_SIGNATURE("", string, 0, ()); REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getName().c_str());
    END
METHOD_IMPL(Part, GetSprite)
    METHOD_SIGNATURE("owning Sprite, or null after removal", [object Sprite], 0, ()); REQUIRE_ARG_COUNT(0);
    auto* sprite = self->getSprite(); RETURN_CPP_OBJECT(sprite, Sprite);
    END
METHOD_IMPL(Part, IsAttached)
    METHOD_SIGNATURE("whether a Sprite still owns this Part", boolean, 0, ()); REQUIRE_ARG_COUNT(0);
    RETURN_BOOL(self->isAttached());
    END
METHOD_IMPL(Part, GetBoneId)
    METHOD_SIGNATURE("boneId_None when unbound, detached, or the rig has changed", [number uint], 0, ()); REQUIRE_ARG_COUNT(0);
    RETURN_UINT32(self->getBoneId());
    END
METHOD_IMPL(Part, IsBoundToBone)
    METHOD_SIGNATURE("", boolean, 0, ()); REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isBoundToBone());
    END
METHOD_IMPL(Part, BindToBone)
    METHOD_SIGNATURE("bind to an owning Sprite bone, preserving local state", [object Part], 1, ([number uint] boneId));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, boneId);
    if (!std::isfinite(boneId) || boneId < 0 || boneId > boneId_None || std::floor(boneId) != boneId) { THROW_RANGE_ERR("Expected a bone ID"); RETURN_NULL; }
    try { self->bindToBone(static_cast<BoneId>(boneId)); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, UnbindFromBone)
    METHOD_SIGNATURE("preserve local state and use the Sprite frame", [object Part], 0, ()); REQUIRE_ARG_COUNT(0);
    try { self->unbindFromBone(); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetParentPart)
    METHOD_SIGNATURE("explicit parent Part, or null", [object Part], 0, ()); REQUIRE_ARG_COUNT(0);
    auto* parent = self->getParentPart(); RETURN_CPP_OBJECT(parent, Part);
    END
METHOD_IMPL(Part, SetParentPart)
    METHOD_SIGNATURE("set parent Part, or omit to use the Sprite frame; preserve local state", [object Part], 0, ({ | [object Part] parent }));
    if (ARGC > 1) { THROW_TYPE_ERR("Expected at most one Part"); RETURN_NULL; }
    try {
        if (ARGC == 0) self->setParentPart(nullptr);
        else { REQUIRE_CPP_OBJECT_ARG(1, parent, Part); self->setParentPart(parent); }
        RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
DECLARE_SYMBOL(a); DECLARE_SYMBOL(b); DECLARE_SYMBOL(c); DECLARE_SYMBOL(d);
DECLARE_SYMBOL(tx); DECLARE_SYMBOL(ty);
METHOD_IMPL(Part, GetTransform)
    METHOD_SIGNATURE("affine snapshot with a,b,c,d,tx,ty; world means owning-layer space", object, 0, ([number int] space = partSpace_Local));
    OPTIONAL_NUMBER_ARG(1, space, 0.0);
    if (!std::isfinite(space) || space < 0 || space > 2 || std::floor(space) != space) { THROW_RANGE_ERR("Expected a partSpace integer constant"); RETURN_NULL; }
    try {
        const auto transform = self->getTransform(static_cast<int>(space));
        OBJECT_REF result = OBJECT_CREATE_EMPTY(0);
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(a), NUM2VAL(transform.a));
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(b), NUM2VAL(transform.b));
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(c), NUM2VAL(transform.c));
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(d), NUM2VAL(transform.d));
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(tx), NUM2VAL(transform.tx));
        OBJECT_SET_PROPERTY_VALUE(result, SYMBOL(ty), NUM2VAL(transform.ty));
        RETURN_OBJECT(result);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

METHOD_IMPL(Part, BindToAnimationBinding)
    METHOD_SIGNATURE("authored frame in the owning Sprite's enabled rig", [object Part], 1, (string name));
    try {
        REQUIRE_ARG_COUNT(1);
        REQUIRE_STRING_ARG(1, name); self->bindToAnimationBinding(name); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, BindToAnimationSocket)
    METHOD_SIGNATURE("authored frame in the owning Sprite's enabled rig", [object Part], 1, (string name));
    try {
        REQUIRE_ARG_COUNT(1);
        REQUIRE_STRING_ARG(1, name); self->bindToAnimationSocket(name); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetAnimationBindingName)
    METHOD_SIGNATURE("authored frame in the owning Sprite's enabled rig", string, 0, ());
    try {
        REQUIRE_ARG_COUNT(0);
        RETURN_STRING(self->getAnimationBindingName().c_str());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetAnimationSocketName)
    METHOD_SIGNATURE("authored frame in the owning Sprite's enabled rig", string, 0, ());
    try {
        REQUIRE_ARG_COUNT(0);
        RETURN_STRING(self->getAnimationSocketName().c_str());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, ClearContent)
    METHOD_SIGNATURE("remove artwork without changing the Part transform or identity", [object Part], 0, ());
    REQUIRE_ARG_COUNT(0); self->clearContent(); RETURN_THIS;
    END
METHOD_IMPL(Part, HasContent)
    METHOD_SIGNATURE("whether artwork is associated with the Part", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasContent());
    END
METHOD_IMPL(Part, GetContentBounds)
    METHOD_SIGNATURE("current artwork bounds; local means artwork coordinates", [object Rect], 1, ([number int] space = partSpace_Local));
    OPTIONAL_NUMBER_ARG(1, space, 0);
    if (!std::isfinite(space) || space < 0 || space > 2 || std::floor(space) != space) { THROW_RANGE_ERR("Expected a partSpace integer constant"); RETURN_NULL; }
    try { auto bounds=self->getContentBounds(static_cast<int>(space)); RETURN(RECT2VAL(bounds)); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#ifndef PDG_NO_GUI
METHOD_IMPL(Part, SetDrawing)
    METHOD_SIGNATURE("retain shared editable Drawing content in the Part's local frame", [object Part], 1, ([object Drawing] drawing));
    REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1, drawing, Drawing);
    try { self->setDrawing(*drawing); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetImage)
    METHOD_SIGNATURE("retain an image placed in a local rectangle", [object Part], 2, ([object Image] image, [object Rect] localBounds));
    REQUIRE_ARG_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1, image, Image); REQUIRE_RECT_ARG(2, bounds);
    try { self->setImage(*image,bounds); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#endif

METHOD_IMPL(Part, SolveIK)
    METHOD_SIGNATURE("solve a contiguous Part chain without bones; returns whether the target is reached", boolean, 6, ([object Part] middle, [object Part] tip, [object Point] target, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1));
    REQUIRE_ARG_MIN_COUNT(3); REQUIRE_CPP_OBJECT_ARG(1, middle, Part); REQUIRE_CPP_OBJECT_ARG(2, tip, Part); REQUIRE_POINT_ARG(3, target);
    OPTIONAL_NUMBER_ARG(4, space, 2); OPTIONAL_NUMBER_ARG(5, bend, 1); OPTIONAL_NUMBER_ARG(6, influence, 1);
    if (!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { RETURN_BOOL(self->solveIK(middle,tip,target,static_cast<int>(space),static_cast<int>(bend),influence)); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetIKTarget)
    METHOD_SIGNATURE("keep solving this Part chain after local animation and before physics", [object Part], 6, ([object Part] middle, [object Part] tip, [object Point] target, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1));
    REQUIRE_ARG_MIN_COUNT(3); REQUIRE_CPP_OBJECT_ARG(1, middle, Part); REQUIRE_CPP_OBJECT_ARG(2, tip, Part); REQUIRE_POINT_ARG(3, target);
    OPTIONAL_NUMBER_ARG(4, space, 2); OPTIONAL_NUMBER_ARG(5, bend, 1); OPTIONAL_NUMBER_ARG(6, influence, 1);
    if (!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { self->setIKTarget(middle,tip,target,static_cast<int>(space),static_cast<int>(bend),influence); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, ClearIKTarget)
    METHOD_SIGNATURE("stop the scheduled IK controller, keeping the current pose", [object Part], 0, ());
    REQUIRE_ARG_COUNT(0); self->clearIKTarget(); RETURN_THIS;
    END
METHOD_IMPL(Part, HasIKTarget)
    METHOD_SIGNATURE("whether this Part has a scheduled IK controller", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasIKTarget());
    END
METHOD_IMPL(Part, IsIKTargetReached)
    METHOD_SIGNATURE("whether the last scheduled solve reached its target", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isIKTargetReached());
    END
METHOD_IMPL(Part, GetIKError)
    METHOD_SIGNATURE("error from the last scheduled solve, or empty on success", string, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getIKError().c_str());
    END
METHOD_IMPL(Part, SetIKLimits)
    METHOD_SIGNATURE("limit this joint's IK rotation using angles or a live rotary constraint", [object Part], 1, ({ number minAngle, number maxAngle | [object PhysicsConstraint] constraint }));
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
METHOD_IMPL(Part, ClearIKLimits)
    METHOD_SIGNATURE("remove this joint's IK rotation limits", [object Part], 0, ());
    REQUIRE_ARG_COUNT(0); self->clearIKLimits(); RETURN_THIS;
    END
METHOD_IMPL(Part, HasIKLimits)
    METHOD_SIGNATURE("whether this joint has local IK rotation limits", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasIKLimits());
    END
METHOD_IMPL(Part, GetIKMinAngle)
    METHOD_SIGNATURE("minimum local IK rotation in radians, or zero without limits", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getIKMinAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetIKMaxAngle)
    METHOD_SIGNATURE("maximum local IK rotation in radians, or zero without limits", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getIKMaxAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, IsIKDriven)
    METHOD_SIGNATURE("whether the scheduled IK controller drives physical bodies", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isIKDriven());
    END
METHOD_IMPL(Part, SetIKDriveTarget)
    METHOD_SIGNATURE("drive a Part chain toward an IK pose using bounded forces and torques", [object Part], 10, ([object Part] middle, [object Part] tip, [object Point] target, number maxForce, number maxTorque, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1, number frequency = 4, number dampingRatio = 1));
    REQUIRE_ARG_MIN_COUNT(5); REQUIRE_CPP_OBJECT_ARG(1,middle,Part); REQUIRE_CPP_OBJECT_ARG(2,tip,Part); REQUIRE_POINT_ARG(3,target);
    REQUIRE_NUMBER_ARG(4,force); REQUIRE_NUMBER_ARG(5,torque);
    OPTIONAL_NUMBER_ARG(6,space,2); OPTIONAL_NUMBER_ARG(7,bend,1); OPTIONAL_NUMBER_ARG(8,influence,1);
    OPTIONAL_NUMBER_ARG(9,frequency,4); OPTIONAL_NUMBER_ARG(10,damping,1);
    if(!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { self->setIKDriveTarget(middle,tip,target,force,torque,static_cast<int>(space),static_cast<int>(bend),influence,frequency,damping); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, AttachSprite)
    METHOD_SIGNATURE("return a new animated mounting Part retaining an independent child Sprite", [object Part], 1, ({ [object Sprite] child, [number int] placement = partPlacement_Snap | [object Sprite] child, [number int] placement, [object Part] childMount }));
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1, child, Sprite); OPTIONAL_NUMBER_ARG(2, placement, 0);
    if (!std::isfinite(placement) || placement < 0 || placement > 1 || std::floor(placement)!=placement) { THROW_RANGE_ERR("Expected a partPlacement integer constant"); RETURN_NULL; }
    try {
        Part* childMount=nullptr;
        if (ARGC>2) { REQUIRE_CPP_OBJECT_ARG(3, mount, Part); childMount=mount; }
        auto* result=self->attachSprite(child,static_cast<int>(placement),childMount); RETURN_CPP_OBJECT(result,Part);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetAttachedSprite)
    METHOD_SIGNATURE("retained child Sprite, or null on an ordinary or detached mounting Part", [object Sprite], 0, ());
    REQUIRE_ARG_COUNT(0); auto* child=self->getAttachedSprite(); RETURN_CPP_OBJECT(child,Sprite);
    END
METHOD_IMPL(Part, DetachSprite)
    METHOD_SIGNATURE("release the child, preserving its last published world pose", [object Part], 0, ());
    REQUIRE_ARG_COUNT(0); self->detachSprite(); RETURN_THIS;
    END
METHOD_IMPL(Part, GetAttachmentError)
    METHOD_SIGNATURE("empty on success; diagnostic when follow placement cannot be represented", string, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getAttachmentError().c_str());
    END

METHOD_IMPL(Part, ReadPhysics)
    METHOD_SIGNATURE("optional body or shared NoPhysics; this never creates a body", [object PhysicsBody], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); auto* body=&static_cast<PhysicsBody&>(self->physics); RETURN_CPP_OBJECT(body,PhysicsBody);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetupPhysicsBody)
    METHOD_SIGNATURE("set up the body, applying mass and inertia on every call", [object PhysicsBody], 0, (number mass = 1, number momentOfInertia = 1));
    try {
        OPTIONAL_NUMBER_ARG(1,mass,1.0); OPTIONAL_NUMBER_ARG(2,inertia,1.0); auto* body=&self->setupPhysicsBody(mass,inertia); RETURN_CPP_OBJECT(body,PhysicsBody);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, RemovePhysicsBody)
    METHOD_SIGNATURE("detach the body; retained references keep their state", undefined, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->removePhysicsBody(); NO_RETURN;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

%#ifdef PDG_USING_JAVASCRIPT_CORE
Collider* New_Collider(SCRIPT_ARGS) { return nullptr; }
static void Collider_finalize(JSObjectRef object) {
    auto* body=static_cast<Collider*>(JSObjectGetPrivate(object));
    if(body) {body->mColliderScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
}
%#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj=obj
%#else
%#define COLLIDER_SAVE_WEAK(cppObj,obj) cppObj->mColliderScriptObj.Reset(isolate,obj);cppObj->mColliderScriptObj.SetWeak()
ColliderWrap::ColliderWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
ColliderWrap::~ColliderWrap() {
    if(cppPtr_) {cppPtr_->mColliderScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(Collider, "Sprite.setupCollider or Part.setupCollider",
    COLLIDER_SAVE_WEAK(cppObj,obj);cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("Collider", Collider, Collider_finalize, , ,
        HAS_METHOD(Collider, "setWantsContactEvents", SetWantsContactEvents)
        HAS_METHOD(Collider, "getWantsContactEvents", GetWantsContactEvents)
        HAS_METHOD(Collider, "setFriction", SetFriction)
        HAS_METHOD(Collider, "setRestitution", SetRestitution)
        HAS_METHOD(Collider, "getFriction", GetFriction)
        HAS_METHOD(Collider, "getRestitution", GetRestitution)
        HAS_METHOD(Collider, "useBodyMaterial", UseBodyMaterial)
        HAS_METHOD(Collider, "isPresent", IsPresent)
        HAS_METHOD(Collider, "isAttached", IsAttached)
        HAS_METHOD(Collider, "isEnabled", IsEnabled)
        HAS_METHOD(Collider, "isSensor", IsSensor)
        HAS_METHOD(Collider, "getId", GetId)
        HAS_METHOD(Collider, "getCategory", GetCategory)
        HAS_METHOD(Collider, "getCollisionMask", GetCollisionMask)
        HAS_METHOD(Collider, "getGroup", GetGroup)
        HAS_METHOD(Collider, "getShapeCount", GetShapeCount)
        HAS_METHOD(Collider, "setEnabled", SetEnabled)
        HAS_METHOD(Collider, "setSensor", SetSensor)
        HAS_METHOD(Collider, "setCategory", SetCategory)
        HAS_METHOD(Collider, "setCollisionMask", SetCollisionMask)
        HAS_METHOD(Collider, "setGroup", SetGroup)
        HAS_METHOD(Collider, "getPhysicsBody", GetPhysicsBody)
        HAS_METHOD(Collider, "setCircle", SetCircle)
        HAS_METHOD(Collider, "addCircle", AddCircle)
        HAS_METHOD(Collider, "setCapsule", SetCapsule)
        HAS_METHOD(Collider, "addCapsule", AddCapsule)
        HAS_METHOD(Collider, "getCapsuleStart", GetCapsuleStart)
        HAS_METHOD(Collider, "getCapsuleEnd", GetCapsuleEnd)
        HAS_METHOD(Collider, "getCapsuleRadius", GetCapsuleRadius)
        HAS_METHOD(Collider, "setBox", SetBox)
        HAS_METHOD(Collider, "addBox", AddBox)
        HAS_METHOD(Collider, "clearShapes", ClearShapes)
        HAS_METHOD(Collider, "useOwnerPhysics", UseOwnerPhysics)
        HAS_METHOD(Collider, "setPhysicsBody", SetPhysicsBody)
        HAS_METHOD(Collider, "getBounds", GetBounds)
        HAS_METHOD(Collider, "contains", Contains)
        HAS_METHOD(Collider, "overlaps", Overlaps)
        HAS_METHOD(Collider, "removeShape", RemoveShape)
        HAS_METHOD(Collider, "getShapeId", GetShapeId)
        HAS_METHOD(Collider, "getContactError", GetContactError)
        HAS_METHOD(Collider, "addPolygon", AddPolygon)
        HAS_METHOD(Collider, "setPolygon", SetPolygon)
        HAS_METHOD(Collider, "setImageMask", SetImageMask)
        HAS_METHOD(Collider, "addImageMask", AddImageMask)
        HAS_METHOD(Collider, "getGeometrySource", GetGeometrySource)
        HAS_METHOD(Collider, "isSourceShape", IsSourceShape)
        HAS_METHOD(Collider, "getShapeName", GetShapeName)
        HAS_METHOD(Collider, "getShapeType", GetShapeType)
        HAS_METHOD(Collider, "getCircleRadius", GetCircleRadius)
        HAS_METHOD(Collider, "setContactHandler", SetContactHandler)
        HAS_METHOD(Collider, "setCollisionFilter", SetCollisionFilter)

    );
    END
%#undef COLLIDER_SAVE_WEAK

%#ifdef PDG_USING_JAVASCRIPT_CORE
PhysicsConstraint* New_PhysicsConstraint(SCRIPT_ARGS) { return nullptr; }
static void PhysicsConstraint_finalize(JSObjectRef object) {
    auto* body=static_cast<PhysicsConstraint*>(JSObjectGetPrivate(object));
    if(body) {body->mPhysicsConstraintScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
}
%#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj=obj
%#else
%#define PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsConstraintScriptObj.Reset(isolate,obj);cppObj->mPhysicsConstraintScriptObj.SetWeak()
PhysicsConstraintWrap::PhysicsConstraintWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
PhysicsConstraintWrap::~PhysicsConstraintWrap() {
    if(cppPtr_) {cppPtr_->mPhysicsConstraintScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(PhysicsConstraint, "PhysicsBody.createPinJoint and other constraint factories",
    PHYSICSCONSTRAINT_SAVE_WEAK(cppObj,obj);cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("PhysicsConstraint", PhysicsConstraint, PhysicsConstraint_finalize, , ,
        HAS_METHOD(PhysicsConstraint, "isActive", IsActive)
        HAS_METHOD(PhysicsConstraint, "isBroken", IsBroken)
        HAS_METHOD(PhysicsConstraint, "getCollideBodies", GetCollideBodies)
        HAS_METHOD(PhysicsConstraint, "getType", GetType)
        HAS_METHOD(PhysicsConstraint, "getMaxForce", GetMaxForce)
        HAS_METHOD(PhysicsConstraint, "getBreakForce", GetBreakForce)
        HAS_METHOD(PhysicsConstraint, "getImpulse", GetImpulse)
        HAS_METHOD(PhysicsConstraint, "getForce", GetForce)
        HAS_METHOD(PhysicsConstraint, "setCollideBodies", SetCollideBodies)
        HAS_METHOD(PhysicsConstraint, "setMaxForce", SetMaxForce)
        HAS_METHOD(PhysicsConstraint, "setBreakForce", SetBreakForce)
        HAS_METHOD(PhysicsConstraint, "getBodyA", GetBodyA)
        HAS_METHOD(PhysicsConstraint, "getBodyB", GetBodyB)
        HAS_METHOD(PhysicsConstraint, "getAnchorA", GetAnchorA)
        HAS_METHOD(PhysicsConstraint, "getAnchorB", GetAnchorB)
        HAS_METHOD(PhysicsConstraint, "setAnchorA", SetAnchorA)
        HAS_METHOD(PhysicsConstraint, "setAnchorB", SetAnchorB)
        HAS_METHOD(PhysicsConstraint, "setAnchors", SetAnchors)
        HAS_METHOD(PhysicsConstraint, "getGrooveStart", GetGrooveStart)
        HAS_METHOD(PhysicsConstraint, "getGrooveEnd", GetGrooveEnd)
        HAS_METHOD(PhysicsConstraint, "setGroove", SetGroove)
        HAS_METHOD(PhysicsConstraint, "getMinAngle", GetMinAngle)
        HAS_METHOD(PhysicsConstraint, "getMaxAngle", GetMaxAngle)
        HAS_METHOD(PhysicsConstraint, "setAngleLimits", SetAngleLimits)
        HAS_METHOD(PhysicsConstraint, "disconnect", Disconnect)
    );
    END
%#undef PHYSICSCONSTRAINT_SAVE_WEAK

%#ifdef PDG_USING_JAVASCRIPT_CORE
PhysicsBody* New_PhysicsBody(SCRIPT_ARGS) { return nullptr; }
static void PhysicsBody_finalize(JSObjectRef object) {
    auto* body=static_cast<PhysicsBody*>(JSObjectGetPrivate(object));
    if(body) {body->mPhysicsBodyScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);body->release();}
}
%#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj=obj
%#else
%#define BODY_SAVE_WEAK(cppObj,obj) cppObj->mPhysicsBodyScriptObj.Reset(isolate,obj);cppObj->mPhysicsBodyScriptObj.SetWeak()
PhysicsBodyWrap::PhysicsBodyWrap(SCRIPT_ARGS) : cppPtr_(nullptr) {}
PhysicsBodyWrap::~PhysicsBodyWrap() {
    if(cppPtr_) {cppPtr_->mPhysicsBodyScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;}
}
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(PhysicsBody, "Sprite.setupPhysicsBody or Part.setupPhysicsBody",
    BODY_SAVE_WEAK(cppObj,obj);cppObj->addRef())
    EXPORT_FINALIZED_CLASS_SYMBOLS("PhysicsBody", PhysicsBody, PhysicsBody_finalize, , ,
        HAS_METHOD(PhysicsBody, "getConstraintCount", GetConstraintCount)
        HAS_METHOD(PhysicsBody, "createPinJoint", CreatePinJoint)
        HAS_METHOD(PhysicsBody, "createPivotJoint", CreatePivotJoint)
        HAS_METHOD(PhysicsBody, "createSlideJoint", CreateSlideJoint)
        HAS_METHOD(PhysicsBody, "createGrooveJoint", CreateGrooveJoint)
        HAS_METHOD(PhysicsBody, "createSpring", CreateSpring)
        HAS_METHOD(PhysicsBody, "createRotarySpring", CreateRotarySpring)
        HAS_METHOD(PhysicsBody, "createRotaryLimit", CreateRotaryLimit)
        HAS_METHOD(PhysicsBody, "createRatchet", CreateRatchet)
        HAS_METHOD(PhysicsBody, "createGear", CreateGear)
        HAS_METHOD(PhysicsBody, "createMotor", CreateMotor)
        HAS_METHOD(PhysicsBody, "getConstraint", GetConstraint)
        HAS_METHOD(PhysicsBody, "disconnect", Disconnect)
        HAS_METHOD(PhysicsBody, "setDriveTarget", SetDriveTarget)
        HAS_METHOD(PhysicsBody, "clearDrive", ClearDrive)
        HAS_METHOD(PhysicsBody, "isDriveEnabled", IsDriveEnabled)
        HAS_METHOD(PhysicsBody, "getDriveState", GetDriveState)
        HAS_METHOD(PhysicsBody, "getMode", GetMode)
        HAS_METHOD(PhysicsBody, "setMode", SetMode)
        HAS_METHOD(PhysicsBody, "getMass", GetMass)
        HAS_METHOD(PhysicsBody, "setMass", SetMass)
        HAS_METHOD(PhysicsBody, "getMomentOfInertia", GetMomentOfInertia)
        HAS_METHOD(PhysicsBody, "setMomentOfInertia", SetMomentOfInertia)
        HAS_METHOD(PhysicsBody, "getLinearDamping", GetLinearDamping)
        HAS_METHOD(PhysicsBody, "setLinearDamping", SetLinearDamping)
        HAS_METHOD(PhysicsBody, "getAngularDamping", GetAngularDamping)
        HAS_METHOD(PhysicsBody, "setAngularDamping", SetAngularDamping)
        HAS_METHOD(PhysicsBody, "getFriction", GetFriction)
        HAS_METHOD(PhysicsBody, "setFriction", SetFriction)
        HAS_METHOD(PhysicsBody, "getRestitution", GetRestitution)
        HAS_METHOD(PhysicsBody, "setRestitution", SetRestitution)
        HAS_METHOD(PhysicsBody, "setBreakAngularSpeed", SetBreakAngularSpeed)
        HAS_METHOD(PhysicsBody, "getBreakAngularSpeed", GetBreakAngularSpeed)
        HAS_METHOD(PhysicsBody, "getBreakAngularSpeedReference", GetBreakAngularSpeedReference)
        HAS_METHOD(PhysicsBody, "getAngularVelocity", GetAngularVelocity)
        HAS_METHOD(PhysicsBody, "setAngularVelocity", SetAngularVelocity)
        HAS_METHOD(PhysicsBody, "getSpeed", GetSpeed)
        HAS_METHOD(PhysicsBody, "setSpeed", SetSpeed)
        HAS_METHOD(PhysicsBody, "getSolver", GetSolver)
        HAS_METHOD(PhysicsBody, "getAngularMomentum", GetAngularMomentum)
        HAS_METHOD(PhysicsBody, "getMovementDirectionInRadians", GetMovementDirectionInRadians)
        HAS_METHOD(PhysicsBody, "isPresent", IsPresent)
        HAS_METHOD(PhysicsBody, "isAttached", IsAttached)
        HAS_METHOD(PhysicsBody, "getState", GetState)
        HAS_METHOD(PhysicsBody, "getVelocity", GetVelocity)
        HAS_METHOD(PhysicsBody, "setVelocity", SetVelocity)
        HAS_METHOD(PhysicsBody, "setVelocityInRadians", SetVelocityInRadians)
        HAS_METHOD(PhysicsBody, "teleport", Teleport)
        HAS_METHOD(PhysicsBody, "applyImpulse", ApplyImpulse)
        HAS_METHOD(PhysicsBody, "applyAngularImpulse", ApplyAngularImpulse)
        HAS_METHOD(PhysicsBody, "applyForce", ApplyForce)
        HAS_METHOD(PhysicsBody, "applyTorque", ApplyTorque)
        HAS_METHOD(PhysicsBody, "addContinuousForce", AddContinuousForce)
        HAS_METHOD(PhysicsBody, "addContinuousTorque", AddContinuousTorque)
        HAS_METHOD(PhysicsBody, "removeForce", RemoveForce)
        HAS_METHOD(PhysicsBody, "stopAllForces", StopAllForces)
        HAS_METHOD(PhysicsBody, "stopMoving", StopMoving)
        HAS_METHOD(PhysicsBody, "stopSpinning", StopSpinning)
        HAS_METHOD(PhysicsBody, "step", Step)
    );
    END
%#undef BODY_SAVE_WEAK
METHOD_IMPL(PhysicsBody, SetDriveTarget)
    METHOD_SIGNATURE("apply bounded force and torque toward a world target", [object PhysicsBody], 4, ([object Point] position, number radians, number maxForce, number maxTorque, number frequency = 4, number dampingRatio = 1, [number int] direction = rotationDirection_Shortest));
    try {
        REQUIRE_ARG_MIN_COUNT(4); REQUIRE_POINT_ARG(1,position); REQUIRE_NUMBER_ARG(2,radians);
        REQUIRE_NUMBER_ARG(3,maxForce); REQUIRE_NUMBER_ARG(4,maxTorque);
        OPTIONAL_NUMBER_ARG(5,frequency,4.0); OPTIONAL_NUMBER_ARG(6,dampingRatio,1.0);
        OPTIONAL_NUMBER_ARG(7,direction,static_cast<double>(rotationDirection_Shortest));
        if (!std::isfinite(direction) || direction!=std::floor(direction) || direction<0 || direction>3) {
            THROW_TYPE_ERR("Expected an integer rotationDirection constant"); RETURN_NULL;
        }
        self->setDriveTarget(position,radians,maxForce,maxTorque,frequency,dampingRatio,static_cast<int>(direction));
        RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ClearDrive)
    METHOD_SIGNATURE("remove the drive while preserving physical velocity", [object PhysicsBody], 0, ());
    REQUIRE_ARG_COUNT(0);
    try { self->clearDrive(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, IsDriveEnabled)
    METHOD_SIGNATURE("whether an active physical drive is installed", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isDriveEnabled());
    END
METHOD_IMPL(PhysicsBody, GetMode)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMode());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetMode)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value) || std::floor(value)!=value || value<1 || value>3) { THROW_RANGE_ERR("Expected a physicsBody mode"); RETURN_NULL; }
        self->setMode(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetMass)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMass());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetMass)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setMass(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetMomentOfInertia)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMomentOfInertia());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetMomentOfInertia)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setMomentOfInertia(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetLinearDamping)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getLinearDamping());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetLinearDamping)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setLinearDamping(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetAngularDamping)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAngularDamping());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetAngularDamping)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setAngularDamping(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetFriction)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getFriction());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetFriction)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setFriction(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetRestitution)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getRestitution());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetRestitution)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setRestitution(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetBreakAngularSpeed)
    METHOD_SIGNATURE("notify when absolute or reference-relative angular speed exceeds a limit", [object PhysicsBody], 1, ({ number radiansPerSecond | number radiansPerSecond, [object PhysicsBody] referenceBody }));
    try {
        REQUIRE_ARG_MIN_COUNT(1); if (ARGC>2) { THROW_TYPE_ERR("Expected speed and optional reference body"); RETURN_NULL; } REQUIRE_NUMBER_ARG(1,speed);
        PhysicsBody* reference=nullptr;
        if (ARGC>1 && !VALUE_IS_NULL(ARGV[1]) && !VALUE_IS_UNDEFINED(ARGV[1])) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsObjectOfClass(ctx,ARGV[1],PhysicsBody_class())) { THROW_TYPE_ERR("Expected a PhysicsBody reference"); RETURN_NULL; }
%#else
            if (!PhysicsBodyWrap::GetTemplate(isolate)->HasInstance(ARGV[1])) { THROW_TYPE_ERR("Expected a PhysicsBody reference"); RETURN_NULL; }
%#endif
            REQUIRE_CPP_OBJECT_ARG(2,body,PhysicsBody); reference=body;
        }
        self->setBreakAngularSpeed(speed,reference); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetBreakAngularSpeed)
    METHOD_SIGNATURE("angular-speed break threshold in radians/second; zero disables", number, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getBreakAngularSpeed());
    END
METHOD_IMPL(PhysicsBody, GetBreakAngularSpeedReference)
    METHOD_SIGNATURE("optional reference body, or null for absolute angular speed", [object PhysicsBody], 0, ());
    REQUIRE_ARG_COUNT(0); auto* reference=self->getBreakAngularSpeedReference(); RETURN_CPP_OBJECT(reference,PhysicsBody);
    END
METHOD_IMPL(PhysicsBody, GetAngularVelocity)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAngularVelocity());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetAngularVelocity)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setAngularVelocity(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetSpeed)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSpeed());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetSpeed)
    METHOD_SIGNATURE("", [object PhysicsBody], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setSpeed(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetSolver)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSolver());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetAngularMomentum)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAngularMomentum());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetMovementDirectionInRadians)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMovementDirectionInRadians());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, IsPresent)
    METHOD_SIGNATURE("", boolean, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isPresent());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, IsAttached)
    METHOD_SIGNATURE("", boolean, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAttached());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetVelocity)
    METHOD_SIGNATURE("world distance units per second", [object Vector], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); auto velocity=self->getVelocity(); RETURN(VECTOR2VAL(velocity));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetVelocity)
    METHOD_SIGNATURE("physical velocity in world distance units per second", [object PhysicsBody], 2, ({[object Vector] velocity|number xPerSecond, number yPerSecond}));
    try {
        if(ARGC==2) { REQUIRE_NUMBER_ARG(1,x); REQUIRE_NUMBER_ARG(2,y); self->setVelocity(x,y); }
        else { REQUIRE_ARG_COUNT(1); REQUIRE_VECTOR_ARG(1,velocity); self->setVelocity(velocity); }
        RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetVelocityInRadians)
    METHOD_SIGNATURE("", [object PhysicsBody], 2, (number speed, number direction));
    try {
        REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,speed); REQUIRE_NUMBER_ARG(2,direction); self->setVelocityInRadians(speed,direction); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, Teleport)
    METHOD_SIGNATURE("teleport the center of mass in owning-layer/world space", [object PhysicsBody], 2, ([object Point] position, number radians));
    try {
        REQUIRE_ARG_COUNT(2); REQUIRE_POINT_ARG(1,position); REQUIRE_NUMBER_ARG(2,radians); self->teleport(position,radians); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyImpulse)
    METHOD_SIGNATURE("instantaneous world-space momentum change", [object PhysicsBody], 1, ({ [object Vector] impulse | [object Vector] impulse, [object Point] worldPoint }));
    try {
        REQUIRE_ARG_MIN_COUNT(1); REQUIRE_VECTOR_ARG(1,impulse);
        if(ARGC>1) { REQUIRE_POINT_ARG(2,worldPoint); self->applyImpulse(impulse,worldPoint); } else self->applyImpulse(impulse); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyAngularImpulse)
    METHOD_SIGNATURE("instantaneous angular momentum change", [object PhysicsBody], 1, (number impulse));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,impulse); self->applyAngularImpulse(impulse); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyForce)
    METHOD_SIGNATURE("world force for finite seconds; zero duration contributes nothing", [number uint], 2, ({ [object Vector] force, number durationSeconds, number delaySeconds = 0 | [object Vector] force, number durationSeconds, number delaySeconds, [object Point] worldPoint }));
    try {
        REQUIRE_ARG_MIN_COUNT(2); REQUIRE_VECTOR_ARG(1,force); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_NUMBER_ARG(3,delay,0.0);
        if(ARGC>3) { REQUIRE_POINT_ARG(4,point); RETURN_UINT32(self->applyForce(force,point,seconds,delay)); }
        RETURN_UINT32(self->applyForce(force,seconds,delay));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyTorque)
    METHOD_SIGNATURE("torque for finite seconds, using moment of inertia", [number uint], 2, (number torque, number durationSeconds, number delaySeconds = 0));
    try {
        REQUIRE_ARG_MIN_COUNT(2); REQUIRE_NUMBER_ARG(1,torque); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_NUMBER_ARG(3,delay,0.0); RETURN_UINT32(self->applyTorque(torque,seconds,delay));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, AddContinuousForce)
    METHOD_SIGNATURE("persists until removeForce or stopAllForces", [number uint], 1, ([object Vector] force));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_VECTOR_ARG(1,force); RETURN_UINT32(self->addContinuousForce(force));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, AddContinuousTorque)
    METHOD_SIGNATURE("persists until removeForce or stopAllForces", [number uint], 1, (number torque));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,torque); RETURN_UINT32(self->addContinuousTorque(torque));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, RemoveForce)
    METHOD_SIGNATURE("", boolean, 1, ([number uint] id));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id);
        if(!std::isfinite(id) || id<0 || id>UINT32_MAX || std::floor(id)!=id) { THROW_RANGE_ERR("Expected a force ID"); RETURN_NULL; }
        RETURN_BOOL(self->removeForce(static_cast<uint32>(id)));
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, StopAllForces)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->stopAllForces(); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, StopMoving)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->stopMoving(); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, StopSpinning)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->stopSpinning(); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, Step)
    METHOD_SIGNATURE("advance a detached basic body in seconds; owned bodies advance automatically", undefined, 1, (number deltaSeconds));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds);
        if(self->isAttached()) { THROW_ERR("Owned bodies advance with their Sprite or Part"); RETURN_NULL; }
        self->step(seconds); NO_RETURN;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
DECLARE_SYMBOL(x);
DECLARE_SYMBOL(y);
DECLARE_SYMBOL(rotation);
DECLARE_SYMBOL(velocityX);
DECLARE_SYMBOL(velocityY);
DECLARE_SYMBOL(angularVelocity);
METHOD_IMPL(PhysicsBody, GetState)
    METHOD_SIGNATURE("snapshot in owning-layer/world coordinates and seconds", object, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); const auto state=self->getState(); OBJECT_REF result=OBJECT_CREATE_EMPTY(0);
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(x),NUM2VAL(state.x));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(y),NUM2VAL(state.y));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(rotation),NUM2VAL(state.rotation));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(velocityX),NUM2VAL(state.velocityX));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(velocityY),NUM2VAL(state.velocityY));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(angularVelocity),NUM2VAL(state.angularVelocity));
        RETURN_OBJECT(result);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

DECLARE_SYMBOL(enabled);
DECLARE_SYMBOL(maxForce);
DECLARE_SYMBOL(maxTorque);
DECLARE_SYMBOL(frequency);
DECLARE_SYMBOL(dampingRatio);
DECLARE_SYMBOL(forceX);
DECLARE_SYMBOL(forceY);
DECLARE_SYMBOL(torque);
DECLARE_SYMBOL(positionError);
DECLARE_SYMBOL(rotationError);
METHOD_IMPL(PhysicsBody, GetDriveState)
    METHOD_SIGNATURE("independent snapshot of the drive target and last force", object, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); const auto state=self->getDriveState(); OBJECT_REF result=OBJECT_CREATE_EMPTY(0);
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(enabled),BOOL2VAL(state.enabled));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(x),NUM2VAL(state.x));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(y),NUM2VAL(state.y));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(rotation),NUM2VAL(state.rotation));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(maxForce),NUM2VAL(state.maxForce));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(maxTorque),NUM2VAL(state.maxTorque));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(frequency),NUM2VAL(state.frequency));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(dampingRatio),NUM2VAL(state.dampingRatio));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(forceX),NUM2VAL(state.forceX));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(forceY),NUM2VAL(state.forceY));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(torque),NUM2VAL(state.torque));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(positionError),NUM2VAL(state.positionError));
        OBJECT_SET_PROPERTY_VALUE(result,SYMBOL(rotationError),NUM2VAL(state.rotationError));
        RETURN_OBJECT(result);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

%#ifdef PDG_USING_JAVASCRIPT_CORE
static bool collisionArgumentIs(JSContextRef ctx, JSValueRef value, bool body) {
    return JSValueIsObjectOfClass(ctx, value, body ? PhysicsBody_class() : Collider_class());
}
%#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(ctx, value, body)
%#else
static bool collisionArgumentIs(v8::Isolate* isolate, v8::Local<v8::Value> value, bool body) {
    return (body ? PhysicsBodyWrap::GetTemplate(isolate) : ColliderWrap::GetTemplate(isolate))->HasInstance(value);
}
%#define COLLISION_ARGUMENT_IS(value, body) collisionArgumentIs(isolate, value, body)
%#endif
METHOD_IMPL(Collider, IsPresent)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isPresent()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsAttached)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAttached()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsEnabled)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isEnabled()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, IsSensor)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isSensor()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetId)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getId()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCategory)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getCategory()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCollisionMask)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getCollisionMask()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetGroup)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getGroup()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetShapeCount)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getShapeCount()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetEnabled)
    METHOD_SIGNATURE("", [object Collider], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setEnabled(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetSensor)
    METHOD_SIGNATURE("", [object Collider], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setSensor(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCategory)
    METHOD_SIGNATURE("", [object Collider], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setCategory(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCollisionMask)
    METHOD_SIGNATURE("", [object Collider], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setCollisionMask(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetGroup)
    METHOD_SIGNATURE("", [object Collider], 1, ([number uint] value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } self->setGroup(uint32_t(value)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetPhysicsBody)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getPhysicsBody(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCircle)
    METHOD_SIGNATURE("", [object Collider], 1, (number radius, [object Point] center = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,radius); OPTIONAL_POINT_ARG(2,center,Point()); self->setCircle(radius,center); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddCircle)
    METHOD_SIGNATURE("", [number uint], 1, (number radius, [object Point] center = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,radius); OPTIONAL_POINT_ARG(2,center,Point()); RETURN_NUMBER(self->addCircle(radius,center)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetCapsule)
    METHOD_SIGNATURE("", [object Collider], 3, ([object Point] start, [object Point] end, number radius));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_NUMBER_ARG(3,radius); self->setCapsule(start,end,radius); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddCapsule)
    METHOD_SIGNATURE("", [number uint], 3, ([object Point] start, [object Point] end, number radius));
    try { REQUIRE_ARG_COUNT(3); REQUIRE_POINT_ARG(1,start); REQUIRE_POINT_ARG(2,end); REQUIRE_NUMBER_ARG(3,radius); RETURN_NUMBER(self->addCapsule(start,end,radius)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleStart)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        auto result=self->getCapsuleStart(uint32_t(value)); RETURN_POINT(result);
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleEnd)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        auto result=self->getCapsuleEnd(uint32_t(value)); RETURN_POINT(result);
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetCapsuleRadius)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        RETURN_NUMBER(self->getCapsuleRadius(uint32_t(value)));
    } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetBox)
    METHOD_SIGNATURE("", [object Collider], 1, ([object Rect] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); self->setBox(bounds); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddBox)
    METHOD_SIGNATURE("", [number uint], 1, ([object Rect] bounds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1,bounds); RETURN_NUMBER(self->addBox(bounds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, ClearShapes)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearShapes(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, UseOwnerPhysics)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->useOwnerPhysics(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetPhysicsBody)
    METHOD_SIGNATURE("", [object Collider], 1, ([object PhysicsBody] body));
    try { REQUIRE_ARG_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,body,PhysicsBody); self->setPhysicsBody(*body); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto bounds=self->getBounds(); RETURN_RECT(bounds); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, Contains)
    METHOD_SIGNATURE("", boolean, 1, ([object Point] worldPoint));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_POINT_ARG(1,point); RETURN_BOOL(self->contains(point)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, Overlaps)
    METHOD_SIGNATURE("", boolean, 1, ([object Collider] other));
    try { REQUIRE_ARG_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],false)) { THROW_TYPE_ERR("Expected a Collider"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,Collider); RETURN_BOOL(self->overlaps(*other)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, RemoveShape)
    METHOD_SIGNATURE("", boolean, 1, ([number uint] id));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } RETURN_BOOL(self->removeShape(uint32_t(id))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetShapeId)
    METHOD_SIGNATURE("", [number uint], 1, ([number uint] id));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,id); if(!std::isfinite(id)||id<0||id>4294967295.0||id!=std::floor(id)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } RETURN_NUMBER(self->getShapeId(uint32_t(id))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetContactError)
    METHOD_SIGNATURE("", string, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getContactError().c_str()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, AddPolygon)
    METHOD_SIGNATURE("", [number uint], 1, ({ array vertices | [object Polygon] polygon }));
    try { REQUIRE_ARG_COUNT(1); std::vector<Point> points;
%#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,ARGV[0])) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=VAL2OBJ(ARGV[0]); auto lengthName=JSStringCreateWithUTF8CString("length");
        auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
        const double length=VAL2NUM(lengthValue);
        if(length<3||length>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<unsigned(length);++i) { auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#else
        if(!ARGV[0]->IsArray()) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=ARGV[0].As<v8::Array>();
        if(array->Length()<3||array->Length()>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<array->Length();++i) { v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#endif
        RETURN_NUMBER(self->addPolygon(points)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetPolygon)
    METHOD_SIGNATURE("", [object Collider], 1, ({ array vertices | [object Polygon] polygon }));
    try { REQUIRE_ARG_COUNT(1); std::vector<Point> points;
%#ifdef PDG_USING_JAVASCRIPT_CORE
        if(!JSValueIsArray(ctx,ARGV[0])) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=VAL2OBJ(ARGV[0]); auto lengthName=JSStringCreateWithUTF8CString("length");
        auto lengthValue=JSObjectGetProperty(ctx,array,lengthName,exception);JSStringRelease(lengthName);
        const double length=VAL2NUM(lengthValue);
        if(length<3||length>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<unsigned(length);++i) { auto value=JSObjectGetPropertyAtIndex(ctx,array,i,exception); Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#else
        if(!ARGV[0]->IsArray()) { THROW_TYPE_ERR("Expected an array of Points"); RETURN_NULL; }
        auto array=ARGV[0].As<v8::Array>();
        if(array->Length()<3||array->Length()>4096) { THROW_RANGE_ERR("Expected 3 to 4096 vertices"); RETURN_NULL; }
        for(unsigned i=0;i<array->Length();++i) { v8::Local<v8::Value> value; if(!array->Get(isolate->GetCurrentContext(),i).ToLocal(&value)) return; Point point; auto isPoint = VALUE_IS_POINT(value, point); if (!isPoint.has_value()) { RETURN_NULL; } if (!*isPoint) { THROW_TYPE_ERR("Expected a Point vertex"); RETURN_NULL; } points.push_back(point); }
%#endif
        self->setPolygon(points); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
DECLARE_SYMBOL(collider); DECLARE_SYMBOL(other); DECLARE_SYMBOL(shape); DECLARE_SYMBOL(otherShape);
DECLARE_SYMBOL(phase); DECLARE_SYMBOL(penetration); DECLARE_SYMBOL(point); DECLARE_SYMBOL(normal);
DECLARE_SYMBOL(impulse); DECLARE_SYMBOL(sensor);
struct ColliderScriptCallback {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    JSGlobalContextRef context;
    JSObjectRef function;
    ColliderScriptCallback(JSContextRef ctx, JSObjectRef callback)
        : context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(callback) { JSValueProtect(context,function); }
    ~ColliderScriptCallback() { JSValueUnprotect(context,function);JSGlobalContextRelease(context); }
%#else
    v8::Isolate* isolate;
    v8::Global<v8::Context> context;
    v8::Global<v8::Function> function;
    ColliderScriptCallback(v8::Isolate* engine,v8::Local<v8::Function> callback)
        : isolate(engine),context(engine,engine->GetCurrentContext()),function(engine,callback) {}
%#endif
    bool invoke(const Collider& a,const Collider& b,const ColliderContact* contact) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
        JSContextRef ctx=context;JSValueRef error=nullptr;JSValueRef* exception=&error;
        auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c); };
        auto event=JSObjectMake(ctx,nullptr,nullptr);
%#else
        v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
        auto object=[&](const Collider& value) { auto* c=const_cast<Collider*>(&value);return c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj); };
        auto event=v8::Object::New(isolate);
%#endif
        VALUE argv[2]={object(a),object(b)};
        if(contact) {
            Point point=contact->point;Vector normal=contact->normal,impulse=contact->impulse;
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(collider),argv[0]);
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(other),argv[1]);
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(shape),NUM2VAL(contact->shape));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(otherShape),NUM2VAL(contact->otherShape));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(phase),NUM2VAL(contact->phase));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(penetration),NUM2VAL(contact->penetration));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(point),POINT2VAL(point));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(normal),VECTOR2VAL(normal));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(impulse),VECTOR2VAL(impulse));
            OBJECT_SET_PROPERTY_VALUE(event,SYMBOL(sensor),BOOL2VAL(contact->sensor));
            argv[0]=event;
        }
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto result=JSObjectCallAsFunction(ctx,function,nullptr,contact?1:2,argv,exception);
        if(error) throw std::runtime_error("Collider callback failed");
        if(!contact&&!JSValueIsBoolean(ctx,result)) throw std::runtime_error("Collision filter must return a boolean");
        return contact || JSValueToBoolean(ctx,result);
%#else
        v8::Local<v8::Value> result;
        if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),contact?1:2,argv).ToLocal(&result)) {
            v8::String::Utf8Value message(isolate,catcher.Exception());
            throw std::runtime_error(*message?*message:"Collider callback failed");
        }
        if(!contact&&!result->IsBoolean()) throw std::runtime_error("Collision filter must return a boolean");
        return contact || result->BooleanValue(isolate);
%#endif
    }
};
METHOD_IMPL(Collider, SetContactHandler)
    // Null clears this callback; documentation metadata is supplied separately.
    try { REQUIRE_ARG_COUNT(1);
        if(VALUE_IS_NULL(ARGV[0])) { self->setContactHandler({}); RETURN_THIS; }
        REQUIRE_FUNCTION_ARG(1,func);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
%#else
        auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
%#endif
        self->setContactHandler([callback](const ColliderContact& c) { callback->invoke(*c.collider,*c.other,&c); }); RETURN_THIS;
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, SetCollisionFilter)
    // Null clears this callback; documentation metadata is supplied separately.
    try { REQUIRE_ARG_COUNT(1);
        if(VALUE_IS_NULL(ARGV[0])) { self->setCollisionFilter({}); RETURN_THIS; }
        REQUIRE_FUNCTION_ARG(1,func);
%#ifdef PDG_USING_JAVASCRIPT_CORE
        auto callback=std::make_shared<ColliderScriptCallback>(ctx,func);
%#else
        auto callback=std::make_shared<ColliderScriptCallback>(isolate,func);
%#endif
        self->setCollisionFilter([callback](const Collider& a,const Collider& b) { return callback->invoke(a,b,nullptr); }); RETURN_THIS;
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetGeometrySource)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_INTEGER(self->getGeometrySource()); } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, IsSourceShape)
    METHOD_SIGNATURE("", boolean, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_BOOL(self->isSourceShape(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetShapeName)
    METHOD_SIGNATURE("", string, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); auto name=self->getShapeName(id); RETURN_STRING(name.c_str());
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetShapeType)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_INTEGER(self->getShapeType(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, GetCircleRadius)
    METHOD_SIGNATURE("", number, 1, ([number uint] shapeId));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); if(!std::isfinite(value)||value<0||value>4294967295.0||std::floor(value)!=value) { THROW_RANGE_ERR("Expected an unsigned shape ID"); RETURN_NULL; }
        const auto id=uint32_t(value); RETURN_NUMBER(self->getCircleRadius(id));
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, SetImageMask)
    METHOD_SIGNATURE("", [object Collider], 2, ([object Image] image, [object Rect] localBounds, [number int] alphaThreshold = 128));
    try { REQUIRE_ARG_MIN_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1,image,Image); REQUIRE_RECT_ARG(2,bounds); OPTIONAL_NUMBER_ARG(3,threshold,128); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold) { THROW_RANGE_ERR("Expected an integer alpha threshold from 1 to 255"); RETURN_NULL; } self->setImageMask(*image,bounds,threshold); RETURN_THIS; }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Collider, AddImageMask)
    METHOD_SIGNATURE("", [number uint], 2, ([object Image] image, [object Rect] localBounds, [number int] alphaThreshold = 128));
    try { REQUIRE_ARG_MIN_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1,image,Image); REQUIRE_RECT_ARG(2,bounds); OPTIONAL_NUMBER_ARG(3,threshold,128); if(!std::isfinite(threshold)||threshold<1||threshold>255||std::floor(threshold)!=threshold) { THROW_RANGE_ERR("Expected an integer alpha threshold from 1 to 255"); RETURN_NULL; } RETURN_NUMBER(self->addImageMask(*image,bounds,threshold)); }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(PhysicsConstraint, IsActive)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isActive()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, IsBroken)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isBroken()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetCollideBodies)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->getCollideBodies()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetType)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getType()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetMaxForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBreakForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getBreakForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetImpulse)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getImpulse()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetForce)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getForce()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetCollideBodies)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, (boolean value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,value); self->setCollideBodies(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetMaxForce)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setMaxForce(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetBreakForce)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setBreakForce(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBodyA)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getBodyA(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetBodyB)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->getBodyB(); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
// Read coordinates once and reject coercion/defaulting by the legacy Point converter.
%#ifdef PDG_USING_JAVASCRIPT_CORE
%#define CONSTRAINT_VALUE_MISSING(value) (!(value) || (exception && *exception))
%#else
%#define CONSTRAINT_VALUE_MISSING(value) ((value).IsEmpty())
%#endif
#define REQUIRE_CONSTRAINT_POINT_ARG(n, name) \
    if(!VALUE_IS_OBJECT(ARGV[n-1])) { THROW_TYPE_ERR("Expected a Point"); RETURN_NULL; } \
    auto name##_object=VAL2OBJ(ARGV[n-1]); \
    auto name##_x=OBJECT_GET_PROPERTY(name##_object,SYMBOL(x)); \
    if(CONSTRAINT_VALUE_MISSING(name##_x)) { RETURN_NULL; } \
    auto name##_y=OBJECT_GET_PROPERTY(name##_object,SYMBOL(y)); \
    if(CONSTRAINT_VALUE_MISSING(name##_y)) { RETURN_NULL; } \
    if(!VALUE_IS_NUMBER(name##_x) || !VALUE_IS_NUMBER(name##_y) || \
       !std::isfinite(VAL2NUM(name##_x)) || !std::isfinite(VAL2NUM(name##_y))) { \
        THROW_TYPE_ERR("Expected finite Point coordinates"); RETURN_NULL; \
    } \
    pdg::Point name(VAL2NUM(name##_x),VAL2NUM(name##_y))
METHOD_IMPL(PhysicsConstraint, GetAnchorA)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getAnchorA(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetAnchorB)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getAnchorB(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchorA)
    METHOD_SIGNATURE("edit body-local constraint geometry", [object PhysicsConstraint], 1, ([object Point] anchor));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CONSTRAINT_POINT_ARG(1,anchor); self->setAnchorA(anchor); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchorB)
    METHOD_SIGNATURE("edit body-local constraint geometry", [object PhysicsConstraint], 1, ([object Point] anchor));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CONSTRAINT_POINT_ARG(1,anchor); self->setAnchorB(anchor); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAnchors)
    METHOD_SIGNATURE("edit body-local constraint geometry", [object PhysicsConstraint], 2, ([object Point] anchorA, [object Point] anchorB));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_CONSTRAINT_POINT_ARG(1,a); REQUIRE_CONSTRAINT_POINT_ARG(2,b); self->setAnchors(a,b); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetGrooveStart)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getGrooveStart(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetGrooveEnd)
    METHOD_SIGNATURE("read body-local constraint geometry", [object Point], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto result=self->getGrooveEnd(); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetGroove)
    METHOD_SIGNATURE("edit body-local constraint geometry", [object PhysicsConstraint], 2, ([object Point] start, [object Point] end));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_CONSTRAINT_POINT_ARG(1,a); REQUIRE_CONSTRAINT_POINT_ARG(2,b); self->setGroove(a,b); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
#undef REQUIRE_CONSTRAINT_POINT_ARG
%#undef CONSTRAINT_VALUE_MISSING
METHOD_IMPL(PhysicsConstraint, GetMinAngle)
    METHOD_SIGNATURE("rotary-limit angle in radians", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMinAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, GetMaxAngle)
    METHOD_SIGNATURE("rotary-limit angle in radians", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxAngle()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, SetAngleLimits)
    METHOD_SIGNATURE("set the rotary-limit interval in radians", [object PhysicsConstraint], 2, (number minAngle, number maxAngle));
    try { REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,lo); REQUIRE_NUMBER_ARG(2,hi); self->setAngleLimits(lo,hi); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsConstraint, Disconnect)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->disconnect(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetConstraintCount)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getConstraintCount()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreatePinJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, ([object PhysicsBody] other, [object Point] anchor = Point(0,0), [object Point] otherAnchor = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); OPTIONAL_POINT_ARG(2,anchor,Point()); OPTIONAL_POINT_ARG(3,otherAnchor,Point()); auto* result=&self->createPinJoint(*other,anchor,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreatePivotJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, ([object PhysicsBody] other, [object Point] anchor = Point(0,0), [object Point] otherAnchor = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); OPTIONAL_POINT_ARG(2,anchor,Point()); OPTIONAL_POINT_ARG(3,otherAnchor,Point()); auto* result=&self->createPivotJoint(*other,anchor,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateSlideJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 5, ([object PhysicsBody] other, [object Point] anchor, [object Point] otherAnchor, number minDistance, number maxDistance));
    try { REQUIRE_ARG_MIN_COUNT(5); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,anchor); REQUIRE_POINT_ARG(3,otherAnchor); REQUIRE_NUMBER_ARG(4,minDistance); REQUIRE_NUMBER_ARG(5,maxDistance); auto* result=&self->createSlideJoint(*other,anchor,otherAnchor,minDistance,maxDistance); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateGrooveJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 4, ([object PhysicsBody] other, [object Point] start, [object Point] end, [object Point] otherAnchor));
    try { REQUIRE_ARG_MIN_COUNT(4); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,start); REQUIRE_POINT_ARG(3,end); REQUIRE_POINT_ARG(4,otherAnchor); auto* result=&self->createGrooveJoint(*other,start,end,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateSpring)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 6, ([object PhysicsBody] other, [object Point] anchor, [object Point] otherAnchor, number restLength, number stiffness, number damping));
    try { REQUIRE_ARG_MIN_COUNT(6); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,anchor); REQUIRE_POINT_ARG(3,otherAnchor); REQUIRE_NUMBER_ARG(4,restLength); REQUIRE_NUMBER_ARG(5,stiffness); REQUIRE_NUMBER_ARG(6,damping); auto* result=&self->createSpring(*other,anchor,otherAnchor,restLength,stiffness,damping); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRotarySpring)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 4, ([object PhysicsBody] other, number restAngle, number stiffness, number damping));
    try { REQUIRE_ARG_MIN_COUNT(4); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,restAngle); REQUIRE_NUMBER_ARG(3,stiffness); REQUIRE_NUMBER_ARG(4,damping); auto* result=&self->createRotarySpring(*other,restAngle,stiffness,damping); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRotaryLimit)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 3, ([object PhysicsBody] other, number minAngle, number maxAngle));
    try { REQUIRE_ARG_MIN_COUNT(3); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,minAngle); REQUIRE_NUMBER_ARG(3,maxAngle); auto* result=&self->createRotaryLimit(*other,minAngle,maxAngle); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRatchet)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 2, ([object PhysicsBody] other, number interval, number phase = 0));
    try { REQUIRE_ARG_MIN_COUNT(2); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,interval); OPTIONAL_NUMBER_ARG(3,phase,0); auto* result=&self->createRatchet(*other,interval,phase); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateGear)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 2, ([object PhysicsBody] other, number ratio, number phase = 0));
    try { REQUIRE_ARG_MIN_COUNT(2); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,ratio); OPTIONAL_NUMBER_ARG(3,phase,0); auto* result=&self->createGear(*other,ratio,phase); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateMotor)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 3, ([object PhysicsBody] other, number radiansPerSecond, number maxTorque));
    try { REQUIRE_ARG_MIN_COUNT(3); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,radiansPerSecond); REQUIRE_NUMBER_ARG(3,maxTorque); auto* result=&self->createMotor(*other,radiansPerSecond,maxTorque); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetConstraint)
    METHOD_SIGNATURE("", [object PhysicsConstraint], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,index); if(!std::isfinite(index)||index<0||index>4294967295.0||index!=std::floor(index)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } auto* result=&self->getConstraint(uint32_t(index)); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, Disconnect)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ([object PhysicsBody] other = null));
    try { if(ARGC==0||VALUE_IS_NULL(ARGV[0])) self->disconnect(); else { if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); self->disconnect(other); } RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, ReadCollider)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<Collider&>(self->collider); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, SetupCollider)
    METHOD_SIGNATURE("set up the collision geometry association", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupCollider(); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Sprite, RemoveCollider)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeCollider(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, ReadCollider)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<Collider&>(self->collider); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetupCollider)
    METHOD_SIGNATURE("set up the collision geometry association", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupCollider(); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetupFrameCollider)
    METHOD_SIGNATURE("Follow current frame collision geometry", [object Collider], 0, ([number int] mode = frameCollider_AlphaMask, [number int] alphaThreshold = 128));
    try {
        OPTIONAL_NUMBER_ARG(1,modeValue,static_cast<double>(frameCollider_AlphaMask));
        OPTIONAL_NUMBER_ARG(2,threshold,128);
        if(!std::isfinite(modeValue) || modeValue<0 || modeValue>std::numeric_limits<int>::max() || std::floor(modeValue)!=modeValue) {
            THROW_RANGE_ERR("Expected an integer frameCollider mode"); RETURN_NULL;
        }
        const int mode=static_cast<int>(modeValue);
        if((mode!=frameCollider_Bounds && mode!=frameCollider_AlphaMask) || !std::isfinite(threshold) || threshold<1 || threshold>255 || std::floor(threshold)!=threshold) {
            THROW_RANGE_ERR("Expected a frameCollider mode and an integer alpha threshold from 1 to 255"); RETURN_NULL;
        }
        auto* result=&self->setupFrameCollider(mode,threshold); RETURN_CPP_OBJECT(result,Collider);
    } catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Part, SetupAnimationCollider)
    METHOD_SIGNATURE("Follow a named authored collision box", [object Collider], 1, (string boxName));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_STRING_ARG(1,name); auto* result=&self->setupAnimationCollider(name); RETURN_CPP_OBJECT(result,Collider); }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Part, RemoveCollider)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeCollider(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetWantsContactEvents)
    METHOD_SIGNATURE("opt in to eventType_ColliderContact on the owning Sprite", [object Collider], 1, (boolean wanted));
    REQUIRE_ARG_COUNT(1); REQUIRE_BOOL_ARG(1,wanted); self->setWantsContactEvents(wanted); RETURN_THIS;
    END
METHOD_IMPL(Collider, GetWantsContactEvents)
    METHOD_SIGNATURE("whether owner contact events are requested", boolean, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->getWantsContactEvents());
    END
METHOD_IMPL(Collider, SetFriction)
    METHOD_SIGNATURE("", [object Collider], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setFriction(value); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, SetRestitution)
    METHOD_SIGNATURE("", [object Collider], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setRestitution(value); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetFriction)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getFriction()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, GetRestitution)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getRestitution()); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Collider, UseBodyMaterial)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->useBodyMaterial(); RETURN_THIS; } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
%#undef COLLISION_ARGUMENT_IS

// Lightweight particles and point emitters.
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void Particle_finalize(JSObjectRef object) {
    auto* value=static_cast<Particle*>(JSObjectGetPrivate(object)); if (!value) return;
    value->mParticleScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr; value->mEventEmitterScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr); value->release();
}
%#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj; cppObj->mEventEmitterScriptObj=obj
%#else
%#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj.Reset(isolate,obj); cppObj->mParticleScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak(); cppObj->mEventEmitterScriptObj.Reset(isolate,obj); cppObj->mEventEmitterScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(Particle, PARTICLE_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("Particle", Particle, AnimatedBase, Particle_finalize, , ,
        HAS_ANIMATED_METHODS(Particle)
        HAS_EMITTER_METHODS(Particle)
        HAS_METHOD(Particle, "_readPhysics", ReadPhysics)
        HAS_METHOD(Particle, "setupPhysicsBody", SetupPhysicsBody)
        HAS_METHOD(Particle, "removePhysicsBody", RemovePhysicsBody)
        HAS_METHOD(Particle, "_readCollider", ReadCollider)
        HAS_METHOD(Particle, "setupCollider", SetupCollider)
        HAS_METHOD(Particle, "removeCollider", RemoveCollider)
        HAS_METHOD(Particle, "setupParticleEmitter", SetupParticleEmitter)
        HAS_METHOD(Particle, "getParticleEmitter", GetParticleEmitter)
        HAS_METHOD(Particle, "removeParticleEmitter", RemoveParticleEmitter)
        HAS_METHOD(Particle, "clearContent", ClearContent)
        HAS_METHOD(Particle, "hasContent", HasContent)
        HAS_METHOD(Particle, "setOpacity", SetOpacity)
        HAS_METHOD(Particle, "getOpacity", GetOpacity)
        HAS_METHOD(Particle, "fadeTo", FadeTo)
        HAS_METHOD(Particle, "setLifetime", SetLifetime)
        HAS_METHOD(Particle, "getLifetime", GetLifetime)
        HAS_METHOD(Particle, "getAge", GetAge)
        HAS_METHOD(Particle, "isAlive", IsAlive)
        HAS_METHOD(Particle, "expire", Expire)
        HAS_METHOD(Particle, "getLayer", GetLayer)
        HAS_METHOD(Particle, "animate", Animate)
%#ifndef PDG_NO_GUI CR
        HAS_METHOD(Particle, "setImage", SetImage)
        HAS_METHOD(Particle, "setDrawing", SetDrawing)
%#endif CR
    );
    END
ANIMATED_BASE_CLASS_IMPL(Particle)
EMITTER_BASE_CLASS_IMPL(Particle)
CLEANUP_IMPL(Particle)
%#ifdef PDG_USING_JAVASCRIPT_CORE
Particle* New_Particle(SCRIPT_ARGS) { return new Particle(); }
%#else
ParticleWrap::ParticleWrap(SCRIPT_ARGS) : cppPtr_(New_Particle(args)) {}
ParticleWrap::~ParticleWrap() { if (cppPtr_) { cppPtr_->mParticleScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
Particle* New_Particle(SCRIPT_ARGS) {
    if (s_Particle_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate(); auto* cppObj=new Particle(); cppObj->addRef();
    PARTICLE_SAVE(cppObj,args.This()); return cppObj;
}
%#endif
%#undef PARTICLE_SAVE
%#ifdef PDG_USING_JAVASCRIPT_CORE
static void ParticleEmitter_finalize(JSObjectRef object) {
    auto* value=static_cast<ParticleEmitter*>(JSObjectGetPrivate(object)); if (!value) return;
    value->mParticleEmitterScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr;
    JSObjectSetPrivate(object,nullptr); value->release();
}
%#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj
%#else
%#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj.Reset(isolate,obj); cppObj->mParticleEmitterScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak()
%#endif
WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(ParticleEmitter, PARTICLEEMITTER_SAVE(cppObj,obj); cppObj->addRef())
    EXPORT_DERIVED_CLASS_SYMBOLS("ParticleEmitter", ParticleEmitter, AnimatedBase, ParticleEmitter_finalize, , ,
        HAS_ANIMATED_METHODS(ParticleEmitter)
        HAS_METHOD(ParticleEmitter, "setParticleTemplate", SetParticleTemplate)
        HAS_METHOD(ParticleEmitter, "hasParticleTemplate", HasParticleTemplate)
        HAS_METHOD(ParticleEmitter, "setEmissionRate", SetEmissionRate)
        HAS_METHOD(ParticleEmitter, "getEmissionRate", GetEmissionRate)
        HAS_METHOD(ParticleEmitter, "setParticleSpeed", SetParticleSpeed)
        HAS_METHOD(ParticleEmitter, "getMinParticleSpeed", GetMinParticleSpeed)
        HAS_METHOD(ParticleEmitter, "getMaxParticleSpeed", GetMaxParticleSpeed)
        HAS_METHOD(ParticleEmitter, "setSpread", SetSpread)
        HAS_METHOD(ParticleEmitter, "getSpread", GetSpread)
        HAS_METHOD(ParticleEmitter, "setVelocityInheritance", SetVelocityInheritance)
        HAS_METHOD(ParticleEmitter, "getVelocityInheritance", GetVelocityInheritance)
        HAS_METHOD(ParticleEmitter, "setSeed", SetSeed)
        HAS_METHOD(ParticleEmitter, "getSeed", GetSeed)
        HAS_METHOD(ParticleEmitter, "startEmitting", StartEmitting)
        HAS_METHOD(ParticleEmitter, "stopEmitting", StopEmitting)
        HAS_METHOD(ParticleEmitter, "isEmitting", IsEmitting)
        HAS_METHOD(ParticleEmitter, "emit", Emit)
        HAS_METHOD(ParticleEmitter, "getLayer", GetLayer)
        HAS_METHOD(ParticleEmitter, "getParticle", GetParticle)
        HAS_METHOD(ParticleEmitter, "animate", Animate)
    );
    END
ANIMATED_BASE_CLASS_IMPL(ParticleEmitter)
CLEANUP_IMPL(ParticleEmitter)
%#ifdef PDG_USING_JAVASCRIPT_CORE
ParticleEmitter* New_ParticleEmitter(SCRIPT_ARGS) { return new ParticleEmitter(); }
%#else
ParticleEmitterWrap::ParticleEmitterWrap(SCRIPT_ARGS) : cppPtr_(New_ParticleEmitter(args)) {}
ParticleEmitterWrap::~ParticleEmitterWrap() { if (cppPtr_) { cppPtr_->mParticleEmitterScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr; } }
ParticleEmitter* New_ParticleEmitter(SCRIPT_ARGS) {
    if (s_ParticleEmitter_InNewFromCpp) return nullptr;
    auto* isolate=args.GetIsolate(); auto* cppObj=new ParticleEmitter(); cppObj->addRef();
    PARTICLEEMITTER_SAVE(cppObj,args.This()); return cppObj;
}
%#endif
%#undef PARTICLEEMITTER_SAVE
METHOD_IMPL(Particle, HasContent)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasContent()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetOpacity)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getOpacity()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetLifetime)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getLifetime()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetAge)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAge()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, IsAlive)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isAlive()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, Animate)
    METHOD_SIGNATURE("advance a detached object in simulation seconds", boolean, 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); RETURN_BOOL(self->animate(seconds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetLayer)
    METHOD_SIGNATURE("", [object SpriteLayer], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getLayer(); RETURN_CPP_OBJECT(result,SpriteLayer); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, HasParticleTemplate)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->hasParticleTemplate()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetEmissionRate)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getEmissionRate()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetMinParticleSpeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMinParticleSpeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetMaxParticleSpeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getMaxParticleSpeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetSpread)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSpread()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetVelocityInheritance)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getVelocityInheritance()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetSeed)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getSeed()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, IsEmitting)
    METHOD_SIGNATURE("", boolean, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_BOOL(self->isEmitting()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, Animate)
    METHOD_SIGNATURE("advance a detached object in simulation seconds", boolean, 1, (number seconds));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seconds); RETURN_BOOL(self->animate(seconds)); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetLayer)
    METHOD_SIGNATURE("", [object SpriteLayer], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getLayer(); RETURN_CPP_OBJECT(result,SpriteLayer); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetOpacity)
    METHOD_SIGNATURE("", [object Particle], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setOpacity(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetLifetime)
    METHOD_SIGNATURE("", [object Particle], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setLifetime(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetEmissionRate)
    METHOD_SIGNATURE("", [object ParticleEmitter], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setEmissionRate(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetSpread)
    METHOD_SIGNATURE("", [object ParticleEmitter], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setSpread(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetVelocityInheritance)
    METHOD_SIGNATURE("", [object ParticleEmitter], 1, (number value));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value); self->setVelocityInheritance(value); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ClearContent)
    METHOD_SIGNATURE("", [object Particle], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->clearContent(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemoveCollider)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeCollider(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemovePhysicsBody)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removePhysicsBody(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, RemoveParticleEmitter)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeParticleEmitter(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, Expire)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->expire(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ReadPhysics)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<PhysicsBody&>(self->physics); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupPhysicsBody)
    METHOD_SIGNATURE("", [object PhysicsBody], 0, (number mass = 1, number momentOfInertia = 1));
    try { OPTIONAL_NUMBER_ARG(1,mass,1); OPTIONAL_NUMBER_ARG(2,inertia,1); auto* result=&self->setupPhysicsBody(mass,inertia); RETURN_CPP_OBJECT(result,PhysicsBody); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, ReadCollider)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<Collider&>(self->collider); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupCollider)
    METHOD_SIGNATURE("", [object Collider], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupCollider(); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetupParticleEmitter)
    METHOD_SIGNATURE("", [object ParticleEmitter], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupParticleEmitter(); RETURN_CPP_OBJECT(result,ParticleEmitter); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, GetParticleEmitter)
    METHOD_SIGNATURE("", [object ParticleEmitter], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getParticleEmitter(); RETURN_CPP_OBJECT(result,ParticleEmitter); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, FadeTo)
    METHOD_SIGNATURE("", [object Particle], 2, (number opacity, number seconds, [number int] easing = linearTween));
    try { REQUIRE_ARG_MIN_COUNT(2); REQUIRE_NUMBER_ARG(1,opacity); REQUIRE_NUMBER_ARG(2,seconds); OPTIONAL_NUMBER_ARG(3,easing,static_cast<int>(EasingFuncRef::linearTween)); if (!std::isfinite(easing) || easing < 0 || easing >= NUM_EASING_FUNCTIONS || std::floor(easing)!=easing) throw std::invalid_argument("Unknown easing"); self->fadeTo(opacity,seconds,gEasingFunctions[static_cast<int>(easing)]); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#ifndef PDG_NO_GUI
METHOD_IMPL(Particle, SetImage)
    METHOD_SIGNATURE("", [object Particle], 1, ([object Image] content));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,content,Image); self->setImage(*content); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Particle, SetDrawing)
    METHOD_SIGNATURE("", [object Particle], 1, ([object Drawing] content));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,content,Drawing); self->setDrawing(*content); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#endif
METHOD_IMPL(ParticleEmitter, SetParticleTemplate)
    METHOD_SIGNATURE("capture artwork, settings and remaining animation; each emission has independent runtime state", [object ParticleEmitter], 1, ([object Particle] particle));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1,particle,Particle); self->setParticleTemplate(*particle); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetParticleSpeed)
    METHOD_SIGNATURE("", [object ParticleEmitter], 1, (number minimum, number maximum = minimum));
    try { REQUIRE_ARG_MIN_COUNT(1); REQUIRE_NUMBER_ARG(1,minimum); OPTIONAL_NUMBER_ARG(2,maximum,minimum); self->setParticleSpeed(minimum,maximum); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, StartEmitting)
    METHOD_SIGNATURE("", [object ParticleEmitter], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->startEmitting(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, StopEmitting)
    METHOD_SIGNATURE("", [object ParticleEmitter], 0, ());
    try { REQUIRE_ARG_COUNT(0); self->stopEmitting(); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, SetSeed)
    METHOD_SIGNATURE("", [object ParticleEmitter], 1, ([number uint] seed));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,seed); if (!std::isfinite(seed) || seed < 0 || seed > UINT32_MAX || std::floor(seed) != seed) throw std::invalid_argument("Expected uint32 seed"); self->setSeed(static_cast<uint32_t>(seed)); RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, Emit)
    METHOD_SIGNATURE("", number, 0, ([number uint] count = 1));
    try { OPTIONAL_NUMBER_ARG(1,count,1); if (!std::isfinite(count) || count < 0 || count > UINT32_MAX || std::floor(count) != count) throw std::invalid_argument("Expected uint32 count"); RETURN_UINT32(self->emit(static_cast<uint32_t>(count))); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(ParticleEmitter, GetParticle)
    METHOD_SIGNATURE("", [object Particle], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=self->getParticle(); RETURN_CPP_OBJECT(result,Particle); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

} // pdg namespace
