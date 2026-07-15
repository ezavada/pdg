// -----------------------------------------------
// cp_space.cpp
//
// cpSpace bindings for pdg classes 
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
//MARK: cpSpace
// ========================================================================================

WRAPPER_INITIALIZER_IMPL_CUSTOM(cpSpace, ) 
    EXPORT_CLASS_SYMBOLS("CpSpace", cpSpace, , ,
    	// method section
		HAS_METHOD(cpSpace, "useSpatialHash", UseSpatialHash)
		HAS_METHOD(cpSpace, "reindexStatic", ReindexStatic)
		HAS_METHOD(cpSpace, "step", Step)
		HAS_PROPERTY(cpSpace, IdleSpeedThreshold)
		HAS_PROPERTY(cpSpace, SleepTimeThreshold)
		HAS_PROPERTY(cpSpace, CollisionSlop)
		HAS_PROPERTY(cpSpace, CollisionBias)
		HAS_PROPERTY(cpSpace, CollisionPersistence)
    );
	END
METHOD_IMPL(cpSpace, UseSpatialHash)
	METHOD_SIGNATURE("", undefined, 2, (number dim, [number int] count));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_NUMBER_ARG(1, dim);
    REQUIRE_INT32_ARG(2, count);
	cpSpaceUseSpatialHash(self, dim, count);
	NO_RETURN;
	END
METHOD_IMPL(cpSpace, ReindexStatic)
	METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
	cpSpaceReindexStatic(self);
	NO_RETURN;
	END
METHOD_IMPL(cpSpace, Step)
	METHOD_SIGNATURE("", undefined, 1, (number dt));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, dt);
	cpSpaceStep(self, dt);
	NO_RETURN;
	END
CP_PROPERTY_IMPL(cpSpace, IdleSpeedThreshold, NUMBER)
CP_PROPERTY_IMPL(cpSpace, SleepTimeThreshold, NUMBER)
CP_PROPERTY_IMPL(cpSpace, CollisionSlop, NUMBER)
CP_PROPERTY_IMPL(cpSpace, CollisionBias, NUMBER)
CP_PROPERTY_IMPL(cpSpace, CollisionPersistence, NUMBER)

CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpSpace, cppPtr_ = nullptr; CR )
    SAVE_ERR("CpSpace cannot be created directly, it is only returned from certain Sprite calls.");
 	return 0;
	END

} // end pdg namespace 