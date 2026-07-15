// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/audio/sound_manager.cpp
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

    static bool s_Sound_InNewFromCpp = false;

    void SoundWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = new SoundWrap(args);
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
    v8::Local<v8::Object> SoundWrap::NewFromCpp(v8::Isolate* isolate, Sound* cppObj)
    {
        s_Sound_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Sound_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Sound_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mEventEmitterScriptObj.Reset(isolate, obj); cppObj->mSoundScriptObj.Reset(isolate, obj); cppObj->addRef();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Sound_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SoundWrap::constructorTpl_;

    void SoundWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Sound").ToLocalChecked();
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
        v8::Local<v8::Signature> GetVolume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetVolume_Tpl =
            v8::FunctionTemplate::New(isolate, GetVolume, v8::Local<v8::Value>(), GetVolume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Volume").ToLocalChecked(), GetVolume_Tpl);
        v8::Local<v8::Signature> SetVolume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetVolume_Tpl =
            v8::FunctionTemplate::New(isolate, SetVolume, v8::Local<v8::Value>(), SetVolume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Volume").ToLocalChecked(), SetVolume_Tpl);
        v8::Local<v8::Signature> Play_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Play_Tpl =
            v8::FunctionTemplate::New(isolate, Play, v8::Local<v8::Value>(), Play_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "play").ToLocalChecked(), Play_Tpl);
        v8::Local<v8::Signature> Start_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Start_Tpl =
            v8::FunctionTemplate::New(isolate, Start, v8::Local<v8::Value>(), Start_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "start").ToLocalChecked(), Start_Tpl);
        v8::Local<v8::Signature> Stop_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Stop_Tpl =
            v8::FunctionTemplate::New(isolate, Stop, v8::Local<v8::Value>(), Stop_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stop").ToLocalChecked(), Stop_Tpl);
        v8::Local<v8::Signature> Pause_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Pause_Tpl =
            v8::FunctionTemplate::New(isolate, Pause, v8::Local<v8::Value>(), Pause_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pause").ToLocalChecked(), Pause_Tpl);
        v8::Local<v8::Signature> Resume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Resume_Tpl =
            v8::FunctionTemplate::New(isolate, Resume, v8::Local<v8::Value>(), Resume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resume").ToLocalChecked(), Resume_Tpl);
        v8::Local<v8::Signature> IsPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsPaused, v8::Local<v8::Value>(), IsPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isPaused").ToLocalChecked(), IsPaused_Tpl);
        v8::Local<v8::Signature> SetLooping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLooping_Tpl =
            v8::FunctionTemplate::New(isolate, SetLooping, v8::Local<v8::Value>(), SetLooping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLooping").ToLocalChecked(), SetLooping_Tpl);
        v8::Local<v8::Signature> IsLooping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsLooping_Tpl =
            v8::FunctionTemplate::New(isolate, IsLooping, v8::Local<v8::Value>(), IsLooping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isLooping").ToLocalChecked(), IsLooping_Tpl);
        v8::Local<v8::Signature> SetPitch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPitch_Tpl =
            v8::FunctionTemplate::New(isolate, SetPitch, v8::Local<v8::Value>(), SetPitch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPitch").ToLocalChecked(), SetPitch_Tpl);
        v8::Local<v8::Signature> ChangePitch_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangePitch_Tpl =
            v8::FunctionTemplate::New(isolate, ChangePitch, v8::Local<v8::Value>(), ChangePitch_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changePitch").ToLocalChecked(), ChangePitch_Tpl);
        v8::Local<v8::Signature> SetOffsetX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOffsetX_Tpl =
            v8::FunctionTemplate::New(isolate, SetOffsetX, v8::Local<v8::Value>(), SetOffsetX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setOffsetX").ToLocalChecked(), SetOffsetX_Tpl);
        v8::Local<v8::Signature> ChangeOffsetX_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeOffsetX_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeOffsetX, v8::Local<v8::Value>(), ChangeOffsetX_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeOffsetX").ToLocalChecked(), ChangeOffsetX_Tpl);
        v8::Local<v8::Signature> FadeOut_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeOut_Tpl =
            v8::FunctionTemplate::New(isolate, FadeOut, v8::Local<v8::Value>(), FadeOut_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeOut").ToLocalChecked(), FadeOut_Tpl);
        v8::Local<v8::Signature> FadeIn_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FadeIn_Tpl =
            v8::FunctionTemplate::New(isolate, FadeIn, v8::Local<v8::Value>(), FadeIn_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fadeIn").ToLocalChecked(), FadeIn_Tpl);
        v8::Local<v8::Signature> ChangeVolume_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeVolume_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeVolume, v8::Local<v8::Value>(), ChangeVolume_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeVolume").ToLocalChecked(), ChangeVolume_Tpl);
        v8::Local<v8::Signature> Skip_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Skip_Tpl =
            v8::FunctionTemplate::New(isolate, Skip, v8::Local<v8::Value>(), Skip_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "skip").ToLocalChecked(), Skip_Tpl);
        v8::Local<v8::Signature> SkipTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SkipTo_Tpl =
            v8::FunctionTemplate::New(isolate, SkipTo, v8::Local<v8::Value>(), SkipTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "skipTo").ToLocalChecked(), SkipTo_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SoundWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

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
            std::cerr << __func__<<":"<< 62 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 62 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 62 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 62 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 62 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void SoundWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

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

    void SoundWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

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

    void SoundWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

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

    void SoundWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

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

    void SoundWrap::GetVolume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theVolume = self->getVolume();
        { args.GetReturnValue().Set( v8::Number::New(isolate, theVolume) ); return; };
    }

    void SoundWrap::SetVolume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Sound]" " function" "(number inVolume)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theVolume"")");
            return;
        }
        double theVolume = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        self->setVolume(theVolume);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SoundWrap::Play(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number vol = 1.0, [number int] offsetX = 0, number pitch = 0, [number uint] fromMs = 0, [number int] lenMs = ENTIRE_LENGTH)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""vol"")");
            return;
        }
        double vol = (args.Length()<1) ? 1.0 : args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""offsetX"")");
            return;
        }
        long offsetX = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""pitch"")");
            return;
        }
        double pitch = (args.Length()<3) ? 0.0 : args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""fromMs"")");
            return;
        }
        unsigned long fromMs = (args.Length()<4) ? 0 : args[4 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 5 && !args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""lenMs"")");
            return;
        }
        long lenMs = (args.Length()<5) ? -1 : args[5 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->play(vol, offsetX, pitch, fromMs, lenMs);
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::Start(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->start();
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::Stop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->stop();
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::Pause(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->pause();
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::Resume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->resume();
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::IsPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool result = self->isPaused();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void SoundWrap::SetLooping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "Sound" " function" "(boolean loopingOn)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""loopingOn"")");
            return;
        }
        bool loopingOn = args[1 -1]->BooleanValue(isolate);
        self->setLooping(loopingOn);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SoundWrap::IsLooping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool result = self->isLooping();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void SoundWrap::SetPitch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "Sound" " function" "(number pitchOffset)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""pitchOffset"")");
            return;
        }
        double pitchOffset = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setPitch(pitchOffset);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SoundWrap::ChangePitch(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number targetOffset, [number int] msDuration, [number int] easing = easeInOutQuad)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""targetOffset"")");
            return;
        }
        double targetOffset = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
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
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changePitch(targetOffset, msDuration);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::SetOffsetX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "Sound" " function" "([number int] offsetX)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""offsetX"")");
            return;
        }
        long offsetX = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->setOffsetX(offsetX);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SoundWrap::ChangeOffsetX(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] targetOffset, [number int] msDuration, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""targetOffset"")");
            return;
        }
        long targetOffset = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
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
            self->changePitch(targetOffset, msDuration, gEasingFunctions[easing]);
        }
        else
        {
            self->changePitch(targetOffset, msDuration);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::FadeOut(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] fadeMs, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""fadeMs"")");
            return;
        }
        unsigned long fadeMs = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeOut(fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeOut(fadeMs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::FadeIn(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] fadeMs, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""fadeMs"")");
            return;
        }
        unsigned long fadeMs = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<2) ? EasingFuncRef::linearTween : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->fadeIn(fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->fadeIn(fadeMs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::ChangeVolume(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number level, [number uint] fadeMs, [number int] easing = linearTween)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""level"")");
            return;
        }
        double level = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""fadeMs"")");
            return;
        }
        unsigned long fadeMs = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""easing"")");
            return;
        }
        long easing = (args.Length()<3) ? EasingFuncRef::linearTween : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (easing >= 0 && easing < NUM_EASING_FUNCTIONS)
        {
            self->changeVolume(level, fadeMs, gEasingFunctions[easing]);
        }
        else
        {
            self->changeVolume(level, fadeMs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SoundWrap::Skip(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "Sound" " function" "([number int] skipMilliseconds)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""skipMilliseconds"")");
            return;
        }
        long skipMilliseconds = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->skip(skipMilliseconds);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void SoundWrap::SkipTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SoundWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SoundWrap>(args.This());
        Sound* self = dynamic_cast<Sound*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "Sound" " function" "([number uint] timeMs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""timeMs"")");
            return;
        }
        unsigned long timeMs = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        self->skipTo(timeMs);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void CleanupSoundScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    SoundWrap::SoundWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Sound(args);
        if (!cppPtr_ && !s_Sound_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Sound" " instance")));
            };
        }
    }

    SoundWrap::~SoundWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Sound* New_Sound(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Sound_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() < 1)
        {
            return 0;
        }
        else if ((args.Length() == 1 && args[0]->IsNull()))
        {
            return Sound::createEmptySoundForIntrospection();
        }
        else if (!args[0]->IsString())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 must be a string (filename)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        else
        {
            v8::String::Utf8Value filename_Str(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* filename = *filename_Str;;
            Sound* snd = Sound::createSoundFromFile(filename);
            if (!snd)
            {
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << "could not create Sound from file ["<<filename<<"]";
                    v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };
                return 0;
            }
            else
            {
                return snd;
            }
        }
    }
#endif

}
