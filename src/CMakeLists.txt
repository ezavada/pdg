INCLUDE_DIRECTORIES (
	${PDG_SOURCE_DIR}/src/inc 
	${PDG_SOURCE_DIR}/src/sys
	${PDG_SOURCE_DIR}/deps/node/deps/zlib
	${PDG_SOURCE_DIR}/deps/node/deps/zlib/contrib/minizip
	${PDG_SOURCE_DIR}/src/bindings/javascript
	${PDG_SOURCE_DIR}/src/bindings/javascript/v8
	${PDG_SOURCE_DIR}/src/bindings/node
	${PDG_SOURCE_DIR}/deps/node/src
	${PDG_SOURCE_DIR}/deps/node/deps/uv/include
	${PDG_SOURCE_DIR}/deps/node/deps/v8/include
	${OPENGL_INCLUDE_DIR}
)

IF( USE_SPRITER )
	INCLUDE_DIRECTORIES ( 
		${PDG_SOURCE_DIR}/deps/scml-pp/source 
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries
		${PDG_SOURCE_DIR}/deps/scml-pp/source/renderers
	)
	SET( SPRITER_FILES
		${PDG_SOURCE_DIR}/deps/scml-pp/source/SCMLpp.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries/tinystr.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries/tinyxml.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries/tinyxmlerror.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries/tinyxmlparser.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/libraries/XML_Helpers.cpp
		${PDG_SOURCE_DIR}/deps/scml-pp/source/renderers/SCML_pdg.cpp
	)
	ADD_DEFINITIONS ( -DPDG_SCML_SUPPORT )
ELSE( USE_SPRITER )
	SET( SPRITER_FILES )
ENDIF( USE_SPRITER )

IF( MACOSX )
	INCLUDE_DIRECTORIES ( ${PDG_SOURCE_DIR}/src/sys/macosx )
	IF( USE_GLFW_MAC ) 
		ADD_DEFINITIONS ( -DPDG_USE_GLFW )
		INCLUDE_DIRECTORIES ( ${PDG_SOURCE_DIR}/deps/glfw/include )
		SET( PLATFORM_FILES sys/glfw/platform-graphics-glfw.cpp )
	ELSE( USE_GLFW_MAC )
		SET( PLATFORM_FILES sys/macosx/platform-graphics-macosx.mm )
	ENDIF( USE_GLFW_MAC )
	SET( PLATFORM_FILES
		${PLATFORM_FILES}
		sys/unix/os-unix.cpp
		sys/macosx/config-macosx.cpp
		sys/macosx/graphics-macosx-opengl.cpp
		sys/macosx/internals-macosx.mm
		sys/macosx/platform-dirs-macosx.cpp
		sys/macosx/platform-events-macosx.cpp
		sys/macosx/platform-image-macosx.mm
		sys/macosx/pdg-lib-macosx.mm
		sys/macosx/pdg-opengl-view.mm
		sys/macosx/sound-macosx.cpp
		sys/macosx/sound-mgr-macosx.cpp
	)
	SET( PLATFORM_LIBS
		${APPKIT} ${APPSERVICES} ${COREFOUND} ${AUDIOTOOLBOX} ${IOKIT}
	)
#	ADD_DEFINITIONS ( -arch i386 -arch x86_64 )
ENDIF( MACOSX )

IF( WIN32 )
	INCLUDE_DIRECTORIES ( 
		${PDG_SOURCE_DIR}/src/sys/win32
		${PDG_SOURCE_DIR}/deps/glfw/include
		${PDG_SOURCE_DIR}/deps/png
		${PDG_SOURCE_DIR}/deps
	)
	SET( PLATFORM_FILES
    	sys/pdg-lib.cpp
		sys/glfw/platform-graphics-glfw.cpp
		sys/glfw/platform-events-glfw.cpp
		sys/win32/graphics-win32-opengl.cpp
		sys/win32/config-win32.cpp
		sys/win32/os-win32.cpp
		sys/win32/platform-win32.cpp
		sys/win32/sound-directx.cpp
		sys/win32/sound-mgr-directx.cpp
		sys/image-png.cpp
		../deps/png/png.c
		../deps/png/pngerror.c
		../deps/png/pngget.c
		../deps/png/pngmem.c
		../deps/png/pngpread.c
		../deps/png/pngwrite.c
		../deps/png/pngread.c
		../deps/png/pngrio.c
		../deps/png/pngwio.c
		../deps/png/pngrtran.c
		../deps/png/pngwtran.c
		../deps/png/pngrutil.c
		../deps/png/pngwutil.c
		../deps/png/pngset.c
		../deps/png/pngtrans.c
	)
	ADD_DEFINITIONS ( -DPDG_USE_GLFW -DPDG_USE_LIBPNG )
	ADD_DEFINITIONS ( /D "_ITERATOR_DEBUG_LEVEL=0" /D UNICODE /D _UNICODE /D _CRT_SECURE_NO_WARNINGS /wd4244)
ENDIF( WIN32 )

