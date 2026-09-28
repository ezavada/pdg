// -----------------------------------------------
//  serializer.cpp
//
// Written by Ed Zavada, 2010-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------


#include "pdg_project.h"

#include "pdg/sys/serializer.h"
#include "pdg/sys/serializable.h"
#include "pdg/sys/os.h"

#include "serializer-impl.h"

#include <limits.h>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <map>
#include <fstream>
#include <format>
#include <limits>

#define SERIALIZER_MALLOC_BLOCK_SIZE 1024

namespace pdg {

bool ISerializer::s_DebugMode = false;


//! Serialize an 8 byte (64 bit) value into a buffer
void   Serializer::serialize_8u(uint64 val) {
	ensureSpace(8);
	SERIALIZE_START;
	mData[mOffset++] = (val >> 56) & 0xff;
	mData[mOffset++] = (val >> 48) & 0xff;
	mData[mOffset++] = (val >> 40) & 0xff;
	mData[mOffset++] = (val >> 32) & 0xff;
	mData[mOffset++] = (val >> 24) & 0xff;
	mData[mOffset++] = (val >> 16) & 0xff;
	mData[mOffset++] = (val >> 8) & 0xff;
	mData[mOffset++] = val & 0xff;
	SERIALIZED("8u  ", 8);
}

//! Serialize a 4 byte (32 bit) value into a buffer
void   Serializer::serialize_4u(uint32 val) {
	ensureSpace(4);
	SERIALIZE_START;
	mData[mOffset++] = (val >> 24) & 0xff;
	mData[mOffset++] = (val >> 16) & 0xff;
	mData[mOffset++] = (val >> 8) & 0xff;
	mData[mOffset++] = val & 0xff;
	SERIALIZED("4u  ", 4);
}

//! Serialize a 3 byte (24 bit) value into a buffer
void   Serializer::serialize_3u(uint32 val) {
	ensureSpace(3);
	SERIALIZE_START;
	mData[mOffset++] = (val >> 16) & 0xff;
	mData[mOffset++] = (val >> 8) & 0xff;
	mData[mOffset++] = val & 0xff;
	SERIALIZED("3u  ", 3);
}

//! Serialize a 2 byte (16 bit) value into a buffer
void   Serializer::serialize_2u(uint16 val) {
	ensureSpace(2);
	SERIALIZE_START;
	mData[mOffset++] = (val >> 8) & 0xff;
	mData[mOffset++] = val & 0xff;
	SERIALIZED("2u  ", 2);
}

//! Serialize an 1 byte (8 bit) value into a buffer
void   Serializer::serialize_1u(uint8 val) {
	ensureSpace(1);
	SERIALIZE_START;
	mData[mOffset++] = val & 0xff;
	SERIALIZED("1u  ", 1);
}

void   
Serializer::serialize_bool(bool val) {
	ensureSpace(1);
	SERIALIZE_START;
	if (mLastBoolOffset) {
		uint8 byte = mData[*mLastBoolOffset];
		if (val) {
			byte |= (1 << mBoolBitOffset);
			mData[*mLastBoolOffset] = byte;
		}
		mBoolBitOffset++;
		if (mBoolBitOffset > 7) {
			// filled the current byte with bits, reset
			mLastBoolOffset.reset();
			mBoolBitOffset = 0;
		}
		SERIALIZED("bool", 0);
	} else {
		mLastBoolOffset = mOffset;
		mBoolBitOffset = 1;
		mData[mOffset++] = val ? 1 : 0;
		SERIALIZED("bool", 1);
	}
	// if we actually serialized a boolean, reset the size count
	// to where we actually are, so interspersed calls to 
	// sizeof_bool(bool) and serialize_bool() will work
	mBoolSizeCount = mBoolBitOffset;
}

// write a length value into the buffer in a way that is more efficient for shorter lengths
void 
Serializer::serialize_uint(uint32 len) {
	ensureSpace(5);
	SERIALIZE_START;
	if (len < tag_smallestLenTag) {
		serialize_1u(len);
	} else if (len <= USHRT_MAX) {
		// large value
		serialize_1u(tag_longLen);
		serialize_2u(len);
	} else {
		// very large value
		serialize_1u(tag_veryLongLen);
		serialize_4u(len);
	}
	SERIALIZED("uint", 0);
}

void
Serializer::serialize_mem(const void* mem, uint32 memLen) {
	ensureSpace(static_cast<size_t>(memLen) + 8);
	SERIALIZE_START;
    if (mUsingTags) {
    	serialize_3u(tag_mem);
    }
	if (mem == 0) memLen = 0;
	serialize_uint(memLen);
	if (memLen > 0) {
        ensureSpace(memLen);
		std::memcpy(mData.data() + mOffset, mem, memLen);
		mOffset += memLen;
	}
	SERIALIZED("mem ", 0);
}

void   
Serializer::serialize_str(const char* str) { 
	size_t len = std::strlen(str);
	ensureSpace(len + 8);
	SERIALIZE_START;
    if (mUsingTags) {
    	serialize_3u(tag_string);
    }
	serialize_uint((uint32)len);
	if (len > 0) {
		ensureSpace(len);
		std::memcpy(mData.data() + mOffset, str, len);
		mOffset += len;
	}
	SERIALIZED("str ", 0);
}

void
Serializer::serialize_obj(const ISerializable* obj) {
	SERIALIZE_START;
	if (obj == 0) {
		serialize_3u(tag_objectNil);
		SERIALIZED("obj ", 0);
		return;
	}
	// see if the object has already been serialized
	for (uint16 i = 0; i < mSerializedInstances.size(); i++) {
		if (mSerializedInstances[i] == obj) {
			serialize_3u(tag_objectRef);
			serialize_uint(i);
			SERIALIZED("obj ", 0);
			return;
		}
	}
	// wasn't previously serialized, do so now
	mSerializeObjDepth++;
	mSerializedInstances.push_back(obj);
//	obj->addRef();
	serialize_3u(tag_object);
	uint32 tag = obj->getMyClassTag();
	serialize_4u(tag);
    if (mUsingTags) {
    	serialize_2u(mSerializedInstances.size());
    }
    // Size this record against the objects actually emitted so far. Descendant
    // size calls share this temporary set, so repeated assets count only once.
    auto priorSized = std::move(mSerializedSizeInstances);
    mSerializedSizeInstances = mSerializedInstances;
    // A prior preflight may have advanced the sizing cursor. The envelope
    // describes the bytes we will emit from the current packed-boolean position.
    mBoolSizeCount = mBoolBitOffset;
    uint32 objLen;
    try { objLen = obj->getSerializedSize(this); }
    catch (...) {
        mBoolSizeCount = mBoolBitOffset;
        mSerializedSizeInstances = std::move(priorSized);
        throw;
    }
    mBoolSizeCount = mBoolBitOffset;
    mSerializedSizeInstances = std::move(priorSized);
	serialize_uint(objLen);
	SERIALIZED("obj ", 0);   // stop here so we can see the object being serialized
	obj->serialize(this);
	mSerializeObjDepth--;
}

void   
Serializer::serialize_color(const Color& c) {
	SERIALIZE_START;
	uint8 v = c.alpha * 255.0f;
	bool hasAlpha = (v != 255);
	serialize_bool(hasAlpha);
	if (hasAlpha) {
		serialize_1u(v);
	}
	serialize_1u(c.red * 255.0f);
	serialize_1u(c.green * 255.0f);
	serialize_1u(c.blue * 255.0f);	
	SERIALIZED("colr", 0);
}

void   
Serializer::serialize_offset(const Offset& o) {
	SERIALIZE_START;
	bool nonZero = ((o.x != 0.0f) || (o.y != 0.0f));
	serialize_bool(nonZero);
	if (nonZero) {
		double ix;
		double fx = modf(o.x, &ix);
		double iy;
		double fy = modf(o.y, &iy);
		bool xIsInt = ( (ix >= 0.0f) && (ix <= 65535.0f) && ((int)(fabs(fx)*1000.0f) == 0) );
		bool yIsInt = ( (iy >= 0.0f) && (iy <= 65535.0f) && ((int)(fabs(fy)*1000.0f) == 0) );
		serialize_bool(xIsInt);
		serialize_bool(yIsInt);	
		if (xIsInt) {
			serialize_uint((uint32)ix);
		} else {
			serialize_f(o.x);
		}
		if (yIsInt) {
			serialize_uint((uint32)iy);
		} else {
			serialize_f(o.y);
		}
	}
	SERIALIZED("off ", 0);
}

void   
Serializer::serialize_rect(const Rect& r) {
	SERIALIZE_START;
	serialize_point(r.leftTop());
	serialize_offset(Offset(r.width(), r.height()));
	SERIALIZED("rect", 0);
}

void   
Serializer::serialize_rotr(const RotatedRect& rr) {
	SERIALIZE_START;
	serialize_rect(rr);
	serialize_f(rr.radians);
	serialize_offset(rr.centerOffset);
	SERIALIZED("rotr", 0);
}

void   
Serializer::serialize_quad(const Quad& q) {
	SERIALIZE_START;
	serialize_point(q.points[0]);
	serialize_point(q.points[1]);
	serialize_point(q.points[2]);
	serialize_point(q.points[3]);
	SERIALIZED("quad", 0);
}

void   
Serializer::serialize_ptr(const void* ptr) {
	SERIALIZE_START;
    uint32 uniqueId = 0;
    for(ObjectRegistryT::iterator i = gObjectRegistry.begin(); i != gObjectRegistry.end(); i++) {
        if (i->second == ptr) {
            uniqueId = i->first;
            break;
        }
    }
    if (!uniqueId) {
        throw unknown_object("");
    }
    if (mUsingTags) {
    	serialize_3u(tag_pointerRef);
    }
	serialize_uint(uniqueId);
	SERIALIZED("ptr ", 0);
}

uint32
Serializer::sizeof_mem(const void* mem, uint32 memLen) const {
	uint32 lenOfLen = sizeof_uint(memLen);
    if (!mData.empty() ? mUsingTags : mSendTags) {
    	lenOfLen += 3;
    }
	if (mem == 0) memLen = 0;
	return lenOfLen + memLen;
}

//! How many bytes are used to serialize a particular boolean value
uint32 
Serializer::sizeof_bool(bool val) const {
	uint32 result = (mBoolSizeCount == 0) ? 1 : 0;
	mBoolSizeCount++;
	if (mBoolSizeCount > 7) {
		mBoolSizeCount = 0;
	}
	return result;
}

// how many bytes are used to serialize this particular length value
uint32 
Serializer::sizeof_uint(uint32 num) const {
	if (num < tag_smallestLenTag) {
		return 1;
	} else if (num <= USHRT_MAX) {
		return 3;
	} else {
		return 5;
	}
}

//! How many bytes are used to serialize a particular pdg::Color value
uint32 
Serializer::sizeof_color(const Color& c) const {
	uint8 v = c.alpha * 255.f;
	bool hasAlpha = (v != 255);
	uint32 result = sizeof_bool(hasAlpha) + (hasAlpha ? + 4 : 3);
	return result;
}

//! How many bytes are used to serialize a particular pdg::Offset, Point or Vector value
uint32 
Serializer::sizeof_offset(const Offset& o) const {
	bool nonZero = ((o.x != 0.0f) || (o.y != 0.0f));
	uint32 result = sizeof_bool(nonZero);
	if (nonZero) {
		double ix;
		double fx = modf(o.x, &ix);
		double iy;
		double fy = modf(o.y, &iy);
		bool xIsInt = ( (ix >= 0.0f) && (ix <= 65535.0f) && ((int)(fabs(fx)*1000.0f) == 0) );
		bool yIsInt = ( (iy >= 0.0f) && (iy <= 65535.0f) && ((int)(fabs(fy)*1000.0f) == 0) );
		result += sizeof_bool(xIsInt);
		result += sizeof_bool(yIsInt);	
		if (xIsInt) {
			result += sizeof_uint(ix);
		} else {
			result += 4;
		}
		if (yIsInt) {
			result += sizeof_uint(iy);
		} else {
			result += 4;
		}
	}
	return result;
}

//! How many bytes are used to serialize a particular pdg::Rect or RotatedRect value
uint32 
Serializer::sizeof_rect(const Rect& r) const {
	uint32 result = sizeof_point(r.leftTop());
	result += sizeof_offset(Offset(r.width(), r.height()));
	return result;
}

//! How many bytes are used to serialize a particular pdg::Rect or RotatedRect value
uint32 
Serializer::sizeof_rotr(const RotatedRect& rr) const {
	uint32 result = sizeof_rect(rr);
	result += sizeof_offset(rr.centerOffset) + 4;
	return result;
}

//! How many bytes are used to serialize a particular pdg::Quad value
uint32 
Serializer::sizeof_quad(const Quad& q) const {
	uint32 result = sizeof_point(q.points[0]);
	result += sizeof_point(q.points[1]);
	result += sizeof_point(q.points[2]);
	result += sizeof_point(q.points[3]);
	return result;
}


uint32 
Serializer::sizeof_str(const char* str) const { 
	size_t strLen = std::strlen(str);
	size_t lenOfLen = sizeof_uint((uint32)strLen);
    if (!mData.empty() ? mUsingTags : mSendTags) {
    	lenOfLen += 3;
    }
	return (uint32)(lenOfLen + strLen);
}

uint32
Serializer::sizeof_obj(const ISerializable* obj) {
	if (obj == 0) {
		return 3;
	}
    for (size_t i = 0; i < mSerializedSizeInstances.size(); ++i) {
        if (mSerializedSizeInstances[i] == obj) return sizeof_uint(static_cast<uint32>(i)) + 3;
    }
    mSerializedSizeInstances.push_back(obj);
	uint32 objLen = obj->getSerializedSize(this);
	uint32 len = 3 + 4;
    if (!mData.empty() ? mUsingTags : mSendTags) {
    	len += 2;
    }
	len += sizeof_uint(objLen);
	len += objLen;
    return len;
}


//! How many bytes are used to serialize a particular Object Reference value
uint32 
Serializer::sizeof_ptr(const void* ptr) const {
    uint32 uniqueId = 0;
    for(ObjectRegistryT::iterator i = gObjectRegistry.begin(); i != gObjectRegistry.end(); i++) {
        if (i->second == ptr) {
            uniqueId = i->first;
            break;
        }
    }
    if (!uniqueId) {
        throw unknown_object("");
    }
    uint32 result = 0;
    if (!mData.empty() ? mUsingTags : mSendTags) {
    	result += 3;
    }
	result += sizeof_uint(uniqueId);
	return result;
}


void Serializer::ensureSpace(size_t bytes) {
    constexpr size_t blockSize = SERIALIZER_MALLOC_BLOCK_SIZE;
    const size_t maximum = mData.max_size();
    if (bytes > maximum - mOffset) throw std::length_error("Serialized buffer is too large");
    const size_t needed = mOffset + bytes;
    if (needed <= mData.size()) return;
    const bool firstAllocation = mData.empty();
    const size_t padding = blockSize - needed % blockSize;
    const size_t allocated = padding <= maximum - needed ? needed + padding : needed;
    mData.resize(allocated);
    if (firstAllocation && mSendTags) {
        mUsingTags = true;
        serialize_3u(tag_pdgTaggedStream);
    }
}

// --------------------------------------------
// constructors
// --------------------------------------------

ISerializer& Serializer::setResourceMode(int mode) {
    if (mode == getResourceMode()) return *this;
    if (mode != getResourceMode() && getDataSize() != 0)
        throw std::logic_error("Set the resource mode before serializing objects");
    ISerializer::setResourceMode(mode);
    mSerializedSizeInstances.clear();
    mBoolSizeCount = 0;
    return *this;
}

Serializer::Serializer()
 : mSerializeObjDepth(0), mBoolBitOffset(0), mBoolSizeCount(0), mUsingTags(false)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mSerializerScriptObj);
#endif
}

Serializer::~Serializer() {
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupSerializerScriptObject(mSerializerScriptObj);
#endif
}

char* Serializer::statusDump(int hiliteBytes) {
    thread_local std::string result;
    const size_t blockStart = mMark / 16 * 16;
    const size_t blockLen = std::min<size_t>(20, mData.size() - blockStart);
    char dump[1000] = {};
    OS::binaryDump(dump, sizeof(dump), reinterpret_cast<const char*>((mData.empty() ? nullptr : mData.data() + blockStart)),
        static_cast<int>(blockLen), 20, static_cast<int>(mMark - blockStart), hiliteBytes);
    result = std::format("@{:05}/{:05}:  {:04X} | {}", mOffset, mData.size(), blockStart, dump);
    return result.data();
}

void Serializer::startMark() {
    if (mData.empty()) ensureSpace(1);
    mMark = mOffset;
}

int Serializer::bytesFromMark() {
    return static_cast<int>(mOffset - mMark);
}

} // end namespace pdg
