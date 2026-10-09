// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/timer_manager.cpp
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



#include "pdg_project.h"

#define PDG_COMPILING_SCRIPT_IMPL

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>

namespace pdg
{

    static bool s_TimerManager_InNewFromCpp = false;

    JSObjectRef TimerManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_TimerManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "TimerManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "tm" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        TimerManager* cppObj = New_TimerManager(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "TimerManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, TimerManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, TimerManager_class());
        return obj;
    }

    JSObjectRef TimerManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_TimerManager_InNewFromCpp = true;
            instance = TimerManager_new(gMainContext, 0, 0, NULL, NULL);
            s_TimerManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    TimerManager* TimerManager_getSingletonInstance()
    {
        JSObjectRef obj = TimerManager_getScriptSingletonInstance();
        return static_cast<TimerManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef TimerManager_class()
    {
        static JSStaticValue TimerManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction TimerManager_staticFunctions[] =
        {
            { "addHandler", TimerManager_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", TimerManager_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", TimerManager_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", TimerManager_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", TimerManager_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "startTimer", TimerManager_StartTimer, kJSPropertyAttributeDontDelete },
            { "cancelTimer", TimerManager_CancelTimer, kJSPropertyAttributeDontDelete },
            { "cancelAllTimers", TimerManager_CancelAllTimers, kJSPropertyAttributeDontDelete },
            { "delayTimer", TimerManager_DelayTimer, kJSPropertyAttributeDontDelete },
            { "delayTimerUntil", TimerManager_DelayTimerUntil, kJSPropertyAttributeDontDelete },
            { "pause", TimerManager_Pause, kJSPropertyAttributeDontDelete },
            { "unpause", TimerManager_Unpause, kJSPropertyAttributeDontDelete },
            { "isPaused", TimerManager_IsPaused, kJSPropertyAttributeDontDelete },
            { "pauseTimer", TimerManager_PauseTimer, kJSPropertyAttributeDontDelete },
            { "unpauseTimer", TimerManager_UnpauseTimer, kJSPropertyAttributeDontDelete },
            { "isTimerPaused", TimerManager_IsTimerPaused, kJSPropertyAttributeDontDelete },
            { "getWhenTimerFiresNext", TimerManager_GetWhenTimerFiresNext, kJSPropertyAttributeDontDelete },
            { "getMilliseconds", TimerManager_GetMilliseconds, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "TimerManager";
            definition.staticFunctions = TimerManager_staticFunctions;
            definition.staticValues = TimerManager_staticValues;
            definition.callAsConstructor = TimerManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef TimerManager_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IEventHandler" " object:") );
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_StartTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""delay"")");
        uint32 delay = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsBoolean(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""oneShot"")");
        bool oneShot = (argumentCount<3) ? true : JSValueToBoolean(ctx, arguments[3 -1]);
        self->startTimer(id, delay, oneShot);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_CancelTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->cancelTimer(id);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_CancelAllTimers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->cancelAllTimers();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_DelayTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""delay"")");
        uint32 delay = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->delayTimer(id, delay);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_DelayTimerUntil(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""msTime"")");
        double msTime_temp = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (msTime_temp < -9223372036854775808.0 || msTime_temp > 9223372036854775807.0 || msTime_temp != (long long)msTime_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number in range [-9223372036854775808, 9223372036854775807] (""msTime"")");
        }
        int64 msTime = (int64)msTime_temp;
        self->delayTimerUntil(id, msTime);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_Pause(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->pause();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_Unpause(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->unpause();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_IsPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool isPaused = self->isPaused();
        return JSValueMakeBoolean(ctx, isPaused);
    }
    JSValueRef TimerManager_PauseTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->pauseTimer(id);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_UnpauseTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unpauseTimer(id);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef TimerManager_IsTimerPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        bool isPaused = self->isTimerPaused(id);
        return JSValueMakeBoolean(ctx, isPaused);
    }
    JSValueRef TimerManager_GetWhenTimerFiresNext(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        TimerManager* self = static_cast<TimerManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        ms_time when = self->getWhenTimerFiresNext(id);

        if (when == 0xffffffff)
        {
            return JSValueMakeNumber(ctx, -1);
        }
        else
        {
            return JSValueMakeNumber(ctx, when);
        }
    }
    JSValueRef TimerManager_GetMilliseconds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return JSValueMakeNumber(ctx, OS::getMilliseconds());
    }

    TimerManager* New_TimerManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return TimerManager::getSingletonInstance(); }

}
