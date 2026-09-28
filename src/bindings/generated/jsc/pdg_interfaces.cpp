// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_js_classes.cpp
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

#include "pdg_script_interface.h"

#define PDG_LIBRARY

#include "internals.h"
#include "pdg-lib.h"

#include <sstream>
#include <cmath>
#include <cstdlib>

#ifndef PDG_DEBUG_JAVASCRIPT

#define SCRIPT_DEBUG_ONLY(_expression)
#else
#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
#endif

namespace pdg
{

    std::ostringstream s_SavedError;

    static std::ostringstream s_ExceptStr;
    JSContextRef gMainContext = 0;
    static JSValueRef s_PendingScriptException = 0;
    static JSStringRef symbol_roll = 0;
    static JSStringRef symbol_pitch = 0;
    static JSStringRef symbol_yaw = 0;

    void SavePendingScriptException(JSValueRef exception)
    {
        if (s_PendingScriptException)
        {
            JSValueUnprotect(gMainContext, s_PendingScriptException);
        }
        s_PendingScriptException = exception;
        if (s_PendingScriptException)
        {
            JSValueProtect(gMainContext, s_PendingScriptException);
        }
    }

    bool RestorePendingScriptException(JSValueRef* exception)
    {
        if (!s_PendingScriptException)
        {
            return false;
        }
        JSValueRef pendingException = s_PendingScriptException;
        s_PendingScriptException = 0;
        if (exception)
        {
            *exception = pendingException;
        }
        JSValueUnprotect(gMainContext, pendingException);
        return true;
    }

    JSValueRef GetConfigManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return ConfigManager_getScriptSingletonInstance();
    }

    JSValueRef GetLogManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return LogManager_getScriptSingletonInstance();
    }

    IEventHandler* New_IEventHandler(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            ScriptEventHandler* handler = new ScriptEventHandler();
            handler->addRef();
            return handler;
        }
        else if (argumentCount != 1 || !JSC_ValueIsFunction(ctx, arguments[0], exception))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "EventHandler must be created with a function argument (handlerFunc)";
            s_HaveSavedError = true;
            return 0;
        }
        JSObjectRef funcObj = JSC_ValueToFunction(ctx, arguments[0], exception);

        ScriptEventHandler* handler = new ScriptEventHandler(funcObj);
        handler->addRef();
        return handler;
    }

    JSValueRef EventManager_IsKeyDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (JSValueIsString(ctx, arguments[0]))
        {
            JSStringRef keyCode_String = JSValueToStringCopy(ctx, arguments[0], exception);
            uint16 utf16Char = JSStringGetCharactersPtr(keyCode_String)[0];
            return JSValueMakeBoolean(ctx, OS::isKeyDown(utf16Char));
        }
        else
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""utf16CharCode"")");
            uint32 utf16CharCode = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
            return JSValueMakeBoolean(ctx, OS::isKeyDown(utf16CharCode));
        }
    }
    JSValueRef EventManager_GetDeviceOrientation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""absolute"")");
        bool absolute = (argumentCount<1) ? false : JSValueToBoolean(ctx, arguments[1 -1]);
        float roll, pitch, yaw;
        OS::getDeviceOrientation(roll, pitch, yaw, absolute);
        JSObjectRef jsOrientation = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, jsOrientation, ((symbol_roll) ? symbol_roll : symbol_roll = JSStringCreateWithUTF8CString("roll")), JSValueMakeNumber(ctx, roll), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsOrientation, ((symbol_pitch) ? symbol_pitch : symbol_pitch = JSStringCreateWithUTF8CString("pitch")), JSValueMakeNumber(ctx, pitch), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsOrientation, ((symbol_yaw) ? symbol_yaw : symbol_yaw = JSStringCreateWithUTF8CString("yaw")), JSValueMakeNumber(ctx, yaw), kJSPropertyAttributeNone, exception);
        return jsOrientation;
    }
    JSValueRef GetEventManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        JSObjectRef jsInstance = EventManager_getScriptSingletonInstance();
        EventManager* evtMgr = EventManager::getSingletonInstance();
        evtMgr->mEventEmitterScriptObj = jsInstance;
        return jsInstance;
    }

    static JSStringRef symbol_name = 0;

    JSValueRef ResourceManager_GetImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""imageName"")");
        JSStringRef imageName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock imageName_Mem(JSStringGetMaximumUTF8CStringSize(imageName_Str));
        JSStringGetUTF8CString(imageName_Str, imageName_Mem.ptr, imageName_Mem.bytes);
        const char* imageName = (const char*)imageName_Mem.ptr;
        JSStringRelease(imageName_Str);
        Image* img = self->getImage(imageName);
        if (img == NULL)
        {
            return JSValueMakeNull(ctx);
        }
        JSObjectRef obj = Image_newFromCpp(ctx, img);

        JSObjectSetProperty(ctx, obj, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), arguments[0], kJSPropertyAttributeNone, exception);
        return obj;
    }
    JSValueRef ResourceManager_GetImageStrip(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""imageName"")");
        JSStringRef imageName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock imageName_Mem(JSStringGetMaximumUTF8CStringSize(imageName_Str));
        JSStringGetUTF8CString(imageName_Str, imageName_Mem.ptr, imageName_Mem.bytes);
        const char* imageName = (const char*)imageName_Mem.ptr;
        JSStringRelease(imageName_Str);
        ImageStrip* img = self->getImageStrip(imageName);
        if (img == NULL)
        {
            return JSValueMakeNull(ctx);
        }
        JSObjectRef obj = ImageStrip_newFromCpp(ctx, img);

        JSObjectSetProperty(ctx, obj, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), arguments[0], kJSPropertyAttributeNone, exception);
        return obj;
    }
#ifndef PDG_NO_SOUND
    JSValueRef ResourceManager_GetSound(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ResourceManager* self = static_cast<ResourceManager*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""soundName"")");
        JSStringRef soundName_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock soundName_Mem(JSStringGetMaximumUTF8CStringSize(soundName_Str));
        JSStringGetUTF8CString(soundName_Str, soundName_Mem.ptr, soundName_Mem.bytes);
        const char* soundName = (const char*)soundName_Mem.ptr;
        JSStringRelease(soundName_Str);
        Sound* snd = self->getSound(soundName);
        if (snd == NULL)
        {
            return JSValueMakeNull(ctx);
        }
        JSObjectRef obj = snd->mSoundScriptObj ? snd->mSoundScriptObj : Sound_newFromCpp(ctx, snd);

        JSObjectSetProperty(ctx, obj, ((symbol_name) ? symbol_name : symbol_name = JSStringCreateWithUTF8CString("name")), arguments[0], kJSPropertyAttributeNone, exception);
        return obj;
    }
#endif

    JSValueRef GetResourceManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return ResourceManager_getScriptSingletonInstance();
    }

    ISerializable* New_ISerializable(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            ScriptSerializable* serializable = new ScriptSerializable();
            serializable->addRef();
            return serializable;
        } else if (argumentCount != 4
            || !JSC_ValueIsFunction(ctx, arguments[0], exception) || !JSC_ValueIsFunction(ctx, arguments[1], exception)
            || !JSC_ValueIsFunction(ctx, arguments[2], exception) || !JSC_ValueIsFunction(ctx, arguments[3], exception))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "Serializable must be created with 4 function arguments " "(getSerializedSizeFunc, serializeFunc, deserializeFunc, getMyClassTagFunc)";
            s_HaveSavedError = true;

            return 0;
        }
        JSObjectRef getSerializedSizeFunc = JSC_ValueToFunction(ctx, arguments[0], exception);
        JSObjectRef serializeFunc = JSC_ValueToFunction(ctx, arguments[1], exception);
        JSObjectRef deserializeFunc = JSC_ValueToFunction(ctx, arguments[2], exception);
        JSObjectRef getMyClassTagFunc = JSC_ValueToFunction(ctx, arguments[3], exception);
        ScriptSerializable* serializable =
            new ScriptSerializable(getSerializedSizeFunc, serializeFunc,
            deserializeFunc, getMyClassTagFunc);
        serializable->addRef();
        return serializable;
    }

    ISerializable* JSC_GetSerializable(JSContextRef ctx, JSValueRef value)
    {
        if (!JSValueIsObject(ctx, value)) return nullptr;
        JSObjectRef object = JSValueToObject(ctx, value, nullptr);

        if (JSValueIsObjectOfClass(ctx, value, ImageStrip_class())) return ImageStrip_getCppObject(object);
        if (JSValueIsObjectOfClass(ctx, value, Image_class())) return Image_getCppObject(object);
        if (JSValueIsObjectOfClass(ctx, value, Sprite_class())) return Sprite_getCppObject(object);
        if (JSValueIsObjectOfClass(ctx, value, TileLayer_class())) return static_cast<Serializable<SpriteLayer>*>(TileLayer_getCppObject(object));
        if (JSValueIsObjectOfClass(ctx, value, SpriteLayer_class())) return static_cast<Serializable<SpriteLayer>*>(SpriteLayer_getCppObject(object));
        if (JSValueIsObjectOfClass(ctx, value, ISerializable_class())) return ISerializable_getCppObject(object);
        return nullptr;
    }

    JSValueRef Serializer_Serialize_obj(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        self->mSerializerScriptObj = thisObject;
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        ISerializable* obj = JSC_GetSerializable(ctx, arguments[0]);
        if (!obj && !JSValueIsNull(ctx, arguments[0]))
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected a serializable object or null" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "ISerializable" " object:") );
        try { self->serialize_obj(obj); }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        if (RestorePendingScriptException(exception))
        {
            return JSValueMakeUndefined(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Serializer_SerializedSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Serializer* self = static_cast<Serializer*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        uint32 dataSize = 0;
        Offset offset;
        Rect rect;
        RotatedRect rotatedRect;
        Quad quad;
        Color color;
        if (JSValueIsString(ctx, arguments[0]))
        {
            JSStringRef str_Str = JSValueToStringCopy(ctx, arguments[0], exception);
            MemBlock str_Mem(JSStringGetMaximumUTF8CStringSize(str_Str));
            JSStringGetUTF8CString(str_Str, str_Mem.ptr, str_Mem.bytes);
            const char* str = (const char*)str_Mem.ptr;
            JSStringRelease(str_Str);
            dataSize = self->sizeof_str(str);
        }
        else if (JSValueIsBoolean(ctx, arguments[0]))
        {
            bool val = JSValueToBoolean(ctx, arguments[0]);
            dataSize = self->sizeof_bool(val);
        }
        else if (JSValueIsNumber(ctx, arguments[0]))
        {
            uint32 val = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[0], exception)));
            dataSize = self->sizeof_uint(val);
        }
        else if (auto isColor = JSC_ValueIsColor(ctx, arguments[0], color, exception); !isColor.has_value())
        {
            return JSValueMakeNull(ctx);
        }
        else if (*isColor)
        {
            dataSize = self->sizeof_color(color);
        }
        else if (auto isOffset = JSC_ValueIsOffset(ctx, arguments[0], offset, exception); !isOffset.has_value())
        {
            return JSValueMakeNull(ctx);
        }
        else if (*isOffset)
        {
            dataSize = self->sizeof_offset(offset);
        }
        else if (auto isRect = JSC_ValueIsRect(ctx, arguments[0], rect, exception); !isRect.has_value())
        {
            return JSValueMakeNull(ctx);
        }
        else if (*isRect)
        {
            dataSize = self->sizeof_rect(rect);
        }
        else if (auto isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[0], rotatedRect, exception); !isRotatedRect.has_value())
        {
            return JSValueMakeNull(ctx);
        }
        else if (*isRotatedRect)
        {
            dataSize = self->sizeof_rotr(rotatedRect);
        }
        else if (auto isQuad = JSC_ValueIsQuad(ctx, arguments[0], quad, exception); !isQuad.has_value())
        {
            return JSValueMakeNull(ctx);
        }
        else if (*isQuad)
        {
            dataSize = self->sizeof_quad(quad);
        }
        else if (JSValueIsObjectOfClass(ctx, arguments[0], MemBlock_class()))
        {
            JSObjectRef obj = JSValueToObject(ctx, arguments[0], exception);
            MemBlock* memBlock = MemBlock_getCppObject(obj);
            dataSize = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
        }
        else
        {

            ISerializable* serializable = 0;
            if (JSValueIsObjectOfClass(ctx, arguments[1 -1], ISerializable_class()))
            {
                JSObjectRef serializable_ = JSValueToObject(ctx, arguments[1 -1], exception);
                serializable = ISerializable_getCppObject(serializable_);
            };
            if (serializable)
            {
                SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, self->mSerializerScriptObj, "Dumping " "Serializer" " object:") );
                SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, serializable->mISerializableScriptObj, "Dumping " "ISerializable" " object:") );
                dataSize = self->sizeof_obj(serializable);
            }
            else
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "TypeError" << "('" << "argument 1 must be either an unsigned integer, " "a string, a MemBlock object, an ISerializable object" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);

            }
        }
        return JSValueMakeNumber(ctx, dataSize);
    }

    JSValueRef RegisterSerializableObject(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsObject(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object (""obj"")");
        JSObjectRef obj = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""uniqueId"")");
        uint32 uniqueId = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[2 -1], exception)));

        JSObjectRef objRef;
        objRef = obj;

        void* objPtr = static_cast<void*>(&objRef);

        Deserializer::registerObject(objPtr, uniqueId);
        return JSValueMakeUndefined(ctx);
    }

#ifndef PDG_NO_GUI

    JSValueRef GraphicsManager_GetCurrentScreenMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));;

        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""screenNum"")");
        long screenNum = (argumentCount<1) ? screenNum_PrimaryScreen : (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        pdg::Rect maxWindowRect;
        pdg::GraphicsManager::ScreenMode mode;
        mode = self->getCurrentScreenMode(screenNum, &maxWindowRect);

        JSValueRef jsScreenMode;
        std::ostringstream jsScreenMode_;
        jsScreenMode_ << "({width:"<<mode.width<<",height:"<<mode.height <<",depth:"<<mode.bpp<<",maxWindowRect:{right:" <<maxWindowRect.right<<",top:"<<maxWindowRect.top<<",left:" <<maxWindowRect.left<<",bottom:"<<maxWindowRect.bottom<<"}})";
        jsScreenMode = JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( jsScreenMode_.str().c_str()), 0, 0, 1, exception);

        return jsScreenMode;
    }

    JSValueRef GraphicsManager_GetNthSupportedScreenMode(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        GraphicsManager* self = static_cast<GraphicsManager*>(JSObjectGetPrivate(thisObject));;

        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""n"")");
        int32 n = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""screenNum"")");
        long screenNum = (argumentCount<2) ? screenNum_PrimaryScreen : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        pdg::GraphicsManager::ScreenMode mode;
        mode = self->getNthSupportedScreenMode(n, screenNum);

        JSValueRef jsScreenMode;
        std::ostringstream jsScreenMode_;
        jsScreenMode_ << "({width:"<<mode.width<<",height:"<<mode.height <<",depth:"<<mode.bpp<<"})";
        jsScreenMode = JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( jsScreenMode_.str().c_str()), 0, 0, 1, exception);

        return jsScreenMode;
    }

    JSValueRef GetGraphicsManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return GraphicsManager_getScriptSingletonInstance();
    }
