// -----------------------------------------------
// pdg_script_macros.h
// 
// Macros used to generate JavaScript bindings for 
// the JavaScriptCore engine
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


#ifndef PDG_SCRIPT_MACROS_H_INCLUDED
#define PDG_SCRIPT_MACROS_H_INCLUDED

#ifndef PDG_BUILDING_INTERFACE_FILES

	#define CR

	#ifdef PDG_COMPILING_SCRIPT_IMPL
		#define _JSC_SCRIPT_IMPL_ONLY( ops )	ops
	#else
		#define _JSC_SCRIPT_IMPL_ONLY( ops )
	#endif

#else

	#define CR @

#endif // PDG_BUILDING_INTERFACE_FILES

#define _JSC_STR(s)      JSStringCreateWithUTF8CString(s)   // internal you shouldn't need to use this


// ========================================================================================
//MARK: UTILITY MACROS
// ========================================================================================

// used to hold a local copy of a value, object or function
#define VALUE	 	 JSValueRef    // v8::Local<v8::Value>
#define OBJECT	 	 JSObjectRef   // v8::Local<v8::Object>
#define FUNCTION	 JSObjectRef   // v8::Local<v8::Function>

// used to hold a reference to a value, object, or function that can be passed around
#define VALUE_REF 	 JSValueRef    // v8::Handle<v8::Value>
#define OBJECT_REF	 JSObjectRef   // v8::Handle<v8::Object>
#define FUNCTION_REF JSObjectRef   // v8::Handle<v8::Function>

// used to hold a persistent copy of a value, object or function
#define SAVED_VALUE		JSValueRef    // v8::Persistent<v8::Value>
#define SAVED_OBJECT	JSObjectRef   // v8::Persistent<v8::Object>
#define SAVED_FUNCTION	JSObjectRef   // v8::Persistent<v8::Function>

// used to save a Local VALUE/OBJECT/FUNCTION into SAVED_VALUE/OBJECT/FUNCTION storage space
#define VALUE_SAVE(dst, val)		dst = val
#define OBJECT_SAVE(dst, obj)		dst = obj
#define OBJECT_SAVE_WEAK(dst, obj) dst = obj
#define FUNCTION_SAVE(dst, func)	dst = func

// calling conventions for C++ functions called from javascript
#define SCRIPT_ARGS	 	size_t argumentCount, const JSValueRef arguments[], JSValueRef* constructorException
#define ARGC			argumentCount
#define ARGV			arguments
#define THIS	 		thisObject
#define NULL_VAL		JSValueMakeNull(ctx)

#define HAVE_ONLY_ONE_NULL_ARG		(ARGC == 1 && JSValueIsNull(ctx, ARGV[0]))

// static symbols (strings) that are declared once and reused often
// avoids reallocation that comes with using JavaScript Strings
#define DECLARE_SYMBOL(sym)	static JSStringRef symbol_##sym = 0
#define SYMBOL(sym)			((symbol_##sym) ? symbol_##sym \
								: symbol_##sym = JSStringCreateWithUTF8CString(#sym))

// conversion between C++ primitives and the all-encompassing JavaScript Value type
#define STR2VAL(s)			JSC_MakeValueFromCString(ctx, s)
#define INT2VAL(n)			JSValueMakeNumber(ctx, n)
#define UINT2VAL(n)         JSValueMakeNumber(ctx, n)
#define NUM2VAL(n)          JSValueMakeNumber(ctx, n)
#define BOOL2VAL(b)         JSValueMakeBoolean(ctx, b)
//#define VAL2STR    // not that simple, use VALUE_TO_CSTRING
#define VAL2INT(val)		(int32)floor(JSValueToNumber(ctx, val, exception))
#define VAL2UINT(val)		(uint32)floor(fabs(JSValueToNumber(ctx, val, exception)))
#define VAL2NUM(val)		JSValueToNumber(ctx, val, exception)
#define VAL2BOOL(val)		JSValueToBoolean(ctx, val)

// Allocates space for a C String to hold the contents of the JavaScript String Value
// and copies the JavaScript string into it, converting from the internal JavaScript
// string representation (usually UTF-16) to UTF-8 in the process. 
// When the C variable goes out of scope the memory is automatically freed, ie:
// 
//  {  
//      VALUE_TO_CSTRING(myfilename, ARGV[0]); // myfilename declared and allocated here
//		printf("%s", myfilename);              // then freed as soon as it goes out of scope
//  }  

