// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/particle.cpp
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

#include <cstdlib>
#include "../../common/animation/particle_trail_options.h"

namespace pdg
{

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void Particle_finalize(JSObjectRef object)
    {
        auto* value=static_cast<Particle*>(JSObjectGetPrivate(object)); if (!value) return;
        value->mParticleScriptObj=nullptr; value->mAnimatedScriptObj=nullptr; value->mISerializableScriptObj=nullptr; value->mEventEmitterScriptObj=nullptr;
        JSObjectSetPrivate(object,nullptr); value->release();
    }
#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj=obj; cppObj->mAnimatedScriptObj=obj; cppObj->mISerializableScriptObj=obj; cppObj->mEventEmitterScriptObj=obj
#else
#define PARTICLE_SAVE(cppObj,obj) cppObj->mParticleScriptObj.Reset(isolate,obj); cppObj->mParticleScriptObj.SetWeak(); cppObj->mAnimatedScriptObj.Reset(isolate,obj); cppObj->mAnimatedScriptObj.SetWeak(); cppObj->mISerializableScriptObj.Reset(isolate,obj); cppObj->mISerializableScriptObj.SetWeak(); cppObj->mEventEmitterScriptObj.Reset(isolate,obj); cppObj->mEventEmitterScriptObj.SetWeak()
#endif
    static bool s_Particle_InNewFromCpp = false;

