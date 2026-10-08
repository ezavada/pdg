// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animated.cpp
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

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>
#include "pdg/sys/animationrecorder.h"
#include "../../common/animation/particle_trail_options.h"

namespace pdg
{

    float customEasing0(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(0, ut, b, c, ud);
    }

    float customEasing1(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(1, ut, b, c, ud);
    }

    float customEasing2(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(2, ut, b, c, ud);
    }

    float customEasing3(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(3, ut, b, c, ud);
    }

    float customEasing4(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(4, ut, b, c, ud);
    }

    float customEasing5(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(5, ut, b, c, ud);
    }

    float customEasing6(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(6, ut, b, c, ud);
    }

    float customEasing7(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(7, ut, b, c, ud);
    }

    float customEasing8(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(8, ut, b, c, ud);
    }

    float customEasing9(double ut, float b, float c, double ud)
    {
        return CallScriptEasingFunc(9, ut, b, c, ud);
    }

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void AnimatedBase_finalize(JSObjectRef object)
    {
        auto* value=static_cast<AnimatedBase*>(JSObjectGetPrivate(object));
        if(value) { value->mAnimatedScriptObj=nullptr; value->release(); }
        JSObjectSetPrivate(object,nullptr);
    }
#endif
    JSObjectRef AnimatedBase_newFromCpp(JSContextRef ctx, AnimatedBase* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, AnimatedBase_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, AnimatedBase_class());
        cppObj->mAnimatedScriptObj = obj; cppObj->addRef();
        return obj;
    }

    JSObjectRef AnimatedBase_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* cppObj = New_AnimatedBase(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "AnimatedBase" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, AnimatedBase_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, AnimatedBase_class());
        cppObj->mAnimatedScriptObj = obj; cppObj->addRef();
        return obj;
    }

    JSClassRef AnimatedBase_class()
    {

        static JSStaticValue AnimatedBase_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction AnimatedBase_staticFunctions[] =
        {
            { "playScript", AnimatedBase_PlayScript, kJSPropertyAttributeDontDelete },
            { "batch", AnimatedBase_Batch, kJSPropertyAttributeDontDelete },
            { "endBatch", AnimatedBase_EndBatch, kJSPropertyAttributeDontDelete },
            { "series", AnimatedBase_Series, kJSPropertyAttributeDontDelete },
            { "endSeries", AnimatedBase_EndSeries, kJSPropertyAttributeDontDelete },
            { "andAlso", AnimatedBase_AndAlso, kJSPropertyAttributeDontDelete },
            { "stagger", AnimatedBase_Stagger, kJSPropertyAttributeDontDelete },
            { "mark", AnimatedBase_Mark, kJSPropertyAttributeDontDelete },
            { "jumpToMark", AnimatedBase_JumpToMark, kJSPropertyAttributeDontDelete },
            { "on", AnimatedBase_ScriptOn, kJSPropertyAttributeDontDelete },
            { "triggerEvent", AnimatedBase_TriggerEvent, kJSPropertyAttributeDontDelete },
            { "onStarted", AnimatedBase_OnStarted, kJSPropertyAttributeDontDelete },
            { "onFinished", AnimatedBase_OnFinished, kJSPropertyAttributeDontDelete },
            { "onScriptFinished", AnimatedBase_OnScriptFinished, kJSPropertyAttributeDontDelete },
            { "onMark", AnimatedBase_OnMark, kJSPropertyAttributeDontDelete },
            { "onYoyo", AnimatedBase_OnYoyo, kJSPropertyAttributeDontDelete },
            { "onRepeat", AnimatedBase_OnRepeat, kJSPropertyAttributeDontDelete },
            { "onUntilFired", AnimatedBase_OnUntilFired, kJSPropertyAttributeDontDelete },
            { "when", AnimatedBase_When, kJSPropertyAttributeDontDelete },
            { "otherwise", AnimatedBase_Otherwise, kJSPropertyAttributeDontDelete },
            { "endWhen", AnimatedBase_EndWhen, kJSPropertyAttributeDontDelete },
            { "endOtherwise", AnimatedBase_EndOtherwise, kJSPropertyAttributeDontDelete },
            { "until", AnimatedBase_Until, kJSPropertyAttributeDontDelete },
            { "yoyo", AnimatedBase_Yoyo, kJSPropertyAttributeDontDelete },
            { "repeat", AnimatedBase_Repeat, kJSPropertyAttributeDontDelete },
            { "diminish", AnimatedBase_Diminish, kJSPropertyAttributeDontDelete },
            { "increase", AnimatedBase_Increase, kJSPropertyAttributeDontDelete },
            { "slowDown", AnimatedBase_SlowDown, kJSPropertyAttributeDontDelete },
            { "speedUp", AnimatedBase_SpeedUp, kJSPropertyAttributeDontDelete },
            { "stopIt", AnimatedBase_StopIt, kJSPropertyAttributeDontDelete },
            { "restartIt", AnimatedBase_RestartIt, kJSPropertyAttributeDontDelete },
            { "pauseIt", AnimatedBase_PauseIt, kJSPropertyAttributeDontDelete },
            { "resumeIt", AnimatedBase_ResumeIt, kJSPropertyAttributeDontDelete },
            { "getBoundingBox", AnimatedBase_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", AnimatedBase_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", AnimatedBase_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", AnimatedBase_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", AnimatedBase_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", AnimatedBase_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", AnimatedBase_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", AnimatedBase_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", AnimatedBase_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", AnimatedBase_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", AnimatedBase_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", AnimatedBase_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", AnimatedBase_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", AnimatedBase_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", AnimatedBase_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", AnimatedBase_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", AnimatedBase_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", AnimatedBase_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", AnimatedBase_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", AnimatedBase_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", AnimatedBase_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", AnimatedBase_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", AnimatedBase_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", AnimatedBase_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", AnimatedBase_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", AnimatedBase_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", AnimatedBase_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", AnimatedBase_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", AnimatedBase_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", AnimatedBase_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", AnimatedBase_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", AnimatedBase_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", AnimatedBase_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", AnimatedBase_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", AnimatedBase_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", AnimatedBase_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", AnimatedBase_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", AnimatedBase_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", AnimatedBase_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", AnimatedBase_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", AnimatedBase_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", AnimatedBase_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", AnimatedBase_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", AnimatedBase_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", AnimatedBase_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", AnimatedBase_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", AnimatedBase_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", AnimatedBase_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", AnimatedBase_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", AnimatedBase_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", AnimatedBase_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", AnimatedBase_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", AnimatedBase_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", AnimatedBase_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", AnimatedBase_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", AnimatedBase_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", AnimatedBase_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", AnimatedBase_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", AnimatedBase_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", AnimatedBase_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", AnimatedBase_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", AnimatedBase_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", AnimatedBase_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "animate", AnimatedBase_Animate, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = AnimatedBase_finalize;
            definition.className = "Animated";
            definition.staticFunctions = AnimatedBase_staticFunctions;
            definition.staticValues = AnimatedBase_staticValues;
            definition.callAsConstructor = AnimatedBase_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef AnimatedBase_PlayScript(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            self->playScript(name); return thisObject;
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
    JSValueRef AnimatedBase_Batch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->batch(); return thisObject;
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
    JSValueRef AnimatedBase_EndBatch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endBatch(); return thisObject;
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
    JSValueRef AnimatedBase_Series(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->series(); return thisObject;
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
    JSValueRef AnimatedBase_EndSeries(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endSeries(); return thisObject;
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
    JSValueRef AnimatedBase_AndAlso(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->andAlso(); return thisObject;
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
    JSValueRef AnimatedBase_Stagger(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""intervalSeconds"")");
            double intervalSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->stagger(intervalSeconds); return thisObject;
        }
        catch(const std::exception& error)
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
    JSValueRef AnimatedBase_Mark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if(argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            }
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""saveState"")");
            bool saveState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
            self->mark(name, saveState); return thisObject;
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
    JSValueRef AnimatedBase_JumpToMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            if(argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            }
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""restoreState"")");
            bool restoreState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
            self->jumpToMark(name, restoreState); return thisObject;
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
    JSValueRef AnimatedBase_When(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
            self->when(MakeAnimationEvaluator(evaluator)); return thisObject;
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
    JSValueRef AnimatedBase_ScriptOn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""event"")");
            JSStringRef event_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock event_Mem(JSStringGetMaximumUTF8CStringSize(event_Str));
            JSStringGetUTF8CString(event_Str, event_Mem.ptr, event_Mem.bytes);
            const char* event = (const char*)event_Mem.ptr;
            JSStringRelease(event_Str);
            JSObjectRef handler = JSValueToObject(ctx, arguments[2 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""handler"")");
            self->on(event, MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnStarted(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onStarted(MakeAnimationEventHandler(handler)); return thisObject;
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
    JSValueRef AnimatedBase_TriggerEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsString(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
            JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
            MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
            JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
            const char* name = (const char*)name_Mem.ptr;
            JSStringRelease(name_Str);
            self->triggerEvent(name); return thisObject;
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

    JSValueRef AnimatedBase_OnFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onFinished(MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnScriptFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onScriptFinished(MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onMark(MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnYoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onYoyo(MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnRepeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onRepeat(MakeAnimationEventHandler(handler)); return thisObject;
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

    JSValueRef AnimatedBase_OnUntilFired(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            self->mAnimatedScriptObj = thisObject;
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!handler || !JSObjectIsFunction(ctx, handler) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
            self->onUntilFired(MakeAnimationEventHandler(handler)); return thisObject;
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
    JSValueRef AnimatedBase_Otherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->otherwise(); return thisObject;
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
    JSValueRef AnimatedBase_EndWhen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endWhen(); return thisObject;
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
    JSValueRef AnimatedBase_EndOtherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->endOtherwise(); return thisObject;
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
    JSValueRef AnimatedBase_Until(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
            self->until(MakeAnimationEvaluator(evaluator)); return thisObject;
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
    JSValueRef AnimatedBase_Yoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->yoyo(); return thisObject;
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
    JSValueRef AnimatedBase_Repeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);
            if (argumentCount>1)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            }
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""countValue"")");
            double countValue = (argumentCount<1) ? -1 : JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount && (!std::isfinite(countValue) || countValue<0 || countValue>INT32_MAX || std::floor(countValue)!=countValue)) throw std::invalid_argument("Repeat count must be a nonnegative integer");
            self->repeat(static_cast<int>(countValue)); return thisObject;
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
    JSValueRef AnimatedBase_Diminish(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->diminish(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
    JSValueRef AnimatedBase_Increase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->increase(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
    JSValueRef AnimatedBase_SlowDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->slowDown(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
    JSValueRef AnimatedBase_SpeedUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
            if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            }
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            self->speedUp(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
    JSValueRef AnimatedBase_StopIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->stopIt(); return thisObject;
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
    JSValueRef AnimatedBase_RestartIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->restartIt(); return thisObject;
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
    JSValueRef AnimatedBase_PauseIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->pauseIt(); return thisObject;
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
    JSValueRef AnimatedBase_ResumeIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->resumeIt(); return thisObject;
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

    JSValueRef AnimatedBase_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Rect value=self->getBoundingBox(); return JSC_RectToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::RotatedRect value=self->getRotatedBounds(); return JSC_RectToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Point value=self->getLocation(); return JSC_PointToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getMovement(); return JSC_OffsetToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getSize(); return JSC_OffsetToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getWidth(); return JSValueMakeNumber(ctx, value);
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

    JSValueRef AnimatedBase_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getHeight(); return JSValueMakeNumber(ctx, value);
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

    JSValueRef AnimatedBase_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getScale(); return JSC_OffsetToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getStretching(); return JSC_OffsetToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getRotation(); return JSValueMakeNumber(ctx, value);
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

    JSValueRef AnimatedBase_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            pdg::Offset value=self->getCenterOffset(); return JSC_OffsetToValue(ctx, value, exception);
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

    JSValueRef AnimatedBase_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            double value=self->getSpin(); return JSValueMakeNumber(ctx, value);
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
    JSValueRef AnimatedBase_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
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
    JSValueRef AnimatedBase_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        try
        {
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
    JSValueRef AnimatedBase_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef AnimatedBase_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef AnimatedBase_Animate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        AnimatedBase* self = static_cast<AnimatedBase*>(JSObjectGetPrivate(thisObject));
        self->mAnimatedScriptObj = thisObject;
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaSeconds"")");
        double deltaSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
        try
        {
            bool result = self->animate(deltaSeconds);
            return JSValueMakeBoolean(ctx, result);
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    void CleanupAnimatedBaseScriptObject(JSObjectRef obj) { }

#ifdef PDG_USING_JAVASCRIPT_CORE
    AnimatedBase* New_AnimatedBase(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
#else
        AnimatedBaseWrap::AnimatedBaseWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_AnimatedBase(args)) {}
        AnimatedBaseWrap::~AnimatedBaseWrap()
        {
            if(cppPtr_)
            {
                cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr;
            }
        }
        AnimatedBase* New_AnimatedBase(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
        {
            if(s_AnimatedBase_InNewFromCpp) return nullptr;
            auto* isolate=args.GetIsolate();
#endif
            auto* value=new AnimatedBase();
#ifdef PDG_USING_V8
            value->addRef(); value->mAnimatedScriptObj = thisObject;
#endif
            return value;
        }

#ifdef PDG_USING_JAVASCRIPT_CORE
        static void Troupe_finalize(JSObjectRef object)
        {
            auto* value=static_cast<Troupe*>(JSObjectGetPrivate(object));
            if(value) { value->mAnimatedScriptObj=nullptr; value->release(); }
            JSObjectSetPrivate(object,nullptr);
        }
#endif
        JSObjectRef Troupe_newFromCpp(JSContextRef ctx, Troupe* cppObj)
        {
            JSObjectRef obj = JSObjectMake(ctx, Troupe_class(), cppObj);
            JSC_SetObjectClassConstructor(ctx, obj, Troupe_class());
            cppObj->mAnimatedScriptObj = obj; cppObj->addRef();
            return obj;
        }

        JSObjectRef Troupe_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Troupe* cppObj = New_Troupe(argumentCount, arguments, exception);
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
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Troupe" "'"), NULL, 0, 1, exception);
                return 0;
            }
            JSObjectRef obj = JSObjectMake(ctx, Troupe_class(), cppObj);
            JSC_SetObjectClassConstructor(ctx, obj, Troupe_class());
            cppObj->mAnimatedScriptObj = obj; cppObj->addRef();
            return obj;
        }

        JSClassRef Troupe_class()
        {
            static JSStaticValue Troupe_staticValues[] =
            {
                { 0, 0, 0, 0 }
            };
            static JSStaticFunction Troupe_staticFunctions[] =
            {
                { "playScript", Troupe_PlayScript, kJSPropertyAttributeDontDelete },
                { "batch", Troupe_Batch, kJSPropertyAttributeDontDelete },
                { "endBatch", Troupe_EndBatch, kJSPropertyAttributeDontDelete },
                { "series", Troupe_Series, kJSPropertyAttributeDontDelete },
                { "endSeries", Troupe_EndSeries, kJSPropertyAttributeDontDelete },
                { "andAlso", Troupe_AndAlso, kJSPropertyAttributeDontDelete },
                { "stagger", Troupe_Stagger, kJSPropertyAttributeDontDelete },
                { "mark", Troupe_Mark, kJSPropertyAttributeDontDelete },
                { "jumpToMark", Troupe_JumpToMark, kJSPropertyAttributeDontDelete },
                { "on", Troupe_ScriptOn, kJSPropertyAttributeDontDelete },
                { "triggerEvent", Troupe_TriggerEvent, kJSPropertyAttributeDontDelete },
                { "onStarted", Troupe_OnStarted, kJSPropertyAttributeDontDelete },
                { "onFinished", Troupe_OnFinished, kJSPropertyAttributeDontDelete },
                { "onScriptFinished", Troupe_OnScriptFinished, kJSPropertyAttributeDontDelete },
                { "onMark", Troupe_OnMark, kJSPropertyAttributeDontDelete },
                { "onYoyo", Troupe_OnYoyo, kJSPropertyAttributeDontDelete },
                { "onRepeat", Troupe_OnRepeat, kJSPropertyAttributeDontDelete },
                { "onUntilFired", Troupe_OnUntilFired, kJSPropertyAttributeDontDelete },
                { "when", Troupe_When, kJSPropertyAttributeDontDelete },
                { "otherwise", Troupe_Otherwise, kJSPropertyAttributeDontDelete },
                { "endWhen", Troupe_EndWhen, kJSPropertyAttributeDontDelete },
                { "endOtherwise", Troupe_EndOtherwise, kJSPropertyAttributeDontDelete },
                { "until", Troupe_Until, kJSPropertyAttributeDontDelete },
                { "yoyo", Troupe_Yoyo, kJSPropertyAttributeDontDelete },
                { "repeat", Troupe_Repeat, kJSPropertyAttributeDontDelete },
                { "diminish", Troupe_Diminish, kJSPropertyAttributeDontDelete },
                { "increase", Troupe_Increase, kJSPropertyAttributeDontDelete },
                { "slowDown", Troupe_SlowDown, kJSPropertyAttributeDontDelete },
                { "speedUp", Troupe_SpeedUp, kJSPropertyAttributeDontDelete },
                { "stopIt", Troupe_StopIt, kJSPropertyAttributeDontDelete },
                { "restartIt", Troupe_RestartIt, kJSPropertyAttributeDontDelete },
                { "pauseIt", Troupe_PauseIt, kJSPropertyAttributeDontDelete },
                { "resumeIt", Troupe_ResumeIt, kJSPropertyAttributeDontDelete },
                { "getBoundingBox", Troupe_GetBoundingBox, kJSPropertyAttributeDontDelete },
                { "getRotatedBounds", Troupe_GetRotatedBounds, kJSPropertyAttributeDontDelete },
                { "getLocation", Troupe_GetLocation, kJSPropertyAttributeDontDelete },
                { "getMovement", Troupe_GetMovement, kJSPropertyAttributeDontDelete },
                { "getSize", Troupe_GetSize, kJSPropertyAttributeDontDelete },
                { "getWidth", Troupe_GetWidth, kJSPropertyAttributeDontDelete },
                { "getHeight", Troupe_GetHeight, kJSPropertyAttributeDontDelete },
                { "getScale", Troupe_GetScale, kJSPropertyAttributeDontDelete },
                { "getStretching", Troupe_GetStretching, kJSPropertyAttributeDontDelete },
                { "getRotation", Troupe_GetRotation, kJSPropertyAttributeDontDelete },
                { "getCenterOffset", Troupe_GetCenterOffset, kJSPropertyAttributeDontDelete },
                { "getSpin", Troupe_GetSpin, kJSPropertyAttributeDontDelete },
                { "setLocation", Troupe_SetLocation, kJSPropertyAttributeDontDelete },
                { "moveTo", Troupe_MoveTo, kJSPropertyAttributeDontDelete },
                { "moveBy", Troupe_MoveBy, kJSPropertyAttributeDontDelete },
                { "setMovement", Troupe_SetMovement, kJSPropertyAttributeDontDelete },
                { "changeMovementTo", Troupe_ChangeMovementTo, kJSPropertyAttributeDontDelete },
                { "changeMovementBy", Troupe_ChangeMovementBy, kJSPropertyAttributeDontDelete },
                { "setSize", Troupe_SetSize, kJSPropertyAttributeDontDelete },
                { "changeCenterOffsetTo", Troupe_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
                { "changeCenterOffsetBy", Troupe_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
                { "setWidth", Troupe_SetWidth, kJSPropertyAttributeDontDelete },
                { "setHeight", Troupe_SetHeight, kJSPropertyAttributeDontDelete },
                { "setRotation", Troupe_SetRotation, kJSPropertyAttributeDontDelete },
                { "setSpin", Troupe_SetSpin, kJSPropertyAttributeDontDelete },
                { "setGrowing", Troupe_SetGrowing, kJSPropertyAttributeDontDelete },
                { "setStretching", Troupe_SetStretching, kJSPropertyAttributeDontDelete },
                { "setScale", Troupe_SetScale, kJSPropertyAttributeDontDelete },
                { "changeSpinTo", Troupe_ChangeSpinTo, kJSPropertyAttributeDontDelete },
                { "changeSpinBy", Troupe_ChangeSpinBy, kJSPropertyAttributeDontDelete },
                { "changeGrowingTo", Troupe_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
                { "changeGrowingBy", Troupe_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
                { "changeStretchingTo", Troupe_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
                { "changeStretchingBy", Troupe_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
                { "changeScaleTo", Troupe_ChangeScaleTo, kJSPropertyAttributeDontDelete },
                { "changeScaleBy", Troupe_ChangeScaleBy, kJSPropertyAttributeDontDelete },
                { "grow", Troupe_Grow, kJSPropertyAttributeDontDelete },
                { "stretch", Troupe_Stretch, kJSPropertyAttributeDontDelete },
                { "resizeBy", Troupe_ResizeBy, kJSPropertyAttributeDontDelete },
                { "resizeTo", Troupe_ResizeTo, kJSPropertyAttributeDontDelete },
                { "rotateBy", Troupe_RotateBy, kJSPropertyAttributeDontDelete },
                { "rotateTo", Troupe_RotateTo, kJSPropertyAttributeDontDelete },
                { "setCenterOffset", Troupe_SetCenterOffset, kJSPropertyAttributeDontDelete },
                { "setFlipX", Troupe_SetFlipX, kJSPropertyAttributeDontDelete },
                { "setFlipY", Troupe_SetFlipY, kJSPropertyAttributeDontDelete },
                { "stopMovement", Troupe_StopMovement, kJSPropertyAttributeDontDelete },
                { "stopSpinning", Troupe_StopSpinning, kJSPropertyAttributeDontDelete },
                { "stopGrowing", Troupe_StopGrowing, kJSPropertyAttributeDontDelete },
                { "stopStretching", Troupe_StopStretching, kJSPropertyAttributeDontDelete },
                { "pauseSchedule", Troupe_PauseSchedule, kJSPropertyAttributeDontDelete },
                { "resumeSchedule", Troupe_ResumeSchedule, kJSPropertyAttributeDontDelete },
                { "cancelSchedule", Troupe_CancelSchedule, kJSPropertyAttributeDontDelete },
                { "flipX", Troupe_FlipX, kJSPropertyAttributeDontDelete },
                { "flipY", Troupe_FlipY, kJSPropertyAttributeDontDelete },
                { "andThen", Troupe_AndThen, kJSPropertyAttributeDontDelete },
                { "isFlippedX", Troupe_IsFlippedX, kJSPropertyAttributeDontDelete },
                { "isFlippedY", Troupe_IsFlippedY, kJSPropertyAttributeDontDelete },
                { "isSchedulePaused", Troupe_IsSchedulePaused, kJSPropertyAttributeDontDelete },
                { "hasScheduledAnimations", Troupe_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
                { "wait", Troupe_Wait, kJSPropertyAttributeDontDelete },
                { "addAnimationHelper", Troupe_AddAnimationHelper, kJSPropertyAttributeDontDelete },
                { "removeAnimationHelper", Troupe_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
                { "clearAnimationHelpers", Troupe_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
                { "_recordAnimationCommand", Troupe_RecordCommand, kJSPropertyAttributeDontDelete },
                { "animate", Troupe_Animate, kJSPropertyAttributeDontDelete },
                { "add", Troupe_Add, kJSPropertyAttributeDontDelete },
                { "remove", Troupe_Remove, kJSPropertyAttributeDontDelete },
                { "clear", Troupe_Clear, kJSPropertyAttributeDontDelete },
                { "contains", Troupe_Contains, kJSPropertyAttributeDontDelete },
                { "getMemberCount", Troupe_GetMemberCount, kJSPropertyAttributeDontDelete },
                { 0, 0, 0 }
            };
            static JSClassRef jsClass = 0;
            if (!jsClass)
            {
                JSClassDefinition definition = kJSClassDefinitionEmpty;
                definition.parentClass = AnimatedBase_class();
                definition.finalize = Troupe_finalize;
                definition.className = "Troupe";
                definition.staticFunctions = Troupe_staticFunctions;
                definition.staticValues = Troupe_staticValues;
                definition.callAsConstructor = Troupe_new;
                jsClass = JSClassCreate(&definition);
            }
            return jsClass;

        }
#ifdef PDG_USING_JAVASCRIPT_CORE
        Troupe* New_Troupe(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
        {
#else
            TroupeWrap::TroupeWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_Troupe(args)) {}
            TroupeWrap::~TroupeWrap()
            {
                if(cppPtr_)
                {
                    cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr;
                }
            }
            Troupe* New_Troupe(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
            {
                if(s_Troupe_InNewFromCpp) return nullptr;
                auto* isolate=args.GetIsolate();
#endif
                JSContextRef ctx = gMainContext;
                JSValueRef _exception = 0;
                JSValueRef* exception = &_exception;
                if(argumentCount)
                {
                    s_SavedError.str(""); s_SavedError.clear();
                    s_SavedError << "Type Error: " << "Troupe accepts no constructor arguments";
                    s_HaveSavedError = true; return nullptr;
                }
                auto* value=new Troupe();
#ifdef PDG_USING_V8
                value->addRef(); value->mAnimatedScriptObj = thisObject;
#endif
                return value;
            }

            JSValueRef Troupe_PlayScript(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    if (!JSValueIsString(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
                    JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                    MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
                    JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
                    const char* name = (const char*)name_Mem.ptr;
                    JSStringRelease(name_Str);
                    self->playScript(name); return thisObject;
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
            JSValueRef Troupe_Batch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->batch(); return thisObject;
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
            JSValueRef Troupe_EndBatch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->endBatch(); return thisObject;
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
            JSValueRef Troupe_Series(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->series(); return thisObject;
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
            JSValueRef Troupe_EndSeries(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->endSeries(); return thisObject;
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
            JSValueRef Troupe_AndAlso(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->andAlso(); return thisObject;
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
            JSValueRef Troupe_Stagger(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""intervalSeconds"")");
                    double intervalSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
                    self->stagger(intervalSeconds); return thisObject;
                }
                catch(const std::exception& error)
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
            JSValueRef Troupe_Mark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
                    if(argumentCount>2)
                    {
                        if (argumentCount != 2)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                    }
                    if (!JSValueIsString(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
                    JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                    MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
                    JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
                    const char* name = (const char*)name_Mem.ptr;
                    JSStringRelease(name_Str);
                    if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""saveState"")");
                    bool saveState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
                    self->mark(name, saveState); return thisObject;
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
            JSValueRef Troupe_JumpToMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
                    if(argumentCount>2)
                    {
                        if (argumentCount != 2)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                    }
                    if (!JSValueIsString(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
                    JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                    MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
                    JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
                    const char* name = (const char*)name_Mem.ptr;
                    JSStringRelease(name_Str);
                    if (argumentCount >= 2 && !JSValueIsBoolean(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a boolean (""restoreState"")");
                    bool restoreState = (argumentCount<2) ? true : JSValueToBoolean(ctx, arguments[2 -1]);
                    self->jumpToMark(name, restoreState); return thisObject;
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
            JSValueRef Troupe_When(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
                    self->when(MakeAnimationEvaluator(evaluator)); return thisObject;
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
            JSValueRef Troupe_ScriptOn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 2)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                    if (!JSValueIsString(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""event"")");
                    JSStringRef event_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                    MemBlock event_Mem(JSStringGetMaximumUTF8CStringSize(event_Str));
                    JSStringGetUTF8CString(event_Str, event_Mem.ptr, event_Mem.bytes);
                    const char* event = (const char*)event_Mem.ptr;
                    JSStringRelease(event_Str);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[2 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a function (""handler"")");
                    self->on(event, MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnStarted(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onStarted(MakeAnimationEventHandler(handler)); return thisObject;
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
            JSValueRef Troupe_TriggerEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    if (!JSValueIsString(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""name"")");
                    JSStringRef name_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
                    MemBlock name_Mem(JSStringGetMaximumUTF8CStringSize(name_Str));
                    JSStringGetUTF8CString(name_Str, name_Mem.ptr, name_Mem.bytes);
                    const char* name = (const char*)name_Mem.ptr;
                    JSStringRelease(name_Str);
                    self->triggerEvent(name); return thisObject;
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

            JSValueRef Troupe_OnFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onFinished(MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnScriptFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onScriptFinished(MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onMark(MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnYoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onYoyo(MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnRepeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onRepeat(MakeAnimationEventHandler(handler)); return thisObject;
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

            JSValueRef Troupe_OnUntilFired(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    self->mAnimatedScriptObj = thisObject;
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef handler = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!handler || !JSObjectIsFunction(ctx, handler) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""handler"")");
                    self->onUntilFired(MakeAnimationEventHandler(handler)); return thisObject;
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
            JSValueRef Troupe_Otherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->otherwise(); return thisObject;
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
            JSValueRef Troupe_EndWhen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->endWhen(); return thisObject;
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
            JSValueRef Troupe_EndOtherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->endOtherwise(); return thisObject;
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
            JSValueRef Troupe_Until(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    JSObjectRef evaluator = JSValueToObject(ctx, arguments[1 -1], exception);
                    if (!evaluator || !JSObjectIsFunction(ctx, evaluator) )
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""evaluator"")");
                    self->until(MakeAnimationEvaluator(evaluator)); return thisObject;
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
            JSValueRef Troupe_Yoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->yoyo(); return thisObject;
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
            JSValueRef Troupe_Repeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0, true);
                    if (argumentCount>1)
                    {
                        if (argumentCount != 1)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                    }
                    if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""countValue"")");
                    double countValue = (argumentCount<1) ? -1 : JSValueToNumber(ctx, arguments[1 -1], exception);
                    if (argumentCount && (!std::isfinite(countValue) || countValue<0 || countValue>INT32_MAX || std::floor(countValue)!=countValue)) throw std::invalid_argument("Repeat count must be a nonnegative integer");
                    self->repeat(static_cast<int>(countValue)); return thisObject;
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
            JSValueRef Troupe_Diminish(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 2)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
                    if (argumentCount>3)
                    {
                        if (argumentCount != 3)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
                    }
                    if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
                    double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
                    if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
                    double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                    if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
                    long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
                    self->diminish(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
            JSValueRef Troupe_Increase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 2)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
                    if (argumentCount>3)
                    {
                        if (argumentCount != 3)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
                    }
                    if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
                    double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
                    if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
                    double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                    if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
                    long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
                    self->increase(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
            JSValueRef Troupe_SlowDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 2)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
                    if (argumentCount>3)
                    {
                        if (argumentCount != 3)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
                    }
                    if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
                    double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
                    if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
                    double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                    if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
                    long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
                    self->slowDown(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
            JSValueRef Troupe_SpeedUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount < 2)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true);
                    if (argumentCount>3)
                    {
                        if (argumentCount != 3)
                            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
                    }
                    if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
                    double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
                    if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
                    double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
                    if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
                    long easing = (argumentCount<3) ? 0 : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
                    self->speedUp(factor, seconds, easingIdToFunc(easing)); return thisObject;
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
            JSValueRef Troupe_StopIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->stopIt(); return thisObject;
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
            JSValueRef Troupe_RestartIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->restartIt(); return thisObject;
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
            JSValueRef Troupe_PauseIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->pauseIt(); return thisObject;
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
            JSValueRef Troupe_ResumeIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    self->resumeIt(); return thisObject;
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

            JSValueRef Troupe_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Rect value=self->getBoundingBox(); return JSC_RectToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::RotatedRect value=self->getRotatedBounds(); return JSC_RectToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Point value=self->getLocation(); return JSC_PointToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Offset value=self->getMovement(); return JSC_OffsetToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Offset value=self->getSize(); return JSC_OffsetToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    double value=self->getWidth(); return JSValueMakeNumber(ctx, value);
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

            JSValueRef Troupe_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    double value=self->getHeight(); return JSValueMakeNumber(ctx, value);
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

            JSValueRef Troupe_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Offset value=self->getScale(); return JSC_OffsetToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Offset value=self->getStretching(); return JSC_OffsetToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    double value=self->getRotation(); return JSValueMakeNumber(ctx, value);
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

            JSValueRef Troupe_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    pdg::Offset value=self->getCenterOffset(); return JSC_OffsetToValue(ctx, value, exception);
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

            JSValueRef Troupe_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
                    ;
                    if (argumentCount != 0)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                    double value=self->getSpin(); return JSValueMakeNumber(ctx, value);
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
            JSValueRef Troupe_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
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
            JSValueRef Troupe_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                try
                {
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
            JSValueRef Troupe_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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
            JSValueRef Troupe_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
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

            JSValueRef Troupe_RecordCommand(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));

                try
                {
                    if (argumentCount < 1)
                        return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (!JSValueIsNumber(ctx, arguments[1 -1]))
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""commandId"")");
                    int32 commandId = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
                    auto get = [&](auto value, const char* name)
                    {
                        if (!JSValueIsObject(ctx, value)) { throw std::invalid_argument("Expected options record"); }
#ifdef PDG_USING_JAVASCRIPT_CORE
                        auto key=JSStringCreateWithUTF8CString(name); auto result=JSObjectGetProperty(ctx,JSValueToObject(ctx,value,exception),key,exception); JSStringRelease(key);
                        if(exception && *exception) { throw std::invalid_argument("Unable to read animation argument"); }
                        return result;
#else
                        v8::Local<v8::Value> result;
                        if(!value.template As<v8::Object>()->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&result)) { throw std::invalid_argument("Unable to read animation argument"); }
                        return result;
#endif
                    };
                    auto number = [&](auto value) -> double
                    {
                        if (!JSValueIsNumber(ctx, value)) { throw std::invalid_argument("Expected numeric animation argument"); }
                        const double n=JSValueToNumber(ctx, value, exception); if(!std::isfinite(n)) { throw std::invalid_argument("Expected finite animation argument"); }
                        return n;
                    };
                    auto boolean = [&](auto value) -> bool
                    {
                        if (!JSValueIsBoolean(ctx, value)) { throw std::invalid_argument("Expected boolean animation argument"); }
                        return JSValueToBoolean(ctx, value);
                    };
                    auto easing = [&](auto value) -> EasingFunc
                    {
                        const double n=number(value); if(n<0 || n>=NUM_EASING_FUNCTIONS || std::floor(n)!=n) { throw std::invalid_argument("Invalid easing constant"); }
                        return gEasingFunctions[int(n)];
                    };
                    auto read = [&](int index, const std::string& kind) -> std::any
                    {
                        auto value=arguments[index+1];
                        if(kind=="number") return number(value);
                        if(kind=="boolean") return double(boolean(value));
                        if(kind=="string")
                        {
                            if(!JSValueIsString(ctx, value))
                            {
                                throw std::invalid_argument("Expected string animation argument");
                            } JSStringRef text_Str = JSValueToStringCopy(ctx, value, exception);
                            MemBlock text_Mem(JSStringGetMaximumUTF8CStringSize(text_Str));
                            JSStringGetUTF8CString(text_Str, text_Mem.ptr, text_Mem.bytes);
                            const char* text = (const char*)text_Mem.ptr;
                            JSStringRelease(text_Str); return std::string(text);
                        }
                        if(kind=="EasingFunc") return easing(value);
                        if(kind=="Point")
                        {
                            Point result; auto ok=JSC_ValueIsPoint(ctx, value, result, exception); if(!ok.has_value() || !*ok)
                            {
                                throw std::invalid_argument("Expected Point");
                            }
                            return result;
                        }
                        if(kind=="Offset")
                        {
                            Offset result; auto ok=JSC_ValueIsOffset(ctx, value, result, exception); if(!ok.has_value() || !*ok)
                            {
                                throw std::invalid_argument("Expected Offset");
                            }
                            return result;
                        }
                        if(kind=="Rect")
                        {
                            Rect result; auto ok=JSC_ValueIsRect(ctx, value, result, exception); if(!ok.has_value() || !*ok)
                            {
                                throw std::invalid_argument("Expected Rect");
                            }
                            return result;
                        }
                        if(kind=="Color")
                        {
                            Color result; auto ok=JSC_ValueIsColor(ctx, value, result, exception); if(!ok.has_value() || !*ok)
                            {
                                throw std::invalid_argument("Expected Color");
                            }
                            return result;
                        }
                        if(kind=="Camera")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Camera* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Camera_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Camera_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Camera");
                            }
                            return captureAnimationArgument(*object);
                        }
                        if(kind=="Sprite")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Sprite* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Sprite_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Sprite_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Sprite");
                            }
                            return captureAnimationArgument(object);
                        }
                        if(kind=="Part")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Part* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Part_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Part_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Part");
                            }
                            return captureAnimationArgument(object);
                        }
                        if(kind=="Particle")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Particle* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Particle_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Particle_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Particle");
                            }
                            return captureAnimationArgument(*object);
                        }
                        if(kind=="PhysicsConstraint")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } PhysicsConstraint* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = PhysicsConstraint_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = PhysicsConstraint_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected PhysicsConstraint");
                            }
                            return captureAnimationArgument(*object);
                        }
                        if(kind=="Animated")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } AnimatedBase* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = AnimatedBase_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = AnimatedBase_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Animated");
                            }
                            return captureAnimationArgument(*object);
                        }
#ifndef PDG_NO_GUI
                        if(kind=="Font")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Font* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Font_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Font_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Font");
                            }
                            return captureAnimationArgument(object);
                        }
#endif
#ifndef PDG_NO_GUI
                        if(kind=="Image")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Image* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Image_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Image_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Image");
                            }
                            return captureAnimationArgument(object);
                        }
#endif
#ifndef PDG_NO_GUI
                        if(kind=="Drawing")
                        {
                            if(JSValueIsNull(ctx, value))
                            {
                                return captureAnimationArgument(nullptr);
                            } Drawing* object = 0;
                            if (JSValueIsObject(ctx, value))
                            {
                                JSObjectRef object_obj_ = JSValueToObject(ctx, value, exception);
                                object = Drawing_getCppObject(object_obj_);
                                if (!object)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, object_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        object = Drawing_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!object)
                            {
                                throw std::invalid_argument("Expected Drawing");
                            }
                            return captureAnimationArgument(*object);
                        }
#endif
                        if(kind=="AffineTransform") { glm::mat3 m(1.f); m[0][0]=number(get(value,"a"));m[0][1]=number(get(value,"b"));m[1][0]=number(get(value,"c"));m[1][1]=number(get(value,"d"));m[2][0]=number(get(value,"tx"));m[2][1]=number(get(value,"ty"));return m; }
                        auto numericField = [&](const char* key,double fallback) { auto v=get(value,key); return JSValueIsUndefined(ctx, v)?fallback:number(v); };
                        if(kind=="ParticleTrailOptions") return readParticleTrailOptions(numericField,[&](Color fallback)
                        {
                            auto v=get(value,"color");if(JSValueIsUndefined(ctx, v))return fallback;Color result;auto ok=JSC_ValueIsColor(ctx, v, result, exception);if(!ok.has_value() || !*ok)
                            {
                                throw std::invalid_argument("Expected trail Color");
                            }
                            return result;
                        });
                        if(kind=="AnimationPhysicsDriveSettings") { AnimationPhysicsDriveSettings s; s.maxForce=numericField("maxForce",s.maxForce);s.maxTorque=numericField("maxTorque",s.maxTorque);s.frequency=numericField("frequency",s.frequency);s.dampingRatio=numericField("dampingRatio",s.dampingRatio);s.direction=int(numericField("direction",s.direction));return s; }
                        if(kind=="CameraMatchOptions")
                        {
                            CameraMatchOptions s;
                            auto sourceValue=get(value,"matchSource"),targetValue=get(value,"matchTarget");
                            Sprite* source = 0;
                            if (JSValueIsObject(ctx, sourceValue))
                            {
                                JSObjectRef source_obj_ = JSValueToObject(ctx, sourceValue, exception);
                                source = Sprite_getCppObject(source_obj_);
                                if (!source)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, source_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        source = Sprite_getCppObject(protoObj_);
                                    }
                                }
                            }; Sprite* destination = 0;
                            if (JSValueIsObject(ctx, targetValue))
                            {
                                JSObjectRef destination_obj_ = JSValueToObject(ctx, targetValue, exception);
                                destination = Sprite_getCppObject(destination_obj_);
                                if (!destination)
                                {
                                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, destination_obj_);
                                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                                    {
                                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                                        destination = Sprite_getCppObject(protoObj_);
                                    }
                                }
                            };
                            if(!source || !destination) { throw std::invalid_argument("Expected matchSource and matchTarget Sprites"); }
                            s.matchSource=source;s.matchTarget=destination;
                            s.mode=CameraMatchMode(int(numericField("mode",s.mode)));s.approachSeconds=numericField("approachSeconds",s.approachSeconds);s.settleSeconds=numericField("settleSeconds",s.settleSeconds);s.fadeSeconds=numericField("fadeSeconds",s.fadeSeconds);
                            auto restore=get(value,"settleReturnsCamera");if(!JSValueIsUndefined(ctx, restore))s.settleReturnsCamera=boolean(restore);
                            auto a=get(value,"approachEasing"),b=get(value,"settleEasing"),c=get(value,"fadeEasing");if(!JSValueIsUndefined(ctx, a))s.approachEasing=easing(a);if(!JSValueIsUndefined(ctx, b))s.settleEasing=easing(b);if(!JSValueIsUndefined(ctx, c))s.fadeEasing=easing(c);return captureRecorderMatchOptions(s);
                        }
                        throw std::invalid_argument("Unsupported animation argument type");
                    };
                    recordScriptCommand(*self, commandId, argumentCount-1, read); return thisObject;
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
            JSValueRef Troupe_Animate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                self->mAnimatedScriptObj = thisObject;
                ;
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""deltaSeconds"")");
                double deltaSeconds = JSValueToNumber(ctx, arguments[1 -1], exception);
                try { return JSValueMakeBoolean(ctx, self->animate(deltaSeconds)); }
                catch(const std::exception& error)
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
            JSValueRef Troupe_Add(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                ;
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
#ifdef PDG_USING_V8
                auto* member=V8_GetAnimationTarget(isolate,arguments[0]);
#else
                auto* member=JSC_GetAnimationTarget(ctx,arguments[0]);
#endif
                if(!member)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an Animated target" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                try { self->add(*member); return thisObject; }
                catch(const std::exception& error)
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
            JSValueRef Troupe_Remove(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                ;
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
#ifdef PDG_USING_V8
                auto* member=V8_GetAnimationTarget(isolate,arguments[0]);
#else
                auto* member=JSC_GetAnimationTarget(ctx,arguments[0]);
#endif
                if(!member)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an Animated target" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                try { self->remove(*member); return thisObject; }
                catch(const std::exception& error)
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
            JSValueRef Troupe_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                ;
                if (argumentCount != 0)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
                try { self->clear(); return thisObject; }
                catch(const std::exception& error)
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
            JSValueRef Troupe_Contains(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                ;
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
#ifdef PDG_USING_V8
                auto* member=V8_GetAnimationTarget(isolate,arguments[0]);
#else
                auto* member=JSC_GetAnimationTarget(ctx,arguments[0]);
#endif
                if(!member)
                {
                    std::ostringstream excpt_;
                    excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected an Animated target" << "')";
                    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                    return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
                }
                return JSValueMakeBoolean(ctx, self->contains(*member));
            }
            JSValueRef Troupe_GetMemberCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
            {
                Troupe* self = static_cast<Troupe*>(JSObjectGetPrivate(thisObject));
                ;
                if (argumentCount != 0)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMemberCount());
            }
            void CleanupTroupeScriptObject(JSObjectRef obj) { }

        }
