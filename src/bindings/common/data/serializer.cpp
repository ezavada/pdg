// -----------------------------------------------
// serializer.cpp
//
// Implementation file for Serializer bindings
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
//MARK: Serializer
// ========================================================================================

BINDING_INITIALIZER_IMPL(Serializer)
    EXPORT_CLASS_SYMBOLS("Serializer", Serializer, , ,
    	// method section
	  %#ifndef PDG_NO_64BIT CR
		HAS_METHOD(Serializer, "serialize_8", Serialize_8)   // no 64 bit int in Script
		HAS_METHOD(Serializer, "serialize_8u", Serialize_8u)
		HAS_METHOD(Serializer, "sizeof_8", Sizeof_8)
		HAS_METHOD(Serializer, "sizeof_8u", Sizeof_8u)
	  %#endif CR
		HAS_METHOD(Serializer, "serialize_d", Serialize_d)
		HAS_METHOD(Serializer, "serialize_f", Serialize_f)
		HAS_METHOD(Serializer, "serialize_4", Serialize_4)
		HAS_METHOD(Serializer, "serialize_4u", Serialize_4u)
		HAS_METHOD(Serializer, "serialize_3u", Serialize_3u)
		HAS_METHOD(Serializer, "serialize_2", Serialize_2)
		HAS_METHOD(Serializer, "serialize_2u", Serialize_2u)
		HAS_METHOD(Serializer, "serialize_1", Serialize_1)
		HAS_METHOD(Serializer, "serialize_1u", Serialize_1u)
		HAS_METHOD(Serializer, "serialize_bool", Serialize_bool)
		HAS_METHOD(Serializer, "serialize_uint", Serialize_uint)
 		HAS_METHOD(Serializer, "serialize_color", Serialize_color)
 		HAS_METHOD(Serializer, "serialize_offset", Serialize_offset)
 		HAS_METHOD(Serializer, "serialize_point", Serialize_point)
 		HAS_METHOD(Serializer, "serialize_vector", Serialize_vector)
 		HAS_METHOD(Serializer, "serialize_rect", Serialize_rect)
 		HAS_METHOD(Serializer, "serialize_rotr", Serialize_rotr)
 		HAS_METHOD(Serializer, "serialize_quad", Serialize_quad)
		HAS_METHOD(Serializer, "serialize_str", Serialize_str)
		HAS_METHOD(Serializer, "serialize_mem", Serialize_mem)
		HAS_METHOD(Serializer, "serialize_obj", Serialize_obj)
		HAS_METHOD(Serializer, "serialize_ref", Serialize_ref)
//		HAS_METHOD(Serializer, "serializedSize", SerializedSize)
		HAS_METHOD(Serializer, "sizeof_d", Sizeof_d)
		HAS_METHOD(Serializer, "sizeof_f", Sizeof_f)
		HAS_METHOD(Serializer, "sizeof_4", Sizeof_4)
		HAS_METHOD(Serializer, "sizeof_4u", Sizeof_4u)
		HAS_METHOD(Serializer, "sizeof_3u", Sizeof_3u)
		HAS_METHOD(Serializer, "sizeof_2", Sizeof_2)
		HAS_METHOD(Serializer, "sizeof_2u", Sizeof_2u)
		HAS_METHOD(Serializer, "sizeof_1", Sizeof_1)
		HAS_METHOD(Serializer, "sizeof_1u", Sizeof_1u)
		HAS_METHOD(Serializer, "sizeof_bool", Sizeof_bool)
		HAS_METHOD(Serializer, "sizeof_uint", Sizeof_uint)
 		HAS_METHOD(Serializer, "sizeof_color", Sizeof_color)
 		HAS_METHOD(Serializer, "sizeof_offset", Sizeof_offset)
 		HAS_METHOD(Serializer, "sizeof_point", Sizeof_point)
 		HAS_METHOD(Serializer, "sizeof_vector", Sizeof_vector)
 		HAS_METHOD(Serializer, "sizeof_rect", Sizeof_rect)
 		HAS_METHOD(Serializer, "sizeof_rotr", Sizeof_rotr)
 		HAS_METHOD(Serializer, "sizeof_quad", Sizeof_quad)
		HAS_METHOD(Serializer, "sizeof_str", Sizeof_str)
		HAS_METHOD(Serializer, "sizeof_mem", Sizeof_mem)
		HAS_METHOD(Serializer, "sizeof_obj", Sizeof_obj)
		HAS_METHOD(Serializer, "sizeof_ref", Sizeof_ref)
		HAS_METHOD(Serializer, "getDataSize", GetDataSize)
		HAS_METHOD(Serializer, "getDataPtr", GetDataPtr)
    );
	END
