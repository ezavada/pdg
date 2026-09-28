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
#include <numbers>

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
#include <limits>
#include <stdexcept>

#include "opengl-framebuffer.h"
#include "graphics-opengl.h"
#include "image-opengl.h"
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

static PortImpl* gDrawingPort = nullptr;
static std::vector<std::weak_ptr<OffscreenSurface>> gOffscreenSurfaces;

ScopedOffscreenDrawing::ScopedOffscreenDrawing(Port* port) {
    // Custom renderers can implement Port without the OpenGL backend's state.
    auto* implementation = dynamic_cast<PortImpl*>(port);
    if (implementation && implementation->mOffscreen) begin(*implementation->mOffscreen, implementation);
}

ScopedOffscreenDrawing::ScopedOffscreenDrawing(OffscreenSurface& offscreen, PortImpl* port) { begin(offscreen, port); }

void ScopedOffscreenDrawing::begin(OffscreenSurface& offscreen, PortImpl* port) {
    if (port && gDrawingPort == port) return;
    surface = &offscreen;
    target = port;
    previous = gDrawingPort;
    PortImpl* previousContext = previous ? (previous->mOffscreen ? previous->mOffscreen->contextPort : previous)
        : static_cast<PortImpl*>(GraphicsManager::instance().getMainPort());
    switchedContext = previousContext && previousContext != offscreen.contextPort;
    platform_startDrawing(offscreen.contextPort->mPlatformWindowRef);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &renderbuffer);
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetIntegerv(GL_SCISSOR_BOX, scissor);
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment);
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    glGetFloatv(GL_PROJECTION_MATRIX, projection);
    glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
    scissorEnabled = glIsEnabled(GL_SCISSOR_TEST);
    savedDirty = gPortDirty;
    framebuffer::BindFramebuffer(GL_FRAMEBUFFER, offscreen.framebuffer);
    glViewport(0, 0, offscreen.width, offscreen.height);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    gDrawingPort = port;
    gModesSet = false;
    gBoundTexture = GLuint(-1);
    if (port) { port->beginFrame(); port->mStateCache.resetState(); port->setClipRect(port->getClipRect()); }
}

ScopedOffscreenDrawing::~ScopedOffscreenDrawing() {
    if (!surface) return;
    framebuffer::BindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    framebuffer::BindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glBindTexture(GL_TEXTURE_2D, texture);
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
    if (scissorEnabled) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    glMatrixMode(GL_PROJECTION); glLoadMatrixf(projection);
    glMatrixMode(GL_MODELVIEW); glLoadMatrixf(modelview);
    glMatrixMode(matrixMode);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glPixelStorei(GL_PACK_ALIGNMENT, packAlignment);
    if (target) ++surface->revision;
    if (switchedContext) {
        PortImpl* context = previous ? (previous->mOffscreen ? previous->mOffscreen->contextPort : previous)
            : static_cast<PortImpl*>(GraphicsManager::instance().getMainPort());
        if (context) platform_startDrawing(context->mPlatformWindowRef);
    }
    gDrawingPort = previous;
    gPortDirty = savedDirty;
    gModesSet = false;
    gBoundTexture = GLuint(-1);
    surface->contextPort->mStateCache.resetState();
    if (previous) { previous->mStateCache.resetState(); previous->setClipRect(previous->getClipRect()); }
}

bool PortImpl::initOffscreen(long width, long height, PortImpl* contextPort) {
    platform_startDrawing(contextPort->mPlatformWindowRef);
    if (!framebuffer::available()) return false;
    auto surface = std::make_shared<OffscreenSurface>();
    surface->contextPort = contextPort; surface->width = width; surface->height = height;
    {
        ScopedOffscreenDrawing scope(*surface);
        GLint maximum = 0; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maximum);
        if (width > maximum || height > maximum) return false;
        glGenTextures(1, &surface->texture);
        glBindTexture(GL_TEXTURE_2D, surface->texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        framebuffer::GenFramebuffers(1, &surface->framebuffer);
        framebuffer::BindFramebuffer(GL_FRAMEBUFFER, surface->framebuffer);
        framebuffer::FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, surface->texture, 0);
        framebuffer::GenRenderbuffers(1, &surface->depth);
        framebuffer::BindRenderbuffer(GL_RENDERBUFFER, surface->depth);
        framebuffer::RenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        framebuffer::FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, surface->depth);
        if (framebuffer::CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return false;
        glDisable(GL_SCISSOR_TEST);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    mOffscreen = surface;
    setPortRects(Rect(width, height));
    std::erase_if(gOffscreenSurfaces, [](const auto& entry) { return entry.expired(); });
    gOffscreenSurfaces.push_back(surface);
    return true;
}

