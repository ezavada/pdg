// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/port.cpp
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

    JSObjectRef Port_newFromCpp(JSContextRef ctx, Port* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Port_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Port_class());
        cppObj->mPortScriptObj = obj;
        return obj;
    }

    JSObjectRef Port_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* cppObj = New_Port(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Port" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Port_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Port_class());
        cppObj->mPortScriptObj = obj;
        return obj;
    }

    JSClassRef Port_class()
    {

        static JSStaticValue Port_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Port_staticFunctions[] =
        {
            { "getCamera", Port_GetCamera, kJSPropertyAttributeDontDelete },
            { "get""CameraAnchor", Port_GetCameraAnchor, kJSPropertyAttributeDontDelete },
            { "set""CameraAnchor", Port_SetCameraAnchor, kJSPropertyAttributeDontDelete },
            { "get""CameraDrawingEnabled", Port_GetCameraDrawingEnabled, kJSPropertyAttributeDontDelete },
            { "set""CameraDrawingEnabled", Port_SetCameraDrawingEnabled, kJSPropertyAttributeDontDelete },
            { "worldToPort", Port_WorldToPort, kJSPropertyAttributeDontDelete },
            { "portToWorld", Port_PortToWorld, kJSPropertyAttributeDontDelete },
            { "get""ClipRect", Port_GetClipRect, kJSPropertyAttributeDontDelete },
            { "set""ClipRect", Port_SetClipRect, kJSPropertyAttributeDontDelete },
            { "resetClipRect", Port_ResetClipRect, kJSPropertyAttributeDontDelete },
            { "clear", Port_Clear, kJSPropertyAttributeDontDelete },
            { "setDrawingOrigin", Port_SetDrawingOrigin, kJSPropertyAttributeDontDelete },
            { "get""Cursor", Port_GetCursor, kJSPropertyAttributeDontDelete },
            { "set""Cursor", Port_SetCursor, kJSPropertyAttributeDontDelete },
            { "get""DrawingArea", Port_GetDrawingArea, kJSPropertyAttributeDontDelete },
            { "drawLine", Port_DrawLine, kJSPropertyAttributeDontDelete },
            { "drawSpline", Port_DrawSpline, kJSPropertyAttributeDontDelete },
            { "drawText", Port_DrawText, kJSPropertyAttributeDontDelete },
            { "drawImage", Port_DrawImage, kJSPropertyAttributeDontDelete },
            { "getTextWidth", Port_GetTextWidth, kJSPropertyAttributeDontDelete },
            { "getCurrentFont", Port_GetCurrentFont, kJSPropertyAttributeDontDelete },
            { "setFont", Port_SetFont, kJSPropertyAttributeDontDelete },
            { "setFontForStyle", Port_SetFontForStyle, kJSPropertyAttributeDontDelete },
            { "setFontScalingFactor", Port_SetFontScalingFactor, kJSPropertyAttributeDontDelete },
            { "startTrackingMouse", Port_StartTrackingMouse, kJSPropertyAttributeDontDelete },
            { "stopTrackingMouse", Port_StopTrackingMouse, kJSPropertyAttributeDontDelete },
            { "resetCursor", Port_ResetCursor, kJSPropertyAttributeDontDelete },
            { "drawRect", Port_DrawRect, kJSPropertyAttributeDontDelete },
            { "drawQuad", Port_DrawQuad, kJSPropertyAttributeDontDelete },
            { "drawPolygon", Port_DrawPolygon, kJSPropertyAttributeDontDelete },
            { "drawEllipse", Port_DrawEllipse, kJSPropertyAttributeDontDelete },
            { "drawArc", Port_DrawArc, kJSPropertyAttributeDontDelete },
            { "drawBezier", Port_DrawBezier, kJSPropertyAttributeDontDelete },
            { "drawCircle", Port_DrawCircle, kJSPropertyAttributeDontDelete },
            { "drawVector", Port_DrawVector, kJSPropertyAttributeDontDelete },
            { "drawRoundedRect", Port_DrawRoundedRect, kJSPropertyAttributeDontDelete },
            { "drawDrawing", Port_DrawDrawing, kJSPropertyAttributeDontDelete },
            { "drawSphere", Port_DrawSphere, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Port";
            definition.staticFunctions = Port_staticFunctions;
            definition.staticValues = Port_staticValues;
            definition.callAsConstructor = Port_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef Port_GetCameraAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Point theCameraAnchor = self->getCameraAnchor();
        return JSC_PointToValue(ctx, theCameraAnchor, exception);
    }
    JSValueRef Port_SetCameraAnchor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Point value;
        auto value_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], value, exception);
        if (!value_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*value_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        self->setCameraAnchor(value); return thisObject;
    }
    JSValueRef Port_GetCameraDrawingEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool theCameraDrawingEnabled = self->getCameraDrawingEnabled();
        return JSValueMakeBoolean(ctx, theCameraDrawingEnabled);
    }
    JSValueRef Port_SetCameraDrawingEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""theCameraDrawingEnabled"")");
        bool theCameraDrawingEnabled = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setCameraDrawingEnabled(theCameraDrawingEnabled);
        return thisObject;
    }
    JSValueRef Port_GetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        auto* camera=self->getCamera(); if (!camera) return JSValueMakeNull(ctx);
        if (!camera->mCameraScriptObj)
        {
            return Camera_newFromCpp(ctx, camera);
        }
        else
        {
            return camera->mCameraScriptObj;
        };
    }
    JSValueRef Port_WorldToPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            auto result=self->worldToPort(point); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Port_PortToWorld(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            auto result=self->portToWorld(point); return JSC_PointToValue(ctx, result, exception);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Port_GetDrawingArea(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Rect theDrawingArea = self->getDrawingArea();
        return JSC_RectToValue(ctx, theDrawingArea, exception);
    }
    JSValueRef Port_GetClipRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Rect theClipRect = self->getClipRect();
        return JSC_RectToValue(ctx, theClipRect, exception);
    }
    JSValueRef Port_SetClipRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect value;
        auto value_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], value, exception);
        if (!value_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*value_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        self->setClipRect(value); return thisObject;
    }
    JSValueRef Port_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        pdg::Color color;
        if (argumentCount < 1)
        {
            color = Color(0, 0, 0, 0);
        }
        else
        {
            auto color_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], color, exception);
            if (!color_isColor.has_value()) { return JSValueMakeNull(ctx); }
            if (!*color_isColor)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
            }
        };
        self->clear(color);
        return thisObject;
    }
    JSValueRef Port_SetDrawingOrigin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Point origin;
        auto origin_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], origin, exception);
        if (!origin_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*origin_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        try { self->setDrawingOrigin(origin); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        return thisObject;
    }
    JSValueRef Port_ResetClipRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->resetClipRect();
        return thisObject;
    }
    JSValueRef Port_DrawLine(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Point from;
        auto from_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], from, exception);
        if (!from_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*from_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        pdg::Point to;
        auto to_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], to, exception);
        if (!to_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*to_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawLine(from, to, *attrs);
        return thisObject;
    }
    JSValueRef Port_DrawSpline(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Spline* spline = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef spline_ = JSValueToObject(ctx, arguments[1 -1], exception);
            spline = Spline_getCppObject(spline_);
        }
        if (!spline)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Spline"" (""spline"")");

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawSpline(*spline, *attrs);
        return thisObject;
    }
    JSValueRef Port_GetTextWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""text"")");
        JSStringRef text_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock text_Mem(JSStringGetMaximumUTF8CStringSize(text_Str));
        JSStringGetUTF8CString(text_Str, text_Mem.ptr, text_Mem.bytes);
        const char* text = (const char*)text_Mem.ptr;
        JSStringRelease(text_Str);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""size"")");
        int32 size = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""style"")");
        unsigned long style = (argumentCount<3) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""len"")");
        long len = (argumentCount<4) ? -1 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        int width = self->getTextWidth(text, size, style, len);
        return JSValueMakeNumber(ctx, width);
    }
    JSValueRef Port_GetCurrentFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""style"")");
        unsigned long style = (argumentCount<1) ? textStyle_Plain : pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
        Font* font = self->getCurrentFont(style);
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
    JSValueRef Port_SetFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
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
        self->setFont(font);
        return thisObject;
    }
    JSValueRef Port_SetFontForStyle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""style"")");
        uint32 style = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
        Font* font = 0;
        if (argumentCount >= 2)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[2 -1], Font_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Font"" (""font"")");
            }
            else
            {
                JSObjectRef font_ = JSValueToObject(ctx, arguments[2 -1], exception);
                font = Font_getCppObject(font_);
            }
        };
        self->setFontForStyle(font, style);
        return thisObject;
    }
    JSValueRef Port_SetFontScalingFactor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""scaleBy"")");
        double scaleBy = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setFontScalingFactor(scaleBy);
        return thisObject;
    }
    JSValueRef Port_StartTrackingMouse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        int trackingRef = self->startTrackingMouse(rect);
        return JSValueMakeNumber(ctx, trackingRef);
    }
    JSValueRef Port_StopTrackingMouse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""trackingRef"")");
        int32 trackingRef = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->stopTrackingMouse(trackingRef);
        return thisObject;
    }
    JSValueRef Port_SetCursor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Image* cursorImage = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef cursorImage_ = JSValueToObject(ctx, arguments[1 -1], exception);
            cursorImage = Image_getCppObject(cursorImage_);
        }
        if (!cursorImage)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""cursorImage"")");
        pdg::Point hotSpot;
        auto hotSpot_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], hotSpot, exception);
        if (!hotSpot_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*hotSpot_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };
        self->setCursor(cursorImage, hotSpot);
        return thisObject;
    }
    JSValueRef Port_GetCursor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Image* cursorImage = self->getCursor();
        if (!cursorImage) return JSValueMakeNull(ctx);
        if (!cursorImage->mImageScriptObj)
        {
            return Image_newFromCpp(ctx, cursorImage);
        }
        else
        {
            return cursorImage->mImageScriptObj;
        };
    }
    JSValueRef Port_ResetCursor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->resetCursor();
        return thisObject;
    }

    JSValueRef Port_DrawRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawRect(rect, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        pdg::Quad quad;
        auto quad_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], quad, exception);
        if (!quad_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*quad_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawQuad(quad, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawPolygon(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Polygon* polygon = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef polygon_ = JSValueToObject(ctx, arguments[1 -1], exception);
            polygon = Polygon_getCppObject(polygon_);
        }
        if (!polygon)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Polygon"" (""polygon"")");

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawPolygon(*polygon, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawEllipse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
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
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""xRadius"")");
        double xRadius = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""yRadius"")");
        double yRadius = JSValueToNumber(ctx, arguments[3 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[4 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawEllipse(center, xRadius, yRadius, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawArc(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 6)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 6);
        pdg::Point center;
        auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
        if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*center_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""xRadius"")");
        double xRadius = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""yRadius"")");
        double yRadius = JSValueToNumber(ctx, arguments[3 -1], exception);
        if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""startAngle"")");
        double startAngle = JSValueToNumber(ctx, arguments[4 -1], exception);
        if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""endAngle"")");
        double endAngle = JSValueToNumber(ctx, arguments[5 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[6 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawBezier(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 5)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5);
        pdg::Point from;
        auto from_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], from, exception);
        if (!from_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*from_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        pdg::Point control1;
        auto control1_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], control1, exception);
        if (!control1_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*control1_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };
        pdg::Point control2;
        auto control2_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], control2, exception);
        if (!control2_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*control2_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
        };
        pdg::Point to;
        auto to_isPoint = JSC_ValueIsPoint(ctx, arguments[4 -1], to, exception);
        if (!to_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*to_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 4, "Point", arguments[4 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[5 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawBezier(from, control1, control2, to, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawCircle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Point center;
        auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
        if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*center_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radius"")");
        double radius = JSValueToNumber(ctx, arguments[2 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawCircle(center, radius, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawVector(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        pdg::Vector vector;
        auto vector_isVector = JSC_ValueIsVector(ctx, arguments[1 -1], vector, exception);
        if (!vector_isVector.has_value()) { return JSValueMakeNull(ctx); }
        if (!*vector_isVector)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Vector", arguments[1 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawVector(vector, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawRoundedRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radius"")");
        double radius = JSValueToNumber(ctx, arguments[2 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawRoundedRect(rect, radius, *attrs);
        return thisObject;
    }

    JSValueRef Port_DrawImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        Image* img = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef img_ = JSValueToObject(ctx, arguments[1 -1], exception);
            img = Image_getCppObject(img_);
        }
        if (!img)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Image"" (""img"")");

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        pdg::Point loc;
        auto isPoint = JSC_ValueIsPoint(ctx, arguments[1], loc, exception);
        if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (*isPoint)
        {
            self->drawImage(img, loc, *attrs);
        }
        else
        {

            pdg::Quad quad;
            auto quad_isQuad = JSC_ValueIsQuad(ctx, arguments[2 -1], quad, exception);
            if (!quad_isQuad.has_value()) { return JSValueMakeNull(ctx); }
            if (!*quad_isQuad)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Quad", arguments[2 -1]);
            };
            self->drawImage(img, quad, *attrs);
        }
        return thisObject;
    }

    JSValueRef Port_DrawDrawing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        Drawing* drawing = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef drawing_ = JSValueToObject(ctx, arguments[1 -1], exception);
            drawing = Drawing_getCppObject(drawing_);
        }
        if (!drawing)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Drawing"" (""drawing"")");

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        pdg::Point loc;
        auto isPoint = JSC_ValueIsPoint(ctx, arguments[1], loc, exception);
        if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (*isPoint)
        {
            self->drawDrawing(*drawing, loc, *attrs);
        }
        else
        {

            pdg::Rect rect;
            auto rect_isRect = JSC_ValueIsRect(ctx, arguments[2 -1], rect, exception);
            if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*rect_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Rect", arguments[2 -1]);
            };
            self->drawDrawing(*drawing, rect, *attrs);
        }
        return thisObject;
    }

    JSValueRef Port_DrawText(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""text"")");
        JSStringRef text_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock text_Mem(JSStringGetMaximumUTF8CStringSize(text_Str));
        JSStringGetUTF8CString(text_Str, text_Mem.ptr, text_Mem.bytes);
        const char* text = (const char*)text_Mem.ptr;
        JSStringRelease(text_Str);

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        pdg::Point loc;
        auto isPoint = JSC_ValueIsPoint(ctx, arguments[1], loc, exception);
        if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (*isPoint)
        {
            self->drawText(text, loc, *attrs);
        }
        else
        {

            pdg::Rect rect;
            auto rect_isRect = JSC_ValueIsRect(ctx, arguments[2 -1], rect, exception);
            if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*rect_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Rect", arguments[2 -1]);
            };
            self->drawText(text, rect, *attrs);
        }
        return thisObject;
    }

    JSValueRef Port_DrawSphere(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Port* self = static_cast<Port*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Point center;
        auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
        if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*center_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radius"")");
        double radius = JSValueToNumber(ctx, arguments[2 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->drawSphere(center, radius, *attrs);
        return thisObject;
    }

    void CleanupPortScriptObject(JSObjectRef obj) { }

    Port* New_Port(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        s_SavedError.str(""); s_SavedError.clear();
        s_SavedError << "Port cannot be created directly, use pdg.gfx.createWindowPort() or pdg.gfx.createFullScreenPort()";
        s_HaveSavedError = true;
        return 0;
    }
#endif

}
