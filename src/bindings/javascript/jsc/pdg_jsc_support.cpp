// -----------------------------------------------
// pdg_jsc_support.cpp
// 
// Stuff to support Javascript bindings
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


#include "pdg_project.h"

#include "pdg_jsc_support.h"
#include "pdg_script_macros.h"
#include "memblock.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#include "color-utils.h"

namespace pdg {

VALUE EncodeBinary(const void *buf, size_t len);
void* DecodeBinary(VALUE val, size_t* outLen);

extern JSContextRef gMainContext;

static std::map<JSClassRef, JSObjectRef> sClassConstructors;

static JSObjectRef JSC_ClassConstructorCallAsConstructor(JSContextRef ctx,
        JSObjectRef constructor, size_t argumentCount,
        const JSValueRef arguments[], JSValueRef* exception) {
	JSStringRef nativeName = JSStringCreateWithUTF8CString("_nativeConstructor");
	JSValueRef nativeValue = JSObjectGetProperty(ctx, constructor, nativeName, exception);
	JSStringRelease(nativeName);
	if (!nativeValue || !JSValueIsObject(ctx, nativeValue)) {
		return 0;
	}
	JSObjectRef nativeConstructor = JSValueToObject(ctx, nativeValue, exception);
	JSObjectRef obj = JSObjectCallAsConstructor(ctx, nativeConstructor,
		argumentCount, arguments, exception);
	if (obj) {
		JSStringRef constructorName = JSStringCreateWithUTF8CString("constructor");
		JSObjectSetProperty(ctx, obj, constructorName, constructor,
			kJSPropertyAttributeDontEnum, exception);
		JSStringRelease(constructorName);
	}
	return obj;
}

static JSValueRef JSC_ClassConstructorCallAsFunction(JSContextRef ctx,
        JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
        const JSValueRef arguments[], JSValueRef* exception) {
	return JSC_ClassConstructorCallAsConstructor(ctx, function, argumentCount,
		arguments, exception);
}

static bool JSC_ClassConstructorHasInstance(JSContextRef ctx,
        JSObjectRef constructor, JSValueRef possibleInstance,
        JSValueRef* exception) {
	if (!JSValueIsObject(ctx, possibleInstance)) {
		return false;
	}
	JSStringRef prototypeName = JSStringCreateWithUTF8CString("prototype");
	JSValueRef expectedPrototype = JSObjectGetProperty(ctx, constructor,
		prototypeName, exception);
	JSStringRelease(prototypeName);
	if (!expectedPrototype || !JSValueIsObject(ctx, expectedPrototype)) {
		return false;
	}
	JSObjectRef instance = JSValueToObject(ctx, possibleInstance, exception);
	JSValueRef prototype = JSObjectGetPrototype(ctx, instance);
	while (prototype && JSValueIsObject(ctx, prototype)) {
		if (JSValueIsStrictEqual(ctx, prototype, expectedPrototype)) {
			return true;
		}
		prototype = JSObjectGetPrototype(ctx,
			JSValueToObject(ctx, prototype, exception));
	}
	return false;
}

JSObjectRef JSC_CreateClassConstructor(JSContextRef ctx, const char* className,
        JSObjectRef nativeConstructor, JSValueRef* exception) {
	// JSObjectMakeConstructor produces an object that is constructible but whose
	// JavaScript type is not "function". Wrap it in a real JS function so the
	// exported class behaves like a normal constructor and, critically, retains
	// new.target when it is used as an ES6 superclass.
	JSStringRef functionName = JSStringCreateWithUTF8CString(className);
	JSStringRef functionBody = JSStringCreateWithUTF8CString(
		"var wrapper = arguments.callee;"
		"var object = Reflect.construct(wrapper._nativeConstructor, "
			"Array.prototype.slice.call(arguments));"
		"var target = new.target || wrapper;"
		"if (target.prototype) Object.setPrototypeOf(object, target.prototype);"
		"return object;");
	JSObjectRef constructor = JSObjectMakeFunction(ctx, functionName, 0, 0,
		functionBody, 0, 1, exception);
	JSStringRelease(functionBody);
	JSStringRelease(functionName);
	if (!constructor || (exception && *exception)) {
		return 0;
	}
	JSStringRef nativeName = JSStringCreateWithUTF8CString("_nativeConstructor");
	JSObjectSetProperty(ctx, constructor, nativeName, nativeConstructor,
		kJSPropertyAttributeDontEnum | kJSPropertyAttributeReadOnly, exception);
	JSStringRelease(nativeName);
	JSStringRef prototypeName = JSStringCreateWithUTF8CString("prototype");
	JSValueRef prototypeValue = JSObjectGetProperty(ctx, nativeConstructor,
		prototypeName, exception);
	if (prototypeValue && JSValueIsObject(ctx, prototypeValue)) {
		JSObjectSetProperty(ctx, constructor, prototypeName, prototypeValue,
			kJSPropertyAttributeDontEnum | kJSPropertyAttributeReadOnly, exception);
		JSObjectRef prototype = JSValueToObject(ctx, prototypeValue, exception);
		JSStringRef constructorName = JSStringCreateWithUTF8CString("constructor");
		JSObjectSetProperty(ctx, prototype, constructorName, constructor,
			kJSPropertyAttributeDontEnum, exception);
		JSStringRelease(constructorName);
	}
	JSStringRelease(prototypeName);
	JSStringRef nameName = JSStringCreateWithUTF8CString("name");
	JSStringRef classNameString = JSStringCreateWithUTF8CString(className);
	JSObjectSetProperty(ctx, constructor, nameName,
		JSValueMakeString(ctx, classNameString),
		kJSPropertyAttributeDontEnum | kJSPropertyAttributeReadOnly, exception);
	JSStringRelease(classNameString);
	JSStringRelease(nameName);
	return constructor;
}

void JSC_RegisterClassConstructor(JSClassRef jsClass, JSObjectRef constructor) {
	sClassConstructors[jsClass] = constructor;
}

void JSC_SetObjectClassConstructor(JSContextRef ctx, JSObjectRef obj, JSClassRef jsClass) {
	std::map<JSClassRef, JSObjectRef>::const_iterator it = sClassConstructors.find(jsClass);
	if (it == sClassConstructors.end()) {
		return;
	}
	JSStringRef prototypeName = JSStringCreateWithUTF8CString("prototype");
	JSValueRef prototype = JSObjectGetProperty(ctx, it->second, prototypeName, 0);
	if (prototype && JSValueIsObject(ctx, prototype)) {
		JSObjectSetPrototype(ctx, obj, prototype);
	}
	JSStringRelease(prototypeName);
	JSStringRef constructorName = JSStringCreateWithUTF8CString("constructor");
	JSObjectSetProperty(ctx, obj, constructorName, it->second,
		kJSPropertyAttributeDontEnum, 0);
	JSStringRelease(constructorName);
}

DECLARE_SYMBOL(x);
DECLARE_SYMBOL(y);
DECLARE_SYMBOL(top);
DECLARE_SYMBOL(left);
DECLARE_SYMBOL(bottom);
DECLARE_SYMBOL(right);
DECLARE_SYMBOL(height);
DECLARE_SYMBOL(width);
DECLARE_SYMBOL(topLeft);
DECLARE_SYMBOL(bottomRight);
DECLARE_SYMBOL(radians);
DECLARE_SYMBOL(centerOffset);
DECLARE_SYMBOL(points);
DECLARE_SYMBOL(red);
DECLARE_SYMBOL(green);
DECLARE_SYMBOL(blue);
DECLARE_SYMBOL(alpha);
DECLARE_SYMBOL(__proto__);

JSObjectRef gOffsetPrototype = 0;
JSObjectRef gPointPrototype = 0;
JSObjectRef gVectorPrototype = 0;
JSObjectRef gRectPrototype = 0;
JSObjectRef gRotatedRectPrototype = 0;
JSObjectRef gQuadPrototype = 0;
JSObjectRef gColorPrototype = 0;
JSObjectRef gMemBlockPrototype = 0;
JSObjectRef gNetServerPrototype = 0;
JSObjectRef gNetClientPrototype = 0;
JSObjectRef gNetConnectionPrototype = 0;

const char* JSC_GetFunctionName(JSContextRef ctx, JSObjectRef func) {
    if (!func) return "NULL";
    JSValueRef jsName = JSObjectGetProperty(ctx, func, _JSC_STR("name"), 0);
    if (!jsName) return "(No Name Property)";
    return "Unknown Function";
}

const char* JSC_GetFunctionFileAndLine(JSContextRef ctx, JSObjectRef func) {
    if (!func) return "??";
    JSValueRef jsFileName = JSObjectGetProperty(ctx, func, _JSC_STR("fileName"), 0);
    JSValueRef jsLineNum = JSObjectGetProperty(ctx, func, _JSC_STR("lineNumber"), 0);
    return "Unknown File:??";
}

const char* JSC_GetObjectClassName(JSContextRef ctx, JSObjectRef obj) {
    if (!obj) return "NULL";
    JSValueRef jsPrototype = JSObjectGetPrototype(ctx, obj);
	if (!jsPrototype) return "(No Prototype)";
	JSObjectRef jsPrototypeObj = JSValueToObject(ctx, jsPrototype, 0);
	if (!jsPrototypeObj) return "(No Prototype Object)";
    JSValueRef jsName = JSObjectGetProperty(ctx, jsPrototypeObj, _JSC_STR("name"), 0);
    
    return "Unknown Function";
}

JSValueRef JSC_ThrowArgCountException(JSContextRef ctx, JSValueRef* exception, size_t argc, int requiredCount, bool allowExtra) {
	std::ostringstream excpt_;
	excpt_ << "throw SyntaxError('" << "Syntax Error: " << "argument count mismatch: expected ";
	if (allowExtra) {
		excpt_ << "at least ";
	}
	excpt_ << requiredCount << ", but got ";
	if (allowExtra) {
		excpt_ << "only ";
	}
	excpt_ << argc << " arguments." << "')";
	JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
	return JSValueMakeNull(ctx);
}

JSValueRef JSC_ThrowArgTypeException(JSContextRef ctx, JSValueRef* exception, int argn, const char* mustBeStr, JSValueRef val) {
	std::ostringstream excpt_;
    excpt_ << "throw TypeError('" << "Type Error: " << "argument " << argn << " must be ";
    if (val && JSValueIsUndefined(ctx, val)) {
    	excpt_ << "an object of type " << mustBeStr << " but got undefined. Did you pass in \""
    		<< mustBeStr << "()\" instead of \"new " << mustBeStr << "()\"?'";
    } else {
    	excpt_ << mustBeStr << "')";
    }
	JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( excpt_.str().c_str()), NULL, 0, 1, exception);
	return JSValueMakeNull(ctx);
}

