#
# Makefile for 'libpdg.so'.
#
# Type 'make' or 'make libpdg.so' to create the binary.
# Type 'make clean' or 'make clear' to delete all temporaries.
#

# build target specs

# first target entry is the target invoked when typing 'make'
.PHONY: all
all: libpdg


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
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/ \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/tinyxml2 \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/pugixml \
	-I$(PDG_ROOT)/deps/SpriterPlusPlus/nlohmann-json

DEFINES := \
	'-DDEBUG' \
	'-DPDG_DEBUG_OUT_TO_LOG' \
	'-DPDG_USE_CHIPMUNK_PHYSICS' \
	'-DPDG_SPRITER_SUPPORT' \
	'-DPDG_NO_GUI' \
	'-DPDG_NO_SOUND' \
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
    -s USE_ZLIB=1


CFLAGS_ALL=-gsource-map -Wno-warn-absolute-paths -DMOZZCONF_H $(DEFINES) $(INCLUDES)

CFLAGS=$(CFLAGS_ALL)
CXXFLAGS=$(CFLAGS_ALL)

OUT_DIR=$(PDG_ROOT)/build/js/pdg
SRC_SYS_DIR=$(PDG_ROOT)/src/sys
SRC_CHIPMUNK_DIR=$(PDG_ROOT)/deps/chipmunk/src
SRC_MINIZIP_DIR=$(PDG_ROOT)/deps/node/deps/zlib/contrib/minizip
SRC_SPRITERPLUSPLUS_DIR=$(PDG_ROOT)/deps/SpriterPlusPlus
SRC_UNIX_DIR=$(PDG_ROOT)/src/sys/unix
SRC_BINDINGS_DIR=$(PDG_ROOT)/src/bindings/emscripten
SRC_BINDINGS_JAVASCRIPT_DIR=$(PDG_ROOT)/src/bindings/javascript
SRC_JS_DIR=$(PDG_ROOT)/src/js


ADDITIONAL_JS_FILES= \
    --embed-file $(SRC_JS_DIR)/dump.js@/js_modules/dump.js \
    --embed-file $(SRC_JS_DIR)/pdg-defs.js@/js_modules/pdg-defs.js \
    --embed-file $(SRC_JS_DIR)/classify.js@/js_modules/classify.js \
    --post-js $(SRC_JS_DIR)/require.js \
    --post-js $(SRC_BINDINGS_DIR)/pdg_emscripten.js \
    --post-js $(SRC_BINDINGS_DIR)/../javascript/pdg.js



OBJS= \
    $(OUT_DIR)/pdg_em_adaptors.cpp.o \
    $(OUT_DIR)/ConvertUTF.c.o \
	$(OUT_DIR)/memblock.cpp.o \
	$(OUT_DIR)/animated.cpp.o \
	$(OUT_DIR)/collisiondetection.cpp.o \
    $(OUT_DIR)/color.cpp.o \
	$(OUT_DIR)/deserializer.cpp.o \
	$(OUT_DIR)/eventemitter.cpp.o \
    $(OUT_DIR)/eventmanager.cpp.o \
	$(OUT_DIR)/font-impl.cpp.o \
	$(OUT_DIR)/graphics-manager.cpp.o \
    $(OUT_DIR)/graphics-opengl.cpp.o \
	$(OUT_DIR)/image-opengl.cpp.o \
	$(OUT_DIR)/image.cpp.o \
    $(OUT_DIR)/log.cpp.o \
	$(OUT_DIR)/os.cpp.o \
	$(OUT_DIR)/pdg-lib.cpp.o \
	$(OUT_DIR)/pdg-main.cpp.o \
    $(OUT_DIR)/resource.cpp.o \
	$(OUT_DIR)/serializer.cpp.o \
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
	$(OUT_DIR)/cpHastySpace.c.o \
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
    $(OUT_DIR)/unzip.c.o \
    $(OUT_DIR)/ioapi.c.o \
	$(OUT_DIR)/spriterengine_combined.o \
	$(OUT_DIR)/image-unix.cpp.o \
	$(OUT_DIR)/config-unix.cpp.o \
	$(OUT_DIR)/platform-unix.cpp.o \
	$(OUT_DIR)/os-unix.cpp.o


#bindings: $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
#	@echo  'Creating JavaScript bindings for C++ objects...'
#	@$(CXX) --bind $(CXXFLAGS) -o $(SRC_BINDINGS_DIR)/pdg_em_bindings.js $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
#	-@ls -l $(SRC_BINDINGS_DIR)/bindings.*
#	@echo Done.


# $(ADDITIONAL_JS_FILES) -s EXPORTED_FUNCTIONS=$(EXPORTS)
#	-@rm parser.out WebIDLGrammar.pkl 
libpdg: $(OBJS)
	@echo  'Linking libpdg...'
	@$(CC) --bind $(CFLAGS) $(ADDITIONAL_JS_FILES) -o $(PDG_ROOT)/libpdg.js $(OBJS) $(LIBS) $(SRC_BINDINGS_DIR)/pdg_em_bindings.cpp
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
	

