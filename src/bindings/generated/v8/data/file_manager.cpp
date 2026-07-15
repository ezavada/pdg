// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/file_manager.cpp
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

    FileManagerWrap::FileManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) { }

    FileManagerWrap::~FileManagerWrap() { }

    void FileManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FileManagerWrap* objWrapper = new FileManagerWrap(args);
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
    v8::Persistent<v8::Object> FileManagerWrap::instance_;
    bool FileManagerWrap::instanced_ = false;

    v8::Local<v8::Object> FileManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    v8::Persistent<v8::FunctionTemplate> FileManagerWrap::constructorTpl_;

    void FileManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "FileManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> FindFirst_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FindFirst_Tpl =
            v8::FunctionTemplate::New(isolate, FindFirst, v8::Local<v8::Value>(), FindFirst_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "findFirst").ToLocalChecked(), FindFirst_Tpl);
        v8::Local<v8::Signature> FindNext_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FindNext_Tpl =
            v8::FunctionTemplate::New(isolate, FindNext, v8::Local<v8::Value>(), FindNext_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "findNext").ToLocalChecked(), FindNext_Tpl);
        v8::Local<v8::Signature> FindClose_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FindClose_Tpl =
            v8::FunctionTemplate::New(isolate, FindClose, v8::Local<v8::Value>(), FindClose_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "findClose").ToLocalChecked(), FindClose_Tpl);
        v8::Local<v8::Signature> GetApplicationDataDirectory_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetApplicationDataDirectory_Tpl =
            v8::FunctionTemplate::New(isolate, GetApplicationDataDirectory, v8::Local<v8::Value>(), GetApplicationDataDirectory_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ApplicationDataDirectory").ToLocalChecked(), GetApplicationDataDirectory_Tpl);
        v8::Local<v8::Signature> GetApplicationDirectory_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetApplicationDirectory_Tpl =
            v8::FunctionTemplate::New(isolate, GetApplicationDirectory, v8::Local<v8::Value>(), GetApplicationDirectory_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ApplicationDirectory").ToLocalChecked(), GetApplicationDirectory_Tpl);
        v8::Local<v8::Signature> GetApplicationResourceDirectory_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetApplicationResourceDirectory_Tpl =
            v8::FunctionTemplate::New(isolate, GetApplicationResourceDirectory, v8::Local<v8::Value>(), GetApplicationResourceDirectory_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ApplicationResourceDirectory").ToLocalChecked(), GetApplicationResourceDirectory_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void FileManagerWrap::FindFirst(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(string inFindName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inFindName"")");
            return;
        }
        v8::String::Utf8Value inFindName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inFindName = *inFindName_Str;;
        FindDataT* ioFindDataPtr = new FindDataT;
        bool found = OS::findFirst(inFindName, *ioFindDataPtr);
        v8::Local<v8::Object> jsFindData = v8_ObjectCreateEmpty(isolate, ioFindDataPtr);
        v8::Local<v8::Value> nodeName = v8::String::NewFromUtf8(isolate, ioFindDataPtr->nodeName).ToLocalChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "nodeName").ToLocalChecked(), nodeName).ToChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "isDirectory").ToLocalChecked(), v8::Boolean::New(isolate, ioFindDataPtr->isDirectory)).ToChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "found").ToLocalChecked(), v8::Boolean::New(isolate, found)).ToChecked();
        { args.GetReturnValue().Set( jsFindData ); return; };
    }
    void FileManagerWrap::FindNext(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "object" " function" "(object inFindData)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, jsFindData);
        FindDataT* ioFindDataPtr = static_cast<FindDataT*>(jsFindData->GetAlignedPointerFromInternalField(0));
        if (!ioFindDataPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "findNext must only be called with the object returned by findFirst";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        bool found = OS::findNext(*ioFindDataPtr);
        v8::Local<v8::Value> nodeName = v8::String::NewFromUtf8(isolate, ioFindDataPtr->nodeName).ToLocalChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "nodeName").ToLocalChecked(), nodeName).ToChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "isDirectory").ToLocalChecked(), v8::Boolean::New(isolate, ioFindDataPtr->isDirectory)).ToChecked();
        (void)jsFindData->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "found").ToLocalChecked(), v8::Boolean::New(isolate, found)).ToChecked();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, found) ); return; };
    }
    void FileManagerWrap::FindClose(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(object inFindData)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, jsFindData);
        FindDataT* ioFindDataPtr = static_cast<FindDataT*>(jsFindData->GetAlignedPointerFromInternalField(0));
        if (!ioFindDataPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "findClose must only be called with the object returned by findFirst";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        OS::findClose(*ioFindDataPtr);
        delete ioFindDataPtr;
        args.GetReturnValue().SetUndefined();
    }
    void FileManagerWrap::GetApplicationDataDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, OS::getApplicationDataDirectory()).ToLocalChecked() ); return; };
    }
    void FileManagerWrap::GetApplicationDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, OS::getApplicationDirectory()).ToLocalChecked() ); return; };
    }
    void FileManagerWrap::GetApplicationResourceDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, OS::getApplicationResourceDirectory()).ToLocalChecked() ); return; };
    }

}