// these let us set a prototype that will be used when an object of a particulr JavaScript class is created
void JSC_SetOffsetPrototype(JSObjectRef obj) {
	gOffsetPrototype = obj;
}

void JSC_SetPointPrototype(JSObjectRef obj) {
	gPointPrototype = obj;
}

void JSC_SetVectorPrototype(JSObjectRef obj) {
	gVectorPrototype = obj;
}

void JSC_SetRectPrototype(JSObjectRef obj) {
	gRectPrototype = obj;
}

void JSC_SetRotatedRectPrototype(JSObjectRef obj) {
	gRotatedRectPrototype = obj;
}

void JSC_SetQuadPrototype(JSObjectRef obj) {
	gQuadPrototype = obj;
}

void JSC_SetColorPrototype(JSObjectRef obj) {
	gColorPrototype = obj;
}

void JSC_SetMemBlockPrototype(JSObjectRef obj) {
	gMemBlockPrototype = obj;
}


bool JSC_ValueIsObjectWithProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
	return JSObjectHasProperty(ctx, obj, propSymbol);
}

bool JSC_ValueIsObjectWithDataProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasDataProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ValueIsObjectWithNumProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasNumProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ValueIsObjectWithBoolProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasBoolProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ValueIsObjectWithStringProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasStringProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ValueIsObjectWithObjectProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasObjectProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ValueIsObjectWithFunctionProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, objVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return false;
    return JSC_ObjectHasFunctionProperty(ctx, obj, propSymbol, exception);
}

