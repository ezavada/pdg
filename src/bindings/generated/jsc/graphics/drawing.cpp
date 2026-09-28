// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/drawing.cpp
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

    JSObjectRef ElementRef_newFromCpp(JSContextRef ctx, ElementRef* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, ElementRef_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ElementRef_class());
        cppObj->mElementRefScriptObj = obj;
        return obj;
    }

    JSObjectRef ElementRef_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* cppObj = New_ElementRef(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "ElementRef" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, ElementRef_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, ElementRef_class());
        cppObj->mElementRefScriptObj = obj;
        return obj;
    }

    JSClassRef ElementRef_class()
    {

        static JSStaticValue ElementRef_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction ElementRef_staticFunctions[] =
        {
            { "type", ElementRef_Type, kJSPropertyAttributeDontDelete },
            { "getControlPoints", ElementRef_GetControlPoints, kJSPropertyAttributeDontDelete },
            { "getControlPoint", ElementRef_GetControlPoint, kJSPropertyAttributeDontDelete },
            { "changeControlPoint", ElementRef_ChangeControlPoint, kJSPropertyAttributeDontDelete },
            { "getAttributes", ElementRef_GetAttributes, kJSPropertyAttributeDontDelete },
            { "setAttributes", ElementRef_SetAttributes, kJSPropertyAttributeDontDelete },
            { "setLiveAttributes", ElementRef_SetLiveAttributes, kJSPropertyAttributeDontDelete },
            { "clearLiveAttributes", ElementRef_ClearLiveAttributes, kJSPropertyAttributeDontDelete },
            { "hasLiveAttributes", ElementRef_HasLiveAttributes, kJSPropertyAttributeDontDelete },
            { "moveForward", ElementRef_MoveForward, kJSPropertyAttributeDontDelete },
            { "moveBackward", ElementRef_MoveBackward, kJSPropertyAttributeDontDelete },
            { "moveToFront", ElementRef_MoveToFront, kJSPropertyAttributeDontDelete },
            { "moveToBack", ElementRef_MoveToBack, kJSPropertyAttributeDontDelete },
            { "remove", ElementRef_Remove, kJSPropertyAttributeDontDelete },
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "ElementRef";
            definition.staticFunctions = ElementRef_staticFunctions;
            definition.staticValues = ElementRef_staticValues;
            definition.callAsConstructor = ElementRef_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    ElementRef* New_ElementRef(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        return nullptr;
    }

    void CleanupElementRefScriptObject(JSObjectRef obj) { }

    JSValueRef ElementRef_Type(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        ElementType type = self->type();
        return JSValueMakeNumber(ctx, static_cast<uint32_t>(type));
    }

    JSValueRef ElementRef_GetControlPoints(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        const std::vector<Point>& points = self->getControlPoints();

#ifdef PDG_USING_JAVASCRIPT_CORE
        JSObjectRef result = JSObjectMakeArray(ctx, 0, nullptr, exception);
        for (size_t i = 0; i < points.size(); i++)
        {
            Point point = points[i];
            JSObjectSetPropertyAtIndex(ctx, result, (unsigned)i, JSC_PointToValue(ctx, point, exception), exception);
        }
#else
        v8::Local<v8::Array> result = v8::Array::New(isolate, points.size());
        v8::Local<v8::Context> context = isolate->GetCurrentContext();

        for (size_t i = 0; i < points.size(); i++)
        {
            Point point = points[i];
            result->Set(context, i, JSC_PointToValue(ctx, point, exception)).ToChecked();
        }
#endif

        return result;
    }

    JSValueRef ElementRef_GetControlPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""controlPointIndex"")");
        uint32 controlPointIndex = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        try
        {
            const Point& point = self->getControlPoint(controlPointIndex);
            Point pointCopy = point;
            return JSC_PointToValue(ctx, pointCopy, exception);
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "ElementRef::getControlPoint: index out of range" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef ElementRef_ChangeControlPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""controlPointIndex"")");
        uint32 controlPointIndex = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        pdg::Point controlPoint;
        auto controlPoint_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], controlPoint, exception);
        if (!controlPoint_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*controlPoint_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };
        try
        {
            self->changeControlPoint(controlPointIndex, controlPoint);
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "ElementRef::changeControlPoint: index out of range" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_GetAttributes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Attributes* attrsPtr = new Attributes();
        self->getAttributes(*attrsPtr);
        if (!attrsPtr) return JSValueMakeNull(ctx);
        if (!attrsPtr->mAttributesScriptObj)
        {
            return Attributes_newFromCpp(ctx, attrsPtr);
        }
        else
        {
            return attrsPtr->mAttributesScriptObj;
        };
    }

    JSValueRef ElementRef_SetAttributes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);

        Attributes* attrs = ExtractAttributes(arguments[1 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->setAttributes(*attrs);
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_SetLiveAttributes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);

        Attributes* attrs = ExtractAttributes(arguments[1 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        self->setLiveAttributes(*attrs);
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ElementRef_ClearLiveAttributes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->clearLiveAttributes();
        return JSValueMakeUndefined(ctx);
    }
    JSValueRef ElementRef_HasLiveAttributes(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        return JSValueMakeBoolean(ctx, self->hasLiveAttributes());
    }

    JSValueRef ElementRef_MoveForward(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveForward();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_MoveBackward(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveBackward();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_MoveToFront(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToFront();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_MoveToBack(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->moveToBack();
        return JSValueMakeUndefined(ctx);
    }

    JSValueRef ElementRef_Remove(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        self->remove();
        return JSValueMakeUndefined(ctx);
    }

    JSObjectRef Drawing_newFromCpp(JSContextRef ctx, Drawing* cppObj)
    {
        JSObjectRef obj = JSObjectMake(ctx, Drawing_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Drawing_class());
        cppObj->mDrawingScriptObj = obj;
        return obj;
    }

    JSObjectRef Drawing_new(JSContextRef ctx, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* cppObj = New_Drawing(argumentCount, arguments, exception);
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
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( "throw 'failed to " "create" " C++ native " "Drawing" "'"), NULL, 0, 1, exception);
            return 0;
        }
        JSObjectRef obj = JSObjectMake(ctx, Drawing_class(), cppObj);
        JSC_SetObjectClassConstructor(ctx, obj, Drawing_class());
        cppObj->mDrawingScriptObj = obj;
        return obj;
    }

    JSClassRef Drawing_class()
    {

        static JSStaticValue Drawing_staticValues[] =
        {
            { 0, 0, 0, 0 }
        };
        static JSStaticFunction Drawing_staticFunctions[] =
        {
            { "addLine", Drawing_AddLine, kJSPropertyAttributeDontDelete },
            { "addSpline", Drawing_AddSpline, kJSPropertyAttributeDontDelete },
            { "addRect", Drawing_AddRect, kJSPropertyAttributeDontDelete },
            { "addArc", Drawing_AddArc, kJSPropertyAttributeDontDelete },
            { "addQuad", Drawing_AddQuad, kJSPropertyAttributeDontDelete },
            { "addPolygon", Drawing_AddPolygon, kJSPropertyAttributeDontDelete },
            { "addEllipse", Drawing_AddEllipse, kJSPropertyAttributeDontDelete },
            { "addImage", Drawing_AddImage, kJSPropertyAttributeDontDelete },
            { "addImageStrip", Drawing_AddImageStrip, kJSPropertyAttributeDontDelete },
            { "addDrawing", Drawing_AddDrawing, kJSPropertyAttributeDontDelete },
            { "getElementCount", Drawing_GetElementCount, kJSPropertyAttributeDontDelete },
            { "getElement", Drawing_GetElement, kJSPropertyAttributeDontDelete },
            { "getElementHitBy", Drawing_GetElementHitBy, kJSPropertyAttributeDontDelete },
            { "getBounds", Drawing_GetBounds, kJSPropertyAttributeDontDelete },
            { "centerPoint", Drawing_CenterPoint, kJSPropertyAttributeDontDelete },
            { "empty", Drawing_Empty, kJSPropertyAttributeDontDelete },
#ifndef PDG_NO_GUI
            { "draw", Drawing_Draw, kJSPropertyAttributeDontDelete },
#endif
            { 0, 0, 0 }
        };
        static JSClassRef jsClass = 0;
        if (!jsClass)
        {
            JSClassDefinition definition = kJSClassDefinitionEmpty;
            definition.className = "Drawing";
            definition.staticFunctions = Drawing_staticFunctions;
            definition.staticValues = Drawing_staticValues;
            definition.callAsConstructor = Drawing_new;
            jsClass = JSClassCreate(&definition);
        }
        return jsClass;

    }

    Drawing* New_Drawing(size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException)
    {
        JSContextRef ctx = gMainContext;
        JSValueRef _exception = 0;
        JSValueRef* exception = &_exception;

        return nullptr;
    }

    void CleanupDrawingScriptObject(JSObjectRef obj) { }

    JSValueRef CreateDrawing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Drawing* drawing = Drawing::create();
        if (!drawing) return JSValueMakeNull(ctx);
        return Drawing_newFromCpp(ctx, drawing);;
    }

    JSValueRef Drawing_AddLine(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Point from;
        auto from_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], from, exception);
        if (!from_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*from_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        pdg::Point to;
        auto to_isPoint = JSC_ValueIsPoint(ctx, arguments[2 -1], to, exception);
        if (!to_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*to_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 2, "Point", arguments[2 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addLine(from, to, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddSpline(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Spline* spline = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef spline_ = JSValueToObject(ctx, arguments[1 -1], exception);
            spline = Spline_getCppObject(spline_);
        }
        if (!spline)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Spline"" (""spline"")");

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addSpline(std::move(*spline), *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddRect(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addRect(rect, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddQuad(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        pdg::Quad quad;
        auto quad_isQuad = JSC_ValueIsQuad(ctx, arguments[1 -1], quad, exception);
        if (!quad_isQuad.has_value()) { return JSValueMakeNull(ctx); }
        if (!*quad_isQuad)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", arguments[1 -1]);
        };

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addQuad(quad, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddPolygon(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 2)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 2);
        Polygon* polygon = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef polygon_ = JSValueToObject(ctx, arguments[1 -1], exception);
            polygon = Polygon_getCppObject(polygon_);
        }
        if (!polygon)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Polygon"" (""polygon"")");

        Attributes* attrs = ExtractAttributes(arguments[2 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addPolygon(std::move(*polygon), *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddEllipse(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 4)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 4);
        pdg::Point center;
        auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
        if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*center_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""xRadius"")");
        double xRadius = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""yRadius"")");
        double yRadius = JSValueToNumber(ctx, arguments[3 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[4 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addEllipse(center, xRadius, yRadius, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddArc(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 6)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 6);
        pdg::Point center;
        auto center_isPoint = JSC_ValueIsPoint(ctx, arguments[1 -1], center, exception);
        if (!center_isPoint.has_value()) { return JSValueMakeNull(ctx); }
        if (!*center_isPoint)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Point", arguments[1 -1]);
        };
        if (argumentCount < 2 || !JSValueIsNumber(ctx, arguments[2 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 2, "a number (""xRadius"")");
        double xRadius = JSValueToNumber(ctx, arguments[2 -1], exception);
        if (argumentCount < 3 || !JSValueIsNumber(ctx, arguments[3 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 3, "a number (""yRadius"")");
        double yRadius = JSValueToNumber(ctx, arguments[3 -1], exception);
        if (argumentCount < 4 || !JSValueIsNumber(ctx, arguments[4 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 4, "a number (""startAngle"")");
        double startAngle = JSValueToNumber(ctx, arguments[4 -1], exception);
        if (argumentCount < 5 || !JSValueIsNumber(ctx, arguments[5 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 5, "a number (""endAngle"")");
        double endAngle = JSValueToNumber(ctx, arguments[5 -1], exception);

        Attributes* attrs = ExtractAttributes(arguments[6 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addArc(center, xRadius, yRadius, startAngle, endAngle, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddImage(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        Image* image = 0;
        if (JSValueIsObject(ctx, arguments[2 -1]))
        {
            JSObjectRef image_ = JSValueToObject(ctx, arguments[2 -1], exception);
            image = Image_getCppObject(image_);
        }
        if (!image)
            return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Image"" (""image"")");

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addImage(rect, *image, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddImageStrip(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        ImageStrip* imageStrip = 0;
        if (JSValueIsObject(ctx, arguments[2 -1]))
        {
            JSObjectRef imageStrip_ = JSValueToObject(ctx, arguments[2 -1], exception);
            imageStrip = ImageStrip_getCppObject(imageStrip_);
        }
        if (!imageStrip)
            return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""ImageStrip"" (""imageStrip"")");

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        ElementRef* result = self->addImageStrip(rect, *imageStrip, *attrs);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_AddDrawing(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 3)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 3);
        pdg::Rect rect;
        auto rect_isRect = JSC_ValueIsRect(ctx, arguments[1 -1], rect, exception);
        if (!rect_isRect.has_value()) { return JSValueMakeNull(ctx); }
        if (!*rect_isRect)
        {
            return JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", arguments[1 -1]);
        };
        Drawing* drawing = 0;
        if (JSValueIsObject(ctx, arguments[2 -1]))
        {
            JSObjectRef drawing_ = JSValueToObject(ctx, arguments[2 -1], exception);
            drawing = Drawing_getCppObject(drawing_);
        }
        if (!drawing)
            return JSC_ThrowArgTypeException(ctx, exception, 2, "an object of type ""Drawing"" (""drawing"")");

        Attributes* attrs = ExtractAttributes(arguments[3 -1]);
        if (!attrs)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "TypeError" << "('" << "Type Error: " << "Expected Attributes or AnimatedAttributes" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx); return JSValueMakeNull(ctx);
        };
        try
        {
            ElementRef* result = self->addDrawing(rect, *drawing, *attrs);
            if (!result) return JSValueMakeNull(ctx);
            if (!result->mElementRefScriptObj)
            {
                return ElementRef_newFromCpp(ctx, result);
            }
            else
            {
                return result->mElementRefScriptObj;
            };
        }
        catch (const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Drawing_GetElementCount(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        size_t count = self->getElementCount();
        return JSValueMakeNumber(ctx, count);
    }

    JSValueRef Drawing_GetElement(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        if (!JSValueIsNumber(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a number (""index"")");
        uint32 index = (uint32)floor(fabs(JSValueToNumber(ctx, arguments[1 -1], exception)));
        try
        {
            ElementRef* result = self->getElement(index);
            if (!result) return JSValueMakeNull(ctx);
            if (!result->mElementRefScriptObj)
            {
                return ElementRef_newFromCpp(ctx, result);
            }
            else
            {
                return result->mElementRefScriptObj;
            };
        }
        catch (const std::out_of_range& e)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "RangeError" << "('" << "Range Error: " << "Drawing::getElement: index out of range" << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }

    JSValueRef Drawing_GetElementHitBy(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
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
        ElementRef* result = self->getElementHitBy(point);
        if (!result) return JSValueMakeNull(ctx);
        if (!result->mElementRefScriptObj)
        {
            return ElementRef_newFromCpp(ctx, result);
        }
        else
        {
            return result->mElementRefScriptObj;
        };
    }

    JSValueRef Drawing_GetBounds(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Rect bounds = self->getBounds();
        return JSC_RectToValue(ctx, bounds, exception);
    }

    JSValueRef Drawing_CenterPoint(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        Point center = self->centerPoint();
        return JSC_PointToValue(ctx, center, exception);
    }

    JSValueRef Drawing_Empty(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        bool empty = self->empty();
        return JSValueMakeBoolean(ctx, empty);
    }

#ifndef PDG_NO_GUI

    JSValueRef Drawing_Draw(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        Drawing* self = static_cast<Drawing*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);
        Port* port = 0;
        if (JSValueIsObject(ctx, arguments[1 -1]))
        {
            JSObjectRef port_ = JSValueToObject(ctx, arguments[1 -1], exception);
            port = Port_getCppObject(port_);
        }
        if (!port)
            return JSC_ThrowArgTypeException(ctx, exception, 1, "an object of type ""Port"" (""port"")");

        self->draw(port);
        return JSValueMakeUndefined(ctx);
    }
#endif

}
