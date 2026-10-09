// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/config_manager.cpp
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

    static bool s_ConfigManager_InNewFromCpp = false;

    JSObjectRef ConfigManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_ConfigManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "ConfigManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "cfg" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        ConfigManager* cppObj = New_ConfigManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "ConfigManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ConfigManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ConfigManager_class());
        return obj;
    }

    JSObjectRef ConfigManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_ConfigManager_InNewFromCpp = true;
            instance = ConfigManager_new(gMainContext, 0, 0, NULL, NULL);
            s_ConfigManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    ConfigManager* ConfigManager_getSingletonInstance()
    {
        JSObjectRef obj = ConfigManager_getScriptSingletonInstance();
        return static_cast<ConfigManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef ConfigManager_class()
    {
        static JSStaticValue ConfigManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ConfigManager_staticFunctions[] =
        {
            { "useConfig", ConfigManager_UseConfig, kJSPropertyAttributeDontDelete },
            { "getConfigString", ConfigManager_GetConfigString, kJSPropertyAttributeDontDelete },
            { "getConfigLong", ConfigManager_GetConfigLong, kJSPropertyAttributeDontDelete },
            { "getConfigFloat", ConfigManager_GetConfigFloat, kJSPropertyAttributeDontDelete },
            { "getConfigBool", ConfigManager_GetConfigBool, kJSPropertyAttributeDontDelete },
            { "setConfigString", ConfigManager_SetConfigString, kJSPropertyAttributeDontDelete },
            { "setConfigLong", ConfigManager_SetConfigLong, kJSPropertyAttributeDontDelete },
            { "setConfigFloat", ConfigManager_SetConfigFloat, kJSPropertyAttributeDontDelete },
            { "setConfigBool", ConfigManager_SetConfigBool, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ConfigManager";
            definition.staticFunctions = ConfigManager_staticFunctions;
            definition.staticValues = ConfigManager_staticValues;
            definition.callAsConstructor = ConfigManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef ConfigManager_UseConfig(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigName"")");
        JSStringRef inConfigName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigName_Str));
        JSStringGetUTF8CString(inConfigName_Str, inConfigName_Mem.ptr, inConfigName_Mem.bytes);
        const char* inConfigName = (const char*)inConfigName_Mem.ptr;
        JSStringRelease(inConfigName_Str);
        bool result = self->useConfig(inConfigName);
        return JSValueMakeBoolean(ctx, result);
    }

    JSValueRef ConfigManager_GetConfigString(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        std::string outVal;
        bool found = self->getConfigString(inConfigItemName, outVal);
        if (found)
        {
            return JSC_MakeValueFromCString(ctx, outVal.c_str());
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
    }

    JSValueRef ConfigManager_GetConfigLong(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        long outVal;
        bool found = self->getConfigLong(inConfigItemName, outVal);
        if (found)
        {
            return JSValueMakeNumber(ctx, outVal);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
    }

    JSValueRef ConfigManager_GetConfigFloat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        float outVal;
        bool found = self->getConfigFloat(inConfigItemName, outVal);
        if (found)
        {
            return JSValueMakeNumber(ctx, outVal);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
    }

    JSValueRef ConfigManager_GetConfigBool(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        bool outVal;
        bool found = self->getConfigBool(inConfigItemName, outVal);
        if (found)
        {
            return JSValueMakeBoolean(ctx, outVal);
        }
        else
        {
            return JSValueMakeUndefined(ctx);
        }
    }
    JSValueRef ConfigManager_SetConfigString(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        if (!JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""inValue"")");
        JSStringRef inValue_Str = JSValueToStringCopy(ctx, arguments[2 -1], exception);
        MemBlock inValue_Mem(JSStringGetMaximumUTF8CStringSize(inValue_Str));
        JSStringGetUTF8CString(inValue_Str, inValue_Mem.ptr, inValue_Mem.bytes);
        const char* inValue = (const char*)inValue_Mem.ptr;
        JSStringRelease(inValue_Str);
        std::string theString(inValue);
        self->setConfigString(inConfigItemName, theString);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ConfigManager_SetConfigLong(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inValue"")");
        int32 inValue = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->setConfigLong(inConfigItemName, inValue);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ConfigManager_SetConfigFloat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inValue"")");
        double inValue = JSValueToNumber(ctx, arguments[2 -1], exception);
        self->setConfigFloat(inConfigItemName, inValue);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ConfigManager_SetConfigBool(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ConfigManager* self = static_cast<ConfigManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inConfigItemName"")");
        JSStringRef inConfigItemName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inConfigItemName_Mem(JSStringGetMaximumUTF8CStringSize(inConfigItemName_Str));
        JSStringGetUTF8CString(inConfigItemName_Str, inConfigItemName_Mem.ptr, inConfigItemName_Mem.bytes);
        const char* inConfigItemName = (const char*)inConfigItemName_Mem.ptr;
        JSStringRelease(inConfigItemName_Str);
        if (!JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""inValue"")");
        bool inValue = JSValueToBoolean(ctx, arguments[2 -1]);
        self->setConfigBool(inConfigItemName, inValue);
        return JSValueMakeUndefined(ctx);
    }

    ConfigManager* New_ConfigManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return ConfigManager::getSingletonInstance(); }

}
