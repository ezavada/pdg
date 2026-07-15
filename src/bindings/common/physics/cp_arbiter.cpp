// -----------------------------------------------
// cp_arbiter.cpp
//
// cpArbiter bindings for pdg classes 
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
//MARK: cpArbiter
// ========================================================================================

WRAPPER_INITIALIZER_IMPL_CUSTOM(cpArbiter, ) 
    EXPORT_CLASS_SYMBOLS("CpArbiter", cpArbiter, , ,
    	// method section
		HAS_METHOD(cpArbiter, "isFirstContact", IsFirstContact)
		HAS_GETTER(cpArbiter, Count)
		HAS_GETTER(cpArbiter, Normal)
		HAS_GETTER(cpArbiter, PointA)
		HAS_GETTER(cpArbiter, PointB)
		HAS_GETTER(cpArbiter, Depth)
    );
	END

METHOD_IMPL(cpArbiter, IsFirstContact)
	METHOD_SIGNATURE("true if this is the first moment of contact between the objects, false if part of an ongoing collison", 
		boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
	cpBool isFirst = cpArbiterIsFirstContact(self);
	RETURN_BOOL(isFirst);
	END
CP_GETTER_IMPL(cpArbiter, Count, INTEGER)
CUSTOM_GETTER_IMPL(cpArbiter, Normal, VECTOR, 0, , ,
	cpVect nv = cpArbiterGetNormal(self); CR
	pdg::Vector theNormal(nv.x, nv.y), () )
CUSTOM_GETTER_IMPL(cpArbiter, PointA, POINT, 1, ,
	REQUIRE_INT32_ARG(1, i); CR ,
	cpVect pt = cpArbiterGetPointA(self, i); CR
	pdg::Point thePointA(pt.x, pt.y), ([number int] i) )
CUSTOM_GETTER_IMPL(cpArbiter, PointB, POINT, 1, ,
	REQUIRE_INT32_ARG(1, i); CR ,
	cpVect pt = cpArbiterGetPointB(self, i); CR
	pdg::Point thePointB(pt.x, pt.y), ([number int] i) )
CUSTOM_GETTER_IMPL(cpArbiter, Depth, NUMBER, 1, ,
	REQUIRE_INT32_ARG(1, i); CR ,
	cpFloat theDepth = cpArbiterGetDepth(self, i), ([number int] i) )

CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpArbiter, cppPtr_ = nullptr; CR )
    SAVE_ERR("CpArbiter cannot be created directly, it is only returned from certain Sprite calls.");
 	return 0;
	END

} // end pdg namespace 