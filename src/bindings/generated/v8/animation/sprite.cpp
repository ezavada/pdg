// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/sprite.cpp
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

namespace pdg
{

    bool s_ISpriteCollideHelper_InNewFromCpp = false;

    void ISpriteCollideHelperWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ISpriteCollideHelperWrap* objWrapper = new ISpriteCollideHelperWrap(args);
        objWrapper->Wrap(args.This());
        ISpriteCollideHelper* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mISpriteCollideHelperScriptObj.Reset(isolate, args.This());
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
    v8::Local<v8::Object> ISpriteCollideHelperWrap::NewFromCpp(v8::Isolate* isolate, ISpriteCollideHelper* cppObj)
    {
        s_ISpriteCollideHelper_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_ISpriteCollideHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_ISpriteCollideHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ISpriteCollideHelperWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ISpriteCollideHelperWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mISpriteCollideHelperScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_ISpriteCollideHelper_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ISpriteCollideHelperWrap::constructorTpl_;

    void ISpriteCollideHelperWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ISpriteCollideHelper").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }

    void CleanupISpriteCollideHelperScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

#ifndef PDG_NO_GUI

    bool s_ISpriteDrawHelper_InNewFromCpp = false;

    void ISpriteDrawHelperWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ISpriteDrawHelperWrap* objWrapper = new ISpriteDrawHelperWrap(args);
        objWrapper->Wrap(args.This());
        ISpriteDrawHelper* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mISpriteDrawHelperScriptObj.Reset(isolate, args.This());
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
    v8::Local<v8::Object> ISpriteDrawHelperWrap::NewFromCpp(v8::Isolate* isolate, ISpriteDrawHelper* cppObj)
    {
        s_ISpriteDrawHelper_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_ISpriteDrawHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_ISpriteDrawHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ISpriteDrawHelperWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ISpriteDrawHelperWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mISpriteDrawHelperScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_ISpriteDrawHelper_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ISpriteDrawHelperWrap::constructorTpl_;

    void ISpriteDrawHelperWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ISpriteDrawHelper").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }

    void CleanupISpriteDrawHelperScriptObject(v8::UniquePersistent<v8::Object> &obj) { }
#endif

    static const char* sPinJointStr = "PinJoint";
    static const char* sSlideJointStr = "SlideJoint";
    static const char* sPivotJointStr = "PivotJoint";
    static const char* sGrooveJointStr = "GrooveJoint";
    static const char* sSpringJointStr = "SpringJoint";
    static const char* sRotarySpringStr = "RotarySpring";
    static const char* sRotaryLimitStr = "RotaryLimit";
    static const char* sRatchetStr = "Ratchet";
    static const char* sGearStr = "Gear";
    static const char* sMotorStr = "Motor";

    static bool s_Sprite_InNewFromCpp = false;

    void SpriteWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = new SpriteWrap(args);
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
    v8::Local<v8::Object> SpriteWrap::NewFromCpp(v8::Isolate* isolate, Sprite* cppObj)
    {
        s_Sprite_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Sprite_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Sprite_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mEventEmitterScriptObj.Reset(isolate, obj); cppObj->mAnimatedScriptObj.Reset(isolate, obj); cppObj->mSpriteScriptObj.Reset(isolate, obj); cppObj->mISerializableScriptObj.Reset(isolate, obj); cppObj->addRef();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Sprite_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SpriteWrap::constructorTpl_;

    void SpriteWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Sprite").ToLocalChecked();
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
        v8::Local<v8::Signature> GetMyClassTag_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMyClassTag_Tpl =
            v8::FunctionTemplate::New(isolate, GetMyClassTag, v8::Local<v8::Value>(), GetMyClassTag_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MyClassTag").ToLocalChecked(), GetMyClassTag_Tpl);
        v8::Local<v8::Signature> GetSerializedSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSerializedSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetSerializedSize, v8::Local<v8::Value>(), GetSerializedSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SerializedSize").ToLocalChecked(), GetSerializedSize_Tpl);
        v8::Local<v8::Signature> Serialize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize, v8::Local<v8::Value>(), Serialize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize").ToLocalChecked(), Serialize_Tpl);
        v8::Local<v8::Signature> Deserialize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize, v8::Local<v8::Value>(), Deserialize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize").ToLocalChecked(), Deserialize_Tpl);
        v8::Local<v8::Signature> GetFrameRotatedBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameRotatedBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameRotatedBounds, v8::Local<v8::Value>(), GetFrameRotatedBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameRotatedBounds").ToLocalChecked(), GetFrameRotatedBounds_Tpl);
        v8::Local<v8::Signature> SetFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFrame_Tpl =
            v8::FunctionTemplate::New(isolate, SetFrame, v8::Local<v8::Value>(), SetFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFrame").ToLocalChecked(), SetFrame_Tpl);
        v8::Local<v8::Signature> GetCurrentFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCurrentFrame_Tpl =
            v8::FunctionTemplate::New(isolate, GetCurrentFrame, v8::Local<v8::Value>(), GetCurrentFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCurrentFrame").ToLocalChecked(), GetCurrentFrame_Tpl);
        v8::Local<v8::Signature> GetFrameCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameCount, v8::Local<v8::Value>(), GetFrameCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameCount").ToLocalChecked(), GetFrameCount_Tpl);
        v8::Local<v8::Signature> StartFrameAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartFrameAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StartFrameAnimation, v8::Local<v8::Value>(), StartFrameAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startFrameAnimation").ToLocalChecked(), StartFrameAnimation_Tpl);
        v8::Local<v8::Signature> StopFrameAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopFrameAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StopFrameAnimation, v8::Local<v8::Value>(), StopFrameAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopFrameAnimation").ToLocalChecked(), StopFrameAnimation_Tpl);
        v8::Local<v8::Signature> GetWantsAnimLoopEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsAnimLoopEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsAnimLoopEvents, v8::Local<v8::Value>(), GetWantsAnimLoopEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsAnimLoopEvents").ToLocalChecked(), GetWantsAnimLoopEvents_Tpl);
        v8::Local<v8::Signature> SetWantsAnimLoopEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsAnimLoopEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsAnimLoopEvents, v8::Local<v8::Value>(), SetWantsAnimLoopEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsAnimLoopEvents").ToLocalChecked(), SetWantsAnimLoopEvents_Tpl);
        v8::Local<v8::Signature> GetWantsAnimEndEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsAnimEndEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsAnimEndEvents, v8::Local<v8::Value>(), GetWantsAnimEndEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsAnimEndEvents").ToLocalChecked(), GetWantsAnimEndEvents_Tpl);
        v8::Local<v8::Signature> SetWantsAnimEndEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsAnimEndEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsAnimEndEvents, v8::Local<v8::Value>(), SetWantsAnimEndEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsAnimEndEvents").ToLocalChecked(), SetWantsAnimEndEvents_Tpl);
        v8::Local<v8::Signature> GetWantsCollideWallEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsCollideWallEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsCollideWallEvents, v8::Local<v8::Value>(), GetWantsCollideWallEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsCollideWallEvents").ToLocalChecked(), GetWantsCollideWallEvents_Tpl);
        v8::Local<v8::Signature> SetWantsCollideWallEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsCollideWallEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsCollideWallEvents, v8::Local<v8::Value>(), SetWantsCollideWallEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsCollideWallEvents").ToLocalChecked(), SetWantsCollideWallEvents_Tpl);
        v8::Local<v8::Signature> AddFramesImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddFramesImage_Tpl =
            v8::FunctionTemplate::New(isolate, AddFramesImage, v8::Local<v8::Value>(), AddFramesImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addFramesImage").ToLocalChecked(), AddFramesImage_Tpl);
#ifdef PDG_SPRITER_SUPPORT
        v8::Local<v8::Signature> HasAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, HasAnimation, v8::Local<v8::Value>(), HasAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasAnimation").ToLocalChecked(), HasAnimation_Tpl);
        v8::Local<v8::Signature> StartAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StartAnimation, v8::Local<v8::Value>(), StartAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startAnimation").ToLocalChecked(), StartAnimation_Tpl);
        v8::Local<v8::Signature> SetEntityScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetEntityScale_Tpl =
            v8::FunctionTemplate::New(isolate, SetEntityScale, v8::Local<v8::Value>(), SetEntityScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setEntityScale").ToLocalChecked(), SetEntityScale_Tpl);
        v8::Local<v8::Signature> ApplyCharacterMap_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ApplyCharacterMap_Tpl =
            v8::FunctionTemplate::New(isolate, ApplyCharacterMap, v8::Local<v8::Value>(), ApplyCharacterMap_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "applyCharacterMap").ToLocalChecked(), ApplyCharacterMap_Tpl);
        v8::Local<v8::Signature> RemoveCharacterMap_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveCharacterMap_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveCharacterMap, v8::Local<v8::Value>(), RemoveCharacterMap_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeCharacterMap").ToLocalChecked(), RemoveCharacterMap_Tpl);
        v8::Local<v8::Signature> RemoveAllCharacterMaps_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAllCharacterMaps_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAllCharacterMaps, v8::Local<v8::Value>(), RemoveAllCharacterMaps_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAllCharacterMaps").ToLocalChecked(), RemoveAllCharacterMaps_Tpl);
        v8::Local<v8::Signature> GetAppliedCharacterMaps_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAppliedCharacterMaps_Tpl =
            v8::FunctionTemplate::New(isolate, GetAppliedCharacterMaps, v8::Local<v8::Value>(), GetAppliedCharacterMaps_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAppliedCharacterMaps").ToLocalChecked(), GetAppliedCharacterMaps_Tpl);
        v8::Local<v8::Signature> EnableSpriterEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableSpriterEvents_Tpl =
            v8::FunctionTemplate::New(isolate, EnableSpriterEvents, v8::Local<v8::Value>(), EnableSpriterEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableSpriterEvents").ToLocalChecked(), EnableSpriterEvents_Tpl);
        v8::Local<v8::Signature> AreSpriterEventsEnabled_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AreSpriterEventsEnabled_Tpl =
            v8::FunctionTemplate::New(isolate, AreSpriterEventsEnabled, v8::Local<v8::Value>(), AreSpriterEventsEnabled_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "areSpriterEventsEnabled").ToLocalChecked(), AreSpriterEventsEnabled_Tpl);
        v8::Local<v8::Signature> BlendToAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BlendToAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, BlendToAnimation, v8::Local<v8::Value>(), BlendToAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blendToAnimation").ToLocalChecked(), BlendToAnimation_Tpl);
        v8::Local<v8::Signature> IsBlending_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsBlending_Tpl =
            v8::FunctionTemplate::New(isolate, IsBlending, v8::Local<v8::Value>(), IsBlending_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isBlending").ToLocalChecked(), IsBlending_Tpl);
        v8::Local<v8::Signature> GetBlendProgress_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBlendProgress_Tpl =
            v8::FunctionTemplate::New(isolate, GetBlendProgress, v8::Local<v8::Value>(), GetBlendProgress_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBlendProgress").ToLocalChecked(), GetBlendProgress_Tpl);
        v8::Local<v8::Signature> PauseAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, PauseAnimation, v8::Local<v8::Value>(), PauseAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseAnimation").ToLocalChecked(), PauseAnimation_Tpl);
        v8::Local<v8::Signature> ResumeAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResumeAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, ResumeAnimation, v8::Local<v8::Value>(), ResumeAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resumeAnimation").ToLocalChecked(), ResumeAnimation_Tpl);
        v8::Local<v8::Signature> StopAnimation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopAnimation_Tpl =
            v8::FunctionTemplate::New(isolate, StopAnimation, v8::Local<v8::Value>(), StopAnimation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopAnimation").ToLocalChecked(), StopAnimation_Tpl);
        v8::Local<v8::Signature> IsAnimationPlaying_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPlaying_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPlaying, v8::Local<v8::Value>(), IsAnimationPlaying_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPlaying").ToLocalChecked(), IsAnimationPlaying_Tpl);
        v8::Local<v8::Signature> IsAnimationPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsAnimationPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsAnimationPaused, v8::Local<v8::Value>(), IsAnimationPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isAnimationPaused").ToLocalChecked(), IsAnimationPaused_Tpl);
        v8::Local<v8::Signature> GetAnimationProgress_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAnimationProgress_Tpl =
            v8::FunctionTemplate::New(isolate, GetAnimationProgress, v8::Local<v8::Value>(), GetAnimationProgress_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAnimationProgress").ToLocalChecked(), GetAnimationProgress_Tpl);
        v8::Local<v8::Signature> HasAttachPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasAttachPoint_Tpl =
            v8::FunctionTemplate::New(isolate, HasAttachPoint, v8::Local<v8::Value>(), HasAttachPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasAttachPoint").ToLocalChecked(), HasAttachPoint_Tpl);
        v8::Local<v8::Signature> GetAttachPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttachPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttachPoint, v8::Local<v8::Value>(), GetAttachPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttachPoint").ToLocalChecked(), GetAttachPoint_Tpl);
        v8::Local<v8::Signature> AttachSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AttachSprite_Tpl =
            v8::FunctionTemplate::New(isolate, AttachSprite, v8::Local<v8::Value>(), AttachSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "attachSprite").ToLocalChecked(), AttachSprite_Tpl);
        v8::Local<v8::Signature> ActivateSubEntity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ActivateSubEntity_Tpl =
            v8::FunctionTemplate::New(isolate, ActivateSubEntity, v8::Local<v8::Value>(), ActivateSubEntity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "activateSubEntity").ToLocalChecked(), ActivateSubEntity_Tpl);
        v8::Local<v8::Signature> DetachSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DetachSprite_Tpl =
            v8::FunctionTemplate::New(isolate, DetachSprite, v8::Local<v8::Value>(), DetachSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "detachSprite").ToLocalChecked(), DetachSprite_Tpl);
        v8::Local<v8::Signature> GetAttachedSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttachedSprite_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttachedSprite, v8::Local<v8::Value>(), GetAttachedSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttachedSprite").ToLocalChecked(), GetAttachedSprite_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBox_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBox_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBox, v8::Local<v8::Value>(), GetSpriterCollisionBox_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBox").ToLocalChecked(), GetSpriterCollisionBox_Tpl);
        v8::Local<v8::Signature> IsSpriterCollisionActive_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSpriterCollisionActive_Tpl =
            v8::FunctionTemplate::New(isolate, IsSpriterCollisionActive, v8::Local<v8::Value>(), IsSpriterCollisionActive_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSpriterCollisionActive").ToLocalChecked(), IsSpriterCollisionActive_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBoxCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBoxCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBoxCount, v8::Local<v8::Value>(), GetSpriterCollisionBoxCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBoxCount").ToLocalChecked(), GetSpriterCollisionBoxCount_Tpl);
        v8::Local<v8::Signature> GetSpriterCollisionBoxName_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriterCollisionBoxName_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriterCollisionBoxName, v8::Local<v8::Value>(), GetSpriterCollisionBoxName_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriterCollisionBoxName").ToLocalChecked(), GetSpriterCollisionBoxName_Tpl);
#endif
        v8::Local<v8::Signature> ChangeFramesImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeFramesImage_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeFramesImage, v8::Local<v8::Value>(), ChangeFramesImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeFramesImage").ToLocalChecked(), ChangeFramesImage_Tpl);
        v8::Local<v8::Signature> OffsetFrameCenters_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OffsetFrameCenters_Tpl =
            v8::FunctionTemplate::New(isolate, OffsetFrameCenters, v8::Local<v8::Value>(), OffsetFrameCenters_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "offsetFrameCenters").ToLocalChecked(), OffsetFrameCenters_Tpl);
        v8::Local<v8::Signature> GetFrameCenterOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameCenterOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameCenterOffset, v8::Local<v8::Value>(), GetFrameCenterOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrameCenterOffset").ToLocalChecked(), GetFrameCenterOffset_Tpl);
        v8::Local<v8::Signature> GetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetOpacity, v8::Local<v8::Value>(), GetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Opacity").ToLocalChecked(), GetOpacity_Tpl);
        v8::Local<v8::Signature> SetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, SetOpacity, v8::Local<v8::Value>(), SetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Opacity").ToLocalChecked(), SetOpacity_Tpl);
        v8::Local<v8::Signature> FadeTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeTo_Tpl =
            v8::FunctionTemplate::New(isolate, FadeTo, v8::Local<v8::Value>(), FadeTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeTo").ToLocalChecked(), FadeTo_Tpl);
        v8::Local<v8::Signature> FadeIn_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeIn_Tpl =
            v8::FunctionTemplate::New(isolate, FadeIn, v8::Local<v8::Value>(), FadeIn_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeIn").ToLocalChecked(), FadeIn_Tpl);
        v8::Local<v8::Signature> FadeOut_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeOut_Tpl =
            v8::FunctionTemplate::New(isolate, FadeOut, v8::Local<v8::Value>(), FadeOut_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeOut").ToLocalChecked(), FadeOut_Tpl);
        v8::Local<v8::Signature> IsBehind_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsBehind_Tpl =
            v8::FunctionTemplate::New(isolate, IsBehind, v8::Local<v8::Value>(), IsBehind_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isBehind").ToLocalChecked(), IsBehind_Tpl);
        v8::Local<v8::Signature> GetZOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetZOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetZOrder, v8::Local<v8::Value>(), GetZOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getZOrder").ToLocalChecked(), GetZOrder_Tpl);
        v8::Local<v8::Signature> MoveBehind_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveBehind_Tpl =
            v8::FunctionTemplate::New(isolate, MoveBehind, v8::Local<v8::Value>(), MoveBehind_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveBehind").ToLocalChecked(), MoveBehind_Tpl);
        v8::Local<v8::Signature> MoveInFrontOf_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveInFrontOf_Tpl =
            v8::FunctionTemplate::New(isolate, MoveInFrontOf, v8::Local<v8::Value>(), MoveInFrontOf_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveInFrontOf").ToLocalChecked(), MoveInFrontOf_Tpl);
        v8::Local<v8::Signature> MoveToFront_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToFront_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToFront, v8::Local<v8::Value>(), MoveToFront_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToFront").ToLocalChecked(), MoveToFront_Tpl);
        v8::Local<v8::Signature> MoveToBack_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToBack_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToBack, v8::Local<v8::Value>(), MoveToBack_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToBack").ToLocalChecked(), MoveToBack_Tpl);
        v8::Local<v8::Signature> EnableCollisions_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableCollisions_Tpl =
            v8::FunctionTemplate::New(isolate, EnableCollisions, v8::Local<v8::Value>(), EnableCollisions_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableCollisions").ToLocalChecked(), EnableCollisions_Tpl);
        v8::Local<v8::Signature> DisableCollisions_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisableCollisions_Tpl =
            v8::FunctionTemplate::New(isolate, DisableCollisions, v8::Local<v8::Value>(), DisableCollisions_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disableCollisions").ToLocalChecked(), DisableCollisions_Tpl);
        v8::Local<v8::Signature> GetCollisionType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionType_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionType, v8::Local<v8::Value>(), GetCollisionType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCollisionType").ToLocalChecked(), GetCollisionType_Tpl);
        v8::Local<v8::Signature> GetCollisionRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionRadius, v8::Local<v8::Value>(), GetCollisionRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""CollisionRadius").ToLocalChecked(), GetCollisionRadius_Tpl);
        v8::Local<v8::Signature> SetCollisionRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionRadius_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionRadius, v8::Local<v8::Value>(), SetCollisionRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""CollisionRadius").ToLocalChecked(), SetCollisionRadius_Tpl);
        v8::Local<v8::Signature> UseCollisionMask_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UseCollisionMask_Tpl =
            v8::FunctionTemplate::New(isolate, UseCollisionMask, v8::Local<v8::Value>(), UseCollisionMask_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "useCollisionMask").ToLocalChecked(), UseCollisionMask_Tpl);
        v8::Local<v8::Signature> SetCollisionHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionHelper_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionHelper, v8::Local<v8::Value>(), SetCollisionHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCollisionHelper").ToLocalChecked(), SetCollisionHelper_Tpl);
        v8::Local<v8::Signature> GetElasticity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetElasticity_Tpl =
            v8::FunctionTemplate::New(isolate, GetElasticity, v8::Local<v8::Value>(), GetElasticity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Elasticity").ToLocalChecked(), GetElasticity_Tpl);
        v8::Local<v8::Signature> SetElasticity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetElasticity_Tpl =
            v8::FunctionTemplate::New(isolate, SetElasticity, v8::Local<v8::Value>(), SetElasticity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Elasticity").ToLocalChecked(), SetElasticity_Tpl);
        v8::Local<v8::Signature> GetLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLayer_Tpl =
            v8::FunctionTemplate::New(isolate, GetLayer, v8::Local<v8::Value>(), GetLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLayer").ToLocalChecked(), GetLayer_Tpl);
#ifndef PDG_NO_GUI
        v8::Local<v8::Signature> SetDrawHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDrawHelper_Tpl =
            v8::FunctionTemplate::New(isolate, SetDrawHelper, v8::Local<v8::Value>(), SetDrawHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDrawHelper").ToLocalChecked(), SetDrawHelper_Tpl);
        v8::Local<v8::Signature> SetPostDrawHelper_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPostDrawHelper_Tpl =
            v8::FunctionTemplate::New(isolate, SetPostDrawHelper, v8::Local<v8::Value>(), SetPostDrawHelper_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPostDrawHelper").ToLocalChecked(), SetPostDrawHelper_Tpl);
        v8::Local<v8::Signature> GetWantsMouseOverEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsMouseOverEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsMouseOverEvents, v8::Local<v8::Value>(), GetWantsMouseOverEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsMouseOverEvents").ToLocalChecked(), GetWantsMouseOverEvents_Tpl);
        v8::Local<v8::Signature> SetWantsMouseOverEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsMouseOverEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsMouseOverEvents, v8::Local<v8::Value>(), SetWantsMouseOverEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsMouseOverEvents").ToLocalChecked(), SetWantsMouseOverEvents_Tpl);
        v8::Local<v8::Signature> GetWantsClickEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsClickEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsClickEvents, v8::Local<v8::Value>(), GetWantsClickEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsClickEvents").ToLocalChecked(), GetWantsClickEvents_Tpl);
        v8::Local<v8::Signature> SetWantsClickEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsClickEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsClickEvents, v8::Local<v8::Value>(), SetWantsClickEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsClickEvents").ToLocalChecked(), SetWantsClickEvents_Tpl);
        v8::Local<v8::Signature> GetMouseDetectMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMouseDetectMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetMouseDetectMode, v8::Local<v8::Value>(), GetMouseDetectMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""MouseDetectMode").ToLocalChecked(), GetMouseDetectMode_Tpl);
        v8::Local<v8::Signature> SetMouseDetectMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMouseDetectMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetMouseDetectMode, v8::Local<v8::Value>(), SetMouseDetectMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""MouseDetectMode").ToLocalChecked(), SetMouseDetectMode_Tpl);
        v8::Local<v8::Signature> GetWantsOffscreenEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWantsOffscreenEvents_Tpl =
            v8::FunctionTemplate::New(isolate, GetWantsOffscreenEvents, v8::Local<v8::Value>(), GetWantsOffscreenEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WantsOffscreenEvents").ToLocalChecked(), GetWantsOffscreenEvents_Tpl);
        v8::Local<v8::Signature> SetWantsOffscreenEvents_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWantsOffscreenEvents_Tpl =
            v8::FunctionTemplate::New(isolate, SetWantsOffscreenEvents, v8::Local<v8::Value>(), SetWantsOffscreenEvents_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WantsOffscreenEvents").ToLocalChecked(), SetWantsOffscreenEvents_Tpl);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        v8::Local<v8::Signature> MakeStatic_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MakeStatic_Tpl =
            v8::FunctionTemplate::New(isolate, MakeStatic, v8::Local<v8::Value>(), MakeStatic_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "makeStatic").ToLocalChecked(), MakeStatic_Tpl);
        v8::Local<v8::Signature> GetFriction_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFriction_Tpl =
            v8::FunctionTemplate::New(isolate, GetFriction, v8::Local<v8::Value>(), GetFriction_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFriction").ToLocalChecked(), GetFriction_Tpl);
        v8::Local<v8::Signature> SetCollideGroup_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollideGroup_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollideGroup, v8::Local<v8::Value>(), SetCollideGroup_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCollideGroup").ToLocalChecked(), SetCollideGroup_Tpl);
        v8::Local<v8::Signature> GetCollideGroup_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollideGroup_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollideGroup, v8::Local<v8::Value>(), GetCollideGroup_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCollideGroup").ToLocalChecked(), GetCollideGroup_Tpl);
        v8::Local<v8::Signature> PinJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PinJoint_Tpl =
            v8::FunctionTemplate::New(isolate, PinJoint, v8::Local<v8::Value>(), PinJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pinJoint").ToLocalChecked(), PinJoint_Tpl);
        v8::Local<v8::Signature> SlideJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SlideJoint_Tpl =
            v8::FunctionTemplate::New(isolate, SlideJoint, v8::Local<v8::Value>(), SlideJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "slideJoint").ToLocalChecked(), SlideJoint_Tpl);
        v8::Local<v8::Signature> PivotJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PivotJoint_Tpl =
            v8::FunctionTemplate::New(isolate, PivotJoint, v8::Local<v8::Value>(), PivotJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pivotJoint").ToLocalChecked(), PivotJoint_Tpl);
        v8::Local<v8::Signature> GrooveJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GrooveJoint_Tpl =
            v8::FunctionTemplate::New(isolate, GrooveJoint, v8::Local<v8::Value>(), GrooveJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "grooveJoint").ToLocalChecked(), GrooveJoint_Tpl);
        v8::Local<v8::Signature> SpringJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SpringJoint_Tpl =
            v8::FunctionTemplate::New(isolate, SpringJoint, v8::Local<v8::Value>(), SpringJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "springJoint").ToLocalChecked(), SpringJoint_Tpl);
        v8::Local<v8::Signature> RotarySpring_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotarySpring_Tpl =
            v8::FunctionTemplate::New(isolate, RotarySpring, v8::Local<v8::Value>(), RotarySpring_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotarySpring").ToLocalChecked(), RotarySpring_Tpl);
        v8::Local<v8::Signature> RotaryLimit_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotaryLimit_Tpl =
            v8::FunctionTemplate::New(isolate, RotaryLimit, v8::Local<v8::Value>(), RotaryLimit_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotaryLimit").ToLocalChecked(), RotaryLimit_Tpl);
        v8::Local<v8::Signature> Ratchet_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Ratchet_Tpl =
            v8::FunctionTemplate::New(isolate, Ratchet, v8::Local<v8::Value>(), Ratchet_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "ratchet").ToLocalChecked(), Ratchet_Tpl);
        v8::Local<v8::Signature> Gear_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Gear_Tpl =
            v8::FunctionTemplate::New(isolate, Gear, v8::Local<v8::Value>(), Gear_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "gear").ToLocalChecked(), Gear_Tpl);
        v8::Local<v8::Signature> Motor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Motor_Tpl =
            v8::FunctionTemplate::New(isolate, Motor, v8::Local<v8::Value>(), Motor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "motor").ToLocalChecked(), Motor_Tpl);
        v8::Local<v8::Signature> RemoveJoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveJoint_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveJoint, v8::Local<v8::Value>(), RemoveJoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeJoint").ToLocalChecked(), RemoveJoint_Tpl);
        v8::Local<v8::Signature> Disconnect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Disconnect_Tpl =
            v8::FunctionTemplate::New(isolate, Disconnect, v8::Local<v8::Value>(), Disconnect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disconnect").ToLocalChecked(), Disconnect_Tpl);
        v8::Local<v8::Signature> MakeJointBreakable_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MakeJointBreakable_Tpl =
            v8::FunctionTemplate::New(isolate, MakeJointBreakable, v8::Local<v8::Value>(), MakeJointBreakable_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "makeJointBreakable").ToLocalChecked(), MakeJointBreakable_Tpl);
        v8::Local<v8::Signature> MakeJointUnbreakable_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MakeJointUnbreakable_Tpl =
            v8::FunctionTemplate::New(isolate, MakeJointUnbreakable, v8::Local<v8::Value>(), MakeJointUnbreakable_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "makeJointUnbreakable").ToLocalChecked(), MakeJointUnbreakable_Tpl);
#endif
        v8::Local<v8::Signature> On_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> On_Tpl =
            v8::FunctionTemplate::New(isolate, On, v8::Local<v8::Value>(), On_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "on").ToLocalChecked(), On_Tpl);
        v8::Local<v8::Signature> OnCollideSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnCollideSprite_Tpl =
            v8::FunctionTemplate::New(isolate, OnCollideSprite, v8::Local<v8::Value>(), OnCollideSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onCollideSprite").ToLocalChecked(), OnCollideSprite_Tpl);
        v8::Local<v8::Signature> OnCollideWall_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnCollideWall_Tpl =
            v8::FunctionTemplate::New(isolate, OnCollideWall, v8::Local<v8::Value>(), OnCollideWall_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onCollideWall").ToLocalChecked(), OnCollideWall_Tpl);
        v8::Local<v8::Signature> OnOffscreen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnOffscreen_Tpl =
            v8::FunctionTemplate::New(isolate, OnOffscreen, v8::Local<v8::Value>(), OnOffscreen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onOffscreen").ToLocalChecked(), OnOffscreen_Tpl);
        v8::Local<v8::Signature> OnOnscreen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnOnscreen_Tpl =
            v8::FunctionTemplate::New(isolate, OnOnscreen, v8::Local<v8::Value>(), OnOnscreen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onOnscreen").ToLocalChecked(), OnOnscreen_Tpl);
        v8::Local<v8::Signature> OnExitLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnExitLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnExitLayer, v8::Local<v8::Value>(), OnExitLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onExitLayer").ToLocalChecked(), OnExitLayer_Tpl);
        v8::Local<v8::Signature> OnAnimationLoop_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationLoop_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationLoop, v8::Local<v8::Value>(), OnAnimationLoop_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationLoop").ToLocalChecked(), OnAnimationLoop_Tpl);
        v8::Local<v8::Signature> OnAnimationEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationEnd_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationEnd, v8::Local<v8::Value>(), OnAnimationEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationEnd").ToLocalChecked(), OnAnimationEnd_Tpl);
        v8::Local<v8::Signature> OnAnimationBlendComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationBlendComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationBlendComplete, v8::Local<v8::Value>(), OnAnimationBlendComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationBlendComplete").ToLocalChecked(), OnAnimationBlendComplete_Tpl);
        v8::Local<v8::Signature> OnFadeComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeComplete, v8::Local<v8::Value>(), OnFadeComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeComplete").ToLocalChecked(), OnFadeComplete_Tpl);
        v8::Local<v8::Signature> OnFadeInComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeInComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeInComplete, v8::Local<v8::Value>(), OnFadeInComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeInComplete").ToLocalChecked(), OnFadeInComplete_Tpl);
        v8::Local<v8::Signature> OnFadeOutComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnFadeOutComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnFadeOutComplete, v8::Local<v8::Value>(), OnFadeOutComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onFadeOutComplete").ToLocalChecked(), OnFadeOutComplete_Tpl);
        v8::Local<v8::Signature> OnMouseEnter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseEnter_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseEnter, v8::Local<v8::Value>(), OnMouseEnter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseEnter").ToLocalChecked(), OnMouseEnter_Tpl);
        v8::Local<v8::Signature> OnMouseLeave_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseLeave_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseLeave, v8::Local<v8::Value>(), OnMouseLeave_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseLeave").ToLocalChecked(), OnMouseLeave_Tpl);
        v8::Local<v8::Signature> OnMouseDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseDown_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseDown, v8::Local<v8::Value>(), OnMouseDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseDown").ToLocalChecked(), OnMouseDown_Tpl);
        v8::Local<v8::Signature> OnMouseUp_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseUp_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseUp, v8::Local<v8::Value>(), OnMouseUp_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseUp").ToLocalChecked(), OnMouseUp_Tpl);
        v8::Local<v8::Signature> OnMouseClick_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnMouseClick_Tpl =
            v8::FunctionTemplate::New(isolate, OnMouseClick, v8::Local<v8::Value>(), OnMouseClick_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onMouseClick").ToLocalChecked(), OnMouseClick_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SpriteWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IEventHandler] inHandler, [number int] inEventType = all_events)" " - " "add a new handler for some event type, or for all events if no type specified. "
                    " \\param inHandler the object to handle events" " \\param inEventType the type of event to handle").ToLocalChecked() ); return;
            };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 190 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 190 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 190 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 190 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 190 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void SpriteWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IEventHandler] inHandler, [number int] inEventType = all_events)" " - " "remove a handler for some event type, or for all events (see note) if no type specified. "
                    "If the handler is listed multiple times it will only remove it once.\n"
                    "NOTE: inType == all_events doesn't work quite like you might expect. If "
                    "you have registered a handler for multiple events, but not with all_events, "
                    "doing removeHandler(handler, all_events) will do nothing. Basically, "
                    "all_events is a special event type that matches all event types when "
                    "considering whether to invoke a handler or not.\n"
                    "It is safe to call remove handler from within an event handler's handleEvent() call."
                    " \\param inHandler the object to handle events" " \\param inEventType the type of event to stop handling (see note)").ToLocalChecked() ); return;
            };
        };
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

    void SpriteWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "remove all handlers").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clear();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] inEventType)" " - " "temporarily ignore all events of a particular type. "
                    "Events that are blocked are NOT cached for later, they are just dropped."
                    " \\param inEventType the type of event to block").ToLocalChecked() ); return;
            };
        };
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

    void SpriteWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] inEventType)" " - " "stop ignoring events of a particular type "
                    " \\param inEventType the type of event to unblock").ToLocalChecked() ); return;
            };
        };
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

    void SpriteWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Point] inLocation)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inSpeed)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inWidth)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inHeight)").ToLocalChecked() ); return; };
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

    void SpriteWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean inFlipX)").ToLocalChecked() ); return; };
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

    void SpriteWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean inFlipY)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inRotation)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Offset] inCenterOffset)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inSpin)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inMass)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inMoveFriction)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inSpinFriction)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number inSizeFriction)").ToLocalChecked() ); return; };
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

    void SpriteWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Move(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetVelocityInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::GetMovementDirectionInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::GetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StopMoving(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Accelerate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::AccelerateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StartGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StartStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Resize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Rotate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ChangeCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ChangeCenterTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::SetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ApplyForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ApplyTorque(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::StopAllForces(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mAnimatedScriptObj.Reset(isolate, args.This());
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 191 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 191 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 191 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 191 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                }
            }
            else
            {
                IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 191 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
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

    void SpriteWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

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

    void SpriteWrap::GetMyClassTag(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        uint32 theMyClassTag = self->getMyClassTag();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, theMyClassTag) ); return; };
    }

    void SpriteWrap::GetSerializedSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [number uint]" " function" "([object Serializer] serializer)" " - " "get size of this object's data for the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer);
        uint32 dataSize = self->getSerializedSize(serializer);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, dataSize) ); return; };
    }

    void SpriteWrap::Serialize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "([object Serializer] serializer)" " - " "write this object's data into the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, serializer, Serializer);
        self->serialize(serializer);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::Deserialize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "([object Deserializer] deserializer)" " - " "read this object's data from the given stream").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, deserializer, Deserializer);
        try
        {
            self->deserialize(deserializer);
            args.GetReturnValue().SetUndefined();
        }
        catch(out_of_data& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(bad_tag& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(sync_error& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        catch(unknown_object& e)
        {
            std::ostringstream excpt_;
            excpt_ << e.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
    }

    void SpriteWrap::GetWantsAnimLoopEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsAnimLoopEvents = self->getWantsAnimLoopEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsAnimLoopEvents) ); return; };
    }

    void SpriteWrap::GetWantsAnimEndEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsAnimEndEvents = self->getWantsAnimEndEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsAnimEndEvents) ); return; };
    }

    void SpriteWrap::GetWantsCollideWallEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsCollideWallEvents = self->getWantsCollideWallEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsCollideWallEvents) ); return; };
    }
