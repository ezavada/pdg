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

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void AnimatedAttributesBase_finalize(JSObjectRef object)
    {
        delete static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(object));
        JSObjectSetPrivate(object, nullptr);
    }
#endif
    JSObjectRef AnimatedAttributesBase_newFromCpp(JSContextRef ctx, AnimatedAttributesBase* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, AnimatedAttributesBase_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, AnimatedAttributesBase_class());
        cppObj->mAnimatedScriptObj = obj;
        return obj;
    }

    JSObjectRef AnimatedAttributesBase_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* cppObj = New_AnimatedAttributesBase(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "AnimatedAttributesBase" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, AnimatedAttributesBase_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, AnimatedAttributesBase_class());
        cppObj->mAnimatedScriptObj = obj;
        return obj;
    }

    JSClassRef AnimatedAttributesBase_class()
    {

        static JSStaticValue AnimatedAttributesBase_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction AnimatedAttributesBase_staticFunctions[] =
        {
            { "getBoundingBox", AnimatedAttributesBase_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", AnimatedAttributesBase_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", AnimatedAttributesBase_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", AnimatedAttributesBase_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", AnimatedAttributesBase_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", AnimatedAttributesBase_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", AnimatedAttributesBase_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", AnimatedAttributesBase_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", AnimatedAttributesBase_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", AnimatedAttributesBase_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", AnimatedAttributesBase_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", AnimatedAttributesBase_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", AnimatedAttributesBase_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", AnimatedAttributesBase_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", AnimatedAttributesBase_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", AnimatedAttributesBase_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", AnimatedAttributesBase_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", AnimatedAttributesBase_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", AnimatedAttributesBase_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", AnimatedAttributesBase_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", AnimatedAttributesBase_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", AnimatedAttributesBase_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", AnimatedAttributesBase_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", AnimatedAttributesBase_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", AnimatedAttributesBase_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", AnimatedAttributesBase_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", AnimatedAttributesBase_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", AnimatedAttributesBase_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", AnimatedAttributesBase_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", AnimatedAttributesBase_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", AnimatedAttributesBase_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", AnimatedAttributesBase_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", AnimatedAttributesBase_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", AnimatedAttributesBase_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", AnimatedAttributesBase_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", AnimatedAttributesBase_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", AnimatedAttributesBase_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", AnimatedAttributesBase_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", AnimatedAttributesBase_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", AnimatedAttributesBase_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", AnimatedAttributesBase_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", AnimatedAttributesBase_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", AnimatedAttributesBase_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", AnimatedAttributesBase_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", AnimatedAttributesBase_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", AnimatedAttributesBase_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", AnimatedAttributesBase_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", AnimatedAttributesBase_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", AnimatedAttributesBase_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", AnimatedAttributesBase_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", AnimatedAttributesBase_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", AnimatedAttributesBase_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", AnimatedAttributesBase_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", AnimatedAttributesBase_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", AnimatedAttributesBase_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", AnimatedAttributesBase_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", AnimatedAttributesBase_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", AnimatedAttributesBase_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", AnimatedAttributesBase_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", AnimatedAttributesBase_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", AnimatedAttributesBase_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", AnimatedAttributesBase_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", AnimatedAttributesBase_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "withAppearance", AnimatedAttributesBase_WithAppearance, kJSPropertyAttributeDontDelete },

            { "lineColor", AnimatedAttributesBase_LineColor, kJSPropertyAttributeDontDelete },

            { "lineThickness", AnimatedAttributesBase_LineThickness, kJSPropertyAttributeDontDelete },

            { "lineOpacity", AnimatedAttributesBase_LineOpacity, kJSPropertyAttributeDontDelete },

            { "lineStyle", AnimatedAttributesBase_SetLineStyle, kJSPropertyAttributeDontDelete },

            { "fillColor", AnimatedAttributesBase_FillColor, kJSPropertyAttributeDontDelete },

            { "fillOpacity", AnimatedAttributesBase_FillOpacity, kJSPropertyAttributeDontDelete },

            { "fillGradient", AnimatedAttributesBase_FillGradient, kJSPropertyAttributeDontDelete },

            { "fillRadialGradient", AnimatedAttributesBase_FillRadialGradient, kJSPropertyAttributeDontDelete },

            { "roundedCorners", AnimatedAttributesBase_RoundedCorners, kJSPropertyAttributeDontDelete },

            { "translation", AnimatedAttributesBase_Translation, kJSPropertyAttributeDontDelete },

            { "rotation", AnimatedAttributesBase_Rotation, kJSPropertyAttributeDontDelete },

            { "scale", AnimatedAttributesBase_Scale, kJSPropertyAttributeDontDelete },

            { "skew", AnimatedAttributesBase_Skew, kJSPropertyAttributeDontDelete },

            { "transform", AnimatedAttributesBase_Transform, kJSPropertyAttributeDontDelete },

            { "setTransform", AnimatedAttributesBase_SetTransform, kJSPropertyAttributeDontDelete },

            { "blendMode", AnimatedAttributesBase_SetBlendMode, kJSPropertyAttributeDontDelete },

            { "textSize", AnimatedAttributesBase_TextSize, kJSPropertyAttributeDontDelete },

            { "textStyle", AnimatedAttributesBase_TextStyle, kJSPropertyAttributeDontDelete },

#ifndef PDG_NO_GUI

            { "font", AnimatedAttributesBase_SetFont, kJSPropertyAttributeDontDelete },
#endif

            { "frame", AnimatedAttributesBase_Frame, kJSPropertyAttributeDontDelete },

            { "fitType", AnimatedAttributesBase_SetFitType, kJSPropertyAttributeDontDelete },

            { "clipOverflow", AnimatedAttributesBase_ClipOverflow, kJSPropertyAttributeDontDelete },

            { "subsection", AnimatedAttributesBase_Subsection, kJSPropertyAttributeDontDelete },

            { "sphereRotation", AnimatedAttributesBase_SphereRotation, kJSPropertyAttributeDontDelete },

            { "polarOffset", AnimatedAttributesBase_PolarOffset, kJSPropertyAttributeDontDelete },

            { "lightOffset", AnimatedAttributesBase_LightOffset, kJSPropertyAttributeDontDelete },

            { "ambientLight", AnimatedAttributesBase_AmbientLight, kJSPropertyAttributeDontDelete },

            { "texture", AnimatedAttributesBase_Texture, kJSPropertyAttributeDontDelete },

            { "getLineColor", AnimatedAttributesBase_GetLineColor, kJSPropertyAttributeDontDelete },

            { "getLineThickness", AnimatedAttributesBase_GetLineThickness, kJSPropertyAttributeDontDelete },

            { "getLineOpacity", AnimatedAttributesBase_GetLineOpacity, kJSPropertyAttributeDontDelete },

            { "getLineStyle", AnimatedAttributesBase_GetLineStyle, kJSPropertyAttributeDontDelete },

            { "getFillColor", AnimatedAttributesBase_GetFillColor, kJSPropertyAttributeDontDelete },

            { "getFillOpacity", AnimatedAttributesBase_GetFillOpacity, kJSPropertyAttributeDontDelete },

            { "getRoundedCornerRadius", AnimatedAttributesBase_GetRoundedCornerRadius, kJSPropertyAttributeDontDelete },

            { "getGradientType", AnimatedAttributesBase_GetGradientType, kJSPropertyAttributeDontDelete },

            { "getGradientStart", AnimatedAttributesBase_GetGradientStart, kJSPropertyAttributeDontDelete },

            { "getGradientEnd", AnimatedAttributesBase_GetGradientEnd, kJSPropertyAttributeDontDelete },

            { "getGradientStartColor", AnimatedAttributesBase_GetGradientStartColor, kJSPropertyAttributeDontDelete },

            { "getGradientEndColor", AnimatedAttributesBase_GetGradientEndColor, kJSPropertyAttributeDontDelete },

            { "getRadialGradientCenter", AnimatedAttributesBase_GetRadialGradientCenter, kJSPropertyAttributeDontDelete },

            { "getRadialGradientRadius", AnimatedAttributesBase_GetRadialGradientRadius, kJSPropertyAttributeDontDelete },

            { "getRadialGradientCenterColor", AnimatedAttributesBase_GetRadialGradientCenterColor, kJSPropertyAttributeDontDelete },

            { "getRadialGradientEndColor", AnimatedAttributesBase_GetRadialGradientEndColor, kJSPropertyAttributeDontDelete },

            { "getTransform", AnimatedAttributesBase_GetTransform, kJSPropertyAttributeDontDelete },

            { "getBlendMode", AnimatedAttributesBase_GetBlendMode, kJSPropertyAttributeDontDelete },

            { "getTextSize", AnimatedAttributesBase_GetTextSize, kJSPropertyAttributeDontDelete },

            { "getTextStyle", AnimatedAttributesBase_GetTextStyle, kJSPropertyAttributeDontDelete },

#ifndef PDG_NO_GUI

            { "getFont", AnimatedAttributesBase_GetFont, kJSPropertyAttributeDontDelete },
#endif

            { "getFrame", AnimatedAttributesBase_GetFrame, kJSPropertyAttributeDontDelete },

            { "getFitType", AnimatedAttributesBase_GetFitType, kJSPropertyAttributeDontDelete },

            { "getClipOverflow", AnimatedAttributesBase_GetClipOverflow, kJSPropertyAttributeDontDelete },

            { "getSubsection", AnimatedAttributesBase_GetSubsection, kJSPropertyAttributeDontDelete },

            { "getSphereRotation", AnimatedAttributesBase_GetSphereRotation, kJSPropertyAttributeDontDelete },

            { "getPolarOffset", AnimatedAttributesBase_GetPolarOffset, kJSPropertyAttributeDontDelete },

            { "getLightOffset", AnimatedAttributesBase_GetLightOffset, kJSPropertyAttributeDontDelete },

            { "getAmbientLight", AnimatedAttributesBase_GetAmbientLight, kJSPropertyAttributeDontDelete },

            { "getTexture", AnimatedAttributesBase_GetTexture, kJSPropertyAttributeDontDelete },
            { "animate", AnimatedAttributesBase_Animate, kJSPropertyAttributeDontDelete },
            { "_setDrawingLayout", AnimatedAttributesBase_SetDrawingLayout, kJSPropertyAttributeDontDelete },
            { "changeLineColor", AnimatedAttributesBase_ChangeLineColor, kJSPropertyAttributeDontDelete },
            { "changeLineThickness", AnimatedAttributesBase_ChangeLineThickness, kJSPropertyAttributeDontDelete },
            { "changeLineOpacity", AnimatedAttributesBase_ChangeLineOpacity, kJSPropertyAttributeDontDelete },
            { "changeFillColor", AnimatedAttributesBase_ChangeFillColor, kJSPropertyAttributeDontDelete },
            { "changeFillOpacity", AnimatedAttributesBase_ChangeFillOpacity, kJSPropertyAttributeDontDelete },
            { "changeRoundedCorners", AnimatedAttributesBase_ChangeRoundedCorners, kJSPropertyAttributeDontDelete },
            { "changeTextSize", AnimatedAttributesBase_ChangeTextSize, kJSPropertyAttributeDontDelete },
            { "changeSubsection", AnimatedAttributesBase_ChangeSubsection, kJSPropertyAttributeDontDelete },
            { "changePolarOffset", AnimatedAttributesBase_ChangePolarOffset, kJSPropertyAttributeDontDelete },
            { "changeLightOffset", AnimatedAttributesBase_ChangeLightOffset, kJSPropertyAttributeDontDelete },
            { "changeAmbientLight", AnimatedAttributesBase_ChangeAmbientLight, kJSPropertyAttributeDontDelete },
            { "changeFillGradient", AnimatedAttributesBase_ChangeFillGradient, kJSPropertyAttributeDontDelete },
            { "changeFillRadialGradient", AnimatedAttributesBase_ChangeFillRadialGradient, kJSPropertyAttributeDontDelete },
            { "changeSphereRotation", AnimatedAttributesBase_ChangeSphereRotation, kJSPropertyAttributeDontDelete },
            { "changeFrames", AnimatedAttributesBase_ChangeFrames, kJSPropertyAttributeDontDelete },
            { "changeSkew", AnimatedAttributesBase_ChangeSkew, kJSPropertyAttributeDontDelete },
            { "changeTransform", AnimatedAttributesBase_ChangeTransform, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.parentClass = AnimatedBase_class();
            definition.finalize = AnimatedAttributesBase_finalize;
            definition.className = "AnimatedAttributes";
            definition.staticFunctions = AnimatedAttributesBase_staticFunctions;
            definition.staticValues = AnimatedAttributesBase_staticValues;
            definition.callAsConstructor = AnimatedAttributesBase_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    AnimatedAttributesBase* New_AnimatedAttributesBase(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (argumentCount > 1)
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Type Error: " << "AnimatedAttributes accepts optional Attributes";
            s_HaveSavedError = true; return nullptr;
        }
        Attributes* initial = nullptr;
        if (argumentCount == 1 && !JSValueIsNull(ctx, arguments[0]) && !JSValueIsUndefined(ctx, arguments[0]))
        {
            initial = ExtractAttributes(arguments[0]);
            if (!initial)
            {
                s_SavedError.str(""); s_SavedError.clear();
                s_SavedError << "Type Error: " << "Expected Attributes or AnimatedAttributes";
                s_HaveSavedError = true; return nullptr;
            }
        }
        AnimatedAttributesBase* result;
        try { result = initial ? new AnimatedAttributesBase(*initial) : new AnimatedAttributesBase(); }
        catch (const std::exception& error)
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Range Error: " << error.what();
            s_HaveSavedError = true; return nullptr;
        }
#ifndef PDG_USING_JAVASCRIPT_CORE
        result->mAnimatedScriptObj.Reset(isolate, thisObject);
        result->mAnimatedScriptObj.SetWeak();
#endif
        return result;
    }

    JSValueRef AnimatedAttributesBase_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Rect theBoundingBox = self->getBoundingBox();
        return JSC_RectToValue(ctx, theBoundingBox, exception);
    }
    JSValueRef AnimatedAttributesBase_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::RotatedRect theRotatedBounds = self->getRotatedBounds();
        return JSC_RectToValue(ctx, theRotatedBounds, exception);
    }
    JSValueRef AnimatedAttributesBase_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Point theLocation = self->getLocation();
        return JSC_PointToValue(ctx, theLocation, exception);
    }
    JSValueRef AnimatedAttributesBase_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theMovement = self->getMovement();
        return JSC_OffsetToValue(ctx, theMovement, exception);
    }
    JSValueRef AnimatedAttributesBase_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theSize = self->getSize();
        return JSC_OffsetToValue(ctx, theSize, exception);
    }
    JSValueRef AnimatedAttributesBase_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theWidth = self->getWidth();
        return JSValueMakeNumber(ctx, theWidth);
    }
    JSValueRef AnimatedAttributesBase_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theHeight = self->getHeight();
        return JSValueMakeNumber(ctx, theHeight);
    }
    JSValueRef AnimatedAttributesBase_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theScale = self->getScale();
        return JSC_OffsetToValue(ctx, theScale, exception);
    }
    JSValueRef AnimatedAttributesBase_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theStretching = self->getStretching();
        return JSC_OffsetToValue(ctx, theStretching, exception);
    }
    JSValueRef AnimatedAttributesBase_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theRotation = self->getRotation();
        return JSValueMakeNumber(ctx, theRotation);
    }
    JSValueRef AnimatedAttributesBase_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Offset theCenterOffset = self->getCenterOffset();
        return JSC_OffsetToValue(ctx, theCenterOffset, exception);
    }
    JSValueRef AnimatedAttributesBase_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theSpin = self->getSpin();
        return JSValueMakeNumber(ctx, theSpin);
    }
    JSValueRef AnimatedAttributesBase_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setLocation(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setLocation(x, y); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point value;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], value, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount == 1) { self->moveTo(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveTo(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount == 1) { self->moveBy(value); return thisObject; }
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount == 2) { self->moveBy(x, y); return thisObject; }
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setMovement(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setMovement(xPerSecond, yPerSecond); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Vector value;
            auto converted = JSC_ValueIsVector(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""xPerSecond"")");
                double xPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""yPerSecond"")");
                double yPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->setSize(value); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
                double width = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
                double height = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                self->setSize(width, height); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Offset value;
            auto converted = JSC_ValueIsOffset(ctx, arguments[0], value, exception);
            if (!converted.has_value()) { return JSValueMakeNull(ctx); }
            if (*converted)
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
                double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
            else
            {
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
                double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
                if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
                double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
            }
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
    JSValueRef AnimatedAttributesBase_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setWidth(value); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setHeight(value); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setRotation(value); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setSpin(value); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->setGrowing(value); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            self->setStretching(widthPerSecond, heightPerSecond); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = (argumentCount<2) ? x : JSValueToNumber(ctx, arguments[2 -1], exception);
            self->setScale(x, y); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radiansPerSecond"")");
            double radiansPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""amountPerSecond"")");
            double amountPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthPerSecond"")");
            double widthPerSecond = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightPerSecond"")");
            double heightPerSecond = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::linearTween) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->grow(factor); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->grow(factor, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""widthFactor"")");
            double widthFactor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""heightFactor"")");
            double heightFactor = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->stretch(widthFactor, heightFactor); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaWidth"")");
            double deltaWidth = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""deltaHeight"")");
            double deltaHeight = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount == 2) { self->resizeBy(deltaWidth, deltaHeight); return thisObject; }
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
            double width = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
            double height = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[3 -1], exception);
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
            double easingValue = (argumentCount<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); return thisObject;
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
    JSValueRef AnimatedAttributesBase_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateBy(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
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
    JSValueRef AnimatedAttributesBase_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount == 1) { self->rotateTo(radians); return thisObject; }
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
            double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int direction = static_cast<int>(directionValue);
            self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->setCenterOffset(offset); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipX(flip); return thisObject;
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
    JSValueRef AnimatedAttributesBase_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""flip"")");
            bool flip = JSValueToBoolean(ctx, arguments[1 -1]);
            self->setFlipY(flip); return thisObject;
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
    JSValueRef AnimatedAttributesBase_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopMovement(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopSpinning(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopGrowing(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopStretching(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->pauseSchedule(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->resumeSchedule(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->cancelSchedule(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipX(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->flipY(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->andThen(); return thisObject;
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
    JSValueRef AnimatedAttributesBase_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isFlippedX());
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
    JSValueRef AnimatedAttributesBase_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isFlippedY());
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
    JSValueRef AnimatedAttributesBase_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->isSchedulePaused());
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
    JSValueRef AnimatedAttributesBase_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            return JSValueMakeBoolean(ctx, self->hasScheduledAnimations());
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
    JSValueRef AnimatedAttributesBase_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""durationSeconds"")");
            double durationSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            self->wait(durationSeconds); return thisObject;
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
    JSValueRef AnimatedAttributesBase_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            self->mAnimatedScriptObj = thisObject;
            SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IAnimationHelper" " object:") );
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IAnimationHelper_class()))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IAnimationHelper"" (""helper"")");
            self->addAnimationHelper(helper);
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
    JSValueRef AnimatedAttributesBase_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            IAnimationHelper* helper = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef helper_ = JSValueToObject(ctx, arguments[1 -1], exception);
                helper = IAnimationHelper_getCppObject(helper_);
            }
            if (!helper)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""IAnimationHelper"" (""helper"")");
            self->removeAnimationHelper(helper);
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
    JSValueRef AnimatedAttributesBase_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->clearAnimationHelpers();
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

    JSValueRef AnimatedAttributesBase_WithAppearance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_GetLineColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getLineColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetLineThickness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float thickness = self->getLineThickness();
        return JSValueMakeNumber(ctx, thickness);
    }
    JSValueRef AnimatedAttributesBase_GetLineOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float opacity = self->getLineOpacity();
        return JSValueMakeNumber(ctx, opacity);
    }
    JSValueRef AnimatedAttributesBase_GetLineStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        LineStyle style = self->getLineStyle();
        return JSValueMakeNumber(ctx, style);
    }
    JSValueRef AnimatedAttributesBase_GetFillColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getFillColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetFillOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float opacity = self->getFillOpacity();
        return JSValueMakeNumber(ctx, opacity);
    }
    JSValueRef AnimatedAttributesBase_GetRoundedCornerRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float radius = self->getRoundedCornerRadius();
        return JSValueMakeNumber(ctx, radius);
    }
    JSValueRef AnimatedAttributesBase_GetGradientType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        GradientType type = self->getGradientType();
        return JSValueMakeNumber(ctx, type);
    }
    JSValueRef AnimatedAttributesBase_GetGradientStart(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point start = const_cast<Point&>(self->getGradientStart());
        return JSC_PointToValue(ctx, start, exception);
    }
    JSValueRef AnimatedAttributesBase_GetGradientEnd(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point end = const_cast<Point&>(self->getGradientEnd());
        return JSC_PointToValue(ctx, end, exception);
    }
    JSValueRef AnimatedAttributesBase_GetGradientStartColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getGradientStartColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetGradientEndColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getGradientEndColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetRadialGradientCenter(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point center = const_cast<Point&>(self->getRadialGradientCenter());
        return JSC_PointToValue(ctx, center, exception);
    }
    JSValueRef AnimatedAttributesBase_GetRadialGradientRadius(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float radius = self->getRadialGradientRadius();
        return JSValueMakeNumber(ctx, radius);
    }
    JSValueRef AnimatedAttributesBase_GetRadialGradientCenterColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getRadialGradientCenterColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetRadialGradientEndColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getRadialGradientEndColor());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_GetBlendMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        BlendMode blendMode = self->getBlendMode();
        return JSValueMakeNumber(ctx, static_cast<int>(blendMode));
    }
    JSValueRef AnimatedAttributesBase_LineColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_LineThickness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_LineOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SetLineStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_FillColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_FillOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_FillGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_FillRadialGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_RoundedCorners(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Translation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Rotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Scale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Skew(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Transform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SetTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SetBlendMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_TextSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_TextStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SetFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Frame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SetFitType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_ClipOverflow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Subsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_SphereRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_PolarOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_LightOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_AmbientLight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_Texture(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_GetTextSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float size = self->getTextSize();
        return JSValueMakeNumber(ctx, size);
    }
    JSValueRef AnimatedAttributesBase_GetTextStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 style = self->getTextStyle();
        return JSValueMakeNumber(ctx, style);
    }
#ifndef PDG_NO_GUI
    JSValueRef AnimatedAttributesBase_GetFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedAttributesBase_GetFrame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int frame = self->getFrame();
        return JSValueMakeNumber(ctx, frame);
    }
    JSValueRef AnimatedAttributesBase_GetFitType(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        FitType fit = self->getFitType();
        return JSValueMakeNumber(ctx, static_cast<int>(fit));
    }
    JSValueRef AnimatedAttributesBase_GetClipOverflow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool clip = self->getClipOverflow();
        return JSValueMakeBoolean(ctx, clip);
    }
    JSValueRef AnimatedAttributesBase_GetSubsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Rect section = self->getSubsection();
        return JSC_RectToValue(ctx, section, exception);
    }
    JSValueRef AnimatedAttributesBase_GetSphereRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float rotation = self->getSphereRotation();
        return JSValueMakeNumber(ctx, rotation);
    }
    JSValueRef AnimatedAttributesBase_GetPolarOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Offset offset = const_cast<Offset&>(self->getPolarOffset());
        return JSC_OffsetToValue(ctx, offset, exception);
    }
    JSValueRef AnimatedAttributesBase_GetLightOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Offset offset = const_cast<Offset&>(self->getLightOffset());
        return JSC_OffsetToValue(ctx, offset, exception);
    }
    JSValueRef AnimatedAttributesBase_GetAmbientLight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Color color = const_cast<Color&>(self->getAmbientLight());
        return JSC_ColorToValue(ctx, color, exception);
    }
    JSValueRef AnimatedAttributesBase_GetTexture(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef AnimatedAttributesBase_SetDrawingLayout(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enabled"")");
        bool enabled = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setDrawingLayout(enabled);
        return JSValueMakeUndefined(ctx);
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
    JSValueRef AnimatedAttributesBase_Animate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaSeconds"")");
        double deltaSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        try { return JSValueMakeBoolean(ctx, self->animate(deltaSeconds)); }
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

    JSValueRef AnimatedAttributesBase_ChangeLineColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Color target;
        auto target_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], target, exception);
        if (!target_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeLineColor(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeLineThickness(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""target"")");
        double target = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeLineThickness(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeLineOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""target"")");
        double target = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeLineOpacity(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeFillColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Color target;
        auto target_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], target, exception);
        if (!target_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeFillColor(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeFillOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""target"")");
        double target = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeFillOpacity(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeRoundedCorners(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""target"")");
        double target = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeRoundedCorners(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeTextSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""target"")");
        double target = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeTextSize(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeSubsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Rect target;
        auto target_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], target, exception);
        if (!target_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeSubsection(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangePolarOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Offset target;
        auto target_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], target, exception);
        if (!target_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changePolarOffset(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeLightOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Offset target;
        auto target_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], target, exception);
        if (!target_isOffset.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isOffset)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeLightOffset(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeAmbientLight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        pdg::Color target;
        auto target_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], target, exception);
        if (!target_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*target_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeAmbientLight(target, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeFillGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 5)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5, true);
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
        if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[5 -1], exception);
        if (argumentCount >= 6 && !JSValueIsNumber(ctx, arguments[6 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""easingValue"")");
        double easingValue = (argumentCount<6) ? 0 : JSValueToNumber(ctx, arguments[6 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeFillGradient(start, startColor, end, endColor, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeFillRadialGradient(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 5)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5, true);
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
        if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[5 -1], exception);
        if (argumentCount >= 6 && !JSValueIsNumber(ctx, arguments[6 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""easingValue"")");
        double easingValue = (argumentCount<6) ? 0 : JSValueToNumber(ctx, arguments[6 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeFillRadialGradient(center, centerColor, radius, endColor, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeSphereRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
        double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""directionValue"")");
        double directionValue = (argumentCount<4) ? static_cast<int>(rotationDirection_AsSpecified) : JSValueToNumber(ctx, arguments[4 -1], exception);
        if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue ||
            directionValue < std::numeric_limits<int>::min() || directionValue > std::numeric_limits<int>::max())
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer rotation direction" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int direction = static_cast<int>(directionValue);
        try { self->changeSphereRotation(radians, seconds, gEasingFunctions[easing], direction); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeFrames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""firstValue"")");
        double firstValue = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!std::isfinite(firstValue) || std::floor(firstValue) != firstValue ||
            firstValue < std::numeric_limits<int>::min() || firstValue > std::numeric_limits<int>::max())
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer frame index" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int first = static_cast<int>(firstValue);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""lastValue"")");
        double lastValue = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (!std::isfinite(lastValue) || std::floor(lastValue) != lastValue ||
            lastValue < std::numeric_limits<int>::min() || lastValue > std::numeric_limits<int>::max())
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer frame index" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int last = static_cast<int>(lastValue);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[3 -1], exception);
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
        double easingValue = (argumentCount<4) ? 0 : JSValueToNumber(ctx, arguments[4 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeFrames(first, last, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeSkew(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
        double x = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
        double y = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[3 -1], exception);
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easingValue"")");
        double easingValue = (argumentCount<4) ? 0 : JSValueToNumber(ctx, arguments[4 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeSkew(x, y, seconds, gEasingFunctions[easing]); return thisObject; }
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

    JSValueRef AnimatedAttributesBase_ChangeTransform(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedAttributesBase* self = static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);

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

        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
        double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
        double easingValue = (argumentCount<3) ? 0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        const int easing = static_cast<int>(easingValue);
        if (!gEasingFunctions[easing])
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        }
        try { self->changeTransform(matrix, seconds, gEasingFunctions[easing]); return thisObject; }
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

}
