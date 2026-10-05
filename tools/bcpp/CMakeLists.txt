# Build the bcpp C++ beautifier (used by gen-script-interface.*) from the
# sources shipped in tools/bcpp.tar.zip (extracted by the platform configure script).
cmake_minimum_required(VERSION 3.16)
project(bcpp LANGUAGES CXX)

if(NOT DEFINED BCPP_SOURCE_DIR OR NOT EXISTS "${BCPP_SOURCE_DIR}")
	message(FATAL_ERROR "BCPP_SOURCE_DIR must point to the extracted bcpp .../code directory (run configure.ps1 -EnableInterfaceTools or ./configure --enable-interface-tools).")
endif()

file(GLOB BCPP_SOURCES "${BCPP_SOURCE_DIR}/*.cpp")
if(NOT BCPP_SOURCES)
	message(FATAL_ERROR "No .cpp sources under ${BCPP_SOURCE_DIR}")
endif()

# Patch a build-local copy so re-extracting the bundled archive keeps the fix.
# Both brace-merging paths allocate newLen bytes for the code and state buffers.
set(BCPP_MAIN_SOURCE "${BCPP_SOURCE_DIR}/bcpp.cpp")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${BCPP_MAIN_SOURCE}")
file(READ "${BCPP_MAIN_SOURCE}" BCPP_MAIN_CONTENT)
foreach(buffer pNewCode pNewState)
	string(REPLACE "sprintf (${buffer}," "snprintf (${buffer}, newLen,"
		BCPP_MAIN_CONTENT "${BCPP_MAIN_CONTENT}")
endforeach()
set(BCPP_PATCHED_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/bcpp.cpp")
file(GENERATE OUTPUT "${BCPP_PATCHED_SOURCE}" CONTENT "${BCPP_MAIN_CONTENT}")
list(REMOVE_ITEM BCPP_SOURCES "${BCPP_MAIN_SOURCE}")
list(APPEND BCPP_SOURCES "${BCPP_PATCHED_SOURCE}")

add_executable(bcpp ${BCPP_SOURCES})
target_include_directories(bcpp PRIVATE "${BCPP_SOURCE_DIR}")
set_property(TARGET bcpp PROPERTY CXX_STANDARD 20)
set_property(TARGET bcpp PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	target_compile_definitions(bcpp PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
