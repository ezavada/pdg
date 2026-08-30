#
# Makefile for 'libpdg.so'.
#
# Type 'make' or 'make libpdg.so' to create the binary.
# Type 'make clean' or 'make clear' to delete all temporaries.
#

# build target specs

# first target entry is the target invoked when typing 'make'
.PHONY: all client-tests
all: libpdg

client-tests: libpdg
	@$(PDG_ROOT)/test/client --emscripten --no-build


EXPORTS='[ \
    "_pdg_LibSaveArgs", \
    "_pdg_LibGetArgc", \
    "_pdg_LibGetArgv", \
    "_pdg_LibNeedsInit", \
    "_pdg_LibInit", \
    "_pdg_LibIdle", \
    "_pdg_LibRun", \
    "_pdg_LibQuit", \
    "_pdg_LibIsQuitting", \
    ]'

INCLUDES := \
	-I$(PDG_ROOT)/src/inc \
	-I$(PDG_ROOT)/src/sys \
	-I$(PDG_ROOT)/deps/glfw/include \
	-I$(PDG_ROOT)/deps \
	-I$(PDG_ROOT)/deps/png \
	-I$(PDG_ROOT)/deps/node/deps/zlib \
	-I$(PDG_ROOT)/deps/node/deps/zlib/contrib/minizip \
	-I$(PDG_ROOT)/src/sys/unix \
	-I$(PDG_ROOT)/src/sys/glfw \
	-I$(PDG_ROOT)/deps/chipmunk/include \
	-I$(PDG_ROOT)/deps/libtess2/Include \
	-I$(PDG_ROOT)/deps/libtess2/Source \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/ \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/tinyxml2 \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/pugixml \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/example \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/nlohmann-json

DEFINES := \
	'-DDEBUG' \
	'-DPDG_DEBUG_OUT_TO_LOG' \
	'-DPDG_USE_CHIPMUNK_PHYSICS' \
	'-DPDG_USE_GLFW' \
	'-DPDG_USE_LIBJPEG' \
	'-DPDG_SPRITER_SUPPORT' \
	'-DPDG_NO_APP_FRAMEWORK' \
	'-DPDG_NO_NETWORK' \
	'-DPDG_LIBRARY' \
	'-DPDG_NO_SLEEP' \
	'-DPDG_INTERNAL_LIB' \
#	'-DPDG_NO_DEBUG_TO_CONSOLE' 


PATH_TO_CC="`which $(CC)`"
EMSCRIPTEN_INSTALL_DIR=$(filter-out ./,$(dir $(PATH_TO_CC)))
WEBIDL_BIND=$(EMSCRIPTEN_INSTALL_DIR)/tools/webidl_binder.py


LIBS = \
    -s USE_ZLIB=1 \
    -s USE_LIBPNG=1 \
    -s USE_LIBJPEG=1 \
    -s USE_GLFW=3 \
    -s LEGACY_GL_EMULATION=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s INITIAL_MEMORY=67108864 \
    -s DISABLE_EXCEPTION_CATCHING=0


CFLAGS_ALL=-gsource-map -Wno-warn-absolute-paths -DMOZZCONF_H $(DEFINES) $(INCLUDES)

CFLAGS=$(CFLAGS_ALL)
CXXFLAGS=-std=c++17 -fexceptions $(CFLAGS_ALL)

WASM_OUT_DIR=$(PDG_ROOT)/build/wasm
OUT_DIR=$(WASM_OUT_DIR)/pdg
SRC_SYS_DIR=$(PDG_ROOT)/src/sys
SRC_CHIPMUNK_DIR=$(PDG_ROOT)/deps/chipmunk/src
SRC_MINIZIP_DIR=$(PDG_ROOT)/deps/node/deps/zlib/contrib/minizip
SRC_SPRITERPLUSPLUS_DIR=$(PDG_ROOT)/deps/SpriterPlusPlus
SRC_UNIX_DIR=$(PDG_ROOT)/src/sys/unix
SRC_BINDINGS_DIR=$(PDG_ROOT)/src/bindings/emscripten
SRC_BINDINGS_JAVASCRIPT_DIR=$(PDG_ROOT)/src/bindings/javascript
SRC_JS_DIR=$(PDG_ROOT)/src/js