#endif

#ifndef PDG_NO_SOUND

    JSValueRef GetSoundManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return SoundManager_getScriptSingletonInstance();
    }
#endif

    JSValueRef GetFileManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        return FileManager_getScriptSingletonInstance();
    }

    JSValueRef GetTimerManager(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        JSObjectRef jsInstance = TimerManager_getScriptSingletonInstance();
        TimerManager* timMgr = TimerManager::getSingletonInstance();
        timMgr->mEventEmitterScriptObj = jsInstance;
        return jsInstance;
    }

    IAnimationHelper* New_IAnimationHelper(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            ScriptAnimationHelper* helper = new ScriptAnimationHelper();
            return helper;
        }
        else if (argumentCount != 1 || !JSC_ValueIsFunction(ctx, arguments[0], exception))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "AnimationHelper must be created with a function argument (handlerFunc)";
            s_HaveSavedError = true;
            return 0;
        }
        JSObjectRef funcObj = JSC_ValueToFunction(ctx, arguments[0], exception);
        ScriptAnimationHelper* helper = new ScriptAnimationHelper(funcObj);
        return helper;
    }

    static JSObjectRef s_CustomJavascriptEasing[MAX_CUSTOM_EASINGS];

#ifndef PDG_NO_GUI

    ISpriteDrawHelper* New_ISpriteDrawHelper(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper();
            return helper;
        }
        else if (argumentCount != 1 || !JSC_ValueIsFunction(ctx, arguments[0], exception))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Syntax Error: " << "SpriteDrawHelper must be created with a function argument (drawFunc)";
            s_HaveSavedError = true;
            return 0;
        }
        JSObjectRef funcObj = JSC_ValueToFunction(ctx, arguments[0], exception);
        ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper(funcObj);
        return helper;
    }
#endif

    static JSStringRef symbol_getSerializedSize = 0;
    static JSStringRef symbol_serialize = 0;
    static JSStringRef symbol_deserialize = 0;
    static JSStringRef symbol_getMyClassTag = 0;

    ScriptSerializable::ScriptSerializable(
        JSObjectRef javascriptGetSerializedSizeFunc,
        JSObjectRef javascriptSerializeFunc,
        JSObjectRef javascriptDeserializeFunc,
        JSObjectRef javascriptGetMyClassTagFunc)
    {
        mScriptGetSerializedSizeFunc = javascriptGetSerializedSizeFunc;
        JSValueProtect(gMainContext, mScriptGetSerializedSizeFunc);
        mScriptSerializeFunc = javascriptSerializeFunc;
        JSValueProtect(gMainContext, mScriptSerializeFunc);
        mScriptDeserializeFunc = javascriptDeserializeFunc;
        JSValueProtect(gMainContext, mScriptDeserializeFunc);
        mScriptGetMyClassTagFunc = javascriptGetMyClassTagFunc;
        JSValueProtect(gMainContext, mScriptGetMyClassTagFunc);
    }

    uint32
        ScriptSerializable::getSerializedSize(ISerializer* serializer) const
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        JSValueRef argv[1];
        Serializer* ser = dynamic_cast<Serializer*>(serializer);
        if (!ser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
                exit(1);
                )
        }

        argv[0] = ser->mSerializerScriptObj;
        JSObjectRef func;
        if (mScriptGetSerializedSizeFunc)
        {
            func = mScriptGetSerializedSizeFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mISerializableScriptObj, ((symbol_getSerializedSize) ? symbol_getSerializedSize : symbol_getSerializedSize = JSStringCreateWithUTF8CString("getSerializedSize")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mISerializableScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            SavePendingScriptException(*exception);
            return 0;
        }
        if (!JSValueIsNumber(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from getSerializedSize Function must be an unsigned integer ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return 0;
        }
        return (uint32)floor(fabs(JSValueToNumber(ctx, resVal, exception)));
    }

    void
        ScriptSerializable::serialize(ISerializer* serializer) const
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        JSValueRef argv[1];
        Serializer* ser = dynamic_cast<Serializer*>(serializer);
        if (!ser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
                exit(1);
                )
        }

        argv[0] = ser->mSerializerScriptObj;
        JSObjectRef func;
        if (mScriptSerializeFunc)
        {
            func = mScriptSerializeFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mISerializableScriptObj, ((symbol_serialize) ? symbol_serialize : symbol_serialize = JSStringCreateWithUTF8CString("serialize")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mISerializableScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            SavePendingScriptException(*exception);
        }
    }

    void
        ScriptSerializable::deserialize(IDeserializer* deserializer)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        JSValueRef argv[1];
        Deserializer* deser = dynamic_cast<Deserializer*>(deserializer);
        if (!deser)
        {
            DEBUG_ONLY(
                std::cerr << "Internal Error: deserialize Function called with invalid Deserializer\n";
                exit(1);
                )
        }
        argv[0] = deser->mDeserializerScriptObj;
        JSObjectRef func;
        if (mScriptDeserializeFunc)
        {
            func = mScriptDeserializeFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mISerializableScriptObj, ((symbol_deserialize) ? symbol_deserialize : symbol_deserialize = JSStringCreateWithUTF8CString("deserialize")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mISerializableScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            SavePendingScriptException(*exception);
        }
    }

    uint32
        ScriptSerializable::getMyClassTag() const
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        JSObjectRef func;
        if (mScriptGetMyClassTagFunc)
        {
            func = mScriptGetMyClassTagFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mISerializableScriptObj, ((symbol_getMyClassTag) ? symbol_getMyClassTag : symbol_getMyClassTag = JSStringCreateWithUTF8CString("getMyClassTag")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mISerializableScriptObj, 0, 0, exception);

        if (resVal == 0 && *exception)
        {
            SavePendingScriptException(*exception);
            return 0;
        }
        if (!JSValueIsNumber(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from getMyClassTag Function must be an unsigned integer ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return 0;
        }
        return (uint32)floor(fabs(JSValueToNumber(ctx, resVal, exception)));
    }

    static JSStringRef symbol_collider = 0;
    static JSStringRef symbol_other = 0;
    static JSStringRef symbol_shape = 0;
    static JSStringRef symbol_otherShape = 0;
    static JSStringRef symbol_phase = 0;
    static JSStringRef symbol_penetration = 0;
    static JSStringRef symbol_point = 0;
    static JSStringRef symbol_sensor = 0;
    static JSStringRef symbol_emitter = 0;
    static JSStringRef symbol_eventType = 0;
    static JSStringRef symbol_startupReason = 0;
    static JSStringRef symbol_exitReason = 0;
    static JSStringRef symbol_exitCode = 0;
    static JSStringRef symbol_id = 0;
    static JSStringRef symbol_millisec = 0;
    static JSStringRef symbol_msElapsed = 0;
    static JSStringRef symbol_keyCode = 0;
    static JSStringRef symbol_shift = 0;
    static JSStringRef symbol_ctrl = 0;
    static JSStringRef symbol_alt = 0;
    static JSStringRef symbol_meta = 0;
    static JSStringRef symbol_unicode = 0;
    static JSStringRef symbol_isRepeating = 0;
    static JSStringRef symbol_touchType = 0;
    static JSStringRef symbol_touchedSprite = 0;
    static JSStringRef symbol_inLayer = 0;
    static JSStringRef symbol_mousePos = 0;
    static JSStringRef symbol_leftButton = 0;
    static JSStringRef symbol_rightButton = 0;
    static JSStringRef symbol_buttonNumber = 0;
    static JSStringRef symbol_lastClickPos = 0;
    static JSStringRef symbol_lastClickElapsed = 0;
    static JSStringRef symbol_horizDelta = 0;
    static JSStringRef symbol_vertDelta = 0;
    static JSStringRef symbol_sound = 0;
    static JSStringRef symbol_eventCode = 0;
    static JSStringRef symbol_port = 0;
    static JSStringRef symbol_screenPos = 0;
    static JSStringRef symbol_frameNum = 0;
    static JSStringRef symbol_targetSprite = 0;
    static JSStringRef symbol_normal = 0;
    static JSStringRef symbol_impulse = 0;
    static JSStringRef symbol_force = 0;
    static JSStringRef symbol_arbiter = 0;
    static JSStringRef symbol_kineticEnergy = 0;
    static JSStringRef symbol_collisionName = 0;
    static JSStringRef symbol_withCollisionName = 0;
    static JSStringRef symbol_isFirstContact = 0;
    static JSStringRef symbol_breakForce = 0;
    static JSStringRef symbol_breakAngularSpeed = 0;
    static JSStringRef symbol_angularSpeed = 0;
    static JSStringRef symbol_referenceBody = 0;
    static JSStringRef symbol_part = 0;
    static JSStringRef symbol_body = 0;
    static JSStringRef symbol_reason = 0;
    static JSStringRef symbol_joint = 0;
    static JSStringRef symbol_action = 0;
    static JSStringRef symbol_bone = 0;
    static JSStringRef symbol_wholeRig = 0;
    static JSStringRef symbol_includeDescendants = 0;
    static JSStringRef symbol_mode = 0;
    static JSStringRef symbol_bodyCount = 0;
    static JSStringRef symbol_disabled = 0;

    static JSStringRef symbol_actingLayer = 0;
    static JSStringRef symbol_actingSprite = 0;
    static JSStringRef symbol_handleEvent = 0;
    static JSStringRef symbol_oldScreenPos = 0;
    static JSStringRef symbol_oldWidth = 0;
    static JSStringRef symbol_oldHeight = 0;

    ScriptEventHandler::ScriptEventHandler(JSObjectRef func)
    {
        mScriptHandlerFunc = func;
        JSValueProtect(gMainContext, mScriptHandlerFunc);

    }

    static JSStringRef symbol_triggerName = 0;
    static JSStringRef symbol_clipName = 0;
    static JSStringRef symbol_entityName = 0;
    static JSStringRef symbol_timeSeconds = 0;
    static JSStringRef symbol_offsetSeconds = 0;

    bool ScriptEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (!emitter->mEventEmitterScriptObj)
            if (auto* particle = dynamic_cast<Particle*>(emitter)) Particle_newFromCpp(ctx, particle);
        JSObjectRef jsEvent = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_emitter) ? symbol_emitter : symbol_emitter = JSStringCreateWithUTF8CString("emitter")), emitter->mEventEmitterScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_eventType) ? symbol_eventType : symbol_eventType = JSStringCreateWithUTF8CString("eventType")), JSValueMakeNumber(ctx, inEventType), kJSPropertyAttributeNone, exception);
        switch (inEventType)
        {
            case pdg::eventType_Startup:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_startupReason) ? symbol_startupReason : symbol_startupReason = JSStringCreateWithUTF8CString("startupReason")), JSValueMakeNumber(ctx, static_cast<StartupInfo*>(inEventData)->startupReason), kJSPropertyAttributeNone, exception);

                break;
            case pdg::eventType_Shutdown:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_exitReason) ? symbol_exitReason : symbol_exitReason = JSStringCreateWithUTF8CString("exitReason")), JSValueMakeNumber(ctx, static_cast<ShutdownInfo*>(inEventData)->exitReason), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_exitCode) ? symbol_exitCode : symbol_exitCode = JSStringCreateWithUTF8CString("exitCode")), JSValueMakeNumber(ctx, static_cast<ShutdownInfo*>(inEventData)->exitCode), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_Timer:
                if (static_cast<TimerInfo*>(inEventData)->id <= 0)
                {

                    return false;
                }
                JSObjectSetProperty(ctx, jsEvent, ((symbol_id) ? symbol_id : symbol_id = JSStringCreateWithUTF8CString("id")), JSValueMakeNumber(ctx, static_cast<TimerInfo*>(inEventData)->id), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_millisec) ? symbol_millisec : symbol_millisec = JSStringCreateWithUTF8CString("millisec")), JSValueMakeNumber(ctx, static_cast<TimerInfo*>(inEventData)->millisec), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_msElapsed) ? symbol_msElapsed : symbol_msElapsed = JSStringCreateWithUTF8CString("msElapsed")), JSValueMakeNumber(ctx, static_cast<TimerInfo*>(inEventData)->msElapsed), kJSPropertyAttributeNone, exception);
                break;
