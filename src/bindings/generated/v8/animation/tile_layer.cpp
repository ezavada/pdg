// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/tile_layer.cpp
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

    ;
    ;

    static bool s_TileLayer_InNewFromCpp = false;

    void TileLayerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_TileLayer_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "TileLayer" " cannot be instantiated with 'new'. Use the factory function: pdg." "createTileLayer" "()"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        TileLayerWrap* objWrapper = new TileLayerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Local<v8::Object> TileLayerWrap::NewFromCpp(v8::Isolate* isolate, TileLayer* cppObj)
    {
        s_TileLayer_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_TileLayer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_TileLayer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mEventEmitterScriptObj.Reset(isolate, obj); cppObj->mAnimatedScriptObj.Reset(isolate, obj); cppObj->mSpriteLayerScriptObj.Reset(isolate, obj); cppObj->mTileLayerScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_TileLayer_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> TileLayerWrap::constructorTpl_;

    void TileLayerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "TileLayer").ToLocalChecked();
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
        v8::Local<v8::Signature> SetSerializationFlags_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSerializationFlags_Tpl =
            v8::FunctionTemplate::New(isolate, SetSerializationFlags, v8::Local<v8::Value>(), SetSerializationFlags_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSerializationFlags").ToLocalChecked(), SetSerializationFlags_Tpl);
        v8::Local<v8::Signature> StartAnimations_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartAnimations_Tpl =
            v8::FunctionTemplate::New(isolate, StartAnimations, v8::Local<v8::Value>(), StartAnimations_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startAnimations").ToLocalChecked(), StartAnimations_Tpl);
        v8::Local<v8::Signature> StopAnimations_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopAnimations_Tpl =
            v8::FunctionTemplate::New(isolate, StopAnimations, v8::Local<v8::Value>(), StopAnimations_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopAnimations").ToLocalChecked(), StopAnimations_Tpl);
        v8::Local<v8::Signature> Hide_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Hide_Tpl =
            v8::FunctionTemplate::New(isolate, Hide, v8::Local<v8::Value>(), Hide_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hide").ToLocalChecked(), Hide_Tpl);
        v8::Local<v8::Signature> Show_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Show_Tpl =
            v8::FunctionTemplate::New(isolate, Show, v8::Local<v8::Value>(), Show_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "show").ToLocalChecked(), Show_Tpl);
        v8::Local<v8::Signature> IsHidden_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsHidden_Tpl =
            v8::FunctionTemplate::New(isolate, IsHidden, v8::Local<v8::Value>(), IsHidden_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isHidden").ToLocalChecked(), IsHidden_Tpl);
        v8::Local<v8::Signature> FadeIn_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeIn_Tpl =
            v8::FunctionTemplate::New(isolate, FadeIn, v8::Local<v8::Value>(), FadeIn_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeIn").ToLocalChecked(), FadeIn_Tpl);
        v8::Local<v8::Signature> FadeOut_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeOut_Tpl =
            v8::FunctionTemplate::New(isolate, FadeOut, v8::Local<v8::Value>(), FadeOut_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeOut").ToLocalChecked(), FadeOut_Tpl);
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
        v8::Local<v8::Signature> GetZOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetZOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetZOrder, v8::Local<v8::Value>(), GetZOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getZOrder").ToLocalChecked(), GetZOrder_Tpl);
        v8::Local<v8::Signature> MoveWith_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveWith_Tpl =
            v8::FunctionTemplate::New(isolate, MoveWith, v8::Local<v8::Value>(), MoveWith_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveWith").ToLocalChecked(), MoveWith_Tpl);
        v8::Local<v8::Signature> FindSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FindSprite_Tpl =
            v8::FunctionTemplate::New(isolate, FindSprite, v8::Local<v8::Value>(), FindSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "findSprite").ToLocalChecked(), FindSprite_Tpl);
        v8::Local<v8::Signature> GetNthSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNthSprite_Tpl =
            v8::FunctionTemplate::New(isolate, GetNthSprite, v8::Local<v8::Value>(), GetNthSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNthSprite").ToLocalChecked(), GetNthSprite_Tpl);
        v8::Local<v8::Signature> GetSpriteZOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpriteZOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpriteZOrder, v8::Local<v8::Value>(), GetSpriteZOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpriteZOrder").ToLocalChecked(), GetSpriteZOrder_Tpl);
        v8::Local<v8::Signature> IsSpriteBehind_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsSpriteBehind_Tpl =
            v8::FunctionTemplate::New(isolate, IsSpriteBehind, v8::Local<v8::Value>(), IsSpriteBehind_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isSpriteBehind").ToLocalChecked(), IsSpriteBehind_Tpl);
        v8::Local<v8::Signature> HasSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasSprite_Tpl =
            v8::FunctionTemplate::New(isolate, HasSprite, v8::Local<v8::Value>(), HasSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasSprite").ToLocalChecked(), HasSprite_Tpl);
        v8::Local<v8::Signature> AddSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddSprite_Tpl =
            v8::FunctionTemplate::New(isolate, AddSprite, v8::Local<v8::Value>(), AddSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addSprite").ToLocalChecked(), AddSprite_Tpl);
        v8::Local<v8::Signature> RemoveSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveSprite_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveSprite, v8::Local<v8::Value>(), RemoveSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeSprite").ToLocalChecked(), RemoveSprite_Tpl);
        v8::Local<v8::Signature> RemoveAllSprites_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAllSprites_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAllSprites, v8::Local<v8::Value>(), RemoveAllSprites_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAllSprites").ToLocalChecked(), RemoveAllSprites_Tpl);
        v8::Local<v8::Signature> EnableCollisions_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableCollisions_Tpl =
            v8::FunctionTemplate::New(isolate, EnableCollisions, v8::Local<v8::Value>(), EnableCollisions_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableCollisions").ToLocalChecked(), EnableCollisions_Tpl);
        v8::Local<v8::Signature> DisableCollisions_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisableCollisions_Tpl =
            v8::FunctionTemplate::New(isolate, DisableCollisions, v8::Local<v8::Value>(), DisableCollisions_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disableCollisions").ToLocalChecked(), DisableCollisions_Tpl);
        v8::Local<v8::Signature> EnableCollisionsWithLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> EnableCollisionsWithLayer_Tpl =
            v8::FunctionTemplate::New(isolate, EnableCollisionsWithLayer, v8::Local<v8::Value>(), EnableCollisionsWithLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "enableCollisionsWithLayer").ToLocalChecked(), EnableCollisionsWithLayer_Tpl);
        v8::Local<v8::Signature> DisableCollisionsWithLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DisableCollisionsWithLayer_Tpl =
            v8::FunctionTemplate::New(isolate, DisableCollisionsWithLayer, v8::Local<v8::Value>(), DisableCollisionsWithLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "disableCollisionsWithLayer").ToLocalChecked(), DisableCollisionsWithLayer_Tpl);
        v8::Local<v8::Signature> CreateSprite_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateSprite_Tpl =
            v8::FunctionTemplate::New(isolate, CreateSprite, v8::Local<v8::Value>(), CreateSprite_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createSprite").ToLocalChecked(), CreateSprite_Tpl);
#ifndef PDG_NO_GUI
        v8::Local<v8::Signature> GetSpritePort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpritePort_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpritePort, v8::Local<v8::Value>(), GetSpritePort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpritePort").ToLocalChecked(), GetSpritePort_Tpl);
        v8::Local<v8::Signature> SetSpritePort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSpritePort_Tpl =
            v8::FunctionTemplate::New(isolate, SetSpritePort, v8::Local<v8::Value>(), SetSpritePort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setSpritePort").ToLocalChecked(), SetSpritePort_Tpl);
        v8::Local<v8::Signature> SetOrigin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOrigin_Tpl =
            v8::FunctionTemplate::New(isolate, SetOrigin, v8::Local<v8::Value>(), SetOrigin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setOrigin").ToLocalChecked(), SetOrigin_Tpl);
        v8::Local<v8::Signature> GetOrigin_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOrigin_Tpl =
            v8::FunctionTemplate::New(isolate, GetOrigin, v8::Local<v8::Value>(), GetOrigin_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getOrigin").ToLocalChecked(), GetOrigin_Tpl);
        v8::Local<v8::Signature> SetAutoCenter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAutoCenter_Tpl =
            v8::FunctionTemplate::New(isolate, SetAutoCenter, v8::Local<v8::Value>(), SetAutoCenter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAutoCenter").ToLocalChecked(), SetAutoCenter_Tpl);
        v8::Local<v8::Signature> SetFixedMoveAxis_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFixedMoveAxis_Tpl =
            v8::FunctionTemplate::New(isolate, SetFixedMoveAxis, v8::Local<v8::Value>(), SetFixedMoveAxis_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFixedMoveAxis").ToLocalChecked(), SetFixedMoveAxis_Tpl);
        v8::Local<v8::Signature> SetZoom_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetZoom_Tpl =
            v8::FunctionTemplate::New(isolate, SetZoom, v8::Local<v8::Value>(), SetZoom_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setZoom").ToLocalChecked(), SetZoom_Tpl);
        v8::Local<v8::Signature> GetZoom_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetZoom_Tpl =
            v8::FunctionTemplate::New(isolate, GetZoom, v8::Local<v8::Value>(), GetZoom_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getZoom").ToLocalChecked(), GetZoom_Tpl);
        v8::Local<v8::Signature> ZoomTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ZoomTo_Tpl =
            v8::FunctionTemplate::New(isolate, ZoomTo, v8::Local<v8::Value>(), ZoomTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "zoomTo").ToLocalChecked(), ZoomTo_Tpl);
        v8::Local<v8::Signature> Zoom_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Zoom_Tpl =
            v8::FunctionTemplate::New(isolate, Zoom, v8::Local<v8::Value>(), Zoom_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "zoom").ToLocalChecked(), Zoom_Tpl);
        v8::Local<v8::Signature> LayerToPortPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LayerToPortPoint_Tpl =
            v8::FunctionTemplate::New(isolate, LayerToPortPoint, v8::Local<v8::Value>(), LayerToPortPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "layerToPortPoint").ToLocalChecked(), LayerToPortPoint_Tpl);
        v8::Local<v8::Signature> LayerToPortOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LayerToPortOffset_Tpl =
            v8::FunctionTemplate::New(isolate, LayerToPortOffset, v8::Local<v8::Value>(), LayerToPortOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "layerToPortOffset").ToLocalChecked(), LayerToPortOffset_Tpl);
        v8::Local<v8::Signature> LayerToPortVector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LayerToPortVector_Tpl =
            v8::FunctionTemplate::New(isolate, LayerToPortVector, v8::Local<v8::Value>(), LayerToPortVector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "layerToPortVector").ToLocalChecked(), LayerToPortVector_Tpl);
        v8::Local<v8::Signature> LayerToPortRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LayerToPortRect_Tpl =
            v8::FunctionTemplate::New(isolate, LayerToPortRect, v8::Local<v8::Value>(), LayerToPortRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "layerToPortRect").ToLocalChecked(), LayerToPortRect_Tpl);
        v8::Local<v8::Signature> LayerToPortQuad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LayerToPortQuad_Tpl =
            v8::FunctionTemplate::New(isolate, LayerToPortQuad, v8::Local<v8::Value>(), LayerToPortQuad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "layerToPortQuad").ToLocalChecked(), LayerToPortQuad_Tpl);
        v8::Local<v8::Signature> PortToLayerPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PortToLayerPoint_Tpl =
            v8::FunctionTemplate::New(isolate, PortToLayerPoint, v8::Local<v8::Value>(), PortToLayerPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "portToLayerPoint").ToLocalChecked(), PortToLayerPoint_Tpl);
        v8::Local<v8::Signature> PortToLayerOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PortToLayerOffset_Tpl =
            v8::FunctionTemplate::New(isolate, PortToLayerOffset, v8::Local<v8::Value>(), PortToLayerOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "portToLayerOffset").ToLocalChecked(), PortToLayerOffset_Tpl);
        v8::Local<v8::Signature> PortToLayerVector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PortToLayerVector_Tpl =
            v8::FunctionTemplate::New(isolate, PortToLayerVector, v8::Local<v8::Value>(), PortToLayerVector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "portToLayerVector").ToLocalChecked(), PortToLayerVector_Tpl);
        v8::Local<v8::Signature> PortToLayerRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PortToLayerRect_Tpl =
            v8::FunctionTemplate::New(isolate, PortToLayerRect, v8::Local<v8::Value>(), PortToLayerRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "portToLayerRect").ToLocalChecked(), PortToLayerRect_Tpl);
        v8::Local<v8::Signature> PortToLayerQuad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PortToLayerQuad_Tpl =
            v8::FunctionTemplate::New(isolate, PortToLayerQuad, v8::Local<v8::Value>(), PortToLayerQuad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "portToLayerQuad").ToLocalChecked(), PortToLayerQuad_Tpl);
#endif
#ifdef PDG_USE_CHIPMUNK_PHYSICS
        v8::Local<v8::Signature> SetGravity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetGravity_Tpl =
            v8::FunctionTemplate::New(isolate, SetGravity, v8::Local<v8::Value>(), SetGravity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setGravity").ToLocalChecked(), SetGravity_Tpl);
        v8::Local<v8::Signature> SetUseChipmunkPhysics_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetUseChipmunkPhysics_Tpl =
            v8::FunctionTemplate::New(isolate, SetUseChipmunkPhysics, v8::Local<v8::Value>(), SetUseChipmunkPhysics_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setUseChipmunkPhysics").ToLocalChecked(), SetUseChipmunkPhysics_Tpl);
        v8::Local<v8::Signature> SetStaticLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetStaticLayer_Tpl =
            v8::FunctionTemplate::New(isolate, SetStaticLayer, v8::Local<v8::Value>(), SetStaticLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setStaticLayer").ToLocalChecked(), SetStaticLayer_Tpl);
        v8::Local<v8::Signature> SetKeepGravityDownward_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetKeepGravityDownward_Tpl =
            v8::FunctionTemplate::New(isolate, SetKeepGravityDownward, v8::Local<v8::Value>(), SetKeepGravityDownward_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setKeepGravityDownward").ToLocalChecked(), SetKeepGravityDownward_Tpl);
        v8::Local<v8::Signature> SetDamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetDamping, v8::Local<v8::Value>(), SetDamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDamping").ToLocalChecked(), SetDamping_Tpl);
        v8::Local<v8::Signature> GetSpace_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSpace_Tpl =
            v8::FunctionTemplate::New(isolate, GetSpace, v8::Local<v8::Value>(), GetSpace_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSpace").ToLocalChecked(), GetSpace_Tpl);
#endif
        v8::Local<v8::Signature> SetWorldSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWorldSize_Tpl =
            v8::FunctionTemplate::New(isolate, SetWorldSize, v8::Local<v8::Value>(), SetWorldSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setWorldSize").ToLocalChecked(), SetWorldSize_Tpl);
        v8::Local<v8::Signature> GetWorldSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWorldSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetWorldSize, v8::Local<v8::Value>(), GetWorldSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWorldSize").ToLocalChecked(), GetWorldSize_Tpl);
        v8::Local<v8::Signature> GetWorldBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWorldBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetWorldBounds, v8::Local<v8::Value>(), GetWorldBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWorldBounds").ToLocalChecked(), GetWorldBounds_Tpl);
        v8::Local<v8::Signature> DefineTileSet_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DefineTileSet_Tpl =
            v8::FunctionTemplate::New(isolate, DefineTileSet, v8::Local<v8::Value>(), DefineTileSet_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "defineTileSet").ToLocalChecked(), DefineTileSet_Tpl);
        v8::Local<v8::Signature> LoadMapData_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LoadMapData_Tpl =
            v8::FunctionTemplate::New(isolate, LoadMapData, v8::Local<v8::Value>(), LoadMapData_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "loadMapData").ToLocalChecked(), LoadMapData_Tpl);
        v8::Local<v8::Signature> GetMapData_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMapData_Tpl =
            v8::FunctionTemplate::New(isolate, GetMapData, v8::Local<v8::Value>(), GetMapData_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMapData").ToLocalChecked(), GetMapData_Tpl);
        v8::Local<v8::Signature> GetTileSetImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTileSetImage_Tpl =
            v8::FunctionTemplate::New(isolate, GetTileSetImage, v8::Local<v8::Value>(), GetTileSetImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTileSetImage").ToLocalChecked(), GetTileSetImage_Tpl);
        v8::Local<v8::Signature> GetTileSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTileSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetTileSize, v8::Local<v8::Value>(), GetTileSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTileSize").ToLocalChecked(), GetTileSize_Tpl);
        v8::Local<v8::Signature> GetTileTypeAt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTileTypeAt_Tpl =
            v8::FunctionTemplate::New(isolate, GetTileTypeAt, v8::Local<v8::Value>(), GetTileTypeAt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTileTypeAt").ToLocalChecked(), GetTileTypeAt_Tpl);
        v8::Local<v8::Signature> GetTileTypeAndFacingAt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTileTypeAndFacingAt_Tpl =
            v8::FunctionTemplate::New(isolate, GetTileTypeAndFacingAt, v8::Local<v8::Value>(), GetTileTypeAndFacingAt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTileTypeAndFacingAt").ToLocalChecked(), GetTileTypeAndFacingAt_Tpl);
        v8::Local<v8::Signature> SetTileTypeAt_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTileTypeAt_Tpl =
            v8::FunctionTemplate::New(isolate, SetTileTypeAt, v8::Local<v8::Value>(), SetTileTypeAt_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setTileTypeAt").ToLocalChecked(), SetTileTypeAt_Tpl);
        v8::Local<v8::Signature> CheckCollision_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CheckCollision_Tpl =
            v8::FunctionTemplate::New(isolate, CheckCollision, v8::Local<v8::Value>(), CheckCollision_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "checkCollision").ToLocalChecked(), CheckCollision_Tpl);
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
        v8::Local<v8::Signature> OnErasePort_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnErasePort_Tpl =
            v8::FunctionTemplate::New(isolate, OnErasePort, v8::Local<v8::Value>(), OnErasePort_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onErasePort").ToLocalChecked(), OnErasePort_Tpl);
        v8::Local<v8::Signature> OnPreDrawLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnPreDrawLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnPreDrawLayer, v8::Local<v8::Value>(), OnPreDrawLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onPreDrawLayer").ToLocalChecked(), OnPreDrawLayer_Tpl);
        v8::Local<v8::Signature> OnPostDrawLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnPostDrawLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnPostDrawLayer, v8::Local<v8::Value>(), OnPostDrawLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onPostDrawLayer").ToLocalChecked(), OnPostDrawLayer_Tpl);
        v8::Local<v8::Signature> OnDrawPortComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnDrawPortComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnDrawPortComplete, v8::Local<v8::Value>(), OnDrawPortComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onDrawPortComplete").ToLocalChecked(), OnDrawPortComplete_Tpl);
        v8::Local<v8::Signature> OnAnimationStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationStart_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationStart, v8::Local<v8::Value>(), OnAnimationStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationStart").ToLocalChecked(), OnAnimationStart_Tpl);
        v8::Local<v8::Signature> OnPreAnimateLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnPreAnimateLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnPreAnimateLayer, v8::Local<v8::Value>(), OnPreAnimateLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onPreAnimateLayer").ToLocalChecked(), OnPreAnimateLayer_Tpl);
        v8::Local<v8::Signature> OnPostAnimateLayer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnPostAnimateLayer_Tpl =
            v8::FunctionTemplate::New(isolate, OnPostAnimateLayer, v8::Local<v8::Value>(), OnPostAnimateLayer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onPostAnimateLayer").ToLocalChecked(), OnPostAnimateLayer_Tpl);
        v8::Local<v8::Signature> OnAnimationComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnAnimationComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnAnimationComplete, v8::Local<v8::Value>(), OnAnimationComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onAnimationComplete").ToLocalChecked(), OnAnimationComplete_Tpl);
        v8::Local<v8::Signature> OnZoomComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnZoomComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnZoomComplete, v8::Local<v8::Value>(), OnZoomComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onZoomComplete").ToLocalChecked(), OnZoomComplete_Tpl);
        v8::Local<v8::Signature> OnLayerFadeInComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnLayerFadeInComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnLayerFadeInComplete, v8::Local<v8::Value>(), OnLayerFadeInComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onLayerFadeInComplete").ToLocalChecked(), OnLayerFadeInComplete_Tpl);
        v8::Local<v8::Signature> OnLayerFadeOutComplete_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OnLayerFadeOutComplete_Tpl =
            v8::FunctionTemplate::New(isolate, OnLayerFadeOutComplete, v8::Local<v8::Value>(), OnLayerFadeOutComplete_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "onLayerFadeOutComplete").ToLocalChecked(), OnLayerFadeOutComplete_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void TileLayerWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
            std::cerr << __func__<<":"<< 96 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 96 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 96 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 96 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 96 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void TileLayerWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::GetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "([object Point] inLocation)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetSpeed(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inSpeed)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inWidth)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inHeight)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::SetFlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(boolean inFlipX)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::SetFlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(boolean inFlipY)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inRotation)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetCenterOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "([object Offset] inCenterOffset)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetSpin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inSpin)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetMass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inMass)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetMoveFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inMoveFriction)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetSpinFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inSpinFriction)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetSizeFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object TileLayer]" " function" "(number inSizeFriction)").ToLocalChecked() ); return; };
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

    void TileLayerWrap::GetBoundingBox(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::GetRotatedBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Move(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetVelocityInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::GetMovementDirectionInRadians(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::GetVelocity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StopMoving(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Accelerate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::AccelerateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Grow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Stretch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StartGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StopGrowing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StartStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StopStretching(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Resize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ResizeTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::FlipX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::FlipY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::IsFlippedX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::IsFlippedY(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Rotate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::RotateTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StopSpinning(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ChangeCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ChangeCenterTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::Wait(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::SetFriction(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ApplyForce(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ApplyTorque(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::StopAllForces(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::AddAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object IAnimationHelper] helper)" " - " "").ToLocalChecked() ); return; };
        };
        self->mAnimatedScriptObj.Reset(isolate, args.This());
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 97 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 97 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 97 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IAnimationHelper""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 97 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IAnimationHelper""\n";
                }
            }
            else
            {
                IAnimationHelper* obj = dynamic_cast<IAnimationHelper*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 97 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IAnimationHelper"" ("<<(void*)obj<<")\n";
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

    void TileLayerWrap::RemoveAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::ClearAnimationHelpers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

#ifndef PDG_NO_GUI

    void TileLayerWrap::GetSpritePort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Port]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Port* port = self->getSpritePort();
        if (!port) { args.GetReturnValue().SetNull(); return; };
        if (port->mPortScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( PortWrap::NewFromCpp(isolate, port) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, port->mPortScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void TileLayerWrap::SetSpritePort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Port] port)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, port, Port);
        self->setSpritePort(port);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetOrigin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] origin)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point origin = v8_ValueToPoint(isolate, args[1 -1]);
        self->setOrigin(origin);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::GetOrigin(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()" " - " "get the point in the layer that is drawn at 0,0 in the port").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point p = self->getOrigin();
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, p) ); return; };
    }

    void TileLayerWrap::SetAutoCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean autoCenter = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""autoCenter"")");
            return;
        }
        bool autoCenter = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setAutoCenter(autoCenter);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetFixedMoveAxis(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean fixedAxis = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""fixedAxis"")");
            return;
        }
        bool fixedAxis = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setFixedMoveAxis(fixedAxis);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetZoom(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number zoomLevel)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""zoomLevel"")");
            return;
        }
        double zoomLevel = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setZoom(zoomLevel);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::GetZoom(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "get the current zoom factor").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float zoom = self->getZoom();
        { args.GetReturnValue().Set( v8::Number::New(isolate, zoom) ); return; };
    }

    void TileLayerWrap::ZoomTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number zoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""zoomLevel"")");
            return;
        }
        double zoomLevel = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
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
        long easing = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !v8_ValueIsRect(isolate, args[4 -1]))
        {
            v8_ThrowArgTypeException(isolate, 4, "Rect", *args[4 -1]);
            return;
        }
        pdg::Rect keepInRect = (args.Length()<4) ? pdg::Rect(0,0) : v8_ValueToRect(isolate, args[4 -1]);
        if (args.Length() >= 5 && !v8_ValueIsPoint(isolate, args[5 -1]))
        {
            v8_ThrowArgTypeException(isolate, 5, "Point", *args[5 -1]);
            return;
        }
        pdg::Point centerOn = (args.Length()<5) ? pdg::Point(0,0) : v8_ValueToPoint(isolate, args[5 -1]);
        pdg::Point* centerOnPtr = (args.Length() >= 5) ? &centerOn : 0;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->zoomTo(zoomLevel, msDuration, gEasingFunctions[easing], keepInRect, centerOnPtr);
        }
        else
        {
            self->zoomTo(zoomLevel, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void TileLayerWrap::Zoom(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number deltaZoomLevel, [number int] msDuration, [number int] easing = easeInOutQuad, [object Rect] keepInRect = Rect(0,0), [object Point] centerOn = Point(0,0) )" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""deltaZoomLevel"")");
            return;
        }
        double deltaZoomLevel = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
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
        long easing = (args.Length()<3) ? EasingFuncRef::easeInOutQuad : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !v8_ValueIsRect(isolate, args[4 -1]))
        {
            v8_ThrowArgTypeException(isolate, 4, "Rect", *args[4 -1]);
            return;
        }
        pdg::Rect keepInRect = (args.Length()<4) ? pdg::Rect(0,0) : v8_ValueToRect(isolate, args[4 -1]);
        if (args.Length() >= 5 && !v8_ValueIsPoint(isolate, args[5 -1]))
        {
            v8_ThrowArgTypeException(isolate, 5, "Point", *args[5 -1]);
            return;
        }
        pdg::Point centerOn = (args.Length()<5) ? pdg::Point(0,0) : v8_ValueToPoint(isolate, args[5 -1]);
        pdg::Point* centerOnPtr = (args.Length() >= 5) ? &centerOn : 0;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->zoom(deltaZoomLevel, msDuration, gEasingFunctions[easing], keepInRect, centerOnPtr);
        }
        else
        {
            self->zoom(deltaZoomLevel, msDuration);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void TileLayerWrap::LayerToPortPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([object Point] p)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
        Point out = self->layerToPort(p);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, out) ); return; };
    }

    void TileLayerWrap::LayerToPortOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "([object Offset] o)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Offset o = v8_ValueToOffset(isolate, args[1 -1]);
        Offset out = self->layerToPort(o);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, out) ); return; };
    }

    void TileLayerWrap::LayerToPortVector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Vector]" " function" "([object Vector] v)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsVector(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
            return;
        }
        pdg::Vector v = v8_ValueToVector(isolate, args[1 -1]);
        Vector out = self->layerToPort(v);
        { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, out) ); return; };
    }

    void TileLayerWrap::LayerToPortRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "([object Rect] r)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsRotatedRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *args[1 -1]);
            return;
        }
        pdg::RotatedRect r = v8_ValueToRotatedRect(isolate, args[1 -1]);
        RotatedRect out = self->layerToPort(r);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, out) ); return; };
    }

    void TileLayerWrap::LayerToPortQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Quad]" " function" "([object Quad] q)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsQuad(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
            return;
        }
        pdg::Quad q = v8_ValueToQuad(isolate, args[1 -1]);
        Quad out = self->layerToPort(q);
        { args.GetReturnValue().Set( v8_MakeJavascriptQuad(isolate, out) ); return; };
    }

    void TileLayerWrap::PortToLayerPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([object Point] p)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
        Point out = self->portToLayer(p);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, out) ); return; };
    }

    void TileLayerWrap::PortToLayerOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "([object Offset] o)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Offset o = v8_ValueToOffset(isolate, args[1 -1]);
        Offset out = self->portToLayer(o);
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, out) ); return; };
    }

    void TileLayerWrap::PortToLayerVector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Vector]" " function" "([object Vector] v)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsVector(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
            return;
        }
        pdg::Vector v = v8_ValueToVector(isolate, args[1 -1]);
        Vector out = self->portToLayer(v);
        { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, out) ); return; };
    }

    void TileLayerWrap::PortToLayerRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "([object Rect] r)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsRotatedRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *args[1 -1]);
            return;
        }
        pdg::RotatedRect r = v8_ValueToRotatedRect(isolate, args[1 -1]);
        RotatedRect out = self->portToLayer(r);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, out) ); return; };
    }

    void TileLayerWrap::PortToLayerQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Quad]" " function" "([object Quad] q)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsQuad(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
            return;
        }
        pdg::Quad q = v8_ValueToQuad(isolate, args[1 -1]);
        Quad out = self->portToLayer(q);
        { args.GetReturnValue().Set( v8_MakeJavascriptQuad(isolate, out) ); return; };
    }
