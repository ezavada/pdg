// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/log_manager.cpp
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

    static bool s_LogManager_InNewFromCpp = false;

    JSObjectRef LogManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_LogManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "LogManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "lm" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        LogManager* cppObj = New_LogManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "LogManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, LogManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, LogManager_class());
        return obj;
    }

    JSObjectRef LogManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_LogManager_InNewFromCpp = true;
            instance = LogManager_new(gMainContext, 0, 0, NULL, NULL);
            s_LogManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    LogManager* LogManager_getSingletonInstance()
    {
        JSObjectRef obj = LogManager_getScriptSingletonInstance();
        return static_cast<LogManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef LogManager_class()
    {
        static JSStaticValue LogManager_staticValues[] =
        {
            { "init_CreateUniqueNewFile", LogManager_init_CreateUniqueNewFile, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
            { "init_OverwriteExisting", LogManager_init_OverwriteExisting, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
            { "init_AppendToExisting", LogManager_init_AppendToExisting, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
            { "init_StdOut", LogManager_init_StdOut, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
            { "init_StdErr", LogManager_init_StdErr, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete },
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction LogManager_staticFunctions[] =
        {
            { "get""LogLevel", LogManager_GetLogLevel, kJSPropertyAttributeDontDelete },
            { "set""LogLevel", LogManager_SetLogLevel, kJSPropertyAttributeDontDelete },
            { "initialize", LogManager_Initialize, kJSPropertyAttributeDontDelete },
            { "writeLogEntry", LogManager_WriteLogEntry, kJSPropertyAttributeDontDelete },
            { "binaryDump", LogManager_BinaryDump, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "LogManager";
            definition.staticFunctions = LogManager_staticFunctions;
            definition.staticValues = LogManager_staticValues;
            definition.callAsConstructor = LogManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef LogManager_GetLogLevel(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        LogManager* self = static_cast<LogManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int32 theLogLevel = self->getLogLevel();
        return JSValueMakeNumber(ctx, theLogLevel);
    }
    JSValueRef LogManager_SetLogLevel(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        LogManager* self = static_cast<LogManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theLogLevel"")");
        int32 theLogLevel = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setLogLevel(theLogLevel);
        return thisObject;
    }
    JSValueRef LogManager_Initialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        LogManager* self = static_cast<LogManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""inLogNameBase"")");
        JSStringRef inLogNameBase_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock inLogNameBase_Mem(JSStringGetMaximumUTF8CStringSize(inLogNameBase_Str));
        JSStringGetUTF8CString(inLogNameBase_Str, inLogNameBase_Mem.ptr, inLogNameBase_Mem.bytes);
        const char* inLogNameBase = (const char*)inLogNameBase_Mem.ptr;
        JSStringRelease(inLogNameBase_Str);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""initMode"")");
        long initMode = (argumentCount<2) ? pdg::LogManager::init_StdOut : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->initialize(inLogNameBase, initMode);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef LogManager_WriteLogEntry(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        LogManager* self = static_cast<LogManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""level"")");
        int32 level = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""category"")");
        JSStringRef category_Str = JSValueToStringCopy(ctx, arguments[2 -1], exception);
        MemBlock category_Mem(JSStringGetMaximumUTF8CStringSize(category_Str));
        JSStringGetUTF8CString(category_Str, category_Mem.ptr, category_Mem.bytes);
        const char* category = (const char*)category_Mem.ptr;
        JSStringRelease(category_Str);
        if (!JSValueIsString(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a string (""message"")");
        JSStringRef message_Str = JSValueToStringCopy(ctx, arguments[3 -1], exception);
        MemBlock message_Mem(JSStringGetMaximumUTF8CStringSize(message_Str));
        JSStringGetUTF8CString(message_Str, message_Mem.ptr, message_Mem.bytes);
        const char* message = (const char*)message_Mem.ptr;
        JSStringRelease(message_Str);
        self->writeLogEntry(level, category, message);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef LogManager_BinaryDump(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""length"")");
        long length = (argumentCount<2) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""bytesPerLine"")");
        long bytesPerLine = (argumentCount<3) ? 20 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        size_t available = 0;
        if (length < 0 || bytesPerLine <= 0)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "invalid dump length or line width" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const char* inData = 0;
        if (IsUint8Array(arguments[0]))
        {
            size_t bytes = 0;
            const uint8* ptr = nullptr;
            if (!GetUint8ArrayData(arguments[0], ptr, bytes))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "expected an attached, non-shared Uint8Array" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (bytes > UINT32_MAX)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "byte array exceeds the supported size" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            inData = (const char*)ptr;
            available = bytes;
        }
        else
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[0], MemBlock_class()))
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "expected Uint8Array or MemBlock" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            MemBlock* memBlock = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef memBlock_ = JSValueToObject(ctx, arguments[1 -1], exception);
                memBlock = MemBlock_getCppObject(memBlock_);
            }
            if (!memBlock)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""MemBlock"" (""memBlock"")");
            inData = memBlock->ptr;
            available = memBlock->bytes;
        }
        size_t count = length == 0 ? available : static_cast<size_t>(length);
        if (count > available || count > (INT32_MAX - 32) / 16 || bytesPerLine > (INT32_MAX - 32) / 16)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "binaryDump range exceeds available or supported data" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        int dataSize = static_cast<int>(count);
        int outBufSize = (4 * dataSize) + (6 * dataSize/bytesPerLine) + (4 * bytesPerLine) + 32;
        char* outBuf = new char[outBufSize];
        OS::binaryDump(outBuf, outBufSize, inData, dataSize, bytesPerLine);
        JSValueRef dumpStrVal = JSC_MakeValueFromCString(ctx, outBuf);
        delete[] outBuf;
        return dumpStrVal;
    }

    log& main_getDebugLog();

    LogManager* New_LogManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        LogManager *theLogMgr = LogManager::getSingletonInstance();
        pdg::log& debugLog = main_getDebugLog();
        debugLog.setLogManager(theLogMgr);
        return theLogMgr;
    }

}
