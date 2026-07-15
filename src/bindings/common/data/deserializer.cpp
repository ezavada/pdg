 // -----------------------------------------------
// deserializer.cpp
//
// Implementation file for Deserializer bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    


// ========================================================================================
//MARK: Deserializer
// ========================================================================================

DECLARE_SYMBOL(getSerializedSize);
DECLARE_SYMBOL(serialize);
DECLARE_SYMBOL(deserialize);
DECLARE_SYMBOL(getMyClassTag);
DECLARE_SYMBOL(constructor);


BINDING_INITIALIZER_IMPL(Deserializer) 
    EXPORT_CLASS_SYMBOLS("Deserializer", Deserializer, , ,
    	// method section
	  %#ifndef PDG_NO_64BIT CR
		HAS_METHOD(Deserializer, "deserialize_8", Deserialize_8)
		HAS_METHOD(Deserializer, "deserialize_8u", Deserialize_8u)
	  %#endif CR
		HAS_METHOD(Deserializer, "deserialize_d", Deserialize_d)
		HAS_METHOD(Deserializer, "deserialize_f", Deserialize_f)
		HAS_METHOD(Deserializer, "deserialize_4", Deserialize_4)
		HAS_METHOD(Deserializer, "deserialize_4u", Deserialize_4u)
		HAS_METHOD(Deserializer, "deserialize_3u", Deserialize_3u)
		HAS_METHOD(Deserializer, "deserialize_2", Deserialize_2)
		HAS_METHOD(Deserializer, "deserialize_2u", Deserialize_2u)
		HAS_METHOD(Deserializer, "deserialize_1", Deserialize_1)
		HAS_METHOD(Deserializer, "deserialize_1u", Deserialize_1u)
		HAS_METHOD(Deserializer, "deserialize_bool", Deserialize_bool)
		HAS_METHOD(Deserializer, "deserialize_uint", Deserialize_uint)
 		HAS_METHOD(Deserializer, "deserialize_color", Deserialize_color)
 		HAS_METHOD(Deserializer, "deserialize_offset", Deserialize_offset)
 		HAS_METHOD(Deserializer, "deserialize_point", Deserialize_point)
 		HAS_METHOD(Deserializer, "deserialize_vector", Deserialize_vector)
 		HAS_METHOD(Deserializer, "deserialize_rect", Deserialize_rect)
 		HAS_METHOD(Deserializer, "deserialize_rotr", Deserialize_rotr)
 		HAS_METHOD(Deserializer, "deserialize_quad", Deserialize_quad)
		HAS_METHOD(Deserializer, "deserialize_str", Deserialize_str)
	//	HAS_METHOD(Deserializer, "deserialize_strGetLen", Deserialize_strGetLen)  // returns utf-8 length, useless in JavaScript
		HAS_METHOD(Deserializer, "deserialize_mem", Deserialize_mem)
		HAS_METHOD(Deserializer, "deserialize_memGetLen", Deserialize_memGetLen)
		HAS_METHOD(Deserializer, "deserialize_obj", Deserialize_obj)
		HAS_METHOD(Deserializer, "deserialize_ref", Deserialize_ref)
		HAS_METHOD(Deserializer, "setDataPtr", SetDataPtr)
    );
	END
