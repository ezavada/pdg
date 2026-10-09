// -----------------------------------------------
// image.cpp
//
// Implementation file for Image bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "graphics_impl_macros.h"
#include "../data/data_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
// @pdg-member {"name":"Image.getImageBounds","native_binding":{"adapter":"image.bounds-at","binding_name":"_getImageBoundsAt","browser":{"generate":false}}}
    
// ========================================================================================
//MARK: Image
// ========================================================================================


BINDING_INITIALIZER_IMPL(Image)
    EXPORT_CLASS_SYMBOLS("Image", Image, , ,
    	// method section
    	HAS_IMAGE_METHODS(Image)
        HAS_SERIALIZABLE_METHODS(Image)
    );
	END

IMAGE_BASE_CLASS_IMPL(Image)
SERIALIZABLE_BASE_CLASS_IMPL(Image)

CLEANUP_IMPL(Image)

/* @pdg-member
{
  "name": "Image.Image",
  "type": "constructor",
  "native": true,
  "brief": "load an image file or create a snapshot or live image of an offscreen port",
  "returns": "object Image",
  "params": [
    [
      {
        "name": "filename",
        "type": "string"
      }
    ],
    [
      {
        "name": "port",
        "type": "object Port"
      },
      {
        "name": "copyPixels",
        "type": "boolean",
        "optional": true,
        "default_value": "CopyPixels"
      }
    ]
  ]
}
*/
CPP_MANAGED_CONSTRUCTOR_IMPL(Image)
	SETUP_NON_SCRIPT_CALL;
	if (ARGC < 1) {
		return 0;
	} else if (HAVE_ONLY_ONE_NULL_ARG) {
		return Image::createEmptyImageForIntrospection();
	} else if (!VALUE_IS_STRING(ARGV[0])) {
		SAVE_SYNTAX_ERR("argument 1 must be a string (filename)");
		return 0;
	} else {
		VALUE_TO_CSTRING(filename, ARGV[0]);
		Image* img = Image::createImageFromFile(filename);
		if (!img) {
		    SAVE_ERR("could not create Image from file ["<<filename<<"]");
		    return 0;
		} else {
		    return img;
		}
	}
	END


// ========================================================================================
//MARK: ImageStrip
// ========================================================================================

BINDING_INITIALIZER_IMPL(ImageStrip)
    EXPORT_CLASS_SYMBOLS("ImageStrip", ImageStrip, , ,
    	// method section
		HAS_IMAGE_METHODS(ImageStrip)
        HAS_SERIALIZABLE_METHODS(ImageStrip)
		HAS_GETTER(ImageStrip, Frame)
		HAS_PROPERTY(ImageStrip, FrameWidth)
		HAS_PROPERTY(ImageStrip, NumFrames)
    );
	END
IMAGE_BASE_CLASS_IMPL(ImageStrip)
SERIALIZABLE_BASE_CLASS_IMPL(ImageStrip)
PROPERTY_IMPL(ImageStrip, NumFrames, INT32)
PROPERTY_IMPL(ImageStrip, FrameWidth, INT32)
METHOD_IMPL(ImageStrip, GetFrame)
	METHOD_SIGNATURE("get image that is a single frame of this multi-frame image",
		[object Image*], 1, ([number int] frameNum));
    REQUIRE_ARG_COUNT(1);
	REQUIRE_INT32_ARG(1, frameNum);
	Image* image = self->getFrame(frameNum);
	RETURN_CPP_OBJECT(image, Image);
	END

CLEANUP_IMPL(ImageStrip)


CPP_MANAGED_CONSTRUCTOR_IMPL(ImageStrip)
	SETUP_NON_SCRIPT_CALL;
	if (ARGC < 1) {
		return 0;
	} else if (HAVE_ONLY_ONE_NULL_ARG) {
		return ImageStrip::createEmptyImageStripForIntrospection();
	} else if (!VALUE_IS_STRING(ARGV[0])) {
		SAVE_SYNTAX_ERR("argument 1 must be a string (filename)");
		return 0;
	} else {
		VALUE_TO_CSTRING(filename, ARGV[0]);
		ImageStrip* img = ImageStrip::createImageStripFromFile(filename);
		if (!img) {
		    SAVE_ERR("could not create ImageStrip from file ["<<filename<<"]");
		    return 0;
		} else {
		    return img;
		}
	}
	END


} // pdg namespace

/* @pdg-member
{
  "name": "ImageStrip.ImageStrip",
  "type": "constructor",
  "params": [
    {
      "name": "filename",
      "type": "string"
    }
  ],
  "returns": "object ImageStrip",
  "brief": "Load an image strip from a file."
}
*/

// @pdg-member {"name":"Image.getOpacity","native_binding":{"binding_name":"_getOpacity"}}


// @pdg-member {"name":"Image.getAlphaValue","native_binding":{"binding_name":"_getAlphaValue"}}

// @pdg-member {"name":"ImageStrip.getFrame","native_binding":{"allow_raw_pointers":true}}

// @pdg-class {"name":"ImageStrip","native_binding":{"browser":{"generate":true,"base":"pdg::Image","constructors":[{"factory":"pdg::emscriptenCreateImageStrip","allow_raw_pointers":true}]}}}
