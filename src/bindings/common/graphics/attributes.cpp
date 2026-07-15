// -----------------------------------------------
// attributes.cpp
//
// Implementation file for Attributes bindings
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {

// ========================================================================================
//MARK: Attributes
// ========================================================================================

WRAPPER_INITIALIZER_IMPL_CUSTOM(Attributes,
    OBJECT_SAVE(cppObj->mAttributesScriptObj, obj) )
    EXPORT_CLASS_SYMBOLS("Attributes", Attributes, , ,
        // method section
        HAS_METHOD(Attributes, "lineColor", LineColor)
        HAS_METHOD(Attributes, "lineThickness", LineThickness)
        HAS_METHOD(Attributes, "lineOpacity", LineOpacity)
        HAS_METHOD(Attributes, "lineStyle", SetLineStyle)
        HAS_METHOD(Attributes, "fillColor", FillColor)
        HAS_METHOD(Attributes, "fillOpacity", FillOpacity)
        HAS_METHOD(Attributes, "fillGradient", FillGradient)
        HAS_METHOD(Attributes, "fillRadialGradient", FillRadialGradient)
        HAS_METHOD(Attributes, "roundedCorners", RoundedCorners)
        HAS_METHOD(Attributes, "translation", Translation)
        HAS_METHOD(Attributes, "rotation", Rotation)
        HAS_METHOD(Attributes, "scale", Scale)
        HAS_METHOD(Attributes, "skew", Skew)
        HAS_METHOD(Attributes, "transform", Transform)
        HAS_METHOD(Attributes, "blendMode", SetBlendMode)
        // Text attributes
        HAS_METHOD(Attributes, "textSize", TextSize)
        HAS_METHOD(Attributes, "textStyle", TextStyle)
%#ifndef PDG_NO_GUI CR
        HAS_METHOD(Attributes, "font", SetFont)
%#endif CR
        // Image attributes
        HAS_METHOD(Attributes, "frame", Frame)
        HAS_METHOD(Attributes, "fitType", SetFitType)
        HAS_METHOD(Attributes, "clipOverflow", ClipOverflow)
        HAS_METHOD(Attributes, "subsection", Subsection)
        // Sphere attributes
        HAS_METHOD(Attributes, "sphereRotation", SphereRotation)
        HAS_METHOD(Attributes, "polarOffset", PolarOffset)
        HAS_METHOD(Attributes, "lightOffset", LightOffset)
        HAS_METHOD(Attributes, "ambientLight", AmbientLight)
        HAS_METHOD(Attributes, "texture", Texture)
    // getter methods
        HAS_METHOD(Attributes, "getLineColor", GetLineColor)
        HAS_METHOD(Attributes, "getLineThickness", GetLineThickness)
        HAS_METHOD(Attributes, "getLineOpacity", GetLineOpacity)
        HAS_METHOD(Attributes, "getLineStyle", GetLineStyle)
        HAS_METHOD(Attributes, "getFillColor", GetFillColor)
        HAS_METHOD(Attributes, "getFillOpacity", GetFillOpacity)
        HAS_METHOD(Attributes, "getRoundedCornerRadius", GetRoundedCornerRadius)
        HAS_METHOD(Attributes, "getGradientType", GetGradientType)
        HAS_METHOD(Attributes, "getGradientStart", GetGradientStart)
        HAS_METHOD(Attributes, "getGradientEnd", GetGradientEnd)
        HAS_METHOD(Attributes, "getGradientStartColor", GetGradientStartColor)
        HAS_METHOD(Attributes, "getGradientEndColor", GetGradientEndColor)
        HAS_METHOD(Attributes, "getRadialGradientCenter", GetRadialGradientCenter)
        HAS_METHOD(Attributes, "getRadialGradientRadius", GetRadialGradientRadius)
        HAS_METHOD(Attributes, "getRadialGradientCenterColor", GetRadialGradientCenterColor)
        HAS_METHOD(Attributes, "getRadialGradientEndColor", GetRadialGradientEndColor)
        HAS_METHOD(Attributes, "getTransform", GetTransform)
        HAS_METHOD(Attributes, "getBlendMode", GetBlendMode)
        // New getter methods
        HAS_METHOD(Attributes, "getTextSize", GetTextSize)
        HAS_METHOD(Attributes, "getTextStyle", GetTextStyle)
%#ifndef PDG_NO_GUI CR
        HAS_METHOD(Attributes, "getFont", GetFont)
%#endif CR
        HAS_METHOD(Attributes, "getFrame", GetFrame)
        HAS_METHOD(Attributes, "getFitType", GetFitType)
        HAS_METHOD(Attributes, "getClipOverflow", GetClipOverflow)
        HAS_METHOD(Attributes, "getSubsection", GetSubsection)
        HAS_METHOD(Attributes, "getSphereRotation", GetSphereRotation)
        HAS_METHOD(Attributes, "getPolarOffset", GetPolarOffset)
        HAS_METHOD(Attributes, "getLightOffset", GetLightOffset)
        HAS_METHOD(Attributes, "getAmbientLight", GetAmbientLight)
        HAS_METHOD(Attributes, "getTexture", GetTexture)
    );
    END

CLEANUP_IMPL(Attributes)

CPP_MANAGED_CONSTRUCTOR_IMPL(Attributes)
	SETUP_NON_SCRIPT_CALL;
    return new Attributes();
	END

// ========================================================================================
// Getter method implementations
// ========================================================================================

METHOD_IMPL(Attributes, GetLineColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getLineColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetLineThickness)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float thickness = self->getLineThickness();
    RETURN_NUMBER(thickness);
    END

METHOD_IMPL(Attributes, GetLineOpacity)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float opacity = self->getLineOpacity();
    RETURN_NUMBER(opacity);
    END

METHOD_IMPL(Attributes, GetLineStyle)
    METHOD_SIGNATURE("", [number uint], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    LineStyle style = self->getLineStyle();
    RETURN_UINT32(style);
    END

METHOD_IMPL(Attributes, GetFillColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getFillColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetFillOpacity)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float opacity = self->getFillOpacity();
    RETURN_NUMBER(opacity);
    END

METHOD_IMPL(Attributes, GetRoundedCornerRadius)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float radius = self->getRoundedCornerRadius();
    RETURN_NUMBER(radius);
    END

METHOD_IMPL(Attributes, GetGradientType)
    METHOD_SIGNATURE("", [number int], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    GradientType type = self->getGradientType();
    RETURN_UINT32(type);
    END

METHOD_IMPL(Attributes, GetGradientStart)
    METHOD_SIGNATURE("", [object Point], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Point start = const_cast<Point&>(self->getGradientStart());
    RETURN_POINT(start);
    END

METHOD_IMPL(Attributes, GetGradientEnd)
    METHOD_SIGNATURE("", [object Point], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Point end = const_cast<Point&>(self->getGradientEnd());
    RETURN_POINT(end);
    END

METHOD_IMPL(Attributes, GetGradientStartColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getGradientStartColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetGradientEndColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getGradientEndColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetRadialGradientCenter)
    METHOD_SIGNATURE("", [object Point], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Point center = const_cast<Point&>(self->getRadialGradientCenter());
    RETURN_POINT(center);
    END

METHOD_IMPL(Attributes, GetRadialGradientRadius)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float radius = self->getRadialGradientRadius();
    RETURN_NUMBER(radius);
    END

METHOD_IMPL(Attributes, GetRadialGradientCenterColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getRadialGradientCenterColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetRadialGradientEndColor)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getRadialGradientEndColor());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetTransform)
    METHOD_SIGNATURE("", [array number], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    
    // Get the transform matrix from the Attributes object
    const glm::mat3& matrix = self->getTransform();
    
    // Convert glm::mat3 to JavaScript array of 9 numbers
    v8::Local<v8::Array> result = v8::Array::New(isolate, 9);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            result->Set(context, index, v8::Number::New(isolate, matrix[i][j]));
        }
    }
    
    args.GetReturnValue().Set(result);
    END

METHOD_IMPL(Attributes, GetBlendMode)
    METHOD_SIGNATURE("", [number int], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    BlendMode blendMode = self->getBlendMode();
    RETURN_NUMBER(static_cast<int>(blendMode));
    END

// ========================================================================================
//MARK: Attributes Assignment Method Implementations
// ========================================================================================

METHOD_IMPL(Attributes, LineColor)
    METHOD_SIGNATURE("", undefined, 1, ([object Color] color));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_COLOR_ARG(1, color);
    self->lineColor(color);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, LineThickness)
    METHOD_SIGNATURE("", undefined, 1, ([number float] thickness));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, thickness);
    self->lineThickness(thickness);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, LineOpacity)
    METHOD_SIGNATURE("", undefined, 1, ([number float] opacity));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, opacity);
    self->lineOpacity(opacity);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, SetLineStyle)
    METHOD_SIGNATURE("", undefined, 1, ([number int] lineStyle));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, lineStyle);
    self->lineStyle(static_cast<LineStyle>(lineStyle));
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, FillColor)
    METHOD_SIGNATURE("", undefined, 1, ([object Color] color));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_COLOR_ARG(1, color);
    self->fillColor(color);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, FillOpacity)
    METHOD_SIGNATURE("", undefined, 1, ([number float] opacity));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, opacity);
    self->fillOpacity(opacity);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, FillGradient)
    METHOD_SIGNATURE("", undefined, 4, ([object Point] start, [object Color] startColor, [object Point] end, [object Color] endColor));
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, start);
    REQUIRE_COLOR_ARG(2, startColor);
    REQUIRE_POINT_ARG(3, end);
    REQUIRE_COLOR_ARG(4, endColor);
    self->fillGradient(start, startColor, end, endColor);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, FillRadialGradient)
    METHOD_SIGNATURE("", undefined, 4, ([object Point] center, [object Color] centerColor, [number float] radius, [object Color] endColor));
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_COLOR_ARG(2, centerColor);
    REQUIRE_NUMBER_ARG(3, radius);
    REQUIRE_COLOR_ARG(4, endColor);
    self->fillRadialGradient(center, centerColor, radius, endColor);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, RoundedCorners)
    METHOD_SIGNATURE("", undefined, 1, ([number float] radius));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, radius);
    self->roundedCorners(radius);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Translation)
    METHOD_SIGNATURE("", undefined, 1, ([object Offset] offset));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OFFSET_ARG(1, offset);
    self->translation(offset);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Rotation)
    METHOD_SIGNATURE("", undefined, 2, ([number float] radians, [object Point] center = Point(0,0)));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_NUMBER_ARG(1, radians);
    OPTIONAL_POINT_ARG(2, center, Point(0, 0));
    self->rotation(radians, center);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Scale)
    METHOD_SIGNATURE("", undefined, 3, ([number float] xFactor, [number float] yFactor = xFactor, [object Point] center = Point(0,0)));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_NUMBER_ARG(1, xFactor);
    OPTIONAL_NUMBER_ARG(2, yFactor, xFactor);
    OPTIONAL_POINT_ARG(3, center, Point(0, 0));
    if (args.Length() > 1 && !ARGV[1]->IsUndefined()) {
        self->scale(xFactor, yFactor, center);
    } else {
        self->scale(xFactor, center);
    }
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Skew)
    METHOD_SIGNATURE("", undefined, 3, ([number float] xSkew, [number float] ySkew, [object Point] center = Point(0,0)));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, xSkew);
    REQUIRE_NUMBER_ARG(2, ySkew);
    OPTIONAL_POINT_ARG(3, center, Point(0, 0));
    self->skew(xSkew, ySkew, center);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Transform)
    METHOD_SIGNATURE("", undefined, 1, ([array number] matrix));
    REQUIRE_ARG_COUNT(1);
    
    // Validate that argument is an array
    if (!ARGV[0]->IsArray()) {
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
        return;
    }
    
    // Convert JavaScript array to glm::mat3
    v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(ARGV[0]);
    if (matrixArray->Length() != 9) {
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
        return;
    }
    
    // Create glm::mat3 from array elements
    // GLM matrices are column-major, so we need to map the array correctly
    glm::mat3 matrix;
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            v8::Local<v8::Value> element = matrixArray->Get(context, i * 3 + j).ToLocalChecked();
            if (!element->IsNumber()) {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            matrix[i][j] = element->NumberValue(context).ToChecked();
        }
    }
    
    self->transform(matrix);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, SetBlendMode)
    METHOD_SIGNATURE("", undefined, 1, ([number int] blendMode));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, blendMode);
    self->blendMode(static_cast<BlendMode>(blendMode));
    RETURN_THIS;
    END

