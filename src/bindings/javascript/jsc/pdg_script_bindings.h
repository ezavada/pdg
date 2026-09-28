// -----------------------------------------------
// pdg_script_bindings.h
// 
// Stuff to support Javascript bindings via JavaScriptCore
//
// Written by Ed Zavada, 2012-2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------


#ifndef PDG_SCRIPT_BINDINGS_H_INCLUDED
#define PDG_SCRIPT_BINDINGS_H_INCLUDED

#include "pdg_project.h"

// don't do anything unless we are actually targeting Javascript
#ifdef PDG_COMPILING_FOR_JAVASCRIPT

#define PDG_USING_JAVASCRIPT_CORE

#include <JavaScriptCore/JavaScript.h>

#define SCRIPT_OBJECT_REF   	JSObjectRef
#define SCRIPT_CLEANUP_PARAM	JSObjectRef obj
#define INIT_SCRIPT_OBJECT(obj)	obj = 0


namespace pdg {

// this may be used anywhere we don't have a context passed in
extern JSContextRef gMainContext;

// Preserve exceptions raised by JavaScript callbacks until the native binding
// which initiated the callback can return them to JavaScriptCore.
void SavePendingScriptException(JSValueRef exception);
bool RestorePendingScriptException(JSValueRef* exception);
    
// Destructors for these object will call these matching
// cleanup function whenever one of them is deleted.

void CleanupMemBlockScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupIEventHandlerScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupEventEmitterScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupSoundScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupFontScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupPortScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupImageScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupImageStripScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupIAnimationHelperScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupAnimatedBaseScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupSpriteScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupSpriteLayerScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupTileLayerScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupISpriteDrawHelperScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupISerializableScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupSerializerScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupDeserializerScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupDrawingScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupElementRefScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupAttributesScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupPolygonScriptObject(SCRIPT_CLEANUP_PARAM);
void CleanupSplineScriptObject(SCRIPT_CLEANUP_PARAM);

// initializes the bindings for the pdg module
void initBindings(JSContextRef ctx, JSObjectRef exports);


} // end namespace pdg

// called by the bindings when pdg is completely setup in the scripting language
// implemented in pdg_jsc_ios.cpp, but done this way so bindings are not dependent on
// the JSC IOS stuff
extern "C" void scriptSetupCompleted();

#endif // PDG_COMPILING_FOR_JAVASCRIPT

#endif // PDG_SCRIPT_BINDINGS_H_INCLUDED
