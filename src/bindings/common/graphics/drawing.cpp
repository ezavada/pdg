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

WRAPPER_INITIALIZER_IMPL_CUSTOM(ElementRef,
    OBJECT_SAVE(cppObj->mElementRefScriptObj, obj)
)
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
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
    for (size_t i = 0; i < points.size(); i++) {
        Point point = points[i];
        JSObjectSetPropertyAtIndex(ctx, result, (unsigned)i, POINT2VAL(point), exception);
    }
    %#else
    v8::Local<v8::Array> result = v8::Array::New(isolate, points.size());
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    for (size_t i = 0; i < points.size(); i++) {
        Point point = points[i]; // Create a non-const copy
        result->Set(context, i, POINT2VAL(point)).ToChecked();
    }
    %#endif

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
    REQUIRE_CPP_OBJECT_ARG(1, attrs, Attributes);
    self->setAttributes(*attrs);
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
    REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
    ElementRef* result = self->addLine(from, to, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddSpline)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Spline] spline, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, spline, Spline);
    REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
    ElementRef* result = self->addSpline(std::move(*spline), *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddRect)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
    ElementRef* result = self->addRect(rect, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddQuad)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Quad] quad, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_QUAD_ARG(1, quad);
    REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
    ElementRef* result = self->addQuad(quad, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddPolygon)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Polygon] polygon, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, polygon, Polygon);
    REQUIRE_CPP_OBJECT_ARG(2, attrs, Attributes);
    ElementRef* result = self->addPolygon(std::move(*polygon), *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddEllipse)
    METHOD_SIGNATURE("", [object ElementRef], 4, ([object Point] center, number xRadius, number yRadius, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_NUMBER_ARG(2, xRadius);
    REQUIRE_NUMBER_ARG(3, yRadius);
    REQUIRE_CPP_OBJECT_ARG(4, attrs, Attributes);
    ElementRef* result = self->addEllipse(center, xRadius, yRadius, *attrs);
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
    REQUIRE_CPP_OBJECT_ARG(6, attrs, Attributes);
    ElementRef* result = self->addArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImage)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Image] image, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, image, Image);
    REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
    ElementRef* result = self->addImage(rect, *image, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImageStrip)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object ImageStrip] imageStrip, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, imageStrip, ImageStrip);
    REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
    ElementRef* result = self->addImageStrip(rect, *imageStrip, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddDrawing)
    METHOD_SIGNATURE("", [object ElementRef], 2, ([object Rect] rect, [object Drawing] drawing, [object Attributes] attrs)); 
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, drawing, Drawing);
    REQUIRE_CPP_OBJECT_ARG(3, attrs, Attributes);
    ElementRef* result = self->addDrawing(rect, *drawing, *attrs);
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
    REQUIRE_CPP_OBJECT_ARG(1, port, Port);
    
    // For now, just draw without transformation
    // TODO: Add support for transformation arguments
    self->draw(port);
    NO_RETURN;
    END

%#endif // !PDG_NO_GUI

} // namespace pdg
