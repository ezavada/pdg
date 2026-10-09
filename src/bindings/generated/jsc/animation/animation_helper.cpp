// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animation_helper.cpp
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

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void IAnimationHelper_finalize(JSObjectRef object)
    {
        auto* helper = static_cast<IAnimationHelper*>(JSObjectGetPrivate(object));
        if (!helper) return;
        helper->mIAnimationHelperScriptObj = nullptr;
        JSObjectSetPrivate(object, nullptr);
        helper->release();
    }
#else
    IAnimationHelper* New_IAnimationHelper(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException);
    IAnimationHelperWrap::IAnimationHelperWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_IAnimationHelper(args)) {}
    IAnimationHelperWrap::~IAnimationHelperWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mIAnimationHelperScriptObj.Reset();
            cppPtr_->release();
        }
    }
#endif
    JSObjectRef IAnimationHelper_newFromCpp(JSContextRef ctx, IAnimationHelper* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, IAnimationHelper_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, IAnimationHelper_class());
        cppObj->mIAnimationHelperScriptObj = obj; cppObj->addRef(); if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject();
        return obj;
    }

    JSObjectRef IAnimationHelper_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        IAnimationHelper* cppObj = New_IAnimationHelper(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "IAnimationHelper" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, IAnimationHelper_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, IAnimationHelper_class());
        cppObj->mIAnimationHelperScriptObj = obj; cppObj->addRef(); if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject();
        return obj;
    }

    JSClassRef IAnimationHelper_class()
    {

        static JSStaticValue IAnimationHelper_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction IAnimationHelper_staticFunctions[] =
        {
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = IAnimationHelper_finalize;
            definition.className = "IAnimationHelper";
            definition.staticFunctions = IAnimationHelper_staticFunctions;
            definition.staticValues = IAnimationHelper_staticValues;
            definition.callAsConstructor = IAnimationHelper_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;
    }

    void CleanupIAnimationHelperScriptObject(JSObjectRef obj) { }

}
