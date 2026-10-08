// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/animation/animation_helper.cpp
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

#ifdef PDG_USING_JAVASCRIPT_CORE
    static void IAnimationHelper_finalize(JSObjectRef object)
    {
        auto* helper = static_cast<IAnimationHelper*>(JSObjectGetPrivate(object));
        if (!helper) return;
        helper->mIAnimationHelperScriptObj = nullptr;
        JSObjectSetPrivate(object, nullptr);
        helper->release();
    }
#else
    IAnimationHelper* New_IAnimationHelper(const v8::FunctionCallbackInfo<v8::Value>& args);
    IAnimationHelperWrap::IAnimationHelperWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(New_IAnimationHelper(args)) {}
    IAnimationHelperWrap::~IAnimationHelperWrap()
    {
        if (cppPtr_)
        {
            cppPtr_->mIAnimationHelperScriptObj.Reset();
            cppPtr_->release();
        }
    }
#endif
    bool s_IAnimationHelper_InNewFromCpp = false;

    void IAnimationHelperWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        IAnimationHelperWrap* objWrapper = new IAnimationHelperWrap(args);
        objWrapper->Wrap(args.This());
        if (auto* cppObj = objWrapper->getCppObject()) { v8::Local<v8::Object> obj = args.This(); cppObj->mIAnimationHelperScriptObj.Reset(isolate, obj); cppObj->mIAnimationHelperScriptObj.SetWeak(); cppObj->addRef(); if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject(); };
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> IAnimationHelperWrap::NewFromCpp(v8::Isolate* isolate, IAnimationHelper* cppObj)
    {
        s_IAnimationHelper_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_IAnimationHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_IAnimationHelper_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        IAnimationHelperWrap* objWrapper = jswrap::ObjectWrap::Unwrap<IAnimationHelperWrap>(instance);
        { [[maybe_unused]] v8::Local<v8::Object> obj = instance; cppObj->mIAnimationHelperScriptObj.Reset(isolate, obj); cppObj->mIAnimationHelperScriptObj.SetWeak(); cppObj->addRef(); if (auto* script = dynamic_cast<ScriptAnimationHelper*>(cppObj)) script->initializeScriptObject(); }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) objWrapper->cppPtr_->release();
        objWrapper->cppPtr_ = cppObj;
        s_IAnimationHelper_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> IAnimationHelperWrap::constructorTpl_;

    void IAnimationHelperWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "IAnimationHelper").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }

    void CleanupIAnimationHelperScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

}
