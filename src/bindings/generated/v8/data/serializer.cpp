// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/serializer.cpp
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

    bool s_Serializer_InNewFromCpp = false;

    void SerializerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = new SerializerWrap(args);
        objWrapper->Wrap(args.This());
        Serializer* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mSerializerScriptObj.Reset(isolate, args.This());
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
    v8::Local<v8::Object> SerializerWrap::NewFromCpp(v8::Isolate* isolate, Serializer* cppObj)
    {
        s_Serializer_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Serializer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Serializer_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mSerializerScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Serializer_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SerializerWrap::constructorTpl_;

    void SerializerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Serializer").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
#ifndef PDG_NO_64BIT
        v8::Local<v8::Signature> Serialize_8_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_8_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_8, v8::Local<v8::Value>(), Serialize_8_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_8").ToLocalChecked(), Serialize_8_Tpl);
        v8::Local<v8::Signature> Serialize_8u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_8u_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_8u, v8::Local<v8::Value>(), Serialize_8u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_8u").ToLocalChecked(), Serialize_8u_Tpl);
        v8::Local<v8::Signature> Sizeof_8_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_8_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_8, v8::Local<v8::Value>(), Sizeof_8_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_8").ToLocalChecked(), Sizeof_8_Tpl);
        v8::Local<v8::Signature> Sizeof_8u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_8u_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_8u, v8::Local<v8::Value>(), Sizeof_8u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_8u").ToLocalChecked(), Sizeof_8u_Tpl);
#endif
        v8::Local<v8::Signature> Serialize_d_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_d_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_d, v8::Local<v8::Value>(), Serialize_d_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_d").ToLocalChecked(), Serialize_d_Tpl);
        v8::Local<v8::Signature> Serialize_f_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_f_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_f, v8::Local<v8::Value>(), Serialize_f_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_f").ToLocalChecked(), Serialize_f_Tpl);
        v8::Local<v8::Signature> Serialize_4_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_4_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_4, v8::Local<v8::Value>(), Serialize_4_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_4").ToLocalChecked(), Serialize_4_Tpl);
        v8::Local<v8::Signature> Serialize_4u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_4u_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_4u, v8::Local<v8::Value>(), Serialize_4u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_4u").ToLocalChecked(), Serialize_4u_Tpl);
        v8::Local<v8::Signature> Serialize_3u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_3u_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_3u, v8::Local<v8::Value>(), Serialize_3u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_3u").ToLocalChecked(), Serialize_3u_Tpl);
        v8::Local<v8::Signature> Serialize_2_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_2_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_2, v8::Local<v8::Value>(), Serialize_2_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_2").ToLocalChecked(), Serialize_2_Tpl);
        v8::Local<v8::Signature> Serialize_2u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_2u_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_2u, v8::Local<v8::Value>(), Serialize_2u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_2u").ToLocalChecked(), Serialize_2u_Tpl);
        v8::Local<v8::Signature> Serialize_1_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_1_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_1, v8::Local<v8::Value>(), Serialize_1_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_1").ToLocalChecked(), Serialize_1_Tpl);
        v8::Local<v8::Signature> Serialize_1u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_1u_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_1u, v8::Local<v8::Value>(), Serialize_1u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_1u").ToLocalChecked(), Serialize_1u_Tpl);
        v8::Local<v8::Signature> Serialize_bool_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_bool_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_bool, v8::Local<v8::Value>(), Serialize_bool_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_bool").ToLocalChecked(), Serialize_bool_Tpl);
        v8::Local<v8::Signature> Serialize_uint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_uint_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_uint, v8::Local<v8::Value>(), Serialize_uint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_uint").ToLocalChecked(), Serialize_uint_Tpl);
        v8::Local<v8::Signature> Serialize_color_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_color_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_color, v8::Local<v8::Value>(), Serialize_color_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_color").ToLocalChecked(), Serialize_color_Tpl);
        v8::Local<v8::Signature> Serialize_offset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_offset_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_offset, v8::Local<v8::Value>(), Serialize_offset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_offset").ToLocalChecked(), Serialize_offset_Tpl);
        v8::Local<v8::Signature> Serialize_point_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_point_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_point, v8::Local<v8::Value>(), Serialize_point_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_point").ToLocalChecked(), Serialize_point_Tpl);
        v8::Local<v8::Signature> Serialize_vector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_vector_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_vector, v8::Local<v8::Value>(), Serialize_vector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_vector").ToLocalChecked(), Serialize_vector_Tpl);
        v8::Local<v8::Signature> Serialize_rect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_rect_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_rect, v8::Local<v8::Value>(), Serialize_rect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_rect").ToLocalChecked(), Serialize_rect_Tpl);
        v8::Local<v8::Signature> Serialize_rotr_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_rotr_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_rotr, v8::Local<v8::Value>(), Serialize_rotr_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_rotr").ToLocalChecked(), Serialize_rotr_Tpl);
        v8::Local<v8::Signature> Serialize_quad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_quad_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_quad, v8::Local<v8::Value>(), Serialize_quad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_quad").ToLocalChecked(), Serialize_quad_Tpl);
        v8::Local<v8::Signature> Serialize_str_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_str_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_str, v8::Local<v8::Value>(), Serialize_str_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_str").ToLocalChecked(), Serialize_str_Tpl);
        v8::Local<v8::Signature> Serialize_mem_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_mem_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_mem, v8::Local<v8::Value>(), Serialize_mem_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_mem").ToLocalChecked(), Serialize_mem_Tpl);
        v8::Local<v8::Signature> Serialize_obj_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_obj_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_obj, v8::Local<v8::Value>(), Serialize_obj_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_obj").ToLocalChecked(), Serialize_obj_Tpl);
        v8::Local<v8::Signature> Serialize_ref_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Serialize_ref_Tpl =
            v8::FunctionTemplate::New(isolate, Serialize_ref, v8::Local<v8::Value>(), Serialize_ref_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "serialize_ref").ToLocalChecked(), Serialize_ref_Tpl);
        v8::Local<v8::Signature> Sizeof_d_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_d_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_d, v8::Local<v8::Value>(), Sizeof_d_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_d").ToLocalChecked(), Sizeof_d_Tpl);
        v8::Local<v8::Signature> Sizeof_f_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_f_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_f, v8::Local<v8::Value>(), Sizeof_f_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_f").ToLocalChecked(), Sizeof_f_Tpl);
        v8::Local<v8::Signature> Sizeof_4_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_4_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_4, v8::Local<v8::Value>(), Sizeof_4_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_4").ToLocalChecked(), Sizeof_4_Tpl);
        v8::Local<v8::Signature> Sizeof_4u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_4u_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_4u, v8::Local<v8::Value>(), Sizeof_4u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_4u").ToLocalChecked(), Sizeof_4u_Tpl);
        v8::Local<v8::Signature> Sizeof_3u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_3u_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_3u, v8::Local<v8::Value>(), Sizeof_3u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_3u").ToLocalChecked(), Sizeof_3u_Tpl);
        v8::Local<v8::Signature> Sizeof_2_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_2_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_2, v8::Local<v8::Value>(), Sizeof_2_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_2").ToLocalChecked(), Sizeof_2_Tpl);
        v8::Local<v8::Signature> Sizeof_2u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_2u_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_2u, v8::Local<v8::Value>(), Sizeof_2u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_2u").ToLocalChecked(), Sizeof_2u_Tpl);
        v8::Local<v8::Signature> Sizeof_1_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_1_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_1, v8::Local<v8::Value>(), Sizeof_1_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_1").ToLocalChecked(), Sizeof_1_Tpl);
        v8::Local<v8::Signature> Sizeof_1u_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_1u_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_1u, v8::Local<v8::Value>(), Sizeof_1u_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_1u").ToLocalChecked(), Sizeof_1u_Tpl);
        v8::Local<v8::Signature> Sizeof_bool_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_bool_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_bool, v8::Local<v8::Value>(), Sizeof_bool_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_bool").ToLocalChecked(), Sizeof_bool_Tpl);
        v8::Local<v8::Signature> Sizeof_uint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_uint_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_uint, v8::Local<v8::Value>(), Sizeof_uint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_uint").ToLocalChecked(), Sizeof_uint_Tpl);
        v8::Local<v8::Signature> Sizeof_color_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_color_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_color, v8::Local<v8::Value>(), Sizeof_color_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_color").ToLocalChecked(), Sizeof_color_Tpl);
        v8::Local<v8::Signature> Sizeof_offset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_offset_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_offset, v8::Local<v8::Value>(), Sizeof_offset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_offset").ToLocalChecked(), Sizeof_offset_Tpl);
        v8::Local<v8::Signature> Sizeof_point_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_point_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_point, v8::Local<v8::Value>(), Sizeof_point_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_point").ToLocalChecked(), Sizeof_point_Tpl);
        v8::Local<v8::Signature> Sizeof_vector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_vector_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_vector, v8::Local<v8::Value>(), Sizeof_vector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_vector").ToLocalChecked(), Sizeof_vector_Tpl);
        v8::Local<v8::Signature> Sizeof_rect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_rect_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_rect, v8::Local<v8::Value>(), Sizeof_rect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_rect").ToLocalChecked(), Sizeof_rect_Tpl);
        v8::Local<v8::Signature> Sizeof_rotr_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_rotr_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_rotr, v8::Local<v8::Value>(), Sizeof_rotr_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_rotr").ToLocalChecked(), Sizeof_rotr_Tpl);
        v8::Local<v8::Signature> Sizeof_quad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_quad_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_quad, v8::Local<v8::Value>(), Sizeof_quad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_quad").ToLocalChecked(), Sizeof_quad_Tpl);
        v8::Local<v8::Signature> Sizeof_str_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_str_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_str, v8::Local<v8::Value>(), Sizeof_str_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_str").ToLocalChecked(), Sizeof_str_Tpl);
        v8::Local<v8::Signature> Sizeof_mem_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_mem_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_mem, v8::Local<v8::Value>(), Sizeof_mem_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_mem").ToLocalChecked(), Sizeof_mem_Tpl);
        v8::Local<v8::Signature> Sizeof_obj_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_obj_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_obj, v8::Local<v8::Value>(), Sizeof_obj_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_obj").ToLocalChecked(), Sizeof_obj_Tpl);
        v8::Local<v8::Signature> Sizeof_ref_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Sizeof_ref_Tpl =
            v8::FunctionTemplate::New(isolate, Sizeof_ref, v8::Local<v8::Value>(), Sizeof_ref_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sizeof_ref").ToLocalChecked(), Sizeof_ref_Tpl);
        v8::Local<v8::Signature> GetDataSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDataSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetDataSize, v8::Local<v8::Value>(), GetDataSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDataSize").ToLocalChecked(), GetDataSize_Tpl);
        v8::Local<v8::Signature> GetDataPtr_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDataPtr_Tpl =
            v8::FunctionTemplate::New(isolate, GetDataPtr, v8::Local<v8::Value>(), GetDataPtr_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getDataPtr").ToLocalChecked(), GetDataPtr_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void SerializerWrap::Serialize_d(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->serialize_d(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_f(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->serialize_f(val);
        args.GetReturnValue().SetUndefined();
    }
#ifndef PDG_NO_64BIT

    void SerializerWrap::Serialize_8(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->serialize_8(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_8u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->serialize_8u(val);
        args.GetReturnValue().SetUndefined();
    }
#endif

    void SerializerWrap::Serialize_4(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -2147483648.0 || val_temp > 2147483647.0 || val_temp != (long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-2147483648, 2147483647] (""val"")");
            return;
        }
        int32 val = (int32)val_temp;
        self->serialize_4(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_4u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 4294967295.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 4294967295] (""val"")");
            return;
        }
        uint32 val = (uint32)val_temp;
        self->serialize_4u(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_3u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 16777215.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 16777215] (""val"")");
            return;
        }
        uint32 val = (uint32)val_temp;
        self->serialize_3u(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_2(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        long val_temp = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -32768 || val_temp > 32767)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-32768, 32767] (""val"")");
            return;
        }
        int16 val = (int16)val_temp;
        self->serialize_2(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_2u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 65535.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 65535] (""val"")");
            return;
        }
        uint16 val = (uint16)val_temp;
        self->serialize_2u(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_1(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        long val_temp = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -128 || val_temp > 127)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-128, 127] (""val"")");
            return;
        }
        int8 val = (int8)val_temp;
        self->serialize_1(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_1u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 255.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 255] (""val"")");
            return;
        }
        uint8 val = (uint8)val_temp;
        self->serialize_1u(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_bool(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(boolean val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""val"")");
            return;
        }
        bool val = args[1 -1]->BooleanValue(isolate);
        self->serialize_bool(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_uint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        unsigned long val = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        self->serialize_uint(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_color(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Color] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsColor(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        }
        pdg::Color val = v8_ValueToColor(isolate, args[1 -1]);
        self->serialize_color(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_offset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Offset] val)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Offset val = v8_ValueToOffset(isolate, args[1 -1]);
        self->serialize_offset(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_point(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] val)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point val = v8_ValueToPoint(isolate, args[1 -1]);
        self->serialize_point(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_vector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Vector] val)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Vector val = v8_ValueToVector(isolate, args[1 -1]);
        self->serialize_vector(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_rect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Rect] val)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect r = v8_ValueToRect(isolate, args[1 -1]);
        self->serialize_rect(r);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_rotr(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object RotatedRect] val)" " - " "").ToLocalChecked() ); return; };
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
        pdg::RotatedRect val = v8_ValueToRotatedRect(isolate, args[1 -1]);
        self->serialize_rotr(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_quad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Quad] val)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Quad val = v8_ValueToQuad(isolate, args[1 -1]);
        self->serialize_quad(val);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_str(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string str)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""str"")");
            return;
        }
        v8::String::Utf8Value str_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* str = *str_Str;;
        self->serialize_str(str);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_mem(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({[string Binary]|[object MemBlock]} mem)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        bool isStr = args[0]->IsString();
        if (!isStr && !args[0]->IsObject())
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
        if (isStr)
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(args[0], &bytes);
            self->serialize_mem(ptr, bytes);
        }
        else
        {
            REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
            self->serialize_mem(memBlock->ptr, memBlock->bytes);
        }
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::Serialize_ref(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(object obj)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, obj);
        self->serialize_ref< v8::Local<v8::Object> >(&obj);
        args.GetReturnValue().SetUndefined();
    }

    void SerializerWrap::GetDataSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        uint32 dataSize = self->getDataSize();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, dataSize) ); return; };
    }

    void SerializerWrap::GetDataPtr(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object MemBlock]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        MemBlock* memBlock = new MemBlock((char*)self->getDataPtr(), self->getDataSize(), false);
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

    void SerializerWrap::Sizeof_1(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number int]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        long val_temp = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -128 || val_temp > 127)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-128, 127] (""val"")");
            return;
        }
        int8 val = (int8)val_temp;
        size_t n = self->sizeof_1(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_1u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 255.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 255] (""val"")");
            return;
        }
        uint8 val = (uint8)val_temp;
        size_t n = self->sizeof_1u(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_2(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number int]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        long val_temp = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -32768 || val_temp > 32767)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-32768, 32767] (""val"")");
            return;
        }
        int16 val = (int16)val_temp;
        size_t n = self->sizeof_2(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_2u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 65535.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 65535] (""val"")");
            return;
        }
        uint16 val = (uint16)val_temp;
        size_t n = self->sizeof_2u(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_3u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 16777215.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 16777215] (""val"")");
            return;
        }
        uint32 val = (uint32)val_temp;
        size_t n = self->sizeof_3u(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_4(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number int]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < -2147483648.0 || val_temp > 2147483647.0 || val_temp != (long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [-2147483648, 2147483647] (""val"")");
            return;
        }
        int32 val = (int32)val_temp;
        size_t n = self->sizeof_4(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_4u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val_temp = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (val_temp < 0.0 || val_temp > 4294967295.0 || val_temp != (unsigned long)val_temp)
        {
            v8_ThrowArgTypeException(isolate, 1, "a number in range [0, 4294967295] (""val"")");
            return;
        }
        uint32 val = (uint32)val_temp;
        size_t n = self->sizeof_4u(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }
#ifndef PDG_NO_64BIT

    void SerializerWrap::Sizeof_8(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number int]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        size_t n = self->sizeof_8(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_8u(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        size_t n = self->sizeof_8u(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }
#endif

    void SerializerWrap::Sizeof_f(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "number" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        size_t n = self->sizeof_f(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_d(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "number" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        double val = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        size_t n = self->sizeof_d(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_uint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[number uint]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""val"")");
            return;
        }
        unsigned long val = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        size_t n = self->sizeof_uint(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_str(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "string" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""val"")");
            return;
        }
        v8::String::Utf8Value val_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* val = *val_Str;;
        size_t n = self->sizeof_str(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_bool(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "boolean" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""val"")");
            return;
        }
        bool val = args[1 -1]->BooleanValue(isolate);
        size_t n = self->sizeof_bool(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_point(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Point]" " val) - ").ToLocalChecked() ); return; };
        }
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
        pdg::Point val = v8_ValueToPoint(isolate, args[1 -1]);
        size_t n = self->sizeof_point(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_offset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Offset]" " val) - ").ToLocalChecked() ); return; };
        }
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
        pdg::Offset val = v8_ValueToOffset(isolate, args[1 -1]);
        size_t n = self->sizeof_offset(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_vector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Vector]" " val) - ").ToLocalChecked() ); return; };
        }
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
        pdg::Vector val = v8_ValueToVector(isolate, args[1 -1]);
        size_t n = self->sizeof_vector(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_rect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Rect]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect val = v8_ValueToRect(isolate, args[1 -1]);
        size_t n = self->sizeof_rect(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_rotr(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object RotatedRect]" " val) - ").ToLocalChecked() ); return; };
        }
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
        pdg::RotatedRect val = v8_ValueToRotatedRect(isolate, args[1 -1]);
        size_t n = self->sizeof_rotr(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_quad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Quad]" " val) - ").ToLocalChecked() ); return; };
        }
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
        pdg::Quad val = v8_ValueToQuad(isolate, args[1 -1]);
        size_t n = self->sizeof_quad(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_color(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "[object Color]" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsColor(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        }
        pdg::Color val = v8_ValueToColor(isolate, args[1 -1]);
        size_t n = self->sizeof_color(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_ref(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint] function(" "object" " val) - ").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, val);
        size_t n = self->sizeof_ref< v8::Local<v8::Object> >(&val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_obj(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (args[0]->IsNull())
        {
            size_t n = 3;
            { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
        }
        REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, val, ISerializable);
        size_t n = self->sizeof_obj(val);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void SerializerWrap::Sizeof_mem(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SerializerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SerializerWrap>(args.This());
        Serializer* self = dynamic_cast<Serializer*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "({[string Binary]|[object MemBlock]} mem)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        bool isStr = args[0]->IsString();
        if (!isStr && !args[0]->IsObject())
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
        size_t n = 0;
        if (isStr)
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(args[0], &bytes);
            n = self->sizeof_mem(ptr, bytes);
        }
        else
        {
            REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
            n = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
        }
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, n) ); return; };
    }

    void CleanupSerializerScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    SerializerWrap::SerializerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Serializer(args);
        if (!cppPtr_ && !s_Serializer_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Serializer" " instance")));
            };
        }
    }

    SerializerWrap::~SerializerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Serializer* New_Serializer(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Serializer_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        return new Serializer();
    }

}
