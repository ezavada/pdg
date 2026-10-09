// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/attributes.cpp
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
#include <cmath>
#include <limits>

namespace pdg
{

    static bool s_Attributes_InNewFromCpp = false;

    void AttributesWrap::New(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = new AttributesWrap(args);
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
    v8::Local<v8::Object> AttributesWrap::NewFromCpp(v8::Isolate* isolate, Attributes* cppObj)
    {
        s_Attributes_InNewFromCpp = true;
        v8::EscapableHandleScope scope(isolate);
        v8::Local<v8::FunctionTemplate> constructor = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTpl_);
        v8::MaybeLocal<v8::Function> maybeFunc = constructor->GetFunction(isolate->GetCurrentContext());
        if (maybeFunc.IsEmpty())
        {
            s_Attributes_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Function> func = maybeFunc.ToLocalChecked();
        v8::MaybeLocal<v8::Object> maybeInstance = func->NewInstance(isolate->GetCurrentContext());
        if (maybeInstance.IsEmpty())
        {
            s_Attributes_InNewFromCpp = false;
            return v8::Local<v8::Object>();
        }
        v8::Local<v8::Object> instance = maybeInstance.ToLocalChecked();
        v8::Persistent<v8::Object> obj(isolate, instance);
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(instance);
        {
            [[maybe_unused]] v8::Local<v8::Object> obj = instance;
            cppObj->mAttributesScriptObj.Reset(isolate, obj);
        }
        DEBUG_ASSERT(objWrapper->cppPtr_ == 0, "NewFromCpp() already have C++ object!");
        if (objWrapper->cppPtr_) delete objWrapper->cppPtr_;
        objWrapper->cppPtr_ = cppObj;
        s_Attributes_InNewFromCpp = false;
        return scope.Escape(instance);
    }

    v8::Persistent<v8::FunctionTemplate> AttributesWrap::constructorTpl_;

    void AttributesWrap::Init(v8::Isolate* isolate, v8::Local<v8::Object> target)
    {

        static bool initialized = false;
        if (initialized)
        {
            return;
        }
        initialized = true;
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate, New);
        t->InstanceTemplate()->SetInternalFieldCount(1);
        v8::Local<v8::String> name_str = v8::String::NewFromUtf8(isolate, "Attributes").ToLocalChecked();
        t->SetClassName(name_str);
        constructorTpl_.Reset(isolate, t);
        v8::Local<v8::Signature> WithAppearance_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> WithAppearance_Tpl =
            v8::FunctionTemplate::New(isolate, WithAppearance, v8::Local<v8::Value>(), WithAppearance_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "withAppearance").ToLocalChecked(), WithAppearance_Tpl);