METHOD_IMPL(Serializer, Serialize_d)
	METHOD_SIGNATURE("", undefined, 1, (number val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, val);
	self->serialize_d(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_f)
	METHOD_SIGNATURE("", undefined, 1, (number val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, val);
	self->serialize_f(val);
	NO_RETURN;
	END
%#ifndef PDG_NO_64BIT
METHOD_IMPL(Serializer, Serialize_8)
	METHOD_SIGNATURE("", undefined, 1, (number val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, val);
	self->serialize_8(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_8u)
	METHOD_SIGNATURE("", undefined, 1, (number val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_NUMBER_ARG(1, val);
	self->serialize_8u(val);
	NO_RETURN;
	END
%#endif
METHOD_IMPL(Serializer, Serialize_4)
	METHOD_SIGNATURE("", undefined, 1, ([number int] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG_RANGE(1, val);
	self->serialize_4(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_4u)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_UINT32_ARG_RANGE(1, val);
	self->serialize_4u(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_3u)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_UINT24_ARG(1, val);
	self->serialize_3u(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_2)
	METHOD_SIGNATURE("", undefined, 1, ([number int] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT16_ARG(1, val);
	self->serialize_2(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_2u)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_UINT16_ARG(1, val);
	self->serialize_2u(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_1)
	METHOD_SIGNATURE("", undefined, 1, ([number int] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT8_ARG(1, val);
	self->serialize_1(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_1u)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_UINT8_ARG(1, val);
	self->serialize_1u(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_bool)
	METHOD_SIGNATURE("", undefined, 1, (boolean val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_BOOL_ARG(1, val);
	self->serialize_bool(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_uint)
	METHOD_SIGNATURE("", undefined, 1, ([number uint] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_UINT32_ARG(1, val);
	self->serialize_uint(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_color)
	METHOD_SIGNATURE("", undefined, 1, ([object Color] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_COLOR_ARG(1, val);
	self->serialize_color(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_offset)
	METHOD_SIGNATURE("", undefined, 1, ([object Offset] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_OFFSET_ARG(1, val);
	self->serialize_offset(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_point)
	METHOD_SIGNATURE("", undefined, 1, ([object Point] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_POINT_ARG(1, val);
	self->serialize_point(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_vector)
	METHOD_SIGNATURE("", undefined, 1, ([object Vector] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_VECTOR_ARG(1, val);
	self->serialize_vector(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_rect)
	METHOD_SIGNATURE("", undefined, 1, ([object Rect] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_RECT_ARG(1, r);
	self->serialize_rect(r);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_rotr)
	METHOD_SIGNATURE("", undefined, 1, ([object RotatedRect] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_ROTATED_RECT_ARG(1, val);
	self->serialize_rotr(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_quad)
	METHOD_SIGNATURE("", undefined, 1, ([object Quad] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_QUAD_ARG(1, val);
	self->serialize_quad(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_str)
	METHOD_SIGNATURE("", undefined, 1, (string str));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_STRING_ARG(1, str);
	self->serialize_str(str);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_mem)
	METHOD_SIGNATURE("", undefined, 1, ({[string Binary]|[object MemBlock]} mem));
    REQUIRE_ARG_COUNT(1);
    bool isStr = VALUE_IS_STRING(ARGV[0]);
    if (!isStr && !VALUE_IS_OBJECT(ARGV[0])) {
    	THROW_TYPE_ERR("argument 1 (mem) must be either a binary string or an object of type MemBlock");
    }
    if (isStr) {
    	size_t bytes = 0;
    	uint8* ptr = (uint8*) DecodeBinary(ARGV[0], &bytes);
		self->serialize_mem(ptr, bytes);
	} else {
    	REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
    	self->serialize_mem(memBlock->ptr, memBlock->bytes);
    }
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_ref)
	METHOD_SIGNATURE("", undefined, 1, (object obj));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_OBJECT_ARG(1, obj);
    self->serialize_ref< OBJECT_REF >(&obj);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, GetDataSize)
	METHOD_SIGNATURE("", number, 0, ());
    REQUIRE_ARG_COUNT(0);
 	uint32 dataSize = self->getDataSize();
	RETURN_UINT32(dataSize);
	END
METHOD_IMPL(Serializer, GetDataPtr)
	METHOD_SIGNATURE("", [object MemBlock], 0, ());
    REQUIRE_ARG_COUNT(0);
    // mem block doesn't own this memory, it belongs to the Serializer
 	MemBlock* memBlock = new MemBlock((char*)self->getDataPtr(), self->getDataSize(), false);
	RETURN_CPP_OBJECT(memBlock, MemBlock);
	END
SERIALIZER_SIZE_OF_METHOD_IMPL(1)
SERIALIZER_SIZE_OF_METHOD_IMPL(1u)
SERIALIZER_SIZE_OF_METHOD_IMPL(2)
SERIALIZER_SIZE_OF_METHOD_IMPL(2u)
SERIALIZER_SIZE_OF_METHOD_IMPL(3u)
SERIALIZER_SIZE_OF_METHOD_IMPL(4)
SERIALIZER_SIZE_OF_METHOD_IMPL(4u)
%#ifndef PDG_NO_64BIT
SERIALIZER_SIZE_OF_METHOD_IMPL(8)
SERIALIZER_SIZE_OF_METHOD_IMPL(8u)
%#endif
SERIALIZER_SIZE_OF_METHOD_IMPL(f)
SERIALIZER_SIZE_OF_METHOD_IMPL(d)
SERIALIZER_SIZE_OF_METHOD_IMPL(uint)
SERIALIZER_SIZE_OF_METHOD_IMPL(str)
SERIALIZER_SIZE_OF_METHOD_IMPL(bool)
SERIALIZER_SIZE_OF_METHOD_IMPL(point)
SERIALIZER_SIZE_OF_METHOD_IMPL(offset)
SERIALIZER_SIZE_OF_METHOD_IMPL(vector)
SERIALIZER_SIZE_OF_METHOD_IMPL(rect)
SERIALIZER_SIZE_OF_METHOD_IMPL(rotr)
SERIALIZER_SIZE_OF_METHOD_IMPL(quad)
SERIALIZER_SIZE_OF_METHOD_IMPL(color)
CUSTOM_SERIALIZER_SIZE_OF_METHOD_IMPL(ref,
    size_t n = self->sizeof_ref< OBJECT_REF >(&val) )
METHOD_IMPL(Serializer, Sizeof_obj)
    REQUIRE_ARG_COUNT(1);
    if (VALUE_IS_NULL(ARGV[0])) {
        size_t n = 3; // 3 bytes for null object tag
        RETURN_UNSIGNED(n);
    }
    REQUIRE_CPP_OBJECT_OR_SUBCLASS_ARG(1, val, ISerializable);
    size_t n = self->sizeof_obj(val);
    RETURN_UNSIGNED(n);
    END

METHOD_IMPL(Serializer, Sizeof_mem)
	METHOD_SIGNATURE("", [number uint], 1, ({[string Binary]|[object MemBlock]} mem));
    REQUIRE_ARG_COUNT(1);
    bool isStr = VALUE_IS_STRING(ARGV[0]);
    if (!isStr && !VALUE_IS_OBJECT(ARGV[0])) {
    	THROW_TYPE_ERR("argument 1 (mem) must be either a binary string or an object of type MemBlock");
    }
    size_t n = 0;
    if (isStr) {
    	size_t bytes = 0;
    	uint8* ptr = (uint8*) DecodeBinary(ARGV[0], &bytes);
		n = self->sizeof_mem(ptr, bytes);
	} else {
    	REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
    	n = self->sizeof_mem(memBlock->ptr, memBlock->bytes);
    }
	RETURN_UNSIGNED(n);
	END

//SERIALIZER_SIZE_OF_METHOD_IMPL(mem)

CLEANUP_IMPL(Serializer)

CPP_MANAGED_CONSTRUCTOR_IMPL(Serializer)
	return new Serializer();
	END


} // pdg namespace

