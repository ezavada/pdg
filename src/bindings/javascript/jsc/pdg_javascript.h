// -----------------------------------------------
// pdg_javascript.h
// 
// All inclusive include for JavaScript bindings
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


#ifndef PDG_JAVASCRIPT_H_INCLUDED
#define PDG_JAVASCRIPT_H_INCLUDED

#include "pdg_project.h"

// don't do anything unless we are actually targetting JavaScript
#ifdef PDG_COMPILING_FOR_JAVASCRIPT

#include "jsc/pdg_script_bindings.h"  // must include first

#include "jsc/pdg_jsc_support.h"
#include "jsc/pdg_script_macros.h"

#include "memblock.h"

#endif // PDG_COMPILING_FOR_JAVASCRIPT

#endif // PDG_JAVASCRIPT_H_INCLUDED