$(OUT_DIR)/collisiondetection.cpp.o: $(SRC_SYS_DIR)/collisiondetection.cpp
	@echo  'Compiling collisiondetection.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/collisiondetection.cpp.o -c $(SRC_SYS_DIR)/collisiondetection.cpp
	

$(OUT_DIR)/color.cpp.o: $(SRC_SYS_DIR)/color.cpp
	@echo  'Compiling color.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/color.cpp.o -c $(SRC_SYS_DIR)/color.cpp
	

$(OUT_DIR)/deserializer.cpp.o: $(SRC_SYS_DIR)/deserializer.cpp
	@echo  'Compiling deserializer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/deserializer.cpp.o -c $(SRC_SYS_DIR)/deserializer.cpp
	

$(OUT_DIR)/eventemitter.cpp.o: $(SRC_SYS_DIR)/eventemitter.cpp
	@echo  'Compiling eventemitter.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/eventemitter.cpp.o -c $(SRC_SYS_DIR)/eventemitter.cpp
	

$(OUT_DIR)/eventmanager.cpp.o: $(SRC_SYS_DIR)/eventmanager.cpp
	@echo  'Compiling eventmanager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/eventmanager.cpp.o -c $(SRC_SYS_DIR)/eventmanager.cpp


$(OUT_DIR)/font-impl.cpp.o: $(SRC_SYS_DIR)/font-impl.cpp
	@echo  'Compiling font-impl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/font-impl.cpp.o -c $(SRC_SYS_DIR)/font-impl.cpp
	

$(OUT_DIR)/graphics-manager.cpp.o: $(SRC_SYS_DIR)/graphics-manager.cpp
	@echo  'Compiling graphics-manager.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/graphics-manager.cpp.o -c $(SRC_SYS_DIR)/graphics-manager.cpp
	

$(OUT_DIR)/graphics-opengl.cpp.o: $(SRC_SYS_DIR)/graphics-opengl.cpp
	@echo  'Compiling graphics-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/graphics-opengl.cpp.o -c $(SRC_SYS_DIR)/graphics-opengl.cpp
	

$(OUT_DIR)/image-opengl.cpp.o: $(SRC_SYS_DIR)/image-opengl.cpp
	@echo  'Compiling image-opengl.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/image-opengl.cpp.o -c $(SRC_SYS_DIR)/image-opengl.cpp
	

$(OUT_DIR)/image-png.cpp.o: $(SRC_SYS_DIR)/image-png.cpp
	@echo  'Compiling image-png.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/image-png.cpp.o -c $(SRC_SYS_DIR)/image-png.cpp
	

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
	

$(OUT_DIR)/pdg-lib.cpp.o: $(SRC_SYS_DIR)/pdg-lib.cpp
	@echo  'Compiling pdg-lib.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg-lib.cpp.o -c $(SRC_SYS_DIR)/pdg-lib.cpp
	

$(OUT_DIR)/pdg-main.cpp.o: $(SRC_SYS_DIR)/pdg-main.cpp
	@echo  'Compiling pdg-main.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/pdg-main.cpp.o -c $(SRC_SYS_DIR)/pdg-main.cpp
	

$(OUT_DIR)/resource.cpp.o: $(SRC_SYS_DIR)/resource.cpp
	@echo  'Compiling resource.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/resource.cpp.o -c $(SRC_SYS_DIR)/resource.cpp
	

$(OUT_DIR)/serializer.cpp.o: $(SRC_SYS_DIR)/serializer.cpp
	@echo  'Compiling serializer.cpp...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/serializer.cpp.o -c $(SRC_SYS_DIR)/serializer.cpp
	

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
	

$(OUT_DIR)/unzip.c.o: $(SRC_MINIZIP_DIR)/unzip.c
	@echo  'Compiling unzip.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/unzip.c.o -c $(SRC_MINIZIP_DIR)/unzip.c
	

$(OUT_DIR)/ioapi.c.o: $(SRC_MINIZIP_DIR)/ioapi.c
	@echo  'Compiling ioapi.c...'
	@$(CC) $(CFLAGS) -o $(OUT_DIR)/ioapi.c.o -c $(SRC_MINIZIP_DIR)/ioapi.c
		
	
# SpriterPlusPlus compilation rules - combined approach
$(OUT_DIR)/spriterengine_combined.o: $(SRC_SPRITERPLUSPLUS_DIR)/spriterengine/spriterengine.h
	@echo  'Compiling SpriterPlusPlus engine (combined)...'
	@$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/spriterengine_combined.o -c $(SRC_SPRITERPLUSPLUS_DIR)/spriterengine/spriterengine.h
	

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
	@rm -f libpdg.js libpdg.html libpdg.map parser.out WebIDLGrammar.pkl $(OUT_DIR)/*.o
	

