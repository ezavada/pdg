// -----------------------------------------------
// physics_bindings.h
//
// Header file that contains physics-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for physics classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"

%#ifndef PDG_PHYSICS_BINDINGS_H_INCLUDED
%#define PDG_PHYSICS_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

%#ifdef PDG_USE_CHIPMUNK_PHYSICS


WRAPPER_CLASS(cpArbiter)
	METHOD(cpArbiter, IsFirstContact)
	METHOD(cpArbiter, GetCount)
	METHOD(cpArbiter, GetNormal)
	METHOD(cpArbiter, GetPointA)
	METHOD(cpArbiter, GetPointB)
	METHOD(cpArbiter, GetDepth)
DECL_END

WRAPPER_CLASS(cpConstraint)
	PROPERTY(cpConstraint, MaxForce)
	PROPERTY(cpConstraint, ErrorBias)
	PROPERTY(cpConstraint, MaxBias)
	PROPERTY(cpConstraint, Anchor)
	PROPERTY(cpConstraint, OtherAnchor)
	PROPERTY(cpConstraint, PinDist)
	PROPERTY(cpConstraint, SlideMinDist)
	PROPERTY(cpConstraint, SlideMaxDist)
	PROPERTY(cpConstraint, GrooveStart)
	PROPERTY(cpConstraint, GrooveEnd)
	PROPERTY(cpConstraint, SpringRestLength)
	PROPERTY(cpConstraint, SpringStiffness)
	PROPERTY(cpConstraint, SpringDamping)
	PROPERTY(cpConstraint, RotarySpringRestAngle)
	PROPERTY(cpConstraint, MinAngle)
	PROPERTY(cpConstraint, MaxAngle)
	PROPERTY(cpConstraint, RatchetAngle)
	PROPERTY(cpConstraint, RatchetPhase)
	PROPERTY(cpConstraint, RatchetInterval)
	PROPERTY(cpConstraint, GearRatio)
	PROPERTY(cpConstraint, GearInitialAngle)
	PROPERTY(cpConstraint, MotorSpinRate)
	METHOD(cpConstraint, GetType)	// return string of "pin, slide, etc..."
	METHOD(cpConstraint, ActivateBodies)
	METHOD(cpConstraint, GetImpulse)
	METHOD(cpConstraint, GetSprite)
	METHOD(cpConstraint, GetOtherSprite)
DECL_END

WRAPPER_CLASS(cpSpace)
	PROPERTY(cpSpace, IdleSpeedThreshold)
	PROPERTY(cpSpace, SleepTimeThreshold)
	PROPERTY(cpSpace, CollisionSlop)
	PROPERTY(cpSpace, CollisionBias)
	PROPERTY(cpSpace, CollisionPersistence)
	METHOD(cpSpace, UseSpatialHash)
	METHOD(cpSpace, ReindexStatic)
	METHOD(cpSpace, Step)
DECL_END

%#endif // PDG_PHYSICS_BINDINGS_H_INCLUDED 

} // namespace pdg
%#endif

