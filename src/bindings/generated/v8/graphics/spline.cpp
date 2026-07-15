// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/spline.cpp
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

    static bool s_Spline_InNewFromCpp = false;

    void SplineWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = new SplineWrap(args);
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
    v8::Local<v8::Object> SplineWrap::NewFromCpp(v8::Isolate* isolate, Spline* cppObj)
    {
        s_Spline_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Spline_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Spline_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mSplineScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Spline_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> SplineWrap::constructorTpl_;

    void SplineWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Spline").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetFirstOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFirstOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetFirstOrder, v8::Local<v8::Value>(), GetFirstOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFirstOrder").ToLocalChecked(), GetFirstOrder_Tpl);
        v8::Local<v8::Signature> GetSecondOrder_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSecondOrder_Tpl =
            v8::FunctionTemplate::New(isolate, GetSecondOrder, v8::Local<v8::Value>(), GetSecondOrder_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSecondOrder").ToLocalChecked(), GetSecondOrder_Tpl);
        v8::Local<v8::Signature> AddSegment_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddSegment_Tpl =
            v8::FunctionTemplate::New(isolate, AddSegment, v8::Local<v8::Value>(), AddSegment_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addSegment").ToLocalChecked(), AddSegment_Tpl);
        v8::Local<v8::Signature> AddPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddPoint_Tpl =
            v8::FunctionTemplate::New(isolate, AddPoint, v8::Local<v8::Value>(), AddPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addPoint").ToLocalChecked(), AddPoint_Tpl);
        v8::Local<v8::Signature> GetPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetPoint, v8::Local<v8::Value>(), GetPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPoint").ToLocalChecked(), GetPoint_Tpl);
        v8::Local<v8::Signature> SetPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPoint_Tpl =
            v8::FunctionTemplate::New(isolate, SetPoint, v8::Local<v8::Value>(), SetPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPoint").ToLocalChecked(), SetPoint_Tpl);
        v8::Local<v8::Signature> GetPointCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointCount, v8::Local<v8::Value>(), GetPointCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPointCount").ToLocalChecked(), GetPointCount_Tpl);
        v8::Local<v8::Signature> GetMaxU_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetMaxU_Tpl =
            v8::FunctionTemplate::New(isolate, GetMaxU, v8::Local<v8::Value>(), GetMaxU_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getMaxU").ToLocalChecked(), GetMaxU_Tpl);
        v8::Local<v8::Signature> GetBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetBounds, v8::Local<v8::Value>(), GetBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBounds").ToLocalChecked(), GetBounds_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    SplineWrap::SplineWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Spline(args);
        if (!cppPtr_ && !s_Spline_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Spline" " instance")));
            };
        }
    }

    SplineWrap::~SplineWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Spline* New_Spline(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Spline_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;

        int splineType = SPLINE_CUBIC_BEZIER;
        if (args.Length() >= 1)
        {
            if (args[0]->IsNumber())
            {
                splineType = (int)args[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            }
            else if (!args[0]->IsNull() && !args[0]->IsUndefined())
            {
                return 0;
            }
        }

        return new Spline(splineType);
    }

    void SplineWrap::GetFirstOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "(number u)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""u"")");
            return;
        }
        double u = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        Point result = self->getFirstOrder(u);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return; };
    }

    void SplineWrap::GetSecondOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "(number u)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""u"")");
            return;
        }
        double u = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        Point result = self->getSecondOrder(u);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return; };
    }

    void SplineWrap::AddSegment(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] p1, [object Point] p2, [object Point] p3, [object Point] p4)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point p1 = v8_ValueToPoint(isolate, args[1 -1]);
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point p2 = v8_ValueToPoint(isolate, args[2 -1]);
        if (!v8_ValueIsPoint(isolate, args[3 -1]))
        {
            v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
            return;
        }
        pdg::Point p3 = v8_ValueToPoint(isolate, args[3 -1]);
        if (!v8_ValueIsPoint(isolate, args[4 -1]))
        {
            v8_ThrowArgTypeException(isolate, 4, "Point", *args[4 -1]);
            return;
        }
        pdg::Point p4 = v8_ValueToPoint(isolate, args[4 -1]);
        self->addSegment(p1, p2, p3, p4);
        args.GetReturnValue().SetUndefined();
    }

    void SplineWrap::AddPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] point)" " - " "").ToLocalChecked() ); return; };
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
        self->addPoint(point);
        args.GetReturnValue().SetUndefined();
    }

    void SplineWrap::GetPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "(number pointIndex)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""pointIndex"")");
            return;
        }
        long pointIndex = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        Point result = self->getPoint(pointIndex);
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, result) ); return; };
    }

    void SplineWrap::SetPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number pointIndex, [object Point] point)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""pointIndex"")");
            return;
        }
        long pointIndex = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point point = v8_ValueToPoint(isolate, args[2 -1]);
        self->setPoint(pointIndex, point);
        args.GetReturnValue().SetUndefined();
    }

    void SplineWrap::GetPointCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int result = self->getPointCount();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, result) ); return; };
    }

    void SplineWrap::GetMaxU(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float result = self->getMaxU();
        { args.GetReturnValue().Set( v8::Number::New(isolate, result) ); return; };
    }

    void SplineWrap::GetBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        SplineWrap* objWrapper = jswrap::ObjectWrap::Unwrap<SplineWrap>(args.This());
        Spline* self = dynamic_cast<Spline*>(objWrapper->cppPtr_);

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

    void CleanupSplineScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

}
