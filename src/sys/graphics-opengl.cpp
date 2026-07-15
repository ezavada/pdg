// -----------------------------------------------
// graphics-opengl.cpp
//
// Open GL based implementation of
// common graphics functions
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

#ifndef PDG_NO_GUI

#include "pdg/msvcfix.h"

#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
#include "pdg/sys/events.h"
#include "pdg/sys/initializer.h"
#include "pdg/sys/spline.h"
#include "pdg/sys/polygon.h"
#include "internals.h"
#include "pdg-main.h"

#include <algorithm>
#include <string>
#include <cmath>

#include "graphics-opengl.h"
#include "include-opengl.h"

// Uncomment line below to get baselines and bounding boxes for text drawn automatically
//#define PDG_DEBUG_TEXT_DRAWING


#ifdef PDG_GFX_POINTER_SAFETY_CHECKS
    #define GFX_CHECK_PTR(ptr, block, block_size) CHECK_PTR(ptr, block, block_size)
#else
    #define GFX_CHECK_PTR(ptr, block, block_size)
#endif

namespace pdg {

#ifdef PLATFORM_WIN32
/* glBlendEquation not in Windows opengl32.lib; load at runtime (OpenGL 1.4) */
PFNGLBLENDEQUATIONPROC pdg_glBlendEquation = nullptr;
static void pdg_init_glBlendEquation() {
	if (!pdg_glBlendEquation) {
		pdg_glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
	}
}
#endif

float gRotationAngle = 0.0f;
int gScreenPos = -1;
int gEffectiveScreenPos = -1;
bool gAllowVerticalRotation = true;
bool gAllowHorizontalRotation = true;
bool gPortDirty;
bool gModesSet = false;

extern GLuint gBoundTexture;

void graphics_startDrawing(Port* port) {
	pdg::PortImpl* thePort = dynamic_cast<pdg::PortImpl*>(port);
	platform_startDrawing(thePort->mPlatformWindowRef);
	GLsizei w = thePort->getDrawingArea().width();
	GLsizei h = thePort->getDrawingArea().height();
	if (   (gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise)
		|| (gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise)) {
		glViewport(0, 0, h, w);
	} else {
		glViewport(0, 0, w, h);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	gPortDirty = false;
    gModesSet = false;
    gBoundTexture = -1;
    
    // Begin new frame for image cache (for LRU frame-based protection)
    thePort->beginFrame();
    
    // Reset the texture binding cache at the start of each frame
    thePort->mStateCache.resetState();
}

void graphics_finishDrawing(Port* port) {
	pdg::PortImpl* thePort = dynamic_cast<pdg::PortImpl*>(port);
	platform_finishDrawing(thePort->mPlatformWindowRef);
}

void graphics_getApplicationSupportedOrientations() {
	gAllowVerticalRotation = pdg::Initializer::allowVerticalOrientation();
	gAllowHorizontalRotation = pdg::Initializer::allowHorizontalOrientation();
}

int graphics_getEffectiveScreenPos() {
	return gEffectiveScreenPos;
}

void graphics_setScreenPos(int screenPos) {
	if (gScreenPos == -1) {
		// if screen position has never been determined, then set up some items
		// required for correct transition
		if (gAllowVerticalRotation) {
			gScreenPos = pdg::screenPos_Normal;
			gRotationAngle = 0.0f;
		} else {
			gScreenPos = pdg::screenPos_Rotated90Clockwise;
			gRotationAngle = -90.0f;
		}
		gEffectiveScreenPos = gScreenPos;
	}
	switch (screenPos) {
		case pdg::screenPos_Rotated180:
			if (gAllowVerticalRotation) {
				gRotationAngle = 180.0f;
				gEffectiveScreenPos = screenPos;
			}
			break;
		case pdg::screenPos_Rotated90Clockwise:
			if (gAllowHorizontalRotation) {
				gRotationAngle = -90.0f;
				gEffectiveScreenPos = screenPos;
			}
			break;
		case pdg::screenPos_Rotated90CounterClockwise:
			if (gAllowHorizontalRotation) {
				gRotationAngle = 90.0f;
				gEffectiveScreenPos = screenPos;
			}
			break;
		case pdg::screenPos_Normal:
			if (gAllowVerticalRotation) {
				gRotationAngle = 0.0f;
				gEffectiveScreenPos = screenPos;
			}
			break;
		default:
			break;
	}
	gScreenPos = screenPos;
}


bool graphics_allowHorizontalOrientation() {
	return gAllowHorizontalRotation;
}
	
bool graphics_allowVerticalOrientation() {
	return gAllowVerticalRotation;
}

Rect
Port::getDrawingArea() {
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
    return port.mDrawingRect;
}

Rect
Port::getClipRect() {
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
    return port.mClipRect;
}

void
Port::setClipRect(const Rect& rect) {
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
    // make sure clip rect is never outside drawing area
    port.mClipRect.top = std::max<long>(rect.top, port.mDrawingRect.top);
    port.mClipRect.left = std::max<long>(rect.left, port.mDrawingRect.left);
    port.mClipRect.bottom = std::min<long>(rect.bottom, port.mDrawingRect.bottom);
    port.mClipRect.right = std::min<long>(rect.right, port.mDrawingRect.right);
    mClipChanged = true;
}

// returns the font currently in use for the port
Font*     
Port::getCurrentFont(uint32 style)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	style &= TEXT_STYLES_MASK;
	return port.mFontForStyle[style];
}

// set the name of the font used for this port
// this undoes any setFontNameForStyle calls you may have already made on this port
void     
Port::setFont(Font* font)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if (!font) {
		font = port.mGraphicsMgr->createFont("Arial");
	}
	if (!font) {
		DEBUG_ONLY( OS::_DOUT("Port::setFont() font is null, and Arial font not found"); )
		return;
	}
	// Cached fonts are shared, so refresh their backing port before reusing them.
	FontImpl* fontImpl = dynamic_cast<FontImpl*>(font);
	if (fontImpl) {
		fontImpl->mPort = this;
	}
	for (int i = 0; i < NUM_TEXT_STYLES; i++) {
		if (port.mFontForStyle[i]) {
			port.mFontForStyle[i]->release();
		}
		port.mFontForStyle[i] = font;
		font->addRef();
	}
}