        v8::Local<v8::Signature> LineColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineColor_Tpl =
            v8::FunctionTemplate::New(isolate, LineColor, v8::Local<v8::Value>(), LineColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineColor").ToLocalChecked(), LineColor_Tpl);

        v8::Local<v8::Signature> LineThickness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineThickness_Tpl =
            v8::FunctionTemplate::New(isolate, LineThickness, v8::Local<v8::Value>(), LineThickness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineThickness").ToLocalChecked(), LineThickness_Tpl);

        v8::Local<v8::Signature> LineOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LineOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, LineOpacity, v8::Local<v8::Value>(), LineOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineOpacity").ToLocalChecked(), LineOpacity_Tpl);

        v8::Local<v8::Signature> SetLineStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetLineStyle_Tpl =
            v8::FunctionTemplate::New(isolate, SetLineStyle, v8::Local<v8::Value>(), SetLineStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lineStyle").ToLocalChecked(), SetLineStyle_Tpl);

        v8::Local<v8::Signature> FillColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillColor_Tpl =
            v8::FunctionTemplate::New(isolate, FillColor, v8::Local<v8::Value>(), FillColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillColor").ToLocalChecked(), FillColor_Tpl);

        v8::Local<v8::Signature> FillOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, FillOpacity, v8::Local<v8::Value>(), FillOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillOpacity").ToLocalChecked(), FillOpacity_Tpl);

        v8::Local<v8::Signature> FillGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillGradient_Tpl =
            v8::FunctionTemplate::New(isolate, FillGradient, v8::Local<v8::Value>(), FillGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillGradient").ToLocalChecked(), FillGradient_Tpl);

        v8::Local<v8::Signature> FillRadialGradient_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> FillRadialGradient_Tpl =
            v8::FunctionTemplate::New(isolate, FillRadialGradient, v8::Local<v8::Value>(), FillRadialGradient_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fillRadialGradient").ToLocalChecked(), FillRadialGradient_Tpl);

        v8::Local<v8::Signature> RoundedCorners_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> RoundedCorners_Tpl =
            v8::FunctionTemplate::New(isolate, RoundedCorners, v8::Local<v8::Value>(), RoundedCorners_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "roundedCorners").ToLocalChecked(), RoundedCorners_Tpl);

        v8::Local<v8::Signature> Translation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Translation_Tpl =
            v8::FunctionTemplate::New(isolate, Translation, v8::Local<v8::Value>(), Translation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "translation").ToLocalChecked(), Translation_Tpl);

        v8::Local<v8::Signature> Rotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Rotation_Tpl =
            v8::FunctionTemplate::New(isolate, Rotation, v8::Local<v8::Value>(), Rotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "rotation").ToLocalChecked(), Rotation_Tpl);

        v8::Local<v8::Signature> Scale_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Scale_Tpl =
            v8::FunctionTemplate::New(isolate, Scale, v8::Local<v8::Value>(), Scale_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "scale").ToLocalChecked(), Scale_Tpl);

        v8::Local<v8::Signature> Skew_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Skew_Tpl =
            v8::FunctionTemplate::New(isolate, Skew, v8::Local<v8::Value>(), Skew_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "skew").ToLocalChecked(), Skew_Tpl);

        v8::Local<v8::Signature> Transform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Transform_Tpl =
            v8::FunctionTemplate::New(isolate, Transform, v8::Local<v8::Value>(), Transform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "transform").ToLocalChecked(), Transform_Tpl);

        v8::Local<v8::Signature> SetTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetTransform_Tpl =
            v8::FunctionTemplate::New(isolate, SetTransform, v8::Local<v8::Value>(), SetTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "setTransform").ToLocalChecked(), SetTransform_Tpl);

        v8::Local<v8::Signature> SetBlendMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetBlendMode_Tpl =
            v8::FunctionTemplate::New(isolate, SetBlendMode, v8::Local<v8::Value>(), SetBlendMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "blendMode").ToLocalChecked(), SetBlendMode_Tpl);

        v8::Local<v8::Signature> TextSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TextSize_Tpl =
            v8::FunctionTemplate::New(isolate, TextSize, v8::Local<v8::Value>(), TextSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "textSize").ToLocalChecked(), TextSize_Tpl);

        v8::Local<v8::Signature> TextStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> TextStyle_Tpl =
            v8::FunctionTemplate::New(isolate, TextStyle, v8::Local<v8::Value>(), TextStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "textStyle").ToLocalChecked(), TextStyle_Tpl);

#ifndef PDG_NO_GUI

        v8::Local<v8::Signature> SetFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFont_Tpl =
            v8::FunctionTemplate::New(isolate, SetFont, v8::Local<v8::Value>(), SetFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "font").ToLocalChecked(), SetFont_Tpl);
