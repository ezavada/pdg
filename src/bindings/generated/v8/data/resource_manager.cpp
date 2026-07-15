// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/data/resource_manager.cpp
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

    static bool s_ResourceManager_InNewFromCpp = false;

    void ResourceManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_ResourceManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "ResourceManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "res"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        ResourceManagerWrap* objWrapper = new ResourceManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> ResourceManagerWrap::instance_;
    bool ResourceManagerWrap::instanced_ = false;

    v8::Local<v8::Object> ResourceManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_ResourceManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_ResourceManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_ResourceManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_ResourceManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    ResourceManager* ResourceManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(val);
        return dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> ResourceManagerWrap::constructorTpl_;

    void ResourceManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ResourceManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetLanguage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLanguage_Tpl =
            v8::FunctionTemplate::New(isolate, GetLanguage, v8::Local<v8::Value>(), GetLanguage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Language").ToLocalChecked(), GetLanguage_Tpl);
        v8::Local<v8::Signature> SetLanguage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLanguage_Tpl =
            v8::FunctionTemplate::New(isolate, SetLanguage, v8::Local<v8::Value>(), SetLanguage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Language").ToLocalChecked(), SetLanguage_Tpl);
        v8::Local<v8::Signature> OpenResourceFile_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> OpenResourceFile_Tpl =
            v8::FunctionTemplate::New(isolate, OpenResourceFile, v8::Local<v8::Value>(), OpenResourceFile_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "openResourceFile").ToLocalChecked(), OpenResourceFile_Tpl);
        v8::Local<v8::Signature> CloseResourceFile_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CloseResourceFile_Tpl =
            v8::FunctionTemplate::New(isolate, CloseResourceFile, v8::Local<v8::Value>(), CloseResourceFile_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "closeResourceFile").ToLocalChecked(), CloseResourceFile_Tpl);
        v8::Local<v8::Signature> GetImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImage_Tpl =
            v8::FunctionTemplate::New(isolate, GetImage, v8::Local<v8::Value>(), GetImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getImage").ToLocalChecked(), GetImage_Tpl);
        v8::Local<v8::Signature> GetImageStrip_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImageStrip_Tpl =
            v8::FunctionTemplate::New(isolate, GetImageStrip, v8::Local<v8::Value>(), GetImageStrip_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getImageStrip").ToLocalChecked(), GetImageStrip_Tpl);
#ifndef PDG_NO_SOUND
        v8::Local<v8::Signature> GetSound_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSound_Tpl =
            v8::FunctionTemplate::New(isolate, GetSound, v8::Local<v8::Value>(), GetSound_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSound").ToLocalChecked(), GetSound_Tpl);
#endif
        v8::Local<v8::Signature> GetString_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetString_Tpl =
            v8::FunctionTemplate::New(isolate, GetString, v8::Local<v8::Value>(), GetString_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getString").ToLocalChecked(), GetString_Tpl);
        v8::Local<v8::Signature> GetResourceSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetResourceSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetResourceSize, v8::Local<v8::Value>(), GetResourceSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getResourceSize").ToLocalChecked(), GetResourceSize_Tpl);
        v8::Local<v8::Signature> GetResource_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetResource_Tpl =
            v8::FunctionTemplate::New(isolate, GetResource, v8::Local<v8::Value>(), GetResource_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getResource").ToLocalChecked(), GetResource_Tpl);
        v8::Local<v8::Signature> GetResourcePaths_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetResourcePaths_Tpl =
            v8::FunctionTemplate::New(isolate, GetResourcePaths, v8::Local<v8::Value>(), GetResourcePaths_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getResourcePaths").ToLocalChecked(), GetResourcePaths_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void ResourceManagerWrap::GetLanguage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        const char* theLanguage = self->getLanguage();
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, theLanguage).ToLocalChecked() ); return; };
    }

    void ResourceManagerWrap::SetLanguage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ResourceManager]" " function" "(string inLanguage)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""theLanguage"")");
            return;
        }
        v8::String::Utf8Value theLanguage_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* theLanguage = *theLanguage_Str;;

        self->setLanguage(theLanguage);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ResourceManagerWrap::OpenResourceFile(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(string filename)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""filename"")");
            return;
        }
        v8::String::Utf8Value filename_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* filename = *filename_Str;;
        int refNum = self->openResourceFile(filename);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, refNum) ); return; };
    }

    void ResourceManagerWrap::CloseResourceFile(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] refNum)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""refNum"")");
            return;
        }
        long refNum = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->closeResourceFile(refNum);
        args.GetReturnValue().SetUndefined();
    }

    void ResourceManagerWrap::GetString(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "([number int] id, [number int] substring = -1)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""id"")");
            return;
        }
        long id = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""substring"")");
            return;
        }
        long substring = (args.Length()<2) ? -1 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        std::string ioStr;
        const char* outStr = self->getString(ioStr, id, substring);
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, outStr).ToLocalChecked() ); return; };
    }

    void ResourceManagerWrap::GetResourceSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(string resourceName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""resourceName"")");
            return;
        }
        v8::String::Utf8Value resourceName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* resourceName = *resourceName_Str;;
        unsigned long resSize = self->getResourceSize(resourceName);
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, resSize) ); return; };
    }

    void ResourceManagerWrap::GetResource(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[string Binary]" " function" "(string resourceName)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""resourceName"")");
            return;
        }
        v8::String::Utf8Value resourceName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* resourceName = *resourceName_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""maxSize"")");
            return;
        }
        long maxSize = (args.Length()<2) ? -1 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        unsigned long bufferSize;
        if (maxSize < 0)
        {
            bufferSize = self->getResourceSize(resourceName);
        }
        else
        {
            bufferSize = maxSize;
        }
        uint8* buffer = (uint8*) std::malloc(bufferSize);
        bool loaded = self->getResource(resourceName, buffer, bufferSize);
        if (!loaded)
        {
            std::free(buffer);
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, false) ); return; };
        }
        v8::Local<v8::Value> resultVal = EncodeBinary(buffer, bufferSize);
        std::free(buffer);
        { args.GetReturnValue().Set( resultVal ); return; };
    }

    void ResourceManagerWrap::GetResourcePaths(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ResourceManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ResourceManagerWrap>(args.This());
        ResourceManager* self = dynamic_cast<ResourceManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        std::string outStr = self->getResourcePaths();
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, outStr.c_str()).ToLocalChecked() ); return; };
    }

    ResourceManagerWrap::ResourceManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ResourceManager(args);
        if (!cppPtr_ && !s_ResourceManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ResourceManager" " instance")));
            };
        }
    }

    ResourceManagerWrap::~ResourceManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ResourceManager* New_ResourceManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ResourceManager_InNewFromCpp)
        {
            return ResourceManager::getSingletonInstance();
        }
        else
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "ResourceManager" " directly - use get" "ResourceManager" "() instead")));
            };
            return nullptr;
        }
    }

}
