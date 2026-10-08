// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/event_emitter.cpp
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
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
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
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
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
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
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
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }

    EventEmitter* New_EventEmitter(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new EventEmitter();
    }

}
