// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/mem_block.cpp
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

    bool s_MemBlock_InNewFromCpp = false;

    void MemBlockWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        MemBlockWrap* objWrapper = new MemBlockWrap(args);
        objWrapper->Wrap(args.This());
        MemBlock* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mMemBlockScriptObj.Reset(isolate, args.This());
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
    v8::Local<v8::Object> MemBlockWrap::NewFromCpp(v8::Isolate* isolate, MemBlock* cppObj)
    {
        s_MemBlock_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_MemBlock_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_MemBlock_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        MemBlockWrap* objWrapper = jswrap::ObjectWrap::Unwrap<MemBlockWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mMemBlockScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_MemBlock_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> MemBlockWrap::constructorTpl_;

    void MemBlockWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "MemBlock").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetData_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetData_Tpl =
            v8::FunctionTemplate::New(isolate, GetData, v8::Local<v8::Value>(), GetData_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getData").ToLocalChecked(), GetData_Tpl);
        v8::Local<v8::Signature> GetDataSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDataSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetDataSize, v8::Local<v8::Value>(), GetDataSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDataSize").ToLocalChecked(), GetDataSize_Tpl);
        v8::Local<v8::Signature> GetByte_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetByte_Tpl =
            v8::FunctionTemplate::New(isolate, GetByte, v8::Local<v8::Value>(), GetByte_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getByte").ToLocalChecked(), GetByte_Tpl);
        v8::Local<v8::Signature> GetBytes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBytes_Tpl =
            v8::FunctionTemplate::New(isolate, GetBytes, v8::Local<v8::Value>(), GetBytes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBytes").ToLocalChecked(), GetBytes_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void MemBlockWrap::GetData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        MemBlockWrap* objWrapper = jswrap::ObjectWrap::Unwrap<MemBlockWrap>(args.This());
        MemBlock* self = dynamic_cast<MemBlock*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[string Binary]" " function" "()" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        v8::Local<v8::Value> resultVal = EncodeBinary(self->ptr, self->bytes);
        { args.GetReturnValue().Set( resultVal ); return; };
    }

    void MemBlockWrap::GetDataSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        MemBlockWrap* objWrapper = jswrap::ObjectWrap::Unwrap<MemBlockWrap>(args.This());
        MemBlock* self = dynamic_cast<MemBlock*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->bytes) ); return; };
    }

    void MemBlockWrap::GetByte(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        MemBlockWrap* objWrapper = jswrap::ObjectWrap::Unwrap<MemBlockWrap>(args.This());
        MemBlock* self = dynamic_cast<MemBlock*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([number uint] i)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""i"")");
            return;
        }
        unsigned long i = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, self->ptr[i]) ); return; };
    }

    void MemBlockWrap::GetBytes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        MemBlockWrap* objWrapper = jswrap::ObjectWrap::Unwrap<MemBlockWrap>(args.This());
        MemBlock* self = dynamic_cast<MemBlock*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[string Binary]" " function" "([number uint] start, [number uint] len)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""start"")");
            return;
        }
        unsigned long start = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""len"")");
            return;
        }
        unsigned long len = args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        v8::Local<v8::Value> resultVal = EncodeBinary(self->ptr + start, len);
        { args.GetReturnValue().Set( resultVal ); return; };
    }

    void CleanupMemBlockScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    MemBlockWrap::MemBlockWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_MemBlock(args);
        if (!cppPtr_ && !s_MemBlock_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "MemBlock" " instance")));
            };
        }
    }

    MemBlockWrap::~MemBlockWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    MemBlock* New_MemBlock(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_MemBlock_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new MemBlock(0, 0, false);
    }

}
