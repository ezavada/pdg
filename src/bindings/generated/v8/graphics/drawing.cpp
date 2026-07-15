// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/drawing.cpp
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
        v8::Isolate* isolate = args.GetIsolate();
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
            v8::Local<v8::Object> obj = instance;
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
        cppPtr_ = New_ElementRef(args);
        if (!cppPtr_ && !s_ElementRef_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
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
        v8::Isolate* isolate = args.GetIsolate();
        ;

        std::ostringstream excpt_;
        excpt_ << "ElementRef cannot be constructed directly. Use Drawing methods to get ElementRef objects.";
        isolate->ThrowException( v8::Exception::TypeError( ([&]()
        {
            v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                return maybe.IsEmpty() ?
                v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
        }())));
        return nullptr;
    }

    void CleanupElementRefScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    void ElementRefWrap::Type(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[array]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        const std::vector<Point>& points = self->getControlPoints();

        v8::Local<v8::Array> result = v8::Array::New(isolate, points.size());
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        for (size_t i = 0; i < points.size(); i++)
        {
            Point point = points[i];
            result->Set(context, i, v8_MakeJavascriptPoint(isolate, point)).ToChecked();
        }

        { args.GetReturnValue().Set( result ); return; };
    }

    void ElementRefWrap::GetControlPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([number uint] controlPointIndex)" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] controlPointIndex, [object Point] controlPoint)" " - " "").ToLocalChecked() ); return; };
        };
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
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point controlPoint = v8_ValueToPoint(isolate, args[2 -1]);
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Attributes]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addLine must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        self->setAttributes(*attrsPtr);
        args.GetReturnValue().SetUndefined();
    }

    void ElementRefWrap::MoveForward(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
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
        v8::Isolate* isolate = args.GetIsolate();
        ElementRefWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ElementRefWrap>(args.This());
        ElementRef* self = dynamic_cast<ElementRef*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->remove();
        args.GetReturnValue().SetUndefined();
    }

    static bool s_Drawing_InNewFromCpp = false;

    void DrawingWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = new DrawingWrap(args);
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
    v8::Local<v8::Object> DrawingWrap::NewFromCpp(v8::Isolate* isolate, Drawing* cppObj)
    {
        s_Drawing_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Drawing_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Drawing_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mDrawingScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Drawing_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> DrawingWrap::constructorTpl_;

    void DrawingWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Drawing").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> AddLine_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddLine_Tpl =
            v8::FunctionTemplate::New(isolate, AddLine, v8::Local<v8::Value>(), AddLine_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addLine").ToLocalChecked(), AddLine_Tpl);
        v8::Local<v8::Signature> AddSpline_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddSpline_Tpl =
            v8::FunctionTemplate::New(isolate, AddSpline, v8::Local<v8::Value>(), AddSpline_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addSpline").ToLocalChecked(), AddSpline_Tpl);
        v8::Local<v8::Signature> AddRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddRect_Tpl =
            v8::FunctionTemplate::New(isolate, AddRect, v8::Local<v8::Value>(), AddRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addRect").ToLocalChecked(), AddRect_Tpl);
        v8::Local<v8::Signature> AddArc_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddArc_Tpl =
            v8::FunctionTemplate::New(isolate, AddArc, v8::Local<v8::Value>(), AddArc_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addArc").ToLocalChecked(), AddArc_Tpl);
        v8::Local<v8::Signature> AddQuad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddQuad_Tpl =
            v8::FunctionTemplate::New(isolate, AddQuad, v8::Local<v8::Value>(), AddQuad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addQuad").ToLocalChecked(), AddQuad_Tpl);
        v8::Local<v8::Signature> AddPolygon_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddPolygon_Tpl =
            v8::FunctionTemplate::New(isolate, AddPolygon, v8::Local<v8::Value>(), AddPolygon_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addPolygon").ToLocalChecked(), AddPolygon_Tpl);
        v8::Local<v8::Signature> AddEllipse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddEllipse_Tpl =
            v8::FunctionTemplate::New(isolate, AddEllipse, v8::Local<v8::Value>(), AddEllipse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addEllipse").ToLocalChecked(), AddEllipse_Tpl);
        v8::Local<v8::Signature> AddImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddImage_Tpl =
            v8::FunctionTemplate::New(isolate, AddImage, v8::Local<v8::Value>(), AddImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addImage").ToLocalChecked(), AddImage_Tpl);
        v8::Local<v8::Signature> AddImageStrip_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddImageStrip_Tpl =
            v8::FunctionTemplate::New(isolate, AddImageStrip, v8::Local<v8::Value>(), AddImageStrip_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addImageStrip").ToLocalChecked(), AddImageStrip_Tpl);
        v8::Local<v8::Signature> AddDrawing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddDrawing_Tpl =
            v8::FunctionTemplate::New(isolate, AddDrawing, v8::Local<v8::Value>(), AddDrawing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addDrawing").ToLocalChecked(), AddDrawing_Tpl);
        v8::Local<v8::Signature> GetElementCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetElementCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetElementCount, v8::Local<v8::Value>(), GetElementCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getElementCount").ToLocalChecked(), GetElementCount_Tpl);
        v8::Local<v8::Signature> GetElement_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetElement_Tpl =
            v8::FunctionTemplate::New(isolate, GetElement, v8::Local<v8::Value>(), GetElement_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getElement").ToLocalChecked(), GetElement_Tpl);
        v8::Local<v8::Signature> GetElementHitBy_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetElementHitBy_Tpl =
            v8::FunctionTemplate::New(isolate, GetElementHitBy, v8::Local<v8::Value>(), GetElementHitBy_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getElementHitBy").ToLocalChecked(), GetElementHitBy_Tpl);
        v8::Local<v8::Signature> GetBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetBounds, v8::Local<v8::Value>(), GetBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBounds").ToLocalChecked(), GetBounds_Tpl);
        v8::Local<v8::Signature> CenterPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CenterPoint_Tpl =
            v8::FunctionTemplate::New(isolate, CenterPoint, v8::Local<v8::Value>(), CenterPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "centerPoint").ToLocalChecked(), CenterPoint_Tpl);
        v8::Local<v8::Signature> Empty_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Empty_Tpl =
            v8::FunctionTemplate::New(isolate, Empty, v8::Local<v8::Value>(), Empty_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "empty").ToLocalChecked(), Empty_Tpl);
#ifndef PDG_NO_GUI
        v8::Local<v8::Signature> Draw_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Draw_Tpl =
            v8::FunctionTemplate::New(isolate, Draw, v8::Local<v8::Value>(), Draw_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "draw").ToLocalChecked(), Draw_Tpl);
#endif
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    DrawingWrap::DrawingWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Drawing(args);
        if (!cppPtr_ && !s_Drawing_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Drawing" " instance")));
            };
        }
    }

    DrawingWrap::~DrawingWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Drawing* New_Drawing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Drawing_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;

        std::ostringstream excpt_;
        excpt_ << "Drawing cannot be constructed directly. Use Drawing.create() to create a new Drawing.";
        isolate->ThrowException( v8::Exception::TypeError( ([&]()
        {
            v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                return maybe.IsEmpty() ?
                v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
        }())));
        return nullptr;
    }

    void CleanupDrawingScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    void CreateDrawing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Drawing]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Drawing* drawing = Drawing::create();
        if (!drawing) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( DrawingWrap::NewFromCpp(isolate, drawing) ); return; };
        ;
    }

    void DrawingWrap::AddLine(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Point] from, [object Point] to, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point from = v8_ValueToPoint(isolate, args[1 -1]);
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point to = v8_ValueToPoint(isolate, args[2 -1]);
        REQUIRE_OBJECT_ARG(3, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addLine must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addLine(from, to, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddSpline(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Spline] spline, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_OBJECT_ARG(1, spline);
        SplineWrap* splineWrapper = static_cast<SplineWrap*>(spline->GetAlignedPointerFromInternalField(0));
        Spline* splinePtr = splineWrapper->getCppObject();
        if (!splinePtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addSpline must be called with a valid Spline object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        REQUIRE_OBJECT_ARG(2, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addSpline must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addSpline(std::move(*splinePtr), *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Rect] rect, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        REQUIRE_OBJECT_ARG(2, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addRect must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addRect(rect, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Quad] quad, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!v8_ValueIsQuad(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
            return;
        }
        pdg::Quad quad = v8_ValueToQuad(isolate, args[1 -1]);
        REQUIRE_OBJECT_ARG(2, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addQuad must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addQuad(quad, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddPolygon(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Polygon] polygon, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_OBJECT_ARG(1, polygon);
        PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(polygon->GetAlignedPointerFromInternalField(0));
        Polygon* polygonPtr = polygonWrapper->getCppObject();
        if (!polygonPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addPolygon must be called with a valid Polygon object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        REQUIRE_OBJECT_ARG(2, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addPolygon must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addPolygon(std::move(*polygonPtr), *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddEllipse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Point] center, number xRadius, number yRadius, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 4)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 4);
            return;
        };
        if (!v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point center = v8_ValueToPoint(isolate, args[1 -1]);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""xRadius"")");
            return;
        }
        double xRadius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""yRadius"")");
            return;
        }
        double yRadius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_OBJECT_ARG(4, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addEllipse must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addEllipse(center, xRadius, yRadius, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddArc(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Point] center, number xRadius, number yRadius, number startAngle, number endAngle, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 6)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 6);
            return;
        };
        if (!v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point center = v8_ValueToPoint(isolate, args[1 -1]);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""xRadius"")");
            return;
        }
        double xRadius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""yRadius"")");
            return;
        }
        double yRadius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""startAngle"")");
            return;
        }
        double startAngle = args[4 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[5 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 5, "a number (""endAngle"")");
            return;
        }
        double endAngle = args[5 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_OBJECT_ARG(6, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addArc must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addArc(center, xRadius, yRadius, startAngle, endAngle, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Rect] rect, [object Image] image, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        REQUIRE_OBJECT_ARG(2, image);
        ImageWrap* imageWrapper = static_cast<ImageWrap*>(image->GetAlignedPointerFromInternalField(0));
        Image* imagePtr = imageWrapper->getCppObject();
        if (!imagePtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addImage must be called with a valid Image object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        REQUIRE_OBJECT_ARG(3, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addImage must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addImage(rect, *imagePtr, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddImageStrip(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Rect] rect, [object ImageStrip] imageStrip, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        REQUIRE_OBJECT_ARG(2, imageStrip);
        ImageStripWrap* imageStripWrapper = static_cast<ImageStripWrap*>(imageStrip->GetAlignedPointerFromInternalField(0));
        ImageStrip* imageStripPtr = imageStripWrapper->getCppObject();
        if (!imageStripPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addImageStrip must be called with a valid ImageStrip object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        REQUIRE_OBJECT_ARG(3, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addImageStrip must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addImageStrip(rect, *imageStripPtr, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::AddDrawing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Rect] rect, [object Drawing] drawing, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        REQUIRE_OBJECT_ARG(2, drawing);
        DrawingWrap* drawingWrapper = static_cast<DrawingWrap*>(drawing->GetAlignedPointerFromInternalField(0));
        Drawing* drawingPtr = drawingWrapper->getCppObject();
        if (!drawingPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addDrawing must be called with a valid Drawing object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        REQUIRE_OBJECT_ARG(3, attrs);
        AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(attrs->GetAlignedPointerFromInternalField(0));
        Attributes* attrsPtr = attrsWrapper->getCppObject();
        if (!attrsPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "addDrawing must be called with a valid Attributes object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        ElementRef* result = self->addDrawing(rect, *drawingPtr, *attrsPtr);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::GetElementCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        size_t count = self->getElementCount();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, count) ); return; };
    }

    void DrawingWrap::GetElement(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([number uint] index)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
            return;
        }
        unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        try
        {
            ElementRef* result = self->getElement(index);
            if (!result) { args.GetReturnValue().SetNull(); return; };
            if (result->mElementRefScriptObj.IsEmpty())
            {
                { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
            }
            else
            {
                v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
                { args.GetReturnValue().Set( obj__ ); return; };
            };
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "Drawing::getElement: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
    }

    void DrawingWrap::GetElementHitBy(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ElementRef]" " function" "([object Point] point)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point point = v8_ValueToPoint(isolate, args[1 -1]);
        ElementRef* result = self->getElementHitBy(point);
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mElementRefScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ElementRefWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mElementRefScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void DrawingWrap::GetBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect bounds = self->getBounds();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, bounds) ); return; };
    }

    void DrawingWrap::CenterPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point center = self->centerPoint();
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, center) ); return; };
    }

    void DrawingWrap::Empty(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[boolean]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool empty = self->empty();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, empty) ); return; };
    }

#ifndef PDG_NO_GUI

    void DrawingWrap::Draw(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        DrawingWrap* objWrapper = jswrap::ObjectWrap::Unwrap<DrawingWrap>(args.This());
        Drawing* self = dynamic_cast<Drawing*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Port] port)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, port);
        PortWrap* portWrapper = static_cast<PortWrap*>(port->GetAlignedPointerFromInternalField(0));
        Port* portPtr = portWrapper->getCppObject();
        if (!portPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "draw must be called with a valid Port object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }

        self->draw(portPtr);
        args.GetReturnValue().SetUndefined();
    }
#endif

}
