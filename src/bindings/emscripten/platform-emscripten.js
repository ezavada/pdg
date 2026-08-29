// -----------------------------------------------
// platform-emscripten.js
// 
// part of the emscripten bindings
// implementation of platform calls when platform is javascript
// with an emscripten runtime
//
// Written by Ed Zavada, 2015
// Copyright (c) 2015, Dream Rock Studios, LLC
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


// pdg::platform_cleanup()

function pdg_em_platform_cleanup() 
{
}


// pdg::platform_init(int argc, const char* argv[])

function pdg_em_platform_init(argc, argv) 
{
}


// pdg::platform_pollEvents()

function pdg_em_platform_pollEvents() 
{
}


// pdg::platform_initImageData(unsigned char* imageData, long imageDataLen, 
//		unsigned char** outDataPtr, long* outWidth, long* outHeight, 
//		long* outBufferWidth, long* outBufferHeight, long* outBufferPitch, 
//		int* outFormat)

function pdg_em_platform_initImageData(
    imageData, imageDataLen, outDataPtr, outWidth, outHeight, 
    outBufferWidth, outBufferHeight, outBufferPitch, outFormat) 
{
}

