// -----------------------------------------------
// spline.cpp
//
// JavaScript bindings for Spline class
//
// Written by AI Assistant, 2024
// Copyright (c) 2024, Dream Rock Studios, LLC
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

#ifndef PDG_NO_GUI

WRAPPER_INITIALIZER_IMPL_CUSTOM(Spline,
    OBJECT_SAVE(cppObj->mSplineScriptObj, obj)
)
    EXPORT_CLASS_SYMBOLS("Spline", Spline, , ,
        // method section
        HAS_METHOD(Spline, "getFirstOrder", GetFirstOrder)
        HAS_METHOD(Spline, "getSecondOrder", GetSecondOrder)
        HAS_METHOD(Spline, "addSegment", AddSegment)
        HAS_METHOD(Spline, "addPoint", AddPoint)
        HAS_METHOD(Spline, "getPoint", GetPoint)
        HAS_METHOD(Spline, "setPoint", SetPoint)
        HAS_METHOD(Spline, "getPointCount", GetPointCount)
        HAS_METHOD(Spline, "getMaxU", GetMaxU)
        HAS_METHOD(Spline, "getBounds", GetBounds)
    );
    END

CPP_MANAGED_CONSTRUCTOR_IMPL(Spline)
    SETUP_NON_SCRIPT_CALL;
    
    int splineType = SPLINE_CUBIC_BEZIER; // default to SPLINE_CUBIC_BEZIER
    if (ARGC >= 1) {
        if (ARGV[0]->IsNumber()) {
            splineType = (int)ARGV[0]->Int32Value(isolate->GetCurrentContext()).ToChecked();
        } else if (!ARGV[0]->IsNull() && !ARGV[0]->IsUndefined()) {
            return 0;  // Invalid argument type
        }
    }
    
    return new Spline(splineType);
END

METHOD_IMPL(Spline, GetFirstOrder)
    METHOD_SIGNATURE("", [object Point], 1, (number u)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, u);
    Point result = self->getFirstOrder(u);
    RETURN_POINT(result);
    END

METHOD_IMPL(Spline, GetSecondOrder)
    METHOD_SIGNATURE("", [object Point], 1, (number u)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, u);
    Point result = self->getSecondOrder(u);
    RETURN_POINT(result);
    END

METHOD_IMPL(Spline, AddSegment)
    METHOD_SIGNATURE("", undefined, 4, ([object Point] p1, [object Point] p2, [object Point] p3, [object Point] p4)); 
    REQUIRE_ARG_COUNT(4);
    REQUIRE_POINT_ARG(1, p1);
    REQUIRE_POINT_ARG(2, p2);
    REQUIRE_POINT_ARG(3, p3);
    REQUIRE_POINT_ARG(4, p4);
    self->addSegment(p1, p2, p3, p4);
    NO_RETURN;
    END

METHOD_IMPL(Spline, AddPoint)
    METHOD_SIGNATURE("", undefined, 1, ([object Point] point)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, point);
    self->addPoint(point);
    NO_RETURN;
    END

METHOD_IMPL(Spline, GetPoint)
    METHOD_SIGNATURE("", [object Point], 1, (number pointIndex)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG(1, pointIndex);
    Point result = self->getPoint(pointIndex);
    RETURN_POINT(result);
    END

METHOD_IMPL(Spline, SetPoint)
    METHOD_SIGNATURE("", undefined, 2, (number pointIndex, [object Point] point)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_INT32_ARG(1, pointIndex);
    REQUIRE_POINT_ARG(2, point);
    self->setPoint(pointIndex, point);
    NO_RETURN;
    END

METHOD_IMPL(Spline, GetPointCount)
    METHOD_SIGNATURE("", number, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    int result = self->getPointCount();
    RETURN_INT32(result);
    END

METHOD_IMPL(Spline, GetMaxU)
    METHOD_SIGNATURE("", number, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    float result = self->getMaxU();
    RETURN_NUMBER(result);
    END

METHOD_IMPL(Spline, GetBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Rect bounds = self->getBounds();
    RETURN_RECT(bounds);
    END

CLEANUP_IMPL(Spline)

#endif // !PDG_NO_GUI

} // end namespace pdg
