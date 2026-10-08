// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/font.cpp
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

#ifndef PDG_NO_GUI

    JSObjectRef Font_newFromCpp(JSContextRef ctx, Font* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Font_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Font_class());
        cppObj->mFontScriptObj = obj;
        JSValueProtect(ctx, obj);
        cppObj->addRef();
        return obj;
    }

    JSObjectRef Font_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* cppObj = New_Font(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Font" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Font_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Font_class());
        cppObj->mFontScriptObj = obj;
        JSValueProtect(ctx, obj);
        cppObj->addRef();
        return obj;
    }

    JSClassRef Font_class()
    {
        static JSStaticValue Font_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Font_staticFunctions[] =
        {
            { "get""FontName", Font_GetFontName, kJSPropertyAttributeDontDelete },
            { "get""FontHeight", Font_GetFontHeight, kJSPropertyAttributeDontDelete },
            { "get""FontLeading", Font_GetFontLeading, kJSPropertyAttributeDontDelete },
            { "get""FontCapHeight", Font_GetFontCapHeight, kJSPropertyAttributeDontDelete },
            { "get""FontAscent", Font_GetFontAscent, kJSPropertyAttributeDontDelete },
            { "get""FontDescent", Font_GetFontDescent, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Font";
            definition.staticFunctions = Font_staticFunctions;
            definition.staticValues = Font_staticValues;
            definition.callAsConstructor = Font_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef Font_GetFontName(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const char* theFontName = self->getFontName();
        return JSC_MakeValueFromCString(ctx, theFontName);
    }
    JSValueRef Font_GetFontHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""style"")");
        unsigned long style = (argumentCount<2) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        float theFontHeight = self->getFontHeight(size, style);
        return JSValueMakeNumber(ctx, theFontHeight);
    }
    JSValueRef Font_GetFontLeading(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""style"")");
        unsigned long style = (argumentCount<2) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        float theFontLeading = self->getFontLeading(size, style);
        return JSValueMakeNumber(ctx, theFontLeading);
    }
    JSValueRef Font_GetFontCapHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""style"")");
        unsigned long style = (argumentCount<2) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        float theFontCapHeight = self->getFontCapHeight(size, style);
        return JSValueMakeNumber(ctx, theFontCapHeight);
    }
    JSValueRef Font_GetFontAscent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""style"")");
        unsigned long style = (argumentCount<2) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        float theFontAscent = self->getFontAscent(size, style);
        return JSValueMakeNumber(ctx, theFontAscent);
    }
    JSValueRef Font_GetFontDescent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Font* self = static_cast<Font*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""style"")");
        unsigned long style = (argumentCount<2) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));
        float theFontDescent = self->getFontDescent(size, style);
        return JSValueMakeNumber(ctx, theFontDescent);
    }

    void CleanupFontScriptObject(JSObjectRef obj) { }

    Font* New_Font(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        s_SavedError.str(""); s_SavedError.clear();
        s_SavedError << "Font cannot be created directly, use pdg.gfx.createFont()";
        s_HaveSavedError = true;
        return 0;
    }
#endif

}