#ifndef PDG_NO_GUI
            case pdg::eventType_KeyDown:
            case pdg::eventType_KeyUp:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_keyCode) ? symbol_keyCode : symbol_keyCode = JSStringCreateWithUTF8CString("keyCode")), JSValueMakeNumber(ctx, static_cast<KeyInfo*>(inEventData)->keyCode), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_KeyPress:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_shift) ? symbol_shift : symbol_shift = JSStringCreateWithUTF8CString("shift")), JSValueMakeBoolean(ctx, static_cast<KeyPressInfo*>(inEventData)->shift), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_ctrl) ? symbol_ctrl : symbol_ctrl = JSStringCreateWithUTF8CString("ctrl")), JSValueMakeBoolean(ctx, static_cast<KeyPressInfo*>(inEventData)->ctrl), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_alt) ? symbol_alt : symbol_alt = JSStringCreateWithUTF8CString("alt")), JSValueMakeBoolean(ctx, static_cast<KeyPressInfo*>(inEventData)->alt), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_meta) ? symbol_meta : symbol_meta = JSStringCreateWithUTF8CString("meta")), JSValueMakeBoolean(ctx, static_cast<KeyPressInfo*>(inEventData)->meta), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_unicode) ? symbol_unicode : symbol_unicode = JSStringCreateWithUTF8CString("unicode")), JSValueMakeNumber(ctx, static_cast<KeyPressInfo*>(inEventData)->unicode), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_isRepeating) ? symbol_isRepeating : symbol_isRepeating = JSStringCreateWithUTF8CString("isRepeating")), JSValueMakeBoolean(ctx, static_cast<KeyPressInfo*>(inEventData)->isRepeating), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_SpriteTouch:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_touchType) ? symbol_touchType : symbol_touchType = JSStringCreateWithUTF8CString("touchType")), JSValueMakeNumber(ctx, static_cast<SpriteTouchInfo*>(inEventData)->touchType), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_touchedSprite) ? symbol_touchedSprite : symbol_touchedSprite = JSStringCreateWithUTF8CString("touchedSprite")), static_cast<SpriteTouchInfo*>(inEventData)->touchedSprite->mSpriteScriptObj, kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_inLayer) ? symbol_inLayer : symbol_inLayer = JSStringCreateWithUTF8CString("inLayer")), static_cast<SpriteTouchInfo*>(inEventData)->inLayer->mSpriteLayerScriptObj, kJSPropertyAttributeNone, exception);

            case pdg::eventType_MouseDown:
            case pdg::eventType_MouseUp:
            case pdg::eventType_MouseMove:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_shift) ? symbol_shift : symbol_shift = JSStringCreateWithUTF8CString("shift")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->shift), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_ctrl) ? symbol_ctrl : symbol_ctrl = JSStringCreateWithUTF8CString("ctrl")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->ctrl), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_alt) ? symbol_alt : symbol_alt = JSStringCreateWithUTF8CString("alt")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->alt), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_meta) ? symbol_meta : symbol_meta = JSStringCreateWithUTF8CString("meta")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->meta), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_mousePos) ? symbol_mousePos : symbol_mousePos = JSStringCreateWithUTF8CString("mousePos")), JSC_PointToValue(ctx, static_cast<MouseInfo*>(inEventData)->mousePos, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_leftButton) ? symbol_leftButton : symbol_leftButton = JSStringCreateWithUTF8CString("leftButton")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->leftButton), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_rightButton) ? symbol_rightButton : symbol_rightButton = JSStringCreateWithUTF8CString("rightButton")), JSValueMakeBoolean(ctx, static_cast<MouseInfo*>(inEventData)->rightButton), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_buttonNumber) ? symbol_buttonNumber : symbol_buttonNumber = JSStringCreateWithUTF8CString("buttonNumber")), JSValueMakeNumber(ctx, static_cast<MouseInfo*>(inEventData)->buttonNumber), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_lastClickPos) ? symbol_lastClickPos : symbol_lastClickPos = JSStringCreateWithUTF8CString("lastClickPos")), JSC_PointToValue(ctx, static_cast<MouseInfo*>(inEventData)->lastClickPos, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_lastClickElapsed) ? symbol_lastClickElapsed : symbol_lastClickElapsed = JSStringCreateWithUTF8CString("lastClickElapsed")), JSValueMakeNumber(ctx, static_cast<MouseInfo*>(inEventData)->lastClickElapsed), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_ScrollWheel:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_shift) ? symbol_shift : symbol_shift = JSStringCreateWithUTF8CString("shift")), JSValueMakeBoolean(ctx, static_cast<ScrollWheelInfo*>(inEventData)->shift), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_ctrl) ? symbol_ctrl : symbol_ctrl = JSStringCreateWithUTF8CString("ctrl")), JSValueMakeBoolean(ctx, static_cast<ScrollWheelInfo*>(inEventData)->ctrl), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_alt) ? symbol_alt : symbol_alt = JSStringCreateWithUTF8CString("alt")), JSValueMakeBoolean(ctx, static_cast<ScrollWheelInfo*>(inEventData)->alt), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_meta) ? symbol_meta : symbol_meta = JSStringCreateWithUTF8CString("meta")), JSValueMakeBoolean(ctx, static_cast<ScrollWheelInfo*>(inEventData)->meta), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_horizDelta) ? symbol_horizDelta : symbol_horizDelta = JSStringCreateWithUTF8CString("horizDelta")), JSValueMakeNumber(ctx, static_cast<ScrollWheelInfo*>(inEventData)->horizDelta), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_vertDelta) ? symbol_vertDelta : symbol_vertDelta = JSStringCreateWithUTF8CString("vertDelta")), JSValueMakeNumber(ctx, static_cast<ScrollWheelInfo*>(inEventData)->vertDelta), kJSPropertyAttributeNone, exception);
                break;
#endif
#ifndef PDG_NO_NETWORK

            case pdg::eventType_NetConnect:
                return false;
                break;
            case pdg::eventType_NetDisconnect:
                return false;
                break;
            case pdg::eventType_NetData:
                return false;
                break;
            case pdg::eventType_NetError:
                return false;
                break;
#endif
#ifndef PDG_NO_SOUND
            case pdg::eventType_SoundEvent:
            {
                auto* sound = static_cast<SoundEventInfo*>(inEventData)->sound;
                JSObjectRef soundObject = sound->mSoundScriptObj ? sound->mSoundScriptObj : Sound_newFromCpp(ctx, sound);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_eventCode) ? symbol_eventCode : symbol_eventCode = JSStringCreateWithUTF8CString("eventCode")), JSValueMakeNumber(ctx, static_cast<SoundEventInfo*>(inEventData)->eventCode), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_sound) ? symbol_sound : symbol_sound = JSStringCreateWithUTF8CString("sound")), soundObject, kJSPropertyAttributeNone, exception);
                break;
            }
#endif
#ifndef PDG_NO_GUI
            case pdg::eventType_PortResized:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_port) ? symbol_port : symbol_port = JSStringCreateWithUTF8CString("port")), static_cast<PortResizeInfo*>(inEventData)->port->mPortScriptObj, kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_screenPos) ? symbol_screenPos : symbol_screenPos = JSStringCreateWithUTF8CString("screenPos")), JSValueMakeNumber(ctx, static_cast<PortResizeInfo*>(inEventData)->screenPos), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_oldScreenPos) ? symbol_oldScreenPos : symbol_oldScreenPos = JSStringCreateWithUTF8CString("oldScreenPos")), JSValueMakeNumber(ctx, static_cast<PortResizeInfo*>(inEventData)->oldScreenPos), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_oldWidth) ? symbol_oldWidth : symbol_oldWidth = JSStringCreateWithUTF8CString("oldWidth")), JSValueMakeNumber(ctx, static_cast<PortResizeInfo*>(inEventData)->oldWidth), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_oldHeight) ? symbol_oldHeight : symbol_oldHeight = JSStringCreateWithUTF8CString("oldHeight")), JSValueMakeNumber(ctx, static_cast<PortResizeInfo*>(inEventData)->oldHeight), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_PortDraw:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_port) ? symbol_port : symbol_port = JSStringCreateWithUTF8CString("port")), static_cast<PortDrawInfo*>(inEventData)->port->mPortScriptObj, kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_frameNum) ? symbol_frameNum : symbol_frameNum = JSStringCreateWithUTF8CString("frameNum")), JSValueMakeNumber(ctx, static_cast<PortDrawInfo*>(inEventData)->frameNum), kJSPropertyAttributeNone, exception);
                break;
#endif
            case pdg::eventType_ParticleBreak:
            {
                const auto* info=static_cast<PhysicsBodyBreakInfo*>(inEventData);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_angularSpeed) ? symbol_angularSpeed : symbol_angularSpeed = JSStringCreateWithUTF8CString("angularSpeed")), JSValueMakeNumber(ctx, info->angularSpeed), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_breakAngularSpeed) ? symbol_breakAngularSpeed : symbol_breakAngularSpeed = JSStringCreateWithUTF8CString("breakAngularSpeed")), JSValueMakeNumber(ctx, info->breakAngularSpeed), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_body) ? symbol_body : symbol_body = JSStringCreateWithUTF8CString("body")), (info->body ? info->body->mPhysicsBodyScriptObj ? info->body->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, info->body) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_referenceBody) ? symbol_referenceBody : symbol_referenceBody = JSStringCreateWithUTF8CString("referenceBody")), (info->referenceBody ? info->referenceBody->mPhysicsBodyScriptObj ? info->referenceBody->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, info->referenceBody) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                break;
            }
            case pdg::eventType_ColliderContact:
            {
                auto* contact=static_cast<ColliderContact*>(inEventData);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_collider) ? symbol_collider : symbol_collider = JSStringCreateWithUTF8CString("collider")), (contact->collider->mColliderScriptObj ? contact->collider->mColliderScriptObj : Collider_newFromCpp(ctx, contact->collider)), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_other) ? symbol_other : symbol_other = JSStringCreateWithUTF8CString("other")), (contact->other->mColliderScriptObj ? contact->other->mColliderScriptObj : Collider_newFromCpp(ctx, contact->other)), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_shape) ? symbol_shape : symbol_shape = JSStringCreateWithUTF8CString("shape")), JSValueMakeNumber(ctx, contact->shape), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_otherShape) ? symbol_otherShape : symbol_otherShape = JSStringCreateWithUTF8CString("otherShape")), JSValueMakeNumber(ctx, contact->otherShape), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_phase) ? symbol_phase : symbol_phase = JSStringCreateWithUTF8CString("phase")), JSValueMakeNumber(ctx, contact->phase), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_penetration) ? symbol_penetration : symbol_penetration = JSStringCreateWithUTF8CString("penetration")), JSValueMakeNumber(ctx, contact->penetration), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_point) ? symbol_point : symbol_point = JSStringCreateWithUTF8CString("point")), JSC_PointToValue(ctx, contact->point, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_normal) ? symbol_normal : symbol_normal = JSStringCreateWithUTF8CString("normal")), JSC_VectorToValue(ctx, contact->normal, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_impulse) ? symbol_impulse : symbol_impulse = JSStringCreateWithUTF8CString("impulse")), JSC_VectorToValue(ctx, contact->impulse, exception), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_sensor) ? symbol_sensor : symbol_sensor = JSStringCreateWithUTF8CString("sensor")), JSValueMakeBoolean(ctx, contact->sensor), kJSPropertyAttributeNone, exception);
                break;
            }
            case pdg::eventType_SpriteCollide:
            case pdg::eventType_SpriteBreak:
                if (inEventType == pdg::eventType_SpriteCollide)
                {
                    if (static_cast<SpriteCollideInfo*>(inEventData)->targetSprite)
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_targetSprite) ? symbol_targetSprite : symbol_targetSprite = JSStringCreateWithUTF8CString("targetSprite")), static_cast<SpriteCollideInfo*>(inEventData)->targetSprite->mSpriteScriptObj, kJSPropertyAttributeNone, exception);
                    }
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_normal) ? symbol_normal : symbol_normal = JSStringCreateWithUTF8CString("normal")), JSC_VectorToValue(ctx, static_cast<SpriteCollideInfo*>(inEventData)->normal, exception), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_impulse) ? symbol_impulse : symbol_impulse = JSStringCreateWithUTF8CString("impulse")), JSC_VectorToValue(ctx, static_cast<SpriteCollideInfo*>(inEventData)->impulse, exception), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_force) ? symbol_force : symbol_force = JSStringCreateWithUTF8CString("force")), JSValueMakeNumber(ctx, static_cast<SpriteCollideInfo*>(inEventData)->force), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_kineticEnergy) ? symbol_kineticEnergy : symbol_kineticEnergy = JSStringCreateWithUTF8CString("kineticEnergy")), JSValueMakeNumber(ctx, static_cast<SpriteCollideInfo*>(inEventData)->kineticEnergy), kJSPropertyAttributeNone, exception);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                    if (static_cast<SpriteCollideInfo*>(inEventData)->arbiter)
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_arbiter) ? symbol_arbiter : symbol_arbiter = JSStringCreateWithUTF8CString("arbiter")), cpArbiter_newFromCpp(ctx, static_cast<SpriteCollideInfo*>(inEventData)->arbiter), kJSPropertyAttributeNone, exception);
                    }
#endif
#ifdef PDG_SPRITER_SUPPORT
                    if (static_cast<SpriteCollideInfo*>(inEventData)->collisionName)
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_collisionName) ? symbol_collisionName : symbol_collisionName = JSStringCreateWithUTF8CString("collisionName")), JSC_MakeValueFromCString(ctx, static_cast<SpriteCollideInfo*>(inEventData)->collisionName), kJSPropertyAttributeNone, exception);
                    }
                    else
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_collisionName) ? symbol_collisionName : symbol_collisionName = JSStringCreateWithUTF8CString("collisionName")), JSValueMakeNull(ctx), kJSPropertyAttributeNone, exception);
                    }
                    if (static_cast<SpriteCollideInfo*>(inEventData)->withCollisionName)
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_withCollisionName) ? symbol_withCollisionName : symbol_withCollisionName = JSStringCreateWithUTF8CString("withCollisionName")), JSC_MakeValueFromCString(ctx, static_cast<SpriteCollideInfo*>(inEventData)->withCollisionName), kJSPropertyAttributeNone, exception);
                    }
                    else
                    {
                        JSObjectSetProperty(ctx, jsEvent, ((symbol_withCollisionName) ? symbol_withCollisionName : symbol_withCollisionName = JSStringCreateWithUTF8CString("withCollisionName")), JSValueMakeNull(ctx), kJSPropertyAttributeNone, exception);
                    }
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_isFirstContact) ? symbol_isFirstContact : symbol_isFirstContact = JSStringCreateWithUTF8CString("isFirstContact")), JSValueMakeBoolean(ctx, static_cast<SpriteCollideInfo*>(inEventData)->isFirstContact), kJSPropertyAttributeNone, exception);
#endif
                }
                else
                {
                    auto* sjb = static_cast<SpriteJointBreakInfo*>(inEventData);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_targetSprite) ? symbol_targetSprite : symbol_targetSprite = JSStringCreateWithUTF8CString("targetSprite")), (sjb->targetSprite ? sjb->targetSprite->mSpriteScriptObj : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_impulse) ? symbol_impulse : symbol_impulse = JSStringCreateWithUTF8CString("impulse")), JSValueMakeNumber(ctx, sjb->impulse), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_force) ? symbol_force : symbol_force = JSStringCreateWithUTF8CString("force")), JSValueMakeNumber(ctx, sjb->force), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_breakForce) ? symbol_breakForce : symbol_breakForce = JSStringCreateWithUTF8CString("breakForce")), JSValueMakeNumber(ctx, sjb->breakForce), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_reason) ? symbol_reason : symbol_reason = JSStringCreateWithUTF8CString("reason")), JSValueMakeNumber(ctx, sjb->reason), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_angularSpeed) ? symbol_angularSpeed : symbol_angularSpeed = JSStringCreateWithUTF8CString("angularSpeed")), JSValueMakeNumber(ctx, sjb->angularSpeed), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_breakAngularSpeed) ? symbol_breakAngularSpeed : symbol_breakAngularSpeed = JSStringCreateWithUTF8CString("breakAngularSpeed")), JSValueMakeNumber(ctx, sjb->breakAngularSpeed), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_body) ? symbol_body : symbol_body = JSStringCreateWithUTF8CString("body")), (sjb->body ? sjb->body->mPhysicsBodyScriptObj ? sjb->body->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, sjb->body) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_referenceBody) ? symbol_referenceBody : symbol_referenceBody = JSStringCreateWithUTF8CString("referenceBody")), (sjb->referenceBody ? sjb->referenceBody->mPhysicsBodyScriptObj ? sjb->referenceBody->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, sjb->referenceBody) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_part) ? symbol_part : symbol_part = JSStringCreateWithUTF8CString("part")), (sjb->part ? sjb->part->mPartScriptObj ? sjb->part->mPartScriptObj : Part_newFromCpp(ctx, sjb->part) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_joint) ? symbol_joint : symbol_joint = JSStringCreateWithUTF8CString("joint")), (sjb->joint ? cpConstraint_newFromCpp(ctx, sjb->joint) : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
#else
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_joint) ? symbol_joint : symbol_joint = JSStringCreateWithUTF8CString("joint")), JSValueMakeNull(ctx), kJSPropertyAttributeNone, exception);
#endif
                }

