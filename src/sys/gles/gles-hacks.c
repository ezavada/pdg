// -----------------------------------------------
// gles-hacks.c
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

#include <math.h>
#include <OpenGLES/ES1/gl.h>

#include "gles-hacks.h"

int hack_glMode = 0;
int hack_glIndex = 0;
int hack_glSize = 4;
int hack_glCount = 0;
int hack_glQuadCount = 0;
int hack_glQuadsCompleted = 0;
int hack_glTextured = 0;
int hack_glTextureIndex = 0;
int hack_glColorSize = 4;
int hack_glColored = 0;
int hack_glColorIndex = 0;

#define MAX_ARRAY 1024
//1024

float		hack_glFloatArray[MAX_ARRAY];
float		hack_glTextureArray[MAX_ARRAY];
float		hack_glColorArray[MAX_ARRAY];

#ifdef PDG_HACK_GL_QUAD_SUPPORT
void hack_glFixColorsAndTextures() {
	// rearrange the texture coordinates to match
	if (hack_glTextured) {
		// x coord
		float topLeftX = hack_glTextureArray[hack_glTextureIndex - 8];
		float topRightX= hack_glTextureArray[hack_glTextureIndex - 6];
		float botLeftX = hack_glTextureArray[hack_glTextureIndex - 2];
		hack_glTextureArray[hack_glTextureIndex - 8] = botLeftX;
		hack_glTextureArray[hack_glTextureIndex - 6] = topLeftX;
		hack_glTextureArray[hack_glTextureIndex - 2] = topRightX;
		// y coord
		float topLeftY = hack_glTextureArray[hack_glTextureIndex - 7];
		float topRightY= hack_glTextureArray[hack_glTextureIndex - 5];
		float botLeftY = hack_glTextureArray[hack_glTextureIndex - 1];
		hack_glTextureArray[hack_glTextureIndex - 7] = botLeftY;
		hack_glTextureArray[hack_glTextureIndex - 5] = topLeftY;
		hack_glTextureArray[hack_glTextureIndex - 1] = topRightY;
	}
	if (hack_glColored) {
		// red component
		int size4x = 4 * hack_glColorSize;
		int size3x = 3 * hack_glColorSize;
		float topLeftR = hack_glColorArray[hack_glColorIndex - size4x];
		float topRightR= hack_glColorArray[hack_glColorIndex - size3x];
		float botLeftR = hack_glColorArray[hack_glColorIndex - hack_glColorSize];
		hack_glColorArray[hack_glColorIndex - size4x] = botLeftR;
		hack_glColorArray[hack_glColorIndex - size3x] = topLeftR;
		hack_glColorArray[hack_glColorIndex - hack_glColorSize] = topRightR;
		// green component
		float topLeftG = hack_glColorArray[hack_glColorIndex - size4x +1];
		float topRightG= hack_glColorArray[hack_glColorIndex - size3x + 1];
		float botLeftG = hack_glColorArray[hack_glColorIndex - hack_glColorSize + 1];
		hack_glColorArray[hack_glColorIndex - size4x + 1] = botLeftG;
		hack_glColorArray[hack_glColorIndex - size3x + 1] = topLeftG;
		hack_glColorArray[hack_glColorIndex - hack_glColorSize + 1] = topRightG;
		// blue component
		float topLeftB = hack_glColorArray[hack_glColorIndex - size4x + 2];
		float topRightB= hack_glColorArray[hack_glColorIndex - size3x + 2];
		float botLeftB = hack_glColorArray[hack_glColorIndex - hack_glColorSize + 2];
		hack_glColorArray[hack_glColorIndex - size4x + 2] = botLeftB;
		hack_glColorArray[hack_glColorIndex - size3x + 2] = topLeftB;
		hack_glColorArray[hack_glColorIndex - hack_glColorSize + 2] = topRightB;
		if (hack_glColorSize > 3) {
			// alpha component
			float topLeftA = hack_glColorArray[hack_glColorIndex - size4x + 3];
			float topRightA= hack_glColorArray[hack_glColorIndex - size3x + 3];
			float botLeftA = hack_glColorArray[hack_glColorIndex - hack_glColorSize + 3];
			hack_glColorArray[hack_glColorIndex - size4x + 3] = botLeftA;
			hack_glColorArray[hack_glColorIndex - size3x + 3] = topLeftA;
			hack_glColorArray[hack_glColorIndex - hack_glColorSize + 3] = topRightA;
		}
	}
}

