// -----------------------------------------------
//  drawing.cpp
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

#include "pdg/sys/drawing.h"
#include "pdg/sys/port.h"
#include "pdg/sys/color.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"
#include "pdg/sys/image.h"
#include "pdg/sys/imagestrip.h"
#include "pdg/sys/attributes.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <stdexcept>

namespace pdg {

// Forward declarations for classes used in element data structures
class Spline;
class Polygon;
class Image;
class ImageStrip;
class Drawing;

// Forward declarations for element data structures
struct Element;
struct LineElement;
struct SplineElement;
struct ArcElement;
struct QuadElement;
struct PolygonElement;
struct EllipseElement;
struct ImageElement;
struct ImageStripElement;
struct DrawingElement;

// Helper functions for bounds calculation
Rect getElementBounds(const Element* element, ElementType type);
bool isPointInElement(const Element* element, ElementType type, const Point& point);
float distanceToLineSegment(const Point& point, const Point& lineStart, const Point& lineEnd);
bool isPointInSpline(const SplineElement* splineEl, const Point& point);

// Common properties for all drawing elements
struct Element {
    // the attributes of the element
    Attributes attrs;
    
    // Control points for editing (varies by element type)
    std::vector<Point> controlPoints;
    
    Element(const Attributes& attrsData) : attrs(attrsData) {}
};

// Specific element data structures
struct LineElement : public Element {
    Point from;
    Point to;
    
    LineElement(const Point& fromPoint, const Point& toPoint, const Attributes& attrsData) : 
        Element(attrsData), from(fromPoint), to(toPoint) {
        // Control points are the two endpoints
        controlPoints.push_back(from);
        controlPoints.push_back(to);
    }
};

struct SplineElement : public Element {
    Spline spline;
    
    SplineElement(class Spline&& splineData, const Attributes& attrsData) : 
        Element(attrsData), spline(std::move(splineData)) {
        // Extract control points from spline data
        int pointCount = spline.getPointCount();
        for (int i = 0; i < pointCount; i++) {
            controlPoints.push_back(spline.getPoint(i));
        }
    }
};

struct ArcElement : public Element {
    Point center;
    float xRadius;
    float yRadius;
    float startAngle;
    float endAngle;

    ArcElement(const Point& centerPoint, float xRad, float yRad, float startAngleData, float endAngleData, const Attributes& attrsData) : 
        Element(attrsData), center(centerPoint), xRadius(xRad), yRadius(yRad), startAngle(startAngleData), endAngle(endAngleData) {
        // Control points are the center and the two angles
        controlPoints.push_back(center);
        controlPoints.push_back(Point(center.x + xRadius * cos(startAngle), center.y + yRadius * sin(startAngle)));
        controlPoints.push_back(Point(center.x + xRadius * cos(endAngle), center.y + yRadius * sin(endAngle)));
    }
};

struct QuadElement : public Element {
    Quad quad;
    
    QuadElement(const Quad& quadData, const Attributes& attrsData) : 
        Element(attrsData), quad(quadData) {
        // Control points are the four corners
        for (int i = 0; i < 4; i++) {
            controlPoints.push_back(quad.points[i]);
        }
    }
};

struct PolygonElement : public Element {
    Polygon polygon;
    
    PolygonElement(Polygon&& polygonData, const Attributes& attrsData) : 
        Element(attrsData), polygon(std::move(polygonData)) {
        // Control points are the polygon vertices
        // TODO: Extract points from polygon
    }
};

struct EllipseElement : public Element {
    Point center;
    float xRadius;
    float yRadius;
    
    EllipseElement(const Point& centerPoint, float xRad, float yRad, const Attributes& attrsData) : 
        Element(attrsData), center(centerPoint), xRadius(xRad), yRadius(yRad) {
        // Control points for oval: center and 4 cardinal points
        controlPoints.push_back(center);
        controlPoints.push_back(Point(center.x - xRadius, center.y)); // left
        controlPoints.push_back(Point(center.x + xRadius, center.y)); // right
        controlPoints.push_back(Point(center.x, center.y - yRadius)); // top
        controlPoints.push_back(Point(center.x, center.y + yRadius)); // bottom
    }
};

struct ImageElement : public Element {
    Rect rect;
    Image* image;
    int numFrames;
    int frameNumber;
    