#ifdef PDG_SPRITER_SUPPORT
            case pdg::eventType_SpriteTriggerEvent:
            {

                if (inEventType == pdg::eventType_SpriteTriggerEvent)
                {
                    auto* trigger=static_cast<SpriteTriggerEventInfo*>(inEventData);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_triggerName) ? symbol_triggerName : symbol_triggerName = JSStringCreateWithUTF8CString("triggerName")), JSC_MakeValueFromCString(ctx, trigger->triggerName), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_clipName) ? symbol_clipName : symbol_clipName = JSStringCreateWithUTF8CString("clipName")), JSC_MakeValueFromCString(ctx, trigger->clipName), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_entityName) ? symbol_entityName : symbol_entityName = JSStringCreateWithUTF8CString("entityName")), JSC_MakeValueFromCString(ctx, trigger->entityName), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_timeSeconds) ? symbol_timeSeconds : symbol_timeSeconds = JSStringCreateWithUTF8CString("timeSeconds")), JSValueMakeNumber(ctx, trigger->timeSeconds), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_offsetSeconds) ? symbol_offsetSeconds : symbol_offsetSeconds = JSStringCreateWithUTF8CString("offsetSeconds")), JSValueMakeNumber(ctx, trigger->offsetSeconds), kJSPropertyAttributeNone, exception);
                }
            }
#endif
            case pdg::eventType_SpriteAnimate:

                if (inEventType==pdg::eventType_SpriteAnimate && static_cast<SpriteAnimateInfo*>(inEventData)->action==Sprite::action_AnimationPhysicsRecoveryComplete)
                {
                    const auto* recovery=static_cast<SpriteAnimationPhysicsRecoveryInfo*>(inEventData);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_id) ? symbol_id : symbol_id = JSStringCreateWithUTF8CString("id")), JSValueMakeNumber(ctx, recovery->id), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_bone) ? symbol_bone : symbol_bone = JSStringCreateWithUTF8CString("bone")), JSValueMakeNumber(ctx, recovery->bone), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_wholeRig) ? symbol_wholeRig : symbol_wholeRig = JSStringCreateWithUTF8CString("wholeRig")), JSValueMakeBoolean(ctx, recovery->wholeRig), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_includeDescendants) ? symbol_includeDescendants : symbol_includeDescendants = JSStringCreateWithUTF8CString("includeDescendants")), JSValueMakeBoolean(ctx, recovery->includeDescendants), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_mode) ? symbol_mode : symbol_mode = JSStringCreateWithUTF8CString("mode")), JSValueMakeNumber(ctx, recovery->mode), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_bodyCount) ? symbol_bodyCount : symbol_bodyCount = JSStringCreateWithUTF8CString("bodyCount")), JSValueMakeNumber(ctx, recovery->bodyCount), kJSPropertyAttributeNone, exception);
                    JSObjectSetProperty(ctx, jsEvent, ((symbol_disabled) ? symbol_disabled : symbol_disabled = JSStringCreateWithUTF8CString("disabled")), JSValueMakeBoolean(ctx, recovery->disabled), kJSPropertyAttributeNone, exception);
                }
                JSObjectSetProperty(ctx, jsEvent, ((symbol_action) ? symbol_action : symbol_action = JSStringCreateWithUTF8CString("action")), JSValueMakeNumber(ctx, static_cast<SpriteAnimateInfo*>(inEventData)->action), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_actingSprite) ? symbol_actingSprite : symbol_actingSprite = JSStringCreateWithUTF8CString("actingSprite")), (static_cast<SpriteAnimateInfo*>(inEventData)->actingSprite ? static_cast<SpriteAnimateInfo*>(inEventData)->actingSprite->mSpriteScriptObj : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_inLayer) ? symbol_inLayer : symbol_inLayer = JSStringCreateWithUTF8CString("inLayer")), (static_cast<SpriteAnimateInfo*>(inEventData)->inLayer ? static_cast<SpriteAnimateInfo*>(inEventData)->inLayer->mSpriteLayerScriptObj : JSValueMakeNull(ctx)), kJSPropertyAttributeNone, exception);
                break;
            case pdg::eventType_SpriteLayer:
                JSObjectSetProperty(ctx, jsEvent, ((symbol_action) ? symbol_action : symbol_action = JSStringCreateWithUTF8CString("action")), JSValueMakeNumber(ctx, static_cast<SpriteLayerInfo*>(inEventData)->action), kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_actingLayer) ? symbol_actingLayer : symbol_actingLayer = JSStringCreateWithUTF8CString("actingLayer")), static_cast<SpriteLayerInfo*>(inEventData)->actingLayer->mSpriteLayerScriptObj, kJSPropertyAttributeNone, exception);
                JSObjectSetProperty(ctx, jsEvent, ((symbol_millisec) ? symbol_millisec : symbol_millisec = JSStringCreateWithUTF8CString("millisec")), JSValueMakeNumber(ctx, static_cast<SpriteLayerInfo*>(inEventData)->millisec), kJSPropertyAttributeNone, exception);
                break;
            default:
            {
                std::ostringstream msg;
                msg << "unknown event (" << inEventType << ")";
                s_SavedError.str(""); s_SavedError.clear();
                s_SavedError << "Type Error: " << msg.str().c_str();
                s_HaveSavedError = true;
                return false;
            }
            break;

        }

        JSValueRef argv[1];
        argv[0] = jsEvent;

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mIEventHandlerScriptObj, "Dumping " "IEventHandler" " object:") );

        JSObjectRef func;
        if (mScriptHandlerFunc)
        {
            func = mScriptHandlerFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mIEventHandlerScriptObj, ((symbol_handleEvent) ? symbol_handleEvent : symbol_handleEvent = JSStringCreateWithUTF8CString("handleEvent")), exception), exception);
        }

        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mIEventHandlerScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(*exception);
            return false;
        }
        if (!JSValueIsBoolean(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }

    ScriptTouchEventHandler::ScriptTouchEventHandler()
    {
        mScriptHandlerFunc = 0;
        mExpectedAction = 0;
    }

    ScriptTouchEventHandler::ScriptTouchEventHandler(JSObjectRef func, long expectedAction)
    {
        mScriptHandlerFunc = func;
        mExpectedAction = expectedAction;
        JSValueProtect(gMainContext, mScriptHandlerFunc);
    }

    bool ScriptTouchEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        if (inEventType != pdg::eventType_SpriteTouch)
        {
            return false;
        }

        SpriteTouchInfo* touchInfo = static_cast<SpriteTouchInfo*>(inEventData);
        if (touchInfo->touchType != mExpectedAction)
        {
            return false;
        }

        JSObjectRef jsEvent = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_emitter) ? symbol_emitter : symbol_emitter = JSStringCreateWithUTF8CString("emitter")), emitter->mEventEmitterScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_eventType) ? symbol_eventType : symbol_eventType = JSStringCreateWithUTF8CString("eventType")), JSValueMakeNumber(ctx, inEventType), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_touchType) ? symbol_touchType : symbol_touchType = JSStringCreateWithUTF8CString("touchType")), JSValueMakeNumber(ctx, touchInfo->touchType), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_touchedSprite) ? symbol_touchedSprite : symbol_touchedSprite = JSStringCreateWithUTF8CString("touchedSprite")), touchInfo->touchedSprite->mSpriteScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_inLayer) ? symbol_inLayer : symbol_inLayer = JSStringCreateWithUTF8CString("inLayer")), touchInfo->inLayer->mSpriteLayerScriptObj, kJSPropertyAttributeNone, exception);

        JSValueRef argv[1];
        argv[0] = jsEvent;

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mIEventHandlerScriptObj, "Dumping " "IEventHandler" " object:") );

        JSObjectRef func;
        if (mScriptHandlerFunc)
        {
            func = mScriptHandlerFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mIEventHandlerScriptObj, ((symbol_handleEvent) ? symbol_handleEvent : symbol_handleEvent = JSStringCreateWithUTF8CString("handleEvent")), exception), exception);
        }

        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mIEventHandlerScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(*exception);
            return false;
        }
        if (!JSValueIsBoolean(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }

    ScriptLayerEventHandler::ScriptLayerEventHandler()
    {
        mScriptHandlerFunc = 0;
        mExpectedAction = 0;
    }

    ScriptLayerEventHandler::ScriptLayerEventHandler(JSObjectRef func, long expectedAction)
    {
        mScriptHandlerFunc = func;
        mExpectedAction = expectedAction;
        JSValueProtect(gMainContext, mScriptHandlerFunc);
    }

    bool ScriptLayerEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        if (inEventType != pdg::eventType_SpriteLayer)
        {
            return false;
        }

        SpriteLayerInfo* layerInfo = static_cast<SpriteLayerInfo*>(inEventData);
        if (layerInfo->action != mExpectedAction)
        {
            return false;
        }

        JSObjectRef jsEvent = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_emitter) ? symbol_emitter : symbol_emitter = JSStringCreateWithUTF8CString("emitter")), emitter->mEventEmitterScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_eventType) ? symbol_eventType : symbol_eventType = JSStringCreateWithUTF8CString("eventType")), JSValueMakeNumber(ctx, inEventType), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_action) ? symbol_action : symbol_action = JSStringCreateWithUTF8CString("action")), JSValueMakeNumber(ctx, layerInfo->action), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_actingLayer) ? symbol_actingLayer : symbol_actingLayer = JSStringCreateWithUTF8CString("actingLayer")), layerInfo->actingLayer->mSpriteLayerScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_millisec) ? symbol_millisec : symbol_millisec = JSStringCreateWithUTF8CString("millisec")), JSValueMakeNumber(ctx, layerInfo->millisec), kJSPropertyAttributeNone, exception);

        JSValueRef argv[1];
        argv[0] = jsEvent;

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mIEventHandlerScriptObj, "Dumping " "IEventHandler" " object:") );

        JSObjectRef func;
        if (mScriptHandlerFunc)
        {
            func = mScriptHandlerFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mIEventHandlerScriptObj, ((symbol_handleEvent) ? symbol_handleEvent : symbol_handleEvent = JSStringCreateWithUTF8CString("handleEvent")), exception), exception);
        }

        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mIEventHandlerScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(*exception);
            return false;
        }
        if (!JSValueIsBoolean(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }

    static JSStringRef symbol_animate = 0;

    ScriptAnimationHelper::ScriptAnimationHelper(JSObjectRef func)
    {
        mScriptAnimateFunc = func;
        JSValueProtect(gMainContext, mScriptAnimateFunc);
    }

    ScriptAnimationHelper::~ScriptAnimationHelper()
    {
        if (mScriptAnimateFunc) JSValueUnprotect(gMainContext, mScriptAnimateFunc);
    }
    void ScriptAnimationHelper::initializeScriptObject()
    {
        if (!mScriptAnimateFunc) return;
        JSStringRef key = JSStringCreateWithUTF8CString("_pdgAnimationCallback");
        JSObjectSetProperty(gMainContext, mIAnimationHelperScriptObj, key, mScriptAnimateFunc,
            kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum | kJSPropertyAttributeDontDelete, nullptr);
        JSStringRelease(key);
        JSValueUnprotect(gMainContext, mScriptAnimateFunc);
        mScriptAnimateFunc = nullptr;
    }
    void ScriptAnimationHelper::retainForAnimation()
    {
        addRef();
        if (mAnimationRetains++ == 0 && mIAnimationHelperScriptObj)
            JSValueProtect(gMainContext, mIAnimationHelperScriptObj);
    }
    void ScriptAnimationHelper::releaseForAnimation()
    {
        if (--mAnimationRetains == 0 && mIAnimationHelperScriptObj)
            JSValueUnprotect(gMainContext, mIAnimationHelperScriptObj);
        release();
    }

    bool ScriptAnimationHelper::animate(AnimatedBase* what, double deltaSeconds) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        JSValueRef argv[2];
        if (!what->mAnimatedScriptObj)
        {
            if (auto* particle = dynamic_cast<Particle*>(what)) Particle_newFromCpp(ctx, particle);
            else if (auto* emission = dynamic_cast<ParticleEmitter*>(what)) ParticleEmitter_newFromCpp(ctx, emission);
            else if (auto* part = dynamic_cast<Part*>(what)) Part_newFromCpp(ctx, part);
            else if (auto* sprite = dynamic_cast<Sprite*>(what)) Sprite_newFromCpp(ctx, sprite);
            else AnimatedBase_newFromCpp(ctx, what);
        }
        argv[0] = what->mAnimatedScriptObj;
        argv[1] = JSValueMakeNumber(ctx, deltaSeconds);

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, what->mAnimatedScriptObj, "Dumping " "AnimatedBase" " object:") );
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mIAnimationHelperScriptObj, "Dumping " "IAnimationHelper" " object:") );

        JSObjectRef func;
        JSStringRef key = JSStringCreateWithUTF8CString("_pdgAnimationCallback");
        JSValueRef callback = JSObjectGetProperty(ctx, mIAnimationHelperScriptObj, key, nullptr);
        JSStringRelease(key);
        if (JSC_ValueIsFunction(ctx, callback, exception))
        {
            func = JSC_ValueToFunction(ctx, callback, exception);
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mIAnimationHelperScriptObj, ((symbol_animate) ? symbol_animate : symbol_animate = JSStringCreateWithUTF8CString("animate")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mIAnimationHelperScriptObj, 2, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Animation Helper!!" ); )
                FatalException(*exception);
            return false;
        }
        if (!JSValueIsBoolean(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from animate helper Function must be a boolean ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }

    ScriptAnimationEventHandler::ScriptAnimationEventHandler()
    {
        mScriptHandlerFunc = 0;
        mExpectedAction = 0;
    }

    ScriptAnimationEventHandler::ScriptAnimationEventHandler(JSObjectRef func, long expectedAction)
    {
        mScriptHandlerFunc = func;
        mExpectedAction = expectedAction;
        JSValueProtect(gMainContext, mScriptHandlerFunc);
    }

    bool ScriptAnimationEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        if (inEventType != pdg::eventType_SpriteAnimate)
        {
            return false;
        }

        SpriteAnimateInfo* animateInfo = static_cast<SpriteAnimateInfo*>(inEventData);
        if (animateInfo->action != mExpectedAction)
        {
            return false;
        }

        if (!animateInfo->actingSprite || !animateInfo->inLayer)
        {
            return false;
        }

        JSObjectRef jsEvent = JSC_ObjectCreateEmpty(ctx, 0);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_emitter) ? symbol_emitter : symbol_emitter = JSStringCreateWithUTF8CString("emitter")), emitter->mEventEmitterScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_eventType) ? symbol_eventType : symbol_eventType = JSStringCreateWithUTF8CString("eventType")), JSValueMakeNumber(ctx, inEventType), kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_action) ? symbol_action : symbol_action = JSStringCreateWithUTF8CString("action")), JSValueMakeNumber(ctx, animateInfo->action), kJSPropertyAttributeNone, exception);
        if(animateInfo->action==Sprite::action_AnimationPhysicsRecoveryComplete)
        {
            const auto* recovery=static_cast<SpriteAnimationPhysicsRecoveryInfo*>(inEventData);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_id) ? symbol_id : symbol_id = JSStringCreateWithUTF8CString("id")), JSValueMakeNumber(ctx, recovery->id), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_bone) ? symbol_bone : symbol_bone = JSStringCreateWithUTF8CString("bone")), JSValueMakeNumber(ctx, recovery->bone), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_wholeRig) ? symbol_wholeRig : symbol_wholeRig = JSStringCreateWithUTF8CString("wholeRig")), JSValueMakeBoolean(ctx, recovery->wholeRig), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_includeDescendants) ? symbol_includeDescendants : symbol_includeDescendants = JSStringCreateWithUTF8CString("includeDescendants")), JSValueMakeBoolean(ctx, recovery->includeDescendants), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_mode) ? symbol_mode : symbol_mode = JSStringCreateWithUTF8CString("mode")), JSValueMakeNumber(ctx, recovery->mode), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_bodyCount) ? symbol_bodyCount : symbol_bodyCount = JSStringCreateWithUTF8CString("bodyCount")), JSValueMakeNumber(ctx, recovery->bodyCount), kJSPropertyAttributeNone, exception);
            JSObjectSetProperty(ctx, jsEvent, ((symbol_disabled) ? symbol_disabled : symbol_disabled = JSStringCreateWithUTF8CString("disabled")), JSValueMakeBoolean(ctx, recovery->disabled), kJSPropertyAttributeNone, exception);
        }

        if (!animateInfo->actingSprite->mSpriteScriptObj)
        {
            return false;
        }
        if (!animateInfo->inLayer->mSpriteLayerScriptObj)
        {
            return false;
        }

        JSObjectSetProperty(ctx, jsEvent, ((symbol_actingSprite) ? symbol_actingSprite : symbol_actingSprite = JSStringCreateWithUTF8CString("actingSprite")), animateInfo->actingSprite->mSpriteScriptObj, kJSPropertyAttributeNone, exception);
        JSObjectSetProperty(ctx, jsEvent, ((symbol_inLayer) ? symbol_inLayer : symbol_inLayer = JSStringCreateWithUTF8CString("inLayer")), animateInfo->inLayer->mSpriteLayerScriptObj, kJSPropertyAttributeNone, exception);

        JSValueRef argv[1];
        argv[0] = jsEvent;

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mIEventHandlerScriptObj, "Dumping " "IEventHandler" " object:") );

        JSObjectRef func;
        if (mScriptHandlerFunc)
        {
            func = mScriptHandlerFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mIEventHandlerScriptObj, ((symbol_handleEvent) ? symbol_handleEvent : symbol_handleEvent = JSStringCreateWithUTF8CString("handleEvent")), exception), exception);
        }

        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mIEventHandlerScriptObj, 1, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
                FatalException(*exception);
            return false;
        }
        if (!JSValueIsBoolean(ctx, resVal))
        {
            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
                << JSC_GetFunctionName(ctx, func) << " at " << JSC_GetFunctionFileAndLine(ctx, func) << ")\n";
                exit(1);
                )
                return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }

    static JSStringRef symbol_allowCollision = 0;

