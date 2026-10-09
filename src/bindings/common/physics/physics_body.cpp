// -----------------------------------------------
// physics_body.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

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

#include "physics_object_impl_macros.h"

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
    METHOD_SIGNATURE("Drive a dynamic body toward a position and orientation using bounded force and torque.", [this], 4, ([object Point const&] position, number radians, number maxForce, number maxTorque, number frequency = 4, number dampingRatio = 1, [number int] direction = rotationDirection_Shortest));
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
    METHOD_SIGNATURE("Remove the active physical drive.", [this], 0, ());
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
    METHOD_SIGNATURE("Set the body's simulation mode.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's mass.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's moment of inertia.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's linear damping.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's angular damping.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's contact friction.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's restitution.", [this], 1, (number value));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,value);
        self->setRestitution(value); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetBreakAngularSpeed)
    METHOD_SIGNATURE("Notify when absolute angular speed exceeds the limit.", [this], 1, ({ number radiansPerSecond | number radiansPerSecond, [object PhysicsBody*] referenceBody }));
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
    METHOD_SIGNATURE("optional reference body, or null for absolute angular speed", [object PhysicsBody*], 0, ());
    REQUIRE_ARG_COUNT(0); auto* reference=self->getBreakAngularSpeedReference(); RETURN_CPP_OBJECT(reference,PhysicsBody);
    END
METHOD_IMPL(PhysicsBody, GetAngularVelocity)
    METHOD_SIGNATURE("", number, 0, ());
    try {
        REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getAngularVelocity());
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetAngularVelocity)
    METHOD_SIGNATURE("Set the body's angular velocity.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set the body's speed.", [this], 1, (number value));
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
    METHOD_SIGNATURE("Set linear velocity.", [this], 2, ({[object Vector const&] velocity|number xPerSecond, number yPerSecond}));
    try {
        if(ARGC==2) { REQUIRE_NUMBER_ARG(1,x); REQUIRE_NUMBER_ARG(2,y); self->setVelocity(x,y); }
        else { REQUIRE_ARG_COUNT(1); REQUIRE_VECTOR_ARG(1,velocity); self->setVelocity(velocity); }
        RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, SetVelocityInRadians)
    METHOD_SIGNATURE("Set velocity from speed and direction.", [this], 2, (number speed, number direction));
    try {
        REQUIRE_ARG_COUNT(2); REQUIRE_NUMBER_ARG(1,speed); REQUIRE_NUMBER_ARG(2,direction); self->setVelocityInRadians(speed,direction); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, Teleport)
    METHOD_SIGNATURE("Move a body immediately.", [this], 2, ([object Point const&] position, number radians));
    try {
        REQUIRE_ARG_COUNT(2); REQUIRE_POINT_ARG(1,position); REQUIRE_NUMBER_ARG(2,radians); self->teleport(position,radians); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyImpulse)
    METHOD_SIGNATURE("Change momentum immediately.", [this], 1, ({ [object Vector const&] impulse | [object Vector const&] impulse, [object Point const&] worldPoint }));
    try {
        REQUIRE_ARG_MIN_COUNT(1); REQUIRE_VECTOR_ARG(1,impulse);
        if(ARGC>1) { REQUIRE_POINT_ARG(2,worldPoint); self->applyImpulse(impulse,worldPoint); } else self->applyImpulse(impulse); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyAngularImpulse)
    METHOD_SIGNATURE("Change angular momentum immediately.", [this], 1, (number impulse));
    try {
        REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,impulse); self->applyAngularImpulse(impulse); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, ApplyForce)
    METHOD_SIGNATURE("world force for finite seconds; zero duration contributes nothing", [number uint], 2, ({ [object Vector const&] force, number durationSeconds, number delaySeconds = 0 | [object Vector const&] force, number durationSeconds, number delaySeconds, [object Point const&] worldPoint }));
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
    METHOD_SIGNATURE("persists until removeForce or stopAllForces", [number uint], 1, ([object Vector const&] force));
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
    METHOD_SIGNATURE("Clear active and delayed forces, torques and the physical drive.", [this], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->stopAllForces(); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, StopMoving)
    METHOD_SIGNATURE("Clear linear velocity.", [this], 0, ());
    try {
        REQUIRE_ARG_COUNT(0); self->stopMoving(); RETURN_THIS;
    } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, StopSpinning)
    METHOD_SIGNATURE("Clear angular velocity.", [this], 0, ());
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

