// -----------------------------------------------
// resource_manager.cpp
//
// Implementation file for ResourceManager bindings
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
//MARK: Resource Manager
// ========================================================================================

//DECLARE_SYMBOL(name);


SINGLETON_MANAGER_INITIALIZER_IMPL(ResourceManager, "res")
    EXPORT_CLASS_SYMBOLS("ResourceManager", ResourceManager,
	   ,// property section
		HAS_PROPERTY(ResourceManager, Language)
	   ,// method section
		HAS_METHOD(ResourceManager, "openResourceFile", OpenResourceFile)
		HAS_METHOD(ResourceManager, "closeResourceFile", CloseResourceFile)
		HAS_METHOD(ResourceManager, "getImage", GetImage)
		HAS_METHOD(ResourceManager, "getImageStrip", GetImageStrip)
	%#ifndef PDG_NO_SOUND CR
		HAS_METHOD(ResourceManager, "getSound", GetSound)
	%#endif CR // !PDG_NO_SOUND
		HAS_METHOD(ResourceManager, "getString", GetString)
		HAS_METHOD(ResourceManager, "getResourceSize", GetResourceSize)
		HAS_METHOD(ResourceManager, "getResource", GetResource)
		HAS_METHOD(ResourceManager, "getResourcePaths", GetResourcePaths)
    );
	END

PROPERTY_IMPL(ResourceManager, Language, STRING)
METHOD_IMPL(ResourceManager, OpenResourceFile)
	METHOD_SIGNATURE("", number, 1, (string filename));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, filename);
	int refNum = self->openResourceFile(filename);
	RETURN_INTEGER(refNum);
	END
METHOD_IMPL(ResourceManager, CloseResourceFile)
	METHOD_SIGNATURE("", undefined, 1, ([number int] refNum));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, refNum);
	self->closeResourceFile(refNum);
	NO_RETURN;
	END
METHOD_IMPL(ResourceManager, GetString)
	METHOD_SIGNATURE("", string, 2, ([number int] id, [number int] substring = -1));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_INT32_ARG(1, id);
	OPTIONAL_INT32_ARG(2, substring, -1);
	std::string ioStr;
	const char* outStr = self->getString(ioStr, id, substring);
	RETURN_STRING(outStr);
	END
METHOD_IMPL(ResourceManager, GetResourceSize)
	METHOD_SIGNATURE("", number, 1, (string resourceName));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, resourceName);
	unsigned long resSize = self->getResourceSize(resourceName);
	RETURN_UNSIGNED(resSize);
	END
METHOD_IMPL(ResourceManager, GetResource)
	METHOD_SIGNATURE("", [string Binary], 1, (string resourceName));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_STRING_ARG(1, resourceName);
	OPTIONAL_INT32_ARG(2, maxSize, -1);
	unsigned long bufferSize;
	if (maxSize < 0) {
		bufferSize = self->getResourceSize(resourceName);
	} else {
		bufferSize = maxSize;
	}
	uint8* buffer = (uint8*) std::malloc(bufferSize);
	bool loaded = self->getResource(resourceName, buffer, bufferSize);
	if (!loaded) {
		std::free(buffer);
		RETURN_FALSE;
	}
	VALUE resultVal = EncodeBinary(buffer, bufferSize);
	std::free(buffer);
	RETURN(resultVal);
	END
METHOD_IMPL(ResourceManager, GetResourcePaths)
	METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
	std::string outStr = self->getResourcePaths();
	RETURN_STRING(outStr.c_str());
	END

CPP_SINGLETON_CONSTRUCTOR_IMPL(ResourceManager)


} // pdg namespace

