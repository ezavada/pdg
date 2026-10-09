// -----------------------------------------------
// This file automatically generated from:
//
//    $PDG_ROOT/src/bindings/common/graphics/element_ref.cpp
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
            { "getText", ElementRef_GetText, kJSPropertyAttributeDontDelete },
            { "setText", ElementRef_SetText, kJSPropertyAttributeDontDelete },
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

    JSValueRef ElementRef_GetText(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 0)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 0);
        try {return JSC_MakeValueFromCString(ctx, self->getText());}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
    }
    JSValueRef ElementRef_SetText(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    {
        ElementRef* self = static_cast<ElementRef*>(JSObjectGetPrivate(thisObject));
        ;
        if (argumentCount != 1)
            return JSC_ThrowArgCountException(ctx, exception, argumentCount, 1);if (!JSValueIsString(ctx, arguments[1 -1]))
            return JSC_ThrowArgTypeException(ctx, exception, 1, "a string (""text"")");
        JSStringRef text_Str = JSValueToStringCopy(ctx, arguments[1 -1], exception);
        MemBlock text_Mem(JSStringGetMaximumUTF8CStringSize(text_Str));
        JSStringGetUTF8CString(text_Str, text_Mem.ptr, text_Mem.bytes);
        const char* text = (const char*)text_Mem.ptr;
        JSStringRelease(text_Str);
        try {self->setText(text);}
        catch(const std::exception& error)
        {
            std::ostringstream excpt_;
            excpt_ << "throw "<< "Error" << "('" << "Error: " << error.what() << "')";
            JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
            return JSValueMakeNull(ctx);
        }
        return JSValueMakeUndefined(ctx);
    }

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
        uint32 controlPointIndex = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
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
        uint32 controlPointIndex = pdg::JSC_NumberToUint32(JSValueToNumber(ctx, arguments[1 -1], exception));
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

}
