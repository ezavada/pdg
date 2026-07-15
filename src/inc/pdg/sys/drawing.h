// -----------------------------------------------
//  drawing.h
//
// Written by Ed Zavada, 2025
// Copyright (c) 2024, Dream Rock Studios, LLC
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

#ifndef PDG_DRAWING_H_INCLUDED
#define PDG_DRAWING_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/coordinates.h"
#include "pdg/sys/global_types.h"
#include "pdg/sys/color.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"
#include "pdg/sys/image.h"
#include "pdg/sys/imagestrip.h"
#include "pdg/sys/port.h"
#include "pdg/sys/attributes.h"

#include <vector>
#include <utility>

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

    class Drawing;

    enum ElementType {
        type_Line = 1,
        type_Spline,
        type_Arc,
        type_Rect,
        type_Quad,
        type_Polygon,
        type_Ellipse,
        type_Image,
        type_ImageStrip,
        type_Drawing,  // a drawing can contain other drawings
        // not including Text yet
    };

    class ElementRef {
      #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        friend class ElementRefWrap;
        friend class DrawingWrap;
      #endif // PDG_COMPILING_FOR_SCRIPT_BINDINGS
     public:

        ElementType type() const;

        // control points vary by element type
        // points are in Drawing's coordinate system
        const std::vector<Point>& getControlPoints() const;   // all the control points for the element
        const Point& getControlPoint(int controlPointIndex) const;
        void changeControlPoint(int controlPointIndex, const Point& controlPoint);

        void getAttributes(Attributes& attrs) const;
        void setAttributes(const Attributes& attrs);

        void moveForward();
        void moveBackward();
        void moveToFront();
        void moveToBack();

        void remove();

        ElementRef(Drawing* drawing, uint32_t index) : drawing(drawing), index(index) {
        #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          INIT_SCRIPT_OBJECT(mElementRefScriptObj);
        #endif
        }
        virtual ~ElementRef() {
        #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          #ifndef PDG_NO_GUI
            CleanupElementRefScriptObject(mElementRefScriptObj);
          #endif
        #endif
        }

      protected:
        Drawing* drawing;
        uint32_t index;
      #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        SCRIPT_OBJECT_REF mElementRefScriptObj;
      #endif // PDG_COMPILING_FOR_SCRIPT_BINDINGS
    };

    class Drawing {
      #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
        friend class DrawingWrap;
      #endif // PDG_COMPILING_FOR_SCRIPT_BINDINGS
    public:
        static Drawing* create();

		    // Add operations to the drawing. Returns the index of the added element.
		    virtual ElementRef* addLine(const Point& from, const Point& to, const Attributes& attrs) = 0;
        virtual ElementRef* addSpline(Spline&& spline, const Attributes& attrs) = 0;
        virtual ElementRef* addArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs) = 0;
        virtual ElementRef* addRect(const Rect& rect, const Attributes& attrs) = 0;
        virtual ElementRef* addQuad(const Quad& quad, const Attributes& attrs) = 0;
        virtual ElementRef* addPolygon(Polygon&& polygon, const Attributes& attrs) = 0;
        virtual ElementRef* addEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs) = 0;

        virtual ElementRef* addImage(const Rect& rect, const Image& image, const Attributes& attrs) = 0;
        virtual ElementRef* addImageStrip(const Rect& rect, const ImageStrip& imageStrip, const Attributes& attrs) = 0;
        virtual ElementRef* addDrawing(const Rect& rect, const Drawing& drawing, const Attributes& attrs) = 0;

		    virtual size_t getElementCount() const = 0;
        virtual ElementRef* getElement(size_t index) const = 0;
        virtual ElementRef* getElementHitBy(const Point& point) const = 0;  // returns the index of the element hit by the point, or -1 if no element is hit
		
		// Geometric operations
		virtual Rect getBounds() const = 0;
		virtual Point centerPoint() const = 0;
		virtual bool empty() const = 0;

    #ifndef PDG_NO_GUI
        // drawing operations
        virtual void draw(Port* port) = 0;
        virtual void draw(Port* port, const Rect& rect) = 0;
        virtual void draw(Port* port, const Quad& quad) = 0;
        virtual void draw(Port* port, const RotatedRect& rr) = 0;
    #endif // PDG_NO_GUI

  #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
    SCRIPT_OBJECT_REF mDrawingScriptObj;
  #endif
    protected:
        // Constructors
        Drawing() {
        #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          INIT_SCRIPT_OBJECT(mDrawingScriptObj);
        #endif
        }
        virtual ~Drawing() {
        #ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
          #ifndef PDG_NO_GUI
            CleanupDrawingScriptObject(mDrawingScriptObj);
          #endif
        #endif
        }
	};
	
} // end namespace pdg

#endif // PDG_DRAWING_H_INCLUDED