#endif

    void TileLayerWrap::SetSerializationFlags(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object SpriteLayer]" " function" "([number uint] flags)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""flags"")");
            return;
        }
        unsigned long flags = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        self->setSerializationFlags(flags);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void TileLayerWrap::StartAnimations(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->startAnimations();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::StopAnimations(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stopAnimations();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::Hide(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->hide();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::Show(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->show();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::IsHidden(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool hidden = self->isHidden();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, hidden) ); return; };
    }

    void TileLayerWrap::FadeIn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void TileLayerWrap::FadeOut(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void TileLayerWrap::MoveBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object SpriteLayer] layer)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer);
        self->moveBehind(layer);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::MoveInFrontOf(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object SpriteLayer] layer)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer);
        self->moveInFrontOf(layer);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::MoveToFront(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "move this layer in front of all other layers").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToFront();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::MoveToBack(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "move this layer behind all other layers").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToBack();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::MoveWith(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object SpriteLayer] layer, number moveRatio = 1.0, number zoomRatio = 1.0 )" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""moveRatio"")");
            return;
        }
        double moveRatio = (args.Length()<2) ? 1.0f : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""zoomRatio"")");
            return;
        }
        double zoomRatio = (args.Length()<3) ? 1.0f : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        self->moveWith(layer, moveRatio, zoomRatio);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::IsSpriteBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([object Sprite] sprite, [object Sprite] otherSprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        REQUIRE_CPP_OBJECT_ARG(2, otherSprite, Sprite);
        bool behind = self->isSpriteBehind(sprite, otherSprite);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, behind) ); return; };
    }

    void TileLayerWrap::GetZOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::GetSpriteZOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number int]" " function" "([object Sprite] sprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, sprite, Sprite);
        int zorder = self->getSpriteZOrder(sprite);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, zorder) ); return; };
    }

    void TileLayerWrap::FindSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        Sprite* sprite = self->findSprite(id);
        if (!sprite) { args.GetReturnValue().SetNull(); return; };
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

    void TileLayerWrap::GetNthSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "([number int] index)" " - " "").ToLocalChecked() ); return; };
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
        Sprite* sprite = self->getNthSprite(index);
        if (!sprite) { args.GetReturnValue().SetNull(); return; };
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

    void TileLayerWrap::HasSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        bool found = self->hasSprite(sprite);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, found) ); return; };
    }

    void TileLayerWrap::AddSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] newSprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, newSprite, Sprite);
        self->addSprite(newSprite);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::RemoveSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Sprite] oldSprite)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, oldSprite, Sprite);
        self->removeSprite(oldSprite);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::RemoveAllSprites(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->removeAllSprites();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::EnableCollisions(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->enableCollisions();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::DisableCollisions(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->disableCollisions();
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::EnableCollisionsWithLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object SpriteLayer] otherLayer)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherLayer, SpriteLayer);
        self->enableCollisionsWithLayer(otherLayer);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::DisableCollisionsWithLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object SpriteLayer] otherLayer)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, otherLayer, SpriteLayer);
        self->disableCollisionsWithLayer(otherLayer);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::CreateSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sprite]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Sprite* sprite = self->createSprite();
        if (!sprite) { args.GetReturnValue().SetNull(); return; };
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

