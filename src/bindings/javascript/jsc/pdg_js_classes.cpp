// -----------------------------------------------
// pdg_js_classes.cpp
//
// wrapper definitions for all the classes 
// the are exposed to Javascript, and some
// utility functions
//
// This file is parsed by "make generate-interfaces"
// to generate the interface file:
//       src/sys/js/pdg_interfaces.cpp
//
// This should only be done when the wrappers need 
// to change.
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

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#include "pdg_script_interface.h"

%#define PDG_LIBRARY

%#include "internals.h"
%#include "pdg-lib.h"

//%#include "node.h"  // for FatalException()

%#include <sstream>
%#include <cmath>
%#include <cstdlib>


//%#define PDG_DEBUG_JAVASCRIPT

%#ifndef PDG_DEBUG_JAVASCRIPT
  // if the javascript bindings are not being debugged, we ignore whatever
  // is inside these blocks
  %#define SCRIPT_DEBUG_ONLY(_expression)
%#else
  %#define SCRIPT_DEBUG_ONLY DEBUG_ONLY
%#endif

namespace pdg {

// ========================================================================================
//MARK: Shared Global Declarations
// ========================================================================================

std::ostringstream s_SavedError;

// ========================================================================================
//MARK: Local Declarations
// ========================================================================================

static std::ostringstream s_ExceptStr;
JSContextRef gMainContext = 0;
static JSValueRef s_PendingScriptException = 0;
DECLARE_SYMBOL(roll);
DECLARE_SYMBOL(pitch);
DECLARE_SYMBOL(yaw);

void SavePendingScriptException(JSValueRef exception) {
	if (s_PendingScriptException) {
		JSValueUnprotect(gMainContext, s_PendingScriptException);
	}
	s_PendingScriptException = exception;
	if (s_PendingScriptException) {
		JSValueProtect(gMainContext, s_PendingScriptException);
	}
}

bool RestorePendingScriptException(JSValueRef* exception) {
	if (!s_PendingScriptException) {
		return false;
	}
	JSValueRef pendingException = s_PendingScriptException;
	s_PendingScriptException = 0;
	if (exception) {
		*exception = pendingException;
	}
	JSValueUnprotect(gMainContext, pendingException);
	return true;
}

// ========================================================================================
//MARK: Config Manager
// ========================================================================================

FUNCTION_IMPL(GetConfigManager)
	METHOD_SIGNATURE("", [object ConfigManager*], 0, ());
    RETURN( ConfigManager_getScriptSingletonInstance() );
    END

// ========================================================================================
//MARK: Log Manager
// ========================================================================================

FUNCTION_IMPL(GetLogManager)
	METHOD_SIGNATURE("", [object LogManager*], 0, ());
    RETURN( LogManager_getScriptSingletonInstance() );
END

// ========================================================================================
//MARK: IEventHandler
// ========================================================================================

CPP_CONSTRUCTOR_IMPL(IEventHandler)
	SETUP_NON_SCRIPT_CALL;
	if (HAVE_ONLY_ONE_NULL_ARG) { // for introspection
		ScriptEventHandler* handler = new ScriptEventHandler();
		handler->addRef();
		return handler;
	} else if (ARGC != 1 || !VALUE_IS_FUNCTION(ARGV[0])) {
		SAVE_SYNTAX_ERR("EventHandler must be created with a function argument (handlerFunc)");
		return 0;
	}
	FUNCTION_REF funcObj = VAL2FUNC(ARGV[0]);
//    JSC_DebugPrintObject(ctx, funcObj, "New_IEventHandler with Func:");
	ScriptEventHandler* handler = new ScriptEventHandler(funcObj);
	handler->addRef();
	return handler;
	END

// ========================================================================================
//MARK: Event Manager
// ========================================================================================

STATIC_METHOD_IMPL(EventManager, IsKeyDown)
	METHOD_SIGNATURE("", boolean, 1, ({string unicodeChar|[number uint] utf16CharCode}));
    REQUIRE_ARG_COUNT(1);
	if (VALUE_IS_STRING(ARGV[0])) {
		JSStringRef keyCode_String = JSValueToStringCopy(ctx, ARGV[0], exception);
		uint16 utf16Char = JSStringGetCharactersPtr(keyCode_String)[0];
		RETURN_BOOL( OS::isKeyDown(utf16Char) );
	} else {
    	REQUIRE_UINT32_ARG(1, utf16CharCode);
		RETURN_BOOL( OS::isKeyDown(utf16CharCode) );
	}
	END
STATIC_METHOD_IMPL(EventManager, GetDeviceOrientation)
	METHOD_SIGNATURE("NOT IMPLEMENTED", object, 0, (boolean absolute = false));
    OPTIONAL_BOOL_ARG(1, absolute, false);
    float roll, pitch, yaw;
	OS::getDeviceOrientation(roll, pitch, yaw, absolute); // not yet implemented in C++
	OBJECT jsOrientation = OBJECT_CREATE_EMPTY(0);
	OBJECT_SET_PROPERTY_VALUE(jsOrientation, SYMBOL(roll), NUM2VAL(roll));
	OBJECT_SET_PROPERTY_VALUE(jsOrientation, SYMBOL(pitch), NUM2VAL(pitch));
	OBJECT_SET_PROPERTY_VALUE(jsOrientation, SYMBOL(yaw), NUM2VAL(yaw));
	RETURN(jsOrientation);
	END
FUNCTION_IMPL(GetEventManager)
	METHOD_SIGNATURE("", [object EventManager*], 0, ());
    JSObjectRef jsInstance = EventManager_getScriptSingletonInstance();
    EventManager* evtMgr = EventManager::getSingletonInstance();
    evtMgr->mEventEmitterScriptObj = jsInstance;
    RETURN(jsInstance);
	END

// ========================================================================================
//MARK: Resource Manager
// ========================================================================================

DECLARE_SYMBOL(name);

METHOD_IMPL(ResourceManager, GetImage)
	METHOD_SIGNATURE("", [object Image*], 1, (string imageName));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, imageName);
	Image* img = self->getImage(imageName);
	if (img == NULL) {
		RETURN_NULL;
	}
    JSObjectRef obj = Image_newFromCpp(ctx, img);
	// add a name to the object so it's easier to keep track of
	OBJECT_SET_PROPERTY_VALUE(obj, SYMBOL(name), ARGV[0]);
	RETURN(obj);
	END
METHOD_IMPL(ResourceManager, GetImageStrip)
	METHOD_SIGNATURE("", [object ImageStrip*], 1, (string imageName));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, imageName);
	ImageStrip* img = self->getImageStrip(imageName);
	if (img == NULL) {
		RETURN_NULL;
	}
    JSObjectRef obj = ImageStrip_newFromCpp(ctx, img);
	// add a name to the object so it's easier to keep track of
	OBJECT_SET_PROPERTY_VALUE(obj, SYMBOL(name), ARGV[0]);
	RETURN(obj);
	END
%#ifndef PDG_NO_SOUND
METHOD_IMPL(ResourceManager, GetSound)
	METHOD_SIGNATURE("", [object Sound*], 1, (string soundName));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, soundName);
	Sound* snd = self->getSound(soundName);
	if (snd == NULL) {
		RETURN_NULL;
	}
    JSObjectRef obj = snd->mSoundScriptObj ? snd->mSoundScriptObj : Sound_newFromCpp(ctx, snd);
	// add a name to the sound so it's easier to keep track of
	OBJECT_SET_PROPERTY_VALUE(obj, SYMBOL(name), ARGV[0]);
	RETURN(obj);
	END
%#endif // !PDG_NO_SOUND


FUNCTION_IMPL(GetResourceManager)
	METHOD_SIGNATURE("", [object ResourceManager*], 0, ());
    RETURN( ResourceManager_getScriptSingletonInstance() );
    END

// ========================================================================================
//MARK: ISerializable
// ========================================================================================

CPP_CONSTRUCTOR_IMPL(ISerializable)
	SETUP_NON_SCRIPT_CALL;
	if (HAVE_ONLY_ONE_NULL_ARG) { // for introspection
		ScriptSerializable* serializable = new ScriptSerializable();
		serializable->addRef();
		return serializable;
	} else if (ARGC != 4 
	  || !VALUE_IS_FUNCTION(ARGV[0]) || !VALUE_IS_FUNCTION(ARGV[1]) 
	  || !VALUE_IS_FUNCTION(ARGV[2]) || !VALUE_IS_FUNCTION(ARGV[3])) {
		SAVE_SYNTAX_ERR("Serializable must be created with 4 function arguments "
			"(getSerializedSizeFunc, serializeFunc, deserializeFunc, getMyClassTagFunc)");
		return 0;
	}
	SAVED_FUNCTION getSerializedSizeFunc = VAL2FUNC(ARGV[0]);
	SAVED_FUNCTION serializeFunc = VAL2FUNC(ARGV[1]);
	SAVED_FUNCTION deserializeFunc = VAL2FUNC(ARGV[2]);
	SAVED_FUNCTION getMyClassTagFunc = VAL2FUNC(ARGV[3]);
	ScriptSerializable* serializable = 
		new ScriptSerializable(getSerializedSizeFunc, serializeFunc, 
									deserializeFunc, getMyClassTagFunc);
	serializable->addRef();
	return serializable;
	END

// ========================================================================================
//MARK: Serializer
// ========================================================================================

// JavaScriptCore stores the most-derived native pointer. Convert known native
// classes before using the ISerializable secondary base (not a raw void* cast).
AnimatedBase* JSC_GetAnimationTarget(JSContextRef ctx, JSValueRef value) {
    if(!JSValueIsObject(ctx,value)) return nullptr;
    auto object=JSValueToObject(ctx,value,nullptr);
    if(JSValueIsObjectOfClass(ctx,value,Troupe_class())) return Troupe_getCppObject(object);
%#ifdef PDG_SPRITER_SUPPORT
    if(JSValueIsObjectOfClass(ctx,value,Bone_class())) return Bone_getCppObject(object);
%#endif
    if(JSValueIsObjectOfClass(ctx,value,Part_class())) return Part_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,Sprite_class())) return Sprite_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,AnimatedAttributesBase_class())) return AnimatedAttributesBase_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,Camera_class())) return Camera_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,Particle_class())) return Particle_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,ParticleEmitter_class())) return ParticleEmitter_getCppObject(object);
    if(JSValueIsObjectOfClass(ctx,value,AnimatedBase_class())) return AnimatedBase_getCppObject(object);
    return nullptr;
}

ISerializable* JSC_GetSerializable(JSContextRef ctx, JSValueRef value) {
    if (!JSValueIsObject(ctx, value)) return nullptr;
    JSObjectRef object = JSValueToObject(ctx, value, nullptr);
    // Image data and snapshots are available without a rendering backend.
    if (JSValueIsObjectOfClass(ctx, value, ImageStrip_class())) return ImageStrip_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, Image_class())) return Image_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, Sprite_class())) return Sprite_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, TileLayer_class())) return static_cast<Serializable<SpriteLayer>*>(TileLayer_getCppObject(object));
    if (JSValueIsObjectOfClass(ctx, value, SpriteLayer_class())) return static_cast<Serializable<SpriteLayer>*>(SpriteLayer_getCppObject(object));
    if (JSValueIsObjectOfClass(ctx, value, Camera_class())) return Camera_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, Troupe_class())) return Troupe_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, AnimatedBase_class())) return AnimatedBase_getCppObject(object);
    if (JSValueIsObjectOfClass(ctx, value, ISerializable_class())) return ISerializable_getCppObject(object);
    return nullptr;
}