    ImageElement(const Rect& rectData, const Image& imageData, int frame, const Attributes& attrsData) : 
        Element(attrsData), rect(rectData), image(const_cast<Image*>(&imageData)) {
        frameNumber = frame;
        // Control points are the four corners of the rect
        controlPoints.push_back(rect.leftTop());
        controlPoints.push_back(rect.rightTop());
        controlPoints.push_back(rect.rightBottom());
        controlPoints.push_back(rect.leftBottom());
    }
};

struct DrawingElement : public Element {
    Rect rect;
    Drawing* drawing;
    
    DrawingElement(const Rect& rectData, const Drawing& drawingData, const Attributes& attrsData) : 
        Element(attrsData), rect(rectData), drawing(const_cast<Drawing*>(&drawingData)) {
        // Control points are the four corners of the rect
        controlPoints.push_back(rect.leftTop());
        controlPoints.push_back(rect.rightTop());
        controlPoints.push_back(rect.rightBottom());
        controlPoints.push_back(rect.leftBottom());
    }
};

// ================================
// Helper functions for bounds calculation and hit detection
// ================================

Rect getElementBounds(const Element* element, ElementType type) {
    if (!element) return Rect();
    
    switch (type) {
        case type_Line: {
            const LineElement* lineEl = static_cast<const LineElement*>(element);
            float minX = std::min(lineEl->from.x, lineEl->to.x);
            float maxX = std::max(lineEl->from.x, lineEl->to.x);
            float minY = std::min(lineEl->from.y, lineEl->to.y);
            float maxY = std::max(lineEl->from.y, lineEl->to.y);
            return Rect(minX, minY, maxX, maxY);
        }
        case type_Rect: {
            const QuadElement* quadEl = static_cast<const QuadElement*>(element);
            return quadEl->quad.getBounds();
        }
        case type_Ellipse: {
            const EllipseElement* ellipseEl = static_cast<const EllipseElement*>(element);
            return Rect(ellipseEl->center.x - ellipseEl->xRadius, 
                       ellipseEl->center.y - ellipseEl->yRadius,
                       ellipseEl->center.x + ellipseEl->xRadius,
                       ellipseEl->center.y + ellipseEl->yRadius);
        }
        case type_Polygon: {
            const PolygonElement* polyEl = static_cast<const PolygonElement*>(element);
            return polyEl->polygon.getBounds();
        }
        case type_Spline: {
            const SplineElement* splineEl = static_cast<const SplineElement*>(element);
            return splineEl->spline.getBounds();
        }
        case type_Image: {
            const ImageElement* imgEl = static_cast<const ImageElement*>(element);
            return imgEl->rect;
        }
        case type_Drawing: {
            const DrawingElement* drawEl = static_cast<const DrawingElement*>(element);
            return drawEl->rect;
        }
        default:
            return Rect();
    }
}

bool isPointInElement(const Element* element, ElementType type, const Point& point) {
    if (!element) return false;
    
    switch (type) {
        case type_Line: {
            const LineElement* lineEl = static_cast<const LineElement*>(element);
            // Calculate distance from point to line segment
            float distance = distanceToLineSegment(point, lineEl->from, lineEl->to);
            
            // Consider line thickness for hit detection
            // Use a reasonable hit tolerance (could be made configurable)
            float hitTolerance = 2.0f; // 2 pixels base tolerance
            
            // If the line has thickness specified in attributes, use that
            if (lineEl->attrs.getLineThickness() > 0) {
                hitTolerance = std::max(hitTolerance, lineEl->attrs.getLineThickness() / 2.0f);
            }
            
            return distance <= hitTolerance;
        }
        case type_Rect: {
            const QuadElement* quadEl = static_cast<const QuadElement*>(element);
            return quadEl->quad.contains(point);
        }
        case type_Ellipse: {
            const EllipseElement* ellipseEl = static_cast<const EllipseElement*>(element);
            float dx = point.x - ellipseEl->center.x;
            float dy = point.y - ellipseEl->center.y;
            return (dx * dx) / (ellipseEl->xRadius * ellipseEl->xRadius) + 
                   (dy * dy) / (ellipseEl->yRadius * ellipseEl->yRadius) <= 1.0f;
        }
        case type_Polygon: {
            const PolygonElement* polyEl = static_cast<const PolygonElement*>(element);
            return polyEl->polygon.contains(point);
        }
        case type_Spline: {
            const SplineElement* splineEl = static_cast<const SplineElement*>(element);
            return isPointInSpline(splineEl, point);
        }
        case type_Image:
        case type_Drawing: {
            // For images and drawings, use the rect bounds
            Rect bounds = getElementBounds(element, type);
            return bounds.contains(point);
        }
        default:
            return false;
    }
}

float distanceToLineSegment(const Point& point, const Point& lineStart, const Point& lineEnd) {
    // Calculate the distance from a point to a line segment
    // Using the formula for distance from point to line segment
    
    float A = point.x - lineStart.x;
    float B = point.y - lineStart.y;
    float C = lineEnd.x - lineStart.x;
    float D = lineEnd.y - lineStart.y;
    
    float dot = A * C + B * D;
    float lenSq = C * C + D * D;
    
    if (lenSq == 0) {
        // Line segment is actually a point
        return sqrt(A * A + B * B);
    }
    
    float param = dot / lenSq;
    
    float xx, yy;
    
    if (param < 0) {
        // Closest point is lineStart
        xx = lineStart.x;
        yy = lineStart.y;
    } else if (param > 1) {
        // Closest point is lineEnd
        xx = lineEnd.x;
        yy = lineEnd.y;
    } else {
        // Closest point is on the line segment
        xx = lineStart.x + param * C;
        yy = lineStart.y + param * D;
    }
    
    float dx = point.x - xx;
    float dy = point.y - yy;
    return sqrt(dx * dx + dy * dy);
}

bool isPointInSpline(const SplineElement* splineEl, const Point& point) {
    if (!splineEl) return false;
    
    const Spline& spline = splineEl->spline;
    float maxU = spline.getMaxU();
    int segmentCount = (int)maxU;
    if (segmentCount == 0) return false;
    
    // First, do a quick bounds check for elimination
    Rect bounds = getElementBounds(static_cast<const Element*>(splineEl), type_Spline);
    if (!bounds.contains(point)) {
        return false;
    }
    
    // Consider line thickness for hit detection
    float hitTolerance = 2.0f; // 2 pixels base tolerance
    
    // If the spline has thickness specified in attributes, use that
    if (splineEl->attrs.getLineThickness() > 0) {
        hitTolerance = std::max(hitTolerance, splineEl->attrs.getLineThickness() / 2.0f);
    }
    
    // Sample points along each segment and check distance to line segments
    const int samplesPerSegment = 10; // Number of sample points per segment
    
    for (int segment = 0; segment < segmentCount; segment++) {
        float segmentStart = (float)segment;
        float segmentEnd = (float)(segment + 1);
        
        // Sample points along this segment
        for (int i = 0; i < samplesPerSegment; i++) {
            float u1 = segmentStart + (float)i / (float)samplesPerSegment;
            float u2 = segmentStart + (float)(i + 1) / (float)samplesPerSegment;
            
            // Clamp to valid range
            if (u2 > segmentEnd) u2 = segmentEnd;
            
            Point p1 = spline.getFirstOrder(u1);
            Point p2 = spline.getFirstOrder(u2);
            
            // Check distance from point to this line segment
            float distance = distanceToLineSegment(point, p1, p2);
            if (distance <= hitTolerance) {
                return true;
            }
        }
    }
    
    return false;
}

// ================================
// DrawingImpl methods
// ================================

class DrawingImpl : public Drawing {
public:
    virtual ElementRef* addLine(const Point& from, const Point& to, const Attributes& attrs);
    virtual ElementRef* addSpline(Spline&& spline, const Attributes& attrs);
    virtual ElementRef* addRect(const Rect& rect, const Attributes& attrs);
    virtual ElementRef* addQuad(const Quad& quad, const Attributes& attrs);
    virtual ElementRef* addPolygon(Polygon&& polygon, const Attributes& attrs);
    virtual ElementRef* addEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs);
    virtual ElementRef* addArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs);

    virtual ElementRef* addImage(const Rect& rect, const Image& image, const Attributes& attrs);
    virtual ElementRef* addImageStrip(const Rect& rect, const ImageStrip& imageStrip, const Attributes& attrs);
    virtual ElementRef* addDrawing(const Rect& rect, const Drawing& drawing, const Attributes& attrs);

    virtual size_t getElementCount() const;
    virtual ElementRef* getElement(size_t index) const;
    virtual ElementRef* getElementHitBy(const Point& point) const;  // returns the index of the element hit by the point, or -1 if no element is hit

    // Geometric operations
    virtual Rect getBounds() const;
    virtual Point centerPoint() const;
    virtual bool empty() const;

  #ifndef PDG_NO_GUI 
    // drawing operations
    virtual void draw(Port* port);
    virtual void draw(Port* port, const Rect& rect);
    virtual void draw(Port* port, const Quad& quad);
    virtual void draw(Port* port, const RotatedRect& rr);
  #endif // PDG_NO_GUI

    ElementType getElementType(size_t index) const;

    const std::vector<Point>& getElementControlPoints(size_t index) const;
    const Point& getElementControlPoint(size_t index, size_t controlPointIndex) const;
    void changeElementControlPointPosition(size_t index, size_t controlPointIndex, const Point& controlPoint);

    void moveElement(size_t index, size_t newIndex);
    void removeElement(size_t index);

    void clearElements();

    void getAttributes(size_t index, Attributes& attrs) const;
    void setAttributes(size_t index, const Attributes& attrs);

    DrawingImpl();
    virtual ~DrawingImpl();

    std::vector<std::pair<ElementType, Element*>> elements;
    
    // Bounds caching
    mutable Rect mCachedBounds;
    mutable bool mBoundsDirty;
    
    void invalidateBounds() const { mBoundsDirty = true; }
};