#define VALUE_TO_CSTRING(cVar, valVar) \
	JSStringRef cVar##_Str = JSValueToStringCopy(ctx, valVar, exception);  CR \
	MemBlock cVar##_Mem(JSStringGetMaximumUTF8CStringSize(cVar##_Str));    CR \
	JSStringGetUTF8CString(cVar##_Str, cVar##_Mem.ptr, cVar##_Mem.bytes);  CR \
	const char* cVar = (const char*)cVar##_Mem.ptr;						   CR \
	JSStringRelease(cVar##_Str)

// conversion between JavaScript functions and objects and the all-encompassing JavaScript Value type
#define FUNC2VAL(func)		func
#define OBJ2VAL(obj)		obj
#define VAL2FUNC(val)		JSC_ValueToFunction(ctx, val, exception)
#define VAL2OBJ(val)		JSValueToObject(ctx, val, exception)
#define VAL2OBJ_SAFE(val)	((val && JSValueIsObject(ctx, val)) ? JSValueToObject(ctx, val, exception) : nullptr)

#define TIME_T_TO_VALUE(time)	JSC_TimeToValue(ctx,time, exception)

// conversion between PDG coordinate types and Javascript Value type
#define OFFSET2VAL(o)	JSC_OffsetToValue(ctx, o, exception)
#define POINT2VAL(p)	JSC_PointToValue(ctx, p, exception)
#define VECTOR2VAL(v)	JSC_VectorToValue(ctx, v, exception)
#define RECT2VAL(r)		JSC_RectToValue(ctx, r, exception)
#define ROTRECT2VAL(rr)	JSC_RectToValue(ctx, rr, exception)
#define QUAD2VAL(q)		JSC_QuadToValue(ctx, q, exception)
#define COLOR2VAL(c)	JSC_ColorToValue(ctx, c, exception)

#define VAL2RECT(val)		JSC_ValueToRect(ctx, val, exception)
#define VAL2ROTRECT(val)	JSC_ValueToRotatedRect(ctx, val, exception)
#define VAL2QUAD(val)		JSC_ValueToQuad(ctx, val, exception)

#define VALUE_IS_OFFSET(val, value) JSC_ValueIsOffset(ctx, val, value, exception)
// Fills point on success; false means invalid, nullopt preserves a script exception.
#define VALUE_IS_POINT(val, point) JSC_ValueIsPoint(ctx, val, point, exception)
#define VALUE_IS_VECTOR(val, value) JSC_ValueIsVector(ctx, val, value, exception)
#define VALUE_IS_RECT(val, value) JSC_ValueIsRect(ctx, val, value, exception)
#define VALUE_IS_ROTRECT(val, value) JSC_ValueIsRotatedRect(ctx, val, value, exception)
#define VALUE_IS_QUAD(val, value) JSC_ValueIsQuad(ctx, val, value, exception)
#define VALUE_IS_COLOR(val, value) JSC_ValueIsColor(ctx, val, value, exception)

// JavaScript Value query functions
#define VALUE_IS_UNDEFINED(val)							JSValueIsUndefined(ctx, val)
#define VALUE_IS_NULL(val)								JSValueIsNull(ctx, val)

#define VALUE_IS_BOOL(val)								JSValueIsBoolean(ctx, val)
#define VALUE_IS_TRUE(val)								(JSValueToBoolean(ctx, val, exception) == true)
#define VALUE_IS_FALSE(val)								(JSValueToBoolean(ctx, val, exception) == false)
#define VALUE_IS_EXACTLY_TRUE(val)						(VALUE_IS_BOOL(val) && VALUE_IS_TRUE(val))
#define VALUE_IS_EXACTLY_FALSE(val)						(VALUE_IS_BOOL(val) && VALUE_IS_FALSE(val))

#define VALUE_IS_NUMBER(val)							JSValueIsNumber(ctx, val)
#define VALUE_IS_STRING(val)							JSValueIsString(ctx, val)
#define VALUE_IS_FUNCTION(val)							JSC_ValueIsFunction(ctx, val, exception)
 
#define VALUE_IS_OBJECT(val)							JSValueIsObject(ctx, val)
#define VALUE_IS_OBJECT_OF_CLASS(val, klass)			JSValueIsObjectOfClass(ctx, val, klass##_class())
#define EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(val, paramName, klass) \
	klass* paramName = 0;									CR \
	if (VALUE_IS_OBJECT(val)) {						    	CR \
		JSObjectRef paramName##_obj_ = VAL2OBJ(val);  		CR \
		paramName = klass##_getCppObject(paramName##_obj_);	CR \
		if (!paramName) {									CR \
			JSValueRef protoVal_ = JSObjectGetPrototype(ctx, paramName##_obj_); CR \
			if (protoVal_ && JSValueIsObject(ctx, protoVal_)) { CR \
				JSObjectRef protoObj_ = VAL2OBJ(protoVal_);	CR \
				paramName = klass##_getCppObject(protoObj_);	CR \
			}												CR \
		}													CR \
	}
#define VALUE_IS_OBJECT_WITH_PROPERTY(val, propSymbol)  JSC_ValueIsObjectWithProperty(ctx, val, propSymbol, exception)

// shortcut to get an object property directly from a value 
// without converting to an object first
#define VALUE_GET_OBJECT_PROPERTY(objVal, propSymbol) 	JSC_ValueGetObjectProperty(ctx, objVal, propSymbol, exception)

// JavaScript object query methods
#define OBJECT_HAS_PROPERTY(obj, propSymbol)            (obj && JSObjectHasProperty(ctx, obj, propSymbol))
#define OBJECT_GET_PROPERTY(obj, propSymbol) 			JSObjectGetProperty(ctx, obj, propSymbol, exception)
#define OBJECT_SET_PROPERTY_VALUE(obj, propSymbol, val) JSObjectSetProperty(ctx, obj, propSymbol, val, kJSPropertyAttributeNone, exception)
#define OBJECT_GET_CLASS_NAME(obj)						JSC_GetObjectClassName(ctx, obj)

// creates an empty, anonymous JavaScript object with an optional pointer to C++ private data
// the private data is typically used to associate this with an C++ data structure
#define OBJECT_CREATE_EMPTY(privateDataPtr)		JSC_ObjectCreateEmpty(ctx, privateDataPtr)

// retrieve the C++ private data pointer from a JavaScript object
#define OBJECT_PRIVATE_DATA(obj)				JSObjectGetPrivate(obj)

// call a JavaScript function with "this" set to obj and with the arguments specified
// argv is an array of Values. Returns whatever Value is passed back from the function
// if NULL (0, not JavaScript Null Value) is returned, an exception was thrown from the
// function and is stored in the "exception" variable
#define CALL_SCRIPT(func, obj, argc, argv)		JSObjectCallAsFunction(ctx, func, obj, argc, argv, exception)
#define CALL_CONSTRUCTOR_SAFE(func)				((func) ? JSObjectCallAsConstructor(ctx, func, 0, nullptr, exception) : nullptr)
#define CALL_CONSTRUCTOR(func)	                JSObjectCallAsConstructor(ctx, func, 0, 0, exception)
#define CALL_CONSTRUCTOR_EX(func, argc, argv)	JSObjectCallAsConstructor(ctx, func, argc, argv, exception)

#define FUNCTION_GET_NAME(func)					JSC_GetFunctionName(ctx, func)
#define FUNCTION_GET_FILE_AND_LINE(func)		JSC_GetFunctionFileAndLine(ctx, func)

// used for non-callback functions so they can use the macros above which often assume 
// certain variables are available in the function scope
#define SETUP_NON_SCRIPT_EXCEPTION  \
	JSValueRef  _exception = 0;             CR \
	JSValueRef* exception = &_exception

#define SETUP_NON_SCRIPT_CALL \
	JSContextRef ctx = gMainContext;		CR \
	SETUP_NON_SCRIPT_EXCEPTION

// Constructors propagate errors to their JavaScript caller.
#define SETUP_CONSTRUCTOR_CALL \
    JSContextRef ctx = gMainContext; CR \
    JSValueRef localConstructorException = nullptr; CR \
    JSValueRef* exception = constructorException ? constructorException : &localConstructorException

#define THROW_ARGUMENT_TYPE(n, type, value) JSC_ThrowArgTypeException(ctx, exception, n, type, value)

// Execute arbitrary javascript, with the result put into the JavaScript Value valVar.
// Whatever you pass as obj will be the "this" pointer when the code is evaluated,
// or you can pass NULL to use the global object.
// Script is built using an output stream, so you can use << to combine static strings
// and C++ variables, ie:
//
// JSC_EVAL(jsOrientation, 0, "{roll="<<roll<<";pitch="<<pitch<<";yaw="<<yaw<<";}" );
//
#define JS_EVAL(valVar, obj, script)     \
	std::ostringstream valVar##_;                                  CR \
	valVar##_ << script;                                           CR \
    valVar = JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(  \
    	        valVar##_.str().c_str()), obj, 0, 1, exception)

// ========================================================================================
//MARK: EXCEPTION AND ERROR MACROS
// ========================================================================================

#define TRY

#define CATCH_EXCEPTION(var)  if (var == 0 && *exception)    // if (try_catch.HasCaught())

#define EXCEPTION_DATA	 *exception			// try_catch

#define _JSC_THROW_ERR(errtype, msg)     \
    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString("throw " #errtype "('" msg "')"), NULL, 0, 1, exception);  CR \
    return JSValueMakeNull(ctx)

#define _JSC_THROW_ERR_LITERAL(errtype, msg)     \
	std::ostringstream excpt_;                                  CR \
	excpt_ << "throw "<< #errtype << "('" << msg << "')";        CR \
    JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
    	        excpt_.str().c_str()), NULL, 0, 1, exception);  CR \
    return JSValueMakeNull(ctx)

#define THROW_ERR_LITERAL(msg) _JSC_THROW_ERR_LITERAL(Error, msg)

#define THROW_TYPE_ERR_LITERAL(msg) _JSC_THROW_ERR_LITERAL(TypeError, msg)

#define THROW_ERR(msg) _JSC_THROW_ERR_LITERAL(Error, "Error: " << msg)

// Construct the Error directly: preserve its message without a second Error prefix
// or embedding native text in JavaScript source.
#define THROW_ERR_MESSAGE(msg) { \
    JSStringRef errorMessage = JSStringCreateWithUTF8CString(msg); CR \
    JSValueRef errorValue = JSValueMakeString(ctx, errorMessage); CR \
    JSStringRelease(errorMessage); CR \
    *exception = JSObjectMakeError(ctx, 1, &errorValue, nullptr); CR \
    return JSValueMakeNull(ctx); CR \
}

#define THROW_TYPE_ERR(msg) _JSC_THROW_ERR_LITERAL(TypeError, "Type Error: " << msg)

#define THROW_RANGE_ERR(msg) _JSC_THROW_ERR_LITERAL(RangeError, "Range Error: " << msg)

#define THROW_REFERENCE_ERR(msg) _JSC_THROW_ERR_LITERAL(ReferenceError, "Reference Error: " << msg)

#define THROW_SYNTAX_ERR(msg) _JSC_THROW_ERR_LITERAL(SyntaxError, "Syntax Error: " << msg)

// TODO: fix these so they also correctly throw a particular error type
#define THROW_IF_SAVED_ERR    \
	if (s_HaveSavedError) {                     CR \
		s_HaveSavedError = false;               CR \
		std::ostringstream excpt_;                                  CR \
		excpt_ << "throw '" << s_SavedError.str().c_str() << "'";   CR \
		JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
					excpt_.str().c_str()), NULL, 0, 1, exception);  CR \
		return 0;													CR \
    }

#define UNIMPLEMENTED  THROW_ERR_LITERAL("Not yet implemented!" )

#define SAVED_ERROR_STORAGE     extern std::ostringstream s_SavedError

#define SAVE_ERR(msg)   \
	s_SavedError.str(""); s_SavedError.clear();  CR \
	s_SavedError << msg;                         CR \
	s_HaveSavedError = true

#define SAVE_TYPE_ERR(msg)       SAVE_ERR("Type Error: " << msg)
#define SAVE_RANGE_ERR(msg)      SAVE_ERR("Range Error: " << msg)
#define SAVE_REFERENCE_ERR(msg)  SAVE_ERR("Reference Error: " << msg)
#define SAVE_SYNTAX_ERR(msg)     SAVE_ERR("Syntax Error: " << msg)

// ========================================================================================
//MARK: CLASS AND METHOD DECLARATION MACROS
// ========================================================================================

#define _JSC_HAS_NEW(klass) \
  extern klass* New_##klass(size_t, const JSValueRef[], JSValueRef*);

#define _JSC_CLASS_IS_SINGLETON(klass)    \
	extern JSObjectRef klass##_getScriptSingletonInstance();

