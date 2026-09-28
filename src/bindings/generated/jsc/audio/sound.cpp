// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/sound.cpp
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

#ifndef PDG_NO_SOUND

    static bool s_SoundManager_InNewFromCpp = false;

    JSObjectRef SoundManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_SoundManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "SoundManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "snd" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        SoundManager* cppObj = New_SoundManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "SoundManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, SoundManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, SoundManager_class());
        return obj;
    }

    JSObjectRef SoundManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_SoundManager_InNewFromCpp = true;
            instance = SoundManager_new(gMainContext, 0, 0, NULL, NULL);
            s_SoundManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    SoundManager* SoundManager_getSingletonInstance()
    {
        JSObjectRef obj = SoundManager_getScriptSingletonInstance();
        return static_cast<SoundManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef SoundManager_class()
    {
        static JSStaticValue SoundManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction SoundManager_staticFunctions[] =
        {
            { "setVolume", SoundManager_SetVolume, kJSPropertyAttributeDontDelete },
            { "setMute", SoundManager_SetMute, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "SoundManager";
            definition.staticFunctions = SoundManager_staticFunctions;
            definition.staticValues = SoundManager_staticValues;
            definition.callAsConstructor = SoundManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef SoundManager_SetVolume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SoundManager* self = static_cast<SoundManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""level"")");
        double level = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setVolume(level);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef SoundManager_SetMute(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        SoundManager* self = static_cast<SoundManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""muted"")");
        bool muted = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setMute(muted);
        return JSValueMakeUndefined(ctx);
    }

    SoundManager* New_SoundManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return SoundManager::getSingletonInstance(); }
#endif

}
