// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/polygon.cpp
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

    JSObjectRef Polygon_newFromCpp(JSContextRef ctx, Polygon* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Polygon_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Polygon_class());
        cppObj->mPolygonScriptObj = obj;
        return obj;
    }

    JSObjectRef Polygon_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Polygon* cppObj = New_Polygon(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Polygon" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Polygon_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Polygon_class());
        cppObj->mPolygonScriptObj = obj;
        return obj;
    }

    JSClassRef Polygon_class()
    {

        static JSStaticValue Polygon_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Polygon_staticFunctions[] =
        {
            { "addPoint", Polygon_AddPoint, kJSPropertyAttributeDontDelete },
            { "addSpline", Polygon_AddSpline, kJSPropertyAttributeDontDelete },
            { "insertPoint", Polygon_InsertPoint, kJSPropertyAttributeDontDelete },
            { "removePoint", Polygon_RemovePoint, kJSPropertyAttributeDontDelete },
            { "getPointCount", Polygon_GetPointCount, kJSPropertyAttributeDontDelete },
            { "getPoint", Polygon_GetPoint, kJSPropertyAttributeDontDelete },
            { "setPoint", Polygon_SetPoint, kJSPropertyAttributeDontDelete },
            { "clearPoints", Polygon_ClearPoints, kJSPropertyAttributeDontDelete },
            { "getBounds", Polygon_GetBounds, kJSPropertyAttributeDontDelete },
            { "centerPoint", Polygon_CenterPoint, kJSPropertyAttributeDontDelete },
            { "contains", Polygon_Contains, kJSPropertyAttributeDontDelete },
            { "empty", Polygon_Empty, kJSPropertyAttributeDontDelete },
            { "equals", Polygon_Equals, kJSPropertyAttributeDontDelete },
            { "move", Polygon_Move, kJSPropertyAttributeDontDelete },
            { "moveLeft", Polygon_MoveLeft, kJSPropertyAttributeDontDelete },
            { "moveRight", Polygon_MoveRight, kJSPropertyAttributeDontDelete },
            { "moveUp", Polygon_MoveUp, kJSPropertyAttributeDontDelete },
            { "moveDown", Polygon_MoveDown, kJSPropertyAttributeDontDelete },
            { "moveXTo", Polygon_MoveXTo, kJSPropertyAttributeDontDelete },
            { "moveYTo", Polygon_MoveYTo, kJSPropertyAttributeDontDelete },
            { "moveTo", Polygon_MoveTo, kJSPropertyAttributeDontDelete },
            { "center", Polygon_Center, kJSPropertyAttributeDontDelete },
            { "scale", Polygon_Scale, kJSPropertyAttributeDontDelete },
            { "horzScale", Polygon_HorzScale, kJSPropertyAttributeDontDelete },
            { "vertScale", Polygon_VertScale, kJSPropertyAttributeDontDelete },
            { "scaleAround", Polygon_ScaleAround, kJSPropertyAttributeDontDelete },
            { "rotate", Polygon_Rotate, kJSPropertyAttributeDontDelete },
            { "rotateAround", Polygon_RotateAround, kJSPropertyAttributeDontDelete },
            { "intersection", Polygon_Intersection, kJSPropertyAttributeDontDelete },
            { "unionWith", Polygon_UnionWith, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Polygon";
            definition.staticFunctions = Polygon_staticFunctions;
            definition.staticValues = Polygon_staticValues;
            definition.callAsConstructor = Polygon_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    Polygon* New_Polygon(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef localConstructorException = nullptr;
        JSValueRef* exception = constructorException ? constructorException : &localConstructorException;
        if (argumentCount == 0 || (argumentCount == 1 && (JSValueIsNull(ctx, arguments[0]) || JSValueIsUndefined(ctx, arguments[0]))))
        {
            return new pdg::Polygon();
        }
        std::vector<Point> points;
        auto appendPoint = [&](JSValueRef value)
        {
            Point point;
            auto converted = JSC_ValueIsPoint(ctx, value, point, exception);
            if (!converted.has_value()) return false;
            if (!*converted)
            {
                JSC_ThrowArgTypeException(ctx, exception, 1, "Point", value);
                return false;
            }
            points.push_back(point);
            return true;
        };
#ifdef PDG_USING_JAVASCRIPT_CORE
        if (argumentCount == 1 && JSValueIsArray(ctx, arguments[0]))
        {
            JSObjectRef array = JSValueToObject(ctx, arguments[0], exception);
            JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
            JSValueRef lengthValue = JSObjectGetProperty(ctx, array, lengthName, exception);
            JSStringRelease(lengthName);
            if (*exception) return nullptr;
            double length = JSValueToNumber(ctx, lengthValue, exception);
            if (*exception) return nullptr;
            for (unsigned i = 0; i < length; ++i)
            {
                auto value = JSObjectGetPropertyAtIndex(ctx, array, i, exception);
                if (*exception || !appendPoint(value)) return nullptr;
            }
#else
            if (argumentCount == 1 && arguments[0]->IsArray())
            {
                auto array = arguments[0].As<v8::Array>();
                auto context = isolate->GetCurrentContext();
                for (uint32_t i = 0; i < array->Length(); ++i)
                {
                    v8::Local<v8::Value> value;
                    if (!array->Get(context, i).ToLocal(&value) || !appendPoint(value)) return nullptr;
                }
#endif
            }
            else
            {
                for (int i = 0; i < argumentCount; ++i)
                {
                    if (!appendPoint(arguments[i])) return nullptr;
                }
            }
            return new pdg::Polygon(points);
        }

        JSValueRef Polygon_AddPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
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
            return thisObject;
        }

        JSValueRef Polygon_AddSpline(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            Spline* spline = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef spline_ = JSValueToObject(ctx, arguments[1 -1], exception);
                spline = Spline_getCppObject(spline_);
            }
            if (!spline)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Spline"" (""spline"")");
            float uStep = 0.01f;
            if (argumentCount >= 2 && !JSValueIsUndefined(ctx, arguments[1]) && !JSValueIsNull(ctx, arguments[1]))
            {
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""uStepArg"")");
                double uStepArg = JSValueToNumber(ctx, arguments[2 -1], exception);
                uStep = uStepArg;
            }
            self->addSpline(spline, uStep);
            return thisObject;
        }

        JSValueRef Polygon_InsertPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            };
            self->insertPoint(index, point);
            return thisObject;
        }

        JSValueRef Polygon_RemovePoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            try
            {
                self->removePoint(index);
            }
            catch (const std::out_of_range& e)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Polygon::removePoint: index out of range" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);
            }
            return thisObject;
        }

        JSValueRef Polygon_GetPointCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            size_t count = self->getPointCount();
            return JSValueMakeNumber(ctx, count);
        }

        JSValueRef Polygon_GetPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            try
            {
                Point point = self->getPoint(index);
                return JSC_PointToValue(ctx, point, exception);
            }
            catch (const std::out_of_range& e)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Polygon::getPoint: index out of range" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);
            }
        }

        JSValueRef Polygon_SetPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (!JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
            uint32 index = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
            pdg::Point point;
            auto point_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], point, exception);
            if (!point_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*point_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            };
            try
            {
                self->setPoint(index, point);
                return thisObject;
            }
            catch (const std::out_of_range& e)
            {
                std::ostringstream excpt_;
                excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Polygon::setPoint: index out of range" << "')";
                JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
                return JSValueMakeNull(ctx);
            }
        }

        JSValueRef Polygon_ClearPoints(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            self->clearPoints();
            return thisObject;
        }

        JSValueRef Polygon_GetBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            Rect bounds = self->getBounds();
            return JSC_RectToValue(ctx, bounds, exception);
        }

        JSValueRef Polygon_CenterPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            Point center = self->centerPoint();
            return JSC_PointToValue(ctx, center, exception);
        }

        JSValueRef Polygon_Contains(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
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
            bool contains = self->contains(point);
            return JSValueMakeBoolean(ctx, contains);
        }

        JSValueRef Polygon_Empty(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 0)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
            bool empty = self->empty();
            return JSValueMakeBoolean(ctx, empty);
        }

        JSValueRef Polygon_Equals(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Polygon* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = Polygon_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Polygon"" (""other"")");
            return JSValueMakeBoolean(ctx, *self == *other);
        }

        JSValueRef Polygon_Move(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            pdg::Offset offset;
            auto offset_isOffset = JSC_ValueIsOffset(ctx, arguments[1 -1], offset, exception);
            if (!offset_isOffset.has_value()) { return JSValueMakeNull(ctx); }
            if (!*offset_isOffset)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "Offset", arguments[1 -1]);
            };
            self->move(offset);
            return thisObject;
        }

        JSValueRef Polygon_MoveLeft(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""delta"")");
            double delta = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveLeft(delta);
            return thisObject;
        }

        JSValueRef Polygon_MoveRight(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""delta"")");
            double delta = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveRight(delta);
            return thisObject;
        }

        JSValueRef Polygon_MoveUp(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""delta"")");
            double delta = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveUp(delta);
            return thisObject;
        }

        JSValueRef Polygon_MoveDown(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""delta"")");
            double delta = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveDown(delta);
            return thisObject;
        }

        JSValueRef Polygon_MoveXTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
            double x = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveXTo(x);
            return thisObject;
        }

        JSValueRef Polygon_MoveYTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""y"")");
            double y = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->moveYTo(y);
            return thisObject;
        }

        JSValueRef Polygon_MoveTo(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount < 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1, true);
            pdg::Point point;
            auto isPoint = JSC_ValueIsPoint(ctx, arguments[0], point, exception);
            if (!isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (*isPoint)
            {
                if (argumentCount != 1)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
                self->moveTo(point);
            }
            else
            {
                if (argumentCount != 2)
                    return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
                if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""x"")");
                double x = JSValueToNumber(ctx, arguments[1 -1], exception);
                if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
                    return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""y"")");
                double y = JSValueToNumber(ctx, arguments[2 -1], exception);
                self->moveTo(x, y);
            }
            return thisObject;
        }

        JSValueRef Polygon_Center(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
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
            self->center(point);
            return thisObject;
        }

        JSValueRef Polygon_Scale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->scale(factor);
            return thisObject;
        }

        JSValueRef Polygon_HorzScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->horzScale(factor);
            return thisObject;
        }

        JSValueRef Polygon_VertScale(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->vertScale(factor);
            return thisObject;
        }

        JSValueRef Polygon_ScaleAround(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""factor"")");
            double factor = JSValueToNumber(ctx, arguments[1 -1], exception);
            pdg::Point centerPoint;
            auto centerPoint_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], centerPoint, exception);
            if (!centerPoint_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*centerPoint_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            };
            self->scaleAround(factor, centerPoint);
            return thisObject;
        }

        JSValueRef Polygon_Rotate(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            self->rotate(radians);
            return thisObject;
        }

        JSValueRef Polygon_RotateAround(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 2)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
            if (argumentCount < 1 || !JSValueIsNumber(ctx, arguments[1 -1]))
                return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""radians"")");
            double radians = JSValueToNumber(ctx, arguments[1 -1], exception);
            pdg::Point centerPoint;
            auto centerPoint_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], centerPoint, exception);
            if (!centerPoint_isPoint.has_value()) { return JSValueMakeNull(ctx); }
            if (!*centerPoint_isPoint)
            {
                return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
            };
            self->rotateAround(radians, centerPoint);
            return thisObject;
        }

        JSValueRef Polygon_Intersection(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Polygon* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = Polygon_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Polygon"" (""other"")");
            Polygon* result = new Polygon(self->intersection(*other));
            if (!result) return JSValueMakeNull(ctx);
            return Polygon_newFromCpp(ctx, result);;
        }

        JSValueRef Polygon_UnionWith(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
        {
            Polygon* self = static_cast<Polygon*>(JSObjectGetPrivate(thisObject));
            ;
            if (argumentCount != 1)
                return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
            Polygon* other = 0;
            if (JSValueIsObject(ctx, arguments[1 -1]))
            {
                JSObjectRef other_ = JSValueToObject(ctx, arguments[1 -1], exception);
                other = Polygon_getCppObject(other_);
            }
            if (!other)
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Polygon"" (""other"")");
            Polygon* result = new Polygon(self->unionWith(*other));
            if (!result) return JSValueMakeNull(ctx);
            return Polygon_newFromCpp(ctx, result);;
        }

        void CleanupPolygonScriptObject(JSObjectRef obj) { }

    }
