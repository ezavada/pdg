// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/sound_manager.cpp
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

#ifndef PDG_NO_SOUND

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void Sound_finalize(JSObjectRef object)
    {
        auto* sound = static_cast<Sound*>(JSObjectGetPrivate(object));
        if (!sound) return;
        sound->mSoundScriptObj = nullptr;
        sound->mEventEmitterScriptObj = nullptr;
        JSObjectSetPrivate(object, nullptr);
        sound->release();
    }
#endif
    JSObjectRef Sound_newFromCpp(JSContextRef ctx, Sound* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Sound_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Sound_class());
        cppObj->mEventEmitterScriptObj = obj; cppObj->mSoundScriptObj = obj; cppObj->addRef();
        return obj;
    }

    JSObjectRef Sound_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* cppObj = New_Sound(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Sound" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Sound_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Sound_class());
        cppObj->mEventEmitterScriptObj = obj; cppObj->mSoundScriptObj = obj; cppObj->addRef();
        return obj;
    }

    JSClassRef Sound_class()
    {

        static JSStaticValue Sound_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Sound_staticFunctions[] =
        {
            { "addHandler", Sound_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", Sound_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", Sound_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", Sound_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", Sound_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "get""Volume", Sound_GetVolume, kJSPropertyAttributeDontDelete },
            { "set""Volume", Sound_SetVolume, kJSPropertyAttributeDontDelete },
            { "play", Sound_Play, kJSPropertyAttributeDontDelete },
            { "start", Sound_Start, kJSPropertyAttributeDontDelete },
            { "stop", Sound_Stop, kJSPropertyAttributeDontDelete },
            { "pause", Sound_Pause, kJSPropertyAttributeDontDelete },
            { "resume", Sound_Resume, kJSPropertyAttributeDontDelete },
            { "isPaused", Sound_IsPaused, kJSPropertyAttributeDontDelete },
            { "setLooping", Sound_SetLooping, kJSPropertyAttributeDontDelete },
            { "isLooping", Sound_IsLooping, kJSPropertyAttributeDontDelete },
            { "setPitch", Sound_SetPitch, kJSPropertyAttributeDontDelete },
            { "changePitch", Sound_ChangePitch, kJSPropertyAttributeDontDelete },
            { "setOffsetX", Sound_SetOffsetX, kJSPropertyAttributeDontDelete },
            { "changeOffsetX", Sound_ChangeOffsetX, kJSPropertyAttributeDontDelete },
            { "fadeOut", Sound_FadeOut, kJSPropertyAttributeDontDelete },
            { "fadeIn", Sound_FadeIn, kJSPropertyAttributeDontDelete },
            { "changeVolume", Sound_ChangeVolume, kJSPropertyAttributeDontDelete },
            { "skip", Sound_Skip, kJSPropertyAttributeDontDelete },
            { "skipTo", Sound_SkipTo, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = Sound_finalize;
            definition.className = "Sound";
            definition.staticFunctions = Sound_staticFunctions;
            definition.staticValues = Sound_staticValues;
            definition.callAsConstructor = Sound_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
#ifndef PDG_USING_JAVASCRIPT_CORE
    SoundWrap::SoundWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_Sound(args))
    {
        if (!cppPtr_ && !s_Sound_InNewFromCpp)
        {
            [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Failed to create Sound instance" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    SoundWrap::~SoundWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mSoundScriptObj.Reset();
            cppPtr_->mEventEmitterScriptObj.Reset();
            cppPtr_->release();
        }
    }
#endif

    JSValueRef Sound_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        SCRIPT_DEBUG_ONLY( JSC_DebugPrintValue(ctx, arguments[0], "Dumping " "IEventHandler" " object:") );
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        IEventHandler* inHandler = 0;
        if (JSValueIsObjectOfClass(ctx, arguments[1 -1], IEventHandler_class()))
        {
            JSObjectRef inHandler_ = JSValueToObject(ctx, arguments[1 -1], exception);
            inHandler = IEventHandler_getCppObject(inHandler_);
        }
        if (!inHandler)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object derived from ""IEventHandler"" (""inHandler"")");
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""inType"")");
        long inType = (argumentCount<2) ? pdg::all_events : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_GetVolume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theVolume = self->getVolume();
        return JSValueMakeNumber(ctx, theVolume);
    }
    JSValueRef Sound_SetVolume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""theVolume"")");
        double theVolume = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setVolume(theVolume);
        return thisObject;
    }
    JSValueRef Sound_Play(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""vol"")");
        double vol = (argumentCount<1) ? 1.0 : JSValueToNumber(ctx, arguments[1 -1], exception);
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""offsetX"")");
        long offsetX = (argumentCount<2) ? 0 : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""pitch"")");
        double pitch = (argumentCount<3) ? 0.0 : JSValueToNumber(ctx, arguments[3 -1], exception);
        if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""fromMs"")");
        unsigned long fromMs = (argumentCount<4) ? 0 : (uint32)floor(fabs(JSValueToNumber(ctx, arguments[4 -1], exception)));
        if (argumentCount >= 5 && !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""lenMs"")");
        long lenMs = (argumentCount<5) ? -1 : (int32)floor(JSValueToNumber(ctx, arguments[5 -1], exception));
        self->play(vol, offsetX, pitch, fromMs, lenMs);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Start(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->start();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Stop(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->stop();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Pause(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->pause();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Resume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->resume();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_IsPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool result = self->isPaused();
        return JSValueMakeBoolean(ctx, result);
    }
    JSValueRef Sound_SetLooping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""loopingOn"")");
        bool loopingOn = JSValueToBoolean(ctx, arguments[1 -1]);
        self->setLooping(loopingOn);
        return thisObject;
    }
    JSValueRef Sound_IsLooping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool result = self->isLooping();
        return JSValueMakeBoolean(ctx, result);
    }
    JSValueRef Sound_SetPitch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""pitchOffset"")");
        double pitchOffset = JSValueToNumber(ctx, arguments[1 -1], exception);
        self->setPitch(pitchOffset);
        return thisObject;
    }
    JSValueRef Sound_ChangePitch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""targetOffset"")");
        double targetOffset = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""msDuration"")");
        int32 msDuration = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::easeInOutQuad : (int32)floor(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changePitch(targetOffset, msDuration);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_SetOffsetX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""offsetX"")");
        int32 offsetX = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->setOffsetX(offsetX);
        return thisObject;
    }
    JSValueRef Sound_ChangeOffsetX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""targetOffset"")");
        int32 targetOffset = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""msDuration"")");
        int32 msDuration = (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changePitch(targetOffset, msDuration);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_FadeOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""fadeMs"")");
        uint32 fadeMs = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(fadeMs);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""fadeMs"")");
        uint32 fadeMs = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
        long easing = (argumentCount<2) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[2 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(fadeMs);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_ChangeVolume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount < 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""level"")");
        double level = JSValueToNumber(ctx, arguments[1 -1], exception);
        if (!JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""fadeMs"")");
        uint32 fadeMs = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[2 -1], exception)));
        if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
        long easing = (argumentCount<3) ? EasingFuncRef::linearTween : (int32)floor(JSValueToNumber(ctx, arguments[3 -1], exception));
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changeVolume(level, fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->changeVolume(level, fadeMs);
        }
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Sound_Skip(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""skipMilliseconds"")");
        int32 skipMilliseconds = (int32)floor(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->skip(skipMilliseconds);
        return thisObject;
    }
    JSValueRef Sound_SkipTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Sound* self = static_cast<Sound*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""timeMs"")");
        uint32 timeMs = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        self->skipTo(timeMs);
        return thisObject;
    }

    void CleanupSoundScriptObject(JSObjectRef obj) { }

    Sound* New_Sound(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
#ifndef PDG_USING_JAVASCRIPT_CORE
        if (s_Sound_InNewFromCpp) return nullptr;
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
#endif
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;
        if (argumentCount < 1)
        {
            return 0;
        }
        else if ((argumentCount == 1 && JSValueIsNull(ctx, arguments[0])))
        {
            return Sound::createEmptySoundForIntrospection();
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
            Sound* snd = Sound::createSoundFromFile(filename);
            if (!snd)
            {
                s_SavedError.str(""); s_SavedError.clear();
                s_SavedError << "could not create Sound from file ["<<filename<<"]";
                s_HaveSavedError = true;
                return 0;
            }
            else
            {
                return snd;
            }
        }
    }
#endif

}
