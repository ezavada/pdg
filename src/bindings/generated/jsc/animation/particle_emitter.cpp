// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/particle_emitter.cpp
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
    static void ParticleEmitter_finalize(JSObjectRef object)
    {
        auto* value=static_cast<ParticleEmitter*>(JSObjectGetPrivate(object)); if (!value) return;
        value->mParticleEmitterScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr;
        JSObjectSetPrivate(object,nullptr); value->release();
    }
#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj
#else
#define PARTICLEEMITTER_SAVE(cppObj,obj) cppObj->mParticleEmitterScriptObj.Reset(isolate,obj); cppObj->mParticleEmitterScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak()
#endif
    JSObjectRef ParticleEmitter_newFromCpp(JSContextRef ctx, ParticleEmitter* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, ParticleEmitter_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ParticleEmitter_class());
        PARTICLEEMITTER_SAVE(cppObj,obj); cppObj->addRef();
        return obj;
    }

    JSObjectRef ParticleEmitter_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* cppObj = New_ParticleEmitter(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "ParticleEmitter" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ParticleEmitter_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ParticleEmitter_class());
        PARTICLEEMITTER_SAVE(cppObj,obj); cppObj->addRef();
        return obj;
    }

    JSClassRef ParticleEmitter_class()
    {
        static JSStaticValue ParticleEmitter_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ParticleEmitter_staticFunctions[] =
        {
            { "playScript", ParticleEmitter_PlayScript, kJSPropertyAttributeDontDelete },
            { "batch", ParticleEmitter_Batch, kJSPropertyAttributeDontDelete },
            { "endBatch", ParticleEmitter_EndBatch, kJSPropertyAttributeDontDelete },
            { "series", ParticleEmitter_Series, kJSPropertyAttributeDontDelete },
            { "endSeries", ParticleEmitter_EndSeries, kJSPropertyAttributeDontDelete },
            { "andAlso", ParticleEmitter_AndAlso, kJSPropertyAttributeDontDelete },
            { "stagger", ParticleEmitter_Stagger, kJSPropertyAttributeDontDelete },
            { "mark", ParticleEmitter_Mark, kJSPropertyAttributeDontDelete },
            { "jumpToMark", ParticleEmitter_JumpToMark, kJSPropertyAttributeDontDelete },
            { "on", ParticleEmitter_ScriptOn, kJSPropertyAttributeDontDelete },
            { "triggerEvent", ParticleEmitter_TriggerEvent, kJSPropertyAttributeDontDelete },
            { "onStarted", ParticleEmitter_OnStarted, kJSPropertyAttributeDontDelete },
            { "onFinished", ParticleEmitter_OnFinished, kJSPropertyAttributeDontDelete },
            { "onScriptFinished", ParticleEmitter_OnScriptFinished, kJSPropertyAttributeDontDelete },
            { "onMark", ParticleEmitter_OnMark, kJSPropertyAttributeDontDelete },
            { "onYoyo", ParticleEmitter_OnYoyo, kJSPropertyAttributeDontDelete },
            { "onRepeat", ParticleEmitter_OnRepeat, kJSPropertyAttributeDontDelete },
            { "onUntilFired", ParticleEmitter_OnUntilFired, kJSPropertyAttributeDontDelete },
            { "when", ParticleEmitter_When, kJSPropertyAttributeDontDelete },
            { "otherwise", ParticleEmitter_Otherwise, kJSPropertyAttributeDontDelete },
            { "endWhen", ParticleEmitter_EndWhen, kJSPropertyAttributeDontDelete },
            { "endOtherwise", ParticleEmitter_EndOtherwise, kJSPropertyAttributeDontDelete },
            { "until", ParticleEmitter_Until, kJSPropertyAttributeDontDelete },
            { "yoyo", ParticleEmitter_Yoyo, kJSPropertyAttributeDontDelete },
            { "repeat", ParticleEmitter_Repeat, kJSPropertyAttributeDontDelete },
            { "diminish", ParticleEmitter_Diminish, kJSPropertyAttributeDontDelete },
            { "increase", ParticleEmitter_Increase, kJSPropertyAttributeDontDelete },
            { "slowDown", ParticleEmitter_SlowDown, kJSPropertyAttributeDontDelete },
            { "speedUp", ParticleEmitter_SpeedUp, kJSPropertyAttributeDontDelete },
            { "stopIt", ParticleEmitter_StopIt, kJSPropertyAttributeDontDelete },
            { "restartIt", ParticleEmitter_RestartIt, kJSPropertyAttributeDontDelete },
            { "pauseIt", ParticleEmitter_PauseIt, kJSPropertyAttributeDontDelete },
            { "resumeIt", ParticleEmitter_ResumeIt, kJSPropertyAttributeDontDelete },
            { "getBoundingBox", ParticleEmitter_GetBoundingBox, kJSPropertyAttributeDontDelete },
            { "getRotatedBounds", ParticleEmitter_GetRotatedBounds, kJSPropertyAttributeDontDelete },
            { "getLocation", ParticleEmitter_GetLocation, kJSPropertyAttributeDontDelete },
            { "getMovement", ParticleEmitter_GetMovement, kJSPropertyAttributeDontDelete },
            { "getSize", ParticleEmitter_GetSize, kJSPropertyAttributeDontDelete },
            { "getWidth", ParticleEmitter_GetWidth, kJSPropertyAttributeDontDelete },
            { "getHeight", ParticleEmitter_GetHeight, kJSPropertyAttributeDontDelete },
            { "getScale", ParticleEmitter_GetScale, kJSPropertyAttributeDontDelete },
            { "getStretching", ParticleEmitter_GetStretching, kJSPropertyAttributeDontDelete },
            { "getRotation", ParticleEmitter_GetRotation, kJSPropertyAttributeDontDelete },
            { "getCenterOffset", ParticleEmitter_GetCenterOffset, kJSPropertyAttributeDontDelete },
            { "getSpin", ParticleEmitter_GetSpin, kJSPropertyAttributeDontDelete },
            { "setLocation", ParticleEmitter_SetLocation, kJSPropertyAttributeDontDelete },
            { "moveTo", ParticleEmitter_MoveTo, kJSPropertyAttributeDontDelete },
            { "moveBy", ParticleEmitter_MoveBy, kJSPropertyAttributeDontDelete },
            { "setMovement", ParticleEmitter_SetMovement, kJSPropertyAttributeDontDelete },
            { "changeMovementTo", ParticleEmitter_ChangeMovementTo, kJSPropertyAttributeDontDelete },
            { "changeMovementBy", ParticleEmitter_ChangeMovementBy, kJSPropertyAttributeDontDelete },
            { "setSize", ParticleEmitter_SetSize, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetTo", ParticleEmitter_ChangeCenterOffsetTo, kJSPropertyAttributeDontDelete },
            { "changeCenterOffsetBy", ParticleEmitter_ChangeCenterOffsetBy, kJSPropertyAttributeDontDelete },
            { "setWidth", ParticleEmitter_SetWidth, kJSPropertyAttributeDontDelete },
            { "setHeight", ParticleEmitter_SetHeight, kJSPropertyAttributeDontDelete },
            { "setRotation", ParticleEmitter_SetRotation, kJSPropertyAttributeDontDelete },
            { "setSpin", ParticleEmitter_SetSpin, kJSPropertyAttributeDontDelete },
            { "setGrowing", ParticleEmitter_SetGrowing, kJSPropertyAttributeDontDelete },
            { "setStretching", ParticleEmitter_SetStretching, kJSPropertyAttributeDontDelete },
            { "setScale", ParticleEmitter_SetScale, kJSPropertyAttributeDontDelete },
            { "changeSpinTo", ParticleEmitter_ChangeSpinTo, kJSPropertyAttributeDontDelete },
            { "changeSpinBy", ParticleEmitter_ChangeSpinBy, kJSPropertyAttributeDontDelete },
            { "changeGrowingTo", ParticleEmitter_ChangeGrowingTo, kJSPropertyAttributeDontDelete },
            { "changeGrowingBy", ParticleEmitter_ChangeGrowingBy, kJSPropertyAttributeDontDelete },
            { "changeStretchingTo", ParticleEmitter_ChangeStretchingTo, kJSPropertyAttributeDontDelete },
            { "changeStretchingBy", ParticleEmitter_ChangeStretchingBy, kJSPropertyAttributeDontDelete },
            { "changeScaleTo", ParticleEmitter_ChangeScaleTo, kJSPropertyAttributeDontDelete },
            { "changeScaleBy", ParticleEmitter_ChangeScaleBy, kJSPropertyAttributeDontDelete },
            { "grow", ParticleEmitter_Grow, kJSPropertyAttributeDontDelete },
            { "stretch", ParticleEmitter_Stretch, kJSPropertyAttributeDontDelete },
            { "resizeBy", ParticleEmitter_ResizeBy, kJSPropertyAttributeDontDelete },
            { "resizeTo", ParticleEmitter_ResizeTo, kJSPropertyAttributeDontDelete },
            { "rotateBy", ParticleEmitter_RotateBy, kJSPropertyAttributeDontDelete },
            { "rotateTo", ParticleEmitter_RotateTo, kJSPropertyAttributeDontDelete },
            { "setCenterOffset", ParticleEmitter_SetCenterOffset, kJSPropertyAttributeDontDelete },
            { "setFlipX", ParticleEmitter_SetFlipX, kJSPropertyAttributeDontDelete },
            { "setFlipY", ParticleEmitter_SetFlipY, kJSPropertyAttributeDontDelete },
            { "stopMovement", ParticleEmitter_StopMovement, kJSPropertyAttributeDontDelete },
            { "stopSpinning", ParticleEmitter_StopSpinning, kJSPropertyAttributeDontDelete },
            { "stopGrowing", ParticleEmitter_StopGrowing, kJSPropertyAttributeDontDelete },
            { "stopStretching", ParticleEmitter_StopStretching, kJSPropertyAttributeDontDelete },
            { "pauseSchedule", ParticleEmitter_PauseSchedule, kJSPropertyAttributeDontDelete },
            { "resumeSchedule", ParticleEmitter_ResumeSchedule, kJSPropertyAttributeDontDelete },
            { "cancelSchedule", ParticleEmitter_CancelSchedule, kJSPropertyAttributeDontDelete },
            { "flipX", ParticleEmitter_FlipX, kJSPropertyAttributeDontDelete },
            { "flipY", ParticleEmitter_FlipY, kJSPropertyAttributeDontDelete },
            { "andThen", ParticleEmitter_AndThen, kJSPropertyAttributeDontDelete },
            { "isFlippedX", ParticleEmitter_IsFlippedX, kJSPropertyAttributeDontDelete },
            { "isFlippedY", ParticleEmitter_IsFlippedY, kJSPropertyAttributeDontDelete },
            { "isSchedulePaused", ParticleEmitter_IsSchedulePaused, kJSPropertyAttributeDontDelete },
            { "hasScheduledAnimations", ParticleEmitter_HasScheduledAnimations, kJSPropertyAttributeDontDelete },
            { "wait", ParticleEmitter_Wait, kJSPropertyAttributeDontDelete },
            { "addAnimationHelper", ParticleEmitter_AddAnimationHelper, kJSPropertyAttributeDontDelete },
            { "removeAnimationHelper", ParticleEmitter_RemoveAnimationHelper, kJSPropertyAttributeDontDelete },
            { "clearAnimationHelpers", ParticleEmitter_ClearAnimationHelpers, kJSPropertyAttributeDontDelete },
            { "setParticleTemplate", ParticleEmitter_SetParticleTemplate, kJSPropertyAttributeDontDelete },
            { "hasParticleTemplate", ParticleEmitter_HasParticleTemplate, kJSPropertyAttributeDontDelete },
            { "setEmissionRate", ParticleEmitter_SetEmissionRate, kJSPropertyAttributeDontDelete },
            { "getEmissionRate", ParticleEmitter_GetEmissionRate, kJSPropertyAttributeDontDelete },
            { "setParticleSpeed", ParticleEmitter_SetParticleSpeed, kJSPropertyAttributeDontDelete },
            { "getMinParticleSpeed", ParticleEmitter_GetMinParticleSpeed, kJSPropertyAttributeDontDelete },
            { "getMaxParticleSpeed", ParticleEmitter_GetMaxParticleSpeed, kJSPropertyAttributeDontDelete },
            { "setSpread", ParticleEmitter_SetSpread, kJSPropertyAttributeDontDelete },
            { "getSpread", ParticleEmitter_GetSpread, kJSPropertyAttributeDontDelete },
            { "setVelocityInheritance", ParticleEmitter_SetVelocityInheritance, kJSPropertyAttributeDontDelete },
            { "getVelocityInheritance", ParticleEmitter_GetVelocityInheritance, kJSPropertyAttributeDontDelete },
            { "setSeed", ParticleEmitter_SetSeed, kJSPropertyAttributeDontDelete },
            { "getSeed", ParticleEmitter_GetSeed, kJSPropertyAttributeDontDelete },
            { "startEmitting", ParticleEmitter_StartEmitting, kJSPropertyAttributeDontDelete },
            { "stopEmitting", ParticleEmitter_StopEmitting, kJSPropertyAttributeDontDelete },
            { "isEmitting", ParticleEmitter_IsEmitting, kJSPropertyAttributeDontDelete },
            { "emit", ParticleEmitter_Emit, kJSPropertyAttributeDontDelete },
            { "getLayer", ParticleEmitter_GetLayer, kJSPropertyAttributeDontDelete },
            { "getParticle", ParticleEmitter_GetParticle, kJSPropertyAttributeDontDelete },
            { "animate", ParticleEmitter_Animate, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.parentClass = AnimatedBase_class();
            definition.finalize = ParticleEmitter_finalize;
            definition.className = "ParticleEmitter";
            definition.staticFunctions = ParticleEmitter_staticFunctions;
            definition.staticValues = ParticleEmitter_staticValues;
            definition.callAsConstructor = ParticleEmitter_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef ParticleEmitter_PlayScript(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Batch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_EndBatch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Series(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_EndSeries(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_AndAlso(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Stagger(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Mark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_JumpToMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_When(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ScriptOn(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnStarted(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_TriggerEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnScriptFinished(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnMark(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnYoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnRepeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_OnUntilFired(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Otherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_EndWhen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_EndOtherwise(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Until(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Yoyo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Repeat(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Diminish(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Increase(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SlowDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SpeedUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_StopIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_RestartIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_PauseIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ResumeIt(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetBoundingBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetRotatedBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    JSValueRef ParticleEmitter_GetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetLocation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_MoveBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeMovementTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeMovementBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetSize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeCenterOffsetTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeCenterOffsetBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetWidth(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetHeight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetRotation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetSpin(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeSpinTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeSpinBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeGrowingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeGrowingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeStretchingTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeStretchingBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeScaleTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ChangeScaleBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Grow(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Stretch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ResizeBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ResizeTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_RotateBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_RotateTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetCenterOffset(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetFlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_SetFlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_StopMovement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_StopSpinning(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_StopGrowing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_StopStretching(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_PauseSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ResumeSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_CancelSchedule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_FlipX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_FlipY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_AndThen(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_IsFlippedX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_IsFlippedY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_IsSchedulePaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_HasScheduledAnimations(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_Wait(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_AddAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_RemoveAnimationHelper(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef ParticleEmitter_ClearAnimationHelpers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
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

    void CleanupParticleEmitterScriptObject(JSObjectRef obj) { }

#ifdef PDG_USING_JAVASCRIPT_CORE
    ParticleEmitter* New_ParticleEmitter(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return new ParticleEmitter(); }
#else
    ParticleEmitterWrap::ParticleEmitterWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_ParticleEmitter(args)) {}
    ParticleEmitterWrap::~ParticleEmitterWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mParticleEmitterScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr;
        }
    }
    ParticleEmitter* New_ParticleEmitter(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        if (s_ParticleEmitter_InNewFromCpp) return nullptr;
        auto* isolate=args.GetIsolate(); auto* cppObj=new ParticleEmitter(); cppObj->addRef();
        PARTICLEEMITTER_SAVE(cppObj,args.This()); return cppObj;
    }
#endif
#undef PARTICLEEMITTER_SAVE
    JSValueRef ParticleEmitter_HasParticleTemplate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->hasParticleTemplate());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetEmissionRate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getEmissionRate());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetMinParticleSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMinParticleSpeed());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetMaxParticleSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getMaxParticleSpeed());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetSpread(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getSpread());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetVelocityInheritance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getVelocityInheritance());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetSeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeNumber(ctx, self->getSeed());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_IsEmitting(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); return JSValueMakeBoolean(ctx, self->isEmitting());
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_Animate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); return JSValueMakeBoolean(ctx, self->animate(seconds));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=self->getLayer(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mSpriteLayerScriptObj)
            {
                return SpriteLayer_newFromCpp(ctx, result);
            }
            else
            {
                return result->mSpriteLayerScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetEmissionRate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setEmissionRate(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetSpread(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setSpread(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetVelocityInheritance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""value"")");
            double value = JSValueToNumber(ctx, arguments[1 -1], exception); self->setVelocityInheritance(value); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetParticleTemplate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); Particle* particle = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef particle_ = JSValueToObject(ctx, arguments[1 -1], exception);
                particle = Particle_getCppObject(particle_);
            }
            if (!particle)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Particle"" (""particle"")"); self->setParticleTemplate(*particle); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetParticleSpeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""minimum"")");
            double minimum = JSValueToNumber(ctx, arguments[1 -1], exception); if (argumentCount >= 2 && !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""maximum"")");
            double maximum = (argumentCount<2) ? minimum : JSValueToNumber(ctx, arguments[2 -1], exception); self->setParticleSpeed(minimum,maximum); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_StartEmitting(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->startEmitting(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_StopEmitting(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); self->stopEmitting(); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_SetSeed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seed"")");
            double seed = JSValueToNumber(ctx, arguments[1 -1], exception); if (!std::isfinite(seed) || seed < 0 || seed > UINT32_MAX || std::floor(seed) != seed) throw std::invalid_argument("Expected uint32 seed"); self->setSeed(static_cast<uint32_t>(seed)); return thisObject;
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_Emit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount >= 1 && !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""count"")");
            double count = (argumentCount<1) ? 1 : JSValueToNumber(ctx, arguments[1 -1], exception); if (!std::isfinite(count) || count < 0 || count > UINT32_MAX || std::floor(count) != count) throw std::invalid_argument("Expected uint32 count"); return JSValueMakeNumber(ctx, self->emit(static_cast<uint32_t>(count)));
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ParticleEmitter_GetParticle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ParticleEmitter* self = static_cast<ParticleEmitter*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto* result=self->getParticle(); if (!result) return JSValueMakeNull(ctx);
            if (!result->mParticleScriptObj)
            {
                return Particle_newFromCpp(ctx, result);
            }
            else
            {
                return result->mParticleScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

}
