// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/serializable.cpp
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

    JSObjectRef ISerializable_newFromCpp(JSContextRef ctx, ISerializable* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, ISerializable_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ISerializable_class());
        cppObj->mISerializableScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef ISerializable_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ISerializable* cppObj = New_ISerializable(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "ISerializable" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ISerializable_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ISerializable_class());
        cppObj->mISerializableScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef ISerializable_class()
    {
        static JSStaticValue ISerializable_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ISerializable_staticFunctions[] =
        {
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ISerializable";
            definition.staticFunctions = ISerializable_staticFunctions;
            definition.staticValues = ISerializable_staticValues;
            definition.callAsConstructor = ISerializable_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;
    }

    void CleanupISerializableScriptObject(JSObjectRef obj) { }

}
