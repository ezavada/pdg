// -----------------------------------------------
// drawing.cpp
//
// JavaScript bindings for Drawing and ElementRef classes
//
// Written by AI Assistant, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
//
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

// ===== ElementRef Bindings =====

WRAPPER_INITIALIZER_IMPL(ElementRef)
    EXPORT_CLASS_SYMBOLS("ElementRef", ElementRef, , ,
        // method section
        HAS_METHOD(ElementRef, "type", Type)
        HAS_METHOD(ElementRef, "getControlPoints", GetControlPoints)
        HAS_METHOD(ElementRef, "getControlPoint", GetControlPoint)
        HAS_METHOD(ElementRef, "changeControlPoint", ChangeControlPoint)
        HAS_METHOD(ElementRef, "getAttributes", GetAttributes)
        HAS_METHOD(ElementRef, "setAttributes", SetAttributes)
        HAS_METHOD(ElementRef, "moveForward", MoveForward)
        HAS_METHOD(ElementRef, "moveBackward", MoveBackward)
        HAS_METHOD(ElementRef, "moveToFront", MoveToFront)
        HAS_METHOD(ElementRef, "moveToBack", MoveToBack)
        HAS_METHOD(ElementRef, "remove", Remove)
    );
    END

CPP_MANAGED_CONSTRUCTOR_IMPL(ElementRef)
    SETUP_NON_SCRIPT_CALL;
    
    // ElementRef should not be constructed directly by JavaScript
    THROW_TYPE_ERR("ElementRef cannot be constructed directly. Use Drawing methods to get ElementRef objects.");
    return nullptr;
END

CLEANUP_IMPL(ElementRef)

METHOD_IMPL(ElementRef, Type)
    METHOD_SIGNATURE("", [number uint], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    ElementType type = self->type();
    RETURN_UINT32(static_cast<uint32_t>(type));
    END

METHOD_IMPL(ElementRef, GetControlPoints)
    METHOD_SIGNATURE("", [array], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    const std::vector<Point>& points = self->getControlPoints();
    
    // Create JavaScript array of Point objects
    v8::Local<v8::Array> result = v8::Array::New(isolate, points.size());
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    for (size_t i = 0; i < points.size(); i++) {
        Point point = points[i]; // Create a non-const copy
        result->Set(context, i, POINT2VAL(point)).ToChecked();
    }

    RETURN_OBJECT(result);
    END

METHOD_IMPL(ElementRef, GetControlPoint)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] controlPointIndex)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, controlPointIndex);
    try {
        const Point& point = self->getControlPoint(controlPointIndex);
        Point pointCopy = point; // Create a non-const copy
        RETURN_POINT(pointCopy);
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("ElementRef::getControlPoint: index out of range");
    }
    END

METHOD_IMPL(ElementRef, ChangeControlPoint)
    METHOD_SIGNATURE("", undefined, 2, ([number uint] controlPointIndex, [object Point] controlPoint)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_UINT32_ARG(1, controlPointIndex);
    REQUIRE_POINT_ARG(2, controlPoint);
    try {
        self->changeControlPoint(controlPointIndex, controlPoint);
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("ElementRef::changeControlPoint: index out of range");
    }
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, GetAttributes)
    METHOD_SIGNATURE("", [object Attributes], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Attributes* attrsPtr = new Attributes();
    self->getAttributes(*attrsPtr);
    RETURN_CPP_OBJECT(attrsPtr, Attributes);
    END

METHOD_IMPL(ElementRef, SetAttributes)
    METHOD_SIGNATURE("", undefined, 1, ([object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addLine must be called with a valid Attributes object");
        return;
    }
    self->setAttributes(*attrsPtr);
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, MoveForward)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->moveForward();
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, MoveBackward)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->moveBackward();
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, MoveToFront)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->moveToFront();
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, MoveToBack)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->moveToBack();
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, Remove)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->remove();
    NO_RETURN;
    END

// ===== Drawing Bindings =====

