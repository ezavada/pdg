// -----------------------------------------------
// part.cpp
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
%#define PROCEDURAL_PARAMETERS JSContextRef ctx, JSValueRef* exception
%#define PROCEDURAL_ARGUMENTS ctx, exception
%#else
%#define PROCEDURAL_PARAMETERS v8::Isolate* isolate
%#define PROCEDURAL_ARGUMENTS isolate
%#endif

static std::vector<double> proceduralBindingValues(PROCEDURAL_PARAMETERS, VALUE input) {
    std::vector<double> values;
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    if(!JSValueIsArray(ctx,input)) { throw std::invalid_argument("Expected procedural array"); }
    auto a=JSValueToObject(ctx,input,exception);auto key=JSStringCreateWithUTF8CString("length");
    double n=JSValueToNumber(ctx,JSObjectGetProperty(ctx,a,key,exception),exception);JSStringRelease(key);
    if(*exception||n>50000) { throw std::invalid_argument("Invalid procedural array"); }
    for(unsigned i=0;i<n;++i){auto item=JSObjectGetPropertyAtIndex(ctx,a,i,exception);if(*exception||!JSValueIsNumber(ctx,item)) { throw std::invalid_argument("Invalid procedural number"); }values.push_back(JSValueToNumber(ctx,item,exception));}
    %#else
    if(!input->IsArray()) { throw std::invalid_argument("Expected procedural array"); }auto a=input.As<v8::Array>();if(a->Length()>50000) { throw std::invalid_argument("Procedural array too long"); }
    for(unsigned i=0;i<a->Length();++i){v8::Local<v8::Value> item;if(!a->Get(isolate->GetCurrentContext(),i).ToLocal(&item)||!item->IsNumber()) { throw std::invalid_argument("Invalid procedural number"); }values.push_back(item.As<v8::Number>()->Value());}
    %#endif
    return values;
}


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
        HAS_METHOD(Part, "_procedural", ProceduralControl)
        HAS_METHOD(Part, "solveIK", SolveIK)
        HAS_METHOD(Part, "setIKTarget", SetIKTarget)
        HAS_METHOD(Part, "clearIKTarget", ClearIKTarget)
        HAS_METHOD(Part, "hasIKTarget", HasIKTarget)
        HAS_METHOD(Part, "isIKTargetReached", IsIKTargetReached)
        HAS_METHOD(Part, "getIKError", GetIKError)
        HAS_METHOD(Part, "getJiggleError", GetJiggleError)
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
    METHOD_SIGNATURE("owning Sprite, or null after removal", [object Sprite*], 0, ()); REQUIRE_ARG_COUNT(0);
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
    METHOD_SIGNATURE("Follow a bone while preserving local offsets.", [this], 1, ([number uint] boneId));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, boneId);
    if (!std::isfinite(boneId) || boneId < 0 || boneId > boneId_None || std::floor(boneId) != boneId) { THROW_RANGE_ERR("Expected a bone ID"); RETURN_NULL; }
    try { self->bindToBone(static_cast<BoneId>(boneId)); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, UnbindFromBone)
    METHOD_SIGNATURE("Clear authored frame bindings.", [this], 0, ()); REQUIRE_ARG_COUNT(0);
    try { self->unbindFromBone(); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetParentPart)
    METHOD_SIGNATURE("explicit parent Part, or null", [object Part*], 0, ()); REQUIRE_ARG_COUNT(0);
    auto* parent = self->getParentPart(); RETURN_CPP_OBJECT(parent, Part);
    END
