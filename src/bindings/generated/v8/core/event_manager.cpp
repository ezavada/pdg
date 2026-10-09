// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/event_manager.cpp
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

    static bool s_EventManager_InNewFromCpp = false;

    void EventManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_EventManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "EventManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "evt"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        EventManagerWrap* objWrapper = new EventManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> EventManagerWrap::instance_;
    bool EventManagerWrap::instanced_ = false;

    v8::Local<v8::Object> EventManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_EventManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_EventManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_EventManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_EventManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    EventManager* EventManagerWrap::getSingletonInstance()
    {
        [[maybe_unused]] v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(val);
        return dynamic_cast<EventManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> EventManagerWrap::constructorTpl_;

    void EventManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "EventManager").ToLocalChecked();
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
        v8::Local<v8::Signature> IsKeyDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsKeyDown_Tpl =
            v8::FunctionTemplate::New(isolate, IsKeyDown, v8::Local<v8::Value>(), IsKeyDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isKeyDown").ToLocalChecked(), IsKeyDown_Tpl);
        v8::Local<v8::Signature> IsRawKeyDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsRawKeyDown_Tpl =
            v8::FunctionTemplate::New(isolate, IsRawKeyDown, v8::Local<v8::Value>(), IsRawKeyDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isRawKeyDown").ToLocalChecked(), IsRawKeyDown_Tpl);
        v8::Local<v8::Signature> IsButtonDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsButtonDown_Tpl =
            v8::FunctionTemplate::New(isolate, IsButtonDown, v8::Local<v8::Value>(), IsButtonDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isButtonDown").ToLocalChecked(), IsButtonDown_Tpl);
        v8::Local<v8::Signature> GetDeviceOrientation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDeviceOrientation_Tpl =
            v8::FunctionTemplate::New(isolate, GetDeviceOrientation, v8::Local<v8::Value>(), GetDeviceOrientation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDeviceOrientation").ToLocalChecked(), GetDeviceOrientation_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void EventManagerWrap::AddHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(args.This());
        EventManager* self = dynamic_cast<EventManager*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, inHandler, IEventHandler);
        SCRIPT_DEBUG_ONLY( if (args[0].IsEmpty())
        {
            std::cerr << __func__<<":"<< 44 << " - NIL JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<")\n";
        }
        else if (!args[0]->IsObject())
        {
            std::cerr << __func__<<":"<< 44 << " - NOT JS Object (" "args[0]" "|"<<*((void**)&(args[0]))<<") : " << (args[0].IsEmpty() ? "empty" : args[0]->IsArray() ? "array" : args[0]->IsFunction() ? "function" : args[0]->IsStringObject() ? "string (object)" : args[0]->IsString() ? "string" : args[0]->IsNull() ? "null" : args[0]->IsUndefined() ? "undefined" : args[0]->IsNumberObject() ? "number (object)" : args[0]->IsNumber() ? "number" : args[0]->IsBoolean() ? "boolean" : args[0]->IsDate() ? "date" : args[0]->IsRegExp() ? "regexp" : args[0]->IsNativeError() ? "error" : args[0]->IsObject() ? "object" : "unknown") << "\n";
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
                    std::cout << __func__<<":"<< 44 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - is a subclass of C++ ""IEventHandler""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 44 << " - JS Object (""args[0]""|"<<*((void**)&(args[0]))<<"): " << objName << " - does not wrap ""IEventHandler""\n";
                }
            }
            else
            {
                IEventHandler* obj = dynamic_cast<IEventHandler*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 44 << " - JS Object (""args[0]""|" << *((void**)&(args[0])) << "): " << objName<<" - wraps C++ ""IEventHandler"" ("<<(void*)obj<<")\n";
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

    void EventManagerWrap::RemoveHandler(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(args.This());
        EventManager* self = dynamic_cast<EventManager*>(objWrapper->cppPtr_);

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

    void EventManagerWrap::Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(args.This());
        EventManager* self = dynamic_cast<EventManager*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clear();
        args.GetReturnValue().SetUndefined();
    }

    void EventManagerWrap::BlockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(args.This());
        EventManager* self = dynamic_cast<EventManager*>(objWrapper->cppPtr_);

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

    void EventManagerWrap::UnblockEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        EventManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<EventManagerWrap>(args.This());
        EventManager* self = dynamic_cast<EventManager*>(objWrapper->cppPtr_);

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
    void EventManagerWrap::IsRawKeyDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""keyCode"")");
            return;
        }
        long keyCode = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, OS::isRawKeyDown(keyCode)) ); return; };
    }
    void EventManagerWrap::IsButtonDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""buttonNumber"")");
            return;
        }
        long buttonNumber = (args.Length()<1) ? 0 : args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, OS::isButtonDown(buttonNumber)) ); return; };
    }

    EventManagerWrap::EventManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        {
            v8::TryCatch caught(args.GetIsolate());
            cppPtr_ = New_EventManager(args);
            if (caught.HasCaught()) { caught.ReThrow(); return; }
        }
        if (!cppPtr_ && !s_EventManager_InNewFromCpp)
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "EventManager" " instance")));
            };
        }
    }

    EventManagerWrap::~EventManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    EventManager* New_EventManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_EventManager_InNewFromCpp)
        {
            return EventManager::getSingletonInstance();
        }
        else
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "EventManager" " directly - use get" "EventManager" "() instead")));
            };
            return nullptr;
        }
    }

}
