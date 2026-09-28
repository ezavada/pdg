// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/graphics_bindings.h
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#ifndef PDG_NO_GUI
#endif

#ifndef PDG_GRAPHICS_BINDINGS_H_INCLUDED
#define PDG_GRAPHICS_BINDINGS_H_INCLUDED

#include "pdg_project.h"

#include "pdg_script_impl.h"
#include "pdg_script_interface.h"

#ifndef PDG_NO_APP_FRAMEWORK
#define PDG_NO_APP_FRAMEWORK
#endif
#include "pdg/framework.h"
#include "pdg/sys/drawing.h"
#include "pdg/sys/renderer.h"

#include <cstdlib>

namespace pdg
{

    extern Image* New_Image(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Image_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Image_class();
    extern JSObjectRef Image_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Image* Image_getCppObject(JSObjectRef obj)
    {
        return static_cast<Image*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Image_newFromCpp(JSContextRef, Image*);

    extern JSValueRef Image_GetSerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_Serialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_Deserialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetMyClassTag(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetTransparentColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_SetTransparentColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_SetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetImageBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetSubsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_SetEdgeClamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_RetainData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_RetainAlpha(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_PrepareToRasterize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetAlphaValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Image_GetPixel(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern ImageStrip* New_ImageStrip(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ImageStrip_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ImageStrip_class();
    extern JSObjectRef ImageStrip_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ImageStrip* ImageStrip_getCppObject(JSObjectRef obj)
    {
        return static_cast<ImageStrip*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef ImageStrip_newFromCpp(JSContextRef, ImageStrip*);

    extern JSValueRef ImageStrip_GetSerializedSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_Serialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_Deserialize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetMyClassTag(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetTransparentColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_SetTransparentColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_SetOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetImageBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetSubsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_SetEdgeClamping(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_RetainData(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_RetainAlpha(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_PrepareToRasterize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetAlphaValue(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetPixel(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetFrameWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_SetFrameWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetNumFrames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_SetNumFrames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ImageStrip_GetFrame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Spline* New_Spline(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Spline_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Spline_class();
    extern JSObjectRef Spline_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Spline* Spline_getCppObject(JSObjectRef obj)
    {
        return static_cast<Spline*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Spline_newFromCpp(JSContextRef, Spline*);

    extern JSValueRef Spline_GetFirstOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_GetSecondOrder(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_AddSegment(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_AddPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_GetPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_SetPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_GetPointCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_GetMaxU(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Spline_GetBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Polygon* New_Polygon(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Polygon_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Polygon_class();
    extern JSObjectRef Polygon_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Polygon* Polygon_getCppObject(JSObjectRef obj)
    {
        return static_cast<Polygon*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Polygon_newFromCpp(JSContextRef, Polygon*);

    extern JSValueRef Polygon_AddPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_AddSpline(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_InsertPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_RemovePoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_GetPointCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_GetPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_SetPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_ClearPoints(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_GetBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_CenterPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Contains(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Equals(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Empty(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Move(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveLeft(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveRight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveUp(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveDown(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveXTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveYTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Center(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Scale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_HorzScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_VertScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_ScaleAround(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Rotate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_RotateAround(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_Intersection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Polygon_UnionWith(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern ElementRef* New_ElementRef(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef ElementRef_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef ElementRef_class();
    extern JSObjectRef ElementRef_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline ElementRef* ElementRef_getCppObject(JSObjectRef obj)
    {
        return static_cast<ElementRef*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef ElementRef_newFromCpp(JSContextRef, ElementRef*);

    extern JSValueRef ElementRef_Type(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_GetControlPoints(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_GetControlPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_GetAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_SetAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_SetLiveAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_ClearLiveAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_HasLiveAttributes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_ChangeControlPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_MoveForward(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_MoveBackward(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_MoveToFront(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_MoveToBack(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef ElementRef_Remove(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Attributes* New_Attributes(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Attributes_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Attributes_class();
    extern JSObjectRef Attributes_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Attributes* Attributes_getCppObject(JSObjectRef obj)
    {
        return static_cast<Attributes*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Attributes_newFromCpp(JSContextRef, Attributes*);

    extern JSValueRef Attributes_WithAppearance(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_LineColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_LineThickness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_LineOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_SetLineStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_FillColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_FillOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_FillGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_FillRadialGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_RoundedCorners(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Translation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Rotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Scale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Skew(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Transform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_SetTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_SetBlendMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_TextSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_TextStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef Attributes_SetFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef Attributes_Frame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_SetFitType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_ClipOverflow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Subsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_SphereRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_PolarOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_LightOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_AmbientLight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_Texture(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetLineColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetLineThickness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetLineOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetLineStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetFillColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetFillOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetRoundedCornerRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetGradientType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetGradientStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetGradientEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetGradientStartColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetGradientEndColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetRadialGradientCenter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetRadialGradientRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetRadialGradientCenterColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetRadialGradientEndColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetBlendMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetTextSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetTextStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef Attributes_GetFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef Attributes_GetFrame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetFitType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetClipOverflow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetSubsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetSphereRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetPolarOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetLightOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetAmbientLight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Attributes_GetTexture(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern AnimatedAttributesBase* New_AnimatedAttributesBase(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef AnimatedAttributesBase_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef AnimatedAttributesBase_class();
    extern JSObjectRef AnimatedAttributesBase_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline AnimatedAttributesBase* AnimatedAttributesBase_getCppObject(JSObjectRef obj)
    {
        return static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef AnimatedAttributesBase_newFromCpp(JSContextRef, AnimatedAttributesBase*);

    extern JSValueRef AnimatedAttributesBase_GetBoundingBox(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRotatedBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetLocation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_MoveTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_MoveBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeMovementTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeMovementBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeCenterOffsetTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeCenterOffsetBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetSpin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetScale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeSpinTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeSpinBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeGrowingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeGrowingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeStretchingTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeStretchingBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeScaleTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeScaleBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Grow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Stretch(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ResizeBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ResizeTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_RotateBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_RotateTo(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetCenterOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetFlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetFlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_StopMovement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_StopSpinning(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_StopGrowing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_StopStretching(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_PauseSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ResumeSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_CancelSchedule(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FlipX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FlipY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_AndThen(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_IsFlippedX(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_IsFlippedY(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_IsSchedulePaused(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_HasScheduledAnimations(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Wait(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_AddAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_RemoveAnimationHelper(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ClearAnimationHelpers(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_WithAppearance(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_LineColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_LineThickness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_LineOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetLineStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FillColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FillOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FillGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_FillRadialGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_RoundedCorners(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Translation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Rotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Scale(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Skew(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Transform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetBlendMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_TextSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_TextStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef AnimatedAttributesBase_SetFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef AnimatedAttributesBase_Frame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetFitType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ClipOverflow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Subsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SphereRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_PolarOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_LightOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_AmbientLight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Texture(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLineColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLineThickness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLineOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLineStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetFillColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetFillOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRoundedCornerRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetGradientType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetGradientStart(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetGradientEnd(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetGradientStartColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetGradientEndColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRadialGradientCenter(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRadialGradientRadius(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRadialGradientCenterColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetRadialGradientEndColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetBlendMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetTextSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetTextStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef AnimatedAttributesBase_GetFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
    extern JSValueRef AnimatedAttributesBase_GetFrame(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetFitType(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetClipOverflow(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetSubsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetSphereRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetPolarOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetLightOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetAmbientLight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_GetTexture(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_SetDrawingLayout(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_Animate(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeLineColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeLineThickness(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeLineOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeFillColor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeFillOpacity(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeRoundedCorners(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeTextSize(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeSubsection(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangePolarOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeLightOffset(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeAmbientLight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeFillGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeFillRadialGradient(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeSphereRotation(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeFrames(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeSkew(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef AnimatedAttributesBase_ChangeTransform(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    Attributes* ExtractAttributes(JSValueRef value);

    extern Drawing* New_Drawing(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Drawing_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Drawing_class();
    extern JSObjectRef Drawing_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Drawing* Drawing_getCppObject(JSObjectRef obj)
    {
        return static_cast<Drawing*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Drawing_newFromCpp(JSContextRef, Drawing*);

    extern JSValueRef Drawing_AddLine(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddSpline(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddArc(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddPolygon(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddEllipse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddImageStrip(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_AddDrawing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_GetElementCount(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_GetElement(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_GetElementHitBy(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_GetBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_CenterPoint(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Drawing_Empty(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#ifndef PDG_NO_GUI
    extern JSValueRef Drawing_Draw(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif

#ifndef PDG_NO_GUI

    extern GraphicsManager* New_GraphicsManager(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef GraphicsManager_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef GraphicsManager_class();
    extern JSObjectRef GraphicsManager_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline GraphicsManager* GraphicsManager_getCppObject(JSObjectRef obj)
    {
        return static_cast<GraphicsManager*>(JSObjectGetPrivate(obj));
    }
    extern GraphicsManager* GraphicsManager_getSingletonInstance();
    extern JSObjectRef GraphicsManager_getScriptSingletonInstance();

    extern JSValueRef GraphicsManager_GetNumScreens(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetNumSupportedScreenModes(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetNthSupportedScreenMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetCurrentScreenMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetScreenBounds(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_SetScreenMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CreateWindowPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CreateOffscreenPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CreateImageFromOffscreenPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CreateFullScreenPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CloseGraphicsPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CloseAllGraphicsPorts(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_CreateFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetMainPort(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_SwitchToFullScreenMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_SwitchToWindowMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_InFullScreenMode(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetFPS(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetTargetFPS(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_SetTargetFPS(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef GraphicsManager_GetMouse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Font* New_Font(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Font_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Font_class();
    extern JSObjectRef Font_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Font* Font_getCppObject(JSObjectRef obj)
    {
        return static_cast<Font*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Font_newFromCpp(JSContextRef, Font*);

    extern JSValueRef Font_GetFontName(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Font_GetFontHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Font_GetFontLeading(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Font_GetFontCapHeight(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Font_GetFontAscent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Font_GetFontDescent(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern Port* New_Port(size_t, const JSValueRef[], JSValueRef*);

    extern JSObjectRef Port_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSClassRef Port_class();
    extern JSObjectRef Port_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    inline Port* Port_getCppObject(JSObjectRef obj)
    {
        return static_cast<Port*>(JSObjectGetPrivate(obj));
    }
    extern JSObjectRef Port_newFromCpp(JSContextRef, Port*);

    extern JSValueRef Port_GetClipRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetClipRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_ResetClipRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_Clear(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetDrawingOrigin(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_GetCursor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetCursor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_GetDrawingArea(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawLine(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawSpline(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawText(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawImage(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_GetTextWidth(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_GetCurrentFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetFont(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetFontForStyle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_SetFontScalingFactor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_StartTrackingMouse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_StopTrackingMouse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_ResetCursor(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

    extern JSValueRef Port_DrawRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawQuad(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawPolygon(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawEllipse(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawArc(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawBezier(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawCircle(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawVector(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawRoundedRect(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawDrawing(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
    extern JSValueRef Port_DrawSphere(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);
#endif
#endif

}
