# CMake v4

SET( PDG_SOURCES  
	sys/animated.cpp
	sys/attributes.cpp
	sys/ConvertUTF.c
	sys/collisiondetection.cpp
	sys/color.cpp
	sys/deserializer.cpp
	sys/drawing.cpp
	sys/eventemitter.cpp
	sys/eventmanager.cpp
	sys/font-impl.cpp
	sys/font-fallback.cpp
	sys/graphics-manager.cpp
	sys/graphics-opengl.cpp
	sys/image.cpp
	sys/image-opengl.cpp
	sys/imagecache-opengl.cpp
	sys/imagecache-opengl-v2.cpp
	sys/log.cpp
	sys/opengl-state-cache.cpp
	sys/os.cpp
	sys/pdg-main.cpp
	sys/resource.cpp
	sys/serializer.cpp
	sys/spline.cpp
	sys/polygon.cpp
	sys/port-renderer.cpp
	sys/sprite.cpp
	sys/spritelayer.cpp
	sys/spritemanager.cpp
	sys/textcache-opengl.cpp
	sys/tilelayer.cpp
	sys/timermanager.cpp
	sys/userdata.cpp
)

SET(PDG_HEADLESS_GUI_SOURCES
	sys/font-impl.cpp
	sys/font-fallback.cpp
	sys/graphics-manager.cpp
	sys/graphics-opengl.cpp
	sys/image-opengl.cpp
	sys/imagecache-opengl.cpp
	sys/imagecache-opengl-v2.cpp
	sys/opengl-state-cache.cpp
	sys/port-renderer.cpp
	sys/textcache-opengl.cpp
)

SET(PDG_WITH_GLFW OFF)

IF(PDG_HEADLESS)
	ADD_DEFINITIONS(-DPDG_NO_GUI)
	LIST(REMOVE_ITEM PDG_SOURCES ${PDG_HEADLESS_GUI_SOURCES})
ENDIF()

IF(PDG_HEADLESS AND NOT MACOSX AND NOT WIN32)
	ADD_DEFINITIONS(-DPDG_NO_SOUND)
ENDIF()

SET( PDG_INCLUDE_DIRECTORIES 
	${PDG_SOURCE_DIR}/src/inc 
	${PDG_SOURCE_DIR}/src/sys
)

SET (PDG_JAVASCRIPT_BINDINGS_SOURCES 
	bindings/javascript/memblock.cpp
	bindings/javascript/v8/pdg_v8_support.cpp
	bindings/generated/v8/pdg_script_impl.cpp
	bindings/generated/v8/pdg_interfaces.cpp
	bindings/generated/v8/core/config_manager.cpp
	bindings/generated/v8/core/log_manager.cpp
	bindings/generated/v8/core/event_manager.cpp
	bindings/generated/v8/core/timer_manager.cpp
	bindings/generated/v8/data/file_manager.cpp
	bindings/generated/v8/data/mem_block.cpp
	bindings/generated/v8/data/resource_manager.cpp
	bindings/generated/v8/data/serializer.cpp
	bindings/generated/v8/data/serializable.cpp
	bindings/generated/v8/data/deserializer.cpp
	bindings/generated/v8/graphics/graphics_manager.cpp
	bindings/generated/v8/graphics/image.cpp
	bindings/generated/v8/graphics/port.cpp
	bindings/generated/v8/graphics/spline.cpp
	bindings/generated/v8/graphics/polygon.cpp
	bindings/generated/v8/graphics/drawing.cpp
	bindings/generated/v8/graphics/font.cpp
	bindings/generated/v8/graphics/attributes.cpp
	bindings/generated/v8/animation/animated.cpp
	bindings/generated/v8/animation/sprite.cpp
	bindings/generated/v8/animation/sprite_layer.cpp
	bindings/generated/v8/animation/tile_layer.cpp
	bindings/generated/v8/audio/sound_manager.cpp
	bindings/generated/v8/audio/sound.cpp
	bindings/node/pdg_node.cpp
)

SET(PDG_JAVASCRIPT_PHYSICS_BINDINGS_SOURCES
	bindings/generated/v8/physics/cp_arbiter.cpp
	bindings/generated/v8/physics/cp_constraint.cpp
	bindings/generated/v8/physics/cp_space.cpp
)

IF(USE_CHIPMUNK)
	LIST(APPEND PDG_JAVASCRIPT_BINDINGS_SOURCES ${PDG_JAVASCRIPT_PHYSICS_BINDINGS_SOURCES})
ENDIF()

SET (PDG_JAVASCRIPT_BINDINGS_INCLUDE_DIRECTORIES 
	${PDG_SOURCE_DIR}/src/bindings/javascript
	${PDG_SOURCE_DIR}/src/bindings/javascript/v8
	${PDG_SOURCE_DIR}/src/bindings/generated/v8
	${PDG_SOURCE_DIR}/src/bindings/generated/jsc
	${PDG_SOURCE_DIR}/src/bindings/node
	${PDG_SOURCE_DIR}/deps/node/src
	${PDG_SOURCE_DIR}/deps/node/deps/cares/include
	${PDG_SOURCE_DIR}/deps/node/deps/uv/include
	${PDG_SOURCE_DIR}/deps/node/deps/v8
${PDG_SOURCE_DIR}/deps/node/deps/v8/include
)

SET (PDG_JAVASCRIPT_BINDINGS_LINK_DIRECTORIES 
)

SET (PNG_SOURCES
	${PDG_SOURCE_DIR}/deps/png/png.c
	${PDG_SOURCE_DIR}/deps/png/pngerror.c
	${PDG_SOURCE_DIR}/deps/png/pngget.c
	${PDG_SOURCE_DIR}/deps/png/pngmem.c
	${PDG_SOURCE_DIR}/deps/png/pngpread.c
	${PDG_SOURCE_DIR}/deps/png/pngwrite.c
	${PDG_SOURCE_DIR}/deps/png/pngread.c
	${PDG_SOURCE_DIR}/deps/png/pngrio.c
	${PDG_SOURCE_DIR}/deps/png/pngwio.c
	${PDG_SOURCE_DIR}/deps/png/pngrtran.c
	${PDG_SOURCE_DIR}/deps/png/pngwtran.c
	${PDG_SOURCE_DIR}/deps/png/pngrutil.c
	${PDG_SOURCE_DIR}/deps/png/pngwutil.c
	${PDG_SOURCE_DIR}/deps/png/pngset.c
	${PDG_SOURCE_DIR}/deps/png/pngtrans.c
)

