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
        HAS_METHOD(Serializer, "setResourceMode", SetResourceMode)
        HAS_METHOD(Serializer, "getResourceMode", GetResourceMode)
    	// method section
		HAS_METHOD(Serializer, "serialize_8", Serialize_8)   // no 64 bit int in Script
		HAS_METHOD(Serializer, "serialize_8u", Serialize_8u)
		HAS_METHOD(Serializer, "sizeof_8", Sizeof_8)
		HAS_METHOD(Serializer, "sizeof_8u", Sizeof_8u)
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
METHOD_IMPL(Serializer, SetResourceMode)
    METHOD_SIGNATURE("Choose embedded image resources or permit external resource references.", [this], 1, ([number int] mode));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_INT32_ARG_RANGE(1, mode);
    try { self->setResourceMode(mode); RETURN_THIS; }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
    END
METHOD_IMPL(Serializer, GetResourceMode)
    METHOD_SIGNATURE("get this stream's resource policy", [number int], 0, ());
    REQUIRE_ARG_COUNT(0);
    RETURN_INT32(self->getResourceMode());
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
	METHOD_SIGNATURE("", undefined, 1, ({[object Color const&] val|string colorName|number rgba}));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_COLOR_ARG(1, val);
	self->serialize_color(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_offset)
	METHOD_SIGNATURE("", undefined, 1, ([object Offset const&] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_OFFSET_ARG(1, val);
	self->serialize_offset(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_point)
	METHOD_SIGNATURE("", undefined, 1, ([object Point const&] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_POINT_ARG(1, val);
	self->serialize_point(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_vector)
	METHOD_SIGNATURE("", undefined, 1, ([object Vector const&] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_VECTOR_ARG(1, val);
	self->serialize_vector(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_rect)
	METHOD_SIGNATURE("", undefined, 1, ([object Rect const&] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_RECT_ARG(1, r);
	self->serialize_rect(r);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_rotr)
	METHOD_SIGNATURE("", undefined, 1, ([object RotatedRect const&] val));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_ROTATED_RECT_ARG(1, val);
	self->serialize_rotr(val);
	NO_RETURN;
	END
METHOD_IMPL(Serializer, Serialize_quad)
	METHOD_SIGNATURE("", undefined, 1, ([object Quad const&] val));
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
	METHOD_SIGNATURE("", undefined, 1, ({[object ByteArray]|[object MemBlock]} mem));
    REQUIRE_ARG_COUNT(1);
    bool isBytes = IsUint8Array(ARGV[0]);
    if (!isBytes && !VALUE_IS_MEMBLOCK(ARGV[0])) {
        THROW_TYPE_ERR("argument 1 (mem) must be either a Uint8Array or an object of type MemBlock"); RETURN_NULL;
    }
    if (isBytes) {
    	size_t bytes = 0;
        const uint8* ptr = nullptr;
        if (!GetUint8ArrayData(ARGV[0], ptr, bytes)) {
            THROW_TYPE_ERR("expected an attached, non-shared Uint8Array"); RETURN_NULL;
        }
        if (bytes > UINT32_MAX) { THROW_RANGE_ERR("byte array exceeds the supported size"); RETURN_NULL; }
		self->serialize_mem(ptr, bytes);
	} else {
        if (!VALUE_IS_MEMBLOCK(ARGV[0])) { THROW_TYPE_ERR("expected Uint8Array or MemBlock"); RETURN_NULL; }
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
SERIALIZER_SIZE_OF_METHOD_IMPL(8)
SERIALIZER_SIZE_OF_METHOD_IMPL(8u)
SERIALIZER_SIZE_OF_METHOD_IMPL(f)
SERIALIZER_SIZE_OF_METHOD_IMPL(d)
SERIALIZER_SIZE_OF_METHOD_IMPL(uint)
SERIALIZER_SIZE_OF_METHOD_IMPL(str)
SERIALIZER_SIZE_OF_METHOD_IMPL(bool)
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(point, [object Point const&], size_t n = self->sizeof_point(val))
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(offset, [object Offset const&], size_t n = self->sizeof_offset(val))
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(vector, [object Vector const&], size_t n = self->sizeof_vector(val))
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(rect, [object Rect const&], size_t n = self->sizeof_rect(val))
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(rotr, [object RotatedRect const&], size_t n = self->sizeof_rotr(val))
SERIALIZER_SIZE_OF_SIGNATURE_IMPL(quad, [object Quad const&], size_t n = self->sizeof_quad(val))
METHOD_IMPL(Serializer, Sizeof_color)
    METHOD_SIGNATURE("Calculate the number of bytes needed to serialize the value.", [number uint], 1, ({[object Color const&] val|string colorName|number rgba}));
    REQUIRE_ARG_COUNT(1);
    REQUIRE_COLOR_ARG(1, val);
    size_t n = self->sizeof_color(val);
    RETURN_UNSIGNED(n);
    END
CUSTOM_SERIALIZER_SIZE_OF_METHOD_IMPL(ref,
    size_t n = self->sizeof_ref< OBJECT_REF >(&val) )
METHOD_IMPL(Serializer, Sizeof_obj)
    METHOD_SIGNATURE("get the number of bytes used to serialize the given object, including any objects that it serializes", [number uint], 1, ([object ISerializable const*] obj));
    REQUIRE_ARG_COUNT(1);
    if (VALUE_IS_NULL(ARGV[0])) {
        size_t n = 3; // 3 bytes for null object tag
        RETURN_UNSIGNED(n);
    }
  %#ifdef PDG_USING_JAVASCRIPT_CORE
    ISerializable* val = JSC_GetSerializable(ctx, ARGV[0]);
    if (!val) { THROW_TYPE_ERR("Expected a serializable object"); }
  %#else
    ISerializable* val = V8_GetSerializable(isolate, ARGV[0]);
    if (!val) { THROW_TYPE_ERR("Expected a serializable object"); }
  %#endif
    size_t n;
    try { n = self->sizeof_obj(val); }
    catch (const std::exception& error) { THROW_ERR(error.what()); }
  %#ifdef PDG_USING_JAVASCRIPT_CORE
    if (RestorePendingScriptException(exception)) {
        return JSValueMakeUndefined(ctx);
    }
  %#endif
    RETURN_UNSIGNED(n);
    END

METHOD_IMPL(Serializer, Sizeof_mem)
	METHOD_SIGNATURE("", [number uint], 1, ({[object ByteArray]|[object MemBlock]} mem));
    REQUIRE_ARG_COUNT(1);
    bool isBytes = IsUint8Array(ARGV[0]);
    if (!isBytes && !VALUE_IS_MEMBLOCK(ARGV[0])) {
        THROW_TYPE_ERR("argument 1 (mem) must be either a Uint8Array or an object of type MemBlock"); RETURN_NULL;
    }
    size_t n = 0;
    if (isBytes) {
    	size_t bytes = 0;
        const uint8* ptr = nullptr;
        if (!GetUint8ArrayData(ARGV[0], ptr, bytes)) {
            THROW_TYPE_ERR("expected an attached, non-shared Uint8Array"); RETURN_NULL;
        }
        if (bytes > UINT32_MAX) { THROW_RANGE_ERR("byte array exceeds the supported size"); RETURN_NULL; }
		n = self->sizeof_mem(ptr, bytes);
	} else {
        if (!VALUE_IS_MEMBLOCK(ARGV[0])) { THROW_TYPE_ERR("expected Uint8Array or MemBlock"); RETURN_NULL; }
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

/* @pdg-member
{
  "name": "Serializer.Serializer",
  "type": "constructor",
  "params": [],
  "returns": "object Serializer",
  "brief": "Create a Serializer instance."
}
*/

/* @pdg-contract
{
  "name": "Serializer.serialize_ref",
  "value": {
    "params": {
      "obj": {
        "builtin": "object"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "Serializer.sizeof_ref",
  "value": {
    "params": {
      "val": {
        "builtin": "object"
      }
    }
  }
}
*/

// @pdg-member {"name":"Serializer.serialize_mem","native_binding":{"adapter":"Serializer.serialize_mem","browser":{"wrapper":{}},"binding_name":"_serialize_mem"}}

// @pdg-member {"name":"Serializer.sizeof_mem","native_binding":{"adapter":"Serializer.sizeof_mem","browser":{"wrapper":{}},"binding_name":"_sizeof_mem"}}

// @pdg-member {"name":"Serializer.serialize_color","native_binding":{"allow_raw_pointers":true}}


// @pdg-member {"name":"Serializer.sizeof_color","native_binding":{"allow_raw_pointers":true}}


// @pdg-member {"name":"Serializer.sizeof_obj","native_binding":{"allow_raw_pointers":true}}


// @pdg-class {"name":"Serializer","native_binding":{"browser":{"base":null,"generate":true,"constructors":[{"types":[]}]}}}

// Native 64-bit values and script reference serialization need custom conversion.

// @pdg-member {"name":"Serializer.serialize_8u","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"Serializer.serialize_ref","native_binding":{"browser":{"generate":false}}}













// @pdg-member {"name":"Serializer.sizeof_ref","native_binding":{"browser":{"generate":false}}}

// 64-bit inputs still require number-to-native conversion in the browser.
// @pdg-member {"name":"Serializer.sizeof_8","native_binding":{"browser":{"generate":false}}}
// @pdg-member {"name":"Serializer.sizeof_8u","native_binding":{"browser":{"generate":false}}}