SPRITER_ENGINE_SOURCES := $(shell find $(SRC_SPRITERPLUSPLUS_DIR)/spriterengine -name '*.cpp' -print)
SPRITER_ENGINE_OBJS := $(patsubst $(SRC_SPRITERPLUSPLUS_DIR)/spriterengine/%.cpp,$(OUT_DIR)/spriterengine/%.cpp.o,$(SPRITER_ENGINE_SOURCES))
SPRITER_OVERRIDE_NAMES := tinyxmlspriterfiledocumentwrapper tinyxmlspriterfileelementwrapper tinyxmlspriterfileattributewrapper
SPRITER_OVERRIDE_OBJS := $(addprefix $(OUT_DIR)/spriter-override/,$(addsuffix .cpp.o,$(SPRITER_OVERRIDE_NAMES)))
PDG_SPRITER_NAMES := pdg_file_factory pdg_object_factory pdg_image_file pdg_point_instance_info pdg_bone_instance_info pdg_box_instance_info pdg_spriter_file_document_wrapper
PDG_SPRITER_OBJS := $(addprefix $(OUT_DIR)/pdg-spriter/,$(addsuffix .cpp.o,$(PDG_SPRITER_NAMES)))


ADDITIONAL_JS_FILES= \
    --embed-file $(SRC_JS_DIR)/dump.js@/js_modules/dump.js \
    --embed-file $(SRC_JS_DIR)/coordinates.js@/js_modules/coordinates.js \
    --embed-file $(SRC_JS_DIR)/color.js@/js_modules/color.js \
    --embed-file $(SRC_JS_DIR)/pdg-defs.js@/js_modules/pdg-defs.js \
    --embed-file $(SRC_BINDINGS_JAVASCRIPT_DIR)/pdg.js@/js_modules/pdg-wrapper.js \
    --embed-file $(PDG_ROOT)/test/data@/data \
    --embed-file $(PDG_ROOT)/test/data@/test/data \
    --embed-file $(PDG_ROOT)/test/perf/canvasmark2013/images@/test/perf/canvasmark2013/images \
    --embed-file $(PDG_ROOT)/test/perf/bunnymark/wabbit.png@/test/perf/bunnymark/wabbit.png \
    --embed-file $(PDG_ROOT)/test/spec@/spec \
    --embed-file $(PDG_ROOT)/test/cxx@/cxx \
    --embed-file $(PDG_ROOT)/test/js@/js \
    --embed-file $(PDG_ROOT)/test/misc/blend_mode_test.js@/misc/blend_mode_test.js \
    --embed-file $(PDG_ROOT)/test/perf/bunnymark/README.md@/perf/bunnymark/README.md \
    --post-js $(SRC_JS_DIR)/require.js \
    --post-js $(SRC_BINDINGS_DIR)/platform-emscripten.js \
    --post-js $(SRC_BINDINGS_DIR)/pdg_emscripten.js