#ifdef PDG_USE_CHIPMUNK_PHYSICS

    void TileLayerWrap::SetKeepGravityDownward(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean keepItDownward = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""keepItDownward"")");
            return;
        }
        bool keepItDownward = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setKeepGravityDownward(keepItDownward);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetGravity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number gravity, boolean keepItDownward = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""gravity"")");
            return;
        }
        double gravity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""keepItDownward"")");
            return;
        }
        bool keepItDownward = (args.Length()<2) ? true : args[2 -1]->BooleanValue(isolate);;
        self->setGravity(gravity, keepItDownward);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number damping)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""damping"")");
            return;
        }
        double damping = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setDamping(damping);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetStaticLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean isStatic = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""isStatic"")");
            return;
        }
        bool isStatic = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setStaticLayer(isStatic);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::SetUseChipmunkPhysics(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean useIt = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""useIt"")");
            return;
        }
        bool useIt = (args.Length()<1) ? true : args[1 -1]->BooleanValue(isolate);;
        self->setUseChipmunkPhysics(useIt);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::GetSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object CpSpace]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        cpSpace* space = self->getSpace();
        if (!space) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( cpSpaceWrap::NewFromCpp(isolate, space) ); return; };
        ;
    }
#endif

    void TileLayerWrap::SetWorldSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] width, [number int] height, boolean repeatingX = false, boolean repeatingY = false)" " - " "").ToLocalChecked() ); return; };
        };
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
        long width = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""height"")");
            return;
        }
        long height = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""repeatingX"")");
            return;
        }
        bool repeatingX = (args.Length()<3) ? false : args[3 -1]->BooleanValue(isolate);;
        if (args.Length() >= 4 && !args[4 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 4, "a boolean (""repeatingY"")");
            return;
        }
        bool repeatingY = (args.Length()<4) ? false : args[4 -1]->BooleanValue(isolate);;
        self->setWorldSize(width, height, repeatingX, repeatingY);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::GetWorldSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect r = self->getWorldSize();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void TileLayerWrap::GetWorldBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect r = self->getWorldBounds();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void TileLayerWrap::GetTileTypeAt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([number int] x, [number int] y)" " - " "").ToLocalChecked() ); return; };
        };
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
        long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
            return;
        }
        long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        uint8 tileType;
        tileType = self->getTileTypeAt(x, y);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, tileType) ); return; };
    }

    void TileLayerWrap::GetTileTypeAndFacingAt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "([number int] x, [number int] y)" " - " "").ToLocalChecked() ); return; };
        };
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
        long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
            return;
        }
        long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        uint8 tileType;
        TileLayer::TFacing facing;
        tileType = self->getTileTypeAt(x, y, &facing);
        if (self->mUseFacing || self->mUseFlipping)
        {
            if (self->mUseFlipping && (!self->mFlipHoriz || !self->mFlipVert))
            {
                tileType &= 0x7f;
            }
            else
            {
                tileType &= 0x3f;
            }
        }
        v8::Local<v8::Object> tileInfo = v8_ObjectCreateEmpty(isolate, 0);
        (void)tileInfo->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "tileType").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, tileType)).ToChecked();
        (void)tileInfo->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "facing").ToLocalChecked(), v8::Integer::NewFromUnsigned(isolate, facing)).ToChecked();
        { args.GetReturnValue().Set( tileInfo ); return; };
    }

    void TileLayerWrap::DefineTileSet(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] tileWidth, [number int] tileHeight, [object Image] tiles, boolean hasTransparency = true, boolean flipTiles = false)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""tileWidth"")");
            return;
        }
        long tileWidth = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""tileHeight"")");
            return;
        }
        long tileHeight = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_CPP_OBJECT_ARG(3, tiles, Image);
        if (args.Length() >= 4 && !args[4 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 4, "a boolean (""hasTransparency"")");
            return;
        }
        bool hasTransparency = (args.Length()<4) ? true : args[4 -1]->BooleanValue(isolate);;
        if (args.Length() >= 5 && !args[5 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 5, "a boolean (""flipTiles"")");
            return;
        }
        bool flipTiles = (args.Length()<5) ? false : args[5 -1]->BooleanValue(isolate);;
        self->defineTileSet(tileWidth, tileHeight, tiles, hasTransparency, flipTiles);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::LoadMapData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({[string Binary]|[object MemBlock]} data, [number int] mapWidth = 0, [number int] mapHeight = 0, [number int] dstX, [number int] dstY)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""mapWidth"")");
            return;
        }
        long mapWidth = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""mapHeight"")");
            return;
        }
        long mapHeight = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""dstX"")");
            return;
        }
        long dstX = (args.Length()<4) ? 0 : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""dstY"")");
            return;
        }
        long dstY = (args.Length()<5) ? 0 : args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (mapWidth > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 2 (mapWidth) is larger than world width";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if ((mapWidth + dstX) > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "mapWidth + dstX is larger than world width";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if (mapHeight > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 3 (mapHeight) is larger than world height";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if ((mapHeight + dstY) > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "mapHeight + dstY is larger than world height";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if (!args[0]->IsString() && !(dynamic_cast<MemBlockWrap*>(pdg::v8script::safe_unwrap_object_wrap_or_prototype(isolate, args[0])) != 0))
        {
            std::ostringstream excpt_;
            excpt_ << "argument 1 (data) must be either a binary string or an object of type MemBlock";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if (args[0]->IsString())
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(args[0], &bytes);
            if (bytes < ((size_t)mapWidth * (size_t)mapHeight))
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }())));
            }
            self->loadMapData(ptr, mapWidth, mapHeight, dstX, dstY);
            std::free(ptr);
        }
        else
        {
            REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
            if (memBlock->bytes < ((size_t)mapWidth * (size_t)mapHeight))
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size";
                isolate->ThrowException( v8::Exception::RangeError( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }())));
            }
            self->loadMapData((uint8*)memBlock->ptr, mapWidth, mapHeight, dstX, dstY);
        }
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::GetMapData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object MemBlock]" " function" "([number int] mapWidth = 0, [number int] mapHeight = 0, [number int] srcX, [number int] srcY)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""mapWidth"")");
            return;
        }
        long mapWidth = (args.Length()<1) ? self->mWorldWidth : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""mapHeight"")");
            return;
        }
        long mapHeight = (args.Length()<2) ? self->mWorldHeight : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""srcX"")");
            return;
        }
        long srcX = (args.Length()<3) ? 0 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""srcY"")");
            return;
        }
        long srcY = (args.Length()<4) ? 0 : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (mapWidth > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 1 (mapWidth) is larger than world width";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if ((mapWidth + srcX) > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "mapWidth + srcX is larger than world width";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if (mapHeight > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 2 (mapHeight) is larger than world height";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        if ((mapHeight + srcY) > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "mapHeight + srcY is larger than world height";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        const uint8* dataPtr = self->getMapData(mapWidth, mapHeight, srcX, srcY);
        size_t bufferSize = mapWidth * mapHeight;
        uint8* ptr = (uint8*) std::malloc(bufferSize);
        std::memcpy(ptr, dataPtr, bufferSize);
        MemBlock* memBlock = new MemBlock((char*)ptr, bufferSize, true);
        if (!memBlock) { args.GetReturnValue().SetNull(); return; };
        if (memBlock->mMemBlockScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( MemBlockWrap::NewFromCpp(isolate, memBlock) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, memBlock->mMemBlockScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void TileLayerWrap::GetTileSetImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Image]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Image* tiles = self->getTileSetImage();
        if (!tiles) { args.GetReturnValue().SetNull(); return; };
        if (tiles->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, tiles) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, tiles->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void TileLayerWrap::GetTileSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point size = self->getTileSize();
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, size) ); return; };
    }

    void TileLayerWrap::SetTileTypeAt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] x, [number int] y, [number uint] t, [number uint] facing = facing_Ignore)" " - " "").ToLocalChecked() ); return; };
        };
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
        long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
            return;
        }
        long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""t"")");
            return;
        }
        unsigned long t = args[3 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""facing"")");
            return;
        }
        unsigned long facing = (args.Length()<4) ? (uint32) TileLayer::facing_Ignore : args[4 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;
        self->setTileTypeAt(x, y, t, (TileLayer::TFacing) facing);
        args.GetReturnValue().SetUndefined();
    }

    void TileLayerWrap::CheckCollision(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([object Sprite] movingSprite, [number uint] alphaThreshold = 128, boolean shortCircuit = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, movingSprite, Sprite);
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""alphaThreshold"")");
            return;
        }
        unsigned long alphaThreshold = (args.Length()<2) ? 128 : args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""shortCircuit"")");
            return;
        }
        bool shortCircuit = (args.Length()<3) ? true : args[3 -1]->BooleanValue(isolate);;
        uint32 overlapPx = self->checkCollision(movingSprite, alphaThreshold, shortCircuit);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, overlapPx) ); return; };
    }

    void TileLayerWrap::On(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        else if (eventCode <= pdg::TileLayer::action_FadeOutComplete)
        {
            evtCode = pdg::eventType_SpriteAnimate;
        }
        else if (eventCode >= pdg::TileLayer::action_ErasePort)
        {
            evtCode = pdg::eventType_SpriteLayer;
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

    void TileLayerWrap::OnCollideSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnCollideWall(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnOffscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnOnscreen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnExitLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnAnimationLoop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnAnimationEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnFadeComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnFadeInComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnFadeOutComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnMouseEnter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnMouseLeave(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnMouseDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnMouseUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnMouseClick(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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

    void TileLayerWrap::OnErasePort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ErasePort);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnPreDrawLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreDrawLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnPostDrawLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostDrawLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnDrawPortComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_DrawPortComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnAnimationStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationStart);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnPreAnimateLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreAnimateLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnPostAnimateLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostAnimateLayer);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnAnimationComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnZoomComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ZoomComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnLayerFadeInComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeInComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void TileLayerWrap::OnLayerFadeOutComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self = dynamic_cast<TileLayer*>(objWrapper->cppPtr_);

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
        ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeOutComplete);
        if (!handler) { args.GetReturnValue().SetNull(); return; };
        self->addHandler(handler, pdg::eventType_SpriteLayer);
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

    void CleanupTileLayerScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    TileLayerWrap::TileLayerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_TileLayer(args);
        if (!cppPtr_ && !s_TileLayer_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "TileLayer" " instance")));
            };
        }
    }

    TileLayerWrap::~TileLayerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    TileLayer* New_TileLayer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_TileLayer_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new TileLayer();
    }

}