// translate Quads to Triangles for the short array
void hack_glFixQuads() {
	if (hack_glMode == GL_QUADS) {
		hack_glQuadCount++;
		if (hack_glQuadCount == 4) {
			hack_glQuadCount = 0;
			if (hack_glQuadsCompleted == 0) {
				// rearrange points to match first two triangles in a triangle strip, botRight doesn't change
				// x coord
				int size4x = 4 * hack_glSize;
				int size3x = 3 * hack_glSize;
				float topLeftX = hack_glFloatArray[hack_glIndex - size4x];
				float topRightX= hack_glFloatArray[hack_glIndex - size3x];
				float botLeftX = hack_glFloatArray[hack_glIndex - hack_glSize];
				hack_glFloatArray[hack_glIndex - size4x] = botLeftX;
				hack_glFloatArray[hack_glIndex - size3x] = topLeftX;
				hack_glFloatArray[hack_glIndex - hack_glSize] = topRightX;
				// y coord
				float topLeftY = hack_glFloatArray[hack_glIndex - size4x +1];
				float topRightY= hack_glFloatArray[hack_glIndex - size3x + 1];
				float botLeftY = hack_glFloatArray[hack_glIndex - hack_glSize + 1];
				hack_glFloatArray[hack_glIndex - size4x + 1] = botLeftY;
				hack_glFloatArray[hack_glIndex - size3x + 1] = topLeftY;
				hack_glFloatArray[hack_glIndex - hack_glSize + 1] = topRightY;
				if (hack_glSize > 2) {
					// z coord
					float topLeftZ = hack_glFloatArray[hack_glIndex - size4x + 2];
					float topRightZ= hack_glFloatArray[hack_glIndex - size3x + 2];
					float botLeftZ = hack_glFloatArray[hack_glIndex - hack_glSize + 2];
					hack_glFloatArray[hack_glIndex - size4x + 2] = botLeftZ;
					hack_glFloatArray[hack_glIndex - size3x + 2] = topLeftZ;
					hack_glFloatArray[hack_glIndex - hack_glSize + 2] = topRightZ;
					if (hack_glSize > 3) {
						// w coord
						float topLeftW = hack_glFloatArray[hack_glIndex - size4x + 3];
						float topRightW= hack_glFloatArray[hack_glIndex - size3x + 3];
						float botLeftW = hack_glFloatArray[hack_glIndex - hack_glSize + 3];
						hack_glFloatArray[hack_glIndex - size4x + 3] = botLeftW;
						hack_glFloatArray[hack_glIndex - size3x + 3] = topLeftW;
						hack_glFloatArray[hack_glIndex - hack_glSize + 3] = topRightW;
					}
				}
				// rearrange the colors and texture coordinates to match
				hack_glFixColorsAndTextures();
			} else {
				// rearrange points to successive sets of two triangles in a triangle strip
				// x coord
				
			}
			++hack_glQuadsCompleted;
		}
	}
}
#endif

void glTexCoord2f(float tx, float ty) {
	if (!hack_glTextured) {
		hack_glTextured = 1;
		hack_glTextureIndex = 0;
	}
	if (hack_glTextureIndex + 2 <= MAX_ARRAY) {
		hack_glTextureArray[hack_glTextureIndex++] = tx;
		hack_glTextureArray[hack_glTextureIndex++] = ty;
	}
}

void glVertex2i (int x, int y) {
	glVertex2f(x, y);
}

void glVertex3i (int x, int y, int z) {
	glVertex3f(x, y, z);
}

