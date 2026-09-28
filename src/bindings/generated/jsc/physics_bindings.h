// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/physics_bindings.h
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#ifndef PDG_PHYSICS_BINDINGS_H_INCLUDED
#define PDG_PHYSICS_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

#ifdef PDG_USE_CHIPMUNK_PHYSICS

    extern cpArbiter* New_cpArbiter(size_t, const JSValueRef[]);

    extern JSObjectRef cpArbiter_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef cpArbiter_class();
    extern JSObjectRef cpArbiter_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline cpArbiter* cpArbiter_getCppObject(JSObjectRef obj)
    {
        return static_cast<cpArbiter*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef cpArbiter_newFromCpp(JSContextRef, cpArbiter*);

    extern JSValueRef cpArbiter_IsFirstContact(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpArbiter_GetCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpArbiter_GetNormal(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpArbiter_GetPointA(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpArbiter_GetPointB(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpArbiter_GetDepth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern cpConstraint* New_cpConstraint(size_t, const JSValueRef[]);

    extern JSObjectRef cpConstraint_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef cpConstraint_class();
    extern JSObjectRef cpConstraint_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline cpConstraint* cpConstraint_getCppObject(JSObjectRef obj)
    {
        return static_cast<cpConstraint*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef cpConstraint_newFromCpp(JSContextRef, cpConstraint*);

    extern JSValueRef cpConstraint_GetMaxForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetMaxForce(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetErrorBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetErrorBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetMaxBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetMaxBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetAnchor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetAnchor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetOtherAnchor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetOtherAnchor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetPinDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetPinDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSlideMinDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetSlideMinDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSlideMaxDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetSlideMaxDist(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetGrooveStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetGrooveStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetGrooveEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetGrooveEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSpringRestLength(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetSpringRestLength(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSpringStiffness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetSpringStiffness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSpringDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetSpringDamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetRotarySpringRestAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetRotarySpringRestAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetMinAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetMinAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetMaxAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetMaxAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetRatchetAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetRatchetAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetRatchetPhase(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetRatchetPhase(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetRatchetInterval(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetRatchetInterval(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetGearRatio(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetGearRatio(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetGearInitialAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetGearInitialAngle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetMotorSpinRate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_SetMotorSpinRate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_ActivateBodies(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetImpulse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpConstraint_GetOtherSprite(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern cpSpace* New_cpSpace(size_t, const JSValueRef[]);

    extern JSObjectRef cpSpace_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef cpSpace_class();
    extern JSObjectRef cpSpace_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline cpSpace* cpSpace_getCppObject(JSObjectRef obj)
    {
        return static_cast<cpSpace*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef cpSpace_newFromCpp(JSContextRef, cpSpace*);

    extern JSValueRef cpSpace_GetIdleSpeedThreshold(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_SetIdleSpeedThreshold(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_GetSleepTimeThreshold(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_SetSleepTimeThreshold(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_GetCollisionSlop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_SetCollisionSlop(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_GetCollisionBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_SetCollisionBias(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_GetCollisionPersistence(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_SetCollisionPersistence(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_UseSpatialHash(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_ReindexStatic(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef cpSpace_Step(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

}
#endif
