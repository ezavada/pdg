// -----------------------------------------------
// animated_attributes.cpp
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

%#ifdef PDG_USING_JAVASCRIPT_CORE
static void AnimatedAttributesBase_finalize(JSObjectRef object) {
    delete static_cast<AnimatedAttributesBase*>(JSObjectGetPrivate(object));
    JSObjectSetPrivate(object, nullptr);
}
%#endif
WRAPPER_INITIALIZER_IMPL_CUSTOM(AnimatedAttributesBase,
    OBJECT_SAVE(cppObj->mAnimatedScriptObj, obj))
    EXPORT_DERIVED_CLASS_SYMBOLS("AnimatedAttributes", AnimatedAttributesBase, AnimatedBase, AnimatedAttributesBase_finalize, , ,
        HAS_ANIMATED_METHODS(AnimatedAttributesBase)
        HAS_ATTRIBUTES_METHODS(AnimatedAttributesBase)
        HAS_METHOD(AnimatedAttributesBase, "animate", Animate)
        HAS_METHOD(AnimatedAttributesBase, "_setDrawingLayout", SetDrawingLayout)
        HAS_METHOD(AnimatedAttributesBase, "changeLineColor", ChangeLineColor)
        HAS_METHOD(AnimatedAttributesBase, "changeLineThickness", ChangeLineThickness)
        HAS_METHOD(AnimatedAttributesBase, "changeLineOpacity", ChangeLineOpacity)
        HAS_METHOD(AnimatedAttributesBase, "changeFillColor", ChangeFillColor)
        HAS_METHOD(AnimatedAttributesBase, "changeFillOpacity", ChangeFillOpacity)
        HAS_METHOD(AnimatedAttributesBase, "changeRoundedCorners", ChangeRoundedCorners)
        HAS_METHOD(AnimatedAttributesBase, "changeTextSize", ChangeTextSize)
        HAS_METHOD(AnimatedAttributesBase, "changeSubsection", ChangeSubsection)
        HAS_METHOD(AnimatedAttributesBase, "changePolarOffset", ChangePolarOffset)
        HAS_METHOD(AnimatedAttributesBase, "changeLightOffset", ChangeLightOffset)
        HAS_METHOD(AnimatedAttributesBase, "changeAmbientLight", ChangeAmbientLight)
        HAS_METHOD(AnimatedAttributesBase, "changeFillGradient", ChangeFillGradient)
        HAS_METHOD(AnimatedAttributesBase, "changeFillRadialGradient", ChangeFillRadialGradient)
        HAS_METHOD(AnimatedAttributesBase, "changeSphereRotation", ChangeSphereRotation)
        HAS_METHOD(AnimatedAttributesBase, "changeFrames", ChangeFrames)
        HAS_METHOD(AnimatedAttributesBase, "changeSkew", ChangeSkew)
        HAS_METHOD(AnimatedAttributesBase, "changeTransform", ChangeTransform)

    );
    END
CPP_MANAGED_CONSTRUCTOR_IMPL(AnimatedAttributesBase)
    SETUP_NON_SCRIPT_CALL;
    if (ARGC > 1) { SAVE_TYPE_ERR("AnimatedAttributes accepts optional Attributes"); return nullptr; }
    Attributes* initial = nullptr;
    if (ARGC == 1 && !VALUE_IS_NULL(ARGV[0]) && !VALUE_IS_UNDEFINED(ARGV[0])) {
        initial = ExtractAttributes(ARGV[0]);
        if (!initial) { SAVE_TYPE_ERR("Expected Attributes or AnimatedAttributes"); return nullptr; }
    }
    AnimatedAttributesBase* result;
    try { result = initial ? new AnimatedAttributesBase(*initial) : new AnimatedAttributesBase(); }
    catch (const std::exception& error) { SAVE_RANGE_ERR(error.what()); return nullptr; }
%#ifndef PDG_USING_JAVASCRIPT_CORE
    result->mAnimatedScriptObj.Reset(isolate, THIS);
    result->mAnimatedScriptObj.SetWeak();
%#endif
    return result;
    END
ANIMATED_BASE_CLASS_IMPL(AnimatedAttributesBase)
ATTRIBUTES_METHODS_IMPL(AnimatedAttributesBase, AnimatedAttributes)

METHOD_IMPL(AnimatedAttributesBase, SetDrawingLayout)
    METHOD_SIGNATURE("internal MVC drawing sample", undefined, 1, (boolean enabled));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_BOOL_ARG(1, enabled);
    self->setDrawingLayout(enabled);
    NO_RETURN;
    END