// set the name of the font used for a particular style of text in this port
// does not affect what font is used for any other styles
// NOTE: only works for textStyle_Bold at the moment
void     
Port::setFontForStyle(Font* font, uint32 style)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if (!font) {
		font = port.mGraphicsMgr->createFont("Arial");
	}
	if (!font) {
		DEBUG_ONLY( OS::_DOUT("Port::setFontForStyle() font is null, and Arial font not found"); )
		return;
	}
	// Keep shared cached fonts pointed at the live port using them.
	FontImpl* fontImpl = dynamic_cast<FontImpl*>(font);
	if (fontImpl) {
		fontImpl->mPort = this;
	}
	style &= TEXT_STYLES_MASK;
	if (port.mFontForStyle[style]) {
		port.mFontForStyle[style]->release();
	}
	port.mFontForStyle[style] = font;
	font->addRef();
}

// set a factor by which all font sizes are enlarged or reduced
// > 1.0 is enlarge, < 1.0 is reduce, 1.0 is no scaling
void 
Port::setFontScalingFactor(float scaleBy)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	port.mFontScalingFactor = scaleBy;
}

void     
Port::drawImage(Image* img, const Point& loc) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->draw(loc);
}

void     
Port::drawImage(Image* img, const Quad& quad) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->draw(quad);
}

void     
Port::drawImage(Image* img, const Rect& r, FitType fitType, bool clipOverflow) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->draw(r, fitType, clipOverflow);
}

void     
Port::drawImage(ImageStrip* img, int frame, const Point& loc) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawFrame(loc, frame);
}

void     
Port::drawImage(ImageStrip* img, int frame, const Quad& quad) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawFrame(quad, frame);
}

void     
Port::drawImage(ImageStrip* img, int frame, const Rect& r, FitType fitType, bool clipOverflow) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawFrame(r, frame, fitType, clipOverflow);
}

void 
Port::drawTexture(Image* img, const Rect& r) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawTexture(r);
}

void 
Port::drawTexture(ImageStrip* img, int frame, const Rect& r) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawTextureFrame(r, frame);
}

