// -----------------------------------------------
// include_opengl.h
// 
// include open gl for various platforms and compilers
//
// Written by Ed Zavada, 2010-2012
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


#ifndef INCLUDE_OPENGL_H_INCLUDED
#define INCLUDE_OPENGL_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/platform.h"

#ifdef PLATFORM_WIN32
  #include <windows.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
  #define glVertexColor4f glColor4f
  /* Windows gl.h is old; blend equation constants (OpenGL 1.4) are missing */
  #ifndef GL_FUNC_ADD
  #define GL_FUNC_ADD 0x8006
  #endif
  #ifndef GL_FUNC_SUBTRACT
  #define GL_FUNC_SUBTRACT 0x800A
  #endif
  #ifndef GL_FUNC_REVERSE_SUBTRACT
  #define GL_FUNC_REVERSE_SUBTRACT 0x800B
  #endif
  #ifndef GL_MIN
  #define GL_MIN 0x8007
  #endif
  #ifndef GL_MAX
  #define GL_MAX 0x8008
  #endif
  /* Windows gl.h is old; texture wrap mode (OpenGL 1.2) is missing */
  #ifndef GL_CLAMP_TO_EDGE
  #define GL_CLAMP_TO_EDGE 0x812F
  #endif
  /* glBlendEquation is OpenGL 1.4; not in Windows opengl32.lib - load at runtime */
  typedef void (APIENTRY * PFNGLBLENDEQUATIONPROC)(GLenum mode);
  extern PFNGLBLENDEQUATIONPROC pdg_glBlendEquation;
  #define glBlendEquation(mode) do { if (pdg_glBlendEquation) (*pdg_glBlendEquation)(mode); } while(0)
#elif PLATFORM_MACOSX
  #ifdef PLATFORM_OPENGLES
    #include <OpenGLES/ES1/gl.h>
    #include "gles-hacks.h"
    #include "glues_quad.h"
  #else
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #define glVertexColor4f glColor4f
  #endif
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #define glVertexColor4f glColor4f
#endif




#endif
