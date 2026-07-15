// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/image.cpp
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

    bool s_Image_InNewFromCpp = false;

    void ImageWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = new ImageWrap(args);
        objWrapper->Wrap(args.This());
        Image* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mImageScriptObj.Reset(isolate, args.This());
        }
        objWrapper->Ref();
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> ImageWrap::NewFromCpp(v8::Isolate* isolate, Image* cppObj)
    {
        s_Image_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Image_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Image_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mImageScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Image_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ImageWrap::constructorTpl_;

    void ImageWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Image").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetWidth, v8::Local<v8::Value>(), GetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Width").ToLocalChecked(), GetWidth_Tpl);
        v8::Local<v8::Signature> GetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetHeight, v8::Local<v8::Value>(), GetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Height").ToLocalChecked(), GetHeight_Tpl);
        v8::Local<v8::Signature> GetImageBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImageBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetImageBounds, v8::Local<v8::Value>(), GetImageBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ImageBounds").ToLocalChecked(), GetImageBounds_Tpl);
        v8::Local<v8::Signature> GetSubsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSubsection_Tpl =
            v8::FunctionTemplate::New(isolate, GetSubsection, v8::Local<v8::Value>(), GetSubsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Subsection").ToLocalChecked(), GetSubsection_Tpl);
        v8::Local<v8::Signature> SetTransparentColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTransparentColor_Tpl =
            v8::FunctionTemplate::New(isolate, SetTransparentColor, v8::Local<v8::Value>(), SetTransparentColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""TransparentColor").ToLocalChecked(), SetTransparentColor_Tpl);
        v8::Local<v8::Signature> GetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetOpacity, v8::Local<v8::Value>(), GetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Opacity").ToLocalChecked(), GetOpacity_Tpl);
        v8::Local<v8::Signature> SetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, SetOpacity, v8::Local<v8::Value>(), SetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Opacity").ToLocalChecked(), SetOpacity_Tpl);
        v8::Local<v8::Signature> SetEdgeClamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetEdgeClamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetEdgeClamping, v8::Local<v8::Value>(), SetEdgeClamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""EdgeClamping").ToLocalChecked(), SetEdgeClamping_Tpl);
        v8::Local<v8::Signature> GetTransparentColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTransparentColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetTransparentColor, v8::Local<v8::Value>(), GetTransparentColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTransparentColor").ToLocalChecked(), GetTransparentColor_Tpl);
        v8::Local<v8::Signature> RetainData_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RetainData_Tpl =
            v8::FunctionTemplate::New(isolate, RetainData, v8::Local<v8::Value>(), RetainData_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "retainData").ToLocalChecked(), RetainData_Tpl);
        v8::Local<v8::Signature> RetainAlpha_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RetainAlpha_Tpl =
            v8::FunctionTemplate::New(isolate, RetainAlpha, v8::Local<v8::Value>(), RetainAlpha_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "retainAlpha").ToLocalChecked(), RetainAlpha_Tpl);
        v8::Local<v8::Signature> PrepareToRasterize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PrepareToRasterize_Tpl =
            v8::FunctionTemplate::New(isolate, PrepareToRasterize, v8::Local<v8::Value>(), PrepareToRasterize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "prepareToRasterize").ToLocalChecked(), PrepareToRasterize_Tpl);
        v8::Local<v8::Signature> GetAlphaValue_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAlphaValue_Tpl =
            v8::FunctionTemplate::New(isolate, GetAlphaValue, v8::Local<v8::Value>(), GetAlphaValue_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""AlphaValue").ToLocalChecked(), GetAlphaValue_Tpl);
        v8::Local<v8::Signature> GetPixel_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPixel_Tpl =
            v8::FunctionTemplate::New(isolate, GetPixel, v8::Local<v8::Value>(), GetPixel_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPixel").ToLocalChecked(), GetPixel_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void ImageWrap::GetTransparentColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Color]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Color theTransparentColor = self->getTransparentColor();
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, theTransparentColor) ); return; };
    }

    void ImageWrap::SetTransparentColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Image]" " function" "([object Color] inTransparentColor)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsColor(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        }
        pdg::Color theTransparentColor = v8_ValueToColor(isolate, args[1 -1]);

        self->setTransparentColor(theTransparentColor);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ImageWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theWidth = self->getWidth();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theWidth) ); return; };
    }

    void ImageWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theHeight = self->getHeight();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theHeight) ); return; };
    }

    void ImageWrap::GetImageBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [object Rect]" " function" "([object Point] at)" " - " "get image boundary rect, optionally with top left at given point").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point at = (args.Length()<1) ? pdg::Point(0,0) : v8_ValueToPoint(isolate, args[1 -1]);
        Rect r = self->getImageBounds(at);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void ImageWrap::GetSubsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [object Image]" " function" "({[object Quad]|[object Rect]} quad)" " - " "get image that is an arbitrary subsection of this image").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsQuad(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
            return;
        }
        pdg::Quad quad = v8_ValueToQuad(isolate, args[1 -1]);
        Image* image = self->getSubsection(quad);
        if (!image) { args.GetReturnValue().SetNull(); return; };
        if (image->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, image) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, image->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void ImageWrap::GetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR number" " function" "()" " - " "get opacity of this image: 0.0 - completely transparent to 1.0 - completely solid").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        uint8 opacity = self->getOpacity();
        double opacityFloat = (float)opacity / 255.0f;
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacityFloat) ); return; };
    }

    void ImageWrap::SetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "(number opacity)" " - " "set opacity of this image as range from either (0-255) or (0.0 to 1.0)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""opacityFloat"")");
            return;
        }
        double opacityFloat = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        uint32 opacity;
        if (opacityFloat <= 1.0)
        {
            opacity = std::floor(255.0f * opacityFloat);
        }
        else
        {
            opacity = std::round(opacityFloat);
        }
        if (opacity > 255) opacity = 255;
        self->setOpacity(opacity);
        args.GetReturnValue().SetUndefined();
    }

    void ImageWrap::SetEdgeClamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "(boolean inUseEdgeClamp)" " - " "set whether image uses edge clamping or not").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""inUseEdgeClamp"")");
            return;
        }
        bool inUseEdgeClamp = args[1 -1]->BooleanValue(isolate);
        self->setEdgeClamping(inUseEdgeClamp);
        args.GetReturnValue().SetUndefined();
    }

    void ImageWrap::RetainData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "()" " - " "retain pixel data for use by Image.getPixel()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->retainData();
        args.GetReturnValue().SetUndefined();
    }

    void ImageWrap::RetainAlpha(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "()" " - " "retain alpha data for use by Image.getAlphaValue() or per-pixel sprite collisions").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->retainAlpha();
        args.GetReturnValue().SetUndefined();
    }

    void ImageWrap::PrepareToRasterize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR number" " function" "()" " - " "bind the image into an OpenGL texture and free image data from main memory").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->prepareToRasterize();
        args.GetReturnValue().SetUndefined();
    }

    void ImageWrap::GetAlphaValue(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "({[object Point] p|[number int] x, [number int] y})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        uint8 a;
        if (args.Length() >= 2)
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            a = self->getAlphaValue(x, y);
        }
        else
        {
            if (!v8_ValueIsPoint(isolate, args[1 -1]))
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }
            pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
            a = self->getAlphaValue(p.x, p.y);
        }
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, a) ); return; };
    }

    void ImageWrap::GetPixel(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageWrap>(args.This());
        Image* self = dynamic_cast<Image*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Color]" " function" "({[object Point] p|[number int] x, [number int] y})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Color c;
        if (args.Length() >= 2)
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            c = self->getPixel(x, y);
        }
        else
        {
            if (!v8_ValueIsPoint(isolate, args[1 -1]))
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }
            pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
            c = self->getPixel(p.x, p.y);
        }
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, c) ); return; };
    }

    void CleanupImageScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    ImageWrap::ImageWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_Image(args);
        if (!cppPtr_ && !s_Image_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Image" " instance")));
            };
        }
    }

    ImageWrap::~ImageWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Image* New_Image(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Image_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() < 1)
        {
            return 0;
        }
        else if ((args.Length() == 1 && args[0]->IsNull()))
        {
            return Image::createEmptyImageForIntrospection();
        }
        else if (!args[0]->IsString())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 must be a string (filename)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        else
        {
            v8::String::Utf8Value filename_Str(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* filename = *filename_Str;;
            Image* img = Image::createImageFromFile(filename);
            if (!img)
            {
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << "could not create Image from file ["<<filename<<"]";
                    v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };
                return 0;
            }
            else
            {
                return img;
            }
        }
    }

    bool s_ImageStrip_InNewFromCpp = false;

    void ImageStripWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = new ImageStripWrap(args);
        objWrapper->Wrap(args.This());
        ImageStrip* cppObj = objWrapper->getCppObject();
        if (cppObj)
        {
            cppObj->mImageStripScriptObj.Reset(isolate, args.This());
        }
        objWrapper->Ref();
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            v8::Local<v8::Value> s_err_ = v8::Local<v8::Value>::New(isolate, s_SavedError);
            isolate->ThrowException(s_err_);
        };
        { args.GetReturnValue().Set( args.This() ); return; };
    }
    v8::Local<v8::Object> ImageStripWrap::NewFromCpp(v8::Isolate* isolate, ImageStrip* cppObj)
    {
        s_ImageStrip_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_ImageStrip_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_ImageStrip_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(instance);
        {
            v8::Local<v8::Object> obj = instance;
            cppObj->mImageStripScriptObj.Reset(isolate, obj);
            objWrapper->Ref();
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_ImageStrip_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> ImageStripWrap::constructorTpl_;

    void ImageStripWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "ImageStrip").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> GetWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetWidth, v8::Local<v8::Value>(), GetWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Width").ToLocalChecked(), GetWidth_Tpl);
        v8::Local<v8::Signature> GetHeight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetHeight_Tpl =
            v8::FunctionTemplate::New(isolate, GetHeight, v8::Local<v8::Value>(), GetHeight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Height").ToLocalChecked(), GetHeight_Tpl);
        v8::Local<v8::Signature> GetImageBounds_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetImageBounds_Tpl =
            v8::FunctionTemplate::New(isolate, GetImageBounds, v8::Local<v8::Value>(), GetImageBounds_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""ImageBounds").ToLocalChecked(), GetImageBounds_Tpl);
        v8::Local<v8::Signature> GetSubsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSubsection_Tpl =
            v8::FunctionTemplate::New(isolate, GetSubsection, v8::Local<v8::Value>(), GetSubsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Subsection").ToLocalChecked(), GetSubsection_Tpl);
        v8::Local<v8::Signature> SetTransparentColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTransparentColor_Tpl =
            v8::FunctionTemplate::New(isolate, SetTransparentColor, v8::Local<v8::Value>(), SetTransparentColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""TransparentColor").ToLocalChecked(), SetTransparentColor_Tpl);
        v8::Local<v8::Signature> GetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetOpacity, v8::Local<v8::Value>(), GetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Opacity").ToLocalChecked(), GetOpacity_Tpl);
        v8::Local<v8::Signature> SetOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, SetOpacity, v8::Local<v8::Value>(), SetOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""Opacity").ToLocalChecked(), SetOpacity_Tpl);
        v8::Local<v8::Signature> SetEdgeClamping_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetEdgeClamping_Tpl =
            v8::FunctionTemplate::New(isolate, SetEdgeClamping, v8::Local<v8::Value>(), SetEdgeClamping_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""EdgeClamping").ToLocalChecked(), SetEdgeClamping_Tpl);
        v8::Local<v8::Signature> GetTransparentColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTransparentColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetTransparentColor, v8::Local<v8::Value>(), GetTransparentColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTransparentColor").ToLocalChecked(), GetTransparentColor_Tpl);
        v8::Local<v8::Signature> RetainData_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RetainData_Tpl =
            v8::FunctionTemplate::New(isolate, RetainData, v8::Local<v8::Value>(), RetainData_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "retainData").ToLocalChecked(), RetainData_Tpl);
        v8::Local<v8::Signature> RetainAlpha_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RetainAlpha_Tpl =
            v8::FunctionTemplate::New(isolate, RetainAlpha, v8::Local<v8::Value>(), RetainAlpha_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "retainAlpha").ToLocalChecked(), RetainAlpha_Tpl);
        v8::Local<v8::Signature> PrepareToRasterize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PrepareToRasterize_Tpl =
            v8::FunctionTemplate::New(isolate, PrepareToRasterize, v8::Local<v8::Value>(), PrepareToRasterize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "prepareToRasterize").ToLocalChecked(), PrepareToRasterize_Tpl);
        v8::Local<v8::Signature> GetAlphaValue_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAlphaValue_Tpl =
            v8::FunctionTemplate::New(isolate, GetAlphaValue, v8::Local<v8::Value>(), GetAlphaValue_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""AlphaValue").ToLocalChecked(), GetAlphaValue_Tpl);
        v8::Local<v8::Signature> GetPixel_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPixel_Tpl =
            v8::FunctionTemplate::New(isolate, GetPixel, v8::Local<v8::Value>(), GetPixel_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPixel").ToLocalChecked(), GetPixel_Tpl);
        v8::Local<v8::Signature> GetFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrame_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrame, v8::Local<v8::Value>(), GetFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""Frame").ToLocalChecked(), GetFrame_Tpl);
        v8::Local<v8::Signature> GetFrameWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrameWidth_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrameWidth, v8::Local<v8::Value>(), GetFrameWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""FrameWidth").ToLocalChecked(), GetFrameWidth_Tpl);
        v8::Local<v8::Signature> SetFrameWidth_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFrameWidth_Tpl =
            v8::FunctionTemplate::New(isolate, SetFrameWidth, v8::Local<v8::Value>(), SetFrameWidth_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""FrameWidth").ToLocalChecked(), SetFrameWidth_Tpl);
        v8::Local<v8::Signature> GetNumFrames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetNumFrames_Tpl =
            v8::FunctionTemplate::New(isolate, GetNumFrames, v8::Local<v8::Value>(), GetNumFrames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "get""NumFrames").ToLocalChecked(), GetNumFrames_Tpl);
        v8::Local<v8::Signature> SetNumFrames_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetNumFrames_Tpl =
            v8::FunctionTemplate::New(isolate, SetNumFrames, v8::Local<v8::Value>(), SetNumFrames_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "set""NumFrames").ToLocalChecked(), SetNumFrames_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();

    }

    void ImageStripWrap::GetTransparentColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Color]" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        pdg::Color theTransparentColor = self->getTransparentColor();
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, theTransparentColor) ); return; };
    }

    void ImageStripWrap::SetTransparentColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ImageStrip]" " function" "([object Color] inTransparentColor)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsColor(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
            return;
        }
        pdg::Color theTransparentColor = v8_ValueToColor(isolate, args[1 -1]);

        self->setTransparentColor(theTransparentColor);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ImageStripWrap::GetWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theWidth = self->getWidth();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theWidth) ); return; };
    }

    void ImageStripWrap::GetHeight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int theHeight = self->getHeight();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theHeight) ); return; };
    }

    void ImageStripWrap::GetImageBounds(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [object Rect]" " function" "([object Point] at)" " - " "get image boundary rect, optionally with top left at given point").ToLocalChecked() ); return; };
        };
        if (args.Length() >= 1 && !v8_ValueIsPoint(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
            return;
        }
        pdg::Point at = (args.Length()<1) ? pdg::Point(0,0) : v8_ValueToPoint(isolate, args[1 -1]);
        Rect r = self->getImageBounds(at);
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, r) ); return; };
    }

    void ImageStripWrap::GetSubsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR [object Image]" " function" "({[object Quad]|[object Rect]} quad)" " - " "get image that is an arbitrary subsection of this image").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!v8_ValueIsQuad(isolate, args[1 -1]))
        {
            v8_ThrowArgTypeException(isolate, 1, "Quad", *args[1 -1]);
            return;
        }
        pdg::Quad quad = v8_ValueToQuad(isolate, args[1 -1]);
        Image* image = self->getSubsection(quad);
        if (!image) { args.GetReturnValue().SetNull(); return; };
        if (image->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, image) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, image->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void ImageStripWrap::GetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR number" " function" "()" " - " "get opacity of this image: 0.0 - completely transparent to 1.0 - completely solid").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        uint8 opacity = self->getOpacity();
        double opacityFloat = (float)opacity / 255.0f;
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacityFloat) ); return; };
    }

    void ImageStripWrap::SetOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "(number opacity)" " - " "set opacity of this image as range from either (0-255) or (0.0 to 1.0)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""opacityFloat"")");
            return;
        }
        double opacityFloat = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
        uint32 opacity;
        if (opacityFloat <= 1.0)
        {
            opacity = std::floor(255.0f * opacityFloat);
        }
        else
        {
            opacity = std::round(opacityFloat);
        }
        if (opacity > 255) opacity = 255;
        self->setOpacity(opacity);
        args.GetReturnValue().SetUndefined();
    }

    void ImageStripWrap::SetEdgeClamping(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "(boolean inUseEdgeClamp)" " - " "set whether image uses edge clamping or not").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 1, "a boolean (""inUseEdgeClamp"")");
            return;
        }
        bool inUseEdgeClamp = args[1 -1]->BooleanValue(isolate);
        self->setEdgeClamping(inUseEdgeClamp);
        args.GetReturnValue().SetUndefined();
    }

    void ImageStripWrap::RetainData(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "()" " - " "retain pixel data for use by Image.getPixel()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->retainData();
        args.GetReturnValue().SetUndefined();
    }

    void ImageStripWrap::RetainAlpha(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR undefined" " function" "()" " - " "retain alpha data for use by Image.getAlphaValue() or per-pixel sprite collisions").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->retainAlpha();
        args.GetReturnValue().SetUndefined();
    }

    void ImageStripWrap::PrepareToRasterize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "CR number" " function" "()" " - " "bind the image into an OpenGL texture and free image data from main memory").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        self->prepareToRasterize();
        args.GetReturnValue().SetUndefined();
    }

    void ImageStripWrap::GetAlphaValue(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "({[object Point] p|[number int] x, [number int] y})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        uint8 a;
        if (args.Length() >= 2)
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            a = self->getAlphaValue(x, y);
        }
        else
        {
            if (!v8_ValueIsPoint(isolate, args[1 -1]))
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }
            pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
            a = self->getAlphaValue(p.x, p.y);
        }
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, a) ); return; };
    }

    void ImageStripWrap::GetPixel(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Color]" " function" "({[object Point] p|[number int] x, [number int] y})" " - " "").ToLocalChecked() ); return; };
        };
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };
        pdg::Color c;
        if (args.Length() >= 2)
        {
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""x"")");
                return;
            }
            long x = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""y"")");
                return;
            }
            long y = args[2 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
            c = self->getPixel(x, y);
        }
        else
        {
            if (!v8_ValueIsPoint(isolate, args[1 -1]))
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            }
            pdg::Point p = v8_ValueToPoint(isolate, args[1 -1]);
            c = self->getPixel(p.x, p.y);
        }
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, c) ); return; };
    }

    void ImageStripWrap::GetNumFrames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int32 theNumFrames = self->getNumFrames();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theNumFrames) ); return; };
    }

    void ImageStripWrap::SetNumFrames(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ImageStrip]" " function" "([number int] inNumFrames)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theNumFrames"")");
            return;
        }
        long theNumFrames = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        self->setNumFrames(theNumFrames);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ImageStripWrap::GetFrameWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "number" " function" "()").ToLocalChecked() ); return; };
        };
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };

        int32 theFrameWidth = self->getFrameWidth();
        { args.GetReturnValue().Set( v8::Integer::New(isolate, theFrameWidth) ); return; };
    }

    void ImageStripWrap::SetFrameWidth(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object ImageStrip]" " function" "([number int] inFrameWidth)").ToLocalChecked() ); return; };
        };
        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""theFrameWidth"")");
            return;
        }
        long theFrameWidth = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();

        self->setFrameWidth(theFrameWidth);
        { args.GetReturnValue().Set( args.This() ); return; };
    }

    void ImageStripWrap::GetFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::Isolate* isolate = args.GetIsolate();
        ImageStripWrap* objWrapper = jswrap::ObjectWrap::Unwrap<ImageStripWrap>(args.This());
        ImageStrip* self = dynamic_cast<ImageStrip*>(objWrapper->cppPtr_);

        if (args.Length() == 1 && args[0]->IsNull())
        {
            { args.GetReturnValue().Set( v8::String::NewFromUtf8(isolate, "[object Image]" " function" "([number int] frameNum)" " - " "get image that is a single frame of this multi-frame image").ToLocalChecked() ); return; };
        };

        if (args.Length() != 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1);
            return;
        };
        if (!args[1 -1]->IsNumber())
        {
            v8_ThrowArgTypeException(isolate, 1, "a number (""frameNum"")");
            return;
        }
        long frameNum = args[1 -1]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        Image* image = self->getFrame(frameNum);
        if (!image) { args.GetReturnValue().SetNull(); return; };
        if (image->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, image) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, image->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void CleanupImageStripScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    ImageStripWrap::ImageStripWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        cppPtr_ = New_ImageStrip(args);
        if (!cppPtr_ && !s_ImageStrip_InNewFromCpp)
        {
            {
                v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "ImageStrip" " instance")));
            };
        }
    }

    ImageStripWrap::~ImageStripWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    ImageStrip* New_ImageStrip(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_ImageStrip_InNewFromCpp) return nullptr;
        v8::Isolate* isolate = args.GetIsolate();
        ;
        if (args.Length() < 1)
        {
            return 0;
        }
        else if ((args.Length() == 1 && args[0]->IsNull()))
        {
            return ImageStrip::createEmptyImageStripForIntrospection();
        }
        else if (!args[0]->IsString())
        {
            s_HaveSavedError = true;
            {
                std::ostringstream excpt_;
                excpt_ << "argument 1 must be a string (filename)";
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                s_SavedError.Reset(isolate, v8::Exception::SyntaxError( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
            };
            return 0;
        }
        else
        {
            v8::String::Utf8Value filename_Str(isolate, args[0]->ToString(isolate->GetCurrentContext()).ToLocalChecked());
            const char* filename = *filename_Str;;
            ImageStrip* img = ImageStrip::createImageStripFromFile(filename);
            if (!img)
            {
                s_HaveSavedError = true;
                {
                    std::ostringstream excpt_;
                    excpt_ << "could not create ImageStrip from file ["<<filename<<"]";
                    v8::Isolate* isolate = v8::Isolate::GetCurrent();
                    s_SavedError.Reset(isolate, v8::Exception::Error( v8::String::NewFromUtf8(isolate, excpt_.str().c_str()).ToLocalChecked()));
                };
                return 0;
            }
            else
            {
                return img;
            }
        }
    }

}
