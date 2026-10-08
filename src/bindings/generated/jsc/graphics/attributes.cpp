// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/attributes.cpp
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
#include <cmath>
#include <limits>

namespace pdg
{

    JSObjectRef Attributes_newFromCpp(JSContextRef ctx, Attributes* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Attributes_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Attributes_class());
        cppObj->mAttributesScriptObj = obj;
        return obj;
    }

    JSObjectRef Attributes_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* cppObj = New_Attributes(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Attributes" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Attributes_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Attributes_class());
        cppObj->mAttributesScriptObj = obj;
        return obj;
    }

    JSClassRef Attributes_class()
    {

        static JSStaticValue Attributes_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Attributes_staticFunctions[] =
        {
            { "withAppearance", Attributes_WithAppearance, kJSPropertyAttributeDontDelete },

            { "lineColor", Attributes_LineColor, kJSPropertyAttributeDontDelete },

            { "lineThickness", Attributes_LineThickness, kJSPropertyAttributeDontDelete },

            { "lineOpacity", Attributes_LineOpacity, kJSPropertyAttributeDontDelete },

            { "lineStyle", Attributes_SetLineStyle, kJSPropertyAttributeDontDelete },

            { "fillColor", Attributes_FillColor, kJSPropertyAttributeDontDelete },

            { "fillOpacity", Attributes_FillOpacity, kJSPropertyAttributeDontDelete },

            { "fillGradient", Attributes_FillGradient, kJSPropertyAttributeDontDelete },

            { "fillRadialGradient", Attributes_FillRadialGradient, kJSPropertyAttributeDontDelete },

            { "roundedCorners", Attributes_RoundedCorners, kJSPropertyAttributeDontDelete },

            { "translation", Attributes_Translation, kJSPropertyAttributeDontDelete },

            { "rotation", Attributes_Rotation, kJSPropertyAttributeDontDelete },

            { "scale", Attributes_Scale, kJSPropertyAttributeDontDelete },

            { "skew", Attributes_Skew, kJSPropertyAttributeDontDelete },

            { "transform", Attributes_Transform, kJSPropertyAttributeDontDelete },

            { "setTransform", Attributes_SetTransform, kJSPropertyAttributeDontDelete },

            { "blendMode", Attributes_SetBlendMode, kJSPropertyAttributeDontDelete },

            { "textSize", Attributes_TextSize, kJSPropertyAttributeDontDelete },

            { "textStyle", Attributes_TextStyle, kJSPropertyAttributeDontDelete },

#ifndef PDG_NO_GUI

            { "font", Attributes_SetFont, kJSPropertyAttributeDontDelete },
#endif

            { "frame", Attributes_Frame, kJSPropertyAttributeDontDelete },

            { "fitType", Attributes_SetFitType, kJSPropertyAttributeDontDelete },

            { "clipOverflow", Attributes_ClipOverflow, kJSPropertyAttributeDontDelete },

            { "subsection", Attributes_Subsection, kJSPropertyAttributeDontDelete },

            { "sphereRotation", Attributes_SphereRotation, kJSPropertyAttributeDontDelete },

            { "polarOffset", Attributes_PolarOffset, kJSPropertyAttributeDontDelete },

            { "lightOffset", Attributes_LightOffset, kJSPropertyAttributeDontDelete },

            { "ambientLight", Attributes_AmbientLight, kJSPropertyAttributeDontDelete },

            { "texture", Attributes_Texture, kJSPropertyAttributeDontDelete },

            { "getLineColor", Attributes_GetLineColor, kJSPropertyAttributeDontDelete },

            { "getLineThickness", Attributes_GetLineThickness, kJSPropertyAttributeDontDelete },

            { "getLineOpacity", Attributes_GetLineOpacity, kJSPropertyAttributeDontDelete },

            { "getLineStyle", Attributes_GetLineStyle, kJSPropertyAttributeDontDelete },

            { "getFillColor", Attributes_GetFillColor, kJSPropertyAttributeDontDelete },

            { "getFillOpacity", Attributes_GetFillOpacity, kJSPropertyAttributeDontDelete },

            { "getRoundedCornerRadius", Attributes_GetRoundedCornerRadius, kJSPropertyAttributeDontDelete },

            { "getGradientType", Attributes_GetGradientType, kJSPropertyAttributeDontDelete },

            { "getGradientStart", Attributes_GetGradientStart, kJSPropertyAttributeDontDelete },

            { "getGradientEnd", Attributes_GetGradientEnd, kJSPropertyAttributeDontDelete },

            { "getGradientStartColor", Attributes_GetGradientStartColor, kJSPropertyAttributeDontDelete },

            { "getGradientEndColor", Attributes_GetGradientEndColor, kJSPropertyAttributeDontDelete },

            { "getRadialGradientCenter", Attributes_GetRadialGradientCenter, kJSPropertyAttributeDontDelete },

            { "getRadialGradientRadius", Attributes_GetRadialGradientRadius, kJSPropertyAttributeDontDelete },

            { "getRadialGradientCenterColor", Attributes_GetRadialGradientCenterColor, kJSPropertyAttributeDontDelete },

            { "getRadialGradientEndColor", Attributes_GetRadialGradientEndColor, kJSPropertyAttributeDontDelete },

            { "getTransform", Attributes_GetTransform, kJSPropertyAttributeDontDelete },

            { "getBlendMode", Attributes_GetBlendMode, kJSPropertyAttributeDontDelete },

            { "getTextSize", Attributes_GetTextSize, kJSPropertyAttributeDontDelete },

            { "getTextStyle", Attributes_GetTextStyle, kJSPropertyAttributeDontDelete },

#ifndef PDG_NO_GUI

            { "getFont", Attributes_GetFont, kJSPropertyAttributeDontDelete },
#endif

            { "getFrame", Attributes_GetFrame, kJSPropertyAttributeDontDelete },

            { "getFitType", Attributes_GetFitType, kJSPropertyAttributeDontDelete },

            { "getClipOverflow", Attributes_GetClipOverflow, kJSPropertyAttributeDontDelete },

            { "getSubsection", Attributes_GetSubsection, kJSPropertyAttributeDontDelete },

            { "getSphereRotation", Attributes_GetSphereRotation, kJSPropertyAttributeDontDelete },

            { "getPolarOffset", Attributes_GetPolarOffset, kJSPropertyAttributeDontDelete },

            { "getLightOffset", Attributes_GetLightOffset, kJSPropertyAttributeDontDelete },

            { "getAmbientLight", Attributes_GetAmbientLight, kJSPropertyAttributeDontDelete },

            { "getTexture", Attributes_GetTexture, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Attributes";
            definition.staticFunctions = Attributes_staticFunctions;
            definition.staticValues = Attributes_staticValues;
            definition.callAsConstructor = Attributes_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;
    }
    void CleanupAttributesScriptObject(JSObjectRef obj) { }

    Attributes* New_Attributes(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        return new Attributes();
    }
    JSValueRef Attributes_WithAppearance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);

        Attributes* overrides = ExtractAttributes(arguments[1 -1]);
        if (!overrides)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""textOnly"")");
        bool textOnly = (argumentCount<2) ? false : JSValueToBoolean(ctx, arguments[2 -1]);
        Attributes* result = new Attributes(self->withAppearance(*overrides, textOnly));
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mAttributesScriptObj)
        {
            return Attributes_newFromCpp(ctx, result);
        }
        else
        {
            return result->mAttributesScriptObj;
        };
    }
    JSValueRef Attributes_GetLineColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getLineColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetLineThickness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float thickness = self->getLineThickness();
        return JSValueMakeNumber(ctx, thickness);
    }
    JSValueRef Attributes_GetLineOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float opacity = self->getLineOpacity();
        return JSValueMakeNumber(ctx, opacity);
    }
    JSValueRef Attributes_GetLineStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        LineStyle style = self->getLineStyle();
        return JSValueMakeNumber(ctx, style);
    }
    JSValueRef Attributes_GetFillColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getFillColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetFillOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float opacity = self->getFillOpacity();
        return JSValueMakeNumber(ctx, opacity);
    }
    JSValueRef Attributes_GetRoundedCornerRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float radius = self->getRoundedCornerRadius();
        return JSValueMakeNumber(ctx, radius);
    }
    JSValueRef Attributes_GetGradientType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        GradientType type = self->getGradientType();
        return JSValueMakeNumber(ctx, type);
    }
    JSValueRef Attributes_GetGradientStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point start = const_cast<Point&>(self->getGradientStart());
        return JSC_PointToValue(ctx, start, exception);
    }
    JSValueRef Attributes_GetGradientEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point end = const_cast<Point&>(self->getGradientEnd());
        return JSC_PointToValue(ctx, end, exception);
    }
    JSValueRef Attributes_GetGradientStartColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getGradientStartColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetGradientEndColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getGradientEndColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetRadialGradientCenter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point center = const_cast<Point&>(self->getRadialGradientCenter());
        return JSC_PointToValue(ctx, center, exception);
    }
    JSValueRef Attributes_GetRadialGradientRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float radius = self->getRadialGradientRadius();
        return JSValueMakeNumber(ctx, radius);
    }
    JSValueRef Attributes_GetRadialGradientCenterColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getRadialGradientCenterColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetRadialGradientEndColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getRadialGradientEndColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const glm::mat3& matrix = self->getTransform();
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                JSObjectSetPropertyAtIndex(ctx, result, (unsigned)index,
                    JSValueMakeNumber(ctx, matrix[i][j]), exception);
            }
        }
        return result;
