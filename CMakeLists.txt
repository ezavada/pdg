CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(PDG VERSION 1.2.0 LANGUAGES C CXX)

# Apple's linker resolves archives without repeated entries on the link line.
IF(APPLE)
    FOREACH(policy CMP0156 CMP0179)
        IF(POLICY ${policy})
            CMAKE_POLICY(SET ${policy} NEW)
        ENDIF()
    ENDFOREACH()
ENDIF()

INCLUDE(CTest)

IF(NOT DEFINED PDG_SOURCE_DIR)
	SET(PDG_SOURCE_DIR ${CMAKE_SOURCE_DIR})
ENDIF()

# Set C++ standard to C++20 for V8 compatibility
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
# MSVC: explicitly set /std:c++20 (CMAKE_CXX_STANDARD is not always applied by VS generator)
IF(MSVC)
	ADD_COMPILE_OPTIONS($<$<COMPILE_LANGUAGE:CXX>:/std:c++20>)
	# Node and the Windows PDG libraries use the static runtime. Apply the
	# policy here so targets declared after ADD_SUBDIRECTORY(src) match too.
	SET(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the single-config generator default and expose it through CMakeCache.txt.
IF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
ENDIF()

OPTION(USE_CHIPMUNK "Build with Chipmunk Physics library" ON)
OPTION(USE_GLFW_MAC "Build with GLFW library on Mac OS X" ON)
OPTION(USE_SPRITER "Build with support for Spriter animations" ON)
OPTION(CAN_BUILD_INTERFACES "Support rebuilding JavaScript Interfaces" OFF)
OPTION(CAN_BUILD_JSC_INTERFACES "Support rebuilding JavaScriptCore Interfaces" OFF)
OPTION(PDG_HEADLESS "Build without GUI/graphics support" OFF)

STRING(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" PDG_SYSTEM_PROCESSOR)
IF(PDG_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
    SET(PDG_ARCH "arm64")
ELSEIF(PDG_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|x64)$")
    SET(PDG_ARCH "x86_64")
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8 AND WIN32)
    # Visual Studio generators do not consistently populate
    # CMAKE_SYSTEM_PROCESSOR, but this project currently targets x64 by default.
    SET(PDG_ARCH "x86_64")
ELSE()
    SET(PDG_ARCH "${PDG_SYSTEM_PROCESSOR}")
ENDIF()

IF(WIN32 AND CAN_BUILD_INTERFACES)
	IF(NOT BCPP_EXECUTABLE)
		SET(BCPP_EXECUTABLE "${CMAKE_SOURCE_DIR}/build/win32/${PDG_ARCH}/bcpp/Release/bcpp.exe" CACHE FILEPATH "bcpp pretty-printer (built by configure.ps1)")
	ENDIF()
ENDIF()

IF(PDG_HEADLESS)
	MESSAGE(STATUS "PDG headless mode enabled: GUI/OpenGL/GLFW code will be excluded.")
ELSE()
	FIND_PACKAGE(OpenGL REQUIRED)
	IF(UNIX AND NOT APPLE)
		FIND_LIBRARY(PDG_GLU_LIBRARY NAMES GLU REQUIRED)
		FIND_PACKAGE(Freetype REQUIRED)
		FIND_PACKAGE(Fontconfig REQUIRED)
	ENDIF()
ENDIF()

# Only find Python if we need to build interfaces
IF(CAN_BUILD_INTERFACES)
	# Use modern Python3 finder instead of deprecated PythonInterp
	FIND_PACKAGE(Python3 COMPONENTS Interpreter)
	IF(NOT Python3_FOUND)
		# Fallback to Python if Python3 is not found
		FIND_PACKAGE(Python COMPONENTS Interpreter)
	ENDIF()
	IF(Python3_FOUND)
		SET(PDG_PYTHON3 "${Python3_EXECUTABLE}")
	ELSEIF(Python_FOUND)
		SET(PDG_PYTHON3 "${Python_EXECUTABLE}")
	ELSE()
		SET(PDG_PYTHON3 "python3")
	ENDIF()
ENDIF()

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(MACOSX ON)
ENDIF()

IF (MACOSX)
    SET(BUILD_SUBDIR "darwin/${PDG_ARCH}")
    SET(PLATFORM_SUBDIR "macosx")
    FIND_LIBRARY(COREFOUND CoreFoundation)
    FIND_LIBRARY(AUDIOTOOLBOX AudioToolbox)
    FIND_LIBRARY(IOKIT IOKit)
    IF(NOT PDG_HEADLESS)
        FIND_LIBRARY(APPKIT AppKit)
        FIND_LIBRARY(APPSERVICES ApplicationServices)
    ENDIF()
ENDIF(MACOSX)

IF (WIN32)
    SET(BUILD_SUBDIR "win32/${PDG_ARCH}")
    SET(PLATFORM_SUBDIR "win32")
ENDIF(WIN32)

IF(NOT MACOSX AND NOT WIN32)
    IF(PDG_ARCH STREQUAL "arm64")
        SET(PDG_NODE_OPENSSL_ARCH "linux-aarch64")
    ELSEIF(PDG_ARCH STREQUAL "x86_64")
        SET(PDG_NODE_OPENSSL_ARCH "linux-x86_64")
    ELSE()
        MESSAGE(FATAL_ERROR "Unsupported Linux architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    ENDIF()
    SET(BUILD_SUBDIR "linux/${PDG_ARCH}")
    SET(PLATFORM_SUBDIR "unix")
ENDIF()

IF(NOT MACOSX AND NOT WIN32)
    # Headers and runtime must describe the same libjpeg ABI (62/80/etc.).
    FIND_PACKAGE(JPEG REQUIRED)
    SET(PDG_SYSTEM_JPEG_LIBRARY JPEG::JPEG)
ENDIF()

IF(MACOSX)
    SET(PDG_PLATFORM_NAME "darwin")
ELSEIF(WIN32)
    SET(PDG_PLATFORM_NAME "win32")
ELSE()
    SET(PDG_PLATFORM_NAME "linux")
ENDIF()

# Node and V8 produce architecture-specific static archives. Configure scripts
# point deps/node/out at this location because Node itself fixes that output name.
SET(PDG_NODE_OUT_DIR "${PDG_SOURCE_DIR}/build/${PDG_PLATFORM_NAME}/${PDG_ARCH}/node/out" CACHE PATH
    "Architecture-specific Node.js build output directory")
SET(PDG_NODE_RELEASE_DIR "${PDG_NODE_OUT_DIR}/Release")

ADD_SUBDIRECTORY(src)

IF(BUILD_TESTING AND NOT PDG_HEADLESS)
    ADD_EXECUTABLE(pdg-app-view-utils-tests
        test/cxx/test-view-utils.cpp
    )
    TARGET_INCLUDE_DIRECTORIES(pdg-app-view-utils-tests PRIVATE
        ${PDG_SOURCE_DIR}/src/inc
        ${PDG_SOURCE_DIR}/src/app
        ${PDG_SOURCE_DIR}/deps
    )
    ADD_TEST(NAME pdg-app-view-utils COMMAND pdg-app-view-utils-tests)

    ADD_EXECUTABLE(pdg-app-framework-tests
        test/cxx/test-app-framework.cpp
        src/app/Application.cpp
        src/app/Checkbox.cpp
        src/app/ControlAttributes.cpp
        src/app/Controller.cpp
        src/app/Observer.cpp
        src/app/RadioButton.cpp
        src/app/Scrollbar.cpp
        src/app/View.cpp
    )
    TARGET_COMPILE_DEFINITIONS(pdg-app-framework-tests PRIVATE
        PDG_INTERNAL_LIB=1
        PDG_PROJECT=PDG_PROJECT_C_ONLY_APP
    )
    TARGET_INCLUDE_DIRECTORIES(pdg-app-framework-tests PRIVATE
        ${PDG_SOURCE_DIR}/src/inc
        ${PDG_SOURCE_DIR}/src/sys
        ${PDG_SOURCE_DIR}/src/app
        ${PDG_SOURCE_DIR}/deps
    )
    TARGET_LINK_DIRECTORIES(pdg-app-framework-tests PRIVATE
        ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/glfw/src
        ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src
    )
    TARGET_LINK_LIBRARIES(pdg-app-framework-tests PRIVATE pdg-lib-debug)
    IF(MACOSX)
        TARGET_LINK_LIBRARIES(pdg-app-framework-tests PRIVATE
            "-framework AppKit"
            "-framework CoreGraphics"
            "-framework AudioToolbox"
            "-framework CoreFoundation"
            "-framework Security"
            "-framework OpenGL"
            "-framework GLUT"
            "-framework IOKit"
            ${OPENGL_LIBRARIES}
        )
    ELSEIF(WIN32)
        TARGET_LINK_LIBRARIES(pdg-app-framework-tests PRIVATE
            imm32 psapi winmm user32 strmiids bcrypt advapi32 crypt32 userenv msvcrt
            ${OPENGL_LIBRARIES}
        )
    ELSE()
        TARGET_LINK_LIBRARIES(pdg-app-framework-tests PRIVATE
            ${OPENGL_LIBRARIES} dl pthread
        )
    ENDIF()
    ADD_TEST(NAME pdg-app-framework COMMAND pdg-app-framework-tests)
ENDIF()
