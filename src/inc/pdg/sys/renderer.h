// -----------------------------------------------
//  renderer.h
//
// New graphics API for PDG framework
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
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

#ifndef PDG_RENDERER_H_INCLUDED
#define PDG_RENDERER_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/attributes.h"
#include "pdg/sys/coordinates.h"
#include "pdg/sys/global_types.h"
#include "pdg/sys/color.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"

// Forward declarations to avoid circular includes
namespace pdg {
    class Image;
    class Drawing;
}

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
#include "pdg_script_bindings.h"
#endif

namespace pdg {

    // -----------------------------------------------------------------------------------
    // Renderer interface
    // -----------------------------------------------------------------------------------

    /// Drawing operations return the renderer by reference for chaining.
    class Renderer {
    public:
        virtual ~Renderer() = default;

        // Various types of lines
        virtual Renderer& drawLine(const Point& from, const Point& to, const Attributes& attrs) = 0;
        Renderer&    drawVector(const Vector& v, const Attributes& attrs);
        virtual Renderer& drawSpline(const Spline& spline, const Attributes& attrs) = 0;
        virtual Renderer& drawArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs) = 0;
        Renderer&    drawBezier(const Point& from, const Point& control1, const Point& control2, const Point& to, const Attributes& attrs);

        // Various types of enclosed shapes
        virtual Renderer& drawRect(const Rect& rect, const Attributes& attrs) = 0;
        virtual Renderer& drawQuad(const Quad& quad, const Attributes& attrs) = 0;
        Renderer&    drawCircle(const Point& center, float radius, const Attributes& attrs);
        virtual Renderer& drawPolygon(const Polygon& polygon, const Attributes& attrs) = 0;
        virtual Renderer& drawEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs) = 0;
        Renderer&    drawRoundedRect(const Rect& rect, float radius, const Attributes& attrs);

        // Image drawing
        virtual Renderer& drawImage(Image* img, const Point& loc, const Attributes& attrs) = 0;
        virtual Renderer& drawImage(Image* img, const Rect& rect, const Attributes& attrs) = 0;
        virtual Renderer& drawImage(Image* img, const Quad& quad, const Attributes& attrs) = 0;

        // Drawing drawing  
        virtual Renderer& drawDrawing(const Drawing& drawing, const Point& loc, const Attributes& attrs) = 0;
        virtual Renderer& drawDrawing(const Drawing& drawing, const Rect& rect, const Attributes& attrs) = 0;

        // Text drawing
        virtual Renderer& drawText(const char* text, const Point& loc, const Attributes& attrs) = 0;
        virtual Renderer& drawText(const char* text, const Rect& rect, const Attributes& attrs) = 0;

        // Sphere drawing
        virtual Renderer& drawSphere(const Point& center, float radius, const Attributes& attrs) = 0;
    };

    inline Renderer& Renderer::drawVector(const Vector& v, const Attributes& attrs) {
        drawLine(Point(0, 0), Point(v.x, v.y), attrs);
        return *this;
    }

    inline Renderer& Renderer::drawCircle(const Point& center, float radius, const Attributes& attrs) {
        drawEllipse(center, radius, radius, attrs);
        return *this;
    }
    inline Renderer& Renderer::drawRoundedRect(const Rect& rect, float radius, const Attributes& attrs) {
        Attributes roundedAttrs = attrs;
        roundedAttrs.roundedCorners(radius);
        drawRect(rect, roundedAttrs);
        return *this;
    }

    inline Renderer& Renderer::drawBezier(const Point& from, const Point& control1, const Point& control2, const Point& to, const Attributes& attrs) {
        Spline bezierSpline(SPLINE_CUBIC_BEZIER);
        bezierSpline.addSegment(from, control1, control2, to);
        drawSpline(bezierSpline, attrs);
        return *this;
    }

} // end namespace pdg

#endif // PDG_RENDERER_H_INCLUDED