#define _JSC_CAN_BE_INSTANTIATED_FROM_CPP_OBJECT(klass)    \
    extern JSObjectRef klass##_newFromCpp(JSContextRef, klass*);

#define _JSC_DECLARE_SCRIPT_CLASS(klass)   \
	extern JSObjectRef klass##_new(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);  CR \
	extern JSClassRef  klass##_class();                                                     CR \
	extern JSObjectRef klass##_construct(JSContextRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

#define _JSC_HAS_CPP_OBJECT(klass)   \
	inline klass* klass##_getCppObject(JSObjectRef obj) {       CR \
	    return static_cast<klass*>(JSObjectGetPrivate(obj));       CR \
	}

#define DECL_END

#define END }

// SINGLETON_CLASS - there is only one instance, instantiated first time it is used in
//					Javascript or in C++. Javascript should never call new MySingletonClass(), 
//					instead it should call getMySingletonClass()

#define SINGLETON_CLASS(klass)    \
  _JSC_HAS_NEW(klass)    								CR CR \
  _JSC_DECLARE_SCRIPT_CLASS(klass)                 		CR \
  _JSC_HAS_CPP_OBJECT(klass)                     	CR \
  extern klass* klass##_getSingletonInstance();         CR \
  _JSC_CLASS_IS_SINGLETON(klass)                        CR \


// WRAPPER_CLASS - C++ instances must be instantiated through some kind of 
//                  a factory call, often from another object. This is not a singleton,
//					so calling createMySingletonClass() multiple times will create
//					multiple C++ instances, however the lifecycle of the native
//					C++ object is not tied to the lifecycle of the Javascript object

#define WRAPPER_CLASS(klass)    \
  _JSC_HAS_NEW(klass)    								CR CR \
  _JSC_DECLARE_SCRIPT_CLASS(klass)                      CR \
  _JSC_HAS_CPP_OBJECT(klass)                         CR \
  _JSC_CAN_BE_INSTANTIATED_FROM_CPP_OBJECT(klass)    CR \


// BINDING_CLASS - C++ instances can be instantiated by Javascript code.
// 					var a = new MyClass();
//					Lifecycle of the C++ instance is tied to lifecycle of
//					the Javascript object

#define BINDING_CLASS(klass)   \
  _JSC_HAS_NEW(klass)    								CR CR \
  _JSC_DECLARE_SCRIPT_CLASS(klass)                      CR \
  _JSC_HAS_CPP_OBJECT(klass)                         CR \
  _JSC_CAN_BE_INSTANTIATED_FROM_CPP_OBJECT(klass)    CR \


// FACADE_CLASS	- There is no C++ instance. This is just a facade for a bunch of 
//					static function calls that we want grouped together

#define FACADE_CLASS(klass)   \
  _JSC_DECLARE_SCRIPT_CLASS(klass) CR \
  _JSC_CLASS_IS_SINGLETON(klass)

#define METHOD(klass, name) extern JSValueRef klass##_##name(JSContextRef, JSObjectRef, JSObjectRef, size_t, const JSValueRef[], JSValueRef*);

#define CONSTANT(klass, name) \
	_JSC_SCRIPT_IMPL_ONLY( static JSValueRef klass##_##name(JSContextRef ctx, JSObjectRef, JSStringRef, JSValueRef*) { 	CR \
		return NUM2VAL(pdg::klass::name);														CR \
	} )																							CR

#define PROPERTY(klass, name) \
	METHOD(klass, Get##name) CR \
	METHOD(klass, Set##name)


// ========================================================================================
//MARK: CLASS AND METHOD DEFINITION MACROS
// ========================================================================================

// Sets up the NewFromCpp method, which is used to instantiate a 
// JS class for an already existing C++ object rather than creating 
// the C++ object as we create the JS class.
//
// Usage (C++):
//	   Foo* myFoo = instantiateAndLoadFoo();
//     JSObjectRef obj = Foo_newFromCpp(ctx, myFoo);
//
// Not callable from Javascript
//
#define _JSC_NEW_FROM_CPP_IMPL(klass, extra)    \
JSObjectRef klass##_newFromCpp(JSContextRef ctx, klass* cppObj) {  CR \
    JSObjectRef obj = JSObjectMake(ctx, klass##_class(), cppObj);     CR \
    JSC_SetObjectClassConstructor(ctx, obj, klass##_class());        CR \
    extra;                                                               CR \
    return obj;                                                          CR \
}                                                                        CR CR


// Sets up the {KlassName}_New method, which is used to instantiate
// the C++ object as we create the JS class.
//
// Usage (C++):
//  	JSObjectRef obj = Foo_new(ctx, argc, argv, exception);
//
// Usage (Javascript):
//		var obj = new pdg.Foo(my_args);
//
#define _JSC_NEW_WITH_NEW_CPP_IMPL(klass, fail_verb, extra)    \
JSObjectRef klass##_new(JSContextRef ctx, JSObjectRef thisObject, \
         size_t argumentCount, const JSValueRef arguments[], \
         JSValueRef* exception) {                                     CR \
    klass* cppObj = New_##klass(argumentCount, arguments, exception);         CR \
    if (exception && *exception) return nullptr; CR \
    THROW_IF_SAVED_ERR;                                               CR \
    if (!cppObj) {                                                 CR \
        JSEvaluateScript(ctx, JSStringCreateWithUTF8CString( \
            "throw 'failed to " fail_verb " C++ native " #klass "'"), \
            NULL, 0, 1, exception);                                   CR \
        return 0;													  CR \
    }                                                                 CR \
    JSObjectRef obj = JSObjectMake(ctx, klass##_class(), cppObj);  CR \
    JSC_SetObjectClassConstructor(ctx, obj, klass##_class());       CR \
    extra;                                                            CR \
    return obj;                                                       CR \
}                                                                   CR CR \

// Specialized JSC constructor for singleton managers that prevents external instantiation
#define _JSC_SINGLETON_WRAPPER_NEW_IMPL(klass, singletonName)    \
JSObjectRef klass##_new(JSContextRef ctx, JSObjectRef thisObject, \
         size_t argumentCount, const JSValueRef arguments[], \
         JSValueRef* exception) {                                     CR \
    /* Prevent external constructor usage - singleton managers only */ CR \
    if (!s_##klass##_InNewFromCpp) {                                CR \
        std::ostringstream excpt_;                                  CR \
        excpt_ << "throw TypeError('" #klass " cannot be instantiated with \\'new\\'. Use the singleton instance: require(\\'pdg\\')." singletonName "')"; CR \
        JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
                excpt_.str().c_str()), NULL, 0, 1, exception);      CR \
        return 0;                                                   CR \
    }                                                               CR CR \
    klass* cppObj = New_##klass(argumentCount, arguments, exception);         CR \
    if (exception && *exception) return nullptr; CR \
    THROW_IF_SAVED_ERR;                                             CR \
    if (!cppObj) {                                                  CR \
        JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
            "throw 'failed to get singleton C++ native " #klass "'"), \
            NULL, 0, 1, exception);                                 CR \
        return 0;                                                   CR \
    }                                                               CR \
    JSObjectRef obj = JSObjectMake(ctx, klass##_class(), cppObj);   CR \
    JSC_SetObjectClassConstructor(ctx, obj, klass##_class());       CR \
    return obj;                                                     CR \
}                                                                   CR CR \

// Specialized JSC constructor for factory-only classes that prevents external instantiation
#define _JSC_FACTORY_ONLY_WRAPPER_NEW_IMPL(klass, factoryFunction)    \
JSObjectRef klass##_new(JSContextRef ctx, JSObjectRef thisObject, \
         size_t argumentCount, const JSValueRef arguments[], \
         JSValueRef* exception) {                                     CR \
    /* Prevent external constructor usage - factory-only classes */ CR \
    if (!s_##klass##_InNewFromCpp) {                                CR \
        std::ostringstream excpt_;                                  CR \
        excpt_ << "throw TypeError('" #klass " cannot be instantiated with \\'new\\'. Use the factory function: pdg." factoryFunction "()')"; CR \
        JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
                excpt_.str().c_str()), NULL, 0, 1, exception);      CR \
        return 0;                                                   CR \
    }                                                               CR CR \
    klass* cppObj = New_##klass(argumentCount, arguments, exception);         CR \
    if (exception && *exception) return nullptr; CR \
    THROW_IF_SAVED_ERR;                                             CR \
    if (!cppObj) {                                                  CR \
        JSEvaluateScript(ctx, JSStringCreateWithUTF8CString(        \
            "throw 'failed to create C++ native " #klass "'"), \
            NULL, 0, 1, exception);                                 CR \
        return 0;                                                   CR \
    }                                                               CR \
    JSObjectRef obj = JSObjectMake(ctx, klass##_class(), cppObj);   CR \
    JSC_SetObjectClassConstructor(ctx, obj, klass##_class());       CR \
    return obj;                                                     CR \
}                                                                   CR CR \

// Sets up the methods and fields needed for a singleton 
// Use getScriptSingletonInstance() to get the Javascript JSObjectRef
//   or to create it if it doesn't exist
#define _JSC_GET_SCRIPT_SINGLETON_IMPL(klass)   \
JSObjectRef klass##_getScriptSingletonInstance() {                  CR \
	static JSObjectRef instance = 0;								CR \
  	if (!instance) {                                                CR \
  		instance = klass##_new(gMainContext, 0, 0, NULL, NULL);  	CR \
		JSValueProtect(gMainContext, instance);                     CR \
	}                                                               CR \
  	return instance;                                                CR \
}                                                                   CR CR \

// Specialized version for singleton managers that need the InNewFromCpp flag
#define _JSC_GET_SCRIPT_SINGLETON_MANAGER_IMPL(klass)   \
JSObjectRef klass##_getScriptSingletonInstance() {                  CR \
	static JSObjectRef instance = 0;								CR \
  	if (!instance) {                                                CR \
        /* Set flag to allow internal constructor call for singleton creation */ CR \
        s_##klass##_InNewFromCpp = true;                            CR \
  		instance = klass##_new(gMainContext, 0, 0, NULL, NULL);  	CR \
        s_##klass##_InNewFromCpp = false;                           CR \
		JSValueProtect(gMainContext, instance);                     CR \
	}                                                               CR \
  	return instance;                                                CR \
}                                                                   CR CR


// Sets up the methods and fields needed for a wrapped native singleton 
// Use getSingletonInstance() to get the native object 
//   Note: getSingletonInstance() calls getScriptSingletonInstance()
#define _JSC_GET_CPP_SINGLETON_IMPL(klass)   \
klass* klass##_getSingletonInstance() {                         CR \
	JSObjectRef obj = klass##_getScriptSingletonInstance();     CR \
    return static_cast<klass*>(JSObjectGetPrivate(obj));        CR \
}                                                               CR CR


