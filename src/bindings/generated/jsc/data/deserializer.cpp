// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/deserializer.cpp
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

    static JSStringRef symbol_getSerializedSize = 0;
    static JSStringRef symbol_serialize = 0;
    static JSStringRef symbol_deserialize = 0;
    static JSStringRef symbol_getMyClassTag = 0;
    static JSStringRef symbol_constructor = 0;

    JSObjectRef Deserializer_newFromCpp(JSContextRef ctx, Deserializer* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Deserializer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Deserializer_class());
        cppObj->mDeserializerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef Deserializer_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* cppObj = New_Deserializer(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Deserializer" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Deserializer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Deserializer_class());
        cppObj->mDeserializerScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef Deserializer_class()
    {
        static JSStaticValue Deserializer_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Deserializer_staticFunctions[] =
        {
            { "deserialize_8", Deserializer_Deserialize_8, kJSPropertyAttributeDontDelete },
            { "deserialize_8u", Deserializer_Deserialize_8u, kJSPropertyAttributeDontDelete },
            { "deserialize_d", Deserializer_Deserialize_d, kJSPropertyAttributeDontDelete },
            { "deserialize_f", Deserializer_Deserialize_f, kJSPropertyAttributeDontDelete },
            { "deserialize_4", Deserializer_Deserialize_4, kJSPropertyAttributeDontDelete },
            { "deserialize_4u", Deserializer_Deserialize_4u, kJSPropertyAttributeDontDelete },
            { "deserialize_3u", Deserializer_Deserialize_3u, kJSPropertyAttributeDontDelete },
            { "deserialize_2", Deserializer_Deserialize_2, kJSPropertyAttributeDontDelete },
            { "deserialize_2u", Deserializer_Deserialize_2u, kJSPropertyAttributeDontDelete },
            { "deserialize_1", Deserializer_Deserialize_1, kJSPropertyAttributeDontDelete },
            { "deserialize_1u", Deserializer_Deserialize_1u, kJSPropertyAttributeDontDelete },
            { "deserialize_bool", Deserializer_Deserialize_bool, kJSPropertyAttributeDontDelete },
            { "deserialize_uint", Deserializer_Deserialize_uint, kJSPropertyAttributeDontDelete },
            { "deserialize_color", Deserializer_Deserialize_color, kJSPropertyAttributeDontDelete },
            { "deserialize_offset", Deserializer_Deserialize_offset, kJSPropertyAttributeDontDelete },
            { "deserialize_point", Deserializer_Deserialize_point, kJSPropertyAttributeDontDelete },
            { "deserialize_vector", Deserializer_Deserialize_vector, kJSPropertyAttributeDontDelete },
            { "deserialize_rect", Deserializer_Deserialize_rect, kJSPropertyAttributeDontDelete },
            { "deserialize_rotr", Deserializer_Deserialize_rotr, kJSPropertyAttributeDontDelete },
            { "deserialize_quad", Deserializer_Deserialize_quad, kJSPropertyAttributeDontDelete },
            { "deserialize_str", Deserializer_Deserialize_str, kJSPropertyAttributeDontDelete },
            { "deserialize_mem", Deserializer_Deserialize_mem, kJSPropertyAttributeDontDelete },
            { "deserialize_memGetLen", Deserializer_Deserialize_memGetLen, kJSPropertyAttributeDontDelete },
            { "deserialize_obj", Deserializer_Deserialize_obj, kJSPropertyAttributeDontDelete },
            { "deserialize_ref", Deserializer_Deserialize_ref, kJSPropertyAttributeDontDelete },
            { "setDataPtr", Deserializer_SetDataPtr, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Deserializer";
            definition.staticFunctions = Deserializer_staticFunctions;
            definition.staticValues = Deserializer_staticValues;
            definition.callAsConstructor = Deserializer_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef Deserializer_Deserialize_d(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            double val = self->deserialize_d();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_f(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            float val = self->deserialize_f();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_8(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            int64 val = self->deserialize_8();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_8u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint64 val = self->deserialize_8u();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_4(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            int32 val = self->deserialize_4();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_4u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint32 val = self->deserialize_4u();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_3u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint32 val = self->deserialize_3u();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_2(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            int16 val = self->deserialize_2();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_2u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint16 val = self->deserialize_2u();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_1(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            int8 val = self->deserialize_1();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_1u(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint8 val = self->deserialize_1u();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_bool(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            bool val = self->deserialize_bool();
            return JSValueMakeBoolean(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_uint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint32 val = self->deserialize_uint();
            return JSValueMakeNumber(ctx, val);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_color(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Color val = self->deserialize_color();
            return JSC_ColorToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_offset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Offset val = self->deserialize_offset();
            return JSC_OffsetToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_point(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Point val = self->deserialize_point();
            return JSC_PointToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_vector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Vector val = self->deserialize_vector();
            return JSC_VectorToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_rect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Rect val = self->deserialize_rect();
            return JSC_RectToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_rotr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            RotatedRect val = self->deserialize_rotr();
            return JSC_RectToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_quad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            Quad val = self->deserialize_quad();
            return JSC_QuadToValue(ctx, val, exception);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_str(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            std::string mystr;
            self->deserialize_string(mystr);
            return JSC_MakeValueFromCString(ctx, mystr.c_str());
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_strGetLen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint32 len = self->deserialize_strGetLen();
            return JSValueMakeNumber(ctx, len);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_mem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        size_t len, len2;
        try
        {
            len = self->deserialize_memGetLen();
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        char* mem = (char*) std::malloc(len);
        try
        {
            len2 = self->deserialize_mem(mem, len);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if (len2 != len)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << "Deserializer internal error, deserialized memory length mismatch " << len << " (" << (void*)len << ") != " << len2 << " (" << (void*)len2 << ")" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);

        }

        MemBlock* memBlock = new MemBlock(mem, len, true);
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
    JSValueRef Deserializer_Deserialize_memGetLen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            uint32 len = self->deserialize_memGetLen();
            return JSValueMakeNumber(ctx, len);
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_SetDataPtr(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[0]) && !JSValueIsObject(ctx, arguments[0]))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "argument 1 (mem) must be either a binary string or an object of type MemBlock" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if (JSValueIsString(ctx, arguments[0]))
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(arguments[0], &bytes);
            self->setDataPtr(ptr, bytes);
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
            self->setDataPtr(memBlock->ptr, memBlock->bytes);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Deserializer_Deserialize_obj(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        self->mDeserializerScriptObj = thisObject;
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            ISerializable* obj = self->deserialize_obj();
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (RestorePendingScriptException(exception))
            {
                return JSValueMakeUndefined(ctx);
            }
#endif
            if (!obj) { return JSValueMakeNull(ctx); }
            if (auto* sprite = dynamic_cast<Sprite*>(obj))
            {
#ifdef PDG_USING_V8
                auto result = SpriteWrap::NewFromCpp(isolate, sprite);
#else
                auto result = Sprite_newFromCpp(ctx, sprite);
#endif
                sprite->release();
                return result;
            }

            if (auto* image = dynamic_cast<ImageStrip*>(obj))
            {
                if (!image) return JSValueMakeNull(ctx);
                if (!image->mImageStripScriptObj)
                {
                    return ImageStrip_newFromCpp(ctx, image);
                }
                else
                {
                    return image->mImageStripScriptObj;
                };
            }
            SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, obj->mISerializableScriptObj, "Dumping " "ISerializable" " object:") )
                if (!obj) return JSValueMakeNull(ctx);
            if (!obj->mISerializableScriptObj)
            {
                return ISerializable_newFromCpp(ctx, obj);
            }
            else
            {
                return obj->mISerializableScriptObj;
            };
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(sync_error& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Deserializer_Deserialize_ref(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Deserializer* self = static_cast<Deserializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try
        {
            JSObjectRef obj = *self->deserialize_ref< JSObjectRef >();
            return obj;
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef RegisterSerializableClass(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef constructorFunc = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!constructorFunc || !JSObjectIsFunction(ctx, constructorFunc) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""constructorFunc"")");
        JSValueRef objVal = ((constructorFunc) ? JSObjectCallAsConstructor(ctx, constructorFunc, 0, nullptr, exception) : nullptr);
        JSObjectRef obj = ((objVal && JSValueIsObject(ctx, objVal)) ? JSValueToObject(ctx, objVal, exception) : nullptr);
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, obj, "Dumping " "ISerializable" " object:") );
        ISerializable* nativeSerializable = 0;
        if (JSValueIsObject(ctx, objVal))
        {
            JSObjectRef nativeSerializable_obj_ = JSValueToObject(ctx, objVal, exception);
            nativeSerializable = ISerializable_getCppObject(nativeSerializable_obj_);
            if (!nativeSerializable)
            {
                JSValueRef protoVal_ = JSObjectGetPrototype(ctx, nativeSerializable_obj_);
                if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                {
                    JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                    nativeSerializable = ISerializable_getCppObject(protoObj_);
                }
            }
        };
        uint32 classTag = 0;
        if ((obj && JSObjectHasProperty(ctx, obj, ((symbol_getMyClassTag) ? symbol_getMyClassTag : symbol_getMyClassTag = JSStringCreateWithUTF8CString("getMyClassTag")))))
        {
            JSValueRef getMyClassTagVal = JSObjectGetProperty(ctx, obj, ((symbol_getMyClassTag) ? symbol_getMyClassTag : symbol_getMyClassTag = JSStringCreateWithUTF8CString("getMyClassTag")), exception);
            if (!JSC_ValueIsFunction(ctx, getMyClassTagVal, exception))
            {
                std::ostringstream msg;
                msg << "argument 1: ISerializable subclass " << JSC_GetObjectClassName(ctx, obj) << " getMyClassTag property is not a function!!";
                std::ostringstream excpt_;
                excpt_ << "throw "<< "Error" << "('" << "Error: " << msg.str().c_str() << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);
            }
            JSObjectRef func = JSC_ValueToFunction(ctx, getMyClassTagVal, exception);
            JSValueRef classTagVal = JSObjectCallAsFunction(ctx, func, obj, 0, 0, exception);
            classTag = (uint32)floor(fabs(JSValueToNumber(ctx, classTagVal, exception)));
        }
        else if (nativeSerializable)
        {
            classTag = nativeSerializable->getMyClassTag();
        }
        else
        {
            std::ostringstream msg;
            msg << "argument 1: ISerializable subclass " << JSC_GetObjectClassName(ctx, obj) << " missing getMyClassTag() Function!!";
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << msg.str().c_str() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        Deserializer::registerScriptClass(classTag, constructorFunc);
        return JSValueMakeUndefined(ctx);
    }

    void CleanupDeserializerScriptObject(JSObjectRef obj) { }

    Deserializer* New_Deserializer(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        return new Deserializer();
    }

}
