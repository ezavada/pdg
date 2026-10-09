// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/spline.cpp
//    $PDG_ROOT/src/bindings/javascript/jsc/pdg_script_macros.h
//
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------



#include "pdg_project.h"

#define PDG_COMPILING_SCRIPT_IMPL

#include "pdg_script_interface.h"
#include "pdg_script_impl.h"

#include "internals.h"
#include "pdg-lib.h"

#include <cstdlib>

namespace pdg
{

    JSObjectRef Spline_newFromCpp(JSContextRef ctx, Spline* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Spline_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Spline_class());
        cppObj->mSplineScriptObj = obj;
        return obj;
    }

    JSObjectRef Spline_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* cppObj = New_Spline(argumentCount, arguments, exception);
        if (exception && *exception) return nullptr;
        if (s_HaveSavedError)
        {
            s_HaveSavedError = false;
            std::ostringstream excpt_;
            excpt_ << "throw '" << s_SavedError.str().c_str() << "'";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return 0;
        };
        if (!cppObj)
        {
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Spline" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Spline_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Spline_class());
        cppObj->mSplineScriptObj = obj;
        return obj;
    }

    JSClassRef Spline_class()
    {

        static JSStaticValue Spline_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Spline_staticFunctions[] =
        {
            { "getFirstOrder", Spline_GetFirstOrder, kJSPropertyAttributeDontDelete },
            { "getSecondOrder", Spline_GetSecondOrder, kJSPropertyAttributeDontDelete },
            { "addSegment", Spline_AddSegment, kJSPropertyAttributeDontDelete },
            { "addPoint", Spline_AddPoint, kJSPropertyAttributeDontDelete },
            { "getPoint", Spline_GetPoint, kJSPropertyAttributeDontDelete },
            { "setPoint", Spline_SetPoint, kJSPropertyAttributeDontDelete },
            { "getPointCount", Spline_GetPointCount, kJSPropertyAttributeDontDelete },
            { "getMaxU", Spline_GetMaxU, kJSPropertyAttributeDontDelete },
            { "getBounds", Spline_GetBounds, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Spline";
            definition.staticFunctions = Spline_staticFunctions;
            definition.staticValues = Spline_staticValues;
            definition.callAsConstructor = Spline_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    Spline* New_Spline(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        int splineType = SPLINE_CUBIC_BEZIER;
        if (argumentCount >= 1)
        {
            if (JSValueIsNumber(ctx, arguments[0]))
            {
                splineType = (int)pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[0], exception));
            }
            else if (!JSValueIsNull(ctx, arguments[0]) && !JSValueIsUndefined(ctx, arguments[0]))
            {
                return 0;
            }
        }

        return new Spline(splineType);
    }

    JSValueRef Spline_GetFirstOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""u"")");
        double u = JSValueToNumber(ctx, arguments[1 -1], exception);
        Point result = self->getFirstOrder(u);
        return JSC_PointToValue(ctx, result, exception);
    }

    JSValueRef Spline_GetSecondOrder(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""u"")");
        double u = JSValueToNumber(ctx, arguments[1 -1], exception);
        Point result = self->getSecondOrder(u);
        return JSC_PointToValue(ctx, result, exception);
    }

    JSValueRef Spline_AddSegment(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 4)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4);
        pdg::Point p1;
        auto p1_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], p1, exception);
        if (!p1_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*p1_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        pdg::Point p2;
        auto p2_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], p2, exception);
        if (!p2_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*p2_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };
        pdg::Point p3;
        auto p3_isPoint = JSC_ValueIsPoint(ctx, arguments[3 -1], p3, exception);
        if (!p3_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*p3_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 3, "Point", arguments[3 -1]);
        };
        pdg::Point p4;
        auto p4_isPoint = JSC_ValueIsPoint(ctx, arguments[4 -1], p4, exception);
        if (!p4_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*p4_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 4, "Point", arguments[4 -1]);
        };
        self->addSegment(p1, p2, p3, p4);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Spline_AddPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        pdg::Point point;
        auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], point, exception);
        if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*point_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        self->addPoint(point);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Spline_GetPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""pointIndex"")");
        int32 pointIndex = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        Point result = self->getPoint(pointIndex);
        return JSC_PointToValue(ctx, result, exception);
    }

    JSValueRef Spline_SetPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""pointIndex"")");
        int32 pointIndex = pdg::JSC_NumberToInt32(JSValueToNumber(ctx, arguments[1 -1], exception));
        pdg::Point point;
        auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], point, exception);
        if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*point_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };
        self->setPoint(pointIndex, point);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef Spline_GetPointCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        int result = self->getPointCount();
        return JSValueMakeNumber(ctx, result);
    }

    JSValueRef Spline_GetMaxU(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        float result = self->getMaxU();
        return JSValueMakeNumber(ctx, result);
    }

    JSValueRef Spline_GetBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Spline* self = static_cast<Spline*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Rect bounds = self->getBounds();
        return JSC_RectToValue(ctx, bounds, exception);
    }

    void CleanupSplineScriptObject(JSObjectRef obj) { }

}
