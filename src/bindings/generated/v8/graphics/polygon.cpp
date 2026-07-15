// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/polygon.cpp
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

    static bool s_Polygon_InNewFromCpp = false;

    void PolygonWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = new PolygonWrap(args);
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
    v8::Local<v8::Object> PolygonWrap::NewFromCpp(v8::Isolate* isolate, Polygon* cppObj)
    {
        s_Polygon_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Polygon_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Polygon_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mPolygonScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Polygon_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> PolygonWrap::constructorTpl_;

    void PolygonWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Polygon").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> AddPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddPoint_Tpl =
            v8::FunctionTemplate::New(isolate, AddPoint, v8::Local<v8::Value>(), AddPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addPoint").ToLocalChecked(), AddPoint_Tpl);
        v8::Local<v8::Signature> AddSpline_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AddSpline_Tpl =
            v8::FunctionTemplate::New(isolate, AddSpline, v8::Local<v8::Value>(), AddSpline_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "addSpline").ToLocalChecked(), AddSpline_Tpl);
        v8::Local<v8::Signature> InsertPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> InsertPoint_Tpl =
            v8::FunctionTemplate::New(isolate, InsertPoint, v8::Local<v8::Value>(), InsertPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "insertPoint").ToLocalChecked(), InsertPoint_Tpl);
        v8::Local<v8::Signature> RemovePoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RemovePoint_Tpl =
            v8::FunctionTemplate::New(isolate, RemovePoint, v8::Local<v8::Value>(), RemovePoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "removePoint").ToLocalChecked(), RemovePoint_Tpl);
        v8::Local<v8::Signature> GetPointCount_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPointCount_Tpl =
            v8::FunctionTemplate::New(isolate, GetPointCount, v8::Local<v8::Value>(), GetPointCount_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPointCount").ToLocalChecked(), GetPointCount_Tpl);
        v8::Local<v8::Signature> GetPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPoint_Tpl =
            v8::FunctionTemplate::New(isolate, GetPoint, v8::Local<v8::Value>(), GetPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPoint").ToLocalChecked(), GetPoint_Tpl);
        v8::Local<v8::Signature> SetPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetPoint_Tpl =
            v8::FunctionTemplate::New(isolate, SetPoint, v8::Local<v8::Value>(), SetPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setPoint").ToLocalChecked(), SetPoint_Tpl);
        v8::Local<v8::Signature> ClearPoints_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClearPoints_Tpl =
            v8::FunctionTemplate::New(isolate, ClearPoints, v8::Local<v8::Value>(), ClearPoints_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clearPoints").ToLocalChecked(), ClearPoints_Tpl);
        v8::Local<v8::Signature> GetBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetBounds, v8::Local<v8::Value>(), GetBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBounds").ToLocalChecked(), GetBounds_Tpl);
        v8::Local<v8::Signature> CenterPoint_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> CenterPoint_Tpl =
            v8::FunctionTemplate::New(isolate, CenterPoint, v8::Local<v8::Value>(), CenterPoint_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "centerPoint").ToLocalChecked(), CenterPoint_Tpl);
        v8::Local<v8::Signature> Contains_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Contains_Tpl =
            v8::FunctionTemplate::New(isolate, Contains, v8::Local<v8::Value>(), Contains_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "contains").ToLocalChecked(), Contains_Tpl);
        v8::Local<v8::Signature> Empty_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Empty_Tpl =
            v8::FunctionTemplate::New(isolate, Empty, v8::Local<v8::Value>(), Empty_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "empty").ToLocalChecked(), Empty_Tpl);
        v8::Local<v8::Signature> Equals_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Equals_Tpl =
            v8::FunctionTemplate::New(isolate, Equals, v8::Local<v8::Value>(), Equals_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "equals").ToLocalChecked(), Equals_Tpl);
        v8::Local<v8::Signature> Move_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Move_Tpl =
            v8::FunctionTemplate::New(isolate, Move, v8::Local<v8::Value>(), Move_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "move").ToLocalChecked(), Move_Tpl);
        v8::Local<v8::Signature> MoveLeft_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveLeft_Tpl =
            v8::FunctionTemplate::New(isolate, MoveLeft, v8::Local<v8::Value>(), MoveLeft_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveLeft").ToLocalChecked(), MoveLeft_Tpl);
        v8::Local<v8::Signature> MoveRight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveRight_Tpl =
            v8::FunctionTemplate::New(isolate, MoveRight, v8::Local<v8::Value>(), MoveRight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveRight").ToLocalChecked(), MoveRight_Tpl);
        v8::Local<v8::Signature> MoveUp_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveUp_Tpl =
            v8::FunctionTemplate::New(isolate, MoveUp, v8::Local<v8::Value>(), MoveUp_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveUp").ToLocalChecked(), MoveUp_Tpl);
        v8::Local<v8::Signature> MoveDown_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveDown_Tpl =
            v8::FunctionTemplate::New(isolate, MoveDown, v8::Local<v8::Value>(), MoveDown_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveDown").ToLocalChecked(), MoveDown_Tpl);
        v8::Local<v8::Signature> MoveXTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveXTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveXTo, v8::Local<v8::Value>(), MoveXTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveXTo").ToLocalChecked(), MoveXTo_Tpl);
        v8::Local<v8::Signature> MoveYTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveYTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveYTo, v8::Local<v8::Value>(), MoveYTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveYTo").ToLocalChecked(), MoveYTo_Tpl);
        v8::Local<v8::Signature> MoveTo_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> MoveTo_Tpl =
            v8::FunctionTemplate::New(isolate, MoveTo, v8::Local<v8::Value>(), MoveTo_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "moveTo").ToLocalChecked(), MoveTo_Tpl);
        v8::Local<v8::Signature> Center_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Center_Tpl =
            v8::FunctionTemplate::New(isolate, Center, v8::Local<v8::Value>(), Center_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "center").ToLocalChecked(), Center_Tpl);
        v8::Local<v8::Signature> Scale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Scale_Tpl =
            v8::FunctionTemplate::New(isolate, Scale, v8::Local<v8::Value>(), Scale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "scale").ToLocalChecked(), Scale_Tpl);
        v8::Local<v8::Signature> HorzScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> HorzScale_Tpl =
            v8::FunctionTemplate::New(isolate, HorzScale, v8::Local<v8::Value>(), HorzScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "horzScale").ToLocalChecked(), HorzScale_Tpl);
        v8::Local<v8::Signature> VertScale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> VertScale_Tpl =
            v8::FunctionTemplate::New(isolate, VertScale, v8::Local<v8::Value>(), VertScale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "vertScale").ToLocalChecked(), VertScale_Tpl);
        v8::Local<v8::Signature> ScaleAround_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ScaleAround_Tpl =
            v8::FunctionTemplate::New(isolate, ScaleAround, v8::Local<v8::Value>(), ScaleAround_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "scaleAround").ToLocalChecked(), ScaleAround_Tpl);
        v8::Local<v8::Signature> Rotate_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Rotate_Tpl =
            v8::FunctionTemplate::New(isolate, Rotate, v8::Local<v8::Value>(), Rotate_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotate").ToLocalChecked(), Rotate_Tpl);
        v8::Local<v8::Signature> RotateAround_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RotateAround_Tpl =
            v8::FunctionTemplate::New(isolate, RotateAround, v8::Local<v8::Value>(), RotateAround_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotateAround").ToLocalChecked(), RotateAround_Tpl);
        v8::Local<v8::Signature> Intersection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Intersection_Tpl =
            v8::FunctionTemplate::New(isolate, Intersection, v8::Local<v8::Value>(), Intersection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "intersection").ToLocalChecked(), Intersection_Tpl);
        v8::Local<v8::Signature> UnionWith_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> UnionWith_Tpl =
            v8::FunctionTemplate::New(isolate, UnionWith, v8::Local<v8::Value>(), UnionWith_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "unionWith").ToLocalChecked(), UnionWith_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    PolygonWrap::PolygonWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Polygon(args);
        if (!cppPtr_ && !s_Polygon_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Polygon" " instance")));
            };
        }
    }

    PolygonWrap::~PolygonWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Polygon* New_Polygon(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Polygon_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;

        if (args.Length() == 0)
        {

            return new pdg::Polygon();
        }
        else if (args.Length() == 1 && (args[0]->IsNull() || args[0]->IsUndefined()))
        {

            return new pdg::Polygon();
        }
        else if (args.Length() == 1 && args[0]->IsArray())
        {

            std::vector<Point> points;
            v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < array->Length(); i++)
            {
                points.push_back(v8_ValueToPoint(isolate, array->Get(context, i).ToLocalChecked()));
            }
            return new pdg::Polygon(points);
        }
        else
        {

            std::vector<Point> points;
            for (int i = 0; i < args.Length(); i++)
            {
                if (!args[i]->IsObject())
                {
                    std::ostringstream excpt_;
                    excpt_ << "Polygon constructor arguments must be Point objects";
                    isolate->ThrowException( v8::Exception::TypeError( ([&]()
                    {
                        v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                            return maybe.IsEmpty() ?
                            v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
                    }())));
                    return nullptr;
                }
                Point point = v8_ValueToPoint(isolate, args[i]);
                points.push_back(point);
            }
            return new pdg::Polygon(points);
        }
    }

    void PolygonWrap::AddPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

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

    void PolygonWrap::AddSpline(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Spline] spline, [number] uStep)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
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
        float uStep = 0.01f;
        if (args.Length() >= 2 && !args[1]->IsUndefined() && !args[1]->IsNull())
        {
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""uStepArg"")");
                return;
            }
            double uStepArg = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            uStep = uStepArg;
        }
        self->addSpline(splinePtr, uStep);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::InsertPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] index, [object Point] point)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
            return;
        }
        unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point point = v8_ValueToPoint(isolate, args[2 -1]);
        self->insertPoint(index, point);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::RemovePoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] index)" " - " "").ToLocalChecked() ); return; };
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
            self->removePoint(index);
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "Polygon::removePoint: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::GetPointCount(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[number uint]" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        size_t count = self->getPointCount();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, count) ); return; };
    }

    void PolygonWrap::GetPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Point]" " function" "([number uint] index)" " - " "").ToLocalChecked() ); return; };
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
            Point point = self->getPoint(index);
            { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, point) ); return; };
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "Polygon::getPoint: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
    }

    void PolygonWrap::SetPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] index, [object Point] point)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""index"")");
            return;
        }
        unsigned long index = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point point = v8_ValueToPoint(isolate, args[2 -1]);
        try
        {
            self->setPoint(index, point);
            args.GetReturnValue().SetUndefined();
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "Polygon::setPoint: index out of range";
            isolate->ThrowException( v8::Exception::RangeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
        }
    }

    void PolygonWrap::ClearPoints(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->clearPoints();
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::GetBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

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

    void PolygonWrap::CenterPoint(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

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

    void PolygonWrap::Contains(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[boolean]" " function" "([object Point] point)" " - " "").ToLocalChecked() ); return; };
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
        bool contains = self->contains(point);
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, contains) ); return; };
    }

    void PolygonWrap::Empty(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

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

    void PolygonWrap::Equals(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[boolean]" " function" "([object Polygon] other)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, other);
        PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(other->GetAlignedPointerFromInternalField(0));
        Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
        if (!otherPolygonPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "equals must be called with a valid Polygon object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, *self == *otherPolygonPtr) ); return; };
    }

    void PolygonWrap::Move(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "([object Offset] offset)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Offset offset = v8_ValueToOffset(isolate, args[1 -1]);
        self->move(offset);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveLeft(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number delta)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""delta"")");
            return;
        }
        double delta = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveLeft(delta);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveRight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "(number delta)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""delta"")");
            return;
        }
        double delta = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveRight(delta);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveUp(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "(number delta)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""delta"")");
            return;
        }
        double delta = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveUp(delta);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveDown(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "(number delta)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""delta"")");
            return;
        }
        double delta = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveDown(delta);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveXTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number x)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
            return;
        }
        double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveXTo(x);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveYTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number y)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""y"")");
            return;
        }
        double y = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveYTo(y);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::MoveTo(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number x, number y)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
            return;
        }
        double x = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
            return;
        }
        double y = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->moveTo(x, y);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::Center(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

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
        self->center(point);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::Scale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number factor)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
            return;
        }
        double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->scale(factor);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::HorzScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number factor)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
            return;
        }
        double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->horzScale(factor);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::VertScale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number factor)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
            return;
        }
        double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->vertScale(factor);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::ScaleAround(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number factor, [object Point] centerPoint)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""factor"")");
            return;
        }
        double factor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point centerPoint = v8_ValueToPoint(isolate, args[2 -1]);
        self->scaleAround(factor, centerPoint);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::Rotate(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number radians)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
            return;
        }
        double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->rotate(radians);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::RotateAround(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number radians, [object Point] centerPoint)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
            return;
        }
        double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point centerPoint = v8_ValueToPoint(isolate, args[2 -1]);
        self->rotateAround(radians, centerPoint);
        args.GetReturnValue().SetUndefined();
    }

    void PolygonWrap::Intersection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "([object Polygon] other)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, other);
        PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(other->GetAlignedPointerFromInternalField(0));
        Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
        if (!otherPolygonPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "intersection must be called with a valid Polygon object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        Polygon* result = new Polygon(self->intersection(*otherPolygonPtr));
        if (!result) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( PolygonWrap::NewFromCpp(isolate, result) ); return; };
        ;
    }

    void PolygonWrap::UnionWith(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PolygonWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PolygonWrap>(args.This());
        Polygon* self = dynamic_cast<Polygon*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Polygon]" " function" "([object Polygon] other)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        REQUIRE_OBJECT_ARG(1, other);
        PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(other->GetAlignedPointerFromInternalField(0));
        Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
        if (!otherPolygonPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "unionWith must be called with a valid Polygon object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        Polygon* result = new Polygon(self->unionWith(*otherPolygonPtr));
        if (!result) { args.GetReturnValue().SetNull(); return; };
        { args.GetReturnValue().Set( PolygonWrap::NewFromCpp(isolate, result) ); return; };
        ;
    }

    void CleanupPolygonScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

}
