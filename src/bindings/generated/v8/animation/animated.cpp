// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animated.cpp
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

namespace pdg
{

    float customEasing0(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(0, ut, b, c, ud);
    }

    float customEasing1(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(1, ut, b, c, ud);
    }

    float customEasing2(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(2, ut, b, c, ud);
    }

    float customEasing3(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(3, ut, b, c, ud);
    }

    float customEasing4(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(4, ut, b, c, ud);
    }

    float customEasing5(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(5, ut, b, c, ud);
    }

    float customEasing6(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(6, ut, b, c, ud);
    }

    float customEasing7(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(7, ut, b, c, ud);
    }

    float customEasing8(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(8, ut, b, c, ud);
    }

    float customEasing9(ms_delta ut, float b, float c, ms_delta ud)
    {
        return CallScriptEasingFunc(9, ut, b, c, ud);
    }

    bool s_IAnimationHelper_InNewFromCpp = false;

    void IAnimationHelperWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        IAnimationHelperWrap* objWrapper = new IAnimationHelperWrap(args);
        objWrapper->Wrap(args.This());
        IAnimationHelper* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mIAnimationHelperScriptObj.Reset(isolate, args.This());
        }
        objWrapper->Ref();
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> IAnimationHelperWrap::NewFromCpp(v8::Isolate* isolate, IAnimationHelper* cppObj)
    {
        s_IAnimationHelper_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_IAnimationHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_IAnimationHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        IAnimationHelperWrap* objWrapper = jswrap::ObjectWrap::Unwrap<IAnimationHelperWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mIAnimationHelperScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_IAnimationHelper_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> IAnimationHelperWrap::constructorTpl_;

    void IAnimationHelperWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "IAnimationHelper").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }

    void CleanupIAnimationHelperScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    static bool s_Animated_InNewFromCpp = false;

    void AnimatedWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = new AnimatedWrap(args);
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
    v8::Local<v8::Object> AnimatedWrap::NewFromCpp(v8::Isolate* isolate, Animated* cppObj)
    {
        s_Animated_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Animated_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Animated_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mAnimatedScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Animated_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> AnimatedWrap::constructorTpl_;

    void AnimatedWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Animated").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetBoundingBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBoundingBox_Tpl =
            v8::FunctionTemplate::New(isolate, GetBoundingBox, v8::Local<v8::Value>(), GetBoundingBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""BoundingBox").ToLocalChecked(), GetBoundingBox_Tpl);
        v8::Local<v8::Signature> GetRotatedBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotatedBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotatedBounds, v8::Local<v8::Value>(), GetRotatedBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""RotatedBounds").ToLocalChecked(), GetRotatedBounds_Tpl);
        v8::Local<v8::Signature> GetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, GetLocation, v8::Local<v8::Value>(), GetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Location").ToLocalChecked(), GetLocation_Tpl);
        v8::Local<v8::Signature> SetLocation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLocation_Tpl =
            v8::FunctionTemplate::New(isolate, SetLocation, v8::Local<v8::Value>(), SetLocation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Location").ToLocalChecked(), SetLocation_Tpl);
        v8::Local<v8::Signature> GetSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpeed, v8::Local<v8::Value>(), GetSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Speed").ToLocalChecked(), GetSpeed_Tpl);
        v8::Local<v8::Signature> SetSpeed_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpeed_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpeed, v8::Local<v8::Value>(), SetSpeed_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Speed").ToLocalChecked(), SetSpeed_Tpl);
        v8::Local<v8::Signature> GetVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, GetVelocity, v8::Local<v8::Value>(), GetVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Velocity").ToLocalChecked(), GetVelocity_Tpl);
        v8::Local<v8::Signature> SetVelocity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVelocity_Tpl =
            v8::FunctionTemplate::New(isolate, SetVelocity, v8::Local<v8::Value>(), SetVelocity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Velocity").ToLocalChecked(), SetVelocity_Tpl);
        v8::Local<v8::Signature> GetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetWidth, v8::Local<v8::Value>(), GetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Width").ToLocalChecked(), GetWidth_Tpl);
        v8::Local<v8::Signature> SetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, SetWidth, v8::Local<v8::Value>(), SetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Width").ToLocalChecked(), SetWidth_Tpl);
        v8::Local<v8::Signature> GetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetHeight, v8::Local<v8::Value>(), GetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Height").ToLocalChecked(), GetHeight_Tpl);
        v8::Local<v8::Signature> SetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, SetHeight, v8::Local<v8::Value>(), SetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Height").ToLocalChecked(), SetHeight_Tpl);
        v8::Local<v8::Signature> GetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, GetRotation, v8::Local<v8::Value>(), GetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Rotation").ToLocalChecked(), GetRotation_Tpl);
        v8::Local<v8::Signature> SetRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetRotation_Tpl =
            v8::FunctionTemplate::New(isolate, SetRotation, v8::Local<v8::Value>(), SetRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Rotation").ToLocalChecked(), SetRotation_Tpl);
        v8::Local<v8::Signature> GetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetCenterOffset, v8::Local<v8::Value>(), GetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""CenterOffset").ToLocalChecked(), GetCenterOffset_Tpl);
        v8::Local<v8::Signature> SetCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, SetCenterOffset, v8::Local<v8::Value>(), SetCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""CenterOffset").ToLocalChecked(), SetCenterOffset_Tpl);
        v8::Local<v8::Signature> GetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpin, v8::Local<v8::Value>(), GetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Spin").ToLocalChecked(), GetSpin_Tpl);
        v8::Local<v8::Signature> SetSpin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpin_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpin, v8::Local<v8::Value>(), SetSpin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Spin").ToLocalChecked(), SetSpin_Tpl);
        v8::Local<v8::Signature> GetMass_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMass_Tpl =
            v8::FunctionTemplate::New(isolate, GetMass, v8::Local<v8::Value>(), GetMass_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Mass").ToLocalChecked(), GetMass_Tpl);
        v8::Local<v8::Signature> SetMass_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMass_Tpl =
            v8::FunctionTemplate::New(isolate, SetMass, v8::Local<v8::Value>(), SetMass_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Mass").ToLocalChecked(), SetMass_Tpl);
        v8::Local<v8::Signature> GetMoveFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMoveFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetMoveFriction, v8::Local<v8::Value>(), GetMoveFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MoveFriction").ToLocalChecked(), GetMoveFriction_Tpl);
        v8::Local<v8::Signature> SetMoveFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMoveFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetMoveFriction, v8::Local<v8::Value>(), SetMoveFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MoveFriction").ToLocalChecked(), SetMoveFriction_Tpl);
        v8::Local<v8::Signature> GetSpinFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpinFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpinFriction, v8::Local<v8::Value>(), GetSpinFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SpinFriction").ToLocalChecked(), GetSpinFriction_Tpl);
        v8::Local<v8::Signature> SetSpinFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpinFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpinFriction, v8::Local<v8::Value>(), SetSpinFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SpinFriction").ToLocalChecked(), SetSpinFriction_Tpl);
        v8::Local<v8::Signature> GetSizeFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSizeFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetSizeFriction, v8::Local<v8::Value>(), GetSizeFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SizeFriction").ToLocalChecked(), GetSizeFriction_Tpl);
        v8::Local<v8::Signature> SetSizeFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSizeFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetSizeFriction, v8::Local<v8::Value>(), SetSizeFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SizeFriction").ToLocalChecked(), SetSizeFriction_Tpl);
        v8::Local<v8::Signature> Move_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Move_Tpl =
            v8::FunctionTemplate::New(isolate, Move, v8::Local<v8::Value>(), Move_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "move").ToLocalChecked(), Move_Tpl);
        v8::Local<v8::Signature> MoveTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveTo, v8::Local<v8::Value>(), MoveTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveTo").ToLocalChecked(), MoveTo_Tpl);
        v8::Local<v8::Signature> SetVelocityInRadians_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVelocityInRadians_Tpl =
            v8::FunctionTemplate::New(isolate, SetVelocityInRadians, v8::Local<v8::Value>(), SetVelocityInRadians_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setVelocityInRadians").ToLocalChecked(), SetVelocityInRadians_Tpl);
        v8::Local<v8::Signature> GetMovementDirectionInRadians_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMovementDirectionInRadians_Tpl =
            v8::FunctionTemplate::New(isolate, GetMovementDirectionInRadians, v8::Local<v8::Value>(), GetMovementDirectionInRadians_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMovementDirectionInRadians").ToLocalChecked(), GetMovementDirectionInRadians_Tpl);
        v8::Local<v8::Signature> StopMoving_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopMoving_Tpl =
            v8::FunctionTemplate::New(isolate, StopMoving, v8::Local<v8::Value>(), StopMoving_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopMoving").ToLocalChecked(), StopMoving_Tpl);
        v8::Local<v8::Signature> Accelerate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Accelerate_Tpl =
            v8::FunctionTemplate::New(isolate, Accelerate, v8::Local<v8::Value>(), Accelerate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "accelerate").ToLocalChecked(), Accelerate_Tpl);
        v8::Local<v8::Signature> AccelerateTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AccelerateTo_Tpl =
            v8::FunctionTemplate::New(isolate, AccelerateTo, v8::Local<v8::Value>(), AccelerateTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "accelerateTo").ToLocalChecked(), AccelerateTo_Tpl);
        v8::Local<v8::Signature> SetSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSize_Tpl =
            v8::FunctionTemplate::New(isolate, SetSize, v8::Local<v8::Value>(), SetSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSize").ToLocalChecked(), SetSize_Tpl);
        v8::Local<v8::Signature> Grow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Grow_Tpl =
            v8::FunctionTemplate::New(isolate, Grow, v8::Local<v8::Value>(), Grow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "grow").ToLocalChecked(), Grow_Tpl);
        v8::Local<v8::Signature> Stretch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Stretch_Tpl =
            v8::FunctionTemplate::New(isolate, Stretch, v8::Local<v8::Value>(), Stretch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stretch").ToLocalChecked(), Stretch_Tpl);
        v8::Local<v8::Signature> StartGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, StartGrowing, v8::Local<v8::Value>(), StartGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startGrowing").ToLocalChecked(), StartGrowing_Tpl);
        v8::Local<v8::Signature> StopGrowing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopGrowing_Tpl =
            v8::FunctionTemplate::New(isolate, StopGrowing, v8::Local<v8::Value>(), StopGrowing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopGrowing").ToLocalChecked(), StopGrowing_Tpl);
        v8::Local<v8::Signature> StartStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartStretching_Tpl =
            v8::FunctionTemplate::New(isolate, StartStretching, v8::Local<v8::Value>(), StartStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startStretching").ToLocalChecked(), StartStretching_Tpl);
        v8::Local<v8::Signature> StopStretching_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopStretching_Tpl =
            v8::FunctionTemplate::New(isolate, StopStretching, v8::Local<v8::Value>(), StopStretching_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopStretching").ToLocalChecked(), StopStretching_Tpl);
        v8::Local<v8::Signature> Resize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Resize_Tpl =
            v8::FunctionTemplate::New(isolate, Resize, v8::Local<v8::Value>(), Resize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resize").ToLocalChecked(), Resize_Tpl);
        v8::Local<v8::Signature> ResizeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResizeTo_Tpl =
            v8::FunctionTemplate::New(isolate, ResizeTo, v8::Local<v8::Value>(), ResizeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resizeTo").ToLocalChecked(), ResizeTo_Tpl);
        v8::Local<v8::Signature> SetFlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipX_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipX, v8::Local<v8::Value>(), SetFlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipX").ToLocalChecked(), SetFlipX_Tpl);
        v8::Local<v8::Signature> SetFlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFlipY_Tpl =
            v8::FunctionTemplate::New(isolate, SetFlipY, v8::Local<v8::Value>(), SetFlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFlipY").ToLocalChecked(), SetFlipY_Tpl);
        v8::Local<v8::Signature> FlipX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipX_Tpl =
            v8::FunctionTemplate::New(isolate, FlipX, v8::Local<v8::Value>(), FlipX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipX").ToLocalChecked(), FlipX_Tpl);
        v8::Local<v8::Signature> FlipY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FlipY_Tpl =
            v8::FunctionTemplate::New(isolate, FlipY, v8::Local<v8::Value>(), FlipY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "flipY").ToLocalChecked(), FlipY_Tpl);
        v8::Local<v8::Signature> IsFlippedX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedX_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedX, v8::Local<v8::Value>(), IsFlippedX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedX").ToLocalChecked(), IsFlippedX_Tpl);
        v8::Local<v8::Signature> IsFlippedY_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFlippedY_Tpl =
            v8::FunctionTemplate::New(isolate, IsFlippedY, v8::Local<v8::Value>(), IsFlippedY_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFlippedY").ToLocalChecked(), IsFlippedY_Tpl);
        v8::Local<v8::Signature> Rotate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Rotate_Tpl =
            v8::FunctionTemplate::New(isolate, Rotate, v8::Local<v8::Value>(), Rotate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotate").ToLocalChecked(), Rotate_Tpl);
        v8::Local<v8::Signature> RotateTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateTo_Tpl =
            v8::FunctionTemplate::New(isolate, RotateTo, v8::Local<v8::Value>(), RotateTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateTo").ToLocalChecked(), RotateTo_Tpl);
        v8::Local<v8::Signature> StopSpinning_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopSpinning_Tpl =
            v8::FunctionTemplate::New(isolate, StopSpinning, v8::Local<v8::Value>(), StopSpinning_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopSpinning").ToLocalChecked(), StopSpinning_Tpl);
        v8::Local<v8::Signature> ChangeCenter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenter_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenter, v8::Local<v8::Value>(), ChangeCenter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenter").ToLocalChecked(), ChangeCenter_Tpl);
        v8::Local<v8::Signature> ChangeCenterTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeCenterTo_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeCenterTo, v8::Local<v8::Value>(), ChangeCenterTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeCenterTo").ToLocalChecked(), ChangeCenterTo_Tpl);
        v8::Local<v8::Signature> Wait_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Wait_Tpl =
            v8::FunctionTemplate::New(isolate, Wait, v8::Local<v8::Value>(), Wait_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "wait").ToLocalChecked(), Wait_Tpl);
        v8::Local<v8::Signature> SetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, SetFriction, v8::Local<v8::Value>(), SetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFriction").ToLocalChecked(), SetFriction_Tpl);
        v8::Local<v8::Signature> ApplyForce_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyForce_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyForce, v8::Local<v8::Value>(), ApplyForce_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyForce").ToLocalChecked(), ApplyForce_Tpl);
        v8::Local<v8::Signature> ApplyTorque_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyTorque_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyTorque, v8::Local<v8::Value>(), ApplyTorque_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyTorque").ToLocalChecked(), ApplyTorque_Tpl);
        v8::Local<v8::Signature> StopAllForces_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopAllForces_Tpl =
            v8::FunctionTemplate::New(isolate, StopAllForces, v8::Local<v8::Value>(), StopAllForces_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopAllForces").ToLocalChecked(), StopAllForces_Tpl);
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
        v8::Local<v8::Signature> Animate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Animate_Tpl =
            v8::FunctionTemplate::New(isolate, Animate, v8::Local<v8::Value>(), Animate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "animate").ToLocalChecked(), Animate_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void AnimatedWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Point theLocation = self->getLocation();
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, theLocation) ); return; };
    }

    void AnimatedWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([object Point] inLocation)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point theLocation = v8_ValueToPoint(isolate, args[1 -1]);

        self->setLocation(theLocation);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSpeed = self->getSpeed();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpeed) ); return; };
    }

    void AnimatedWrap::SetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inSpeed)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpeed"")");
            return;
        }
        double theSpeed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setSpeed(theSpeed);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theWidth = self->getWidth();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theWidth) ); return; };
    }

    void AnimatedWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inWidth)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theWidth"")");
            return;
        }
        double theWidth = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setWidth(theWidth);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theHeight = self->getHeight();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theHeight) ); return; };
    }

    void AnimatedWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inHeight)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theHeight"")");
            return;
        }
        double theHeight = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setHeight(theHeight);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(boolean inFlipX)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""theFlipX"")");
            return;
        }
        bool theFlipX = args[1 -1]->BooleanValue(isolate);

        self->setFlipX(theFlipX);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(boolean inFlipY)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""theFlipY"")");
            return;
        }
        bool theFlipY = args[1 -1]->BooleanValue(isolate);

        self->setFlipY(theFlipY);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theRotation = self->getRotation();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theRotation) ); return; };
    }

    void AnimatedWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inRotation)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theRotation"")");
            return;
        }
        double theRotation = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setRotation(theRotation);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Offset theCenterOffset = self->getCenterOffset();
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, theCenterOffset) ); return; };
    }

    void AnimatedWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([object Offset] inCenterOffset)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        }
        pdg::Offset theCenterOffset = v8_ValueToOffset(isolate, args[1 -1]);

        self->setCenterOffset(theCenterOffset);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSpin = self->getSpin();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpin) ); return; };
    }

    void AnimatedWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inSpin)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpin"")");
            return;
        }
        double theSpin = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setSpin(theSpin);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theMass = self->getMass();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMass) ); return; };
    }

    void AnimatedWrap::SetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inMass)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMass"")");
            return;
        }
        double theMass = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setMass(theMass);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theMoveFriction = self->getMoveFriction();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theMoveFriction) ); return; };
    }

    void AnimatedWrap::SetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inMoveFriction)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theMoveFriction"")");
            return;
        }
        double theMoveFriction = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setMoveFriction(theMoveFriction);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSpinFriction = self->getSpinFriction();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSpinFriction) ); return; };
    }

    void AnimatedWrap::SetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inSpinFriction)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSpinFriction"")");
            return;
        }
        double theSpinFriction = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setSpinFriction(theSpinFriction);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSizeFriction = self->getSizeFriction();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSizeFriction) ); return; };
    }

    void AnimatedWrap::SetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number inSizeFriction)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSizeFriction"")");
            return;
        }
        double theSizeFriction = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setSizeFriction(theSizeFriction);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        pdg::Rect r = self->getBoundingBox();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void AnimatedWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        pdg::RotatedRect r = self->getRotatedBounds();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void AnimatedWrap::Move(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Offset] delta, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Offset delta;
        int32 msDuration;
        int easing;
        if (v8_ValueIsOffset(isolate, args[0]))
        {
            delta = v8_ValueToOffset(isolate, args[0]);
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration_2"")");
                return;
            }
            long msDuration_2 = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing_3"")");
                return;
            }
            long easing_3 = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            msDuration = msDuration_2;
            easing = easing_3;
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaX"")");
                return;
            }
            double deltaX = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaY"")");
                return;
            }
            double deltaY = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            delta.x = deltaX;
            delta.y = deltaY;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration_3"")");
                return;
            }
            long msDuration_3 = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easing_4"")");
                return;
            }
            long easing_4 = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            msDuration = msDuration_3;
            easing = easing_4;
        }
        if (msDuration || self->mDelayMs)
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->move(delta, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->move(delta, msDuration);
            }
        }
        else
        {
            self->move(delta);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] where, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Point where;
        int32 msDuration;
        int easing;
        if (v8_ValueIsPoint(isolate, args[0]))
        {
            where = v8_ValueToPoint(isolate, args[0]);
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration_2"")");
                return;
            }
            long msDuration_2 = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing_3"")");
                return;
            }
            long easing_3 = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_3;
            msDuration = msDuration_2;
        }
        else
        {
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
            where.x = x;
            where.y = y;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration3"")");
                return;
            }
            long msDuration3 = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easing_4"")");
                return;
            }
            long easing_4 = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_4;
            msDuration = msDuration3;
        }
        if (msDuration || self->mDelayMs)
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->moveTo(where, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->moveTo(where, msDuration);
            }
        }
        else
        {
            self->moveTo(where);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::SetVelocityInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number speed, number direction)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""speed"")");
            return;
        }
        double speed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""direction"")");
            return;
        }
        double direction = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setVelocityInRadians(speed, direction);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetMovementDirectionInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float dir = self->getMovementDirectionInRadians();
        { args.GetReturnValue().Set( v8::Number::New(isolate, dir) ); return; };
    }

    void AnimatedWrap::SetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "({[object Vector] deltaPerSec|number deltaXPerSec, number deltaYPerSec})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Vector deltaPerSec;
        if (v8_ValueIsVector(isolate, args[0]))
        {
            deltaPerSec = v8_ValueToVector(isolate, args[0]);
            self->setVelocity(deltaPerSec);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaXPerSec"")");
                return;
            }
            double deltaXPerSec = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaYPerSec"")");
                return;
            }
            double deltaYPerSec = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->setVelocity(Vector(deltaXPerSec, deltaYPerSec));
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::GetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Vector]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Vector theVelocity = self->getVelocity();
        { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, theVelocity) ); return; };
    }

    void AnimatedWrap::StopMoving(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopMoving();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::Accelerate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number deltaSpeed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""deltaSpeed"")");
            return;
        }
        double deltaSpeed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::linearTween : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->accelerate(deltaSpeed, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->accelerate(deltaSpeed, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::AccelerateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number speed, [number int] msDuration = duration_Instantaneous, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""speed"")");
            return;
        }
        double speed = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::linearTween : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->accelerateTo(speed, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->accelerateTo(speed, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number width, number height)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
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
        self->setSize(width, height);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number factor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
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
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (msDuration == 0)
        {
            self->grow(factor);
        }
        else
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->grow(factor, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->grow(factor, msDuration);
            }
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number widthFactor, number heightFactor, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
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
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (msDuration == 0)
        {
            self->stretch(widthFactor, heightFactor);
        }
        else
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->stretch(widthFactor, heightFactor, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->stretch(widthFactor, heightFactor, msDuration);
            }
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::StartGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number amountPerSecond)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""amountPerSecond"")");
            return;
        }
        double amountPerSecond = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->startGrowing(amountPerSecond);
        args.GetReturnValue().SetUndefined();
    }

    void AnimatedWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopGrowing();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::StartStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number widthPerSecond, number heightPerSecond)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
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
        self->startStretching(widthPerSecond, heightPerSecond);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopStretching();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::Resize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number deltaWidth, number deltaHeight, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
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
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->resize(deltaWidth, deltaHeight, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->resize(deltaWidth, deltaHeight, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number width, number height, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
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
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->resizeTo(width, height, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->resizeTo(width, height, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "flips the object horizontally, center offset is flipped too. Applied before other transformations.").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->flipX();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "()" " - " "flips the object vertically, center offset is flipped too. Applied before other transformations.").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->flipY();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "returns true if the object is flipped horizontally").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool theFlipX = self->isFlippedX();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theFlipX) ); return; };
    }

    void AnimatedWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "returns true if the object is flipped vertically").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool theFlipY = self->isFlippedY();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theFlipY) ); return; };
    }

    void AnimatedWrap::Rotate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number radians, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
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
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (msDuration == 0)
        {
            self->rotate(radians);
        }
        else
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->rotate(radians, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->rotate(radians, msDuration);
            }
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number radiansRotation, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""radiansRotation"")");
            return;
        }
        double radiansRotation = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (msDuration == 0)
        {
            self->rotateTo(radiansRotation);
        }
        else
        {
            if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
            {
                self->rotateTo(radiansRotation, msDuration, gEasingFunctions[easing]);
            }
            else
            {
                self->rotateTo(radiansRotation, msDuration);
            }
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopSpinning();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::ChangeCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Offset offset;
        int32 msDuration;
        int easing;
        if (v8_ValueIsOffset(isolate, args[0]))
        {
            offset = v8_ValueToOffset(isolate, args[0]);
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration_2"")");
                return;
            }
            long msDuration_2 = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing_3"")");
                return;
            }
            long easing_3 = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_3;
            msDuration = msDuration_2;
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaXOffset"")");
                return;
            }
            double deltaXOffset = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaYOffset"")");
                return;
            }
            double deltaYOffset = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            offset.x = deltaXOffset;
            offset.y = deltaYOffset;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration_3"")");
                return;
            }
            long msDuration_3 = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easing_4"")");
                return;
            }
            long easing_4 = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_4;
            msDuration = msDuration_3;
        }
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changeCenter(offset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changeCenter(offset, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::ChangeCenterTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Offset] offset, [number int] msDuration = duration_Instantaneous, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Offset offset;
        int32 msDuration;
        int easing;
        if (v8_ValueIsOffset(isolate, args[0]))
        {
            offset = v8_ValueToOffset(isolate, args[0]);
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration_2"")");
                return;
            }
            long msDuration_2 = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""easing_3"")");
                return;
            }
            long easing_3 = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_3;
            msDuration = msDuration_2;
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""deltaXOffset"")");
                return;
            }
            double deltaXOffset = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""deltaYOffset"")");
                return;
            }
            double deltaYOffset = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            offset.x = deltaXOffset;
            offset.y = deltaYOffset;
            if (args.Length() >= 3 && !args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""msDuration_3"")");
                return;
            }
            long msDuration_3 = (args.Length()<3) ? duration_Instantaneous : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            if (args.Length() >= 4 && !args[4 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 4, "a number (""easing_4"")");
                return;
            }
            long easing_4 = (args.Length()<4) ? EasingFuncRef::easeInOutQuad : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
            easing = easing_4;
            msDuration = msDuration_3;
        }
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changeCenterTo(offset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changeCenterTo(offset, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "([number int] msDuration)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""msDuration"")");
            return;
        }
        long msDuration = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->wait(msDuration);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::SetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Animated]" " function" "(number frictionCoefficient)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""frictionCoefficient"")");
            return;
        }
        double frictionCoefficient = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setFriction(frictionCoefficient);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::ApplyForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Vector] force, [number int] msDuration = duration_Instantaneous)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!v8_ValueIsVector(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
            return;
        }
        pdg::Vector force = v8_ValueToVector(isolate, args[1 -1]);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->applyForce(force, msDuration);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::ApplyTorque(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number forceSpin, [number int] msDuration = duration_Instantaneous)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""forceSpin"")");
            return;
        }
        double forceSpin = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = (args.Length()<2) ? duration_Instantaneous : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->applyTorque(forceSpin, msDuration);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::StopAllForces(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopAllForces();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void AnimatedWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mAnimatedScriptObj.Reset(isolate, args.This());
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 79 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 79 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 79 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 79 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                }
            }
            else
            {
                IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 79 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
            }
        } );
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, IAnimationHelper);
        self->addAnimationHelper(helper);
        args.GetReturnValue().SetUndefined();
    }

    void AnimatedWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, helper, IAnimationHelper);
        self->removeAnimationHelper(helper);
        args.GetReturnValue().SetUndefined();
    }

    void AnimatedWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clearAnimationHelpers();
        args.GetReturnValue().SetUndefined();
    }

    void AnimatedWrap::Animate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        AnimatedWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AnimatedWrap>(args.This());
        Animated* self = dynamic_cast<Animated*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([number int] msElapsed)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""msElapsed"")");
            return;
        }
        long msElapsed = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        bool result = self->animate(msElapsed);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void CleanupAnimatedScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    AnimatedWrap::AnimatedWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Animated(args);
        if (!cppPtr_ && !s_Animated_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Animated" " instance")));
            };
        }
    }

    AnimatedWrap::~AnimatedWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Animated* New_Animated(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Animated_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new Animated();
    }

}
