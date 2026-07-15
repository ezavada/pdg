// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_constraint.cpp
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
#include "physics_bindings.h"

#include "internals.h"
#include "pdg-lib.h"

#include <sstream>
#include <cmath>
#include <cstdlib>

namespace pdg
{

    static bool s_cpConstraint_InNewFromCpp = false;

    void cpConstraintWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = new cpConstraintWrap(args);
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
    v8::Local<v8::Object> cpConstraintWrap::NewFromCpp(v8::Isolate* isolate, cpConstraint* cppObj)
    {
        s_cpConstraint_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_cpConstraint_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_cpConstraint_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(instance);

        ;
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_cpConstraint_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> cpConstraintWrap::constructorTpl_;

    void cpConstraintWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(v8::String::NewFromUtf8(isolate, "CpConstraint").ToLocalChecked());
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetType_Tpl =
            v8::FunctionTemplate::New(isolate, GetType, v8::Local<v8::Value>(), GetType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Type").ToLocalChecked(), GetType_Tpl);
        v8::Local<v8::Signature> ActivateBodies_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ActivateBodies_Tpl =
            v8::FunctionTemplate::New(isolate, ActivateBodies, v8::Local<v8::Value>(), ActivateBodies_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "activateBodies").ToLocalChecked(), ActivateBodies_Tpl);
        v8::Local<v8::Signature> GetImpulse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImpulse_Tpl =
            v8::FunctionTemplate::New(isolate, GetImpulse, v8::Local<v8::Value>(), GetImpulse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Impulse").ToLocalChecked(), GetImpulse_Tpl);
        v8::Local<v8::Signature> GetMaxForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxForce_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxForce, v8::Local<v8::Value>(), GetMaxForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MaxForce").ToLocalChecked(), GetMaxForce_Tpl);
        v8::Local<v8::Signature> SetMaxForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMaxForce_Tpl =
            v8::FunctionTemplate::New(isolate, SetMaxForce, v8::Local<v8::Value>(), SetMaxForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MaxForce").ToLocalChecked(), SetMaxForce_Tpl);
        v8::Local<v8::Signature> GetErrorBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetErrorBias_Tpl =
            v8::FunctionTemplate::New(isolate, GetErrorBias, v8::Local<v8::Value>(), GetErrorBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ErrorBias").ToLocalChecked(), GetErrorBias_Tpl);
        v8::Local<v8::Signature> SetErrorBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetErrorBias_Tpl =
            v8::FunctionTemplate::New(isolate, SetErrorBias, v8::Local<v8::Value>(), SetErrorBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""ErrorBias").ToLocalChecked(), SetErrorBias_Tpl);
        v8::Local<v8::Signature> GetMaxBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxBias_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxBias, v8::Local<v8::Value>(), GetMaxBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MaxBias").ToLocalChecked(), GetMaxBias_Tpl);
        v8::Local<v8::Signature> SetMaxBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMaxBias_Tpl =
            v8::FunctionTemplate::New(isolate, SetMaxBias, v8::Local<v8::Value>(), SetMaxBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MaxBias").ToLocalChecked(), SetMaxBias_Tpl);
        v8::Local<v8::Signature> GetSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSprite_Tpl =
            v8::FunctionTemplate::New(isolate, GetSprite, v8::Local<v8::Value>(), GetSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Sprite").ToLocalChecked(), GetSprite_Tpl);
        v8::Local<v8::Signature> GetOtherSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOtherSprite_Tpl =
            v8::FunctionTemplate::New(isolate, GetOtherSprite, v8::Local<v8::Value>(), GetOtherSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""OtherSprite").ToLocalChecked(), GetOtherSprite_Tpl);
        v8::Local<v8::Signature> GetAnchor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnchor_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnchor, v8::Local<v8::Value>(), GetAnchor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Anchor").ToLocalChecked(), GetAnchor_Tpl);
        v8::Local<v8::Signature> SetAnchor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAnchor_Tpl =
            v8::FunctionTemplate::New(isolate, SetAnchor, v8::Local<v8::Value>(), SetAnchor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Anchor").ToLocalChecked(), SetAnchor_Tpl);
        v8::Local<v8::Signature> GetOtherAnchor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOtherAnchor_Tpl =
            v8::FunctionTemplate::New(isolate, GetOtherAnchor, v8::Local<v8::Value>(), GetOtherAnchor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""OtherAnchor").ToLocalChecked(), GetOtherAnchor_Tpl);
        v8::Local<v8::Signature> SetOtherAnchor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOtherAnchor_Tpl =
            v8::FunctionTemplate::New(isolate, SetOtherAnchor, v8::Local<v8::Value>(), SetOtherAnchor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""OtherAnchor").ToLocalChecked(), SetOtherAnchor_Tpl);
        v8::Local<v8::Signature> GetPinDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPinDist_Tpl =
            v8::FunctionTemplate::New(isolate, GetPinDist, v8::Local<v8::Value>(), GetPinDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""PinDist").ToLocalChecked(), GetPinDist_Tpl);
        v8::Local<v8::Signature> SetPinDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPinDist_Tpl =
            v8::FunctionTemplate::New(isolate, SetPinDist, v8::Local<v8::Value>(), SetPinDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""PinDist").ToLocalChecked(), SetPinDist_Tpl);
        v8::Local<v8::Signature> GetSpringStiffness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpringStiffness_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpringStiffness, v8::Local<v8::Value>(), GetSpringStiffness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SpringStiffness").ToLocalChecked(), GetSpringStiffness_Tpl);
        v8::Local<v8::Signature> SetSpringStiffness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpringStiffness_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpringStiffness, v8::Local<v8::Value>(), SetSpringStiffness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SpringStiffness").ToLocalChecked(), SetSpringStiffness_Tpl);
        v8::Local<v8::Signature> GetSpringDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpringDamping_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpringDamping, v8::Local<v8::Value>(), GetSpringDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SpringDamping").ToLocalChecked(), GetSpringDamping_Tpl);
        v8::Local<v8::Signature> SetSpringDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpringDamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpringDamping, v8::Local<v8::Value>(), SetSpringDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SpringDamping").ToLocalChecked(), SetSpringDamping_Tpl);
        v8::Local<v8::Signature> GetSlideMinDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSlideMinDist_Tpl =
            v8::FunctionTemplate::New(isolate, GetSlideMinDist, v8::Local<v8::Value>(), GetSlideMinDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SlideMinDist").ToLocalChecked(), GetSlideMinDist_Tpl);
        v8::Local<v8::Signature> SetSlideMinDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSlideMinDist_Tpl =
            v8::FunctionTemplate::New(isolate, SetSlideMinDist, v8::Local<v8::Value>(), SetSlideMinDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SlideMinDist").ToLocalChecked(), SetSlideMinDist_Tpl);
        v8::Local<v8::Signature> GetSlideMaxDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSlideMaxDist_Tpl =
            v8::FunctionTemplate::New(isolate, GetSlideMaxDist, v8::Local<v8::Value>(), GetSlideMaxDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SlideMaxDist").ToLocalChecked(), GetSlideMaxDist_Tpl);
        v8::Local<v8::Signature> SetSlideMaxDist_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSlideMaxDist_Tpl =
            v8::FunctionTemplate::New(isolate, SetSlideMaxDist, v8::Local<v8::Value>(), SetSlideMaxDist_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SlideMaxDist").ToLocalChecked(), SetSlideMaxDist_Tpl);
        v8::Local<v8::Signature> GetGrooveStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGrooveStart_Tpl =
            v8::FunctionTemplate::New(isolate, GetGrooveStart, v8::Local<v8::Value>(), GetGrooveStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""GrooveStart").ToLocalChecked(), GetGrooveStart_Tpl);
        v8::Local<v8::Signature> SetGrooveStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGrooveStart_Tpl =
            v8::FunctionTemplate::New(isolate, SetGrooveStart, v8::Local<v8::Value>(), SetGrooveStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""GrooveStart").ToLocalChecked(), SetGrooveStart_Tpl);
        v8::Local<v8::Signature> GetGrooveEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGrooveEnd_Tpl =
            v8::FunctionTemplate::New(isolate, GetGrooveEnd, v8::Local<v8::Value>(), GetGrooveEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""GrooveEnd").ToLocalChecked(), GetGrooveEnd_Tpl);
        v8::Local<v8::Signature> SetGrooveEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGrooveEnd_Tpl =
            v8::FunctionTemplate::New(isolate, SetGrooveEnd, v8::Local<v8::Value>(), SetGrooveEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""GrooveEnd").ToLocalChecked(), SetGrooveEnd_Tpl);
        v8::Local<v8::Signature> GetSpringRestLength_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpringRestLength_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpringRestLength, v8::Local<v8::Value>(), GetSpringRestLength_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SpringRestLength").ToLocalChecked(), GetSpringRestLength_Tpl);
        v8::Local<v8::Signature> SetSpringRestLength_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpringRestLength_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpringRestLength, v8::Local<v8::Value>(), SetSpringRestLength_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SpringRestLength").ToLocalChecked(), SetSpringRestLength_Tpl);
        v8::Local<v8::Signature> GetRotarySpringRestAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotarySpringRestAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotarySpringRestAngle, v8::Local<v8::Value>(), GetRotarySpringRestAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""RotarySpringRestAngle").ToLocalChecked(), GetRotarySpringRestAngle_Tpl);
        v8::Local<v8::Signature> SetRotarySpringRestAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRotarySpringRestAngle_Tpl =
            v8::FunctionTemplate::New(isolate, SetRotarySpringRestAngle, v8::Local<v8::Value>(), SetRotarySpringRestAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""RotarySpringRestAngle").ToLocalChecked(), SetRotarySpringRestAngle_Tpl);
        v8::Local<v8::Signature> GetMinAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMinAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetMinAngle, v8::Local<v8::Value>(), GetMinAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MinAngle").ToLocalChecked(), GetMinAngle_Tpl);
        v8::Local<v8::Signature> SetMinAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMinAngle_Tpl =
            v8::FunctionTemplate::New(isolate, SetMinAngle, v8::Local<v8::Value>(), SetMinAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MinAngle").ToLocalChecked(), SetMinAngle_Tpl);
        v8::Local<v8::Signature> GetMaxAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxAngle, v8::Local<v8::Value>(), GetMaxAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MaxAngle").ToLocalChecked(), GetMaxAngle_Tpl);
        v8::Local<v8::Signature> SetMaxAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMaxAngle_Tpl =
            v8::FunctionTemplate::New(isolate, SetMaxAngle, v8::Local<v8::Value>(), SetMaxAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MaxAngle").ToLocalChecked(), SetMaxAngle_Tpl);
        v8::Local<v8::Signature> GetRatchetAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRatchetAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetRatchetAngle, v8::Local<v8::Value>(), GetRatchetAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""RatchetAngle").ToLocalChecked(), GetRatchetAngle_Tpl);
        v8::Local<v8::Signature> SetRatchetAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRatchetAngle_Tpl =
            v8::FunctionTemplate::New(isolate, SetRatchetAngle, v8::Local<v8::Value>(), SetRatchetAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""RatchetAngle").ToLocalChecked(), SetRatchetAngle_Tpl);
        v8::Local<v8::Signature> GetRatchetPhase_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRatchetPhase_Tpl =
            v8::FunctionTemplate::New(isolate, GetRatchetPhase, v8::Local<v8::Value>(), GetRatchetPhase_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""RatchetPhase").ToLocalChecked(), GetRatchetPhase_Tpl);
        v8::Local<v8::Signature> SetRatchetPhase_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRatchetPhase_Tpl =
            v8::FunctionTemplate::New(isolate, SetRatchetPhase, v8::Local<v8::Value>(), SetRatchetPhase_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""RatchetPhase").ToLocalChecked(), SetRatchetPhase_Tpl);
        v8::Local<v8::Signature> GetRatchetInterval_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRatchetInterval_Tpl =
            v8::FunctionTemplate::New(isolate, GetRatchetInterval, v8::Local<v8::Value>(), GetRatchetInterval_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""RatchetInterval").ToLocalChecked(), GetRatchetInterval_Tpl);
        v8::Local<v8::Signature> SetRatchetInterval_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRatchetInterval_Tpl =
            v8::FunctionTemplate::New(isolate, SetRatchetInterval, v8::Local<v8::Value>(), SetRatchetInterval_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""RatchetInterval").ToLocalChecked(), SetRatchetInterval_Tpl);
        v8::Local<v8::Signature> GetGearRatio_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGearRatio_Tpl =
            v8::FunctionTemplate::New(isolate, GetGearRatio, v8::Local<v8::Value>(), GetGearRatio_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""GearRatio").ToLocalChecked(), GetGearRatio_Tpl);
        v8::Local<v8::Signature> SetGearRatio_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGearRatio_Tpl =
            v8::FunctionTemplate::New(isolate, SetGearRatio, v8::Local<v8::Value>(), SetGearRatio_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""GearRatio").ToLocalChecked(), SetGearRatio_Tpl);
        v8::Local<v8::Signature> GetGearInitialAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGearInitialAngle_Tpl =
            v8::FunctionTemplate::New(isolate, GetGearInitialAngle, v8::Local<v8::Value>(), GetGearInitialAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""GearInitialAngle").ToLocalChecked(), GetGearInitialAngle_Tpl);
        v8::Local<v8::Signature> SetGearInitialAngle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGearInitialAngle_Tpl =
            v8::FunctionTemplate::New(isolate, SetGearInitialAngle, v8::Local<v8::Value>(), SetGearInitialAngle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""GearInitialAngle").ToLocalChecked(), SetGearInitialAngle_Tpl);
        v8::Local<v8::Signature> GetMotorSpinRate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMotorSpinRate_Tpl =
            v8::FunctionTemplate::New(isolate, GetMotorSpinRate, v8::Local<v8::Value>(), GetMotorSpinRate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MotorSpinRate").ToLocalChecked(), GetMotorSpinRate_Tpl);
        v8::Local<v8::Signature> SetMotorSpinRate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMotorSpinRate_Tpl =
            v8::FunctionTemplate::New(isolate, SetMotorSpinRate, v8::Local<v8::Value>(), SetMotorSpinRate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MotorSpinRate").ToLocalChecked(), SetMotorSpinRate_Tpl);
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "CpConstraint").ToLocalChecked(), t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();

    }

    void cpConstraintWrap::GetType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        const char* theType = (const char*)cpConstraintGetUserData(self);
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, theType).ToLocalChecked() ); return; };
    };

    void cpConstraintWrap::GetImpulse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        double theImpulse = cpConstraintGetImpulse(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theImpulse) ); return; };
    }

    void cpConstraintWrap::GetMaxForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        double theMaxForce = cpConstraintGetMaxForce(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMaxForce) ); return; };
    }

    void cpConstraintWrap::SetMaxForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inMaxForce)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMaxForce"")");
        double theMaxForce = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpConstraintSetMaxForce(self, theMaxForce);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetErrorBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        double theErrorBias = cpConstraintGetErrorBias(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theErrorBias) ); return; };
    }

    void cpConstraintWrap::SetErrorBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inErrorBias)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theErrorBias"")");
        double theErrorBias = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpConstraintSetErrorBias(self, theErrorBias);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetMaxBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        double theMaxBias = cpConstraintGetMaxBias(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMaxBias) ); return; };
    }

    void cpConstraintWrap::SetMaxBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inMaxBias)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMaxBias"")");
        double theMaxBias = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpConstraintSetMaxBias(self, theMaxBias);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::ActivateBodies(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);
        cpConstraintActivateBodies(self);
        args.GetReturnValue().SetUndefined();
    }

    void cpConstraintWrap::GetSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);
        cpBody* body = cpConstraintGetBodyA(self);
        Sprite* sprite = (Sprite*) cpBodyGetUserData(body);
        if (!sprite) args.GetReturnValue().SetNull();
        if (sprite->mSpriteScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( SpriteWrap::NewFromCpp(isolate, sprite) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, sprite->mSpriteScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void cpConstraintWrap::GetOtherSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);
        ;
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);
        cpBody* body = cpConstraintGetBodyB(self);
        Sprite* otherSprite = (Sprite*) cpBodyGetUserData(body);
        if (!otherSprite) args.GetReturnValue().SetNull();
        if (otherSprite->mSpriteScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( SpriteWrap::NewFromCpp(isolate, otherSprite) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, otherSprite->mSpriteScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void cpConstraintWrap::GetAnchor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        cpVect anchor;
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            anchor = cpPinJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            anchor = cpSlideJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            anchor = cpPivotJointGetAnchorA(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            anchor = cpDampedSpringGetAnchorA(self);
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
        pdg::Offset theAnchor(anchor.x, anchor.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theAnchor) ); return; };
    }

    void cpConstraintWrap::SetAnchor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "([object Offset] inAnchor)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
        pdg::Offset theAnchor = v8_ValueToOffset(isolate, args[1 -1]);

        cpVect anchor = cpv(theAnchor.x, theAnchor.y);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            cpPinJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            cpSlideJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            cpPivotJointSetAnchorA(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetAnchorA(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setAnchor() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetOtherAnchor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        cpVect anchor;
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            anchor = cpPinJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            anchor = cpSlideJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            anchor = cpPivotJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") == 0)
        {
            anchor = cpGrooveJointGetAnchorB(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            anchor = cpDampedSpringGetAnchorB(self);
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
        pdg::Offset theOtherAnchor(anchor.x, anchor.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theOtherAnchor) ); return; };
    }

    void cpConstraintWrap::SetOtherAnchor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "([object Offset] inOtherAnchor)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
        pdg::Offset theOtherAnchor = v8_ValueToOffset(isolate, args[1 -1]);

        cpVect anchor = cpv(theOtherAnchor.x, theOtherAnchor.y);
        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") == 0)
        {
            cpPinJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") == 0)
        {
            cpSlideJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "PivotJoint") == 0)
        {
            cpPivotJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") == 0)
        {
            cpGrooveJointSetAnchorB(self, anchor);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetAnchorB(self, anchor);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setOtherAnchor() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetPinDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat thePinDist = cpPinJointGetDist(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, thePinDist) ); return; };
    }

    void cpConstraintWrap::SetPinDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inPinDist)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""thePinDist"")");
        double thePinDist = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "PinJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "PinDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpPinJointSetDist(self, thePinDist);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetSlideMinDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theSlideMinDist = cpSlideJointGetMin(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSlideMinDist) ); return; };
    }

    void cpConstraintWrap::SetSlideMinDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inSlideMinDist)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSlideMinDist"")");
        double theSlideMinDist = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SlideMinDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpSlideJointSetMin(self, theSlideMinDist);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetSlideMaxDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theSlideMaxDist = cpSlideJointGetMax(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSlideMaxDist) ); return; };
    }

    void cpConstraintWrap::SetSlideMaxDist(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inSlideMaxDist)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSlideMaxDist"")");
        double theSlideMaxDist = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "SlideJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SlideMaxDist" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpSlideJointSetMax(self, theSlideMaxDist);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetGrooveStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpVect v = cpGrooveJointGetGrooveA(self);
        pdg::Offset theGrooveStart(v.x, v.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theGrooveStart) ); return; };
    }

    void cpConstraintWrap::SetGrooveStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "([object Offset] inGrooveStart)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
        pdg::Offset theGrooveStart = v8_ValueToOffset(isolate, args[1 -1]);

        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GrooveStart" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpGrooveJointSetGrooveA(self, cpv(theGrooveStart.x, theGrooveStart.y));
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetGrooveEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpVect v = cpGrooveJointGetGrooveB(self);
        pdg::Offset theGrooveEnd(v.x, v.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theGrooveEnd) ); return; };
    }

    void cpConstraintWrap::SetGrooveEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "([object Offset] inGrooveEnd)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
        pdg::Offset theGrooveEnd = v8_ValueToOffset(isolate, args[1 -1]);

        if (strcmp((const char*)cpConstraintGetUserData(self), "GrooveJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GrooveEnd" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpGrooveJointSetGrooveB(self, cpv(theGrooveEnd.x, theGrooveEnd.y));
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetSpringRestLength(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theSpringRestLength = cpDampedSpringGetRestLength(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpringRestLength) ); return; };
    }

    void cpConstraintWrap::SetSpringRestLength(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inSpringRestLength)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpringRestLength"")");
        double theSpringRestLength = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "SpringRestLength" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpDampedSpringSetRestLength(self, theSpringRestLength);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetRotarySpringRestAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theRotarySpringRestAngle = cpDampedRotarySpringGetRestAngle(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRotarySpringRestAngle) ); return; };
    }

    void cpConstraintWrap::SetRotarySpringRestAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inRotarySpringRestAngle)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theRotarySpringRestAngle"")");
        double theRotarySpringRestAngle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RotarySpringRestAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpDampedRotarySpringSetRestAngle(self, theRotarySpringRestAngle);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetMinAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theMinAngle = cpRotaryLimitJointGetMin(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMinAngle) ); return; };
    }

    void cpConstraintWrap::SetMinAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inMinAngle)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMinAngle"")");
        double theMinAngle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MinAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpRotaryLimitJointSetMin(self, theMinAngle);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetMaxAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theMaxAngle = cpRotaryLimitJointGetMax(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMaxAngle) ); return; };
    }

    void cpConstraintWrap::SetMaxAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inMaxAngle)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMaxAngle"")");
        double theMaxAngle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "RotaryLimit") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MaxAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpRotaryLimitJointSetMax(self, theMaxAngle);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetRatchetAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theRatchetAngle = cpRatchetJointGetAngle(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRatchetAngle) ); return; };
    }

    void cpConstraintWrap::SetRatchetAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inRatchetAngle)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theRatchetAngle"")");
        double theRatchetAngle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpRatchetJointSetAngle(self, theRatchetAngle);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetRatchetPhase(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theRatchetPhase = cpRatchetJointGetPhase(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRatchetPhase) ); return; };
    }

    void cpConstraintWrap::SetRatchetPhase(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inRatchetPhase)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theRatchetPhase"")");
        double theRatchetPhase = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetPhase" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpRatchetJointSetPhase(self, theRatchetPhase);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetRatchetInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theRatchetInterval = cpRatchetJointGetRatchet(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRatchetInterval) ); return; };
    }

    void cpConstraintWrap::SetRatchetInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inRatchetInterval)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theRatchetInterval"")");
        double theRatchetInterval = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Ratchet") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "RatchetInterval" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpRatchetJointSetRatchet(self, theRatchetInterval);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetGearRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theGearRatio = cpGearJointGetRatio(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theGearRatio) ); return; };
    }

    void cpConstraintWrap::SetGearRatio(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inGearRatio)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theGearRatio"")");
        double theGearRatio = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GearRatio" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpGearJointSetRatio(self, theGearRatio);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetGearInitialAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theGearInitialAngle = cpGearJointGetPhase(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theGearInitialAngle) ); return; };
    }

    void cpConstraintWrap::SetGearInitialAngle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inGearInitialAngle)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theGearInitialAngle"")");
        double theGearInitialAngle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Gear") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "GearInitialAngle" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpGearJointSetPhase(self, theGearInitialAngle);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetMotorSpinRate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        if (strcmp((const char*)cpConstraintGetUserData(self), "Motor") != 0)
        {
            args.GetReturnValue().SetUndefined();
        };
        cpFloat theMotorSpinRate = cpSimpleMotorGetRate(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMotorSpinRate) ); return; };
    }

    void cpConstraintWrap::SetMotorSpinRate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inMotorSpinRate)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMotorSpinRate"")");
        double theMotorSpinRate = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "Motor") != 0)
        {
            std::ostringstream msg;
            msg << "cpConstraint.set" "MotorSpinRate" "() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        cpSimpleMotorSetRate(self, theMotorSpinRate);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetSpringStiffness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        cpFloat theSpringStiffness;
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            theSpringStiffness = cpDampedSpringGetStiffness(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            theSpringStiffness = cpDampedRotarySpringGetStiffness(self);
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        };
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpringStiffness) ); return; };
    }

    void cpConstraintWrap::SetSpringStiffness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inSpringStiffness)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpringStiffness"")");
        double theSpringStiffness = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetStiffness(self, theSpringStiffness);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            cpDampedRotarySpringSetStiffness(self, theSpringStiffness);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringStiffness() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpConstraintWrap::GetSpringDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        cpFloat theSpringDamping;
        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            theSpringDamping = cpDampedSpringGetDamping(self);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            theSpringDamping = cpDampedRotarySpringGetDamping(self);
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        };
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpringDamping) ); return; };
    }

    void cpConstraintWrap::SetSpringDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpConstraintWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpConstraintWrap>(args.This());
        cpConstraint* self = dynamic_cast<cpConstraint*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpConstraint]" " function" "(number inSpringDamping)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpringDamping"")");
        double theSpringDamping = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        if (strcmp((const char*)cpConstraintGetUserData(self), "SpringJoint") == 0)
        {
            cpDampedSpringSetDamping(self, theSpringDamping);
        }
        else if (strcmp((const char*)cpConstraintGetUserData(self), "RotarySpring") == 0)
        {
            cpDampedRotarySpringSetDamping(self, theSpringDamping);
        }
        else
        {
            std::ostringstream msg;
            msg << "cpConstraint.setSpringDamping() not valid for constraint type "
                << (const char*)cpConstraintGetUserData(self);
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }()))) ;
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    cpConstraintWrap::cpConstraintWrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        cppPtr_ = nullptr;
    }

    cpConstraintWrap::~cpConstraintWrap()
    {
        cppPtr_ = nullptr;
    }

    cpConstraint* New_cpConstraint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_cpConstraint_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        s_HaveSavedError = true;
        {
            std::ostringstream excpt_;
            excpt_ << "CpConstraint cannot be created directly, it is only returned from certain Sprite calls.";
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
        };
        return 0;
    }

}