METHOD_IMPL(Serializer, Serialize_obj)
	self->mSerializerScriptObj = THIS;  // correct for callbacks
	METHOD_SIGNATURE("", undefined, 1, ([object ISerializable const*] obj));
    REQUIRE_ARG_COUNT(1);
    ISerializable* obj = JSC_GetSerializable(ctx, ARGV[0]);
    if (!obj && !VALUE_IS_NULL(ARGV[0])) { THROW_TYPE_ERR("Expected a serializable object or null"); }
	DEBUG_DUMP_SCRIPT_OBJECT(ARGV[0], ISerializable);
    try { self->serialize_obj(obj); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
	if (RestorePendingScriptException(exception)) {
		return JSValueMakeUndefined(ctx);
	}
	NO_RETURN;
	END
METHOD_IMPL(Serializer, SerializedSize)
	METHOD_SIGNATURE("", number, 1, ({string|boolean|[number uint]|[object Color]|[object Offset]|[object Point]|[object Vector]|[object Rect]|[object RotatedRect]|[object Quad]|[object MemBlock]|[object ISerializable]} arg));
    REQUIRE_ARG_COUNT(1);
 	uint32 dataSize = 0;
    Offset offset;
    Rect rect;
    RotatedRect rotatedRect;
    Quad quad;
    Color color;
    if (VALUE_IS_STRING(ARGV[0])) {
    	VALUE_TO_CSTRING(str, ARGV[0]);
		dataSize = self->sizeof_str(str);
    } else if (VALUE_IS_BOOL(ARGV[0])) {
    	bool val = VAL2BOOL(ARGV[0]);
    	dataSize = self->sizeof_bool(val);
    } else if (VALUE_IS_NUMBER(ARGV[0])) {
    	uint32 val = VAL2UINT(ARGV[0]);
    	dataSize = self->sizeof_uint(val);
    } else if (auto isColor = VALUE_IS_COLOR(ARGV[0], color); !isColor.has_value()) {
        RETURN_NULL;
    } else if (*isColor) {
        dataSize = self->sizeof_color(color);
    } else if (auto isOffset = VALUE_IS_OFFSET(ARGV[0], offset); !isOffset.has_value()) {
        RETURN_NULL;
    } else if (*isOffset) {
        dataSize = self->sizeof_offset(offset);
    } else if (auto isRect = VALUE_IS_RECT(ARGV[0], rect); !isRect.has_value()) {
        RETURN_NULL;
    } else if (*isRect) {
        dataSize = self->sizeof_rect(rect);
    } else if (auto isRotatedRect = VALUE_IS_ROTRECT(ARGV[0], rotatedRect); !isRotatedRect.has_value()) {
        RETURN_NULL;
    } else if (*isRotatedRect) {
        dataSize = self->sizeof_rotr(rotatedRect);
    } else if (auto isQuad = VALUE_IS_QUAD(ARGV[0], quad); !isQuad.has_value()) {
        RETURN_NULL;
    } else if (*isQuad) {
        dataSize = self->sizeof_quad(quad);
    } else if (VALUE_IS_OBJECT_OF_CLASS(ARGV[0], MemBlock)) {
		JSObjectRef obj = JSValueToObject(ctx, ARGV[0], exception);
		MemBlock* memBlock = MemBlock_getCppObject(obj);
    	dataSize = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
    } else {
		// perhaps it's an ISerializable?
		EXTRACT_CPP_OBJECT_OR_SUBCLASS_ARG(1, serializable, ISerializable);
		if (serializable) {
			DEBUG_DUMP_SCRIPT_OBJECT(self->mSerializerScriptObj, Serializer);
			DEBUG_DUMP_SCRIPT_OBJECT(serializable->mISerializableScriptObj, ISerializable);
			dataSize = self->sizeof_obj(serializable);
		} else {
			THROW_TYPE_ERR_LITERAL("argument 1 must be either an unsigned integer, "
				"a string, a MemBlock object, an ISerializable object");
		}
    }
	RETURN_UINT32(dataSize);
	END

// ========================================================================================
//MARK: Deserializer
// ========================================================================================

FUNCTION_IMPL(RegisterSerializableObject)
	METHOD_SIGNATURE("", undefined, 2, (object obj, [number uint] uniqueId));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_OBJECT_ARG(1, obj);
	REQUIRE_UINT32_ARG(2, uniqueId);
	
	// We need to keep a reference to the object, but we need to do it
	// in a way that ensures that the JS engine knows it is still around
	// In V8, that means a persistent reference of some kind, for JSC it's simple
	OBJECT_REF objRef;
	OBJECT_SAVE(objRef, obj);
	// FIXME: not at all sure this is what we want to do. Might need a template version of this function too
	void* objPtr = static_cast<void*>(&objRef);
	
	Deserializer::registerObject(objPtr, uniqueId);
    NO_RETURN;
    END



%#ifndef PDG_NO_GUI

// ========================================================================================
//MARK: Graphics Manager
// ========================================================================================

METHOD_IMPL(GraphicsManager, GetCurrentScreenMode);
	METHOD_SIGNATURE("returns object with width, height, depth and maxWindowRect for specified screen", 
		object, 0, ([number int] screenNum = PRIMARY_SCREEN));
	OPTIONAL_INT32_ARG(1, screenNum, screenNum_PrimaryScreen);
	pdg::Rect maxWindowRect;
	pdg::GraphicsManager::ScreenMode mode;
	mode = self->getCurrentScreenMode(screenNum, &maxWindowRect);
	// make native object with these properties
	VALUE jsScreenMode;
	JS_EVAL(jsScreenMode, 0, "({width:"<<mode.width<<",height:"<<mode.height
		<<",depth:"<<mode.bpp<<",maxWindowRect:{right:"
		<<maxWindowRect.right<<",top:"<<maxWindowRect.top<<",left:"
		<<maxWindowRect.left<<",bottom:"<<maxWindowRect.bottom<<"}})" );
	RETURN(jsScreenMode);
	END

METHOD_IMPL(GraphicsManager, GetNthSupportedScreenMode);
	METHOD_SIGNATURE("returns object with width, height, depth and maxWindowRect for specified screen", 
		object, 1, ([number int] n, [number int] screenNum = PRIMARY_SCREEN));
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_INT32_ARG(1, n);
	OPTIONAL_INT32_ARG(2, screenNum, screenNum_PrimaryScreen);
	pdg::GraphicsManager::ScreenMode mode;
	mode = self->getNthSupportedScreenMode(n, screenNum);
	// make native object with these properties
	VALUE jsScreenMode;
	JS_EVAL(jsScreenMode, 0, "({width:"<<mode.width<<",height:"<<mode.height
		<<",depth:"<<mode.bpp<<"})" );
	RETURN(jsScreenMode);
	END
	
	
FUNCTION_IMPL(GetGraphicsManager)
	METHOD_SIGNATURE("", [object GraphicsManager*], 0, ());
    RETURN( GraphicsManager_getScriptSingletonInstance() );
    END


%#endif //!PDG_NO_GUI


%#ifndef PDG_NO_SOUND

// ========================================================================================
//MARK: Sound Manager
// ========================================================================================

FUNCTION_IMPL(GetSoundManager)
	METHOD_SIGNATURE("", [object SoundManager*], 0, ());
    RETURN( SoundManager_getScriptSingletonInstance() );
    END

%#endif //! PDG_NO_SOUND



// ========================================================================================
//MARK: FileManager
// ========================================================================================

FUNCTION_IMPL(GetFileManager)
	METHOD_SIGNATURE("", [object FileManager*], 0, ());
    RETURN( FileManager_getScriptSingletonInstance() );
    END


// ========================================================================================
//MARK: TimerManager
// ========================================================================================

FUNCTION_IMPL(GetTimerManager)
	METHOD_SIGNATURE("", [object TimerManager*], 0, ());
    JSObjectRef jsInstance = TimerManager_getScriptSingletonInstance();
    TimerManager* timMgr = TimerManager::getSingletonInstance();
    timMgr->mEventEmitterScriptObj = jsInstance;
    RETURN(jsInstance);
    END


// ========================================================================================
//MARK: IAnimationHelper
// ========================================================================================


CPP_CONSTRUCTOR_IMPL(IAnimationHelper)
	SETUP_NON_SCRIPT_CALL;
	if (HAVE_ONLY_ONE_NULL_ARG) { // for introspection
		ScriptAnimationHelper* helper = new ScriptAnimationHelper();
		return helper;
	} else if (ARGC != 1 || !VALUE_IS_FUNCTION(ARGV[0])) {
		SAVE_SYNTAX_ERR("AnimationHelper must be created with a function argument (handlerFunc)");
		return 0;
	}	
	SAVED_FUNCTION funcObj = VAL2FUNC(ARGV[0]);
	ScriptAnimationHelper* helper = new ScriptAnimationHelper(funcObj);
	return helper;
	END

// ========================================================================================
//MARK: Easing Functions
// ========================================================================================

static JSObjectRef s_CustomJavascriptEasing[MAX_CUSTOM_EASINGS];


// ========================================================================================
// ========================================================================================




%#ifndef PDG_NO_GUI
// ========================================================================================
//MARK: ISpriteDrawHelper
// ========================================================================================

CPP_CONSTRUCTOR_IMPL(ISpriteDrawHelper)
	SETUP_NON_SCRIPT_CALL;
	if (HAVE_ONLY_ONE_NULL_ARG) { // for introspection
		ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper();
		return helper;
	} else if (ARGC != 1 || !VALUE_IS_FUNCTION(ARGV[0])) {
		SAVE_SYNTAX_ERR("SpriteDrawHelper must be created with a function argument (drawFunc)");
		return 0;
	}	
	SAVED_FUNCTION funcObj = VAL2FUNC(ARGV[0]);
	ScriptSpriteDrawHelper* helper = new ScriptSpriteDrawHelper(funcObj);
	return helper;
	END

%#endif // !PDG_NO_GUI


// ========================================================================================
//MARK: Script Serializable
// ========================================================================================

DECLARE_SYMBOL(getSerializedSize);
DECLARE_SYMBOL(serialize);
DECLARE_SYMBOL(deserialize);
DECLARE_SYMBOL(getMyClassTag);

ScriptSerializable::ScriptSerializable(
		SAVED_FUNCTION javascriptGetSerializedSizeFunc,
		SAVED_FUNCTION javascriptSerializeFunc,
		SAVED_FUNCTION javascriptDeserializeFunc,
		SAVED_FUNCTION javascriptGetMyClassTagFunc) 
{
	mScriptGetSerializedSizeFunc = javascriptGetSerializedSizeFunc;
	JSValueProtect(gMainContext, mScriptGetSerializedSizeFunc);
	mScriptSerializeFunc = javascriptSerializeFunc;
	JSValueProtect(gMainContext, mScriptSerializeFunc);
	mScriptDeserializeFunc = javascriptDeserializeFunc;
	JSValueProtect(gMainContext, mScriptDeserializeFunc);
	mScriptGetMyClassTagFunc = javascriptGetMyClassTagFunc;
	JSValueProtect(gMainContext, mScriptGetMyClassTagFunc);
}

uint32 	
ScriptSerializable::getSerializedSize(ISerializer* serializer) const {
	SETUP_NON_SCRIPT_CALL;
    VALUE argv[1];
    Serializer* ser = dynamic_cast<Serializer*>(serializer);
    if (!ser) {
	  DEBUG_ONLY(
		std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
		exit(1);
	  )
    }

    argv[0] = OBJ2VAL(ser->mSerializerScriptObj);
    FUNCTION_REF func;
    if (mScriptGetSerializedSizeFunc) {
		func = mScriptGetSerializedSizeFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mISerializableScriptObj, SYMBOL(getSerializedSize)) );
	}
    VALUE resVal = CALL_SCRIPT(func, this->mISerializableScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		SavePendingScriptException(EXCEPTION_DATA);
		return 0;
    }
	if (!VALUE_IS_NUMBER(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from getSerializedSize Function must be an unsigned integer ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
		return 0;
	}
	return VAL2UINT(resVal);
}

void 	
ScriptSerializable::serialize(ISerializer* serializer) const {
	SETUP_NON_SCRIPT_CALL;
    VALUE argv[1];
    Serializer* ser = dynamic_cast<Serializer*>(serializer);
    if (!ser) {
	  DEBUG_ONLY(
		std::cerr << "Internal Error: getSerializedSize Function called with invalid Serializer\n";
		exit(1);
	  )
    }

    argv[0] = OBJ2VAL(ser->mSerializerScriptObj);
    FUNCTION_REF func;
    if (mScriptSerializeFunc) {
		func = mScriptSerializeFunc;
    } else {
   		func = VAL2FUNC( OBJECT_GET_PROPERTY(mISerializableScriptObj, SYMBOL(serialize)) );
	}
    VALUE resVal = CALL_SCRIPT(func, this->mISerializableScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		SavePendingScriptException(EXCEPTION_DATA);
    }
}