ADD_DEFINITIONS (
	-DPDG_PROJECT=PDG_PROJECT_NODE_APP
	-DPDG_STANDALONE_NODE_APP
	-DPDG_LIBRARY
	-DPDG_COMPILING_FOR_JAVASCRIPT
	-DPDG_NO_SLEEP
	-DPDG_INTERNAL_LIB
	-DPDG_NO_NETWORK
	-DDEBUG
)

LINK_DIRECTORIES (
	${PDG_SOURCE_DIR}/deps/node/out/Release
)

IF( MACOSX )
	IF( USE_GLFW_MAC ) 
		LINK_DIRECTORIES ( 
			${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/glfw/src 
		)
	ENDIF( USE_GLFW_MAC )
ELSE( MACOSX )
	LINK_DIRECTORIES ( 
		${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/glfw/src 
	)
ENDIF( MACOSX )

IF( USE_CHIPMUNK )
	INCLUDE_DIRECTORIES ( ${PDG_SOURCE_DIR}/deps/chipmunk/include/chipmunk )
	LINK_DIRECTORIES ( 
		${PDG_SOURCE_DIR}/build/${BUILD_SUBDIR}/chipmunk/src 
	)
	ADD_DEFINITIONS ( -DPDG_USE_CHIPMUNK_PHYSICS )
ENDIF( USE_CHIPMUNK )

ADD_EXECUTABLE(pdg WIN32 MACOSX_BUNDLE 
	${SPRITER_FILES}
	${PLATFORM_FILES}
	bindings/javascript/v8/pdg_v8_support.cpp
	bindings/javascript/v8/pdg_script_impl.cpp
	bindings/javascript/v8/pdg_interfaces.cpp
	bindings/node/pdg_node.cpp
    sys/animated.cpp
    sys/ConvertUTF.c
    sys/collisiondetection.cpp
    sys/color.cpp
    sys/deserializer.cpp
    sys/eventemitter.cpp
    sys/eventmanager.cpp
    sys/font-impl.cpp
    sys/graphics-manager.cpp
    sys/graphics-opengl.cpp
    sys/image.cpp
    sys/image-opengl.cpp
    sys/log.cpp
    sys/os.cpp
    sys/pdg-main.cpp
    sys/resource.cpp
    sys/serializer.cpp
    sys/spline.cpp
    sys/sprite.cpp
    sys/spritelayer.cpp
    sys/spritemanager.cpp
    sys/textcache-opengl.cpp
    sys/tilelayer.cpp
    sys/timermanager.cpp
    sys/userdata.cpp
)

SET_SOURCE_FILES_PROPERTIES( 
	${ZLIB_FILES}
	COMPILE_FLAGS "-DCASESENSITIVITYDEFAULT_NO -DNO_GZIP -DNOUNCRYPT -DNOCRYPT"
)

SET( APP_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR} )

IF( MACOSX )
# 	SET_TARGET_PROPERTIES(
# 		pdg PROPERTIES
# 		LINK_FLAGS "-arch i386 -arch x86_64"
# 	)
	SET( APP_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/pdg.app/Contents/MacOS" )
	IF( USE_GLFW_MAC ) 
		TARGET_LINK_LIBRARIES ( pdg glfw3 )
	ENDIF( USE_GLFW_MAC )
ENDIF( MACOSX )

IF( WIN32 )
	SET_TARGET_PROPERTIES(pdg PROPERTIES  COMPILE_DEFINITIONS_DEBUG _CONSOLE)
	SET_TARGET_PROPERTIES(pdg PROPERTIES  COMPILE_DEFINITIONS_RELEASE _CONSOLE) 
	SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SUBSYSTEM:CONSOLE /NODEFAULTLIB:MSVCRT /LTCG /ignore:4049")
	SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SUBSYSTEM:CONSOLE /NODEFAULTLIB:MSVCRT /LTCG /ignore:4049")
	SET(CMAKE_CXX_FLAGS_RELEASE "/MT")
	SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
	TARGET_LINK_LIBRARIES ( pdg glfw3 strmiids imm32 psapi iphlpapi winmm ws2_32 user32)
ENDIF( WIN32 )

SET( APP_JS_OUT_DIR "${APP_OUT_DIR}/lib/" )

IF( USE_CHIPMUNK )
	TARGET_LINK_LIBRARIES (pdg Chipmunk)
ENDIF( USE_CHIPMUNK )

TARGET_LINK_LIBRARIES ( pdg cares v8_base v8_snapshot http_parser openssl nodelib ${PLATFORM_LIBS} ${OPENGL_LIBRARIES} ) 

IF (WIN32)
	TARGET_LINK_LIBRARIES ( pdg libuv zlib ) 
ELSE(WIN32)
	TARGET_LINK_LIBRARIES ( pdg uv chrome_zlib ) 
ENDIF(WIN32)

IF(CAN_BUILD_INTERFACES)
	SET( JS_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/js/classify.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/coordinates.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/color.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netclient.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netconnection.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/netserver.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/js/dump.js"
	) 

	SET( JS_JSC_IOS_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/pdg.js"
		"${CMAKE_CURRENT_SOURCE_DIR}/../deps/node/lib/_linklist.js"
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
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_main.js"
	)

	SET( JS_NATIVE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_natives.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_natives.h"
	)

	# custom command for building the pdg_natives.h file(s)
	# should only need to run when the .js files in src/js/ change
	ADD_CUSTOM_COMMAND(OUTPUT ${JS_NATIVE_FILES}
		COMMAND "${PDG_SOURCE_DIR}/tools/js2c.py" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/node/pdg_natives.h" ${JS_FILES} ${JS_NODE_FILES}
		COMMAND "${PDG_SOURCE_DIR}/tools/js2c.py" "${CMAKE_CURRENT_SOURCE_DIR}/bindings/jsc-ios/pdg_natives.h" ${JS_FILES} ${JS_JSC_IOS_FILES}
		DEPENDS ${JS_FILES} ${JS_NODE_FILES} ${JS_JSC_IOS_FILES}
	)
	ADD_CUSTOM_TARGET(pdg_js2native ALL DEPENDS ${JS_NATIVE_FILES}) 

	SET( COMMON_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_interface.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_impl.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/common/pdg_script_impl.cpp"
	)
	SET( BINDING_SCRIPT_DIRS
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8"
	)
	# custom command for building the script interfaces files common to all languages
	# should only need to run when the files in src/bindings/common/ change
	# to add a new language, setup a new BINDING_SCRIPT_DIR above and
	# implement the various macros and supporting files
	FOREACH(srcfile ${COMMON_BINDING_SRC}) 
		GET_FILENAME_COMPONENT( filename "${srcfile}" NAME )
		FOREACH(dirname ${BINDING_SCRIPT_DIRS})
			SET( outfile "${dirname}/${filename}" )
			LIST(APPEND interface_outfiles ${outfile}) 
			ADD_CUSTOM_COMMAND(OUTPUT "${outfile}"
				COMMAND "${PDG_SOURCE_DIR}/tools/gen-script-interface.sh" "${srcfile}" "${dirname}" "./"
				DEPENDS "${srcfile}" "${dirname}/pdg_script_macros.h"
			) 
		ENDFOREACH(dirname)
	ENDFOREACH(srcfile)
	ADD_CUSTOM_TARGET(pdg_common_interfaces ALL DEPENDS ${interface_outfiles})

	SET( V8_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_classes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_macros.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_script_macros.h"
	)
	SET( V8_INTERFACES_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_interfaces.cpp"
	)
	# custom command for building the v8 version of the pdg_interfaces.cpp file
	# should only need to run when the pdg_js_classes.cpp file in src/bindings/javascript/v8/ change
	ADD_CUSTOM_COMMAND(OUTPUT ${V8_INTERFACES_SRC}
		COMMAND "${PDG_SOURCE_DIR}/tools/gen-script-interface.sh" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8/pdg_js_classes.cpp" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/v8" "./"
			"pdg_interfaces.cpp"
		DEPENDS ${V8_BINDING_SRC}
	)
	ADD_CUSTOM_TARGET(pdg_v8_interfaces ALL DEPENDS ${V8_INTERFACES_SRC})

	SET( JSC_BINDING_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_js_classes.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_script_macros.h"
	)
	SET( JSC_INTERFACES_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_interfaces.cpp"
	)
	# custom command for building the JavaScriptCore version of the pdg_interfaces.cpp file
	# should only need to run when the pdg_js_classes.cpp file in src/bindings/javascript/jsc/ changes
	ADD_CUSTOM_COMMAND(OUTPUT ${JSC_INTERFACES_SRC}
		COMMAND "${PDG_SOURCE_DIR}/tools/gen-script-interface.sh" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc/pdg_js_classes.cpp" 
			"${CMAKE_CURRENT_SOURCE_DIR}/bindings/javascript/jsc" "./"
			"pdg_interfaces.cpp"
		DEPENDS ${JSC_BINDING_SRC}
	)
	ADD_CUSTOM_TARGET(pdg_jsc_interfaces ALL DEPENDS ${JSC_INTERFACES_SRC})

	ADD_DEPENDENCIES(pdg pdg_common_interfaces pdg_js2native pdg_v8_interfaces pdg_jsc_interfaces)
ENDIF(CAN_BUILD_INTERFACES)

# custom command for copying the src/js/pdg.js files into the the App's library directory
# FOREACH ( jspath ${JS_FILES}) 
# 	STRING(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" jsfile ${jspath})
# 	ADD_CUSTOM_COMMAND(OUTPUT "${APP_JS_OUT_DIR}/${jsfile}" 
#     	COMMAND cmake -E copy "${jspath}" "${APP_JS_OUT_DIR}/${jsfile}" 
#     	DEPENDS "${jspath}" 
# 	) 
#    	LIST(APPEND jsfile_dest "${APP_JS_OUT_DIR}/${jsfile}") 
# ENDFOREACH(jspath)
# ADD_CUSTOM_TARGET(pdg_jscopy ALL DEPENDS ${jsfile_dest}) 
