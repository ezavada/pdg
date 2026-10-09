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
#include "pdg/sys/camera.h"
#include "pdg/sys/spritelayer.h"
#include <map>
#include <memory>
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

namespace {
struct TextVertex { float x, y, u, v, r, g, b, a; };
std::vector<TextVertex> textVertices;
PortImpl* textPort = nullptr;
GLuint textTexture = 0;
bool textPremultiplied = false;
}

void graphics_flushText() {
    if (textVertices.empty()) return;
    textPort = nullptr;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(TextVertex), &textVertices[0].x);
    glTexCoordPointer(2, GL_FLOAT, sizeof(TextVertex), &textVertices[0].u);
    glColorPointer(4, GL_FLOAT, sizeof(TextVertex), &textVertices[0].r);
    glDrawArrays(GL_TRIANGLES, 0, textVertices.size());
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    const auto& last = textVertices.back(); glColor4f(last.r, last.g, last.b, last.a);
    glDisable(GL_TEXTURE_2D); glDisable(GL_BLEND);
    textVertices.clear();
}

void graphics_submitText(PortImpl& port, const TextCacheEntry& entry, const Quad& quad, Color color,
                         bool premultiplied, bool bottomOrigin) {
    if (textPort != &port || textTexture != entry.texture || textPremultiplied != premultiplied
        || textVertices.size() >= 24576) graphics_flushText();
    if (textVertices.empty()) {
        port.setOpenGLModesForDrawing(true, blendMode_Normal, premultiplied);
        glEnable(GL_TEXTURE_2D); port.mStateCache.bindTexture(entry.texture);
        gBoundTexture = entry.texture;
        textPort = &port; textTexture = entry.texture; textPremultiplied = premultiplied;
    }
    if (premultiplied) { color.red *= color.alpha; color.green *= color.alpha; color.blue *= color.alpha; }
    const float top = entry.v0 + (bottomOrigin ? entry.ty : 0);
    const float bottom = entry.v0 + (bottomOrigin ? 0 : entry.ty);
    const int corners[] = {lftBot, lftTop, rgtBot, rgtBot, lftTop, rgtTop};
    for (int corner : corners) {
        const bool right = corner == rgtBot || corner == rgtTop;
        const bool upper = corner == lftTop || corner == rgtTop;
        const auto& p = quad.points[corner];
        textVertices.push_back({p.x, p.y, entry.u0 + (right ? entry.tx : 0) + (upper ? entry.tx_topoffset : 0),
            upper ? top : bottom, color.red, color.green, color.blue, color.alpha});
    }
}

void graphics_drawText(PortImpl& port, const char* text, int len, const Quad& quad, int size, uint32 style, Color rgba) {
    auto* font = dynamic_cast<FontImpl*>(port.getCurrentFont(style));
    if (!font) return;
    auto* entry = port.getTextFromCache(text, len, font, size, style);
    if (!entry->measured) port.getTextWidth(text, size, style, len);
    const bool firstDraw = entry->drawCount == 0 && entry->texture == 0;
    ++port.mTextLabelsDrawn;
    if (firstDraw) ++port.mNewTextLabels;
    if (entry->drawCount < 2) ++entry->drawCount;
    // Repeated labels graduate to a single cached raster. A new counter value
    // can instead reuse the stable prefix and ten digit masks in the atlas.
    bool candidate = port.mDigitCacheEnabled && firstDraw && entry->width > 0 && len > 1 && len <= 64
        && (style & TEXT_STYLES_MASK) == textStyle_Plain && std::strcmp(font->getFontName(), "Arial") == 0;
    bool hasDigit = false;
    if (candidate) {
        for (int i = 0; i < len; ++i) {
            const unsigned char c = text[i];
            if (c < 32 || c > 126) { candidate = false; break; }
            hasDigit |= c >= '0' && c <= '9';
        }
        const auto& a = quad.points[lftTop]; const auto& b = quad.points[rgtTop];
        const auto& c = quad.points[lftBot]; const auto& d = quad.points[rgtBot];
        candidate &= hasDigit && std::abs(a.x+d.x-b.x-c.x) < .001f && std::abs(a.y+d.y-b.y-c.y) < .001f;
    }
    if (!candidate) { graphics_drawTextRaster(port, text, len, quad, size, style, rgba, entry); return; }

    const float fullWidth = entry->width, fullAdvance = entry->advanceWidth;
    struct Piece { std::string text; float advance; int width; };
    std::vector<Piece> pieces;
    float sum = 0;
    for (int begin = 0; begin < len;) {
        int end = begin + 1;
        if (text[begin] < '0' || text[begin] > '9')
            while (end < len && (text[end] < '0' || text[end] > '9')) ++end;
        std::string part(text + begin, end - begin);
        const int width = port.getTextWidth(part.c_str(), size, style, part.size());
        const auto* metrics = port.getTextFromCache(part.c_str(), part.size(), font, size, style);
        sum += metrics->advanceWidth;
        pieces.push_back({std::move(part), metrics->advanceWidth, width});
        begin = end;
    }
    // Preserve kerning and shaping across run boundaries by retaining the
    // original whole-string path whenever independent advances do not match.
    if (std::abs(sum - fullAdvance) > .01f) {
        graphics_drawTextRaster(port, text, len, quad, size, style, rgba);
        return;
    }
    float offset = 0;
    for (const auto& piece : pieces) {
        Quad slice;
        const float left = offset / fullWidth, right = (offset + piece.width) / fullWidth;
        for (int edge = 0; edge < 2; ++edge) {
            const int a = edge ? lftBot : lftTop, b = edge ? rgtBot : rgtTop;
            const auto& start = quad.points[a]; const auto& finish = quad.points[b];
            slice.points[a] = Point(start.x + (finish.x-start.x)*left, start.y + (finish.y-start.y)*left);
            slice.points[b] = Point(start.x + (finish.x-start.x)*right, start.y + (finish.y-start.y)*right);
        }
        graphics_drawTextRaster(port, piece.text.c_str(), piece.text.size(), slice, size, style, rgba);
        offset += piece.advance;
    }
}

