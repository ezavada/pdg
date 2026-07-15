// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/font.cpp
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

#ifndef PDG_NO_GUI

    static bool s_Font_InNewFromCpp = false;

    void FontWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = new FontWrap(args);
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
    v8::Local<v8::Object> FontWrap::NewFromCpp(v8::Isolate* isolate, Font* cppObj)
    {
        s_Font_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Font_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Font_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mFontScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Font_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> FontWrap::constructorTpl_;

    void FontWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Font").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetFontName_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFontName_Tpl =
            v8::FunctionTemplate::New(isolate, GetFontName, v8::Local<v8::Value>(), GetFontName_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FontName").ToLocalChecked(), GetFontName_Tpl);
        v8::Local<v8::Signature> GetFontHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFontHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetFontHeight, v8::Local<v8::Value>(), GetFontHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FontHeight").ToLocalChecked(), GetFontHeight_Tpl);
        v8::Local<v8::Signature> GetFontLeading_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFontLeading_Tpl =
            v8::FunctionTemplate::New(isolate, GetFontLeading, v8::Local<v8::Value>(), GetFontLeading_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FontLeading").ToLocalChecked(), GetFontLeading_Tpl);
        v8::Local<v8::Signature> GetFontAscent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFontAscent_Tpl =
            v8::FunctionTemplate::New(isolate, GetFontAscent, v8::Local<v8::Value>(), GetFontAscent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FontAscent").ToLocalChecked(), GetFontAscent_Tpl);
        v8::Local<v8::Signature> GetFontDescent_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFontDescent_Tpl =
            v8::FunctionTemplate::New(isolate, GetFontDescent, v8::Local<v8::Value>(), GetFontDescent_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FontDescent").ToLocalChecked(), GetFontDescent_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void FontWrap::GetFontName(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(args.This());
        Font* self = dynamic_cast<Font*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "string" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        const char* theFontName = self->getFontName();
        { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, theFontName).ToLocalChecked() ); return; };
    }

    void FontWrap::GetFontHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(args.This());
        Font* self = dynamic_cast<Font*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(number size, [number int] style = textStyle_Plain)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
            return;
        }
        long size = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<2) ? textStyle_Plain : args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;

        float theFontHeight = self->getFontHeight(size, style);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theFontHeight) ); return; };
    }

    void FontWrap::GetFontLeading(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(args.This());
        Font* self = dynamic_cast<Font*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(number size, [number int] style = textStyle_Plain)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
            return;
        }
        long size = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<2) ? textStyle_Plain : args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;

        float theFontLeading = self->getFontLeading(size, style);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theFontLeading) ); return; };
    }

    void FontWrap::GetFontAscent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(args.This());
        Font* self = dynamic_cast<Font*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(number size, [number int] style = textStyle_Plain)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
            return;
        }
        long size = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<2) ? textStyle_Plain : args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;

        float theFontAscent = self->getFontAscent(size, style);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theFontAscent) ); return; };
    }

    void FontWrap::GetFontDescent(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        FontWrap* objWrapper = jswrap::ObjectWrap::Unwrap<FontWrap>(args.This());
        Font* self = dynamic_cast<Font*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(number size, [number int] style = textStyle_Plain)").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
            return;
        }
        long size = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 2 && !args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<2) ? textStyle_Plain : args[2 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;

        float theFontDescent = self->getFontDescent(size, style);
        { args.GetReturnValue().Set( v8::Number::New(isolate, theFontDescent) ); return; };
    }

    void CleanupFontScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    FontWrap::FontWrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        cppPtr_ = nullptr;
    }

    FontWrap::~FontWrap()
    {
        cppPtr_ = nullptr;
    }

    Font* New_Font(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Font_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        s_HaveSavedError = true;
        {
            std::ostringstream excpt_;
            excpt_ << "Font cannot be created directly, use pdg.gfx.createFont()";
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
        };
        return 0;
    }
#endif

}