METHOD_IMPL(PhysicsBody, GetConstraintCount)
    METHOD_SIGNATURE("", number, 0, ());
    try { REQUIRE_ARG_COUNT(0); RETURN_NUMBER(self->getConstraintCount()); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreatePinJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 1, ([object PhysicsBody&] other, [object Point const&] anchor = Point(0,0), [object Point const&] otherAnchor = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); OPTIONAL_POINT_ARG(2,anchor,Point()); OPTIONAL_POINT_ARG(3,otherAnchor,Point()); auto* result=&self->createPinJoint(*other,anchor,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreatePivotJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 1, ([object PhysicsBody&] other, [object Point const&] anchor = Point(0,0), [object Point const&] otherAnchor = Point(0,0)));
    try { REQUIRE_ARG_MIN_COUNT(1); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); OPTIONAL_POINT_ARG(2,anchor,Point()); OPTIONAL_POINT_ARG(3,otherAnchor,Point()); auto* result=&self->createPivotJoint(*other,anchor,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateSlideJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 5, ([object PhysicsBody&] other, [object Point const&] anchor, [object Point const&] otherAnchor, number minDistance, number maxDistance));
    try { REQUIRE_ARG_MIN_COUNT(5); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,anchor); REQUIRE_POINT_ARG(3,otherAnchor); REQUIRE_NUMBER_ARG(4,minDistance); REQUIRE_NUMBER_ARG(5,maxDistance); auto* result=&self->createSlideJoint(*other,anchor,otherAnchor,minDistance,maxDistance); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateGrooveJoint)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 4, ([object PhysicsBody&] other, [object Point const&] start, [object Point const&] end, [object Point const&] otherAnchor));
    try { REQUIRE_ARG_MIN_COUNT(4); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,start); REQUIRE_POINT_ARG(3,end); REQUIRE_POINT_ARG(4,otherAnchor); auto* result=&self->createGrooveJoint(*other,start,end,otherAnchor); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateSpring)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 6, ([object PhysicsBody&] other, [object Point const&] anchor, [object Point const&] otherAnchor, number restLength, number stiffness, number damping));
    try { REQUIRE_ARG_MIN_COUNT(6); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_POINT_ARG(2,anchor); REQUIRE_POINT_ARG(3,otherAnchor); REQUIRE_NUMBER_ARG(4,restLength); REQUIRE_NUMBER_ARG(5,stiffness); REQUIRE_NUMBER_ARG(6,damping); auto* result=&self->createSpring(*other,anchor,otherAnchor,restLength,stiffness,damping); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRotarySpring)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 4, ([object PhysicsBody&] other, number restAngle, number stiffness, number damping));
    try { REQUIRE_ARG_MIN_COUNT(4); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,restAngle); REQUIRE_NUMBER_ARG(3,stiffness); REQUIRE_NUMBER_ARG(4,damping); auto* result=&self->createRotarySpring(*other,restAngle,stiffness,damping); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRotaryLimit)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 3, ([object PhysicsBody&] other, number minAngle, number maxAngle));
    try { REQUIRE_ARG_MIN_COUNT(3); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,minAngle); REQUIRE_NUMBER_ARG(3,maxAngle); auto* result=&self->createRotaryLimit(*other,minAngle,maxAngle); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateRatchet)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 2, ([object PhysicsBody&] other, number interval, number phase = 0));
    try { REQUIRE_ARG_MIN_COUNT(2); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,interval); OPTIONAL_NUMBER_ARG(3,phase,0); auto* result=&self->createRatchet(*other,interval,phase); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateGear)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 2, ([object PhysicsBody&] other, number ratio, number phase = 0));
    try { REQUIRE_ARG_MIN_COUNT(2); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,ratio); OPTIONAL_NUMBER_ARG(3,phase,0); auto* result=&self->createGear(*other,ratio,phase); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, CreateMotor)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 3, ([object PhysicsBody&] other, number radiansPerSecond, number maxTorque));
    try { REQUIRE_ARG_MIN_COUNT(3); if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); REQUIRE_NUMBER_ARG(2,radiansPerSecond); REQUIRE_NUMBER_ARG(3,maxTorque); auto* result=&self->createMotor(*other,radiansPerSecond,maxTorque); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, GetConstraint)
    METHOD_SIGNATURE("", [object PhysicsConstraint&], 1, ([number uint] index));
    try { REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1,index); if(!std::isfinite(index)||index<0||index>4294967295.0||index!=std::floor(index)) { THROW_RANGE_ERR("Expected an unsigned 32-bit integer"); RETURN_NULL; } auto* result=&self->getConstraint(uint32_t(index)); RETURN_CPP_OBJECT(result,PhysicsConstraint); } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(PhysicsBody, Disconnect)
    METHOD_SIGNATURE("Disconnect this body's constraints.", [this], 0, ([object PhysicsBody*] other = null));
    try { if(ARGC==0||VALUE_IS_NULL(ARGV[0])) self->disconnect(); else { if(!COLLISION_ARGUMENT_IS(ARGV[0],true)) { THROW_TYPE_ERR("Expected a PhysicsBody"); RETURN_NULL; } REQUIRE_CPP_OBJECT_ARG(1,other,PhysicsBody); self->disconnect(other); } RETURN_THIS; } catch (const std::exception& error) { THROW_ERR(error.what()); }
    END

} // namespace pdg

/* @pdg-schema
{
  "name": "PhysicsBodyState",
  "value": {
    "kind": "record",
    "fields": {
      "x": {
        "type": "number"
      },
      "y": {
        "type": "number"
      },
      "rotation": {
        "type": "number"
      },
      "velocityX": {
        "type": "number"
      },
      "velocityY": {
        "type": "number"
      },
      "angularVelocity": {
        "type": "number"
      }
    }
  }
}
*/

/* @pdg-schema
{
  "name": "PhysicsDriveState",
  "value": {
    "kind": "record",
    "fields": {
      "enabled": {
        "type": "boolean"
      },
      "x": {
        "type": "number"
      },
      "y": {
        "type": "number"
      },
      "rotation": {
        "type": "number"
      },
      "maxForce": {
        "type": "number"
      },
      "maxTorque": {
        "type": "number"
      },
      "frequency": {
        "type": "number"
      },
      "dampingRatio": {
        "type": "number"
      },
      "forceX": {
        "type": "number"
      },
      "forceY": {
        "type": "number"
      },
      "torque": {
        "type": "number"
      },
      "positionError": {
        "type": "number"
      },
      "rotationError": {
        "type": "number"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "PhysicsBody.getState",
  "value": {
    "returns": {
      "schema": "PhysicsBodyState",
      "ownership": "owned"
    }
  }
}
*/

/* @pdg-contract
{
  "name": "PhysicsBody.getDriveState",
  "value": {
    "returns": {
      "schema": "PhysicsDriveState",
      "ownership": "owned"
    }
  }
}
*/