#ifndef PDG_NO_GUI

    void SpriteWrap::GetWantsMouseOverEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsMouseOverEvents = self->getWantsMouseOverEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsMouseOverEvents) ); return; };
    }

    void SpriteWrap::GetWantsClickEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsClickEvents = self->getWantsClickEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsClickEvents) ); return; };
    }

    void SpriteWrap::GetMouseDetectMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theMouseDetectMode = self->getMouseDetectMode();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theMouseDetectMode) ); return; };
    }

    void SpriteWrap::GetWantsOffscreenEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        bool theWantsOffscreenEvents = self->getWantsOffscreenEvents();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, theWantsOffscreenEvents) ); return; };
    }
#endif

    void SpriteWrap::GetFrameRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "([number int] frameNum = -1)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""frameNum"")");
            return;
        }
        long frameNum = (args.Length()<1) ? -1 : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::RotatedRect r = self->getFrameRotatedBounds(frameNum);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void SpriteWrap::SetFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] frame)" " - " "").ToLocalChecked() ); return; };
        };
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
        long frame = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->setFrame(frame);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetCurrentFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "which frame of animation the sprite is currently showing").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int frame = self->getCurrentFrame();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, frame) ); return; };
    }

    void SpriteWrap::GetFrameCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "total number of frames of animation for this sprite").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int count = self->getFrameCount();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, count) ); return; };
    }

    void SpriteWrap::StartFrameAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number fps, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames, [number int] animateFlags = animate_Looping)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""fps"")");
            return;
        }
        double fps = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<2) ? Sprite::start_FromFirstFrame : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<3) ? Sprite::all_Frames : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""animateFlags"")");
            return;
        }
        long animateFlags = (args.Length()<4) ? Sprite::animate_Looping : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->startFrameAnimation(fps, startingFrame, numFrames, animateFlags);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::StopFrameAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopFrameAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetWantsAnimLoopEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsAnimLoopEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsAnimEndEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsAnimEndEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsCollideWallEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsCollideWallEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::AddFramesImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] image, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, image, Image);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<2) ? Sprite::start_FromFirstFrame : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<3) ? Sprite::all_Frames : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->addFramesImage(image, startingFrame, numFrames);
        args.GetReturnValue().SetUndefined();
    }
