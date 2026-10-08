// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/resource_manager.cpp
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
#include <algorithm>

namespace pdg
{

    static bool s_ResourceManager_InNewFromCpp = false;

    JSObjectRef ResourceManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_ResourceManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "ResourceManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "res" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        ResourceManager* cppObj = New_ResourceManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "ResourceManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ResourceManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ResourceManager_class());
        return obj;
    }

    JSObjectRef ResourceManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_ResourceManager_InNewFromCpp = true;
            instance = ResourceManager_new(gMainContext, 0, 0, NULL, NULL);
            s_ResourceManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    ResourceManager* ResourceManager_getSingletonInstance()
    {
        JSObjectRef obj = ResourceManager_getScriptSingletonInstance();
        return static_cast<ResourceManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef ResourceManager_class()
    {
        static JSStaticValue ResourceManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ResourceManager_staticFunctions[] =
        {
            { "get""Language", ResourceManager_GetLanguage, kJSPropertyAttributeDontDelete },
            { "set""Language", ResourceManager_SetLanguage, kJSPropertyAttributeDontDelete },
            { "openResourceFile", ResourceManager_OpenResourceFile, kJSPropertyAttributeDontDelete },
            { "closeResourceFile", ResourceManager_CloseResourceFile, kJSPropertyAttributeDontDelete },
            { "getImage", ResourceManager_GetImage, kJSPropertyAttributeDontDelete },
            { "getImageStrip", ResourceManager_GetImageStrip, kJSPropertyAttributeDontDelete },
#ifndef PDG_NO_SOUND
            { "getSound", ResourceManager_GetSound, kJSPropertyAttributeDontDelete },
#endif
            { "getString", ResourceManager_GetString, kJSPropertyAttributeDontDelete },
            { "getResourceSize", ResourceManager_GetResourceSize, kJSPropertyAttributeDontDelete },
            { "getResource", ResourceManager_GetResource, kJSPropertyAttributeDontDelete },
            { "getResourcePaths", ResourceManager_GetResourcePaths, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ResourceManager";
            definition.staticFunctions = ResourceManager_staticFunctions;
            definition.staticValues = ResourceManager_staticValues;
            definition.callAsConstructor = ResourceManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef ResourceManager_GetLanguage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const char* theLanguage = self->getLanguage();
        return JSC_MakeValueFromCString(ctx, theLanguage);
    }
    JSValueRef ResourceManager_SetLanguage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""theLanguage"")");
        JSStringRef theLanguage_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock theLanguage_Mem(JSStringGetMaximumUTF8CStringSize(theLanguage_Str));
        JSStringGetUTF8CString(theLanguage_Str, theLanguage_Mem.ptr, theLanguage_Mem.bytes);
        const char* theLanguage = (const char*)theLanguage_Mem.ptr;
        JSStringRelease(theLanguage_Str);
        self->setLanguage(theLanguage);
        return thisObject;
    }
    JSValueRef ResourceManager_OpenResourceFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""filename"")");
        JSStringRef filename_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock filename_Mem(JSStringGetMaximumUTF8CStringSize(filename_Str));
        JSStringGetUTF8CString(filename_Str, filename_Mem.ptr, filename_Mem.bytes);
        const char* filename = (const char*)filename_Mem.ptr;
        JSStringRelease(filename_Str);
        int refNum = self->openResourceFile(filename);
        return JSValueMakeNumber(ctx, refNum);
    }
    JSValueRef ResourceManager_CloseResourceFile(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""refNum"")");
        int32 refNum = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->closeResourceFile(refNum);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ResourceManager_GetString(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
        int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""substring"")");
        long substring = (argumentCount<2) ? -1 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        std::string ioStr;
        const char* outStr = self->getString(ioStr, id, substring);
        return JSC_MakeValueFromCString(ctx, outStr);
    }
    JSValueRef ResourceManager_GetResourceSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""resourceName"")");
        JSStringRef resourceName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock resourceName_Mem(JSStringGetMaximumUTF8CStringSize(resourceName_Str));
        JSStringGetUTF8CString(resourceName_Str, resourceName_Mem.ptr, resourceName_Mem.bytes);
        const char* resourceName = (const char*)resourceName_Mem.ptr;
        JSStringRelease(resourceName_Str);
        unsigned long resSize = self->getResourceSize(resourceName);
        return JSValueMakeNumber(ctx, resSize);
    }

    JSValueRef ResourceManager_GetResource(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""resourceName"")");
        JSStringRef resourceName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock resourceName_Mem(JSStringGetMaximumUTF8CStringSize(resourceName_Str));
        JSStringGetUTF8CString(resourceName_Str, resourceName_Mem.ptr, resourceName_Mem.bytes);
        const char* resourceName = (const char*)resourceName_Mem.ptr;
        JSStringRelease(resourceName_Str);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""maxSize"")");
        long maxSize = (argumentCount<2) ? -1 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        unsigned long resourceSize = self->getResourceSize(resourceName);
        unsigned long bufferSize = maxSize < 0 ? resourceSize : std::min(resourceSize, static_cast<unsigned long>(maxSize));
        if (!bufferSize) { return JSValueMakeBoolean(ctx, false); }
        uint8* buffer = (uint8*) std::malloc(bufferSize);
        bool loaded = self->getResource(resourceName, buffer, bufferSize);
        if (!loaded)
        {
            std::free(buffer);
            return JSValueMakeBoolean(ctx, false);
        }
        JSValueRef resultVal = MakeUint8Array(buffer, bufferSize);
        std::free(buffer);
        return resultVal;
    }
    JSValueRef ResourceManager_GetResourcePaths(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        std::string outStr = self->getResourcePaths();
        return JSC_MakeValueFromCString(ctx, outStr.c_str());
    }

    ResourceManager* New_ResourceManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return ResourceManager::getSingletonInstance(); }

}
