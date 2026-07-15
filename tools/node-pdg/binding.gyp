# -----------------------------------------------
# binding.gyp (node.js makefile)
#
# Written by Ed Zavada, 2014
# Copyright (c) 2014, Dream Rock Studios, LLC
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
# NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
# USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# -----------------------------------------------

# -*- mode: python -*-
{

  'variables': {
    'v8_use_snapshot%': 'true',
    'srcdir': '.',
    'blddir': 'build',
    'VERSION': '0.1.0',
    'macosx_min_vers': '10.6',
    'node_version': '<!(node --version)',
    'chipmunk_dir': './deps/chipmunk',
    'scmlpp_dir': './deps/scml-pp',
    'linux_files': [
      'src/sys/glfw/platform-events-glfw.cpp',
      'src/sys/unix/image-unix.cpp',
      'src/sys/unix/config-unix.cpp',
      'src/sys/unix/platform-unix.cpp',
      'src/sys/unix/os-unix.cpp',
      'deps/minizip/mz_os_posix.c',
      'deps/minizip/mz_strm_os_posix.c',
      'deps/minizip/mz_crypt_openssl.c',
    ],
    'macosx_files': [
      'src/sys/macosx/config-macosx.cpp',
      'src/sys/macosx/platform-dirs-macosx.cpp',
      'src/sys/macosx/platform-image-macosx.mm',
      'src/sys/macosx/platform-events-macosx.cpp',
      'src/sys/unix/os-unix.cpp',
      'deps/minizip/mz_os_posix.c',
      'deps/minizip/mz_strm_os_posix.c',
      'deps/minizip/mz_crypt_apple.c',
    ],
    'win32_files': [
      'src/sys/glfw/platform-events-glfw.cpp',
      'src/sys/win32/os-win32.cpp',
      'src/sys/win32/config-win32.cpp',
      'src/sys/win32/platform-win32.cpp',
      'src/sys/win32/crash-handler-win32.cpp',
      'deps/minizip/mz_os_win32.c',
      'deps/minizip/mz_strm_os_win32.c',
      'deps/minizip/mz_crypt_winvista.c',
      'deps/minizip/mz_crypt_winxp.c',
    ],
    'png_files': [
      'src/sys/image-png.cpp',
      'deps/png/png.c',
      'deps/png/pngerror.c',
      'deps/png/pngget.c',
      'deps/png/pngmem.c',
      'deps/png/pngpread.c',
      'deps/png/pngwrite.c',
      'deps/png/pngread.c',
      'deps/png/pngrio.c',
      'deps/png/pngwio.c',
      'deps/png/pngrtran.c',
      'deps/png/pngwtran.c',
      'deps/png/pngrutil.c',
      'deps/png/pngwutil.c',
      'deps/png/pngset.c',
      'deps/png/pngtrans.c',
    ],
  },

  'targets': [
    {
      'target_name': 'pdg',
      'win_delay_load_hook': 'false',
      'include_dirs': [ 
        './src/inc',
        './src/sys', 
        './deps/glfw/include',
        './deps',
        './deps/png',
        './deps/zlib',
        './deps/minizip',
        './deps/glm',
    	'./src/bindings/javascript',
    	'./src/bindings/javascript/v8', 
    	'./src/bindings/generated/v8',
    	'./src/bindings/generated/jsc',
    	'./src/bindings/node', 
    	'./src/sys/unix', 
    	'./src/sys/macosx', 
    	'./src/sys/win32', 
    	'./src/sys/glfw', 
    	'<(chipmunk_dir)/include', 
    	'./deps/SpriterPlusPlus/', 
    	'./deps/SpriterPlusPlus/tinyxml2', 
    	'./deps/SpriterPlusPlus/pugixml', 
    	'./deps/SpriterPlusPlus/nlohmann-json',
    	'./deps/SpriterPlusPlus/example',
      ],
      'libraries': [
      ],
      'defines': [
      	'DEBUG', 
  		#'PDG_DEBUG_SOUND', 
  		'PDG_DEBUG_OUT_TO_LOG', 
  		'PDG_NO_DEBUG_TO_CONSOLE', 
  		#'-DPDG_DEBUG_JAVASCRIPT',
  		'PDG_USE_CHIPMUNK_PHYSICS', 
  		'PDG_SPRITER_SUPPORT',
  		'PDG_NO_GUI',
  		'PDG_NO_SOUND',
  		'PDG_NO_APP_FRAMEWORK',
  		'PDG_NO_NETWORK', 
  		'PDG_LIBRARY', 
  		'PDG_NO_SLEEP',
  		'PDG_INTERNAL_LIB', 
  		'PDG_NODE_MODULE', 
  		'PDG_COMPILING_FOR_JAVASCRIPT',
      ],
      'cflags': [ 
      	'-g',
        '-w' # no warnings
      	#'-Wno-parentheses-equality', # breaks older Gcc
      	#'-O0', 
      	#'-fno-default-inline', 
      	#'-fno-inline',
      ],
      'cflags_c': [ '-std=c99' ],
      'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
      'sources': [
        # extra zip files
        'deps/minizip/compat/unzip.c',
        'deps/minizip/compat/ioapi.c',
        'deps/minizip/compat/zip.c',
        'deps/minizip/mz_zip.c',
        'deps/minizip/mz_zip_rw.c',
        'deps/minizip/mz_os.c',
        'deps/minizip/mz_strm.c',
        'deps/minizip/mz_strm_buf.c',
        'deps/minizip/mz_strm_mem.c',
        'deps/minizip/mz_strm_split.c',
        'deps/minizip/mz_crypt.c',
        # chipmunk physics
        'deps/chipmunk/src/chipmunk.c',
        'deps/chipmunk/src/cpArbiter.c',
        'deps/chipmunk/src/cpArray.c',
        'deps/chipmunk/src/cpBBTree.c',
        'deps/chipmunk/src/cpBody.c',
        'deps/chipmunk/src/cpCollision.c',
        'deps/chipmunk/src/cpConstraint.c',
        'deps/chipmunk/src/cpDampedRotarySpring.c',
        'deps/chipmunk/src/cpDampedSpring.c',
        'deps/chipmunk/src/cpGearJoint.c',
        'deps/chipmunk/src/cpGrooveJoint.c',
        'deps/chipmunk/src/cpHashSet.c',
        'deps/chipmunk/src/cpHastySpace.c',
        'deps/chipmunk/src/cpMarch.c',
        'deps/chipmunk/src/cpPinJoint.c',
        'deps/chipmunk/src/cpPivotJoint.c',
        'deps/chipmunk/src/cpPolyline.c',
        'deps/chipmunk/src/cpPolyShape.c',
        'deps/chipmunk/src/cpRatchetJoint.c',
        'deps/chipmunk/src/cpRotaryLimitJoint.c',
        'deps/chipmunk/src/cpShape.c',
        'deps/chipmunk/src/cpSimpleMotor.c',
        'deps/chipmunk/src/cpSlideJoint.c',
        'deps/chipmunk/src/cpSpace.c',
        'deps/chipmunk/src/cpSpaceComponent.c',
        'deps/chipmunk/src/cpSpaceHash.c',
        'deps/chipmunk/src/cpSpaceQuery.c',
        'deps/chipmunk/src/cpSpaceStep.c',
        'deps/chipmunk/src/cpSpatialIndex.c',
        'deps/chipmunk/src/cpSweep1D.c',
        # SpriterPlusPlus support
        'deps/SpriterPlusPlus/spriterengine/animation/animation.cpp',
        'deps/SpriterPlusPlus/spriterengine/animation/animationinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/animation/mainlinekey.cpp',
        'deps/SpriterPlusPlus/spriterengine/animation/mainlinekeyinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/charactermap/charactermap.cpp',
        'deps/SpriterPlusPlus/spriterengine/charactermap/charactermapinstruction.cpp',
        'deps/SpriterPlusPlus/spriterengine/entity/entityinstancedata.cpp',
        'deps/SpriterPlusPlus/spriterengine/entity/entityinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/entity/entity.cpp',
        'deps/SpriterPlusPlus/spriterengine/entity/object.cpp',
        'deps/SpriterPlusPlus/spriterengine/file/file.cpp',
        'deps/SpriterPlusPlus/spriterengine/file/filereference.cpp',
        'deps/SpriterPlusPlus/spriterengine/global/settings.cpp',
        'deps/SpriterPlusPlus/spriterengine/loading/spriterdocumentloader.cpp',
        'deps/SpriterPlusPlus/spriterengine/loading/loadinghelpers.cpp',
        'deps/SpriterPlusPlus/spriterengine/loading/loader.cpp',
        'deps/SpriterPlusPlus/spriterengine/model/spritermodel.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/angleinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/boneinstanceinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/boneobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/boxinstanceinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/boxobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/entityobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/eventobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/intvariableinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/pointinstanceinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/pointobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/realvariableinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/soundobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/spriteobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/stringvariableinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/stringvariableinforeference.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/taglist.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/tagobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/tagobjectinforeference.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/triggerobjectinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectinfo/universalobjectinterface.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/boneref.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/bonerefinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/entityref.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/entityrefinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/objectref.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/objectrefinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/spriteref.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/spriterefinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/objectref/transformprocessor.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/spriterfiledocumentwrapper.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/soundfile.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/soundobjectinforeference.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/spriterfileelementwrapper.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/atlasfile.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/objectfactory.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/imagefile.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/spriterfileattributewrapper.cpp',
        'deps/SpriterPlusPlus/spriterengine/override/filefactory.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/beziereasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/cubiceasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/easingcurveinterface.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/instanteasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/lineareasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/quadraticeasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/quarticeasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/quinticeasingcurve.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeinfo/timeinfo.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/timeline.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/timelineinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/timelinekey.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/triggertimelineinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/variabletimelineinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/proxytimelinekey.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/soundtimelineinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/timeline/tagtimelineinstance.cpp',
        'deps/SpriterPlusPlus/spriterengine/variable/variableinstancenameandidmap.cpp',
        'deps/SpriterPlusPlus/spriterengine/variable/variablecontainer.cpp',
        'deps/SpriterPlusPlus/spriterengine/variable/variable.cpp',
        'deps/SpriterPlusPlus/tinyxml2/tinyxml2.cpp',
        'deps/SpriterPlusPlus/pugixml/pugixml.cpp',
        'deps/SpriterPlusPlus/example/override/tinyxmlspriterfiledocumentwrapper.cpp',
        'deps/SpriterPlusPlus/example/override/tinyxmlspriterfileelementwrapper.cpp',
        'deps/SpriterPlusPlus/example/override/tinyxmlspriterfileattributewrapper.cpp',
        # core pdg library
        'src/sys/animated.cpp',
        'src/sys/ConvertUTF.c',
        'src/sys/collisiondetection.cpp',
        'src/sys/deserializer.cpp',
        'src/sys/drawing.cpp',
        'src/sys/eventemitter.cpp',
        'src/sys/eventmanager.cpp',
        'src/sys/image.cpp',
        'src/sys/log.cpp',
        'src/sys/os.cpp',
        'src/sys/pdg-lib.cpp',
        'src/sys/pdg-main.cpp',
        'src/sys/resource.cpp',
        'src/sys/serializer.cpp',
        'src/sys/spline.cpp',
        'src/sys/polygon.cpp',
        'src/sys/sprite.cpp',
        'src/sys/spritelayer.cpp',
        'src/sys/spritemanager.cpp',
        'src/sys/tilelayer.cpp',
        'src/sys/spriter/pdg_file_factory.cpp',
        'src/sys/spriter/pdg_object_factory.cpp',
        'src/sys/spriter/pdg_box_instance_info.cpp',
        'src/sys/spriter/pdg_image_file.cpp',
        'src/sys/spriter/pdg_spriter_file_document_wrapper.cpp',
        'src/sys/timermanager.cpp',
        'src/sys/userdata.cpp',
        'src/sys/attributes.cpp',
        # 'src/sys/port-renderer.cpp', # gui only
        # pdg javascript and node bindings
        'src/bindings/javascript/memblock.cpp',
        'src/bindings/javascript/v8/pdg_v8_support.cpp',
        'src/bindings/generated/v8/pdg_script_impl.cpp',
        'src/bindings/generated/v8/pdg_interfaces.cpp',
        'src/bindings/generated/v8/physics/cp_arbiter.cpp',
        'src/bindings/generated/v8/physics/cp_constraint.cpp',
        'src/bindings/generated/v8/physics/cp_space.cpp',
        'src/bindings/generated/v8/core/config_manager.cpp',
        'src/bindings/generated/v8/core/event_manager.cpp',
        'src/bindings/generated/v8/core/log_manager.cpp',
        'src/bindings/generated/v8/core/timer_manager.cpp',
        'src/bindings/generated/v8/data/file_manager.cpp',
        'src/bindings/generated/v8/data/mem_block.cpp',
        'src/bindings/generated/v8/data/resource_manager.cpp',
        'src/bindings/generated/v8/data/serializer.cpp',
        'src/bindings/generated/v8/data/deserializer.cpp',
        'src/bindings/generated/v8/data/serializable.cpp',
        'src/bindings/generated/v8/graphics/attributes.cpp',
        'src/bindings/generated/v8/graphics/graphics_manager.cpp',
        'src/bindings/generated/v8/graphics/image.cpp',
        'src/bindings/generated/v8/graphics/drawing.cpp',
        'src/bindings/generated/v8/graphics/port.cpp',
        'src/bindings/generated/v8/graphics/font.cpp',
        'src/bindings/generated/v8/graphics/spline.cpp',
        'src/bindings/generated/v8/graphics/polygon.cpp',
        'src/bindings/generated/v8/animation/animated.cpp',
        'src/bindings/generated/v8/animation/sprite.cpp',
        'src/bindings/generated/v8/animation/sprite_layer.cpp',
        'src/bindings/generated/v8/animation/tile_layer.cpp',
        'src/bindings/generated/v8/audio/sound_manager.cpp',
        'src/bindings/generated/v8/audio/sound.cpp',
        'src/bindings/node/pdg_node.cpp',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'OTHER_CFLAGS': [
          '-std=c99',
      	  #'-Wno-parentheses-equality', # breaks older gcc (Mac OS X 10.6)
        ],
        'OTHER_CPLUSPLUSFLAGS': [
        ],
        'OTHER_LDFLAGS': [
          #'-macosx-version-min=<@(macosx_min_vers)',  # breaks XCode 5+
        ],
      },
      'conditions': [
         [ 'OS=="linux"', {
             'sources': ['<@(png_files)', '<@(linux_files)'],
             'sources!': ['deps/chipmunk/src/cpHastySpace.c'],
           }
         ],
         [ 'OS=="mac"', {
             'sources': ['<@(macosx_files)'],
             'link_settings': {
                            'libraries': [
                                '$(SDKROOT)/System/Library/Frameworks/CoreFoundation.framework',
                                '$(SDKROOT)/System/Library/Frameworks/AppKit.framework',
                                '$(SDKROOT)/System/Library/Frameworks/Security.framework',
                                 '-lobjc',
                            ]
             },
             #'cflags' doesn't work with gyp on Xcode, have to use OTHER_CFLAGS above
           }
         ],
         [ 'OS=="win"', {
             'defines!': [ '_HAS_EXCEPTIONS=0' ],
             'defines': [ '_HAS_EXCEPTIONS=1' ],
             'msvs_disabled_warnings': [4005, 4018, 4090, 4101, 4530, 4541],
             'configurations': {
               'Debug': {
                 'msvs_settings': {
                   'VCCLCompilerTool': {
                     'ExceptionHandling': 1,
                     'RuntimeTypeInfo': 'true',
                   }
                 }
               },
               'Release': {
                 'msvs_settings': {
                   'VCCLCompilerTool': {
                     'ExceptionHandling': 1,
                     'RuntimeTypeInfo': 'true',
                   }
                 }
               },
             },
             'library_dirs': [
               '<(node_root_dir)/out/$(ConfigurationName)/lib',
             ],
             'libraries': [
               '-lstrmiids.lib',
               '-limm32.lib',
               '-lpsapi.lib',
               '-liphlpapi.lib',
               '-lwinmm.lib',
               '-lws2_32.lib',
               '-lbcrypt.lib',
               '-lncrypt.lib',
               '-lcrypt32.lib',
               '-luserenv.lib',
               '-lv8_libplatform.lib',
             ],
             'msvs_settings': {
               'VCCLCompilerTool': {
                 'ExceptionHandling': 1,
                 'RuntimeTypeInfo': 'true',
                 'WarnAsError': 'false',
                 'AdditionalOptions': ['/WX-'],
               }
             },
             'sources': ['<@(png_files)', '<@(win32_files)'],
           }
         ],
      ],
    },
  ],
}