#ifdef PDG_SPRITER_SUPPORT

    void SpriteWrap::HasAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "({ [number int] animationId | string animationName })" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        bool hasIt = false;
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            hasIt = self->hasAnimation(animationName);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            unsigned long animationId = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            hasIt = self->hasAnimation(animationId);
        }
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, hasIt) ); return; };
    }

    void SpriteWrap::StartAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({ [number int] animationId | string animationName })" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            self->startAnimation(animationName);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            unsigned long animationId = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            self->startAnimation(animationId);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetEntityScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number xScale, number yScale)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""xScale"")");
            return;
        }
        double xScale = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""yScale"")");
            return;
        }
        double yScale = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setEntityScale(xScale, yScale);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::ApplyCharacterMap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string mapName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""mapName"")");
            return;
        }
        v8::String::Utf8Value mapName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* mapName = *mapName_Str;;
        self->applyCharacterMap(mapName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::RemoveCharacterMap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string mapName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""mapName"")");
            return;
        }
        v8::String::Utf8Value mapName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* mapName = *mapName_Str;;
        self->removeCharacterMap(mapName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::RemoveAllCharacterMaps(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->removeAllCharacterMaps();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAppliedCharacterMaps(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Array]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        std::vector<std::string> maps = self->getAppliedCharacterMaps();

        v8::Local<v8::Array> arr = v8::Array::New(isolate);
        for (size_t i = 0; i < maps.size(); i++)
        {
            arr->Set(isolate->GetCurrentContext(), v8::Integer::New(isolate, i),
                v8::String::NewFromUtf8(isolate, maps[i].c_str()).ToLocalChecked()).ToChecked();
        }
        { args.GetReturnValue().Set( arr ); return; };
    }

    void SpriteWrap::EnableSpriterEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean enable = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""enable"")");
            return;
        }
        bool enable = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->enableSpriterEvents(enable);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::AreSpriterEventsEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool enabled = self->areSpriterEventsEnabled();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, enabled) ); return; };
    }

    void SpriteWrap::BlendToAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({ [number int] animationId | string animationName }, number blendTime)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""blendTime"")");
            return;
        }
        double blendTime = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args[0]->IsString())
        {
            if (!args[1 -1]->IsString())
            {
                v8_ThrowArgTypeException(isolate, 1, "a string  (""animationName"")");
                return;
            }
            v8::String::Utf8Value animationName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* animationName = *animationName_Str;;
            self->blendToAnimation(animationName, blendTime);
        }
        else
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""animationId"")");
                return;
            }
            unsigned long animationId = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
            self->blendToAnimation(animationId, blendTime);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsBlending(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool blending = self->isBlending();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, blending) ); return; };
    }

    void SpriteWrap::GetBlendProgress(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float progress = self->getBlendProgress();
        { args.GetReturnValue().Set( v8::Number::New(isolate, progress) ); return; };
    }

    void SpriteWrap::PauseAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->pauseAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::ResumeAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->resumeAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::StopAnimation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopAnimation();
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsAnimationPlaying(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool playing = self->isAnimationPlaying();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, playing) ); return; };
    }

    void SpriteWrap::IsAnimationPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool paused = self->isAnimationPaused();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, paused) ); return; };
    }

    void SpriteWrap::GetAnimationProgress(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float progress = self->getAnimationProgress();
        { args.GetReturnValue().Set( v8::Number::New(isolate, progress) ); return; };
    }

    void SpriteWrap::HasAttachPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        bool hasPoint = self->hasAttachPoint(attachPointName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, hasPoint) ); return; };
    }

    void SpriteWrap::GetAttachPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        pdg::Offset offset = self->getAttachPoint(attachPointName);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void SpriteWrap::AttachSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] sprite, string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        if (!args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        self->attachSprite(sprite, attachPointName);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::DetachSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->detachSprite(sprite);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetAttachedSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(string attachPointName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""attachPointName"")");
            return;
        }
        v8::String::Utf8Value attachPointName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* attachPointName = *attachPointName_Str;;
        pdg::Sprite* attached = self->getAttachedSprite(attachPointName);
        if (attached)
        {
            if (!attached) { args.GetReturnValue().SetNull(); return; };
            { args.GetReturnValue().Set( SpriteWrap::NewFromCpp(isolate, attached) ); return; };
            ;
        }
        else
        {
            { args.GetReturnValue().SetNull(); return; };
        }
    }

    void SpriteWrap::ActivateSubEntity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string entityName, string animationName = \"idle\")" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""entityName"")");
            return;
        }
        v8::String::Utf8Value entityName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* entityName = *entityName_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""animationName"")");
            return;
        }
        v8::String::Utf8Value _animationName_String( isolate, (args.Length()<2) ? v8::String::NewFromUtf8(isolate, "").ToLocalChecked() : args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked() );
        const char* animationName = (args.Length()<2) ? "idle" : *_animationName_String;;
        self->activateSubEntity(entityName, animationName);
        args.GetReturnValue().SetUndefined();
    }