bool JSC_ObjectHasDataProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return !JSC_ValueIsFunction(ctx, val, exception);
}

bool JSC_ObjectHasNumProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return JSValueIsNumber(ctx, val);
}

bool JSC_ObjectHasBoolProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return JSValueIsBoolean(ctx, val);
}

bool JSC_ObjectHasStringProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return JSValueIsString(ctx, val);
}

bool JSC_ObjectHasObjectProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return JSValueIsObject(ctx, val);
}

bool JSC_ObjectHasFunctionProperty(JSContextRef ctx, JSObjectRef obj, JSStringRef propSymbol, JSValueRef* exception) {
	if (!JSObjectHasProperty(ctx, obj, propSymbol)) return false;
    JSValueRef val = JSObjectGetProperty(ctx, obj, propSymbol, exception);
    return JSC_ValueIsFunction(ctx, val, exception);
}

void JSC_DebugPrintValue(JSContextRef ctx, JSValueRef val, const char* label) {
    if (!val) {
        std::cout << label << ": C++ NULL, not a JavaScript Value!\n";
        return;
    }
    JSValueRef* exception = 0;
    JSValueRef res;
    JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
    JSObjectSetProperty(ctx, obj, SYMBOL(x), val, kJSPropertyAttributeNone, 0);
    if (label) {
        JS_EVAL(res, obj, "process._jsc_write_stdout(\"" << label << " \"); console.log(this.x); console.log(\" \" + this.x);" );
    } else {
        JS_EVAL(res, obj, "console.log(this.x); console.log(\" \" + this.x);" );
    }
}

void JSC_DebugPrintObject(JSContextRef ctx, JSObjectRef obj, const char* label) {
    if (!obj) {
        std::cout << label << ": C++ NULL, not a JavaScript Object!\n";
        return;
    }
    JSValueRef* exception = 0;
    JSValueRef res;
    if (label) {
        JS_EVAL(res, obj, "process._jsc_write_stdout(\"" << label << " \"); console.log(this); console.log(\" \" + this);");
    } else {
        JS_EVAL(res, obj, "console.log(this); console.log(\" \" + this);" );
    }
}


bool JSC_ValueIsFunction(JSContextRef ctx, JSValueRef funcVal, JSValueRef* exception) {
	if (exception) {
		*exception = 0;
	}
	if (!JSValueIsObject(ctx, funcVal)) return false;
	JSObjectRef obj = JSValueToObject(ctx, funcVal, exception);
	if (!obj) return false;
	return JSObjectIsFunction(ctx, obj);
}