OBJS= \
    $(OUT_DIR)/pdg_em_adaptors.cpp.o \
    $(OUT_DIR)/ConvertUTF.c.o \
	$(OUT_DIR)/memblock.cpp.o \
	$(OUT_DIR)/animated.cpp.o \
	$(OUT_DIR)/attributes.cpp.o \
	$(OUT_DIR)/collisiondetection.cpp.o \
    $(OUT_DIR)/color.cpp.o \
	$(OUT_DIR)/deserializer.cpp.o \
	$(OUT_DIR)/drawing.cpp.o \
	$(OUT_DIR)/eventemitter.cpp.o \
    $(OUT_DIR)/eventmanager.cpp.o \
	$(OUT_DIR)/font-impl.cpp.o \
	$(OUT_DIR)/font-fallback.cpp.o \
	$(OUT_DIR)/graphics-manager.cpp.o \
    $(OUT_DIR)/graphics-opengl.cpp.o \
	$(OUT_DIR)/image-opengl.cpp.o \
	$(OUT_DIR)/imagecache-opengl.cpp.o \
	$(OUT_DIR)/imagecache-opengl-v2.cpp.o \
	$(OUT_DIR)/image.cpp.o \
    $(OUT_DIR)/log.cpp.o \
	$(OUT_DIR)/os.cpp.o \
	$(OUT_DIR)/opengl-state-cache.cpp.o \
	$(OUT_DIR)/pdg-lib.cpp.o \
	$(OUT_DIR)/pdg-main.cpp.o \
	$(OUT_DIR)/polygon.cpp.o \
	$(OUT_DIR)/port-renderer.cpp.o \
    $(OUT_DIR)/resource.cpp.o \
	$(OUT_DIR)/serializer.cpp.o \
	$(OUT_DIR)/sound-emscripten.cpp.o \
	$(OUT_DIR)/spline.cpp.o \
	$(OUT_DIR)/sprite.cpp.o \
    $(OUT_DIR)/spritelayer.cpp.o \
	$(OUT_DIR)/spritemanager.cpp.o \
	$(OUT_DIR)/textcache-opengl.cpp.o \
    $(OUT_DIR)/tilelayer.cpp.o \
	$(OUT_DIR)/timermanager.cpp.o \
	$(OUT_DIR)/userdata.cpp.o \
	$(OUT_DIR)/chipmunk.c.o \
	$(OUT_DIR)/cpArbiter.c.o \
	$(OUT_DIR)/cpArray.c.o \
	$(OUT_DIR)/cpBBTree.c.o \
	$(OUT_DIR)/cpBody.c.o \
	$(OUT_DIR)/cpCollision.c.o \
	$(OUT_DIR)/cpConstraint.c.o \
	$(OUT_DIR)/cpDampedRotarySpring.c.o \
	$(OUT_DIR)/cpDampedSpring.c.o \
	$(OUT_DIR)/cpGearJoint.c.o \
	$(OUT_DIR)/cpGrooveJoint.c.o \
	$(OUT_DIR)/cpHashSet.c.o \
	$(OUT_DIR)/cpMarch.c.o \
	$(OUT_DIR)/cpPinJoint.c.o \
	$(OUT_DIR)/cpPivotJoint.c.o \
	$(OUT_DIR)/cpPolyline.c.o \
	$(OUT_DIR)/cpPolyShape.c.o \
	$(OUT_DIR)/cpRatchetJoint.c.o \
	$(OUT_DIR)/cpRotaryLimitJoint.c.o \
	$(OUT_DIR)/cpShape.c.o \
	$(OUT_DIR)/cpSimpleMotor.c.o \
	$(OUT_DIR)/cpSlideJoint.c.o \
	$(OUT_DIR)/cpSpace.c.o \
	$(OUT_DIR)/cpSpaceComponent.c.o \
	$(OUT_DIR)/cpSpaceHash.c.o \
	$(OUT_DIR)/cpSpaceQuery.c.o \
	$(OUT_DIR)/cpSpaceStep.c.o \
	$(OUT_DIR)/cpSpatialIndex.c.o \
	$(OUT_DIR)/cpSweep1D.c.o \
	$(OUT_DIR)/libtess2-bucketalloc.c.o \
	$(OUT_DIR)/libtess2-dict.c.o \
	$(OUT_DIR)/libtess2-geom.c.o \
	$(OUT_DIR)/libtess2-mesh.c.o \
	$(OUT_DIR)/libtess2-priorityq.c.o \
	$(OUT_DIR)/libtess2-sweep.c.o \
	$(OUT_DIR)/libtess2-tess.c.o \
    $(OUT_DIR)/unzip.c.o \
    $(OUT_DIR)/ioapi.c.o \
	$(OUT_DIR)/image-png.cpp.o \
	$(OUT_DIR)/image-jpeg.cpp.o \
	$(OUT_DIR)/glues_quad.c.o \
	$(OUT_DIR)/graphics-emscripten.cpp.o \
	$(OUT_DIR)/platform-graphics-glfw.cpp.o \
	$(OUT_DIR)/platform-events-glfw.cpp.o \
	$(OUT_DIR)/config-unix.cpp.o \
	$(OUT_DIR)/platform-unix.cpp.o \
	$(OUT_DIR)/os-unix.cpp.o

OBJS += $(SPRITER_ENGINE_OBJS) \
	$(OUT_DIR)/tinyxml2.cpp.o \
	$(OUT_DIR)/pugixml.cpp.o \
	$(SPRITER_OVERRIDE_OBJS) \
	$(PDG_SPRITER_OBJS)

$(OUT_DIR):
	@mkdir -p $@

$(OBJS): | $(OUT_DIR)


#bindings: $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
#	@echo  'Creating JavaScript bindings for C++ objects...'
#	@$(CXX) --bind $(CXXFLAGS) -o $(SRC_BINDINGS_DIR)/pdg_em_bindings.js $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
#	-@ls -l $(SRC_BINDINGS_DIR)/bindings.*
#	@echo Done.


