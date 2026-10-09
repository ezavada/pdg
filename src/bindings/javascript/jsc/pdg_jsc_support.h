// -----------------------------------------------
// pdg_jsc_support.h
// 
// Stuff to support JavaScriptCore bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
//
// This is the Proprietary and Confidential intellectual
// property of Dream Rock Studios, LLC and its authors
// 
// Copying, Redistribution, or Use of this file without
// license from Dream Rock Studios, LLC is prohibited
// -----------------------------------------------


#ifndef PDG_JSC_SUPPORT_H_INCLUDED
#define PDG_JSC_SUPPORT_H_INCLUDED

#include "pdg_project.h"

// don't do anything unless we are actually targetting Javascript
#ifdef PDG_COMPILING_FOR_JAVASCRIPT

#include <JavaScriptCore/JavaScript.h>

#include "pdg/sys/color.h"
#include "pdg/sys/coordinates.h"
#include "memblock.h"
#include <optional>

#include <time.h>

namespace pdg {
  // ECMAScript ToInt32/ToUint32: truncate, then wrap modulo 2^32.
  int32 JSC_NumberToInt32(double value);
  uint32 JSC_NumberToUint32(double value);
  class Spline; // Forward declaration

const char* JSC_GetFunctionName(JSContextRef ctx, JSObjectRef func);
const char* JSC_GetFunctionFileAndLine(JSContextRef ctx, JSObjectRef func);
const char* JSC_GetObjectClassName(JSContextRef ctx, JSObjectRef func);

JSValueRef JSC_ThrowArgCountException(JSContextRef ctx, JSValueRef* exception, size_t argc, int requiredCount = 0, bool allowExtra = false);
JSValueRef JSC_ThrowArgTypeException(JSContextRef ctx, JSValueRef* exception, int argn, const char* mustBeStr, JSValueRef val = 0);

// these let us set a prototype that will be used when an object of a particulr JavaScript class is created
void JSC_SetOffsetPrototype(JSObjectRef obj);
void JSC_SetPointPrototype(JSObjectRef obj);
void JSC_SetVectorPrototype(JSObjectRef obj);
void JSC_SetRectPrototype(JSObjectRef obj);
void JSC_SetRotatedRectPrototype(JSObjectRef obj);
void JSC_SetQuadPrototype(JSObjectRef obj);
void JSC_SetColorPrototype(JSObjectRef obj);
void JSC_SetMemBlockPrototype(JSObjectRef obj);

bool JSC_ValueIsObjectWithProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithDataProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithNumProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithBoolProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithStringProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithObjectProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ValueIsObjectWithFunctionProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);

bool JSC_ObjectHasDataProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ObjectHasNumProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ObjectHasBoolProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ObjectHasStringProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ObjectHasObjectProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);
bool JSC_ObjectHasFunctionProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception);

void JSC_DebugPrintValue(JSContextRef ctx, JSValueRef val, const char* label = 0);
void JSC_DebugPrintObject(JSContextRef ctx, JSObjectRef obj, const char* label = 0);

bool JSC_ValueIsFunction(JSContextRef ctx, JSValueRef funcVal, JSValueRef* exception);

JSObjectRef JSC_ValueToFunction(JSContextRef ctx, JSValueRef funcVal, JSValueRef* exception);

JSValueRef JSC_ValueGetObjectProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception);

JSValueRef JSC_MakeValueFromCString(JSContextRef ctx, const char* s);

JSObjectRef JSC_ObjectCreateEmpty(JSContextRef ctx, void* privateDataPtr = 0);

JSObjectRef JSC_CreateClassConstructor(JSContextRef ctx, const char* className,
    JSObjectRef nativeConstructor, JSValueRef* exception);
void JSC_RegisterClassConstructor(JSClassRef jsClass, JSObjectRef constructor);
void JSC_SetObjectClassConstructor(JSContextRef ctx, JSObjectRef obj, JSClassRef jsClass);

JSValueRef JSC_ExecuteScriptFile(const char *scriptPath, JSValueRef* exception);

JSValueRef JSC_TimeToValue(JSContextRef ctx, time_t t, JSValueRef* exception);

char* JSC_CreateStringWithContentsOfFile(const char* fileName, const char* openMode = "r");

JSValueRef JSC_OffsetToValue(JSContextRef ctx, Offset& o, JSValueRef* exception);
JSValueRef JSC_PointToValue(JSContextRef ctx, Point& p, JSValueRef* exception);
JSValueRef JSC_VectorToValue(JSContextRef ctx, Vector& v, JSValueRef* exception);
JSValueRef JSC_RectToValue(JSContextRef ctx, Rect& r, JSValueRef* exception);
JSValueRef JSC_RectToValue(JSContextRef ctx, RotatedRect& r, JSValueRef* exception);
JSValueRef JSC_QuadToValue(JSContextRef ctx, Quad& q, JSValueRef* exception);
JSValueRef JSC_ColorToValue(JSContextRef ctx, Color& q, JSValueRef* exception);
JSValueRef JSC_MemBlockToValue(JSContextRef ctx, MemBlock& mb, JSValueRef* exception);
JSValueRef JSC_SplineToValue(JSContextRef ctx, Spline& s, JSValueRef* exception);

Rect		JSC_ValueToRect(JSContextRef ctx, JSValueRef val, JSValueRef* exception);
RotatedRect	JSC_ValueToRotatedRect(JSContextRef ctx, JSValueRef val, JSValueRef* exception);
Quad		JSC_ValueToQuad(JSContextRef ctx, JSValueRef val, JSValueRef* exception);
Spline*     JSC_ValueToSpline(JSContextRef ctx, JSValueRef val, JSValueRef* exception);

std::optional<bool> JSC_ValueIsOffset(JSContextRef ctx, JSValueRef val, Offset& value, JSValueRef* exception);
// true: converted, false: invalid shape, nullopt: pending JavaScript exception.
std::optional<bool> JSC_ValueIsPoint(JSContextRef ctx, JSValueRef val, Point& point, JSValueRef* exception);
std::optional<bool> JSC_ValueIsVector(JSContextRef ctx, JSValueRef val, Vector& value, JSValueRef* exception);
std::optional<bool> JSC_ValueIsRect(JSContextRef ctx, JSValueRef val, Rect& value, JSValueRef* exception);
std::optional<bool> JSC_ValueIsRotatedRect(JSContextRef ctx, JSValueRef val, RotatedRect& value, JSValueRef* exception);
std::optional<bool> JSC_ValueIsQuad(JSContextRef ctx, JSValueRef val, Quad& value, JSValueRef* exception);
std::optional<bool> JSC_ValueIsColor(JSContextRef ctx, JSValueRef val, Color& value, JSValueRef* exception);
bool JSC_ValueIsSpline(JSContextRef ctx, JSValueRef val);

// Tries to call process._fatalException() in JavaScript. If that
// returns true, execution proceeds, otherwise we log the error
// and exit.
// exceptionData is the Error object or message string that was thrown
// inFunc is the JavaScript entry point we called from C++, or NULL
void FatalException(JSValueRef exception, JSObjectRef inFunc = 0);

} // end namespace pdg

#endif // PDG_COMPILING_FOR_JAVASCRIPT

#endif // PDG_JSC_SUPPORT_H_INCLUDED
