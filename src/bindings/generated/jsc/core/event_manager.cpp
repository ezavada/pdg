// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/event_manager.cpp
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

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>

namespace pdg
{

    JSObjectRef IEventHandler_newFromCpp(JSContextRef ctx, IEventHandler* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, IEventHandler_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, IEventHandler_class());
        cppObj->mIEventHandlerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef IEventHandler_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        IEventHandler* cppObj = New_IEventHandler(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "IEventHandler" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, IEventHandler_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, IEventHandler_class());
        cppObj->mIEventHandlerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef IEventHandler_class()
    {
        static JSStaticValue IEventHandler_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction IEventHandler_staticFunctions[] =
        {
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "IEventHandler";
            definition.staticFunctions = IEventHandler_staticFunctions;
            definition.staticValues = IEventHandler_staticValues;
            definition.callAsConstructor = IEventHandler_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;
    }

    void CleanupIEventHandlerScriptObject(JSObjectRef obj) { }

    JSObjectRef EventEmitter_newFromCpp(JSContextRef ctx, EventEmitter* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, EventEmitter_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, EventEmitter_class());
        cppObj->mEventEmitterScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef EventEmitter_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* cppObj = New_EventEmitter(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "EventEmitter" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, EventEmitter_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, EventEmitter_class());
        cppObj->mEventEmitterScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef EventEmitter_class()
    {
        static JSStaticValue EventEmitter_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction EventEmitter_staticFunctions[] =
        {
            { "addHandler", EventEmitter_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", EventEmitter_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", EventEmitter_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", EventEmitter_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", EventEmitter_UnblockEvent, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "EventEmitter";
            definition.staticFunctions = EventEmitter_staticFunctions;
            definition.staticValues = EventEmitter_staticValues;
            definition.callAsConstructor = EventEmitter_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef EventEmitter_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* self = static_cast<EventEmitter*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventEmitter_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* self = static_cast<EventEmitter*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventEmitter_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* self = static_cast<EventEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventEmitter_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* self = static_cast<EventEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventEmitter_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventEmitter* self = static_cast<EventEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }

    EventEmitter* New_EventEmitter(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new EventEmitter();
    }

    static bool s_EventManager_InNewFromCpp = false;

    JSObjectRef EventManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_EventManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "EventManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "evt" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        EventManager* cppObj = New_EventManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "EventManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, EventManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, EventManager_class());
        return obj;
    }

    JSObjectRef EventManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_EventManager_InNewFromCpp = true;
            instance = EventManager_new(gMainContext, 0, 0, NULL, NULL);
            s_EventManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    EventManager* EventManager_getSingletonInstance()
    {
        JSObjectRef obj = EventManager_getScriptSingletonInstance();
        return static_cast<EventManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef EventManager_class()
    {
        static JSStaticValue EventManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction EventManager_staticFunctions[] =
        {
            { "addHandler", EventManager_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", EventManager_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", EventManager_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", EventManager_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", EventManager_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "isKeyDown", EventManager_IsKeyDown, kJSPropertyAttributeDontDelete },
            { "isRawKeyDown", EventManager_IsRawKeyDown, kJSPropertyAttributeDontDelete },
            { "isButtonDown", EventManager_IsButtonDown, kJSPropertyAttributeDontDelete },
            { "getDeviceOrientation", EventManager_GetDeviceOrientation, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "EventManager";
            definition.staticFunctions = EventManager_staticFunctions;
            definition.staticValues = EventManager_staticValues;
            definition.callAsConstructor = EventManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef EventManager_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventManager* self = static_cast<EventManager*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventManager_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventManager* self = static_cast<EventManager*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventManager_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventManager* self = static_cast<EventManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventManager_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventManager* self = static_cast<EventManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventManager_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        EventManager* self = static_cast<EventManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef EventManager_IsRawKeyDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""keyCode"")");
        int32 keyCode = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        return JSValueMakeBoolean(ctx, OS::isRawKeyDown(keyCode));
    }
    JSValueRef EventManager_IsButtonDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""buttonNumber"")");
        long buttonNumber = (argumentCount<1) ? 0 : (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        return JSValueMakeBoolean(ctx, OS::isButtonDown(buttonNumber));
    }

    EventManager* New_EventManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return EventManager::getSingletonInstance(); }

}