IF( USE_SPRITER )
	# Add SpriterPlusPlus include directories
	INCLUDE_DIRECTORIES(
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/example
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
	
	# Get all SpriterPlusPlus source files
	FILE(GLOB_RECURSE SPRITERPLUSPLUS_SOURCES 
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine/*.cpp
	)
	
	# Add TinyXML2 and PugiXML sources
	SET( SPRITERPLUSPLUS_SOURCES
		${SPRITERPLUSPLUS_SOURCES}
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2/tinyxml2.cpp
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml/pugixml.cpp
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/example/override/tinyxmlspriterfiledocumentwrapper.cpp
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/example/override/tinyxmlspriterfileelementwrapper.cpp
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/example/override/tinyxmlspriterfileattributewrapper.cpp
	)
	
	SET( SPRITER_FILES 
		${SPRITERPLUSPLUS_SOURCES}
		sys/spriter/pdg_file_factory.cpp
		sys/spriter/pdg_object_factory.cpp
		sys/spriter/pdg_image_file.cpp
		sys/spriter/pdg_point_instance_info.cpp
		sys/spriter/pdg_bone_instance_info.cpp
		sys/spriter/pdg_box_instance_info.cpp
		sys/spriter/pdg_spriter_file_document_wrapper.cpp
	)
	ADD_DEFINITIONS ( -DPDG_SPRITER_SUPPORT )
ELSE( USE_SPRITER )
	SET( SPRITER_FILES )
ENDIF( USE_SPRITER )

IF( MACOSX )
	IF(PDG_HEADLESS)
		SET( PLATFORM_FILES 
			sys/macosx/platform-events-macosx.cpp
		)
	ELSEIF( USE_GLFW_MAC ) 
		SET(PDG_WITH_GLFW ON)
		ADD_DEFINITIONS ( -DPDG_USE_GLFW )
		SET( PLATFORM_FILES 
			sys/glfw/platform-graphics-glfw.cpp
			sys/glfw/platform-events-glfw.cpp
			sys/pdg-lib.cpp
		)
	ELSE( USE_GLFW_MAC )
		SET( PLATFORM_FILES 
			sys/macosx/pdg-lib-macosx.mm
			sys/macosx/pdg-opengl-view.mm
			sys/macosx/platform-graphics-macosx.mm
			sys/macosx/platform-events-macosx.cpp
		)
	ENDIF()
	SET( PLATFORM_FILES
		${PLATFORM_FILES}
		sys/unix/os-unix.cpp
		sys/macosx/config-macosx.cpp
		sys/macosx/platform-dirs-macosx.cpp
		sys/macosx/sound-macosx.cpp
		sys/macosx/sound-mgr-macosx.cpp
		sys/macosx/audio_cleanup_manager.cpp
	)
	IF(NOT PDG_HEADLESS)
		LIST(APPEND PLATFORM_FILES
			sys/macosx/graphics-macosx-opengl.cpp
			sys/macosx/internals-macosx.mm
			sys/macosx/platform-image-macosx.mm
		)
		SET( PLATFORM_LIBS
			${APPKIT} ${APPSERVICES} ${COREFOUND} ${AUDIOTOOLBOX} ${IOKIT}
		)
		# Silence OpenGL deprecation warnings on macOS
		ADD_DEFINITIONS ( -DGL_SILENCE_DEPRECATION )
	ELSE()
		SET( PLATFORM_LIBS
			${COREFOUND} ${AUDIOTOOLBOX} ${IOKIT}
		)
	ENDIF()
ENDIF( MACOSX )

IF( WIN32 )
	IF(PDG_HEADLESS)
		SET( PLATFORM_FILES 
			sys/win32/platform-events-win32.cpp
    		sys/pdg-lib.cpp
			sys/win32/config-win32.cpp
			sys/win32/crash-handler-win32.cpp
			sys/win32/os-win32.cpp
			sys/win32/platform-win32.cpp
			sys/win32/sound-directx.cpp
			sys/win32/sound-mgr-directx.cpp
			sys/image-png.cpp
			sys/image-jpeg.cpp
			${PNG_SOURCES}
		)
		ADD_DEFINITIONS ( -DPDG_USE_LIBPNG -DPDG_USE_LIBJPEG )
	ELSE()
		SET(PDG_WITH_GLFW ON)
		SET( PLATFORM_FILES 
			sys/glfw/platform-graphics-glfw.cpp
			sys/glfw/platform-events-glfw.cpp
			sys/win32/graphics-win32-opengl.cpp
    		sys/pdg-lib.cpp
			sys/win32/config-win32.cpp
			sys/win32/crash-handler-win32.cpp
			sys/win32/os-win32.cpp
			sys/win32/platform-win32.cpp
			sys/win32/sound-directx.cpp
			sys/win32/sound-mgr-directx.cpp
			sys/image-png.cpp
			sys/image-jpeg.cpp
			${PNG_SOURCES}
		)
		ADD_DEFINITIONS ( -DPDG_USE_GLFW -DPDG_USE_LIBPNG -DPDG_USE_LIBJPEG )
	ENDIF()
	ADD_DEFINITIONS ( /D "_ITERATOR_DEBUG_LEVEL=0" /D UNICODE /D _UNICODE /D _CRT_SECURE_NO_WARNINGS /wd4244)
	# Suppress SpriterPlusPlus virtual function warnings (Clang-only; MSVC does not use -Wno-*)
	IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		ADD_DEFINITIONS ( -Wno-overloaded-virtual )
	ENDIF()
ELSE( WIN32 )
    ADD_DEFINITIONS ( -DV8_IMMINENT_DEPRECATION_WARNINGS -Wdeprecated-declarations )
ENDIF( WIN32 )

# Add JPEG support for Unix/Linux platforms
IF( NOT MACOSX AND NOT WIN32 )
	SET( PLATFORM_FILES
		sys/pdg-lib.cpp
		sys/unix/os-unix.cpp
		sys/unix/config-unix.cpp
		sys/unix/platform-unix.cpp
		sys/image-png.cpp
		sys/image-jpeg.cpp
		${PNG_SOURCES}
	)
	IF(PDG_HEADLESS)
		LIST(APPEND PLATFORM_FILES sys/glfw/platform-events-glfw.cpp)
		ADD_DEFINITIONS ( -DPDG_USE_LIBPNG -DPDG_USE_LIBJPEG )
	ELSE()
		SET(PDG_WITH_GLFW ON)
		LIST(APPEND PLATFORM_FILES
			sys/glfw/platform-graphics-glfw.cpp
			sys/glfw/platform-events-glfw.cpp
		)
		ADD_DEFINITIONS ( -DPDG_USE_GLFW -DPDG_USE_LIBPNG -DPDG_USE_LIBJPEG )
	ENDIF()
ENDIF( NOT MACOSX AND NOT WIN32 )

# Store link directories for later use with target_link_directories
SET( NODE_LINK_DIRS ${PDG_SOURCE_DIR}/deps/node/out/Release )

IF(PDG_WITH_GLFW)
	IF( MACOSX )
		IF( USE_GLFW_MAC ) 
			SET( GLFW_LINK_DIRS ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/glfw/src )
		ENDIF( USE_GLFW_MAC )
	ELSE( MACOSX )
		SET( GLFW_LINK_DIRS ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/glfw/src )
	ENDIF( MACOSX )
ELSE()
	SET(GLFW_LINK_DIRS)
ENDIF()

IF(PDG_WITH_GLFW)
	SET(PDG_PLATFORM_GLFW_INCLUDE_DIRS ${PDG_SOURCE_DIR}/deps/glfw/include)
ELSE()
	SET(PDG_PLATFORM_GLFW_INCLUDE_DIRS)
ENDIF()

IF( USE_CHIPMUNK )
	SET( CHIPMUNK_LINK_DIRS ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src )
	ADD_DEFINITIONS ( -DPDG_USE_CHIPMUNK_PHYSICS )
ENDIF( USE_CHIPMUNK )

# Add libjpeg-turbo link directories for Windows
IF( WIN32 )
	SET( LIBJPEG_LINK_DIRS ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/libjpeg-turbo )
ENDIF( WIN32 )

SET(PDG_NODE_STATIC_ZLIB_LIB_CANDIDATES
	${PDG_SOURCE_DIR}/deps/node/out/Release/libzlib.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libzlib_adler32_simd.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libzlib_arm_crc32.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libzlib_data_chunk_simd.a
)

SET(PDG_NODE_STATIC_ZLIB_LIBS)
FOREACH(node_zlib_lib ${PDG_NODE_STATIC_ZLIB_LIB_CANDIDATES})
	IF(EXISTS "${node_zlib_lib}")
		LIST(APPEND PDG_NODE_STATIC_ZLIB_LIBS "${node_zlib_lib}")
	ENDIF()
ENDFOREACH()

SET(PDG_NODE_NONWIN_LIB_CANDIDATES
	${PDG_SOURCE_DIR}/deps/node/out/Release/libnode.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libuv.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libuvwasi.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libicui18n.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libicuucx.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libicudata.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libcares.a
	${PDG_NODE_STATIC_ZLIB_LIB_CANDIDATES}
	${PDG_SOURCE_DIR}/deps/node/out/Release/libnghttp2.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libhistogram.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libllhttp.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libopenssl.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libsqlite.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libbrotli.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libzstd.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libncrypto.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libsimdutf.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libsimdjson.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libabseil.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libhighway.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libada.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libcrdtp.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libnbytes.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_zlib.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_base_without_compiler.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_compiler.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_init.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_initializers.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_initializers_slow.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_libbase.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_libplatform.a
	${PDG_SOURCE_DIR}/deps/node/out/Release/libv8_snapshot.a
)

SET(PDG_NODE_NONWIN_LIBS)
FOREACH(node_lib ${PDG_NODE_NONWIN_LIB_CANDIDATES})
	IF(EXISTS "${node_lib}")
		LIST(APPEND PDG_NODE_NONWIN_LIBS "${node_lib}")
	ENDIF()
ENDFOREACH()

# Build minizip static library
set(MINIZIP_SRC
    ${PDG_SOURCE_DIR}/deps/minizip/mz_crypt.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_os.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_buf.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_mem.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_split.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_zip.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_zip_rw.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_zlib.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_pkcrypt.c
    ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_wzaes.c
    ${PDG_SOURCE_DIR}/deps/minizip/compat/ioapi.c
    ${PDG_SOURCE_DIR}/deps/minizip/compat/unzip.c
    ${PDG_SOURCE_DIR}/deps/minizip/compat/zip.c
)

# Add platform-specific crypto and OS implementation
IF( MACOSX )
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_crypt_apple.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_os_posix.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_os_posix.c)
ELSEIF( WIN32 )
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_crypt_winvista.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_os_win32.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_os_win32.c)
ELSE()
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_crypt_openssl.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_strm_os_posix.c)
    list(APPEND MINIZIP_SRC ${PDG_SOURCE_DIR}/deps/minizip/mz_os_posix.c)
ENDIF()

# Build libtess2 for polygon tessellation
set(LIBTESS2_SRC
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/bucketalloc.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/dict.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/geom.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/mesh.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/priorityq.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/sweep.c
    ${PDG_SOURCE_DIR}/deps/libtess2/Source/tess.c
)

# Create minizip static library
add_library(minizip_static STATIC ${MINIZIP_SRC})

# Set include directories for minizip
target_include_directories(minizip_static PRIVATE
    ${PDG_SOURCE_DIR}/deps/minizip
    ${PDG_SOURCE_DIR}/deps/minizip/compat
    ${PDG_SOURCE_DIR}/deps/node/deps/zlib
    ${PDG_SOURCE_DIR}/deps/node/deps/v8/third_party/zlib
)

IF( NOT MACOSX AND NOT WIN32 )
	target_include_directories(minizip_static PRIVATE
		${PDG_SOURCE_DIR}/deps/node/deps/openssl/config
		${PDG_SOURCE_DIR}/deps/node/deps/openssl/config/archs/linux-x86_64/asm/include
		${PDG_SOURCE_DIR}/deps/node/deps/openssl/openssl/include
	)
ENDIF()

# Set compile definitions for minizip
target_compile_definitions(minizip_static PRIVATE
    -DHAVE_STDINT_H
    -DHAVE_INTTYPES_H
    -DHAVE_ZLIB
    -DZLIB_COMPAT
    -DHAVE_PKCRYPT
    -DHAVE_WZAES
    -DMZ_EXPORTS
    -DNO_GZIP
    -DNOUNCRYPT
    -DNOCRYPT
)

# Link zlib to minizip (on Windows use Node's built zlib by path; no separate zlib target)
IF(WIN32)
	target_link_libraries(minizip_static PRIVATE ${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib.lib)
ELSE()
	target_link_libraries(minizip_static PRIVATE ${PDG_SOURCE_DIR}/deps/node/out/Release/libzlib.a)
ENDIF()

# Set runtime library to static for minizip_static on Windows
IF( WIN32 )
	SET_PROPERTY(TARGET minizip_static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF( WIN32 )

# Create libtess2 static library
add_library(libtess2_static STATIC ${LIBTESS2_SRC})

# Set include directories for libtess2
target_include_directories(libtess2_static PUBLIC
    ${PDG_SOURCE_DIR}/deps/libtess2/Include
    ${PDG_SOURCE_DIR}/deps/libtess2/Source
)

# Set runtime library to static for libtess2_static on Windows
IF( WIN32 )
	SET_PROPERTY(TARGET libtess2_static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
ENDIF( WIN32 )

ADD_EXECUTABLE(pdg WIN32 MACOSX_BUNDLE 
	${SPRITER_FILES}
	${PLATFORM_FILES}
	${PDG_SOURCES}
	${PDG_JAVASCRIPT_BINDINGS_SOURCES}
)

# V8 requires C++20; ensure MSVC gets /std:c++20 and updates __cplusplus (needed for v8config.h)
SET_TARGET_PROPERTIES(pdg PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
IF(MSVC)
	TARGET_COMPILE_OPTIONS(pdg PRIVATE /std:c++20 /Zc:__cplusplus)
ENDIF()

target_compile_definitions(pdg PRIVATE
	PDG_PROJECT=PDG_PROJECT_NODE_APP
	PDG_COMPILING_FOR_JAVASCRIPT=1
	PDG_STANDALONE_NODE_APP=1
	PDG_LIBRARY=1
	PDG_NO_SLEEP=1
	PDG_INTERNAL_LIB=1
	PDG_NO_NETWORK=1
	DEBUG=1
)

# Set include directories for the target (modern CMake approach)
TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE
	${PDG_INCLUDE_DIRECTORIES}
	${PDG_SOURCE_DIR}/deps/node/deps/zlib
	${PDG_SOURCE_DIR}/deps/minizip
	${PDG_SOURCE_DIR}/deps
	${OPENGL_INCLUDE_DIR}
	${PDG_JAVASCRIPT_BINDINGS_INCLUDE_DIRECTORIES}
)

# Add platform-specific include directories
IF( MACOSX )
	TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE ${PDG_SOURCE_DIR}/src/sys/macosx)
	IF(PDG_WITH_GLFW)
		TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE ${PDG_PLATFORM_GLFW_INCLUDE_DIRS})
	ENDIF()
	ENDIF( MACOSX )

IF( WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_PLATFORM_GLFW_INCLUDE_DIRS}
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
		${PDG_SOURCE_DIR}/deps
	)
ENDIF( WIN32 )

# Add libjpeg-turbo include directories for Unix/Linux
IF( NOT MACOSX AND NOT WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
	)
ENDIF( NOT MACOSX AND NOT WIN32 )

IF( USE_SPRITER )
	TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
ENDIF( USE_SPRITER )

IF( USE_CHIPMUNK )
	TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE ${PDG_SOURCE_DIR}/deps/chipmunk/include)
ENDIF( USE_CHIPMUNK )

# Add libtess2 include directories for polygon tessellation
TARGET_INCLUDE_DIRECTORIES(pdg PRIVATE ${PDG_SOURCE_DIR}/deps/libtess2/Include)

# Set link directories for the target (modern CMake approach)
TARGET_LINK_DIRECTORIES(pdg PRIVATE
    ${NODE_LINK_DIRS}
    ${GLFW_LINK_DIRS}
    ${CHIPMUNK_LINK_DIRS}
    ${LIBJPEG_LINK_DIRS}
)

# ============================================================================
# PDG Core Library (No JavaScript Bindings)
# ============================================================================
# Static library with all PDG C++ framework code

ADD_LIBRARY(pdg-lib STATIC
	${PDG_SOURCES}
	${PLATFORM_FILES}
	${SPRITER_FILES}
)

# Set compile definitions for pdg-lib (C++ only)
TARGET_COMPILE_DEFINITIONS(pdg-lib PRIVATE
	PDG_INTERNAL_LIB=1
	PDG_LIBRARY=1
	PDG_NO_SLEEP=1
	PDG_NO_NETWORK=1
	NDEBUG  # No debug code for performance testing
)

# Force Release build optimizations for pdg-lib used by performance tests
# Remove debug symbols and add full optimizations regardless of build type
IF(MSVC)
	# MSVC: Maximum optimization, inline expansion, favor speed
	TARGET_COMPILE_OPTIONS(pdg-lib PRIVATE /O2 /Oi /Ot /GL /Zi- /DEBUG:NONE)
ELSE()
	# GCC/Clang: Maximum optimization, no debug symbols, aggressive optimizations
	TARGET_COMPILE_OPTIONS(pdg-lib PRIVATE -O3 -g0 -ffast-math -funroll-loops)
ENDIF()

# Set include directories for pdg-lib
TARGET_INCLUDE_DIRECTORIES(pdg-lib PUBLIC
	${PDG_INCLUDE_DIRECTORIES}
)

TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE
	${PDG_SOURCE_DIR}/deps/node/deps/zlib
	${PDG_SOURCE_DIR}/deps/minizip
	${PDG_SOURCE_DIR}/deps
	${OPENGL_INCLUDE_DIR}
)

# Add platform-specific include directories
IF( MACOSX )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE ${PDG_SOURCE_DIR}/src/sys/macosx)
	IF(PDG_WITH_GLFW)
		TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE ${PDG_PLATFORM_GLFW_INCLUDE_DIRS})
	ENDIF()
	ENDIF( MACOSX )

IF( WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_PLATFORM_GLFW_INCLUDE_DIRS}
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
		${PDG_SOURCE_DIR}/deps
	)
ENDIF( WIN32 )

IF( NOT MACOSX AND NOT WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
	)
ENDIF()

IF( USE_SPRITER )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
ENDIF( USE_SPRITER )

IF( USE_CHIPMUNK )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE ${PDG_SOURCE_DIR}/deps/chipmunk/include)
ENDIF( USE_CHIPMUNK )

# Add libtess2 include directories
TARGET_INCLUDE_DIRECTORIES(pdg-lib PRIVATE ${PDG_SOURCE_DIR}/deps/libtess2/Include)

# Link pdg-lib dependencies (minizip, libtess2, zlib)
IF(WIN32)
	TARGET_LINK_LIBRARIES(pdg-lib PUBLIC
		libtess2_static
		minizip_static
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_adler32_simd.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_data_chunk_simd.lib
	)
ELSE()
	TARGET_LINK_LIBRARIES(pdg-lib PUBLIC
		libtess2_static
		minizip_static
		${PDG_NODE_STATIC_ZLIB_LIBS}
	)
ENDIF()

IF( MACOSX )
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg-lib PUBLIC glfw3 )
	ENDIF()
	ENDIF( MACOSX )

IF( WIN32 )
	SET_PROPERTY(TARGET pdg-lib PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg-lib PUBLIC glfw3 )
	ENDIF()
ENDIF( WIN32 )

# ============================================================================
# PDG Library - Debug Version (libpdgd.a)
# ============================================================================
# A debug version of pdg-lib with DEBUG=1 and full debug symbols

ADD_LIBRARY(pdg-lib-debug STATIC
	${PDG_SOURCES}
	${PLATFORM_FILES}
	${SPRITER_FILES}
)

# Set output name to libpdgd.a (debug suffix convention)
SET_TARGET_PROPERTIES(pdg-lib-debug PROPERTIES OUTPUT_NAME pdgd)

# Set compile definitions for debug library
TARGET_COMPILE_DEFINITIONS(pdg-lib-debug PRIVATE
	PDG_INTERNAL_LIB=1
	PDG_LIBRARY=1
	PDG_NO_SLEEP=1
	PDG_NO_NETWORK=1
	DEBUG=1  # Enable debug code
)

# Debug build flags: full debug symbols, no optimization
IF(MSVC)
	# MSVC: No optimization, full debug info
	TARGET_COMPILE_OPTIONS(pdg-lib-debug PRIVATE /Od /Zi /DEBUG:FULL)
	TARGET_LINK_OPTIONS(pdg-lib-debug PRIVATE /DEBUG:FULL)
ELSE()
	# GCC/Clang: No optimization, full debug info
	TARGET_COMPILE_OPTIONS(pdg-lib-debug PRIVATE -O0 -g3)
ENDIF()

# Set include directories for pdg-lib-debug (same as optimized version)
TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PUBLIC
	${PDG_INCLUDE_DIRECTORIES}
)

TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE
	${PDG_SOURCE_DIR}/deps/node/deps/zlib
	${PDG_SOURCE_DIR}/deps/minizip
	${PDG_SOURCE_DIR}/deps
	${OPENGL_INCLUDE_DIR}
)

# Add platform-specific include directories
IF( MACOSX )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE ${PDG_SOURCE_DIR}/src/sys/macosx)
	IF(PDG_WITH_GLFW)
		TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE ${PDG_PLATFORM_GLFW_INCLUDE_DIRS})
	ENDIF()
	ENDIF( MACOSX )

IF( WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_PLATFORM_GLFW_INCLUDE_DIRS}
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
		${PDG_SOURCE_DIR}/deps
	)
ENDIF( WIN32 )

IF( NOT MACOSX AND NOT WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
	)
ENDIF()

IF( USE_SPRITER )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
ENDIF( USE_SPRITER )

IF( USE_CHIPMUNK )
	TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE ${PDG_SOURCE_DIR}/deps/chipmunk/include)
ENDIF( USE_CHIPMUNK )

# Add libtess2 include directories
TARGET_INCLUDE_DIRECTORIES(pdg-lib-debug PRIVATE ${PDG_SOURCE_DIR}/deps/libtess2/Include)

# Link pdg-lib-debug dependencies (same as optimized version)
IF(WIN32)
	TARGET_LINK_LIBRARIES(pdg-lib-debug PUBLIC
		libtess2_static
		minizip_static
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_adler32_simd.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_data_chunk_simd.lib
	)
ELSE()
	TARGET_LINK_LIBRARIES(pdg-lib-debug PUBLIC
		libtess2_static
		minizip_static
		${PDG_NODE_STATIC_ZLIB_LIBS}
	)
ENDIF()

IF( MACOSX )
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg-lib-debug PUBLIC glfw3 )
	ENDIF()
	ENDIF( MACOSX )

IF( WIN32 )
	SET_PROPERTY(TARGET pdg-lib-debug PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg-lib-debug PUBLIC glfw3 )
	ENDIF()
ENDIF( WIN32 )

# ============================================================================
# PDG Libraries - Build Both Versions
# ============================================================================
# Custom target to build both optimized and debug versions

ADD_CUSTOM_TARGET(pdg-libs
	DEPENDS pdg-lib pdg-lib-debug
	COMMENT "Building both optimized (libpdg-lib.a) and debug (libpdgd.a) versions of PDG library"
)

SET_SOURCE_FILES_PROPERTIES( 
	${MINIZIP_SRC}
	COMPILE_FLAGS "-DCASESENSITIVITYDEFAULT_NO -DNO_GZIP -DNOUNCRYPT -DNOCRYPT"
)

SET( APP_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR} )

IF( MACOSX )
	SET( APP_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/pdg.app/Contents/MacOS" )
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg glfw3 )
	ENDIF()
	IF(NOT PDG_HEADLESS)
		# Link OpenGL and other frameworks for macOS
		TARGET_LINK_LIBRARIES ( pdg 
			"-framework AppKit"
			"-framework CoreGraphics"
			"-framework AudioToolbox"
			"-framework CoreFoundation"
			"-framework Security"
			"-framework OpenGL"
			"-framework GLUT"
			"-framework IOKit"
		)
	ELSE()
		TARGET_LINK_LIBRARIES ( pdg
			"-framework AudioToolbox"
			"-framework CoreFoundation"
			"-framework IOKit"
		)
	ENDIF()
ENDIF( MACOSX )

IF( WIN32 )
	SET_TARGET_PROPERTIES(pdg PROPERTIES  COMPILE_DEFINITIONS_DEBUG _CONSOLE)
	SET_TARGET_PROPERTIES(pdg PROPERTIES  COMPILE_DEFINITIONS_RELEASE _CONSOLE) 
	SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:CONSOLE /NODEFAULTLIB:MSVCRT /LTCG /ignore:4049 /ignore:4217 /ignore:4218 /ignore:4219")
	SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE /NODEFAULTLIB:MSVCRT /LTCG /ignore:4049 /ignore:4217 /ignore:4218 /ignore:4219")
	# Set runtime library to static for all configurations
	SET_PROPERTY(TARGET pdg PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	IF(PDG_WITH_GLFW)
		TARGET_LINK_LIBRARIES ( pdg glfw3 strmiids imm32 psapi iphlpapi winmm ws2_32 user32 jpeg bcrypt advapi32 crypt32 userenv msvcrt)
	ELSE()
		TARGET_LINK_LIBRARIES ( pdg strmiids imm32 psapi iphlpapi winmm ws2_32 user32 jpeg bcrypt advapi32 crypt32 userenv msvcrt)
	ENDIF()
ENDIF( WIN32 )

SET( APP_JS_OUT_DIR "${APP_OUT_DIR}/lib/" )

IF( USE_CHIPMUNK )
	IF(WIN32)
		TARGET_LINK_LIBRARIES (pdg Chipmunk)
	ELSE()
		TARGET_LINK_LIBRARIES (pdg ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src/libchipmunk.a)
	ENDIF()
ENDIF( USE_CHIPMUNK )

# Link Node.js components (these are already included in libnode.a on non-Windows platforms)
IF( WIN32 )
	# Link Node.js library and its dependencies (built under out/Release/lib/)
	TARGET_LINK_LIBRARIES ( pdg
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/libnode.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/libuv.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/uvwasi.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/icui18n.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/icuucx.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/icudata.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/cares.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/nghttp2.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/histogram.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/llhttp.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/openssl.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/sqlite.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/brotli.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/ncrypto.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/simdutf.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/simdjson.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/abseil.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/highway.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/ada.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/crdtp.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/nbytes.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_zlib.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_adler32_simd.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zlib_data_chunk_simd.lib
		# V8 libraries
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_base_without_compiler.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_compiler.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_init.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_initializers.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_initializers_slow.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_libbase.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_libplatform.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/v8_snapshot.lib
		${PDG_SOURCE_DIR}/deps/node/out/Release/lib/zstd.lib
		minizip_static
		libtess2_static
		${PLATFORM_LIBS} ${OPENGL_LIBRARIES}
	)
ELSE (WIN32)
    # non-windows platforms
	IF( MACOSX )
		TARGET_LINK_LIBRARIES ( pdg
			${PDG_NODE_NONWIN_LIBS}
			minizip_static
			libtess2_static
		)
	ELSE()
		TARGET_LINK_LIBRARIES ( pdg
			"-Wl,--start-group"
			${PDG_NODE_NONWIN_LIBS}
			"-Wl,--end-group"
			minizip_static
			libtess2_static
		)
	ENDIF()
	# Add libjpeg-turbo for Unix/Linux platforms
	IF( NOT MACOSX )
		TARGET_LINK_LIBRARIES ( pdg ${PDG_SYSTEM_JPEG_LIBRARY} )
	ENDIF( NOT MACOSX )
ENDIF(WIN32)


IF(CAN_BUILD_INTERFACES)
	#check if bindings/jsc-ios exists
	IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios")
		SET( CAN_BUILD_JSC_INTERFACES TRUE )
	ENDIF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios")

	IF(WIN32)
		SET(GEN_SCRIPT_INTERFACE_CMD ${CMAKE_COMMAND} -E env "BCPP_EXE=${BCPP_EXECUTABLE}" powershell -NoProfile -ExecutionPolicy Bypass -File "${CMAKE_SOURCE_DIR}/tools/gen-script-interface.ps1")
	ELSE()
		SET(GEN_SCRIPT_INTERFACE_CMD "${CMAKE_SOURCE_DIR}/tools/gen-script-interface.sh")
	ENDIF()

	SET( JS_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/js/coordinates.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/color.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netclient.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netconnection.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netserver.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/dump.js"
	) 

	SET( JS_JSC_IOS_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/pdg.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/internal/linkedlist.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/assert.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/child_process.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/console.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/events.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/fs.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/module.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/os.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/path.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/punycode.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/timers.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/url.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/util.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/vm.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_main.js"
	)

	SET( JS_NODE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/pdg.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_main_v24.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_bootstrap.js"
	)

	SET( JS_NATIVE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_natives.h"
	)

	IF(CAN_BUILD_JSC_INTERFACES)
		LIST(APPEND JS_NATIVE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_natives.h")
	ENDIF(CAN_BUILD_JSC_INTERFACES)

	# custom command for building the pdg_natives.h file(s)
	# should only need to run when the .js files in src/js/ change
	# (Node and jsc-ios must be separate OUTPUT rules — each COMMAND only writes one file.)
	ADD_CUSTOM_COMMAND(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_natives.h"
		COMMAND ${PDG_PYTHON3} "${PDG_SOURCE_DIR}/tools/js2c.py" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_natives.h" ${JS_FILES} ${JS_NODE_FILES}
		DEPENDS ${JS_FILES} ${JS_NODE_FILES}
	)

	IF(CAN_BUILD_JSC_INTERFACES)
		ADD_CUSTOM_COMMAND(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_natives.h"
			COMMAND ${PDG_PYTHON3} "${PDG_SOURCE_DIR}/tools/js2c.py" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_natives.h" ${JS_FILES} ${JS_JSC_IOS_FILES}
			DEPENDS ${JS_FILES} ${JS_JSC_IOS_FILES}
		)
	ENDIF(CAN_BUILD_JSC_INTERFACES)
	ADD_CUSTOM_TARGET(pdg_js2native ALL DEPENDS ${JS_NATIVE_FILES}) 

	SET( COMMON_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_interface.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_impl.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_impl.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/physics/physics_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/physics/cp_arbiter.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/physics/cp_constraint.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/physics/cp_space.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/config_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/log_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/event_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/timer_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/file_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/mem_block.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/resource_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/serializer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/serializable.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/deserializer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/graphics_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/graphics_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/image.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/port.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/spline.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/polygon.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/drawing.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/font.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/attributes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animation_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animated.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/sprite.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/sprite_layer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/tile_layer.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/audio/audio_bindings.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/audio/sound_manager.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/audio/sound.cpp"
	)
	
	# Add macro files as dependencies for binding generation
	# These are the main macro files that are included by multiple binding files
	SET( BINDING_MACRO_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/graphics_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/graphics_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animation_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animation_macros.h"
	)
	
	# Create a more targeted dependency approach
	# Only add macro files as dependencies to the main script implementation files
	# that actually include them, rather than to all binding files
	SET( SCRIPT_IMPL_MACRO_DEPS
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_impl_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animation_impl_macros.h"
	)
	SET( BINDING_SCRIPT_DIRS
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8"
	)
	SET( BINDING_SCRIPT_SUBDIRS
		"physics"
		"core"
		"data"
		"graphics"
		"audio"
		"animation"
	)
	# custom command for building the script interfaces files common to all languages
	# should only need to run when the files in src/bindings/common/ change
	# to add a new language, setup a new BINDING_SCRIPT_DIR above and
	# implement the various macros and supporting files
	FOREACH(dir ${BINDING_SCRIPT_DIRS})
		FOREACH(subdir ${BINDING_SCRIPT_SUBDIRS})
			ADD_CUSTOM_COMMAND(OUTPUT "${dir}/${subdir}/.dir"
				COMMAND ${CMAKE_COMMAND} -E make_directory "${dir}/${subdir}"
				COMMAND ${CMAKE_COMMAND} -E touch "${dir}/${subdir}/.dir"
			)
		ENDFOREACH(subdir)
	ENDFOREACH(dir)
	
	FOREACH(srcfile ${COMMON_BINDING_SRC}) 
		GET_FILENAME_COMPONENT( filename "${srcfile}" NAME )
		GET_FILENAME_COMPONENT( dirname "${srcfile}" DIRECTORY )
		GET_FILENAME_COMPONENT( parentdir "${dirname}" NAME )
		
		# Determine output directory based on source file location
		IF( "${parentdir}" IN_LIST BINDING_SCRIPT_SUBDIRS )
			SET( outdir "${parentdir}" )
		ELSE()
			SET( outdir "." )
		ENDIF()
		
		# Determine which macro dependencies to add based on the source file
		SET( macro_deps "" )
		IF( "${filename}" STREQUAL "pdg_script_impl.cpp" )
			SET( macro_deps ${SCRIPT_IMPL_MACRO_DEPS} )
		ELSEIF( "${filename}" STREQUAL "image.cpp" )
			SET( macro_deps "${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/graphics/graphics_impl_macros.h" )
		ELSEIF( "${parentdir}" STREQUAL "core" )
			SET( macro_deps "${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_impl_macros.h" )
		ELSEIF( "${parentdir}" STREQUAL "data" )
			SET( macro_deps "${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_impl_macros.h" )
		ELSEIF( "${parentdir}" STREQUAL "animation" )
			SET( macro_deps 
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/animation/animation_impl_macros.h"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/core/core_impl_macros.h"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/data/data_impl_macros.h"
			)
		ENDIF()
		
		# Generate for V8
		SET( outfile "${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/${outdir}/${filename}" )
		LIST(APPEND interface_outfiles ${outfile}) 
		ADD_CUSTOM_COMMAND(OUTPUT "${outfile}"
			COMMAND ${GEN_SCRIPT_INTERFACE_CMD} "javascript/v8" "${srcfile}" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/${outdir}" "./" "${filename}"
			DEPENDS "${srcfile}" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_script_macros.h" 
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/physics/.dir" 
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/core/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/data/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/graphics/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/audio/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/animation/.dir"
				${macro_deps}
		) 
		# Generate for JSC
		SET( outfile "${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/${outdir}/${filename}" )
		LIST(APPEND interface_outfiles ${outfile}) 
		ADD_CUSTOM_COMMAND(OUTPUT "${outfile}"
			COMMAND ${GEN_SCRIPT_INTERFACE_CMD} "javascript/jsc" "${srcfile}" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/${outdir}" "./" "${filename}"
			DEPENDS "${srcfile}" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_script_macros.h" 
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/physics/.dir" 
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/core/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/data/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/graphics/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/audio/.dir"
				"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/animation/.dir"
				${macro_deps}
		) 
	ENDFOREACH(srcfile)
	ADD_CUSTOM_TARGET(pdg_common_interfaces ALL DEPENDS ${interface_outfiles})

	SET( V8_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_classes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_script_macros.h"
	)
	SET( V8_INTERFACES_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8/pdg_interfaces.cpp"
	)
	# custom command for building the v8 version of the pdg_interfaces.cpp file
	# should only need to run when the pdg_js_classes.cpp file in src/bindings/javascript/v8/ change
	ADD_CUSTOM_COMMAND(OUTPUT ${V8_INTERFACES_SRC}
		COMMAND ${GEN_SCRIPT_INTERFACE_CMD}
			"javascript/v8" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_classes.cpp" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/v8" "./"
			"pdg_interfaces.cpp"
		DEPENDS ${V8_BINDING_SRC}
	)
	ADD_CUSTOM_TARGET(pdg_v8_interfaces ALL DEPENDS ${V8_INTERFACES_SRC})

	SET( JSC_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_js_classes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_script_macros.h"
	)
	SET( JSC_INTERFACES_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc/pdg_interfaces.cpp"
	)
	# custom command for building the JavaScriptCore version of the pdg_interfaces.cpp file
	# should only need to run when the pdg_js_classes.cpp file in src/bindings/javascript/jsc/ changes
	ADD_CUSTOM_COMMAND(OUTPUT ${JSC_INTERFACES_SRC}
		COMMAND ${GEN_SCRIPT_INTERFACE_CMD}
			"javascript/jsc" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_js_classes.cpp" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/generated/jsc" "./"
			"pdg_interfaces.cpp"
		DEPENDS ${JSC_BINDING_SRC}
	)
	ADD_CUSTOM_TARGET(pdg_jsc_interfaces ALL DEPENDS ${JSC_INTERFACES_SRC})

	ADD_DEPENDENCIES(pdg pdg_common_interfaces pdg_js2native pdg_v8_interfaces pdg_jsc_interfaces)

IF( USE_CHIPMUNK )
	IF(WIN32)
		TARGET_LINK_LIBRARIES (pdg-lib PUBLIC Chipmunk)
		TARGET_LINK_LIBRARIES (pdg-lib-debug PUBLIC Chipmunk)
	ELSE()
		TARGET_LINK_LIBRARIES (pdg-lib PUBLIC ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src/libchipmunk.a)
		TARGET_LINK_LIBRARIES (pdg-lib-debug PUBLIC ${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src/libchipmunk.a)
	ENDIF()
ENDIF( USE_CHIPMUNK )
ENDIF(CAN_BUILD_INTERFACES)

IF(NOT PDG_HEADLESS)
# ============================================================================
# PDG Bunnymark Performance Test Executable
# ============================================================================
# A standalone C++ benchmark that doesn't require Node.js or V8 bindings

ADD_EXECUTABLE(bunnymark WIN32 MACOSX_BUNDLE
	../test/perf/cpp-bunnymark/bunnymark.cpp
	sys/unix/main-unix.cpp
)

# Bunnymark uses the pure C++ pdg-lib (no JavaScript bindings)
TARGET_COMPILE_DEFINITIONS(bunnymark PRIVATE 
	PDG_INTERNAL_LIB=1
	PDG_PROJECT=PDG_PROJECT_C_ONLY_APP
	NDEBUG  # Disable assertions for performance testing
)

# Force Release build optimizations for performance tests
# Remove debug symbols and add full optimizations regardless of build type
IF(MSVC)
	# MSVC: Maximum optimization, inline expansion, favor speed
	TARGET_COMPILE_OPTIONS(bunnymark PRIVATE /O2 /Oi /Ot /GL /Zi- /DEBUG:NONE)
	TARGET_LINK_OPTIONS(bunnymark PRIVATE /LTCG /DEBUG:NONE)  # Link-time code generation
ELSE()
	# GCC/Clang: Maximum optimization, no debug symbols, aggressive optimizations
	TARGET_COMPILE_OPTIONS(bunnymark PRIVATE -O3 -g0 -ffast-math -funroll-loops)
ENDIF()

# Set include directories for bunnymark
TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE
	${PDG_SOURCE_DIR}/src/inc 
	${PDG_SOURCE_DIR}/src/sys
	${PDG_SOURCE_DIR}/deps
	${OPENGL_INCLUDE_DIR}
)

# Add platform-specific include directories
IF( MACOSX )
	TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE ${PDG_SOURCE_DIR}/src/sys/macosx)
	IF( USE_GLFW_MAC ) 
		TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE ${PDG_SOURCE_DIR}/deps/glfw/include)
	ENDIF( USE_GLFW_MAC )
ENDIF( MACOSX )

IF( WIN32 )
	TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_SOURCE_DIR}/deps/glfw/include
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
		${PDG_SOURCE_DIR}/deps
	)
ENDIF( WIN32 )

# Add libtess2 include directories
TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE ${PDG_SOURCE_DIR}/deps/libtess2/Include)

# Add Spriter include directories if enabled
IF( USE_SPRITER )
	TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
ENDIF( USE_SPRITER )

# Add Chipmunk include directories if enabled
IF( USE_CHIPMUNK )
	TARGET_INCLUDE_DIRECTORIES(bunnymark PRIVATE ${PDG_SOURCE_DIR}/deps/chipmunk/include)
ENDIF( USE_CHIPMUNK )

# Set link directories for bunnymark
TARGET_LINK_DIRECTORIES(bunnymark PRIVATE
	${NODE_LINK_DIRS}
	${GLFW_LINK_DIRS}
	${CHIPMUNK_LINK_DIRS}
)

# Link against pdg-lib and platform frameworks (no Node.js, no V8)
IF( MACOSX )
	TARGET_LINK_LIBRARIES ( bunnymark 
		pdg-lib
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
ENDIF( MACOSX )

IF( WIN32 )
	SET_PROPERTY(TARGET bunnymark PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	TARGET_LINK_LIBRARIES ( bunnymark pdg-lib imm32 psapi winmm user32 strmiids bcrypt advapi32 crypt32 userenv msvcrt ${OPENGL_LIBRARIES})
ENDIF( WIN32 )

# ============================================================================
# PDG PDGMark Performance Test Executable
# ============================================================================
# A standalone C++ benchmark that tests multiple aspects of 2D rendering

ADD_EXECUTABLE(pdgmark WIN32 MACOSX_BUNDLE
	../test/perf/cpp-pdgmark/pdgmark.cpp
	sys/unix/main-unix.cpp
)

# PDGMark uses the pure C++ pdg-lib (no JavaScript bindings)
TARGET_COMPILE_DEFINITIONS(pdgmark PRIVATE 
	PDG_INTERNAL_LIB=1
	PDG_PROJECT=PDG_PROJECT_C_ONLY_APP
	NDEBUG  # Disable assertions for performance testing
)

# Force Release build optimizations for performance tests
# Remove debug symbols and add full optimizations regardless of build type
IF(MSVC)
	# MSVC: Maximum optimization, inline expansion, favor speed
	TARGET_COMPILE_OPTIONS(pdgmark PRIVATE /O2 /Oi /Ot /GL /Zi- /DEBUG:NONE)
	TARGET_LINK_OPTIONS(pdgmark PRIVATE /LTCG /DEBUG:NONE)  # Link-time code generation
ELSE()
	# GCC/Clang: Maximum optimization, no debug symbols, aggressive optimizations
	TARGET_COMPILE_OPTIONS(pdgmark PRIVATE -O3 -g0 -ffast-math -funroll-loops)
ENDIF()

# Set include directories for pdgmark
TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE
	${PDG_SOURCE_DIR}/src/inc 
	${PDG_SOURCE_DIR}/src/sys
	${PDG_SOURCE_DIR}/deps
	${OPENGL_INCLUDE_DIR}
)

# Add platform-specific include directories
IF( MACOSX )
	TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE ${PDG_SOURCE_DIR}/src/sys/macosx)
	IF( USE_GLFW_MAC ) 
		TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE ${PDG_SOURCE_DIR}/deps/glfw/include)
	ENDIF( USE_GLFW_MAC )
ENDIF( MACOSX )

IF( WIN32 )
	TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_SOURCE_DIR}/deps/glfw/include
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps/libjpeg-turbo/src
		${PDG_SOURCE_DIR}/deps
	)
ENDIF( WIN32 )

# Add libtess2 include directories
TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE ${PDG_SOURCE_DIR}/deps/libtess2/Include)

# Add Spriter include directories if enabled
IF( USE_SPRITER )
	TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/spriterengine
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/tinyxml2
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/pugixml
		${PDG_SOURCE_DIR}/deps/SpriterPlusPlus/nlohmann-json
	)
ENDIF( USE_SPRITER )

# Add Chipmunk include directories if enabled
IF( USE_CHIPMUNK )
	TARGET_INCLUDE_DIRECTORIES(pdgmark PRIVATE ${PDG_SOURCE_DIR}/deps/chipmunk/include)
ENDIF( USE_CHIPMUNK )

# Set link directories for pdgmark
TARGET_LINK_DIRECTORIES(pdgmark PRIVATE
	${NODE_LINK_DIRS}
	${GLFW_LINK_DIRS}
	${CHIPMUNK_LINK_DIRS}
)

# Link against pdg-lib and platform frameworks (no Node.js, no V8)
IF( MACOSX )
	TARGET_LINK_LIBRARIES ( pdgmark 
		pdg-lib
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
ENDIF( MACOSX )

IF( WIN32 )
	SET_PROPERTY(TARGET pdgmark PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	TARGET_LINK_LIBRARIES ( pdgmark pdg-lib imm32 psapi winmm user32 strmiids bcrypt advapi32 crypt32 userenv msvcrt ${OPENGL_LIBRARIES})
ENDIF( WIN32 ) 
ENDIF()