// ========================================================================================
// New attribute setter method implementations
// ========================================================================================

METHOD_IMPL(Attributes, TextSize)
    METHOD_SIGNATURE("", undefined, 1, ([number float] size));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, size);
    self->textSize(size);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, TextStyle)
    METHOD_SIGNATURE("", undefined, 1, ([number int] style));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, style);
    self->textStyle(static_cast<uint32>(style));
    RETURN_THIS;
    END

%#ifndef PDG_NO_GUI
METHOD_IMPL(Attributes, SetFont)
    METHOD_SIGNATURE("", undefined, 1, ([object Font] font));
    OPTIONAL_CPP_OBJECT_ARG(1, font, Font, 0);
    self->font(font);
    RETURN_THIS;
    END
%#endif // !PDG_NO_GUI

METHOD_IMPL(Attributes, Frame)
    METHOD_SIGNATURE("", undefined, 1, ([number int] frame));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, frame);
    self->frame(frame);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, SetFitType)
    METHOD_SIGNATURE("", undefined, 1, ([number int] fit));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, fit);
    self->fitType(static_cast<FitType>(fit));
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, ClipOverflow)
    METHOD_SIGNATURE("", undefined, 1, ([boolean] clip));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_BOOL_ARG(1, clip);
    self->clipOverflow(clip);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Subsection)
    METHOD_SIGNATURE("", undefined, 1, ([object Rect] section));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_RECT_ARG(1, section);
    self->subsection(section);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, SphereRotation)
    METHOD_SIGNATURE("", undefined, 1, ([number float] rotation));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, rotation);
    self->sphereRotation(rotation);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, PolarOffset)
    METHOD_SIGNATURE("", undefined, 1, ([object Offset] offset));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OFFSET_ARG(1, offset);
    self->polarOffset(offset);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, LightOffset)
    METHOD_SIGNATURE("", undefined, 1, ([object Offset] offset));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OFFSET_ARG(1, offset);
    self->lightOffset(offset);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, AmbientLight)
    METHOD_SIGNATURE("", undefined, 1, ([object Color] color));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_COLOR_ARG(1, color);
    self->ambientLight(color);
    RETURN_THIS;
    END

