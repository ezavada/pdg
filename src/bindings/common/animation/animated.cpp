// -----------------------------------------------
// animated.cpp
//
// Implementation file for Animated bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "animation_impl_macros.h"

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
  float customEasing##n(ms_delta ut, float b, float c, ms_delta ud) {	CR \
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

BINDING_INITIALIZER_IMPL(IAnimationHelper) 
    EXPORT_CLASS_SYMBOLS("IAnimationHelper", IAnimationHelper, , , );
	END

CLEANUP_IMPL(IAnimationHelper)


// ========================================================================================
//MARK: Animated
// ========================================================================================


WRAPPER_INITIALIZER_IMPL_CUSTOM(Animated,
  OBJECT_SAVE(cppObj->mAnimatedScriptObj, obj) )
    EXPORT_CLASS_SYMBOLS("Animated", Animated, , , 
		HAS_ANIMATED_METHODS(Animated)
		HAS_METHOD(Animated, "animate", Animate)
    );
	END

ANIMATED_BASE_CLASS_IMPL(Animated)
METHOD_IMPL(Animated, Animate)
	METHOD_SIGNATURE("", boolean, 1, ([number int] msElapsed));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, msElapsed);
	bool result = self->animate(msElapsed);
	RETURN_BOOL(result);
	END

CLEANUP_IMPL(Animated)

CPP_MANAGED_CONSTRUCTOR_IMPL(Animated)
    return new Animated();
	END

} // pdg namespace
