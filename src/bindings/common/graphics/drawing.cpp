// -----------------------------------------------
// drawing.cpp
//
// Class-specific JavaScript bindings.
//
// Written by AI Assistant, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
//
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

// ===== Drawing Bindings =====

WRAPPER_INITIALIZER_IMPL_CUSTOM(Drawing,
    OBJECT_SAVE(cppObj->mDrawingScriptObj, obj)
)
    EXPORT_CLASS_SYMBOLS("Drawing", Drawing, , ,
        // method section
        HAS_METHOD(Drawing, "addText", AddText)
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
    METHOD_SIGNATURE("", [object Drawing*], 0, ());
    REQUIRE_ARG_COUNT(0);
    Drawing* drawing = Drawing::create();
    RETURN_NEW_CPP_OBJECT(drawing, Drawing);
    END

METHOD_IMPL(Drawing, AddText)
    METHOD_SIGNATURE("Add owned UTF-8 text in a local rectangle.", [object ElementRef*], 3, (string text, [object Rect const&] rect, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(3);REQUIRE_STRING_ARG(1,text);REQUIRE_RECT_ARG(2,rect);REQUIRE_ATTRIBUTES_ARG(3,attrs);
    try {auto* result=self->addText(text,rect,*attrs);RETURN_CPP_OBJECT(result,ElementRef);}
    catch(const std::exception& error) {THROW_ERR(error.what());}
END

METHOD_IMPL(Drawing, AddLine)
    METHOD_SIGNATURE("", [object ElementRef*], 3, ([object Point const&] from, [object Point const&] to, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(3);
    REQUIRE_POINT_ARG(1, from);
    REQUIRE_POINT_ARG(2, to);
    REQUIRE_ATTRIBUTES_ARG(3, attrs);
    ElementRef* result = self->addLine(from, to, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddSpline)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Spline&&] spline, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, spline, Spline);
    REQUIRE_ATTRIBUTES_ARG(2, attrs);
    ElementRef* result = self->addSpline(std::move(*spline), *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddRect)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Rect const&] rect, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_ATTRIBUTES_ARG(2, attrs);
    ElementRef* result = self->addRect(rect, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddQuad)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Quad const&] quad, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_QUAD_ARG(1, quad);
    REQUIRE_ATTRIBUTES_ARG(2, attrs);
    ElementRef* result = self->addQuad(quad, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddPolygon)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Polygon&&] polygon, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(2);
    REQUIRE_CPP_OBJECT_ARG(1, polygon, Polygon);
    REQUIRE_ATTRIBUTES_ARG(2, attrs);
    ElementRef* result = self->addPolygon(std::move(*polygon), *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddEllipse)
    METHOD_SIGNATURE("", [object ElementRef*], 4, ([object Point const&] center, number xRadius, number yRadius, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_NUMBER_ARG(2, xRadius);
    REQUIRE_NUMBER_ARG(3, yRadius);
    REQUIRE_ATTRIBUTES_ARG(4, attrs);
    ElementRef* result = self->addEllipse(center, xRadius, yRadius, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddArc)
    METHOD_SIGNATURE("", [object ElementRef*], 6, ([object Point const&] center, number xRadius, number yRadius, number startAngle, number endAngle, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(6);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_NUMBER_ARG(2, xRadius);
    REQUIRE_NUMBER_ARG(3, yRadius);
    REQUIRE_NUMBER_ARG(4, startAngle);
    REQUIRE_NUMBER_ARG(5, endAngle);
    REQUIRE_ATTRIBUTES_ARG(6, attrs);
    ElementRef* result = self->addArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImage)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Rect const&] rect, [object Image const&] image, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, image, Image);
    REQUIRE_ATTRIBUTES_ARG(3, attrs);
    ElementRef* result = self->addImage(rect, *image, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddImageStrip)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Rect const&] rect, [object ImageStrip const&] imageStrip, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, imageStrip, ImageStrip);
    REQUIRE_ATTRIBUTES_ARG(3, attrs);
    ElementRef* result = self->addImageStrip(rect, *imageStrip, *attrs);
    RETURN_CPP_OBJECT(result, ElementRef);
    END

METHOD_IMPL(Drawing, AddDrawing)
    METHOD_SIGNATURE("", [object ElementRef*], 2, ([object Rect const&] rect, [object Drawing const&] drawing, [object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(3);
    REQUIRE_RECT_ARG(1, rect);
    REQUIRE_CPP_OBJECT_ARG(2, drawing, Drawing);
    REQUIRE_ATTRIBUTES_ARG(3, attrs);
    try {
        ElementRef* result = self->addDrawing(rect, *drawing, *attrs);
        RETURN_CPP_OBJECT(result, ElementRef);
    } catch (const std::exception& error) {
        THROW_ERR(error.what());
    }
    END

METHOD_IMPL(Drawing, GetElementCount)
    METHOD_SIGNATURE("", [number uint], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    size_t count = self->getElementCount();
    RETURN_UINT32(count);
    END

METHOD_IMPL(Drawing, GetElement)
    METHOD_SIGNATURE("", [object ElementRef*], 1, ([number uint] index));
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
    METHOD_SIGNATURE("", [object ElementRef*], 1, ([object Point const&] point));
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

} // namespace pdg

// @pdg-class {"name":"Drawing","construction":{"kind":"factory","factory":"pdg.createDrawing"},"native_binding":{"browser":{"generate":true,"base":null}}}
// @pdg-member {"name":"Drawing.addText","native_binding":{"adapter":"Drawing.addText"}}

// @pdg-member {"name":"Drawing.addLine","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addArc","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addRect","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addQuad","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addEllipse","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addImage","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addImageStrip","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.addDrawing","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.getElement","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Drawing.getElementHitBy","native_binding":{"allow_raw_pointers":true}}
