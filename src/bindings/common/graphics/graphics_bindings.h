// -----------------------------------------------
// graphics_bindings.h
//
// Header file that contains graphics-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for graphics classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"
#include "graphics_macros.h"
#include "../data/data_macros.h"
#include "../animation/animation_macros.h"

%#ifndef PDG_GRAPHICS_BINDINGS_H_INCLUDED
%#define PDG_GRAPHICS_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"
%#include "pdg/sys/drawing.h"
%#include "pdg/sys/renderer.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

BINDING_CLASS(Image)
  SERIALIZABLE_METHODS(Image)
  IMAGE_METHODS(Image)
DECL_END

BINDING_CLASS(ImageStrip)
  SERIALIZABLE_METHODS(ImageStrip)
  IMAGE_METHODS(ImageStrip)
  PROPERTY(ImageStrip, FrameWidth)
  PROPERTY(ImageStrip, NumFrames)
  METHOD(ImageStrip, GetFrame)
DECL_END

BINDING_CLASS(Spline)
  METHOD(Spline, GetFirstOrder)
  METHOD(Spline, GetSecondOrder)
  METHOD(Spline, AddSegment)
  METHOD(Spline, AddPoint)
  METHOD(Spline, GetPoint)
  METHOD(Spline, SetPoint)
  METHOD(Spline, GetPointCount)
  METHOD(Spline, GetMaxU)
  METHOD(Spline, GetBounds)
DECL_END

BINDING_CLASS(Polygon)
  METHOD(Polygon, AddPoint)
  METHOD(Polygon, AddSpline)
  METHOD(Polygon, InsertPoint)
  METHOD(Polygon, RemovePoint)
  METHOD(Polygon, GetPointCount)
  METHOD(Polygon, GetPoint)
  METHOD(Polygon, SetPoint)
  METHOD(Polygon, ClearPoints)
  METHOD(Polygon, GetBounds)
  METHOD(Polygon, CenterPoint)
  METHOD(Polygon, Contains)
  METHOD(Polygon, Equals)
  METHOD(Polygon, Empty)
  METHOD(Polygon, Move)
  METHOD(Polygon, MoveLeft)
  METHOD(Polygon, MoveRight)
  METHOD(Polygon, MoveUp)
  METHOD(Polygon, MoveDown)
  METHOD(Polygon, MoveXTo)
  METHOD(Polygon, MoveYTo)
  METHOD(Polygon, MoveTo)
  METHOD(Polygon, Center)
  METHOD(Polygon, Scale)
  METHOD(Polygon, HorzScale)
  METHOD(Polygon, VertScale)
  METHOD(Polygon, ScaleAround)
  METHOD(Polygon, Rotate)
  METHOD(Polygon, RotateAround)
  METHOD(Polygon, Intersection)
  METHOD(Polygon, UnionWith)
DECL_END

BINDING_CLASS(ElementRef)
  METHOD(ElementRef, Type)
  METHOD(ElementRef, GetControlPoints)
  METHOD(ElementRef, GetControlPoint)
  METHOD(ElementRef, GetAttributes)
  METHOD(ElementRef, SetAttributes)
  METHOD(ElementRef, SetLiveAttributes)
  METHOD(ElementRef, ClearLiveAttributes)
  METHOD(ElementRef, HasLiveAttributes)
  METHOD(ElementRef, ChangeControlPoint)
  METHOD(ElementRef, MoveForward)
  METHOD(ElementRef, MoveBackward)
  METHOD(ElementRef, MoveToFront)
  METHOD(ElementRef, MoveToBack)
  METHOD(ElementRef, Remove)
DECL_END

BINDING_CLASS(Attributes)
  ATTRIBUTES_METHODS(Attributes)
DECL_END

BINDING_CLASS(AnimatedAttributesBase)
  ANIMATED_METHODS(AnimatedAttributesBase)
  ATTRIBUTES_METHODS(AnimatedAttributesBase)
  METHOD(AnimatedAttributesBase, SetDrawingLayout)
  METHOD(AnimatedAttributesBase, Animate)
  METHOD(AnimatedAttributesBase, ChangeLineColor)
  METHOD(AnimatedAttributesBase, ChangeLineThickness)
  METHOD(AnimatedAttributesBase, ChangeLineOpacity)
  METHOD(AnimatedAttributesBase, ChangeFillColor)
  METHOD(AnimatedAttributesBase, ChangeFillOpacity)
  METHOD(AnimatedAttributesBase, ChangeRoundedCorners)
  METHOD(AnimatedAttributesBase, ChangeTextSize)
  METHOD(AnimatedAttributesBase, ChangeSubsection)
  METHOD(AnimatedAttributesBase, ChangePolarOffset)
  METHOD(AnimatedAttributesBase, ChangeLightOffset)
  METHOD(AnimatedAttributesBase, ChangeAmbientLight)
  METHOD(AnimatedAttributesBase, ChangeFillGradient)
  METHOD(AnimatedAttributesBase, ChangeFillRadialGradient)
  METHOD(AnimatedAttributesBase, ChangeSphereRotation)
  METHOD(AnimatedAttributesBase, ChangeFrames)
  METHOD(AnimatedAttributesBase, ChangeSkew)
  METHOD(AnimatedAttributesBase, ChangeTransform)