void 	
ScriptSerializable::deserialize(IDeserializer* deserializer) {
	SETUP_NON_SCRIPT_CALL;

    VALUE argv[1];
    Deserializer* deser = dynamic_cast<Deserializer*>(deserializer);
    if (!deser) {
	  DEBUG_ONLY(
		std::cerr << "Internal Error: deserialize Function called with invalid Deserializer\n";
		exit(1);
	  )
    }
    argv[0] = OBJ2VAL(deser->mDeserializerScriptObj);
    FUNCTION_REF func;
    if (mScriptDeserializeFunc) {
		func = mScriptDeserializeFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mISerializableScriptObj, SYMBOL(deserialize)) );
	}
    VALUE resVal = CALL_SCRIPT(func, this->mISerializableScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		SavePendingScriptException(EXCEPTION_DATA);
    }
}

uint32 	
ScriptSerializable::getMyClassTag() const {
	SETUP_NON_SCRIPT_CALL;
    FUNCTION_REF func;
    if (mScriptGetMyClassTagFunc) {
		func = mScriptGetMyClassTagFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mISerializableScriptObj, SYMBOL(getMyClassTag)) );
	} 
    VALUE resVal = CALL_SCRIPT(func, this->mISerializableScriptObj, 0, 0);

    CATCH_EXCEPTION(resVal) {
		SavePendingScriptException(EXCEPTION_DATA);
		return 0;
    }
	if (!VALUE_IS_NUMBER(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from getMyClassTag Function must be an unsigned integer ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return 0;
	}
	return VAL2UINT(resVal);
}


// ========================================================================================
//MARK: Script Event Handler
// ========================================================================================

DECLARE_SYMBOL(collider);
DECLARE_SYMBOL(other);
DECLARE_SYMBOL(shape);
DECLARE_SYMBOL(otherShape);
DECLARE_SYMBOL(phase);
DECLARE_SYMBOL(penetration);
DECLARE_SYMBOL(point);
DECLARE_SYMBOL(sensor);
DECLARE_SYMBOL(emitter);
DECLARE_SYMBOL(eventType);
DECLARE_SYMBOL(startupReason);
DECLARE_SYMBOL(exitReason);
DECLARE_SYMBOL(exitCode);
DECLARE_SYMBOL(id);
DECLARE_SYMBOL(millisec);
DECLARE_SYMBOL(msElapsed);
DECLARE_SYMBOL(keyCode);
DECLARE_SYMBOL(shift);
DECLARE_SYMBOL(ctrl);
DECLARE_SYMBOL(alt);
DECLARE_SYMBOL(meta);
DECLARE_SYMBOL(unicode);
DECLARE_SYMBOL(isRepeating);
DECLARE_SYMBOL(touchType);
DECLARE_SYMBOL(touchedSprite);
DECLARE_SYMBOL(inLayer);
DECLARE_SYMBOL(mousePos);
DECLARE_SYMBOL(leftButton);
DECLARE_SYMBOL(rightButton);
DECLARE_SYMBOL(buttonNumber);
DECLARE_SYMBOL(lastClickPos);
DECLARE_SYMBOL(lastClickElapsed);
DECLARE_SYMBOL(horizDelta);
DECLARE_SYMBOL(vertDelta);
DECLARE_SYMBOL(sound);
DECLARE_SYMBOL(eventCode);
DECLARE_SYMBOL(port);
DECLARE_SYMBOL(screenPos);
DECLARE_SYMBOL(frameNum);
DECLARE_SYMBOL(targetSprite);
DECLARE_SYMBOL(normal);
DECLARE_SYMBOL(impulse);
DECLARE_SYMBOL(force);
DECLARE_SYMBOL(arbiter);
DECLARE_SYMBOL(kineticEnergy);
DECLARE_SYMBOL(collisionName);
DECLARE_SYMBOL(withCollisionName);
DECLARE_SYMBOL(isFirstContact);
DECLARE_SYMBOL(breakForce);
DECLARE_SYMBOL(breakAngularSpeed);
DECLARE_SYMBOL(angularSpeed);
DECLARE_SYMBOL(referenceBody);
DECLARE_SYMBOL(part);
DECLARE_SYMBOL(body);
DECLARE_SYMBOL(reason);
DECLARE_SYMBOL(joint);
DECLARE_SYMBOL(action);
DECLARE_SYMBOL(bone);
DECLARE_SYMBOL(wholeRig);
DECLARE_SYMBOL(includeDescendants);
DECLARE_SYMBOL(mode);
DECLARE_SYMBOL(bodyCount);
DECLARE_SYMBOL(disabled);

DECLARE_SYMBOL(actingLayer);
DECLARE_SYMBOL(actingSprite);
DECLARE_SYMBOL(handleEvent);
DECLARE_SYMBOL(oldScreenPos);
DECLARE_SYMBOL(oldWidth);
DECLARE_SYMBOL(oldHeight);

ScriptEventHandler::ScriptEventHandler(JSObjectRef func) {
	mScriptHandlerFunc = func;
	JSValueProtect(gMainContext, mScriptHandlerFunc);
//    JSC_DebugPrintObject(gMainContext, mScriptHandlerFunc, "ScriptEventHandler() func:");
}

DECLARE_SYMBOL(triggerName);
DECLARE_SYMBOL(clipName);
DECLARE_SYMBOL(entityName);
DECLARE_SYMBOL(camera);
DECLARE_SYMBOL(zoom);
DECLARE_SYMBOL(timeSeconds);
DECLARE_SYMBOL(offsetSeconds);

bool ScriptEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept {
  	SETUP_NON_SCRIPT_CALL;
    if (!emitter->mEventEmitterScriptObj) {
        if (auto* particle = dynamic_cast<Particle*>(emitter)) Particle_newFromCpp(ctx, particle);
        else if (auto* scene = dynamic_cast<Scene*>(emitter)) Scene_newFromCpp(ctx, scene);
        else if (auto* camera = dynamic_cast<Camera*>(emitter)) Camera_newFromCpp(ctx, camera);
    }
  	OBJECT jsEvent = OBJECT_CREATE_EMPTY(0);
  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(emitter), OBJ2VAL(emitter->mEventEmitterScriptObj));
  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(eventType), INT2VAL(inEventType));
	switch (inEventType) {
		case pdg::eventType_Startup:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(startupReason), INT2VAL(static_cast<StartupInfo*>(inEventData)->startupReason));
// TODO: startup params converted to an array
//		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(startupParams), INT2VAL(static_cast<StartupInfo*>(inEventData)->startupParam));
			break;
		case pdg::eventType_Shutdown:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(exitReason), INT2VAL(static_cast<ShutdownInfo*>(inEventData)->exitReason));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(exitCode), INT2VAL(static_cast<ShutdownInfo*>(inEventData)->exitCode));
			break;
		case pdg::eventType_Timer:
			if (static_cast<TimerInfo*>(inEventData)->id <= 0) {
				// do not send internal timer events to javascript
				return false;
			}
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(id), INT2VAL(static_cast<TimerInfo*>(inEventData)->id));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(millisec), UINT2VAL(static_cast<TimerInfo*>(inEventData)->millisec));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(msElapsed), UINT2VAL(static_cast<TimerInfo*>(inEventData)->msElapsed));
			break;
%#ifndef PDG_NO_GUI
		case pdg::eventType_KeyDown:
		case pdg::eventType_KeyUp:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(keyCode), INT2VAL(static_cast<KeyInfo*>(inEventData)->keyCode));
			break;
		case pdg::eventType_KeyPress:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(shift), BOOL2VAL(static_cast<KeyPressInfo*>(inEventData)->shift));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(ctrl), BOOL2VAL(static_cast<KeyPressInfo*>(inEventData)->ctrl));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(alt), BOOL2VAL(static_cast<KeyPressInfo*>(inEventData)->alt));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(meta), BOOL2VAL(static_cast<KeyPressInfo*>(inEventData)->meta));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(unicode), INT2VAL(static_cast<KeyPressInfo*>(inEventData)->unicode));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(isRepeating), BOOL2VAL(static_cast<KeyPressInfo*>(inEventData)->isRepeating));
			break;
		case pdg::eventType_SpriteTouch:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(touchType), INT2VAL(static_cast<SpriteTouchInfo*>(inEventData)->touchType));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(touchedSprite), OBJ2VAL(static_cast<SpriteTouchInfo*>(inEventData)->touchedSprite->mSpriteScriptObj));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(inLayer), OBJ2VAL(static_cast<SpriteTouchInfo*>(inEventData)->inLayer->mSpriteLayerScriptObj));
			// break; fall through
		case pdg::eventType_MouseDown:
		case pdg::eventType_MouseUp:
		case pdg::eventType_MouseMove:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(shift), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->shift));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(ctrl), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->ctrl));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(alt), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->alt));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(meta), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->meta));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(mousePos), POINT2VAL(static_cast<MouseInfo*>(inEventData)->mousePos));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(leftButton), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->leftButton));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(rightButton), BOOL2VAL(static_cast<MouseInfo*>(inEventData)->rightButton));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(buttonNumber), UINT2VAL(static_cast<MouseInfo*>(inEventData)->buttonNumber));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(lastClickPos), POINT2VAL(static_cast<MouseInfo*>(inEventData)->lastClickPos));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(lastClickElapsed), UINT2VAL(static_cast<MouseInfo*>(inEventData)->lastClickElapsed));
			break;
		case pdg::eventType_ScrollWheel:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(shift), BOOL2VAL(static_cast<ScrollWheelInfo*>(inEventData)->shift));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(ctrl), BOOL2VAL(static_cast<ScrollWheelInfo*>(inEventData)->ctrl));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(alt), BOOL2VAL(static_cast<ScrollWheelInfo*>(inEventData)->alt));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(meta), BOOL2VAL(static_cast<ScrollWheelInfo*>(inEventData)->meta));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(horizDelta), INT2VAL(static_cast<ScrollWheelInfo*>(inEventData)->horizDelta));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(vertDelta), INT2VAL(static_cast<ScrollWheelInfo*>(inEventData)->vertDelta));
			break;
%#endif // PDG_NO_GUI
%#ifndef PDG_NO_NETWORK
		// not implemented at the moment, since Node.js will provide communications
		case pdg::eventType_NetConnect:
			return false;
			break;
		case pdg::eventType_NetDisconnect:
			return false;
			break;
		case pdg::eventType_NetData:
			return false;
			break;
		case pdg::eventType_NetError:
			return false;
			break;
%#endif // PDG_NO_NETWORK
%#ifndef PDG_NO_SOUND
		case pdg::eventType_SoundEvent: {
            auto* sound = static_cast<SoundEventInfo*>(inEventData)->sound;
            JSObjectRef soundObject = sound->mSoundScriptObj ? sound->mSoundScriptObj : Sound_newFromCpp(ctx, sound);
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(eventCode), INT2VAL(static_cast<SoundEventInfo*>(inEventData)->eventCode));
            OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(sound), OBJ2VAL(soundObject));
			break;
        }
%#endif // PDG_NO_SOUND
%#ifndef PDG_NO_GUI
		case pdg::eventType_PortResized:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(port), OBJ2VAL(static_cast<PortResizeInfo*>(inEventData)->port->mPortScriptObj));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(screenPos), INT2VAL(static_cast<PortResizeInfo*>(inEventData)->screenPos));
			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(oldScreenPos), INT2VAL(static_cast<PortResizeInfo*>(inEventData)->oldScreenPos));
			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(oldWidth), INT2VAL(static_cast<PortResizeInfo*>(inEventData)->oldWidth));
			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(oldHeight), INT2VAL(static_cast<PortResizeInfo*>(inEventData)->oldHeight));
			break;
		case pdg::eventType_PortDraw:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(port), OBJ2VAL(static_cast<PortDrawInfo*>(inEventData)->port->mPortScriptObj));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(frameNum), INT2VAL(static_cast<PortDrawInfo*>(inEventData)->frameNum));
			break;
