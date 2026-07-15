// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_space.cpp
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

#include <sstream>
#include <cmath>
#include <cstdlib>

namespace pdg
{

    static bool s_cpSpace_InNewFromCpp = false;

    void cpSpaceWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = new cpSpaceWrap(args);
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
    v8::Local<v8::Object> cpSpaceWrap::NewFromCpp(v8::Isolate* isolate, cpSpace* cppObj)
    {
        s_cpSpace_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_cpSpace_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_cpSpace_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            ;
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_cpSpace_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> cpSpaceWrap::constructorTpl_;

    void cpSpaceWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "CpSpace").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> UseSpatialHash_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UseSpatialHash_Tpl =
            v8::FunctionTemplate::New(isolate, UseSpatialHash, v8::Local<v8::Value>(), UseSpatialHash_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "useSpatialHash").ToLocalChecked(), UseSpatialHash_Tpl);
        v8::Local<v8::Signature> ReindexStatic_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ReindexStatic_Tpl =
            v8::FunctionTemplate::New(isolate, ReindexStatic, v8::Local<v8::Value>(), ReindexStatic_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "reindexStatic").ToLocalChecked(), ReindexStatic_Tpl);
        v8::Local<v8::Signature> Step_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Step_Tpl =
            v8::FunctionTemplate::New(isolate, Step, v8::Local<v8::Value>(), Step_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "step").ToLocalChecked(), Step_Tpl);
        v8::Local<v8::Signature> GetIdleSpeedThreshold_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetIdleSpeedThreshold_Tpl =
            v8::FunctionTemplate::New(isolate, GetIdleSpeedThreshold, v8::Local<v8::Value>(), GetIdleSpeedThreshold_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""IdleSpeedThreshold").ToLocalChecked(), GetIdleSpeedThreshold_Tpl);
        v8::Local<v8::Signature> SetIdleSpeedThreshold_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetIdleSpeedThreshold_Tpl =
            v8::FunctionTemplate::New(isolate, SetIdleSpeedThreshold, v8::Local<v8::Value>(), SetIdleSpeedThreshold_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""IdleSpeedThreshold").ToLocalChecked(), SetIdleSpeedThreshold_Tpl);
        v8::Local<v8::Signature> GetSleepTimeThreshold_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSleepTimeThreshold_Tpl =
            v8::FunctionTemplate::New(isolate, GetSleepTimeThreshold, v8::Local<v8::Value>(), GetSleepTimeThreshold_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""SleepTimeThreshold").ToLocalChecked(), GetSleepTimeThreshold_Tpl);
        v8::Local<v8::Signature> SetSleepTimeThreshold_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetSleepTimeThreshold_Tpl =
            v8::FunctionTemplate::New(isolate, SetSleepTimeThreshold, v8::Local<v8::Value>(), SetSleepTimeThreshold_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""SleepTimeThreshold").ToLocalChecked(), SetSleepTimeThreshold_Tpl);
        v8::Local<v8::Signature> GetCollisionSlop_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionSlop_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionSlop, v8::Local<v8::Value>(), GetCollisionSlop_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""CollisionSlop").ToLocalChecked(), GetCollisionSlop_Tpl);
        v8::Local<v8::Signature> SetCollisionSlop_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionSlop_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionSlop, v8::Local<v8::Value>(), SetCollisionSlop_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""CollisionSlop").ToLocalChecked(), SetCollisionSlop_Tpl);
        v8::Local<v8::Signature> GetCollisionBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionBias_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionBias, v8::Local<v8::Value>(), GetCollisionBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""CollisionBias").ToLocalChecked(), GetCollisionBias_Tpl);
        v8::Local<v8::Signature> SetCollisionBias_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionBias_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionBias, v8::Local<v8::Value>(), SetCollisionBias_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""CollisionBias").ToLocalChecked(), SetCollisionBias_Tpl);
        v8::Local<v8::Signature> GetCollisionPersistence_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCollisionPersistence_Tpl =
            v8::FunctionTemplate::New(isolate, GetCollisionPersistence, v8::Local<v8::Value>(), GetCollisionPersistence_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""CollisionPersistence").ToLocalChecked(), GetCollisionPersistence_Tpl);
        v8::Local<v8::Signature> SetCollisionPersistence_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCollisionPersistence_Tpl =
            v8::FunctionTemplate::New(isolate, SetCollisionPersistence, v8::Local<v8::Value>(), SetCollisionPersistence_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""CollisionPersistence").ToLocalChecked(), SetCollisionPersistence_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void cpSpaceWrap::UseSpatialHash(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number dim, [number int] count)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""dim"")");
            return;
        }
        double dim = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""count"")");
            return;
        }
        long count = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        cpSpaceUseSpatialHash(self, dim, count);
        args.GetReturnValue().SetUndefined();
    }

    void cpSpaceWrap::ReindexStatic(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        cpSpaceReindexStatic(self);
        args.GetReturnValue().SetUndefined();
    }

    void cpSpaceWrap::Step(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number dt)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""dt"")");
            return;
        }
        double dt = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        cpSpaceStep(self, dt);
        args.GetReturnValue().SetUndefined();
    }

    void cpSpaceWrap::GetIdleSpeedThreshold(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theIdleSpeedThreshold = cpSpaceGetIdleSpeedThreshold(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theIdleSpeedThreshold) ); return; };
    }

    void cpSpaceWrap::SetIdleSpeedThreshold(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpSpace]" " function" "(number inIdleSpeedThreshold)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theIdleSpeedThreshold"")");
            return;
        }
        double theIdleSpeedThreshold = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpSpaceSetIdleSpeedThreshold(self, theIdleSpeedThreshold);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpSpaceWrap::GetSleepTimeThreshold(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theSleepTimeThreshold = cpSpaceGetSleepTimeThreshold(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theSleepTimeThreshold) ); return; };
    }

    void cpSpaceWrap::SetSleepTimeThreshold(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpSpace]" " function" "(number inSleepTimeThreshold)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theSleepTimeThreshold"")");
            return;
        }
        double theSleepTimeThreshold = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpSpaceSetSleepTimeThreshold(self, theSleepTimeThreshold);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpSpaceWrap::GetCollisionSlop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theCollisionSlop = cpSpaceGetCollisionSlop(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theCollisionSlop) ); return; };
    }

    void cpSpaceWrap::SetCollisionSlop(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpSpace]" " function" "(number inCollisionSlop)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theCollisionSlop"")");
            return;
        }
        double theCollisionSlop = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpSpaceSetCollisionSlop(self, theCollisionSlop);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpSpaceWrap::GetCollisionBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theCollisionBias = cpSpaceGetCollisionBias(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theCollisionBias) ); return; };
    }

    void cpSpaceWrap::SetCollisionBias(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpSpace]" " function" "(number inCollisionBias)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theCollisionBias"")");
            return;
        }
        double theCollisionBias = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpSpaceSetCollisionBias(self, theCollisionBias);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void cpSpaceWrap::GetCollisionPersistence(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        double theCollisionPersistence = cpSpaceGetCollisionPersistence(self);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theCollisionPersistence) ); return; };
    }

    void cpSpaceWrap::SetCollisionPersistence(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpSpaceWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpSpaceWrap>(args.This());
        cpSpace* self = dynamic_cast<cpSpace*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object cpSpace]" " function" "(number inCollisionPersistence)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theCollisionPersistence"")");
            return;
        }
        double theCollisionPersistence = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();

        cpSpaceSetCollisionPersistence(self, theCollisionPersistence);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    cpSpaceWrap::cpSpaceWrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        cppPtr_ = nullptr;
    }

    cpSpaceWrap::~cpSpaceWrap()
    {
        cppPtr_ = nullptr;
    }

    cpSpace* New_cpSpace(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_cpSpace_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        s_HaveSavedError = true;
        {
            std::ostringstream excpt_;
            excpt_ << "CpSpace cannot be created directly, it is only returned from certain Sprite calls.";
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
        };
        return 0;
    }

}
