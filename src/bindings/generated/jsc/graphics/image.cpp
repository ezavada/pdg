// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/image.cpp
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

    JSObjectRef Image_newFromCpp(JSContextRef ctx, Image* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Image_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Image_class());
        cppObj->mImageScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef Image_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* cppObj = New_Image(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Image" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Image_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Image_class());
        cppObj->mImageScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef Image_class()
    {
        static JSStaticValue Image_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Image_staticFunctions[] =
        {
            { "get""Width", Image_GetWidth, kJSPropertyAttributeDontDelete },
            { "get""Height", Image_GetHeight, kJSPropertyAttributeDontDelete },
            { "get""ImageBounds", Image_GetImageBounds, kJSPropertyAttributeDontDelete },
            { "get""Subsection", Image_GetSubsection, kJSPropertyAttributeDontDelete },
            { "set""TransparentColor", Image_SetTransparentColor, kJSPropertyAttributeDontDelete },
            { "get""Opacity", Image_GetOpacity, kJSPropertyAttributeDontDelete },
            { "set""Opacity", Image_SetOpacity, kJSPropertyAttributeDontDelete },
            { "set""EdgeClamping", Image_SetEdgeClamping, kJSPropertyAttributeDontDelete },
            { "getTransparentColor", Image_GetTransparentColor, kJSPropertyAttributeDontDelete },
            { "retainData", Image_RetainData, kJSPropertyAttributeDontDelete },
            { "retainAlpha", Image_RetainAlpha, kJSPropertyAttributeDontDelete },
            { "prepareToRasterize", Image_PrepareToRasterize, kJSPropertyAttributeDontDelete },
            { "get""AlphaValue", Image_GetAlphaValue, kJSPropertyAttributeDontDelete },
            { "getPixel", Image_GetPixel, kJSPropertyAttributeDontDelete },
            { "get""MyClassTag", Image_GetMyClassTag, kJSPropertyAttributeDontDelete },
            { "get""SerializedSize", Image_GetSerializedSize, kJSPropertyAttributeDontDelete },
            { "serialize", Image_Serialize, kJSPropertyAttributeDontDelete },
            { "deserialize", Image_Deserialize, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Image";
            definition.staticFunctions = Image_staticFunctions;
            definition.staticValues = Image_staticValues;
            definition.callAsConstructor = Image_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef Image_GetTransparentColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Color theTransparentColor = self->getTransparentColor();
        return JSC_ColorToValue(ctx, theTransparentColor, exception);
    }
    JSValueRef Image_SetTransparentColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Color theTransparentColor;
        auto theTransparentColor_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], theTransparentColor, exception);
        if (!theTransparentColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theTransparentColor_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        self->setTransparentColor(theTransparentColor);
        return thisObject;
    }
    JSValueRef Image_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theWidth = self->getWidth();
        return JSValueMakeNumber(ctx, theWidth);
    }
    JSValueRef Image_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theHeight = self->getHeight();
        return JSValueMakeNumber(ctx, theHeight);
    }
    JSValueRef Image_GetImageBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        pdg::Point at;
        if (argumentCount < 1)
        {
            at = pdg::Point(0,0);
        }
        else
        {
            auto at_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], at, exception);
            if (!at_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*at_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }
        };
        Rect r = self->getImageBounds(at);
        return JSC_RectToValue(ctx, r, exception);
    }
    JSValueRef Image_GetSubsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Quad quad;
        auto quad_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], quad, exception);
        if (!quad_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*quad_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };
        Image* image = self->getSubsection(quad);
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
    JSValueRef Image_GetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint8 opacity = self->getOpacity();
        double opacityFloat = (float)opacity / 255.0f;
        return JSValueMakeNumber(ctx, opacityFloat);
    }
    JSValueRef Image_SetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacityFloat"")");
        double opacityFloat = JSValueToNumber(ctx, arguments[1 -1], exception);
        uint32 opacity;
        if (opacityFloat <= 1.0)
        {
            opacity = std::floor(255.0f * opacityFloat);
        }
        else
        {
            opacity = std::round(opacityFloat);
        }
        if (opacity > 255) opacity = 255;
        self->setOpacity(opacity);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Image_SetEdgeClamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""inUseEdgeClamp"")");
        bool inUseEdgeClamp = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setEdgeClamping(inUseEdgeClamp);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Image_RetainData(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->retainData();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Image_RetainAlpha(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->retainAlpha();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Image_PrepareToRasterize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->prepareToRasterize();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Image_GetAlphaValue(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        uint8 a;
        if (argumentCount >= 2)
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            int32 x = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
            if (!JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            int32 y = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
            a = self->getAlphaValue(x, y);
        }
        else
        {
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            a = self->getAlphaValue(p.x, p.y);
        }
        return JSValueMakeNumber(ctx, a);
    }
    JSValueRef Image_GetPixel(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        pdg::Color c;
        if (argumentCount >= 2)
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            int32 x = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
            if (!JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            int32 y = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
            c = self->getPixel(x, y);
        }
        else
        {
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            c = self->getPixel(p.x, p.y);
        }
        return JSC_ColorToValue(ctx, c, exception);
    }

    JSValueRef Image_GetMyClassTag(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 theMyClassTag = self->getMyClassTag();
        return JSValueMakeNumber(ctx, theMyClassTag);
    }
    JSValueRef Image_GetSerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try
        {
            uint32 dataSize = self->getSerializedSize(serializer);
            return JSValueMakeNumber(ctx, dataSize);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Image_Serialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try { self->serialize(serializer); return JSValueMakeUndefined(ctx); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Image_Deserialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Image* self = static_cast<Image*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Deserializer* deserializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef deserializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            deserializer = Deserializer_getCppObject(deserializer_);
        }
        if (!deserializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Deserializer"" (""deserializer"")");
        try
        {
            self->deserialize(deserializer);
            return JSValueMakeUndefined(ctx);
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

    void CleanupImageScriptObject(JSObjectRef obj) { }

    Image* New_Image(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (argumentCount < 1)
        {
            return 0;
        }
        else if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            return Image::createEmptyImageForIntrospection();
        }
        else if (!JSValueIsString(ctx, arguments[0]))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "argument 1 must be a string (filename)";
            s_HaveSavedError = true;
            return 0;
        }
        else
        {
            JSStringRef filename_Str = JSValueToStringCopy(ctx, arguments[0], exception);
            MemBlock filename_Mem(JSStringGetMaximumUTF8CStringSize(filename_Str));
            JSStringGetUTF8CString(filename_Str, filename_Mem.ptr, filename_Mem.bytes);
            const char* filename = (const char*)filename_Mem.ptr;
            JSStringRelease(filename_Str);
            Image* img = Image::createImageFromFile(filename);
            if (!img)
            {
                s_SavedError.str(""); s_SavedError.clear();
                s_SavedError << "could not create Image from file ["<<filename<<"]";
                s_HaveSavedError = true;
                return 0;
            }
            else
            {
                return img;
            }
        }
    }

    JSObjectRef ImageStrip_newFromCpp(JSContextRef ctx, ImageStrip* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, ImageStrip_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ImageStrip_class());
        cppObj->mImageStripScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSObjectRef ImageStrip_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* cppObj = New_ImageStrip(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "ImageStrip" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ImageStrip_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ImageStrip_class());
        cppObj->mImageStripScriptObj = obj;
        JSValueProtect(ctx, obj);
        return obj;
    }

    JSClassRef ImageStrip_class()
    {
        static JSStaticValue ImageStrip_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ImageStrip_staticFunctions[] =
        {
            { "get""Width", ImageStrip_GetWidth, kJSPropertyAttributeDontDelete },
            { "get""Height", ImageStrip_GetHeight, kJSPropertyAttributeDontDelete },
            { "get""ImageBounds", ImageStrip_GetImageBounds, kJSPropertyAttributeDontDelete },
            { "get""Subsection", ImageStrip_GetSubsection, kJSPropertyAttributeDontDelete },
            { "set""TransparentColor", ImageStrip_SetTransparentColor, kJSPropertyAttributeDontDelete },
            { "get""Opacity", ImageStrip_GetOpacity, kJSPropertyAttributeDontDelete },
            { "set""Opacity", ImageStrip_SetOpacity, kJSPropertyAttributeDontDelete },
            { "set""EdgeClamping", ImageStrip_SetEdgeClamping, kJSPropertyAttributeDontDelete },
            { "getTransparentColor", ImageStrip_GetTransparentColor, kJSPropertyAttributeDontDelete },
            { "retainData", ImageStrip_RetainData, kJSPropertyAttributeDontDelete },
            { "retainAlpha", ImageStrip_RetainAlpha, kJSPropertyAttributeDontDelete },
            { "prepareToRasterize", ImageStrip_PrepareToRasterize, kJSPropertyAttributeDontDelete },
            { "get""AlphaValue", ImageStrip_GetAlphaValue, kJSPropertyAttributeDontDelete },
            { "getPixel", ImageStrip_GetPixel, kJSPropertyAttributeDontDelete },
            { "get""MyClassTag", ImageStrip_GetMyClassTag, kJSPropertyAttributeDontDelete },
            { "get""SerializedSize", ImageStrip_GetSerializedSize, kJSPropertyAttributeDontDelete },
            { "serialize", ImageStrip_Serialize, kJSPropertyAttributeDontDelete },
            { "deserialize", ImageStrip_Deserialize, kJSPropertyAttributeDontDelete },
            { "get""Frame", ImageStrip_GetFrame, kJSPropertyAttributeDontDelete },
            { "get""FrameWidth", ImageStrip_GetFrameWidth, kJSPropertyAttributeDontDelete },
            { "set""FrameWidth", ImageStrip_SetFrameWidth, kJSPropertyAttributeDontDelete },
            { "get""NumFrames", ImageStrip_GetNumFrames, kJSPropertyAttributeDontDelete },
            { "set""NumFrames", ImageStrip_SetNumFrames, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ImageStrip";
            definition.staticFunctions = ImageStrip_staticFunctions;
            definition.staticValues = ImageStrip_staticValues;
            definition.callAsConstructor = ImageStrip_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef ImageStrip_GetTransparentColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        pdg::Color theTransparentColor = self->getTransparentColor();
        return JSC_ColorToValue(ctx, theTransparentColor, exception);
    }
    JSValueRef ImageStrip_SetTransparentColor(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Color theTransparentColor;
        auto theTransparentColor_isColor = JSC_ValueIsColor(ctx, arguments[1 -1], theTransparentColor, exception);
        if (!theTransparentColor_isColor.has_value()) { return JSValueMakeNull(ctx); }
        if (!*theTransparentColor_isColor)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Color", arguments[1 -1]);
        };
        self->setTransparentColor(theTransparentColor);
        return thisObject;
    }
    JSValueRef ImageStrip_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theWidth = self->getWidth();
        return JSValueMakeNumber(ctx, theWidth);
    }
    JSValueRef ImageStrip_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int theHeight = self->getHeight();
        return JSValueMakeNumber(ctx, theHeight);
    }
    JSValueRef ImageStrip_GetImageBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        pdg::Point at;
        if (argumentCount < 1)
        {
            at = pdg::Point(0,0);
        }
        else
        {
            auto at_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], at, exception);
            if (!at_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*at_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }
        };
        Rect r = self->getImageBounds(at);
        return JSC_RectToValue(ctx, r, exception);
    }
    JSValueRef ImageStrip_GetSubsection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Quad quad;
        auto quad_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], quad, exception);
        if (!quad_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*quad_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };
        Image* image = self->getSubsection(quad);
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
    JSValueRef ImageStrip_GetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint8 opacity = self->getOpacity();
        double opacityFloat = (float)opacity / 255.0f;
        return JSValueMakeNumber(ctx, opacityFloat);
    }
    JSValueRef ImageStrip_SetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacityFloat"")");
        double opacityFloat = JSValueToNumber(ctx, arguments[1 -1], exception);
        uint32 opacity;
        if (opacityFloat <= 1.0)
        {
            opacity = std::floor(255.0f * opacityFloat);
        }
        else
        {
            opacity = std::round(opacityFloat);
        }
        if (opacity > 255) opacity = 255;
        self->setOpacity(opacity);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ImageStrip_SetEdgeClamping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""inUseEdgeClamp"")");
        bool inUseEdgeClamp = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setEdgeClamping(inUseEdgeClamp);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ImageStrip_RetainData(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->retainData();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ImageStrip_RetainAlpha(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->retainAlpha();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ImageStrip_PrepareToRasterize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->prepareToRasterize();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ImageStrip_GetAlphaValue(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        uint8 a;
        if (argumentCount >= 2)
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            int32 x = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
            if (!JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            int32 y = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
            a = self->getAlphaValue(x, y);
        }
        else
        {
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            a = self->getAlphaValue(p.x, p.y);
        }
        return JSValueMakeNumber(ctx, a);
    }
    JSValueRef ImageStrip_GetPixel(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        pdg::Color c;
        if (argumentCount >= 2)
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            int32 x = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
            if (!JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
            int32 y = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
            c = self->getPixel(x, y);
        }
        else
        {
            pdg::Point p;
            auto p_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p, exception);
            if (!p_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*p_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            c = self->getPixel(p.x, p.y);
        }
        return JSC_ColorToValue(ctx, c, exception);
    }

    JSValueRef ImageStrip_GetMyClassTag(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        uint32 theMyClassTag = self->getMyClassTag();
        return JSValueMakeNumber(ctx, theMyClassTag);
    }
    JSValueRef ImageStrip_GetSerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try
        {
            uint32 dataSize = self->getSerializedSize(serializer);
            return JSValueMakeNumber(ctx, dataSize);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ImageStrip_Serialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Serializer* serializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef serializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            serializer = Serializer_getCppObject(serializer_);
        }
        if (!serializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Serializer"" (""serializer"")");
        try { self->serialize(serializer); return JSValueMakeUndefined(ctx); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ImageStrip_Deserialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        Deserializer* deserializer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef deserializer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            deserializer = Deserializer_getCppObject(deserializer_);
        }
        if (!deserializer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Deserializer"" (""deserializer"")");
        try
        {
            self->deserialize(deserializer);
            return JSValueMakeUndefined(ctx);
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

    JSValueRef ImageStrip_GetNumFrames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int32 theNumFrames = self->getNumFrames();
        return JSValueMakeNumber(ctx, theNumFrames);
    }
    JSValueRef ImageStrip_SetNumFrames(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theNumFrames"")");
        int32 theNumFrames = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setNumFrames(theNumFrames);
        return thisObject;
    }
    JSValueRef ImageStrip_GetFrameWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int32 theFrameWidth = self->getFrameWidth();
        return JSValueMakeNumber(ctx, theFrameWidth);
    }
    JSValueRef ImageStrip_SetFrameWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theFrameWidth"")");
        int32 theFrameWidth = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setFrameWidth(theFrameWidth);
        return thisObject;
    }
    JSValueRef ImageStrip_GetFrame(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ImageStrip* self = static_cast<ImageStrip*>(JSObjectGetPrivate(thisObject));

        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""frameNum"")");
        int32 frameNum = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        Image* image = self->getFrame(frameNum);
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

    void CleanupImageStripScriptObject(JSObjectRef obj) { }

    ImageStrip* New_ImageStrip(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (argumentCount < 1)
        {
            return 0;
        }
        else if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            return ImageStrip::createEmptyImageStripForIntrospection();
        }
        else if (!JSValueIsString(ctx, arguments[0]))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "argument 1 must be a string (filename)";
            s_HaveSavedError = true;
            return 0;
        }
        else
        {
            JSStringRef filename_Str = JSValueToStringCopy(ctx, arguments[0], exception);
            MemBlock filename_Mem(JSStringGetMaximumUTF8CStringSize(filename_Str));
            JSStringGetUTF8CString(filename_Str, filename_Mem.ptr, filename_Mem.bytes);
            const char* filename = (const char*)filename_Mem.ptr;
            JSStringRelease(filename_Str);
            ImageStrip* img = ImageStrip::createImageStripFromFile(filename);
            if (!img)
            {
                s_SavedError.str(""); s_SavedError.clear();
                s_SavedError << "could not create ImageStrip from file ["<<filename<<"]";
                s_HaveSavedError = true;
                return 0;
            }
            else
            {
                return img;
            }
        }
    }

}
