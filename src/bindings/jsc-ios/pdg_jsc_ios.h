// -----------------------------------------------
// pdg_jsc_ios.h
//
// support and bindings for pdg game engine as with
// a JavaScriptCore engine for JavaScript support
// running on iOS
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#ifndef PDG_JSC_IOS_H_INCLUDED
#define PDG_JSC_IOS_H_INCLUDED

#include "pdg_project.h"

// start up the JavaScriptCore engine, setup the pdg environment
// and start executing the main.js script
void JSC_IOS_Start(int argc, const char* argv[]);

// do whatever is needed for JavaScriptCore to continue execution
void JSC_IOS_Idle();


#endif // PDG_JSC_IOS_H_INCLUDED