#endif

        v8::Local<v8::Signature> Frame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Frame_Tpl =
            v8::FunctionTemplate::New(isolate, Frame, v8::Local<v8::Value>(), Frame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "frame").ToLocalChecked(), Frame_Tpl);

        v8::Local<v8::Signature> SetFitType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SetFitType_Tpl =
            v8::FunctionTemplate::New(isolate, SetFitType, v8::Local<v8::Value>(), SetFitType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "fitType").ToLocalChecked(), SetFitType_Tpl);

        v8::Local<v8::Signature> ClipOverflow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> ClipOverflow_Tpl =
            v8::FunctionTemplate::New(isolate, ClipOverflow, v8::Local<v8::Value>(), ClipOverflow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "clipOverflow").ToLocalChecked(), ClipOverflow_Tpl);

        v8::Local<v8::Signature> Subsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Subsection_Tpl =
            v8::FunctionTemplate::New(isolate, Subsection, v8::Local<v8::Value>(), Subsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "subsection").ToLocalChecked(), Subsection_Tpl);

        v8::Local<v8::Signature> SphereRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> SphereRotation_Tpl =
            v8::FunctionTemplate::New(isolate, SphereRotation, v8::Local<v8::Value>(), SphereRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "sphereRotation").ToLocalChecked(), SphereRotation_Tpl);

        v8::Local<v8::Signature> PolarOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> PolarOffset_Tpl =
            v8::FunctionTemplate::New(isolate, PolarOffset, v8::Local<v8::Value>(), PolarOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "polarOffset").ToLocalChecked(), PolarOffset_Tpl);

        v8::Local<v8::Signature> LightOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> LightOffset_Tpl =
            v8::FunctionTemplate::New(isolate, LightOffset, v8::Local<v8::Value>(), LightOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "lightOffset").ToLocalChecked(), LightOffset_Tpl);

        v8::Local<v8::Signature> AmbientLight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> AmbientLight_Tpl =
            v8::FunctionTemplate::New(isolate, AmbientLight, v8::Local<v8::Value>(), AmbientLight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "ambientLight").ToLocalChecked(), AmbientLight_Tpl);

        v8::Local<v8::Signature> Texture_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> Texture_Tpl =
            v8::FunctionTemplate::New(isolate, Texture, v8::Local<v8::Value>(), Texture_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "texture").ToLocalChecked(), Texture_Tpl);

        v8::Local<v8::Signature> GetLineColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineColor, v8::Local<v8::Value>(), GetLineColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineColor").ToLocalChecked(), GetLineColor_Tpl);

        v8::Local<v8::Signature> GetLineThickness_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineThickness_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineThickness, v8::Local<v8::Value>(), GetLineThickness_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineThickness").ToLocalChecked(), GetLineThickness_Tpl);

        v8::Local<v8::Signature> GetLineOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineOpacity, v8::Local<v8::Value>(), GetLineOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineOpacity").ToLocalChecked(), GetLineOpacity_Tpl);

        v8::Local<v8::Signature> GetLineStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLineStyle_Tpl =
            v8::FunctionTemplate::New(isolate, GetLineStyle, v8::Local<v8::Value>(), GetLineStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLineStyle").ToLocalChecked(), GetLineStyle_Tpl);

        v8::Local<v8::Signature> GetFillColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFillColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetFillColor, v8::Local<v8::Value>(), GetFillColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFillColor").ToLocalChecked(), GetFillColor_Tpl);

        v8::Local<v8::Signature> GetFillOpacity_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFillOpacity_Tpl =
            v8::FunctionTemplate::New(isolate, GetFillOpacity, v8::Local<v8::Value>(), GetFillOpacity_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFillOpacity").ToLocalChecked(), GetFillOpacity_Tpl);

        v8::Local<v8::Signature> GetRoundedCornerRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRoundedCornerRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetRoundedCornerRadius, v8::Local<v8::Value>(), GetRoundedCornerRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRoundedCornerRadius").ToLocalChecked(), GetRoundedCornerRadius_Tpl);

        v8::Local<v8::Signature> GetGradientType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientType_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientType, v8::Local<v8::Value>(), GetGradientType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientType").ToLocalChecked(), GetGradientType_Tpl);

        v8::Local<v8::Signature> GetGradientStart_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientStart_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientStart, v8::Local<v8::Value>(), GetGradientStart_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientStart").ToLocalChecked(), GetGradientStart_Tpl);

        v8::Local<v8::Signature> GetGradientEnd_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientEnd_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientEnd, v8::Local<v8::Value>(), GetGradientEnd_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientEnd").ToLocalChecked(), GetGradientEnd_Tpl);

        v8::Local<v8::Signature> GetGradientStartColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientStartColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientStartColor, v8::Local<v8::Value>(), GetGradientStartColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientStartColor").ToLocalChecked(), GetGradientStartColor_Tpl);

        v8::Local<v8::Signature> GetGradientEndColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetGradientEndColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetGradientEndColor, v8::Local<v8::Value>(), GetGradientEndColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getGradientEndColor").ToLocalChecked(), GetGradientEndColor_Tpl);

        v8::Local<v8::Signature> GetRadialGradientCenter_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientCenter_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientCenter, v8::Local<v8::Value>(), GetRadialGradientCenter_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientCenter").ToLocalChecked(), GetRadialGradientCenter_Tpl);

        v8::Local<v8::Signature> GetRadialGradientRadius_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientRadius_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientRadius, v8::Local<v8::Value>(), GetRadialGradientRadius_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientRadius").ToLocalChecked(), GetRadialGradientRadius_Tpl);

        v8::Local<v8::Signature> GetRadialGradientCenterColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientCenterColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientCenterColor, v8::Local<v8::Value>(), GetRadialGradientCenterColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientCenterColor").ToLocalChecked(), GetRadialGradientCenterColor_Tpl);

        v8::Local<v8::Signature> GetRadialGradientEndColor_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetRadialGradientEndColor_Tpl =
            v8::FunctionTemplate::New(isolate, GetRadialGradientEndColor, v8::Local<v8::Value>(), GetRadialGradientEndColor_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getRadialGradientEndColor").ToLocalChecked(), GetRadialGradientEndColor_Tpl);

        v8::Local<v8::Signature> GetTransform_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTransform_Tpl =
            v8::FunctionTemplate::New(isolate, GetTransform, v8::Local<v8::Value>(), GetTransform_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTransform").ToLocalChecked(), GetTransform_Tpl);

        v8::Local<v8::Signature> GetBlendMode_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetBlendMode_Tpl =
            v8::FunctionTemplate::New(isolate, GetBlendMode, v8::Local<v8::Value>(), GetBlendMode_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getBlendMode").ToLocalChecked(), GetBlendMode_Tpl);

        v8::Local<v8::Signature> GetTextSize_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTextSize_Tpl =
            v8::FunctionTemplate::New(isolate, GetTextSize, v8::Local<v8::Value>(), GetTextSize_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTextSize").ToLocalChecked(), GetTextSize_Tpl);

        v8::Local<v8::Signature> GetTextStyle_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTextStyle_Tpl =
            v8::FunctionTemplate::New(isolate, GetTextStyle, v8::Local<v8::Value>(), GetTextStyle_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTextStyle").ToLocalChecked(), GetTextStyle_Tpl);

#ifndef PDG_NO_GUI

        v8::Local<v8::Signature> GetFont_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFont_Tpl =
            v8::FunctionTemplate::New(isolate, GetFont, v8::Local<v8::Value>(), GetFont_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFont").ToLocalChecked(), GetFont_Tpl);
#endif

        v8::Local<v8::Signature> GetFrame_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFrame_Tpl =
            v8::FunctionTemplate::New(isolate, GetFrame, v8::Local<v8::Value>(), GetFrame_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFrame").ToLocalChecked(), GetFrame_Tpl);

        v8::Local<v8::Signature> GetFitType_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetFitType_Tpl =
            v8::FunctionTemplate::New(isolate, GetFitType, v8::Local<v8::Value>(), GetFitType_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getFitType").ToLocalChecked(), GetFitType_Tpl);

        v8::Local<v8::Signature> GetClipOverflow_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetClipOverflow_Tpl =
            v8::FunctionTemplate::New(isolate, GetClipOverflow, v8::Local<v8::Value>(), GetClipOverflow_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getClipOverflow").ToLocalChecked(), GetClipOverflow_Tpl);

        v8::Local<v8::Signature> GetSubsection_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSubsection_Tpl =
            v8::FunctionTemplate::New(isolate, GetSubsection, v8::Local<v8::Value>(), GetSubsection_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSubsection").ToLocalChecked(), GetSubsection_Tpl);

        v8::Local<v8::Signature> GetSphereRotation_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetSphereRotation_Tpl =
            v8::FunctionTemplate::New(isolate, GetSphereRotation, v8::Local<v8::Value>(), GetSphereRotation_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getSphereRotation").ToLocalChecked(), GetSphereRotation_Tpl);

        v8::Local<v8::Signature> GetPolarOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetPolarOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetPolarOffset, v8::Local<v8::Value>(), GetPolarOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getPolarOffset").ToLocalChecked(), GetPolarOffset_Tpl);

        v8::Local<v8::Signature> GetLightOffset_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetLightOffset_Tpl =
            v8::FunctionTemplate::New(isolate, GetLightOffset, v8::Local<v8::Value>(), GetLightOffset_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getLightOffset").ToLocalChecked(), GetLightOffset_Tpl);

        v8::Local<v8::Signature> GetAmbientLight_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetAmbientLight_Tpl =
            v8::FunctionTemplate::New(isolate, GetAmbientLight, v8::Local<v8::Value>(), GetAmbientLight_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getAmbientLight").ToLocalChecked(), GetAmbientLight_Tpl);

        v8::Local<v8::Signature> GetTexture_Sig = v8::Signature::New(isolate, t);
        v8::Local<v8::FunctionTemplate> GetTexture_Tpl =
            v8::FunctionTemplate::New(isolate, GetTexture, v8::Local<v8::Value>(), GetTexture_Sig);
        t->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, "getTexture").ToLocalChecked(), GetTexture_Tpl);
        v8::Local<v8::Function> func = t->GetFunction(isolate->GetCurrentContext()).ToLocalChecked();
        target->Set(isolate->GetCurrentContext(), name_str, func).ToChecked();
    }
    void CleanupAttributesScriptObject(v8::UniquePersistent<v8::Object> &obj) { }

    AttributesWrap::AttributesWrap(const v8::FunctionCallbackInfo<v8::Value>& args) : cppPtr_(NULL)
    {
        {
            v8::TryCatch caught(args.GetIsolate());
            cppPtr_ = New_Attributes(args);
            if (caught.HasCaught()) { caught.ReThrow(); return; }
        }
        if (!cppPtr_ && !s_Attributes_InNewFromCpp)
        {
            {
                [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
                isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8Literal(isolate, "Failed to create " "Attributes" " instance")));
            };
        }
    }

    AttributesWrap::~AttributesWrap()
    {
        if (cppPtr_)
        {
            delete cppPtr_;
            cppPtr_ = NULL;
        }
    }

    Attributes* New_Attributes(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        if (s_Attributes_InNewFromCpp) return nullptr;
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        ;
        return new Attributes();
    }

    void AttributesWrap::WithAppearance(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() < 1)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 1, true);
            return;
        };

        Attributes* overrides = ExtractAttributes(args[1 -1]);
        if (!overrides)
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
        if (args.Length() >= 2 && !args[2 -1]->IsBoolean())
        {
            v8_ThrowArgTypeException(isolate, 2, "a boolean (""textOnly"")");
            return;
        }
        bool textOnly = (args.Length()<2) ? false : args[2 -1]->BooleanValue(isolate);;
        Attributes* result = new Attributes(self->withAppearance(*overrides, textOnly));
        if (!result) { args.GetReturnValue().SetNull(); return; };
        if (result->mAttributesScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( AttributesWrap::NewFromCpp(isolate, result) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, result->mAttributesScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    void AttributesWrap::GetLineColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getLineColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetLineThickness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float thickness = self->getLineThickness();
        { args.GetReturnValue().Set( v8::Number::New(isolate, thickness) ); return; };
    }

    void AttributesWrap::GetLineOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getLineOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void AttributesWrap::GetLineStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        LineStyle style = self->getLineStyle();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, style) ); return; };
    }

    void AttributesWrap::GetFillColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getFillColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetFillOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float opacity = self->getFillOpacity();
        { args.GetReturnValue().Set( v8::Number::New(isolate, opacity) ); return; };
    }

    void AttributesWrap::GetRoundedCornerRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float radius = self->getRoundedCornerRadius();
        { args.GetReturnValue().Set( v8::Number::New(isolate, radius) ); return; };
    }

    void AttributesWrap::GetGradientType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        GradientType type = self->getGradientType();
        { args.GetReturnValue().Set( v8::Integer::NewFromUnsigned(isolate, type) ); return; };
    }

    void AttributesWrap::GetGradientStart(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point start = const_cast<Point&>(self->getGradientStart());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, start) ); return; };
    }

    void AttributesWrap::GetGradientEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point end = const_cast<Point&>(self->getGradientEnd());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, end) ); return; };
    }

    void AttributesWrap::GetGradientStartColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getGradientStartColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetGradientEndColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getGradientEndColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetRadialGradientCenter(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Point center = const_cast<Point&>(self->getRadialGradientCenter());
        { args.GetReturnValue().Set( v8_MakeJavascriptPoint(isolate, center) ); return; };
    }

    void AttributesWrap::GetRadialGradientRadius(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float radius = self->getRadialGradientRadius();
        { args.GetReturnValue().Set( v8::Number::New(isolate, radius) ); return; };
    }

    void AttributesWrap::GetRadialGradientCenterColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getRadialGradientCenterColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetRadialGradientEndColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getRadialGradientEndColor());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        const glm::mat3& matrix = self->getTransform();
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                JSObjectSetPropertyAtIndex(ctx, result, (unsigned)index,
                    JSValueMakeNumber(ctx, matrix[i][j]), exception);
            }
        }
        { args.GetReturnValue().Set( result ); return; };