#else
        v8::Local<v8::Array> result = v8::Array::New(isolate, 9);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                (void)result->Set(context, index, v8::Number::New(isolate, matrix[i][j]));
            }
        }
        args.GetReturnValue().Set(result);
#endif
    }
    JSValueRef Attributes_GetBlendMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        BlendMode blendMode = self->getBlendMode();
        return JSValueMakeNumber(ctx, static_cast<int>(blendMode));
    }
    JSValueRef Attributes_LineColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Color color;
            auto color_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], color, exception);
            if (!color_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*color_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
            };
            self->lineColor(color);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_LineThickness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""thickness"")");
            double thickness = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->lineThickness(thickness);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_LineOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
            double opacity = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->lineOpacity(opacity);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_SetLineStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""lineStyle"")");
            double lineStyle = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->lineStyle(static_cast<LineStyle>(lineStyle));
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_FillColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Color color;
            auto color_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], color, exception);
            if (!color_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*color_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
            };
            self->fillColor(color);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_FillOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
            double opacity = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->fillOpacity(opacity);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_FillGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4);
            pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            pdg::Color startColor;
            auto startColor_isColor = JSC_ValueIsColor(ctx, arguments[2 -1], startColor, exception);
            if (!startColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*startColor_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Color", arguments[2 -1]);
            };
            pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
            };
            pdg::Color endColor;
            auto endColor_isColor = JSC_ValueIsColor(ctx, arguments[4 -1], endColor, exception);
            if (!endColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*endColor_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 4, "Color", arguments[4 -1]);
            };
            self->fillGradient(start, startColor, end, endColor);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_FillRadialGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4);
            pdg::Point center;
            auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
            if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*center_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            pdg::Color centerColor;
            auto centerColor_isColor = JSC_ValueIsColor(ctx, arguments[2 -1], centerColor, exception);
            if (!centerColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*centerColor_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Color", arguments[2 -1]);
            };
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[3 -1], exception);
            pdg::Color endColor;
            auto endColor_isColor = JSC_ValueIsColor(ctx, arguments[4 -1], endColor, exception);
            if (!endColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*endColor_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 4, "Color", arguments[4 -1]);
            };
            self->fillRadialGradient(center, centerColor, radius, endColor);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_RoundedCorners(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->roundedCorners(radius);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Translation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->translation(offset);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Rotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            pdg::Point center;
            if (argumentCount < 2)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], center, exception);
                if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*center_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
                }
            };
            self->rotation(radians, center);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Scale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xFactor"")");
            double xFactor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yFactor"")");
            double yFactor = (argumentCount<2) ? xFactor : JSValueToNumber(ctx, arguments[2 -1], exception);
            pdg::Point center;
            if (argumentCount < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], center, exception);
                if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*center_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
                }
            };
            if (argumentCount > 1 && !JSValueIsUndefined(ctx, arguments[1]))
            {
                self->scale(xFactor, yFactor, center);
            }
            else
            {
                self->scale(xFactor, center);
            }
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Skew(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xSkew"")");
            double xSkew = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""ySkew"")");
            double ySkew = JSValueToNumber(ctx, arguments[2 -1], exception);
            pdg::Point center;
            if (argumentCount < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], center, exception);
                if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
                if (!*center_isPoint)
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
                }
            };
            self->skew(xSkew, ySkew, center);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Transform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, arguments[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, arguments[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception) { return JSValueMakeNull(ctx); }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception) { return JSValueMakeNull(ctx); }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception) { return JSValueMakeNull(ctx); }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!arguments[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(arguments[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element)) { return JSValueMakeNull(ctx); }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->transform(matrix);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_SetTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, arguments[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, arguments[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception) { return JSValueMakeNull(ctx); }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception) { return JSValueMakeNull(ctx); }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception) { return JSValueMakeNull(ctx); }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", arguments[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!arguments[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(arguments[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element)) { return JSValueMakeNull(ctx); }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->setTransform(matrix);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_SetBlendMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""blendMode"")");
            double blendMode = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->blendMode(static_cast<BlendMode>(blendMode));
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_TextSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""size"")");
            double size = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->textSize(size);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_TextStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""style"")");
            double style = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->textStyle(static_cast<uint32>(style));
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
#ifndef PDG_NO_GUI
    JSValueRef Attributes_SetFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            Font* font = 0;
            if (argumentCount >= 1)
            {
                if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Font_class()))
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Font"" (""font"")");
                }
                else
                {
                    JSObjectRef font_ = JSValueToObject(ctx, arguments[1 -1], exception);
                    font = Font_getCppObject(font_);
                }
            };
            self->font(font);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