#ifndef PDG_NO_GUI

    static JSStringRef symbol_draw = 0;

    ScriptSpriteDrawHelper::ScriptSpriteDrawHelper(JSObjectRef func)
    {
        mScriptDrawFunc = func;
        JSValueProtect(gMainContext, mScriptDrawFunc);
    }

    bool ScriptSpriteDrawHelper::draw(Sprite* sprite, Port* port) noexcept
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        JSValueRef argv[2];
        argv[0] = sprite->mSpriteScriptObj;
        argv[1] = port->mPortScriptObj;

        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, sprite->mSpriteScriptObj, "Dumping " "Sprite" " object:") );
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, port->mPortScriptObj, "Dumping " "Port" " object:") );
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, this->mISpriteDrawHelperScriptObj, "Dumping " "IDrawSpriteHelper" " object:") );

        JSObjectRef func;
        if (mScriptDrawFunc)
        {
            func = mScriptDrawFunc;
        }
        else
        {
            func = JSC_ValueToFunction(ctx, JSObjectGetProperty(ctx, mISpriteDrawHelperScriptObj, ((symbol_draw) ? symbol_draw : symbol_draw = JSStringCreateWithUTF8CString("draw")), exception), exception);
        }
        JSValueRef resVal = JSObjectCallAsFunction(ctx, func, this->mISpriteDrawHelperScriptObj, 2, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Sprite Draw Helper!!" ); )
                FatalException(*exception);
            return false;
        }
        return JSValueToBoolean(ctx, resVal);
    }
