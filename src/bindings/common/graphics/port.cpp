// -----------------------------------------------
// port.cpp
//
// Implementation file for Port bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "graphics_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    
%#ifndef PDG_NO_GUI

// ========================================================================================
//MARK: Port
// ========================================================================================

WRAPPER_INITIALIZER_IMPL_CUSTOM(Port,
    OBJECT_SAVE(cppObj->mPortScriptObj, obj) )
      EXPORT_CLASS_SYMBOLS("Port", Port, , ,
          HAS_METHOD(Port, "getCamera", GetCamera)
          HAS_PROPERTY(Port, CameraAnchor)
          HAS_PROPERTY(Port, CameraDrawingEnabled)
          HAS_METHOD(Port, "worldToPort", WorldToPort)
          HAS_METHOD(Port, "portToWorld", PortToWorld)
          // method section
          HAS_PROPERTY(Port, ClipRect)
    HAS_METHOD(Port, "resetClipRect", ResetClipRect)
    HAS_METHOD(Port, "clear", Clear)
    HAS_METHOD(Port, "setDrawingOrigin", SetDrawingOrigin)
          HAS_PROPERTY(Port, Cursor)
          HAS_GETTER(Port, DrawingArea)
          HAS_METHOD(Port, "drawLine", DrawLine)
          HAS_METHOD(Port, "drawSpline", DrawSpline)
          HAS_METHOD(Port, "drawText", DrawText)
          HAS_METHOD(Port, "drawImage", DrawImage)
          //HAS_METHOD(Port, "drawTexture", DrawTexture)
          //HAS_METHOD(Port, "drawTexturedSphere", DrawTexturedSphere)
          HAS_METHOD(Port, "getTextWidth", GetTextWidth)
          HAS_METHOD(Port, "getCurrentFont", GetCurrentFont)
          HAS_METHOD(Port, "setFont", SetFont)
          HAS_METHOD(Port, "setFontForStyle", SetFontForStyle)
          HAS_METHOD(Port, "setFontScalingFactor", SetFontScalingFactor)
          HAS_METHOD(Port, "startTrackingMouse", StartTrackingMouse)
          HAS_METHOD(Port, "stopTrackingMouse", StopTrackingMouse)
          HAS_METHOD(Port, "resetCursor", ResetCursor)
          // New Renderer API methods
          HAS_METHOD(Port, "drawRect", DrawRect)
          HAS_METHOD(Port, "drawQuad", DrawQuad)
          HAS_METHOD(Port, "drawPolygon", DrawPolygon)
          HAS_METHOD(Port, "drawEllipse", DrawEllipse)
          HAS_METHOD(Port, "drawArc", DrawArc)
          HAS_METHOD(Port, "drawBezier", DrawBezier)
          HAS_METHOD(Port, "drawCircle", DrawCircle)
          HAS_METHOD(Port, "drawVector", DrawVector)
          HAS_METHOD(Port, "drawRoundedRect", DrawRoundedRect)
          HAS_METHOD(Port, "drawDrawing", DrawDrawing)
          HAS_METHOD(Port, "drawSphere", DrawSphere)
      );
      END
  GETTER_IMPL(Port, CameraAnchor, POINT)
  METHOD_IMPL(Port, SetCameraAnchor)
    METHOD_SIGNATURE("", [this], 1, ([object Point const&] inCameraAnchor));
    REQUIRE_ARG_COUNT(1); REQUIRE_POINT_ARG(1, value);
    self->setCameraAnchor(value); RETURN_THIS;
    END
  PROPERTY_IMPL(Port, CameraDrawingEnabled, BOOL)
  METHOD_IMPL(Port, GetCamera)
    METHOD_SIGNATURE("", [object Camera*], 0, ());
    auto* camera=self->getCamera(); RETURN_CPP_OBJECT(camera, Camera);
    END
  METHOD_IMPL(Port, WorldToPort)
    METHOD_SIGNATURE("", [object Point], 1, ([object Point const&] point));
    try { REQUIRE_POINT_ARG(1, point); auto result=self->worldToPort(point); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
  METHOD_IMPL(Port, PortToWorld)
    METHOD_SIGNATURE("", [object Point], 1, ([object Point const&] point));
    try { REQUIRE_POINT_ARG(1, point); auto result=self->portToWorld(point); RETURN_POINT(result); } catch(const std::exception& error) { THROW_ERR(error.what()); }
    END
  GETTER_IMPL(Port, DrawingArea, RECT)
  GETTER_IMPL(Port, ClipRect, RECT)
  METHOD_IMPL(Port, SetClipRect)
    METHOD_SIGNATURE("", [this], 1, ([object Rect const&] inClipRect));
    REQUIRE_ARG_COUNT(1); REQUIRE_RECT_ARG(1, value);
    self->setClipRect(value); RETURN_THIS;
    END
METHOD_IMPL(Port, Clear)
    METHOD_SIGNATURE("Replace pixels inside the current clip with an exact color.", [this], 1, ({[object Color const&] color = Color(0, 0, 0, 0)|string colorName|number rgba}));
    OPTIONAL_COLOR_ARG(1, color, Color(0, 0, 0, 0));
    self->clear(color);
    RETURN_THIS;
    END
METHOD_IMPL(Port, SetDrawingOrigin)
    METHOD_SIGNATURE("Set the Port coordinate at the top left of an offscreen surface.", [this], 1, ([object Point const&] origin));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, origin);
    try { self->setDrawingOrigin(origin); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    RETURN_THIS;
    END
METHOD_IMPL(Port, ResetClipRect)
    METHOD_SIGNATURE("Restore the clipping rectangle to the full drawing area.", [this], 0, ());
    REQUIRE_ARG_COUNT(0);
    self->resetClipRect();
    RETURN_THIS;
    END
  METHOD_IMPL(Port, DrawLine) // support both Attributes and Color objects for arg 3 to avoid name conflicts
      METHOD_SIGNATURE("draws a line from one point to another with the specified attributes", [this], 3, ([object Point const&] from, [object Point const&] to, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, from);
      REQUIRE_POINT_ARG(2, to);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      self->drawLine(from, to, *attrs);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, DrawSpline) // support both Attributes and Color objects for arg 2 to avoid name conflicts
      METHOD_SIGNATURE("draws a spline curve with the specified attributes", [this], 2, ([object Spline const&] spline, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_CPP_OBJECT_ARG(1, spline, Spline);
      REQUIRE_ATTRIBUTES_ARG(2, attrs);
      self->drawSpline(*spline, *attrs);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, GetTextWidth)
      METHOD_SIGNATURE("", number, 4, (string text, [number int] size, [number uint] style = textStyle_Plain, [number int] len = -1));
      REQUIRE_ARG_MIN_COUNT(2);
      REQUIRE_STRING_ARG(1, text);
      REQUIRE_INT32_ARG(2, size); 
      OPTIONAL_UINT32_ARG(3, style, textStyle_Plain); 
      OPTIONAL_INT32_ARG(4, len, -1); 
      int width = self->getTextWidth(text, size, style, len);
      RETURN_INTEGER(width);
      END
  METHOD_IMPL(Port, GetCurrentFont)
      METHOD_SIGNATURE("", [object Font*], 1, ([number uint] style = textStyle_Plain));
      OPTIONAL_UINT32_ARG(1, style, textStyle_Plain);
      Font* font = self->getCurrentFont(style);
      RETURN_CPP_OBJECT(font, Font);
      END
  METHOD_IMPL(Port, SetFont)
      METHOD_SIGNATURE("sets the current font for text rendering", [this], 1, ([object Font*] font = DEFAULT_FONT));
      OPTIONAL_CPP_OBJECT_ARG(1, font, Font, 0);
      self->setFont(font);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, SetFontForStyle)
      METHOD_SIGNATURE("Set a custom font for a specific text style (bold, italic, etc.)", [this], 2, ([number uint] style, [object Font*] font = DEFAULT_FONT));
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_UINT32_ARG(1, style); 
      OPTIONAL_CPP_OBJECT_ARG(2, font, Font, 0);
      self->setFontForStyle(font, style);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, SetFontScalingFactor)
      METHOD_SIGNATURE("Set a scaling factor to adjust the size of all rendered text", [this], 1, (number scaleBy));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_NUMBER_ARG(1, scaleBy); 
      self->setFontScalingFactor(scaleBy);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, StartTrackingMouse)
      METHOD_SIGNATURE("NOT IMPLEMENTED", number, 1, ([object Rect const&] rect));
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_RECT_ARG(1, rect);
      int trackingRef = self->startTrackingMouse(rect);
      RETURN_INTEGER(trackingRef);
      END
  METHOD_IMPL(Port, StopTrackingMouse)
      METHOD_SIGNATURE("NOT IMPLEMENTED", [this], 1, ([number int] trackingRef));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_INT32_ARG(1, trackingRef); 
      self->stopTrackingMouse(trackingRef);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, SetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED", [this], 1, ([object Image*] cursorImage, [object Point const&] hotSpot));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_CPP_OBJECT_ARG(1, cursorImage, Image); 
      REQUIRE_POINT_ARG(2, hotSpot); 
      self->setCursor(cursorImage, hotSpot);
      RETURN_THIS;
      END
  METHOD_IMPL(Port, GetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED: get the Image that is being used as the cursor",
          [object Image*], 0, ());
      REQUIRE_ARG_COUNT(0);
      Image* cursorImage = self->getCursor();
      RETURN_CPP_OBJECT(cursorImage, Image);
      END
  METHOD_IMPL(Port, ResetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED", [this], 0, ());
      REQUIRE_ARG_COUNT(0);
      self->resetCursor();
      RETURN_THIS;
      END

  // New Renderer API method implementations
  METHOD_IMPL(Port, DrawRect)
      METHOD_SIGNATURE("draws a rectangle with the specified attributes", [this], 2, ([object Rect const&] rect, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_RECT_ARG(1, rect);
      REQUIRE_ATTRIBUTES_ARG(2, attrs);
      self->drawRect(rect, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawQuad)
      METHOD_SIGNATURE("draws a quad with the specified attributes", [this], 2, ([object Quad const&] quad, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_QUAD_ARG(1, quad);
      REQUIRE_ATTRIBUTES_ARG(2, attrs);
      self->drawQuad(quad, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawPolygon)
      METHOD_SIGNATURE("draws a polygon with the specified attributes", [this], 2, ([object Polygon const&] polygon, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_CPP_OBJECT_ARG(1, polygon, Polygon);
      REQUIRE_ATTRIBUTES_ARG(2, attrs);
      self->drawPolygon(*polygon, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawEllipse)
      METHOD_SIGNATURE("Draw an ellipse at the specified center point with given x and y radii", [this], 4, ([object Point const&] center, [number float] xRadius, [number float] yRadius, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(4);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, xRadius);
      REQUIRE_NUMBER_ARG(3, yRadius);
      REQUIRE_ATTRIBUTES_ARG(4, attrs);
      self->drawEllipse(center, xRadius, yRadius, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawArc)
      METHOD_SIGNATURE("Draw an elliptical arc using the specified center, radii, and angle range", [this], 6, ([object Point const&] center, [number float] xRadius, [number float] yRadius, [number float] startAngle, [number float] endAngle, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(6);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, xRadius);
      REQUIRE_NUMBER_ARG(3, yRadius);
      REQUIRE_NUMBER_ARG(4, startAngle);
      REQUIRE_NUMBER_ARG(5, endAngle);
      REQUIRE_ATTRIBUTES_ARG(6, attrs);
      self->drawArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawBezier)
      METHOD_SIGNATURE("draws a Bezier curve with the specified control points and attributes", [this], 5, ([object Point const&] from, [object Point const&] control1, [object Point const&] control2, [object Point const&] to, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(5);
      REQUIRE_POINT_ARG(1, from);
      REQUIRE_POINT_ARG(2, control1);
      REQUIRE_POINT_ARG(3, control2);
      REQUIRE_POINT_ARG(4, to);
      REQUIRE_ATTRIBUTES_ARG(5, attrs);
      self->drawBezier(from, control1, control2, to, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawCircle)
      METHOD_SIGNATURE("Draw a circle at the specified center point with given radius", [this], 3, ([object Point const&] center, [number float] radius, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      self->drawCircle(center, radius, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawVector)
      METHOD_SIGNATURE("Draw a vector (arrow) from origin to the specified endpoint", [this], 2, ([object Vector const&] vector, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_VECTOR_ARG(1, vector);
      REQUIRE_ATTRIBUTES_ARG(2, attrs);
      self->drawVector(vector, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawRoundedRect)
      METHOD_SIGNATURE("Draw a rectangle with rounded corners using the specified corner radius", [this], 3, ([object Rect const&] rect, [number float] radius, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_RECT_ARG(1, rect);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      self->drawRoundedRect(rect, radius, *attrs);
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawImage)
      METHOD_SIGNATURE("Draws an image at the specified location with styling attributes", [this], 3, ({[object Image*] img, [object Point const&] loc, [object Attributes const&] attrs|[object Image*] img, [object Rect const&] rect, [object Attributes const&] attrs|[object Image*] img, [object Quad const&] quad, [object Attributes const&] attrs}));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_CPP_OBJECT_ARG(1, img, Image);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      pdg::Point loc;
      auto isPoint = VALUE_IS_POINT(ARGV[1], loc);
      if (!isPoint.has_value()) { RETURN_NULL; }
      if (*isPoint) {
          self->drawImage(img, loc, *attrs);
      } else {
          // Rectangles (including rotation) are accepted by the Quad converter.
          REQUIRE_QUAD_ARG(2, quad);
          self->drawImage(img, quad, *attrs);
      }
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawDrawing)
      METHOD_SIGNATURE("Draws a Drawing object at the specified location with styling attributes", [this], 3, ({[object Drawing const&] drawing, [object Point const&] loc, [object Attributes const&] attrs|[object Drawing const&] drawing, [object Rect const&] rect, [object Attributes const&] attrs}));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_CPP_OBJECT_ARG(1, drawing, Drawing);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      pdg::Point loc;
      auto isPoint = VALUE_IS_POINT(ARGV[1], loc);
      if (!isPoint.has_value()) { RETURN_NULL; }
      if (*isPoint) {
          self->drawDrawing(*drawing, loc, *attrs);
      } else {
          // Rect variant
          REQUIRE_RECT_ARG(2, rect);
          self->drawDrawing(*drawing, rect, *attrs);
      }
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawText)
      METHOD_SIGNATURE("Draws text at the specified location with styling attributes", [this], 3, ({string text, [object Point const&] loc, [object Attributes const&] attrs|string text, [object Rect const&] rect, [object Attributes const&] attrs}));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_STRING_ARG(1, text);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      pdg::Point loc;
      auto isPoint = VALUE_IS_POINT(ARGV[1], loc);
      if (!isPoint.has_value()) { RETURN_NULL; }
      if (*isPoint) {
          self->drawText(text, loc, *attrs);
      } else {
          // Rect variant
          REQUIRE_RECT_ARG(2, rect);
          self->drawText(text, rect, *attrs);
      }
      RETURN_THIS;
      END

  METHOD_IMPL(Port, DrawSphere)
      METHOD_SIGNATURE("Draws a textured sphere at the specified center point with given radius and styling attributes", [this], 3, ([object Point const&] center, [number float] radius, [object Attributes const&] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_ATTRIBUTES_ARG(3, attrs);
      self->drawSphere(center, radius, *attrs);
      RETURN_THIS;
      END
  
  CLEANUP_IMPL(Port)
  
  CPP_UNMANAGED_CONSTRUCTOR_IMPL(Port, cppPtr_ = nullptr; CR )
      SAVE_ERR("Port cannot be created directly, use pdg.gfx.createWindowPort() or pdg.gfx.createFullScreenPort()");
      return 0;
      END
  
%#endif //!PDG_NO_GUI
  

} // pdg namespace

// @pdg-class {"name":"Port","construction":{"kind":"factory","factory":"GraphicsManager port factories"},"native_binding":{"browser":{"base":null,"generate":true,"guard":"!PDG_NO_GUI","constructors":[{"factory":"pdg::emscriptenCreatePort","allow_raw_pointers":true}],"support_bindings":[{"name":"_getNativeIdentity","symbol":"pdg::emscriptenPortGetIdentity"}]}}}

// @pdg-member {"name":"Port.getTextWidth","native_binding":{"adapter":"browser.emscriptenPortGetTextWidth","binding_name":"_getTextWidth"}}

// @pdg-member {"name":"Port.getCurrentFont","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Port.setFont","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Port.setFontForStyle","native_binding":{"allow_raw_pointers":true}}


// @pdg-member {"name":"Port.startTrackingMouse","native_binding":{"adapter":"browser.emscriptenPortStartTrackingMouse"}}






// @pdg-member {"name":"Port.drawImage","native_binding":{"adapter":"browser.emscriptenPortDrawImage","allow_raw_pointers":true}}

// @pdg-member {"name":"Port.drawDrawing","native_binding":{"adapter":"browser.emscriptenPortDrawDrawing"}}

// @pdg-member {"name":"Port.drawText","native_binding":{"adapter":"browser.emscriptenPortDrawText"}}
