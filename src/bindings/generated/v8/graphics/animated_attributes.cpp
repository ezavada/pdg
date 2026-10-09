// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/animated_attributes.cpp
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

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>
#include <cmath>
#include <limits>

namespace pdg
{

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void AnimatedAttributesBase_finalize(JSObjectRef object)
    {
        delete static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(object));
        JSObjectSetPrivate(object, nullptr);
    }
#endif
    static bool s_AnimatedAttributesBase_InNewFromCpp = false;

    void AnimatedAttributesBaseWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = new AnimatedAttributesBaseWrap(args);
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
    v8::Local<v8::Object> AnimatedAttributesBaseWrap::NewFromCpp(v8::Isolate* isolate, AnimatedAttributesBase* cppObj)
    {
        s_AnimatedAttributesBase_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_AnimatedAttributesBase_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_AnimatedAttributesBase_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            cppObj->mAnimatedScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_AnimatedAttributesBase_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> AnimatedAttributesBaseWrap::constructorTpl_;

    void AnimatedAttributesBaseWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
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
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "AnimatedAttributes").ToLocalChecked();
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
        v8::Local<v8::Signature> WithAppearance_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> WithAppearance_Tpl =
            v8::FunctionTemplate::New(isolate, WithAppearance, v8::Local<v8::Value>(), WithAppearance_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "withAppearance").ToLocalChecked(), WithAppearance_Tpl);

        v8::Local<v8::Signature> LineColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineColor_Tpl =
            v8::FunctionTemplate::New(isolate, LineColor, v8::Local<v8::Value>(), LineColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineColor").ToLocalChecked(), LineColor_Tpl);

        v8::Local<v8::Signature> LineThickness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineThickness_Tpl =
            v8::FunctionTemplate::New(isolate, LineThickness, v8::Local<v8::Value>(), LineThickness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineThickness").ToLocalChecked(), LineThickness_Tpl);

        v8::Local<v8::Signature> LineOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, LineOpacity, v8::Local<v8::Value>(), LineOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineOpacity").ToLocalChecked(), LineOpacity_Tpl);

        v8::Local<v8::Signature> SetLineStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLineStyle_Tpl =
            v8::FunctionTemplate::New(isolate, SetLineStyle, v8::Local<v8::Value>(), SetLineStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineStyle").ToLocalChecked(), SetLineStyle_Tpl);

        v8::Local<v8::Signature> FillColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillColor_Tpl =
            v8::FunctionTemplate::New(isolate, FillColor, v8::Local<v8::Value>(), FillColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillColor").ToLocalChecked(), FillColor_Tpl);

        v8::Local<v8::Signature> FillOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, FillOpacity, v8::Local<v8::Value>(), FillOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillOpacity").ToLocalChecked(), FillOpacity_Tpl);

        v8::Local<v8::Signature> FillGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillGradient_Tpl =
            v8::FunctionTemplate::New(isolate, FillGradient, v8::Local<v8::Value>(), FillGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillGradient").ToLocalChecked(), FillGradient_Tpl);

        v8::Local<v8::Signature> FillRadialGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillRadialGradient_Tpl =
            v8::FunctionTemplate::New(isolate, FillRadialGradient, v8::Local<v8::Value>(), FillRadialGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillRadialGradient").ToLocalChecked(), FillRadialGradient_Tpl);

        v8::Local<v8::Signature> RoundedCorners_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RoundedCorners_Tpl =
            v8::FunctionTemplate::New(isolate, RoundedCorners, v8::Local<v8::Value>(), RoundedCorners_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "roundedCorners").ToLocalChecked(), RoundedCorners_Tpl);

        v8::Local<v8::Signature> Translation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Translation_Tpl =
            v8::FunctionTemplate::New(isolate, Translation, v8::Local<v8::Value>(), Translation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "translation").ToLocalChecked(), Translation_Tpl);

        v8::Local<v8::Signature> Rotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Rotation_Tpl =
            v8::FunctionTemplate::New(isolate, Rotation, v8::Local<v8::Value>(), Rotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked(), Rotation_Tpl);

        v8::Local<v8::Signature> Scale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Scale_Tpl =
            v8::FunctionTemplate::New(isolate, Scale, v8::Local<v8::Value>(), Scale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "scale").ToLocalChecked(), Scale_Tpl);

        v8::Local<v8::Signature> Skew_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Skew_Tpl =
            v8::FunctionTemplate::New(isolate, Skew, v8::Local<v8::Value>(), Skew_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "skew").ToLocalChecked(), Skew_Tpl);

        v8::Local<v8::Signature> Transform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Transform_Tpl =
            v8::FunctionTemplate::New(isolate, Transform, v8::Local<v8::Value>(), Transform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "transform").ToLocalChecked(), Transform_Tpl);

        v8::Local<v8::Signature> SetTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTransform_Tpl =
            v8::FunctionTemplate::New(isolate, SetTransform, v8::Local<v8::Value>(), SetTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setTransform").ToLocalChecked(), SetTransform_Tpl);

        v8::Local<v8::Signature> SetBlendMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetBlendMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetBlendMode, v8::Local<v8::Value>(), SetBlendMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blendMode").ToLocalChecked(), SetBlendMode_Tpl);

        v8::Local<v8::Signature> TextSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TextSize_Tpl =
            v8::FunctionTemplate::New(isolate, TextSize, v8::Local<v8::Value>(), TextSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "textSize").ToLocalChecked(), TextSize_Tpl);

        v8::Local<v8::Signature> TextStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TextStyle_Tpl =
            v8::FunctionTemplate::New(isolate, TextStyle, v8::Local<v8::Value>(), TextStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "textStyle").ToLocalChecked(), TextStyle_Tpl);