// this sets up the constructor function template that is used to
// create javascript objects with the class signature desired
// the function must be completed with an EXPORT_CLASS_SYMBOLS macro
// that exports the public constants, properties and methods so they 
// can be added to the class signature
#define _JSC_CLASS_INIT_IMPL(klass)    \
JSClassRef klass##_class() {


// Sets up the {KlassName}_new methods, which are used to create a javascript object and
// the underlying C++ object that is being wrapped. Both are created
// the same time
//
// Usage (C++): 
//  	JSObjectRef obj = Foo_new(ctx, 0, NULL, exception);
//
// Usage (Javascript):
//		var obj = new pdg.Foo();
//

// FACADE_CLASS	- There is no C++ instance. This is just a facade for a bunch of 
//					static function calls that we want grouped together

#define FACADE_INITIALIZER_IMPL(klass)  \
  JSObjectRef klass##_new(JSContextRef ctx, JSObjectRef thisObject, \
  		 size_t argumentCount, const JSValueRef arguments[], \
  		 JSValueRef* exception) {                                     CR \
    JSObjectRef obj = JSObjectMake(ctx, klass##_class(), 0);          CR \
    return obj;                                                       CR \
  }                                                                   CR CR \
  _JSC_GET_SCRIPT_SINGLETON_IMPL(klass)    					  		  CR \
  _JSC_CLASS_INIT_IMPL(klass)


// SINGLETON_CLASS - there is only one instance, instantiated first time it is used in
//					Javascript or in C++. Javascript should never call new MySingletonClass(), 
//					instead it should call getMySingletonClass()

#define SINGLETON_INITIALIZER_IMPL(klass)   \
  _JSC_NEW_WITH_NEW_CPP_IMPL(klass, "get singleton", )             CR \
  _JSC_GET_SCRIPT_SINGLETON_IMPL(klass)    					  		  CR \
  _JSC_GET_CPP_SINGLETON_IMPL(klass)                          	  CR \
  _JSC_CLASS_INIT_IMPL(klass)


// Specialized singleton initializers for manager classes that prevent external instantiation
#define SINGLETON_MANAGER_INITIALIZER_IMPL(klass, singletonName)   \
static bool s_##klass##_InNewFromCpp = false;		    CR CR \
  _JSC_SINGLETON_WRAPPER_NEW_IMPL(klass, singletonName)      		CR \
  _JSC_GET_SCRIPT_SINGLETON_MANAGER_IMPL(klass)   	CR \
  _JSC_GET_CPP_SINGLETON_IMPL(klass)                          	  CR \
  _JSC_CLASS_INIT_IMPL(klass)


// WRAPPER_CLASS - C++ instances must be instantiated through some kind of 
//                  a factory call, often from another object. This is not a singleton,
//					so calling createMySingletonClass() multiple times will create
//					multiple C++ instances, however the lifecycle of the native
//					C++ object is not tied to the lifecycle of the Javascript object

#define WRAPPER_INITIALIZER_IMPL(klass)    \
  _JSC_NEW_FROM_CPP_IMPL(klass,                    				  \
    cppObj->m##klass##ScriptObj = obj;                             CR \
    JSValueProtect(ctx, obj);                                         CR \
	cppObj->addRef()  )                                            CR \
  _JSC_NEW_WITH_NEW_CPP_IMPL(klass, "create",                      \
    cppObj->m##klass##ScriptObj = obj;                             CR \
    JSValueProtect(ctx, obj);                                         CR \
    cppObj->addRef()  )                                            CR \
  _JSC_CLASS_INIT_IMPL(klass)


#define WRAPPER_INITIALIZER_IMPL_CUSTOM(klass, extraNewFromCpp) \
  _JSC_NEW_FROM_CPP_IMPL(klass,                  			      \
    extraNewFromCpp )                                              CR \
  _JSC_NEW_WITH_NEW_CPP_IMPL(klass, "create",                      \
    extraNewFromCpp  )                                             CR \
  _JSC_CLASS_INIT_IMPL(klass)

#define BINDING_INITIALIZER_IMPL_REFCOUNTED(klass, extraNewFromCpp) \
    WRAPPER_INITIALIZER_IMPL_CUSTOM(klass, extraNewFromCpp)

#define WRAPPER_INITIALIZER_IMPL_REFCOUNTED_CUSTOM(klass, extraNewFromCpp) \
    WRAPPER_INITIALIZER_IMPL_CUSTOM(klass, extraNewFromCpp)

#define WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY(klass, factoryFunction, extraNewFromCpp) \
  static bool s_##klass##_InNewFromCpp = false;                 CR CR \
  _JSC_NEW_FROM_CPP_IMPL(klass,                  			      \
    extraNewFromCpp )                                              CR \
  _JSC_FACTORY_ONLY_WRAPPER_NEW_IMPL(klass, factoryFunction)      CR \
  _JSC_CLASS_INIT_IMPL(klass)


// BINDING_CLASS - C++ instances can be instantiated by Javascript code.
// 					var a = new MyClass();
//					Lifecycle of the C++ instance is tied to lifecycle of
//					the Javascript object

#define BINDING_INITIALIZER_IMPL(klass)   \
  _JSC_NEW_FROM_CPP_IMPL(klass,                    				  \
    cppObj->m##klass##ScriptObj = obj;                             CR \
    JSValueProtect(ctx, obj) )                                        CR \
  _JSC_NEW_WITH_NEW_CPP_IMPL(klass, "create",                      \
    cppObj->m##klass##ScriptObj = obj;                             CR \
    JSValueProtect(ctx, obj) )                                        CR \
  _JSC_CLASS_INIT_IMPL(klass)


#define CPP_CONSTRUCTOR_IMPL(klass)	\
klass* New_##klass(SCRIPT_ARGS) {

#define CPP_MANAGED_CONSTRUCTOR_IMPL(klass) CPP_CONSTRUCTOR_IMPL(klass)

#define CPP_UNMANAGED_CONSTRUCTOR_IMPL(klass, ops) CPP_CONSTRUCTOR_IMPL(klass)

#define CPP_SINGLETON_CONSTRUCTOR_IMPL(klass) \
klass* New_##klass(SCRIPT_ARGS) { return klass::getSingletonInstance(); }

#define CPP_SINGLETON_CONSTRUCTOR_IMPL_CUSTOM(klass) CPP_CONSTRUCTOR_IMPL(klass)


// Export all the symbols for a particular class under the name given.
// 1st section is for the list of HAS_CONST() definitions
// 2nd section is for the list of HAS_GETTER/SETTER/PROPERTY() definitions
// Last section is for the list of HAS_METHOD() definitions
#define EXPORT_CLASS_SYMBOLS(name, klass, consts_def, props_def, meth_def) \
	static JSStaticValue klass##_staticValues[] = {					CR \
		consts_def													\
		{ 0, 0, 0, 0 }												CR \
	};																CR \
	static JSStaticFunction klass##_staticFunctions[] = {			CR \
		props_def													\
		meth_def													\
		{ 0, 0, 0 }                                                 CR \
	};                                                              CR \
    static JSClassRef jsClass = 0;                                  CR \
    if (!jsClass) {                                                 CR \
        JSClassDefinition definition = kJSClassDefinitionEmpty;     CR \
        definition.className = name;							    CR \
        definition.staticFunctions = klass##_staticFunctions;       CR \
        definition.staticValues = klass##_staticValues;       		CR \
        definition.callAsConstructor = klass##_new;					CR \
        jsClass = JSClassCreate(&definition);                       CR \
    }                                                               CR \
    return jsClass

