// -----------------------------------------------
// attributes.cpp
//
// Class-specific JavaScript bindings.
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "attributes_impl_macros.h"
#include "graphics_macros.h"
#include "../animation/animation_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>
%#include <cmath>
%#include <limits>


namespace pdg {

// ========================================================================================
//MARK: Attributes
// ========================================================================================


WRAPPER_INITIALIZER_IMPL_CUSTOM(Attributes,
    OBJECT_SAVE(cppObj->mAttributesScriptObj, obj))
    EXPORT_CLASS_SYMBOLS("Attributes", Attributes, , , HAS_ATTRIBUTES_METHODS(Attributes));
    END
CLEANUP_IMPL(Attributes)
CPP_MANAGED_CONSTRUCTOR_IMPL(Attributes)
    SETUP_NON_SCRIPT_CALL;
    return new Attributes();
    END
ATTRIBUTES_METHODS_IMPL(Attributes, Attributes)

// Multiple inheritance needs an adjusted Attributes pointer, not a reinterpret cast.
Attributes* ExtractAttributes(VALUE_REF value) {
%#ifdef PDG_USING_JAVASCRIPT_CORE
    JSContextRef ctx = gMainContext;
    if (JSValueIsObjectOfClass(ctx, value, AnimatedAttributesBase_class()))
        return static_cast<Attributes*>(AnimatedAttributesBase_getCppObject(JSValueToObject(ctx,value,nullptr)));
    if (JSValueIsObjectOfClass(ctx, value, Attributes_class()))
        return Attributes_getCppObject(JSValueToObject(ctx,value,nullptr));
%#else
    auto* wrapper = v8script::safe_unwrap_object_wrap_or_prototype(v8::Isolate::GetCurrent(),value);
    if (auto* animated = dynamic_cast<AnimatedAttributesBaseWrap*>(wrapper))
        return static_cast<Attributes*>(animated->getCppObject());
    if (auto* attributes = dynamic_cast<AttributesWrap*>(wrapper))
        return attributes->getCppObject();
%#endif
    return nullptr;
}

} // namespace pdg

/* @pdg-member
{
  "name": "Attributes.Attributes",
  "type": "constructor",
  "params": [],
  "returns": "object Attributes",
  "brief": "Create a Attributes instance."
}
*/

// @pdg-member {"name":"Attributes.withAppearance","native_binding":{"binding_name":"_withAppearance"}}

// @pdg-member {"name":"Attributes.getFont","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Attributes.font","native_binding":{"allow_raw_pointers":true}}

// @pdg-member {"name":"Attributes.getTexture","native_binding":{"allow_raw_pointers":true}}

// @pdg-class {"name":"Attributes","native_binding":{"browser":{"generate":true,"base":null,"constructors":[{"types":[]}],"defaults":{"exceptions":"javascript"},"argument":{"alternatives":[{"type":"AnimatedAttributes","borrow":"_attributes"}]}}}}

// @pdg-member {"name":"Attributes.texture","native_binding":{"allow_raw_pointers":true}}
