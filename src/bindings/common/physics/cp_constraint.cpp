// -----------------------------------------------
// cp_constraint.cpp
//
// cpConstraint bindings for pdg classes 
// that are exposed to scripting languages without
// any specific language dependencies
//
// This file is parsed by tools/gen-script_interface.sh
// to generate an interface file
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

%#include <sstream>
%#include <cmath>
%#include <cstdlib>

namespace pdg {

// ========================================================================================
//MARK: cpConstraint
// ========================================================================================

#define IF_CONSTRAINT_TYPE(type) \
	if (strcmp((const char*)cpConstraintGetUserData(self), #type) == 0)

#define REQUIRE_CONSTRAINT_TYPE(prop, type) \
	if (strcmp((const char*)cpConstraintGetUserData(self), #type) != 0) { CR \
		std::ostringstream msg; CR \
        msg << "cpConstraint.set" #prop "() not valid for constraint type "  CR \
                << (const char*)cpConstraintGetUserData(self); CR \
		THROW_TYPE_ERR(msg.str().c_str()) ; CR \
	}

#define UNDEFINED_UNLESS_CONSTRAINT_TYPE(type) \
	if (strcmp((const char*)cpConstraintGetUserData(self), #type) != 0) { CR \
		RETURN_UNDEFINED; CR \
	}

#define CONSTRAINT_CUSTOM_PROPERTY_IMPL(prop, type, contype, cpgetcode, cpsetcode) \
CUSTOM_GETTER_IMPL(cpConstraint, prop, type, 0, , , \
	UNDEFINED_UNLESS_CONSTRAINT_TYPE(contype); CR \
	cpgetcode, () ) \
CUSTOM_SETTER_IMPL(cpConstraint, prop, type, 1, , , \
	REQUIRE_CONSTRAINT_TYPE(prop, contype); CR \
	cpsetcode)

#define CONSTRAINT_PROPERTY_IMPL(prop, contype, cpgetcall, cpsetcall) \
	CONSTRAINT_CUSTOM_PROPERTY_IMPL(prop, NUMBER, contype, cpFloat the##prop = cpgetcall(self), cpsetcall(self, the##prop))

WRAPPER_INITIALIZER_IMPL_CUSTOM(cpConstraint, ) 
    EXPORT_CLASS_SYMBOLS("CpConstraint", cpConstraint, , ,
    	// method section
		HAS_GETTER(cpConstraint, Type)	// return string of "pin, slide, etc..."
		HAS_METHOD(cpConstraint, "activateBodies", ActivateBodies)
		HAS_GETTER(cpConstraint, Impulse)
		HAS_PROPERTY(cpConstraint, MaxForce)
		HAS_PROPERTY(cpConstraint, ErrorBias)
		HAS_PROPERTY(cpConstraint, MaxBias)
		HAS_GETTER(cpConstraint, Sprite)
		HAS_GETTER(cpConstraint, OtherSprite)
		HAS_PROPERTY(cpConstraint, Anchor)  				// Anchr1: pin, slide, pivot, spring, 
		HAS_PROPERTY(cpConstraint, OtherAnchor) 			// Anchr2: pin, slide, pivot, groove, spring
		HAS_PROPERTY(cpConstraint, PinDist)					// Dist: pin
		HAS_PROPERTY(cpConstraint, SpringStiffness) 		// Stiffness: spring, rotary spring
		HAS_PROPERTY(cpConstraint, SpringDamping)			// Damping: spring, rotary spring
		HAS_PROPERTY(cpConstraint, SlideMinDist)			// Min: slide
		HAS_PROPERTY(cpConstraint, SlideMaxDist)			// Max: slide
		HAS_PROPERTY(cpConstraint, GrooveStart)				// GrooveA: groove
		HAS_PROPERTY(cpConstraint, GrooveEnd)				// GrooveB: groove
		HAS_PROPERTY(cpConstraint, SpringRestLength)		// RestLength: spring
		HAS_PROPERTY(cpConstraint, RotarySpringRestAngle)  	// Rest Angle: rotary spring
		HAS_PROPERTY(cpConstraint, MinAngle)				// Min: rotary limit
		HAS_PROPERTY(cpConstraint, MaxAngle)				// Max: rotary limit
		HAS_PROPERTY(cpConstraint, RatchetAngle)			// Angle: ratchet
		HAS_PROPERTY(cpConstraint, RatchetPhase)			// Phase: ratchet
		HAS_PROPERTY(cpConstraint, RatchetInterval)			// Ratchet: ratchet
		HAS_PROPERTY(cpConstraint, GearRatio)				// Ratio: gear
		HAS_PROPERTY(cpConstraint, GearInitialAngle)		// Phase: gear
		HAS_PROPERTY(cpConstraint, MotorSpinRate)			// Rate: motor
    );
	END

CUSTOM_GETTER_IMPL(cpConstraint, Type, STRING, 0, , ,
	const char* theType = (const char*)cpConstraintGetUserData(self), () );
CP_GETTER_IMPL(cpConstraint, Impulse, NUMBER)
CP_PROPERTY_IMPL(cpConstraint, MaxForce, NUMBER)
CP_PROPERTY_IMPL(cpConstraint, ErrorBias, NUMBER)
CP_PROPERTY_IMPL(cpConstraint, MaxBias, NUMBER)
METHOD_IMPL(cpConstraint, ActivateBodies);
	METHOD_SIGNATURE("", undefined, 0, ());
	REQUIRE_ARG_COUNT(0);
	cpConstraintActivateBodies(self);
	NO_RETURN;
	END
METHOD_IMPL(cpConstraint, GetSprite);
	METHOD_SIGNATURE("", [object Sprite], 0, ());
	REQUIRE_ARG_COUNT(0);
	cpBody* body = cpConstraintGetBodyA(self);
	Sprite* sprite = (Sprite*) cpBodyGetUserData(body);
	RETURN_CPP_OBJECT(sprite, Sprite);
	END
METHOD_IMPL(cpConstraint, GetOtherSprite);
	METHOD_SIGNATURE("", [object Sprite], 0, ());
	REQUIRE_ARG_COUNT(0);
	cpBody* body = cpConstraintGetBodyB(self);
	Sprite* otherSprite = (Sprite*) cpBodyGetUserData(body);
	RETURN_CPP_OBJECT(otherSprite, Sprite);
	END
CUSTOM_GETTER_IMPL(cpConstraint, Anchor, OFFSET, 0, , ,
	cpVect anchor; CR
	IF_CONSTRAINT_TYPE(PinJoint) { CR
		anchor = cpPinJointGetAnchorA(self);
	} else IF_CONSTRAINT_TYPE(SlideJoint) { CR
		anchor = cpSlideJointGetAnchorA(self);
	} else IF_CONSTRAINT_TYPE(PivotJoint) { CR
		anchor = cpPivotJointGetAnchorA(self);
	} else IF_CONSTRAINT_TYPE(SpringJoint) { CR
		anchor = cpDampedSpringGetAnchorA(self);
	} else { CR
		RETURN_UNDEFINED; CR
	} CR
	pdg::Offset theAnchor(anchor.x, anchor.y), () )
CUSTOM_SETTER_IMPL(cpConstraint, Anchor, OFFSET, 1, , ,
	cpVect anchor = cpv(theAnchor.x, theAnchor.y); CR
	IF_CONSTRAINT_TYPE(PinJoint) { CR
		cpPinJointSetAnchorA(self, anchor);
	} else IF_CONSTRAINT_TYPE(SlideJoint) { CR
		cpSlideJointSetAnchorA(self, anchor);
	} else IF_CONSTRAINT_TYPE(PivotJoint) { CR
		cpPivotJointSetAnchorA(self, anchor);
	} else IF_CONSTRAINT_TYPE(SpringJoint) { CR
		cpDampedSpringSetAnchorA(self, anchor);
	} else { CR
		std::ostringstream msg; CR
        msg << "cpConstraint.setAnchor() not valid for constraint type "  CR
                << (const char*)cpConstraintGetUserData(self); CR
		THROW_TYPE_ERR(msg.str().c_str()) ; CR
	})
CUSTOM_GETTER_IMPL(cpConstraint, OtherAnchor, OFFSET, 0, , ,
	cpVect anchor; CR
	IF_CONSTRAINT_TYPE(PinJoint) { CR
		anchor = cpPinJointGetAnchorB(self);
	} else IF_CONSTRAINT_TYPE(SlideJoint) { CR
		anchor = cpSlideJointGetAnchorB(self);
	} else IF_CONSTRAINT_TYPE(PivotJoint) { CR
		anchor = cpPivotJointGetAnchorB(self);
	} else IF_CONSTRAINT_TYPE(GrooveJoint) { CR
		anchor = cpGrooveJointGetAnchorB(self);
	} else IF_CONSTRAINT_TYPE(SpringJoint) { CR
		anchor = cpDampedSpringGetAnchorB(self);
	} else { CR
		RETURN_UNDEFINED; CR
	} CR
	pdg::Offset theOtherAnchor(anchor.x, anchor.y), () )
CUSTOM_SETTER_IMPL(cpConstraint, OtherAnchor, OFFSET, 1, , ,
	cpVect anchor = cpv(theOtherAnchor.x, theOtherAnchor.y); CR
	IF_CONSTRAINT_TYPE(PinJoint) { CR
		cpPinJointSetAnchorB(self, anchor);
	} else IF_CONSTRAINT_TYPE(SlideJoint) { CR
		cpSlideJointSetAnchorB(self, anchor);
	} else IF_CONSTRAINT_TYPE(PivotJoint) { CR
		cpPivotJointSetAnchorB(self, anchor);
	} else IF_CONSTRAINT_TYPE(GrooveJoint) { CR
		cpGrooveJointSetAnchorB(self, anchor);
	} else IF_CONSTRAINT_TYPE(SpringJoint) { CR
		cpDampedSpringSetAnchorB(self, anchor);
	} else { CR
		std::ostringstream msg; CR
        msg << "cpConstraint.setOtherAnchor() not valid for constraint type "  CR
                << (const char*)cpConstraintGetUserData(self); CR
		THROW_TYPE_ERR(msg.str().c_str()) ; CR
	})
CONSTRAINT_PROPERTY_IMPL(PinDist, PinJoint, cpPinJointGetDist, cpPinJointSetDist)
CONSTRAINT_PROPERTY_IMPL(SlideMinDist, SlideJoint, cpSlideJointGetMin, cpSlideJointSetMin)
CONSTRAINT_PROPERTY_IMPL(SlideMaxDist, SlideJoint, cpSlideJointGetMax, cpSlideJointSetMax)
CONSTRAINT_CUSTOM_PROPERTY_IMPL(GrooveStart, OFFSET, GrooveJoint, 
	cpVect v = cpGrooveJointGetGrooveA(self); CR
	pdg::Offset theGrooveStart(v.x, v.y), 
	cpGrooveJointSetGrooveA(self, cpv(theGrooveStart.x, theGrooveStart.y)))
CONSTRAINT_CUSTOM_PROPERTY_IMPL(GrooveEnd, OFFSET, GrooveJoint,
	cpVect v = cpGrooveJointGetGrooveB(self); CR
	pdg::Offset theGrooveEnd(v.x, v.y), 
	cpGrooveJointSetGrooveB(self, cpv(theGrooveEnd.x, theGrooveEnd.y)))
CONSTRAINT_PROPERTY_IMPL(SpringRestLength, SpringJoint, cpDampedSpringGetRestLength, cpDampedSpringSetRestLength)
CONSTRAINT_PROPERTY_IMPL(RotarySpringRestAngle, RotarySpring, cpDampedRotarySpringGetRestAngle, cpDampedRotarySpringSetRestAngle)
CONSTRAINT_PROPERTY_IMPL(MinAngle, RotaryLimit, cpRotaryLimitJointGetMin, cpRotaryLimitJointSetMin)
CONSTRAINT_PROPERTY_IMPL(MaxAngle, RotaryLimit, cpRotaryLimitJointGetMax, cpRotaryLimitJointSetMax)
CONSTRAINT_PROPERTY_IMPL(RatchetAngle, Ratchet, cpRatchetJointGetAngle, cpRatchetJointSetAngle)
CONSTRAINT_PROPERTY_IMPL(RatchetPhase, Ratchet, cpRatchetJointGetPhase, cpRatchetJointSetPhase)
CONSTRAINT_PROPERTY_IMPL(RatchetInterval, Ratchet, cpRatchetJointGetRatchet, cpRatchetJointSetRatchet)
CONSTRAINT_PROPERTY_IMPL(GearRatio, Gear, cpGearJointGetRatio, cpGearJointSetRatio)
CONSTRAINT_PROPERTY_IMPL(GearInitialAngle, Gear, cpGearJointGetPhase, cpGearJointSetPhase)
CONSTRAINT_PROPERTY_IMPL(MotorSpinRate, Motor, cpSimpleMotorGetRate, cpSimpleMotorSetRate)
CUSTOM_GETTER_IMPL(cpConstraint, SpringStiffness, NUMBER, 0, , ,
	cpFloat theSpringStiffness; CR
	IF_CONSTRAINT_TYPE(SpringJoint) { CR
		theSpringStiffness = cpDampedSpringGetStiffness(self);
	} else IF_CONSTRAINT_TYPE(RotarySpring) { CR
		theSpringStiffness = cpDampedRotarySpringGetStiffness(self);
	} else { CR
		RETURN_UNDEFINED; CR
	}, () )
CUSTOM_SETTER_IMPL(cpConstraint, SpringStiffness, NUMBER, 1, , ,
	IF_CONSTRAINT_TYPE(SpringJoint) { CR
		cpDampedSpringSetStiffness(self, theSpringStiffness);
	} else IF_CONSTRAINT_TYPE(RotarySpring) { CR
		cpDampedRotarySpringSetStiffness(self, theSpringStiffness);
	} else { CR
		std::ostringstream msg; CR
        msg << "cpConstraint.setSpringStiffness() not valid for constraint type "  CR
                << (const char*)cpConstraintGetUserData(self); CR
		THROW_TYPE_ERR(msg.str().c_str()) ; CR
	})
CUSTOM_GETTER_IMPL(cpConstraint, SpringDamping, NUMBER, 0, , ,
	cpFloat theSpringDamping; CR
	IF_CONSTRAINT_TYPE(SpringJoint) { CR
		theSpringDamping = cpDampedSpringGetDamping(self);
	} else IF_CONSTRAINT_TYPE(RotarySpring) { CR
		theSpringDamping = cpDampedRotarySpringGetDamping(self);
	} else { CR
		RETURN_UNDEFINED; CR
	}, () )
CUSTOM_SETTER_IMPL(cpConstraint, SpringDamping, NUMBER, 1, , ,
	IF_CONSTRAINT_TYPE(SpringJoint) { CR
		cpDampedSpringSetDamping(self, theSpringDamping);
	} else IF_CONSTRAINT_TYPE(RotarySpring) { CR
		cpDampedRotarySpringSetDamping(self, theSpringDamping);
	} else { CR
		std::ostringstream msg; CR
        msg << "cpConstraint.setSpringDamping() not valid for constraint type "  CR
                << (const char*)cpConstraintGetUserData(self); CR
		THROW_TYPE_ERR(msg.str().c_str()) ; CR
	})

CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpConstraint, cppPtr_ = nullptr; CR )
    SAVE_ERR("CpConstraint cannot be created directly, it is only returned from certain Sprite calls.");
 	return 0;
	END

} // end pdg namespace 