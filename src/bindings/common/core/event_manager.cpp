// -----------------------------------------------
// event_manager.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "core_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {

// ========================================================================================
//MARK: Event Manager
// ========================================================================================

SINGLETON_MANAGER_INITIALIZER_IMPL(EventManager, "evt")
    EXPORT_CLASS_SYMBOLS("EventManager", EventManager, , ,
    	// method section
		HAS_EMITTER_METHODS(EventManager)
		HAS_METHOD(EventManager, "isKeyDown", IsKeyDown)
		HAS_METHOD(EventManager, "isRawKeyDown", IsRawKeyDown)
		HAS_METHOD(EventManager, "isButtonDown", IsButtonDown)
		HAS_METHOD(EventManager, "getDeviceOrientation", GetDeviceOrientation) // not yet implemented in C++
    );
	END

EMITTER_BASE_CLASS_IMPL(EventManager)
STATIC_METHOD_IMPL(EventManager, IsRawKeyDown)
	METHOD_SIGNATURE("", boolean, 1, ([number int] keyCode));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, keyCode);
	RETURN_BOOL( OS::isRawKeyDown(keyCode) );
	END
STATIC_METHOD_IMPL(EventManager, IsButtonDown)
	METHOD_SIGNATURE("", boolean, 1, ([number int] buttonNumber = 0));
    OPTIONAL_INT32_ARG(1, buttonNumber, 0);
	RETURN_BOOL( OS::isButtonDown(buttonNumber) );
	END

CPP_SINGLETON_CONSTRUCTOR_IMPL(EventManager)

} // namespace pdg

// @pdg-class {"name":"EventManager","native_binding":{"browser":{"generate":true,"base":null,"support_bindings":[{"name":"_addNativeEventBridge","symbol":"pdg::emscriptenEventManagerAddEventBridge"}]}}}

// @pdg-member {"name":"EventManager.getDeviceOrientation","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"EventManager.isButtonDown","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"EventManager.isKeyDown","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"EventManager.isRawKeyDown","native_binding":{"browser":{"generate":false}}}
