// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/serializer.cpp
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

    JSObjectRef Serializer_newFromCpp(JSContextRef ctx, Serializer* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Serializer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Serializer_class());
        cppObj->mSerializerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef Serializer_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* cppObj = New_Serializer(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Serializer" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Serializer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Serializer_class());
        cppObj->mSerializerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef Serializer_class()
    {
        static JSStaticValue Serializer_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Serializer_staticFunctions[] =
        {
            { "setResourceMode", Serializer_SetResourceMode, kJSPropertyAttributeDontDelete },
            { "getResourceMode", Serializer_GetResourceMode, kJSPropertyAttributeDontDelete },
            { "serialize_8", Serializer_Serialize_8, kJSPropertyAttributeDontDelete },
            { "serialize_8u", Serializer_Serialize_8u, kJSPropertyAttributeDontDelete },
            { "sizeof_8", Serializer_Sizeof_8, kJSPropertyAttributeDontDelete },
            { "sizeof_8u", Serializer_Sizeof_8u, kJSPropertyAttributeDontDelete },
            { "serialize_d", Serializer_Serialize_d, kJSPropertyAttributeDontDelete },
            { "serialize_f", Serializer_Serialize_f, kJSPropertyAttributeDontDelete },
            { "serialize_4", Serializer_Serialize_4, kJSPropertyAttributeDontDelete },
            { "serialize_4u", Serializer_Serialize_4u, kJSPropertyAttributeDontDelete },
            { "serialize_3u", Serializer_Serialize_3u, kJSPropertyAttributeDontDelete },
            { "serialize_2", Serializer_Serialize_2, kJSPropertyAttributeDontDelete },
            { "serialize_2u", Serializer_Serialize_2u, kJSPropertyAttributeDontDelete },
            { "serialize_1", Serializer_Serialize_1, kJSPropertyAttributeDontDelete },
            { "serialize_1u", Serializer_Serialize_1u, kJSPropertyAttributeDontDelete },
            { "serialize_bool", Serializer_Serialize_bool, kJSPropertyAttributeDontDelete },
            { "serialize_uint", Serializer_Serialize_uint, kJSPropertyAttributeDontDelete },
            { "serialize_color", Serializer_Serialize_color, kJSPropertyAttributeDontDelete },
            { "serialize_offset", Serializer_Serialize_offset, kJSPropertyAttributeDontDelete },
            { "serialize_point", Serializer_Serialize_point, kJSPropertyAttributeDontDelete },
            { "serialize_vector", Serializer_Serialize_vector, kJSPropertyAttributeDontDelete },
            { "serialize_rect", Serializer_Serialize_rect, kJSPropertyAttributeDontDelete },
            { "serialize_rotr", Serializer_Serialize_rotr, kJSPropertyAttributeDontDelete },
            { "serialize_quad", Serializer_Serialize_quad, kJSPropertyAttributeDontDelete },
            { "serialize_str", Serializer_Serialize_str, kJSPropertyAttributeDontDelete },
            { "serialize_mem", Serializer_Serialize_mem, kJSPropertyAttributeDontDelete },
            { "serialize_obj", Serializer_Serialize_obj, kJSPropertyAttributeDontDelete },
            { "serialize_ref", Serializer_Serialize_ref, kJSPropertyAttributeDontDelete },
            { "sizeof_d", Serializer_Sizeof_d, kJSPropertyAttributeDontDelete },
            { "sizeof_f", Serializer_Sizeof_f, kJSPropertyAttributeDontDelete },
            { "sizeof_4", Serializer_Sizeof_4, kJSPropertyAttributeDontDelete },
            { "sizeof_4u", Serializer_Sizeof_4u, kJSPropertyAttributeDontDelete },
            { "sizeof_3u", Serializer_Sizeof_3u, kJSPropertyAttributeDontDelete },
            { "sizeof_2", Serializer_Sizeof_2, kJSPropertyAttributeDontDelete },
            { "sizeof_2u", Serializer_Sizeof_2u, kJSPropertyAttributeDontDelete },
            { "sizeof_1", Serializer_Sizeof_1, kJSPropertyAttributeDontDelete },
            { "sizeof_1u", Serializer_Sizeof_1u, kJSPropertyAttributeDontDelete },
            { "sizeof_bool", Serializer_Sizeof_bool, kJSPropertyAttributeDontDelete },
            { "sizeof_uint", Serializer_Sizeof_uint, kJSPropertyAttributeDontDelete },
            { "sizeof_color", Serializer_Sizeof_color, kJSPropertyAttributeDontDelete },
            { "sizeof_offset", Serializer_Sizeof_offset, kJSPropertyAttributeDontDelete },
            { "sizeof_point", Serializer_Sizeof_point, kJSPropertyAttributeDontDelete },
            { "sizeof_vector", Serializer_Sizeof_vector, kJSPropertyAttributeDontDelete },
            { "sizeof_rect", Serializer_Sizeof_rect, kJSPropertyAttributeDontDelete },
            { "sizeof_rotr", Serializer_Sizeof_rotr, kJSPropertyAttributeDontDelete },
            { "sizeof_quad", Serializer_Sizeof_quad, kJSPropertyAttributeDontDelete },
            { "sizeof_str", Serializer_Sizeof_str, kJSPropertyAttributeDontDelete },
            { "sizeof_mem", Serializer_Sizeof_mem, kJSPropertyAttributeDontDelete },
            { "sizeof_obj", Serializer_Sizeof_obj, kJSPropertyAttributeDontDelete },
            { "sizeof_ref", Serializer_Sizeof_ref, kJSPropertyAttributeDontDelete },
            { "getDataSize", Serializer_GetDataSize, kJSPropertyAttributeDontDelete },
            { "getDataPtr", Serializer_GetDataPtr, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Serializer";
            definition.staticFunctions = Serializer_staticFunctions;
            definition.staticValues = Serializer_staticValues;
            definition.callAsConstructor = Serializer_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef Serializer_SetResourceMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mode"")");
        double mode_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (mode_temp < -2147483648.0 || mode_temp > 2147483647.0 || mode_temp != (long)mode_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-2147483648, 2147483647] (""mode"")");
        }
        int32 mode = (int32)mode_temp;
        try { self->setResourceMode(mode); return thisObject; }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Serializer_GetResourceMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeNumber(ctx, self->getResourceMode());
    }
    JSValueRef Serializer_Serialize_d(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->serialize_d(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_f(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->serialize_f(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_8(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->serialize_8(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_8u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->serialize_8u(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_4(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < -2147483648.0 || val_temp > 2147483647.0 || val_temp != (long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-2147483648, 2147483647] (""val"")");
        }
        int32 val = (int32)val_temp;
        self->serialize_4(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_4u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 4294967295.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 4294967295] (""val"")");
        }
        uint32 val = (uint32)val_temp;
        self->serialize_4u(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_3u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 16777215.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 16777215] (""val"")");
        }
        uint32 val = (uint32)val_temp;
        self->serialize_3u(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_2(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        long val_temp = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (val_temp < -32768 || val_temp > 32767)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-32768, 32767] (""val"")");
        }
        int16 val = (int16)val_temp;
        self->serialize_2(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_2u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 65535.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 65535] (""val"")");
        }
        uint16 val = (uint16)val_temp;
        self->serialize_2u(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_1(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        long val_temp = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (val_temp < -128 || val_temp > 127)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-128, 127] (""val"")");
        }
        int8 val = (int8)val_temp;
        self->serialize_1(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_1u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 255.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 255] (""val"")");
        }
        uint8 val = (uint8)val_temp;
        self->serialize_1u(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_bool(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""val"")");
        bool val = JSValueToBoolean(ctx, arguments[1 -1]);
        self->serialize_bool(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_uint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        uint32 val = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        self->serialize_uint(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_color(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Color val;
        auto val_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], val, exception);
        if (!val_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        self->serialize_color(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_offset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset val;
        auto val_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], val, exception);
        if (!val_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        self->serialize_offset(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_point(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Point val;
        auto val_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], val, exception);
        if (!val_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        self->serialize_point(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_vector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Vector val;
        auto val_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], val, exception);
        if (!val_isVector.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isVector)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
        };
        self->serialize_vector(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_rect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Rect r;
        auto r_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], r, exception);
        if (!r_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*r_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        self->serialize_rect(r);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_rotr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::RotatedRect val;
        auto val_isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[1 -1], val, exception);
        if (!val_isRotatedRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isRotatedRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", arguments[1 -1]);
        };
        self->serialize_rotr(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_quad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Quad val;
        auto val_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], val, exception);
        if (!val_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };
        self->serialize_quad(val);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_str(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""str"")");
        JSStringRef str_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock str_Mem(JSStringGetMaximumUTF8CStringSize(str_Str));
        JSStringGetUTF8CString(str_Str, str_Mem.ptr, str_Mem.bytes);
        const char* str = (const char*)str_Mem.ptr;
        JSStringRelease(str_Str);
        self->serialize_str(str);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_mem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        bool isStr = JSValueIsString(ctx, arguments[0]);
        if (!isStr && !JSValueIsObject(ctx, arguments[0]))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "argument 1 (mem) must be either a binary string or an object of type MemBlock" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if (isStr)
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(arguments[0], &bytes);
            self->serialize_mem(ptr, bytes);
        }
        else
        {
            MemBlock* memBlock = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef memBlock_ = JSValueToObject(ctx, arguments[1 -1], exception);
                memBlock = MemBlock_getCppObject(memBlock_);
            }
            if (!memBlock)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""MemBlock"" (""memBlock"")");
            self->serialize_mem(memBlock->ptr, memBlock->bytes);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_Serialize_ref(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsObject(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object (""obj"")");
        JSObjectRef obj = JSValueToObject(ctx, arguments[1 -1], exception);
        self->serialize_ref< JSObjectRef >(&obj);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_GetDataSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 dataSize = self->getDataSize();
        return JSValueMakeNumber(ctx, dataSize);
    }
    JSValueRef Serializer_GetDataPtr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);

        MemBlock* memBlock = new MemBlock((char*)self->getDataPtr(), self->getDataSize(), false);
        if (!memBlock) return JSValueMakeNull(ctx);
        if (!memBlock->mMemBlockScriptObj)
        {
            return MemBlock_newFromCpp(ctx, memBlock);
        }
        else
        {
            return memBlock->mMemBlockScriptObj;
        };
    }
    JSValueRef Serializer_Sizeof_1(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number int]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        long val_temp = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (val_temp < -128 || val_temp > 127)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-128, 127] (""val"")");
        }
        int8 val = (int8)val_temp;
        size_t n = self->sizeof_1(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_1u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 255.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 255] (""val"")");
        }
        uint8 val = (uint8)val_temp;
        size_t n = self->sizeof_1u(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_2(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number int]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        long val_temp = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (val_temp < -32768 || val_temp > 32767)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-32768, 32767] (""val"")");
        }
        int16 val = (int16)val_temp;
        size_t n = self->sizeof_2(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_2u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 65535.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 65535] (""val"")");
        }
        uint16 val = (uint16)val_temp;
        size_t n = self->sizeof_2u(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_3u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 16777215.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 16777215] (""val"")");
        }
        uint32 val = (uint32)val_temp;
        size_t n = self->sizeof_3u(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_4(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number int]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < -2147483648.0 || val_temp > 2147483647.0 || val_temp != (long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [-2147483648, 2147483647] (""val"")");
        }
        int32 val = (int32)val_temp;
        size_t n = self->sizeof_4(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_4u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val_temp = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (val_temp < 0.0 || val_temp > 4294967295.0 || val_temp != (unsigned long)val_temp)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number in range [0, 4294967295] (""val"")");
        }
        uint32 val = (uint32)val_temp;
        size_t n = self->sizeof_4u(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_8(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number int]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        size_t n = self->sizeof_8(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_8u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        size_t n = self->sizeof_8u(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_f(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "number" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        size_t n = self->sizeof_f(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_d(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "number" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        double val = JSValueToNumber(ctx, arguments[1 -1], exception);
        size_t n = self->sizeof_d(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_uint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[number uint]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""val"")");
        uint32 val = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        size_t n = self->sizeof_uint(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_str(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "string" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""val"")");
        JSStringRef val_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock val_Mem(JSStringGetMaximumUTF8CStringSize(val_Str));
        JSStringGetUTF8CString(val_Str, val_Mem.ptr, val_Mem.bytes);
        const char* val = (const char*)val_Mem.ptr;
        JSStringRelease(val_Str);
        size_t n = self->sizeof_str(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_bool(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "boolean" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""val"")");
        bool val = JSValueToBoolean(ctx, arguments[1 -1]);
        size_t n = self->sizeof_bool(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_point(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Point]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Point val;
        auto val_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], val, exception);
        if (!val_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        size_t n = self->sizeof_point(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_offset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Offset]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Offset val;
        auto val_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], val, exception);
        if (!val_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        size_t n = self->sizeof_offset(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_vector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Vector]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Vector val;
        auto val_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], val, exception);
        if (!val_isVector.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isVector)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
        };
        size_t n = self->sizeof_vector(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_rect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Rect]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Rect val;
        auto val_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], val, exception);
        if (!val_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        size_t n = self->sizeof_rect(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_rotr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object RotatedRect]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::RotatedRect val;
        auto val_isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[1 -1], val, exception);
        if (!val_isRotatedRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isRotatedRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", arguments[1 -1]);
        };
        size_t n = self->sizeof_rotr(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_quad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Quad]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Quad val;
        auto val_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], val, exception);
        if (!val_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };
        size_t n = self->sizeof_quad(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_color(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "[object Color]" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Color val;
        auto val_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], val, exception);
        if (!val_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*val_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        size_t n = self->sizeof_color(val);
        return JSValueMakeNumber(ctx, n);
    }
    JSValueRef Serializer_Sizeof_ref(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount == 1 && JSValueIsNull(ctx, arguments[0]))
        {
            return JSC_MakeValueFromCString(ctx, "[number uint] function(" "object" " val) - ");
        }
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsObject(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object (""val"")");
        JSObjectRef val = JSValueToObject(ctx, arguments[1 -1], exception);
        size_t n = self->sizeof_ref< JSObjectRef >(&val);
        return JSValueMakeNumber(ctx, n);
    }

    JSValueRef Serializer_Sizeof_obj(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (JSValueIsNull(ctx, arguments[0]))
        {
            size_t n = 3;
            return JSValueMakeNumber(ctx, n);
        }
#ifdef PDG_USING_JAVASCRIPT_CORE
        ISerializable* val = JSC_GetSerializable(ctx, arguments[0]);
        if (!val)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a serializable object" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
#else
        ISerializable* val = V8_GetSerializable(isolate, arguments[0]);
        if (!val)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a serializable object" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
#endif
        size_t n;
        try { n = self->sizeof_obj(val); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
#ifdef PDG_USING_JAVASCRIPT_CORE
        if (RestorePendingScriptException(exception))
        {
            return JSValueMakeUndefined(ctx);
        }
#endif
        return JSValueMakeNumber(ctx, n);
    }

    JSValueRef Serializer_Sizeof_mem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        bool isStr = JSValueIsString(ctx, arguments[0]);
        if (!isStr && !JSValueIsObject(ctx, arguments[0]))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "argument 1 (mem) must be either a binary string or an object of type MemBlock" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        size_t n = 0;
        if (isStr)
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(arguments[0], &bytes);
            n = self->sizeof_mem(ptr, bytes);
        }
        else
        {
            MemBlock* memBlock = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef memBlock_ = JSValueToObject(ctx, arguments[1 -1], exception);
                memBlock = MemBlock_getCppObject(memBlock_);
            }
            if (!memBlock)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""MemBlock"" (""memBlock"")");
            n = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
        }
        return JSValueMakeNumber(ctx, n);
    }

    void CleanupSerializerScriptObject(JSObjectRef obj) { }

    Serializer* New_Serializer(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new Serializer();
    }

}
