// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/file_manager.cpp
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

    static JSStringRef symbol_nodeName = 0;
    static JSStringRef symbol_isDirectory = 0;
    static JSStringRef symbol_found = 0;

    JSObjectRef FileManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        JSObjectRef obj = JSObjectMake(ctx, FileManager_class(), 0);
        return obj;
    }

    JSObjectRef FileManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {
            instance = FileManager_new(gMainContext, 0, 0, NULL, NULL);
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    JSClassRef FileManager_class()
    {
        static JSStaticValue FileManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction FileManager_staticFunctions[] =
        {
            { "findFirst", FileManager_FindFirst, kJSPropertyAttributeDontDelete },
            { "findNext", FileManager_FindNext, kJSPropertyAttributeDontDelete },
            { "findClose", FileManager_FindClose, kJSPropertyAttributeDontDelete },
            { "get""ApplicationDataDirectory", FileManager_GetApplicationDataDirectory, kJSPropertyAttributeDontDelete },
            { "get""ApplicationDirectory", FileManager_GetApplicationDirectory, kJSPropertyAttributeDontDelete },
            { "get""ApplicationResourceDirectory", FileManager_GetApplicationResourceDirectory, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "FileManager";
            definition.staticFunctions = FileManager_staticFunctions;
            definition.staticValues = FileManager_staticValues;
            definition.callAsConstructor = FileManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef FileManager_FindFirst(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inFindName"")");
        JSStringRef inFindName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inFindName_Mem(JSStringGetMaximumUTF8CStringSize(inFindName_Str));
        JSStringGetUTF8CString(inFindName_Str, inFindName_Mem.ptr, inFindName_Mem.bytes);
        const char* inFindName = (const char*)inFindName_Mem.ptr;
        JSStringRelease(inFindName_Str);
        FindDataT* ioFindDataPtr = new FindDataT;
        bool found = OS::findFirst(inFindName, *ioFindDataPtr);
        JSObjectRef jsFindData = JSC_ObjectCreateEmpty(ctx, ioFindDataPtr);
        JSValueRef nodeName = JSC_MakeValueFromCString(ctx, ioFindDataPtr->nodeName);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_nodeName) ? symbol_nodeName : symbol_nodeName = JSStringCreateWithUTF8CString("nodeName")), nodeName, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_isDirectory) ? symbol_isDirectory : symbol_isDirectory = JSStringCreateWithUTF8CString("isDirectory")), JSValueMakeBoolean(ctx, ioFindDataPtr->isDirectory), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_found) ? symbol_found : symbol_found = JSStringCreateWithUTF8CString("found")), JSValueMakeBoolean(ctx, found), kJSPropertyAttributeNone, exception);
        return jsFindData;
    }

    JSValueRef FileManager_FindNext(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsObject(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object (""jsFindData"")");
        JSObjectRef jsFindData = JSValueToObject(ctx, arguments[1 -1], exception);
        FindDataT* ioFindDataPtr = static_cast<FindDataT*>(JSObjectGetPrivate(jsFindData));
        if (!ioFindDataPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "findNext must only be called with the object returned by findFirst" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        bool found = OS::findNext(*ioFindDataPtr);
        JSValueRef nodeName = JSC_MakeValueFromCString(ctx, ioFindDataPtr->nodeName);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_nodeName) ? symbol_nodeName : symbol_nodeName = JSStringCreateWithUTF8CString("nodeName")), nodeName, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_isDirectory) ? symbol_isDirectory : symbol_isDirectory = JSStringCreateWithUTF8CString("isDirectory")), JSValueMakeBoolean(ctx, ioFindDataPtr->isDirectory), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsFindData, ((symbol_found) ? symbol_found : symbol_found = JSStringCreateWithUTF8CString("found")), JSValueMakeBoolean(ctx, found), kJSPropertyAttributeNone, exception);
        return JSValueMakeBoolean(ctx, found);
    }
    JSValueRef FileManager_FindClose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsObject(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object (""jsFindData"")");
        JSObjectRef jsFindData = JSValueToObject(ctx, arguments[1 -1], exception);
        FindDataT* ioFindDataPtr = static_cast<FindDataT*>(JSObjectGetPrivate(jsFindData));
        if (!ioFindDataPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "findClose must only be called with the object returned by findFirst" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        OS::findClose(*ioFindDataPtr);
        delete ioFindDataPtr;
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef FileManager_GetApplicationDataDirectory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSC_MakeValueFromCString(ctx, OS::getApplicationDataDirectory());
    }
    JSValueRef FileManager_GetApplicationDirectory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSC_MakeValueFromCString(ctx, OS::getApplicationDirectory());
    }
    JSValueRef FileManager_GetApplicationResourceDirectory(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSC_MakeValueFromCString(ctx, OS::getApplicationResourceDirectory());
    }

}