void 
Port::drawTexturedSphere(Image* img, const Point& loc, float radius, float rotation, const Offset& polarOffsetRadians, const Offset& lightOffsetRadians, const Color& ambientLight) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawTexturedSphere(loc, radius, rotation, polarOffsetRadians, lightOffsetRadians, ambientLight);
}

void 
Port::drawTexturedSphere(ImageStrip* img, int frame, const Point& loc, float radius, float rotation, const Offset& polarOffsetRadians, const Offset& lightOffsetRadians, const Color& ambientLight) {
	if (img->mPort != this) {
		img->setPort(this);
	}
	img->drawTexturedSphereFrame(loc, frame, radius, rotation, polarOffsetRadians, lightOffsetRadians, ambientLight);
}

void
Port::drawColoredSphere(const Color& color, const Point& loc, float radius, float rotation, const Offset& polarOffsetRadians, const Offset& lightOffsetRadians, const Color& ambientLight) {
	// Decide how many slices to draw (very crude LOD)
	GLint slices = log2f(radius) * 4;
	if (slices < 5) slices = 5;
	
	PortImpl& port = static_cast<PortImpl&>(*this);
	port.setOpenGLModesForDrawing(false);
	
	// Setup material color
	GLfloat mat_diffuse[] = { color.red, color.green, color.blue, color.alpha };
	GLfloat mat_ambient[] = { color.red * 0.5f, color.green * 0.5f, color.blue * 0.5f, color.alpha };
	GLfloat mat_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat mat_shininess[] = { 20.0f };
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	// Setup lighting
	float degreesRot = rotation * 180.0 / M_PI;
	static GLfloat light_position[] = { 0, 0, -10, 1 };
	GLfloat model_ambient[] = { ambientLight.red, ambientLight.green, ambientLight.blue, ambientLight.alpha };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	glPushMatrix();
	
	glTranslatef(loc.x, loc.y, 1.0f);
	
	// Translate light position from spherical to cartesian coordinates
	GLfloat theta = lightOffsetRadians.y;
	GLfloat rho = lightOffsetRadians.x;
	GLfloat r = radius * 10.0f;
	GLfloat lx = -r * sin(rho);
	GLfloat ly = -r * sin(theta) * sin(rho);
	GLfloat lz = 10.0 * cos(theta) * cos(rho);
	light_position[0] = lx;
	light_position[1] = ly;
	light_position[2] = lz;
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glScalef(-radius, radius, 1.0f);
	
	GLfloat xRotDeg = (polarOffsetRadians.x * 180.0 / M_PI) - 90.0;
	GLfloat yRotDeg = polarOffsetRadians.y * 180.0 / M_PI;
	glRotatef(xRotDeg, 1.0f, 0.0f, 0.0);
	glRotatef(yRotDeg, 0.0f, 1.0f, 0.0);
	
	glRotatef(-degreesRot, 0.0f, 0.0f, 1.0);
	
	// Draw sphere without texture
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricOrientation(qobj, GLU_INSIDE);
	gluQuadricTexture(qobj, GL_FALSE);  // No texture
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, 1.0f, slices, slices);
	gluDeleteQuadric(qobj);
	
	glPopMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
}

void
Port::drawText(const char* text, const Point& loc, int size, uint32 style, Color rgba) {
	if (text == 0) return;
	int len = (int)std::strlen(text);
	if (len == 0) return;
	// look for text entirely outside clip rect
	PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	Rect drawable = port.drawableRect();
	// cheapest checks, off to right and left
	if (((style & (textStyle_Centered | textStyle_RightJustified)) == 0) && (loc.x >= drawable.right)) return; // exit early if completely clipped
	if (((style & textStyle_RightJustified) == textStyle_RightJustified) && (loc.x <= drawable.left)) return; // exit early if completely clipped
	// further checks require font info
	FontImpl* font = dynamic_cast<FontImpl*> ( getCurrentFont(style) );
	if (!font) return;
	Rect textRect;
	textRect.bottom = loc.y + std::ceil( font->getFontDescent(size, style) );
	if (textRect.bottom < drawable.top) return; // exit early if completely clipped
	textRect.top = loc.y - std::ceil( font->getFontAscent(size, style) );
	if (textRect.top > drawable.bottom) return; // exit early if completely clipped
	textRect.left = loc.x;

	// adjust for text justification
	int textwidth = getTextWidth(text, size, style, len);
	if (style & textStyle_Centered) {
		textRect.left -= (textwidth/2);     // centered means the point given is the centerpoint for the text
	} else if (style & textStyle_RightJustified) {
		textRect.left -= textwidth;         // otherwise the point given is the right-side end of the text
	}
	textRect.setWidth(textwidth);
	if (drawable.intersection(textRect).empty()) return; // exit early if completely clipped
#ifdef PDG_DEBUG_TEXT_DRAWING
	port.frameRect(textRect, PDG_MAGENTA_COLOR); // draw text bounding box
	port.drawLine(Point(textRect.left, loc.y), Point(textRect.right, loc.y), PDG_RED_COLOR); // draw baseline
#endif
	graphics_drawText(port, text, len, (Quad)textRect, size, style, rgba);
	port.mNeedRedraw = true;
	gPortDirty = true;
}