    void ParticleWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = new ParticleWrap(args);
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
    v8::Local<v8::Object> ParticleWrap::NewFromCpp(v8::Isolate* isolate, Particle* cppObj)
    {
        s_Particle_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Particle_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Particle_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(instance);
        { [[maybe_unused]] v8::Local<v8::Object> obj = instance; PARTICLE_SAVE(cppObj,obj); cppObj->addRef(); }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_Particle_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ParticleWrap::constructorTpl_;

    void ParticleWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->Inherit(AnimatedBaseWrap::GetTemplate(isolate));
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Particle").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> PlayScript_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PlayScript_Tpl =
            v8::FunctionTemplate::New(isolate, PlayScript, v8::Local<v8::Value>(), PlayScript_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "playScript").ToLocalChecked(), PlayScript_Tpl);
        v8::Local<v8::Signature> Batch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Batch_Tpl =
            v8::FunctionTemplate::New(isolate, Batch, v8::Local<v8::Value>(), Batch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "batch").ToLocalChecked(), Batch_Tpl);
        v8::Local<v8::Signature> EndBatch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EndBatch_Tpl =
            v8::FunctionTemplate::New(isolate, EndBatch, v8::Local<v8::Value>(), EndBatch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "endBatch").ToLocalChecked(), EndBatch_Tpl);
        v8::Local<v8::Signature> Series_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Series_Tpl =
            v8::FunctionTemplate::New(isolate, Series, v8::Local<v8::Value>(), Series_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "series").ToLocalChecked(), Series_Tpl);
        v8::Local<v8::Signature> EndSeries_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EndSeries_Tpl =
            v8::FunctionTemplate::New(isolate, EndSeries, v8::Local<v8::Value>(), EndSeries_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "endSeries").ToLocalChecked(), EndSeries_Tpl);
        v8::Local<v8::Signature> AndAlso_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AndAlso_Tpl =
            v8::FunctionTemplate::New(isolate, AndAlso, v8::Local<v8::Value>(), AndAlso_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "andAlso").ToLocalChecked(), AndAlso_Tpl);
        v8::Local<v8::Signature> Stagger_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Stagger_Tpl =
            v8::FunctionTemplate::New(isolate, Stagger, v8::Local<v8::Value>(), Stagger_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stagger").ToLocalChecked(), Stagger_Tpl);
        v8::Local<v8::Signature> Mark_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Mark_Tpl =
            v8::FunctionTemplate::New(isolate, Mark, v8::Local<v8::Value>(), Mark_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "mark").ToLocalChecked(), Mark_Tpl);
        v8::Local<v8::Signature> JumpToMark_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> JumpToMark_Tpl =
            v8::FunctionTemplate::New(isolate, JumpToMark, v8::Local<v8::Value>(), JumpToMark_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "jumpToMark").ToLocalChecked(), JumpToMark_Tpl);
        v8::Local<v8::Signature> ScriptOn_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ScriptOn_Tpl =
            v8::FunctionTemplate::New(isolate, ScriptOn, v8::Local<v8::Value>(), ScriptOn_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "on").ToLocalChecked(), ScriptOn_Tpl);
        v8::Local<v8::Signature> TriggerEvent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TriggerEvent_Tpl =
            v8::FunctionTemplate::New(isolate, TriggerEvent, v8::Local<v8::Value>(), TriggerEvent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "triggerEvent").ToLocalChecked(), TriggerEvent_Tpl);
        v8::Local<v8::Signature> OnStarted_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnStarted_Tpl =
            v8::FunctionTemplate::New(isolate, OnStarted, v8::Local<v8::Value>(), OnStarted_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onStarted").ToLocalChecked(), OnStarted_Tpl);
        v8::Local<v8::Signature> OnFinished_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFinished_Tpl =
            v8::FunctionTemplate::New(isolate, OnFinished, v8::Local<v8::Value>(), OnFinished_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFinished").ToLocalChecked(), OnFinished_Tpl);
        v8::Local<v8::Signature> OnScriptFinished_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnScriptFinished_Tpl =
            v8::FunctionTemplate::New(isolate, OnScriptFinished, v8::Local<v8::Value>(), OnScriptFinished_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onScriptFinished").ToLocalChecked(), OnScriptFinished_Tpl);
        v8::Local<v8::Signature> OnMark_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMark_Tpl =
            v8::FunctionTemplate::New(isolate, OnMark, v8::Local<v8::Value>(), OnMark_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMark").ToLocalChecked(), OnMark_Tpl);
        v8::Local<v8::Signature> OnYoyo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnYoyo_Tpl =
            v8::FunctionTemplate::New(isolate, OnYoyo, v8::Local<v8::Value>(), OnYoyo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onYoyo").ToLocalChecked(), OnYoyo_Tpl);
        v8::Local<v8::Signature> OnRepeat_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnRepeat_Tpl =
            v8::FunctionTemplate::New(isolate, OnRepeat, v8::Local<v8::Value>(), OnRepeat_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onRepeat").ToLocalChecked(), OnRepeat_Tpl);
        v8::Local<v8::Signature> OnUntilFired_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnUntilFired_Tpl =
            v8::FunctionTemplate::New(isolate, OnUntilFired, v8::Local<v8::Value>(), OnUntilFired_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onUntilFired").ToLocalChecked(), OnUntilFired_Tpl);
        v8::Local<v8::Signature> When_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> When_Tpl =
            v8::FunctionTemplate::New(isolate, When, v8::Local<v8::Value>(), When_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "when").ToLocalChecked(), When_Tpl);
        v8::Local<v8::Signature> Otherwise_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Otherwise_Tpl =
            v8::FunctionTemplate::New(isolate, Otherwise, v8::Local<v8::Value>(), Otherwise_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "otherwise").ToLocalChecked(), Otherwise_Tpl);
        v8::Local<v8::Signature> EndWhen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EndWhen_Tpl =
            v8::FunctionTemplate::New(isolate, EndWhen, v8::Local<v8::Value>(), EndWhen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "endWhen").ToLocalChecked(), EndWhen_Tpl);
        v8::Local<v8::Signature> EndOtherwise_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EndOtherwise_Tpl =
            v8::FunctionTemplate::New(isolate, EndOtherwise, v8::Local<v8::Value>(), EndOtherwise_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "endOtherwise").ToLocalChecked(), EndOtherwise_Tpl);
        v8::Local<v8::Signature> Until_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Until_Tpl =
            v8::FunctionTemplate::New(isolate, Until, v8::Local<v8::Value>(), Until_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "until").ToLocalChecked(), Until_Tpl);
        v8::Local<v8::Signature> Yoyo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Yoyo_Tpl =
            v8::FunctionTemplate::New(isolate, Yoyo, v8::Local<v8::Value>(), Yoyo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "yoyo").ToLocalChecked(), Yoyo_Tpl);
        v8::Local<v8::Signature> Repeat_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Repeat_Tpl =
            v8::FunctionTemplate::New(isolate, Repeat, v8::Local<v8::Value>(), Repeat_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "repeat").ToLocalChecked(), Repeat_Tpl);
        v8::Local<v8::Signature> Diminish_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Diminish_Tpl =
            v8::FunctionTemplate::New(isolate, Diminish, v8::Local<v8::Value>(), Diminish_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "diminish").ToLocalChecked(), Diminish_Tpl);
        v8::Local<v8::Signature> Increase_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Increase_Tpl =
            v8::FunctionTemplate::New(isolate, Increase, v8::Local<v8::Value>(), Increase_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "increase").ToLocalChecked(), Increase_Tpl);
        v8::Local<v8::Signature> SlowDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SlowDown_Tpl =
            v8::FunctionTemplate::New(isolate, SlowDown, v8::Local<v8::Value>(), SlowDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "slowDown").ToLocalChecked(), SlowDown_Tpl);
        v8::Local<v8::Signature> SpeedUp_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SpeedUp_Tpl =
            v8::FunctionTemplate::New(isolate, SpeedUp, v8::Local<v8::Value>(), SpeedUp_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "speedUp").ToLocalChecked(), SpeedUp_Tpl);
        v8::Local<v8::Signature> StopIt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopIt_Tpl =
            v8::FunctionTemplate::New(isolate, StopIt, v8::Local<v8::Value>(), StopIt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopIt").ToLocalChecked(), StopIt_Tpl);
        v8::Local<v8::Signature> RestartIt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RestartIt_Tpl =
            v8::FunctionTemplate::New(isolate, RestartIt, v8::Local<v8::Value>(), RestartIt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "restartIt").ToLocalChecked(), RestartIt_Tpl);
        v8::Local<v8::Signature> PauseIt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseIt_Tpl =
            v8::FunctionTemplate::New(isolate, PauseIt, v8::Local<v8::Value>(), PauseIt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseIt").ToLocalChecked(), PauseIt_Tpl);
        v8::Local<v8::Signature> ResumeIt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResumeIt_Tpl =
            v8::FunctionTemplate::New(isolate, ResumeIt, v8::Local<v8::Value>(), ResumeIt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resumeIt").ToLocalChecked(), ResumeIt_Tpl);
        v8::Local<v8::Signature> GetBoundingBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBoundingBox_Tpl =
            v8::FunctionTemplate::New(isolate, GetBoundingBox, v8::Local<v8::Value>(), GetBoundingBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBoundingBox").ToLocalChecked(), GetBoundingBox_Tpl);
        v8::Local<v8::Signature> GetRotatedBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotatedBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotatedBounds, v8::Local<v8::Value>(), GetRotatedBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRotatedBounds").ToLocalChecked(), GetRotatedBounds_Tpl);
        v8::Local<v8::Signature> GetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, GetLocation, v8::Local<v8::Value>(), GetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLocation").ToLocalChecked(), GetLocation_Tpl);
        v8::Local<v8::Signature> GetMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMovement_Tpl =
            v8::FunctionTemplate::New(isolate, GetMovement, v8::Local<v8::Value>(), GetMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMovement").ToLocalChecked(), GetMovement_Tpl);
        v8::Local<v8::Signature> GetSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetSize, v8::Local<v8::Value>(), GetSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSize").ToLocalChecked(), GetSize_Tpl);
        v8::Local<v8::Signature> GetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetWidth, v8::Local<v8::Value>(), GetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWidth").ToLocalChecked(), GetWidth_Tpl);
        v8::Local<v8::Signature> GetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetHeight, v8::Local<v8::Value>(), GetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getHeight").ToLocalChecked(), GetHeight_Tpl);
        v8::Local<v8::Signature> GetScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetScale_Tpl =
            v8::FunctionTemplate::New(isolate, GetScale, v8::Local<v8::Value>(), GetScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getScale").ToLocalChecked(), GetScale_Tpl);
        v8::Local<v8::Signature> GetStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetStretching_Tpl =
            v8::FunctionTemplate::New(isolate, GetStretching, v8::Local<v8::Value>(), GetStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getStretching").ToLocalChecked(), GetStretching_Tpl);
        v8::Local<v8::Signature> GetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotation, v8::Local<v8::Value>(), GetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRotation").ToLocalChecked(), GetRotation_Tpl);
        v8::Local<v8::Signature> GetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetCenterOffset, v8::Local<v8::Value>(), GetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCenterOffset").ToLocalChecked(), GetCenterOffset_Tpl);
        v8::Local<v8::Signature> GetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpin, v8::Local<v8::Value>(), GetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpin").ToLocalChecked(), GetSpin_Tpl);
        v8::Local<v8::Signature> SetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, SetLocation, v8::Local<v8::Value>(), SetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLocation").ToLocalChecked(), SetLocation_Tpl);
        v8::Local<v8::Signature> MoveTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveTo, v8::Local<v8::Value>(), MoveTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveTo").ToLocalChecked(), MoveTo_Tpl);
        v8::Local<v8::Signature> MoveBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveBy_Tpl =
            v8::FunctionTemplate::New(isolate, MoveBy, v8::Local<v8::Value>(), MoveBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveBy").ToLocalChecked(), MoveBy_Tpl);
        v8::Local<v8::Signature> SetMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMovement_Tpl =
            v8::FunctionTemplate::New(isolate, SetMovement, v8::Local<v8::Value>(), SetMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMovement").ToLocalChecked(), SetMovement_Tpl);
        v8::Local<v8::Signature> ChangeMovementTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeMovementTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeMovementTo, v8::Local<v8::Value>(), ChangeMovementTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeMovementTo").ToLocalChecked(), ChangeMovementTo_Tpl);
        v8::Local<v8::Signature> ChangeMovementBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeMovementBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeMovementBy, v8::Local<v8::Value>(), ChangeMovementBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeMovementBy").ToLocalChecked(), ChangeMovementBy_Tpl);
        v8::Local<v8::Signature> SetSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSize_Tpl =
            v8::FunctionTemplate::New(isolate, SetSize, v8::Local<v8::Value>(), SetSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSize").ToLocalChecked(), SetSize_Tpl);
        v8::Local<v8::Signature> ChangeCenterOffsetTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenterOffsetTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenterOffsetTo, v8::Local<v8::Value>(), ChangeCenterOffsetTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenterOffsetTo").ToLocalChecked(), ChangeCenterOffsetTo_Tpl);
        v8::Local<v8::Signature> ChangeCenterOffsetBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenterOffsetBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenterOffsetBy, v8::Local<v8::Value>(), ChangeCenterOffsetBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenterOffsetBy").ToLocalChecked(), ChangeCenterOffsetBy_Tpl);
        v8::Local<v8::Signature> SetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, SetWidth, v8::Local<v8::Value>(), SetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setWidth").ToLocalChecked(), SetWidth_Tpl);
        v8::Local<v8::Signature> SetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, SetHeight, v8::Local<v8::Value>(), SetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setHeight").ToLocalChecked(), SetHeight_Tpl);
        v8::Local<v8::Signature> SetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, SetRotation, v8::Local<v8::Value>(), SetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setRotation").ToLocalChecked(), SetRotation_Tpl);
        v8::Local<v8::Signature> SetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpin, v8::Local<v8::Value>(), SetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSpin").ToLocalChecked(), SetSpin_Tpl);
        v8::Local<v8::Signature> SetGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, SetGrowing, v8::Local<v8::Value>(), SetGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setGrowing").ToLocalChecked(), SetGrowing_Tpl);
        v8::Local<v8::Signature> SetStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetStretching_Tpl =
            v8::FunctionTemplate::New(isolate, SetStretching, v8::Local<v8::Value>(), SetStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setStretching").ToLocalChecked(), SetStretching_Tpl);
        v8::Local<v8::Signature> SetScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetScale_Tpl =
            v8::FunctionTemplate::New(isolate, SetScale, v8::Local<v8::Value>(), SetScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setScale").ToLocalChecked(), SetScale_Tpl);
        v8::Local<v8::Signature> ChangeSpinTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSpinTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSpinTo, v8::Local<v8::Value>(), ChangeSpinTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSpinTo").ToLocalChecked(), ChangeSpinTo_Tpl);
        v8::Local<v8::Signature> ChangeSpinBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSpinBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSpinBy, v8::Local<v8::Value>(), ChangeSpinBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSpinBy").ToLocalChecked(), ChangeSpinBy_Tpl);
        v8::Local<v8::Signature> ChangeGrowingTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeGrowingTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeGrowingTo, v8::Local<v8::Value>(), ChangeGrowingTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeGrowingTo").ToLocalChecked(), ChangeGrowingTo_Tpl);
        v8::Local<v8::Signature> ChangeGrowingBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeGrowingBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeGrowingBy, v8::Local<v8::Value>(), ChangeGrowingBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeGrowingBy").ToLocalChecked(), ChangeGrowingBy_Tpl);
        v8::Local<v8::Signature> ChangeStretchingTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeStretchingTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeStretchingTo, v8::Local<v8::Value>(), ChangeStretchingTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeStretchingTo").ToLocalChecked(), ChangeStretchingTo_Tpl);
        v8::Local<v8::Signature> ChangeStretchingBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeStretchingBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeStretchingBy, v8::Local<v8::Value>(), ChangeStretchingBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeStretchingBy").ToLocalChecked(), ChangeStretchingBy_Tpl);
        v8::Local<v8::Signature> ChangeScaleTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeScaleTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeScaleTo, v8::Local<v8::Value>(), ChangeScaleTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeScaleTo").ToLocalChecked(), ChangeScaleTo_Tpl);
        v8::Local<v8::Signature> ChangeScaleBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeScaleBy_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeScaleBy, v8::Local<v8::Value>(), ChangeScaleBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeScaleBy").ToLocalChecked(), ChangeScaleBy_Tpl);
        v8::Local<v8::Signature> Grow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Grow_Tpl =
            v8::FunctionTemplate::New(isolate, Grow, v8::Local<v8::Value>(), Grow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "grow").ToLocalChecked(), Grow_Tpl);
        v8::Local<v8::Signature> Stretch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Stretch_Tpl =
            v8::FunctionTemplate::New(isolate, Stretch, v8::Local<v8::Value>(), Stretch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stretch").ToLocalChecked(), Stretch_Tpl);
        v8::Local<v8::Signature> ResizeBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResizeBy_Tpl =
            v8::FunctionTemplate::New(isolate, ResizeBy, v8::Local<v8::Value>(), ResizeBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resizeBy").ToLocalChecked(), ResizeBy_Tpl);
        v8::Local<v8::Signature> ResizeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResizeTo_Tpl =
            v8::FunctionTemplate::New(isolate, ResizeTo, v8::Local<v8::Value>(), ResizeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resizeTo").ToLocalChecked(), ResizeTo_Tpl);
        v8::Local<v8::Signature> RotateBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateBy_Tpl =
            v8::FunctionTemplate::New(isolate, RotateBy, v8::Local<v8::Value>(), RotateBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateBy").ToLocalChecked(), RotateBy_Tpl);
        v8::Local<v8::Signature> RotateTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateTo_Tpl =
            v8::FunctionTemplate::New(isolate, RotateTo, v8::Local<v8::Value>(), RotateTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateTo").ToLocalChecked(), RotateTo_Tpl);
        v8::Local<v8::Signature> SetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, SetCenterOffset, v8::Local<v8::Value>(), SetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCenterOffset").ToLocalChecked(), SetCenterOffset_Tpl);
        v8::Local<v8::Signature> SetFlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipX_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipX, v8::Local<v8::Value>(), SetFlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipX").ToLocalChecked(), SetFlipX_Tpl);
        v8::Local<v8::Signature> SetFlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipY_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipY, v8::Local<v8::Value>(), SetFlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipY").ToLocalChecked(), SetFlipY_Tpl);
        v8::Local<v8::Signature> StopMovement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopMovement_Tpl =
            v8::FunctionTemplate::New(isolate, StopMovement, v8::Local<v8::Value>(), StopMovement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopMovement").ToLocalChecked(), StopMovement_Tpl);
        v8::Local<v8::Signature> StopSpinning_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopSpinning_Tpl =
            v8::FunctionTemplate::New(isolate, StopSpinning, v8::Local<v8::Value>(), StopSpinning_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopSpinning").ToLocalChecked(), StopSpinning_Tpl);
        v8::Local<v8::Signature> StopGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, StopGrowing, v8::Local<v8::Value>(), StopGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopGrowing").ToLocalChecked(), StopGrowing_Tpl);
        v8::Local<v8::Signature> StopStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopStretching_Tpl =
            v8::FunctionTemplate::New(isolate, StopStretching, v8::Local<v8::Value>(), StopStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopStretching").ToLocalChecked(), StopStretching_Tpl);
        v8::Local<v8::Signature> PauseSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, PauseSchedule, v8::Local<v8::Value>(), PauseSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseSchedule").ToLocalChecked(), PauseSchedule_Tpl);
        v8::Local<v8::Signature> ResumeSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResumeSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, ResumeSchedule, v8::Local<v8::Value>(), ResumeSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resumeSchedule").ToLocalChecked(), ResumeSchedule_Tpl);
        v8::Local<v8::Signature> CancelSchedule_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelSchedule_Tpl =
            v8::FunctionTemplate::New(isolate, CancelSchedule, v8::Local<v8::Value>(), CancelSchedule_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelSchedule").ToLocalChecked(), CancelSchedule_Tpl);
        v8::Local<v8::Signature> FlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipX_Tpl =
            v8::FunctionTemplate::New(isolate, FlipX, v8::Local<v8::Value>(), FlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipX").ToLocalChecked(), FlipX_Tpl);
        v8::Local<v8::Signature> FlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipY_Tpl =
            v8::FunctionTemplate::New(isolate, FlipY, v8::Local<v8::Value>(), FlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipY").ToLocalChecked(), FlipY_Tpl);
        v8::Local<v8::Signature> AndThen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AndThen_Tpl =
            v8::FunctionTemplate::New(isolate, AndThen, v8::Local<v8::Value>(), AndThen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "andThen").ToLocalChecked(), AndThen_Tpl);
        v8::Local<v8::Signature> IsFlippedX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedX_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedX, v8::Local<v8::Value>(), IsFlippedX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedX").ToLocalChecked(), IsFlippedX_Tpl);
        v8::Local<v8::Signature> IsFlippedY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedY_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedY, v8::Local<v8::Value>(), IsFlippedY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedY").ToLocalChecked(), IsFlippedY_Tpl);
        v8::Local<v8::Signature> IsSchedulePaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSchedulePaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsSchedulePaused, v8::Local<v8::Value>(), IsSchedulePaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSchedulePaused").ToLocalChecked(), IsSchedulePaused_Tpl);
        v8::Local<v8::Signature> HasScheduledAnimations_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasScheduledAnimations_Tpl =
            v8::FunctionTemplate::New(isolate, HasScheduledAnimations, v8::Local<v8::Value>(), HasScheduledAnimations_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasScheduledAnimations").ToLocalChecked(), HasScheduledAnimations_Tpl);
        v8::Local<v8::Signature> Wait_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Wait_Tpl =
            v8::FunctionTemplate::New(isolate, Wait, v8::Local<v8::Value>(), Wait_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "wait").ToLocalChecked(), Wait_Tpl);
        v8::Local<v8::Signature> AddAnimationHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddAnimationHelper_Tpl =
            v8::FunctionTemplate::New(isolate, AddAnimationHelper, v8::Local<v8::Value>(), AddAnimationHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addAnimationHelper").ToLocalChecked(), AddAnimationHelper_Tpl);
        v8::Local<v8::Signature> RemoveAnimationHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAnimationHelper_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAnimationHelper, v8::Local<v8::Value>(), RemoveAnimationHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAnimationHelper").ToLocalChecked(), RemoveAnimationHelper_Tpl);
        v8::Local<v8::Signature> ClearAnimationHelpers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearAnimationHelpers_Tpl =
            v8::FunctionTemplate::New(isolate, ClearAnimationHelpers, v8::Local<v8::Value>(), ClearAnimationHelpers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearAnimationHelpers").ToLocalChecked(), ClearAnimationHelpers_Tpl);
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
        v8::Local<v8::Signature> ReadPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ReadPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, ReadPhysics, v8::Local<v8::Value>(), ReadPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_readPhysics").ToLocalChecked(), ReadPhysics_Tpl);
        v8::Local<v8::Signature> SetupPhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupPhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, SetupPhysicsBody, v8::Local<v8::Value>(), SetupPhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupPhysicsBody").ToLocalChecked(), SetupPhysicsBody_Tpl);
        v8::Local<v8::Signature> RemovePhysicsBody_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemovePhysicsBody_Tpl =
            v8::FunctionTemplate::New(isolate, RemovePhysicsBody, v8::Local<v8::Value>(), RemovePhysicsBody_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removePhysicsBody").ToLocalChecked(), RemovePhysicsBody_Tpl);
        v8::Local<v8::Signature> ReadCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ReadCollider_Tpl =
            v8::FunctionTemplate::New(isolate, ReadCollider, v8::Local<v8::Value>(), ReadCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_readCollider").ToLocalChecked(), ReadCollider_Tpl);
        v8::Local<v8::Signature> SetupCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupCollider_Tpl =
            v8::FunctionTemplate::New(isolate, SetupCollider, v8::Local<v8::Value>(), SetupCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupCollider").ToLocalChecked(), SetupCollider_Tpl);
        v8::Local<v8::Signature> RemoveCollider_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveCollider_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveCollider, v8::Local<v8::Value>(), RemoveCollider_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeCollider").ToLocalChecked(), RemoveCollider_Tpl);
        v8::Local<v8::Signature> SetupParticleEmitter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetupParticleEmitter_Tpl =
            v8::FunctionTemplate::New(isolate, SetupParticleEmitter, v8::Local<v8::Value>(), SetupParticleEmitter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setupParticleEmitter").ToLocalChecked(), SetupParticleEmitter_Tpl);
        v8::Local<v8::Signature> GetParticleEmitter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetParticleEmitter_Tpl =
            v8::FunctionTemplate::New(isolate, GetParticleEmitter, v8::Local<v8::Value>(), GetParticleEmitter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getParticleEmitter").ToLocalChecked(), GetParticleEmitter_Tpl);
        v8::Local<v8::Signature> RemoveParticleEmitter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveParticleEmitter_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveParticleEmitter, v8::Local<v8::Value>(), RemoveParticleEmitter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeParticleEmitter").ToLocalChecked(), RemoveParticleEmitter_Tpl);
        v8::Local<v8::Signature> SetTrail_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTrail_Tpl =
            v8::FunctionTemplate::New(isolate, SetTrail, v8::Local<v8::Value>(), SetTrail_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setTrail").ToLocalChecked(), SetTrail_Tpl);
        v8::Local<v8::Signature> ClearTrail_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearTrail_Tpl =
            v8::FunctionTemplate::New(isolate, ClearTrail, v8::Local<v8::Value>(), ClearTrail_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearTrail").ToLocalChecked(), ClearTrail_Tpl);
        v8::Local<v8::Signature> BreakTrail_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BreakTrail_Tpl =
            v8::FunctionTemplate::New(isolate, BreakTrail, v8::Local<v8::Value>(), BreakTrail_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "breakTrail").ToLocalChecked(), BreakTrail_Tpl);
        v8::Local<v8::Signature> HasTrail_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasTrail_Tpl =
            v8::FunctionTemplate::New(isolate, HasTrail, v8::Local<v8::Value>(), HasTrail_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasTrail").ToLocalChecked(), HasTrail_Tpl);
        v8::Local<v8::Signature> GetTrailPointCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTrailPointCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetTrailPointCount, v8::Local<v8::Value>(), GetTrailPointCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTrailPointCount").ToLocalChecked(), GetTrailPointCount_Tpl);
        v8::Local<v8::Signature> ClearContent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearContent_Tpl =
            v8::FunctionTemplate::New(isolate, ClearContent, v8::Local<v8::Value>(), ClearContent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearContent").ToLocalChecked(), ClearContent_Tpl);
        v8::Local<v8::Signature> HasContent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasContent_Tpl =
            v8::FunctionTemplate::New(isolate, HasContent, v8::Local<v8::Value>(), HasContent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasContent").ToLocalChecked(), HasContent_Tpl);
        v8::Local<v8::Signature> SetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, SetOpacity, v8::Local<v8::Value>(), SetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setOpacity").ToLocalChecked(), SetOpacity_Tpl);
        v8::Local<v8::Signature> GetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetOpacity, v8::Local<v8::Value>(), GetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getOpacity").ToLocalChecked(), GetOpacity_Tpl);
        v8::Local<v8::Signature> FadeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeTo_Tpl =
            v8::FunctionTemplate::New(isolate, FadeTo, v8::Local<v8::Value>(), FadeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeTo").ToLocalChecked(), FadeTo_Tpl);
        v8::Local<v8::Signature> SetLifetime_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLifetime_Tpl =
            v8::FunctionTemplate::New(isolate, SetLifetime, v8::Local<v8::Value>(), SetLifetime_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLifetime").ToLocalChecked(), SetLifetime_Tpl);
        v8::Local<v8::Signature> GetLifetime_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLifetime_Tpl =
            v8::FunctionTemplate::New(isolate, GetLifetime, v8::Local<v8::Value>(), GetLifetime_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLifetime").ToLocalChecked(), GetLifetime_Tpl);
        v8::Local<v8::Signature> GetAge_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAge_Tpl =
            v8::FunctionTemplate::New(isolate, GetAge, v8::Local<v8::Value>(), GetAge_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAge").ToLocalChecked(), GetAge_Tpl);
        v8::Local<v8::Signature> IsAlive_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAlive_Tpl =
            v8::FunctionTemplate::New(isolate, IsAlive, v8::Local<v8::Value>(), IsAlive_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAlive").ToLocalChecked(), IsAlive_Tpl);
        v8::Local<v8::Signature> Expire_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Expire_Tpl =
            v8::FunctionTemplate::New(isolate, Expire, v8::Local<v8::Value>(), Expire_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "expire").ToLocalChecked(), Expire_Tpl);
        v8::Local<v8::Signature> GetLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLayer_Tpl =
            v8::FunctionTemplate::New(isolate, GetLayer, v8::Local<v8::Value>(), GetLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLayer").ToLocalChecked(), GetLayer_Tpl);
        v8::Local<v8::Signature> Animate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Animate_Tpl =
            v8::FunctionTemplate::New(isolate, Animate, v8::Local<v8::Value>(), Animate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "animate").ToLocalChecked(), Animate_Tpl);
#ifndef PDG_NO_GUI
        v8::Local<v8::Signature> SetImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetImage_Tpl =
            v8::FunctionTemplate::New(isolate, SetImage, v8::Local<v8::Value>(), SetImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setImage").ToLocalChecked(), SetImage_Tpl);
        v8::Local<v8::Signature> SetDrawing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDrawing_Tpl =
            v8::FunctionTemplate::New(isolate, SetDrawing, v8::Local<v8::Value>(), SetDrawing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDrawing").ToLocalChecked(), SetDrawing_Tpl);
#endif
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void ParticleWrap::PlayScript(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
                return;
            }
            v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* name = *name_Str;;
            self->playScript(name); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Batch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->batch(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::EndBatch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->endBatch(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Series(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->series(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::EndSeries(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->endSeries(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::AndAlso(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->andAlso(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Stagger(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""intervalSeconds"")");
                return;
            }
            double intervalSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->stagger(intervalSeconds); { args.GetReturnValue().Set( args.This() ); return; };
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

    void ParticleWrap::Mark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if(args.Length()>2)
            {
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
            }
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
                return;
            }
            v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* name = *name_Str;;
            if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 2, "a boolean (""saveState"")");
                return;
            }
            bool saveState = (args.Length()<2) ? true : args[2 -1]->BooleanValue(isolate);;
            self->mark(name, saveState); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::JumpToMark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if(args.Length()>2)
            {
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
            }
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
                return;
            }
            v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* name = *name_Str;;
            if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 2, "a boolean (""restoreState"")");
                return;
            }
            bool restoreState = (args.Length()<2) ? true : args[2 -1]->BooleanValue(isolate);;
            self->jumpToMark(name, restoreState); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::When(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""evaluator"")");
                return;
            }
            v8::Local<v8::Function> evaluator = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->when(MakeAnimationEvaluator(evaluator)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ScriptOn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""event"")");
                return;
            }
            v8::String::Utf8Value event_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* event = *event_Str;;
            if (!args[2 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 2, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[2 -1]);;
            self->on(event, MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnStarted(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onStarted(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::TriggerEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""name"")");
                return;
            }
            v8::String::Utf8Value name_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* name = *name_Str;;
            self->triggerEvent(name); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onFinished(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnScriptFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onScriptFinished(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnMark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onMark(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnYoyo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onYoyo(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnRepeat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onRepeat(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::OnUntilFired(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""handler"")");
                return;
            }
            v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->onUntilFired(MakeAnimationEventHandler(handler)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Otherwise(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->otherwise(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::EndWhen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->endWhen(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::EndOtherwise(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->endOtherwise(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Until(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsFunction())
            {
                v8_ThrowArgTypeException(isolate, 1, "a function (""evaluator"")");
                return;
            }
            v8::Local<v8::Function> evaluator = v8::Local<v8::Function>::Cast(args[1 -1]);;
            self->until(MakeAnimationEvaluator(evaluator)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Yoyo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->yoyo(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Repeat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0, true);
                return;
            };
            if (args.Length()>1)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
            }
            if (args.Length() >= 1 && !args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""countValue"")");
                return;
            }
            double countValue = (args.Length()<1) ? -1 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() && (!std::isfinite(countValue) || countValue<0 || countValue>INT32_MAX || std::floor(countValue)!=countValue)) throw std::invalid_argument("Repeat count must be a nonnegative integer");
            self->repeat(static_cast<int>(countValue)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Diminish(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (args.Length()>3)
            {
                if (args.Length() != 3)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 3);
                    return;
                };
            }
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
                return;
            }
            long easing = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            self->diminish(factor, seconds, easingIdToFunc(easing)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Increase(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (args.Length()>3)
            {
                if (args.Length() != 3)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 3);
                    return;
                };
            }
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
                return;
            }
            long easing = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            self->increase(factor, seconds, easingIdToFunc(easing)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SlowDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (args.Length()>3)
            {
                if (args.Length() != 3)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 3);
                    return;
                };
            }
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
                return;
            }
            long easing = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            self->slowDown(factor, seconds, easingIdToFunc(easing)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SpeedUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (args.Length()>3)
            {
                if (args.Length() != 3)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 3);
                    return;
                };
            }
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
                return;
            }
            long easing = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            self->speedUp(factor, seconds, easingIdToFunc(easing)); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::StopIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopIt(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RestartIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->restartIt(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::PauseIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->pauseIt(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ResumeIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->resumeIt(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Rect value=self->getBoundingBox(); { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::RotatedRect value=self->getRotatedBounds(); { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Point value=self->getLocation(); { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Offset value=self->getMovement(); { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Offset value=self->getSize(); { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            double value=self->getWidth(); { args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            double value=self->getHeight(); { args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Offset value=self->getScale(); { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Offset value=self->getStretching(); { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            double value=self->getRotation(); { args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            pdg::Offset value=self->getCenterOffset(); { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            double value=self->getSpin(); { args.GetReturnValue().Set( v8::Number::New(isolate, value) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Point value;
            auto isPoint = v8_ValueIsPoint(isolate, args[0], value);
            if (!isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*isPoint)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setLocation(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setLocation(x, y); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Point value;
            auto isPoint = v8_ValueIsPoint(isolate, args[0], value);
            if (!isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*isPoint)
            {
                if (args.Length() == 1)
                {
                    self->moveTo(value);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->moveTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() == 2)
                {
                    self->moveTo(x, y);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->moveTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::MoveBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() == 1)
                {
                    self->moveBy(value);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->moveBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() == 2)
                {
                    self->moveBy(x, y);
                    {
                        args.GetReturnValue().Set( args.This() ); return;
                    };
                }
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->moveBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setMovement(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setMovement(xPerSecond, yPerSecond); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeMovementTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeMovementTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeMovementTo(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeMovementBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Vector value;
            auto converted = v8_ValueIsVector(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeMovementBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""xPerSecond"")");
                    return;
                }
                double xPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""yPerSecond"")");
                    return;
                }
                double yPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeMovementBy(xPerSecond, yPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (args.Length() != 1)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 1);
                    return;
                };
                self->setSize(value); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""width"")");
                    return;
                }
                double width = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
                    return;
                }
                double height = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() != 2)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 2);
                    return;
                };
                self->setSize(width, height); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeCenterOffsetTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeCenterOffsetTo(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeCenterOffsetTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeCenterOffsetBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            pdg::Offset value;
            auto converted = v8_ValueIsOffset(isolate, args[0], value);
            if (!converted.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (*converted)
            {
                if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 3 && !args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeCenterOffsetBy(value, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
            else
            {
                if (!args[1 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                    return;
                }
                double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                    return;
                }
                double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (!args[3 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                    return;
                }
                double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
                if (args.Length() >= 4 && !args[4 -1]->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                    return;
                }
                double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
                if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected an integer easing constant";
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
                const int easing = static_cast<int>(easingValue);
                if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
                {
                    std::ostringstream excpt_;
                    excpt_ << "Unknown easing constant";
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
                self->changeCenterOffsetBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
            }
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setWidth(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setHeight(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setRotation(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setSpin(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->setGrowing(value); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2);
                return;
            };
            self->setStretching(widthPerSecond, heightPerSecond); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = (args.Length()<2) ? x : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            self->setScale(x, y); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeSpinTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radiansPerSecond"")");
                return;
            }
            double radiansPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeSpinTo(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeSpinBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radiansPerSecond"")");
                return;
            }
            double radiansPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeSpinBy(radiansPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeGrowingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""amountPerSecond"")");
                return;
            }
            double amountPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeGrowingTo(amountPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeGrowingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""amountPerSecond"")");
                return;
            }
            double amountPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeGrowingBy(amountPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeStretchingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeStretchingTo(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeStretchingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthPerSecond"")");
                return;
            }
            double widthPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightPerSecond"")");
                return;
            }
            double heightPerSecond = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::linearTween) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeStretchingBy(widthPerSecond, heightPerSecond, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeScaleTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeScaleTo(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ChangeScaleBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->changeScaleBy(x, y, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
                return;
            }
            double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->grow(factor);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->grow(factor, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""widthFactor"")");
                return;
            }
            double widthFactor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""heightFactor"")");
                return;
            }
            double heightFactor = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 2)
            {
                self->stretch(widthFactor, heightFactor);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->stretch(widthFactor, heightFactor, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ResizeBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaWidth"")");
                return;
            }
            double deltaWidth = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaHeight"")");
                return;
            }
            double deltaHeight = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 2)
            {
                self->resizeBy(deltaWidth, deltaHeight);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->resizeBy(deltaWidth, deltaHeight, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""width"")");
                return;
            }
            double width = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
                return;
            }
            double height = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<4) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            self->resizeTo(width, height, durationSeconds, gEasingFunctions[easing]); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RotateBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
                return;
            }
            double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->rotateBy(radians);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""directionValue"")");
                return;
            }
            double directionValue = (args.Length()<4) ? static_cast<int>(rotationDirection_AsSpecified) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer rotation direction";
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
            const int direction = static_cast<int>(directionValue);
            self->rotateBy(radians, durationSeconds, gEasingFunctions[easing], direction); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
                return;
            }
            double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() == 1)
            {
                self->rotateTo(radians);
                {
                    args.GetReturnValue().Set( args.This() ); return;
                };
            }
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
                return;
            }
            double easingValue = (args.Length()<3) ? static_cast<int>(EasingFuncRef::easeInOutQuad) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(easingValue) || std::floor(easingValue) != easingValue || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer easing constant";
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
            const int easing = static_cast<int>(easingValue);
            if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !gEasingFunctions[easing])
            {
                std::ostringstream excpt_;
                excpt_ << "Unknown easing constant";
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
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""directionValue"")");
                return;
            }
            double directionValue = (args.Length()<4) ? static_cast<int>(rotationDirection_AsSpecified) : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue || directionValue < 0 || directionValue > 3)
            {
                std::ostringstream excpt_;
                excpt_ << "Expected an integer rotation direction";
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
            const int direction = static_cast<int>(directionValue);
            self->rotateTo(radians, durationSeconds, gEasingFunctions[easing], direction); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; pdg::Offset offset;
            auto offset_isOffset = v8_ValueIsOffset(isolate, args[1 -1], offset);
            if (!offset_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*offset_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            self->setCenterOffset(offset); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""flip"")");
                return;
            }
            bool flip = args[1 -1]->BooleanValue(isolate);
            self->setFlipX(flip); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""flip"")");
                return;
            }
            bool flip = args[1 -1]->BooleanValue(isolate);
            self->setFlipY(flip); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::StopMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopMovement(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopSpinning(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopGrowing(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->stopStretching(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::PauseSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->pauseSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ResumeSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->resumeSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::CancelSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->cancelSchedule(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->flipX(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->flipY(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::AndThen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->andThen(); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            try
            {
                ;
                if (args.Length() != 0)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 0);
                    return;
                };
                { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isFlippedX()) ); return; };
            }
            catch (const std::exception& error)
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
        catch (const std::exception& error)
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

    void ParticleWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            try
            {
                ;
                if (args.Length() != 0)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 0);
                    return;
                };
                { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isFlippedY()) ); return; };
            }
            catch (const std::exception& error)
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
        catch (const std::exception& error)
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

    void ParticleWrap::IsSchedulePaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isSchedulePaused()) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::HasScheduledAnimations(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->hasScheduledAnimations()) ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""durationSeconds"")");
                return;
            }
            double durationSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            self->wait(durationSeconds); { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
            {
                std::cerr << __func__<<":"<< 77 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
            }
            else if (!args[0]->IsObject())
            {
                std::cerr << __func__<<":"<< 77 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
            }
            else
            {
                v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                    v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                    char* objName = *objNameStr;
                    IAnimationHelperWrap* obj__ = dynamic_cast<IAnimationHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                    if (!obj__)
                {
                    v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                        if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                    {
                        obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                            obj__ = dynamic_cast<IAnimationHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                    }
                    if (obj__)
                    {
                        std::cout << __func__<<":"<< 77 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                    }
                    else
                    {
                        std::cout << __func__<<":"<< 77 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                    }
                }
                else
                {
                    IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                        std::cout << __func__<<":"<< 77 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
                }
            } );
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, IAnimationHelper);
            self->addAnimationHelper(helper);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, helper, IAnimationHelper);
            self->removeAnimationHelper(helper);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->clearAnimationHelpers();
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 78 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 78 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 78 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 78 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 78 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void ParticleWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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

    void ParticleWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clear();
        args.GetReturnValue().SetUndefined();
    }

    void ParticleWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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

    void ParticleWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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
    void CleanupParticleScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

#ifdef PDG_USING_JAVASCRIPT_CORE
    Particle* New_Particle(const v8::FunctionCallbackInfo<v8::Value>& args) { return new Particle(); }
#else
    ParticleWrap::ParticleWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(New_Particle(args)) {}
    ParticleWrap::~ParticleWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mParticleScriptObj.Reset(); cppPtr_->mAnimatedScriptObj.Reset(); cppPtr_->mISerializableScriptObj.Reset(); cppPtr_->mEventEmitterScriptObj.Reset(); cppPtr_->release(); cppPtr_=nullptr;
        }
    }
    Particle* New_Particle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Particle_InNewFromCpp) return nullptr;
        auto* isolate=args.GetIsolate(); auto* cppObj=new Particle(); cppObj->addRef();
        PARTICLE_SAVE(cppObj,args.This()); return cppObj;
    }
#endif
#undef PARTICLE_SAVE

    void ParticleWrap::SetTrail(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            }; REQUIRE_OBJECT_ARG(1,options);
            auto get=[&](const char* name)
            {
#ifdef PDG_USING_JAVASCRIPT_CORE
                auto key=JSStringCreateWithUTF8CString(name); auto result=JSObjectGetProperty(ctx,options,key,exception); JSStringRelease(key);
                if(exception && *exception) { throw std::invalid_argument("Unable to read trail option"); }
                return result;
#else
                v8::Local<v8::Value> result;
                if(!options->Get(isolate->GetCurrentContext(),v8::String::NewFromUtf8(isolate,name).ToLocalChecked()).ToLocal(&result)) { throw std::invalid_argument("Unable to read trail option"); }
                return result;
#endif
            };
            auto number=[&](const char* key,double fallback)
            {
                auto value=get(key); if(value->IsUndefined())return fallback; if(!value->IsNumber())
                {
                    throw std::invalid_argument("Expected numeric trail option");
                }
                return double(value->NumberValue(isolate->GetCurrentContext()).ToChecked());
            };
            auto color=[&](Color fallback)
            {
                auto value=get("color");if(value->IsUndefined())return fallback; Color result;auto ok=v8_ValueIsColor(isolate, value, result);if(!ok.has_value() || !*ok)
                {
                    throw std::invalid_argument("Expected trail Color");
                }
                return result;
            };
            self->setTrail(readParticleTrailOptions(number,color)); { args.GetReturnValue().Set( args.This() ); return; };
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

    void ParticleWrap::ClearTrail(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->clearTrail();
            {
                args.GetReturnValue().Set( args.This() ); return;
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

    void ParticleWrap::BreakTrail(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->breakTrail();
            {
                args.GetReturnValue().Set( args.This() ); return;
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

    void ParticleWrap::HasTrail(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->hasTrail()) ); return;
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

    void ParticleWrap::GetTrailPointCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->getTrailPointCount()) ); return;
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

    void ParticleWrap::HasContent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->hasContent()) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getOpacity()) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetLifetime(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getLifetime()) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetAge(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Number::New(isolate, self->getAge()) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::IsAlive(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->isAlive()) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Animate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""seconds"")");
                return;
            }
            double seconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->animate(seconds)) ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=self->getLayer(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mSpriteLayerScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( SpriteLayerWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mSpriteLayerScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setOpacity(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetLifetime(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""value"")");
                return;
            }
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); self->setLifetime(value);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ClearContent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->clearContent();
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RemoveCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removeCollider(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RemovePhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removePhysicsBody(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
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

    void ParticleWrap::RemoveParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removeParticleEmitter(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
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

    void ParticleWrap::Expire(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->expire(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ReadPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&static_cast<PhysicsBody&>(self->physics); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mPhysicsBodyScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsBodyScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetupPhysicsBody(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() >= 1 && !args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""mass"")");
                return;
            }
            double mass = (args.Length()<1) ? 1 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""inertia"")");
                return;
            }
            double inertia = (args.Length()<2) ? 1 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; auto* result=&self->setupPhysicsBody(mass,inertia); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mPhysicsBodyScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( PhysicsBodyWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mPhysicsBodyScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::ReadCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&static_cast<Collider&>(self->collider); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mColliderScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ColliderWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mColliderScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetupCollider(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->setupCollider(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mColliderScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ColliderWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mColliderScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetupParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=&self->setupParticleEmitter(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mParticleEmitterScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ParticleEmitterWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mParticleEmitterScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::GetParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=self->getParticleEmitter(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mParticleEmitterScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ParticleEmitterWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mParticleEmitterScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::FadeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (args.Length()>3)
            {
                if (args.Length() != 3)
                {
                    v8_ThrowArgCountException(isolate, args.Length(), 3);
                    return;
                };
            }
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
                return;
            }
            double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
                return;
            }
            double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
                return;
            }
            double easing = (args.Length()<3) ? static_cast<int>(EasingFuncRef::linearTween) : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (!std::isfinite(easing) || easing < 0 || easing >= NUM_EASING_FUNCTIONS || std::floor(easing)!=easing)
            {
                throw std::invalid_argument("Unknown easing");
            }
            self->fadeTo(opacity,seconds,gEasingFunctions[static_cast<int>(easing)]);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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
#ifndef PDG_NO_GUI

    void ParticleWrap::SetImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,content,Image); self->setImage(*content);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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

    void ParticleWrap::SetDrawing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ParticleWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ParticleWrap>(args.This());
        Particle* self = dynamic_cast<Particle*>(objWrapper->cppPtr_);

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,content,Drawing); self->setDrawing(*content);
            {
                args.GetReturnValue().Set( args.This() ); return;
            };
        }
        catch (const std::exception& error)
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
#endif

}
