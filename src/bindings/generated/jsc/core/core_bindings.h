// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/core_bindings.h
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#ifndef PDG_CORE_BINDINGS_H_INCLUDED
#define PDG_CORE_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"

#include <cstdlib>

namespace pdg
{

    extern IEventHandler* New_IEventHandler(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef IEventHandler_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef IEventHandler_class();
    extern JSObjectRef IEventHandler_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline IEventHandler* IEventHandler_getCppObject(JSObjectRef obj)
    {
        return static_cast<IEventHandler*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef IEventHandler_newFromCpp(JSContextRef, IEventHandler*);

    extern EventEmitter* New_EventEmitter(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef EventEmitter_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef EventEmitter_class();
    extern JSObjectRef EventEmitter_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline EventEmitter* EventEmitter_getCppObject(JSObjectRef obj)
    {
        return static_cast<EventEmitter*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef EventEmitter_newFromCpp(JSContextRef, EventEmitter*);

    extern JSValueRef EventEmitter_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventEmitter_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventEmitter_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventEmitter_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventEmitter_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern ConfigManager* New_ConfigManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ConfigManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ConfigManager_class();
    extern JSObjectRef ConfigManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ConfigManager* ConfigManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<ConfigManager*>(JSObjectGetPrivate(obj));
    }
    extern ConfigManager* ConfigManager_getSingletonInstance();
    extern JSObjectRef ConfigManager_getScriptSingletonInstance();

    extern JSValueRef ConfigManager_UseConfig(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_GetConfigString(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_GetConfigLong(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_GetConfigFloat(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_GetConfigBool(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_SetConfigString(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_SetConfigLong(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_SetConfigFloat(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ConfigManager_SetConfigBool(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern LogManager* New_LogManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef LogManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef LogManager_class();
    extern JSObjectRef LogManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline LogManager* LogManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<LogManager*>(JSObjectGetPrivate(obj));
    }
    extern LogManager* LogManager_getSingletonInstance();
    extern JSObjectRef LogManager_getScriptSingletonInstance();

    _JSC_SCRIPT_IMPL_ONLY( static JSValueRef LogManager_init_CreateUniqueNewFile(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*)
    {
        return JSValueMakeNumber(ctx, pdg::LogManager::init_CreateUniqueNewFile);
    } )

        _JSC_SCRIPT_IMPL_ONLY( static JSValueRef LogManager_init_OverwriteExisting(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*)
    {
        return JSValueMakeNumber(ctx, pdg::LogManager::init_OverwriteExisting);
    } )

        _JSC_SCRIPT_IMPL_ONLY( static JSValueRef LogManager_init_AppendToExisting(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*)
    {
        return JSValueMakeNumber(ctx, pdg::LogManager::init_AppendToExisting);
    } )

        _JSC_SCRIPT_IMPL_ONLY( static JSValueRef LogManager_init_StdOut(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*)
    {
        return JSValueMakeNumber(ctx, pdg::LogManager::init_StdOut);
    } )

        _JSC_SCRIPT_IMPL_ONLY( static JSValueRef LogManager_init_StdErr(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*)
    {
        return JSValueMakeNumber(ctx, pdg::LogManager::init_StdErr);
    } )

        extern JSValueRef LogManager_GetLogLevel(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef LogManager_SetLogLevel(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef LogManager_Initialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef LogManager_WriteLogEntry(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef LogManager_BinaryDump(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern EventManager* New_EventManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef EventManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef EventManager_class();
    extern JSObjectRef EventManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline EventManager* EventManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<EventManager*>(JSObjectGetPrivate(obj));
    }
    extern EventManager* EventManager_getSingletonInstance();
    extern JSObjectRef EventManager_getScriptSingletonInstance();

    extern JSValueRef EventManager_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_IsKeyDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_IsRawKeyDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_IsButtonDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef EventManager_GetDeviceOrientation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern TimerManager* New_TimerManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef TimerManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef TimerManager_class();
    extern JSObjectRef TimerManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline TimerManager* TimerManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<TimerManager*>(JSObjectGetPrivate(obj));
    }
    extern TimerManager* TimerManager_getSingletonInstance();
    extern JSObjectRef TimerManager_getScriptSingletonInstance();

    extern JSValueRef TimerManager_AddHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_RemoveHandler(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_BlockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_UnblockEvent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_StartTimer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_CancelTimer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_CancelAllTimers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_DelayTimer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_DelayTimerUntil(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_Pause(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_Unpause(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_IsPaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_PauseTimer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_UnpauseTimer(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_IsTimerPaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_GetWhenTimerFiresNext(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef TimerManager_GetMilliseconds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

}