void
Port::drawText(const char* text, const Quad& quad, int size, uint32 style, Color rgba) {
	if (text == 0) return;
	int len = (int)std::strlen(text);
	if (len == 0) return;
	PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if (quad.getBounds().intersection(port.drawableRect()).empty()) return; // exit early if completely clipped
#ifdef PDG_DEBUG_TEXT_DRAWING
	port.frameRect(quad, PDG_MAGENTA_COLOR); // draw text bounding box
#endif
	graphics_drawText(port, text, len, quad, size, style, rgba);
	port.mNeedRedraw = true;
	gPortDirty = true;
}


// Note: The image you set will be released when the cursor is set again or reset so
// make sure you allocate Image memory for this function to release. -ADD
void
Port::setCursor(Image* cursorImage, const Point& hotSpot)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data

    if (!cursorImage) return;
    cursorImage->addRef();

	// If there is already a cursor set....
	if(port.mCurrentCursor)
	{
		// Delete the old cursor
		port.mCurrentCursor->release();
		port.mCurrentCursor = 0;
	}
	else
	{
		// otherwise just turn off the OS cursor
//		setHardwareCursorVisible(false);
	}

	// remove the cursor background storage if there is any
	if (port.mCurrentCursorBackground) {
	    std::free(port.mCurrentCursorBackground);
	    port.mCurrentCursorBackground = 0;
	    port.mCurrentCursorBackgroundSize = 0;
	}

	// Set the new cursor
	port.mCurrentCursor = cursorImage;
	port.mHotSpot = hotSpot;
}

Image*
Port::getCursor()
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	return port.mCurrentCursor;
}

void
Port::resetCursor()
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if(port.mCurrentCursor)
	{
		port.mCurrentCursor->release();
		port.mCurrentCursor = 0;
		platform_setHardwareCursorVisible(true);
	}

	// remove the cursor background storage if there is any
	if (port.mCurrentCursorBackground) {
	    std::free(port.mCurrentCursorBackground);
	    port.mCurrentCursorBackground = 0;
	    port.mCurrentCursorBackgroundSize = 0;
	}
}

int
Port::startTrackingMouse(const Rect& rect, void* userData)
{
//    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	// TODO: call private methods in PortImp to add a tracking rect
	return 0;
}

void
Port::stopTrackingMouse(int trackingRef)
{
//    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	// TODO: call private methods in PortImp to remove a tracking rect
}

Port::Port() : mClipChanged(false)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mPortScriptObj);
#endif
}

Port::~Port()
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	CleanupPortScriptObject(mPortScriptObj);
#endif
}


// ==================================================================
// PORTIMPL
// implementation of hidden implementation methods defined in PortImpl
// these implementations are not OS dependent
// ==================================================================

