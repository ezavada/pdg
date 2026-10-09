// -----------------------------------------------
// log_manager.cpp
//
// Implementation file for LogManager bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>

namespace pdg {

// ========================================================================================
//MARK: Log Manager
// ========================================================================================

SINGLETON_MANAGER_INITIALIZER_IMPL(LogManager, "lm")
    EXPORT_CLASS_SYMBOLS("LogManager", LogManager,
    	// constant section
		HAS_CONSTANT(LogManager, init_CreateUniqueNewFile)
		HAS_CONSTANT(LogManager, init_OverwriteExisting)
		HAS_CONSTANT(LogManager, init_AppendToExisting)
		HAS_CONSTANT(LogManager, init_StdOut)
		HAS_CONSTANT(LogManager, init_StdErr)
	   ,// property section
		HAS_PROPERTY(LogManager, LogLevel)
	   ,// method section
		HAS_METHOD(LogManager, "initialize", Initialize)
		HAS_METHOD(LogManager, "writeLogEntry", WriteLogEntry)
		HAS_METHOD(LogManager, "binaryDump", BinaryDump)
    );
	END
PROPERTY_IMPL(LogManager, LogLevel, INT32)
METHOD_IMPL(LogManager, Initialize)
	METHOD_SIGNATURE("", undefined, 2, (string inLogNameBase, [number int] initMode = LogManager.init_StdOut)); 
    REQUIRE_ARG_MIN_COUNT(1);
	REQUIRE_STRING_ARG(1, inLogNameBase);
	OPTIONAL_INT32_ARG(2, initMode, pdg::LogManager::init_StdOut);
	self->initialize(inLogNameBase, initMode);
	NO_RETURN;
	END
METHOD_IMPL(LogManager, WriteLogEntry)
	METHOD_SIGNATURE("", undefined, 3, ([number int] level, string category, string message)); 
    REQUIRE_ARG_COUNT(3);
	REQUIRE_INT32_ARG(1, level);
	REQUIRE_STRING_ARG(2, category);
	REQUIRE_STRING_ARG(3, message);
	self->writeLogEntry(level, category, message);
	NO_RETURN;
	END
STATIC_METHOD_IMPL(LogManager, BinaryDump)
	METHOD_SIGNATURE("", string, 3, ({[object ByteArray]|[object MemBlock]} inData, [number int] length = 0, [number int] bytesPerLine = 20));
    REQUIRE_ARG_MIN_COUNT(1);
    OPTIONAL_INT32_ARG(2, length, 0);
    OPTIONAL_INT32_ARG(3, bytesPerLine, 20);
	size_t available = 0;
    if (length < 0 || bytesPerLine <= 0) { THROW_RANGE_ERR("invalid dump length or line width"); RETURN_NULL; }
	const char* inData = 0;
    if (IsUint8Array(ARGV[0])) {
     	size_t bytes = 0;
        const uint8* ptr = nullptr;
        if (!GetUint8ArrayData(ARGV[0], ptr, bytes)) {
            THROW_TYPE_ERR("expected an attached, non-shared Uint8Array"); RETURN_NULL;
        }
        if (bytes > UINT32_MAX) { THROW_RANGE_ERR("byte array exceeds the supported size"); RETURN_NULL; }
		inData = (const char*)ptr;
		available = bytes;
	} else {
        if (!VALUE_IS_MEMBLOCK(ARGV[0])) { THROW_TYPE_ERR("expected Uint8Array or MemBlock"); RETURN_NULL; }
    	REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
    	inData = memBlock->ptr;
        available = memBlock->bytes;
    }
    size_t count = length == 0 ? available : static_cast<size_t>(length);
    if (count > available || count > (INT32_MAX - 32) / 16 || bytesPerLine > (INT32_MAX - 32) / 16) {
        THROW_RANGE_ERR("binaryDump range exceeds available or supported data"); RETURN_NULL;
    }
    int dataSize = static_cast<int>(count);
    int outBufSize = (4 * dataSize) + (6 * dataSize/bytesPerLine) + (4 * bytesPerLine) + 32;
    char* outBuf = new char[outBufSize];
    OS::binaryDump(outBuf, outBufSize, inData, dataSize, bytesPerLine);
	VALUE dumpStrVal = STR2VAL(outBuf);
    delete[] outBuf;
	RETURN( dumpStrVal );
	END

log& main_getDebugLog();  // defined in main-{platform}.cpp

CPP_SINGLETON_CONSTRUCTOR_IMPL_CUSTOM(LogManager)
    LogManager *theLogMgr = LogManager::getSingletonInstance();
	pdg::log& debugLog = main_getDebugLog();
	debugLog.setLogManager(theLogMgr);
	return theLogMgr;
	END


} // namespace pdg
// @pdg-class {"name":"LogManager","native_binding":{"browser":{"generate":true,"base":null}}}

// Binary dump input needs a native byte-span adapter.
// @pdg-member {"name":"LogManager.binaryDump","native_binding":{"browser":{"generate":false}}}
