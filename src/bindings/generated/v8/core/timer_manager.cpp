// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/timer_manager.cpp
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

    static bool s_TimerManager_InNewFromCpp = false;

    void TimerManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_TimerManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "TimerManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "tm"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        TimerManagerWrap* objWrapper = new TimerManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> TimerManagerWrap::instance_;
    bool TimerManagerWrap::instanced_ = false;

    v8::Local<v8::Object> TimerManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_TimerManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_TimerManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_TimerManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_TimerManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    TimerManager* TimerManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(val);
        return dynamic_cast<TimerManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> TimerManagerWrap::constructorTpl_;

    void TimerManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "TimerManager").ToLocalChecked();
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
        v8::Local<v8::Signature> StartTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartTimer_Tpl =
            v8::FunctionTemplate::New(isolate, StartTimer, v8::Local<v8::Value>(), StartTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startTimer").ToLocalChecked(), StartTimer_Tpl);
        v8::Local<v8::Signature> CancelTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelTimer_Tpl =
            v8::FunctionTemplate::New(isolate, CancelTimer, v8::Local<v8::Value>(), CancelTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelTimer").ToLocalChecked(), CancelTimer_Tpl);
        v8::Local<v8::Signature> CancelAllTimers_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CancelAllTimers_Tpl =
            v8::FunctionTemplate::New(isolate, CancelAllTimers, v8::Local<v8::Value>(), CancelAllTimers_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "cancelAllTimers").ToLocalChecked(), CancelAllTimers_Tpl);
        v8::Local<v8::Signature> DelayTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DelayTimer_Tpl =
            v8::FunctionTemplate::New(isolate, DelayTimer, v8::Local<v8::Value>(), DelayTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "delayTimer").ToLocalChecked(), DelayTimer_Tpl);
        v8::Local<v8::Signature> DelayTimerUntil_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DelayTimerUntil_Tpl =
            v8::FunctionTemplate::New(isolate, DelayTimerUntil, v8::Local<v8::Value>(), DelayTimerUntil_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "delayTimerUntil").ToLocalChecked(), DelayTimerUntil_Tpl);
        v8::Local<v8::Signature> Pause_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Pause_Tpl =
            v8::FunctionTemplate::New(isolate, Pause, v8::Local<v8::Value>(), Pause_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pause").ToLocalChecked(), Pause_Tpl);
        v8::Local<v8::Signature> Unpause_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Unpause_Tpl =
            v8::FunctionTemplate::New(isolate, Unpause, v8::Local<v8::Value>(), Unpause_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unpause").ToLocalChecked(), Unpause_Tpl);
        v8::Local<v8::Signature> IsPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsPaused, v8::Local<v8::Value>(), IsPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isPaused").ToLocalChecked(), IsPaused_Tpl);
        v8::Local<v8::Signature> PauseTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PauseTimer_Tpl =
            v8::FunctionTemplate::New(isolate, PauseTimer, v8::Local<v8::Value>(), PauseTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "pauseTimer").ToLocalChecked(), PauseTimer_Tpl);
        v8::Local<v8::Signature> UnpauseTimer_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UnpauseTimer_Tpl =
            v8::FunctionTemplate::New(isolate, UnpauseTimer, v8::Local<v8::Value>(), UnpauseTimer_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unpauseTimer").ToLocalChecked(), UnpauseTimer_Tpl);
        v8::Local<v8::Signature> IsTimerPaused_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsTimerPaused_Tpl =
            v8::FunctionTemplate::New(isolate, IsTimerPaused, v8::Local<v8::Value>(), IsTimerPaused_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isTimerPaused").ToLocalChecked(), IsTimerPaused_Tpl);
        v8::Local<v8::Signature> GetWhenTimerFiresNext_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWhenTimerFiresNext_Tpl =
            v8::FunctionTemplate::New(isolate, GetWhenTimerFiresNext, v8::Local<v8::Value>(), GetWhenTimerFiresNext_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getWhenTimerFiresNext").ToLocalChecked(), GetWhenTimerFiresNext_Tpl);
        v8::Local<v8::Signature> GetMilliseconds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMilliseconds_Tpl =
            v8::FunctionTemplate::New(isolate, GetMilliseconds, v8::Local<v8::Value>(), GetMilliseconds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMilliseconds").ToLocalChecked(), GetMilliseconds_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void TimerManagerWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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
            std::cerr << __func__<<":"<< 52 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 52 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 52 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 52 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 52 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void TimerManagerWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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

    void TimerManagerWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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

    void TimerManagerWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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

    void TimerManagerWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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

    void TimerManagerWrap::StartTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id, [number uint] delay, boolean oneShot = true)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""delay"")");
            return;
        }
        unsigned long delay = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 3, "a boolean (""oneShot"")");
            return;
        }
        bool oneShot = (args.Length()<3) ? true : args[3 -1]->BooleanValue(isolate);;
        self->startTimer(id, delay, oneShot);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::CancelTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
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
        self->cancelTimer(id);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::CancelAllTimers(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->cancelAllTimers();
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::DelayTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id, [number uint] delay)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""delay"")");
            return;
        }
        unsigned long delay = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        self->delayTimer(id, delay);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::DelayTimerUntil(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id, [number int] msTime)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""msTime"")");
            return;
        }
        double msTime_temp = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (msTime_temp < -9223372036854775808.0 || msTime_temp > 9223372036854775807.0 || msTime_temp != (long long)msTime_temp)
        {
            v8_ThrowArgTypeException(isolate, 2, "a number in range [-9223372036854775808, 9223372036854775807] (""msTime"")");
            return;
        }
        int64 msTime = (int64)msTime_temp;
        self->delayTimerUntil(id, msTime);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::Pause(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

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

    void TimerManagerWrap::Unpause(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->unpause();
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::IsPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool isPaused = self->isPaused();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, isPaused) ); return; };
    }

    void TimerManagerWrap::PauseTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
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
        self->pauseTimer(id);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::UnpauseTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
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
        self->unpauseTimer(id);
        args.GetReturnValue().SetUndefined();
    }

    void TimerManagerWrap::IsTimerPaused(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
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
        bool isPaused = self->isTimerPaused(id);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, isPaused) ); return; };
    }

    void TimerManagerWrap::GetWhenTimerFiresNext(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        TimerManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<TimerManagerWrap>(args.This());
        TimerManager* self = dynamic_cast<TimerManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([number int] id)" " - " "").ToLocalChecked() ); return; };
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
        ms_time when = self->getWhenTimerFiresNext(id);

        if (when == 0xffffffff)
        {
            { args.GetReturnValue().Set( v8::Number::New(isolate, -1) ); return; };
        }
        else
        {
            { args.GetReturnValue().Set( v8::Number::New(isolate, when) ); return; };
        }
    }
    void TimerManagerWrap::GetMilliseconds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        { args.GetReturnValue().Set( v8::Number::New(isolate, OS::getMilliseconds()) ); return; };
    }

    TimerManagerWrap::TimerManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_TimerManager(args);
        if (!cppPtr_ && !s_TimerManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "TimerManager" " instance")));
            };
        }
    }

    TimerManagerWrap::~TimerManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    TimerManager* New_TimerManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_TimerManager_InNewFromCpp)
        {
            return TimerManager::getSingletonInstance();
        }
        else
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "TimerManager" " directly - use get" "TimerManager" "() instead")));
            };
            return nullptr;
        }
    }

}