#define EXPORT_FINALIZED_CLASS_SYMBOLS(name, klass, finalizer, consts_def, props_def, meth_def) \
	static JSStaticValue klass##_staticValues[] = {					CR \
		consts_def													\
		{ 0, 0, 0, 0 }												CR \
	};																CR \
	static JSStaticFunction klass##_staticFunctions[] = {			CR \
		props_def													\
		meth_def													\
		{ 0, 0, 0 }                                                 CR \
	};                                                              CR \
    static JSClassRef jsClass = 0;                                  CR \
    if (!jsClass) {                                                 CR \
        JSClassDefinition definition = kJSClassDefinitionEmpty;     CR \
        definition.finalize = finalizer; CR \
        definition.className = name;							    CR \
        definition.staticFunctions = klass##_staticFunctions;       CR \
        definition.staticValues = klass##_staticValues;       		CR \
        definition.callAsConstructor = klass##_new;					CR \
        jsClass = JSClassCreate(&definition);                       CR \
    }                                                               CR \
    return jsClass

#define EXPORT_DERIVED_CLASS_SYMBOLS(name, klass, base, finalizer, consts_def, props_def, meth_def) \
	static JSStaticValue klass##_staticValues[] = {					CR \
		consts_def													\
		{ 0, 0, 0, 0 }												CR \
	};																CR \
	static JSStaticFunction klass##_staticFunctions[] = {			CR \
		props_def													\
		meth_def													\
		{ 0, 0, 0 }                                                 CR \
	};                                                              CR \
    static JSClassRef jsClass = 0;                                  CR \
    if (!jsClass) {                                                 CR \
        JSClassDefinition definition = kJSClassDefinitionEmpty;     CR \
        definition.parentClass = base##_class(); CR \
        definition.finalize = finalizer; CR \
        definition.className = name;							    CR \
        definition.staticFunctions = klass##_staticFunctions;       CR \
        definition.staticValues = klass##_staticValues;       		CR \
        definition.callAsConstructor = klass##_new;					CR \
        jsClass = JSClassCreate(&definition);                       CR \
    }                                                               CR \
    return jsClass
//         definition.initialize = klass##_initialize;                 CR \
//         definition.finalize = klass##_finalize;                     CR \