JSObjectRef JSC_ValueToFunction(JSContextRef ctx, JSValueRef funcVal, JSValueRef* exception) {
	JSObjectRef obj = JSValueToObject(ctx, funcVal, exception);
	if (!obj || !JSObjectIsFunction(ctx, obj)) {
		obj = 0;
	}
	return obj;
}

JSValueRef JSC_ValueGetObjectProperty(JSContextRef ctx, JSValueRef objVal, JSStringRef propSymbol, JSValueRef* exception) {
	JSObjectRef obj = JSValueToObject(ctx, objVal, exception);
	if (!obj) return 0; // this signals that an exception was thrown
	return JSObjectGetProperty(ctx, obj, propSymbol, exception);
}

JSValueRef JSC_MakeValueFromCString(JSContextRef ctx, const char* s) {
	JSStringRef str = JSStringCreateWithUTF8CString(s);
	JSValueRef result = JSValueMakeString(ctx, str);
	JSStringRelease(str);
	return result;
}


JSValueRef JSC_TimeToValue(JSContextRef ctx, time_t t, JSValueRef* exception) {
	JSValueRef _dt_values[] = { 
		JSValueMakeNumber(ctx, t) 
	};
	return JSObjectMakeDate(ctx, 1, _dt_values, exception);
}

JSObjectRef JSC_ObjectCreateEmpty(JSContextRef ctx, void* privateDataPtr) {
    // A JSClassRef describes a reusable object class. Creating a new class for
    // every temporary event/value object leaks the class and forces JSC to
    // accumulate a distinct Structure for every instance.
    static JSClassRef dataClass = 0;
    if (!dataClass) {
        JSClassDefinition definition = kJSClassDefinitionEmpty;
        dataClass = JSClassCreate(&definition);
    }
    return JSObjectMake(ctx, dataClass, privateDataPtr);
}

void FatalException(JSValueRef exceptionData, JSObjectRef inFunc) {
// TODO: Try to call process._fatalException() in JavaScript. If that
// returns true, execution proceeds, otherwise we log the error
// and exit.
    char* src = 0;
    long line;
    JSStringRef msgStr;
    size_t bytes;
    if (JSC_ValueIsObjectWithStringProperty(gMainContext, exceptionData, _JSC_STR("sourceURL"), 0)) {
        JSObjectRef obj = JSValueToObject(gMainContext, exceptionData, 0);
        // extract the sourceURL -> C String
        JSValueRef sourceURLVal = JSObjectGetProperty(gMainContext, obj, _JSC_STR("sourceURL"), 0);
        JSStringRef srcStr = JSValueToStringCopy(gMainContext, sourceURLVal, 0);
        bytes = JSStringGetMaximumUTF8CStringSize(srcStr);
        src = (char*) std::malloc(bytes);
        JSStringGetUTF8CString(srcStr, src, bytes);
        JSStringRelease(srcStr);
        // extract the line number into a long
        JSValueRef lineVal = JSObjectGetProperty(gMainContext, obj, _JSC_STR("line"), 0);
        line = floor(JSValueToNumber(gMainContext, lineVal, 0));
    }
    // call toString() on the object, which gives us error type as well as message
    msgStr = JSValueToStringCopy(gMainContext, exceptionData, 0);
    bytes = JSStringGetMaximumUTF8CStringSize(msgStr);
    char* msg = (char*)std::malloc(bytes);
    JSStringGetUTF8CString(msgStr, msg, bytes);
    JSStringRelease(msgStr);
    
    std::cerr << "Fatal Exception";
    if (src) {
        std::cerr << " in " << src << ":" << line;
        std::free((void*)src);
    } 
    std::cerr << " - " << msg << "\n";
    std::free((void*)msg);
    if (JSC_ValueIsObjectWithStringProperty(gMainContext, exceptionData, _JSC_STR("stack"), 0)) {
        JSObjectRef error = JSValueToObject(gMainContext, exceptionData, 0);
        JSValueRef stack = JSObjectGetProperty(gMainContext, error, _JSC_STR("stack"), 0);
        JSStringRef stackString = JSValueToStringCopy(gMainContext, stack, 0);
        size_t capacity = JSStringGetMaximumUTF8CStringSize(stackString);
        std::vector<char> trace(capacity);
        JSStringGetUTF8CString(stackString, trace.data(), capacity);
        JSStringRelease(stackString);
        std::cerr << trace.data() << "\n";
    }

    exit(1);
}

