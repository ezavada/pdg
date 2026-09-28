// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_space.cpp
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

#include <sstream>
#include <cmath>
#include <cstdlib>

namespace pdg
{

    JSObjectRef cpSpace_newFromCpp(JSContextRef ctx, cpSpace* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, cpSpace_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, cpSpace_class());
        ;
        return obj;
    }

    JSObjectRef cpSpace_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* cppObj = New_cpSpace(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "cpSpace" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, cpSpace_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, cpSpace_class());
        ;
        return obj;
    }

    JSClassRef cpSpace_class()
    {
        static JSStaticValue cpSpace_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction cpSpace_staticFunctions[] =
        {
            { "useSpatialHash", cpSpace_UseSpatialHash, kJSPropertyAttributeDontDelete },
            { "reindexStatic", cpSpace_ReindexStatic, kJSPropertyAttributeDontDelete },
            { "step", cpSpace_Step, kJSPropertyAttributeDontDelete },
            { "get""IdleSpeedThreshold", cpSpace_GetIdleSpeedThreshold, kJSPropertyAttributeDontDelete },
            { "set""IdleSpeedThreshold", cpSpace_SetIdleSpeedThreshold, kJSPropertyAttributeDontDelete },
            { "get""SleepTimeThreshold", cpSpace_GetSleepTimeThreshold, kJSPropertyAttributeDontDelete },
            { "set""SleepTimeThreshold", cpSpace_SetSleepTimeThreshold, kJSPropertyAttributeDontDelete },
            { "get""CollisionSlop", cpSpace_GetCollisionSlop, kJSPropertyAttributeDontDelete },
            { "set""CollisionSlop", cpSpace_SetCollisionSlop, kJSPropertyAttributeDontDelete },
            { "get""CollisionBias", cpSpace_GetCollisionBias, kJSPropertyAttributeDontDelete },
            { "set""CollisionBias", cpSpace_SetCollisionBias, kJSPropertyAttributeDontDelete },
            { "get""CollisionPersistence", cpSpace_GetCollisionPersistence, kJSPropertyAttributeDontDelete },
            { "set""CollisionPersistence", cpSpace_SetCollisionPersistence, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "CpSpace";
            definition.staticFunctions = cpSpace_staticFunctions;
            definition.staticValues = cpSpace_staticValues;
            definition.callAsConstructor = cpSpace_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef cpSpace_UseSpatialHash(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""dim"")");
        double dim = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""count"")");
        int32 count = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        cpSpaceUseSpatialHash(self, dim, count);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_ReindexStatic(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpSpaceReindexStatic(self);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_Step(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""dt"")");
        double dt = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceStep(self, dt);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef cpSpace_GetIdleSpeedThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theIdleSpeedThreshold = cpSpaceGetIdleSpeedThreshold(self);
        return JSValueMakeNumber(ctx, theIdleSpeedThreshold);
    }
    JSValueRef cpSpace_SetIdleSpeedThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theIdleSpeedThreshold"")");
        double theIdleSpeedThreshold = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetIdleSpeedThreshold(self, theIdleSpeedThreshold);
        return thisObject;
    }
    JSValueRef cpSpace_GetSleepTimeThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theSleepTimeThreshold = cpSpaceGetSleepTimeThreshold(self);
        return JSValueMakeNumber(ctx, theSleepTimeThreshold);
    }
    JSValueRef cpSpace_SetSleepTimeThreshold(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theSleepTimeThreshold"")");
        double theSleepTimeThreshold = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetSleepTimeThreshold(self, theSleepTimeThreshold);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionSlop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionSlop = cpSpaceGetCollisionSlop(self);
        return JSValueMakeNumber(ctx, theCollisionSlop);
    }
    JSValueRef cpSpace_SetCollisionSlop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionSlop"")");
        double theCollisionSlop = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionSlop(self, theCollisionSlop);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionBias = cpSpaceGetCollisionBias(self);
        return JSValueMakeNumber(ctx, theCollisionBias);
    }
    JSValueRef cpSpace_SetCollisionBias(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionBias"")");
        double theCollisionBias = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionBias(self, theCollisionBias);
        return thisObject;
    }
    JSValueRef cpSpace_GetCollisionPersistence(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theCollisionPersistence = cpSpaceGetCollisionPersistence(self);
        return JSValueMakeNumber(ctx, theCollisionPersistence);
    }
    JSValueRef cpSpace_SetCollisionPersistence(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpSpace* self = static_cast<cpSpace*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theCollisionPersistence"")");
        double theCollisionPersistence = JSValueToNumber(ctx, arguments[1 -1], exception);
        cpSpaceSetCollisionPersistence(self, theCollisionPersistence);
        return thisObject;
    }

    cpSpace* New_cpSpace(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        s_SavedError.str(""); s_SavedError.clear();
        s_SavedError << "CpSpace cannot be created directly, it is only returned from certain Sprite calls.";
        s_HaveSavedError = true;
        return 0;
    }

}