#endif
#ifndef PDG_NO_GUI

    void SpriteWrap::SetWantsOffscreenEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsOffscreenEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object ISpriteDrawHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mSpriteScriptObj.Reset(isolate, args.This());
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 494 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 494 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISpriteDrawHelperWrap* obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 494 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISpriteDrawHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 494 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISpriteDrawHelper""\n";
                }
            }
            else
            {
                ISpriteDrawHelper* obj = dynamic_cast<ISpriteDrawHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 494 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISpriteDrawHelper"" ("<<(void*)obj<<")\n";
            }
        } )
            self->setDrawHelper(helper);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetPostDrawHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object ISpriteDrawHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mSpriteScriptObj.Reset(isolate, args.This());
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(1, helper, ISpriteDrawHelper);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 503 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 503 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISpriteDrawHelperWrap* obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISpriteDrawHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 503 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISpriteDrawHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 503 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISpriteDrawHelper""\n";
                }
            }
            else
            {
                ISpriteDrawHelper* obj = dynamic_cast<ISpriteDrawHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 503 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISpriteDrawHelper"" ("<<(void*)obj<<")\n";
            }
        } )
            self->setPostDrawHelper(helper);
        args.GetReturnValue().SetUndefined();
    }
#endif

    void SpriteWrap::ChangeFramesImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] oldImage, [object Image] newImage)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, oldImage, Image);
        REQUIRE_CPP_OBJECT_ARG(2, newImage, Image);
        self->changeFramesImage(oldImage, newImage);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::OffsetFrameCenters(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] offsetX, [number int] offsetY, [object Image] image = null, [number int] startingFrame = start_FromFirstFrame, [number int] numFrames = all_Frames)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""offsetX"")");
            return;
        }
        long offsetX = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""offsetY"")");
            return;
        }
        long offsetY = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        Image* image = 0;
        if (args.Length() >= 3)
        {
            if (!args[3 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 3, "an object of type ""Image"" (""image"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> image_ = args[3 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                ImageWrap* image__ = jswrap::ObjectWrap::Unwrap<ImageWrap>(image_);
                image = image__->getCppObject();
            }
        };
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""startingFrame"")");
            return;
        }
        long startingFrame = (args.Length()<4) ? Sprite::start_FromFirstFrame : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""numFrames"")");
            return;
        }
        long numFrames = (args.Length()<5) ? Sprite::all_Frames : args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->offsetFrameCenters(offsetX, offsetY, image, startingFrame, numFrames);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::GetFrameCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "([object Image] image = null, [number int] frameNum = 0)" " - " "").ToLocalChecked() ); return; };
        };
        Image* image = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Image"" (""image"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> image_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                ImageWrap* image__ = jswrap::ObjectWrap::Unwrap<ImageWrap>(image_);
                image = image__->getCppObject();
            }
        };
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""frameNum"")");
            return;
        }
        long frameNum = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        pdg::Offset offset = self->getFrameCenterOffset(image, frameNum);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void SpriteWrap::SetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number opacity)" " - " "").ToLocalChecked() ); return; };
        };
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
        self->setOpacity(opacity);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void SpriteWrap::FadeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number targetOpacity, [number int] msDuration, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""targetOpacity"")");
            return;
        }
        double targetOpacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msDuration"")");
            return;
        }
        long msDuration = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::linearTween : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeTo(targetOpacity, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeTo(targetOpacity, msDuration);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::FadeIn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] msDuration, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""msDuration"")");
            return;
        }
        long msDuration = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(msDuration);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::FadeOut(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] msDuration, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""msDuration"")");
            return;
        }
        long msDuration = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(msDuration);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::IsBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        bool behind = self->isBehind(sprite);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, behind) ); return; };
    }

    void SpriteWrap::GetZOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int zorder = self->getZOrder();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, zorder) ); return; };
    }

    void SpriteWrap::MoveBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->moveBehind(sprite);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveInFrontOf(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        self->moveInFrontOf(sprite);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveToFront(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "put this sprite in front of all others in its layer").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToFront();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::MoveToBack(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "put this sprite behind all others in its layer").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToBack();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::EnableCollisions(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] collisionType = collide_AlphaChannel)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""collisionType"")");
            return;
        }
        long collisionType = (args.Length()<1) ? Sprite::collide_AlphaChannel : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->enableCollisions(collisionType);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::DisableCollisions(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->disableCollisions();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetCollisionType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "get the current collision type").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int collisionType = self->getCollisionType();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, collisionType) ); return; };
    }

    void SpriteWrap::SetCollisionRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number pixelRadius)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""pixelRadius"")");
            return;
        }
        double pixelRadius = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setCollisionRadius(pixelRadius);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetCollisionRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float radius = self->getCollisionRadius();
        { args.GetReturnValue().Set( v8::Number::New(isolate, radius) ); return; };
    }

    void SpriteWrap::UseCollisionMask(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] frameImage, [object Image] maskImage)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, frameImage, Image);
        REQUIRE_CPP_OBJECT_ARG(2, maskImage, Image);
        self->useCollisionMask(frameImage, maskImage);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetCollisionHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object ISpriteCollideHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mSpriteScriptObj.Reset(isolate, args.This());
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 665 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 665 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = args[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISpriteCollideHelperWrap* obj__ = dynamic_cast<ISpriteCollideHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISpriteCollideHelperWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 665 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""ISpriteCollideHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 665 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""ISpriteCollideHelper""\n";
                }
            }
            else
            {
                ISpriteCollideHelper* obj = dynamic_cast<ISpriteCollideHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 665 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""ISpriteCollideHelper"" ("<<(void*)obj<<")\n";
            }
        } );
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, helper, ISpriteCollideHelper);
        self->setCollisionHelper(helper);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::SetElasticity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(number elasticity)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""elasticity"")");
            return;
        }
        double elasticity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setElasticity(elasticity);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetElasticity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float elasticity = self->getElasticity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, elasticity) ); return; };
    }
