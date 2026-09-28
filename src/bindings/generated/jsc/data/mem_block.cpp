// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/mem_block.cpp
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

    JSObjectRef MemBlock_newFromCpp(JSContextRef ctx, MemBlock* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, MemBlock_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, MemBlock_class());
        cppObj->mMemBlockScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef MemBlock_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        MemBlock* cppObj = New_MemBlock(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "MemBlock" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, MemBlock_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, MemBlock_class());
        cppObj->mMemBlockScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef MemBlock_class()
    {
        static JSStaticValue MemBlock_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction MemBlock_staticFunctions[] =
        {
            { "getData", MemBlock_GetData, kJSPropertyAttributeDontDelete },
            { "getDataSize", MemBlock_GetDataSize, kJSPropertyAttributeDontDelete },
            { "getByte", MemBlock_GetByte, kJSPropertyAttributeDontDelete },
            { "getBytes", MemBlock_GetBytes, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "MemBlock";
            definition.staticFunctions = MemBlock_staticFunctions;
            definition.staticValues = MemBlock_staticValues;
            definition.callAsConstructor = MemBlock_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef MemBlock_GetData(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        MemBlock* self = static_cast<MemBlock*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        JSValueRef resultVal = EncodeBinary(self->ptr, self->bytes);
        return resultVal;
    }
    JSValueRef MemBlock_GetDataSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        MemBlock* self = static_cast<MemBlock*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, self->bytes);
    }
    JSValueRef MemBlock_GetByte(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        MemBlock* self = static_cast<MemBlock*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""i"")");
        uint32 i = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        return JSValueMakeNumber(ctx, self->getByte(i));
    }
    JSValueRef MemBlock_GetBytes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        MemBlock* self = static_cast<MemBlock*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""start"")");
        uint32 start = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""len"")");
        uint32 len = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[2 -1], exception)));
        const std::string bytes = self->getBytes(start, len);
        JSValueRef resultVal = EncodeBinary(bytes.data(), bytes.size());
        return resultVal;
    }

    void CleanupMemBlockScriptObject(JSObjectRef obj) { }

    MemBlock* New_MemBlock(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new MemBlock(0, 0, false);
    }

}
