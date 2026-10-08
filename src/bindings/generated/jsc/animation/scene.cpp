// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/scene.cpp
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
#include <stdexcept>
#include <cmath>
namespace pdg
{
#ifdef PDG_USING_JAVASCRIPT_CORE
    static void Scene_finalize(JSObjectRef object)
    {
        auto* value=static_cast<Scene*>(JSObjectGetPrivate(object)); if(!value)return;
        value->mSceneScriptObj=nullptr;value->mEventEmitterScriptObj=nullptr;
        JSObjectSetPrivate(object,nullptr);value->release();
    }
#define SCENE_SAVE(cppObj,obj) cppObj->mSceneScriptObj=obj;cppObj->mEventEmitterScriptObj=obj
#else
#define SCENE_SAVE(cppObj,obj) cppObj->mSceneScriptObj.Reset(isolate,obj);cppObj->mSceneScriptObj.SetWeak();cppObj->mEventEmitterScriptObj.Reset(isolate,obj);cppObj->mEventEmitterScriptObj.SetWeak()
#endif
    JSObjectRef Scene_newFromCpp(JSContextRef ctx, Scene* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Scene_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Scene_class());
        SCENE_SAVE(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSObjectRef Scene_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* cppObj = New_Scene(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Scene" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Scene_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Scene_class());
        SCENE_SAVE(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSClassRef Scene_class()
    {
        static JSStaticValue Scene_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Scene_staticFunctions[] =
        {
            { "addHandler", Scene_AddHandler, kJSPropertyAttributeDontDelete },
            { "removeHandler", Scene_RemoveHandler, kJSPropertyAttributeDontDelete },
            { "clear", Scene_Clear, kJSPropertyAttributeDontDelete },
            { "blockEvent", Scene_BlockEvent, kJSPropertyAttributeDontDelete },
            { "unblockEvent", Scene_UnblockEvent, kJSPropertyAttributeDontDelete },
            { "_raycast", Scene_Raycast, kJSPropertyAttributeDontDelete },
            { "_sweepCircle", Scene_SweepCircle, kJSPropertyAttributeDontDelete },
            { "_overlapPoint", Scene_OverlapPoint, kJSPropertyAttributeDontDelete },
            { "_overlapCircle", Scene_OverlapCircle, kJSPropertyAttributeDontDelete },
            { "_overlapBox", Scene_OverlapBox, kJSPropertyAttributeDontDelete },
            { "_overlapCapsule", Scene_OverlapCapsule, kJSPropertyAttributeDontDelete },
            { "_nearestPoint", Scene_NearestPoint, kJSPropertyAttributeDontDelete },
            { "addLayer", Scene_AddLayer, kJSPropertyAttributeDontDelete },
            { "removeLayer", Scene_RemoveLayer, kJSPropertyAttributeDontDelete },
            { "disposeLayer", Scene_DisposeLayer, kJSPropertyAttributeDontDelete },
            { "createSpriteLayer", Scene_CreateSpriteLayer, kJSPropertyAttributeDontDelete },
            { "getLayer", Scene_GetLayer, kJSPropertyAttributeDontDelete },
            { "pause", Scene_Pause, kJSPropertyAttributeDontDelete },
            { "resume", Scene_Resume, kJSPropertyAttributeDontDelete },
            { "dispose", Scene_Dispose, kJSPropertyAttributeDontDelete },
            { "cancelAllTimers", Scene_CancelAllTimers, kJSPropertyAttributeDontDelete },
            { "isPaused", Scene_IsPaused, kJSPropertyAttributeDontDelete },
            { "isDisposed", Scene_IsDisposed, kJSPropertyAttributeDontDelete },
            { "getLayerCount", Scene_GetLayerCount, kJSPropertyAttributeDontDelete },
            { "getTimeScale", Scene_GetTimeScale, kJSPropertyAttributeDontDelete },
            { "getFixedStep", Scene_GetFixedStep, kJSPropertyAttributeDontDelete },
            { "getSimulationTime", Scene_GetSimulationTime, kJSPropertyAttributeDontDelete },
            { "getDroppedTime", Scene_GetDroppedTime, kJSPropertyAttributeDontDelete },
            { "getInterpolationAlpha", Scene_GetInterpolationAlpha, kJSPropertyAttributeDontDelete },
            { "getTick", Scene_GetTick, kJSPropertyAttributeDontDelete },
            { "isInputEnabled", Scene_IsInputEnabled, kJSPropertyAttributeDontDelete },
            { "isManual", Scene_IsManual, kJSPropertyAttributeDontDelete },
            { "isInterpolationEnabled", Scene_IsInterpolationEnabled, kJSPropertyAttributeDontDelete },
            { "setTimeScale", Scene_SetTimeScale, kJSPropertyAttributeDontDelete },
            { "setFixedStep", Scene_SetFixedStep, kJSPropertyAttributeDontDelete },
            { "advance", Scene_Advance, kJSPropertyAttributeDontDelete },
            { "setManual", Scene_SetManual, kJSPropertyAttributeDontDelete },
            { "setInputEnabled", Scene_SetInputEnabled, kJSPropertyAttributeDontDelete },
            { "setInterpolation", Scene_SetInterpolation, kJSPropertyAttributeDontDelete },
            { "getCamera", Scene_GetCamera, kJSPropertyAttributeDontDelete },
            { "setCamera", Scene_SetCamera, kJSPropertyAttributeDontDelete },
            { "startTimer", Scene_StartTimer, kJSPropertyAttributeDontDelete },
            { "cancelTimer", Scene_CancelTimer, kJSPropertyAttributeDontDelete },
            { "pauseTimer", Scene_PauseTimer, kJSPropertyAttributeDontDelete },
            { "unpauseTimer", Scene_UnpauseTimer, kJSPropertyAttributeDontDelete },
            { "delayTimer", Scene_DelayTimer, kJSPropertyAttributeDontDelete },
            { "isTimerPaused", Scene_IsTimerPaused, kJSPropertyAttributeDontDelete },
            { "getWhenTimerFiresNext", Scene_GetWhenTimerFiresNext, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.parentClass = EventEmitter_class();
            definition.finalize = Scene_finalize;
            definition.className = "Scene";
            definition.staticFunctions = Scene_staticFunctions;
            definition.staticValues = Scene_staticValues;
            definition.callAsConstructor = Scene_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    JSValueRef Scene_AddHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Scene_RemoveHandler(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
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
    JSValueRef Scene_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clear();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Scene_BlockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->blockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef Scene_UnblockEvent(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""inEventType"")");
        int32 inEventType = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        self->unblockEvent(inEventType);
        return JSValueMakeUndefined(ctx);
    }
#ifdef PDG_USING_JAVASCRIPT_CORE
    Scene* New_Scene(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) { return new Scene(); }
#else
    SceneWrap::SceneWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException) : cppPtr_(New_Scene(args)) {}
    SceneWrap::~SceneWrap()
    {
        if(cppPtr_)
        {
            cppPtr_->mSceneScriptObj.Reset();cppPtr_->mEventEmitterScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;
        }
    }
    Scene* New_Scene(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        if(s_Scene_InNewFromCpp)
        {
            return nullptr;
        }
        auto* isolate=args.GetIsolate();auto* cppObj=new Scene();cppObj->addRef();SCENE_SAVE(cppObj,args.This());return cppObj;
    }
#endif
#undef SCENE_SAVE
    JSValueRef Scene_AddLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            SpriteLayer* layer = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
                layer = SpriteLayer_getCppObject(layer_);
            }
            if (!layer)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")"); self->addLayer(layer); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_RemoveLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            SpriteLayer* layer = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
                layer = SpriteLayer_getCppObject(layer_);
            }
            if (!layer)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")"); self->removeLayer(layer); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_DisposeLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            SpriteLayer* layer = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
                layer = SpriteLayer_getCppObject(layer_);
            }
            if (!layer)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")"); self->disposeLayer(layer); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_CreateSpriteLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!self->createSpriteLayer()) return JSValueMakeNull(ctx);
            return SpriteLayer_newFromCpp(ctx, self->createSpriteLayer());;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            int32 index = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); if (!self->getLayer(index)) return JSValueMakeNull(ctx);
            if (!self->getLayer(index)->mSpriteLayerScriptObj)
            {
                return SpriteLayer_newFromCpp(ctx, self->getLayer(index));
            }
            else
            {
                return self->getLayer(index)->mSpriteLayerScriptObj;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_Pause(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { self->pause(); return JSValueMakeUndefined(ctx); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_Resume(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { self->resume(); return JSValueMakeUndefined(ctx); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_Dispose(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { self->dispose(); return JSValueMakeUndefined(ctx); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_CancelAllTimers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { self->cancelAllTimers(); return JSValueMakeUndefined(ctx); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeBoolean(ctx, self->isPaused()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsDisposed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeBoolean(ctx, self->isDisposed()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetLayerCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getLayerCount()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetTimeScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getTimeScale()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetFixedStep(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getFixedStep()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetSimulationTime(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getSimulationTime()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetDroppedTime(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getDroppedTime()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetInterpolationAlpha(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getInterpolationAlpha()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetTick(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeNumber(ctx, self->getTick()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsInputEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeBoolean(ctx, self->isInputEnabled()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsManual(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeBoolean(ctx, self->isManual()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsInterpolationEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try { return JSValueMakeBoolean(ctx, self->isInterpolationEnabled()); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetTimeScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""scale"")");
            double scale = JSValueToNumber(ctx, arguments[1 -1], exception); self->setTimeScale(scale); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetFixedStep(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); self->setFixedStep(seconds); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_Advance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""seconds"")");
            double seconds = JSValueToNumber(ctx, arguments[1 -1], exception); self->advance(seconds); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetManual(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enabled"")");
            bool enabled = JSValueToBoolean(ctx, arguments[1 -1]); self->setManual(enabled); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetInputEnabled(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enabled"")");
            bool enabled = JSValueToBoolean(ctx, arguments[1 -1]); self->setInputEnabled(enabled); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetInterpolation(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsBoolean(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a boolean (""enabled"")");
            bool enabled = JSValueToBoolean(ctx, arguments[1 -1]); self->setInterpolation(enabled); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!self->getCamera()) return JSValueMakeNull(ctx);
            if (!self->getCamera()->mCameraScriptObj)
            {
                return Camera_newFromCpp(ctx, self->getCamera());
            }
            else
            {
                return self->getCamera()->mCameraScriptObj;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_SetCamera(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            Camera* camera = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef camera_ = JSValueToObject(ctx, arguments[1 -1], exception);
                camera = Camera_getCppObject(camera_);
            }
            if (!camera)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Camera"" (""camera"")"); self->setCamera(camera); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_StartTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""delayMs"")");
            double delayMs = JSValueToNumber(ctx, arguments[2 -1], exception); if (argumentCount >= 3 && !JSValueIsBoolean(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""oneShot"")");
            bool oneShot = (argumentCount<3) ? true : JSValueToBoolean(ctx, arguments[3 -1]); self->startTimer(id,delayMs,oneShot); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_CancelTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); self->cancelTimer(id); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_PauseTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); self->pauseTimer(id); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_UnpauseTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); self->unpauseTimer(id); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_DelayTimer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""delayMs"")");
            double delayMs = JSValueToNumber(ctx, arguments[2 -1], exception); self->delayTimer(id,delayMs); return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_IsTimerPaused(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeBoolean(ctx, self->isTimerPaused(id));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_GetWhenTimerFiresNext(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""id"")");
            int32 id = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeNumber(ctx, self->getWhenTimerFiresNext(id));
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef Scene_Raycast(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[3 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[3 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->raycast(start,end,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_SweepCircle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4); pdg::Point center;
            auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
            if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*center_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[2 -1], exception); pdg::Vector delta;
            auto delta_isVector = JSC_ValueIsVector(ctx, arguments[3 -1], delta, exception);
            if (!delta_isVector.has_value()) { return JSValueMakeNull(ctx); }
            if (!*delta_isVector)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 3, "Vector", arguments[3 -1]);
            }; CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[4 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[4 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 4, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->sweepCircle(center,radius,delta,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_OverlapPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[2 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[2 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->overlapPoint(point,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_OverlapCircle(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); pdg::Point center;
            auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
            if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*center_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[2 -1], exception); CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[3 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[3 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->overlapCircle(center,radius,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_OverlapBox(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2); pdg::RotatedRect box;
            auto box_isRotatedRect = JSC_ValueIsRotatedRect(ctx, arguments[1 -1], box, exception);
            if (!box_isRotatedRect.has_value()) { return JSValueMakeNull(ctx); }
            if (!*box_isRotatedRect)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", arguments[1 -1]);
            }; CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[2 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[2 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->overlapBox(box,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_OverlapCapsule(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 4)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4); pdg::Point start;
            auto start_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], start, exception);
            if (!start_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*start_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; pdg::Point end;
            auto end_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], end, exception);
            if (!end_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*end_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            }; if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""radius"")");
            double radius = JSValueToNumber(ctx, arguments[3 -1], exception); CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[4 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[4 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 4, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->overlapCapsule(start,end,radius,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Scene_NearestPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Scene* self = static_cast<Scene*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 3)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3); pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
            }; if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""maxDistance"")");
            double maxDistance = JSValueToNumber(ctx, arguments[2 -1], exception); CollisionQueryBuffer* results = 0;
            if (JSValueIsObject(ctx, arguments[3 -1]))
            {
                JSObjectRef results_ = JSValueToObject(ctx, arguments[3 -1], exception);
                results = CollisionQueryBuffer_getCppObject(results_);
            }
            if (!results)
                return JSC_ThrowArgTypeException(ctx, exception, 3, "an object of type ""CollisionQueryBuffer"" (""results"")");
            return JSValueMakeNumber(ctx, self->queryNearestPoint(point,maxDistance,*results));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void CollisionQueryBuffer_finalize(JSObjectRef object)
    {
        auto* value=static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(object)); if(!value)return;
        value->mCollisionQueryBufferScriptObj=nullptr;JSObjectSetPrivate(object,nullptr);value->release();
    }
#define QUERY_SAVE(cppObj,obj) cppObj->mCollisionQueryBufferScriptObj=obj
#else
#define QUERY_SAVE(cppObj,obj) cppObj->mCollisionQueryBufferScriptObj.Reset(isolate,obj);cppObj->mCollisionQueryBufferScriptObj.SetWeak()
#endif
    JSObjectRef CollisionQueryBuffer_newFromCpp(JSContextRef ctx, CollisionQueryBuffer* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, CollisionQueryBuffer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, CollisionQueryBuffer_class());
        QUERY_SAVE(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSObjectRef CollisionQueryBuffer_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* cppObj = New_CollisionQueryBuffer(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "CollisionQueryBuffer" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, CollisionQueryBuffer_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, CollisionQueryBuffer_class());
        QUERY_SAVE(cppObj,obj);cppObj->addRef();
        return obj;
    }

    JSClassRef CollisionQueryBuffer_class()
    {
        static JSStaticValue CollisionQueryBuffer_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction CollisionQueryBuffer_staticFunctions[] =
        {
            { "getCapacity", CollisionQueryBuffer_GetCapacity, kJSPropertyAttributeDontDelete },
            { "getPointX", CollisionQueryBuffer_GetPointX, kJSPropertyAttributeDontDelete },
            { "getPointY", CollisionQueryBuffer_GetPointY, kJSPropertyAttributeDontDelete },
            { "getNormalX", CollisionQueryBuffer_GetNormalX, kJSPropertyAttributeDontDelete },
            { "getNormalY", CollisionQueryBuffer_GetNormalY, kJSPropertyAttributeDontDelete },
            { "getCount", CollisionQueryBuffer_GetCount, kJSPropertyAttributeDontDelete },
            { "isOverflowed", CollisionQueryBuffer_IsOverflowed, kJSPropertyAttributeDontDelete },
            { "clear", CollisionQueryBuffer_Clear, kJSPropertyAttributeDontDelete },
            { "getCollider", CollisionQueryBuffer_GetCollider, kJSPropertyAttributeDontDelete },
            { "getShapeId", CollisionQueryBuffer_GetShapeId, kJSPropertyAttributeDontDelete },
            { "getPoint", CollisionQueryBuffer_GetPoint, kJSPropertyAttributeDontDelete },
            { "getNormal", CollisionQueryBuffer_GetNormal, kJSPropertyAttributeDontDelete },
            { "getFraction", CollisionQueryBuffer_GetFraction, kJSPropertyAttributeDontDelete },
            { "getDistance", CollisionQueryBuffer_GetDistance, kJSPropertyAttributeDontDelete },
            { "getInitialOverlap", CollisionQueryBuffer_GetInitialOverlap, kJSPropertyAttributeDontDelete },
            { "configure", CollisionQueryBuffer_Configure, kJSPropertyAttributeDontDelete },
            { "selectLayers", CollisionQueryBuffer_SelectLayers, kJSPropertyAttributeDontDelete },
            { "addLayer", CollisionQueryBuffer_AddLayer, kJSPropertyAttributeDontDelete },
            { "excludeCollider", CollisionQueryBuffer_ExcludeCollider, kJSPropertyAttributeDontDelete },
            { "excludeBody", CollisionQueryBuffer_ExcludeBody, kJSPropertyAttributeDontDelete },
            { "setPredicate", CollisionQueryBuffer_SetPredicate, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.finalize = CollisionQueryBuffer_finalize;
            definition.className = "CollisionQueryBuffer";
            definition.staticFunctions = CollisionQueryBuffer_staticFunctions;
            definition.staticValues = CollisionQueryBuffer_staticValues;
            definition.callAsConstructor = CollisionQueryBuffer_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }
    CollisionQueryBuffer* New_CollisionQueryBuffer(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef localConstructorException = nullptr;
        JSValueRef* exception = constructorException ? constructorException : &localConstructorException;
#ifndef PDG_USING_JAVASCRIPT_CORE
        if(s_CollisionQueryBuffer_InNewFromCpp) { return nullptr; }
        auto* isolate=args.GetIsolate();
#endif
        if(argumentCount>1 || (argumentCount && !JSValueIsNumber(ctx, arguments[0])))
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Expected optional query capacity";
            s_HaveSavedError = true; return nullptr;
        }
        const double capacity=argumentCount ? JSValueToNumber(ctx, arguments[0], exception) : 16;
        if(!std::isfinite(capacity)||capacity<0||capacity>1048576||std::floor(capacity)!=capacity)
        {
            s_SavedError.str(""); s_SavedError.clear();
            s_SavedError << "Expected integer query capacity from 0 to 1048576";
            s_HaveSavedError = true; return nullptr;
        }
        auto* cppObj=new CollisionQueryBuffer(uint32_t(capacity));
#ifndef PDG_USING_JAVASCRIPT_CORE
        cppObj->addRef();QUERY_SAVE(cppObj,args.This());
#endif
        return cppObj;
    }
#ifndef PDG_USING_JAVASCRIPT_CORE
    CollisionQueryBufferWrap::CollisionQueryBufferWrap(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException):cppPtr_(New_CollisionQueryBuffer(args)) {}
    CollisionQueryBufferWrap::~CollisionQueryBufferWrap()
    {
        if(cppPtr_)
        {
            cppPtr_->mCollisionQueryBufferScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;
        }
    }
#endif
#undef QUERY_SAVE
    JSValueRef CollisionQueryBuffer_GetCapacity(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getCapacity(); return JSValueMakeNumber(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetPointX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeNumber(ctx, self->getPointX(index));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetPointY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeNumber(ctx, self->getPointY(index));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetNormalX(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeNumber(ctx, self->getNormalX(index));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetNormalY(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception)); return JSValueMakeNumber(ctx, self->getNormalY(index));
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->getCount(); return JSValueMakeNumber(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_IsOverflowed(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0); auto value=self->isOverflowed(); return JSValueMakeBoolean(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetShapeId(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getShapeId(index); return JSValueMakeNumber(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getPoint(index); return JSC_PointToValue(ctx, value, exception);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetNormal(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getNormal(index); return JSC_VectorToValue(ctx, value, exception);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetFraction(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getFraction(index); return JSValueMakeNumber(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetDistance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getDistance(index); return JSValueMakeNumber(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetInitialOverlap(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1); if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            }
            const auto index=uint32_t(indexValue); auto value=self->getInitialOverlap(index); return JSValueMakeBoolean(ctx, value);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_GetCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""indexValue"")");
            double indexValue = JSValueToNumber(ctx, arguments[1 -1], exception); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Expected unsigned integer hit index" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
            } const auto index=uint32_t(indexValue); if (!self->getCollider(index)) return JSValueMakeNull(ctx);
            if (!self->getCollider(index)->mColliderScriptObj)
            {
                return Collider_newFromCpp(ctx, self->getCollider(index));
            }
            else
            {
                return self->getCollider(index)->mColliderScriptObj;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_Clear(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try {self->clear();return JSValueMakeUndefined(ctx);}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_Configure(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""layers"")");
        uint32 layers = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));if (!JSValueIsNumber(ctx, arguments[2 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""categories"")");
        uint32 categories = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[2 -1], exception));if (!JSValueIsBoolean(ctx, arguments[3 -1]))
        return JSC_ThrowArgTypeException(ctx, exception, 3, "a boolean (""sensors"")");
        bool sensors = JSValueToBoolean(ctx, arguments[3 -1]);
        try {self->configure(layers,categories,sensors);return JSValueMakeUndefined(ctx);}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_SelectLayers(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try {self->selectLayers();return JSValueMakeUndefined(ctx);}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_AddLayer(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        SpriteLayer* layer = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef layer_ = JSValueToObject(ctx, arguments[1 -1], exception);
            layer = SpriteLayer_getCppObject(layer_);
        }
        if (!layer)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""SpriteLayer"" (""layer"")");try
        {
            self->addLayer(layer);return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_ExcludeCollider(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        Collider* collider = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef collider_ = JSValueToObject(ctx, arguments[1 -1], exception);
            collider = Collider_getCppObject(collider_);
        }
        if (!collider)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Collider"" (""collider"")");try
        {
            self->excludeCollider(collider);return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef CollisionQueryBuffer_ExcludeBody(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        PhysicsBody* body = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef body_ = JSValueToObject(ctx, arguments[1 -1], exception);
            body = PhysicsBody_getCppObject(body_);
        }
        if (!body)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""PhysicsBody"" (""body"")");try
        {
            self->excludeBody(body);return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    struct QueryScriptPredicate
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSGlobalContextRef context; JSObjectRef function;
        QueryScriptPredicate(JSContextRef ctx,JSObjectRef f):context(JSGlobalContextRetain(JSContextGetGlobalContext(ctx))),function(f){JSValueProtect(context,function);}
        ~QueryScriptPredicate(){JSValueUnprotect(context,function);JSGlobalContextRelease(context);}
#else
        v8::Isolate* isolate; v8::Global<v8::Context> context; v8::Global<v8::Function> function;
        QueryScriptPredicate(v8::Isolate* i,v8::Local<v8::Function> f):isolate(i),context(i,i->GetCurrentContext()),function(i,f){}
#endif
        bool invoke(const Collider& collider)
        {
            auto* c=const_cast<Collider*>(&collider);
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto ctx=context; JSValueRef error=nullptr;
            JSValueRef argv[]={c->mColliderScriptObj?c->mColliderScriptObj:Collider_newFromCpp(ctx,c)};
            auto result=JSObjectCallAsFunction(ctx,function,nullptr,1,argv,&error);
            if(error)throw std::runtime_error("Query predicate failed");
            if(!JSValueIsBoolean(ctx,result))throw std::runtime_error("Query predicate must return a boolean");
            return JSValueToBoolean(ctx,result);
#else
            v8::HandleScope handles(isolate);auto ctx=context.Get(isolate);v8::Context::Scope scope(ctx);v8::TryCatch catcher(isolate);
            v8::Local<v8::Value> argv[]={c->mColliderScriptObj.IsEmpty()?ColliderWrap::NewFromCpp(isolate,c):v8::Local<v8::Object>::New(isolate,c->mColliderScriptObj)},
            result;
            if(!function.Get(isolate)->Call(ctx,v8::Undefined(isolate),1,argv).ToLocal(&result))
            {
                v8::String::Utf8Value message(isolate,catcher.Exception());throw std::runtime_error(*message?*message:"Query predicate failed");
            }
            if(!result->IsBoolean())throw std::runtime_error("Query predicate must return a boolean");
            return result->BooleanValue(isolate);
#endif
        }
    };
    JSValueRef CollisionQueryBuffer_SetPredicate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        CollisionQueryBuffer* self = static_cast<CollisionQueryBuffer*>(JSObjectGetPrivate(thisObject));
        ;
        try
        {
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);if(JSValueIsNull(ctx, arguments[0]))
            {
                self->setPredicate(
                {
                }
                );return JSValueMakeUndefined(ctx);
            }
            JSObjectRef func = JSValueToObject(ctx, arguments[1 -1], exception);
            if (!func || !JSObjectIsFunction(ctx, func) )
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a function (""func"")");
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto predicate=std::make_shared<QueryScriptPredicate>(ctx,func);
#else
            auto predicate=std::make_shared<QueryScriptPredicate>(isolate,func);
#endif
            self->setPredicate([predicate](const Collider& c){return predicate->invoke(c);}
            );return JSValueMakeUndefined(ctx);
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << e.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

}
