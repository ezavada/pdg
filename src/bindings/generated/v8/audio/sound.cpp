// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/sound.cpp
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

#ifndef PDG_NO_SOUND

    static bool s_SoundManager_InNewFromCpp = false;

    void SoundManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_SoundManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "SoundManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "snd"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        SoundManagerWrap* objWrapper = new SoundManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> SoundManagerWrap::instance_;
    bool SoundManagerWrap::instanced_ = false;

    v8::Local<v8::Object> SoundManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_SoundManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_SoundManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_SoundManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_SoundManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    SoundManager* SoundManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        SoundManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundManagerWrap>(val);
        return dynamic_cast<SoundManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> SoundManagerWrap::constructorTpl_;

    void SoundManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "SoundManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> SetVolume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVolume_Tpl =
            v8::FunctionTemplate::New(isolate, SetVolume, v8::Local<v8::Value>(), SetVolume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setVolume").ToLocalChecked(), SetVolume_Tpl);
        v8::Local<v8::Signature> SetMute_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetMute_Tpl =
            v8::FunctionTemplate::New(isolate, SetMute, v8::Local<v8::Value>(), SetMute_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setMute").ToLocalChecked(), SetMute_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SoundManagerWrap::SetVolume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundManagerWrap>(args.This());
        SoundManager* self = dynamic_cast<SoundManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number level)" " - " "0.0 - silent to 1.0 - full volume").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""level"")");
            return;
        }
        double level = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setVolume(level);
        args.GetReturnValue().SetUndefined();
    }

    void SoundManagerWrap::SetMute(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundManagerWrap>(args.This());
        SoundManager* self = dynamic_cast<SoundManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean muted)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""muted"")");
            return;
        }
        bool muted = args[1 -1]->BooleanValue(isolate);
        self->setMute(muted);
        args.GetReturnValue().SetUndefined();
    }

    SoundManagerWrap::SoundManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_SoundManager(args);
        if (!cppPtr_ && !s_SoundManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "SoundManager" " instance")));
            };
        }
    }

    SoundManagerWrap::~SoundManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    SoundManager* New_SoundManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_SoundManager_InNewFromCpp)
        {
            return SoundManager::getSingletonInstance();
        }
        else
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "SoundManager" " directly - use get" "SoundManager" "() instead")));
            };
            return nullptr;
        }
    }
#endif

}
