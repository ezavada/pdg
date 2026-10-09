// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/element_ref.cpp
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

    static bool s_ElementRef_InNewFromCpp = false;

    void ElementRefWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = new ElementRefWrap(args);
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
    v8::Local<v8::Object> ElementRefWrap::NewFromCpp(v8::Isolate* isolate, ElementRef* cppObj)
    {
        s_ElementRef_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_ElementRef_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_ElementRef_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            cppObj->mElementRefScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_ElementRef_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ElementRefWrap::constructorTpl_;

    void ElementRefWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ElementRef").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetText_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetText_Tpl =
            v8::FunctionTemplate::New(isolate, GetText, v8::Local<v8::Value>(), GetText_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getText").ToLocalChecked(), GetText_Tpl);
        v8::Local<v8::Signature> SetText_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetText_Tpl =
            v8::FunctionTemplate::New(isolate, SetText, v8::Local<v8::Value>(), SetText_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setText").ToLocalChecked(), SetText_Tpl);
        v8::Local<v8::Signature> Type_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Type_Tpl =
            v8::FunctionTemplate::New(isolate, Type, v8::Local<v8::Value>(), Type_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "type").ToLocalChecked(), Type_Tpl);
        v8::Local<v8::Signature> GetControlPoints_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetControlPoints_Tpl =
            v8::FunctionTemplate::New(isolate, GetControlPoints, v8::Local<v8::Value>(), GetControlPoints_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getControlPoints").ToLocalChecked(), GetControlPoints_Tpl);
        v8::Local<v8::Signature> GetControlPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetControlPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetControlPoint, v8::Local<v8::Value>(), GetControlPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getControlPoint").ToLocalChecked(), GetControlPoint_Tpl);
        v8::Local<v8::Signature> ChangeControlPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ChangeControlPoint_Tpl =
            v8::FunctionTemplate::New(isolate, ChangeControlPoint, v8::Local<v8::Value>(), ChangeControlPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "changeControlPoint").ToLocalChecked(), ChangeControlPoint_Tpl);
        v8::Local<v8::Signature> GetAttributes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAttributes_Tpl =
            v8::FunctionTemplate::New(isolate, GetAttributes, v8::Local<v8::Value>(), GetAttributes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAttributes").ToLocalChecked(), GetAttributes_Tpl);
        v8::Local<v8::Signature> SetAttributes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetAttributes_Tpl =
            v8::FunctionTemplate::New(isolate, SetAttributes, v8::Local<v8::Value>(), SetAttributes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setAttributes").ToLocalChecked(), SetAttributes_Tpl);
        v8::Local<v8::Signature> SetLiveAttributes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLiveAttributes_Tpl =
            v8::FunctionTemplate::New(isolate, SetLiveAttributes, v8::Local<v8::Value>(), SetLiveAttributes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setLiveAttributes").ToLocalChecked(), SetLiveAttributes_Tpl);
        v8::Local<v8::Signature> ClearLiveAttributes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearLiveAttributes_Tpl =
            v8::FunctionTemplate::New(isolate, ClearLiveAttributes, v8::Local<v8::Value>(), ClearLiveAttributes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearLiveAttributes").ToLocalChecked(), ClearLiveAttributes_Tpl);
        v8::Local<v8::Signature> HasLiveAttributes_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HasLiveAttributes_Tpl =
            v8::FunctionTemplate::New(isolate, HasLiveAttributes, v8::Local<v8::Value>(), HasLiveAttributes_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "hasLiveAttributes").ToLocalChecked(), HasLiveAttributes_Tpl);
        v8::Local<v8::Signature> MoveForward_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveForward_Tpl =
            v8::FunctionTemplate::New(isolate, MoveForward, v8::Local<v8::Value>(), MoveForward_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveForward").ToLocalChecked(), MoveForward_Tpl);
        v8::Local<v8::Signature> MoveBackward_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveBackward_Tpl =
            v8::FunctionTemplate::New(isolate, MoveBackward, v8::Local<v8::Value>(), MoveBackward_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveBackward").ToLocalChecked(), MoveBackward_Tpl);
        v8::Local<v8::Signature> MoveToFront_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToFront_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToFront, v8::Local<v8::Value>(), MoveToFront_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToFront").ToLocalChecked(), MoveToFront_Tpl);
        v8::Local<v8::Signature> MoveToBack_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveToBack_Tpl =
            v8::FunctionTemplate::New(isolate, MoveToBack, v8::Local<v8::Value>(), MoveToBack_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveToBack").ToLocalChecked(), MoveToBack_Tpl);
        v8::Local<v8::Signature> Remove_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Remove_Tpl =
            v8::FunctionTemplate::New(isolate, Remove, v8::Local<v8::Value>(), Remove_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "remove").ToLocalChecked(), Remove_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    ElementRefWrap::ElementRefWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        {
            v8::TryCatch caught(args.GetIsolate());
            cppPtr_ = New_ElementRef(args);
            if (caught.HasCaught()) { caught.ReThrow(); return; }
        }
        if (!cppPtr_ && !s_ElementRef_InNewFromCpp)
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ElementRef" " instance")));
            };
        }
    }

    ElementRefWrap::~ElementRefWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ElementRef* New_ElementRef(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ElementRef_InNewFromCpp) return nullptr;
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ;

        return nullptr;
    }

    void CleanupElementRefScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    void ElementRefWrap::GetText(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        try
        {
            {
                args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, self->getText()).ToLocalChecked() ); return;
            };
        }
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
    }

    void ElementRefWrap::SetText(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""text"")");
            return;
        }
        v8::String::Utf8Value text_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* text = *text_Str;;
        try {self->setText(text);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << error.what();
            isolate->ThrowException( v8::Exception::Error( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
        }
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::Type(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        ElementType type = self->type();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, static_cast<uint32_t>(type)) ); return; };
    }

    void ElementRefWrap::GetControlPoints(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        const std::vector<Point>& points = self->getControlPoints();

#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < points.size(); i++)
        {
            Point point = points[i];
            JSObjectSetPropertyAtIndex(ctx, result, (unsigned)i, v8_MakeJavascriptPoint(isolate, point), exception);
        }
#else
        v8::Local<v8::Array> result = v8::Array::New(isolate, points.size());
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        for (size_t i = 0; i < points.size(); i++)
        {
            Point point = points[i];
            result->Set(context, i, v8_MakeJavascriptPoint(isolate, point)).ToChecked();
        }
#endif

        { args.GetReturnValue().Set( result ); return; };
    }

    void ElementRefWrap::GetControlPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""controlPointIndex"")");
            return;
        }
        unsigned long controlPointIndex = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        try
        {
            const Point& point = self->getControlPoint(controlPointIndex);
            Point pointCopy = point;
            { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, pointCopy) ); return; };
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "ElementRef::getControlPoint: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
    }

    void ElementRefWrap::ChangeControlPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""controlPointIndex"")");
            return;
        }
        unsigned long controlPointIndex = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        pdg::Point controlPoint;
        auto controlPoint_isPoint = v8_ValueIsPoint(isolate, args[2 -1], controlPoint);
        if (!controlPoint_isPoint.has_value())
        {
            {
                args.GetReturnValue().SetNull(); return;
            };
        }
        if (!*controlPoint_isPoint)
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        };
        try
        {
            self->changeControlPoint(controlPointIndex, controlPoint);
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "ElementRef::changeControlPoint: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::GetAttributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Attributes* attrsPtr = new Attributes();
        self->getAttributes(*attrsPtr);
        if (!attrsPtr) { args.GetReturnValue().SetNull(); return; };
        if (attrsPtr->mAttributesScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( AttributesWrap::NewFromCpp(isolate, attrsPtr) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, attrsPtr->mAttributesScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void ElementRefWrap::SetAttributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };

        Attributes* attrs = ExtractAttributes(args[1 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected Attributes or AnimatedAttributes";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        };
        self->setAttributes(*attrs);
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::SetLiveAttributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };

        Attributes* attrs = ExtractAttributes(args[1 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "Expected Attributes or AnimatedAttributes";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }
            ())));
            {
                args.GetReturnValue().SetNull(); return;
            };
        };
        self->setLiveAttributes(*attrs);
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::ClearLiveAttributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clearLiveAttributes();
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::HasLiveAttributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, self->hasLiveAttributes()) ); return; };
    }

    void ElementRefWrap::MoveForward(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveForward();
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::MoveBackward(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveBackward();
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::MoveToFront(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToFront();
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::MoveToBack(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->moveToBack();
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::Remove(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->remove();
        args.GetReturnValue().SetUndefined();
    }

}