# $(ADDITIONAL_JS_FILES) -s EXPORTED_FUNCTIONS=$(EXPORTS)
#	-@rm parser.out WebIDLGrammar.pkl 
libpdg: $(OBJS) \
	$(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp \
	$(SRC_BINDINGS_DIR)/pdg.embind \
	$(SRC_BINDINGS_DIR)/platform-emscripten.js \
	$(SRC_BINDINGS_DIR)/pdg_emscripten.js \
	$(SRC_BINDINGS_JAVASCRIPT_DIR)/pdg.js
	@echo  'Linking libpdg...'
	@mkdir -p $(WASM_OUT_DIR)
	@$(CXX) --bind $(CXXFLAGS) $(ADDITIONAL_JS_FILES) -o $(WASM_OUT_DIR)/libpdg.js $(OBJS) $(LIBS) $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
	@echo Done.


# this C++ file contains the actual bindings spec
$(OUT_DIR)/pdg_em_bindings.cpp.o: $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp $(SRC_BINDINGS_DIR)/pdg_em_adaptors.h
	@echo  'Compiling pdg_em_bindings.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg_em_bindings.cpp.o -c $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp

# this C++ file contains all the code that adapts between the JavaScript and C++ classes, which
# do not always have identical method signatures
$(OUT_DIR)/pdg_em_adaptors.cpp.o: $(SRC_BINDINGS_DIR)/pdg_em_adaptors.cpp $(SRC_BINDINGS_DIR)/pdg_em_adaptors.h
	@echo  'Compiling pdg_em_adaptors.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg_em_adaptors.cpp.o -c $(SRC_BINDINGS_DIR)/pdg_em_adaptors.cpp
	

$(OUT_DIR)/ConvertUTF.c.o: $(SRC_SYS_DIR)/ConvertUTF.c
	@echo  'Compiling ConvertUTF.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/ConvertUTF.c.o -c $(SRC_SYS_DIR)/ConvertUTF.c
	

$(OUT_DIR)/stricasecmp.c.o: $(SRC_SYS_DIR)/stricasecmp.c
	@echo  'Compiling stricasecmp.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/stricasecmp.c.o -c $(SRC_SYS_DIR)/stricasecmp.c
	

$(OUT_DIR)/memblock.cpp.o: $(SRC_BINDINGS_JAVASCRIPT_DIR)/memblock.cpp
	@echo  'Compiling memblock.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/memblock.cpp.o -c $(SRC_BINDINGS_JAVASCRIPT_DIR)/memblock.cpp
	

$(OUT_DIR)/animated.cpp.o: $(SRC_SYS_DIR)/animated.cpp
	@echo  'Compiling animated.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/animated.cpp.o -c $(SRC_SYS_DIR)/animated.cpp
	

$(OUT_DIR)/attributes.cpp.o: $(SRC_SYS_DIR)/attributes.cpp
	@echo  'Compiling attributes.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/attributes.cpp.o -c $(SRC_SYS_DIR)/attributes.cpp


$(OUT_DIR)/collisiondetection.cpp.o: $(SRC_SYS_DIR)/collisiondetection.cpp
	@echo  'Compiling collisiondetection.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/collisiondetection.cpp.o -c $(SRC_SYS_DIR)/collisiondetection.cpp
	

$(OUT_DIR)/color.cpp.o: $(SRC_SYS_DIR)/color.cpp
	@echo  'Compiling color.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/color.cpp.o -c $(SRC_SYS_DIR)/color.cpp
	

$(OUT_DIR)/deserializer.cpp.o: $(SRC_SYS_DIR)/deserializer.cpp
	@echo  'Compiling deserializer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/deserializer.cpp.o -c $(SRC_SYS_DIR)/deserializer.cpp
	


$(OUT_DIR)/drawing.cpp.o: $(SRC_SYS_DIR)/drawing.cpp
	@echo  'Compiling drawing.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/drawing.cpp.o -c $(SRC_SYS_DIR)/drawing.cpp


$(OUT_DIR)/eventemitter.cpp.o: $(SRC_SYS_DIR)/eventemitter.cpp
	@echo  'Compiling eventemitter.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/eventemitter.cpp.o -c $(SRC_SYS_DIR)/eventemitter.cpp
	

$(OUT_DIR)/eventmanager.cpp.o: $(SRC_SYS_DIR)/eventmanager.cpp
	@echo  'Compiling eventmanager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/eventmanager.cpp.o -c $(SRC_SYS_DIR)/eventmanager.cpp


$(OUT_DIR)/font-impl.cpp.o: $(SRC_SYS_DIR)/font-impl.cpp
	@echo  'Compiling font-impl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/font-impl.cpp.o -c $(SRC_SYS_DIR)/font-impl.cpp

$(OUT_DIR)/font-fallback.cpp.o: $(SRC_SYS_DIR)/font-fallback.cpp
	@echo  'Compiling font-fallback.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/font-fallback.cpp.o -c $(SRC_SYS_DIR)/font-fallback.cpp

$(OUT_DIR)/graphics-manager.cpp.o: $(SRC_SYS_DIR)/graphics-manager.cpp
	@echo  'Compiling graphics-manager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/graphics-manager.cpp.o -c $(SRC_SYS_DIR)/graphics-manager.cpp

$(OUT_DIR)/graphics-opengl.cpp.o: $(SRC_SYS_DIR)/graphics-opengl.cpp
	@echo  'Compiling graphics-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/graphics-opengl.cpp.o -c $(SRC_SYS_DIR)/graphics-opengl.cpp

$(OUT_DIR)/image-opengl.cpp.o: $(SRC_SYS_DIR)/image-opengl.cpp
	@echo  'Compiling image-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/image-opengl.cpp.o -c $(SRC_SYS_DIR)/image-opengl.cpp

$(OUT_DIR)/imagecache-opengl.cpp.o: $(SRC_SYS_DIR)/imagecache-opengl.cpp
	@echo  'Compiling imagecache-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/imagecache-opengl.cpp.o -c $(SRC_SYS_DIR)/imagecache-opengl.cpp

$(OUT_DIR)/imagecache-opengl-v2.cpp.o: $(SRC_SYS_DIR)/imagecache-opengl-v2.cpp
	@echo  'Compiling imagecache-opengl-v2.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/imagecache-opengl-v2.cpp.o -c $(SRC_SYS_DIR)/imagecache-opengl-v2.cpp

$(OUT_DIR)/image-png.cpp.o: $(SRC_SYS_DIR)/image-png.cpp
	@echo  'Compiling image-png.cpp...'
	@$(CXX) $(CXXFLAGS) -include $(PDG_ROOT)/deps/png/scripts/pnglibconf.h.prebuilt -o $(OUT_DIR)/image-png.cpp.o -c $(SRC_SYS_DIR)/image-png.cpp

$(OUT_DIR)/image-jpeg.cpp.o: $(SRC_SYS_DIR)/image-jpeg.cpp
	@echo  'Compiling image-jpeg.cpp...'
	@$(CXX) $(CXXFLAGS) -s USE_LIBJPEG=1 -o $(OUT_DIR)/image-jpeg.cpp.o -c $(SRC_SYS_DIR)/image-jpeg.cpp

$(OUT_DIR)/glues_quad.c.o: $(SRC_SYS_DIR)/gles/glues_quad.c
	@echo  'Compiling glues_quad.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/glues_quad.c.o -c $(SRC_SYS_DIR)/gles/glues_quad.c

$(OUT_DIR)/graphics-emscripten.cpp.o: $(SRC_SYS_DIR)/emscripten/graphics-emscripten.cpp
	@echo  'Compiling graphics-emscripten.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/graphics-emscripten.cpp.o -c $(SRC_SYS_DIR)/emscripten/graphics-emscripten.cpp

$(OUT_DIR)/sound-emscripten.cpp.o: $(SRC_SYS_DIR)/emscripten/sound-emscripten.cpp
	@echo  'Compiling sound-emscripten.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/sound-emscripten.cpp.o -c $(SRC_SYS_DIR)/emscripten/sound-emscripten.cpp

$(OUT_DIR)/platform-graphics-glfw.cpp.o: $(SRC_SYS_DIR)/glfw/platform-graphics-glfw.cpp
	@echo  'Compiling platform-graphics-glfw.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/platform-graphics-glfw.cpp.o -c $(SRC_SYS_DIR)/glfw/platform-graphics-glfw.cpp

$(OUT_DIR)/platform-events-glfw.cpp.o: $(SRC_SYS_DIR)/glfw/platform-events-glfw.cpp
	@echo  'Compiling platform-events-glfw.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/platform-events-glfw.cpp.o -c $(SRC_SYS_DIR)/glfw/platform-events-glfw.cpp

$(OUT_DIR)/spriterengine/%.cpp.o: $(SRC_SPRITERPLUSPLUS_DIR)/spriterengine/%.cpp
	@echo  'Compiling SpriterPlusPlus $*.cpp...'
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -Wno-overloaded-virtual -o $@ -c $<

$(OUT_DIR)/tinyxml2.cpp.o: $(SRC_SPRITERPLUSPLUS_DIR)/tinyxml2/tinyxml2.cpp
	@echo  'Compiling tinyxml2.cpp...'
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUT_DIR)/pugixml.cpp.o: $(SRC_SPRITERPLUSPLUS_DIR)/pugixml/pugixml.cpp
	@echo  'Compiling pugixml.cpp...'
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUT_DIR)/spriter-override/%.cpp.o: $(SRC_SPRITERPLUSPLUS_DIR)/example/override/%.cpp
	@echo  'Compiling Spriter override $*.cpp...'
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -Wno-overloaded-virtual -o $@ -c $<

