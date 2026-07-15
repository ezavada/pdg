// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/deserializer.cpp
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
    ;
    ;
    ;

    bool s_Deserializer_InNewFromCpp = false;

    void DeserializerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = new DeserializerWrap(args);
        objWrapper->Wrap(args.This());
        Deserializer* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mDeserializerScriptObj.Reset(isolate, args.This());
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
    v8::Local<v8::Object> DeserializerWrap::NewFromCpp(v8::Isolate* isolate, Deserializer* cppObj)
    {
        s_Deserializer_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Deserializer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Deserializer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mDeserializerScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Deserializer_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> DeserializerWrap::constructorTpl_;

    void DeserializerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Deserializer").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
#ifndef PDG_NO_64BIT
        v8::Local<v8::Signature> Deserialize_8_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_8_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_8, v8::Local<v8::Value>(), Deserialize_8_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_8").ToLocalChecked(), Deserialize_8_Tpl);
        v8::Local<v8::Signature> Deserialize_8u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_8u_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_8u, v8::Local<v8::Value>(), Deserialize_8u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_8u").ToLocalChecked(), Deserialize_8u_Tpl);
#endif
        v8::Local<v8::Signature> Deserialize_d_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_d_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_d, v8::Local<v8::Value>(), Deserialize_d_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_d").ToLocalChecked(), Deserialize_d_Tpl);
        v8::Local<v8::Signature> Deserialize_f_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_f_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_f, v8::Local<v8::Value>(), Deserialize_f_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_f").ToLocalChecked(), Deserialize_f_Tpl);
        v8::Local<v8::Signature> Deserialize_4_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_4_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_4, v8::Local<v8::Value>(), Deserialize_4_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_4").ToLocalChecked(), Deserialize_4_Tpl);
        v8::Local<v8::Signature> Deserialize_4u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_4u_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_4u, v8::Local<v8::Value>(), Deserialize_4u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_4u").ToLocalChecked(), Deserialize_4u_Tpl);
        v8::Local<v8::Signature> Deserialize_3u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_3u_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_3u, v8::Local<v8::Value>(), Deserialize_3u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_3u").ToLocalChecked(), Deserialize_3u_Tpl);
        v8::Local<v8::Signature> Deserialize_2_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_2_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_2, v8::Local<v8::Value>(), Deserialize_2_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_2").ToLocalChecked(), Deserialize_2_Tpl);
        v8::Local<v8::Signature> Deserialize_2u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_2u_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_2u, v8::Local<v8::Value>(), Deserialize_2u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_2u").ToLocalChecked(), Deserialize_2u_Tpl);
        v8::Local<v8::Signature> Deserialize_1_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_1_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_1, v8::Local<v8::Value>(), Deserialize_1_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_1").ToLocalChecked(), Deserialize_1_Tpl);
        v8::Local<v8::Signature> Deserialize_1u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_1u_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_1u, v8::Local<v8::Value>(), Deserialize_1u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_1u").ToLocalChecked(), Deserialize_1u_Tpl);
        v8::Local<v8::Signature> Deserialize_bool_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_bool_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_bool, v8::Local<v8::Value>(), Deserialize_bool_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_bool").ToLocalChecked(), Deserialize_bool_Tpl);
        v8::Local<v8::Signature> Deserialize_uint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_uint_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_uint, v8::Local<v8::Value>(), Deserialize_uint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_uint").ToLocalChecked(), Deserialize_uint_Tpl);
        v8::Local<v8::Signature> Deserialize_color_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_color_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_color, v8::Local<v8::Value>(), Deserialize_color_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_color").ToLocalChecked(), Deserialize_color_Tpl);
        v8::Local<v8::Signature> Deserialize_offset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_offset_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_offset, v8::Local<v8::Value>(), Deserialize_offset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_offset").ToLocalChecked(), Deserialize_offset_Tpl);
        v8::Local<v8::Signature> Deserialize_point_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_point_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_point, v8::Local<v8::Value>(), Deserialize_point_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_point").ToLocalChecked(), Deserialize_point_Tpl);
        v8::Local<v8::Signature> Deserialize_vector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_vector_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_vector, v8::Local<v8::Value>(), Deserialize_vector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_vector").ToLocalChecked(), Deserialize_vector_Tpl);
        v8::Local<v8::Signature> Deserialize_rect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_rect_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_rect, v8::Local<v8::Value>(), Deserialize_rect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_rect").ToLocalChecked(), Deserialize_rect_Tpl);
        v8::Local<v8::Signature> Deserialize_rotr_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_rotr_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_rotr, v8::Local<v8::Value>(), Deserialize_rotr_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_rotr").ToLocalChecked(), Deserialize_rotr_Tpl);
        v8::Local<v8::Signature> Deserialize_quad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_quad_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_quad, v8::Local<v8::Value>(), Deserialize_quad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_quad").ToLocalChecked(), Deserialize_quad_Tpl);
        v8::Local<v8::Signature> Deserialize_str_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_str_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_str, v8::Local<v8::Value>(), Deserialize_str_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_str").ToLocalChecked(), Deserialize_str_Tpl);
        v8::Local<v8::Signature> Deserialize_mem_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_mem_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_mem, v8::Local<v8::Value>(), Deserialize_mem_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_mem").ToLocalChecked(), Deserialize_mem_Tpl);
        v8::Local<v8::Signature> Deserialize_memGetLen_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_memGetLen_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_memGetLen, v8::Local<v8::Value>(), Deserialize_memGetLen_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_memGetLen").ToLocalChecked(), Deserialize_memGetLen_Tpl);
        v8::Local<v8::Signature> Deserialize_obj_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_obj_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_obj, v8::Local<v8::Value>(), Deserialize_obj_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_obj").ToLocalChecked(), Deserialize_obj_Tpl);
        v8::Local<v8::Signature> Deserialize_ref_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Deserialize_ref_Tpl =
            v8::FunctionTemplate::New(isolate, Deserialize_ref, v8::Local<v8::Value>(), Deserialize_ref_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "deserialize_ref").ToLocalChecked(), Deserialize_ref_Tpl);
        v8::Local<v8::Signature> SetDataPtr_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetDataPtr_Tpl =
            v8::FunctionTemplate::New(isolate, SetDataPtr, v8::Local<v8::Value>(), SetDataPtr_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setDataPtr").ToLocalChecked(), SetDataPtr_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void DeserializerWrap::Deserialize_d(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            double val = self->deserialize_d();
            { args.GetReturnValue().Set( v8::Number::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_f(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            float val = self->deserialize_f();
            { args.GetReturnValue().Set( v8::Number::New(isolate, val) ); return; };
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
    }
#ifndef PDG_NO_64BIT

    void DeserializerWrap::Deserialize_8(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            int64 val = self->deserialize_8();
            { args.GetReturnValue().Set( v8::Number::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_8u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint64 val = self->deserialize_8u();
            { args.GetReturnValue().Set( v8::Number::New(isolate, val) ); return; };
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
    }
#endif

    void DeserializerWrap::Deserialize_4(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            int32 val = self->deserialize_4();
            { args.GetReturnValue().Set( v8::Integer::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_4u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint32 val = self->deserialize_4u();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_3u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint32 val = self->deserialize_3u();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_2(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            int16 val = self->deserialize_2();
            { args.GetReturnValue().Set( v8::Integer::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_2u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint16 val = self->deserialize_2u();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_1(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            int8 val = self->deserialize_1();
            { args.GetReturnValue().Set( v8::Integer::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_1u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint8 val = self->deserialize_1u();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_bool(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            bool val = self->deserialize_bool();
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_uint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint32 val = self->deserialize_uint();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_color(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Color]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Color val = self->deserialize_color();
            { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_offset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Offset]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Offset val = self->deserialize_offset();
            { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_point(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Point val = self->deserialize_point();
            { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_vector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Vector]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Vector val = self->deserialize_vector();
            { args.GetReturnValue().Set( v8_MakeJavascriptVector(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_rect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Rect val = self->deserialize_rect();
            { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_rotr(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object RotatedRect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            RotatedRect val = self->deserialize_rotr();
            { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_quad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Quad]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            Quad val = self->deserialize_quad();
            { args.GetReturnValue().Set( v8_MakeJavascriptQuad(isolate, val) ); return; };
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
    }

    void DeserializerWrap::Deserialize_str(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            std::string mystr;
            self->deserialize_string(mystr);
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, mystr.c_str()).ToLocalChecked() ); return; };
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
    }

    void DeserializerWrap::Deserialize_strGetLen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint32 len = self->deserialize_strGetLen();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, len) ); return; };
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
    }

    void DeserializerWrap::Deserialize_mem(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object MemBlock]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        size_t len, len2;
        try
        {
            len = self->deserialize_memGetLen();
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
        char* mem = (char*) std::malloc(len);
        try
        {
            len2 = self->deserialize_mem(mem, len);
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
        if (len2 != len)
        {
            std::ostringstream excpt_;
            excpt_ << "Deserializer internal error, deserialized memory length mismatch " << len << " (" << (void*)len << ") != " << len2 << " (" << (void*)len2 << ")";
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));

        }

        MemBlock* memBlock = new MemBlock(mem, len, true);
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

    void DeserializerWrap::Deserialize_memGetLen(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            uint32 len = self->deserialize_memGetLen();
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, len) ); return; };
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
    }

    void DeserializerWrap::SetDataPtr(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({[string Binary]|[object MemBlock]} data)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[0]->IsString() && !args[0]->IsObject())
        {
            std::ostringstream excpt_;
            excpt_ << "argument 1 (mem) must be either a binary string or an object of type MemBlock";
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
            self->setDataPtr(ptr, bytes);
        }
        else
        {
            REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
            self->setDataPtr(memBlock->ptr, memBlock->bytes);
        }
        args.GetReturnValue().SetUndefined();
    }

    void DeserializerWrap::Deserialize_obj(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        self->mDeserializerScriptObj.Reset(isolate, args.This());
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ISerializable]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            ISerializable* obj = self->deserialize_obj();
            SCRIPT_DEBUG_ONLY( if (obj->mISerializableScriptObj.IsEmpty())
            {
                std::cerr << __func__<<":"<< 361 << " - NIL JS Object (" "obj->mISerializableScriptObj" "|"<<*((void**)&(obj->mISerializableScriptObj))<<")\n";
            }
            else if (!obj->mISerializableScriptObj->IsObject())
            {
                std::cerr << __func__<<":"<< 361 << " - NOT JS Object (" "obj->mISerializableScriptObj" "|"<<*((void**)&(obj->mISerializableScriptObj))<<") : " << (obj->mISerializableScriptObj.IsEmpty() ? "empty" : obj->mISerializableScriptObj->IsArray() ? "array" : obj->mISerializableScriptObj->IsFunction() ? "function" : obj->mISerializableScriptObj->IsStringObject() ? "string (object)" : obj->mISerializableScriptObj->IsString() ? "string" : obj->mISerializableScriptObj->IsNull() ? "null" : obj->mISerializableScriptObj->IsUndefined() ? "undefined" : obj->mISerializableScriptObj->IsNumberObject() ? "number (object)" : obj->mISerializableScriptObj->IsNumber() ? "number" : obj->mISerializableScriptObj->IsBoolean() ? "boolean" : obj->mISerializableScriptObj->IsDate() ? "date" : obj->mISerializableScriptObj->IsRegExp() ? "regexp" : obj->mISerializableScriptObj->IsNativeError() ? "error" : obj->mISerializableScriptObj->IsObject() ? "object" : "unknown") << "\n";
            }
            else
            {
                v8::Local<v8::Object> obj_ = obj->mISerializableScriptObj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                    v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                    char* objName = *objNameStr;
                    ISerializableWrap* obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                    if (!obj__)
                {
                    v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                        if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                    {
                        obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                            obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                    }
                    if (obj__)
                    {
                        std::cout << __func__<<":"<< 361 << " - JS Object (""obj->mISerializableScriptObj""|"<<*((void**)&(obj->mISerializableScriptObj))<<"): " << objName << " - is a subclass of C++ ""ISerializable""\n";
                    }
                    else
                    {
                        std::cout << __func__<<":"<< 361 << " - JS Object (""obj->mISerializableScriptObj""|"<<*((void**)&(obj->mISerializableScriptObj))<<"): " << objName << " - does not wrap ""ISerializable""\n";
                    }
                }
                else
                {
                    ISerializable* obj = dynamic_cast<ISerializable*>(obj__->getCppObject());
                        std::cout << __func__<<":"<< 361 << " - JS Object (""obj->mISerializableScriptObj""|" << *((void**)&(obj->mISerializableScriptObj)) << "): " << objName<<" - wraps C++ ""ISerializable"" ("<<(void*)obj<<")\n";
                }
            } )
                if (!obj) { args.GetReturnValue().SetNull(); return; };
            if (obj->mISerializableScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ISerializableWrap::NewFromCpp(isolate, obj) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, obj->mISerializableScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
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

    void DeserializerWrap::Deserialize_ref(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DeserializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DeserializerWrap>(args.This());
        Deserializer* self = dynamic_cast<Deserializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            v8::Local<v8::Object> obj = *self->deserialize_ref< v8::Local<v8::Object> >();
            { args.GetReturnValue().Set( obj ); return; };
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

    void RegisterSerializableClass(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(function klass)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsFunction())
        {
            v8_ThrowArgTypeException(isolate, 1, "a function (""constructorFunc"")");
            return;
        }
        v8::Local<v8::Function> constructorFunc = v8::Local<v8::Function>::Cast(args[1 -1]);;
        v8::Local<v8::Value> objVal = ([&]() -> v8::Local<v8::Value>
        {
            if (constructorFunc.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            v8::TryCatch try_catch(isolate);
                v8::MaybeLocal<v8::Value> maybe = constructorFunc->CallAsConstructor(isolate->GetCurrentContext(), 0, 0);
                if (try_catch.HasCaught())
            {
                return v8::Local<v8::Value>();
            }
            if (maybe.IsEmpty())
            {
                return v8::Local<v8::Value>();
            }
            return maybe.ToLocalChecked();
        }());
        v8::Local<v8::Object> obj = ([&]() -> v8::Local<v8::Object>
        {
            if (objVal.IsEmpty())
            {
                isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8Literal(isolate, "Cannot convert empty value to object")));
                    return v8::Local<v8::Object>();
            }
            if (objVal->IsNull() || objVal->IsUndefined())
            {
                isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8Literal(isolate, "Cannot convert null/undefined value to object")));
                    return v8::Local<v8::Object>();
            }
            v8::MaybeLocal<v8::Object> maybe = objVal->ToObject(isolate->GetCurrentContext());
                if (maybe.IsEmpty())
            {
                isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8Literal(isolate, "Cannot convert value to object")));
                    return v8::Local<v8::Object>();
            }
            return maybe.ToLocalChecked();
        }());
        SCRIPT_DEBUG_ONLY( if (obj.IsEmpty())
        {
            std::cerr << __func__<<":"<< 395 << " - NIL JS Object (" "obj" "|"<<*((void**)&(obj))<<")\n";
        }
        else if (!obj->IsObject())
        {
            std::cerr << __func__<<":"<< 395 << " - NOT JS Object (" "obj" "|"<<*((void**)&(obj))<<") : " << (obj.IsEmpty() ? "empty" : obj->IsArray() ? "array" : obj->IsFunction() ? "function" : obj->IsStringObject() ? "string (object)" : obj->IsString() ? "string" : obj->IsNull() ? "null" : obj->IsUndefined() ? "undefined" : obj->IsNumberObject() ? "number (object)" : obj->IsNumber() ? "number" : obj->IsBoolean() ? "boolean" : obj->IsDate() ? "date" : obj->IsRegExp() ? "regexp" : obj->IsNativeError() ? "error" : obj->IsObject() ? "object" : "unknown") << "\n";
        }
        else
        {
            v8::Local<v8::Object> obj_ = obj->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                v8::String::Utf8Value objNameStr(isolate, obj_->ToString(isolate->GetCurrentContext()).ToLocalChecked());
                char* objName = *objNameStr;
                ISerializableWrap* obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                if (!obj__)
            {
                v8::Local<v8::Value> protoVal_ = obj_->GetPrototypeV2();
                    if (!protoVal_.IsEmpty() && protoVal_->IsObject())
                {
                    obj_ = protoVal_->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                        obj__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap(obj_));
                }
                if (obj__)
                {
                    std::cout << __func__<<":"<< 395 << " - JS Object (""obj""|"<<*((void**)&(obj))<<"): " << objName << " - is a subclass of C++ ""ISerializable""\n";
                }
                else
                {
                    std::cout << __func__<<":"<< 395 << " - JS Object (""obj""|"<<*((void**)&(obj))<<"): " << objName << " - does not wrap ""ISerializable""\n";
                }
            }
            else
            {
                ISerializable* obj = dynamic_cast<ISerializable*>(obj__->getCppObject());
                    std::cout << __func__<<":"<< 395 << " - JS Object (""obj""|" << *((void**)&(obj)) << "): " << objName<<" - wraps C++ ""ISerializable"" ("<<(void*)obj<<")\n";
            }
        } );
        ISerializable* nativeSerializable = 0;
        if ((objVal)->IsObject())
        {
            v8::Local<v8::Object> nativeSerializable_scriptObj_ = (objVal)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
            ISerializableWrap* nativeSerializable__ = dynamic_cast<ISerializableWrap*>(pdg::v8script::safe_unwrap_object_wrap_or_prototype(isolate, objVal, &nativeSerializable_scriptObj_));
            if (nativeSerializable__)
            {
                nativeSerializable = nativeSerializable__->getCppObject();
            }
        };
        uint32 classTag = 0;
        if ((!obj->IsNull() && obj->Has(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getMyClassTag").ToLocalChecked()).ToChecked()))
        {
            v8::Local<v8::Value> getMyClassTagVal = ([&]() -> v8::Local<v8::Value>
            {
                v8::MaybeLocal<v8::Value> maybe = obj->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "getMyClassTag").ToLocalChecked());
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Object>();
                }
                return maybe.ToLocalChecked();
            }());
            if (!getMyClassTagVal->IsFunction())
            {
                std::ostringstream msg;
                msg << "argument 1: ISerializable subclass " << v8_GetObjectClassName(obj) << " getMyClassTag property is not a function!!";
                std::ostringstream excpt_;
                excpt_ << msg.str().c_str();
                isolate->ThrowException( v8::Exception::Error( ([&]()
                {
                    v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                        return maybe.IsEmpty() ?
                        v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                }())));
                return;
            }
            v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(getMyClassTagVal);
            v8::Local<v8::Value> classTagVal = ([&]() -> v8::Local<v8::Value>
            {
                if (func.IsEmpty())
                {
                    return v8::Local<v8::Value>();
                }
                v8::MaybeLocal<v8::Value> maybe = func->Call(isolate->GetCurrentContext(), obj, 0, 0);
                    if (maybe.IsEmpty())
                {
                    return v8::Local<v8::Value>();
                }
                return maybe.ToLocalChecked();
            }());
            classTag = classTagVal->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        }
        else if (nativeSerializable)
        {
            classTag = nativeSerializable->getMyClassTag();
        }
        else
        {
            std::ostringstream msg;
            msg << "argument 1: ISerializable subclass " << v8_GetObjectClassName(obj) << " missing getMyClassTag() Function!!";
            std::ostringstream excpt_;
            excpt_ << msg.str().c_str();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        Deserializer::registerScriptClass(classTag, constructorFunc);
        args.GetReturnValue().SetUndefined();
    }

    void CleanupDeserializerScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    DeserializerWrap::DeserializerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Deserializer(args);
        if (!cppPtr_ && !s_Deserializer_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Deserializer" " instance")));
            };
        }
    }

    DeserializerWrap::~DeserializerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Deserializer* New_Deserializer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Deserializer_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new Deserializer();
    }

}