METHOD_IMPL(Part, SetParentPart)
    METHOD_SIGNATURE("Select an explicit parent Part.", [this], 0, ({ | [object Part*] parent }));
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
    METHOD_SIGNATURE("Follow an authored binding.", [this], 1, (string name));
    try {
        REQUIRE_ARG_COUNT(1);
        REQUIRE_STRING_ARG(1, name); self->bindToAnimationBinding(name); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, BindToAnimationSocket)
    METHOD_SIGNATURE("Follow an authored socket.", [this], 1, (string name));
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
    METHOD_SIGNATURE("Remove artwork from the Part.", [this], 0, ());
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
    METHOD_SIGNATURE("Assign editable Drawing artwork.", [this], 1, ([object Drawing const&] drawing));
    REQUIRE_ARG_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1, drawing, Drawing);
    try { self->setDrawing(*drawing); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetImage)
    METHOD_SIGNATURE("Assign an image to a local rectangle.", [this], 2, ([object Image const&] image, [object Rect const&] localBounds));
    REQUIRE_ARG_COUNT(2); REQUIRE_CPP_OBJECT_ARG(1, image, Image); REQUIRE_RECT_ARG(2, bounds);
    try { self->setImage(*image,bounds); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
%#endif


METHOD_IMPL(Part, ProceduralControl)
    METHOD_SIGNATURE("internal procedural value adapter", object, 2, (int operation, object values));
    REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,operation);
    try {
        if(!std::isfinite(operation)||operation!=std::floor(operation)||operation<1||operation>16) { throw std::invalid_argument("Invalid procedural operation"); }
        auto result=self->proceduralControl(int(operation),proceduralBindingValues(PROCEDURAL_ARGUMENTS,ARGV[1]));
        %#ifdef PDG_USING_JAVASCRIPT_CORE
        auto a=JSObjectMakeArray(ctx,0,nullptr,exception);for(unsigned i=0;i<result.size();++i)JSObjectSetPropertyAtIndex(ctx,a,i,NUM2VAL(result[i]),exception);
        %#else
        auto a=v8::Array::New(isolate);for(unsigned i=0;i<result.size();++i)(void)a->Set(isolate->GetCurrentContext(),i,NUM2VAL(result[i])).ToChecked();
        %#endif
        RETURN(a);
    } catch(const std::exception& e){THROW_ERR(e.what());RETURN_NULL;}
    END