%#endif // PDG_NO_GUI
        case pdg::eventType_ParticleBreak: {
            const auto* info=static_cast<PhysicsBodyBreakInfo*>(inEventData);
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(angularSpeed),NUM2VAL(info->angularSpeed));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(breakAngularSpeed),NUM2VAL(info->breakAngularSpeed));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(body),(info->body ? OBJ2VAL(info->body->mPhysicsBodyScriptObj ? info->body->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, info->body)) : JSValueMakeNull(ctx)));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(referenceBody),(info->referenceBody ? OBJ2VAL(info->referenceBody->mPhysicsBodyScriptObj ? info->referenceBody->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, info->referenceBody)) : JSValueMakeNull(ctx)));
            break;
        }
        case pdg::eventType_ZoomComplete: {
            const auto* info = static_cast<CameraZoomInfo*>(inEventData);
            OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(camera), OBJ2VAL(emitter->mEventEmitterScriptObj));
            OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(zoom), NUM2VAL(info->zoom));
            break;
        }
        case pdg::eventType_ColliderContact: {
            auto* contact=static_cast<ColliderContact*>(inEventData);
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(collider),(contact->collider->mColliderScriptObj ? contact->collider->mColliderScriptObj : Collider_newFromCpp(ctx, contact->collider)));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(other),(contact->other->mColliderScriptObj ? contact->other->mColliderScriptObj : Collider_newFromCpp(ctx, contact->other)));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(shape),NUM2VAL(contact->shape));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(otherShape),NUM2VAL(contact->otherShape));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(phase),NUM2VAL(contact->phase));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(penetration),NUM2VAL(contact->penetration));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(point),POINT2VAL(contact->point));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(normal),VECTOR2VAL(contact->normal));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(impulse),VECTOR2VAL(contact->impulse));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(sensor),BOOL2VAL(contact->sensor));
            break;
        }
		case pdg::eventType_SpriteCollide:
		case pdg::eventType_SpriteBreak:
			if (inEventType == pdg::eventType_SpriteCollide) {
				if (static_cast<SpriteCollideInfo*>(inEventData)->targetSprite) {
			  		OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(targetSprite), OBJ2VAL(static_cast<SpriteCollideInfo*>(inEventData)->targetSprite->mSpriteScriptObj));
			  	}
			  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(normal), VECTOR2VAL(static_cast<SpriteCollideInfo*>(inEventData)->normal));
			  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(impulse), VECTOR2VAL(static_cast<SpriteCollideInfo*>(inEventData)->impulse));
			  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(force), NUM2VAL(static_cast<SpriteCollideInfo*>(inEventData)->force));
			  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(kineticEnergy), NUM2VAL(static_cast<SpriteCollideInfo*>(inEventData)->kineticEnergy));
			  %#ifdef PDG_USE_CHIPMUNK_PHYSICS
			    if (static_cast<SpriteCollideInfo*>(inEventData)->arbiter) {
		  			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(arbiter), OBJ2VAL(cpArbiter_newFromCpp(ctx, static_cast<SpriteCollideInfo*>(inEventData)->arbiter)));
				}
			  %#endif
			  %#ifdef PDG_SPRITER_SUPPORT
			    if (static_cast<SpriteCollideInfo*>(inEventData)->collisionName) {
					OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(collisionName), STR2VAL(static_cast<SpriteCollideInfo*>(inEventData)->collisionName));
				} else {
					OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(collisionName), JSValueMakeNull(ctx));
				}
			    if (static_cast<SpriteCollideInfo*>(inEventData)->withCollisionName) {
					OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(withCollisionName), STR2VAL(static_cast<SpriteCollideInfo*>(inEventData)->withCollisionName));
				} else {
					OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(withCollisionName), JSValueMakeNull(ctx));
				}
				OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(isFirstContact), BOOL2VAL(static_cast<SpriteCollideInfo*>(inEventData)->isFirstContact));
			  %#endif
 			} else {
                auto* sjb = static_cast<SpriteJointBreakInfo*>(inEventData);
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(targetSprite), (sjb->targetSprite ? OBJ2VAL(sjb->targetSprite->mSpriteScriptObj) : JSValueMakeNull(ctx)));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(impulse), NUM2VAL(sjb->impulse));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(force), NUM2VAL(sjb->force));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(breakForce), NUM2VAL(sjb->breakForce));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(reason), NUM2VAL(sjb->reason));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(angularSpeed), NUM2VAL(sjb->angularSpeed));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(breakAngularSpeed), NUM2VAL(sjb->breakAngularSpeed));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(body), (sjb->body ? OBJ2VAL(sjb->body->mPhysicsBodyScriptObj ? sjb->body->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, sjb->body)) : JSValueMakeNull(ctx)));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(referenceBody), (sjb->referenceBody ? OBJ2VAL(sjb->referenceBody->mPhysicsBodyScriptObj ? sjb->referenceBody->mPhysicsBodyScriptObj : PhysicsBody_newFromCpp(ctx, sjb->referenceBody)) : JSValueMakeNull(ctx)));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(part), (sjb->part ? OBJ2VAL(sjb->part->mPartScriptObj ? sjb->part->mPartScriptObj : Part_newFromCpp(ctx, sjb->part)) : JSValueMakeNull(ctx)));
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(joint), (sjb->joint ? OBJ2VAL(cpConstraint_newFromCpp(ctx, sjb->joint)) : JSValueMakeNull(ctx)));
%#else
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(joint), JSValueMakeNull(ctx));
%#endif
 			}
			// break; fall through
        %#ifdef PDG_SPRITER_SUPPORT
        case pdg::eventType_SpriteTriggerEvent: {
            // Collision/break events also fall through to the common animation fields.
            if (inEventType == pdg::eventType_SpriteTriggerEvent) {
            auto* trigger=static_cast<SpriteTriggerEventInfo*>(inEventData);
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(triggerName),STR2VAL(trigger->triggerName));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(clipName),STR2VAL(trigger->clipName));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(entityName),STR2VAL(trigger->entityName));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(timeSeconds),NUM2VAL(trigger->timeSeconds));
            OBJECT_SET_PROPERTY_VALUE(jsEvent,SYMBOL(offsetSeconds),NUM2VAL(trigger->offsetSeconds));
        }
        }
        // Trigger events share SpriteAnimateInfo ownership fields.
        %#endif
		case pdg::eventType_SpriteAnimate:

            if (inEventType==pdg::eventType_SpriteAnimate && static_cast<SpriteAnimateInfo*>(inEventData)->action==Sprite::action_AnimationPhysicsRecoveryComplete) {
                const auto* recovery=static_cast<SpriteAnimationPhysicsRecoveryInfo*>(inEventData);
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(id), NUM2VAL(recovery->id));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(bone), UINT2VAL(recovery->bone));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(wholeRig), BOOL2VAL(recovery->wholeRig));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(includeDescendants), BOOL2VAL(recovery->includeDescendants));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(mode), INT2VAL(recovery->mode));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(bodyCount), UINT2VAL(recovery->bodyCount));
                OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(disabled), BOOL2VAL(recovery->disabled));
            }
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(action), INT2VAL(static_cast<SpriteAnimateInfo*>(inEventData)->action));
			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(actingSprite), (static_cast<SpriteAnimateInfo*>(inEventData)->actingSprite ? OBJ2VAL(static_cast<SpriteAnimateInfo*>(inEventData)->actingSprite->mSpriteScriptObj) : NULL_VAL));
			OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(inLayer), (static_cast<SpriteAnimateInfo*>(inEventData)->inLayer ? OBJ2VAL(static_cast<SpriteAnimateInfo*>(inEventData)->inLayer->mSpriteLayerScriptObj) : NULL_VAL));
			break;
		case pdg::eventType_SpriteLayer:
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(action), INT2VAL(static_cast<SpriteLayerInfo*>(inEventData)->action));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(actingLayer), OBJ2VAL(static_cast<SpriteLayerInfo*>(inEventData)->actingLayer->mSpriteLayerScriptObj));
		  	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(millisec), UINT2VAL(static_cast<SpriteLayerInfo*>(inEventData)->millisec));
			break;
		default: {
			std::ostringstream msg;
			msg << "unknown event (" << inEventType << ")";
			SAVE_TYPE_ERR(msg.str().c_str());
			return false; // can't handle event we don't know about
			}
			break;
	
	}

    VALUE argv[1];
    argv[0] = OBJ2VAL(jsEvent);

    DEBUG_DUMP_SCRIPT_OBJECT(this->mIEventHandlerScriptObj, IEventHandler);

    FUNCTION_REF func;
    if (mScriptHandlerFunc) {
		func = mScriptHandlerFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mIEventHandlerScriptObj, SYMBOL(handleEvent)) );
	}
	
