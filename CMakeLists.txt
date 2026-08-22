CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(PDG VERSION 1.0.0 LANGUAGES C CXX)

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
ENDIF()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type if not specified
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE DEBUG)
ENDIF()

OPTION(USE_CHIPMUNK "Build with Chipmunk Physics library" ON)
OPTION(USE_GLFW_MAC "Build with GLFW library on Mac OS X" ON)
OPTION(USE_SPRITER "Build with support for Spriter animations" ON)
OPTION(CAN_BUILD_INTERFACES "Support rebuilding JavaScript Interfaces" OFF)
OPTION(CAN_BUILD_JSC_INTERFACES "Support rebuilding JavaScriptCore Interfaces" OFF)
OPTION(PDG_HEADLESS "Build without GUI/graphics support" OFF)

IF(WIN32 AND CAN_BUILD_INTERFACES)
	IF(NOT BCPP_EXECUTABLE)
		SET(BCPP_EXECUTABLE "${CMAKE_SOURCE_DIR}/build/win32/bcpp/Release/bcpp.exe" CACHE FILEPATH "bcpp pretty-printer (built by configure.ps1)")
	ENDIF()
ENDIF()

IF(PDG_HEADLESS)
	MESSAGE(STATUS "PDG headless mode enabled: GUI/OpenGL/GLFW code will be excluded.")
ELSE()
	FIND_PACKAGE(OpenGL REQUIRED)
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
    SET(BUILD_SUBDIR "darwin")
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
    SET(BUILD_SUBDIR "win32")
    SET(PLATFORM_SUBDIR "win32")
ENDIF(WIN32)

IF(NOT MACOSX AND NOT WIN32)
    SET(BUILD_SUBDIR "linux")
    SET(PLATFORM_SUBDIR "unix")
ENDIF()

IF(NOT MACOSX AND NOT WIN32)
    FIND_LIBRARY(
        PDG_SYSTEM_JPEG_LIBRARY
        NAMES jpeg libjpeg.so.8 jpeg.so.8
        PATHS /usr/lib /usr/lib64 /usr/lib/x86_64-linux-gnu /lib /lib64 /lib/x86_64-linux-gnu
    )
    IF(PDG_SYSTEM_JPEG_LIBRARY)
        MESSAGE(STATUS "Using system JPEG library: ${PDG_SYSTEM_JPEG_LIBRARY}")
    ELSE()
        SET(PDG_SYSTEM_JPEG_LIBRARY jpeg)
        MESSAGE(STATUS "Falling back to linker search for JPEG library: ${PDG_SYSTEM_JPEG_LIBRARY}")
    ENDIF()
ENDIF()

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
        SET_PROPERTY(TARGET pdg-app-framework-tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
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