#ifndef PDG_NO_GUI

        v8::Local<v8::Signature> SetFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFont_Tpl =
            v8::FunctionTemplate::New(isolate, SetFont, v8::Local<v8::Value>(), SetFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "font").ToLocalChecked(), SetFont_Tpl);
#endif

        v8::Local<v8::Signature> Frame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Frame_Tpl =
            v8::FunctionTemplate::New(isolate, Frame, v8::Local<v8::Value>(), Frame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "frame").ToLocalChecked(), Frame_Tpl);

        v8::Local<v8::Signature> SetFitType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFitType_Tpl =
            v8::FunctionTemplate::New(isolate, SetFitType, v8::Local<v8::Value>(), SetFitType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fitType").ToLocalChecked(), SetFitType_Tpl);

        v8::Local<v8::Signature> ClipOverflow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClipOverflow_Tpl =
            v8::FunctionTemplate::New(isolate, ClipOverflow, v8::Local<v8::Value>(), ClipOverflow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clipOverflow").ToLocalChecked(), ClipOverflow_Tpl);

        v8::Local<v8::Signature> Subsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Subsection_Tpl =
            v8::FunctionTemplate::New(isolate, Subsection, v8::Local<v8::Value>(), Subsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "subsection").ToLocalChecked(), Subsection_Tpl);

        v8::Local<v8::Signature> SphereRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SphereRotation_Tpl =
            v8::FunctionTemplate::New(isolate, SphereRotation, v8::Local<v8::Value>(), SphereRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sphereRotation").ToLocalChecked(), SphereRotation_Tpl);

        v8::Local<v8::Signature> PolarOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PolarOffset_Tpl =
            v8::FunctionTemplate::New(isolate, PolarOffset, v8::Local<v8::Value>(), PolarOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "polarOffset").ToLocalChecked(), PolarOffset_Tpl);

        v8::Local<v8::Signature> LightOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LightOffset_Tpl =
            v8::FunctionTemplate::New(isolate, LightOffset, v8::Local<v8::Value>(), LightOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lightOffset").ToLocalChecked(), LightOffset_Tpl);

        v8::Local<v8::Signature> AmbientLight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AmbientLight_Tpl =
            v8::FunctionTemplate::New(isolate, AmbientLight, v8::Local<v8::Value>(), AmbientLight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "ambientLight").ToLocalChecked(), AmbientLight_Tpl);

        v8::Local<v8::Signature> Texture_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Texture_Tpl =
            v8::FunctionTemplate::New(isolate, Texture, v8::Local<v8::Value>(), Texture_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "texture").ToLocalChecked(), Texture_Tpl);

        v8::Local<v8::Signature> GetLineColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineColor, v8::Local<v8::Value>(), GetLineColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineColor").ToLocalChecked(), GetLineColor_Tpl);

        v8::Local<v8::Signature> GetLineThickness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineThickness_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineThickness, v8::Local<v8::Value>(), GetLineThickness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineThickness").ToLocalChecked(), GetLineThickness_Tpl);

        v8::Local<v8::Signature> GetLineOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineOpacity, v8::Local<v8::Value>(), GetLineOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineOpacity").ToLocalChecked(), GetLineOpacity_Tpl);

        v8::Local<v8::Signature> GetLineStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineStyle_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineStyle, v8::Local<v8::Value>(), GetLineStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineStyle").ToLocalChecked(), GetLineStyle_Tpl);

        v8::Local<v8::Signature> GetFillColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFillColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetFillColor, v8::Local<v8::Value>(), GetFillColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFillColor").ToLocalChecked(), GetFillColor_Tpl);

        v8::Local<v8::Signature> GetFillOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFillOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetFillOpacity, v8::Local<v8::Value>(), GetFillOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFillOpacity").ToLocalChecked(), GetFillOpacity_Tpl);

        v8::Local<v8::Signature> GetRoundedCornerRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRoundedCornerRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetRoundedCornerRadius, v8::Local<v8::Value>(), GetRoundedCornerRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRoundedCornerRadius").ToLocalChecked(), GetRoundedCornerRadius_Tpl);

        v8::Local<v8::Signature> GetGradientType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientType_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientType, v8::Local<v8::Value>(), GetGradientType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientType").ToLocalChecked(), GetGradientType_Tpl);

        v8::Local<v8::Signature> GetGradientStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientStart_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientStart, v8::Local<v8::Value>(), GetGradientStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientStart").ToLocalChecked(), GetGradientStart_Tpl);

        v8::Local<v8::Signature> GetGradientEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientEnd_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientEnd, v8::Local<v8::Value>(), GetGradientEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientEnd").ToLocalChecked(), GetGradientEnd_Tpl);

        v8::Local<v8::Signature> GetGradientStartColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientStartColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientStartColor, v8::Local<v8::Value>(), GetGradientStartColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientStartColor").ToLocalChecked(), GetGradientStartColor_Tpl);

        v8::Local<v8::Signature> GetGradientEndColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientEndColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientEndColor, v8::Local<v8::Value>(), GetGradientEndColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientEndColor").ToLocalChecked(), GetGradientEndColor_Tpl);

        v8::Local<v8::Signature> GetRadialGradientCenter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientCenter_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientCenter, v8::Local<v8::Value>(), GetRadialGradientCenter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientCenter").ToLocalChecked(), GetRadialGradientCenter_Tpl);

        v8::Local<v8::Signature> GetRadialGradientRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientRadius, v8::Local<v8::Value>(), GetRadialGradientRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientRadius").ToLocalChecked(), GetRadialGradientRadius_Tpl);

        v8::Local<v8::Signature> GetRadialGradientCenterColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientCenterColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientCenterColor, v8::Local<v8::Value>(), GetRadialGradientCenterColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientCenterColor").ToLocalChecked(), GetRadialGradientCenterColor_Tpl);

        v8::Local<v8::Signature> GetRadialGradientEndColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientEndColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientEndColor, v8::Local<v8::Value>(), GetRadialGradientEndColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientEndColor").ToLocalChecked(), GetRadialGradientEndColor_Tpl);

        v8::Local<v8::Signature> GetTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTransform_Tpl =
            v8::FunctionTemplate::New(isolate, GetTransform, v8::Local<v8::Value>(), GetTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTransform").ToLocalChecked(), GetTransform_Tpl);

        v8::Local<v8::Signature> GetBlendMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBlendMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetBlendMode, v8::Local<v8::Value>(), GetBlendMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBlendMode").ToLocalChecked(), GetBlendMode_Tpl);

        v8::Local<v8::Signature> GetTextSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTextSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetTextSize, v8::Local<v8::Value>(), GetTextSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTextSize").ToLocalChecked(), GetTextSize_Tpl);

        v8::Local<v8::Signature> GetTextStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTextStyle_Tpl =
            v8::FunctionTemplate::New(isolate, GetTextStyle, v8::Local<v8::Value>(), GetTextStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTextStyle").ToLocalChecked(), GetTextStyle_Tpl);

#ifndef PDG_NO_GUI

        v8::Local<v8::Signature> GetFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFont_Tpl =
            v8::FunctionTemplate::New(isolate, GetFont, v8::Local<v8::Value>(), GetFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFont").ToLocalChecked(), GetFont_Tpl);
#endif

        v8::Local<v8::Signature> GetFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrame_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrame, v8::Local<v8::Value>(), GetFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrame").ToLocalChecked(), GetFrame_Tpl);

        v8::Local<v8::Signature> GetFitType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFitType_Tpl =
            v8::FunctionTemplate::New(isolate, GetFitType, v8::Local<v8::Value>(), GetFitType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFitType").ToLocalChecked(), GetFitType_Tpl);

        v8::Local<v8::Signature> GetClipOverflow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetClipOverflow_Tpl =
            v8::FunctionTemplate::New(isolate, GetClipOverflow, v8::Local<v8::Value>(), GetClipOverflow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getClipOverflow").ToLocalChecked(), GetClipOverflow_Tpl);

        v8::Local<v8::Signature> GetSubsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSubsection_Tpl =
            v8::FunctionTemplate::New(isolate, GetSubsection, v8::Local<v8::Value>(), GetSubsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSubsection").ToLocalChecked(), GetSubsection_Tpl);

        v8::Local<v8::Signature> GetSphereRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSphereRotation_Tpl =
            v8::FunctionTemplate::New(isolate, GetSphereRotation, v8::Local<v8::Value>(), GetSphereRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSphereRotation").ToLocalChecked(), GetSphereRotation_Tpl);

        v8::Local<v8::Signature> GetPolarOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPolarOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetPolarOffset, v8::Local<v8::Value>(), GetPolarOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPolarOffset").ToLocalChecked(), GetPolarOffset_Tpl);

        v8::Local<v8::Signature> GetLightOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLightOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetLightOffset, v8::Local<v8::Value>(), GetLightOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLightOffset").ToLocalChecked(), GetLightOffset_Tpl);

        v8::Local<v8::Signature> GetAmbientLight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAmbientLight_Tpl =
            v8::FunctionTemplate::New(isolate, GetAmbientLight, v8::Local<v8::Value>(), GetAmbientLight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAmbientLight").ToLocalChecked(), GetAmbientLight_Tpl);

        v8::Local<v8::Signature> GetTexture_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTexture_Tpl =
            v8::FunctionTemplate::New(isolate, GetTexture, v8::Local<v8::Value>(), GetTexture_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTexture").ToLocalChecked(), GetTexture_Tpl);
        v8::Local<v8::Signature> Animate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Animate_Tpl =
            v8::FunctionTemplate::New(isolate, Animate, v8::Local<v8::Value>(), Animate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "animate").ToLocalChecked(), Animate_Tpl);
        v8::Local<v8::Signature> SetDrawingLayout_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDrawingLayout_Tpl =
            v8::FunctionTemplate::New(isolate, SetDrawingLayout, v8::Local<v8::Value>(), SetDrawingLayout_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "_setDrawingLayout").ToLocalChecked(), SetDrawingLayout_Tpl);
        v8::Local<v8::Signature> ChangeLineColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeLineColor_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeLineColor, v8::Local<v8::Value>(), ChangeLineColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeLineColor").ToLocalChecked(), ChangeLineColor_Tpl);
        v8::Local<v8::Signature> ChangeLineThickness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeLineThickness_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeLineThickness, v8::Local<v8::Value>(), ChangeLineThickness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeLineThickness").ToLocalChecked(), ChangeLineThickness_Tpl);
        v8::Local<v8::Signature> ChangeLineOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeLineOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeLineOpacity, v8::Local<v8::Value>(), ChangeLineOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeLineOpacity").ToLocalChecked(), ChangeLineOpacity_Tpl);
        v8::Local<v8::Signature> ChangeFillColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFillColor_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFillColor, v8::Local<v8::Value>(), ChangeFillColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFillColor").ToLocalChecked(), ChangeFillColor_Tpl);
        v8::Local<v8::Signature> ChangeFillOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFillOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFillOpacity, v8::Local<v8::Value>(), ChangeFillOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFillOpacity").ToLocalChecked(), ChangeFillOpacity_Tpl);
        v8::Local<v8::Signature> ChangeRoundedCorners_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeRoundedCorners_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeRoundedCorners, v8::Local<v8::Value>(), ChangeRoundedCorners_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeRoundedCorners").ToLocalChecked(), ChangeRoundedCorners_Tpl);
        v8::Local<v8::Signature> ChangeTextSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeTextSize_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeTextSize, v8::Local<v8::Value>(), ChangeTextSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeTextSize").ToLocalChecked(), ChangeTextSize_Tpl);
        v8::Local<v8::Signature> ChangeSubsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSubsection_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSubsection, v8::Local<v8::Value>(), ChangeSubsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSubsection").ToLocalChecked(), ChangeSubsection_Tpl);
        v8::Local<v8::Signature> ChangePolarOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangePolarOffset_Tpl =
            v8::FunctionTemplate::New(isolate, ChangePolarOffset, v8::Local<v8::Value>(), ChangePolarOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changePolarOffset").ToLocalChecked(), ChangePolarOffset_Tpl);
        v8::Local<v8::Signature> ChangeLightOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeLightOffset_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeLightOffset, v8::Local<v8::Value>(), ChangeLightOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeLightOffset").ToLocalChecked(), ChangeLightOffset_Tpl);
        v8::Local<v8::Signature> ChangeAmbientLight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeAmbientLight_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeAmbientLight, v8::Local<v8::Value>(), ChangeAmbientLight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeAmbientLight").ToLocalChecked(), ChangeAmbientLight_Tpl);
        v8::Local<v8::Signature> ChangeFillGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFillGradient_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFillGradient, v8::Local<v8::Value>(), ChangeFillGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFillGradient").ToLocalChecked(), ChangeFillGradient_Tpl);
        v8::Local<v8::Signature> ChangeFillRadialGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFillRadialGradient_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFillRadialGradient, v8::Local<v8::Value>(), ChangeFillRadialGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFillRadialGradient").ToLocalChecked(), ChangeFillRadialGradient_Tpl);
        v8::Local<v8::Signature> ChangeSphereRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSphereRotation_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSphereRotation, v8::Local<v8::Value>(), ChangeSphereRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSphereRotation").ToLocalChecked(), ChangeSphereRotation_Tpl);
        v8::Local<v8::Signature> ChangeFrames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFrames_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFrames, v8::Local<v8::Value>(), ChangeFrames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFrames").ToLocalChecked(), ChangeFrames_Tpl);
        v8::Local<v8::Signature> ChangeSkew_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeSkew_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeSkew, v8::Local<v8::Value>(), ChangeSkew_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeSkew").ToLocalChecked(), ChangeSkew_Tpl);
        v8::Local<v8::Signature> ChangeTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeTransform_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeTransform, v8::Local<v8::Value>(), ChangeTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeTransform").ToLocalChecked(), ChangeTransform_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }
    AnimatedAttributesBaseWrap::AnimatedAttributesBaseWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        {
            v8::TryCatch caught(args.GetIsolate());
            cppPtr_ = New_AnimatedAttributesBase(args);
            if (caught.HasCaught()) { caught.ReThrow(); return; }
        }
        if (!cppPtr_ && !s_AnimatedAttributesBase_InNewFromCpp)
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "AnimatedAttributesBase" " instance")));
            };
        }
    }

    AnimatedAttributesBaseWrap::~AnimatedAttributesBaseWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    AnimatedAttributesBase* New_AnimatedAttributesBase(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_AnimatedAttributesBase_InNewFromCpp) return nullptr;
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() > 1)
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "AnimatedAttributes accepts optional Attributes";
                [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::TypeError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return nullptr;
        }
        Attributes* initial = nullptr;
        if (args.Length() == 1 && !args[0]->IsNull() && !args[0]->IsUndefined())
        {
            initial = ExtractAttributes(args[0]);
            if (!initial)
            {
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected Attributes or AnimatedAttributes";
                    [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::TypeError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };
                return nullptr;
            }
        }
        AnimatedAttributesBase* result;
        try { result = initial ? new AnimatedAttributesBase(*initial) : new AnimatedAttributesBase(); }
        catch (const std::exception& error)
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << error.what();
                [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::RangeError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return nullptr;
        }
#ifndef PDG_USING_JAVASCRIPT_CORE
        result->mAnimatedScriptObj.Reset(isolate, args.This());
        result->mAnimatedScriptObj.SetWeak();
#endif
        return result;
    }

    void AnimatedAttributesBaseWrap::PlayScript(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Batch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::EndBatch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Series(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::EndSeries(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::AndAlso(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Stagger(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Mark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::JumpToMark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::When(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ScriptOn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnStarted(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::TriggerEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnScriptFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnMark(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnYoyo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnRepeat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::OnUntilFired(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Otherwise(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::EndWhen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::EndOtherwise(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Until(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Yoyo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Repeat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Diminish(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Increase(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SlowDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SpeedUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::StopIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::RestartIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::PauseIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ResumeIt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::MoveBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeMovementTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeMovementBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeCenterOffsetTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeCenterOffsetBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeSpinTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeSpinBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeGrowingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeGrowingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeStretchingTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeStretchingBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeScaleTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ChangeScaleBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ResizeBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::RotateBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::StopMovement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::PauseSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ResumeSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::CancelSchedule(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::AndThen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::IsSchedulePaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::HasScheduledAnimations(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            self->mAnimatedScriptObj.Reset(isolate, args.This()); self->mAnimatedScriptObj.SetWeak();
            SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
            {
                std::cerr << __func__<<":"<< 83 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
            }
            else if (!args[0]->IsObject())
            {
                std::cerr << __func__<<":"<< 83 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                        std::cout << __func__<<":"<< 83 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                    }
                    else
                    {
                        std::cout << __func__<<":"<< 83 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                    }
                }
                else
                {
                    IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                        std::cout << __func__<<":"<< 83 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
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

    void AnimatedAttributesBaseWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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

    void AnimatedAttributesBaseWrap::WithAppearance(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };

        Attributes* overrides = ExtractAttributes(args[1 -1]);
        if (!overrides)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected Attributes or AnimatedAttributes";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        };
        if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""textOnly"")");
            return;
        }
        bool textOnly = (args.Length()<2) ? false : args[2 -1]->BooleanValue(isolate);;
        Attributes* result = new Attributes(self->withAppearance(*overrides, textOnly));
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mAttributesScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( AttributesWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mAttributesScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void AnimatedAttributesBaseWrap::GetLineColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getLineColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetLineThickness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float thickness = self->getLineThickness();
        { args.GetReturnValue().Set( v8::Number::New(isolate, thickness) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetLineOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getLineOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetLineStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        LineStyle style = self->getLineStyle();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, style) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetFillColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getFillColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetFillOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getFillOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetRoundedCornerRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float radius = self->getRoundedCornerRadius();
        { args.GetReturnValue().Set( v8::Number::New(isolate, radius) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetGradientType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        GradientType type = self->getGradientType();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, type) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetGradientStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point start = const_cast<Point&>(self->getGradientStart());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, start) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetGradientEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point end = const_cast<Point&>(self->getGradientEnd());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, end) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetGradientStartColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getGradientStartColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetGradientEndColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getGradientEndColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetRadialGradientCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point center = const_cast<Point&>(self->getRadialGradientCenter());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, center) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetRadialGradientRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float radius = self->getRadialGradientRadius();
        { args.GetReturnValue().Set( v8::Number::New(isolate, radius) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetRadialGradientCenterColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getRadialGradientCenterColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetRadialGradientEndColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getRadialGradientEndColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        const glm::mat3& matrix = self->getTransform();
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                JSObjectSetPropertyAtIndex(ctx, result, (unsigned)index,
                    JSValueMakeNumber(ctx, matrix[i][j]), exception);
            }
        }
        { args.GetReturnValue().Set( result ); return; };
#else
        v8::Local<v8::Array> result = v8::Array::New(isolate, 9);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                (void)result->Set(context, index, v8::Number::New(isolate, matrix[i][j]));
            }
        }
        args.GetReturnValue().Set(result);
#endif
    }

    void AnimatedAttributesBaseWrap::GetBlendMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        BlendMode blendMode = self->getBlendMode();
        { args.GetReturnValue().Set( v8::Number::New(isolate, static_cast<int>(blendMode)) ); return; };
    }

    void AnimatedAttributesBaseWrap::LineColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->lineColor(color);
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

    void AnimatedAttributesBaseWrap::LineThickness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""thickness"")");
                return;
            }
            double thickness = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineThickness(thickness);
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

    void AnimatedAttributesBaseWrap::LineOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
                return;
            }
            double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineOpacity(opacity);
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

    void AnimatedAttributesBaseWrap::SetLineStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""lineStyle"")");
                return;
            }
            double lineStyle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineStyle(static_cast<LineStyle>(lineStyle));
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

    void AnimatedAttributesBaseWrap::FillColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->fillColor(color);
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

    void AnimatedAttributesBaseWrap::FillOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
                return;
            }
            double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->fillOpacity(opacity);
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

    void AnimatedAttributesBaseWrap::FillGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            };
            pdg::Point start;
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
            };
            pdg::Color startColor;
            auto startColor_isColor = v8_ValueIsColor(isolate, args[2 -1], startColor);
            if (!startColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*startColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
                return;
            };
            pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[3 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                return;
            };
            pdg::Color endColor;
            auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
            if (!endColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*endColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
                return;
            };
            self->fillGradient(start, startColor, end, endColor);
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

    void AnimatedAttributesBaseWrap::FillRadialGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            };
            pdg::Point center;
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
            pdg::Color centerColor;
            auto centerColor_isColor = v8_ValueIsColor(isolate, args[2 -1], centerColor);
            if (!centerColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*centerColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
                return;
            };
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
                return;
            }
            double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            pdg::Color endColor;
            auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
            if (!endColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*endColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
                return;
            };
            self->fillRadialGradient(center, centerColor, radius, endColor);
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

    void AnimatedAttributesBaseWrap::RoundedCorners(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""radius"")");
                return;
            }
            double radius = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->roundedCorners(radius);
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

    void AnimatedAttributesBaseWrap::Translation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
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
            self->translation(offset);
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

    void AnimatedAttributesBaseWrap::Rotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
            pdg::Point center;
            if (args.Length() < 2)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[2 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            };
            self->rotation(radians, center);
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

    void AnimatedAttributesBaseWrap::Scale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""xFactor"")");
                return;
            }
            double xFactor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""yFactor"")");
                return;
            }
            double yFactor = (args.Length()<2) ? xFactor : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            pdg::Point center;
            if (args.Length() < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[3 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            if (args.Length() > 1 && !args[1]->IsUndefined())
            {
                self->scale(xFactor, yFactor, center);
            }
            else
            {
                self->scale(xFactor, center);
            }
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

    void AnimatedAttributesBaseWrap::Skew(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""xSkew"")");
                return;
            }
            double xSkew = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""ySkew"")");
                return;
            }
            double ySkew = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            pdg::Point center;
            if (args.Length() < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[3 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            self->skew(xSkew, ySkew, center);
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

    void AnimatedAttributesBaseWrap::Transform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, args[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, args[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception)
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!args[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(args[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element))
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->transform(matrix);
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

    void AnimatedAttributesBaseWrap::SetTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, args[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, args[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception)
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!args[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(args[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element))
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->setTransform(matrix);
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

    void AnimatedAttributesBaseWrap::SetBlendMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""blendMode"")");
                return;
            }
            double blendMode = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->blendMode(static_cast<BlendMode>(blendMode));
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

    void AnimatedAttributesBaseWrap::TextSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
                return;
            }
            double size = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->textSize(size);
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

    void AnimatedAttributesBaseWrap::TextStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""style"")");
                return;
            }
            double style = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->textStyle(static_cast<uint32>(style));
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
#ifndef PDG_NO_GUI

    void AnimatedAttributesBaseWrap::SetFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            Font* font = 0;
            if (args.Length() >= 1)
            {
                if (!args[1 -1]->IsObject())
                {
                    v8_ThrowArgTypeException(isolate, 1, "an object of type ""Font"" (""font"")");
                    return;
                }
                else
                {
                    v8::Local<v8::Object> font_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                    FontWrap* font__ = jswrap::ObjectWrap::Unwrap<FontWrap>(font_);
                    font = font__->getCppObject();
                }
            };
            self->font(font);
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
#endif

    void AnimatedAttributesBaseWrap::Frame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""frame"")");
                return;
            }
            double frame = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->frame(frame);
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

    void AnimatedAttributesBaseWrap::SetFitType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""fit"")");
                return;
            }
            double fit = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->fitType(static_cast<FitType>(fit));
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

    void AnimatedAttributesBaseWrap::ClipOverflow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""clip"")");
                return;
            }
            bool clip = args[1 -1]->BooleanValue(isolate);
            self->clipOverflow(clip);
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

    void AnimatedAttributesBaseWrap::Subsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Rect section;
            auto section_isRect = v8_ValueIsRect(isolate, args[1 -1], section);
            if (!section_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*section_isRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
                return;
            };
            self->subsection(section);
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

    void AnimatedAttributesBaseWrap::SphereRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

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
                v8_ThrowArgTypeException(isolate, 1, "a number (""rotation"")");
                return;
            }
            double rotation = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->sphereRotation(rotation);
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

    void AnimatedAttributesBaseWrap::PolarOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
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
            self->polarOffset(offset);
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

    void AnimatedAttributesBaseWrap::LightOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
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
            self->lightOffset(offset);
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

    void AnimatedAttributesBaseWrap::AmbientLight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->ambientLight(color);
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

    void AnimatedAttributesBaseWrap::Texture(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, texture, Image);
            self->texture(texture);
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

    void AnimatedAttributesBaseWrap::GetTextSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float size = self->getTextSize();
        { args.GetReturnValue().Set( v8::Number::New(isolate, size) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetTextStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        uint32 style = self->getTextStyle();
        { args.GetReturnValue().Set( v8::Number::New(isolate, style) ); return; };
    }
#ifndef PDG_NO_GUI

    void AnimatedAttributesBaseWrap::GetFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Font* font = self->getFont();
        if (!font) { args.GetReturnValue().SetNull(); return; };
        if (font->mFontScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( FontWrap::NewFromCpp(isolate, font) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, font->mFontScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }
#endif

    void AnimatedAttributesBaseWrap::GetFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int frame = self->getFrame();
        { args.GetReturnValue().Set( v8::Number::New(isolate, frame) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetFitType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        FitType fit = self->getFitType();
        { args.GetReturnValue().Set( v8::Number::New(isolate, static_cast<int>(fit)) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetClipOverflow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool clip = self->getClipOverflow();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, clip) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetSubsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect section = self->getSubsection();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, section) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetSphereRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float rotation = self->getSphereRotation();
        { args.GetReturnValue().Set( v8::Number::New(isolate, rotation) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetPolarOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Offset offset = const_cast<Offset&>(self->getPolarOffset());
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetLightOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Offset offset = const_cast<Offset&>(self->getLightOffset());
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetAmbientLight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getAmbientLight());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AnimatedAttributesBaseWrap::GetTexture(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Image* texture = self->getTexture();
        if (!texture) { args.GetReturnValue().SetNull(); return; };
        if (texture->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, texture) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, texture->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void AnimatedAttributesBaseWrap::SetDrawingLayout(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""enabled"")");
            return;
        }
        bool enabled = args[1 -1]->BooleanValue(isolate);
        self->setDrawingLayout(enabled);
        args.GetReturnValue().SetUndefined();
    }

    void AnimatedAttributesBaseWrap::Animate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""deltaSeconds"")");
            return;
        }
        double deltaSeconds = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        try
        {
            {
                args.GetReturnValue().Set( v8::Boolean::New(isolate, self->animate(deltaSeconds)) ); return;
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

    void AnimatedAttributesBaseWrap::ChangeLineColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Color target;
        auto target_isColor = v8_ValueIsColor(isolate, args[1 -1], target);
        if (!target_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isColor)
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeLineColor(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeLineThickness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""target"")");
            return;
        }
        double target = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeLineThickness(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeLineOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""target"")");
            return;
        }
        double target = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeLineOpacity(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeFillColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Color target;
        auto target_isColor = v8_ValueIsColor(isolate, args[1 -1], target);
        if (!target_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isColor)
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeFillColor(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeFillOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""target"")");
            return;
        }
        double target = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeFillOpacity(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeRoundedCorners(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""target"")");
            return;
        }
        double target = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeRoundedCorners(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeTextSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""target"")");
            return;
        }
        double target = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeTextSize(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeSubsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Rect target;
        auto target_isRect = v8_ValueIsRect(isolate, args[1 -1], target);
        if (!target_isRect.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isRect)
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeSubsection(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangePolarOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Offset target;
        auto target_isOffset = v8_ValueIsOffset(isolate, args[1 -1], target);
        if (!target_isOffset.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isOffset)
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changePolarOffset(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeLightOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Offset target;
        auto target_isOffset = v8_ValueIsOffset(isolate, args[1 -1], target);
        if (!target_isOffset.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isOffset)
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeLightOffset(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeAmbientLight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        pdg::Color target;
        auto target_isColor = v8_ValueIsColor(isolate, args[1 -1], target);
        if (!target_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*target_isColor)
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeAmbientLight(target, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeFillGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 5)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 5, true);
            return;
        };
        pdg::Point start;
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
        };
        pdg::Color startColor;
        auto startColor_isColor = v8_ValueIsColor(isolate, args[2 -1], startColor);
        if (!startColor_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*startColor_isColor)
        {
            v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
            return;
        };
        pdg::Point end;
        auto end_isPoint = v8_ValueIsPoint(isolate, args[3 -1], end);
        if (!end_isPoint.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*end_isPoint)
        {
            v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
            return;
        };
        pdg::Color endColor;
        auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
        if (!endColor_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*endColor_isColor)
        {
            v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
            return;
        };
        if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""seconds"")");
            return;
        }
        double seconds = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 6 && !args[6 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 6, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<6) ? 0 : args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeFillGradient(start, startColor, end, endColor, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeFillRadialGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 5)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 5, true);
            return;
        };
        pdg::Point center;
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
        pdg::Color centerColor;
        auto centerColor_isColor = v8_ValueIsColor(isolate, args[2 -1], centerColor);
        if (!centerColor_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*centerColor_isColor)
        {
            v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
            return;
        };
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
            return;
        }
        double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        pdg::Color endColor;
        auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
        if (!endColor_isColor.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*endColor_isColor)
        {
            v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
            return;
        };
        if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""seconds"")");
            return;
        }
        double seconds = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 6 && !args[6 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 6, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<6) ? 0 : args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeFillRadialGradient(center, centerColor, radius, endColor, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeSphereRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
            return;
        }
        double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue ||
            directionValue < std::numeric_limits<int>::min() || directionValue > std::numeric_limits<int>::max())
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
        try
        {
            self->changeSphereRotation(radians, seconds, gEasingFunctions[easing], direction);
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

    void AnimatedAttributesBaseWrap::ChangeFrames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""firstValue"")");
            return;
        }
        double firstValue = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(firstValue) || std::floor(firstValue) != firstValue ||
            firstValue < std::numeric_limits<int>::min() || firstValue > std::numeric_limits<int>::max())
        {
            std::ostringstream excpt_;
            excpt_ << "Expected an integer frame index";
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
        const int first = static_cast<int>(firstValue);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""lastValue"")");
            return;
        }
        double lastValue = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!std::isfinite(lastValue) || std::floor(lastValue) != lastValue ||
            lastValue < std::numeric_limits<int>::min() || lastValue > std::numeric_limits<int>::max())
        {
            std::ostringstream excpt_;
            excpt_ << "Expected an integer frame index";
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
        const int last = static_cast<int>(lastValue);
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""seconds"")");
            return;
        }
        double seconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<4) ? 0 : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeFrames(first, last, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeSkew(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
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
            v8_ThrowArgTypeException(isolate, 3, "a number (""seconds"")");
            return;
        }
        double seconds = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<4) ? 0 : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeSkew(x, y, seconds, gEasingFunctions[easing]);
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

    void AnimatedAttributesBaseWrap::ChangeTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AnimatedAttributesBaseWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedAttributesBaseWrap>(args.This());
        AnimatedAttributesBase* self = dynamic_cast<AnimatedAttributesBase*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };

#ifdef PDG_USING_JAVASCRIPT_CORE
        if (!JSValueIsArray(ctx, args[0]))
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
        }

        JSObjectRef matrixArray = JSValueToObject(ctx, args[0], exception);
        JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
        JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
        JSStringRelease(lengthName);
        if (*exception)
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
        if (*exception)
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (matrixLength != 9)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
        }

        glm::mat3 matrix;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                if (*exception)
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!JSValueIsNumber(ctx, element))
                {
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
                }
                matrix[i][j] = JSValueToNumber(ctx, element, exception);
            }
        }
#else
        if (!args[0]->IsArray())
        {
            v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
            return;
        }

        v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(args[0]);
        if (matrixArray->Length() != 9)
        {
            v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
            return;
        }

        glm::mat3 matrix;
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                v8::Local<v8::Value> element;
                if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element))
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!element->IsNumber())
                {
                    v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                    return;
                }
                matrix[i][j] = element.As<v8::Number>()->Value();
            }
        }
#endif

        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""seconds"")");
            return;
        }
        double seconds = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easingValue"")");
            return;
        }
        double easingValue = (args.Length()<3) ? 0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue)
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
        if (!gEasingFunctions[easing])
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
        try
        {
            self->changeTransform(matrix, seconds, gEasingFunctions[easing]);
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

}