//    JSC_DebugPrintObject(ctx, func, "About to call Handler Func:");
    VALUE resVal = CALL_SCRIPT(func, this->mIEventHandlerScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	if (!VALUE_IS_BOOL(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return false;
	}
	return VAL2BOOL(resVal);
}

// ========================================================================================
//MARK: Script Touch Event Handler
// ========================================================================================

ScriptTouchEventHandler::ScriptTouchEventHandler() {
    mScriptHandlerFunc = 0;
    mExpectedAction = 0;
}

ScriptTouchEventHandler::ScriptTouchEventHandler(FUNCTION_REF func, long expectedAction) {
	mScriptHandlerFunc = func;
	mExpectedAction = expectedAction;
	JSValueProtect(gMainContext, mScriptHandlerFunc);
}

bool ScriptTouchEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept {
	SETUP_NON_SCRIPT_CALL;

	// Only handle SpriteTouch events
	if (inEventType != pdg::eventType_SpriteTouch) {
		return false;
	}

	// Check if this is the specific touch type we're looking for
	SpriteTouchInfo* touchInfo = static_cast<SpriteTouchInfo*>(inEventData);
	if (touchInfo->touchType != mExpectedAction) {
		return false;
	}

	OBJECT jsEvent = OBJECT_CREATE_EMPTY(0);
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(emitter), OBJ2VAL(emitter->mEventEmitterScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(eventType), INT2VAL(inEventType));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(touchType), INT2VAL(touchInfo->touchType));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(touchedSprite), OBJ2VAL(touchInfo->touchedSprite->mSpriteScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(inLayer), OBJ2VAL(touchInfo->inLayer->mSpriteLayerScriptObj));

    VALUE argv[1];
    argv[0] = OBJ2VAL(jsEvent);

    DEBUG_DUMP_SCRIPT_OBJECT(this->mIEventHandlerScriptObj, IEventHandler);

    FUNCTION_REF func;
    if (mScriptHandlerFunc) {
		func = mScriptHandlerFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mIEventHandlerScriptObj, SYMBOL(handleEvent)) );
	}
	
    VALUE resVal = CALL_SCRIPT(func, this->mIEventHandlerScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	if (!VALUE_IS_BOOL(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return false;
	}
	return VAL2BOOL(resVal);
}

// ========================================================================================
//MARK: Script Layer Event Handler
// ========================================================================================

ScriptLayerEventHandler::ScriptLayerEventHandler() {
    mScriptHandlerFunc = 0;
    mExpectedAction = 0;
}

ScriptLayerEventHandler::ScriptLayerEventHandler(FUNCTION_REF func, long expectedAction) {
	mScriptHandlerFunc = func;
	mExpectedAction = expectedAction;
	JSValueProtect(gMainContext, mScriptHandlerFunc);
}

bool ScriptLayerEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept {
	SETUP_NON_SCRIPT_CALL;

	// Only handle SpriteLayer events
	if (inEventType != pdg::eventType_SpriteLayer) {
		return false;
	}

	// Check if this is the specific action we're looking for
	SpriteLayerInfo* layerInfo = static_cast<SpriteLayerInfo*>(inEventData);
	if (layerInfo->action != mExpectedAction) {
		return false;
	}

	OBJECT jsEvent = OBJECT_CREATE_EMPTY(0);
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(emitter), OBJ2VAL(emitter->mEventEmitterScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(eventType), INT2VAL(inEventType));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(action), INT2VAL(layerInfo->action));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(actingLayer), OBJ2VAL(layerInfo->actingLayer->mSpriteLayerScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(millisec), UINT2VAL(layerInfo->millisec));

    VALUE argv[1];
    argv[0] = OBJ2VAL(jsEvent);

    DEBUG_DUMP_SCRIPT_OBJECT(this->mIEventHandlerScriptObj, IEventHandler);

    FUNCTION_REF func;
    if (mScriptHandlerFunc) {
		func = mScriptHandlerFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mIEventHandlerScriptObj, SYMBOL(handleEvent)) );
	}
	
    VALUE resVal = CALL_SCRIPT(func, this->mIEventHandlerScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	if (!VALUE_IS_BOOL(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return false;
	}
	return VAL2BOOL(resVal);
}

// ========================================================================================
//MARK: Script Animation Helper
// ========================================================================================

DECLARE_SYMBOL(animate);

// ScriptAnimationHelper::ScriptAnimationHelper() {
// }
// 
ScriptAnimationHelper::ScriptAnimationHelper(SAVED_FUNCTION func) {
	mScriptAnimateFunc = func;
	JSValueProtect(gMainContext, mScriptAnimateFunc);
}

ScriptAnimationHelper::~ScriptAnimationHelper() {
    if (mScriptAnimateFunc) JSValueUnprotect(gMainContext, mScriptAnimateFunc);
}
void ScriptAnimationHelper::initializeScriptObject() {
    if (!mScriptAnimateFunc) return;
    JSStringRef key = JSStringCreateWithUTF8CString("_pdgAnimationCallback");
    JSObjectSetProperty(gMainContext, mIAnimationHelperScriptObj, key, mScriptAnimateFunc,
        kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum | kJSPropertyAttributeDontDelete, nullptr);
    JSStringRelease(key);
    JSValueUnprotect(gMainContext, mScriptAnimateFunc);
    mScriptAnimateFunc = nullptr;
}
void ScriptAnimationHelper::retainForAnimation() {
    addRef();
    if (mAnimationRetains++ == 0 && mIAnimationHelperScriptObj)
        JSValueProtect(gMainContext, mIAnimationHelperScriptObj);
}
void ScriptAnimationHelper::releaseForAnimation() {
    if (--mAnimationRetains == 0 && mIAnimationHelperScriptObj)
        JSValueUnprotect(gMainContext, mIAnimationHelperScriptObj);
    release();
}

bool ScriptAnimationHelper::animate(AnimatedBase* what, double deltaSeconds) noexcept {
	SETUP_NON_SCRIPT_CALL;
    VALUE argv[2];
    if (!what->mAnimatedScriptObj) {
        if (auto* particle = dynamic_cast<Particle*>(what)) Particle_newFromCpp(ctx, particle);
        else if (auto* emission = dynamic_cast<ParticleEmitter*>(what)) ParticleEmitter_newFromCpp(ctx, emission);
        else if (auto* part = dynamic_cast<Part*>(what)) Part_newFromCpp(ctx, part);
        else if (auto* sprite = dynamic_cast<Sprite*>(what)) Sprite_newFromCpp(ctx, sprite);
        else if (auto* camera = dynamic_cast<Camera*>(what)) Camera_newFromCpp(ctx, camera);
        else AnimatedBase_newFromCpp(ctx, what);
    }
    argv[0] = OBJ2VAL(what->mAnimatedScriptObj);
    argv[1] = NUM2VAL(deltaSeconds);

    DEBUG_DUMP_SCRIPT_OBJECT(what->mAnimatedScriptObj, AnimatedBase);
    DEBUG_DUMP_SCRIPT_OBJECT(this->mIAnimationHelperScriptObj, IAnimationHelper);

    FUNCTION_REF func;
    JSStringRef key = JSStringCreateWithUTF8CString("_pdgAnimationCallback");
    VALUE callback = JSObjectGetProperty(ctx, mIAnimationHelperScriptObj, key, nullptr);
    JSStringRelease(key);
    if (VALUE_IS_FUNCTION(callback)) {
        func = VAL2FUNC(callback);
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mIAnimationHelperScriptObj, SYMBOL(animate)) );
	}
    VALUE resVal = CALL_SCRIPT(func, this->mIAnimationHelperScriptObj, 2, argv);

//    JSC_DebugPrintValue(gMainContext, resVal, "IAnimationHelper return:");
//        JSC_DebugPrintValue(gMainContext, func, "Animation Helper Func:");
        
    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Animation Helper!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	if (!VALUE_IS_BOOL(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from animate helper Function must be a boolean ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return false;
	}
	return VAL2BOOL(resVal);
}

// ========================================================================================
//MARK: Script Animation Event Handler
// ========================================================================================

ScriptAnimationEventHandler::ScriptAnimationEventHandler() {
	mScriptHandlerFunc = 0;
	mExpectedAction = 0;
}

ScriptAnimationEventHandler::ScriptAnimationEventHandler(SAVED_FUNCTION func, long expectedAction) {
	mScriptHandlerFunc = func;
	mExpectedAction = expectedAction;
	JSValueProtect(gMainContext, mScriptHandlerFunc);
}

bool ScriptAnimationEventHandler::handleEvent(EventEmitter* emitter, long inEventType, void* inEventData) noexcept {
	SETUP_NON_SCRIPT_CALL;

	// Only handle SpriteAnimate events
	if (inEventType != pdg::eventType_SpriteAnimate) {
		return false;
	}

	// Check if this is the specific action we're looking for
	SpriteAnimateInfo* animateInfo = static_cast<SpriteAnimateInfo*>(inEventData);
	if (animateInfo->action != mExpectedAction) {
		return false;
	}

	// Add null pointer checks to prevent segmentation faults
	if (!animateInfo->actingSprite || !animateInfo->inLayer) {
		return false;
	}

	OBJECT jsEvent = OBJECT_CREATE_EMPTY(0);
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(emitter), OBJ2VAL(emitter->mEventEmitterScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(eventType), INT2VAL(inEventType));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(action), INT2VAL(animateInfo->action));
    if(animateInfo->action==Sprite::action_AnimationPhysicsRecoveryComplete) {
        const auto* recovery=static_cast<SpriteAnimationPhysicsRecoveryInfo*>(inEventData);
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(id), NUM2VAL(recovery->id));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(bone), UINT2VAL(recovery->bone));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(wholeRig), BOOL2VAL(recovery->wholeRig));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(includeDescendants), BOOL2VAL(recovery->includeDescendants));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(mode), INT2VAL(recovery->mode));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(bodyCount), UINT2VAL(recovery->bodyCount));
        OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(disabled), BOOL2VAL(recovery->disabled));
    }

	
	// Add additional null checks for script objects
	if (!animateInfo->actingSprite->mSpriteScriptObj) {
		return false;
	}
	if (!animateInfo->inLayer->mSpriteLayerScriptObj) {
		return false;
	}
	
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(actingSprite), OBJ2VAL(animateInfo->actingSprite->mSpriteScriptObj));
	OBJECT_SET_PROPERTY_VALUE(jsEvent, SYMBOL(inLayer), OBJ2VAL(animateInfo->inLayer->mSpriteLayerScriptObj));

    VALUE argv[1];
    argv[0] = OBJ2VAL(jsEvent);

    DEBUG_DUMP_SCRIPT_OBJECT(this->mIEventHandlerScriptObj, IEventHandler);

    FUNCTION_REF func;
    if (mScriptHandlerFunc) {
		func = mScriptHandlerFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mIEventHandlerScriptObj, SYMBOL(handleEvent)) );
	}
	
    VALUE resVal = CALL_SCRIPT(func, this->mIEventHandlerScriptObj, 1, argv);

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling event Handler!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	if (!VALUE_IS_BOOL(resVal)) {
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from event handler Function must be a boolean ("
		    << FUNCTION_GET_NAME(func) << " at " << FUNCTION_GET_FILE_AND_LINE(func) << ")\n";
		exit(1);
	  )
	    return false;
	}
	return VAL2BOOL(resVal);
}

// ========================================================================================
//MARK: Script Sprite Collide Helper
// ========================================================================================

DECLARE_SYMBOL(allowCollision);

%#ifndef PDG_NO_GUI
// ========================================================================================
//MARK: Script Sprite Draw Helper
// ========================================================================================

DECLARE_SYMBOL(draw);

ScriptSpriteDrawHelper::ScriptSpriteDrawHelper(SAVED_FUNCTION func) {
	mScriptDrawFunc = func;
	JSValueProtect(gMainContext, mScriptDrawFunc);
}

bool ScriptSpriteDrawHelper::draw(Sprite* sprite, Port* port) noexcept {
	SETUP_NON_SCRIPT_CALL;
    VALUE argv[2];
    argv[0] = OBJ2VAL(sprite->mSpriteScriptObj);
    argv[1] = OBJ2VAL(port->mPortScriptObj);

    DEBUG_DUMP_SCRIPT_OBJECT(sprite->mSpriteScriptObj, Sprite);
    DEBUG_DUMP_SCRIPT_OBJECT(port->mPortScriptObj, Port);
    DEBUG_DUMP_SCRIPT_OBJECT(this->mISpriteDrawHelperScriptObj, IDrawSpriteHelper);

    FUNCTION_REF func;
    if (mScriptDrawFunc) {
		func = mScriptDrawFunc;
    } else {
    	func = VAL2FUNC( OBJECT_GET_PROPERTY(mISpriteDrawHelperScriptObj, SYMBOL(draw)) );
	}
    VALUE resVal = CALL_SCRIPT(func, this->mISpriteDrawHelperScriptObj, 2, argv);

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Script Fatal Exception calling Sprite Draw Helper!!" ); )
		FatalException(EXCEPTION_DATA);
		return false;
    }
	return VAL2BOOL(resVal);
}
%#endif // !PDG_NO_GUI


// ========================================================================================
//MARK: Utility Functions
// ========================================================================================

// =========================  easing functions =============================

// Native easing slots include all ten script bridges; script registrations
// have their own count and must not treat those bridges as occupied callbacks.
static int sNumScriptEasings = 0;

float CallScriptEasingFunc(int which, double ut, float b, float c, double ud) {
    SETUP_NON_SCRIPT_CALL;
	if (which < 0 || which >= sNumScriptEasings) {
	  %#ifdef DEBUG
		std::cerr << "logic error: attempting to call an unregistered easing function #"
		    << which << "(only "<< sNumScriptEasings <<" custom easings have been"
		    " registered via registerEasingFunction())\n";
		exit(1);
	  %#else
	  	return 0.0f; // don't do anything in release builds
	  %#endif
	}

    VALUE argv[4];
    argv[0] = NUM2VAL(ut);
    argv[1] = NUM2VAL(b);
    argv[2] = NUM2VAL(c);
    argv[3] = NUM2VAL(ud);
    VALUE resVal = CALL_SCRIPT(s_CustomJavascriptEasing[which], 0, 4, argv); // global this

    CATCH_EXCEPTION(resVal) {
		DEBUG_ONLY( OS::_DOUT( "Javascript Fatal Exception calling Easing Function!!" ); )
		FatalException(EXCEPTION_DATA);
		return 0.0f;
    }
	if (!VALUE_IS_NUMBER(resVal)) {
		// TODO: call FatalError
	  DEBUG_ONLY(
		std::cerr << "result mismatch: return value from easing Function must be a Number ("
		    << FUNCTION_GET_NAME(s_CustomJavascriptEasing[which]) << " at " 
		    << FUNCTION_GET_FILE_AND_LINE(s_CustomJavascriptEasing[which]) << ")\n";
		exit(1);
	  )
	    return 0.0f;
	}
	return JSValueToNumber(ctx, resVal, 0);	
}

FUNCTION_IMPL(RegisterEasingFunction)
	METHOD_SIGNATURE("", [number int], 1, (function easingFunc)); 
    REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, easingFunc);
    if (sNumScriptEasings >= MAX_CUSTOM_EASINGS) {
        THROW_ERR_LITERAL("Custom easing function capacity exceeded");
    } else {
        // Keep the actual callback/closure. Function.toString() is source code,
        // not an identifier that can be used in a generated variable declaration.
        s_CustomJavascriptEasing[sNumScriptEasings] = easingFunc;
        JSValueProtect(ctx, easingFunc);
        const int funcId = NUM_BUILTIN_EASINGS + sNumScriptEasings;
        CallScriptEasingFunc(sNumScriptEasings++, 0, 0.0f, 0.0f, 1);
        RETURN_INT32(funcId);
    }
	NO_RETURN;
