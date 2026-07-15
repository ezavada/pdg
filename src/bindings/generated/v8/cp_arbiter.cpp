// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/physics/cp_arbiter.cpp
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

    static bool s_cpArbiter_InNewFromCpp = false;

    void cpArbiterWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = new cpArbiterWrap(args);
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
    v8::Local<v8::Object> cpArbiterWrap::NewFromCpp(v8::Isolate* isolate, cpArbiter* cppObj)
    {
        s_cpArbiter_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_cpArbiter_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_cpArbiter_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(instance);

        ;
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_cpArbiter_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> cpArbiterWrap::constructorTpl_;

    void cpArbiterWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        t->SetClassName(v8::String::NewFromUtf8(isolate, "CpArbiter").ToLocalChecked());
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> IsFirstContact_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> IsFirstContact_Tpl =
            v8::FunctionTemplate::New(isolate, IsFirstContact, v8::Local<v8::Value>(), IsFirstContact_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "isFirstContact").ToLocalChecked(), IsFirstContact_Tpl);
        v8::Local<v8::Signature> GetCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetCount, v8::Local<v8::Value>(), GetCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Count").ToLocalChecked(), GetCount_Tpl);
        v8::Local<v8::Signature> GetNormal_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNormal_Tpl =
            v8::FunctionTemplate::New(isolate, GetNormal, v8::Local<v8::Value>(), GetNormal_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Normal").ToLocalChecked(), GetNormal_Tpl);
        v8::Local<v8::Signature> GetPointA_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointA_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointA, v8::Local<v8::Value>(), GetPointA_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""PointA").ToLocalChecked(), GetPointA_Tpl);
        v8::Local<v8::Signature> GetPointB_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointB_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointB, v8::Local<v8::Value>(), GetPointB_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""PointB").ToLocalChecked(), GetPointB_Tpl);
        v8::Local<v8::Signature> GetDepth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDepth_Tpl =
            v8::FunctionTemplate::New(isolate, GetDepth, v8::Local<v8::Value>(), GetDepth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Depth").ToLocalChecked(), GetDepth_Tpl);
        target->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "CpArbiter").ToLocalChecked(), t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()).ToChecked();

    }

    void cpArbiterWrap::IsFirstContact(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "true if this is the first moment of contact between the objects, false if part of an ongoing collison").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);
        cpBool isFirst = cpArbiterIsFirstContact(self);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, isFirst) ); return; };
    }

    void cpArbiterWrap::GetCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        int theCount = cpArbiterGetCount(self);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theCount) ); return; };
    }

    void cpArbiterWrap::GetNormal(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Vector]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
            v8_ThrowArgCountException(isolate, args.Length(), 0);

        cpVect nv = cpArbiterGetNormal(self);
        pdg::Vector theNormal(nv.x, nv.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, theNormal) ); return; };
    }

    void cpArbiterWrap::GetPointA(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([number int] i)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""i"")");
        long i = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        cpVect pt = cpArbiterGetPointA(self, i);
        pdg::Point thePointA(pt.x, pt.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, thePointA) ); return; };
    }

    void cpArbiterWrap::GetPointB(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([number int] i)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""i"")");
        long i = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        cpVect pt = cpArbiterGetPointB(self, i);
        pdg::Point thePointB(pt.x, pt.y);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, thePointB) ); return; };
    }

    void cpArbiterWrap::GetDepth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        cpArbiterWrap* objWrapper = jswrap::ObjectWrap::Unwrap<cpArbiterWrap>(args.This());
        cpArbiter* self = dynamic_cast<cpArbiter*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([number int] i)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
            v8_ThrowArgCountException(isolate, args.Length(), 1);
        if (!args[1 -1]->IsNumber())
            v8_ThrowArgTypeException(isolate, 1, "a number (""i"")");
        long i = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        cpFloat theDepth = cpArbiterGetDepth(self, i);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theDepth) ); return; };
    }

    cpArbiterWrap::cpArbiterWrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        cppPtr_ = nullptr;
    }

    cpArbiterWrap::~cpArbiterWrap()
    {
        cppPtr_ = nullptr;
    }

    cpArbiter* New_cpArbiter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_cpArbiter_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        s_HaveSavedError = true;
        {
            std::ostringstream excpt_;
            excpt_ << "CpArbiter cannot be created directly, it is only returned from certain Sprite calls.";
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
        };
        return 0;
    }

}
