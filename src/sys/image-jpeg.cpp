// -----------------------------------------------
// image-jpeg.cpp
//
// implementation of JPEG loading using libjpeg-turbo
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

// Include libjpeg-turbo headers
extern "C" {
#include <cstdio>  // for FILE type
#include "jpeglib.h"
#include "jerror.h"
}

#include <cstdlib>
#include <csetjmp>

// JPEG error handling structure (using standard libjpeg-turbo structure)
typedef struct {
    struct jpeg_error_mgr pub;    /* "public" fields */
    jmp_buf setjmp_buffer;        /* for return to caller */
} jpeg_error_mgr_ext;

typedef jpeg_error_mgr_ext * jpeg_error_ptr;

// JPEG error handler
METHODDEF(void) jpeg_error_exit(j_common_ptr cinfo) {
    jpeg_error_ptr myerr = (jpeg_error_ptr)cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}

// JPEG data source manager for reading from memory
typedef struct {
    struct jpeg_source_mgr pub;   /* public fields */
    unsigned char* imageData;
    long imageDataLen;
    long currOffset;
} jpeg_memory_source;

METHODDEF(void) jpeg_memory_init_source(j_decompress_ptr cinfo) {
    // Nothing to do
}

METHODDEF(boolean) jpeg_memory_fill_input_buffer(j_decompress_ptr cinfo) {
    jpeg_memory_source* src = (jpeg_memory_source*)cinfo->src;
    
    if (src->currOffset >= src->imageDataLen) {
        // End of file
        src->pub.next_input_byte = (const JOCTET*)src->imageData + src->imageDataLen;
        src->pub.bytes_in_buffer = 0;
        return FALSE;
    }
    
    src->pub.next_input_byte = (const JOCTET*)src->imageData + src->currOffset;
    src->pub.bytes_in_buffer = src->imageDataLen - src->currOffset;
    return TRUE;
}

METHODDEF(void) jpeg_memory_skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
    jpeg_memory_source* src = (jpeg_memory_source*)cinfo->src;
    
    if (num_bytes > 0) {
        if (num_bytes > (long)src->pub.bytes_in_buffer) {
            num_bytes = (long)src->pub.bytes_in_buffer;
        }
        src->pub.next_input_byte += num_bytes;
        src->pub.bytes_in_buffer -= num_bytes;
        src->currOffset += num_bytes;
    }
}

METHODDEF(void) jpeg_memory_term_source(j_decompress_ptr cinfo) {
    // Nothing to do
}

METHODDEF(void) jpeg_memory_set_source(j_decompress_ptr cinfo, unsigned char* imageData, long imageDataLen) {
    jpeg_memory_source* src;
    
    if (cinfo->src == NULL) {
        cinfo->src = (struct jpeg_source_mgr*)
            (*cinfo->mem->alloc_small) ((j_common_ptr)cinfo, JPOOL_PERMANENT,
                                       sizeof(jpeg_memory_source));
    }
    
    src = (jpeg_memory_source*)cinfo->src;
    src->imageData = imageData;
    src->imageDataLen = imageDataLen;
    src->currOffset = 0;
    
    src->pub.init_source = jpeg_memory_init_source;
    src->pub.fill_input_buffer = jpeg_memory_fill_input_buffer;
    src->pub.skip_input_data = jpeg_memory_skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart;
    src->pub.term_source = jpeg_memory_term_source;
    
    src->pub.bytes_in_buffer = 0;
    src->pub.next_input_byte = NULL;
}

namespace pdg {

void platform_initJPEGData(unsigned char* imageData, long imageDataLen, unsigned char** outDataPtr, 
    long* outWidth, long* outHeight, long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, 
    int* outFormat)
{
    *outDataPtr = 0;
    *outWidth = 0;
    *outHeight = 0;
    *outBufferWidth = 0;
    *outBufferHeight = 0;
    *outBufferPitch = 0;
    *outFormat = GL_RGB;

    // Check if this looks like a JPEG file
    if (imageDataLen < 2 || imageData[0] != 0xFF || imageData[1] != 0xD8) {
        return; // Not a JPEG file
    }

    struct jpeg_decompress_struct cinfo;
    jpeg_error_mgr_ext jerr;
    
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_error_exit;
    
    if (setjmp(jerr.setjmp_buffer)) {
        jpeg_destroy_decompress(&cinfo);
        return;
    }
    
    jpeg_create_decompress(&cinfo);
    jpeg_memory_set_source(&cinfo, imageData, imageDataLen);
    
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    
    *outWidth = cinfo.output_width;
    *outHeight = cinfo.output_height;
    *outBufferWidth = cinfo.output_width;
    *outBufferHeight = cinfo.output_height;
    
    int components = cinfo.output_components;
    if (components == 4) {
        *outFormat = GL_RGBA;
        *outBufferPitch = cinfo.output_width * 4;
    } else {
        *outFormat = GL_RGB;
        *outBufferPitch = cinfo.output_width * 3;
    }
    
    *outDataPtr = (unsigned char*)std::malloc(*outBufferPitch * *outHeight);
    if (*outDataPtr) {
        JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr)&cinfo, JPOOL_IMAGE, *outBufferPitch, 1);
        
        unsigned char* dst = *outDataPtr;
        while (cinfo.output_scanline < cinfo.output_height) {
            jpeg_read_scanlines(&cinfo, buffer, 1);
            memcpy(dst, buffer[0], *outBufferPitch);
            dst += *outBufferPitch;
        }
    }
    
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}

}  // end namespace pdg 