DECL_END

Attributes* ExtractAttributes(VALUE_REF value);

BINDING_CLASS(Drawing)
  METHOD(Drawing, AddLine)
  METHOD(Drawing, AddSpline)
  METHOD(Drawing, AddRect)
  METHOD(Drawing, AddArc)
  METHOD(Drawing, AddQuad)
  METHOD(Drawing, AddPolygon)
  METHOD(Drawing, AddEllipse)
  METHOD(Drawing, AddImage)
  METHOD(Drawing, AddImageStrip)
  METHOD(Drawing, AddDrawing)
  METHOD(Drawing, GetElementCount)
  METHOD(Drawing, GetElement)
  METHOD(Drawing, GetElementHitBy)
  METHOD(Drawing, GetBounds)
  METHOD(Drawing, CenterPoint)
  METHOD(Drawing, Empty)
%#ifndef PDG_NO_GUI
  METHOD(Drawing, Draw)
%#endif // !PDG_NO_GUI
DECL_END

%#ifndef PDG_NO_GUI

SINGLETON_CLASS(GraphicsManager)
  METHOD(GraphicsManager, GetNumScreens)
  METHOD(GraphicsManager, GetNumSupportedScreenModes)
  METHOD(GraphicsManager, GetNthSupportedScreenMode)
  METHOD(GraphicsManager, GetCurrentScreenMode)
  METHOD(GraphicsManager, GetScreenBounds)
  METHOD(GraphicsManager, SetScreenMode)
  METHOD(GraphicsManager, CreateWindowPort)
  METHOD(GraphicsManager, CreateOffscreenPort)
  METHOD(GraphicsManager, CreateImageFromOffscreenPort)
  METHOD(GraphicsManager, CreateFullScreenPort)
  METHOD(GraphicsManager, CloseGraphicsPort)
  METHOD(GraphicsManager, CloseAllGraphicsPorts)
  METHOD(GraphicsManager, CreateFont)
  METHOD(GraphicsManager, GetMainPort)
  METHOD(GraphicsManager, SwitchToFullScreenMode)
  METHOD(GraphicsManager, SwitchToWindowMode)
  METHOD(GraphicsManager, InFullScreenMode)
  METHOD(GraphicsManager, GetFPS)
  PROPERTY(GraphicsManager, TargetFPS)
  METHOD(GraphicsManager, GetMouse)
DECL_END

WRAPPER_CLASS(Font)
  METHOD(Font, GetFontName)
  METHOD(Font, GetFontHeight)
  METHOD(Font, GetFontLeading)
  METHOD(Font, GetFontCapHeight)
  METHOD(Font, GetFontAscent)
  METHOD(Font, GetFontDescent)
DECL_END

WRAPPER_CLASS(Port)
  PROPERTY(Port, ClipRect)
  METHOD(Port, ResetClipRect)
  METHOD(Port, Clear)
  METHOD(Port, SetDrawingOrigin)
  PROPERTY(Port, Cursor)
  METHOD(Port, GetDrawingArea)
  METHOD(Port, DrawLine)
  METHOD(Port, DrawSpline)
  METHOD(Port, DrawText)
  METHOD(Port, DrawImage)
  METHOD(Port, GetTextWidth)
  METHOD(Port, GetCurrentFont)
  METHOD(Port, SetFont)
  METHOD(Port, SetFontForStyle)
  METHOD(Port, SetFontScalingFactor)
  METHOD(Port, StartTrackingMouse)
  METHOD(Port, StopTrackingMouse)
  METHOD(Port, ResetCursor)
  // New Renderer API methods
  METHOD(Port, DrawRect)
  METHOD(Port, DrawQuad)
  METHOD(Port, DrawPolygon)
  METHOD(Port, DrawEllipse)
  METHOD(Port, DrawArc)
  METHOD(Port, DrawBezier)
  METHOD(Port, DrawCircle)
  METHOD(Port, DrawVector)
  METHOD(Port, DrawRoundedRect)
  METHOD(Port, DrawDrawing)
  METHOD(Port, DrawSphere)
DECL_END

%#endif // !PDG_NO_GUI


%#endif // PDG_GRAPHICS_BINDINGS_H_INCLUDED 

} // namespace pdg