METHOD_IMPL(Part, SolveIK)
    METHOD_SIGNATURE("solve a contiguous Part chain without bones; returns whether the target is reached", boolean, 6, ([object Part*] middle, [object Part*] tip, [object Point const&] target, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1));
    REQUIRE_ARG_MIN_COUNT(3); REQUIRE_CPP_OBJECT_ARG(1, middle, Part); REQUIRE_CPP_OBJECT_ARG(2, tip, Part); REQUIRE_POINT_ARG(3, target);
    OPTIONAL_NUMBER_ARG(4, space, 2); OPTIONAL_NUMBER_ARG(5, bend, 1); OPTIONAL_NUMBER_ARG(6, influence, 1);
    if (!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { RETURN_BOOL(self->solveIK(middle,tip,target,static_cast<int>(space),static_cast<int>(bend),influence)); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetIKTarget)
    METHOD_SIGNATURE("Maintain a target for a contiguous two-segment Part chain.", [this], 6, ([object Part*] middle, [object Part*] tip, [object Point const&] target, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1));
    REQUIRE_ARG_MIN_COUNT(3); REQUIRE_CPP_OBJECT_ARG(1, middle, Part); REQUIRE_CPP_OBJECT_ARG(2, tip, Part); REQUIRE_POINT_ARG(3, target);
    OPTIONAL_NUMBER_ARG(4, space, 2); OPTIONAL_NUMBER_ARG(5, bend, 1); OPTIONAL_NUMBER_ARG(6, influence, 1);
    if (!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { self->setIKTarget(middle,tip,target,static_cast<int>(space),static_cast<int>(bend),influence); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, ClearIKTarget)
    METHOD_SIGNATURE("Stop this root's scheduled IK controller.", [this], 0, ());
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
METHOD_IMPL(Part, GetJiggleError)
    METHOD_SIGNATURE("error from the last chain jiggle or FABRIK evaluation, or empty on success", string, 0, ());
    REQUIRE_ARG_COUNT(0); RETURN_STRING(self->getJiggleError().c_str());
    END
METHOD_IMPL(Part, SetIKLimits)
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
METHOD_IMPL(Part, ClearIKLimits)
    METHOD_SIGNATURE("Remove this joint's IK rotation limits.", [this], 0, ());
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
    METHOD_SIGNATURE("Drive a two-segment Part chain toward an IK target using bounded forces and torques.", [this], 10, ([object Part*] middle, [object Part*] tip, [object Point const&] target, number maxForce, number maxTorque, [number int] space = partSpace_World, [number int] bendDirection = 1, number influence = 1, number frequency = 4, number dampingRatio = 1));
    REQUIRE_ARG_MIN_COUNT(5); REQUIRE_CPP_OBJECT_ARG(1,middle,Part); REQUIRE_CPP_OBJECT_ARG(2,tip,Part); REQUIRE_POINT_ARG(3,target);
    REQUIRE_NUMBER_ARG(4,force); REQUIRE_NUMBER_ARG(5,torque);
    OPTIONAL_NUMBER_ARG(6,space,2); OPTIONAL_NUMBER_ARG(7,bend,1); OPTIONAL_NUMBER_ARG(8,influence,1);
    OPTIONAL_NUMBER_ARG(9,frequency,4); OPTIONAL_NUMBER_ARG(10,damping,1);
    if(!std::isfinite(space) || space<0 || space>2 || std::floor(space)!=space || (bend!=1 && bend!=-1)) { THROW_RANGE_ERR("Invalid Part IK integer constants"); RETURN_NULL; }
    try { self->setIKDriveTarget(middle,tip,target,force,torque,static_cast<int>(space),static_cast<int>(bend),influence,frequency,damping); RETURN_THIS; }
    catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, AttachSprite)
    METHOD_SIGNATURE("return a new animated mounting Part retaining an independent child Sprite", [object Part*], 1, ({ [object Sprite*] child, [number int] placement = partPlacement_Snap | [object Sprite*] child, [number int] placement, [object Part*] childMount }));
    REQUIRE_ARG_MIN_COUNT(1); REQUIRE_CPP_OBJECT_ARG(1, child, Sprite); OPTIONAL_NUMBER_ARG(2, placement, 0);
    if (!std::isfinite(placement) || placement < 0 || placement > 1 || std::floor(placement)!=placement) { THROW_RANGE_ERR("Expected a partPlacement integer constant"); RETURN_NULL; }
    try {
        Part* childMount=nullptr;
        if (ARGC>2) { REQUIRE_CPP_OBJECT_ARG(3, mount, Part); childMount=mount; }
        auto* result=self->attachSprite(child,static_cast<int>(placement),childMount); RETURN_CPP_OBJECT(result,Part);
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, GetAttachedSprite)
    METHOD_SIGNATURE("retained child Sprite, or null on an ordinary or detached mounting Part", [object Sprite*], 0, ());
    REQUIRE_ARG_COUNT(0); auto* child=self->getAttachedSprite(); RETURN_CPP_OBJECT(child,Sprite);
    END
METHOD_IMPL(Part, DetachSprite)
    METHOD_SIGNATURE("Release a mounted Sprite.", [this], 0, ());
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
    METHOD_SIGNATURE("set up the body, applying mass and inertia on every call", [object PhysicsBody&], 0, (number mass = 1, number momentOfInertia = 1));
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
METHOD_IMPL(Part, ReadCollider)
    METHOD_SIGNATURE("", [object Collider&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&static_cast<Collider&>(self->collider); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetupCollider)
    METHOD_SIGNATURE("set up the collision geometry association", [object Collider&], 0, ());
    try { REQUIRE_ARG_COUNT(0); auto* result=&self->setupCollider(); RETURN_CPP_OBJECT(result,Collider); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Part, SetupFrameCollider)
    METHOD_SIGNATURE("Follow current frame collision geometry", [object Collider&], 0, ([number int] mode = frameCollider_AlphaMask, [number int] alphaThreshold = 128));
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
    METHOD_SIGNATURE("Follow a named authored collision box", [object Collider&], 1, (string boxName));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_STRING_ARG(1,name); auto* result=&self->setupAnimationCollider(name); RETURN_CPP_OBJECT(result,Collider); }
    catch(const std::exception& e) { THROW_ERR(e.what()); }
    END
METHOD_IMPL(Part, RemoveCollider)
    METHOD_SIGNATURE("", undefined, 0, ());
    try { REQUIRE_ARG_COUNT(0); self->removeCollider(); NO_RETURN; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

} // namespace pdg

/* @pdg-schema
{
  "name": "AffineTransform",
  "value": {
    "kind": "record",
    "fields": {
      "a": {
        "type": "number"
      },
      "b": {
        "type": "number"
      },
      "c": {
        "type": "number"
      },
      "d": {
        "type": "number"
      },
      "tx": {
        "type": "number"
      },
      "ty": {
        "type": "number"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Part.getTransform",
  "value": {
    "returns": {
      "schema": "AffineTransform",
      "ownership": "owned",
      "copy": true
    }
  }
}
*/
