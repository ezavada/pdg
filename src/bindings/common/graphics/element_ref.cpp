// -----------------------------------------------
// element_ref.cpp
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

// ===== ElementRef Bindings =====

WRAPPER_INITIALIZER_IMPL_CUSTOM(ElementRef,
    OBJECT_SAVE(cppObj->mElementRefScriptObj, obj)
)
    EXPORT_CLASS_SYMBOLS("ElementRef", ElementRef, , ,
        // method section
        HAS_METHOD(ElementRef, "getText", GetText)
        HAS_METHOD(ElementRef, "setText", SetText)
        HAS_METHOD(ElementRef, "type", Type)
        HAS_METHOD(ElementRef, "getControlPoints", GetControlPoints)
        HAS_METHOD(ElementRef, "getControlPoint", GetControlPoint)
        HAS_METHOD(ElementRef, "changeControlPoint", ChangeControlPoint)
        HAS_METHOD(ElementRef, "getAttributes", GetAttributes)
        HAS_METHOD(ElementRef, "setAttributes", SetAttributes)
        HAS_METHOD(ElementRef, "setLiveAttributes", SetLiveAttributes)
        HAS_METHOD(ElementRef, "clearLiveAttributes", ClearLiveAttributes)
        HAS_METHOD(ElementRef, "hasLiveAttributes", HasLiveAttributes)
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

METHOD_IMPL(ElementRef, GetText)
    METHOD_SIGNATURE("Read a text element's UTF-8 contents.", string, 0, ());
    REQUIRE_ARG_COUNT(0);
    try {RETURN_STRING(self->getText());}catch(const std::exception& error) {THROW_ERR(error.what());}
END
METHOD_IMPL(ElementRef, SetText)
    METHOD_SIGNATURE("Replace a text element's UTF-8 contents.", undefined, 1, (string text));
    REQUIRE_ARG_COUNT(1);REQUIRE_STRING_ARG(1,text);
    try {self->setText(text);}catch(const std::exception& error) {THROW_ERR(error.what());}
    NO_RETURN;
END

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
    METHOD_SIGNATURE("", [object Point const&], 1, ([number uint] controlPointIndex));
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
    METHOD_SIGNATURE("", undefined, 2, ([number uint] controlPointIndex, [object Point const&] controlPoint));
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
    METHOD_SIGNATURE("", undefined, 1, ([object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_ATTRIBUTES_ARG(1, attrs);
    self->setAttributes(*attrs);
    NO_RETURN;
    END

METHOD_IMPL(ElementRef, SetLiveAttributes)
    METHOD_SIGNATURE("", undefined, 1, ([object Attributes const&] attrs));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_ATTRIBUTES_ARG(1, attrs);
    self->setLiveAttributes(*attrs);
    NO_RETURN;
    END
METHOD_IMPL(ElementRef, ClearLiveAttributes)
    METHOD_SIGNATURE("", undefined, 0, ());
    REQUIRE_ARG_COUNT(0);
    self->clearLiveAttributes();
    NO_RETURN;
    END
METHOD_IMPL(ElementRef, HasLiveAttributes)
    METHOD_SIGNATURE("", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_BOOL(self->hasLiveAttributes());
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

} // namespace pdg

// @pdg-class {"name":"ElementRef","construction":{"kind":"factory","factory":"Drawing.addLine and other element factories"},"native_binding":{"browser":{"generate":true,"base":null}}}
// @pdg-member {"name":"ElementRef.getText","native_binding":{"adapter":"ElementRef.getText"}}
// @pdg-member {"name":"ElementRef.setText","native_binding":{"adapter":"ElementRef.setText"}}

/* @pdg-contract
{
  "name": "ElementRef.getControlPoints",
  "value": {
    "returns": {
      "items": {
        "type": "object Point"
      },
      "ownership": "owned"
    }
  }
}
*/
