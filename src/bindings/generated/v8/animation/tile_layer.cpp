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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();

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
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            cppObj->mEventEmitterScriptObj.Reset(isolate, obj); cppObj->mSpriteLayerScriptObj.Reset(isolate, obj); cppObj->mTileLayerScriptObj.Reset(isolate, obj);
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
        v8::Local<v8::Signature> SetQueryBits_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetQueryBits_Tpl =
            v8::FunctionTemplate::New(isolate, SetQueryBits, v8::Local<v8::Value>(), SetQueryBits_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setQueryBits").ToLocalChecked(), SetQueryBits_Tpl);
        v8::Local<v8::Signature> GetQueryBits_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetQueryBits_Tpl =
            v8::FunctionTemplate::New(isolate, GetQueryBits, v8::Local<v8::Value>(), GetQueryBits_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getQueryBits").ToLocalChecked(), GetQueryBits_Tpl);
        v8::Local<v8::Signature> SetCamera_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCamera_Tpl =
            v8::FunctionTemplate::New(isolate, SetCamera, v8::Local<v8::Value>(), SetCamera_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCamera").ToLocalChecked(), SetCamera_Tpl);
        v8::Local<v8::Signature> GetCamera_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCamera_Tpl =
            v8::FunctionTemplate::New(isolate, GetCamera, v8::Local<v8::Value>(), GetCamera_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCamera").ToLocalChecked(), GetCamera_Tpl);
        v8::Local<v8::Signature> GetEffectiveCamera_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetEffectiveCamera_Tpl =
            v8::FunctionTemplate::New(isolate, GetEffectiveCamera, v8::Local<v8::Value>(), GetEffectiveCamera_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getEffectiveCamera").ToLocalChecked(), GetEffectiveCamera_Tpl);
        v8::Local<v8::Signature> SetCameraParallax_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCameraParallax_Tpl =
            v8::FunctionTemplate::New(isolate, SetCameraParallax, v8::Local<v8::Value>(), SetCameraParallax_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setCameraParallax").ToLocalChecked(), SetCameraParallax_Tpl);
        v8::Local<v8::Signature> GetWorldBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWorldBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetWorldBounds, v8::Local<v8::Value>(), GetWorldBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""WorldBounds").ToLocalChecked(), GetWorldBounds_Tpl);
        v8::Local<v8::Signature> SetWorldBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetWorldBounds_Tpl =
            v8::FunctionTemplate::New(isolate, SetWorldBounds, v8::Local<v8::Value>(), SetWorldBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""WorldBounds").ToLocalChecked(), SetWorldBounds_Tpl);
        v8::Local<v8::Signature> CreateParticle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateParticle_Tpl =
            v8::FunctionTemplate::New(isolate, CreateParticle, v8::Local<v8::Value>(), CreateParticle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createParticle").ToLocalChecked(), CreateParticle_Tpl);
        v8::Local<v8::Signature> AddParticle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddParticle_Tpl =
            v8::FunctionTemplate::New(isolate, AddParticle, v8::Local<v8::Value>(), AddParticle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addParticle").ToLocalChecked(), AddParticle_Tpl);
        v8::Local<v8::Signature> RemoveParticle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveParticle_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveParticle, v8::Local<v8::Value>(), RemoveParticle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeParticle").ToLocalChecked(), RemoveParticle_Tpl);
        v8::Local<v8::Signature> RemoveAllParticles_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAllParticles_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAllParticles, v8::Local<v8::Value>(), RemoveAllParticles_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAllParticles").ToLocalChecked(), RemoveAllParticles_Tpl);
        v8::Local<v8::Signature> GetParticleTrailCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetParticleTrailCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetParticleTrailCount, v8::Local<v8::Value>(), GetParticleTrailCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getParticleTrailCount").ToLocalChecked(), GetParticleTrailCount_Tpl);
        v8::Local<v8::Signature> GetParticleCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetParticleCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetParticleCount, v8::Local<v8::Value>(), GetParticleCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getParticleCount").ToLocalChecked(), GetParticleCount_Tpl);
        v8::Local<v8::Signature> GetNthParticle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNthParticle_Tpl =
            v8::FunctionTemplate::New(isolate, GetNthParticle, v8::Local<v8::Value>(), GetNthParticle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getNthParticle").ToLocalChecked(), GetNthParticle_Tpl);
        v8::Local<v8::Signature> SetMaxParticles_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMaxParticles_Tpl =
            v8::FunctionTemplate::New(isolate, SetMaxParticles, v8::Local<v8::Value>(), SetMaxParticles_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMaxParticles").ToLocalChecked(), SetMaxParticles_Tpl);
        v8::Local<v8::Signature> GetMaxParticles_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxParticles_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxParticles, v8::Local<v8::Value>(), GetMaxParticles_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMaxParticles").ToLocalChecked(), GetMaxParticles_Tpl);
        v8::Local<v8::Signature> CreateParticleEmitter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CreateParticleEmitter_Tpl =
            v8::FunctionTemplate::New(isolate, CreateParticleEmitter, v8::Local<v8::Value>(), CreateParticleEmitter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "createParticleEmitter").ToLocalChecked(), CreateParticleEmitter_Tpl);
        v8::Local<v8::Signature> RemoveParticleEmitter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveParticleEmitter_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveParticleEmitter, v8::Local<v8::Value>(), RemoveParticleEmitter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeParticleEmitter").ToLocalChecked(), RemoveParticleEmitter_Tpl);
        v8::Local<v8::Signature> RemoveAllParticleEmitters_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemoveAllParticleEmitters_Tpl =
            v8::FunctionTemplate::New(isolate, RemoveAllParticleEmitters, v8::Local<v8::Value>(), RemoveAllParticleEmitters_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removeAllParticleEmitters").ToLocalChecked(), RemoveAllParticleEmitters_Tpl);
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 69 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 69 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 69 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 69 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 69 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
    void TileLayerWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
    void TileLayerWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
#ifndef PDG_NO_GUI

    void TileLayerWrap::GetSpritePort(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, port, Port);
        self->setSpritePort(port);
        args.GetReturnValue().SetUndefined();
    }
    void TileLayerWrap::LayerToPortPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Point p;
            auto p_isPoint = v8_ValueIsPoint(isolate, args[1 -1], p);
            if (!p_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*p_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            Point out = self->layerToPort(p);
            { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, out) ); return; };
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
    void TileLayerWrap::LayerToPortOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset o;
            auto o_isOffset = v8_ValueIsOffset(isolate, args[1 -1], o);
            if (!o_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*o_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            Offset out = self->layerToPort(o);
            { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, out) ); return; };
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
    void TileLayerWrap::LayerToPortVector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Vector v;
            auto v_isVector = v8_ValueIsVector(isolate, args[1 -1], v);
            if (!v_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*v_isVector)
            {
                v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                return;
            };
            Vector out = self->layerToPort(v);
            { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, out) ); return; };
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
    void TileLayerWrap::LayerToPortRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::RotatedRect r;
            auto r_isRotatedRect = v8_ValueIsRotatedRect(isolate, args[1 -1], r);
            if (!r_isRotatedRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*r_isRotatedRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *args[1 -1]);
                return;
            };
            RotatedRect out = self->layerToPort(r);
            { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, out) ); return; };
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
    void TileLayerWrap::LayerToPortQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Quad q;
            auto q_isQuad = v8_ValueIsQuad(isolate, args[1 -1], q);
            if (!q_isQuad.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*q_isQuad)
            {
                v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
                return;
            };
            Quad out = self->layerToPort(q);
            { args.GetReturnValue().Set( v8_MakeJavascriptQuad(isolate, out) ); return; };
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
    void TileLayerWrap::PortToLayerPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Point p;
            auto p_isPoint = v8_ValueIsPoint(isolate, args[1 -1], p);
            if (!p_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*p_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            Point out = self->portToLayer(p);
            { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, out) ); return; };
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
    void TileLayerWrap::PortToLayerOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset o;
            auto o_isOffset = v8_ValueIsOffset(isolate, args[1 -1], o);
            if (!o_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*o_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            Offset out = self->portToLayer(o);
            { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, out) ); return; };
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
    void TileLayerWrap::PortToLayerVector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Vector v;
            auto v_isVector = v8_ValueIsVector(isolate, args[1 -1], v);
            if (!v_isVector.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*v_isVector)
            {
                v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
                return;
            };
            Vector out = self->portToLayer(v);
            { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, out) ); return; };
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
    void TileLayerWrap::PortToLayerRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::RotatedRect r;
            auto r_isRotatedRect = v8_ValueIsRotatedRect(isolate, args[1 -1], r);
            if (!r_isRotatedRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*r_isRotatedRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "RotatedRect", *args[1 -1]);
                return;
            };
            RotatedRect out = self->portToLayer(r);
            { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, out) ); return; };
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
    void TileLayerWrap::PortToLayerQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Quad q;
            auto q_isQuad = v8_ValueIsQuad(isolate, args[1 -1], q);
            if (!q_isQuad.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*q_isQuad)
            {
                v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
                return;
            };
            Quad out = self->portToLayer(q);
            { args.GetReturnValue().Set( v8_MakeJavascriptQuad(isolate, out) ); return; };
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
#endif

    void TileLayerWrap::SetQueryBits(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""bits"")");
            return;
        }
        double bits = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if(!std::isfinite(bits)||bits<0||bits>4294967295.0||std::floor(bits)!=bits)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected unsigned 32-bit query bits";
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
        self->setQueryBits(uint32_t(bits)); args.GetReturnValue().SetUndefined();
    }
    void TileLayerWrap::GetQueryBits(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        { args.GetReturnValue().Set( v8::Number::New(isolate, self->getQueryBits()) ); return; };
    }
    void TileLayerWrap::SetCamera(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        if (!args.Length() || args[0]->IsNull() || args[0]->IsUndefined())
        {
            self->setCamera(nullptr); args.GetReturnValue().SetUndefined();
        }
        else
        {
            ;
            try
            {
                if (!(dynamic_cast<CameraWrap*>(pdg::v8script::safe_unwrap_object_wrap_or_prototype(isolate, args[0])) != 0))
                {
                    std::ostringstream excpt_;
                    excpt_ << "Expected a Camera or null";
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
                }
                REQUIRE_CPP_OBJECT_ARG(1, camera, Camera); self->setCamera(camera); args.GetReturnValue().SetUndefined();
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
    }
    void TileLayerWrap::GetCamera(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        auto* camera=self->getCamera(); if (!camera) { args.GetReturnValue().SetNull(); return; };
        if (camera->mCameraScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( CameraWrap::NewFromCpp(isolate, camera) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, camera->mCameraScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }
    void TileLayerWrap::GetEffectiveCamera(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        auto* camera=self->getEffectiveCamera(); if (!camera) { args.GetReturnValue().SetNull(); return; };
        if (camera->mCameraScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( CameraWrap::NewFromCpp(isolate, camera) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, camera->mCameraScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }
    void TileLayerWrap::SetCameraParallax(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() >= 1 && !args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""movementRatio"")");
                return;
            }
            double movementRatio = (args.Length()<1) ? 1 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""zoomRatio"")");
                return;
            }
            double zoomRatio = (args.Length()<2) ? 1 : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();; self->setCameraParallax(movementRatio,zoomRatio); args.GetReturnValue().SetUndefined();
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
    void TileLayerWrap::GetWorldBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Rect theWorldBounds = self->getWorldBounds();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, theWorldBounds) ); return; };
    }
    void TileLayerWrap::SetWorldBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            pdg::Rect bounds;
            auto bounds_isRect = v8_ValueIsRect(isolate, args[1 -1], bounds);
            if (!bounds_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*bounds_isRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
                return;
            };
            self->setWorldBounds(bounds); args.GetReturnValue().SetUndefined();
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
    void TileLayerWrap::CreateParticle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=self->createParticle(); if (!result)
            {
                args.GetReturnValue().SetNull(); return;
            };
            if (result->mParticleScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ParticleWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mParticleScriptObj );
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
    void TileLayerWrap::AddParticle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,value,Particle); self->addParticle(value); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::RemoveParticle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,value,Particle); self->removeParticle(value); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::RemoveAllParticles(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removeAllParticles(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::GetParticleTrailCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->getParticleTrailCount()) ); return;
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
    void TileLayerWrap::GetParticleCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->getParticleCount()) ); return;
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
    void TileLayerWrap::GetNthParticle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); auto* result=self->getNthParticle(static_cast<uint32_t>(value)); if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mParticleScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ParticleWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mParticleScriptObj );
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
    void TileLayerWrap::SetMaxParticles(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            double value = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked(); if (!std::isfinite(value) || value < 0 || value > UINT32_MAX || std::floor(value)!=value) throw std::invalid_argument("Expected a particle count or index"); self->setMaxParticles(static_cast<uint32_t>(value));
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
    void TileLayerWrap::GetMaxParticles(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            {
                args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->getMaxParticles()) ); return;
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
    void TileLayerWrap::CreateParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            auto* result=self->createParticleEmitter(); if (!result)
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
    void TileLayerWrap::RemoveParticleEmitter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1,value,ParticleEmitter); self->removeParticleEmitter(value); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::RemoveAllParticleEmitters(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        try
        {
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removeAllParticleEmitters(); args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::SetSerializationFlags(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(durationSeconds);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    void TileLayerWrap::FadeOut(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(durationSeconds, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(durationSeconds);
        }
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    void TileLayerWrap::MoveBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToBack();
        args.GetReturnValue().SetUndefined();
    }
    void TileLayerWrap::IsSpriteBehind(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, newSprite, Sprite);
            self->addSprite(newSprite);
            args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::RemoveSprite(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, oldSprite, Sprite);
            self->removeSprite(oldSprite);
            args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::RemoveAllSprites(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
            ;
            if (args.Length() != 0)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 0);
                return;
            };
            self->removeAllSprites();
            args.GetReturnValue().SetUndefined();
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }
    void TileLayerWrap::EnableCollisions(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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

    void TileLayerWrap::SetGravity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        self->setGravity(gravity);
        args.GetReturnValue().SetUndefined();
    }
    void TileLayerWrap::SetDamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect r = self->getWorldSize();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }
    void TileLayerWrap::GetTileTypeAt(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        if (mapWidth < 0 || mapHeight < 0 || dstX < 0 || dstY < 0)
        {
            std::ostringstream excpt_;
            excpt_ << "negative tile map dimensions";
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
        if (mapWidth > self->mWorldWidth)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 2 (mapWidth) is larger than world width";
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
        if (mapWidth > self->mWorldWidth - dstX)
        {
            std::ostringstream excpt_;
            excpt_ << "mapWidth + dstX is larger than world width";
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
        if (mapHeight > self->mWorldHeight)
        {
            std::ostringstream excpt_;
            excpt_ << "argument 3 (mapHeight) is larger than world height";
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
        if (mapHeight > self->mWorldHeight - dstY)
        {
            std::ostringstream excpt_;
            excpt_ << "mapHeight + dstY is larger than world height";
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
        if (!IsUint8Array(args[0]) && !MemBlockWrap::GetTemplate(isolate)->HasInstance(args[0]))
        {
            std::ostringstream excpt_;
            excpt_ << "argument 1 (data) must be either a Uint8Array or an object of type MemBlock";
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
        }
        if (IsUint8Array(args[0]))
        {
            size_t bytes = 0;
            const uint8* ptr = nullptr;
            if (!GetUint8ArrayData(args[0], ptr, bytes))
            {
                std::ostringstream excpt_;
                excpt_ << "expected an attached, non-shared Uint8Array";
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
            }
            if (bytes > UINT32_MAX)
            {
                std::ostringstream excpt_;
                excpt_ << "byte array exceeds the supported size";
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
            if (bytes < ((size_t)mapWidth * (size_t)mapHeight))
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size";
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
            self->loadMapData(ptr, mapWidth, mapHeight, dstX, dstY);

        }
        else
        {
            if (!MemBlockWrap::GetTemplate(isolate)->HasInstance(args[0]))
            {
                std::ostringstream excpt_;
                excpt_ << "expected Uint8Array or MemBlock";
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
            }
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
                }
                ())));
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            self->loadMapData((uint8*)memBlock->ptr, mapWidth, mapHeight, dstX, dstY);
        }
        args.GetReturnValue().SetUndefined();
    }
    void TileLayerWrap::GetMapData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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

    void TileLayerWrap::OnLayerFadeInComplete(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        TileLayerWrap* objWrapper=jswrap::ObjectWrap::Unwrap<TileLayerWrap>(args.This());
        TileLayer* self=dynamic_cast<TileLayer*>(objWrapper->getCppObject());
        if(!self)
        {
            std::ostringstream excpt_;
            excpt_ << "Layer is disposed";
            isolate->ThrowException( v8::Exception::Error( ([&]()
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

        ;
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

#ifdef PDG_USING_JAVASCRIPT_CORE
    void CleanupTileLayerScriptObject(JSObjectRef obj) { if(obj)JSObjectSetPrivate(obj,nullptr); }
#else
    void CleanupTileLayerScriptObject(v8::UniquePersistent<v8::Object>& obj)
    {
        if(!obj.IsEmpty())
        {
            auto* isolate=v8::Isolate::GetCurrent();
            auto value=v8::Local<v8::Object>::New(isolate,obj);
            if(auto* wrapper=dynamic_cast<TileLayerWrap*>(v8script::safe_unwrap_object_wrap_or_prototype(isolate,value)))wrapper->forgetCppObject();
            obj.Reset();
        }
    }
#endif

    TileLayerWrap::TileLayerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        {
            v8::TryCatch caught(args.GetIsolate());
            cppPtr_ = New_TileLayer(args);
            if (caught.HasCaught()) { caught.ReThrow(); return; }
        }
        if (!cppPtr_ && !s_TileLayer_InNewFromCpp)
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
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
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        return new TileLayer();
    }

}