METHOD_IMPL(AnimatedAttributesBase, Animate)
    METHOD_SIGNATURE("advance attributes in seconds", boolean, 1, (number deltaSeconds));
    REQUIRE_ARG_COUNT(1); REQUIRE_NUMBER_ARG(1, deltaSeconds);
    try { RETURN_BOOL(self->animate(deltaSeconds)); }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeLineColor)
    METHOD_SIGNATURE("Animate stroke color.", [this], 3, ({[object Color const&] target|string targetColorName|number targetRGBA}, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_COLOR_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeLineColor(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeLineThickness)
    METHOD_SIGNATURE("Animate stroke thickness.", [this], 3, (number target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeLineThickness(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeLineOpacity)
    METHOD_SIGNATURE("Animate stroke opacity.", [this], 3, (number target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeLineOpacity(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeFillColor)
    METHOD_SIGNATURE("Animate solid fill color.", [this], 3, ({[object Color const&] target|string targetColorName|number targetRGBA}, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_COLOR_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeFillColor(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeFillOpacity)
    METHOD_SIGNATURE("Animate fill opacity.", [this], 3, (number target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeFillOpacity(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeRoundedCorners)
    METHOD_SIGNATURE("Animate corner radius.", [this], 3, (number target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeRoundedCorners(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeTextSize)
    METHOD_SIGNATURE("Animate text size.", [this], 3, (number target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeTextSize(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeSubsection)
    METHOD_SIGNATURE("Animate image subsection.", [this], 3, ([object Rect const&] target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_RECT_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeSubsection(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangePolarOffset)
    METHOD_SIGNATURE("Animate sphere polar offset.", [this], 3, ([object Offset const&] target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_OFFSET_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changePolarOffset(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeLightOffset)
    METHOD_SIGNATURE("Animate sphere light offset.", [this], 3, ([object Offset const&] target, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_OFFSET_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeLightOffset(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeAmbientLight)
    METHOD_SIGNATURE("Animate ambient light color.", [this], 3, ({[object Color const&] target|string targetColorName|number targetRGBA}, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_COLOR_ARG(1, target);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeAmbientLight(target, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeFillGradient)
    METHOD_SIGNATURE("Animate a linear fill gradient.", [this], 6, ([object Point const&] start, {[object Color const&] startColor|string startColorName|number startRGBA}, [object Point const&] end, {[object Color const&] endColor|string endColorName|number endRGBA}, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(5);
    REQUIRE_POINT_ARG(1, start);
    REQUIRE_COLOR_ARG(2, startColor);
    REQUIRE_POINT_ARG(3, end);
    REQUIRE_COLOR_ARG(4, endColor);
    REQUIRE_NUMBER_ARG(5, seconds);
    OPTIONAL_NUMBER_ARG(6, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeFillGradient(start, startColor, end, endColor, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeFillRadialGradient)
    METHOD_SIGNATURE("Animate a radial fill gradient.", [this], 6, ([object Point const&] center, {[object Color const&] centerColor|string centerColorName|number centerRGBA}, number radius, {[object Color const&] endColor|string endColorName|number endRGBA}, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(5);
    REQUIRE_POINT_ARG(1, center);
    REQUIRE_COLOR_ARG(2, centerColor);
    REQUIRE_NUMBER_ARG(3, radius);
    REQUIRE_COLOR_ARG(4, endColor);
    REQUIRE_NUMBER_ARG(5, seconds);
    OPTIONAL_NUMBER_ARG(6, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeFillRadialGradient(center, centerColor, radius, endColor, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeSphereRotation)
    METHOD_SIGNATURE("Animate spherical-image rotation.", [this], 4, (number radians, number seconds, [number int] easing = linearTween, [number int] direction = rotationDirection_AsSpecified));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_NUMBER_ARG(1, radians);
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    OPTIONAL_NUMBER_ARG(4, directionValue, static_cast<int>(rotationDirection_AsSpecified));
    if (!std::isfinite(directionValue) || std::floor(directionValue) != directionValue ||
        directionValue < std::numeric_limits<int>::min() || directionValue > std::numeric_limits<int>::max()) {
        THROW_RANGE_ERR("Expected an integer rotation direction"); RETURN_NULL;
    }
    const int direction = static_cast<int>(directionValue);
    try { self->changeSphereRotation(radians, seconds, gEasingFunctions[easing], direction); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeFrames)
    METHOD_SIGNATURE("Animate an inclusive sequence of image frames.", [this], 4, ([number int] first, [number int] last, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(3);
    REQUIRE_NUMBER_ARG(1, firstValue);
    if (!std::isfinite(firstValue) || std::floor(firstValue) != firstValue ||
        firstValue < std::numeric_limits<int>::min() || firstValue > std::numeric_limits<int>::max()) {
        THROW_RANGE_ERR("Expected an integer frame index"); RETURN_NULL;
    }
    const int first = static_cast<int>(firstValue);
    REQUIRE_NUMBER_ARG(2, lastValue);
    if (!std::isfinite(lastValue) || std::floor(lastValue) != lastValue ||
        lastValue < std::numeric_limits<int>::min() || lastValue > std::numeric_limits<int>::max()) {
        THROW_RANGE_ERR("Expected an integer frame index"); RETURN_NULL;
    }
    const int last = static_cast<int>(lastValue);
    REQUIRE_NUMBER_ARG(3, seconds);
    OPTIONAL_NUMBER_ARG(4, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeFrames(first, last, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeSkew)
    METHOD_SIGNATURE("Animate a relative shear.", [this], 4, (number x, number y, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(3);
    REQUIRE_NUMBER_ARG(1, x);
    REQUIRE_NUMBER_ARG(2, y);
    REQUIRE_NUMBER_ARG(3, seconds);
    OPTIONAL_NUMBER_ARG(4, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeSkew(x, y, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

METHOD_IMPL(AnimatedAttributesBase, ChangeTransform)
    METHOD_SIGNATURE("Animate a replacement affine matrix.", [this], 3, ([array number] matrix, number seconds, [number int] easing = linearTween));
    REQUIRE_ARG_MIN_COUNT(2);
    // Validate that argument is an array
    %#ifdef PDG_USING_JAVASCRIPT_CORE
    if (!JSValueIsArray(ctx, ARGV[0])) {
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]);
    }

    JSObjectRef matrixArray = JSValueToObject(ctx, ARGV[0], exception);
    JSStringRef lengthName = JSStringCreateWithUTF8CString("length");
    JSValueRef lengthValue = JSObjectGetProperty(ctx, matrixArray, lengthName, exception);
    JSStringRelease(lengthName);
    if (*exception) { RETURN_NULL; }
    double matrixLength = JSValueToNumber(ctx, lengthValue, exception);
    if (*exception) { RETURN_NULL; }
    if (matrixLength != 9) {
        return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]);
    }

    glm::mat3 matrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            JSValueRef element = JSObjectGetPropertyAtIndex(ctx, matrixArray, (unsigned)(i * 3 + j), exception);
            if (*exception) { RETURN_NULL; }
            if (!JSValueIsNumber(ctx, element)) {
                return JSC_ThrowArgTypeException(ctx, exception, 1, "an array of 9 numbers", ARGV[0]);
            }
            matrix[i][j] = JSValueToNumber(ctx, element, exception);
        }
    }
    %#else
    if (!ARGV[0]->IsArray()) {
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
        return;
    }
    
    // Convert JavaScript array to glm::mat3
    v8::Local<v8::Array> matrixArray = v8::Local<v8::Array>::Cast(ARGV[0]);
    if (matrixArray->Length() != 9) {
        v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
        return;
    }
    
    // Create glm::mat3 from array elements
    // GLM matrices are column-major, so we need to map the array correctly
    glm::mat3 matrix;
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            v8::Local<v8::Value> element;
            if (!matrixArray->Get(context, i * 3 + j).ToLocal(&element)) { RETURN_NULL; }
            if (!element->IsNumber()) {
                v8_ThrowArgTypeException(isolate, 1, "an array of 9 numbers");
                return;
            }
            matrix[i][j] = element.As<v8::Number>()->Value();
        }
    }
    %#endif
    
    REQUIRE_NUMBER_ARG(2, seconds);
    OPTIONAL_NUMBER_ARG(3, easingValue, 0);
    if (!std::isfinite(easingValue) || easingValue < 0 || easingValue >= NUM_EASING_FUNCTIONS || std::floor(easingValue) != easingValue) {
        THROW_RANGE_ERR("Expected an integer easing constant"); RETURN_NULL;
    }
    const int easing = static_cast<int>(easingValue);
    if (!gEasingFunctions[easing]) { THROW_RANGE_ERR("Unknown easing constant"); RETURN_NULL; }
    try { self->changeTransform(matrix, seconds, gEasingFunctions[easing]); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
    END

} // namespace pdg

/* @pdg-member
{
  "name": "AnimatedAttributes.AnimatedAttributes",
  "type": "constructor",
  "params": [
    {
      "name": "initial",
      "type": "object Attributes",
      "optional": true,
      "contract": {
        "type": "object Attributes",
        "nullable": true
      }
    }
  ],
  "returns": "object AnimatedAttributes",
  "brief": "Create animated attributes, optionally copying an appearance."
}
*/

// @pdg-class {"name":"AnimatedAttributes","mixins":["Attributes"],"native_binding":{"browser":{"generate":true,"base":"pdg::AnimatedBase","constructors":[{"types":[]},{"types":["const pdg::Attributes&"]}],"support_bindings":[{"name":"_setDrawingLayout","symbol":"pdg::AnimatedAttributesBase::setDrawingLayout"}],"defaults":{"exceptions":"javascript"}}}}