END


FUNCTION_IMPL(DeleteAnimationScript)
    REQUIRE_ARG_COUNT(1);
    REQUIRE_STRING_ARG(1, name);
    try { const bool removed=AnimatedBase::deleteScript(name); RETURN_BOOL(removed); }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END

FUNCTION_IMPL(DefineAnimationScript)
    REQUIRE_ARG_COUNT(1);
    REQUIRE_STRING_ARG(1, name);
    try { auto* builder=&AnimatedBase::defineScript(name); RETURN_CPP_OBJECT(builder, AnimationScript); }
    catch (const std::exception& error) { THROW_ERR_MESSAGE(error.what()); }
END

FUNCTION_IMPL(FinishedScriptSetup)
	scriptSetupCompleted();  // let the application do anything further it needs to
	NO_RETURN;
END


SCRIPT_DEBUG_ONLY(
static size_t sLastHeapUsed = 0;
static ms_time sIdleLastHeapReport = OS::getMilliseconds();
)

void initBindings(JSContextRef ctx, JSObjectRef exports) {

	// register all our customEasing functions with pdg C++
	easingFuncToId(customEasing0);
	easingFuncToId(customEasing1);
	easingFuncToId(customEasing2);
	easingFuncToId(customEasing3);
	easingFuncToId(customEasing4);
	easingFuncToId(customEasing5);
	easingFuncToId(customEasing6);
	easingFuncToId(customEasing7);
	easingFuncToId(customEasing8);
	easingFuncToId(customEasing9);

    // save our binding target for runtime bindings, such as easing functions
    gMainContext = ctx;
    JSValueRef exceptionValue = 0;
    JSValueRef* exception = &exceptionValue;

    JSObjectRef globalObject = exports; //JSContextGetGlobalObject(ctx);
//	VALUE const_val;  // used by the INIT_CONSTANT macro	

	INIT_CLASS(MemBlock);
	INIT_CLASS(FileManager);
	INIT_CLASS(LogManager);
	INIT_CLASS(ConfigManager);
	INIT_CLASS(ResourceManager);
	INIT_CLASS(Serializer);
	INIT_CLASS(Deserializer);
	INIT_CLASS(ISerializable);
	INIT_CLASS(IEventHandler);
	INIT_CLASS(EventEmitter);
	INIT_CLASS(EventManager);
	INIT_CLASS(TimerManager);
	INIT_CLASS(IAnimationHelper);
	INIT_CLASS_NAMED(AnimatedBase, "Animated");
    INIT_CLASS(AnimationScript);
    INIT_CLASS(Troupe);
	INIT_CLASS(Part);
%#ifdef PDG_SPRITER_SUPPORT
    INIT_CLASS(Bone);
%#endif
    INIT_CLASS(CollisionQueryBuffer);
    INIT_CLASS(Scene);
    INIT_CLASS(Camera);
    INIT_CLASS(Particle);
    INIT_CLASS(ParticleEmitter);
    INIT_CLASS(PhysicsBody);
    INIT_CLASS(Collider);
    INIT_CLASS(PhysicsConstraint);
  %#ifdef PDG_USE_CHIPMUNK_PHYSICS
	INIT_CLASS(cpArbiter);
	INIT_CLASS(cpConstraint);
	INIT_CLASS(cpSpace);
  %#endif // PDG_USE_CHIPMUNK_PHYSICS
  %#ifndef PDG_NO_GUI
	INIT_CLASS(ISpriteDrawHelper);
  %#endif // !PDG_NO_GUI
	INIT_CLASS(Sprite);
	INIT_CLASS(SpriteLayer);
	INIT_CLASS(TileLayer);
	INIT_CLASS(Image);
	INIT_CLASS(ImageStrip);
	INIT_CLASS(Spline);
	INIT_CLASS(Polygon);
	INIT_CLASS(Attributes);
    INIT_CLASS_NAMED(AnimatedAttributesBase, "AnimatedAttributes");
	INIT_CLASS(ElementRef);
	INIT_CLASS(Drawing);
  %#ifndef PDG_NO_GUI
	INIT_CLASS(Font);
	INIT_CLASS(Port);
	INIT_CLASS(GraphicsManager);
  %#endif
  %#ifndef PDG_NO_SOUND
	INIT_CLASS(Sound);
	INIT_CLASS(SoundManager);
  %#endif

	// methods of this module
	INIT_FUNCTION("_idle", Idle);
	INIT_FUNCTION("_run", Run);
	INIT_FUNCTION("_quit", Quit);
	INIT_FUNCTION("_isQuitting", IsQuitting);
	INIT_FUNCTION("_finishedScriptSetup", FinishedScriptSetup);

//    INIT_FUNCTION("rand", Rand);
//    INIT_FUNCTION("gameCriticalRandom", GameCriticalRandom);
    INIT_FUNCTION("rand", GameCriticalRandom);
    INIT_FUNCTION("srand", Srand);
    
	INIT_FUNCTION("setSerializationDebugMode", SetSerializationDebugMode);

    INIT_FUNCTION("registerEasingFunction", RegisterEasingFunction);
    INIT_FUNCTION("_defineAnimationScript", DefineAnimationScript);
    INIT_FUNCTION("_deleteAnimationScript", DeleteAnimationScript);
    
    INIT_FUNCTION("getFileManager", GetFileManager);
    INIT_FUNCTION("getLogManager", GetLogManager);
    INIT_FUNCTION("getConfigManager", GetConfigManager);
    INIT_FUNCTION("getResourceManager", GetResourceManager);
    INIT_FUNCTION("getEventManager", GetEventManager);
    INIT_FUNCTION("getTimerManager", GetTimerManager);
    INIT_FUNCTION("registerSerializableClass", RegisterSerializableClass);
    
  %#ifndef PDG_NO_GUI
	INIT_FUNCTION("getGraphicsManager", GetGraphicsManager);
  %#endif
  %#ifndef PDG_NO_SOUND
    INIT_FUNCTION("getSoundManager", GetSoundManager);
  %#endif

	INIT_FUNCTION("createSpriteLayer", CreateSpriteLayer);
	INIT_FUNCTION("cleanupLayer", CleanupLayer);
%#ifdef PDG_SPRITER_SUPPORT
	INIT_FUNCTION("createSpriteLayerFromSpriterFile", CreateSpriteLayerFromSpriterFile);
%#endif
	INIT_FUNCTION("createTileLayer", CreateTileLayer);
	INIT_FUNCTION("createDrawing", CreateDrawing);

	// Constants
    INIT_CONSTANT("all_events", all_events);
//	INIT_CONSTANT("eventType_Startup", eventType_Startup);
	INIT_CONSTANT("eventType_Shutdown", eventType_Shutdown);
	INIT_CONSTANT("eventType_Timer", eventType_Timer);
	INIT_CONSTANT("eventType_KeyDown", eventType_KeyDown);
	INIT_CONSTANT("eventType_KeyUp", eventType_KeyUp);
	INIT_CONSTANT("eventType_KeyPress", eventType_KeyPress);
	INIT_CONSTANT("eventType_MouseDown", eventType_MouseDown);
	INIT_CONSTANT("eventType_MouseUp", eventType_MouseUp);
	INIT_CONSTANT("eventType_MouseMove", eventType_MouseMove);
	INIT_CONSTANT("eventType_MouseEnter", eventType_MouseEnter);
	INIT_CONSTANT("eventType_MouseLeave", eventType_MouseLeave);
	INIT_CONSTANT("eventType_PortResized", eventType_PortResized);
	INIT_CONSTANT("eventType_ScrollWheel", eventType_ScrollWheel);
	INIT_CONSTANT("eventType_SpriteTouch", eventType_SpriteTouch);
	INIT_CONSTANT("eventType_SpriteAnimate", eventType_SpriteAnimate);
	INIT_CONSTANT("eventType_SpriteTriggerEvent", eventType_SpriteTriggerEvent);
	INIT_CONSTANT("eventType_SpriteLayer", eventType_SpriteLayer);
	INIT_CONSTANT("eventType_SpriteCollide", eventType_SpriteCollide);
    INIT_CONSTANT("collisionShape_Polygon", collisionShape_Polygon);
    INIT_CONSTANT("collisionShape_ImageMask", collisionShape_ImageMask);
    INIT_CONSTANT("collisionShape_Capsule", collisionShape_Capsule);
    INIT_CONSTANT("colliderSource_Explicit", colliderSource_Explicit);
    INIT_CONSTANT("colliderSource_Frame", colliderSource_Frame);
    INIT_CONSTANT("colliderSource_Animation", colliderSource_Animation);
    INIT_CONSTANT("frameCollider_Bounds", frameCollider_Bounds);
    INIT_CONSTANT("frameCollider_AlphaMask", frameCollider_AlphaMask);
    INIT_CONSTANT("eventType_ZoomComplete", eventType_ZoomComplete);
    INIT_CONSTANT("camera_Crossfade", camera_Crossfade);
    INIT_CONSTANT("camera_WipeLeft", camera_WipeLeft);
    INIT_CONSTANT("camera_WipeRight", camera_WipeRight);
    INIT_CONSTANT("camera_WipeUp", camera_WipeUp);
    INIT_CONSTANT("camera_WipeDown", camera_WipeDown);
    INIT_CONSTANT("camera_LumaFade", camera_LumaFade);
    INIT_CONSTANT("camera_WhipLeft", camera_WhipLeft);
    INIT_CONSTANT("camera_WhipRight", camera_WhipRight);
    INIT_CONSTANT("camera_WhipUp", camera_WhipUp);
    INIT_CONSTANT("camera_WhipDown", camera_WhipDown);
    INIT_CONSTANT("matchSource", matchSource);
    INIT_CONSTANT("matchSourceAndSize", matchSourceAndSize);
    INIT_CONSTANT("matchTarget", matchTarget);
    INIT_CONSTANT("matchTargetAndSize", matchTargetAndSize);
    INIT_CONSTANT("eventType_ColliderContact", eventType_ColliderContact);
    INIT_CONSTANT("eventType_ParticleBreak", eventType_ParticleBreak);
	INIT_CONSTANT("eventType_SpriteBreak", eventType_SpriteBreak);
	INIT_CONSTANT("eventType_SoundEvent", eventType_SoundEvent);
	INIT_CONSTANT("eventType_PortDraw", eventType_PortDraw);

	INIT_CONSTANT("soundEvent_DonePlaying", soundEvent_DonePlaying);
	INIT_CONSTANT("soundEvent_Looping", soundEvent_Looping);
	INIT_CONSTANT("soundEvent_FailedToPlay", soundEvent_FailedToPlay);

    INIT_CONSTANT("key_Break", key_Break); 
	INIT_CONSTANT("key_Home", key_Home);
	INIT_CONSTANT("key_End", key_End);
    INIT_CONSTANT("key_Clear", key_Clear);
    INIT_CONSTANT("key_Help", key_Help);
    INIT_CONSTANT("key_Pause", key_Pause);
    INIT_CONSTANT("key_Mute", key_Mute);
    INIT_CONSTANT("key_Backspace", key_Backspace);
    INIT_CONSTANT("key_Delete", key_Delete);
    INIT_CONSTANT("key_Tab", key_Tab);
    INIT_CONSTANT("key_PageUp", key_PageUp);
    INIT_CONSTANT("key_PageDown", key_PageDown);
    INIT_CONSTANT("key_Return", key_Return);
    INIT_CONSTANT("key_Enter", key_Enter);
    INIT_CONSTANT("key_F1", key_F1);
    INIT_CONSTANT("key_F2", key_F2);
    INIT_CONSTANT("key_F3", key_F3);
    INIT_CONSTANT("key_F4", key_F4);
    INIT_CONSTANT("key_F5", key_F5);
    INIT_CONSTANT("key_F6", key_F6);
    INIT_CONSTANT("key_F7", key_F7);
    INIT_CONSTANT("key_F8", key_F8);
    INIT_CONSTANT("key_F9", key_F9);
    INIT_CONSTANT("key_F10", key_F10);
    INIT_CONSTANT("key_F11", key_F11);
    INIT_CONSTANT("key_F12", key_F12);
    INIT_CONSTANT("key_FirstF", key_FirstF);
    INIT_CONSTANT("key_LastF", key_LastF);
    INIT_CONSTANT("key_Insert", key_Insert);
    INIT_CONSTANT("key_Escape", key_Escape);
    INIT_CONSTANT("key_LeftArrow", key_LeftArrow);
    INIT_CONSTANT("key_RightArrow", key_RightArrow);
    INIT_CONSTANT("key_UpArrow", key_UpArrow);
    INIT_CONSTANT("key_DownArrow", key_DownArrow);
    INIT_CONSTANT("key_FirstPrintable", key_FirstPrintable);
    
    // Platform-specific raw keycodes for modifier keys
    INIT_CONSTANT("keyCode_LeftShift", keyCode_LeftShift);
    INIT_CONSTANT("keyCode_RightShift", keyCode_RightShift);
    INIT_CONSTANT("keyCode_LeftControl", keyCode_LeftControl);
    INIT_CONSTANT("keyCode_RightControl", keyCode_RightControl);
    INIT_CONSTANT("keyCode_LeftAlt", keyCode_LeftAlt);
    INIT_CONSTANT("keyCode_RightAlt", keyCode_RightAlt);
    INIT_CONSTANT("keyCode_LeftMeta", keyCode_LeftMeta);
    INIT_CONSTANT("keyCode_RightMeta", keyCode_RightMeta);
    INIT_CONSTANT("keyCode_Shift", keyCode_Shift);
    INIT_CONSTANT("keyCode_Control", keyCode_Control);
    INIT_CONSTANT("keyCode_Alt", keyCode_Alt);
    INIT_CONSTANT("keyCode_Meta", keyCode_Meta);
    
    INIT_CONSTANT("screenPos_Normal", screenPos_Normal);
    INIT_CONSTANT("screenPos_Rotated180", screenPos_Rotated180);
    INIT_CONSTANT("screenPos_Rotated90Clockwise", screenPos_Rotated90Clockwise);
    INIT_CONSTANT("screenPos_Rotated90CounterClockwise", screenPos_Rotated90CounterClockwise);
    INIT_CONSTANT("screenPos_FaceUp", screenPos_FaceUp);
    INIT_CONSTANT("screenPos_FaceDown", screenPos_FaceDown);
    
    // Attributes stores text styles even in headless builds.
    INIT_CONSTANT("textStyle_Plain", textStyle_Plain);
	INIT_CONSTANT("textStyle_Bold", textStyle_Bold);
	INIT_CONSTANT("textStyle_Italic", textStyle_Italic);
	INIT_CONSTANT("textStyle_Underline", textStyle_Underline);
	INIT_CONSTANT("textStyle_Centered", textStyle_Centered);
	INIT_CONSTANT("textStyle_LeftJustified", textStyle_LeftJustified);
	INIT_CONSTANT("textStyle_RightJustified", textStyle_RightJustified);

	INIT_CONSTANT("lineStyle_Auto", lineStyle_Auto);
	INIT_CONSTANT("lineStyle_None", lineStyle_None);
	INIT_CONSTANT("lineStyle_Solid", lineStyle_Solid);
	INIT_CONSTANT("lineStyle_Dashed", lineStyle_Dashed);
	INIT_CONSTANT("lineStyle_Dotted", lineStyle_Dotted);
	INIT_CONSTANT("lineStyle_DashDot", lineStyle_DashDot);
	INIT_CONSTANT("lineStyle_DashDotDot", lineStyle_DashDotDot);

	INIT_CONSTANT("blendMode_Normal", blendMode_Normal);
	INIT_CONSTANT("blendMode_Additive", blendMode_Additive);
	INIT_CONSTANT("blendMode_Multiply", blendMode_Multiply);
	INIT_CONSTANT("blendMode_Screen", blendMode_Screen);
	INIT_CONSTANT("blendMode_Darken", blendMode_Darken);
	INIT_CONSTANT("blendMode_Lighten", blendMode_Lighten);

	INIT_CONSTANT("type_Line", type_Line);
	INIT_CONSTANT("type_Spline", type_Spline);
	INIT_CONSTANT("type_Arc", type_Arc);
	INIT_CONSTANT("type_Rect", type_Rect);
	INIT_CONSTANT("type_Quad", type_Quad);
	INIT_CONSTANT("type_Polygon", type_Polygon);
	INIT_CONSTANT("type_Ellipse", type_Ellipse);
	INIT_CONSTANT("type_Image", type_Image);
	INIT_CONSTANT("type_ImageStrip", type_ImageStrip);
	INIT_CONSTANT("type_Drawing", type_Drawing);
	INIT_CONSTANT("type_Text", type_Text);

	INIT_CONSTANT("gradientType_None", gradientType_None);
	INIT_CONSTANT("gradientType_Linear", gradientType_Linear);
	INIT_CONSTANT("gradientType_Radial", gradientType_Radial);

	INIT_CONSTANT("fit_None", fit_None);
   	INIT_CONSTANT("fit_Fill", fit_Fill);
    INIT_CONSTANT("fit_Height", fit_Height);
    INIT_CONSTANT("fit_Width", fit_Width);
    INIT_CONSTANT("fit_Inside", fit_Inside);
    INIT_CONSTANT("fit_Overflow", fit_Overflow);
    INIT_CONSTANT("fit_FillKeepProportions", fit_Overflow);
    INIT_CONSTANT("fit_Clipped", fit_Clipped);
    INIT_CONSTANT("fit_TileX", fit_TileX);
    INIT_CONSTANT("fit_TileY", fit_TileY);
    INIT_CONSTANT("fit_Tile", fit_Tile);

    INIT_CONSTANT("init_CreateUniqueNewFile", LogManager::init_CreateUniqueNewFile);
    INIT_CONSTANT("init_OverwriteExisting", LogManager::init_OverwriteExisting);
    INIT_CONSTANT("init_AppendToExisting", LogManager::init_AppendToExisting);
    INIT_CONSTANT("init_StdOut", LogManager::init_StdOut);
    INIT_CONSTANT("init_StdErr", LogManager::init_StdErr);

	INIT_UINT_CONSTANT("partId_None", partId_None);
    INIT_UINT_CONSTANT("boneId_None", boneId_None);
    INIT_UINT_CONSTANT("physicsBody_None", physicsBody_None);
    INIT_UINT_CONSTANT("physicsBody_Dynamic", physicsBody_Dynamic);
    INIT_UINT_CONSTANT("physicsBody_Kinematic", physicsBody_Kinematic);
    INIT_UINT_CONSTANT("physicsBody_Static", physicsBody_Static);
    INIT_UINT_CONSTANT("physicsSolver_None", physicsSolver_None);
    INIT_UINT_CONSTANT("physicsSolver_Basic", physicsSolver_Basic);
    INIT_UINT_CONSTANT("physicsSolver_Chipmunk", physicsSolver_Chipmunk);
    INIT_UINT_CONSTANT("physicsForce_None", physicsForce_None);
    INIT_UINT_CONSTANT("collisionShape_None", collisionShape_None);
    INIT_UINT_CONSTANT("collisionShape_Circle", collisionShape_Circle);
    INIT_UINT_CONSTANT("collisionShape_Convex", collisionShape_Convex);
    INIT_UINT_CONSTANT("collision_Begin", collision_Begin);
    INIT_UINT_CONSTANT("collision_Stay", collision_Stay);
    INIT_UINT_CONSTANT("collision_End", collision_End);
    INIT_UINT_CONSTANT("constraint_Pin", constraint_Pin);
    INIT_UINT_CONSTANT("constraint_Slide", constraint_Slide);
    INIT_UINT_CONSTANT("constraint_Pivot", constraint_Pivot);
    INIT_UINT_CONSTANT("constraint_Groove", constraint_Groove);
    INIT_UINT_CONSTANT("constraint_Spring", constraint_Spring);
    INIT_UINT_CONSTANT("constraint_RotarySpring", constraint_RotarySpring);
    INIT_UINT_CONSTANT("constraint_RotaryLimit", constraint_RotaryLimit);
    INIT_UINT_CONSTANT("constraint_Ratchet", constraint_Ratchet);
    INIT_UINT_CONSTANT("constraint_Gear", constraint_Gear);
    INIT_UINT_CONSTANT("constraint_Motor", constraint_Motor);


    INIT_CONSTANT("partSpace_Local", partSpace_Local);
    INIT_CONSTANT("partSpace_Sprite", partSpace_Sprite);
    INIT_CONSTANT("partSpace_World", partSpace_World);
    INIT_CONSTANT("partPlacement_Snap", partPlacement_Snap);
    INIT_CONSTANT("partPlacement_PreserveWorld", partPlacement_PreserveWorld);
    INIT_CONSTANT("rotationDirection_AsSpecified", rotationDirection_AsSpecified);
	INIT_CONSTANT("rotationDirection_Shortest", rotationDirection_Shortest);
	INIT_CONSTANT("rotationDirection_Clockwise", rotationDirection_Clockwise);
	INIT_CONSTANT("rotationDirection_CounterClockwise", rotationDirection_CounterClockwise);

	INIT_CONSTANT("animate_StartToEnd", Sprite::animate_StartToEnd);
	INIT_CONSTANT("animate_EndToStart", Sprite::animate_EndToStart);
	INIT_CONSTANT("animate_Unidirectional", Sprite::animate_Unidirectional);
	INIT_CONSTANT("animate_Bidirectional", Sprite::animate_Bidirectional);
	INIT_CONSTANT("animate_NoLooping", Sprite::animate_NoLooping);
	INIT_CONSTANT("animate_Looping", Sprite::animate_Looping);
		
	INIT_CONSTANT("start_FromFirstFrame", Sprite::start_FromFirstFrame);
	INIT_CONSTANT("start_FromLastFrame", Sprite::start_FromLastFrame);
		
	INIT_CONSTANT("all_Frames", Sprite::all_Frames);

	INIT_CONSTANT("action_CollideSprite", Sprite::action_CollideSprite);
	INIT_CONSTANT("action_CollideWall", Sprite::action_CollideWall);
	INIT_CONSTANT("action_Offscreen", Sprite::action_Offscreen);
	INIT_CONSTANT("action_Onscreen", Sprite::action_Onscreen);
	INIT_CONSTANT("action_ExitLayer", Sprite::action_ExitLayer);
	INIT_CONSTANT("action_AnimationLoop", Sprite::action_AnimationLoop);
	INIT_CONSTANT("action_AnimationEnd", Sprite::action_AnimationEnd);
	INIT_CONSTANT("action_FadeComplete", Sprite::action_FadeComplete);
	INIT_CONSTANT("action_FadeInComplete", Sprite::action_FadeInComplete);
	INIT_CONSTANT("action_FadeOutComplete", Sprite::action_FadeOutComplete);
	INIT_CONSTANT("action_JointBreak", Sprite::action_JointBreak);
    INIT_CONSTANT("action_BodyBreak", Sprite::action_BodyBreak);
    INIT_CONSTANT("physicsBreak_Force", physicsBreak_Force);
    INIT_CONSTANT("physicsBreak_AngularSpeed", physicsBreak_AngularSpeed);
	INIT_CONSTANT("action_AnimationBlendComplete", Sprite::action_AnimationBlendComplete);
    INIT_CONSTANT("action_AnimationPhysicsRecoveryComplete", Sprite::action_AnimationPhysicsRecoveryComplete);
    %#ifdef PDG_SPRITER_SUPPORT
    INIT_CONSTANT("animationPhysics_Kinematic", animationPhysics_Kinematic);
    INIT_CONSTANT("animationPhysics_Dynamic", animationPhysics_Dynamic);
    INIT_CONSTANT("animationPhysics_Driven", animationPhysics_Driven);
    INIT_CONSTANT("animationPhysics_Mixed", animationPhysics_Mixed);
    %#endif
	
	INIT_CONSTANT("touch_MouseEnter", Sprite::touch_MouseEnter);
	INIT_CONSTANT("touch_MouseLeave", Sprite::touch_MouseLeave);
	INIT_CONSTANT("touch_MouseDown", Sprite::touch_MouseDown);
	INIT_CONSTANT("touch_MouseUp", Sprite::touch_MouseUp);
	INIT_CONSTANT("touch_MouseClick", Sprite::touch_MouseClick);

	INIT_CONSTANT("collide_None", Sprite::collide_None);
	INIT_CONSTANT("collide_Point", Sprite::collide_Point);
	INIT_CONSTANT("collide_BoundingBox", Sprite::collide_BoundingBox);
	INIT_CONSTANT("collide_CollisionRadius", Sprite::collide_CollisionRadius);
	INIT_CONSTANT("collide_AlphaChannel", Sprite::collide_AlphaChannel);
	INIT_CONSTANT("collide_SpriterCollisionBox", Sprite::collide_SpriterCollisionBox);
	INIT_CONSTANT("collide_Last", Sprite::collide_Last);

%#ifdef PDG_SPRITER_SUPPORT
	INIT_CONSTANT("animationSpace_Local", animationSpace_Local);
	INIT_CONSTANT("animationSpace_Rig", animationSpace_Rig);
	INIT_CONSTANT("animationSpace_World", animationSpace_World);
	INIT_CONSTANT("animationDebug_None", animationDebug_None);
	INIT_CONSTANT("animationDebug_Bones", animationDebug_Bones);
	INIT_CONSTANT("animationDebug_Sockets", animationDebug_Sockets);
	INIT_CONSTANT("animationDebug_Boxes", animationDebug_Boxes);
	INIT_CONSTANT("animationDebug_All", animationDebug_All);
	INIT_CONSTANT("animationBinding_Image", animationBinding_Image);
	INIT_CONSTANT("animationBinding_Point", animationBinding_Point);
	INIT_CONSTANT("animationBinding_Box", animationBinding_Box);
	INIT_CONSTANT("animationVariable_Float", animationVariable_Float);
	INIT_CONSTANT("animationVariable_Int", animationVariable_Int);
	INIT_CONSTANT("animationVariable_String", animationVariable_String);
	INIT_CONSTANT("animationStage_PreConstraint", animationStage_PreConstraint);
	INIT_CONSTANT("animationStage_Constraint", animationStage_Constraint);
	INIT_CONSTANT("animationStage_PostConstraint", animationStage_PostConstraint);
	INIT_CONSTANT("animationSource_Clip", animationSource_Clip);
	INIT_CONSTANT("animationSource_Reference", animationSource_Reference);
	INIT_CONSTANT("animationSource_Procedural", animationSource_Procedural);
	INIT_CONSTANT("animationBody_Dynamic", animationBody_Dynamic);
	INIT_CONSTANT("animationBody_Kinematic", animationBody_Kinematic);
	INIT_CONSTANT("animationRoot_Fixed", animationRoot_Fixed);
	INIT_CONSTANT("animationRoot_Follow", animationRoot_Follow);
	INIT_CONSTANT("animationDraw_BeforeAll", animationDraw_BeforeAll);
	INIT_CONSTANT("animationDraw_AfterAll", animationDraw_AfterAll);
	INIT_CONSTANT("animationDraw_BeforeSlot", animationDraw_BeforeSlot);
	INIT_CONSTANT("animationDraw_AfterSlot", animationDraw_AfterSlot);
	INIT_CONSTANT("animationDraw_ReplaceSlot", animationDraw_ReplaceSlot);
	INIT_CONSTANT("animationStroke_PortPixels", animationStroke_PortPixels);
	INIT_CONSTANT("animationStroke_Local", animationStroke_Local);
	INIT_CONSTANT("animationIK_NoStretch", animationIK_NoStretch);
	INIT_CONSTANT("animationIK_Stretch", animationIK_Stretch);
%#endif

	INIT_CONSTANT("action_ErasePort", SpriteLayer::action_ErasePort);
	INIT_CONSTANT("action_PreDrawLayer", SpriteLayer::action_PreDrawLayer);
	INIT_CONSTANT("action_PostDrawLayer", SpriteLayer::action_PostDrawLayer);
	INIT_CONSTANT("action_DrawPortComplete", SpriteLayer::action_DrawPortComplete);
	INIT_CONSTANT("action_AnimationStart", SpriteLayer::action_AnimationStart);
	INIT_CONSTANT("action_PreAnimateLayer", SpriteLayer::action_PreAnimateLayer);
	INIT_CONSTANT("action_PostAnimateLayer", SpriteLayer::action_PostAnimateLayer);
	INIT_CONSTANT("action_AnimationComplete", SpriteLayer::action_AnimationComplete);
	INIT_CONSTANT("action_LayerFadeInComplete", SpriteLayer::action_FadeInComplete);
	INIT_CONSTANT("action_LayerFadeOutComplete", SpriteLayer::action_FadeOutComplete);

	INIT_CONSTANT("facing_North", TileLayer::facing_North);
	INIT_CONSTANT("facing_East", TileLayer::facing_East);
	INIT_CONSTANT("facing_South", TileLayer::facing_South);
	INIT_CONSTANT("facing_West", TileLayer::facing_West);
	INIT_CONSTANT("facing_Ignore", TileLayer::facing_Ignore);
	INIT_CONSTANT("flipped_None", TileLayer::flipped_None);
	INIT_CONSTANT("flipped_Horizontal", TileLayer::flipped_Horizontal);
	INIT_CONSTANT("flipped_Vertical", TileLayer::flipped_Vertical);
	INIT_CONSTANT("flipped_Both", TileLayer::flipped_Both);
	INIT_CONSTANT("flipped_Ignore", TileLayer::flipped_Ignore);

	INIT_BOOL_CONSTANT("timer_OneShot", timer_OneShot);
	INIT_BOOL_CONSTANT("timer_Repeating", timer_Repeating);
	// timer_Never is declared as 0xffffffff, but timer APIs expose it through
	// the signed ms_time type. Keep the JavaScript constant consistent with
	// the -1 returned by those APIs on 64-bit Apple platforms.
	INIT_CONSTANT("timer_Never", (int32) timer_Never);

	// setup easing list, leave out custom easings since
	// we will register those constants when the easing function is
	// defined
	INIT_CONSTANT("linearTween", EasingFuncRef::linearTween);
	INIT_CONSTANT("easeInQuad", EasingFuncRef::easeInQuad);
	INIT_CONSTANT("easeOutQuad", EasingFuncRef::easeOutQuad);
	INIT_CONSTANT("easeInOutQuad", EasingFuncRef::easeInOutQuad);
	INIT_CONSTANT("easeInCubic", EasingFuncRef::easeInCubic);
	INIT_CONSTANT("easeOutCubic", EasingFuncRef::easeOutCubic);
	INIT_CONSTANT("easeInOutCubic", EasingFuncRef::easeInOutCubic);
	INIT_CONSTANT("easeInQuart", EasingFuncRef::easeInQuart);
	INIT_CONSTANT("easeOutQuart", EasingFuncRef::easeOutQuart);
	INIT_CONSTANT("easeInOutCubic", EasingFuncRef::easeInOutCubic);
	INIT_CONSTANT("easeInQuint", EasingFuncRef::easeInQuint);
	INIT_CONSTANT("easeOutQuint", EasingFuncRef::easeOutQuint);
	INIT_CONSTANT("easeInOutQuint", EasingFuncRef::easeInOutQuint);
	INIT_CONSTANT("easeInSine", EasingFuncRef::easeInSine);
	INIT_CONSTANT("easeOutSine", EasingFuncRef::easeOutSine);
	INIT_CONSTANT("easeInOutSine", EasingFuncRef::easeInOutSine);
	INIT_CONSTANT("easeInExpo", EasingFuncRef::easeInExpo);
	INIT_CONSTANT("easeOutExpo", EasingFuncRef::easeOutExpo);
	INIT_CONSTANT("easeInOutExpo", EasingFuncRef::easeInOutExpo);
	INIT_CONSTANT("easeInCirc", EasingFuncRef::easeInCirc);
	INIT_CONSTANT("easeOutCirc", EasingFuncRef::easeOutCirc);
	INIT_CONSTANT("easeInOutCirc", EasingFuncRef::easeInOutCirc);
	INIT_CONSTANT("easeInBounce", EasingFuncRef::easeInBounce);
	INIT_CONSTANT("easeOutBounce", EasingFuncRef::easeOutBounce);
	INIT_CONSTANT("easeInOutBounce", EasingFuncRef::easeInOutBounce);
	INIT_CONSTANT("easeInBack", EasingFuncRef::easeInBack);
	INIT_CONSTANT("easeOutBack", EasingFuncRef::easeOutBack);
	INIT_CONSTANT("easeInOutBack", EasingFuncRef::easeInOutBack);

	INIT_CONSTANT("ser_Positions", ser_Positions);
	INIT_CONSTANT("ser_ZOrder", ser_ZOrder);
	INIT_CONSTANT("ser_Sizes", ser_Sizes);
	INIT_CONSTANT("ser_Animations", ser_Animations);
	INIT_CONSTANT("ser_Motion", ser_Motion);
	INIT_CONSTANT("ser_Forces", ser_Forces);
	INIT_CONSTANT("ser_Physics", ser_Physics);
	INIT_CONSTANT("ser_LayerDraw", ser_LayerDraw);
	INIT_CONSTANT("ser_ImageRefs", ser_ImageRefs);
	INIT_CONSTANT("ser_SCMLRefs", ser_SCMLRefs);
	INIT_CONSTANT("ser_HelperRefs", ser_HelperRefs);
	INIT_CONSTANT("ser_HelperObjs", ser_HelperObjs);
	INIT_CONSTANT("ser_InitialData", ser_InitialData);
	INIT_CONSTANT("ser_Micro", ser_Micro);
	INIT_CONSTANT("ser_Update", ser_Update);
	INIT_CONSTANT("ser_Full", ser_Full);
    INIT_CONSTANT("serialization_Complete", serialization_Complete);
    INIT_CONSTANT("serialization_ExternalReferences", serialization_ExternalReferences);

	INIT_CONSTANT("spline_Hermite", 1);
	INIT_CONSTANT("spline_Cardinal", 2);
	INIT_CONSTANT("spline_UniformB", 3);
	INIT_CONSTANT("spline_CubicBezier", 4);
	INIT_CONSTANT("spline_TCB", 5);
	INIT_CONSTANT("spline_NaturalCubic", 6);

}


