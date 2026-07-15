// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/config_manager.cpp
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

    static bool s_ConfigManager_InNewFromCpp = false;

    void ConfigManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_ConfigManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "ConfigManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "cfg"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        ConfigManagerWrap* objWrapper = new ConfigManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> ConfigManagerWrap::instance_;
    bool ConfigManagerWrap::instanced_ = false;

    v8::Local<v8::Object> ConfigManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_ConfigManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_ConfigManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_ConfigManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_ConfigManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    ConfigManager* ConfigManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(val);
        return dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> ConfigManagerWrap::constructorTpl_;

    void ConfigManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ConfigManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> UseConfig_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UseConfig_Tpl =
            v8::FunctionTemplate::New(isolate, UseConfig, v8::Local<v8::Value>(), UseConfig_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "useConfig").ToLocalChecked(), UseConfig_Tpl);
        v8::Local<v8::Signature> GetConfigString_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConfigString_Tpl =
            v8::FunctionTemplate::New(isolate, GetConfigString, v8::Local<v8::Value>(), GetConfigString_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConfigString").ToLocalChecked(), GetConfigString_Tpl);
        v8::Local<v8::Signature> GetConfigLong_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConfigLong_Tpl =
            v8::FunctionTemplate::New(isolate, GetConfigLong, v8::Local<v8::Value>(), GetConfigLong_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConfigLong").ToLocalChecked(), GetConfigLong_Tpl);
        v8::Local<v8::Signature> GetConfigFloat_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConfigFloat_Tpl =
            v8::FunctionTemplate::New(isolate, GetConfigFloat, v8::Local<v8::Value>(), GetConfigFloat_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConfigFloat").ToLocalChecked(), GetConfigFloat_Tpl);
        v8::Local<v8::Signature> GetConfigBool_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetConfigBool_Tpl =
            v8::FunctionTemplate::New(isolate, GetConfigBool, v8::Local<v8::Value>(), GetConfigBool_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getConfigBool").ToLocalChecked(), GetConfigBool_Tpl);
        v8::Local<v8::Signature> SetConfigString_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetConfigString_Tpl =
            v8::FunctionTemplate::New(isolate, SetConfigString, v8::Local<v8::Value>(), SetConfigString_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setConfigString").ToLocalChecked(), SetConfigString_Tpl);
        v8::Local<v8::Signature> SetConfigLong_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetConfigLong_Tpl =
            v8::FunctionTemplate::New(isolate, SetConfigLong, v8::Local<v8::Value>(), SetConfigLong_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setConfigLong").ToLocalChecked(), SetConfigLong_Tpl);
        v8::Local<v8::Signature> SetConfigFloat_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetConfigFloat_Tpl =
            v8::FunctionTemplate::New(isolate, SetConfigFloat, v8::Local<v8::Value>(), SetConfigFloat_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setConfigFloat").ToLocalChecked(), SetConfigFloat_Tpl);
        v8::Local<v8::Signature> SetConfigBool_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetConfigBool_Tpl =
            v8::FunctionTemplate::New(isolate, SetConfigBool, v8::Local<v8::Value>(), SetConfigBool_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setConfigBool").ToLocalChecked(), SetConfigBool_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void ConfigManagerWrap::UseConfig(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string inConfigName)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigName"")");
            return;
        }
        v8::String::Utf8Value inConfigName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigName = *inConfigName_Str;;
        bool result = self->useConfig(inConfigName);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, result) ); return; };
    }

    void ConfigManagerWrap::GetConfigString(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "(string inConfigItemName)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        std::string outVal;
        bool found = self->getConfigString(inConfigItemName, outVal);
        if (found)
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, outVal.c_str()).ToLocalChecked() ); return; };
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
    }

    void ConfigManagerWrap::GetConfigLong(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(string inConfigItemName)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        long outVal;
        bool found = self->getConfigLong(inConfigItemName, outVal);
        if (found)
        {
            { args.GetReturnValue().Set( v8::Integer::New(isolate, outVal) ); return; };
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
    }

    void ConfigManagerWrap::GetConfigFloat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(string inConfigItemName)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        float outVal;
        bool found = self->getConfigFloat(inConfigItemName, outVal);
        if (found)
        {
            { args.GetReturnValue().Set( v8::Number::New(isolate, outVal) ); return; };
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
    }

    void ConfigManagerWrap::GetConfigBool(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "boolean" " function" "(string inConfigItemName)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        bool outVal;
        bool found = self->getConfigBool(inConfigItemName, outVal);
        if (found)
        {
            { args.GetReturnValue().Set( v8::Boolean::New(isolate, outVal) ); return; };
        }
        else
        {
            args.GetReturnValue().SetUndefined();
        }
    }

    void ConfigManagerWrap::SetConfigString(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string inConfigItemName, string inValue)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        if (!args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""inValue"")");
            return;
        }
        v8::String::Utf8Value inValue_Str(isolate, args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inValue = *inValue_Str;;
        std::string theString(inValue);
        self->setConfigString(inConfigItemName, theString);
        args.GetReturnValue().SetUndefined();
    }

    void ConfigManagerWrap::SetConfigLong(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string inConfigItemName, [number int] inValue)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inValue"")");
            return;
        }
        long inValue = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->setConfigLong(inConfigItemName, inValue);
        args.GetReturnValue().SetUndefined();
    }

    void ConfigManagerWrap::SetConfigFloat(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string inConfigItemName, number inValue)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""inValue"")");
            return;
        }
        double inValue = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setConfigFloat(inConfigItemName, inValue);
        args.GetReturnValue().SetUndefined();
    }

    void ConfigManagerWrap::SetConfigBool(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ConfigManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ConfigManagerWrap>(args.This());
        ConfigManager* self = dynamic_cast<ConfigManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string inConfigItemName, boolean inValue)" " - " "").ToLocalChecked() ); return; };
        }
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inConfigItemName"")");
            return;
        }
        v8::String::Utf8Value inConfigItemName_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inConfigItemName = *inConfigItemName_Str;;
        if (!args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""inValue"")");
            return;
        }
        bool inValue = args[2 -1]->BooleanValue(isolate);
        self->setConfigBool(inConfigItemName, inValue);
        args.GetReturnValue().SetUndefined();
    }

    ConfigManagerWrap::ConfigManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ConfigManager(args);
        if (!cppPtr_ && !s_ConfigManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ConfigManager" " instance")));
            };
        }
    }

    ConfigManagerWrap::~ConfigManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ConfigManager* New_ConfigManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ConfigManager_InNewFromCpp)
        {
            return ConfigManager::getSingletonInstance();
        }
        else
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "ConfigManager" " directly - use get" "ConfigManager" "() instead")));
            };
            return nullptr;
        }
    }

}