JSValueRef JSC_OffsetToValue(JSContextRef ctx, Offset& o, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(x), NUM2VAL(o.x), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(y), NUM2VAL(o.y), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gOffsetPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_PointToValue(JSContextRef ctx, Point& p, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(x), NUM2VAL(p.x), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(y), NUM2VAL(p.y), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gPointPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_VectorToValue(JSContextRef ctx, Vector& v, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(x), NUM2VAL(v.x), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(y), NUM2VAL(v.y), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gVectorPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_RectToValue(JSContextRef ctx, Rect& r, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(left), NUM2VAL(r.left), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(top), NUM2VAL(r.top), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(right), NUM2VAL(r.right), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(bottom), NUM2VAL(r.bottom), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gRectPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_RectToValue(JSContextRef ctx, RotatedRect& r, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(left), NUM2VAL(r.left), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(top), NUM2VAL(r.top), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(right), NUM2VAL(r.right), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(bottom), NUM2VAL(r.bottom), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(radians), NUM2VAL(r.radians), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(centerOffset), OFFSET2VAL(r.centerOffset), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gRotatedRectPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_QuadToValue(JSContextRef ctx, Quad& q, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSValueRef pointValues[4];
	for (int i = 0; i<4; i++) {
		pointValues[i] = POINT2VAL(q.points[i]);
		JSObjectSetPropertyAtIndex(ctx, obj, i, pointValues[i], exception);
	}
	JSObjectRef pointArray = JSObjectMakeArray(ctx, 4, pointValues, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(points), pointArray,
		kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gQuadPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_ColorToValue(JSContextRef ctx, Color& c, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	JSObjectSetProperty(ctx, obj, SYMBOL(red), NUM2VAL(c.red), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(green), NUM2VAL(c.green), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(blue), NUM2VAL(c.blue), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(alpha), NUM2VAL(c.alpha), kJSPropertyAttributeNone, exception);
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gColorPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}

JSValueRef JSC_MemBlockToValue(JSContextRef ctx, MemBlock& mb, JSValueRef* exception) {
	JSObjectRef obj = JSC_ObjectCreateEmpty(ctx);
	// Note: MemBlock objects are created with their data already set, so we don't need to set properties here
	JSObjectSetProperty(ctx, obj, SYMBOL(__proto__), gMemBlockPrototype, kJSPropertyAttributeNone, exception);
  	return obj;
}








Rect JSC_ValueToRect(JSContextRef ctx, JSValueRef val, JSValueRef* exception) {
    Rect result;
    auto converted = JSC_ValueIsRect(ctx, val, result, exception);
    if (converted.has_value() && !*converted) { JSC_ThrowArgTypeException(ctx, exception, 1, "Rect", val); }
    return result;
}

RotatedRect JSC_ValueToRotatedRect(JSContextRef ctx, JSValueRef val, JSValueRef* exception) {
    RotatedRect result;
    auto converted = JSC_ValueIsRotatedRect(ctx, val, result, exception);
    if (converted.has_value() && !*converted) { JSC_ThrowArgTypeException(ctx, exception, 1, "RotatedRect", val); }
    return result;
}

Quad JSC_ValueToQuad(JSContextRef ctx, JSValueRef val, JSValueRef* exception) {
    Quad result;
    auto converted = JSC_ValueIsQuad(ctx, val, result, exception);
    if (converted.has_value() && !*converted) { JSC_ThrowArgTypeException(ctx, exception, 1, "Quad", val); }
    return result;
}




std::optional<bool> JSC_ValueIsOffset(JSContextRef ctx, JSValueRef val, Offset& value, JSValueRef* exception) {
    Point point;
    auto converted = JSC_ValueIsPoint(ctx, val, point, exception);
    if (converted.value_or(false)) value = Offset(point.x, point.y);
    return converted;
}



std::optional<bool> JSC_ValueIsPoint(JSContextRef ctx, JSValueRef val, Point& point, JSValueRef* exception) {
    if (*exception) return std::nullopt;
    if (!val || !JSValueIsObject(ctx, val)) return false;
    auto object = JSValueToObject(ctx, val, exception);
    if (*exception) return std::nullopt;

    // Keep JSC's numeric-coordinate contract, including indexed objects. Read
    // each coordinate once instead of repeating property checks and conversion.
    auto x = JSObjectGetProperty(ctx, object, SYMBOL(x), exception);
    if (*exception) return std::nullopt;
    if (JSValueIsNumber(ctx, x)) {
        auto y = JSObjectGetProperty(ctx, object, SYMBOL(y), exception);
        if (*exception) return std::nullopt;
        if (JSValueIsNumber(ctx, y)) {
            point = Point(JSValueToNumber(ctx, x, exception), JSValueToNumber(ctx, y, exception));
            return true;
        }
    }
    x = JSObjectGetPropertyAtIndex(ctx, object, 0, exception);
    if (*exception) return std::nullopt;
    if (!JSValueIsNumber(ctx, x)) return false;
    auto y = JSObjectGetPropertyAtIndex(ctx, object, 1, exception);
    if (*exception) return std::nullopt;
    if (!JSValueIsNumber(ctx, y)) return false;
    point = Point(JSValueToNumber(ctx, x, exception), JSValueToNumber(ctx, y, exception));
    return true;
}

std::optional<bool> JSC_ValueIsVector(JSContextRef ctx, JSValueRef val, Vector& value, JSValueRef* exception) {
    Point point;
    auto converted = JSC_ValueIsPoint(ctx, val, point, exception);
    if (converted.value_or(false)) value = Vector(point.x, point.y);
    return converted;
}

class JSCPropertyReader {
public:
    JSCPropertyReader(JSContextRef ctx, JSValueRef* exception) : ctx(ctx), exception(exception) {}
    JSValueRef get(JSObjectRef object, JSStringRef key) {
        if (failed()) return JSValueMakeUndefined(ctx);
        return JSObjectGetProperty(ctx, object, key, exception);
    }
    JSValueRef get(JSObjectRef object, unsigned index) {
        if (failed()) return JSValueMakeUndefined(ctx);
        return JSObjectGetPropertyAtIndex(ctx, object, index, exception);
    }
    bool isNumber(JSValueRef value) const { return !failed() && value && JSValueIsNumber(ctx, value); }
    double number(JSValueRef value) { return failed() ? 0 : JSValueToNumber(ctx, value, exception); }
    bool failed() const { return *exception != nullptr; }
private:
    JSContextRef ctx;
    JSValueRef* exception;
};

static std::optional<bool> JSC_ReadRect(JSContextRef ctx, JSValueRef val, Rect& rect, JSValueRef* exception, bool arrayCheck) {
    if (*exception) return std::nullopt;
    if (!val || !JSValueIsObject(ctx, val)) return false;
    auto object = JSValueToObject(ctx, val, exception);
    JSCPropertyReader read(ctx, exception);
    auto height = read.get(object, SYMBOL(height));
    if (read.isNumber(height)) {
        auto width = read.get(object, SYMBOL(width));
        if (read.isNumber(width)) {
            Point topLeft;
            auto corner = read.get(object, SYMBOL(topLeft));
            if (read.failed()) return std::nullopt;
            if (JSValueIsObject(ctx, corner)) {
                auto isPoint = JSC_ValueIsPoint(ctx, corner, topLeft, exception);
                if (!isPoint.value_or(false)) return isPoint;
            }
            rect = Rect(topLeft, read.number(width), read.number(height));
            return true;
        }
    }
    if (read.failed()) return std::nullopt;
    Point topLeft, bottomRight;
    bool hasTopLeft = false, hasBottomRight = false;
    auto top = read.get(object, SYMBOL(top));
    if (read.isNumber(top)) {
        auto left = read.get(object, SYMBOL(left));
        if (read.isNumber(left)) {
            topLeft = Point(read.number(left), read.number(top));
            hasTopLeft = true;
        }
    }
    if (!hasTopLeft) {
        auto corner = read.get(object, SYMBOL(topLeft));
        if (read.failed()) return std::nullopt;
        auto isPoint = JSC_ValueIsPoint(ctx, corner, topLeft, exception);
        if (!isPoint.has_value()) return std::nullopt;
        hasTopLeft = *isPoint;
    }
    auto bottom = read.get(object, SYMBOL(bottom));
    if (read.isNumber(bottom)) {
        auto right = read.get(object, SYMBOL(right));
        if (read.isNumber(right)) {
            bottomRight = Point(read.number(right), read.number(bottom));
            hasBottomRight = true;
        }
    }
    if (!hasBottomRight) {
        auto corner = read.get(object, SYMBOL(bottomRight));
        if (read.failed()) return std::nullopt;
        auto isPoint = JSC_ValueIsPoint(ctx, corner, bottomRight, exception);
        if (!isPoint.has_value()) return std::nullopt;
        hasBottomRight = *isPoint;
    }
    if (read.failed()) return std::nullopt;
    if (hasTopLeft && hasBottomRight) {
        rect = Rect(topLeft, bottomRight);
        return true;
    }
    if (!arrayCheck) return false;
    JSValueRef values[4];
    bool numbers[4];
    for (unsigned i = 0; i < 4; ++i) {
        values[i] = read.get(object, i);
        if (read.failed()) return std::nullopt;
        numbers[i] = read.isNumber(values[i]);
    }
    if (numbers[0] && numbers[1]) {
        if (numbers[2] && numbers[3]) {
            rect = Rect(read.number(values[0]), read.number(values[1]), read.number(values[2]), read.number(values[3]));
        } else {
            Point origin;
            auto isPoint = JSC_ValueIsPoint(ctx, values[2], origin, exception);
            if (!isPoint.has_value()) return std::nullopt;
            rect = Rect(origin, read.number(values[0]), read.number(values[1]));
        }
        return true;
    }
    auto isPoint = JSC_ValueIsPoint(ctx, values[0], topLeft, exception);
    if (!isPoint.value_or(false)) return isPoint;
    if (numbers[1] && numbers[2]) {
        rect = Rect(topLeft, read.number(values[1]), read.number(values[2]));
        return true;
    }
    isPoint = JSC_ValueIsPoint(ctx, values[1], bottomRight, exception);
    if (!isPoint.value_or(false)) return isPoint;
    rect = Rect(topLeft, bottomRight);
    return true;
}

std::optional<bool> JSC_ValueIsRect(JSContextRef ctx, JSValueRef val, Rect& rect, JSValueRef* exception) {
    return JSC_ReadRect(ctx, val, rect, exception, true);
}

static std::optional<bool> JSC_ReadRectRotation(JSContextRef ctx, JSObjectRef object, RotatedRect& rect, JSValueRef* exception) {
    JSCPropertyReader read(ctx, exception);
    auto radians = read.get(object, SYMBOL(radians));
    if (read.failed()) return std::nullopt;
    if (!JSValueIsUndefined(ctx, radians)) {
        rect.radians = read.number(radians);
        if (read.failed()) return std::nullopt;
        if (std::isnan(rect.radians)) rect.radians = 0;
    }
    auto center = read.get(object, SYMBOL(centerOffset));
    if (read.failed()) return std::nullopt;
    if (!JSValueIsUndefined(ctx, center)) {
        auto isPoint = JSC_ValueIsOffset(ctx, center, rect.centerOffset, exception);
        if (!isPoint.value_or(false)) return isPoint;
    }
    return true;
}

std::optional<bool> JSC_ValueIsRotatedRect(JSContextRef ctx, JSValueRef val, RotatedRect& rect, JSValueRef* exception) {
    Rect base;
    auto converted = JSC_ValueIsRect(ctx, val, base, exception);
    if (!converted.value_or(false)) return converted;
    RotatedRect result(base);
    converted = JSC_ReadRectRotation(ctx, JSValueToObject(ctx, val, exception), result, exception);
    if (!converted.value_or(false)) return converted;
    rect = result;
    return true;
}

std::optional<bool> JSC_ValueIsQuad(JSContextRef ctx, JSValueRef val, Quad& quad, JSValueRef* exception) {
    if (*exception) return std::nullopt;
    if (!val || !JSValueIsObject(ctx, val)) return false;
    auto object = JSValueToObject(ctx, val, exception);
    JSCPropertyReader read(ctx, exception);
    auto points = read.get(object, SYMBOL(points));
    if (read.failed()) return std::nullopt;
    bool explicitPoints = JSValueIsObject(ctx, points);
    auto array = explicitPoints ? JSValueToObject(ctx, points, exception) : object;
    JSValueRef values[8];
    bool numbers[8];
    for (unsigned i = 0; i < 4; ++i) {
        values[i] = read.get(array, i);
        if (read.failed()) return std::nullopt;
        numbers[i] = read.isNumber(values[i]);
    }
    auto finishRectangle = [&](const Rect& base) -> std::optional<bool> {
        RotatedRect rect(base);
        auto converted = JSC_ReadRectRotation(ctx, object, rect, exception);
        if (!converted.value_or(false)) return converted;
        quad = rect.radians == 0 ? Quad(static_cast<Rect>(rect)) : Quad(rect);
        return true;
    };
    if (numbers[0] && numbers[1]) {
        if (numbers[2] && numbers[3]) {
            bool allNumbers = true;
            for (unsigned i = 4; i < 8; ++i) {
                values[i] = read.get(array, i);
                if (read.failed()) return std::nullopt;
                numbers[i] = read.isNumber(values[i]);
                allNumbers &= numbers[i];
            }
            if (allNumbers) {
                Quad result;
                for (unsigned i = 0; i < 4; ++i)
                    result.points[i] = Point(read.number(values[2*i]), read.number(values[2*i+1]));
                quad = result;
                return true;
            }
            return finishRectangle(Rect(read.number(values[0]), read.number(values[1]), read.number(values[2]), read.number(values[3])));
        }
        Point origin;
        auto converted = JSC_ValueIsPoint(ctx, values[2], origin, exception);
        if (!converted.has_value()) return std::nullopt;
        return finishRectangle(Rect(origin, read.number(values[0]), read.number(values[1])));
    }
    Quad result;
    auto converted = JSC_ValueIsPoint(ctx, values[0], result.points[0], exception);
    if (!converted.has_value()) return std::nullopt;
    if (*converted) {
        if (numbers[1] && numbers[2])
            return finishRectangle(Rect(result.points[0], read.number(values[1]), read.number(values[2])));
        for (unsigned i = 1; i < 4; ++i) {
            converted = JSC_ValueIsPoint(ctx, values[i], result.points[i], exception);
            if (!converted.has_value()) return std::nullopt;
            if (!*converted) {
                if (i == 2 && JSValueIsUndefined(ctx, values[2]) && JSValueIsUndefined(ctx, values[3]))
                    return finishRectangle(Rect(result.points[0], result.points[1]));
                return false;
            }
        }
        quad = result;
        return true;
    }
    if (explicitPoints) return false;
    Rect rect;
    converted = JSC_ReadRect(ctx, val, rect, exception, false);
    if (!converted.value_or(false)) return converted;
    return finishRectangle(rect);
}

std::optional<bool> JSC_ValueIsColor(JSContextRef ctx, JSValueRef val, Color& color, JSValueRef* exception) {
    if (*exception) return std::nullopt;
    if (!val) return false;
    if (JSValueIsNumber(ctx, val)) {
        color = Color(VAL2UINT(val));
        return true;
    }
    if (JSValueIsString(ctx, val)) {
        auto text = JSValueToStringCopy(ctx, val, exception);
        if (*exception) return std::nullopt;
        std::string buffer(JSStringGetMaximumUTF8CStringSize(text), '\0');
        auto bytes = JSStringGetUTF8CString(text, buffer.data(), buffer.size());
        JSStringRelease(text);
        return parseCssColor(std::string_view(buffer.data(), bytes ? bytes - 1 : 0), color);
    }
    if (!JSValueIsObject(ctx, val)) return false;
    auto object = JSValueToObject(ctx, val, exception);
    JSCPropertyReader read(ctx, exception);
    JSValueRef values[4];
    values[0] = read.get(object, SYMBOL(red));
    bool named = read.isNumber(values[0]);
    if (named) {
        values[1] = read.get(object, SYMBOL(green));
        values[2] = read.get(object, SYMBOL(blue));
        named = read.isNumber(values[1]) && read.isNumber(values[2]);
    }
    if (read.failed()) return std::nullopt;
    if (named) values[3] = read.get(object, SYMBOL(alpha));
    else {
        for (unsigned i = 0; i < 4; ++i) values[i] = read.get(object, i);
    }
    if (read.failed()) return std::nullopt;
    bool missingAlpha = JSValueIsUndefined(ctx, values[3]);
    double channels[4] = {0, 0, 0, 1};
    bool floats = true;
    for (unsigned i = 0; i < 4; ++i) {
        if (i == 3 && missingAlpha) continue;
        if (!read.isNumber(values[i])) return false;
        channels[i] = read.number(values[i]);
        if (!std::isfinite(channels[i]) || channels[i] < 0 || channels[i] > 255) return false;
        floats &= channels[i] <= 1;
    }
    if (!floats) {
        for (unsigned i = 0; i < 4; ++i) {
            if (i != 3 || !missingAlpha) channels[i] = std::floor(channels[i]) / 255.0;
        }
    }
    color = Color(static_cast<float>(channels[0]), static_cast<float>(channels[1]),
                  static_cast<float>(channels[2]), static_cast<float>(channels[3]));
    return true;
}




VALUE EncodeBinary(const void *buf, size_t len) {
	const uint8 *cbuf = static_cast<const uint8*>(buf);
	JSChar* jsbuf = new JSChar[len];
	for (size_t i = 0; i < len; i++) {
	  jsbuf[i] = cbuf[i];
	}
	JSStringRef chunk = JSStringCreateWithCharacters(jsbuf, len);
	VALUE val = JSValueMakeString(gMainContext, chunk);
	JSStringRelease(chunk);
	delete [] jsbuf;
	return val;
}


// Returns number of bytes written. 
// call free on the pointer returned when you are done with it
void* DecodeBinary(VALUE val, size_t* outLen) {
	JSStringRef str = JSValueToStringCopy(gMainContext, val, 0);
	if (!str) return 0;
	size_t buflen = JSStringGetLength(str);
	if (outLen) {
		*outLen = buflen;
	}

	const JSChar* jsbuf = JSStringGetCharactersPtr(str);

	char* buf = (char*)std::malloc(buflen);
	for (size_t i = 0; i < buflen; i++) {
		const unsigned char* bp = reinterpret_cast<const unsigned char*>(&jsbuf[i]);
		buf[i] = *bp;
	}
	JSStringRelease(str);
	return buf;
}


/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */



JSValueRef JSC_ExecuteScriptFile(const char *scriptPath, JSValueRef* exception)
{
	char* scriptUTF8 = JSC_CreateStringWithContentsOfFile(scriptPath);
	if (!scriptUTF8) {
		return JSValueMakeUndefined(gMainContext);
	} else {
		JSStringRef script = JSStringCreateWithUTF8CString(scriptUTF8);
		JSValueRef result = JSEvaluateScript(gMainContext, script, NULL, NULL, 1, exception);
		JSStringRelease(script);
		free(scriptUTF8);
		return result;
	}
}

#include <unistd.h>

char* JSC_CreateStringWithContentsOfFile(const char* fileName, const char* openMode)
{
	char* buffer;
	
	size_t buffer_size = 0;
	size_t buffer_capacity = 1024;
	buffer = (char*)malloc(buffer_capacity);
	
	FILE* f = fopen(fileName, openMode);
	if (!f) {
//		fprintf(stderr, "Could not open file: %s\n", fileName);
		return 0;
	}
	
	while (!feof(f) && !ferror(f)) {
		buffer_size += fread(buffer + buffer_size, 1, buffer_capacity - buffer_size, f);
		if (buffer_size == buffer_capacity) { // guarantees space for trailing '\0'
			buffer_capacity *= 2;
			buffer = (char*)realloc(buffer, buffer_capacity);
//                ASSERT(buffer);
		}
		
//            ASSERT(buffer_size < buffer_capacity);
	}
	fclose(f);
	buffer[buffer_size] = '\0';
	
	return buffer;
}
    

} // end namespace pdg
