// -----------------------------------------------
// mem_block.cpp
//
// Implementation file for MemBlock bindings
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
//MARK: MemBlock
// ========================================================================================

BINDING_INITIALIZER_IMPL(MemBlock)
    EXPORT_CLASS_SYMBOLS("MemBlock", MemBlock, , ,
    	// method section
		HAS_METHOD(MemBlock, "getData", GetData)
		HAS_METHOD(MemBlock, "getDataSize", GetDataSize)
		HAS_METHOD(MemBlock, "getByte", GetByte)
		HAS_METHOD(MemBlock, "getBytes", GetBytes)
    );
	END
METHOD_IMPL(MemBlock, GetData)
	METHOD_SIGNATURE("", [string Binary], 0, ())
    REQUIRE_ARG_COUNT(0);
	VALUE resultVal = EncodeBinary(self->ptr, self->bytes);
	RETURN(resultVal);
	END
METHOD_IMPL(MemBlock, GetDataSize)
	METHOD_SIGNATURE("", number, 0, ())
	REQUIRE_ARG_COUNT(0);
	RETURN_UINT32(self->bytes);
	END
METHOD_IMPL(MemBlock, GetByte)
	METHOD_SIGNATURE("", number, 1, ([number uint] i))
    REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, i);
	RETURN_UNSIGNED(self->ptr[i]);
	END
METHOD_IMPL(MemBlock, GetBytes)
	METHOD_SIGNATURE("", [string Binary], 2, ([number uint] start, [number uint] len))
    REQUIRE_ARG_COUNT(2);
    REQUIRE_UINT32_ARG(1, start);
    REQUIRE_UINT32_ARG(2, len);
	VALUE resultVal = EncodeBinary(self->ptr + start, len);
	RETURN(resultVal);
	END

CLEANUP_IMPL(MemBlock)

CPP_MANAGED_CONSTRUCTOR_IMPL(MemBlock)
	return new MemBlock(0, 0, false);
	END

} // pdg namespace
