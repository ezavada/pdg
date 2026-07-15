// -----------------------------------------------
// polygon.cpp
//
// JavaScript bindings for Polygon class
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

WRAPPER_INITIALIZER_IMPL_CUSTOM(Polygon,
    OBJECT_SAVE(cppObj->mPolygonScriptObj, obj)
)
    EXPORT_CLASS_SYMBOLS("Polygon", Polygon, , ,
        // method section
        HAS_METHOD(Polygon, "addPoint", AddPoint)
        HAS_METHOD(Polygon, "addSpline", AddSpline)
        HAS_METHOD(Polygon, "insertPoint", InsertPoint)
        HAS_METHOD(Polygon, "removePoint", RemovePoint)
        HAS_METHOD(Polygon, "getPointCount", GetPointCount)
        HAS_METHOD(Polygon, "getPoint", GetPoint)
        HAS_METHOD(Polygon, "setPoint", SetPoint)
        HAS_METHOD(Polygon, "clearPoints", ClearPoints)
        HAS_METHOD(Polygon, "getBounds", GetBounds)
        HAS_METHOD(Polygon, "centerPoint", CenterPoint)
        HAS_METHOD(Polygon, "contains", Contains)
        HAS_METHOD(Polygon, "empty", Empty)
        HAS_METHOD(Polygon, "equals", Equals)
        HAS_METHOD(Polygon, "move", Move)
        HAS_METHOD(Polygon, "moveLeft", MoveLeft)
        HAS_METHOD(Polygon, "moveRight", MoveRight)
        HAS_METHOD(Polygon, "moveUp", MoveUp)
        HAS_METHOD(Polygon, "moveDown", MoveDown)
        HAS_METHOD(Polygon, "moveXTo", MoveXTo)
        HAS_METHOD(Polygon, "moveYTo", MoveYTo)
        HAS_METHOD(Polygon, "moveTo", MoveTo)
        HAS_METHOD(Polygon, "center", Center)
        HAS_METHOD(Polygon, "scale", Scale)
        HAS_METHOD(Polygon, "horzScale", HorzScale)
        HAS_METHOD(Polygon, "vertScale", VertScale)
        HAS_METHOD(Polygon, "scaleAround", ScaleAround)
        HAS_METHOD(Polygon, "rotate", Rotate)
        HAS_METHOD(Polygon, "rotateAround", RotateAround)
        HAS_METHOD(Polygon, "intersection", Intersection)
        HAS_METHOD(Polygon, "unionWith", UnionWith)
    );
    END

CPP_MANAGED_CONSTRUCTOR_IMPL(Polygon)
    SETUP_NON_SCRIPT_CALL;
    
    // Support constructor with multiple Point arguments
    if (ARGC == 0) {
        // Empty constructor
        return new pdg::Polygon();
    } else if (ARGC == 1 && (ARGV[0]->IsNull() || ARGV[0]->IsUndefined())) {
        // Handle null/undefined arguments during document generation
        return new pdg::Polygon();
    } else if (ARGC == 1 && ARGV[0]->IsArray()) {
        // Constructor with array of Point arguments
        std::vector<Point> points;
        v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(ARGV[0]);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        for (int i = 0; i < array->Length(); i++) {
            points.push_back(VAL2POINT(array->Get(context, i).ToLocalChecked()));
        }
        return new pdg::Polygon(points);
    } else {
        // Constructor with Point arguments
        std::vector<Point> points;
        for (int i = 0; i < ARGC; i++) {
            if (!ARGV[i]->IsObject()) {
                THROW_TYPE_ERR("Polygon constructor arguments must be Point objects");
                return nullptr;
            }
            Point point = VAL2POINT(ARGV[i]);
            points.push_back(point);
        }
        return new pdg::Polygon(points);
    }
END