Drawing* Drawing::create() {
    return new DrawingImpl();
}

// Drawing class implementation
DrawingImpl::DrawingImpl() : Drawing(), mBoundsDirty(true) {
    // Constructor - initialize bounds cache as dirty
}

DrawingImpl::~DrawingImpl() {
    clearElements();
}

// Add methods for each element type
ElementRef* DrawingImpl::addLine(const Point& from, const Point& to, const Attributes& attrs) {
    LineElement* element = new LineElement(from, to, attrs);
    elements.push_back(std::make_pair(type_Line, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addSpline(Spline&& spline, const Attributes& attrs) {
    SplineElement* element = new SplineElement(std::move(spline), attrs);
    elements.push_back(std::make_pair(type_Spline, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addRect(const Rect& rect, const Attributes& attrs) {
    QuadElement* element = new QuadElement(Quad(rect), attrs);
    elements.push_back(std::make_pair(type_Rect, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addQuad(const Quad& quad, const Attributes& attrs) {
    QuadElement* element = new QuadElement(quad, attrs);
    elements.push_back(std::make_pair(type_Quad, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addArc(const Point& center, float xRadius, float yRadius, float startAngle, float endAngle, const Attributes& attrs) {
    ArcElement* element = new ArcElement(center, xRadius, yRadius, startAngle, endAngle, attrs);
    elements.push_back(std::make_pair(type_Arc, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addEllipse(const Point& center, float xRadius, float yRadius, const Attributes& attrs) {
    EllipseElement* element = new EllipseElement(center, xRadius, yRadius, attrs);
    elements.push_back(std::make_pair(type_Ellipse, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addPolygon(Polygon&& polygon, const Attributes& attrs) {
    PolygonElement* element = new PolygonElement(std::move(polygon), attrs);
    elements.push_back(std::make_pair(type_Polygon, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}


ElementRef* DrawingImpl::addImage(const Rect& rect, const Image& image, const Attributes& attrs) {
    ImageElement* element = new ImageElement(rect, image, 0, attrs);
    elements.push_back(std::make_pair(type_Image, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef*  DrawingImpl::addImageStrip(const Rect& rect, const ImageStrip& imageStrip, const Attributes& attrs) {
    ImageElement* element = new ImageElement(rect, dynamic_cast<const Image&>(imageStrip), 0, attrs);
    elements.push_back(std::make_pair(type_ImageStrip, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}

ElementRef* DrawingImpl::addDrawing(const Rect& rect, const Drawing& drawing, const Attributes& attrs) {
    DrawingElement* element = new DrawingElement(rect, drawing, attrs);
    elements.push_back(std::make_pair(type_Drawing, element));
    invalidateBounds();
    return new ElementRef(this, elements.size() - 1);
}


ElementRef* DrawingImpl::getElementHitBy(const Point& point) const {
    // Check elements from back to front (last added is on top)
    for (int i = elements.size() - 1; i >= 0; i--) {
        ElementType type = elements[i].first;
        Element* element = static_cast<Element*>(elements[i].second);
        
        if (!element) continue;
        
        // Check if point is within the element
        if (isPointInElement(element, type, point)) {
            return new ElementRef(const_cast<DrawingImpl*>(this), i);
        }
    }

    return nullptr;
}

size_t DrawingImpl::getElementCount() const {
    return elements.size();
}

ElementRef* DrawingImpl::getElement(size_t index) const {
    if (index >= elements.size()) {
        throw std::out_of_range("Drawing::getElement: index out of range");
    }
    return new ElementRef(const_cast<DrawingImpl*>(this), index);
}

ElementType DrawingImpl::getElementType(size_t index) const {
    if (index >= elements.size()) return static_cast<ElementType>(0);
    return elements[index].first;
}

const std::vector<Point>& DrawingImpl::getElementControlPoints(size_t index) const {
    static std::vector<Point> emptyPoints;
    if (index >= elements.size()) return emptyPoints;
    
    Element* element = static_cast<Element*>(elements[index].second);
    if (element) {
        return element->controlPoints;
    }
    return emptyPoints;
}

const Point& DrawingImpl::getElementControlPoint(size_t index, size_t controlPointIndex) const {
    if (index >= elements.size()) {
        throw std::out_of_range("Drawing::getElementControlPoint: element index out of range");
    }
    
    Element* element = static_cast<Element*>(elements[index].second);
    if (!element) {
        throw std::out_of_range("Drawing::getElementControlPoint: element is null");
    }
    
    if (controlPointIndex >= element->controlPoints.size()) {
        throw std::out_of_range("Drawing::getElementControlPoint: control point index out of range");
    }
    
    return element->controlPoints[controlPointIndex];
}

void DrawingImpl::changeElementControlPointPosition(size_t index, size_t controlPointIndex, const Point& controlPoint) {
    if (index >= elements.size()) return;
    
    Element* element = static_cast<Element*>(elements[index].second);
    if (element && controlPointIndex < element->controlPoints.size()) {
        element->controlPoints[controlPointIndex] = controlPoint;
        invalidateBounds();
        
        // Update the actual element data based on type
        ElementType type = elements[index].first;
        switch (type) {
            case type_Line: {
                LineElement* lineElement = static_cast<LineElement*>(element);
                if (controlPointIndex == 0) lineElement->from = controlPoint;
                else if (controlPointIndex == 1) lineElement->to = controlPoint;
                break;
            }
             case type_Quad: {
                QuadElement* quadElement = static_cast<QuadElement*>(element);
                if (controlPointIndex < 4) {
                    quadElement->quad.points[controlPointIndex] = controlPoint;
                }
                break;
            }
            case type_Ellipse: {
                EllipseElement* ellipseElement = static_cast<EllipseElement*>(element);
                if (controlPointIndex == 0) {
                    // Moving center point
                    Point offset = controlPoint - ellipseElement->center;
                    ellipseElement->center = controlPoint;
                    // Update other control points
                    for (size_t i = 1; i < element->controlPoints.size(); i++) {
                        element->controlPoints[i] += offset;
                    }
                } else if (controlPointIndex >= 1 && controlPointIndex <= 4) {
                    // Moving a radius point
                    element->controlPoints[controlPointIndex] = controlPoint;
                    // Recalculate radii
                    float leftDist = fabs(controlPoint.x - ellipseElement->center.x);
                    float rightDist = fabs(controlPoint.x - ellipseElement->center.x);
                    float topDist = fabs(controlPoint.y - ellipseElement->center.y);
                    float bottomDist = fabs(controlPoint.y - ellipseElement->center.y);
                    
                    if (controlPointIndex == 1 || controlPointIndex == 2) {
                        ellipseElement->xRadius = std::max(leftDist, rightDist);
                    }
                    if (controlPointIndex == 3 || controlPointIndex == 4) {
                        ellipseElement->yRadius = std::max(topDist, bottomDist);
                    }
                }
                break;
            }
            case type_Image:
            case type_ImageStrip:
            case type_Drawing: {
                // Update rect corners for these types
                // TODO: Implement rect corner updates
                break;
            }
            default:
                break;
        }
    }
}

void DrawingImpl::moveElement(size_t index, size_t newIndex) {
    if (index >= elements.size() || newIndex >= elements.size()) return;
    
    auto element = elements[index];
    elements.erase(elements.begin() + index);
    elements.insert(elements.begin() + newIndex, element);
    // Note: Moving elements doesn't change bounds, so no invalidation needed
}

void DrawingImpl::removeElement(size_t index) {
    if (index >= elements.size()) return;
    
    // Delete the element data
    delete static_cast<Element*>(elements[index].second);
    elements.erase(elements.begin() + index);
    invalidateBounds();
}

void DrawingImpl::clearElements() {
    for (auto& element : elements) {
        delete static_cast<Element*>(element.second);
    }
    elements.clear();
    invalidateBounds();
}

void DrawingImpl::getAttributes(size_t index, Attributes& attrs) const {
    if (index >= elements.size()) return;
    attrs = static_cast<Element*>(elements[index].second)->attrs;
}

void DrawingImpl::setAttributes(size_t index, const Attributes& attrs) {
    if (index >= elements.size()) return;
    static_cast<Element*>(elements[index].second)->attrs = attrs;
}

Rect DrawingImpl::getBounds() const {
    if (elements.empty()) {
        mCachedBounds = Rect();
        mBoundsDirty = false;
        return mCachedBounds;
    }
    
    // Return cached bounds if they're still valid
    if (!mBoundsDirty) {
        return mCachedBounds;
    }
    
    // Recalculate bounds
    Rect bounds;
    bool first = true;
    
    for (const auto& element : elements) {
        Rect elementBounds = getElementBounds(static_cast<Element*>(element.second), element.first);
        if (elementBounds.empty()) continue;
        if (first) {
            bounds = elementBounds;
            first = false;
        } else {
            bounds = bounds.unionWith(elementBounds);
        }
    }
    
    // Cache the result
    mCachedBounds = bounds;
    mBoundsDirty = false;
    
    return bounds;
}

Point DrawingImpl::centerPoint() const {
    return getBounds().centerPoint();
}

bool DrawingImpl::empty() const {
    return elements.empty();
}

#ifndef PDG_NO_GUI

// Drawing methods
void DrawingImpl::draw(Port* port) {
    if (!port) return;
    
    for (const auto& element : elements) {
        Element* elementData = static_cast<Element*>(element.second);
        if (!elementData) continue;
        
        switch (element.first) {
            case type_Line: {
                LineElement* lineElement = static_cast<LineElement*>(elementData);
                port->drawLine(lineElement->from, lineElement->to, elementData->attrs);
                break;
            }
            case type_Spline: {
                SplineElement* splineElement = static_cast<SplineElement*>(elementData);
                port->drawSpline(splineElement->spline, elementData->attrs);
                break;
            }
            case type_Rect:
            case type_Quad: {
                QuadElement* quadElement = static_cast<QuadElement*>(elementData);
                port->drawQuad(quadElement->quad, elementData->attrs);
                break;
            }
            case type_Arc: {
                ArcElement* arcElement = static_cast<ArcElement*>(elementData);
                port->drawArc(arcElement->center, arcElement->xRadius, arcElement->yRadius, arcElement->startAngle, arcElement->endAngle, elementData->attrs);
                break;
            }
            case type_Polygon: {
                PolygonElement* polygonElement = static_cast<PolygonElement*>(elementData);
                port->drawPolygon(polygonElement->polygon, elementData->attrs);
                break;
            }
            case type_Ellipse: {
                EllipseElement* ellipseElement = static_cast<EllipseElement*>(elementData);
                port->drawEllipse(ellipseElement->center, ellipseElement->xRadius, ellipseElement->yRadius, elementData->attrs);
                break;
            }
            case type_ImageStrip:
            case type_Image: {
                ImageElement* imageElement = static_cast<ImageElement*>(elementData);
                //port->drawImage(imageElement->image, imageElement->transformedBounds);
                break;
            }
            case type_Drawing: {
                DrawingElement* drawingElement = static_cast<DrawingElement*>(elementData);
                //drawingElement->drawing->draw(port, drawingElement->transformedBounds);
                break;
            }
        }
    }
}

void DrawingImpl::draw(Port* port, const Rect& rect) {
    if (!port) return;
    
    // Save current clip rect
    Rect originalClip = port->getClipRect();
    
    // Set clip rect to intersection of original and drawing rect
    Rect clipRect = originalClip.intersection(rect);
    port->setClipRect(clipRect);
    
    // Draw the drawing
    draw(port);
    
    // Restore original clip rect
    port->setClipRect(originalClip);
}

void DrawingImpl::draw(Port* port, const Quad& quad) {
    if (!port) return;
    
    // Convert quad to rect bounds for clipping
    Rect bounds = quad.getBounds();
    draw(port, bounds);
}

void DrawingImpl::draw(Port* port, const RotatedRect& rr) {
    if (!port) return;
    
    // Convert rotated rect to quad and use quad drawing
    Quad quad = rr.getQuad();
    draw(port, quad);
}

#endif // PDG_NO_GUI

// ================================
// ElementRef methods
// ================================

ElementType ElementRef::type() const {
    return static_cast<DrawingImpl*>(drawing)->getElementType(index);
}
const std::vector<Point>& ElementRef::getControlPoints() const {
    return static_cast<DrawingImpl*>(drawing)->getElementControlPoints(index);
}
void ElementRef::getAttributes(Attributes& attrs) const {
    static_cast<DrawingImpl*>(drawing)->getAttributes(index, attrs);
}
void ElementRef::setAttributes(const Attributes& attrs) {
    static_cast<DrawingImpl*>(drawing)->setAttributes(index, attrs);
}
const Point& ElementRef::getControlPoint(int controlPointIndex) const {
    return static_cast<DrawingImpl*>(drawing)->getElementControlPoint(index, controlPointIndex);
}
void ElementRef::changeControlPoint(int controlPointIndex, const Point& controlPoint) {
    static_cast<DrawingImpl*>(drawing)->changeElementControlPointPosition(index, controlPointIndex, controlPoint);
}
void ElementRef::moveForward() {
    static_cast<DrawingImpl*>(drawing)->moveElement(index, index + 1);
}
void ElementRef::moveBackward() {
    static_cast<DrawingImpl*>(drawing)->moveElement(index, index - 1);
}
void ElementRef::moveToFront() {
    static_cast<DrawingImpl*>(drawing)->moveElement(index, static_cast<DrawingImpl*>(drawing)->getElementCount() - 1);
}
void ElementRef::moveToBack() {
    static_cast<DrawingImpl*>(drawing)->moveElement(index, 0);
}
void ElementRef::remove() {
    static_cast<DrawingImpl*>(drawing)->removeElement(index);
}

} // end namespace pdg