#else
        v8::Local<v8::Array> result = v8::Array::New(isolate, 9);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int index = i * 3 + j;
                (void)result->Set(context, index, v8::Number::New(isolate, matrix[i][j]));
            }
        }
        args.GetReturnValue().Set(result);
#endif
    }

    void AttributesWrap::GetBlendMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        BlendMode blendMode = self->getBlendMode();
        { args.GetReturnValue().Set( v8::Number::New(isolate, static_cast<int>(blendMode)) ); return; };
    }

    void AttributesWrap::LineColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->lineColor(color);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::LineThickness(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""thickness"")");
                return;
            }
            double thickness = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineThickness(thickness);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::LineOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
                return;
            }
            double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineOpacity(opacity);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::SetLineStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""lineStyle"")");
                return;
            }
            double lineStyle = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->lineStyle(static_cast<LineStyle>(lineStyle));
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::FillColor(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->fillColor(color);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::FillOpacity(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""opacity"")");
                return;
            }
            double opacity = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->fillOpacity(opacity);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::FillGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            };
            pdg::Point start;
            auto start_isPoint = v8_ValueIsPoint(isolate, args[1 -1], start);
            if (!start_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*start_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            pdg::Color startColor;
            auto startColor_isColor = v8_ValueIsColor(isolate, args[2 -1], startColor);
            if (!startColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*startColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
                return;
            };
            pdg::Point end;
            auto end_isPoint = v8_ValueIsPoint(isolate, args[3 -1], end);
            if (!end_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*end_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                return;
            };
            pdg::Color endColor;
            auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
            if (!endColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*endColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
                return;
            };
            self->fillGradient(start, startColor, end, endColor);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::FillRadialGradient(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 4)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 4);
                return;
            };
            pdg::Point center;
            auto center_isPoint = v8_ValueIsPoint(isolate, args[1 -1], center);
            if (!center_isPoint.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*center_isPoint)
            {
                v8_ThrowArgTypeException(isolate, 1, "Point", *args[1 -1]);
                return;
            };
            pdg::Color centerColor;
            auto centerColor_isColor = v8_ValueIsColor(isolate, args[2 -1], centerColor);
            if (!centerColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*centerColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 2, "Color", *args[2 -1]);
                return;
            };
            if (!args[3 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 3, "a number (""radius"")");
                return;
            }
            double radius = args[3 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            pdg::Color endColor;
            auto endColor_isColor = v8_ValueIsColor(isolate, args[4 -1], endColor);
            if (!endColor_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*endColor_isColor)
            {
                v8_ThrowArgTypeException(isolate, 4, "Color", *args[4 -1]);
                return;
            };
            self->fillRadialGradient(center, centerColor, radius, endColor);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::RoundedCorners(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radius"")");
                return;
            }
            double radius = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->roundedCorners(radius);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Translation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
            auto offset_isOffset = v8_ValueIsOffset(isolate, args[1 -1], offset);
            if (!offset_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*offset_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            self->translation(offset);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Rotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""radians"")");
                return;
            }
            double radians = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            pdg::Point center;
            if (args.Length() < 2)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[2 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 2, "Point", *args[2 -1]);
                    return;
                }
            };
            self->rotation(radians, center);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Scale(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""xFactor"")");
                return;
            }
            double xFactor = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (args.Length() >= 2 && !args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""yFactor"")");
                return;
            }
            double yFactor = (args.Length()<2) ? xFactor : args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();;
            pdg::Point center;
            if (args.Length() < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[3 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            if (args.Length() > 1 && !args[1]->IsUndefined())
            {
                self->scale(xFactor, yFactor, center);
            }
            else
            {
                self->scale(xFactor, center);
            }
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Skew(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() < 2)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 2, true);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""xSkew"")");
                return;
            }
            double xSkew = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            if (!args[2 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 2, "a number (""ySkew"")");
                return;
            }
            double ySkew = args[2 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            pdg::Point center;
            if (args.Length() < 3)
            {
                center = Point(0, 0);
            }
            else
            {
                auto center_isPoint = v8_ValueIsPoint(isolate, args[3 -1], center);
                if (!center_isPoint.has_value())
                {
                    {
                        args.GetReturnValue().SetNull(); return;
                    };
                }
                if (!*center_isPoint)
                {
                    v8_ThrowArgTypeException(isolate, 3, "Point", *args[3 -1]);
                    return;
                }
            };
            self->skew(xSkew, ySkew, center);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Transform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, args[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, args[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception)
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!args[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(args[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element))
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->transform(matrix);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::SetTransform(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
#ifdef PDG_USING_JAVASCRIPT_CORE
            if (!JSValueIsArray(ctx, args[0]))
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            JSObjectRef matrixArray = JSValueToObject(ctx, args[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception)
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (matrixLength != 9)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
            }
            glm::mat3 matrix;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
                    if (*exception)
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!JSValueIsNumber(ctx, element))
                    {
                        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", args[0]);
                    }
                    matrix[i][j] = JSValueToNumber(ctx, element, exception);
                }
            }
#else
            if (!args[0]->IsArray())
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(args[0]);
            if (matrixArray->Length() != 9)
            {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            glm::mat3 matrix;
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    v8::Local<v8::Value> element;
                    if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element))
                    {
                        {
                            args.GetReturnValue().SetNull(); return;
                        };
                    }
                    if (!element->IsNumber())
                    {
                        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                        return;
                    }
                    matrix[i][j] = element.As<v8::Number>()->Value();
                }
            }
