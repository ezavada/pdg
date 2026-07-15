// -----------------------------------------------
// config_manager.cpp
//
// Implementation file for ConfigManager bindings
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

%#include <cstdlib>

namespace pdg {

// ========================================================================================
//MARK: Config Manager
// ========================================================================================

SINGLETON_MANAGER_INITIALIZER_IMPL(ConfigManager, "cfg")
    EXPORT_CLASS_SYMBOLS("ConfigManager", ConfigManager, , ,
    	// method section
		HAS_METHOD(ConfigManager, "useConfig", UseConfig)
		HAS_METHOD(ConfigManager, "getConfigString", GetConfigString)
		HAS_METHOD(ConfigManager, "getConfigLong", GetConfigLong)
		HAS_METHOD(ConfigManager, "getConfigFloat", GetConfigFloat)
		HAS_METHOD(ConfigManager, "getConfigBool", GetConfigBool)
		HAS_METHOD(ConfigManager, "setConfigString", SetConfigString)
		HAS_METHOD(ConfigManager, "setConfigLong", SetConfigLong)
		HAS_METHOD(ConfigManager, "setConfigFloat", SetConfigFloat)
		HAS_METHOD(ConfigManager, "setConfigBool", SetConfigBool)
    );
	END
METHOD_IMPL(ConfigManager, UseConfig)
	METHOD_SIGNATURE("", boolean, 1, (string inConfigName))
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, inConfigName);
	bool result = self->useConfig(inConfigName);
	RETURN_BOOL(result);
	END
METHOD_IMPL(ConfigManager, GetConfigString)	
	METHOD_SIGNATURE("", string, 1, (string inConfigItemName))
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	std::string outVal;
	bool found = self->getConfigString(inConfigItemName, outVal);
	if (found) {
		RETURN_STRING(outVal.c_str());
	} else {
		RETURN_UNDEFINED;
	}
	END
METHOD_IMPL(ConfigManager, GetConfigLong)	
	METHOD_SIGNATURE("", number, 1, (string inConfigItemName))
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	long outVal;
	bool found = self->getConfigLong(inConfigItemName, outVal);
	if (found) {
		RETURN_INTEGER(outVal);
	} else {
		RETURN_UNDEFINED;
	}
	END
METHOD_IMPL(ConfigManager, GetConfigFloat)	
	METHOD_SIGNATURE("", number, 1, (string inConfigItemName))
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	float outVal;
	bool found = self->getConfigFloat(inConfigItemName, outVal);
	if (found) {
		RETURN_NUMBER(outVal);
	} else {
		RETURN_UNDEFINED;
	}
	END
METHOD_IMPL(ConfigManager, GetConfigBool)	
	METHOD_SIGNATURE("", boolean, 1, (string inConfigItemName))
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	bool outVal;
	bool found = self->getConfigBool(inConfigItemName, outVal);
	if (found) {
		RETURN_BOOL(outVal);
	} else {
		RETURN_UNDEFINED;
	}
	END
METHOD_IMPL(ConfigManager, SetConfigString)	
	METHOD_SIGNATURE("", undefined, 2, (string inConfigItemName, string inValue))
    REQUIRE_ARG_COUNT(2);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	REQUIRE_STRING_ARG(2, inValue);
	std::string theString(inValue);
	self->setConfigString(inConfigItemName, theString);
	NO_RETURN;
	END
METHOD_IMPL(ConfigManager, SetConfigLong)	
	METHOD_SIGNATURE("", undefined, 2, (string inConfigItemName, [number int] inValue))
    REQUIRE_ARG_COUNT(2);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	REQUIRE_INT32_ARG(2, inValue);
	self->setConfigLong(inConfigItemName, inValue);
	NO_RETURN;
	END
METHOD_IMPL(ConfigManager, SetConfigFloat)	
	METHOD_SIGNATURE("", undefined, 2, (string inConfigItemName, number inValue))
    REQUIRE_ARG_COUNT(2);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	REQUIRE_NUMBER_ARG(2, inValue);
	self->setConfigFloat(inConfigItemName, inValue);
	NO_RETURN;
	END
METHOD_IMPL(ConfigManager, SetConfigBool)	
	METHOD_SIGNATURE("", undefined, 2, (string inConfigItemName, boolean inValue))
    REQUIRE_ARG_COUNT(2);
	REQUIRE_STRING_ARG(1, inConfigItemName);
	REQUIRE_BOOL_ARG(2, inValue);
	self->setConfigBool(inConfigItemName, inValue);
	NO_RETURN;
	END

CPP_SINGLETON_CONSTRUCTOR_IMPL(ConfigManager)

} // namespace pdg 