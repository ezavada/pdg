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
          // method section
          HAS_PROPERTY(Port, ClipRect)
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
  GETTER_IMPL(Port, DrawingArea, RECT)
  PROPERTY_IMPL(Port, ClipRect, RECT)
  METHOD_IMPL(Port, DrawLine) // support both Attributes and Color objects for arg 3 to avoid name conflicts
      METHOD_SIGNATURE("", undefined, 3, ([object Point] from, [object Point] to, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, from);
      REQUIRE_POINT_ARG(2, to);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      self->drawLine(from, to, *attrs);
      NO_RETURN;
      END
  METHOD_IMPL(Port, DrawSpline) // support both Attributes and Color objects for arg 2 to avoid name conflicts
      METHOD_SIGNATURE("", undefined, 2, ([object Spline] spline, [object Attributes] attrs)); 
      REQUIRE_ARG_COUNT(2);
      REQUIRE_OBJECT_ARG(1, spline);
      REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
      SplineWrap* splineWrapper = static_cast<SplineWrap*>(OBJECT_PRIVATE_DATA(spline));
      Spline* splinePtr = splineWrapper->getCppObject();
      if (!splinePtr) {
          THROW_TYPE_ERR("drawSpline must be called with a valid Spline object");
          return;
      }
      self->drawSpline(*splinePtr, *attrs);
      NO_RETURN;
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
      METHOD_SIGNATURE("", [object Font], 1, ([number uint] style = textStyle_Plain)); 
      OPTIONAL_UINT32_ARG(1, style, textStyle_Plain);
      Font* font = self->getCurrentFont(style);
      RETURN_CPP_OBJECT(font, Font);
      END
  METHOD_IMPL(Port, SetFont)
      METHOD_SIGNATURE("", undefined, 1, ([object Font] font = DEFAULT_FONT)); 
      OPTIONAL_CPP_OBJECT_ARG(1, font, Font, 0);
      self->setFont(font);
      NO_RETURN;
      END
  METHOD_IMPL(Port, SetFontForStyle)
      METHOD_SIGNATURE("", undefined, 2, ([number uint] style, [object Font] font = DEFAULT_FONT)); 
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_UINT32_ARG(1, style); 
      OPTIONAL_CPP_OBJECT_ARG(2, font, Font, 0);
      self->setFontForStyle(font, style);
      NO_RETURN;
      END
  METHOD_IMPL(Port, SetFontScalingFactor)
      METHOD_SIGNATURE("", undefined, 1, (number scaleBy));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_NUMBER_ARG(1, scaleBy); 
      self->setFontScalingFactor(scaleBy);
      NO_RETURN;
      END
  METHOD_IMPL(Port, StartTrackingMouse)
      METHOD_SIGNATURE("NOT IMPLEMENTED", number, 1, ([object Rect] rect));
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_RECT_ARG(1, rect);
      int trackingRef = self->startTrackingMouse(rect);
      RETURN_INTEGER(trackingRef);
      END
  METHOD_IMPL(Port, StopTrackingMouse)
      METHOD_SIGNATURE("NOT IMPLEMENTED", undefined, 1, ([number int] trackingRef));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_INT32_ARG(1, trackingRef); 
      self->stopTrackingMouse(trackingRef);
      NO_RETURN;
      END
  METHOD_IMPL(Port, SetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED", undefined, 1, ([object Image] cursorImage, [object Point] hotSpot));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_CPP_OBJECT_ARG(1, cursorImage, Image); 
      REQUIRE_POINT_ARG(2, hotSpot); 
      self->setCursor(cursorImage, hotSpot);
      NO_RETURN;
      END
  METHOD_IMPL(Port, GetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED: get the Image that is being used as the cursor",
          [object Image], 0, ());
      REQUIRE_ARG_COUNT(0);
      Image* cursorImage = self->getCursor();
      RETURN_CPP_OBJECT(cursorImage, Image);
      END
  METHOD_IMPL(Port, ResetCursor)
      METHOD_SIGNATURE("NOT IMPLEMENTED: restore the default system cursor",
          undefined, 0, ());
      REQUIRE_ARG_COUNT(0);
      self->resetCursor();
      NO_RETURN;
      END

  // New Renderer API method implementations
  METHOD_IMPL(Port, DrawRect)
      METHOD_SIGNATURE("", undefined, 2, ([object Rect] rect, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_RECT_ARG(1, rect);
      REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
      self->drawRect(rect, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawQuad)
      METHOD_SIGNATURE("", undefined, 2, ([object Quad] quad, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_QUAD_ARG(1, quad);
      REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
      self->drawQuad(quad, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawPolygon)
      METHOD_SIGNATURE("", undefined, 2, ([object Polygon] polygon, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_CPP_OBJECT_ARG(1, polygon, Polygon);
      REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
      self->drawPolygon(*polygon, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawEllipse)
      METHOD_SIGNATURE("", undefined, 4, ([object Point] center, [number float] xRadius, [number float] yRadius, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(4);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, xRadius);
      REQUIRE_NUMBER_ARG(3, yRadius);
      REQUIRE_CPP_OBJECT_ARG(4, attrs, Attributes);
      self->drawEllipse(center, xRadius, yRadius, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawArc)
      METHOD_SIGNATURE("", undefined, 6, ([object Point] center, [number float] xRadius, [number float] yRadius, [number float] startAngle, [number float] endAngle, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(6);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, xRadius);
      REQUIRE_NUMBER_ARG(3, yRadius);
      REQUIRE_NUMBER_ARG(4, startAngle);
      REQUIRE_NUMBER_ARG(5, endAngle);
      REQUIRE_CPP_OBJECT_ARG(6, attrs, Attributes);
      self->drawArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawBezier)
      METHOD_SIGNATURE("", undefined, 5, ([object Point] from, [object Point] control1, [object Point] control2, [object Point] to, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(5);
      REQUIRE_POINT_ARG(1, from);
      REQUIRE_POINT_ARG(2, control1);
      REQUIRE_POINT_ARG(3, control2);
      REQUIRE_POINT_ARG(4, to);
      REQUIRE_CPP_OBJECT_ARG(5, attrs, Attributes);
      self->drawBezier(from, control1, control2, to, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawCircle)
      METHOD_SIGNATURE("", undefined, 3, ([object Point] center, [number float] radius, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      self->drawCircle(center, radius, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawVector)
      METHOD_SIGNATURE("", undefined, 2, ([object Vector] vector, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_VECTOR_ARG(1, vector);
      REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
      self->drawVector(vector, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawRoundedRect)
      METHOD_SIGNATURE("", undefined, 3, ([object Rect] rect, [number float] radius, [object Attributes] attrs));
      REQUIRE_ARG_COUNT(3);
      REQUIRE_RECT_ARG(1, rect);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      self->drawRoundedRect(rect, radius, *attrs);
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawImage)
      METHOD_SIGNATURE("", undefined, 3, ({[object Image] img, [object Point] loc, [object Attributes] attrs|[object Image] img, [object Rect] rect, [object Attributes] attrs|[object Image] img, [object Quad] quad, [object Attributes] attrs})); 
      REQUIRE_ARG_COUNT(3);
      REQUIRE_CPP_OBJECT_ARG(1, img, Image);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      if (VALUE_IS_POINT(ARGV[1])) { 
          // Point variant
          pdg::Point loc = VAL2POINT(ARGV[1]);
          self->drawImage(img, loc, *attrs);
      } else if (VALUE_IS_QUAD(ARGV[1])) {
          // Quad variant
          pdg::Quad quad = VAL2QUAD(ARGV[1]);
          self->drawImage(img, quad, *attrs);
      } else {
          // Rect variant
          REQUIRE_RECT_ARG(2, rect);
          self->drawImage(img, rect, *attrs);
      }
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawDrawing)
      METHOD_SIGNATURE("", undefined, 3, ({[object Drawing] drawing, [object Point] loc, [object Attributes] attrs|[object Drawing] drawing, [object Rect] rect, [object Attributes] attrs})); 
      REQUIRE_ARG_COUNT(3);
      REQUIRE_OBJECT_ARG(1, drawing);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      DrawingWrap* drawingWrapper = static_cast<DrawingWrap*>(OBJECT_PRIVATE_DATA(drawing));
      Drawing* drawingPtr = drawingWrapper->getCppObject();
      if (!drawingPtr) {
          THROW_TYPE_ERR("drawDrawingWithAttrs must be called with a valid Drawing object");
          return;
      }
      if (VALUE_IS_POINT(ARGV[1])) { 
          // Point variant
          pdg::Point loc = VAL2POINT(ARGV[1]);
          self->drawDrawing(*drawingPtr, loc, *attrs);
      } else {
          // Rect variant
          REQUIRE_RECT_ARG(2, rect);
          self->drawDrawing(*drawingPtr, rect, *attrs);
      }
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawText)
      METHOD_SIGNATURE("", undefined, 3, ({string text, [object Point] loc, [object Attributes] attrs|string text, [object Rect] rect, [object Attributes] attrs})); 
      REQUIRE_ARG_COUNT(3);
      REQUIRE_STRING_ARG(1, text);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      if (VALUE_IS_POINT(ARGV[1])) { 
          // Point variant
          pdg::Point loc = VAL2POINT(ARGV[1]);
          self->drawText(text, loc, *attrs);
      } else {
          // Rect variant
          REQUIRE_RECT_ARG(2, rect);
          self->drawText(text, rect, *attrs);
      }
      NO_RETURN;
      END

  METHOD_IMPL(Port, DrawSphere)
      METHOD_SIGNATURE("", undefined, 3, ([object Point] center, [number float] radius, [object Attributes] attrs)); 
      REQUIRE_ARG_COUNT(3);
      REQUIRE_POINT_ARG(1, center);
      REQUIRE_NUMBER_ARG(2, radius);
      REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
      self->drawSphere(center, radius, *attrs);
      NO_RETURN;
      END
  
  CLEANUP_IMPL(Port)
  
  CPP_UNMANAGED_CONSTRUCTOR_IMPL(Port, cppPtr_ = nullptr; CR )
      SAVE_ERR("Port cannot be created directly, use pdg.gfx.createWindowPort() or pdg.gfx.createFullScreenPort()");
      return 0;
      END
  
%#endif //!PDG_NO_GUI
  

} // pdg namespace