WRAPPER_INITIALIZER_IMPL_CUSTOM(Drawing,
    OBJECT_SAVE(cppObj->mDrawingScriptObj, obj)
)
    EXPORT_CLASS_SYMBOLS("Drawing", Drawing, , ,
        // method section
        HAS_METHOD(Drawing, "addLine", AddLine)
        HAS_METHOD(Drawing, "addSpline", AddSpline)
        HAS_METHOD(Drawing, "addRect", AddRect)
        HAS_METHOD(Drawing, "addArc", AddArc)
        HAS_METHOD(Drawing, "addQuad", AddQuad)
        HAS_METHOD(Drawing, "addPolygon", AddPolygon)
        HAS_METHOD(Drawing, "addEllipse", AddEllipse)
        HAS_METHOD(Drawing, "addImage", AddImage)
        HAS_METHOD(Drawing, "addImageStrip", AddImageStrip)
        HAS_METHOD(Drawing, "addDrawing", AddDrawing)
        HAS_METHOD(Drawing, "getElementCount", GetElementCount)
        HAS_METHOD(Drawing, "getElement", GetElement)
        HAS_METHOD(Drawing, "getElementHitBy", GetElementHitBy)
        HAS_METHOD(Drawing, "getBounds", GetBounds)
        HAS_METHOD(Drawing, "centerPoint", CenterPoint)
        HAS_METHOD(Drawing, "empty", Empty)
    %#ifndef PDG_NO_GUI CR
        HAS_METHOD(Drawing, "draw", Draw)
    %#endif // !PDG_NO_GUI
        CR
    );
    END

CPP_MANAGED_CONSTRUCTOR_IMPL(Drawing)
    SETUP_NON_SCRIPT_CALL;
    
    // Drawing should not be constructed directly by JavaScript, use Drawing.create() instead
    THROW_TYPE_ERR("Drawing cannot be constructed directly. Use Drawing.create() to create a new Drawing.");
    return nullptr;
END

CLEANUP_IMPL(Drawing)

