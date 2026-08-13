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

add_executable(bcpp ${BCPP_SOURCES})
set_property(TARGET bcpp PROPERTY CXX_STANDARD 17)
set_property(TARGET bcpp PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	target_compile_definitions(bcpp PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
