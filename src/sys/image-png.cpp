// -----------------------------------------------
// image-png.cpp
//
// implementation of png loading
//
// Written by Ed Zavada, 2004-2012
// Copyright (c) 2012, Dream Rock Studios, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// -----------------------------------------------


#include "pdg_project.h"

#include "internals.h"

#ifndef PDG_NO_GUI
  #include "include-opengl.h"  // for real GL_RGB & GL_RGBA definitions
#else
  #include "image-impl.h"  // for fake GL_RGB & GL_RGBA definitions
#endif
#include "png/png.h"

#include <cstdlib>
#include <cstring>
#include <limits>


extern "C" {
void pdg_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
void pdg_png_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
void pdg_png_flush_data(png_structp png_ptr);
}

#define PNG_SIG_BYTES 8

typedef struct pdg_png_data_t {
	unsigned char* imageData;
	png_size_t imageDataLen;
	png_size_t currOffset;
} pdg_png_data;

namespace pdg {

#ifdef PDG_USE_LIBJPEG
void platform_initJPEGData(unsigned char* imageData, long imageDataLen, unsigned char** outDataPtr,
	long* outWidth, long* outHeight, long* outBufferWidth, long* outBufferHeight,
	long* outBufferPitch, int* outFormat);
#endif

void platform_initImageData(unsigned char* imageData, long imageDataLen, unsigned char** outDataPtr, 
	long* outWidth, long* outHeight, long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, 
	int* outFormat)
{
	*outDataPtr = 0;
	*outWidth = 0;
	*outHeight = 0;
	*outBufferWidth = 0;
	*outBufferHeight = 0;
	*outBufferPitch = 0;
	*outFormat = GL_RGBA;

#ifdef PDG_USE_LIBJPEG
	if (imageDataLen >= 2 && imageData[0] == 0xFF && imageData[1] == 0xD8) {
		platform_initJPEGData(imageData, imageDataLen, outDataPtr, outWidth, outHeight,
			outBufferWidth, outBufferHeight, outBufferPitch, outFormat);
		return;
	}
#endif

	bool is_png = imageDataLen >= PNG_SIG_BYTES && !png_sig_cmp(imageData, 0, PNG_SIG_BYTES);
	if (!is_png) return;

	// create lib png structures
	png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) return;

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return;
	}
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		return;
	}

	// Keep cleanup pointers valid across libpng's longjmp error path.
	png_bytep* volatile row_pointers = nullptr;
	unsigned char* volatile pixels = nullptr;

    // define a block to handle cleanup after an error
	if (setjmp(png_jmpbuf(png_ptr))) {
	    std::free(row_pointers);
	    std::free(pixels);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return;
	}

    // setup an io pointer for reading from memory
	pdg_png_data_t read_data;
	read_data.imageData = imageData;
	read_data.imageDataLen = imageDataLen;
	read_data.currOffset = PNG_SIG_BYTES;

	png_set_read_fn(png_ptr, &read_data, pdg_png_read_data);

	// we have skipped the sig bytes
	png_set_sig_bytes(png_ptr, PNG_SIG_BYTES);

	// now read the PNG header
	png_read_info(png_ptr, info_ptr);
	png_uint_32 width, height;
	int bit_depth, color_type;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

	// do appropriate transformations based on the info in the header
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
	}
	if (bit_depth == 16) {
		png_set_strip_16(png_ptr);
	}
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}

	// Palette and tRNS expansion can add an alpha channel even when the PNG
	// header has no alpha bit. Query the transformed layout before allocating:
	// using the original color_type under-allocated transparent palette images.
	png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);
	const int channels = png_get_channels(png_ptr, info_ptr);
	const png_size_t pitch = png_get_rowbytes(png_ptr, info_ptr);
	if ((channels != 3 && channels != 4) || png_get_bit_depth(png_ptr, info_ptr) != 8 ||
	    !pitch || pitch > size_t((std::numeric_limits<long>::max)()) ||
	    height > (std::numeric_limits<size_t>::max)() / pitch ||
	    size_t(height) > (std::numeric_limits<size_t>::max)() / sizeof(png_bytep)) {
		png_error(png_ptr, "Unsupported PNG pixel layout");
	}
	pixels = static_cast<unsigned char*>(std::malloc(pitch * height));
	row_pointers = static_cast<png_bytep*>(std::malloc(sizeof(png_bytep) * height));
	if (!pixels || !row_pointers) png_error(png_ptr, "Cannot allocate PNG pixels");
	for (png_uint_32 i = 0; i < height; i++) {
		row_pointers[i] = pixels + pitch * i;
	}
	png_read_image(png_ptr, row_pointers);
	png_read_end(png_ptr, end_info);
	std::free(row_pointers);
	row_pointers = nullptr;

	// Publish only a complete decode. The caller owns the malloc'd pixels.
	*outWidth = *outBufferWidth = width;
	*outHeight = *outBufferHeight = height;
	*outBufferPitch = pitch;
	*outFormat = channels == 4 ? GL_RGBA : GL_RGB;
	*outDataPtr = pixels;
	// clean up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
}

}  // end namespace pdg

void pdg_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	pdg_png_data* read_io_ptr = (pdg_png_data*) png_get_io_ptr(png_ptr);
	if (read_io_ptr->currOffset > read_io_ptr->imageDataLen ||
	    length > read_io_ptr->imageDataLen - read_io_ptr->currOffset) {
		png_error(png_ptr, "Read Error");
		return;
	}
	memcpy(data, &read_io_ptr->imageData[read_io_ptr->currOffset], length);
	read_io_ptr->currOffset += length;
}