#ifndef PDG_NO_GUI

    void SpriteWrap::SetWantsMouseOverEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsMouseOverEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetWantsClickEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "(boolean wantsThem = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""wantsThem"")");
            return;
        }
        bool wantsThem = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setWantsClickEvents(wantsThem);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::SetMouseDetectMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] collisionType = collide_BoundingBox)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""collisionType"")");
            return;
        }
        long collisionType = (args.Length()<1) ? Sprite::collide_BoundingBox : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->setMouseDetectMode(collisionType);
        { args.GetReturnValue().Set( args.This() ); return; };
    }
#endif

    void SpriteWrap::GetLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object SpriteLayer]" " function" "()" " - " "get the layer that contains this sprite").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        SpriteLayer* layer = self->getLayer();
        if (!layer) { args.GetReturnValue().SetNull(); return; };
        if (layer->mSpriteLayerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( SpriteLayerWrap::NewFromCpp(isolate, layer) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, layer->mSpriteLayerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }
#ifdef PDG_USE_CHIPMUNK_PHYSICS

    void SpriteWrap::MakeStatic(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->makeStatic();
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float friction = self->getFriction();
        { args.GetReturnValue().Set( v8::Number::New(isolate, friction) ); return; };
    }

    void SpriteWrap::SetCollideGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] group)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""group"")");
            return;
        }
        long group = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->setCollideGroup(group);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SpriteWrap::GetCollideGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        long group = self->getCollideGroup();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, group) ); return; };
    }

    void SpriteWrap::PinJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        }
        pdg::Offset anchor = v8_ValueToOffset(isolate, args[1 -1]);
        REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
        if (!v8_ValueIsOffset(isolate, args[3 -1]))
        {
            v8_ThrowArgTypeException(isolate, 3, "Offset", *args[3 -1]);
            return;
        }
        pdg::Offset otherAnchor = v8_ValueToOffset(isolate, args[3 -1]);
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<4) ? 0.0f : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->pinJoint(anchor, otherSprite, otherAnchor, breakingForce);
        cpConstraintSetUserData(joint, (void*)sPinJointStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::SlideJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number minDist, number maxDist, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 5)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 5, true);
            return;
        };
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        }
        pdg::Offset anchor = v8_ValueToOffset(isolate, args[1 -1]);
        REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
        if (!v8_ValueIsOffset(isolate, args[3 -1]))
        {
            v8_ThrowArgTypeException(isolate, 3, "Offset", *args[3 -1]);
            return;
        }
        pdg::Offset otherAnchor = v8_ValueToOffset(isolate, args[3 -1]);
        if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""minDist"")");
            return;
        }
        double minDist = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""maxDist"")");
            return;
        }
        double maxDist = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 6 && !args[6 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 6, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<6) ? 0.0f : args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->slideJoint(anchor, otherSprite, otherAnchor, minDist, maxDist, breakingForce);
        cpConstraintSetUserData(joint, (void*)sSlideJointStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::PivotJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, [object Point] pivot, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point pivot = v8_ValueToPoint(isolate, args[2 -1]);
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<3) ? 0.0f : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->pivotJoint(otherSprite, pivot, breakingForce);
        cpConstraintSetUserData(joint, (void*)sPivotJointStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::GrooveJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Offset] grooveStart, [object Offset] grooveEnd, [object Sprite] otherSprite, [object Offset] otherAnchor, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 4)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 4, true);
            return;
        };
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        }
        pdg::Offset grooveStart = v8_ValueToOffset(isolate, args[1 -1]);
        if (!v8_ValueIsOffset(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Offset", *args[2 -1]);
            return;
        }
        pdg::Offset grooveEnd = v8_ValueToOffset(isolate, args[2 -1]);
        REQUIRE_CPP_OBJECT_ARG(3, otherSprite, Sprite);
        if (!v8_ValueIsOffset(isolate, args[4 -1]))
        {
            v8_ThrowArgTypeException(isolate, 4, "Offset", *args[4 -1]);
            return;
        }
        pdg::Offset otherAnchor = v8_ValueToOffset(isolate, args[4 -1]);
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<5) ? 0.0f : args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->grooveJoint(grooveStart, grooveEnd, otherSprite, otherAnchor, breakingForce);
        cpConstraintSetUserData(joint, (void*)sGrooveJointStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::SpringJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Offset] anchor, [object Sprite] otherSprite, [object Offset] otherAnchor, number restLength, number stiffness, number damping, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 6)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 6, true);
            return;
        };
        if (!v8_ValueIsOffset(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
            return;
        }
        pdg::Offset anchor = v8_ValueToOffset(isolate, args[1 -1]);
        REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
        if (!v8_ValueIsOffset(isolate, args[3 -1]))
        {
            v8_ThrowArgTypeException(isolate, 3, "Offset", *args[3 -1]);
            return;
        }
        pdg::Offset otherAnchor = v8_ValueToOffset(isolate, args[3 -1]);
        if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""restLength"")");
            return;
        }
        double restLength = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""stiffness"")");
            return;
        }
        double stiffness = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[6 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 6, "a number (""damping"")");
            return;
        }
        double damping = args[6 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 7 && !args[7 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 7, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<7) ? 0.0f : args[7 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->springJoint(anchor, otherSprite, otherAnchor, restLength, stiffness, damping, breakingForce);
        cpConstraintSetUserData(joint, (void*)sSpringJointStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::RotarySpring(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, number restAngle, number stiffness, number damping, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 4)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 4, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""restAngle"")");
            return;
        }
        double restAngle = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""stiffness"")");
            return;
        }
        double stiffness = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""damping"")");
            return;
        }
        double damping = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<5) ? 0.0f : args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->rotarySpring(otherSprite, restAngle, stiffness, damping, breakingForce);
        cpConstraintSetUserData(joint, (void*)sRotarySpringStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::RotaryLimit(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, number minAngle, number maxAngle, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""minAngle"")");
            return;
        }
        double minAngle = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""maxAngle"")");
            return;
        }
        double maxAngle = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<4) ? 0.0f : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->rotaryLimit(otherSprite, minAngle, maxAngle, breakingForce);
        cpConstraintSetUserData(joint, (void*)sRotaryLimitStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::Ratchet(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, number rachetInterval, number phase, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""rachetInterval"")");
            return;
        }
        double rachetInterval = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""phase"")");
            return;
        }
        double phase = (args.Length()<3) ? 0.0f : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<4) ? 0.0f : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->ratchet(otherSprite, rachetInterval, phase, breakingForce);
        cpConstraintSetUserData(joint, (void*)sRatchetStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::Gear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, number gearRatio, number initialAngle = 0, number breakingForce = 0)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""gearRatio"")");
            return;
        }
        double gearRatio = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""initialAngle"")");
            return;
        }
        double initialAngle = (args.Length()<3) ? 0.0f : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = (args.Length()<4) ? 0.0f : args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->gear(otherSprite, gearRatio, initialAngle, breakingForce);
        cpConstraintSetUserData(joint, (void*)sGearStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::Motor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpConstraint]" " function" "([object Sprite] otherSprite, number spin, number maxTorque = INFINITY)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherSprite, Sprite);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""spin"")");
            return;
        }
        double spin = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""maxTorque"")");
            return;
        }
        double maxTorque = (args.Length()<3) ? std::numeric_limits<float>::infinity() : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        cpConstraint* joint = self->motor(otherSprite, spin, maxTorque);
        cpConstraintSetUserData(joint, (void*)sMotorStr);
        if (!joint) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpConstraintWrap::NewFromCpp(isolate, joint) ); return; };
        ;
    }

    void SpriteWrap::RemoveJoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object CpConstraint] joint)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
        self->removeJoint(joint);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::Disconnect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] otherSprite = ALL_SPRITES)" " - " "").ToLocalChecked() ); return; };
        };
        Sprite* otherSprite = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Sprite"" (""otherSprite"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> otherSprite_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                SpriteWrap* otherSprite__ = jswrap::ObjectWrap::Unwrap<SpriteWrap>(otherSprite_);
                otherSprite = otherSprite__->getCppObject();
            }
        };
        self->disconnect(otherSprite);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::MakeJointBreakable(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object CpConstraint] joint, number breakingForce)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""breakingForce"")");
            return;
        }
        double breakingForce = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->makeJointBreakable(joint, breakingForce);
        args.GetReturnValue().SetUndefined();
    }

    void SpriteWrap::MakeJointUnbreakable(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object CpConstraint] joint)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, joint, cpConstraint);
        self->makeJointUnbreakable(joint);
        args.GetReturnValue().SetUndefined();
    }
