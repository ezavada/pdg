// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/graphics_manager.cpp
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

    static bool s_GraphicsManager_InNewFromCpp = false;

    JSObjectRef GraphicsManager_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {

        if (!s_GraphicsManager_InNewFromCpp)
        {
            std::ostringstream excpt_;
            excpt_ << "throw TypeError('" "GraphicsManager" " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." "gfx" "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        }

        GraphicsManager* cppObj = New_GraphicsManager(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to get singleton C++ native " "GraphicsManager" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, GraphicsManager_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, GraphicsManager_class());
        return obj;
    }

    JSObjectRef GraphicsManager_getScriptSingletonInstance()
    {
        static JSObjectRef instance = 0;
        if (!instance)
        {

            s_GraphicsManager_InNewFromCpp = true;
            instance = GraphicsManager_new(gMainContext, 0, 0, NULL, NULL);
            s_GraphicsManager_InNewFromCpp = false;
            JSValueProtect(gMainContext, instance);
        }
        return instance;
    }

    GraphicsManager* GraphicsManager_getSingletonInstance()
    {
        JSObjectRef obj = GraphicsManager_getScriptSingletonInstance();
        return static_cast<GraphicsManager*>(JSObjectGetPrivate(obj));
    }

    JSClassRef GraphicsManager_class()
    {
        static JSStaticValue GraphicsManager_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction GraphicsManager_staticFunctions[] =
        {
            { "get""NumScreens", GraphicsManager_GetNumScreens, kJSPropertyAttributeDontDelete },
            { "get""FPS", GraphicsManager_GetFPS, kJSPropertyAttributeDontDelete },
            { "get""TargetFPS", GraphicsManager_GetTargetFPS, kJSPropertyAttributeDontDelete },
            { "set""TargetFPS", GraphicsManager_SetTargetFPS, kJSPropertyAttributeDontDelete },
            { "get""Mouse", GraphicsManager_GetMouse, kJSPropertyAttributeDontDelete },
            { "getCurrentScreenMode", GraphicsManager_GetCurrentScreenMode, kJSPropertyAttributeDontDelete },
            { "getScreenBounds", GraphicsManager_GetScreenBounds, kJSPropertyAttributeDontDelete },
            { "getNumSupportedScreenModes", GraphicsManager_GetNumSupportedScreenModes, kJSPropertyAttributeDontDelete },
            { "getNthSupportedScreenMode", GraphicsManager_GetNthSupportedScreenMode, kJSPropertyAttributeDontDelete },
            { "setScreenMode", GraphicsManager_SetScreenMode, kJSPropertyAttributeDontDelete },
            { "createWindowPort", GraphicsManager_CreateWindowPort, kJSPropertyAttributeDontDelete },
            { "createOffscreenPort", GraphicsManager_CreateOffscreenPort, kJSPropertyAttributeDontDelete },
            { "_createImageFromOffscreenPort", GraphicsManager_CreateImageFromOffscreenPort, kJSPropertyAttributeDontDelete },
            { "createFullScreenPort", GraphicsManager_CreateFullScreenPort, kJSPropertyAttributeDontDelete },
            { "closeGraphicsPort", GraphicsManager_CloseGraphicsPort, kJSPropertyAttributeDontDelete },
            { "closeAllGraphicsPorts", GraphicsManager_CloseAllGraphicsPorts, kJSPropertyAttributeDontDelete },
            { "createFont", GraphicsManager_CreateFont, kJSPropertyAttributeDontDelete },
            { "getMainPort", GraphicsManager_GetMainPort, kJSPropertyAttributeDontDelete },
            { "switchToFullScreenMode", GraphicsManager_SwitchToFullScreenMode, kJSPropertyAttributeDontDelete },
            { "switchToWindowMode", GraphicsManager_SwitchToWindowMode, kJSPropertyAttributeDontDelete },
            { "inFullScreenMode", GraphicsManager_InFullScreenMode, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "GraphicsManager";
            definition.staticFunctions = GraphicsManager_staticFunctions;
            definition.staticValues = GraphicsManager_staticValues;
            definition.callAsConstructor = GraphicsManager_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    JSValueRef GraphicsManager_GetNumScreens(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theNumScreens = self->getNumScreens();
        return JSValueMakeNumber(ctx, theNumScreens);
    }
    JSValueRef GraphicsManager_GetFPS(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theFPS = self->getFPS();
        return JSValueMakeNumber(ctx, theFPS);
    }
    JSValueRef GraphicsManager_GetTargetFPS(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theTargetFPS = self->getTargetFPS();
        return JSValueMakeNumber(ctx, theTargetFPS);
    }
    JSValueRef GraphicsManager_SetTargetFPS(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theTargetFPS"")");
        double theTargetFPS = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setTargetFPS(theTargetFPS);
        return thisObject;
    }
    JSValueRef GraphicsManager_GetMouse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""mouseNumber"")");
        long mouseNumber = (argumentCount<1) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        pdg::Point theMouse = self->getMouse(mouseNumber);
        return JSC_PointToValue(ctx, theMouse, exception);
    }

    JSValueRef GraphicsManager_GetNumSupportedScreenModes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        if (argumentCount < 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""screenNum"")");
        long screenNum = (argumentCount<1) ? screenNum_PrimaryScreen : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        int32 theNumSupportedScreenModes = self->getNumSupportedScreenModes(screenNum);
        return JSValueMakeNumber(ctx, theNumSupportedScreenModes);
    }

    JSValueRef GraphicsManager_SetScreenMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));;

        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""width"")");
        int32 width = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""height"")");
        int32 height = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""screenNum"")");
        long screenNum = (argumentCount<3) ? screenNum_PrimaryScreen : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""bpp"")");
        long bpp = (argumentCount<4) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        self->setScreenMode(width, height, screenNum, bpp);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef GraphicsManager_CreateWindowPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

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
        if (argumentCount >= 2 && !JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""windName"")");
        JSStringRef windName_Str = (argumentCount >= 2) ? JSValueToStringCopy(ctx, arguments[2 -1], exception) : 0;
        MemBlock windName_Mem((argumentCount >= 2) ? JSStringGetMaximumUTF8CStringSize(windName_Str) : 0);
        if (argumentCount >= 2)
        {
            JSStringGetUTF8CString(windName_Str, windName_Mem.ptr, windName_Mem.bytes); JSStringRelease(windName_Str);
        }
        const char* windName = (argumentCount < 2) ? "" : (const char*)windName_Mem.ptr;
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""bpp"")");
        long bpp = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
        Port* port = self->createWindowPort(rect, windName, bpp);
        if (!port) return JSValueMakeNull(ctx);
        if (!port->mPortScriptObj)
        {
            return Port_newFromCpp(ctx, port);
        }
        else
        {
            return port->mPortScriptObj;
        };
    }
    JSValueRef GraphicsManager_CreateImageFromOffscreenPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Port* port = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
            port = Port_getCppObject(port_);
        }
        if (!port)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
        if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""copyPixels"")");
        bool copyPixels = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
        Image* image = Image::createImageFromOffscreenPort(port, copyPixels);
        if (!image) return JSValueMakeNull(ctx);
        if (!image->mImageScriptObj)
        {
            return Image_newFromCpp(ctx, image);
        }
        else
        {
            return image->mImageScriptObj;
        };
    }
    JSValueRef GraphicsManager_CreateOffscreenPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        Port* port = self->createOffscreenPort(rect);
        if (!port) return JSValueMakeNull(ctx);
        if (!port->mPortScriptObj)
        {
            return Port_newFromCpp(ctx, port);
        }
        else
        {
            return port->mPortScriptObj;
        };
    }
    JSValueRef GraphicsManager_CreateFullScreenPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

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
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""screenNum"")");
        long screenNum = (argumentCount<2) ? screenNum_PrimaryScreen : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsBoolean(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""allowResChange"")");
        bool allowResChange = (argumentCount<3) ? true : JSValueToBoolean(ctx, arguments[3 -1]);
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""bpp"")");
        long bpp = (argumentCount<4) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
        Port* port = self->createFullScreenPort(rect, screenNum, allowResChange, bpp);
        if (!port) return JSValueMakeNull(ctx);
        if (!port->mPortScriptObj)
        {
            return Port_newFromCpp(ctx, port);
        }
        else
        {
            return port->mPortScriptObj;
        };
    }
    JSValueRef GraphicsManager_CloseGraphicsPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        Port* port = 0;
        if (argumentCount >= 1)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        self->closeGraphicsPort(port);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef GraphicsManager_CloseAllGraphicsPorts(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->closeAllGraphicsPorts();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef GraphicsManager_CreateFont(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""fontName"")");
        JSStringRef fontName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock fontName_Mem(JSStringGetMaximumUTF8CStringSize(fontName_Str));
        JSStringGetUTF8CString(fontName_Str, fontName_Mem.ptr, fontName_Mem.bytes);
        const char* fontName = (const char*)fontName_Mem.ptr;
        JSStringRelease(fontName_Str);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""scalingFactor"")");
        double scalingFactor = (argumentCount<2) ? 1.0f : JSValueToNumber(ctx, arguments[2 -1], exception);
        Font* font = self->createFont(fontName, scalingFactor);
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
    JSValueRef GraphicsManager_GetMainPort(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Port* port = self->getMainPort();
        if (!port) return JSValueMakeNull(ctx);
        if (!port->mPortScriptObj)
        {
            return Port_newFromCpp(ctx, port);
        }
        else
        {
            return port->mPortScriptObj;
        };
    }
    JSValueRef GraphicsManager_SwitchToFullScreenMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""allowResChange"")");
        bool allowResChange = (argumentCount<1) ? 0 : JSValueToBoolean(ctx, arguments[1 -1]);
        Port* port = 0;
        if (argumentCount >= 2)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[2 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[2 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        bool result = self->switchToFullScreenMode(allowResChange, port);
        return JSValueMakeBoolean(ctx, result);
    }
    JSValueRef GraphicsManager_SwitchToWindowMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        Port* port = 0;
        if (argumentCount >= 1)
        {
            if (!JSValueIsObjectOfClass(ctx, arguments[1 -1], Port_class()))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");
            }
            else
            {
                JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
                port = Port_getCppObject(port_);
            }
        };
        if (argumentCount >= 2 && !JSValueIsString(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a string (""windName"")");
        JSStringRef windName_Str = (argumentCount >= 2) ? JSValueToStringCopy(ctx, arguments[2 -1], exception) : 0;
        MemBlock windName_Mem((argumentCount >= 2) ? JSStringGetMaximumUTF8CStringSize(windName_Str) : 0);
        if (argumentCount >= 2)
        {
            JSStringGetUTF8CString(windName_Str, windName_Mem.ptr, windName_Mem.bytes); JSStringRelease(windName_Str);
        }
        const char* windName = (argumentCount < 2) ? "" : (const char*)windName_Mem.ptr;
        bool result = self->switchToWindowMode(port, windName);
        return JSValueMakeBoolean(ctx, result);
    }
    JSValueRef GraphicsManager_InFullScreenMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool fullscreen = self->inFullScreenMode();
        return JSValueMakeBoolean(ctx, fullscreen);
    }

    JSValueRef GraphicsManager_GetScreenBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));;

        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""screenNum"")");
        long screenNum = (argumentCount<1) ? screenNum_PrimaryScreen : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        pdg::Rect bounds = self->getScreenBounds(screenNum);
        return JSC_RectToValue(ctx, bounds, exception);
    }

    GraphicsManager* New_GraphicsManager(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return GraphicsManager::getSingletonInstance(); }
#endif

}