#endif
    JSValueRef Attributes_Frame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""frame"")");
            double frame = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->frame(frame);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_SetFitType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""fit"")");
            double fit = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->fitType(static_cast<FitType>(fit));
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_ClipOverflow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""clip"")");
            bool clip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->clipOverflow(clip);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Subsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Rect section;
            auto section_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], section, exception);
            if (!section_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*section_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->subsection(section);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_SphereRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""rotation"")");
            double rotation = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->sphereRotation(rotation);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_PolarOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->polarOffset(offset);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_LightOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->lightOffset(offset);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_AmbientLight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Color color;
            auto color_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], color, exception);
            if (!color_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*color_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
            };
            self->ambientLight(color);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_Texture(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Image* texture = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef texture_ = JSValueToObject(ctx, arguments[1 -1], exception);
                texture = Image_getCppObject(texture_);
            }
            if (!texture)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""texture"")");
            self->texture(texture);
            return thisObject;
        }
        catch (const std::exception& error)
        {
            {
                JSStringRef errorMessage = JSStringCreateWithUTF8CString(error.what());
                JSValueRef errorValue = JSValueMakeString(ctx, errorMessage);
                JSStringRelease(errorMessage);
                *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr);
                return JSValueMakeNull(ctx);
            };
        }
    }
    JSValueRef Attributes_GetTextSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float size = self->getTextSize();
        return JSValueMakeNumber(ctx, size);
    }
    JSValueRef Attributes_GetTextStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 style = self->getTextStyle();
        return JSValueMakeNumber(ctx, style);
    }