#endif

    void SpriteWrap::On(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "([number int] eventCode, function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""eventCode"")");
            return;
        }
        long eventCode = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 2, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[2 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        long evtCode;
        if (eventCode <= pdg::Sprite::action_CollideWall)
        {
            evtCode = pdg::eventType_SpriteCollide;
        }
        else if (eventCode <= pdg::Sprite::action_FadeOutComplete)
        {
            evtCode = pdg::eventType_SpriteAnimate;
        }
        else
        {
            evtCode = pdg::eventType_SpriteTouch;
        }
        self->addHandler(handler, evtCode);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnCollideSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler)
        {
            DEBUG_ONLY( OS::_DOUT("OnCollideSprite: failed to create handler"); )
                { args.GetReturnValue().SetNull(); return; };
        }
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnCollideWall(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteCollide);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnOffscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnOnscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnExitLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationLoop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptEventHandler* handler = new ScriptEventHandler(func);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnAnimationBlendComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationBlendComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeInComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnFadeOutComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteAnimate);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseEnter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseLeave(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void SpriteWrap::OnMouseClick(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object IEventHandler]" " function" "(function func)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""func"")");
            return;
        }
        v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(args[1 -1]);;
        ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteTouch);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        if (handler->mIEventHandlerScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( IEventHandlerWrap::NewFromCpp(isolate, handler) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, handler->mIEventHandlerScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

#ifdef PDG_SPRITER_SUPPORT

    void SpriteWrap::GetSpriterCollisionBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "(string boxName)" " - " "get a Spriter collision box by name").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""boxName"")");
            return;
        }
        v8::String::Utf8Value boxName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* boxName = *boxName_Str;;
        pdg::RotatedRect rect = self->getSpriterCollisionBox(boxName);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, rect) ); return; };
    }

    void SpriteWrap::IsSpriterCollisionActive(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string boxName)" " - " "check if a Spriter collision box is active").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""boxName"")");
            return;
        }
        v8::String::Utf8Value boxName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* boxName = *boxName_Str;;
        bool active = self->isSpriterCollisionActive(boxName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, active) ); return; };
    }

    void SpriteWrap::GetSpriterCollisionBoxCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "get the number of active Spriter collision boxes").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int count = self->getSpriterCollisionBoxCount();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, count) ); return; };
    }

    void SpriteWrap::GetSpriterCollisionBoxName(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SpriteWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SpriteWrap>(args.This());
        Sprite* self = dynamic_cast<Sprite*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "(number index)" " - " "get the name of a Spriter collision box by index").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
            return;
        }
        long index = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        const char* name = self->getSpriterCollisionBoxName(index);
        if (name)
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, name).ToLocalChecked() ); return; };
        }
        else
        {
            { args.GetReturnValue().SetNull(); return; };
        }
    }
#endif

    void CleanupSpriteScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    SpriteWrap::SpriteWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Sprite(args);
        if (!cppPtr_ && !s_Sprite_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Sprite" " instance")));
            };
        }
    }

    SpriteWrap::~SpriteWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Sprite* New_Sprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Sprite_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new Sprite();
    }

}