METHOD_IMPL(Attributes, Texture)
    METHOD_SIGNATURE("", undefined, 1, ([object Image] texture));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, texture, Image);
    self->texture(texture);
    RETURN_THIS;
    END

// ========================================================================================
// New attribute getter method implementations
// ========================================================================================

METHOD_IMPL(Attributes, GetTextSize)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float size = self->getTextSize();
    RETURN_NUMBER(size);
    END

METHOD_IMPL(Attributes, GetTextStyle)
    METHOD_SIGNATURE("", [number int], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    uint32 style = self->getTextStyle();
    RETURN_NUMBER(style);
    END

%#ifndef PDG_NO_GUI
METHOD_IMPL(Attributes, GetFont)
    METHOD_SIGNATURE("", [object Font], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Font* font = self->getFont();
    RETURN_CPP_OBJECT(font, Font);
    END
%#endif // !PDG_NO_GUI

METHOD_IMPL(Attributes, GetFrame)
    METHOD_SIGNATURE("", [number int], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    int frame = self->getFrame();
    RETURN_NUMBER(frame);
    END

METHOD_IMPL(Attributes, GetFitType)
    METHOD_SIGNATURE("", [number int], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    FitType fit = self->getFitType();
    RETURN_NUMBER(static_cast<int>(fit));
    END

METHOD_IMPL(Attributes, GetClipOverflow)
    METHOD_SIGNATURE("", [boolean], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    bool clip = self->getClipOverflow();
    RETURN_BOOL(clip);
    END

METHOD_IMPL(Attributes, GetSubsection)
    METHOD_SIGNATURE("", [object Rect], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Rect section = self->getSubsection();
    RETURN_RECT(section);
    END

METHOD_IMPL(Attributes, GetSphereRotation)
    METHOD_SIGNATURE("", [number float], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float rotation = self->getSphereRotation();
    RETURN_NUMBER(rotation);
    END

METHOD_IMPL(Attributes, GetPolarOffset)
    METHOD_SIGNATURE("", [object Offset], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Offset offset = const_cast<Offset&>(self->getPolarOffset());
    RETURN_OFFSET(offset);
    END

METHOD_IMPL(Attributes, GetLightOffset)
    METHOD_SIGNATURE("", [object Offset], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Offset offset = const_cast<Offset&>(self->getLightOffset());
    RETURN_OFFSET(offset);
    END

METHOD_IMPL(Attributes, GetAmbientLight)
    METHOD_SIGNATURE("", [object Color], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Color color = const_cast<Color&>(self->getAmbientLight());
    RETURN_COLOR(color);
    END

METHOD_IMPL(Attributes, GetTexture)
    METHOD_SIGNATURE("", [object Image], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Image* texture = self->getTexture();
    RETURN_CPP_OBJECT(texture, Image);
    END

} // end namespace pdg