#endif

    static int sNumScriptEasings = 0;

    float CallScriptEasingFunc(int which, double ut, float b, float c, double ud)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (which < 0 || which >= sNumScriptEasings)
        {
#ifdef DEBUG
            std::cerr << "logic error: attempting to call an unregistered easing function #"
                << which << "(only "<< sNumScriptEasings <<" custom easings have been"
                " registered via registerEasingFunction())\n";
            exit(1);
#else
            return 0.0f;
#endif
        }

        JSValueRef argv[4];
        argv[0] = JSValueMakeNumber(ctx, ut);
        argv[1] = JSValueMakeNumber(ctx, b);
        argv[2] = JSValueMakeNumber(ctx, c);
        argv[3] = JSValueMakeNumber(ctx, ud);
        JSValueRef resVal = JSObjectCallAsFunction(ctx, s_CustomJavascriptEasing[which], 0, 4, argv, exception);

        if (resVal == 0 && *exception)
        {
            DEBUG_ONLY( OS::_DOUT( "Javascript Fatal Exception calling Easing Function!!" ); )
                FatalException(*exception);
            return 0.0f;
        }
        if (!JSValueIsNumber(ctx, resVal))
        {

            DEBUG_ONLY(
                std::cerr << "result mismatch: return value from easing Function must be a Number ("
                << JSC_GetFunctionName(ctx, s_CustomJavascriptEasing[which]) << " at "
                << JSC_GetFunctionFileAndLine(ctx, s_CustomJavascriptEasing[which]) << ")\n";
                exit(1);
                )
                return 0.0f;
        }
        return JSValueToNumber(ctx, resVal, 0);
    }

    JSValueRef RegisterEasingFunction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        JSObjectRef easingFunc = JSValueToObject(ctx, arguments[1 -1], exception);
        if (!easingFunc || !JSObjectIsFunction(ctx, easingFunc) )
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""easingFunc"")");
        if (sNumScriptEasings >= MAX_CUSTOM_EASINGS)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Custom easing function capacity exceeded" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        else
        {

            s_CustomJavascriptEasing[sNumScriptEasings] = easingFunc;
            JSValueProtect(ctx, easingFunc);
            const int funcId = NUM_BUILTIN_EASINGS + sNumScriptEasings;
            CallScriptEasingFunc(sNumScriptEasings++, 0, 0.0f, 0.0f, 1);
            return JSValueMakeNumber(ctx, funcId);
        }
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef FinishedScriptSetup(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        scriptSetupCompleted();
        return JSValueMakeUndefined(ctx);
    }

    SCRIPT_DEBUG_ONLY(
        static size_t sLastHeapUsed = 0;
        static ms_time sIdleLastHeapReport = OS::getMilliseconds();
        )

        void initBindings(JSContextRef ctx, JSObjectRef exports)
    {

        easingFuncToId(customEasing0);
        easingFuncToId(customEasing1);
        easingFuncToId(customEasing2);
        easingFuncToId(customEasing3);
        easingFuncToId(customEasing4);
        easingFuncToId(customEasing5);
        easingFuncToId(customEasing6);
        easingFuncToId(customEasing7);
        easingFuncToId(customEasing8);
        easingFuncToId(customEasing9);

        gMainContext = ctx;
        JSValueRef exceptionValue = 0;
        JSValueRef* exception = &exceptionValue;

        JSObjectRef globalObject = exports;

        JSObjectRef MemBlockNativeConstructor = JSObjectMakeConstructor(ctx, MemBlock_class(), MemBlock_new);
        JSObjectRef MemBlockObj = JSC_CreateClassConstructor(ctx, "MemBlock", MemBlockNativeConstructor, 0);
        JSC_RegisterClassConstructor(MemBlock_class(), MemBlockObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("MemBlock"), MemBlockObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef FileManagerNativeConstructor = JSObjectMakeConstructor(ctx, FileManager_class(), FileManager_new);
        JSObjectRef FileManagerObj = JSC_CreateClassConstructor(ctx, "FileManager", FileManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(FileManager_class(), FileManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("FileManager"), FileManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef LogManagerNativeConstructor = JSObjectMakeConstructor(ctx, LogManager_class(), LogManager_new);
        JSObjectRef LogManagerObj = JSC_CreateClassConstructor(ctx, "LogManager", LogManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(LogManager_class(), LogManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("LogManager"), LogManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ConfigManagerNativeConstructor = JSObjectMakeConstructor(ctx, ConfigManager_class(), ConfigManager_new);
        JSObjectRef ConfigManagerObj = JSC_CreateClassConstructor(ctx, "ConfigManager", ConfigManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(ConfigManager_class(), ConfigManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ConfigManager"), ConfigManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ResourceManagerNativeConstructor = JSObjectMakeConstructor(ctx, ResourceManager_class(), ResourceManager_new);
        JSObjectRef ResourceManagerObj = JSC_CreateClassConstructor(ctx, "ResourceManager", ResourceManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(ResourceManager_class(), ResourceManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ResourceManager"), ResourceManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef SerializerNativeConstructor = JSObjectMakeConstructor(ctx, Serializer_class(), Serializer_new);
        JSObjectRef SerializerObj = JSC_CreateClassConstructor(ctx, "Serializer", SerializerNativeConstructor, 0);
        JSC_RegisterClassConstructor(Serializer_class(), SerializerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Serializer"), SerializerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef DeserializerNativeConstructor = JSObjectMakeConstructor(ctx, Deserializer_class(), Deserializer_new);
        JSObjectRef DeserializerObj = JSC_CreateClassConstructor(ctx, "Deserializer", DeserializerNativeConstructor, 0);
        JSC_RegisterClassConstructor(Deserializer_class(), DeserializerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Deserializer"), DeserializerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ISerializableNativeConstructor = JSObjectMakeConstructor(ctx, ISerializable_class(), ISerializable_new);
        JSObjectRef ISerializableObj = JSC_CreateClassConstructor(ctx, "ISerializable", ISerializableNativeConstructor, 0);
        JSC_RegisterClassConstructor(ISerializable_class(), ISerializableObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ISerializable"), ISerializableObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef IEventHandlerNativeConstructor = JSObjectMakeConstructor(ctx, IEventHandler_class(), IEventHandler_new);
        JSObjectRef IEventHandlerObj = JSC_CreateClassConstructor(ctx, "IEventHandler", IEventHandlerNativeConstructor, 0);
        JSC_RegisterClassConstructor(IEventHandler_class(), IEventHandlerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("IEventHandler"), IEventHandlerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef EventEmitterNativeConstructor = JSObjectMakeConstructor(ctx, EventEmitter_class(), EventEmitter_new);
        JSObjectRef EventEmitterObj = JSC_CreateClassConstructor(ctx, "EventEmitter", EventEmitterNativeConstructor, 0);
        JSC_RegisterClassConstructor(EventEmitter_class(), EventEmitterObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("EventEmitter"), EventEmitterObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef EventManagerNativeConstructor = JSObjectMakeConstructor(ctx, EventManager_class(), EventManager_new);
        JSObjectRef EventManagerObj = JSC_CreateClassConstructor(ctx, "EventManager", EventManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(EventManager_class(), EventManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("EventManager"), EventManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef TimerManagerNativeConstructor = JSObjectMakeConstructor(ctx, TimerManager_class(), TimerManager_new);
        JSObjectRef TimerManagerObj = JSC_CreateClassConstructor(ctx, "TimerManager", TimerManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(TimerManager_class(), TimerManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("TimerManager"), TimerManagerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef IAnimationHelperNativeConstructor = JSObjectMakeConstructor(ctx, IAnimationHelper_class(), IAnimationHelper_new);
        JSObjectRef IAnimationHelperObj = JSC_CreateClassConstructor(ctx, "IAnimationHelper", IAnimationHelperNativeConstructor, 0);
        JSC_RegisterClassConstructor(IAnimationHelper_class(), IAnimationHelperObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("IAnimationHelper"), IAnimationHelperObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef AnimatedBaseNativeConstructor = JSObjectMakeConstructor(ctx, AnimatedBase_class(), AnimatedBase_new);
        JSObjectRef AnimatedBaseObj = JSC_CreateClassConstructor(ctx, "Animated", AnimatedBaseNativeConstructor, 0);
        JSC_RegisterClassConstructor(AnimatedBase_class(), AnimatedBaseObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Animated"), AnimatedBaseObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef PartNativeConstructor = JSObjectMakeConstructor(ctx, Part_class(), Part_new);
        JSObjectRef PartObj = JSC_CreateClassConstructor(ctx, "Part", PartNativeConstructor, 0);
        JSC_RegisterClassConstructor(Part_class(), PartObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Part"), PartObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ParticleNativeConstructor = JSObjectMakeConstructor(ctx, Particle_class(), Particle_new);
        JSObjectRef ParticleObj = JSC_CreateClassConstructor(ctx, "Particle", ParticleNativeConstructor, 0);
        JSC_RegisterClassConstructor(Particle_class(), ParticleObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Particle"), ParticleObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ParticleEmitterNativeConstructor = JSObjectMakeConstructor(ctx, ParticleEmitter_class(), ParticleEmitter_new);
        JSObjectRef ParticleEmitterObj = JSC_CreateClassConstructor(ctx, "ParticleEmitter", ParticleEmitterNativeConstructor, 0);
        JSC_RegisterClassConstructor(ParticleEmitter_class(), ParticleEmitterObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ParticleEmitter"), ParticleEmitterObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef PhysicsBodyNativeConstructor = JSObjectMakeConstructor(ctx, PhysicsBody_class(), PhysicsBody_new);
        JSObjectRef PhysicsBodyObj = JSC_CreateClassConstructor(ctx, "PhysicsBody", PhysicsBodyNativeConstructor, 0);
        JSC_RegisterClassConstructor(PhysicsBody_class(), PhysicsBodyObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("PhysicsBody"), PhysicsBodyObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ColliderNativeConstructor = JSObjectMakeConstructor(ctx, Collider_class(), Collider_new);
        JSObjectRef ColliderObj = JSC_CreateClassConstructor(ctx, "Collider", ColliderNativeConstructor, 0);
        JSC_RegisterClassConstructor(Collider_class(), ColliderObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Collider"), ColliderObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef PhysicsConstraintNativeConstructor = JSObjectMakeConstructor(ctx, PhysicsConstraint_class(), PhysicsConstraint_new);
        JSObjectRef PhysicsConstraintObj = JSC_CreateClassConstructor(ctx, "PhysicsConstraint", PhysicsConstraintNativeConstructor, 0);
        JSC_RegisterClassConstructor(PhysicsConstraint_class(), PhysicsConstraintObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("PhysicsConstraint"), PhysicsConstraintObj, kJSPropertyAttributeNone, NULL);
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        JSObjectRef cpArbiterNativeConstructor = JSObjectMakeConstructor(ctx, cpArbiter_class(), cpArbiter_new);
        JSObjectRef cpArbiterObj = JSC_CreateClassConstructor(ctx, "cpArbiter", cpArbiterNativeConstructor, 0);
        JSC_RegisterClassConstructor(cpArbiter_class(), cpArbiterObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("cpArbiter"), cpArbiterObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef cpConstraintNativeConstructor = JSObjectMakeConstructor(ctx, cpConstraint_class(), cpConstraint_new);
        JSObjectRef cpConstraintObj = JSC_CreateClassConstructor(ctx, "cpConstraint", cpConstraintNativeConstructor, 0);
        JSC_RegisterClassConstructor(cpConstraint_class(), cpConstraintObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("cpConstraint"), cpConstraintObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef cpSpaceNativeConstructor = JSObjectMakeConstructor(ctx, cpSpace_class(), cpSpace_new);
        JSObjectRef cpSpaceObj = JSC_CreateClassConstructor(ctx, "cpSpace", cpSpaceNativeConstructor, 0);
        JSC_RegisterClassConstructor(cpSpace_class(), cpSpaceObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("cpSpace"), cpSpaceObj, kJSPropertyAttributeNone, NULL);
#endif
#ifndef PDG_NO_GUI
        JSObjectRef ISpriteDrawHelperNativeConstructor = JSObjectMakeConstructor(ctx, ISpriteDrawHelper_class(), ISpriteDrawHelper_new);
        JSObjectRef ISpriteDrawHelperObj = JSC_CreateClassConstructor(ctx, "ISpriteDrawHelper", ISpriteDrawHelperNativeConstructor, 0);
        JSC_RegisterClassConstructor(ISpriteDrawHelper_class(), ISpriteDrawHelperObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ISpriteDrawHelper"), ISpriteDrawHelperObj, kJSPropertyAttributeNone, NULL);
#endif
        JSObjectRef SpriteNativeConstructor = JSObjectMakeConstructor(ctx, Sprite_class(), Sprite_new);
        JSObjectRef SpriteObj = JSC_CreateClassConstructor(ctx, "Sprite", SpriteNativeConstructor, 0);
        JSC_RegisterClassConstructor(Sprite_class(), SpriteObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Sprite"), SpriteObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef SpriteLayerNativeConstructor = JSObjectMakeConstructor(ctx, SpriteLayer_class(), SpriteLayer_new);
        JSObjectRef SpriteLayerObj = JSC_CreateClassConstructor(ctx, "SpriteLayer", SpriteLayerNativeConstructor, 0);
        JSC_RegisterClassConstructor(SpriteLayer_class(), SpriteLayerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("SpriteLayer"), SpriteLayerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef TileLayerNativeConstructor = JSObjectMakeConstructor(ctx, TileLayer_class(), TileLayer_new);
        JSObjectRef TileLayerObj = JSC_CreateClassConstructor(ctx, "TileLayer", TileLayerNativeConstructor, 0);
        JSC_RegisterClassConstructor(TileLayer_class(), TileLayerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("TileLayer"), TileLayerObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ImageNativeConstructor = JSObjectMakeConstructor(ctx, Image_class(), Image_new);
        JSObjectRef ImageObj = JSC_CreateClassConstructor(ctx, "Image", ImageNativeConstructor, 0);
        JSC_RegisterClassConstructor(Image_class(), ImageObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Image"), ImageObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ImageStripNativeConstructor = JSObjectMakeConstructor(ctx, ImageStrip_class(), ImageStrip_new);
        JSObjectRef ImageStripObj = JSC_CreateClassConstructor(ctx, "ImageStrip", ImageStripNativeConstructor, 0);
        JSC_RegisterClassConstructor(ImageStrip_class(), ImageStripObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ImageStrip"), ImageStripObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef SplineNativeConstructor = JSObjectMakeConstructor(ctx, Spline_class(), Spline_new);
        JSObjectRef SplineObj = JSC_CreateClassConstructor(ctx, "Spline", SplineNativeConstructor, 0);
        JSC_RegisterClassConstructor(Spline_class(), SplineObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Spline"), SplineObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef PolygonNativeConstructor = JSObjectMakeConstructor(ctx, Polygon_class(), Polygon_new);
        JSObjectRef PolygonObj = JSC_CreateClassConstructor(ctx, "Polygon", PolygonNativeConstructor, 0);
        JSC_RegisterClassConstructor(Polygon_class(), PolygonObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Polygon"), PolygonObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef AttributesNativeConstructor = JSObjectMakeConstructor(ctx, Attributes_class(), Attributes_new);
        JSObjectRef AttributesObj = JSC_CreateClassConstructor(ctx, "Attributes", AttributesNativeConstructor, 0);
        JSC_RegisterClassConstructor(Attributes_class(), AttributesObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Attributes"), AttributesObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef AnimatedAttributesBaseNativeConstructor = JSObjectMakeConstructor(ctx, AnimatedAttributesBase_class(), AnimatedAttributesBase_new);
        JSObjectRef AnimatedAttributesBaseObj = JSC_CreateClassConstructor(ctx, "AnimatedAttributes", AnimatedAttributesBaseNativeConstructor, 0);
        JSC_RegisterClassConstructor(AnimatedAttributesBase_class(), AnimatedAttributesBaseObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("AnimatedAttributes"), AnimatedAttributesBaseObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef ElementRefNativeConstructor = JSObjectMakeConstructor(ctx, ElementRef_class(), ElementRef_new);
        JSObjectRef ElementRefObj = JSC_CreateClassConstructor(ctx, "ElementRef", ElementRefNativeConstructor, 0);
        JSC_RegisterClassConstructor(ElementRef_class(), ElementRefObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ElementRef"), ElementRefObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef DrawingNativeConstructor = JSObjectMakeConstructor(ctx, Drawing_class(), Drawing_new);
        JSObjectRef DrawingObj = JSC_CreateClassConstructor(ctx, "Drawing", DrawingNativeConstructor, 0);
        JSC_RegisterClassConstructor(Drawing_class(), DrawingObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Drawing"), DrawingObj, kJSPropertyAttributeNone, NULL);
#ifndef PDG_NO_GUI
        JSObjectRef FontNativeConstructor = JSObjectMakeConstructor(ctx, Font_class(), Font_new);
        JSObjectRef FontObj = JSC_CreateClassConstructor(ctx, "Font", FontNativeConstructor, 0);
        JSC_RegisterClassConstructor(Font_class(), FontObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Font"), FontObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef PortNativeConstructor = JSObjectMakeConstructor(ctx, Port_class(), Port_new);
        JSObjectRef PortObj = JSC_CreateClassConstructor(ctx, "Port", PortNativeConstructor, 0);
        JSC_RegisterClassConstructor(Port_class(), PortObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Port"), PortObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef GraphicsManagerNativeConstructor = JSObjectMakeConstructor(ctx, GraphicsManager_class(), GraphicsManager_new);
        JSObjectRef GraphicsManagerObj = JSC_CreateClassConstructor(ctx, "GraphicsManager", GraphicsManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(GraphicsManager_class(), GraphicsManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("GraphicsManager"), GraphicsManagerObj, kJSPropertyAttributeNone, NULL);
#endif
#ifndef PDG_NO_SOUND
        JSObjectRef SoundNativeConstructor = JSObjectMakeConstructor(ctx, Sound_class(), Sound_new);
        JSObjectRef SoundObj = JSC_CreateClassConstructor(ctx, "Sound", SoundNativeConstructor, 0);
        JSC_RegisterClassConstructor(Sound_class(), SoundObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("Sound"), SoundObj, kJSPropertyAttributeNone, NULL);
        JSObjectRef SoundManagerNativeConstructor = JSObjectMakeConstructor(ctx, SoundManager_class(), SoundManager_new);
        JSObjectRef SoundManagerObj = JSC_CreateClassConstructor(ctx, "SoundManager", SoundManagerNativeConstructor, 0);
        JSC_RegisterClassConstructor(SoundManager_class(), SoundManagerObj);
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("SoundManager"), SoundManagerObj, kJSPropertyAttributeNone, NULL);
#endif

        JSStringRef IdleName = JSStringCreateWithUTF8CString("_idle");
        JSObjectRef IdleRef = JSObjectMakeFunctionWithCallback(ctx, IdleName, Idle);
        JSObjectSetProperty(ctx, globalObject, IdleName, IdleRef, kJSPropertyAttributeNone, exception);;
        JSStringRef RunName = JSStringCreateWithUTF8CString("_run");
        JSObjectRef RunRef = JSObjectMakeFunctionWithCallback(ctx, RunName, Run);
        JSObjectSetProperty(ctx, globalObject, RunName, RunRef, kJSPropertyAttributeNone, exception);;
        JSStringRef QuitName = JSStringCreateWithUTF8CString("_quit");
        JSObjectRef QuitRef = JSObjectMakeFunctionWithCallback(ctx, QuitName, Quit);
        JSObjectSetProperty(ctx, globalObject, QuitName, QuitRef, kJSPropertyAttributeNone, exception);;
        JSStringRef IsQuittingName = JSStringCreateWithUTF8CString("_isQuitting");
        JSObjectRef IsQuittingRef = JSObjectMakeFunctionWithCallback(ctx, IsQuittingName, IsQuitting);
        JSObjectSetProperty(ctx, globalObject, IsQuittingName, IsQuittingRef, kJSPropertyAttributeNone, exception);;
        JSStringRef FinishedScriptSetupName = JSStringCreateWithUTF8CString("_finishedScriptSetup");
        JSObjectRef FinishedScriptSetupRef = JSObjectMakeFunctionWithCallback(ctx, FinishedScriptSetupName, FinishedScriptSetup);
        JSObjectSetProperty(ctx, globalObject, FinishedScriptSetupName, FinishedScriptSetupRef, kJSPropertyAttributeNone, exception);;

        JSStringRef GameCriticalRandomName = JSStringCreateWithUTF8CString("rand");
        JSObjectRef GameCriticalRandomRef = JSObjectMakeFunctionWithCallback(ctx, GameCriticalRandomName, GameCriticalRandom);
        JSObjectSetProperty(ctx, globalObject, GameCriticalRandomName, GameCriticalRandomRef, kJSPropertyAttributeNone, exception);;
        JSStringRef SrandName = JSStringCreateWithUTF8CString("srand");
        JSObjectRef SrandRef = JSObjectMakeFunctionWithCallback(ctx, SrandName, Srand);
        JSObjectSetProperty(ctx, globalObject, SrandName, SrandRef, kJSPropertyAttributeNone, exception);;

        JSStringRef SetSerializationDebugModeName = JSStringCreateWithUTF8CString("setSerializationDebugMode");
        JSObjectRef SetSerializationDebugModeRef = JSObjectMakeFunctionWithCallback(ctx, SetSerializationDebugModeName, SetSerializationDebugMode);
        JSObjectSetProperty(ctx, globalObject, SetSerializationDebugModeName, SetSerializationDebugModeRef, kJSPropertyAttributeNone, exception);;

        JSStringRef RegisterEasingFunctionName = JSStringCreateWithUTF8CString("registerEasingFunction");
        JSObjectRef RegisterEasingFunctionRef = JSObjectMakeFunctionWithCallback(ctx, RegisterEasingFunctionName, RegisterEasingFunction);
        JSObjectSetProperty(ctx, globalObject, RegisterEasingFunctionName, RegisterEasingFunctionRef, kJSPropertyAttributeNone, exception);;

        JSStringRef GetFileManagerName = JSStringCreateWithUTF8CString("getFileManager");
        JSObjectRef GetFileManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetFileManagerName, GetFileManager);
        JSObjectSetProperty(ctx, globalObject, GetFileManagerName, GetFileManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef GetLogManagerName = JSStringCreateWithUTF8CString("getLogManager");
        JSObjectRef GetLogManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetLogManagerName, GetLogManager);
        JSObjectSetProperty(ctx, globalObject, GetLogManagerName, GetLogManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef GetConfigManagerName = JSStringCreateWithUTF8CString("getConfigManager");
        JSObjectRef GetConfigManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetConfigManagerName, GetConfigManager);
        JSObjectSetProperty(ctx, globalObject, GetConfigManagerName, GetConfigManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef GetResourceManagerName = JSStringCreateWithUTF8CString("getResourceManager");
        JSObjectRef GetResourceManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetResourceManagerName, GetResourceManager);
        JSObjectSetProperty(ctx, globalObject, GetResourceManagerName, GetResourceManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef GetEventManagerName = JSStringCreateWithUTF8CString("getEventManager");
        JSObjectRef GetEventManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetEventManagerName, GetEventManager);
        JSObjectSetProperty(ctx, globalObject, GetEventManagerName, GetEventManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef GetTimerManagerName = JSStringCreateWithUTF8CString("getTimerManager");
        JSObjectRef GetTimerManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetTimerManagerName, GetTimerManager);
        JSObjectSetProperty(ctx, globalObject, GetTimerManagerName, GetTimerManagerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef RegisterSerializableClassName = JSStringCreateWithUTF8CString("registerSerializableClass");
        JSObjectRef RegisterSerializableClassRef = JSObjectMakeFunctionWithCallback(ctx, RegisterSerializableClassName, RegisterSerializableClass);
        JSObjectSetProperty(ctx, globalObject, RegisterSerializableClassName, RegisterSerializableClassRef, kJSPropertyAttributeNone, exception);;

#ifndef PDG_NO_GUI
        JSStringRef GetGraphicsManagerName = JSStringCreateWithUTF8CString("getGraphicsManager");
        JSObjectRef GetGraphicsManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetGraphicsManagerName, GetGraphicsManager);
        JSObjectSetProperty(ctx, globalObject, GetGraphicsManagerName, GetGraphicsManagerRef, kJSPropertyAttributeNone, exception);;
#endif
#ifndef PDG_NO_SOUND
        JSStringRef GetSoundManagerName = JSStringCreateWithUTF8CString("getSoundManager");
        JSObjectRef GetSoundManagerRef = JSObjectMakeFunctionWithCallback(ctx, GetSoundManagerName, GetSoundManager);
        JSObjectSetProperty(ctx, globalObject, GetSoundManagerName, GetSoundManagerRef, kJSPropertyAttributeNone, exception);;
#endif

        JSStringRef CreateSpriteLayerName = JSStringCreateWithUTF8CString("createSpriteLayer");
        JSObjectRef CreateSpriteLayerRef = JSObjectMakeFunctionWithCallback(ctx, CreateSpriteLayerName, CreateSpriteLayer);
        JSObjectSetProperty(ctx, globalObject, CreateSpriteLayerName, CreateSpriteLayerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef CleanupLayerName = JSStringCreateWithUTF8CString("cleanupLayer");
        JSObjectRef CleanupLayerRef = JSObjectMakeFunctionWithCallback(ctx, CleanupLayerName, CleanupLayer);
        JSObjectSetProperty(ctx, globalObject, CleanupLayerName, CleanupLayerRef, kJSPropertyAttributeNone, exception);;
#ifdef PDG_SPRITER_SUPPORT
        JSStringRef CreateSpriteLayerFromSpriterFileName = JSStringCreateWithUTF8CString("createSpriteLayerFromSpriterFile");
        JSObjectRef CreateSpriteLayerFromSpriterFileRef = JSObjectMakeFunctionWithCallback(ctx, CreateSpriteLayerFromSpriterFileName, CreateSpriteLayerFromSpriterFile);
        JSObjectSetProperty(ctx, globalObject, CreateSpriteLayerFromSpriterFileName, CreateSpriteLayerFromSpriterFileRef, kJSPropertyAttributeNone, exception);;
#endif
        JSStringRef CreateTileLayerName = JSStringCreateWithUTF8CString("createTileLayer");
        JSObjectRef CreateTileLayerRef = JSObjectMakeFunctionWithCallback(ctx, CreateTileLayerName, CreateTileLayer);
        JSObjectSetProperty(ctx, globalObject, CreateTileLayerName, CreateTileLayerRef, kJSPropertyAttributeNone, exception);;
        JSStringRef CreateDrawingName = JSStringCreateWithUTF8CString("createDrawing");
        JSObjectRef CreateDrawingRef = JSObjectMakeFunctionWithCallback(ctx, CreateDrawingName, CreateDrawing);
        JSObjectSetProperty(ctx, globalObject, CreateDrawingName, CreateDrawingRef, kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("all_events"), JSValueMakeNumber(ctx, all_events), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_Shutdown"), JSValueMakeNumber(ctx, eventType_Shutdown), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_Timer"), JSValueMakeNumber(ctx, eventType_Timer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_KeyDown"), JSValueMakeNumber(ctx, eventType_KeyDown), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_KeyUp"), JSValueMakeNumber(ctx, eventType_KeyUp), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_KeyPress"), JSValueMakeNumber(ctx, eventType_KeyPress), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_MouseDown"), JSValueMakeNumber(ctx, eventType_MouseDown), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_MouseUp"), JSValueMakeNumber(ctx, eventType_MouseUp), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_MouseMove"), JSValueMakeNumber(ctx, eventType_MouseMove), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_MouseEnter"), JSValueMakeNumber(ctx, eventType_MouseEnter), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_MouseLeave"), JSValueMakeNumber(ctx, eventType_MouseLeave), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_PortResized"), JSValueMakeNumber(ctx, eventType_PortResized), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_ScrollWheel"), JSValueMakeNumber(ctx, eventType_ScrollWheel), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteTouch"), JSValueMakeNumber(ctx, eventType_SpriteTouch), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteAnimate"), JSValueMakeNumber(ctx, eventType_SpriteAnimate), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteTriggerEvent"), JSValueMakeNumber(ctx, eventType_SpriteTriggerEvent), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteLayer"), JSValueMakeNumber(ctx, eventType_SpriteLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteCollide"), JSValueMakeNumber(ctx, eventType_SpriteCollide), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_Polygon"), JSValueMakeNumber(ctx, collisionShape_Polygon), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_ImageMask"), JSValueMakeNumber(ctx, collisionShape_ImageMask), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_Capsule"), JSValueMakeNumber(ctx, collisionShape_Capsule), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("colliderSource_Explicit"), JSValueMakeNumber(ctx, colliderSource_Explicit), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("colliderSource_Frame"), JSValueMakeNumber(ctx, colliderSource_Frame), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("colliderSource_Animation"), JSValueMakeNumber(ctx, colliderSource_Animation), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("frameCollider_Bounds"), JSValueMakeNumber(ctx, frameCollider_Bounds), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("frameCollider_AlphaMask"), JSValueMakeNumber(ctx, frameCollider_AlphaMask), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_ColliderContact"), JSValueMakeNumber(ctx, eventType_ColliderContact), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_ParticleBreak"), JSValueMakeNumber(ctx, eventType_ParticleBreak), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SpriteBreak"), JSValueMakeNumber(ctx, eventType_SpriteBreak), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_SoundEvent"), JSValueMakeNumber(ctx, eventType_SoundEvent), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("eventType_PortDraw"), JSValueMakeNumber(ctx, eventType_PortDraw), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("soundEvent_DonePlaying"), JSValueMakeNumber(ctx, soundEvent_DonePlaying), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("soundEvent_Looping"), JSValueMakeNumber(ctx, soundEvent_Looping), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("soundEvent_FailedToPlay"), JSValueMakeNumber(ctx, soundEvent_FailedToPlay), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Break"), JSValueMakeNumber(ctx, key_Break), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Home"), JSValueMakeNumber(ctx, key_Home), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_End"), JSValueMakeNumber(ctx, key_End), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Clear"), JSValueMakeNumber(ctx, key_Clear), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Help"), JSValueMakeNumber(ctx, key_Help), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Pause"), JSValueMakeNumber(ctx, key_Pause), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Mute"), JSValueMakeNumber(ctx, key_Mute), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Backspace"), JSValueMakeNumber(ctx, key_Backspace), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Delete"), JSValueMakeNumber(ctx, key_Delete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Tab"), JSValueMakeNumber(ctx, key_Tab), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_PageUp"), JSValueMakeNumber(ctx, key_PageUp), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_PageDown"), JSValueMakeNumber(ctx, key_PageDown), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Return"), JSValueMakeNumber(ctx, key_Return), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Enter"), JSValueMakeNumber(ctx, key_Enter), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F1"), JSValueMakeNumber(ctx, key_F1), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F2"), JSValueMakeNumber(ctx, key_F2), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F3"), JSValueMakeNumber(ctx, key_F3), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F4"), JSValueMakeNumber(ctx, key_F4), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F5"), JSValueMakeNumber(ctx, key_F5), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F6"), JSValueMakeNumber(ctx, key_F6), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F7"), JSValueMakeNumber(ctx, key_F7), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F8"), JSValueMakeNumber(ctx, key_F8), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F9"), JSValueMakeNumber(ctx, key_F9), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F10"), JSValueMakeNumber(ctx, key_F10), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F11"), JSValueMakeNumber(ctx, key_F11), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_F12"), JSValueMakeNumber(ctx, key_F12), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_FirstF"), JSValueMakeNumber(ctx, key_FirstF), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_LastF"), JSValueMakeNumber(ctx, key_LastF), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Insert"), JSValueMakeNumber(ctx, key_Insert), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_Escape"), JSValueMakeNumber(ctx, key_Escape), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_LeftArrow"), JSValueMakeNumber(ctx, key_LeftArrow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_RightArrow"), JSValueMakeNumber(ctx, key_RightArrow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_UpArrow"), JSValueMakeNumber(ctx, key_UpArrow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_DownArrow"), JSValueMakeNumber(ctx, key_DownArrow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("key_FirstPrintable"), JSValueMakeNumber(ctx, key_FirstPrintable), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_LeftShift"), JSValueMakeNumber(ctx, keyCode_LeftShift), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_RightShift"), JSValueMakeNumber(ctx, keyCode_RightShift), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_LeftControl"), JSValueMakeNumber(ctx, keyCode_LeftControl), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_RightControl"), JSValueMakeNumber(ctx, keyCode_RightControl), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_LeftAlt"), JSValueMakeNumber(ctx, keyCode_LeftAlt), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_RightAlt"), JSValueMakeNumber(ctx, keyCode_RightAlt), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_LeftMeta"), JSValueMakeNumber(ctx, keyCode_LeftMeta), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_RightMeta"), JSValueMakeNumber(ctx, keyCode_RightMeta), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_Shift"), JSValueMakeNumber(ctx, keyCode_Shift), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_Control"), JSValueMakeNumber(ctx, keyCode_Control), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_Alt"), JSValueMakeNumber(ctx, keyCode_Alt), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("keyCode_Meta"), JSValueMakeNumber(ctx, keyCode_Meta), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_Normal"), JSValueMakeNumber(ctx, screenPos_Normal), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_Rotated180"), JSValueMakeNumber(ctx, screenPos_Rotated180), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_Rotated90Clockwise"), JSValueMakeNumber(ctx, screenPos_Rotated90Clockwise), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_Rotated90CounterClockwise"), JSValueMakeNumber(ctx, screenPos_Rotated90CounterClockwise), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_FaceUp"), JSValueMakeNumber(ctx, screenPos_FaceUp), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("screenPos_FaceDown"), JSValueMakeNumber(ctx, screenPos_FaceDown), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_Plain"), JSValueMakeNumber(ctx, textStyle_Plain), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_Bold"), JSValueMakeNumber(ctx, textStyle_Bold), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_Italic"), JSValueMakeNumber(ctx, textStyle_Italic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_Underline"), JSValueMakeNumber(ctx, textStyle_Underline), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_Centered"), JSValueMakeNumber(ctx, textStyle_Centered), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_LeftJustified"), JSValueMakeNumber(ctx, textStyle_LeftJustified), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("textStyle_RightJustified"), JSValueMakeNumber(ctx, textStyle_RightJustified), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_Auto"), JSValueMakeNumber(ctx, lineStyle_Auto), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_None"), JSValueMakeNumber(ctx, lineStyle_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_Solid"), JSValueMakeNumber(ctx, lineStyle_Solid), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_Dashed"), JSValueMakeNumber(ctx, lineStyle_Dashed), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_Dotted"), JSValueMakeNumber(ctx, lineStyle_Dotted), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_DashDot"), JSValueMakeNumber(ctx, lineStyle_DashDot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("lineStyle_DashDotDot"), JSValueMakeNumber(ctx, lineStyle_DashDotDot), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Normal"), JSValueMakeNumber(ctx, blendMode_Normal), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Additive"), JSValueMakeNumber(ctx, blendMode_Additive), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Multiply"), JSValueMakeNumber(ctx, blendMode_Multiply), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Screen"), JSValueMakeNumber(ctx, blendMode_Screen), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Darken"), JSValueMakeNumber(ctx, blendMode_Darken), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("blendMode_Lighten"), JSValueMakeNumber(ctx, blendMode_Lighten), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Line"), JSValueMakeNumber(ctx, type_Line), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Spline"), JSValueMakeNumber(ctx, type_Spline), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Arc"), JSValueMakeNumber(ctx, type_Arc), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Rect"), JSValueMakeNumber(ctx, type_Rect), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Quad"), JSValueMakeNumber(ctx, type_Quad), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Polygon"), JSValueMakeNumber(ctx, type_Polygon), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Ellipse"), JSValueMakeNumber(ctx, type_Ellipse), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Image"), JSValueMakeNumber(ctx, type_Image), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_ImageStrip"), JSValueMakeNumber(ctx, type_ImageStrip), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("type_Drawing"), JSValueMakeNumber(ctx, type_Drawing), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("gradientType_None"), JSValueMakeNumber(ctx, gradientType_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("gradientType_Linear"), JSValueMakeNumber(ctx, gradientType_Linear), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("gradientType_Radial"), JSValueMakeNumber(ctx, gradientType_Radial), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_None"), JSValueMakeNumber(ctx, fit_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Fill"), JSValueMakeNumber(ctx, fit_Fill), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Height"), JSValueMakeNumber(ctx, fit_Height), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Width"), JSValueMakeNumber(ctx, fit_Width), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Inside"), JSValueMakeNumber(ctx, fit_Inside), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Overflow"), JSValueMakeNumber(ctx, fit_Overflow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_FillKeepProportions"), JSValueMakeNumber(ctx, fit_Overflow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Clipped"), JSValueMakeNumber(ctx, fit_Clipped), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_TileX"), JSValueMakeNumber(ctx, fit_TileX), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_TileY"), JSValueMakeNumber(ctx, fit_TileY), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("fit_Tile"), JSValueMakeNumber(ctx, fit_Tile), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("init_CreateUniqueNewFile"), JSValueMakeNumber(ctx, LogManager::init_CreateUniqueNewFile), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("init_OverwriteExisting"), JSValueMakeNumber(ctx, LogManager::init_OverwriteExisting), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("init_AppendToExisting"), JSValueMakeNumber(ctx, LogManager::init_AppendToExisting), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("init_StdOut"), JSValueMakeNumber(ctx, LogManager::init_StdOut), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("init_StdErr"), JSValueMakeNumber(ctx, LogManager::init_StdErr), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partId_None"), JSValueMakeNumber(ctx, partId_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("boneId_None"), JSValueMakeNumber(ctx, boneId_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBody_None"), JSValueMakeNumber(ctx, physicsBody_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBody_Dynamic"), JSValueMakeNumber(ctx, physicsBody_Dynamic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBody_Kinematic"), JSValueMakeNumber(ctx, physicsBody_Kinematic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBody_Static"), JSValueMakeNumber(ctx, physicsBody_Static), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsSolver_None"), JSValueMakeNumber(ctx, physicsSolver_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsSolver_Basic"), JSValueMakeNumber(ctx, physicsSolver_Basic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsSolver_Chipmunk"), JSValueMakeNumber(ctx, physicsSolver_Chipmunk), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsForce_None"), JSValueMakeNumber(ctx, physicsForce_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_None"), JSValueMakeNumber(ctx, collisionShape_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_Circle"), JSValueMakeNumber(ctx, collisionShape_Circle), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collisionShape_Convex"), JSValueMakeNumber(ctx, collisionShape_Convex), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collision_Begin"), JSValueMakeNumber(ctx, collision_Begin), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collision_Stay"), JSValueMakeNumber(ctx, collision_Stay), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collision_End"), JSValueMakeNumber(ctx, collision_End), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Pin"), JSValueMakeNumber(ctx, constraint_Pin), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Slide"), JSValueMakeNumber(ctx, constraint_Slide), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Pivot"), JSValueMakeNumber(ctx, constraint_Pivot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Groove"), JSValueMakeNumber(ctx, constraint_Groove), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Spring"), JSValueMakeNumber(ctx, constraint_Spring), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_RotarySpring"), JSValueMakeNumber(ctx, constraint_RotarySpring), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_RotaryLimit"), JSValueMakeNumber(ctx, constraint_RotaryLimit), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Ratchet"), JSValueMakeNumber(ctx, constraint_Ratchet), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Gear"), JSValueMakeNumber(ctx, constraint_Gear), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("constraint_Motor"), JSValueMakeNumber(ctx, constraint_Motor), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partSpace_Local"), JSValueMakeNumber(ctx, partSpace_Local), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partSpace_Sprite"), JSValueMakeNumber(ctx, partSpace_Sprite), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partSpace_World"), JSValueMakeNumber(ctx, partSpace_World), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partPlacement_Snap"), JSValueMakeNumber(ctx, partPlacement_Snap), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("partPlacement_PreserveWorld"), JSValueMakeNumber(ctx, partPlacement_PreserveWorld), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("rotationDirection_AsSpecified"), JSValueMakeNumber(ctx, rotationDirection_AsSpecified), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("rotationDirection_Shortest"), JSValueMakeNumber(ctx, rotationDirection_Shortest), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("rotationDirection_Clockwise"), JSValueMakeNumber(ctx, rotationDirection_Clockwise), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("rotationDirection_CounterClockwise"), JSValueMakeNumber(ctx, rotationDirection_CounterClockwise), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_StartToEnd"), JSValueMakeNumber(ctx, Sprite::animate_StartToEnd), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_EndToStart"), JSValueMakeNumber(ctx, Sprite::animate_EndToStart), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_Unidirectional"), JSValueMakeNumber(ctx, Sprite::animate_Unidirectional), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_Bidirectional"), JSValueMakeNumber(ctx, Sprite::animate_Bidirectional), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_NoLooping"), JSValueMakeNumber(ctx, Sprite::animate_NoLooping), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animate_Looping"), JSValueMakeNumber(ctx, Sprite::animate_Looping), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("start_FromFirstFrame"), JSValueMakeNumber(ctx, Sprite::start_FromFirstFrame), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("start_FromLastFrame"), JSValueMakeNumber(ctx, Sprite::start_FromLastFrame), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("all_Frames"), JSValueMakeNumber(ctx, Sprite::all_Frames), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_CollideSprite"), JSValueMakeNumber(ctx, Sprite::action_CollideSprite), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_CollideWall"), JSValueMakeNumber(ctx, Sprite::action_CollideWall), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_Offscreen"), JSValueMakeNumber(ctx, Sprite::action_Offscreen), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_Onscreen"), JSValueMakeNumber(ctx, Sprite::action_Onscreen), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_ExitLayer"), JSValueMakeNumber(ctx, Sprite::action_ExitLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationLoop"), JSValueMakeNumber(ctx, Sprite::action_AnimationLoop), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationEnd"), JSValueMakeNumber(ctx, Sprite::action_AnimationEnd), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_FadeComplete"), JSValueMakeNumber(ctx, Sprite::action_FadeComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_FadeInComplete"), JSValueMakeNumber(ctx, Sprite::action_FadeInComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_FadeOutComplete"), JSValueMakeNumber(ctx, Sprite::action_FadeOutComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_JointBreak"), JSValueMakeNumber(ctx, Sprite::action_JointBreak), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_BodyBreak"), JSValueMakeNumber(ctx, Sprite::action_BodyBreak), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBreak_Force"), JSValueMakeNumber(ctx, physicsBreak_Force), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("physicsBreak_AngularSpeed"), JSValueMakeNumber(ctx, physicsBreak_AngularSpeed), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationBlendComplete"), JSValueMakeNumber(ctx, Sprite::action_AnimationBlendComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationPhysicsRecoveryComplete"), JSValueMakeNumber(ctx, Sprite::action_AnimationPhysicsRecoveryComplete), kJSPropertyAttributeNone, exception);;
#ifdef PDG_SPRITER_SUPPORT
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationPhysics_Kinematic"), JSValueMakeNumber(ctx, animationPhysics_Kinematic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationPhysics_Dynamic"), JSValueMakeNumber(ctx, animationPhysics_Dynamic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationPhysics_Driven"), JSValueMakeNumber(ctx, animationPhysics_Driven), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationPhysics_Mixed"), JSValueMakeNumber(ctx, animationPhysics_Mixed), kJSPropertyAttributeNone, exception);;
#endif

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("touch_MouseEnter"), JSValueMakeNumber(ctx, Sprite::touch_MouseEnter), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("touch_MouseLeave"), JSValueMakeNumber(ctx, Sprite::touch_MouseLeave), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("touch_MouseDown"), JSValueMakeNumber(ctx, Sprite::touch_MouseDown), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("touch_MouseUp"), JSValueMakeNumber(ctx, Sprite::touch_MouseUp), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("touch_MouseClick"), JSValueMakeNumber(ctx, Sprite::touch_MouseClick), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_None"), JSValueMakeNumber(ctx, Sprite::collide_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_Point"), JSValueMakeNumber(ctx, Sprite::collide_Point), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_BoundingBox"), JSValueMakeNumber(ctx, Sprite::collide_BoundingBox), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_CollisionRadius"), JSValueMakeNumber(ctx, Sprite::collide_CollisionRadius), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_AlphaChannel"), JSValueMakeNumber(ctx, Sprite::collide_AlphaChannel), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_SpriterCollisionBox"), JSValueMakeNumber(ctx, Sprite::collide_SpriterCollisionBox), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("collide_Last"), JSValueMakeNumber(ctx, Sprite::collide_Last), kJSPropertyAttributeNone, exception);;

