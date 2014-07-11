// -----------------------------------------------
// gles-hacks.h
//
// Written by Ed Zavada, 2009-2012
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

#ifdef PDG_HACK_GL_QUAD_SUPPORT
#define GL_QUADS 100
#endif

#ifdef __cplusplus
extern "C" {
#endif

void glTexCoord2f(float tx, float ty);
void glVertex2i (int x, int y);
void glVertex3i (int x, int y, int z);
void glVertex2f (float x, float y);
void glVertex3f (float x, float y, float z);
void glVertex3fv (float *v);
void glColor4fv (float *v);
void glVertexColor4f (float r, float g, float b, float a);
void glVertexColor3f (float r, float g, float b);
		
void gluPerspective(float fovy, float aspect, float zNear, float zFar);

int gluBuild2DMipmaps(GLenum target,
                      GLint components,
                      GLint width,
                      GLint height,
                      GLenum format,
                      GLenum type,
                      const void *data);



void glOrtho(int left, int right, int bottom, int top, int zNear, int zFar);
void glClearDepth(int depth);
void glBegin(int mode);
void glEnd(void);
void glPolygonMode(int mode);

#ifdef __cplusplus
}
#endif