METHOD_IMPL(Polygon, AddPoint)
    METHOD_SIGNATURE("", undefined, 1, ([object Point] point)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, point);
    self->addPoint(point);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, AddSpline)
    METHOD_SIGNATURE("", undefined, 1, ([object Spline] spline, [number] uStep)); 
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_OBJECT_ARG(1, spline);
    SplineWrap* splineWrapper = static_cast<SplineWrap*>(OBJECT_PRIVATE_DATA(spline));
    Spline* splinePtr = splineWrapper->getCppObject();
    if (!splinePtr) {
        THROW_TYPE_ERR("addSpline must be called with a valid Spline object");
        return;
    }
    float uStep = 0.01f;
    if (ARGC >= 2 && !ARGV[1]->IsUndefined() && !ARGV[1]->IsNull()) {
        REQUIRE_NUMBER_ARG(2, uStepArg);
        uStep = uStepArg;
    }
    self->addSpline(splinePtr, uStep);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, InsertPoint)
    METHOD_SIGNATURE("", undefined, 2, ([number uint] index, [object Point] point)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_UINT32_ARG(1, index);
    REQUIRE_POINT_ARG(2, point);
    self->insertPoint(index, point);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, RemovePoint)
    METHOD_SIGNATURE("", undefined, 1, ([number uint] index)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, index);
    try {
        self->removePoint(index);
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("Polygon::removePoint: index out of range");
    }
    NO_RETURN;
    END

METHOD_IMPL(Polygon, GetPointCount)
    METHOD_SIGNATURE("", [number uint], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    size_t count = self->getPointCount();
    RETURN_UINT32(count);
    END

METHOD_IMPL(Polygon, GetPoint)
    METHOD_SIGNATURE("", [object Point], 1, ([number uint] index)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_UINT32_ARG(1, index);
    try {
        Point point = self->getPoint(index);
        RETURN_POINT(point);
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("Polygon::getPoint: index out of range");
    }
    END

METHOD_IMPL(Polygon, SetPoint)
    METHOD_SIGNATURE("", undefined, 2, ([number uint] index, [object Point] point)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_UINT32_ARG(1, index);
    REQUIRE_POINT_ARG(2, point);
    try {
        self->setPoint(index, point);
        NO_RETURN;
    } catch (const std::out_of_range& e) {
        THROW_RANGE_ERR("Polygon::setPoint: index out of range");
    }
    END

METHOD_IMPL(Polygon, ClearPoints)
    METHOD_SIGNATURE("", undefined, 0, ()); 
    REQUIRE_ARG_COUNT(0);
    self->clearPoints();
    NO_RETURN;
    END

METHOD_IMPL(Polygon, GetBounds)
    METHOD_SIGNATURE("", [object Rect], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Rect bounds = self->getBounds();
    RETURN_RECT(bounds);
    END

METHOD_IMPL(Polygon, CenterPoint)
    METHOD_SIGNATURE("", [object Point], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    Point center = self->centerPoint();
    RETURN_POINT(center);
    END

METHOD_IMPL(Polygon, Contains)
    METHOD_SIGNATURE("", [boolean], 1, ([object Point] point)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, point);
    bool contains = self->contains(point);
    RETURN_BOOL(contains);
    END

METHOD_IMPL(Polygon, Empty)
    METHOD_SIGNATURE("", [boolean], 0, ()); 
    REQUIRE_ARG_COUNT(0);
    bool empty = self->empty();
    RETURN_BOOL(empty);
    END

METHOD_IMPL(Polygon, Equals)
    METHOD_SIGNATURE("", [boolean], 1, ([object Polygon] other)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, other);
    PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(OBJECT_PRIVATE_DATA(other));
    Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
    if (!otherPolygonPtr) {
        THROW_TYPE_ERR("equals must be called with a valid Polygon object");
        return;
    }
    RETURN_BOOL(*self == *otherPolygonPtr); // compare contents, not pointers
    END

METHOD_IMPL(Polygon, Move)
    METHOD_SIGNATURE("", [object Polygon], 1, ([object Offset] offset)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OFFSET_ARG(1, offset);
    self->move(offset);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveLeft)
    METHOD_SIGNATURE("", undefined, 1, (number delta)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, delta);
    self->moveLeft(delta);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveRight)
    METHOD_SIGNATURE("", [object Polygon], 1, (number delta)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, delta);
    self->moveRight(delta);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveUp)
    METHOD_SIGNATURE("", [object Polygon], 1, (number delta)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, delta);
    self->moveUp(delta);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveDown)
    METHOD_SIGNATURE("", [object Polygon], 1, (number delta)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, delta);
    self->moveDown(delta);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveXTo)
    METHOD_SIGNATURE("", undefined, 1, (number x)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, x);
    self->moveXTo(x);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveYTo)
    METHOD_SIGNATURE("", undefined, 1, (number y)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, y);
    self->moveYTo(y);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, MoveTo)
    METHOD_SIGNATURE("", undefined, 2, (number x, number y)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_NUMBER_ARG(1, x);
    REQUIRE_NUMBER_ARG(2, y);
    self->moveTo(x, y);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, Center)
    METHOD_SIGNATURE("", undefined, 1, ([object Point] point)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_POINT_ARG(1, point);
    self->center(point);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, Scale)
    METHOD_SIGNATURE("", undefined, 1, (number factor)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, factor);
    self->scale(factor);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, HorzScale)
    METHOD_SIGNATURE("", undefined, 1, (number factor)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, factor);
    self->horzScale(factor);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, VertScale)
    METHOD_SIGNATURE("", undefined, 1, (number factor)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, factor);
    self->vertScale(factor);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, ScaleAround)
    METHOD_SIGNATURE("", undefined, 2, (number factor, [object Point] centerPoint)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_NUMBER_ARG(1, factor);
    REQUIRE_POINT_ARG(2, centerPoint);
    self->scaleAround(factor, centerPoint);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, Rotate)
    METHOD_SIGNATURE("", undefined, 1, (number radians)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_NUMBER_ARG(1, radians);
    self->rotate(radians);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, RotateAround)
    METHOD_SIGNATURE("", undefined, 2, (number radians, [object Point] centerPoint)); 
    REQUIRE_ARG_COUNT(2);
    REQUIRE_NUMBER_ARG(1, radians);
    REQUIRE_POINT_ARG(2, centerPoint);
    self->rotateAround(radians, centerPoint);
    NO_RETURN;
    END