#ifdef PDG_SPRITER_SUPPORT
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSpace_Local"), JSValueMakeNumber(ctx, animationSpace_Local), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSpace_Rig"), JSValueMakeNumber(ctx, animationSpace_Rig), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSpace_World"), JSValueMakeNumber(ctx, animationSpace_World), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDebug_None"), JSValueMakeNumber(ctx, animationDebug_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDebug_Bones"), JSValueMakeNumber(ctx, animationDebug_Bones), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDebug_Sockets"), JSValueMakeNumber(ctx, animationDebug_Sockets), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDebug_Boxes"), JSValueMakeNumber(ctx, animationDebug_Boxes), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDebug_All"), JSValueMakeNumber(ctx, animationDebug_All), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationBinding_Image"), JSValueMakeNumber(ctx, animationBinding_Image), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationBinding_Point"), JSValueMakeNumber(ctx, animationBinding_Point), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationBinding_Box"), JSValueMakeNumber(ctx, animationBinding_Box), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationVariable_Float"), JSValueMakeNumber(ctx, animationVariable_Float), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationVariable_Int"), JSValueMakeNumber(ctx, animationVariable_Int), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationVariable_String"), JSValueMakeNumber(ctx, animationVariable_String), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationStage_PreConstraint"), JSValueMakeNumber(ctx, animationStage_PreConstraint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationStage_Constraint"), JSValueMakeNumber(ctx, animationStage_Constraint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationStage_PostConstraint"), JSValueMakeNumber(ctx, animationStage_PostConstraint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSource_Clip"), JSValueMakeNumber(ctx, animationSource_Clip), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSource_Reference"), JSValueMakeNumber(ctx, animationSource_Reference), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationSource_Procedural"), JSValueMakeNumber(ctx, animationSource_Procedural), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationBody_Dynamic"), JSValueMakeNumber(ctx, animationBody_Dynamic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationBody_Kinematic"), JSValueMakeNumber(ctx, animationBody_Kinematic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationRoot_Fixed"), JSValueMakeNumber(ctx, animationRoot_Fixed), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationRoot_Follow"), JSValueMakeNumber(ctx, animationRoot_Follow), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDraw_BeforeAll"), JSValueMakeNumber(ctx, animationDraw_BeforeAll), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDraw_AfterAll"), JSValueMakeNumber(ctx, animationDraw_AfterAll), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDraw_BeforeSlot"), JSValueMakeNumber(ctx, animationDraw_BeforeSlot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDraw_AfterSlot"), JSValueMakeNumber(ctx, animationDraw_AfterSlot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationDraw_ReplaceSlot"), JSValueMakeNumber(ctx, animationDraw_ReplaceSlot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationStroke_PortPixels"), JSValueMakeNumber(ctx, animationStroke_PortPixels), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationStroke_Local"), JSValueMakeNumber(ctx, animationStroke_Local), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationIK_NoStretch"), JSValueMakeNumber(ctx, animationIK_NoStretch), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("animationIK_Stretch"), JSValueMakeNumber(ctx, animationIK_Stretch), kJSPropertyAttributeNone, exception);;
#endif

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_ErasePort"), JSValueMakeNumber(ctx, SpriteLayer::action_ErasePort), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_PreDrawLayer"), JSValueMakeNumber(ctx, SpriteLayer::action_PreDrawLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_PostDrawLayer"), JSValueMakeNumber(ctx, SpriteLayer::action_PostDrawLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_DrawPortComplete"), JSValueMakeNumber(ctx, SpriteLayer::action_DrawPortComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationStart"), JSValueMakeNumber(ctx, SpriteLayer::action_AnimationStart), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_PreAnimateLayer"), JSValueMakeNumber(ctx, SpriteLayer::action_PreAnimateLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_PostAnimateLayer"), JSValueMakeNumber(ctx, SpriteLayer::action_PostAnimateLayer), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_AnimationComplete"), JSValueMakeNumber(ctx, SpriteLayer::action_AnimationComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_ZoomComplete"), JSValueMakeNumber(ctx, SpriteLayer::action_ZoomComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_LayerFadeInComplete"), JSValueMakeNumber(ctx, SpriteLayer::action_FadeInComplete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("action_LayerFadeOutComplete"), JSValueMakeNumber(ctx, SpriteLayer::action_FadeOutComplete), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("facing_North"), JSValueMakeNumber(ctx, TileLayer::facing_North), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("facing_East"), JSValueMakeNumber(ctx, TileLayer::facing_East), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("facing_South"), JSValueMakeNumber(ctx, TileLayer::facing_South), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("facing_West"), JSValueMakeNumber(ctx, TileLayer::facing_West), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("facing_Ignore"), JSValueMakeNumber(ctx, TileLayer::facing_Ignore), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("flipped_None"), JSValueMakeNumber(ctx, TileLayer::flipped_None), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("flipped_Horizontal"), JSValueMakeNumber(ctx, TileLayer::flipped_Horizontal), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("flipped_Vertical"), JSValueMakeNumber(ctx, TileLayer::flipped_Vertical), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("flipped_Both"), JSValueMakeNumber(ctx, TileLayer::flipped_Both), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("flipped_Ignore"), JSValueMakeNumber(ctx, TileLayer::flipped_Ignore), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("timer_OneShot"), JSValueMakeBoolean(ctx, timer_OneShot), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("timer_Repeating"), JSValueMakeBoolean(ctx, timer_Repeating), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("timer_Never"), JSValueMakeNumber(ctx, (int32) timer_Never), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("linearTween"), JSValueMakeNumber(ctx, EasingFuncRef::linearTween), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInQuad"), JSValueMakeNumber(ctx, EasingFuncRef::easeInQuad), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutQuad"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutQuad), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutQuad"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutQuad), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInCubic"), JSValueMakeNumber(ctx, EasingFuncRef::easeInCubic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutCubic"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutCubic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutCubic"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutCubic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInQuart"), JSValueMakeNumber(ctx, EasingFuncRef::easeInQuart), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutQuart"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutQuart), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutCubic"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutCubic), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInQuint"), JSValueMakeNumber(ctx, EasingFuncRef::easeInQuint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutQuint"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutQuint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutQuint"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutQuint), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInSine"), JSValueMakeNumber(ctx, EasingFuncRef::easeInSine), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutSine"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutSine), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutSine"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutSine), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInExpo"), JSValueMakeNumber(ctx, EasingFuncRef::easeInExpo), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutExpo"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutExpo), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutExpo"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutExpo), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInCirc"), JSValueMakeNumber(ctx, EasingFuncRef::easeInCirc), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutCirc"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutCirc), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutCirc"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutCirc), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInBounce"), JSValueMakeNumber(ctx, EasingFuncRef::easeInBounce), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutBounce"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutBounce), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutBounce"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutBounce), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInBack"), JSValueMakeNumber(ctx, EasingFuncRef::easeInBack), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeOutBack"), JSValueMakeNumber(ctx, EasingFuncRef::easeOutBack), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("easeInOutBack"), JSValueMakeNumber(ctx, EasingFuncRef::easeInOutBack), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Positions"), JSValueMakeNumber(ctx, ser_Positions), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_ZOrder"), JSValueMakeNumber(ctx, ser_ZOrder), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Sizes"), JSValueMakeNumber(ctx, ser_Sizes), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Animations"), JSValueMakeNumber(ctx, ser_Animations), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Motion"), JSValueMakeNumber(ctx, ser_Motion), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Forces"), JSValueMakeNumber(ctx, ser_Forces), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Physics"), JSValueMakeNumber(ctx, ser_Physics), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_LayerDraw"), JSValueMakeNumber(ctx, ser_LayerDraw), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_ImageRefs"), JSValueMakeNumber(ctx, ser_ImageRefs), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_SCMLRefs"), JSValueMakeNumber(ctx, ser_SCMLRefs), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_HelperRefs"), JSValueMakeNumber(ctx, ser_HelperRefs), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_HelperObjs"), JSValueMakeNumber(ctx, ser_HelperObjs), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_InitialData"), JSValueMakeNumber(ctx, ser_InitialData), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Micro"), JSValueMakeNumber(ctx, ser_Micro), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Update"), JSValueMakeNumber(ctx, ser_Update), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("ser_Full"), JSValueMakeNumber(ctx, ser_Full), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("serialization_Complete"), JSValueMakeNumber(ctx, serialization_Complete), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("serialization_ExternalReferences"), JSValueMakeNumber(ctx, serialization_ExternalReferences), kJSPropertyAttributeNone, exception);;

        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_Hermite"), JSValueMakeNumber(ctx, 1), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_Cardinal"), JSValueMakeNumber(ctx, 2), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_UniformB"), JSValueMakeNumber(ctx, 3), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_CubicBezier"), JSValueMakeNumber(ctx, 4), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_TCB"), JSValueMakeNumber(ctx, 5), kJSPropertyAttributeNone, exception);;
        JSObjectSetProperty(ctx, globalObject, JSStringCreateWithUTF8CString("spline_NaturalCubic"), JSValueMakeNumber(ctx, 6), kJSPropertyAttributeNone, exception);;

    }

    void CreateSingletons()
    {

        FileManager_getScriptSingletonInstance();

        LogManager_getSingletonInstance();
        ConfigManager_getSingletonInstance();
        ResourceManager_getSingletonInstance();
        EventManager_getSingletonInstance();
        TimerManager_getSingletonInstance();
#ifndef PDG_NO_GUI
        GraphicsManager_getSingletonInstance();
#endif
#ifndef PDG_NO_SOUND
        SoundManager_getSingletonInstance();
#endif
#ifndef PDG_NO_NETWORK
        NetworkManager::getSingletonInstance();
#endif
    }

}


extern "C" void pdg_LibContainerDoIdle()
{

    JSGarbageCollect(pdg::gMainContext);

}
