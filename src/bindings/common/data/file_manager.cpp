// -----------------------------------------------
// file_manager.cpp
//
// Implementation file for FileManager bindings
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
//MARK: FileManager
// ========================================================================================

DECLARE_SYMBOL(nodeName);
DECLARE_SYMBOL(isDirectory);
DECLARE_SYMBOL(found);

FACADE_INITIALIZER_IMPL(FileManager)
    EXPORT_CLASS_SYMBOLS("FileManager", FileManager, , ,
    	// method section
		HAS_METHOD(FileManager, "findFirst", FindFirst)
		HAS_METHOD(FileManager, "findNext", FindNext)
		HAS_METHOD(FileManager, "findClose", FindClose)
		HAS_GETTER(FileManager, ApplicationDataDirectory)
		HAS_GETTER(FileManager, ApplicationDirectory)
		HAS_GETTER(FileManager, ApplicationResourceDirectory)
    );
	END

SCRIPT_METHOD_IMPL(FileManager, FindFirst)
	METHOD_SIGNATURE("", object, 1, (string inFindName));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_STRING_ARG(1, inFindName);
    FindDataT* ioFindDataPtr = new FindDataT;
	bool found = OS::findFirst(inFindName, *ioFindDataPtr);
	OBJECT_REF jsFindData = OBJECT_CREATE_EMPTY(ioFindDataPtr);
	VALUE nodeName = STR2VAL(ioFindDataPtr->nodeName);
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(nodeName), nodeName);
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(isDirectory), BOOL2VAL(ioFindDataPtr->isDirectory));
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(found), BOOL2VAL(found));
	RETURN_OBJECT(jsFindData);
	END
SCRIPT_METHOD_IMPL(FileManager, FindNext)
	METHOD_SIGNATURE("", object, 1, (object inFindData));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, jsFindData);
	FindDataT* ioFindDataPtr = static_cast<FindDataT*>(OBJECT_PRIVATE_DATA(jsFindData));
	if (!ioFindDataPtr) {
		THROW_TYPE_ERR("findNext must only be called with the object returned by findFirst");
	}
	bool found = OS::findNext(*ioFindDataPtr);
	VALUE nodeName = STR2VAL(ioFindDataPtr->nodeName);
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(nodeName), nodeName);
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(isDirectory), BOOL2VAL(ioFindDataPtr->isDirectory));
	OBJECT_SET_PROPERTY_VALUE(jsFindData, SYMBOL(found), BOOL2VAL(found));
	RETURN_BOOL(found);
	END
SCRIPT_METHOD_IMPL(FileManager, FindClose)
	METHOD_SIGNATURE("", undefined, 1, (object inFindData));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, jsFindData);
	FindDataT* ioFindDataPtr = static_cast<FindDataT*>(OBJECT_PRIVATE_DATA(jsFindData));
	if (!ioFindDataPtr) {
		THROW_TYPE_ERR("findClose must only be called with the object returned by findFirst");
	}
	OS::findClose(*ioFindDataPtr);
	delete ioFindDataPtr;
	NO_RETURN;
	END
SCRIPT_METHOD_IMPL(FileManager, GetApplicationDataDirectory)
	METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
	RETURN_STRING( OS::getApplicationDataDirectory() );
	END
SCRIPT_METHOD_IMPL(FileManager, GetApplicationDirectory)
	METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
	RETURN_STRING( OS::getApplicationDirectory() );
	END
SCRIPT_METHOD_IMPL(FileManager, GetApplicationResourceDirectory)
	METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
	RETURN_STRING( OS::getApplicationResourceDirectory() );
	END


} // pdg namespace