#ifndef PDG_NO_GUI
    JSValueRef Attributes_GetFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Font* font = self->getFont();
        if (!font) return JSValueMakeNull(ctx);
        if (!font->mFontScriptObj)
        {
            return Font_newFromCpp(ctx, font);
        }
        else
        {
            return font->mFontScriptObj;
        };
    }
#endif
    JSValueRef Attributes_GetFrame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int frame = self->getFrame();
        return JSValueMakeNumber(ctx, frame);
    }
    JSValueRef Attributes_GetFitType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        FitType fit = self->getFitType();
        return JSValueMakeNumber(ctx, static_cast<int>(fit));
    }
    JSValueRef Attributes_GetClipOverflow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool clip = self->getClipOverflow();
        return JSValueMakeBoolean(ctx, clip);
    }
    JSValueRef Attributes_GetSubsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Rect section = self->getSubsection();
        return JSC_RectToValue(ctx, section, exception);
    }
    JSValueRef Attributes_GetSphereRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float rotation = self->getSphereRotation();
        return JSValueMakeNumber(ctx, rotation);
    }
    JSValueRef Attributes_GetPolarOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Offset offset = const_cast<Offset&>(self->getPolarOffset());
        return JSC_OffsetToValue(ctx, offset, exception);
    }
    JSValueRef Attributes_GetLightOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Offset offset = const_cast<Offset&>(self->getLightOffset());
        return JSC_OffsetToValue(ctx, offset, exception);
    }
    JSValueRef Attributes_GetAmbientLight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getAmbientLight());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef Attributes_GetTexture(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Attributes* self = static_cast<Attributes*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Image* texture = self->getTexture();
        if (!texture) return JSValueMakeNull(ctx);
        if (!texture->mImageScriptObj)
        {
            return Image_newFromCpp(ctx, texture);
        }
        else
        {
            return texture->mImageScriptObj;
        };
    }

    Attributes* ExtractAttributes(JSValueRef value)
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSContextRef ctx = gMainContext;
        if (JSValueIsObjectOfClass(ctx, value, AnimatedAttributesBase_class()))
            return static_cast<Attributes*>(AnimatedAttributesBase_getCppObject(JSValueToObject(ctx,value,nullptr)));
        if (JSValueIsObjectOfClass(ctx, value, Attributes_class()))
            return Attributes_getCppObject(JSValueToObject(ctx,value,nullptr));
#else
        auto* wrapper = v8script::safe_unwrap_object_wrap_or_prototype(v8::Isolate::GetCurrent(),value);
        if (auto* animated = dynamic_cast<AnimatedAttributesBaseWrap*>(wrapper))
            return static_cast<Attributes*>(animated->getCppObject());
        if (auto* attributes = dynamic_cast<AttributesWrap*>(wrapper))
            return attributes->getCppObject();
#endif
        return nullptr;
    }

}
