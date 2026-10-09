// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/scene.cpp
//    $PDG_ROOT/src/bindings/javascript/v8/pdg_script_macros.h
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
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
    static bool s_Scene_InNewFromCpp = false;

    void SceneWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = new SceneWrap(args);
        objWrapper->Wrap(args.This());
        ;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> SceneWrap::NewFromCpp(v8::Isolate* isolate, Scene* cppObj)
    {
        s_Scene_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Scene_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Scene_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(instance);
        { [[maybe_unused]] v8::Local<v8::Object> obj = instance; SCENE_SAVE(cppObj,obj);cppObj->addRef(); }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_Scene_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SceneWrap::constructorTpl_;

    void SceneWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->Inherit(EventEmitterWrap::GetTemplate(isolate));
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Scene").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> AddHandler_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddHandler_Tpl =
            v8::FunctionTemplate::New(isolate, AddHandler, v8::Local<v8::Value>(), AddHandler_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addHandler").ToLocalChecked(), AddHandler_Tpl);
        v8::Local<v8::Signature> RemoveHandler_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveHandler_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveHandler, v8::Local<v8::Value>(), RemoveHandler_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeHandler").ToLocalChecked(), RemoveHandler_Tpl);
        v8::Local<v8::Signature> Clear_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Clear_Tpl =
            v8::FunctionTemplate::New(isolate, Clear, v8::Local<v8::Value>(), Clear_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clear").ToLocalChecked(), Clear_Tpl);
        v8::Local<v8::Signature> BlockEvent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BlockEvent_Tpl =
            v8::FunctionTemplate::New(isolate, BlockEvent, v8::Local<v8::Value>(), BlockEvent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blockEvent").ToLocalChecked(), BlockEvent_Tpl);
        v8::Local<v8::Signature> UnblockEvent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UnblockEvent_Tpl =
            v8::FunctionTemplate::New(isolate, UnblockEvent, v8::Local<v8::Value>(), UnblockEvent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unblockEvent").ToLocalChecked(), UnblockEvent_Tpl);
        v8::Local<v8::Signature> Raycast_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Raycast_Tpl =
            v8::FunctionTemplate::New(isolate, Raycast, v8::Local<v8::Value>(), Raycast_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_raycast").ToLocalChecked(), Raycast_Tpl);
        v8::Local<v8::Signature> SweepCircle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SweepCircle_Tpl =
            v8::FunctionTemplate::New(isolate, SweepCircle, v8::Local<v8::Value>(), SweepCircle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_sweepCircle").ToLocalChecked(), SweepCircle_Tpl);
        v8::Local<v8::Signature> OverlapPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OverlapPoint_Tpl =
            v8::FunctionTemplate::New(isolate, OverlapPoint, v8::Local<v8::Value>(), OverlapPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_overlapPoint").ToLocalChecked(), OverlapPoint_Tpl);
        v8::Local<v8::Signature> OverlapCircle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OverlapCircle_Tpl =
            v8::FunctionTemplate::New(isolate, OverlapCircle, v8::Local<v8::Value>(), OverlapCircle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_overlapCircle").ToLocalChecked(), OverlapCircle_Tpl);
        v8::Local<v8::Signature> OverlapBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OverlapBox_Tpl =
            v8::FunctionTemplate::New(isolate, OverlapBox, v8::Local<v8::Value>(), OverlapBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_overlapBox").ToLocalChecked(), OverlapBox_Tpl);
        v8::Local<v8::Signature> OverlapCapsule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OverlapCapsule_Tpl =
            v8::FunctionTemplate::New(isolate, OverlapCapsule, v8::Local<v8::Value>(), OverlapCapsule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_overlapCapsule").ToLocalChecked(), OverlapCapsule_Tpl);
        v8::Local<v8::Signature> NearestPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> NearestPoint_Tpl =
            v8::FunctionTemplate::New(isolate, NearestPoint, v8::Local<v8::Value>(), NearestPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_nearestPoint").ToLocalChecked(), NearestPoint_Tpl);
        v8::Local<v8::Signature> AddLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddLayer_Tpl =
            v8::FunctionTemplate::New(isolate, AddLayer, v8::Local<v8::Value>(), AddLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addLayer").ToLocalChecked(), AddLayer_Tpl);
        v8::Local<v8::Signature> RemoveLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveLayer_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveLayer, v8::Local<v8::Value>(), RemoveLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeLayer").ToLocalChecked(), RemoveLayer_Tpl);
        v8::Local<v8::Signature> DisposeLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisposeLayer_Tpl =
            v8::FunctionTemplate::New(isolate, DisposeLayer, v8::Local<v8::Value>(), DisposeLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disposeLayer").ToLocalChecked(), DisposeLayer_Tpl);
        v8::Local<v8::Signature> CreateSpriteLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateSpriteLayer_Tpl =
            v8::FunctionTemplate::New(isolate, CreateSpriteLayer, v8::Local<v8::Value>(), CreateSpriteLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createSpriteLayer").ToLocalChecked(), CreateSpriteLayer_Tpl);
        v8::Local<v8::Signature> GetLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLayer_Tpl =
            v8::FunctionTemplate::New(isolate, GetLayer, v8::Local<v8::Value>(), GetLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLayer").ToLocalChecked(), GetLayer_Tpl);
        v8::Local<v8::Signature> Pause_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Pause_Tpl =
            v8::FunctionTemplate::New(isolate, Pause, v8::Local<v8::Value>(), Pause_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pause").ToLocalChecked(), Pause_Tpl);
        v8::Local<v8::Signature> Resume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Resume_Tpl =
            v8::FunctionTemplate::New(isolate, Resume, v8::Local<v8::Value>(), Resume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resume").ToLocalChecked(), Resume_Tpl);
        v8::Local<v8::Signature> Dispose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Dispose_Tpl =
            v8::FunctionTemplate::New(isolate, Dispose, v8::Local<v8::Value>(), Dispose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "dispose").ToLocalChecked(), Dispose_Tpl);
        v8::Local<v8::Signature> CancelAllTimers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelAllTimers_Tpl =
            v8::FunctionTemplate::New(isolate, CancelAllTimers, v8::Local<v8::Value>(), CancelAllTimers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelAllTimers").ToLocalChecked(), CancelAllTimers_Tpl);
        v8::Local<v8::Signature> IsPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsPaused, v8::Local<v8::Value>(), IsPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isPaused").ToLocalChecked(), IsPaused_Tpl);
        v8::Local<v8::Signature> IsDisposed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsDisposed_Tpl =
            v8::FunctionTemplate::New(isolate, IsDisposed, v8::Local<v8::Value>(), IsDisposed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isDisposed").ToLocalChecked(), IsDisposed_Tpl);
        v8::Local<v8::Signature> GetLayerCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLayerCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetLayerCount, v8::Local<v8::Value>(), GetLayerCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLayerCount").ToLocalChecked(), GetLayerCount_Tpl);
        v8::Local<v8::Signature> GetTimeScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTimeScale_Tpl =
            v8::FunctionTemplate::New(isolate, GetTimeScale, v8::Local<v8::Value>(), GetTimeScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTimeScale").ToLocalChecked(), GetTimeScale_Tpl);
        v8::Local<v8::Signature> GetFixedStep_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFixedStep_Tpl =
            v8::FunctionTemplate::New(isolate, GetFixedStep, v8::Local<v8::Value>(), GetFixedStep_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFixedStep").ToLocalChecked(), GetFixedStep_Tpl);
        v8::Local<v8::Signature> GetSimulationTime_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSimulationTime_Tpl =
            v8::FunctionTemplate::New(isolate, GetSimulationTime, v8::Local<v8::Value>(), GetSimulationTime_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSimulationTime").ToLocalChecked(), GetSimulationTime_Tpl);
        v8::Local<v8::Signature> GetDroppedTime_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDroppedTime_Tpl =
            v8::FunctionTemplate::New(isolate, GetDroppedTime, v8::Local<v8::Value>(), GetDroppedTime_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDroppedTime").ToLocalChecked(), GetDroppedTime_Tpl);
        v8::Local<v8::Signature> GetInterpolationAlpha_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetInterpolationAlpha_Tpl =
            v8::FunctionTemplate::New(isolate, GetInterpolationAlpha, v8::Local<v8::Value>(), GetInterpolationAlpha_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getInterpolationAlpha").ToLocalChecked(), GetInterpolationAlpha_Tpl);
        v8::Local<v8::Signature> GetTick_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTick_Tpl =
            v8::FunctionTemplate::New(isolate, GetTick, v8::Local<v8::Value>(), GetTick_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTick").ToLocalChecked(), GetTick_Tpl);
        v8::Local<v8::Signature> IsInputEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsInputEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsInputEnabled, v8::Local<v8::Value>(), IsInputEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isInputEnabled").ToLocalChecked(), IsInputEnabled_Tpl);
        v8::Local<v8::Signature> IsManual_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsManual_Tpl =
            v8::FunctionTemplate::New(isolate, IsManual, v8::Local<v8::Value>(), IsManual_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isManual").ToLocalChecked(), IsManual_Tpl);
        v8::Local<v8::Signature> IsInterpolationEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsInterpolationEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, IsInterpolationEnabled, v8::Local<v8::Value>(), IsInterpolationEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isInterpolationEnabled").ToLocalChecked(), IsInterpolationEnabled_Tpl);
        v8::Local<v8::Signature> SetTimeScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTimeScale_Tpl =
            v8::FunctionTemplate::New(isolate, SetTimeScale, v8::Local<v8::Value>(), SetTimeScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setTimeScale").ToLocalChecked(), SetTimeScale_Tpl);
        v8::Local<v8::Signature> SetFixedStep_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFixedStep_Tpl =
            v8::FunctionTemplate::New(isolate, SetFixedStep, v8::Local<v8::Value>(), SetFixedStep_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFixedStep").ToLocalChecked(), SetFixedStep_Tpl);
        v8::Local<v8::Signature> Advance_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Advance_Tpl =
            v8::FunctionTemplate::New(isolate, Advance, v8::Local<v8::Value>(), Advance_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "advance").ToLocalChecked(), Advance_Tpl);
        v8::Local<v8::Signature> SetManual_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetManual_Tpl =
            v8::FunctionTemplate::New(isolate, SetManual, v8::Local<v8::Value>(), SetManual_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setManual").ToLocalChecked(), SetManual_Tpl);
        v8::Local<v8::Signature> SetInputEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetInputEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, SetInputEnabled, v8::Local<v8::Value>(), SetInputEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setInputEnabled").ToLocalChecked(), SetInputEnabled_Tpl);
        v8::Local<v8::Signature> SetInterpolation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetInterpolation_Tpl =
            v8::FunctionTemplate::New(isolate, SetInterpolation, v8::Local<v8::Value>(), SetInterpolation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setInterpolation").ToLocalChecked(), SetInterpolation_Tpl);
        v8::Local<v8::Signature> GetCamera_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCamera_Tpl =
            v8::FunctionTemplate::New(isolate, GetCamera, v8::Local<v8::Value>(), GetCamera_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCamera").ToLocalChecked(), GetCamera_Tpl);
        v8::Local<v8::Signature> SetCamera_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCamera_Tpl =
            v8::FunctionTemplate::New(isolate, SetCamera, v8::Local<v8::Value>(), SetCamera_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCamera").ToLocalChecked(), SetCamera_Tpl);
        v8::Local<v8::Signature> StartTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartTimer_Tpl =
            v8::FunctionTemplate::New(isolate, StartTimer, v8::Local<v8::Value>(), StartTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startTimer").ToLocalChecked(), StartTimer_Tpl);
        v8::Local<v8::Signature> CancelTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelTimer_Tpl =
            v8::FunctionTemplate::New(isolate, CancelTimer, v8::Local<v8::Value>(), CancelTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelTimer").ToLocalChecked(), CancelTimer_Tpl);
        v8::Local<v8::Signature> PauseTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseTimer_Tpl =
            v8::FunctionTemplate::New(isolate, PauseTimer, v8::Local<v8::Value>(), PauseTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseTimer").ToLocalChecked(), PauseTimer_Tpl);
        v8::Local<v8::Signature> UnpauseTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UnpauseTimer_Tpl =
            v8::FunctionTemplate::New(isolate, UnpauseTimer, v8::Local<v8::Value>(), UnpauseTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unpauseTimer").ToLocalChecked(), UnpauseTimer_Tpl);
        v8::Local<v8::Signature> DelayTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DelayTimer_Tpl =
            v8::FunctionTemplate::New(isolate, DelayTimer, v8::Local<v8::Value>(), DelayTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "delayTimer").ToLocalChecked(), DelayTimer_Tpl);
        v8::Local<v8::Signature> IsTimerPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsTimerPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsTimerPaused, v8::Local<v8::Value>(), IsTimerPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isTimerPaused").ToLocalChecked(), IsTimerPaused_Tpl);
        v8::Local<v8::Signature> GetWhenTimerFiresNext_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWhenTimerFiresNext_Tpl =
            v8::FunctionTemplate::New(isolate, GetWhenTimerFiresNext, v8::Local<v8::Value>(), GetWhenTimerFiresNext_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWhenTimerFiresNext").ToLocalChecked(), GetWhenTimerFiresNext_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SceneWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 70 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 70 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                IEventHandlerWrap* obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<IEventHandlerWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 70 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 70 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 70 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
            }
        } );
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inType"")");
            return;
        }
        long inType = (args.Length()<2) ? pdg::all_events : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->addHandler(inHandler, inType);
        args.GetReturnValue().SetUndefined();
    }

    void SceneWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inType"")");
            return;
        }
        long inType = (args.Length()<2) ? pdg::all_events : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->removeHandler(inHandler, inType);
        args.GetReturnValue().SetUndefined();
    }

    void SceneWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clear();
        args.GetReturnValue().SetUndefined();
    }

    void SceneWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""inEventType"")");
            return;
        }
        long inEventType = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->blockEvent(inEventType);
        args.GetReturnValue().SetUndefined();
    }

    void SceneWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""inEventType"")");
            return;
        }
        long inEventType = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->unblockEvent(inEventType);
        args.GetReturnValue().SetUndefined();
    }
#ifdef PDG_USING_JAVASCRIPT_CORE
    Scene* New_Scene(const v8::FunctionCallbackInfo<v8::Value>& args) { return new Scene(); }
#else
    SceneWrap::SceneWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(New_Scene(args)) {}
    SceneWrap::~SceneWrap()
    {
        if(cppPtr_)
        {
            cppPtr_->mSceneScriptObj.Reset();cppPtr_->mEventEmitterScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;
        }
    }
    Scene* New_Scene(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if(s_Scene_InNewFromCpp)
        {
            return nullptr;
        }
        auto* isolate=args.GetIsolate();auto* cppObj=new Scene();cppObj->addRef();SCENE_SAVE(cppObj,args.This());return cppObj;
    }
#endif
#undef SCENE_SAVE

    void SceneWrap::AddLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->addLayer(layer); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::RemoveLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->removeLayer(layer); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::DisposeLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer); self->disposeLayer(layer); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::CreateSpriteLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!self->createSpriteLayer())
            {
                args.GetReturnValue().SetNull(); return;
            };
            { args.GetReturnValue().Set( SpriteLayerWrap::NewFromCpp(isolate, self->createSpriteLayer()) ); return; };
            ;
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            long index = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); if (!self->getLayer(index)) { args.GetReturnValue().SetNull(); return; };
            if (self->getLayer(index)->mSpriteLayerScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( SpriteLayerWrap::NewFromCpp(isolate, self->getLayer(index)) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, self->getLayer(index)->mSpriteLayerScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::Pause(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { self->pause(); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::Resume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { self->resume(); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::Dispose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { self->dispose(); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::CancelAllTimers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { self->cancelAllTimers(); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isPaused()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsDisposed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isDisposed()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetLayerCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Integer::New(isolate, self->getLayerCount()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetTimeScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getTimeScale()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetFixedStep(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getFixedStep()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetSimulationTime(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getSimulationTime()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetDroppedTime(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getDroppedTime()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetInterpolationAlpha(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getInterpolationAlpha()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetTick(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getTick()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsInputEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isInputEnabled()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsManual(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isManual()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsInterpolationEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isInterpolationEnabled()) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetTimeScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""scale"")");
                return;
            }
            double scale = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setTimeScale(scale); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetFixedStep(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""seconds"")");
                return;
            }
            double seconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setFixedStep(seconds); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::Advance(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""seconds"")");
                return;
            }
            double seconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->advance(seconds); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetManual(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""enabled"")");
                return;
            }
            bool enabled = args[1 -1]->BooleanValue(isolate); self->setManual(enabled); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetInputEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""enabled"")");
                return;
            }
            bool enabled = args[1 -1]->BooleanValue(isolate); self->setInputEnabled(enabled); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetInterpolation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""enabled"")");
                return;
            }
            bool enabled = args[1 -1]->BooleanValue(isolate); self->setInterpolation(enabled); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetCamera(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!self->getCamera())
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (self->getCamera()->mCameraScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( CameraWrap::NewFromCpp(isolate, self->getCamera()) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, self->getCamera()->mCameraScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SetCamera(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try { REQUIRE_CPP_OBJECT_ARG(1,camera,Camera); self->setCamera(camera); args.GetReturnValue().SetUndefined(); }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::StartTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""delayMs"")");
                return;
            }
            double delayMs = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 3, "a boolean (""oneShot"")");
                return;
            }
            bool oneShot = (args.Length()<3) ? true : args[3 -1]->BooleanValue(isolate);; self->startTimer(id,delayMs,oneShot); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::CancelTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); self->cancelTimer(id); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::PauseTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); self->pauseTimer(id); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::UnpauseTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); self->unpauseTimer(id); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::DelayTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""delayMs"")");
                return;
            }
            double delayMs = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->delayTimer(id,delayMs); args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::IsTimerPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isTimerPaused(id)) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::GetWhenTimerFiresNext(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
                return;
            }
            long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getWhenTimerFiresNext(id)) ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::Raycast(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3);
                return;
            }; pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[1 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }; pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[2 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->raycast(start,end,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::SweepCircle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            }; pdg::Point center;
            auto center_isPoint = v8_ValueIsPoint(isolate, args[1 -1], center);
            if (!center_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*center_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""radius"")");
                return;
            }
            double radius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); pdg::Vector delta;
            auto delta_isVector = v8_ValueIsVector(isolate, args[3 -1], delta);
            if (!delta_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*delta_isVector)
            {
                v8_ThrowArgTypeException(isolate, 3, "Vector", *args[3 -1]);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(4,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->sweepCircle(center,radius,delta,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::OverlapPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            }; pdg::Point point;
            auto point_isPoint = v8_ValueIsPoint(isolate, args[1 -1], point);
            if (!point_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*point_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(2,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->overlapPoint(point,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::OverlapCircle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3);
                return;
            }; pdg::Point center;
            auto center_isPoint = v8_ValueIsPoint(isolate, args[1 -1], center);
            if (!center_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*center_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""radius"")");
                return;
            }
            double radius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->overlapCircle(center,radius,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::OverlapBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            }; pdg::RotatedRect box;
            auto box_isRotatedRect = v8_ValueIsRotatedRect(isolate, args[1 -1], box);
            if (!box_isRotatedRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*box_isRotatedRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *args[1 -1]);
                return;
            }; REQUIRE_CPP_OBJECT_ARG(2,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->overlapBox(box,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::OverlapCapsule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            }; pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[1 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }; pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[2 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                return;
            };
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
                return;
            }
            double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); REQUIRE_CPP_OBJECT_ARG(4,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->overlapCapsule(start,end,radius,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void SceneWrap::NearestPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        SceneWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SceneWrap>(args.This());
        Scene* self = dynamic_cast<Scene*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 3)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 3);
                return;
            }; pdg::Point point;
            auto point_isPoint = v8_ValueIsPoint(isolate, args[1 -1], point);
            if (!point_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*point_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""maxDistance"")");
                return;
            }
            double maxDistance = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); REQUIRE_CPP_OBJECT_ARG(3,results,CollisionQueryBuffer);
            { args.GetReturnValue().Set( v8::Number::New(isolate, self->queryNearestPoint(point,maxDistance,*results)) ); return; };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
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
    static bool s_CollisionQueryBuffer_InNewFromCpp = false;

    void CollisionQueryBufferWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = new CollisionQueryBufferWrap(args);
        objWrapper->Wrap(args.This());
        ;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> CollisionQueryBufferWrap::NewFromCpp(v8::Isolate* isolate, CollisionQueryBuffer* cppObj)
    {
        s_CollisionQueryBuffer_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_CollisionQueryBuffer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_CollisionQueryBuffer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(instance);
        { [[maybe_unused]] v8::Local<v8::Object> obj = instance; QUERY_SAVE(cppObj,obj);cppObj->addRef(); }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_CollisionQueryBuffer_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> CollisionQueryBufferWrap::constructorTpl_;

    void CollisionQueryBufferWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "CollisionQueryBuffer").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetCapacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCapacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetCapacity, v8::Local<v8::Value>(), GetCapacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCapacity").ToLocalChecked(), GetCapacity_Tpl);
        v8::Local<v8::Signature> GetPointX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointX_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointX, v8::Local<v8::Value>(), GetPointX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPointX").ToLocalChecked(), GetPointX_Tpl);
        v8::Local<v8::Signature> GetPointY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointY_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointY, v8::Local<v8::Value>(), GetPointY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPointY").ToLocalChecked(), GetPointY_Tpl);
        v8::Local<v8::Signature> GetNormalX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNormalX_Tpl =
            v8::FunctionTemplate::New(isolate, GetNormalX, v8::Local<v8::Value>(), GetNormalX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNormalX").ToLocalChecked(), GetNormalX_Tpl);
        v8::Local<v8::Signature> GetNormalY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNormalY_Tpl =
            v8::FunctionTemplate::New(isolate, GetNormalY, v8::Local<v8::Value>(), GetNormalY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNormalY").ToLocalChecked(), GetNormalY_Tpl);
        v8::Local<v8::Signature> GetCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetCount, v8::Local<v8::Value>(), GetCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCount").ToLocalChecked(), GetCount_Tpl);
        v8::Local<v8::Signature> IsOverflowed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsOverflowed_Tpl =
            v8::FunctionTemplate::New(isolate, IsOverflowed, v8::Local<v8::Value>(), IsOverflowed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isOverflowed").ToLocalChecked(), IsOverflowed_Tpl);
        v8::Local<v8::Signature> Clear_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Clear_Tpl =
            v8::FunctionTemplate::New(isolate, Clear, v8::Local<v8::Value>(), Clear_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clear").ToLocalChecked(), Clear_Tpl);
        v8::Local<v8::Signature> GetCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollider_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollider, v8::Local<v8::Value>(), GetCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCollider").ToLocalChecked(), GetCollider_Tpl);
        v8::Local<v8::Signature> GetShapeId_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetShapeId_Tpl =
            v8::FunctionTemplate::New(isolate, GetShapeId, v8::Local<v8::Value>(), GetShapeId_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getShapeId").ToLocalChecked(), GetShapeId_Tpl);
        v8::Local<v8::Signature> GetPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetPoint, v8::Local<v8::Value>(), GetPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPoint").ToLocalChecked(), GetPoint_Tpl);
        v8::Local<v8::Signature> GetNormal_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNormal_Tpl =
            v8::FunctionTemplate::New(isolate, GetNormal, v8::Local<v8::Value>(), GetNormal_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNormal").ToLocalChecked(), GetNormal_Tpl);
        v8::Local<v8::Signature> GetFraction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFraction_Tpl =
            v8::FunctionTemplate::New(isolate, GetFraction, v8::Local<v8::Value>(), GetFraction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFraction").ToLocalChecked(), GetFraction_Tpl);
        v8::Local<v8::Signature> GetDistance_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDistance_Tpl =
            v8::FunctionTemplate::New(isolate, GetDistance, v8::Local<v8::Value>(), GetDistance_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDistance").ToLocalChecked(), GetDistance_Tpl);
        v8::Local<v8::Signature> GetInitialOverlap_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetInitialOverlap_Tpl =
            v8::FunctionTemplate::New(isolate, GetInitialOverlap, v8::Local<v8::Value>(), GetInitialOverlap_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getInitialOverlap").ToLocalChecked(), GetInitialOverlap_Tpl);
        v8::Local<v8::Signature> Configure_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Configure_Tpl =
            v8::FunctionTemplate::New(isolate, Configure, v8::Local<v8::Value>(), Configure_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "configure").ToLocalChecked(), Configure_Tpl);
        v8::Local<v8::Signature> SelectLayers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SelectLayers_Tpl =
            v8::FunctionTemplate::New(isolate, SelectLayers, v8::Local<v8::Value>(), SelectLayers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "selectLayers").ToLocalChecked(), SelectLayers_Tpl);
        v8::Local<v8::Signature> AddLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddLayer_Tpl =
            v8::FunctionTemplate::New(isolate, AddLayer, v8::Local<v8::Value>(), AddLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addLayer").ToLocalChecked(), AddLayer_Tpl);
        v8::Local<v8::Signature> ExcludeCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ExcludeCollider_Tpl =
            v8::FunctionTemplate::New(isolate, ExcludeCollider, v8::Local<v8::Value>(), ExcludeCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "excludeCollider").ToLocalChecked(), ExcludeCollider_Tpl);
        v8::Local<v8::Signature> ExcludeBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ExcludeBody_Tpl =
            v8::FunctionTemplate::New(isolate, ExcludeBody, v8::Local<v8::Value>(), ExcludeBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "excludeBody").ToLocalChecked(), ExcludeBody_Tpl);
        v8::Local<v8::Signature> SetPredicate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPredicate_Tpl =
            v8::FunctionTemplate::New(isolate, SetPredicate, v8::Local<v8::Value>(), SetPredicate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPredicate").ToLocalChecked(), SetPredicate_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }
    CollisionQueryBuffer* New_CollisionQueryBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        ;
#ifndef PDG_USING_JAVASCRIPT_CORE
        if(s_CollisionQueryBuffer_InNewFromCpp) { return nullptr; }
        auto* isolate=args.GetIsolate();
#endif
        if(args.Length()>1 || (args.Length() && !args[0]->IsNumber()))
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "Expected optional query capacity";
                [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return nullptr;
        }
        const double capacity=args.Length() ? args[0]->NumberValue(isolate->GetCurrentContext()).ToChecked() : 16;
        if(!std::isfinite(capacity)||capacity<0||capacity>1048576||std::floor(capacity)!=capacity)
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "Expected integer query capacity from 0 to 1048576";
                [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return nullptr;
        }
        auto* cppObj=new CollisionQueryBuffer(uint32_t(capacity));
#ifndef PDG_USING_JAVASCRIPT_CORE
        cppObj->addRef();QUERY_SAVE(cppObj,args.This());
#endif
        return cppObj;
    }
#ifndef PDG_USING_JAVASCRIPT_CORE
    CollisionQueryBufferWrap::CollisionQueryBufferWrap(const v8::FunctionCallbackInfo<v8::Value>& args):cppPtr_(New_CollisionQueryBuffer(args)) {}
    CollisionQueryBufferWrap::~CollisionQueryBufferWrap()
    {
        if(cppPtr_)
        {
            cppPtr_->mCollisionQueryBufferScriptObj.Reset();cppPtr_->release();cppPtr_=nullptr;
        }
    }
#endif
#undef QUERY_SAVE

    void CollisionQueryBufferWrap::GetCapacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto value=self->getCapacity();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetPointX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getPointX(index)) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetPointY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getPointY(index)) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetNormalX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getNormalX(index)) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetNormalY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
                return;
            }
            unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getNormalY(index)) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto value=self->getCount();
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::IsOverflowed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto value=self->isOverflowed();
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetShapeId(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getShapeId(index);
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getPoint(index);
            {
                args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetNormal(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getNormal(index);
            {
                args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetFraction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getFraction(index);
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetDistance(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getDistance(index);
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetInitialOverlap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); auto value=self->getInitialOverlap(index);
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, value) ); return;
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::GetCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""indexValue"")");
                return;
            }
            double indexValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if(!std::isfinite(indexValue)||indexValue<0||indexValue>4294967295.0||std::floor(indexValue)!=indexValue)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected unsigned integer hit index";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            const auto index=uint32_t(indexValue); if (!self->getCollider(index))
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (self->getCollider(index)->mColliderScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ColliderWrap::NewFromCpp(isolate, self->getCollider(index)) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, self->getCollider(index)->mColliderScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try {self->clear();args.GetReturnValue().SetUndefined();}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::Configure(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""layers"")");
            return;
        }
        unsigned long layers = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""categories"")");
            return;
        }
        unsigned long categories = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();if (!args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""sensors"")");
            return;
        }
        bool sensors = args[3 -1]->BooleanValue(isolate);
        try {self->configure(layers,categories,sensors);args.GetReturnValue().SetUndefined();}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::SelectLayers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try {self->selectLayers();args.GetReturnValue().SetUndefined();}
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::AddLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        REQUIRE_CPP_OBJECT_ARG(1,layer,SpriteLayer);try
        {
            self->addLayer(layer);args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::ExcludeCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        REQUIRE_CPP_OBJECT_ARG(1,collider,Collider);try
        {
            self->excludeCollider(collider);args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void CollisionQueryBufferWrap::ExcludeBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        REQUIRE_CPP_OBJECT_ARG(1,body,PhysicsBody);try
        {
            self->excludeBody(body);args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
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

    void CollisionQueryBufferWrap::SetPredicate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        CollisionQueryBufferWrap* objWrapper = jswrap::ObjectWrap::Unwrap<CollisionQueryBufferWrap>(args.This());
        CollisionQueryBuffer* self = dynamic_cast<CollisionQueryBuffer*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if(args[0]->IsNull())
            {
                self->setPredicate(
                {
                }
                );args.GetReturnValue().SetUndefined();
            }
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
                return;
            }
            v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
#ifdef PDG_USING_JAVASCRIPT_CORE
            auto predicate=std::make_shared<QueryScriptPredicate>(ctx,func);
#else
            auto predicate=std::make_shared<QueryScriptPredicate>(isolate,func);
#endif
            self->setPredicate([predicate](const Collider& c){return predicate->invoke(c);}
            );args.GetReturnValue().SetUndefined();
        }
        catch(const std::exception& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

}