#endif
            self->setTransform(matrix);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::SetBlendMode(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""blendMode"")");
                return;
            }
            double blendMode = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->blendMode(static_cast<BlendMode>(blendMode));
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::TextSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""size"")");
                return;
            }
            double size = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->textSize(size);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::TextStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""style"")");
                return;
            }
            double style = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->textStyle(static_cast<uint32>(style));
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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
#ifndef PDG_NO_GUI

    void AttributesWrap::SetFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
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
            self->font(font);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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
#endif

    void AttributesWrap::Frame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""frame"")");
                return;
            }
            double frame = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->frame(frame);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::SetFitType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""fit"")");
                return;
            }
            double fit = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->fitType(static_cast<FitType>(fit));
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::ClipOverflow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsBoolean())
            {
                v8_ThrowArgTypeException(isolate, 1, "a boolean (""clip"")");
                return;
            }
            bool clip = args[1 -1]->BooleanValue(isolate);
            self->clipOverflow(clip);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Subsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Rect section;
            auto section_isRect = v8_ValueIsRect(isolate, args[1 -1], section);
            if (!section_isRect.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*section_isRect)
            {
                v8_ThrowArgTypeException(isolate, 1, "Rect", *args[1 -1]);
                return;
            };
            self->subsection(section);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::SphereRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            if (!args[1 -1]->IsNumber())
            {
                v8_ThrowArgTypeException(isolate, 1, "a number (""rotation"")");
                return;
            }
            double rotation = args[1 -1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
            self->sphereRotation(rotation);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::PolarOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
            auto offset_isOffset = v8_ValueIsOffset(isolate, args[1 -1], offset);
            if (!offset_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*offset_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            self->polarOffset(offset);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::LightOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Offset offset;
            auto offset_isOffset = v8_ValueIsOffset(isolate, args[1 -1], offset);
            if (!offset_isOffset.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*offset_isOffset)
            {
                v8_ThrowArgTypeException(isolate, 1, "Offset", *args[1 -1]);
                return;
            };
            self->lightOffset(offset);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::AmbientLight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            pdg::Color color;
            auto color_isColor = v8_ValueIsColor(isolate, args[1 -1], color);
            if (!color_isColor.has_value())
            {
                {
                    args.GetReturnValue().SetNull(); return;
                };
            }
            if (!*color_isColor)
            {
                v8_ThrowArgTypeException(isolate, 1, "Color", *args[1 -1]);
                return;
            };
            self->ambientLight(color);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::Texture(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        try
        {
            ;
            if (args.Length() != 1)
            {
                v8_ThrowArgCountException(isolate, args.Length(), 1);
                return;
            };
            REQUIRE_CPP_OBJECT_ARG(1, texture, Image);
            self->texture(texture);
            { args.GetReturnValue().Set( args.This() ); return; };
        }
        catch (const std::exception& error)
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

    void AttributesWrap::GetTextSize(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float size = self->getTextSize();
        { args.GetReturnValue().Set( v8::Number::New(isolate, size) ); return; };
    }

    void AttributesWrap::GetTextStyle(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        uint32 style = self->getTextStyle();
        { args.GetReturnValue().Set( v8::Number::New(isolate, style) ); return; };
    }
#ifndef PDG_NO_GUI

    void AttributesWrap::GetFont(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Font* font = self->getFont();
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
#endif

    void AttributesWrap::GetFrame(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        int frame = self->getFrame();
        { args.GetReturnValue().Set( v8::Number::New(isolate, frame) ); return; };
    }

    void AttributesWrap::GetFitType(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        FitType fit = self->getFitType();
        { args.GetReturnValue().Set( v8::Number::New(isolate, static_cast<int>(fit)) ); return; };
    }

    void AttributesWrap::GetClipOverflow(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        bool clip = self->getClipOverflow();
        { args.GetReturnValue().Set( v8::Boolean::New(isolate, clip) ); return; };
    }

    void AttributesWrap::GetSubsection(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Rect section = self->getSubsection();
        { args.GetReturnValue().Set( v8_MakeJavascriptRect(isolate, section) ); return; };
    }

    void AttributesWrap::GetSphereRotation(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        float rotation = self->getSphereRotation();
        { args.GetReturnValue().Set( v8::Number::New(isolate, rotation) ); return; };
    }

    void AttributesWrap::GetPolarOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Offset offset = const_cast<Offset&>(self->getPolarOffset());
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void AttributesWrap::GetLightOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Offset offset = const_cast<Offset&>(self->getLightOffset());
        { args.GetReturnValue().Set( v8_MakeJavascriptOffset(isolate, offset) ); return; };
    }

    void AttributesWrap::GetAmbientLight(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Color color = const_cast<Color&>(self->getAmbientLight());
        { args.GetReturnValue().Set( v8_MakeJavascriptColor(isolate, color) ); return; };
    }

    void AttributesWrap::GetTexture(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        [[maybe_unused]] v8::Isolate* isolate = args.GetIsolate();
        AttributesWrap* objWrapper = jswrap::ObjectWrap::Unwrap<AttributesWrap>(args.This());
        Attributes* self = dynamic_cast<Attributes*>(objWrapper->cppPtr_);

        ;
        if (args.Length() != 0)
        {
            v8_ThrowArgCountException(isolate, args.Length(), 0);
            return;
        };
        Image* texture = self->getTexture();
        if (!texture) { args.GetReturnValue().SetNull(); return; };
        if (texture->mImageScriptObj.IsEmpty())
        {
            { args.GetReturnValue().Set( ImageWrap::NewFromCpp(isolate, texture) ); return; };
        }
        else
        {
            v8::Local<v8::Object> obj__ = v8::Local<v8::Object>::New(isolate, texture->mImageScriptObj );
            { args.GetReturnValue().Set( obj__ ); return; };
        };
    }

    Attributes* ExtractAttributes(v8::Local<v8::Value> value)
    {
#ifdef PDG_USING_JAVASCRIPT_CORE
        JSContextRef ctx = gMainContext;
        if (JSValueIsObjectOfClass(ctx, value, AnimatedAttributesBase_class()))
            return static_cast<Attributes*>(AnimatedAttributesBase_getCppObject(JSValueToObject(ctx,value,nullptr)));
        if (JSValueIsObjectOfClass(ctx, value, Attributes_class()))
            return Attributes_getCppObject(JSValueToObject(ctx,value,nullptr));
#else
        auto* wrapper = v8script::safe_unwrap_object_wrap_or_prototype(v8::Isolate::GetCurrent(),value);
        if (auto* animated = dynamic_cast<AnimatedAttributesBaseWrap*>(wrapper))
            return static_cast<Attributes*>(animated->getCppObject());
        if (auto* attributes = dynamic_cast<AttributesWrap*>(wrapper))
            return attributes->getCppObject();
#endif
        return nullptr;
    }

}