$(OUT_DIR)/pdg-spriter/%.cpp.o: $(SRC_SYS_DIR)/spriter/%.cpp
	@echo  'Compiling PDG Spriter $*.cpp...'
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -Wno-overloaded-virtual -o $@ -c $<
	

$(OUT_DIR)/image.cpp.o: $(SRC_SYS_DIR)/image.cpp
	@echo  'Compiling image.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/image.cpp.o -c $(SRC_SYS_DIR)/image.cpp
	

$(OUT_DIR)/log.cpp.o: $(SRC_SYS_DIR)/log.cpp
	@echo  'Compiling log.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/log.cpp.o -c $(SRC_SYS_DIR)/log.cpp
	

$(OUT_DIR)/network-posix.cpp.o: $(SRC_SYS_DIR)/network-posix.cpp
	@echo  'Compiling network-posix.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/network-posix.cpp.o -c $(SRC_SYS_DIR)/network-posix.cpp
	

$(OUT_DIR)/os.cpp.o: $(SRC_SYS_DIR)/os.cpp
	@echo  'Compiling os.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/os.cpp.o -c $(SRC_SYS_DIR)/os.cpp
	

$(OUT_DIR)/opengl-state-cache.cpp.o: $(SRC_SYS_DIR)/opengl-state-cache.cpp
	@echo  'Compiling opengl-state-cache.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/opengl-state-cache.cpp.o -c $(SRC_SYS_DIR)/opengl-state-cache.cpp

