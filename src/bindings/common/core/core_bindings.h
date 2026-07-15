// -----------------------------------------------
// core_bindings.h
//
// Header file that contains core-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for core classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"
#include "core_macros.h"

%#ifndef PDG_CORE_BINDINGS_H_INCLUDED
%#define PDG_CORE_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

BINDING_CLASS(IEventHandler)
DECL_END

BINDING_CLASS(EventEmitter)
EMITTER_METHODS(EventEmitter)
//  METHOD(EventEmitter, PostEvent)
DECL_END
  
SINGLETON_CLASS(ConfigManager)
  METHOD(ConfigManager, UseConfig)
  METHOD(ConfigManager, GetConfigString)
  METHOD(ConfigManager, GetConfigLong)
  METHOD(ConfigManager, GetConfigFloat)
  METHOD(ConfigManager, GetConfigBool)
  METHOD(ConfigManager, SetConfigString)
  METHOD(ConfigManager, SetConfigLong)
  METHOD(ConfigManager, SetConfigFloat)
  METHOD(ConfigManager, SetConfigBool)
DECL_END

SINGLETON_CLASS(LogManager)
  CONSTANT(LogManager, init_CreateUniqueNewFile)
  CONSTANT(LogManager, init_OverwriteExisting)
  CONSTANT(LogManager, init_AppendToExisting)
  CONSTANT(LogManager, init_StdOut)
  CONSTANT(LogManager, init_StdErr)
  PROPERTY(LogManager, LogLevel)
  METHOD(LogManager, Initialize)
  METHOD(LogManager, WriteLogEntry)
  METHOD(LogManager, BinaryDump)
DECL_END

SINGLETON_CLASS(EventManager)
  EMITTER_METHODS(EventManager)
  METHOD(EventManager, IsKeyDown)
  METHOD(EventManager, IsRawKeyDown)
  METHOD(EventManager, IsButtonDown)
  METHOD(EventManager, GetDeviceOrientation)
DECL_END

SINGLETON_CLASS(TimerManager)
  EMITTER_METHODS(TimerManager)
  METHOD(TimerManager, StartTimer)
  METHOD(TimerManager, CancelTimer)
  METHOD(TimerManager, CancelAllTimers)
  METHOD(TimerManager, DelayTimer)
  METHOD(TimerManager, DelayTimerUntil)
  METHOD(TimerManager, Pause)
  METHOD(TimerManager, Unpause)
  METHOD(TimerManager, IsPaused)
  METHOD(TimerManager, PauseTimer)
  METHOD(TimerManager, UnpauseTimer)
  METHOD(TimerManager, IsTimerPaused)
  METHOD(TimerManager, GetWhenTimerFiresNext)
  METHOD(TimerManager, GetMilliseconds)
DECL_END

%#endif // PDG_CORE_BINDINGS_H_INCLUDED 

} // namespace pdg