void
PortImpl::internalSaveCursorBackground()
{
	if(!mCurrentCursor)
	{
		return;
	}

	// only allocate the cursor background when the cursor changes
	// this saves lots of allocations and deallocations every time
	// the cursor is drawn
/*	if(!mCurrentCursorBackground) {
	    mCurrentCursorBackgroundSize = mBufInfo.bytespixel * mCurrentCursor->width * mCurrentCursor->height;
        mCurrentCursorBackground = (addr) std::malloc(mCurrentCursorBackgroundSize);
	}

	Point mousePt = OS::getMouse();
	mousePt = mousePt - mHotSpot;
	Point cursorExtent = mousePt;
	cursorExtent.x += mCurrentCursor->width;
	cursorExtent.y += mCurrentCursor->height;
	// Don't save the background if is mouse is off the drawing surface.
	if(mousePt.x < 0 || cursorExtent.x >= mBufInfo.width ||
	   mousePt.y < 0 || cursorExtent.y >= mBufInfo.height)
	{
		return;
	}

    addr deviceDataPtr = (addr) mBufInfo.data;
    int  devicePitch = mBufInfo.pitch;
    int  deviceBytesPerPixel = mBufInfo.bytespixel;
    long deviceYByteOffset = (mousePt.y * devicePitch);
    long deviceXByteOffset;
	if (deviceBytesPerPixel == 4) {     // 32 bit color
	    deviceXByteOffset = mousePt.x << 2;
	} else if (deviceBytesPerPixel == 2) {  // 16 bit color
	    deviceXByteOffset = mousePt.x << 1;
	} else {
        deviceXByteOffset = mousePt.x;  // 256 color
	}

    register long i = mCurrentCursor->height;    // number of pixel rows to grab
	register addr dst = mCurrentCursorBackground;
	register addr src = deviceDataPtr + deviceYByteOffset + deviceXByteOffset;
	register long bytes = deviceBytesPerPixel * mCurrentCursor->width;
    while (i-- > 0) {
        CHECK_PTR(src, mBufInfo.data, mBufInfo.dataSize);
        CHECK_PTR(src+bytes-1, mBufInfo.data, mBufInfo.dataSize);
        CHECK_PTR(dst, mCurrentCursorBackground, mCurrentCursorBackgroundSize);
        CHECK_PTR(dst+bytes-1, mCurrentCursorBackground, mCurrentCursorBackgroundSize);
        std::memcpy(dst, src, bytes);
        dst += bytes;
        src += devicePitch;
    } */

}

bool
PortImpl::lockDrawingSurface()
{
	return true;
}

void
PortImpl::unlockDrawingSurface()
{
}


void
PortImpl::internalDrawCursor()
{
/*	if(mCurrentCursor)
	{
		if (!lockDrawingSurface())
		{
			return;
		}
		Point mousePt = OS::getMouse();
		mousePt = mousePt - mHotSpot;
		Point cursorExtent = mousePt;
		cursorExtent.x += mCurrentCursor->width;
		cursorExtent.y += mCurrentCursor->height;
		// Don't draw the cursor if the mouse is off the drawing surface.
		if(mousePt.x < 0 || cursorExtent.x >= mBufInfo.width ||
			mousePt.y < 0 || cursorExtent.y >= mBufInfo.height)
		{
			return;
		}
		mCurrentCursor->draw(mousePt);
	} */
}

void
PortImpl::internalRestoreCursorBackground()
{
/*	if(!mCurrentCursorBackground)
	{
		return;
	}
	if(!mCurrentCursor)
	{
		return;
	}
    if (!lockDrawingSurface())
	{
		return;
	}

	Point mousePt = OS::getMouse();
	mousePt = mousePt - mHotSpot;
	Point cursorExtent = mousePt;
	cursorExtent.x += mCurrentCursor->width;
	cursorExtent.y += mCurrentCursor->height;
	// Don't save the background if is mouse is off the drawing surface.
	if(mousePt.x < 0 || cursorExtent.x >= mBufInfo.width ||
	   mousePt.y < 0 || cursorExtent.y >= mBufInfo.height)
	{
		return;
	}

    addr deviceDataPtr = (addr) mBufInfo.data;
    int  devicePitch = mBufInfo.pitch;
    int  deviceBytesPerPixel = mBufInfo.bytespixel;
    long deviceYByteOffset = (mousePt.y * devicePitch);
    long deviceXByteOffset;
	if (deviceBytesPerPixel == 4) {     // 32 bit color
	    deviceXByteOffset = mousePt.x << 2;
	} else if (deviceBytesPerPixel == 2) {  // 16 bit color
	    deviceXByteOffset = mousePt.x << 1;
	} else {
        deviceXByteOffset = mousePt.x;  // 256 color
	}

    register long i = mCurrentCursor->height;    // number of pixel rows to grab
	register addr src = mCurrentCursorBackground;
	register addr dst = deviceDataPtr + deviceYByteOffset + deviceXByteOffset;
	register long bytes = deviceBytesPerPixel * mCurrentCursor->width;
    while (i-- > 0) {
        CHECK_PTR(dst, mBufInfo.data, mBufInfo.dataSize);
        CHECK_PTR(dst+bytes-1, mBufInfo.data, mBufInfo.dataSize);
        CHECK_PTR(src, mCurrentCursorBackground, mCurrentCursorBackgroundSize);
        CHECK_PTR(src+bytes-1, mCurrentCursorBackground, mCurrentCursorBackgroundSize);
        std::memcpy(dst, src, bytes);
        src += bytes;
        dst += devicePitch;
    } */
}

