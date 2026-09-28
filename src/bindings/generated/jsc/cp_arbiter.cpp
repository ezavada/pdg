// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_arbiter.cpp
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
#include "physics_bindings.h"

#include "internals.h"
#include "pdg-lib.h"

#include <sstream>
#include <cmath>
#include <cstdlib>

namespace pdg
{

    JSObjectRef cpArbiter_newFromCpp(JSContextRef ctx, cpArbiter* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, cpArbiter_class(), cppObj);
        ;
        return obj;
    }

    JSObjectRef cpArbiter_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* cppObj = New_cpArbiter(argumentCount, arguments);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "cpArbiter" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, cpArbiter_class(), cppObj);
        ;
        return obj;
    }

    JSClassRef cpArbiter_class()
    {
        static JSStaticValue cpArbiter_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction cpArbiter_staticFunctions[] =
        {
            { "isFirstContact", cpArbiter_IsFirstContact, kJSPropertyAttributeDontDelete },
            { "get""Count", cpArbiter_GetCount, kJSPropertyAttributeDontDelete },
            { "get""Normal", cpArbiter_GetNormal, kJSPropertyAttributeDontDelete },
            { "get""PointA", cpArbiter_GetPointA, kJSPropertyAttributeDontDelete },
            { "get""PointB", cpArbiter_GetPointB, kJSPropertyAttributeDontDelete },
            { "get""Depth", cpArbiter_GetDepth, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "CpArbiter";
            definition.staticFunctions = cpArbiter_staticFunctions;
            definition.staticValues = cpArbiter_staticValues;
            definition.callAsConstructor = cpArbiter_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef cpArbiter_IsFirstContact(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpBool isFirst = cpArbiterIsFirstContact(self);
        return JSValueMakeBoolean(ctx, isFirst);
    }
    JSValueRef cpArbiter_GetCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theCount = cpArbiterGetCount(self);
        return JSValueMakeNumber(ctx, theCount);
    }
    JSValueRef cpArbiter_GetNormal(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        cpVect nv = cpArbiterGetNormal(self);
        pdg::Vector theNormal(nv.x, nv.y);
        return JSC_VectorToValue(ctx, theNormal, exception);
    }

    JSValueRef cpArbiter_GetPointA(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpVect pt = cpArbiterGetPointA(self, i);
        pdg::Point thePointA(pt.x, pt.y);
        return JSC_PointToValue(ctx, thePointA, exception);
    }

    JSValueRef cpArbiter_GetPointB(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpVect pt = cpArbiterGetPointB(self, i);
        pdg::Point thePointB(pt.x, pt.y);
        return JSC_PointToValue(ctx, thePointB, exception);
    }

    JSValueRef cpArbiter_GetDepth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        cpArbiter* self = static_cast<cpArbiter*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        int32 i = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        cpFloat theDepth = cpArbiterGetDepth(self, i);
        return JSValueMakeNumber(ctx, theDepth);
    }

    CPP_UNMANAGED_CONSTRUCTOR_IMPL(cpArbiter, cppPtr_ = nullptr;
        )
        s_SavedError.str(""); s_SavedError.clear();
    s_SavedError << "CpArbiter cannot be created directly, it is only returned from certain Sprite calls.";
    s_HaveSavedError = true;
    return 0;
}


}