METHOD_IMPL(Polygon, Intersection)
    METHOD_SIGNATURE("", [object Polygon], 1, ([object Polygon] other)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, other);
    PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(OBJECT_PRIVATE_DATA(other));
    Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
    if (!otherPolygonPtr) {
        THROW_TYPE_ERR("intersection must be called with a valid Polygon object");
        return;
    }
    Polygon* result = new Polygon(self->intersection(*otherPolygonPtr));
    RETURN_NEW_CPP_OBJECT(result, Polygon);
    END

METHOD_IMPL(Polygon, UnionWith)
    METHOD_SIGNATURE("", [object Polygon], 1, ([object Polygon] other)); 
    REQUIRE_ARG_COUNT(1);
    REQUIRE_OBJECT_ARG(1, other);
    PolygonWrap* polygonWrapper = static_cast<PolygonWrap*>(OBJECT_PRIVATE_DATA(other));
    Polygon* otherPolygonPtr = polygonWrapper->getCppObject();
    if (!otherPolygonPtr) {
        THROW_TYPE_ERR("unionWith must be called with a valid Polygon object");
        return;
    }
    Polygon* result = new Polygon(self->unionWith(*otherPolygonPtr));
    RETURN_NEW_CPP_OBJECT(result, Polygon);
    END

CLEANUP_IMPL(Polygon)

#endif // !PDG_NO_GUI

} // namespace pdg