void
PortImpl::resizePort(long width, long height) {
    Rect r(width, height);
    mDrawingRect = r;
    mClipRect = r;
    mNeedRedraw = true;
}

//	bool avoidRecursion = false;

void
PortImpl::setOpenGLModesForDrawing(bool useAlpha, BlendMode blendMode) {
//	if (avoidRecursion) return;
//	avoidRecursion = true;
    if (!gModesSet) {
        long width = mDrawingRect.width();
        long height = mDrawingRect.height();
        long swidth = width;
        long sheight = height;
        if (   (gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise)
            || (gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise)) {
            sheight = width;
            swidth = height;
        }

        // set orthograhic 1:1  pixel transform in local view coords
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(2.0f / swidth, -2.0f /  sheight, 1.0f);
        glRotatef(gRotationAngle, 0, 0, 1);
        glTranslatef(-width / 2.0f, -height / 2.0f, 0.0f);
        glDisable(GL_DEPTH_TEST); // ensure stuff we are about to draw is not removed by depth test
        gModesSet = true; // don't do this again till next frame
    }

	// Enable blending if we have alpha or a non-normal blend mode
	if (useAlpha || blendMode != blendMode_Normal) {
		glEnable(GL_BLEND);
#ifdef PLATFORM_WIN32
		pdg_init_glBlendEquation();
#endif
		// Apply blend mode from attributes
		switch (blendMode) {
			case blendMode_Normal:
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case blendMode_Additive:
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
			case blendMode_Multiply:
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_DST_COLOR, GL_ZERO);
				break;
			case blendMode_Screen:
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
				break;
			case blendMode_Darken:
				// Darken uses MIN blend equation to keep darker color
				glBlendEquation(GL_MIN);
				glBlendFunc(GL_ONE, GL_ONE);
				break;
			case blendMode_Lighten:
				// Lighten uses MAX blend equation to keep lighter color
				glBlendEquation(GL_MAX);
				glBlendFunc(GL_ONE, GL_ONE);
				break;
			default:
				glBlendEquation(GL_FUNC_ADD);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
		}
	} else {
		glDisable(GL_BLEND);
	}

    if ( mClipChanged) {
        if ( mClipRect.empty() ) {
            glDisable(GL_SCISSOR_TEST);
        } else {
            // scissor is in OpenGL window coordinates, so 0,0 is bottom left with flipped Y axis
            if (gEffectiveScreenPos == screenPos_Normal) {
                glScissor(mClipRect.left, mDrawingRect.bottom - mClipRect.bottom, mClipRect.width(), mClipRect.height() );
            } else if (gEffectiveScreenPos == screenPos_Rotated180) {
                glScissor(mDrawingRect.right - mClipRect.right, mClipRect.top, mClipRect.width(), mClipRect.height() );
            } else if (gEffectiveScreenPos == screenPos_Rotated90Clockwise) {
                glScissor(mClipRect.top, mClipRect.left, mClipRect.height(), mClipRect.width() );
            } else if (gEffectiveScreenPos == screenPos_Rotated90CounterClockwise) {
                Rect sr(mClipRect.height(), mClipRect.width() );
                sr.moveTo(mDrawingRect.bottom - mClipRect.bottom, mDrawingRect.right - mClipRect.right);
                glScissor(sr.left, sr.top, sr.width(), sr.height() );
            }
            glEnable(GL_SCISSOR_TEST);  // make sure we are clipping
        }
        mClipChanged = false;
    }
//	glEnableClientState(GL_VERTEX_ARRAY);
//	avoidRecursion = false;
}

