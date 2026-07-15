// -----------------------------------------------
// serializable.cpp
//
// Implementation file for Serializable bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    
// ========================================================================================
//MARK: ISerializable
// ========================================================================================

BINDING_INITIALIZER_IMPL(ISerializable) 
    EXPORT_CLASS_SYMBOLS("ISerializable", ISerializable, , , );
	END


CLEANUP_IMPL(ISerializable)


} // pdg namespace
