// -----------------------------------------------
// pdg_script_impl.cpp
//
// wrapper definitions for pdg classes 
// that are exposed to scripting languages without
// any specific language dependencies
//
// This file is parsed by tools/gen-script_interface.sh
// to generate an interface file
//
// This should only be done when the wrappers need 
// to change.
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


//%#define PDG_DEBUG_SCRIPTING

%#ifndef PDG_DEBUG_SCRIPTING
  // if the javascript bindings are not being debugged, we ignore whatever
  // is inside these blocks
  %#define SCRIPT_DEBUG_ONLY(_expression)
%#else
  %#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
%#endif

namespace pdg {

bool s_HaveSavedError = false;

#include "core/core_impl_macros.h"
#include "data/data_impl_macros.h"
#include "animation/animation_impl_macros.h"



// ========================================================================================
//MARK: Script Serializable
// ========================================================================================

ScriptSerializable::ScriptSerializable() {
}


// ========================================================================================
//MARK: Script Event Handler
// ========================================================================================

ScriptEventHandler::ScriptEventHandler() {
}

// ========================================================================================
//MARK: Script Animation Helper
// ========================================================================================

ScriptAnimationHelper::ScriptAnimationHelper() {
}


// ========================================================================================
//MARK: Script Sprite Collide Helper
// ========================================================================================

ScriptSpriteCollideHelper::ScriptSpriteCollideHelper() {
}


%#ifndef PDG_NO_GUI
// ========================================================================================
//MARK: Script Sprite Draw Helper
// ========================================================================================

ScriptSpriteDrawHelper::ScriptSpriteDrawHelper() {
}


%#endif // !PDG_NO_GUI


// ========================================================================================
//MARK: Utility Functions
// ========================================================================================

FUNCTION_IMPL(Rand)
	METHOD_SIGNATURE("", number, 0, ()); 
	REQUIRE_ARG_COUNT(0);
	RETURN_UNSIGNED( OS::rand() );
	END
FUNCTION_IMPL(GameCriticalRandom)
	METHOD_SIGNATURE("", number, 0, ()); 
	REQUIRE_ARG_COUNT(0);
 	RETURN_UNSIGNED( OS::gameCriticalRandom() );
 	END
FUNCTION_IMPL(Srand)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] seed)); 
	REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, seed);
 	OS::srand( seed );
 	NO_RETURN;
 	END
FUNCTION_IMPL(SetSerializationDebugMode)
	METHOD_SIGNATURE("", undefined, 1, (bool debugMode)); 
	REQUIRE_ARG_COUNT(1);
    REQUIRE_BOOL_ARG(1, debugMode);
 	ISerializer::s_DebugMode = debugMode;
 	NO_RETURN;
 	END



// =========================  initializers =============================
bool Initializer::allowHorizontalOrientation() throw() { return true; }
bool Initializer::allowVerticalOrientation() throw() { return true; }
const char* Initializer::getAppName(bool haveMainResourceFile) throw() { return "pdg"; }
const char* Initializer::getMainResourceFileName() throw() {return NULL;}
bool Initializer::installGlobalHandlers() throw() {return true;}
bool Initializer::getGraphicsEnvironmentDimensions(Rect maxWindowDim, Rect maxFullScreenDim,
	long& ioWidth, long& ioHeight, uint8& ioDepth) throw()
{
  ioWidth = 640;
  ioHeight = 480;
  ioDepth = 32;
  return false;
}


FUNCTION_IMPL(Idle)
	METHOD_SIGNATURE("", undefined, 0, ()); 
	REQUIRE_ARG_COUNT(0);
	pdg_LibIdle();
	NO_RETURN;
END

FUNCTION_IMPL(Run)
	METHOD_SIGNATURE("", undefined, 0, ()); 
	REQUIRE_ARG_COUNT(0);
	pdg_LibRun();
	NO_RETURN;
END

FUNCTION_IMPL(Quit)
	METHOD_SIGNATURE("", undefined, 0, ()); 
	REQUIRE_ARG_COUNT(0);
	pdg_LibQuit();
	NO_RETURN;
END

FUNCTION_IMPL(IsQuitting)
	METHOD_SIGNATURE("", boolean, 0, ()); 
	REQUIRE_ARG_COUNT(0);
	bool isQuitting = pdg_LibIsQuitting();
	RETURN_BOOL( isQuitting );
END



} // end pdg namespace