$(OUT_DIR)/pdg-lib.cpp.o: $(SRC_SYS_DIR)/pdg-lib.cpp
	@echo  'Compiling pdg-lib.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg-lib.cpp.o -c $(SRC_SYS_DIR)/pdg-lib.cpp
	

$(OUT_DIR)/pdg-main.cpp.o: $(SRC_SYS_DIR)/pdg-main.cpp
	@echo  'Compiling pdg-main.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg-main.cpp.o -c $(SRC_SYS_DIR)/pdg-main.cpp
	

$(OUT_DIR)/polygon.cpp.o: $(SRC_SYS_DIR)/polygon.cpp
	@echo  'Compiling polygon.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/polygon.cpp.o -c $(SRC_SYS_DIR)/polygon.cpp


$(OUT_DIR)/port-renderer.cpp.o: $(SRC_SYS_DIR)/port-renderer.cpp
	@echo  'Compiling port-renderer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/port-renderer.cpp.o -c $(SRC_SYS_DIR)/port-renderer.cpp


$(OUT_DIR)/resource.cpp.o: $(SRC_SYS_DIR)/resource.cpp
	@echo  'Compiling resource.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/resource.cpp.o -c $(SRC_SYS_DIR)/resource.cpp
	

$(OUT_DIR)/serializer.cpp.o: $(SRC_SYS_DIR)/serializer.cpp
	@echo  'Compiling serializer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/serializer.cpp.o -c $(SRC_SYS_DIR)/serializer.cpp
	

$(OUT_DIR)/spline.cpp.o: $(SRC_SYS_DIR)/spline.cpp
	@echo  'Compiling spline.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/spline.cpp.o -c $(SRC_SYS_DIR)/spline.cpp


$(OUT_DIR)/sprite.cpp.o: $(SRC_SYS_DIR)/sprite.cpp
	@echo  'Compiling sprite.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/sprite.cpp.o -c $(SRC_SYS_DIR)/sprite.cpp
	

$(OUT_DIR)/spritelayer.cpp.o: $(SRC_SYS_DIR)/spritelayer.cpp
	@echo  'Compiling spritelayer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/spritelayer.cpp.o -c $(SRC_SYS_DIR)/spritelayer.cpp
	

$(OUT_DIR)/spritemanager.cpp.o: $(SRC_SYS_DIR)/spritemanager.cpp
	@echo  'Compiling spritemanager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/spritemanager.cpp.o -c $(SRC_SYS_DIR)/spritemanager.cpp
	

$(OUT_DIR)/textcache-opengl.cpp.o: $(SRC_SYS_DIR)/textcache-opengl.cpp
	@echo  'Compiling textcache-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/textcache-opengl.cpp.o -c $(SRC_SYS_DIR)/textcache-opengl.cpp
	

$(OUT_DIR)/tilelayer.cpp.o: $(SRC_SYS_DIR)/tilelayer.cpp
	@echo  'Compiling tilelayer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/tilelayer.cpp.o -c $(SRC_SYS_DIR)/tilelayer.cpp
	

$(OUT_DIR)/timermanager.cpp.o: $(SRC_SYS_DIR)/timermanager.cpp
	@echo  'Compiling timermanager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/timermanager.cpp.o -c $(SRC_SYS_DIR)/timermanager.cpp
	

$(OUT_DIR)/userdata.cpp.o: $(SRC_SYS_DIR)/userdata.cpp
	@echo  'Compiling userdata.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/userdata.cpp.o -c $(SRC_SYS_DIR)/userdata.cpp
	

$(OUT_DIR)/chipmunk.c.o: $(SRC_CHIPMUNK_DIR)/chipmunk.c
	@echo  'Compiling chipmunk.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/chipmunk.c.o -c $(SRC_CHIPMUNK_DIR)/chipmunk.c
	

$(OUT_DIR)/cpArbiter.c.o: $(SRC_CHIPMUNK_DIR)/cpArbiter.c
	@echo  'Compiling cpArbiter.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpArbiter.c.o -c $(SRC_CHIPMUNK_DIR)/cpArbiter.c
	