void glVertex2f (float x, float y) {
	if (hack_glIndex == 0) {
		hack_glSize = 2;
	}
	if (hack_glIndex + 2 <= MAX_ARRAY) {
		hack_glFloatArray[hack_glIndex++] = x;
		hack_glFloatArray[hack_glIndex++] = y;
		hack_glCount++;
#ifdef PDG_HACK_GL_QUAD_SUPPORT
		hack_glFixQuads();
#endif
	}
}

void glVertex3f (float x, float y, float z) {
	if (hack_glIndex == 0) {
		hack_glSize = 3;
	}
	if (hack_glIndex + 3 <= MAX_ARRAY) {
		hack_glFloatArray[hack_glIndex++] = x;
		hack_glFloatArray[hack_glIndex++] = y;
		hack_glFloatArray[hack_glIndex++] = z;
		hack_glCount++;
#ifdef PDG_HACK_GL_QUAD_SUPPORT
		hack_glFixQuads();
#endif
	}
}

void glVertexColor4f (float r, float g, float b, float a) {
	if (!hack_glColored) {
		hack_glColored = 1;
		hack_glColorIndex = 0;
		hack_glColorSize = 4;
	}
	if (hack_glColorIndex + 4 <= MAX_ARRAY) {
		hack_glColorArray[hack_glColorIndex++] = r;
		hack_glColorArray[hack_glColorIndex++] = g;
		hack_glColorArray[hack_glColorIndex++] = b;
		hack_glColorArray[hack_glColorIndex++] = a;
	}
}

void glVertexColor3f (float r, float g, float b) {
	if (!hack_glColored) {
		hack_glColored = 1;
		hack_glColorIndex = 0;
		hack_glColorSize = 3;
	}
	if (hack_glColorIndex + 3 <= MAX_ARRAY) {
		hack_glColorArray[hack_glColorIndex++] = r;
		hack_glColorArray[hack_glColorIndex++] = g;
		hack_glColorArray[hack_glColorIndex++] = b;
	}
}

void glColor4fv (float *v) {
	glColor4f(v[0], v[1], v[2], v[3]);
}

void gluPerspective(float fovy, float aspect, float zNear, float zFar) {
	// Start in projection mode.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	double xmin, xmax, ymin, ymax;
	
	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;	
	
	glFrustumf(xmin, xmax, ymin, ymax, zNear, zFar);
}

int gluBuild2DMipmaps(GLenum target,
                      GLint components,
                      GLint width,
                      GLint height,
                      GLenum format,
                      GLenum type,
                      const void *data) {
	glTexParameterf(target, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(target, 0, components, width, height, 0, format, type, data); 
	return 0;
}



void glOrtho(int left, int right, int bottom, int top, int zNear, int zFar) {
	glOrthof(left, right, bottom, top, zNear, zFar);
}

void glClearDepth(int depth) {
	glClearDepthx(depth);
}

void glBegin(int mode) {
	hack_glMode = mode;
	hack_glIndex = 0;
	hack_glSize = 4;
	hack_glCount = 0;
	hack_glTextured = 0;
	hack_glColored = 0;
	hack_glQuadCount = 0;
	hack_glQuadsCompleted = 0;
}

void glEnd(void) {

	// FIXME("use single array with strides for efficiency");
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(hack_glSize, GL_FLOAT, 0, hack_glFloatArray);
	if (hack_glColored) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(hack_glColorSize, GL_FLOAT, 0, hack_glColorArray);
	}
	if (hack_glTextured) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, hack_glTextureArray);
	}

#ifdef PDG_HACK_GL_QUAD_SUPPORT
	// adjust for quads having been converted to triangles
	if (hack_glMode == GL_QUADS) {
		hack_glMode = GL_TRIANGLE_STRIP;
	}
#endif
	
	glDrawArrays(hack_glMode, 0, hack_glCount);
	if (hack_glColored) {
		glDisableClientState(GL_COLOR_ARRAY);
	}
	if (hack_glTextured) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void glPolygonMode(int mode) {
	if (mode == GL_FRONT) {
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_BACK);
	} else if (mode == GL_BACK) {
		glEnable(GL_CULL_FACE); 
		glCullFace(GL_FRONT);
	} else {
		glDisable(GL_CULL_FACE);
	}
}