FUNCTION_IMPL(CreateDrawing)
    METHOD_SIGNATURE("", [object Drawing], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Drawing* drawing = Drawing::create();
    RETURN_NEW_CPP_OBJECT(drawing, Drawing);
    END

METHOD_IMPL(Drawing, AddLine)
    METHOD_SIGNATURE("", [object ElementRef], 3, ([object Point] from, [object Point] to, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_POINT_ARG(1, from);
    REQUIRE_POINT_ARG(2, to);
    REQUIRE_OBJECT_ARG(3, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addLine must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addLine(from, to, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddSpline)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Spline] spline, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_OBJECT_ARG(1, spline);
    SplineWrap* splineWrapper = static_cast<SplineWrap*>(OBJECT_PRIVATE_DATA(spline));
    Spline* splinePtr = splineWrapper->getCppObject();
    if (!splinePtr) {
        THROW_TYPE_ERR("addSpline must be called with a valid Spline object");
        return;
    }
    REQUIRE_OBJECT_ARG(2, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addSpline must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addSpline(std::move(*splinePtr), *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddRect)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_OBJECT_ARG(2, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addRect must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addRect(rect, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddQuad)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Quad] quad, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_QUAD_ARG(1, quad);
    REQUIRE_OBJECT_ARG(2, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addQuad must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addQuad(quad, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddPolygon)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Polygon] polygon, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_OBJECT_ARG(1, polygon);
    PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(OBJECT_PRIVATE_DATA(polygon));
    Polygon* polygonPtr = polygonWrapper->getCppObject();
    if (!polygonPtr) {
        THROW_TYPE_ERR("addPolygon must be called with a valid Polygon object");
        return;
    }
    REQUIRE_OBJECT_ARG(2, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addPolygon must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addPolygon(std::move(*polygonPtr), *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddEllipse)
    METHOD_SIGNATURE("", [object ElementRef], 4, ([object Point] center, number xRadius, number yRadius, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_NUMBER_ARG(2, xRadius);
    REQUIRE_NUMBER_ARG(3, yRadius);
    REQUIRE_OBJECT_ARG(4, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addEllipse must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addEllipse(center, xRadius, yRadius, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddArc)
    METHOD_SIGNATURE("", [object ElementRef], 6, ([object Point] center, number xRadius, number yRadius, number startAngle, number endAngle, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(6);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_NUMBER_ARG(2, xRadius);
    REQUIRE_NUMBER_ARG(3, yRadius);
    REQUIRE_NUMBER_ARG(4, startAngle);
    REQUIRE_NUMBER_ARG(5, endAngle);
    REQUIRE_OBJECT_ARG(6, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addArc must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addArc(center, xRadius, yRadius, startAngle, endAngle, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImage)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Image] image, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_OBJECT_ARG(2, image);
    ImageWrap* imageWrapper = static_cast<ImageWrap*>(OBJECT_PRIVATE_DATA(image));
    Image* imagePtr = imageWrapper->getCppObject();
    if (!imagePtr) {
        THROW_TYPE_ERR("addImage must be called with a valid Image object");
        return;
    }
    REQUIRE_OBJECT_ARG(3, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addImage must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addImage(rect, *imagePtr, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImageStrip)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object ImageStrip] imageStrip, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_OBJECT_ARG(2, imageStrip);
    ImageStripWrap* imageStripWrapper = static_cast<ImageStripWrap*>(OBJECT_PRIVATE_DATA(imageStrip));
    ImageStrip* imageStripPtr = imageStripWrapper->getCppObject();
    if (!imageStripPtr) {
        THROW_TYPE_ERR("addImageStrip must be called with a valid ImageStrip object");
        return;
    }
    REQUIRE_OBJECT_ARG(3, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addImageStrip must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addImageStrip(rect, *imageStripPtr, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddDrawing)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Drawing] drawing, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_OBJECT_ARG(2, drawing);
    DrawingWrap* drawingWrapper = static_cast<DrawingWrap*>(OBJECT_PRIVATE_DATA(drawing));
    Drawing* drawingPtr = drawingWrapper->getCppObject();
    if (!drawingPtr) {
        THROW_TYPE_ERR("addDrawing must be called with a valid Drawing object");
        return;
    }
    REQUIRE_OBJECT_ARG(3, attrs);
    AttributesWrap* attrsWrapper = static_cast<AttributesWrap*>(OBJECT_PRIVATE_DATA(attrs));
    Attributes* attrsPtr = attrsWrapper->getCppObject();
    if (!attrsPtr) {
        THROW_TYPE_ERR("addDrawing must be called with a valid Attributes object");
        return;
    }
    ElementRef* result = self->addDrawing(rect, *drawingPtr, *attrsPtr);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, GetElementCount)
    METHOD_SIGNATURE("", [number uint], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    size_t count = self->getElementCount();
    RETURN_UINT32(count);
    END

METHOD_IMPL(Drawing, GetElement)
    METHOD_SIGNATURE("", [object ElementRef], 1, ([number uint] index)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, index);
    try {
        ElementRef* result = self->getElement(index);
        RETURN_CPP_OBJECT(result, ElementRef);
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("Drawing::getElement: index out of range");
    }
    END

METHOD_IMPL(Drawing, GetElementHitBy)
    METHOD_SIGNATURE("", [object ElementRef], 1, ([object Point] point)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, point);
    ElementRef* result = self->getElementHitBy(point);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, GetBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Rect bounds = self->getBounds();
    RETURN_RECT(bounds);
    END

METHOD_IMPL(Drawing, CenterPoint)
    METHOD_SIGNATURE("", [object Point], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Point center = self->centerPoint();
    RETURN_POINT(center);
    END

METHOD_IMPL(Drawing, Empty)
    METHOD_SIGNATURE("", [boolean], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    bool empty = self->empty();
    RETURN_BOOL(empty);
    END

%#ifndef PDG_NO_GUI

METHOD_IMPL(Drawing, Draw)
    METHOD_SIGNATURE("", undefined, 1, ([object Port] port)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, port);
    PortWrap* portWrapper = static_cast<PortWrap*>(OBJECT_PRIVATE_DATA(port));
    Port* portPtr = portWrapper->getCppObject();
    if (!portPtr) {
        THROW_TYPE_ERR("draw must be called with a valid Port object");
        return;
    }
    
    // For now, just draw without transformation
    // TODO: Add support for transformation arguments
    self->draw(portPtr);
    NO_RETURN;
    END

%#endif // !PDG_NO_GUI

} // namespace pdg