void OffscreenSurface::readPixels() {
    if (!contextPort || pixelRevision == revision) return;
    ScopedOffscreenDrawing scope(*this);
    pixels.resize(static_cast<size_t>(width) * height * 4);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    // Offscreen coordinates put the top row at texture v=0. Convert the
    // composited premultiplied RGB to the straight RGBA used by Image pixels.
    for (size_t i = 0; i < pixels.size(); i += 4) {
        const unsigned alpha = pixels[i+3];
        for (int channel = 0; channel < 3; ++channel)
            pixels[i+channel] = alpha ? std::min(255u, (pixels[i+channel]*255u + alpha/2)/alpha) : 0;
    }
    pixelRevision = revision;
}

OffscreenSurface::~OffscreenSurface() {
    if (contextPort) {
        ScopedOffscreenDrawing scope(*this);
        framebuffer::DeleteFramebuffers(1, &framebuffer);
        framebuffer::DeleteRenderbuffers(1, &depth);
        glDeleteTextures(1, &texture);
    }
}

void OffscreenSurface::releaseContext() {
    if (!contextPort) return;
    readPixels(); // Surviving live images keep their final pixels after context destruction.
    {
        ScopedOffscreenDrawing scope(*this);
        framebuffer::DeleteFramebuffers(1, &framebuffer);
        framebuffer::DeleteRenderbuffers(1, &depth);
        glDeleteTextures(1, &texture);
    }
    framebuffer = texture = depth = 0;
    contextPort = nullptr;
}

void releaseOffscreenSurfacesForContext(PortImpl* port) {
    for (auto& entry : gOffscreenSurfaces)
        if (auto surface = entry.lock(); surface && surface->contextPort == port) surface->releaseContext();
    if (gDrawingPort == port) gDrawingPort = nullptr;
}

void graphics_startDrawing(Port* port) {
	pdg::PortImpl* thePort = dynamic_cast<pdg::PortImpl*>(port);
	platform_startDrawing(thePort->mPlatformWindowRef);
    gDrawingPort = thePort;
	GLsizei w = thePort->getDrawingArea().width();
	GLsizei h = thePort->getDrawingArea().height();
	if (   (gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise)
		|| (gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise)) {
		glViewport(0, 0, h, w);
	} else {
		glViewport(0, 0, w, h);
	}
	glDisable(GL_SCISSOR_TEST); // Frame clearing is independent of the previous draw clip.
    thePort->setClipRect(thePort->getClipRect());
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
	thePort->internalDrawCursor();
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
    // Preserve fractional coordinates and distinguish empty from the full-area reset.
    port.mClipRect = rect.intersection(port.mDrawingRect);
    mClipChanged = true;
}