ScopedOffscreenDrawing::ScopedOffscreenDrawing(Port* port, bool textOperation) {
    if (!textOperation) graphics_flushText();
    // Custom renderers can implement Port without the OpenGL backend's state.
    auto* implementation = dynamic_cast<PortImpl*>(port);
    if (implementation && implementation->mCameraCaptureDepth) return;
    if (implementation && implementation->mCameraCompositing) {
        auto capture=implementation->cameraDrawingSurface();
        if (capture) {
            cameraCapture=true; ++implementation->mCameraCaptureDepth;
            try { begin(*capture,implementation); } catch (...) {--implementation->mCameraCaptureDepth;throw;}
            return;
        }
    }
    if (implementation && implementation->mOffscreen) begin(*implementation->mOffscreen, implementation);
}

ScopedOffscreenDrawing::ScopedOffscreenDrawing(OffscreenSurface& offscreen, PortImpl* port) { begin(offscreen, port); }

void ScopedOffscreenDrawing::begin(OffscreenSurface& offscreen, PortImpl* port) {
    if (port && gDrawingPort == port && !cameraCapture) {
        GLint current=0;glGetIntegerv(GL_FRAMEBUFFER_BINDING,&current);
        if (static_cast<GLuint>(current)==offscreen.framebuffer) return;
    }
    graphics_flushText();
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
    graphics_flushText();
    if (cameraCapture) --target->mCameraCaptureDepth;
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

std::shared_ptr<OffscreenSurface> createOffscreenSurface(long width, long height, PortImpl* contextPort, bool preservePixels) {
    platform_startDrawing(contextPort->mPlatformWindowRef);
    if (!framebuffer::available()) return {};
    auto surface = std::make_shared<OffscreenSurface>();
    surface->contextPort = contextPort; surface->width = width; surface->height = height;
    surface->preservePixels=preservePixels;
    {
        ScopedOffscreenDrawing scope(*surface);
        GLint maximum = 0; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maximum);
        if (width <= 0 || height <= 0 || width > maximum || height > maximum) return {};
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
        if (framebuffer::CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return {};
        glDisable(GL_SCISSOR_TEST);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    std::erase_if(gOffscreenSurfaces, [](const auto& entry) { return entry.expired(); });
    gOffscreenSurfaces.push_back(surface);
    return surface;
}
bool PortImpl::initOffscreen(long width, long height, PortImpl* contextPort) {
    auto surface=createOffscreenSurface(width,height,contextPort);
    if (!surface) return false;
    mOffscreen=std::move(surface); setPortRects(Rect(width,height)); return true;
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
    if (preservePixels) readPixels(); // Private camera buffers never need CPU copies.
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

namespace { std::map<Port*,std::unique_ptr<ScopedOffscreenDrawing>> offscreenFrames; }
void PortImpl::beginCameraFrame() {
    mCameraFrame=true; mCameraPasses.clear();
    glGetIntegerv(GL_FRAMEBUFFER_BINDING,&mCameraDestinationFramebuffer);
    glGetIntegerv(GL_VIEWPORT,mCameraDestinationViewport);
    auto needs=[](Camera* camera) {return camera && (camera->isHidden() || camera->getOpacity()!=1 || camera->getFlashOpacity()>0 || (camera->mTransitionDestination && !camera->mTransitionIsCut) || (camera->mTransitionSource && !camera->mTransitionSource->mTransitionIsCut));};
    mCameraCompositing=needs(mCamera);
    for (auto* layer:mLayers) mCameraCompositing=mCameraCompositing || needs(layer->getEffectiveCamera());
    if (mCameraCompositing) for(auto* layer:mLayers) {
        auto* camera=layer->getEffectiveCamera();
        if (camera && !camera->isHidden() && camera->getOpacity()!=1) camera->validateSceneOrder();
    }
    if (!mCameraCompositing) {mCameraSurfaces.clear();mCameraBlendSurface.reset();mCameraWeightSurface.reset();mCameraScratchSurface.reset();}
}

std::shared_ptr<OffscreenSurface> PortImpl::cameraDrawingSurface() {
    if (!mCameraFrame || !mCameraCompositing) return {};
    Camera* camera=mLayerDrawingCamera ? mLayerDrawingCamera : (isCameraDrawingEnabled() ? getCamera() : nullptr);
    if (!mCameraPasses.empty() && mCameraPasses.back().camera==camera) return mCameraPasses.back().surface;
    if (camera && (camera->getOpacity()!=1 || (camera->mTransitionDestination && !camera->mTransitionIsCut) || (camera->mTransitionSource && !camera->mTransitionSource->mTransitionIsCut)) &&
        std::any_of(mCameraPasses.begin(),mCameraPasses.end(),[&](const auto& pass){return pass.camera==camera;}))
        throw std::logic_error("A composited Camera scene must be contiguous; keep other cameras and screen-space drawing outside its layers");
    auto* context=mOffscreen ? mOffscreen->contextPort : this;
    const long width=static_cast<long>(std::ceil(mDrawingRect.width())), height=static_cast<long>(std::ceil(mDrawingRect.height()));
    const size_t index=mCameraPasses.size();
    if (mCameraSurfaces.size()<=index) mCameraSurfaces.resize(index+1);
    auto& surface=mCameraSurfaces[index];
    if (!surface || !surface->contextPort || surface->width!=width || surface->height!=height)
        surface=createOffscreenSurface(width,height,context,false);
    if (!surface) throw std::runtime_error("Unable to allocate Camera render target");
    {
        ScopedOffscreenDrawing scope(*surface);
        glDisable(GL_SCISSOR_TEST);glClearColor(0,0,0,0);glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    if (camera) queueCameraEffects(camera);
    mCameraPasses.push_back({camera,surface});
    return surface;
}

namespace {
// Offscreen pixels are premultiplied. Weight RGB and alpha together, including
// when accumulating a crossfade; source-over between weighted scenes is wrong.
void drawCameraTexture(PortImpl& port, const OffscreenSurface& surface, float weight, bool additive, const Offset& shift = Offset(), bool multiply = false) {
    if (weight<=0) return;
    Rect shifted=port.getDrawingArea();
    shifted.left+=shift.x;shifted.right+=shift.x;shifted.top+=shift.y;shifted.bottom+=shift.y;
    const Rect rect=shifted.intersection(port.getDrawingArea()).intersection(port.getClipRect());
    if (rect.empty()) return;
    // Clip translated samples before submitting triangles. Some OpenGL ES
    // implementations drop fragments when clipping these quads at the viewport.
    // Crop texture coordinates with the geometry so the image does not stretch.
    const float u0=(rect.left-shifted.left)/shifted.width(),u1=(rect.right-shifted.left)/shifted.width();
    const float v0=(rect.top-shifted.top)/shifted.height(),v1=(rect.bottom-shifted.top)/shifted.height();
    port.setOpenGLModesForDrawing(true,blendMode_Normal,true);
    glEnable(GL_TEXTURE_2D);glBindTexture(GL_TEXTURE_2D,surface.texture);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBlendEquation(GL_FUNC_ADD);
    framebuffer::BlendFuncSeparate(GL_ONE,additive?GL_ONE:GL_ONE_MINUS_SRC_ALPHA,GL_ONE,additive?GL_ONE:GL_ONE_MINUS_SRC_ALPHA);
    if (multiply) framebuffer::BlendFuncSeparate(GL_DST_COLOR,GL_ZERO,GL_DST_ALPHA,GL_ZERO);
    glColor4f(weight,weight,weight,weight);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(u0,v0);glVertex2f(rect.left,rect.top);
    glTexCoord2f(u1,v0);glVertex2f(rect.right,rect.top);
    glTexCoord2f(u1,v1);glVertex2f(rect.right,rect.bottom);
    glTexCoord2f(u0,v0);glVertex2f(rect.left,rect.top);
    glTexCoord2f(u1,v1);glVertex2f(rect.right,rect.bottom);
    glTexCoord2f(u0,v1);glVertex2f(rect.left,rect.bottom);
    glEnd();glDisable(GL_TEXTURE_2D);
    gBoundTexture=GLuint(-1);port.mStateCache.resetState();
}
}

void PortImpl::finishCameraFrame() {
    const auto savedClip=getClipRect();
    struct Finish {
        PortImpl& port; Rect clip;
        ~Finish() {
            port.mCameraFrame=false;port.mCameraCompositing=false;port.mCameraPasses.clear();port.setClipRect(clip);
            for(auto* camera:port.mFrameCameras) camera->release();
            port.mFrameCameras.clear();
        }
    } finish{*this,savedClip};
    if (mCamera) queueCameraEffects(mCamera);
    const auto cameras=mFrameCameras;
    for (auto* camera:cameras) if (!camera->isHidden() && camera->getFlashOpacity()>0 &&
        std::none_of(mCameraPasses.begin(),mCameraPasses.end(),[&](const auto& pass){return pass.camera==camera;})) {
        auto* previous=mLayerDrawingCamera;mLayerDrawingCamera=camera;
        cameraDrawingSurface();mLayerDrawingCamera=previous;
    }
    mCameraCompositing=false;
    // Include each flash in its camera image, before scene opacity/transition.
    for (size_t i=0;i<mCameraPasses.size();++i) {
        auto& pass=mCameraPasses[i];
        if (!pass.camera || pass.camera->isHidden() || pass.camera->getFlashOpacity()==0) continue;
        if (std::any_of(mCameraPasses.begin()+i+1,mCameraPasses.end(),[&](const auto& later){return later.camera==pass.camera;})) continue;
        ++mCameraCaptureDepth;
        struct Depth {unsigned& depth;~Depth(){--depth;}} depth{mCameraCaptureDepth};
        ScopedOffscreenDrawing scope(*pass.surface,this);
        gModesSet=false;setClipRect(pass.camera->getViewport().intersection(mDrawingRect));
        pass.camera->drawEffects(*this);
    }
    // Restore the frame's destination after effect captures above.
    framebuffer::BindFramebuffer(GL_FRAMEBUFFER,mCameraDestinationFramebuffer);
    glViewport(mCameraDestinationViewport[0],mCameraDestinationViewport[1],mCameraDestinationViewport[2],mCameraDestinationViewport[3]);gModesSet=false;mClipChanged=true;
    for (size_t i=0;i<mCameraPasses.size();++i) {
        auto& pass=mCameraPasses[i]; auto* camera=pass.camera;
        Camera* source=camera && camera->mTransitionActive && !camera->mTransitionIsCut ? camera : camera && camera->mTransitionSource && camera->mTransitionSource->mTransitionActive && !camera->mTransitionSource->mTransitionIsCut ? camera->mTransitionSource : nullptr;
        if (source) {
            auto find=[&](Camera* item) {return std::find_if(mCameraPasses.begin(),mCameraPasses.end(),[&](const auto& entry){return entry.camera==item;});};
            const auto from=find(source),to=find(source->mTransitionDestination);
            // An empty scene is transparent; still blend the other scene correctly.
            const size_t last=std::max(from==mCameraPasses.end()?i:static_cast<size_t>(from-mCameraPasses.begin()),to==mCameraPasses.end()?i:static_cast<size_t>(to-mCameraPasses.begin()));
            if (i!=last) continue;
            const size_t first=std::min(from==mCameraPasses.end()?i:static_cast<size_t>(from-mCameraPasses.begin()),to==mCameraPasses.end()?i:static_cast<size_t>(to-mCameraPasses.begin()));
            for(size_t position=first+1;position<last;++position) {
                auto* other=mCameraPasses[position].camera;
                if (other!=source && other!=source->mTransitionDestination && (!other || !other->getViewport().intersection(source->getViewport()).empty()))
                    throw std::logic_error("Crossfade scenes must keep overlapping camera and screen-space drawing outside their scene pair");
            }
            const auto viewport=source->getViewport().intersection(mDrawingRect);
            auto* context=mOffscreen?mOffscreen->contextPort:this;
            if (!mCameraBlendSurface || !mCameraBlendSurface->contextPort || mCameraBlendSurface->width!=std::ceil(mDrawingRect.width()) || mCameraBlendSurface->height!=std::ceil(mDrawingRect.height()))
                mCameraBlendSurface=createOffscreenSurface(std::ceil(mDrawingRect.width()),std::ceil(mDrawingRect.height()),context,false);
            if (!mCameraBlendSurface) throw std::runtime_error("Unable to allocate Camera crossfade target");
            {
                ++mCameraCaptureDepth;
                struct Depth {unsigned& depth;~Depth(){--depth;}} depth{mCameraCaptureDepth};
                ScopedOffscreenDrawing scope(*mCameraBlendSurface);
                glDisable(GL_SCISSOR_TEST);glClearColor(0,0,0,0);glClear(GL_COLOR_BUFFER_BIT);
                gModesSet=false;setClipRect(viewport);mClipChanged=true;
                const float progress=source->transitionBlendProgress();
                if (source->mTransitionStyle==camera_Crossfade) {
                    if (from!=mCameraPasses.end()) drawCameraTexture(*this,*from->surface,(1-progress)*source->getOpacity(),true);
                    if (to!=mCameraPasses.end()) drawCameraTexture(*this,*to->surface,progress*source->mTransitionDestination->getOpacity(),true);
                } else if (source->mTransitionStyle>=camera_WhipLeft) {
                    const Rect area=source->getViewport();
                    const bool horizontal=source->mTransitionStyle==camera_WhipLeft || source->mTransitionStyle==camera_WhipRight;
                    const int sign=(source->mTransitionStyle==camera_WhipLeft || source->mTransitionStyle==camera_WhipUp)?-1:1;
                    const float extent=horizontal?area.width():area.height();
                    const int samples=source->mTransitionBlur>0 && progress>0 && progress<1 ? 8 : 1;
                    // Preserve the original 0.65-second look; the same shutter
                    // exposure covers more distance when the requested pan is faster.
                    const double exposure=source->mTransitionSeconds>0 ? source->mTransitionBlur*.15*.65/source->mTransitionSeconds : 0;
                    const float spread=static_cast<float>(std::min(1.,exposure))*std::sin(std::numbers::pi_v<float>*progress);
                    for (int sample=0;sample<samples;++sample) {
                        const float t=std::clamp(progress+spread*((sample+.5f)/samples-.5f),0.f,1.f);
                        const float distance=std::floor(extent*t);
                        const Offset fromShift(horizontal?sign*distance:0,horizontal?0:sign*distance);
                        const Offset toShift(horizontal?sign*(distance-extent):0,horizontal?0:sign*(distance-extent));
                        if (from!=mCameraPasses.end()) drawCameraTexture(*this,*from->surface,source->getOpacity()/samples,true,fromShift);
                        if (to!=mCameraPasses.end()) drawCameraTexture(*this,*to->surface,source->mTransitionDestination->getOpacity()/samples,true,toShift);
                    }
                } else if (source->mTransitionStyle==camera_LumaFade) {
                    // Freeze only the mask at the first rendered transition frame.
                    const Rect area=source->getViewport();
                    if (source->mTransitionLuminance.empty()) {
                        const long width=std::max(1L,static_cast<long>(std::min(static_cast<float>(mCameraBlendSurface->width),std::ceil(area.width()))));
                        const long height=std::max(1L,static_cast<long>(std::min(static_cast<float>(mCameraBlendSurface->height),std::ceil(area.height()))));
                        source->mTransitionMaskWidth=width;source->mTransitionMaskHeight=height;
                        source->mTransitionLuminance.resize(static_cast<size_t>(width)*height);
                        if (!source->mTransitionMask && from!=mCameraPasses.end()) from->surface->readPixels();
                        auto linear=[](float value) {return value<=.04045f?value/12.92f:std::pow((value+.055f)/1.055f,2.4f);};
                        for (long y=0;y<height;++y) for(long x=0;x<width;++x) {
                            Color color(0.f,0.f,0.f,0.f);
                            if (auto* mask=source->mTransitionMask) {
                                color=mask->getPixel(std::min(mask->getWidth()-1,x*mask->getWidth()/width),std::min(mask->getHeight()-1,y*mask->getHeight()/height));
                            } else if (from!=mCameraPasses.end()) {
                                auto& surface=*from->surface;
                                const long px=static_cast<long>(std::floor(area.left+(x+.5f)*area.width()/width-mDrawingRect.left)),py=static_cast<long>(std::floor(area.top+(y+.5f)*area.height()/height-mDrawingRect.top));
                                if(px>=0 && py>=0 && px<surface.width && py<surface.height) {
                                    const auto index=(static_cast<size_t>(py)*surface.width+px)*4;
                                    color=Color(surface.pixels[index]/255.f,surface.pixels[index+1]/255.f,surface.pixels[index+2]/255.f,surface.pixels[index+3]/255.f);
                                }
                            }
                            source->mTransitionLuminance[static_cast<size_t>(y)*width+x]=color.alpha>0 ? .2126f*linear(color.red)+.7152f*linear(color.green)+.0722f*linear(color.blue):0;
                        }
                    }
                    auto ensure=[&](std::shared_ptr<OffscreenSurface>& target) {
                        if (!target || !target->contextPort || target->width!=mCameraBlendSurface->width || target->height!=mCameraBlendSurface->height)
                            target=createOffscreenSurface(mCameraBlendSurface->width,mCameraBlendSurface->height,context,false);
                        if (!target) throw std::runtime_error("Unable to allocate luma transition target");
                    };
                    ensure(mCameraWeightSurface);ensure(mCameraScratchSurface);
                    auto& mask=*mCameraWeightSurface;
                    mask.pixels.resize(static_cast<size_t>(mask.width)*mask.height*4);
                    for (long y=0;y<mask.height;++y) for(long x=0;x<mask.width;++x) {
                        const long mx=std::clamp(static_cast<long>((x+mDrawingRect.left-area.left)*source->mTransitionMaskWidth/area.width()),0L,source->mTransitionMaskWidth-1);
                        const long my=std::clamp(static_cast<long>((y+mDrawingRect.top-area.top)*source->mTransitionMaskHeight/area.height()),0L,source->mTransitionMaskHeight-1);
                        const float luma=source->mTransitionLuminance[static_cast<size_t>(my)*source->mTransitionMaskWidth+mx];
                        const float threshold=source->mTransitionDarkFirst?luma:1-luma;
                        const float softness=source->mTransitionSoftness;
                        float reveal=progress<=0?0:progress>=1?1:softness==0?(progress>=threshold?1:0):std::clamp((progress*(1+softness)-threshold)/softness,0.f,1.f);
                        reveal=reveal*reveal*(3-2*reveal);
                        const uint8 value=static_cast<uint8>(std::round(255*(1-reveal)));
                        const auto index=(static_cast<size_t>(y)*mask.width+x)*4;
                        std::fill_n(mask.pixels.data()+index,4,value);
                    }
                    auto upload=[&] {
                        glBindTexture(GL_TEXTURE_2D,mask.texture);glPixelStorei(GL_UNPACK_ALIGNMENT,4);
                        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,mask.width,mask.height,GL_RGBA,GL_UNSIGNED_BYTE,mask.pixels.data());
                    };
                    upload();
                    if (from!=mCameraPasses.end()) drawCameraTexture(*this,*from->surface,source->getOpacity(),false);
                    drawCameraTexture(*this,mask,1,false,Offset(),true);
                    for (auto& value:mask.pixels) value=255-value;
                    upload();
                    {
                        ScopedOffscreenDrawing scratch(*mCameraScratchSurface);
                        glDisable(GL_SCISSOR_TEST);glClearColor(0,0,0,0);glClear(GL_COLOR_BUFFER_BIT);
                        gModesSet=false;setClipRect(viewport);mClipChanged=true;
                        if (to!=mCameraPasses.end()) drawCameraTexture(*this,*to->surface,source->mTransitionDestination->getOpacity(),false);
                        drawCameraTexture(*this,mask,1,false,Offset(),true);
                    }
                    gModesSet=false;setClipRect(viewport);mClipChanged=true;
                    drawCameraTexture(*this,*mCameraScratchSurface,1,true);
                } else {
                    // Partition the viewport at one pixel boundary. Each scene
                    // keeps its own opacity, with no gap or overlapping strips.
                    Rect revealed=source->getViewport(),remaining=revealed;
                    const float width=std::floor(revealed.width()*progress),height=std::floor(revealed.height()*progress);
                    switch (source->mTransitionStyle) {
                    case camera_WipeLeft: revealed.left=revealed.right-width;remaining.right=revealed.left;break;
                    case camera_WipeRight: revealed.right=revealed.left+width;remaining.left=revealed.right;break;
                    case camera_WipeUp: revealed.top=revealed.bottom-height;remaining.bottom=revealed.top;break;
                    case camera_WipeDown: revealed.bottom=revealed.top+height;remaining.top=revealed.bottom;break;
                    }
                    remaining=remaining.intersection(viewport);revealed=revealed.intersection(viewport);
                    if (from!=mCameraPasses.end() && !remaining.empty()) {
                        setClipRect(remaining);drawCameraTexture(*this,*from->surface,source->getOpacity(),false);
                    }
                    if (to!=mCameraPasses.end() && !revealed.empty()) {
                        setClipRect(revealed);drawCameraTexture(*this,*to->surface,source->mTransitionDestination->getOpacity(),false);
                    }
                }
            }
            gModesSet=false;mClipChanged=true;setClipRect(viewport);
            drawCameraTexture(*this,*mCameraBlendSurface,1,false);
        } else {
            if (camera && camera->isHidden()) continue;
            setClipRect(camera?camera->getViewport().intersection(mDrawingRect):mDrawingRect);
            drawCameraTexture(*this,*pass.surface,camera?camera->getOpacity():1,false);
        }
    }
    mCameraSurfaces.resize(mCameraPasses.size());
}
void graphics_startDrawing(Port* port) {
    graphics_flushText();
    auto* offscreenPort=dynamic_cast<PortImpl*>(port);
    if (offscreenPort->mTextLabelsDrawn && offscreenPort->mNewTextLabels > offscreenPort->mTextLabelsDrawn / 2)
        offscreenPort->mTextChurnFrames = std::min(2u, offscreenPort->mTextChurnFrames + 1);
    else offscreenPort->mTextChurnFrames = 0;
    offscreenPort->mDigitCacheEnabled = offscreenPort->mTextChurnFrames >= 2;
    offscreenPort->mTextLabelsDrawn = offscreenPort->mNewTextLabels = 0;
    if (offscreenPort->mOffscreen) {
        offscreenFrames[port]=std::make_unique<ScopedOffscreenDrawing>(port);
        port->clear(); offscreenPort->beginCameraFrame(); return;
    }
	pdg::PortImpl* thePort = dynamic_cast<pdg::PortImpl*>(port);
	platform_startDrawing(thePort->mPlatformWindowRef);
    gDrawingPort = thePort;
	GLsizei w = thePort->getDrawingArea().width();
	GLsizei h = thePort->getDrawingArea().height();
	long drawableWidth = 0, drawableHeight = 0;
	platform_getWindowDrawableSize(thePort->mPlatformWindowRef, &drawableWidth, &drawableHeight);
	const bool rotated = gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise
	    || gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise;
	thePort->mDrawableScaleX = drawableWidth > 0 && (rotated ? h : w) > 0
	    ? float(drawableWidth) / (rotated ? h : w) : 1.0f;
	thePort->mDrawableScaleY = drawableHeight > 0 && (rotated ? w : h) > 0
	    ? float(drawableHeight) / (rotated ? w : h) : 1.0f;
	glViewport(0, 0, drawableWidth > 0 ? drawableWidth : (rotated ? h : w),
	    drawableHeight > 0 ? drawableHeight : (rotated ? w : h));
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
    thePort->beginCameraFrame();
}

void graphics_finishDrawing(Port* port) {
    graphics_flushText();
    auto* implementation=dynamic_cast<PortImpl*>(port);
    try {
        if (implementation->mCameraCompositing) implementation->finishCameraFrame();
        else {implementation->mCameraFrame=false;port->finishCameraEffects();}
    } catch (...) {
        offscreenFrames.erase(port);
        throw;
    }
    if (offscreenFrames.erase(port)) return;
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

Port&
Port::setClipRect(const Rect& rect) {
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
    if (port.mClipRect != rect.intersection(port.mDrawingRect)) graphics_flushText();
    // Preserve fractional coordinates and distinguish empty from the full-area reset.
    port.mClipRect = rect.intersection(port.mDrawingRect);
    mClipChanged = true;
    return *this;
}

Port& Port::clear(const Color& color) {
    auto& implementation=static_cast<PortImpl&>(*this);
    const bool composing=implementation.mCameraCompositing;
    if (!implementation.mCameraCaptureDepth) { implementation.mCameraCompositing=false; implementation.mCameraPasses.clear(); }
    struct Restore {PortImpl& port;bool composing;~Restore(){port.mCameraCompositing=composing;}} restore{implementation,composing};
    ScopedOffscreenDrawing scope(this);
    auto& port = static_cast<PortImpl&>(*this);
    port.setOpenGLModesForDrawing(false);
    GLfloat previous[4]; glGetFloatv(GL_COLOR_CLEAR_VALUE, previous);
    const float alpha = std::clamp(color.alpha, 0.0f, 1.0f);
    const float rgbScale = (port.mOffscreen || port.mCameraCaptureDepth) ? alpha : 1.0f;
    glClearColor(color.red * rgbScale, color.green * rgbScale, color.blue * rgbScale, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(previous[0], previous[1], previous[2], previous[3]);
    port.mNeedRedraw = gPortDirty = true;
    return *this;
}

Port& Port::setDrawingOrigin(const Point& origin) {
    auto& port = static_cast<PortImpl&>(*this);
    if (!port.mOffscreen) throw std::invalid_argument("Drawing origin requires an offscreen Port");
    if (!std::isfinite(origin.x) || !std::isfinite(origin.y)) throw std::invalid_argument("Drawing origin must be finite");
    port.setPortRects(Rect(origin, port.mDrawingRect.width(), port.mDrawingRect.height()));
    gModesSet = false;
    return *this;
}

Port& Port::resetClipRect() { return setClipRect(getDrawingArea()); }

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
Port&
Port::setFont(Font* font)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if (!font) {
		font = port.mGraphicsMgr->createFont("Arial");
	}
	if (!font) {
		DEBUG_ONLY( OS::_DOUT("Port::setFont() font is null, and Arial font not found"); )
		return *this;
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
    return *this;
}

// set the name of the font used for a particular style of text in this port
// does not affect what font is used for any other styles
// NOTE: only works for textStyle_Bold at the moment
Port&
Port::setFontForStyle(Font* font, uint32 style)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	if (!font) {
		font = port.mGraphicsMgr->createFont("Arial");
	}
	if (!font) {
		DEBUG_ONLY( OS::_DOUT("Port::setFontForStyle() font is null, and Arial font not found"); )
		return *this;
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
    return *this;
}

// set a factor by which all font sizes are enlarged or reduced
// > 1.0 is enlarge, < 1.0 is reduce, 1.0 is no scaling
Port&
Port::setFontScalingFactor(float scaleBy)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	port.mFontScalingFactor = scaleBy;
    return *this;
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
	// Keep material calls valid on desktop GL and OpenGL ES 1.x. The ES
	// API accepts only FRONT_AND_BACK; FRONT leaves the default grey material.
	GLfloat mat_diffuse[] = { color.red * (1.0f - 0.5f * std::clamp(ambientLight.red, 0.0f, 1.0f)),
		color.green * (1.0f - 0.5f * std::clamp(ambientLight.green, 0.0f, 1.0f)),
		color.blue * (1.0f - 0.5f * std::clamp(ambientLight.blue, 0.0f, 1.0f)), color.alpha };
	GLfloat mat_ambient[] = { color.red * 0.75f, color.green * 0.75f, color.blue * 0.75f, color.alpha };
	GLfloat mat_specular[] = { color.red * 0.1f, color.green * 0.1f, color.blue * 0.1f, 1.0f };
	GLfloat mat_shininess[] = { 20.0f };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	
	// Setup lighting
	float degreesRot = rotation * 180.0 / std::numbers::pi;
	static GLfloat light_position[] = { 0, 0, -10, 1 };
	GLfloat model_ambient[] = { ambientLight.red, ambientLight.green, ambientLight.blue, ambientLight.alpha };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	
	const GLboolean normalizeWasEnabled = glIsEnabled(GL_NORMALIZE);
	glEnable(GL_NORMALIZE);
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
	if (!normalizeWasEnabled) glDisable(GL_NORMALIZE);
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
Port&
Port::setCursor(Image* cursorImage, const Point& hotSpot)
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data

    if (!cursorImage) return *this;
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
    return *this;
}

Image*
Port::getCursor()
{
    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	return port.mCurrentCursor;
}

Port&
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
    return *this;
}

int
Port::startTrackingMouse(const Rect& rect, void* userData)
{
//    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	// TODO: call private methods in PortImp to add a tracking rect
	return 0;
}

Port&
Port::stopTrackingMouse(int trackingRef)
{
//    PortImpl& port = static_cast<PortImpl&>(*this); // get us access to our private data
	// TODO: call private methods in PortImp to remove a tracking rect
    return *this;
}

Port::Port() : mClipChanged(false)
{
#ifdef PDG_COMPILING_FOR_SCRIPT_BINDINGS
	INIT_SCRIPT_OBJECT(mPortScriptObj);
#endif
}

Port::~Port()
{
    while (!mLayers.empty()) mLayers.back()->setSpritePort(nullptr);
    for (auto* camera:mFrameCameras) camera->release();
    mFrameCameras.clear();
    if (mCamera) {mCamera->mViewport=getDrawingArea();mCamera->mHasViewport=true;mCamera->mOwnerPort=nullptr;mCamera->detach();mCamera=nullptr;}
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
    graphics_flushText();
//	if (avoidRecursion) return;
//	avoidRecursion = true;
    if (!gModesSet) {
        long width = mDrawingRect.width();
        long height = mDrawingRect.height();
        long swidth = width;
        long sheight = height;
		if (!mOffscreen && !mCameraCaptureDepth && ((gEffectiveScreenPos == pdg::screenPos_Rotated90Clockwise)
            || (gEffectiveScreenPos == pdg::screenPos_Rotated90CounterClockwise))) {
            sheight = width;
            swidth = height;
        }

        // set orthograhic 1:1  pixel transform in local view coords
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(2.0f / swidth, ((mOffscreen || mCameraCaptureDepth) ? 2.0f : -2.0f) / sheight, 1.0f);
        if (!mOffscreen && !mCameraCaptureDepth) glRotatef(gRotationAngle, 0, 0, 1);
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
				if (mOffscreen || mCameraCaptureDepth) framebuffer::BlendFuncSeparate(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
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
				if (mOffscreen || mCameraCaptureDepth) framebuffer::BlendFuncSeparate(premultiplied ? GL_ONE : GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
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
            const float left = mClipRect.left - mDrawingRect.left;
            const float top = mClipRect.top - mDrawingRect.top;
            const float right = mClipRect.right - mDrawingRect.left;
            const float bottom = mClipRect.bottom - mDrawingRect.top;
            const float width = mDrawingRect.width(), height = mDrawingRect.height();
            Rect clip(left, top, right, bottom);
            const bool offscreen = mOffscreen || mCameraCaptureDepth;
            bool flipX = false, flipY = false;
            if (!offscreen) {
                if (gEffectiveScreenPos == screenPos_Rotated180) {
                    clip = Rect(width - right, top, width - left, bottom);
                    flipX = true;
                } else if (gEffectiveScreenPos == screenPos_Rotated90Clockwise)
                    clip = Rect(top, left, bottom, right);
                else if (gEffectiveScreenPos == screenPos_Rotated90CounterClockwise) {
                    clip = Rect(height - bottom, width - right, height - top, width - left);
                    flipX = flipY = true;
                } else {
                    clip = Rect(left, height - bottom, right, height - top);
                    flipY = true;
                }
            }
            const float sx = offscreen ? 1.0f : mDrawableScaleX;
            const float sy = offscreen ? 1.0f : mDrawableScaleY;
            // Reversing an axis also reverses which edge includes pixel centers.
            const auto edge = [](float coordinate, float scale, bool flipped) {
                return int(flipped ? std::floor(coordinate * scale + 0.5f)
                    : std::ceil(coordinate * scale - 0.5f));
            };
            const int x0 = edge(clip.left, sx, flipX), x1 = edge(clip.right, sx, flipX);
            const int y0 = edge(clip.top, sy, flipY), y1 = edge(clip.bottom, sy, flipY);
            glScissor(x0, y0, std::max(0, x1 - x0), std::max(0, y1 - y0));
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
    FontCacheEntry::detachPort(this);
    // Window teardown invalidates texture IDs before destroying its context.
    // Offscreen teardown keeps that context current and releases textures here.
    mTextCache.clear();
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
    const size_t revision = mTextCache.textureRevision();
    auto* entry = mTextCache.find(text, len, font, size, style);
    if (revision != mTextCache.textureRevision()) mStateCache.resetState();
    return entry;
}

void PortImpl::addTextToCache(TextCacheEntry* entry) {
    const size_t revision = mTextCache.textureRevision();
    mTextCache.uploaded(entry);
    if (revision != mTextCache.textureRevision()) mStateCache.resetState();
}

void PortImpl::invalidateTextCache() {
    graphics_flushText();
    mTextCache.invalidateTextures();
}

} // end namespace pdg

#endif // PDG_NO_GUI
