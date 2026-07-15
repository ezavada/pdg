// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/port.cpp
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

    static bool s_Port_InNewFromCpp = false;

    void PortWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = new PortWrap(args);
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
    v8::Local<v8::Object> PortWrap::NewFromCpp(v8::Isolate* isolate, Port* cppObj)
    {
        s_Port_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Port_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Port_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mPortScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Port_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> PortWrap::constructorTpl_;

    void PortWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Port").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetClipRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetClipRect_Tpl =
            v8::FunctionTemplate::New(isolate, GetClipRect, v8::Local<v8::Value>(), GetClipRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ClipRect").ToLocalChecked(), GetClipRect_Tpl);
        v8::Local<v8::Signature> SetClipRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetClipRect_Tpl =
            v8::FunctionTemplate::New(isolate, SetClipRect, v8::Local<v8::Value>(), SetClipRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""ClipRect").ToLocalChecked(), SetClipRect_Tpl);
        v8::Local<v8::Signature> GetCursor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCursor_Tpl =
            v8::FunctionTemplate::New(isolate, GetCursor, v8::Local<v8::Value>(), GetCursor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Cursor").ToLocalChecked(), GetCursor_Tpl);
        v8::Local<v8::Signature> SetCursor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetCursor_Tpl =
            v8::FunctionTemplate::New(isolate, SetCursor, v8::Local<v8::Value>(), SetCursor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Cursor").ToLocalChecked(), SetCursor_Tpl);
        v8::Local<v8::Signature> GetDrawingArea_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetDrawingArea_Tpl =
            v8::FunctionTemplate::New(isolate, GetDrawingArea, v8::Local<v8::Value>(), GetDrawingArea_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""DrawingArea").ToLocalChecked(), GetDrawingArea_Tpl);
        v8::Local<v8::Signature> DrawLine_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawLine_Tpl =
            v8::FunctionTemplate::New(isolate, DrawLine, v8::Local<v8::Value>(), DrawLine_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawLine").ToLocalChecked(), DrawLine_Tpl);
        v8::Local<v8::Signature> DrawSpline_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawSpline_Tpl =
            v8::FunctionTemplate::New(isolate, DrawSpline, v8::Local<v8::Value>(), DrawSpline_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawSpline").ToLocalChecked(), DrawSpline_Tpl);
        v8::Local<v8::Signature> DrawText_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawText_Tpl =
            v8::FunctionTemplate::New(isolate, DrawText, v8::Local<v8::Value>(), DrawText_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawText").ToLocalChecked(), DrawText_Tpl);
        v8::Local<v8::Signature> DrawImage_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawImage_Tpl =
            v8::FunctionTemplate::New(isolate, DrawImage, v8::Local<v8::Value>(), DrawImage_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawImage").ToLocalChecked(), DrawImage_Tpl);
        v8::Local<v8::Signature> GetTextWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTextWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetTextWidth, v8::Local<v8::Value>(), GetTextWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTextWidth").ToLocalChecked(), GetTextWidth_Tpl);
        v8::Local<v8::Signature> GetCurrentFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetCurrentFont_Tpl =
            v8::FunctionTemplate::New(isolate, GetCurrentFont, v8::Local<v8::Value>(), GetCurrentFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getCurrentFont").ToLocalChecked(), GetCurrentFont_Tpl);
        v8::Local<v8::Signature> SetFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFont_Tpl =
            v8::FunctionTemplate::New(isolate, SetFont, v8::Local<v8::Value>(), SetFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFont").ToLocalChecked(), SetFont_Tpl);
        v8::Local<v8::Signature> SetFontForStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFontForStyle_Tpl =
            v8::FunctionTemplate::New(isolate, SetFontForStyle, v8::Local<v8::Value>(), SetFontForStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFontForStyle").ToLocalChecked(), SetFontForStyle_Tpl);
        v8::Local<v8::Signature> SetFontScalingFactor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFontScalingFactor_Tpl =
            v8::FunctionTemplate::New(isolate, SetFontScalingFactor, v8::Local<v8::Value>(), SetFontScalingFactor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setFontScalingFactor").ToLocalChecked(), SetFontScalingFactor_Tpl);
        v8::Local<v8::Signature> StartTrackingMouse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StartTrackingMouse_Tpl =
            v8::FunctionTemplate::New(isolate, StartTrackingMouse, v8::Local<v8::Value>(), StartTrackingMouse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "startTrackingMouse").ToLocalChecked(), StartTrackingMouse_Tpl);
        v8::Local<v8::Signature> StopTrackingMouse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> StopTrackingMouse_Tpl =
            v8::FunctionTemplate::New(isolate, StopTrackingMouse, v8::Local<v8::Value>(), StopTrackingMouse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "stopTrackingMouse").ToLocalChecked(), StopTrackingMouse_Tpl);
        v8::Local<v8::Signature> ResetCursor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ResetCursor_Tpl =
            v8::FunctionTemplate::New(isolate, ResetCursor, v8::Local<v8::Value>(), ResetCursor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "resetCursor").ToLocalChecked(), ResetCursor_Tpl);
        v8::Local<v8::Signature> DrawRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawRect_Tpl =
            v8::FunctionTemplate::New(isolate, DrawRect, v8::Local<v8::Value>(), DrawRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawRect").ToLocalChecked(), DrawRect_Tpl);
        v8::Local<v8::Signature> DrawQuad_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawQuad_Tpl =
            v8::FunctionTemplate::New(isolate, DrawQuad, v8::Local<v8::Value>(), DrawQuad_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawQuad").ToLocalChecked(), DrawQuad_Tpl);
        v8::Local<v8::Signature> DrawPolygon_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawPolygon_Tpl =
            v8::FunctionTemplate::New(isolate, DrawPolygon, v8::Local<v8::Value>(), DrawPolygon_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawPolygon").ToLocalChecked(), DrawPolygon_Tpl);
        v8::Local<v8::Signature> DrawEllipse_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawEllipse_Tpl =
            v8::FunctionTemplate::New(isolate, DrawEllipse, v8::Local<v8::Value>(), DrawEllipse_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawEllipse").ToLocalChecked(), DrawEllipse_Tpl);
        v8::Local<v8::Signature> DrawArc_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawArc_Tpl =
            v8::FunctionTemplate::New(isolate, DrawArc, v8::Local<v8::Value>(), DrawArc_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawArc").ToLocalChecked(), DrawArc_Tpl);
        v8::Local<v8::Signature> DrawBezier_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawBezier_Tpl =
            v8::FunctionTemplate::New(isolate, DrawBezier, v8::Local<v8::Value>(), DrawBezier_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawBezier").ToLocalChecked(), DrawBezier_Tpl);
        v8::Local<v8::Signature> DrawCircle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawCircle_Tpl =
            v8::FunctionTemplate::New(isolate, DrawCircle, v8::Local<v8::Value>(), DrawCircle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawCircle").ToLocalChecked(), DrawCircle_Tpl);
        v8::Local<v8::Signature> DrawVector_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawVector_Tpl =
            v8::FunctionTemplate::New(isolate, DrawVector, v8::Local<v8::Value>(), DrawVector_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawVector").ToLocalChecked(), DrawVector_Tpl);
        v8::Local<v8::Signature> DrawRoundedRect_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawRoundedRect_Tpl =
            v8::FunctionTemplate::New(isolate, DrawRoundedRect, v8::Local<v8::Value>(), DrawRoundedRect_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawRoundedRect").ToLocalChecked(), DrawRoundedRect_Tpl);
        v8::Local<v8::Signature> DrawDrawing_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawDrawing_Tpl =
            v8::FunctionTemplate::New(isolate, DrawDrawing, v8::Local<v8::Value>(), DrawDrawing_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawDrawing").ToLocalChecked(), DrawDrawing_Tpl);
        v8::Local<v8::Signature> DrawSphere_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> DrawSphere_Tpl =
            v8::FunctionTemplate::New(isolate, DrawSphere, v8::Local<v8::Value>(), DrawSphere_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "drawSphere").ToLocalChecked(), DrawSphere_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void PortWrap::GetDrawingArea(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Rect theDrawingArea = self->getDrawingArea();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, theDrawingArea) ); return; };
    }

    void PortWrap::GetClipRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Rect]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Rect theClipRect = self->getClipRect();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, theClipRect) ); return; };
    }

    void PortWrap::SetClipRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Port]" " function" "([object Rect] inClipRect)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect theClipRect = v8_ValueToRect(isolate, args[1 -1]);

        self->setClipRect(theClipRect);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void PortWrap::DrawLine(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] from, [object Point] to, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        self->drawLine(from, to, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawSpline(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Spline] spline, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_OBJECT_ARG(1, spline);
        REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
        SplineWrap* splineWrapper = static_cast<SplineWrap*>(spline->GetAlignedPointerFromInternalField(0));
        Spline* splinePtr = splineWrapper->getCppObject();
        if (!splinePtr)
        {
            std::ostringstream excpt_;
            excpt_ << "drawSpline must be called with a valid Spline object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        self->drawSpline(*splinePtr, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::GetTextWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "(string text, [number int] size, [number uint] style = textStyle_Plain, [number int] len = -1)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2, true);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""text"")");
            return;
        }
        v8::String::Utf8Value text_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* text = *text_Str;;
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""size"")");
            return;
        }
        long size = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        if (args.Length() >= 3 && !args[3 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 3, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<3) ? textStyle_Plain : args[3 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;
        if (args.Length() >= 4 && !args[4 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 4, "a number (""len"")");
            return;
        }
        long len = (args.Length()<4) ? -1 : args[4 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();;
        int width = self->getTextWidth(text, size, style, len);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, width) ); return; };
    }

    void PortWrap::GetCurrentFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Font]" " function" "([number uint] style = textStyle_Plain)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""style"")");
            return;
        }
        unsigned long style = (args.Length()<1) ? textStyle_Plain : args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();;
        Font* font = self->getCurrentFont(style);
        if (!font) { args.GetReturnValue().SetNull(); return; };
        if (font->mFontScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( FontWrap::NewFromCpp(isolate, font) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, font->mFontScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void PortWrap::SetFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Font] font = DEFAULT_FONT)" " - " "").ToLocalChecked() ); return; };
        };
        Font* font = 0;
        if (args.Length() >= 1)
        {
            if (!args[1 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 1, "an object of type ""Font"" (""font"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> font_ = args[1 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                FontWrap* font__ = jswrap::ObjectWrap::Unwrap<FontWrap>(font_);
                font = font__->getCppObject();
            }
        };
        self->setFont(font);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::SetFontForStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number uint] style, [object Font] font = DEFAULT_FONT)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""style"")");
            return;
        }
        unsigned long style = args[1 -1]->Uint32Value(isolate->GetCurrentContext()).ToChecked();
        Font* font = 0;
        if (args.Length() >= 2)
        {
            if (!args[2 -1]->IsObject())
            {
                v8_ThrowArgTypeException(isolate, 2, "an object of type ""Font"" (""font"")");
                return;
            }
            else
            {
                v8::Local<v8::Object> font_ = args[2 -1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
                FontWrap* font__ = jswrap::ObjectWrap::Unwrap<FontWrap>(font_);
                font = font__->getCppObject();
            }
        };
        self->setFontForStyle(font, style);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::SetFontScalingFactor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "(number scaleBy)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""scaleBy"")");
            return;
        }
        double scaleBy = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        self->setFontScalingFactor(scaleBy);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::StartTrackingMouse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "([object Rect] rect)" " - " "NOT IMPLEMENTED").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        if (!v8_ValueIsRect(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
            return;
        }
        pdg::Rect rect = v8_ValueToRect(isolate, args[1 -1]);
        int trackingRef = self->startTrackingMouse(rect);
        { args.GetReturnValue().Set( v8::Integer::New(isolate, trackingRef) ); return; };
    }

    void PortWrap::StopTrackingMouse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([number int] trackingRef)" " - " "NOT IMPLEMENTED").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""trackingRef"")");
            return;
        }
        long trackingRef = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        self->stopTrackingMouse(trackingRef);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::SetCursor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Image] cursorImage, [object Point] hotSpot)" " - " "NOT IMPLEMENTED").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, cursorImage, Image);
        if (!v8_ValueIsPoint(isolate, args[2 -1]))
        {
            v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
            return;
        }
        pdg::Point hotSpot = v8_ValueToPoint(isolate, args[2 -1]);
        self->setCursor(cursorImage, hotSpot);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::GetCursor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Image]" " function" "()" " - " "NOT IMPLEMENTED: get the Image that is being used as the cursor").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Image* cursorImage = self->getCursor();
        if (!cursorImage) { args.GetReturnValue().SetNull(); return; };
        if (cursorImage->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, cursorImage) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, cursorImage->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void PortWrap::ResetCursor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "()" " - " "NOT IMPLEMENTED: restore the default system cursor").ToLocalChecked() ); return; };
        };

        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->resetCursor();
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Rect] rect, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
        self->drawRect(rect, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawQuad(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Quad] quad, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
        self->drawQuad(quad, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawPolygon(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Polygon] polygon, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, polygon, Polygon);
        REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
        self->drawPolygon(*polygon, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawEllipse(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] center, [number float] xRadius, [number float] yRadius, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        REQUIRE_CPP_OBJECT_ARG(4, attrs, Attributes);
        self->drawEllipse(center, xRadius, yRadius, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawArc(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] center, [number float] xRadius, [number float] yRadius, [number float] startAngle, [number float] endAngle, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        REQUIRE_CPP_OBJECT_ARG(6, attrs, Attributes);
        self->drawArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawBezier(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] from, [object Point] control1, [object Point] control2, [object Point] to, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 5)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 5);
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
        pdg::Point control1 = v8_ValueToPoint(isolate, args[2 -1]);
        if (!v8_ValueIsPoint(isolate, args[3 -1]))
        {
            v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
            return;
        }
        pdg::Point control2 = v8_ValueToPoint(isolate, args[3 -1]);
        if (!v8_ValueIsPoint(isolate, args[4 -1]))
        {
            v8_ThrowArgTypeException(isolate, 4, "Point", *args[4 -1]);
            return;
        }
        pdg::Point to = v8_ValueToPoint(isolate, args[4 -1]);
        REQUIRE_CPP_OBJECT_ARG(5, attrs, Attributes);
        self->drawBezier(from, control1, control2, to, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawCircle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] center, [number float] radius, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point center = v8_ValueToPoint(isolate, args[1 -1]);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""radius"")");
            return;
        }
        double radius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        self->drawCircle(center, radius, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawVector(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Vector] vector, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 2)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 2);
            return;
        };
        if (!v8_ValueIsVector(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Vector", *args[1 -1]);
            return;
        }
        pdg::Vector vector = v8_ValueToVector(isolate, args[1 -1]);
        REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
        self->drawVector(vector, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawRoundedRect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Rect] rect, [number float] radius, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""radius"")");
            return;
        }
        double radius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        self->drawRoundedRect(rect, radius, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawImage(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({[object Image] img, [object Point] loc, [object Attributes] attrs|[object Image] img, [object Rect] rect, [object Attributes] attrs|[object Image] img, [object Quad] quad, [object Attributes] attrs})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        REQUIRE_CPP_OBJECT_ARG(1, img, Image);
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        if (v8_ValueIsPoint(isolate, args[1]))
        {

            pdg::Point loc = v8_ValueToPoint(isolate, args[1]);
            self->drawImage(img, loc, *attrs);
        }
        else if (v8_ValueIsQuad(isolate, args[1]))
        {

            pdg::Quad quad = v8_ValueToQuad(isolate, args[1]);
            self->drawImage(img, quad, *attrs);
        }
        else
        {

            if (!v8_ValueIsRect(isolate, args[2 -1]))
            {
                v8_ThrowArgTypeException(isolate, 2, "Rect", *args[2 -1]);
                return;
            }
            pdg::Rect rect = v8_ValueToRect(isolate, args[2 -1]);
            self->drawImage(img, rect, *attrs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawDrawing(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({[object Drawing] drawing, [object Point] loc, [object Attributes] attrs|[object Drawing] drawing, [object Rect] rect, [object Attributes] attrs})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        REQUIRE_OBJECT_ARG(1, drawing);
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        DrawingWrap* drawingWrapper = static_cast<DrawingWrap*>(drawing->GetAlignedPointerFromInternalField(0));
        Drawing* drawingPtr = drawingWrapper->getCppObject();
        if (!drawingPtr)
        {
            std::ostringstream excpt_;
            excpt_ << "drawDrawingWithAttrs must be called with a valid Drawing object";
            isolate->ThrowException( v8::Exception::TypeError( ([&]()
            {
                v8::MaybeLocal<v8::String> maybe = v8::String::NewFromUtf8(isolate, excpt_.str().c_str());
                    return maybe.IsEmpty() ?
                    v8::String::NewFromUtf8Literal(isolate, "[String creation failed]") : maybe.ToLocalChecked();
            }())));
            return;
        }
        if (v8_ValueIsPoint(isolate, args[1]))
        {

            pdg::Point loc = v8_ValueToPoint(isolate, args[1]);
            self->drawDrawing(*drawingPtr, loc, *attrs);
        }
        else
        {

            if (!v8_ValueIsRect(isolate, args[2 -1]))
            {
                v8_ThrowArgTypeException(isolate, 2, "Rect", *args[2 -1]);
                return;
            }
            pdg::Rect rect = v8_ValueToRect(isolate, args[2 -1]);
            self->drawDrawing(*drawingPtr, rect, *attrs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawText(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "({string text, [object Point] loc, [object Attributes] attrs|string text, [object Rect] rect, [object Attributes] attrs})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() != 3)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 3);
            return;
        };
        if (!args[1 -1]->IsString())
        {
            v8_ThrowArgTypeException(isolate, 1, "a string  (""text"")");
            return;
        }
        v8::String::Utf8Value text_Str(isolate, args[1 -1]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
        const char* text = *text_Str;;
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        if (v8_ValueIsPoint(isolate, args[1]))
        {

            pdg::Point loc = v8_ValueToPoint(isolate, args[1]);
            self->drawText(text, loc, *attrs);
        }
        else
        {

            if (!v8_ValueIsRect(isolate, args[2 -1]))
            {
                v8_ThrowArgTypeException(isolate, 2, "Rect", *args[2 -1]);
                return;
            }
            pdg::Rect rect = v8_ValueToRect(isolate, args[2 -1]);
            self->drawText(text, rect, *attrs);
        }
        args.GetReturnValue().SetUndefined();
    }

    void PortWrap::DrawSphere(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        PortWrap* objWrapper = jswrap::ObjectWrap::Unwrap<PortWrap>(args.This());
        Port* self = dynamic_cast<Port*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "undefined" " function" "([object Point] center, [number float] radius, [object Attributes] attrs)" " - " "").ToLocalChecked() ); return; };
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
        pdg::Point center = v8_ValueToPoint(isolate, args[1 -1]);
        if (!args[2 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 2, "a number (""radius"")");
            return;
        }
        double radius = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
        self->drawSphere(center, radius, *attrs);
        args.GetReturnValue().SetUndefined();
    }

    void CleanupPortScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    PortWrap::PortWrap(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        cppPtr_ = nullptr;
    }

    PortWrap::~PortWrap()
    {
        cppPtr_ = nullptr;
    }

    Port* New_Port(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Port_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        s_HaveSavedError = true;
        {
            std::ostringstream excpt_;
            excpt_ << "Port cannot be created directly, use pdg.gfx.createWindowPort() or pdg.gfx.createFullScreenPort()";
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
        };
        return 0;
    }
#endif

}