$(OUT_DIR)/cpArray.c.o: $(SRC_CHIPMUNK_DIR)/cpArray.c
	@echo  'Compiling cpArray.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpArray.c.o -c $(SRC_CHIPMUNK_DIR)/cpArray.c
	

$(OUT_DIR)/cpBBTree.c.o: $(SRC_CHIPMUNK_DIR)/cpBBTree.c
	@echo  'Compiling cpBBTree.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpBBTree.c.o -c $(SRC_CHIPMUNK_DIR)/cpBBTree.c
	

$(OUT_DIR)/cpBody.c.o: $(SRC_CHIPMUNK_DIR)/cpBody.c
	@echo  'Compiling cpBody.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpBody.c.o -c $(SRC_CHIPMUNK_DIR)/cpBody.c
	

$(OUT_DIR)/cpCollision.c.o: $(SRC_CHIPMUNK_DIR)/cpCollision.c
	@echo  'Compiling cpCollision.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpCollision.c.o -c $(SRC_CHIPMUNK_DIR)/cpCollision.c
	

$(OUT_DIR)/cpConstraint.c.o: $(SRC_CHIPMUNK_DIR)/cpConstraint.c
	@echo  'Compiling cpConstraint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpConstraint.c.o -c $(SRC_CHIPMUNK_DIR)/cpConstraint.c
	

$(OUT_DIR)/cpDampedRotarySpring.c.o: $(SRC_CHIPMUNK_DIR)/cpDampedRotarySpring.c
	@echo  'Compiling cpDampedRotarySpring.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpDampedRotarySpring.c.o -c $(SRC_CHIPMUNK_DIR)/cpDampedRotarySpring.c
	

$(OUT_DIR)/cpDampedSpring.c.o: $(SRC_CHIPMUNK_DIR)/cpDampedSpring.c
	@echo  'Compiling cpDampedSpring.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpDampedSpring.c.o -c $(SRC_CHIPMUNK_DIR)/cpDampedSpring.c
	

$(OUT_DIR)/cpGearJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpGearJoint.c
	@echo  'Compiling cpGearJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpGearJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpGearJoint.c
	

$(OUT_DIR)/cpGrooveJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpGrooveJoint.c
	@echo  'Compiling cpGrooveJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpGrooveJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpGrooveJoint.c
	

$(OUT_DIR)/cpHashSet.c.o: $(SRC_CHIPMUNK_DIR)/cpHashSet.c
	@echo  'Compiling cpHashSet.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpHashSet.c.o -c $(SRC_CHIPMUNK_DIR)/cpHashSet.c
	

$(OUT_DIR)/cpHastySpace.c.o: $(SRC_CHIPMUNK_DIR)/cpHastySpace.c
	@echo  'Compiling cpHastySpace.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpHastySpace.c.o -c $(SRC_CHIPMUNK_DIR)/cpHastySpace.c
	

$(OUT_DIR)/cpMarch.c.o: $(SRC_CHIPMUNK_DIR)/cpMarch.c
	@echo  'Compiling cpMarch.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpMarch.c.o -c $(SRC_CHIPMUNK_DIR)/cpMarch.c
	

$(OUT_DIR)/cpPinJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpPinJoint.c
	@echo  'Compiling cpPinJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpPinJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpPinJoint.c
	

$(OUT_DIR)/cpPivotJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpPivotJoint.c
	@echo  'Compiling cpPivotJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpPivotJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpPivotJoint.c
	

$(OUT_DIR)/cpPolyline.c.o: $(SRC_CHIPMUNK_DIR)/cpPolyline.c
	@echo  'Compiling cpPolyline.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpPolyline.c.o -c $(SRC_CHIPMUNK_DIR)/cpPolyline.c
	

$(OUT_DIR)/cpPolyShape.c.o: $(SRC_CHIPMUNK_DIR)/cpPolyShape.c
	@echo  'Compiling cpPolyShape.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpPolyShape.c.o -c $(SRC_CHIPMUNK_DIR)/cpPolyShape.c
	

$(OUT_DIR)/cpRatchetJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpRatchetJoint.c
	@echo  'Compiling cpRatchetJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpRatchetJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpRatchetJoint.c
	

$(OUT_DIR)/cpRotaryLimitJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpRotaryLimitJoint.c
	@echo  'Compiling cpRotaryLimitJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpRotaryLimitJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpRotaryLimitJoint.c
	

$(OUT_DIR)/cpShape.c.o: $(SRC_CHIPMUNK_DIR)/cpShape.c
	@echo  'Compiling cpShape.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpShape.c.o -c $(SRC_CHIPMUNK_DIR)/cpShape.c
	

