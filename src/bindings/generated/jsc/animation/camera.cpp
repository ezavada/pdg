// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/camera.cpp
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
#include <cmath>
#include <limits>

namespace pdg
{

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void Camera_finalize(JSObjectRef object)
    {
        auto* value=static_cast<Camera*>(JSObjectGetPrivate(object)); if (!value) return;
        value->mCameraScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mEventEmitterScriptObj=nullptr;
        JSObjectSetPrivate(object,nullptr); value->release();
    }
#define CAMERA_SAVE(cppObj,obj) cppObj->mCameraScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mEventEmitterScriptObj=obj
#else
#define CAMERA_SAVE(cppObj,obj) cppObj->mCameraScriptObj.Reset(isolate,obj); cppObj->mCameraScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mEventEmitterScriptObj.Reset(isolate,obj); cppObj->mEventEmitterScriptObj.SetWeak()
#endif
    JSObjectRef Camera_newFromCpp(JSContextRef ctx, Camera* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Camera_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Camera_class());
        CAMERA_SAVE(cppObj,obj); cppObj->addRef();
        return obj;
    }

    JSObjectRef Camera_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* cppObj = New_Camera(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Camera" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Camera_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Camera_class());
        CAMERA_SAVE(cppObj,obj); cppObj->addRef();
        return obj;
    }

    JSClassRef Camera_class()
    {
        static JSStaticValue Camera_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Camera_staticFunctions[] =
        {
            { "playScript", Camera_PlayScript, kJSPropertyAttributeDontDelete },
            { "batch", Camera_Batch, kJSPropertyAttributeDontDelete },
            { "endBatch", Camera_EndBatch, kJSPropertyAttributeDontDelete },
            { "series", Camera_Series, kJSPropertyAttributeDontDelete },
            { "endSeries", Camera_EndSeries, kJSPropertyAttributeDontDelete },
            { "andAlso", Camera_AndAlso, kJSPropertyAttributeDontDelete },
            { "stagger", Camera_Stagger, kJSPropertyAttributeDontDelete },
            { "mark", Camera_Mark, kJSPropertyAttributeDontDelete },
            { "jumpToMark", Camera_JumpToMark, kJSPropertyAttributeDontDelete },
            { "on", Camera_ScriptOn, kJSPropertyAttributeDontDelete },
            { "triggerEvent", Camera_TriggerEvent, kJSPropertyAttributeDontDelete },
            { "onStarted", Camera_OnStarted, kJSPropertyAttributeDontDelete },
            { "onFinished", Camera_OnFinished, kJSPropertyAttributeDontDelete },
            { "onScriptFinished", Camera_OnScriptFinished, kJSPropertyAttributeDontDelete },
            { "onMark", Camera_OnMark, kJSPropertyAttributeDontDelete },
            { "onYoyo", Camera_OnYoyo, kJSPropertyAttributeDontDelete },
            { "onRepeat", Camera_OnRepeat, kJSPropertyAttributeDontDelete },
            { "onUntilFired", Camera_OnUntilFired, kJSPropertyAttributeDontDelete },
            { "when", Camera_When, kJSPropertyAttributeDontDelete },
            { "otherwise", Camera_Otherwise, kJSPropertyAttributeDontDelete },
            { "endWhen", Camera_EndWhen, kJSPropertyAttributeDontDelete },
            { "endOtherwise", Camera_EndOtherwise, kJSPropertyAttributeDontDelete },
            { "until", Camera_Until, kJSPropertyAttributeDontDelete },
            { "yoyo", Camera_Yoyo, kJSPropertyAttributeDontDelete },
            { "repeat", Camera_Repeat, kJSPropertyAttributeDontDelete },
            { "diminish", Camera_Diminish, kJSPropertyAttributeDontDelete },
            { "increase", Camera_Increase, kJSPropertyAttributeDontDelete },
            { "slowDown", Camera_SlowDown, kJSPropertyAttributeDontDelete },
            { "speedUp", Camera_SpeedUp, kJSPropertyAttributeDontDelete },
            { "stopIt", Camera_StopIt, kJSPropertyAttributeDontDelete },
            { "restartIt", Camera_RestartIt, kJSPropertyAttributeDontDelete },
            { "pauseIt", Camera_PauseIt, kJSPropertyAttributeDontDelete },
            { "resumeIt", Camera_ResumeIt, kJSPropertyAttributeDontDelete },
            { "getBoundingBox", Camera_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", Camera_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", Camera_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", Camera_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", Camera_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", Camera_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", Camera_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", Camera_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", Camera_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", Camera_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", Camera_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", Camera_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", Camera_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", Camera_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", Camera_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", Camera_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", Camera_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", Camera_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", Camera_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", Camera_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", Camera_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", Camera_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", Camera_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", Camera_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", Camera_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", Camera_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", Camera_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", Camera_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", Camera_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", Camera_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", Camera_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", Camera_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", Camera_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", Camera_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", Camera_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", Camera_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", Camera_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", Camera_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", Camera_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", Camera_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", Camera_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", Camera_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", Camera_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", Camera_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", Camera_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", Camera_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", Camera_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", Camera_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", Camera_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", Camera_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", Camera_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", Camera_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", Camera_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", Camera_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", Camera_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", Camera_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", Camera_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", Camera_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", Camera_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", Camera_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", Camera_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", Camera_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", Camera_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "addHandler", Camera_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", Camera_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", Camera_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", Camera_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", Camera_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "get""Zoom", Camera_GetZoom, kJSPropertyAttributeDontDelete },
            { "set""Zoom", Camera_SetZoom, kJSPropertyAttributeDontDelete },
            { "get""PixelSnapping", Camera_GetPixelSnapping, kJSPropertyAttributeDontDelete },
            { "set""PixelSnapping", Camera_SetPixelSnapping, kJSPropertyAttributeDontDelete },
            { "zoom", Camera_Zoom, kJSPropertyAttributeDontDelete },
            { "zoomTo", Camera_ZoomTo, kJSPropertyAttributeDontDelete },
            { "animate", Camera_Animate, kJSPropertyAttributeDontDelete },
            { "follow", Camera_Follow, kJSPropertyAttributeDontDelete },
            { "stopFollowing", Camera_StopFollowing, kJSPropertyAttributeDontDelete },
            { "isFollowing", Camera_IsFollowing, kJSPropertyAttributeDontDelete },
            { "setSmoothing", Camera_SetSmoothing, kJSPropertyAttributeDontDelete },
            { "getSmoothing", Camera_GetSmoothing, kJSPropertyAttributeDontDelete },
            { "setLookAhead", Camera_SetLookAhead, kJSPropertyAttributeDontDelete },
            { "getLookAhead", Camera_GetLookAhead, kJSPropertyAttributeDontDelete },
            { "setDeadzone", Camera_SetDeadzone, kJSPropertyAttributeDontDelete },
            { "getDeadzone", Camera_GetDeadzone, kJSPropertyAttributeDontDelete },
            { "setFollowOffset", Camera_SetFollowOffset, kJSPropertyAttributeDontDelete },
            { "getFollowOffset", Camera_GetFollowOffset, kJSPropertyAttributeDontDelete },
            { "setViewBounds", Camera_SetViewBounds, kJSPropertyAttributeDontDelete },
            { "clearViewBounds", Camera_ClearViewBounds, kJSPropertyAttributeDontDelete },
            { "hasViewBounds", Camera_HasViewBounds, kJSPropertyAttributeDontDelete },
            { "getViewBounds", Camera_GetViewBounds, kJSPropertyAttributeDontDelete },
            { "setViewport", Camera_SetViewport, kJSPropertyAttributeDontDelete },
            { "getViewport", Camera_GetViewport, kJSPropertyAttributeDontDelete },
            { "worldToView", Camera_WorldToView, kJSPropertyAttributeDontDelete },
            { "viewToWorld", Camera_ViewToWorld, kJSPropertyAttributeDontDelete },
            { "getEffects", Camera_GetEffects, kJSPropertyAttributeDontDelete },
            { "flash", Camera_Flash, kJSPropertyAttributeDontDelete },
            { "getFlashOpacity", Camera_GetFlashOpacity, kJSPropertyAttributeDontDelete },
            { "show", Camera_Show, kJSPropertyAttributeDontDelete },
            { "hide", Camera_Hide, kJSPropertyAttributeDontDelete },
            { "isHidden", Camera_IsHidden, kJSPropertyAttributeDontDelete },
            { "setOpacity", Camera_SetOpacity, kJSPropertyAttributeDontDelete },
            { "getOpacity", Camera_GetOpacity, kJSPropertyAttributeDontDelete },
            { "fadeTo", Camera_FadeTo, kJSPropertyAttributeDontDelete },
            { "fadeIn", Camera_FadeIn, kJSPropertyAttributeDontDelete },
            { "fadeOut", Camera_FadeOut, kJSPropertyAttributeDontDelete },
            { "cutTo", Camera_CutTo, kJSPropertyAttributeDontDelete },
            { "matchCutTo", Camera_MatchCutTo, kJSPropertyAttributeDontDelete },
            { "matchFadeTo", Camera_MatchFadeTo, kJSPropertyAttributeDontDelete },
            { "transitionTo", Camera_TransitionTo, kJSPropertyAttributeDontDelete },
            { "lumaFadeTo", Camera_LumaFadeTo, kJSPropertyAttributeDontDelete },
            { "whipPanTo", Camera_WhipPanTo, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.parentClass = AnimatedBase_class();
            definition.finalize = Camera_finalize;
            definition.className = "Camera";
            definition.staticFunctions = Camera_staticFunctions;
            definition.staticValues = Camera_staticValues;
            definition.callAsConstructor = Camera_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef Camera_PlayScript(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Batch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_EndBatch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Series(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_EndSeries(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_AndAlso(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Stagger(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Mark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_JumpToMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_When(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ScriptOn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnStarted(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_TriggerEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnScriptFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnYoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnRepeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_OnUntilFired(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Otherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_EndWhen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_EndOtherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Until(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Yoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Repeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Diminish(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Increase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SlowDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SpeedUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_StopIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_RestartIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_PauseIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ResumeIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Camera_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef Camera_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->addHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Camera_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
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
        long inType = (argumentCount<2) ? pdg::all_events : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
        self->removeHandler(inHandler, inType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Camera_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Camera_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Camera_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Camera_GetZoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        double theZoom = self->getZoom();
        return JSValueMakeNumber(ctx, theZoom);
    }
    JSValueRef Camera_SetZoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""zoom"")");
            double zoom = JSValueToNumber(ctx, arguments[1 -1], exception); self->setZoom(zoom); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Camera_GetPixelSnapping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));

        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool thePixelSnapping = self->getPixelSnapping();
        return JSValueMakeBoolean(ctx, thePixelSnapping);
    }
    JSValueRef Camera_SetPixelSnapping(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount >= 1 && !JSValueIsBoolean(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""snap"")");
        bool snap = (argumentCount<1) ? true : JSValueToBoolean(ctx, arguments[1 -1]); self->setPixelSnapping(snap); return thisObject;
    }
    JSValueRef Camera_ZoomTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""zoom"")");
            double zoom = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing=static_cast<int>(easingValue);
            if (!gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->zoomTo(zoom,seconds,gEasingFunctions[easing]); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Camera_Zoom(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easingValue"")");
            double easingValue = (argumentCount<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : JSValueToNumber(ctx, arguments[3 -1], exception);
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected an integer easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const int easing=static_cast<int>(easingValue);
            if (!gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Unknown easing constant" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            self->zoom(factor,seconds,gEasingFunctions[easing]); return thisObject;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Camera_Animate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); return JSValueMakeBoolean(ctx, self->animate(seconds));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
#ifdef PDG_USING_JAVASCRIPT_CORE
    Camera* New_Camera(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return new Camera(); }
#else
    CameraWrap::CameraWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_Camera(args)) {}
    CameraWrap::~CameraWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mCameraScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr;
        }
    }
    Camera* New_Camera(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        if (s_Camera_InNewFromCpp) return nullptr;
        auto* isolate=args.GetIsolate(); auto* cppObj=new Camera(); cppObj->addRef();
        CAMERA_SAVE(cppObj,args.This()); return cppObj;
    }
#endif
#undef CAMERA_SAVE
    JSValueRef Camera_Follow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);AnimatedBase* target=nullptr;
            if (JSValueIsObjectOfClass(ctx, arguments[0], Sprite_class()))
            {
                Sprite* value = 0;
                if (JSValueIsObject(ctx, arguments[0]))
                {
                    JSObjectRef value_obj_ = JSValueToObject(ctx, arguments[0], exception);
                    value = Sprite_getCppObject(value_obj_);
                    if (!value)
                    {
                        JSValueRef protoVal_ = JSObjectGetPrototype(ctx, value_obj_);
                        if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                        {
                            JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                            value = Sprite_getCppObject(protoObj_);
                        }
                    }
                };
                target=value;
            }
            else if (JSValueIsObjectOfClass(ctx, arguments[0], Camera_class()))
            {
                Camera* value = 0;
                if (JSValueIsObject(ctx, arguments[0]))
                {
                    JSObjectRef value_obj_ = JSValueToObject(ctx, arguments[0], exception);
                    value = Camera_getCppObject(value_obj_);
                    if (!value)
                    {
                        JSValueRef protoVal_ = JSObjectGetPrototype(ctx, value_obj_);
                        if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                        {
                            JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                            value = Camera_getCppObject(protoObj_);
                        }
                    }
                };
                target=value;
            }
            else if (JSValueIsObjectOfClass(ctx, arguments[0], Particle_class()))
            {
                Particle* value = 0;
                if (JSValueIsObject(ctx, arguments[0]))
                {
                    JSObjectRef value_obj_ = JSValueToObject(ctx, arguments[0], exception);
                    value = Particle_getCppObject(value_obj_);
                    if (!value)
                    {
                        JSValueRef protoVal_ = JSObjectGetPrototype(ctx, value_obj_);
                        if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                        {
                            JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                            value = Particle_getCppObject(protoObj_);
                        }
                    }
                };
                target=value;
            }
            else if (JSValueIsObjectOfClass(ctx, arguments[0], ParticleEmitter_class()))
            {
                ParticleEmitter* value = 0;
                if (JSValueIsObject(ctx, arguments[0]))
                {
                    JSObjectRef value_obj_ = JSValueToObject(ctx, arguments[0], exception);
                    value = ParticleEmitter_getCppObject(value_obj_);
                    if (!value)
                    {
                        JSValueRef protoVal_ = JSObjectGetPrototype(ctx, value_obj_);
                        if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                        {
                            JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                            value = ParticleEmitter_getCppObject(protoObj_);
                        }
                    }
                };
                target=value;
            }
            else if (JSValueIsObjectOfClass(ctx, arguments[0], AnimatedBase_class()))
            {
                AnimatedBase* value = 0;
                if (JSValueIsObject(ctx, arguments[0]))
                {
                    JSObjectRef value_obj_ = JSValueToObject(ctx, arguments[0], exception);
                    value = AnimatedBase_getCppObject(value_obj_);
                    if (!value)
                    {
                        JSValueRef protoVal_ = JSObjectGetPrototype(ctx, value_obj_);
                        if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                        {
                            JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                            value = AnimatedBase_getCppObject(protoObj_);
                        }
                    }
                };
                target=value;
            }
            if (!target) throw std::invalid_argument("Expected an Animated target");
            self->follow(*target);return thisObject;
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
    JSValueRef Camera_StopFollowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->stopFollowing(); return thisObject;
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
    JSValueRef Camera_ClearViewBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->clearViewBounds(); return thisObject;
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
    JSValueRef Camera_IsFollowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isFollowing());
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
    JSValueRef Camera_HasViewBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->hasViewBounds());
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
    JSValueRef Camera_SetSmoothing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); self->setSmoothing(seconds); return thisObject;
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
    JSValueRef Camera_GetSmoothing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getSmoothing());
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
    JSValueRef Camera_SetLookAhead(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); self->setLookAhead(seconds); return thisObject;
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
    JSValueRef Camera_GetLookAhead(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getLookAhead());
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
    JSValueRef Camera_SetDeadzone(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->setDeadzone(bounds); return thisObject;
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
    JSValueRef Camera_GetDeadzone(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getDeadzone(); return JSC_RectToValue(ctx, value, exception);
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
    JSValueRef Camera_SetViewBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect bounds;
            auto bounds_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], bounds, exception);
            if (!bounds_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*bounds_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->setViewBounds(bounds); return thisObject;
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
    JSValueRef Camera_GetViewBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getViewBounds(); return JSC_RectToValue(ctx, value, exception);
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
    JSValueRef Camera_SetFollowOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->setFollowOffset(offset); return thisObject;
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
    JSValueRef Camera_GetFollowOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getFollowOffset(); return JSC_OffsetToValue(ctx, value, exception);
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
    JSValueRef Camera_SetViewport(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Rect viewport;
            auto viewport_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], viewport, exception);
            if (!viewport_isRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*viewport_isRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
            };
            self->setViewport(viewport); return thisObject;
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
    JSValueRef Camera_GetViewport(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getViewport(); return JSC_RectToValue(ctx, value, exception);
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
    JSValueRef Camera_WorldToView(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            auto value=self->worldToView(point); return JSC_PointToValue(ctx, value, exception);
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
    JSValueRef Camera_ViewToWorld(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            };
            auto value=self->viewToWorld(point); return JSC_PointToValue(ctx, value, exception);
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
    JSValueRef Camera_GetEffects(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* effects=&self->getEffects(); if (!effects) return JSValueMakeNull(ctx);
            if (!effects->mCameraScriptObj)
            {
                return Camera_newFromCpp(ctx, effects);
            }
            else
            {
                return effects->mCameraScriptObj;
            };
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
    JSValueRef Camera_GetFlashOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getFlashOpacity());
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
    JSValueRef Camera_Flash(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            } if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
            double opacity = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? easingFuncToId(easeOutQuad) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid flash easing");
            self->flash(opacity,seconds,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->show(); return thisObject;
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
    JSValueRef Camera_Hide(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->hide(); return thisObject;
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
    JSValueRef Camera_IsHidden(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isHidden());
    }
    JSValueRef Camera_SetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
            double opacity = JSValueToNumber(ctx, arguments[1 -1], exception); self->setOpacity(opacity); return thisObject;
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
    JSValueRef Camera_GetOpacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getOpacity());
    }
    JSValueRef Camera_FadeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount>3)
            {
                if (argumentCount != 3)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
            } if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""opacity"")");
            double opacity = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""easing"")");
            long easing = (argumentCount<3) ? easingFuncToId(linearTween) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
            self->fadeTo(opacity,seconds,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_FadeIn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            } if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
            long easing = (argumentCount<2) ? easingFuncToId(linearTween) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
            self->fadeIn(seconds,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_FadeOut(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount>2)
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            } if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""easing"")");
            long easing = (argumentCount<2) ? easingFuncToId(linearTween) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[2 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid fade easing");
            self->fadeOut(seconds,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_CutTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (!destination) throw std::invalid_argument("Expected destination Camera"); self->cutTo(*destination); return thisObject;
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
    static JSStringRef symbol_matchSource = 0;
    static JSStringRef symbol_matchTarget = 0;
    static JSStringRef symbol_mode = 0;
    static JSStringRef symbol_approachSeconds = 0;
    static JSStringRef symbol_settleSeconds = 0;
    static JSStringRef symbol_settleReturnsCamera = 0;
    static JSStringRef symbol_approachEasing = 0;
    static JSStringRef symbol_settleEasing = 0;
    static JSStringRef symbol_fadeSeconds = 0;
    static JSStringRef symbol_fadeEasing = 0;
    JSValueRef Camera_MatchCutTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsObjectOfClass(ctx, arguments[0], Camera_class())) throw std::invalid_argument("Expected destination Camera");
            Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (!JSValueIsObject(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object (""options"")");
            JSObjectRef options = JSValueToObject(ctx, arguments[2 -1], exception);
            auto read=[&](auto key)
            {
                auto value=JSObjectGetProperty(ctx, options, key, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
                if (!value || (exception && *exception)) throw std::invalid_argument("Unable to read matching option");
#else
                if (value.IsEmpty()) throw std::invalid_argument("Unable to read matching option");
#endif
                return value;
            };
            if (!destination) throw std::invalid_argument("Expected destination Camera");
            CameraMatchOptions settings;
            auto sourceValue=read(((symbol_matchSource) ? symbol_matchSource : symbol_matchSource = JSStringCreateWithUTF8CString("matchSource")));
            auto targetValue=read(((symbol_matchTarget) ? symbol_matchTarget : symbol_matchTarget = JSStringCreateWithUTF8CString("matchTarget")));
            if (!JSValueIsObjectOfClass(ctx, sourceValue, Sprite_class()) || !JSValueIsObjectOfClass(ctx, targetValue, Sprite_class()))
                throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
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
            };
            Sprite* target = 0;
            if (JSValueIsObject(ctx, targetValue))
            {
                JSObjectRef target_obj_ = JSValueToObject(ctx, targetValue, exception);
                target = Sprite_getCppObject(target_obj_);
                if (!target)
                {
                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, target_obj_);
                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                    {
                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                        target = Sprite_getCppObject(protoObj_);
                    }
                }
            };
            if (!source || !target) throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
            settings.matchSource=source;settings.matchTarget=target;
            auto mode=read(((symbol_mode) ? symbol_mode : symbol_mode = JSStringCreateWithUTF8CString("mode")));
            if (!JSValueIsUndefined(ctx, mode))
            {
                if (!JSValueIsNumber(ctx, mode)) throw std::invalid_argument("Expected camera match mode");
                const double id=JSValueToNumber(ctx, mode, exception);
                if (!std::isfinite(id) || std::floor(id)!=id || id<static_cast<int>(matchSource) || id>static_cast<int>(matchTargetAndSize))
                    throw std::invalid_argument("Invalid camera match mode");
                settings.mode=static_cast<CameraMatchMode>(static_cast<int>(id));
            }
            auto approach=read(((symbol_approachSeconds) ? symbol_approachSeconds : symbol_approachSeconds = JSStringCreateWithUTF8CString("approachSeconds")));
            if (!JSValueIsUndefined(ctx, approach)) {if (!JSValueIsNumber(ctx, approach)) throw std::invalid_argument("Expected numeric approachSeconds");settings.approachSeconds=JSValueToNumber(ctx, approach, exception);}
            auto settle=read(((symbol_settleSeconds) ? symbol_settleSeconds : symbol_settleSeconds = JSStringCreateWithUTF8CString("settleSeconds")));
            if (!JSValueIsUndefined(ctx, settle)) {if (!JSValueIsNumber(ctx, settle)) throw std::invalid_argument("Expected numeric settleSeconds");settings.settleSeconds=JSValueToNumber(ctx, settle, exception);}
            auto restore=read(((symbol_settleReturnsCamera) ? symbol_settleReturnsCamera : symbol_settleReturnsCamera = JSStringCreateWithUTF8CString("settleReturnsCamera")));
            if (!JSValueIsUndefined(ctx, restore)) {if (!JSValueIsBoolean(ctx, restore)) throw std::invalid_argument("Expected boolean settleReturnsCamera");settings.settleReturnsCamera=JSValueToBoolean(ctx, restore);}
            auto approachEase=read(((symbol_approachEasing) ? symbol_approachEasing : symbol_approachEasing = JSStringCreateWithUTF8CString("approachEasing")));
            if (!JSValueIsUndefined(ctx, approachEase))
            {
                if (!JSValueIsNumber(ctx, approachEase)) throw std::invalid_argument("Invalid approachEasing");
                const double id=JSValueToNumber(ctx, approachEase, exception);
                if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid approachEasing");
                settings.approachEasing=gEasingFunctions[static_cast<int>(id)];
            }
            auto settleEase=read(((symbol_settleEasing) ? symbol_settleEasing : symbol_settleEasing = JSStringCreateWithUTF8CString("settleEasing")));
            if (!JSValueIsUndefined(ctx, settleEase))
            {
                if (!JSValueIsNumber(ctx, settleEase)) throw std::invalid_argument("Invalid settleEasing");
                const double id=JSValueToNumber(ctx, settleEase, exception);
                if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid settleEasing");
                settings.settleEasing=gEasingFunctions[static_cast<int>(id)];
            }
            self->matchCutTo(*destination,settings);return thisObject;
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
    JSValueRef Camera_MatchFadeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsObjectOfClass(ctx, arguments[0], Camera_class())) throw std::invalid_argument("Expected destination Camera");
            Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (!JSValueIsObject(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object (""options"")");
            JSObjectRef options = JSValueToObject(ctx, arguments[2 -1], exception);
            auto read=[&](auto key)
            {
                auto value=JSObjectGetProperty(ctx, options, key, exception);
#ifdef PDG_USING_JAVASCRIPT_CORE
                if (!value || (exception && *exception)) throw std::invalid_argument("Unable to read matching option");
#else
                if (value.IsEmpty()) throw std::invalid_argument("Unable to read matching option");
#endif
                return value;
            };
            if (!destination) throw std::invalid_argument("Expected destination Camera");
            CameraMatchOptions settings;
            auto sourceValue=read(((symbol_matchSource) ? symbol_matchSource : symbol_matchSource = JSStringCreateWithUTF8CString("matchSource")));
            auto targetValue=read(((symbol_matchTarget) ? symbol_matchTarget : symbol_matchTarget = JSStringCreateWithUTF8CString("matchTarget")));
            if (!JSValueIsObjectOfClass(ctx, sourceValue, Sprite_class()) || !JSValueIsObjectOfClass(ctx, targetValue, Sprite_class()))
                throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
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
            };
            Sprite* target = 0;
            if (JSValueIsObject(ctx, targetValue))
            {
                JSObjectRef target_obj_ = JSValueToObject(ctx, targetValue, exception);
                target = Sprite_getCppObject(target_obj_);
                if (!target)
                {
                    JSValueRef protoVal_ = JSObjectGetPrototype(ctx, target_obj_);
                    if (protoVal_ && JSValueIsObject(ctx, protoVal_))
                    {
                        JSObjectRef protoObj_ = JSValueToObject(ctx, protoVal_, exception);
                        target = Sprite_getCppObject(protoObj_);
                    }
                }
            };
            if (!source || !target) throw std::invalid_argument("Expected matchSource and matchTarget Sprites");
            settings.matchSource=source;settings.matchTarget=target;
            auto mode=read(((symbol_mode) ? symbol_mode : symbol_mode = JSStringCreateWithUTF8CString("mode")));
            if (!JSValueIsUndefined(ctx, mode))
            {
                if (!JSValueIsNumber(ctx, mode)) throw std::invalid_argument("Expected camera match mode");
                const double id=JSValueToNumber(ctx, mode, exception);
                if (!std::isfinite(id) || std::floor(id)!=id || id<static_cast<int>(matchSource) || id>static_cast<int>(matchTargetAndSize))
                    throw std::invalid_argument("Invalid camera match mode");
                settings.mode=static_cast<CameraMatchMode>(static_cast<int>(id));
            }
            auto approach=read(((symbol_approachSeconds) ? symbol_approachSeconds : symbol_approachSeconds = JSStringCreateWithUTF8CString("approachSeconds")));
            if (!JSValueIsUndefined(ctx, approach)) {if (!JSValueIsNumber(ctx, approach)) throw std::invalid_argument("Expected numeric approachSeconds");settings.approachSeconds=JSValueToNumber(ctx, approach, exception);}
            auto settle=read(((symbol_settleSeconds) ? symbol_settleSeconds : symbol_settleSeconds = JSStringCreateWithUTF8CString("settleSeconds")));
            if (!JSValueIsUndefined(ctx, settle)) {if (!JSValueIsNumber(ctx, settle)) throw std::invalid_argument("Expected numeric settleSeconds");settings.settleSeconds=JSValueToNumber(ctx, settle, exception);}
            auto restore=read(((symbol_settleReturnsCamera) ? symbol_settleReturnsCamera : symbol_settleReturnsCamera = JSStringCreateWithUTF8CString("settleReturnsCamera")));
            if (!JSValueIsUndefined(ctx, restore)) {if (!JSValueIsBoolean(ctx, restore)) throw std::invalid_argument("Expected boolean settleReturnsCamera");settings.settleReturnsCamera=JSValueToBoolean(ctx, restore);}
            auto approachEase=read(((symbol_approachEasing) ? symbol_approachEasing : symbol_approachEasing = JSStringCreateWithUTF8CString("approachEasing")));
            if (!JSValueIsUndefined(ctx, approachEase))
            {
                if (!JSValueIsNumber(ctx, approachEase)) throw std::invalid_argument("Invalid approachEasing");
                const double id=JSValueToNumber(ctx, approachEase, exception);
                if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid approachEasing");
                settings.approachEasing=gEasingFunctions[static_cast<int>(id)];
            }
            auto settleEase=read(((symbol_settleEasing) ? symbol_settleEasing : symbol_settleEasing = JSStringCreateWithUTF8CString("settleEasing")));
            if (!JSValueIsUndefined(ctx, settleEase))
            {
                if (!JSValueIsNumber(ctx, settleEase)) throw std::invalid_argument("Invalid settleEasing");
                const double id=JSValueToNumber(ctx, settleEase, exception);
                if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid settleEasing");
                settings.settleEasing=gEasingFunctions[static_cast<int>(id)];
            }
            auto fade=read(((symbol_fadeSeconds) ? symbol_fadeSeconds : symbol_fadeSeconds = JSStringCreateWithUTF8CString("fadeSeconds")));
            if (!JSValueIsUndefined(ctx, fade)) {if (!JSValueIsNumber(ctx, fade)) throw std::invalid_argument("Expected numeric fadeSeconds");settings.fadeSeconds=JSValueToNumber(ctx, fade, exception);}
            auto fadeEase=read(((symbol_fadeEasing) ? symbol_fadeEasing : symbol_fadeEasing = JSStringCreateWithUTF8CString("fadeEasing")));
            if (!JSValueIsUndefined(ctx, fadeEase))
            {
                if (!JSValueIsNumber(ctx, fadeEase)) throw std::invalid_argument("Invalid fadeEasing");
                const double id=JSValueToNumber(ctx, fadeEase, exception);
                if (!std::isfinite(id) || id<0 || id>=NUM_EASING_FUNCTIONS || std::floor(id)!=id) throw std::invalid_argument("Invalid fadeEasing");
                settings.fadeEasing=gEasingFunctions[static_cast<int>(id)];
            }
            self->matchFadeTo(*destination,settings);return thisObject;
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
    JSValueRef Camera_TransitionTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount>4)
            {
                if (argumentCount != 4)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4);
            } Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""style"")");
            long style = (argumentCount<3) ? camera_Crossfade : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception)); if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""easing"")");
            long easing = (argumentCount<4) ? easingFuncToId(easeInOutQuad) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[4 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid transition easing");
            self->transitionTo(*destination,seconds,style,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_LumaFadeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount>6)
            {
                if (argumentCount != 6)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 6);
            } Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            Image* mask=nullptr; if (argumentCount>2 && !JSValueIsNull(ctx, arguments[2]) && !JSValueIsUndefined(ctx, arguments[2]))
            {
                Image* value = 0;
                if (JSValueIsObject(ctx, arguments[3 -1]))
                {
                    JSObjectRef value_ = JSValueToObject(ctx, arguments[3 -1], exception);
                    value = Image_getCppObject(value_);
                }
                if (!value)
                    return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""Image"" (""value"")");mask=value;
            }
            if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""softness"")");
            double softness = (argumentCount<4) ? .1 : JSValueToNumber(ctx, arguments[4 -1], exception); if (argumentCount >= 5 && !JSValueIsBoolean(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a boolean (""darkFirst"")");
            bool darkFirst = (argumentCount<5) ? false : JSValueToBoolean(ctx, arguments[5 -1]); if (argumentCount >= 6 && !JSValueIsNumber(ctx, arguments[6 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 6, "a number (""easing"")");
            long easing = (argumentCount<6) ? easingFuncToId(easeInOutQuad) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[6 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid luma easing");
            self->lumaFadeTo(*destination,seconds,mask,softness,darkFirst,gEasingFunctions[easing]); return thisObject;
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
    JSValueRef Camera_WhipPanTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Camera* self = static_cast<Camera*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2, true); if (argumentCount>5)
            {
                if (argumentCount != 5)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 5);
            } Camera* destination = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef destination_ = JSValueToObject(ctx, arguments[1 -1], exception);
                destination = Camera_getCppObject(destination_);
            }
            if (!destination)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""destination"")"); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[2 -1], exception);
            if (argumentCount >= 3 && !JSValueIsNumber(ctx, arguments[3 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""style"")");
            long style = (argumentCount<3) ? camera_WhipLeft : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[3 -1], exception)); if (argumentCount >= 4 && !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""blur"")");
            double blur = (argumentCount<4) ? 0 : JSValueToNumber(ctx, arguments[4 -1], exception); if (argumentCount >= 5 && !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""easing"")");
            long easing = (argumentCount<5) ? easingFuncToId(easeInOutQuad) : pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[5 -1], exception));
            if (easing<0 || easing>=NUM_EASING_FUNCTIONS || !gEasingFunctions[easing]) throw std::invalid_argument("Invalid whip easing");
            self->whipPanTo(*destination,seconds,style,blur,gEasingFunctions[easing]); return thisObject;
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

}