METHOD_IMPL(Deserializer, Deserialize_d)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
    try {
		double val = self->deserialize_d();
		RETURN_NUMBER(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_f)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		float val = self->deserialize_f();
		RETURN_NUMBER(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
%#ifndef PDG_NO_64BIT
METHOD_IMPL(Deserializer, Deserialize_8)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		int64 val = self->deserialize_8();
		RETURN_NUMBER(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_8u)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint64 val = self->deserialize_8u();
		RETURN_NUMBER(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
%#endif
METHOD_IMPL(Deserializer, Deserialize_4)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		int32 val = self->deserialize_4();
		RETURN_INT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_4u)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint32 val = self->deserialize_4u();
		RETURN_UINT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_3u)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint32 val = self->deserialize_3u();
		RETURN_UINT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_2)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		int16 val = self->deserialize_2();
		RETURN_INT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_2u)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint16 val = self->deserialize_2u();
		RETURN_UINT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_1)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		int8 val = self->deserialize_1();
		RETURN_INT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_1u)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint8 val = self->deserialize_1u();
		RETURN_UINT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_bool)
	METHOD_SIGNATURE("", boolean, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		bool val = self->deserialize_bool();
		RETURN_BOOL(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_uint)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint32 val = self->deserialize_uint();
		RETURN_UINT32(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_color)
	METHOD_SIGNATURE("", [object Color], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Color val = self->deserialize_color();
		RETURN_COLOR(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_offset)
	METHOD_SIGNATURE("", [object Offset], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Offset val = self->deserialize_offset();
		RETURN_OFFSET(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_point)
	METHOD_SIGNATURE("", [object Point], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Point val = self->deserialize_point();
		RETURN_POINT(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_vector)
	METHOD_SIGNATURE("", [object Vector], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Vector val = self->deserialize_vector();
		RETURN_VECTOR(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_rect)
	METHOD_SIGNATURE("", [object Rect], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Rect val = self->deserialize_rect();
		RETURN_RECT(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_rotr)
	METHOD_SIGNATURE("", [object RotatedRect], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		RotatedRect val = self->deserialize_rotr();
		RETURN_ROTATED_RECT(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_quad)
	METHOD_SIGNATURE("", [object Quad], 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		Quad val = self->deserialize_quad();
		RETURN_QUAD(val);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_str)
	METHOD_SIGNATURE("", string, 0, ());
    REQUIRE_ARG_COUNT(0);
    try {
		std::string mystr;
		self->deserialize_string(mystr);
		RETURN_STRING(mystr.c_str());
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_strGetLen)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
	try {
		uint32 len = self->deserialize_strGetLen();
		RETURN_UINT32(len);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_mem)
	METHOD_SIGNATURE("", [object MemBlock], 0, ());
    REQUIRE_ARG_COUNT(0);
    size_t len, len2;
    try {
		len = self->deserialize_memGetLen();
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	}
    char* mem = (char*) std::malloc(len);
    try {
		len2 = self->deserialize_mem(mem, len);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	}
    if (len2 != len) {
    	THROW_ERR("Deserializer internal error, deserialized memory length mismatch " << len 
    		<< " (" << (void*)len << ") != " << len2 << " (" << (void*)len2 << ")");
    }
    // MemBlock owns this memory and will free it when destroyed
 	MemBlock* memBlock = new MemBlock(mem, len, true);
	RETURN_CPP_OBJECT(memBlock, MemBlock);
	END
METHOD_IMPL(Deserializer, Deserialize_memGetLen)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
    try {
		uint32 len = self->deserialize_memGetLen();
		RETURN_UINT32(len);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, SetDataPtr)
	METHOD_SIGNATURE("", undefined, 1, ({[string Binary]|[object MemBlock]} data));
    REQUIRE_ARG_COUNT(1);
    if (!VALUE_IS_STRING(ARGV[0]) && !VALUE_IS_OBJECT(ARGV[0])) {
    	THROW_TYPE_ERR("argument 1 (mem) must be either a binary string or an object of type MemBlock");
    }
    if (VALUE_IS_STRING(ARGV[0])) {
    	size_t bytes = 0;
    	uint8* ptr = (uint8*) DecodeBinary(ARGV[0], &bytes);
		self->setDataPtr(ptr, bytes);
	} else {
    	REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
    	self->setDataPtr(memBlock->ptr, memBlock->bytes);
    }
	NO_RETURN;
	END
METHOD_IMPL(Deserializer, Deserialize_obj)
	OBJECT_SAVE(self->mDeserializerScriptObj, THIS);
	METHOD_SIGNATURE("", [object ISerializable], 1, ());
    REQUIRE_ARG_COUNT(0);
  	try {
		ISerializable* obj = self->deserialize_obj();
		DEBUG_DUMP_SCRIPT_OBJECT(obj->mISerializableScriptObj, ISerializable)
		RETURN_CPP_OBJECT(obj, ISerializable);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	} catch(sync_error& e) {
    	THROW_ERR(e.what());
	} catch(unknown_object& e) {
    	THROW_ERR(e.what());
	}
	END
METHOD_IMPL(Deserializer, Deserialize_ref)
	METHOD_SIGNATURE("", object, 0, ());
    REQUIRE_ARG_COUNT(0);
    try {
		OBJECT_REF obj = *self->deserialize_ref< OBJECT_REF >();
        RETURN_OBJECT(obj);
	} catch(out_of_data& e) {
    	THROW_ERR(e.what());
	} catch(bad_tag& e) {
    	THROW_ERR(e.what());
	} catch(unknown_object& e) {
    	THROW_ERR(e.what());
	}
	END


FUNCTION_IMPL(RegisterSerializableClass)
	METHOD_SIGNATURE("", undefined, 1, (function klass));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, constructorFunc);
	VALUE objVal = CALL_CONSTRUCTOR_SAFE(constructorFunc);
	OBJECT obj = VAL2OBJ_SAFE(objVal);
	DEBUG_DUMP_SCRIPT_OBJECT(obj, ISerializable);
	EXTRACT_CPP_OBJECT_OR_SUBCLASS_VALUE(objVal, nativeSerializable, ISerializable);
	uint32 classTag = 0;
	if (OBJECT_HAS_PROPERTY(obj, SYMBOL(getMyClassTag))) {
		VALUE getMyClassTagVal = OBJECT_GET_PROPERTY(obj, SYMBOL(getMyClassTag));
		if (!VALUE_IS_FUNCTION(getMyClassTagVal)) {
			std::ostringstream msg;
			msg << "argument 1: ISerializable subclass " << OBJECT_GET_CLASS_NAME(obj) << " getMyClassTag property is not a function!!";
			THROW_ERR(msg.str().c_str());
			return;
		}
		FUNCTION_REF func = VAL2FUNC(getMyClassTagVal);
		VALUE classTagVal = CALL_SCRIPT(func, obj, 0, 0);
		classTag = VAL2UINT(classTagVal);
	} else if (nativeSerializable) {
		classTag = nativeSerializable->getMyClassTag();
	} else {
		std::ostringstream msg;
        msg << "argument 1: ISerializable subclass " << OBJECT_GET_CLASS_NAME(obj) << " missing getMyClassTag() Function!!";
		THROW_ERR(msg.str().c_str());
		return;
	}
	Deserializer::registerScriptClass(classTag, constructorFunc);
    NO_RETURN;
    END



CLEANUP_IMPL(Deserializer)

CPP_MANAGED_CONSTRUCTOR_IMPL(Deserializer)
	return new Deserializer();
	END


} // pdg namespace

