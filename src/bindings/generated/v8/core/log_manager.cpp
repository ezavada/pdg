// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/core/log_manager.cpp
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

    static bool s_LogManager_InNewFromCpp = false;

    void LogManagerWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall() && !s_LogManager_InNewFromCpp)
        {
            v8::Local<v8::String> error_msg = v8::String::NewFromUtf8(isolate,
                "LogManager" " cannot be instantiated with 'new'. Use the singleton instance: require('pdg')." "lm"
                ).ToLocalChecked();
            isolate->ThrowException(v8::Exception::TypeError(error_msg));
            return;
        }

        LogManagerWrap* objWrapper = new LogManagerWrap(args);
        objWrapper->Wrap(args.This());

        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    v8::Persistent<v8::Object> LogManagerWrap::instance_;
    bool LogManagerWrap::instanced_ = false;

    v8::Local<v8::Object> LogManagerWrap::GetScriptSingletonInstance(v8::Isolate* isolate)
    {
        v8::EscapableHandleScope scope(isolate);
        if (!instanced_)
        {

            s_LogManager_InNewFromCpp = true;
            v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
            v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
            if (maybeFunc.IsEmpty())
            {
                s_LogManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
            v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
            if (maybeInstance.IsEmpty())
            {
                s_LogManager_InNewFromCpp = false;
                return v8::Local<v8::Object>();
            }
            v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
            s_LogManager_InNewFromCpp = false;
            instance_.Reset(isolate, instance);
            instanced_ = true;
        }
        v8::Local<v8::Object> inst_ = v8::Local<v8::Object>::New(isolate, instance_);
        return scope.Escape(inst_);
    }

    LogManager* LogManagerWrap::getSingletonInstance()
    {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Object> val = GetScriptSingletonInstance(isolate)->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
        LogManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<LogManagerWrap>(val);
        return dynamic_cast<LogManager*>(objWrapper->cppPtr_);
    }

    v8::Persistent<v8::FunctionTemplate> LogManagerWrap::constructorTpl_;

    void LogManagerWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "LogManager").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        t->InstanceTemplate()->Set(v8::String::NewFromUtf8(isolate, "init_CreateUniqueNewFile").ToLocalChecked(), v8::Integer::New(isolate, pdg::LogManager::init_CreateUniqueNewFile), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
        t->InstanceTemplate()->Set(v8::String::NewFromUtf8(isolate, "init_OverwriteExisting").ToLocalChecked(), v8::Integer::New(isolate, pdg::LogManager::init_OverwriteExisting), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
        t->InstanceTemplate()->Set(v8::String::NewFromUtf8(isolate, "init_AppendToExisting").ToLocalChecked(), v8::Integer::New(isolate, pdg::LogManager::init_AppendToExisting), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
        t->InstanceTemplate()->Set(v8::String::NewFromUtf8(isolate, "init_StdOut").ToLocalChecked(), v8::Integer::New(isolate, pdg::LogManager::init_StdOut), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
        t->InstanceTemplate()->Set(v8::String::NewFromUtf8(isolate, "init_StdErr").ToLocalChecked(), v8::Integer::New(isolate, pdg::LogManager::init_StdErr), static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete));
        v8::Local<v8::Signature> GetLogLevel_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLogLevel_Tpl =
            v8::FunctionTemplate::New(isolate, GetLogLevel, v8::Local<v8::Value>(), GetLogLevel_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""LogLevel").ToLocalChecked(), GetLogLevel_Tpl);
        v8::Local<v8::Signature> SetLogLevel_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLogLevel_Tpl =
            v8::FunctionTemplate::New(isolate, SetLogLevel, v8::Local<v8::Value>(), SetLogLevel_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""LogLevel").ToLocalChecked(), SetLogLevel_Tpl);
        v8::Local<v8::Signature> Initialize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Initialize_Tpl =
            v8::FunctionTemplate::New(isolate, Initialize, v8::Local<v8::Value>(), Initialize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "initialize").ToLocalChecked(), Initialize_Tpl);
        v8::Local<v8::Signature> WriteLogEntry_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> WriteLogEntry_Tpl =
            v8::FunctionTemplate::New(isolate, WriteLogEntry, v8::Local<v8::Value>(), WriteLogEntry_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "writeLogEntry").ToLocalChecked(), WriteLogEntry_Tpl);
        v8::Local<v8::Signature> BinaryDump_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> BinaryDump_Tpl =
            v8::FunctionTemplate::New(isolate, BinaryDump, v8::Local<v8::Value>(), BinaryDump_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "binaryDump").ToLocalChecked(), BinaryDump_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void LogManagerWrap::GetLogLevel(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        LogManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<LogManagerWrap>(args.This());
        LogManager* self = dynamic_cast<LogManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int32 theLogLevel = self->getLogLevel();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theLogLevel) ); return; };
    }

    void LogManagerWrap::SetLogLevel(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        LogManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<LogManagerWrap>(args.This());
        LogManager* self = dynamic_cast<LogManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object LogManager]" " function" "([number int] inLogLevel)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theLogLevel"")");
            return;
        }
        long theLogLevel = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        self->setLogLevel(theLogLevel);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void LogManagerWrap::Initialize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        LogManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<LogManagerWrap>(args.This());
        LogManager* self = dynamic_cast<LogManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(string inLogNameBase, [number int] initMode = LogManager.init_StdOut)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""inLogNameBase"")");
            return;
        }
        v8::String::Utf8Value inLogNameBase_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* inLogNameBase = *inLogNameBase_Str;;
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""initMode"")");
            return;
        }
        long initMode = (args.Length()<2) ? pdg::LogManager::init_StdOut : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        self->initialize(inLogNameBase, initMode);
        args.GetReturnValue().SetUndefined();
    }

    void LogManagerWrap::WriteLogEntry(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        LogManagerWrap* objWrapper = jswrap::ObjectWrap::Unwrap<LogManagerWrap>(args.This());
        LogManager* self = dynamic_cast<LogManager*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] level, string category, string message)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""level"")");
            return;
        }
        long level = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 2, "a string  (""category"")");
            return;
        }
        v8::String::Utf8Value category_Str(isolate, args[2 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* category = *category_Str;;
        if (!args[3 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 3, "a string  (""message"")");
            return;
        }
        v8::String::Utf8Value message_Str(isolate, args[3 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* message = *message_Str;;
        self->writeLogEntry(level, category, message);
        args.GetReturnValue().SetUndefined();
    }
    void LogManagerWrap::BinaryDump(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "({[string Binary]|[object MemBlock]} inData, [number int] length = 0, [number int] bytesPerLine = 20)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""length"")");
            return;
        }
        long length = (args.Length()<2) ? 0 : args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""bytesPerLine"")");
            return;
        }
        long bytesPerLine = (args.Length()<3) ? 20 : args[3 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        int dataSize = 0;
        char* inData = 0;
        if (args[0]->IsString())
        {
            size_t bytes = 0;
            uint8* ptr = (uint8*) DecodeBinary(args[0], &bytes);
            inData = (char*)ptr;
            dataSize = (length == 0) ? bytes : length;
        }
        else
        {
            REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
            inData = memBlock->ptr;
            dataSize = (length == 0) ? memBlock->bytes : length;
        }
        int outBufSize = (4 * dataSize) + (6 * dataSize/bytesPerLine) + (4 * bytesPerLine) + 32;
        char* outBuf = new char[outBufSize];
        OS::binaryDump(outBuf, outBufSize, inData, dataSize, bytesPerLine);
        v8::Local<v8::Value> dumpStrVal = v8::String::NewFromUtf8(isolate, outBuf).ToLocalChecked();
        delete[] outBuf;
        { args.GetReturnValue().Set( dumpStrVal ); return; };
    }

    log& main_getDebugLog();

    LogManagerWrap::LogManagerWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_LogManager(args);
        if (!cppPtr_ && !s_LogManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "LogManager" " instance")));
            };
        }
    }

    LogManagerWrap::~LogManagerWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    LogManager* New_LogManager(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (!s_LogManager_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Cannot construct " "LogManager" " directly - use get" "LogManager" "() instead")));
            };
            return nullptr;
        }

        v8::Isolate* isolate = args.GetIsolate();
        LogManager *theLogMgr = LogManager::getSingletonInstance();
        pdg::log& debugLog = main_getDebugLog();
        debugLog.setLogManager(theLogMgr);
        return theLogMgr;
    }

}