$(OUT_DIR)/cpSimpleMotor.c.o: $(SRC_CHIPMUNK_DIR)/cpSimpleMotor.c
	@echo  'Compiling cpSimpleMotor.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSimpleMotor.c.o -c $(SRC_CHIPMUNK_DIR)/cpSimpleMotor.c
	

$(OUT_DIR)/cpSlideJoint.c.o: $(SRC_CHIPMUNK_DIR)/cpSlideJoint.c
	@echo  'Compiling cpSlideJoint.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSlideJoint.c.o -c $(SRC_CHIPMUNK_DIR)/cpSlideJoint.c
	

$(OUT_DIR)/cpSpace.c.o: $(SRC_CHIPMUNK_DIR)/cpSpace.c
	@echo  'Compiling cpSpace.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpace.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpace.c
	

$(OUT_DIR)/cpSpaceComponent.c.o: $(SRC_CHIPMUNK_DIR)/cpSpaceComponent.c
	@echo  'Compiling cpSpaceComponent.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpaceComponent.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpaceComponent.c
	

$(OUT_DIR)/cpSpaceHash.c.o: $(SRC_CHIPMUNK_DIR)/cpSpaceHash.c
	@echo  'Compiling cpSpaceHash.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpaceHash.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpaceHash.c
	

$(OUT_DIR)/cpSpaceQuery.c.o: $(SRC_CHIPMUNK_DIR)/cpSpaceQuery.c
	@echo  'Compiling cpSpaceQuery.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpaceQuery.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpaceQuery.c
	

$(OUT_DIR)/cpSpaceStep.c.o: $(SRC_CHIPMUNK_DIR)/cpSpaceStep.c
	@echo  'Compiling cpSpaceStep.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpaceStep.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpaceStep.c
	

$(OUT_DIR)/cpSpatialIndex.c.o: $(SRC_CHIPMUNK_DIR)/cpSpatialIndex.c
	@echo  'Compiling cpSpatialIndex.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSpatialIndex.c.o -c $(SRC_CHIPMUNK_DIR)/cpSpatialIndex.c
	

$(OUT_DIR)/cpSweep1D.c.o: $(SRC_CHIPMUNK_DIR)/cpSweep1D.c
	@echo  'Compiling cpSweep1D.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/cpSweep1D.c.o -c $(SRC_CHIPMUNK_DIR)/cpSweep1D.c
	

$(OUT_DIR)/libtess2-%.c.o: $(PDG_ROOT)/deps/libtess2/Source/%.c
	@echo  'Compiling libtess2 $*.c...'
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OUT_DIR)/unzip.c.o: $(SRC_MINIZIP_DIR)/unzip.c
	@echo  'Compiling unzip.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/unzip.c.o -c $(SRC_MINIZIP_DIR)/unzip.c
	

$(OUT_DIR)/ioapi.c.o: $(SRC_MINIZIP_DIR)/ioapi.c
	@echo  'Compiling ioapi.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/ioapi.c.o -c $(SRC_MINIZIP_DIR)/ioapi.c
		
	
$(OUT_DIR)/image-unix.cpp.o: $(SRC_UNIX_DIR)/image-unix.cpp
	@echo  'Compiling image-unix.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/image-unix.cpp.o -c $(SRC_UNIX_DIR)/image-unix.cpp
	

$(OUT_DIR)/config-unix.cpp.o: $(SRC_UNIX_DIR)/config-unix.cpp
	@echo  'Compiling config-unix.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/config-unix.cpp.o -c $(SRC_UNIX_DIR)/config-unix.cpp
	

$(OUT_DIR)/platform-unix.cpp.o: $(SRC_UNIX_DIR)/platform-unix.cpp
	@echo  'Compiling platform-unix.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/platform-unix.cpp.o -c $(SRC_UNIX_DIR)/platform-unix.cpp
	

$(OUT_DIR)/os-unix.cpp.o: $(SRC_UNIX_DIR)/os-unix.cpp
	@echo  'Compiling os-unix.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/os-unix.cpp.o -c $(SRC_UNIX_DIR)/os-unix.cpp
	



.PHONY: clean
clean:
	@echo  'Removing all temporary binaries...'
	@rm -f $(WASM_OUT_DIR)/libpdg.js $(WASM_OUT_DIR)/libpdg.wasm $(WASM_OUT_DIR)/libpdg.data $(WASM_OUT_DIR)/libpdg.wasm.map $(WASM_OUT_DIR)/libpdg.js.map $(WASM_OUT_DIR)/libpdg.html $(WASM_OUT_DIR)/libpdg.map parser.out WebIDLGrammar.pkl $(OUT_DIR)/*.o
	
