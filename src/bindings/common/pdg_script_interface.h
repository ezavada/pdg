// -----------------------------------------------
// pdg_script_interface.h
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
// Written by Ed Zavada, 2012-2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"

%#ifndef PDG_INTERFACES_H_INCLUDED
%#define PDG_INTERFACES_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

%#include "physics/physics_bindings.h"
%#include "core/core_bindings.h"
%#include "data/data_bindings.h"
%#include "graphics/graphics_bindings.h"
%#include "audio/audio_bindings.h"
%#include "animation/animation_bindings.h"

namespace pdg {


#endif //!PDG_GENERATING_DOCS


// ========================================================================================
// Class Declarations
// ========================================================================================
//
// There are 4 types of classes:
//
// BINDING_CLASS - Native C++ instances can be instantiated by Javascript code.
// 					var a = new MyClass();
//					Lifecycle of the Native C++ instance is tied to lifecycle of
//					the Javascript object
// 
// SINGLETON_CLASS - there is only one Native instance, instantiated first time it is used in
//					Javascript or in C++. Javascript should never call new MySingletonClass(), 
//					instead it should call getMySingletonClass()
//
// WRAPPER_CLASS - Native C++ instances must be instantiated through some kind of 
//                  a factory call, often from another object. This is not a singleton,
//					so calling createMySingletonClass() multiple times will create
//					multiple Native C++ instances, however the lifecycle of the native
//					C++ object is not tied to the lifecycle of the Javascript object
//
// FACADE_CLASS	- There is no Native C++ instance. This is just a facade for a bunch of 
//					static function calls that we want grouped together


#include "core/core_macros.h"
#include "data/data_macros.h"
#include "graphics/graphics_macros.h"
#include "animation/animation_macros.h"


FUNCTION_DECL(GetConfigManager)
FUNCTION_DECL(GetLogManager)
FUNCTION_DECL(GetEventManager)
FUNCTION_DECL(GetResourceManager)
FUNCTION_DECL(SetSerializationDebugMode)
FUNCTION_DECL(RegisterSerializableClass)
FUNCTION_DECL(RegisterSerializableObject)
FUNCTION_DECL(GetGraphicsManager)
FUNCTION_DECL(GetSoundManager)
FUNCTION_DECL(GetFileManager)
FUNCTION_DECL(GetTimerManager)
FUNCTION_DECL(CreateSpriteLayer)
%#ifdef PDG_SPRITER_SUPPORT
FUNCTION_DECL(CreateSpriteLayerFromSpriterFile)
%#endif
FUNCTION_DECL(CleanupLayer)
FUNCTION_DECL(CreateTileLayer)
FUNCTION_DECL(CreateDrawing)
FUNCTION_DECL(Rand)
FUNCTION_DECL(GameCriticalRandom)
FUNCTION_DECL(Srand)
FUNCTION_DECL(RegisterEasingFunction)
FUNCTION_DECL(Idle)
FUNCTION_DECL(Run)
FUNCTION_DECL(Quit)
FUNCTION_DECL(IsQuitting)
FUNCTION_DECL(FinishedScriptSetup)


} // end pdg namespace

%#endif // PDG_INTERFACES_H_INCLUDED