PortImpl::PortImpl(GraphicsManager* graphicsMgr)
: Port(),
  mGraphicsMgr(graphicsMgr),
  mNeedRedraw(false),
  mDrawingRect(),
  mClipRect(),
  mCurrentCursor(0),
  mHotSpot(),
  mCurrentCursorBackground(0),
  mFontScalingFactor(0.0),
  mImageCache(0),
  mTextCache(0)
{
	for (int i = 0; i<NUM_TEXT_STYLES; i++) {
		mFontForStyle[i] = 0;
	}
	if (!graphicsMgr->getMainPort()) {
		graphicsMgr->setMainPort(this);
	}
	// Create hash-based image cache
	mImageCache = new ImageCache(100);  // Max 100 cached textures
	setFont();  // set the default font
}

PortImpl::~PortImpl()
{
    // Clean up fonts
    for (int i = 0; i < NUM_TEXT_STYLES; i++) {
        if (mFontForStyle[i]) {
            mFontForStyle[i]->release();
            mFontForStyle[i] = 0;
        }
    }
    
    // Clean up cursor
	if(mCurrentCursor)
	{
		mCurrentCursor->release();
		mCurrentCursor = 0;
		platform_setHardwareCursorVisible(true);
	}
	if (mCurrentCursorBackground) {
	    std::free(mCurrentCursorBackground);
	    mCurrentCursorBackground = 0;
	    mCurrentCursorBackgroundSize = 0;
	}
	
	// Clean up image cache
	if (mImageCache) {
		delete mImageCache;
		mImageCache = 0;
	}
}

// New key-based image cache management methods
CacheKey 
PortImpl::getCacheKey(const char* sourceName, int width, int height, bool useEdgeClamp) {
	// Create cache if it doesn't exist yet
	if (!mImageCache) {
		mImageCache = new ImageCache(100);  // Max 100 entries
	}
	return mImageCache->getCacheKey(sourceName, width, height, useEdgeClamp);
}

GLuint 
PortImpl::getTexture(CacheKey key) {
	if (mImageCache) {
		return mImageCache->getTexture(key);
	}
	return 0;
}

void 
PortImpl::setTexture(CacheKey key, GLuint texture) {
	if (mImageCache) {
		mImageCache->setTexture(key, texture);
	}
}

void 
PortImpl::releaseCachedEntry(CacheKey key) {
	if (mImageCache) {
		mImageCache->releaseCachedEntry(key);
	}
}

void 
PortImpl::beginFrame() {
	if (mImageCache) {
		mImageCache->beginFrame();
	}
}

// Legacy image cache management methods (deprecated)
ImageCacheEntry* 
PortImpl::getImageFromCache(const char* sourceName, int width, int height, bool useEdgeClamp) {
	if (mImageCache) {
		// Use hash-based cache for O(1) lookup
		return mImageCache->getImage(sourceName, width, height, useEdgeClamp);
	} else {
		// No cache yet, create new entry
		return new ImageCacheEntry(sourceName, width, height, useEdgeClamp);
	}
}

void 
PortImpl::addImageToCache(ImageCacheEntry* entry) {
	if (mImageCache) {
		// Add to hash-based cache with LRU eviction
		mImageCache->addImage(entry);
	}
}

void 
PortImpl::invalidateImageCache() {
	if (mImageCache) {
		// Invalidate all cached textures
		mImageCache->invalidateAll();
	}
}

// Text cache management methods
TextCacheEntry* 
PortImpl::getTextFromCache(const char* text, int len, FontImpl* font, int size, uint32 style) {
	if (mTextCache) {
		// Use port-specific cache
		return mTextCache->findTextInPortCache(text, len, font, size, style);
	} else {
		// No cache yet, create new entry
		return new TextCacheEntry(text, len, font, size, style);
	}
}

void 
PortImpl::addTextToCache(TextCacheEntry* entry) {
	if (mTextCache) {
		// Add to port-specific cache
		mTextCache->addEntryToPortCache(entry);
		// Update the port's cache pointer to point to the new head
		mTextCache = entry;
	} else {
		// Initialize port cache with this entry
		mTextCache = entry;
	}
}

void 
PortImpl::invalidateTextCache() {
	if (mTextCache) {
		// Invalidate port-specific cache
		mTextCache->invalidatePortTextures();
	}
}

} // end namespace pdg

#endif // PDG_NO_GUI