#define HAS_METHOD(klass, name, method)  \
    { name, klass##_##method, kJSPropertyAttributeDontDelete }, CR


#define HAS_CONSTANT(klass, name)     \
    { #name, klass##_##name, NULL, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete }, CR


#define HAS_GETTER(klass, name)  \
	HAS_METHOD(klass, "get"#name, Get##name)


#define HAS_SETTER(klass, name)  \
	HAS_METHOD(klass, "set"#name, Set##name)


#define HAS_PROPERTY(klass, name)  \
	HAS_GETTER(klass, name) \
	HAS_SETTER(klass, name)


#define FUNCTION_DECL(func)    \
  extern JSValueRef func(JSContextRef, JSObjectRef, JSObjectRef, size_t, \
  					const JSValueRef[], JSValueRef*);


#define FUNCTION_IMPL(func)    \
  JSValueRef func(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject,    \
  		size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {


#define SCRIPT_METHOD_IMPL(klass, method)   \
    JSValueRef klass##_##method(JSContextRef ctx, JSObjectRef function, \
  		JSObjectRef thisObject,  size_t argumentCount, const JSValueRef arguments[], \
  		JSValueRef* exception) {


#define METHOD_IMPL(klass, method)    \
  SCRIPT_METHOD_IMPL(klass, method)                                         CR \
    klass* self = static_cast<klass*>(JSObjectGetPrivate(thisObject));


#define STATIC_METHOD_IMPL(klass, method)  SCRIPT_METHOD_IMPL(klass, method)

  
#define INIT_CLASS(klass) INIT_CLASS_NAMED(klass, #klass)

#define INIT_CLASS_NAMED(klass, name) \
    JSObjectRef klass##NativeConstructor = JSObjectMakeConstructor(ctx, klass##_class(), klass##_new); CR \
    JSObjectRef klass##Obj = JSC_CreateClassConstructor(ctx, name, klass##NativeConstructor, 0); CR \
    JSC_RegisterClassConstructor(klass##_class(), klass##Obj); CR \
    JSObjectSetProperty(ctx, globalObject, _JSC_STR(name), klass##Obj, kJSPropertyAttributeNone, NULL)


#define INIT_FUNCTION(sym, func)   \
	JSStringRef func##Name = _JSC_STR(sym);		                                      CR \
	JSObjectRef func##Ref = JSObjectMakeFunctionWithCallback(ctx, func##Name, func);  CR \
	JSObjectSetProperty(ctx, globalObject, func##Name, func##Ref, kJSPropertyAttributeNone, exception);


#define INIT_CONSTANT(name, value) \
	JSObjectSetProperty(ctx, globalObject, _JSC_STR(name), INT2VAL(value), kJSPropertyAttributeNone, exception);

#define INIT_BOOL_CONSTANT(name, value) \
	JSObjectSetProperty(ctx, globalObject, _JSC_STR(name), BOOL2VAL(value), kJSPropertyAttributeNone, exception);


#define CLEANUP_IMPL(klass)   \
  void Cleanup##klass##ScriptObject(JSObjectRef obj) { }  CR \
// 	DEBUG_DUMP_SCRIPT_OBJECT(obj, klass);                CR \
//     if (obj) {                                               CR \
// 		DEBUG_PRINT("Cleanup" #klass "ScriptObject for JSObj [%p][%s]", obj, typeid_name(obj)); CR \
//         JSValueUnprotect(gMainContext, obj);                 CR \
// 	} CR \
// }


// ========================================================================================
//MARK: ARGUMENT HANDLING MACROS
// ========================================================================================

#define REQUIRE_ARG_COUNT(n)   \
	if (ARGC != n)                             				CR \
		return JSC_ThrowArgCountException(ctx, exception, ARGC, n)


#define REQUIRE_ARG_MIN_COUNT(n)  \
	if (ARGC < n)                 							CR \
		return JSC_ThrowArgCountException(ctx, exception, ARGC, n, true)


#define REQUIRE_STRING_ARG(n, paramName)   \
	if (!VALUE_IS_STRING(ARGV[n-1]))         				CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a string ("#paramName")");      				CR \
	VALUE_TO_CSTRING(paramName, ARGV[n-1])


#define REQUIRE_NUMBER_ARG(n, paramName)   \
	if (ARGC < n || !VALUE_IS_NUMBER(ARGV[n-1]))                       	CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName = VAL2NUM(ARGV[n-1])


#define REQUIRE_INT32_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	int32 paramName = VAL2INT(ARGV[n-1])
	

#define REQUIRE_UINT32_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	uint32 paramName = VAL2UINT(ARGV[n-1])


#define REQUIRE_BOOL_ARG(n, paramName)   \
	if (!VALUE_IS_BOOL(ARGV[n-1]))                          CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a boolean ("#paramName")");                    CR \
	bool paramName = VAL2BOOL(ARGV[n-1])


#define REQUIRE_OBJECT_ARG(n, paramName)   \
	if (!VALUE_IS_OBJECT(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"an object ("#paramName")");                    CR \
	JSObjectRef paramName = VAL2OBJ(ARGV[n-1])


#define EXTRACT_CPP_OBJECT_OR_SUBCLASS_ARG(n, paramName, klass)  \
	klass* paramName = 0;									CR \
	if (VALUE_IS_OBJECT_OF_CLASS(ARGV[n-1], klass)) {    	CR \
		JSObjectRef paramName##_ = VAL2OBJ(ARGV[n-1]);  	CR \
		paramName = klass##_getCppObject(paramName##_);	CR \
	}


#define REQUIRE_CPP_OBJECT_OR_SUBCLASS_OR_NULL_ARG(n, paramName, klass) \
	EXTRACT_CPP_OBJECT_OR_SUBCLASS_ARG(n, paramName, klass)   		CR \
	if (!paramName && !VALUE_IS_NULL(ARGV[n-1]))             			CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 			\
			"null or an object derived from "#klass" ("#paramName")")


#define REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(n, paramName, klass) \
	EXTRACT_CPP_OBJECT_OR_SUBCLASS_ARG(n, paramName, klass)   	CR \
	if (!paramName)                                               	CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"an object derived from "#klass" ("#paramName")")


#define EXTRACT_CPP_OBJECT_ARG(n, paramName, klass)   \
	klass* paramName = 0;											CR \
	if (VALUE_IS_OBJECT(ARGV[n-1])) {                         		CR \
		JSObjectRef paramName##_ = VAL2OBJ(ARGV[n-1]);  			CR \
	    paramName = klass##_getCppObject(paramName##_);          CR \
	}


#define REQUIRE_CPP_OBJECT_ARG(n, paramName, klass)   \
	EXTRACT_CPP_OBJECT_ARG(n, paramName, klass)      			CR \
	if (!paramName)                                               	CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"an object of type "#klass" ("#paramName")")


#define REQUIRE_CPP_OBJECT_OR_NULL_ARG(n, paramName, klass)   \
	EXTRACT_CPP_OBJECT_ARG(n, paramName, klass)  				CR \
	if (!paramName && !VALUE_IS_NULL(ARGV[n-1]))             		CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"null or an object of type "#klass" ("#paramName")")


#define REQUIRE_FUNCTION_ARG(n, paramName)   \
	JSObjectRef paramName = VAL2OBJ(ARGV[n-1]);  					CR \
	if (!paramName || !JSObjectIsFunction(ctx, paramName) )			CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"a function ("#paramName")")


#define REQUIRE_ARRAY_ARG(n, paramName)   \
	if (!VALUE_IS_OBJECT(ARGV[n-1]))                         		CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"an array ("#paramName")");      						CR \
	JSObjectRef paramName = VAL2OBJ(ARGV[n-1])


#define REQUIRE_OFFSET_ARG(n, paramName) \
    pdg::Offset paramName; CR \
    auto paramName##_isOffset = VALUE_IS_OFFSET(ARGV[n-1], paramName); CR \
    if (!paramName##_isOffset.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isOffset) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Offset", ARGV[n-1]); CR \
    }



#define REQUIRE_POINT_ARG(n, paramName) \
    pdg::Point paramName; CR \
    auto paramName##_isPoint = VALUE_IS_POINT(ARGV[n-1], paramName); CR \
    if (!paramName##_isPoint.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isPoint) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Point", ARGV[n-1]); CR \
    }


#define REQUIRE_VECTOR_ARG(n, paramName) \
    pdg::Vector paramName; CR \
    auto paramName##_isVector = VALUE_IS_VECTOR(ARGV[n-1], paramName); CR \
    if (!paramName##_isVector.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isVector) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Vector", ARGV[n-1]); CR \
    }



#define REQUIRE_RECT_ARG(n, paramName) \
    pdg::Rect paramName; CR \
    auto paramName##_isRect = VALUE_IS_RECT(ARGV[n-1], paramName); CR \
    if (!paramName##_isRect.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isRect) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Rect", ARGV[n-1]); CR \
    }



#define REQUIRE_ROTATED_RECT_ARG(n, paramName) \
    pdg::RotatedRect paramName; CR \
    auto paramName##_isRotatedRect = VALUE_IS_ROTRECT(ARGV[n-1], paramName); CR \
    if (!paramName##_isRotatedRect.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isRotatedRect) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "RotatedRect", ARGV[n-1]); CR \
    }



#define REQUIRE_QUAD_ARG(n, paramName) \
    pdg::Quad paramName; CR \
    auto paramName##_isQuad = VALUE_IS_QUAD(ARGV[n-1], paramName); CR \
    if (!paramName##_isQuad.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isQuad) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Quad", ARGV[n-1]); CR \
    }



#define REQUIRE_COLOR_ARG(n, paramName) \
    pdg::Color paramName; CR \
    auto paramName##_isColor = VALUE_IS_COLOR(ARGV[n-1], paramName); CR \
    if (!paramName##_isColor.has_value()) { RETURN_NULL; } CR \
    if (!*paramName##_isColor) { CR \
        return JSC_ThrowArgTypeException(ctx, exception, n, "Color", ARGV[n-1]); CR \
    }



#define REQUIRE_1_ARG  REQUIRE_INT8_ARG
#define REQUIRE_2_ARG  REQUIRE_INT16_ARG
#define REQUIRE_4_ARG  REQUIRE_INT32_ARG_RANGE
#define REQUIRE_8_ARG  REQUIRE_NUMBER_ARG
#define REQUIRE_f_ARG  REQUIRE_NUMBER_ARG
#define REQUIRE_d_ARG  REQUIRE_NUMBER_ARG
#define REQUIRE_uint_ARG   REQUIRE_UINT32_ARG
#define REQUIRE_1u_ARG     REQUIRE_UINT8_ARG
#define REQUIRE_2u_ARG     REQUIRE_UINT16_ARG
#define REQUIRE_3u_ARG     REQUIRE_UINT24_ARG
#define REQUIRE_4u_ARG     REQUIRE_UINT32_ARG_RANGE
#define REQUIRE_8u_ARG     REQUIRE_NUMBER_ARG
#define REQUIRE_ref_ARG    REQUIRE_OBJECT_ARG
#define REQUIRE_str_ARG    REQUIRE_STRING_ARG
#define REQUIRE_bool_ARG   REQUIRE_BOOL_ARG
#define REQUIRE_point_ARG  REQUIRE_POINT_ARG
#define REQUIRE_spline_ARG REQUIRE_SPLINE_ARG
#define REQUIRE_offset_ARG REQUIRE_OFFSET_ARG
#define REQUIRE_vector_ARG REQUIRE_VECTOR_ARG
#define REQUIRE_rect_ARG   REQUIRE_RECT_ARG
#define REQUIRE_rotr_ARG   REQUIRE_ROTATED_RECT_ARG
#define REQUIRE_quad_ARG   REQUIRE_QUAD_ARG
#define REQUIRE_color_ARG  REQUIRE_COLOR_ARG
#define REQUIRE_obj_ARG    REQUIRE_OBJECT_ARG

// Range-checking macros for fixed-size serialization methods
#define REQUIRE_INT8_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	long paramName##_temp = VAL2INT(ARGV[n-1]); CR \
	if (paramName##_temp < -128 || paramName##_temp > 127) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [-128, 127] ("#paramName")"); CR \
	} CR \
	int8 paramName = (int8)paramName##_temp

#define REQUIRE_INT16_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	long paramName##_temp = VAL2INT(ARGV[n-1]); CR \
	if (paramName##_temp < -32768 || paramName##_temp > 32767) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [-32768, 32767] ("#paramName")"); CR \
	} CR \
	int16 paramName = (int16)paramName##_temp

#define REQUIRE_INT32_ARG_RANGE(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < -2147483648.0 || paramName##_temp > 2147483647.0 || \
		paramName##_temp != (long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [-2147483648, 2147483647] ("#paramName")"); CR \
	} CR \
	int32 paramName = (int32)paramName##_temp

#define REQUIRE_INT64_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < -9223372036854775808.0 || paramName##_temp > 9223372036854775807.0 || \
		paramName##_temp != (long long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [-9223372036854775808, 9223372036854775807] ("#paramName")"); CR \
	} CR \
	int64 paramName = (int64)paramName##_temp

#define REQUIRE_UINT8_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < 0.0 || paramName##_temp > 255.0 || \
		paramName##_temp != (unsigned long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [0, 255] ("#paramName")"); CR \
	} CR \
	uint8 paramName = (uint8)paramName##_temp

#define REQUIRE_UINT16_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < 0.0 || paramName##_temp > 65535.0 || \
		paramName##_temp != (unsigned long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [0, 65535] ("#paramName")"); CR \
	} CR \
	uint16 paramName = (uint16)paramName##_temp

#define REQUIRE_UINT24_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < 0.0 || paramName##_temp > 16777215.0 || \
		paramName##_temp != (unsigned long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [0, 16777215] ("#paramName")"); CR \
	} CR \
	uint32 paramName = (uint32)paramName##_temp

#define REQUIRE_UINT32_ARG_RANGE(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < 0.0 || paramName##_temp > 4294967295.0 || \
		paramName##_temp != (unsigned long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [0, 4294967295] ("#paramName")"); CR \
	} CR \
	uint32 paramName = (uint32)paramName##_temp

#define REQUIRE_UINT64_ARG(n, paramName) \
	if (!VALUE_IS_NUMBER(ARGV[n-1]))                        CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number ("#paramName")");                     CR \
	double paramName##_temp = VAL2NUM(ARGV[n-1]); CR \
	if (paramName##_temp < 0.0 || paramName##_temp > 18446744073709551615.0 || \
		paramName##_temp != (unsigned long long)paramName##_temp) { CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, \
			"a number in range [0, 18446744073709551615] ("#paramName")"); CR \
	} CR \
	uint64 paramName = (uint64)paramName##_temp


#define OPTIONAL_STRING_ARG(n, paramName, defaultVal)   \
	if (ARGC >= n && !VALUE_IS_STRING(ARGV[n-1]))              						CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 						\
			"a string ("#paramName")");            									CR \
	JSStringRef paramName##_Str = (ARGC >= n)                                   \
		? JSValueToStringCopy(ctx, ARGV[n-1], exception) : 0;                    CR \
	MemBlock paramName##_Mem((ARGC >= n)                                        \
		? JSStringGetMaximumUTF8CStringSize(paramName##_Str) : 0);               CR \
	if (ARGC >= n) {                                                       			CR \
		JSStringGetUTF8CString(paramName##_Str, paramName##_Mem.ptr,                \
		paramName##_Mem.bytes);                                                     \
		JSStringRelease(paramName##_Str);                                          CR \
	}                                                                               CR \
	const char* paramName = (ARGC < n) ? defaultVal                        			\
		: (const char*)paramName##_Mem.ptr


#define OPTIONAL_INT32_ARG(n, paramName, defaultVal)   \
	if (ARGC >= n && !VALUE_IS_NUMBER(ARGV[n-1]))   				CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"a number ("#paramName")");  							CR \
	long paramName = (ARGC<n) ? defaultVal : VAL2INT(ARGV[n-1])


#define OPTIONAL_UINT32_ARG(n, paramName, defaultVal)   \
	if (ARGC >= n && !VALUE_IS_NUMBER(ARGV[n-1]))    				CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"a number ("#paramName")");								CR \
	unsigned long paramName = (ARGC<n) ? defaultVal : VAL2UINT(ARGV[n-1])


#define OPTIONAL_NUMBER_ARG(n, paramName, defaultVal)   \
	if (ARGC >= n && !VALUE_IS_NUMBER(ARGV[n-1]))     				CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"a number ("#paramName")");  							CR \
	double paramName = (ARGC<n) ? defaultVal : VAL2NUM(ARGV[n-1])


#define OPTIONAL_BOOL_ARG(n, paramName, defaultVal)   \
	if (ARGC >= n && !VALUE_IS_BOOL(ARGV[n-1]))       				CR \
		return JSC_ThrowArgTypeException(ctx, exception, n, 		\
			"a boolean ("#paramName")");  							CR \
	bool paramName = (ARGC<n) ? defaultVal : VAL2BOOL(ARGV[n-1])


#define OPTIONAL_CPP_OBJECT_ARG(n, paramName, klass, defaultVal) \
	klass* paramName = defaultVal;                                  CR \
	if (ARGC >= n) {                                       			CR \
		if (!VALUE_IS_OBJECT_OF_CLASS(ARGV[n-1], klass)) {     		CR \
			return JSC_ThrowArgTypeException(ctx, exception, n, 	\
				"an object of type "#klass" ("#paramName")");  		CR \
		} else {                                                   	CR \
			JSObjectRef paramName##_ = VAL2OBJ(ARGV[n-1]);  		CR \
			paramName = klass##_getCppObject(paramName##_);      CR \
		}                                                           CR \
	}


#define OPTIONAL_POINT_ARG(n, paramName, defaultVal) \
    pdg::Point paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isPoint = VALUE_IS_POINT(ARGV[n-1], paramName); CR \
        if (!paramName##_isPoint.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isPoint) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "Point", ARGV[n-1]); CR \
        } CR \
    }


#define OPTIONAL_OFFSET_ARG(n, paramName, defaultVal) \
    pdg::Offset paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isOffset = VALUE_IS_OFFSET(ARGV[n-1], paramName); CR \
        if (!paramName##_isOffset.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isOffset) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "Offset", ARGV[n-1]); CR \
        } CR \
    }



#define OPTIONAL_RECT_ARG(n, paramName, defaultVal) \
    pdg::Rect paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isRect = VALUE_IS_RECT(ARGV[n-1], paramName); CR \
        if (!paramName##_isRect.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isRect) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "Rect", ARGV[n-1]); CR \
        } CR \
    }



#define OPTIONAL_ROTATED_RECT_ARG(n, paramName, defaultVal) \
    pdg::RotatedRect paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isRotatedRect = VALUE_IS_ROTRECT(ARGV[n-1], paramName); CR \
        if (!paramName##_isRotatedRect.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isRotatedRect) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "RotatedRect", ARGV[n-1]); CR \
        } CR \
    }



#define OPTIONAL_QUAD_ARG(n, paramName, defaultVal) \
    pdg::Quad paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isQuad = VALUE_IS_QUAD(ARGV[n-1], paramName); CR \
        if (!paramName##_isQuad.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isQuad) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "Quad", ARGV[n-1]); CR \
        } CR \
    }



#define OPTIONAL_COLOR_ARG(n, paramName, defaultVal) \
    pdg::Color paramName; CR \
    if (ARGC < n) { CR \
        paramName = defaultVal; CR \
    } else { CR \
        auto paramName##_isColor = VALUE_IS_COLOR(ARGV[n-1], paramName); CR \
        if (!paramName##_isColor.has_value()) { RETURN_NULL; } CR \
        if (!*paramName##_isColor) { CR \
            return JSC_ThrowArgTypeException(ctx, exception, n, "Color", ARGV[n-1]); CR \
        } CR \
    }



#define RETURN(what) return what

#define RETURN_TRUE            return BOOL2VAL(true)
#define RETURN_FALSE           return BOOL2VAL(false)
#define RETURN_NULL            return NULL_VAL
#define RETURN_THIS            return THIS
#define RETURN_BOOL(what)      return BOOL2VAL(what)
#define RETURN_UNSIGNED(what)  return UINT2VAL(what)
#define RETURN_INTEGER(what)   return INT2VAL(what)
#define RETURN_UINT32(what)    RETURN_UNSIGNED(what)
#define RETURN_INT32(what)     RETURN_INTEGER(what)
#define RETURN_NUMBER(what)    return NUM2VAL(what)
#define RETURN_STRING(what)    return STR2VAL(what)
#define RETURN_OBJECT(what)	   return what
#define RETURN_FUNCTION(what)  return what

#define RETURN_OFFSET(what)	   return OFFSET2VAL( what )
#define RETURN_VECTOR(what)	   return VECTOR2VAL( what )
#define RETURN_POINT(what)	   return POINT2VAL(what)
#define RETURN_RECT(what)	   return RECT2VAL( what )
#define RETURN_ROTATED_RECT(what)   return ROTRECT2VAL( what )
#define RETURN_QUAD(what)	   return QUAD2VAL( what )
#define RETURN_COLOR(what)	   return COLOR2VAL( what )

#define RETURN_CPP_OBJECT(what, klass)   \
	if (!what) RETURN_NULL;												CR \
    if (!what->m##klass##ScriptObj) {                                   CR \
    	return klass##_newFromCpp(ctx, what);                   		CR \
	} else {                                                            CR \
		return what->m##klass##ScriptObj;                               CR \
	}

#define RETURN_NEW_CPP_OBJECT(what, klass)   \
	if (!what) RETURN_NULL;												CR \
	return klass##_newFromCpp(ctx, what);

#define RETURN_UNDEFINED       return JSValueMakeUndefined(ctx)
#define NO_RETURN              RETURN_UNDEFINED

// ========================================================================================
//MARK: PROPERTY GETTER/SETTER MACROS
// ========================================================================================

#define C_BOOL		bool
#define C_UNSIGNED	unsigned int
#define C_INTEGER	int
#define C_UINT32	uint32
#define C_INT32		int32
#define C_NUMBER	double
#define C_STRING	const char*
#define C_OFFSET	pdg::Offset
#define C_VECTOR	pdg::Vector
#define C_POINT		pdg::Point
#define C_RECT		pdg::Rect
#define C_ROTATED_RECT	pdg::RotatedRect
#define C_QUAD		pdg::Quad
#define C_COLOR		pdg::Color
#define C_SPLINE	pdg::Spline*

#define SIG_BOOL		boolean
#define SIG_UNSIGNED	[number uint]
#define SIG_INTEGER		[number int]
#define SIG_UINT32		[number uint]
#define SIG_INT32		[number int]
#define SIG_NUMBER		number
#define SIG_STRING		string
#define SIG_OFFSET		[object Offset]
#define SIG_VECTOR		[object Vector]
#define SIG_POINT		[object Point]
#define SIG_RECT		[object Rect]
#define SIG_ROTATED_RECT	[object RotatedRect]
#define SIG_QUAD		[object Quad]
#define SIG_COLOR		object
#define SIG_SPLINE		[object Spline]

#define SIG_1u_STR     "[number uint]"
#define SIG_2u_STR     "[number uint]"
#define SIG_3u_STR     "[number uint]"
#define SIG_4u_STR     "[number uint]"
#define SIG_8u_STR     "[number uint]"
#define SIG_1_STR      "[number int]"
#define SIG_2_STR      "[number int]"
#define SIG_4_STR      "[number int]"
#define SIG_8_STR      "[number int]"
#define SIG_f_STR      "number"
#define SIG_d_STR      "number"
#define SIG_uint_STR   "[number uint]"
#define SIG_bool_STR   "boolean"
#define SIG_point_STR  "[object Point]"
#define SIG_offset_STR "[object Offset]"
#define SIG_vector_STR "[object Vector]"
#define SIG_color_STR  "[object Color]"
#define SIG_rect_STR   "[object Rect]"
#define SIG_rotr_STR   "[object RotatedRect]"
#define SIG_quad_STR   "[object Quad]"
#define SIG_str_STR    "string"
#define SIG_ref_STR    "object"
#define SIG_mem_STR    "{[string Binary]|[object MemBlock]}"
#define SIG_obj_STR    "constructor"

#define SIG_RET_BOOL		boolean
#define SIG_RET_UNSIGNED	number
#define SIG_RET_INTEGER		number
#define SIG_RET_UINT32		number
#define SIG_RET_INT32		number
#define SIG_RET_NUMBER		number
#define SIG_RET_STRING		string
#define SIG_RET_OFFSET		[object Offset]
#define SIG_RET_VECTOR		[object Vector]
#define SIG_RET_POINT		[object Point]
#define SIG_RET_RECT		[object Rect]
#define SIG_RET_ROTATED_RECT	[object RotatedRect]
#define SIG_RET_QUAD		[object Quad]
#define SIG_RET_COLOR		object

#define CUSTOM_GETTER_IMPL(klass, prop, type, xargc, m, xargs, getcode, paramdoc) \
METHOD_IMPL(klass, Get##prop)  		CR \
	CUSTOM_GETTER_SIG(SIG_RET_##type, paramdoc) 		CR \
    REQUIRE_ARG_##m##COUNT(xargc);  CR \
    xargs						    \
	getcode; 				        CR \
	RETURN_##type(the##prop);  		CR \
	END

#define CUSTOM_SETTER_IMPL(klass, prop, type, xargc, m, xargs, setcode) \
METHOD_IMPL(klass, Set##prop)  		CR \
	SETTER_SIG([object klass], SIG_##type, in##prop) CR \
    REQUIRE_ARG_##m##COUNT(xargc);  CR \
    REQUIRE_##type##_ARG(1, the##prop);  CR \
    xargs						 	\
    setcode;       					CR \
	RETURN_THIS;                    CR \
	END

#define GETTER_IMPL(klass, prop, type) \
CUSTOM_GETTER_IMPL(klass, prop, type, 0, , , C_##type the##prop = self->get##prop(), () )

#define SETTER_IMPL(klass, prop, type) \
CUSTOM_SETTER_IMPL(klass, prop, type, 1, , , self->set##prop(the##prop) )

#define PROPERTY_IMPL(klass, prop, type) \
	GETTER_IMPL(klass, prop, type) CR \
	SETTER_IMPL(klass, prop, type)

#define CP_GETTER_IMPL(klass, prop, type) \
CUSTOM_GETTER_IMPL(klass, prop, type, 0, , , C_##type the##prop = klass##Get##prop(self), () )

#define CP_SETTER_IMPL(klass, prop, type) \
CUSTOM_SETTER_IMPL(klass, prop, type, 1, , , klass##Set##prop(self, the##prop) )

#define CP_PROPERTY_IMPL(klass, prop, type) \
	CP_GETTER_IMPL(klass, prop, type) CR \
	CP_SETTER_IMPL(klass, prop, type)


// ========================================================================================
//MARK: METHOD SIGNATURE MACROS
// ========================================================================================

#define METHOD_SIGNATURE_NO_DOCS(rettype, paramcount, params) \
// 	if (ARGC == 1 && VALUE_IS_NULL(ARGV[0])) {   CR \
// 		RETURN_STRING(#rettype " function" #params);                CR \
// 	}

#define METHOD_SIGNATURE(brief, rettype, paramcount, params) \
// 	if (ARGC == 1 && VALUE_IS_NULL(ARGV[0])) {   CR \
// 		RETURN_STRING(#rettype " function" #params " - " brief);    CR \
// 	}

#define CUSTOM_GETTER_SIG(rettype, params) METHOD_SIGNATURE_NO_DOCS(rettype, 0, params)
#define GETTER_SIG(rettype) METHOD_SIGNATURE_NO_DOCS(rettype, 0, ())
#define SETTER_SIG(klass, type, name) METHOD_SIGNATURE_NO_DOCS(klass, 1, (type name))


#define CUSTOM_SERIALIZER_SIZE_OF_METHOD_IMPL(type, ops) \
METHOD_IMPL(Serializer, Sizeof_##type)   CR \
	if (ARGC == 1 && VALUE_IS_NULL(ARGV[0])) {                  CR \
		RETURN_STRING("[number uint] function(" SIG_##type##_STR " val) - " ); CR \
	} CR \
    REQUIRE_ARG_COUNT(1); CR \
    REQUIRE_##type##_ARG(1, val); CR \
	ops; CR \
	RETURN_UNSIGNED(n); CR \
	END

#define SERIALIZER_SIZE_OF_METHOD_IMPL(type) \
    CUSTOM_SERIALIZER_SIZE_OF_METHOD_IMPL(type, size_t n = self->sizeof_##type(val) )


// ========================================================================================
//MARK: DEBUG MACROS
// ========================================================================================

#define VALUE_TYPE_STR(val) \
        ((val == 0) ? "empty" : val->IsArray() ? "array" : JSC_ValueIsFunction(ctx, val, 0) ? "function" : \
		JSValueIsString(ctx, val) ? "string" : \
		JSValueIsNull(ctx, val) ? "null" : JSValueIsUndefined(ctx, val) ? "undefined" : \
		JSValueIsNumber(ctx, val) ? "number" : \
		JSValueIsBoolean(ctx, val) ? "boolean" : \
		JSValueIsObject(ctx, val) ? "object" : "unknown")

// for internal debugging use, shouldn't ever be in non-debug builds

#define DUMP_SCRIPT_OBJECT(val, klass)  \
	JSC_DebugPrintValue(ctx, val, "Dumping " #klass " object:")

#define DEBUG_DUMP_SCRIPT_OBJECT(val, klass) SCRIPT_DEBUG_ONLY( DUMP_SCRIPT_OBJECT(val, klass) )

#define DEBUG_CHECK_OBJECT_PROPERTY(val, prop) SCRIPT_DEBUG_ONLY( \
	if (VALUE_IS_OBJECT(val)) {\
		JSObjectRef obj_ = JSValueToObject(ctx, val, 0);\
		if (JSObjectHasProperty(ctx, obj_, _JSC_STR(#prop))) {\
			JSValueRef val_ = JSObjectGetProperty(ctx, obj_, _JSC_STR(#prop)); \
			VALUE_TO_CSTRING(valStr, val_); \
			std::cout << #val " " <<" has property "#prop" : "<<valStr<<"\n";\
		} else {\
			std::cerr << #val " " <<" has no property "#prop"\n";\
		}     \
	} else {  \
		std::cerr << #val " " <<" is not an object\n"; \
	} )


#endif // PDG_SCRIPT_MACROS_H_INCLUDED

#define WRAPPER_INITIALIZER_IMPL_REFCOUNTED_FACTORY(klass, factoryFunction, extra) WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY(klass, factoryFunction, extra)
#define INIT_UINT_CONSTANT(name, value) INIT_CONSTANT(name, value)