void CreateSingletons() {
	// this creation order matches the behavior of the native pdg framework app
	FileManager_getScriptSingletonInstance();

	LogManager_getSingletonInstance();
	ConfigManager_getSingletonInstance();
	ResourceManager_getSingletonInstance();
	EventManager_getSingletonInstance();
	TimerManager_getSingletonInstance();
  %#ifndef PDG_NO_GUI
	GraphicsManager_getSingletonInstance();
  %#endif
  %#ifndef PDG_NO_SOUND
	SoundManager_getSingletonInstance();
  %#endif
  %#ifndef PDG_NO_NETWORK
	NetworkManager::getSingletonInstance();
  %#endif
}

} // end pdg namespace

// this is called from pdg::main_run()
extern "C" void pdg_LibContainerDoIdle() {
	
	// give JavaScriptCore some time to garbage collect
    JSGarbageCollect(pdg::gMainContext);

	// report heap
	// TODO: figure out how to do this under JSC
// 	SCRIPT_DEBUG_ONLY(
// 	if ((sIdleLastHeapReport + 1000) < OS::getMilliseconds()) {
// 		v8::HeapStatistics hs;
// 		v8::V8::GetHeapStatistics(&hs);
// 		long deltaUsed = hs.used_heap_size() - sLastHeapUsed;
// 		sLastHeapUsed = hs.used_heap_size();
// 		if (deltaUsed != 0) {
// 			std::cout << "heap: delta ["<<deltaUsed<<"] used ["<<sLastHeapUsed<<"] total ["<<hs.total_heap_size()
// 				<<"] executable ["<<hs.total_heap_size_executable()
// 				<<"]  limit ["<<hs.heap_size_limit()<<"]\n";
// 			sIdleLastHeapReport = OS::getMilliseconds();
// 		}
// 	}
// 	)
}
