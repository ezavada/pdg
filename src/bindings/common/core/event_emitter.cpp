// -----------------------------------------------
// event_emitter.cpp
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
//MARK: IEventHandler
// ========================================================================================

BINDING_INITIALIZER_IMPL(IEventHandler)
EXPORT_CLASS_SYMBOLS("IEventHandler", IEventHandler, , , );
END

CLEANUP_IMPL(IEventHandler)


// ========================================================================================
//MARK: EventEmitter
// ========================================================================================

BINDING_INITIALIZER_IMPL(EventEmitter)
    EXPORT_CLASS_SYMBOLS("EventEmitter", EventEmitter, , ,
    	// method section
		HAS_EMITTER_METHODS(EventEmitter)
    );
	END
EMITTER_BASE_CLASS_IMPL(EventEmitter)

CPP_MANAGED_CONSTRUCTOR_IMPL(EventEmitter)
    return new EventEmitter();
	END

} // namespace pdg

/* @pdg-member
{
  "name": "EventEmitter.EventEmitter",
  "type": "constructor",
  "params": [],
  "returns": "object EventEmitter",
  "brief": "Create a EventEmitter instance."
}
*/

// @pdg-member {"name":"EventEmitter.addHandler","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"EventEmitter.removeHandler","native_binding":{"allow_raw_pointers":true}}

// @pdg-class {"name":"EventEmitter","native_binding":{"browser":{"base":null,"generate":true,"constructors":[{"types":[]}],"support_bindings":[{"name":"_addNativeEventBridge","symbol":"pdg::emscriptenEventEmitterAddBridge"}]}}}