void Port::clear(const Color& color) {
    ScopedOffscreenDrawing scope(this);
    auto& port = static_cast<PortImpl&>(*this);
    port.setOpenGLModesForDrawing(false);
    GLfloat previous[4]; glGetFloatv(GL_COLOR_CLEAR_VALUE, previous);
    const float alpha = std::clamp(color.alpha, 0.0f, 1.0f);
    const float rgbScale = port.mOffscreen ? alpha : 1.0f;
    glClearColor(color.red * rgbScale, color.green * rgbScale, color.blue * rgbScale, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(previous[0], previous[1], previous[2], previous[3]);
    port.mNeedRedraw = gPortDirty = true;
}

void Port::setDrawingOrigin(const Point& origin) {
    auto& port = static_cast<PortImpl&>(*this);
    if (!port.mOffscreen) throw std::invalid_argument("Drawing origin requires an offscreen Port");
    if (!std::isfinite(origin.x) || !std::isfinite(origin.y)) throw std::invalid_argument("Drawing origin must be finite");
    port.setPortRects(Rect(origin, port.mDrawingRect.width(), port.mDrawingRect.height()));
    gModesSet = false;
}

void Port::resetClipRect() { setClipRect(getDrawingArea()); }

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
	GLint slices = std::log2(radius) * 4;
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
	float degreesRot = rotation * 180.0 / std::numbers::pi;
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
	
	GLfloat xRotDeg = (polarOffsetRadians.x * 180.0 / std::numbers::pi) - 90.0;
	GLfloat yRotDeg = polarOffsetRadians.y * 180.0 / std::numbers::pi;
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
		platform_setHardwareCursorVisible(false);
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
    // The derived port already released its cache. Clear links without trying
    // to release entries through that destroyed cache (including custom Ports).
    for (auto* image : mLinkedImages) {
        image->mCacheKey = 0;
        image->Image::setPort(nullptr);
    }
    mLinkedImages.clear();
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
	if(mCurrentCursor)
	{
		Rect savedClip = getClipRect();
		setClipRect(getDrawingArea());
		Point mousePt = OS::getMouse();
		mousePt = mousePt - mHotSpot;
		mCurrentCursor->draw(mousePt);
		setClipRect(savedClip);
	}
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
    mClipChanged = true;
    mNeedRedraw = true;
}

//	bool avoidRecursion = false;

void
PortImpl::setOpenGLModesForDrawing(bool useAlpha, BlendMode blendMode, bool premultiplied) {
//	if (avoidRecursion) return;
//	avoidRecursion = true;
    if (!gModesSet) {
        long width = mDrawingRect.width();
        long height = mDrawingRect.height();
        long swidth = width;
        long sheight = height;
        if (!mOffscreen && ((gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise)
            || (gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise))) {
            sheight = width;
            swidth = height;
        }

        // set orthograhic 1:1  pixel transform in local view coords
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(2.0f / swidth, (mOffscreen ? 2.0f : -2.0f) / sheight, 1.0f);
        if (!mOffscreen) glRotatef(gRotationAngle, 0, 0, 1);
        glTranslatef(-width / 2.0f - mDrawingRect.left, -height / 2.0f - mDrawingRect.top, 0.0f);
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
				if (mOffscreen) framebuffer::BlendFuncSeparate(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                else glBlendFunc(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
				if (mOffscreen) framebuffer::BlendFuncSeparate(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                else glBlendFunc(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
		}
	} else {
		glDisable(GL_BLEND);
	}

    if ( mClipChanged) {
        if ( mClipRect.empty() ) {
            glScissor(0, 0, 0, 0);
            glEnable(GL_SCISSOR_TEST);
        } else {
            const int left = int(std::ceil(mClipRect.left - mDrawingRect.left - 0.5f));
            const int top = int(std::ceil(mClipRect.top - mDrawingRect.top - 0.5f));
            const int right = int(std::ceil(mClipRect.right - mDrawingRect.left - 0.5f));
            const int bottom = int(std::ceil(mClipRect.bottom - mDrawingRect.top - 0.5f));
            const int width = std::max(0, right - left), height = std::max(0, bottom - top);
            if (mOffscreen)
                glScissor(left, top, width, height);
            else if (gEffectiveScreenPos == screenPos_Rotated180)
                glScissor(mDrawingRect.right - right, top, width, height);
            else if (gEffectiveScreenPos == screenPos_Rotated90Clockwise)
                glScissor(top, left, height, width);
            else if (gEffectiveScreenPos == screenPos_Rotated90CounterClockwise)
                glScissor(mDrawingRect.bottom - bottom, mDrawingRect.right - right, height, width);
            else
                glScissor(left, mDrawingRect.bottom - bottom, width, height);
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
  mTextCache(0),
  mPlatformWindowRef(nullptr)
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
    // Window teardown invalidates texture IDs before destroying its context.
    // Offscreen teardown keeps that context current and releases textures here.
    while (mTextCache) {
        auto* entry = mTextCache;
        mTextCache = entry->nextEntry;
        if (entry->texture) glDeleteTextures(1, &entry->texture);
        delete entry;
    }
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
