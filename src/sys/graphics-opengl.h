// -----------------------------------------------
// graphics-opengl.h
//
// OpenGL based implementation of port based
// graphics functionality
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


#ifndef PDG_GRAPHICS_OPENGL_H_INCLUDED
#define PDG_GRAPHICS_OPENGL_H_INCLUDED

#include "pdg_project.h"

#include "pdg/sys/platform.h"
#include "pdg/sys/graphics.h"

#include "internals.h"

#include "font-impl.h"
#include "imagecache-opengl.h"
#include "imagecache-opengl-v2.h"
#include "textcache-opengl.h"
#include "opengl-state-cache.h"

#include <string>
#include <memory>
#include <vector>

typedef char* addr;

namespace pdg {

struct OffscreenSurface {
    PortImpl* contextPort = nullptr;
    GLuint framebuffer = 0, texture = 0, depth = 0;
    long width = 0, height = 0;
    uint64 revision = 1, pixelRevision = 0;
    std::vector<uint8> pixels; // straight RGBA, populated only for explicit CPU access
    bool preservePixels = true;
    ~OffscreenSurface();
    void readPixels();
    void releaseContext();
};
void releaseOffscreenSurfacesForContext(PortImpl* port);
std::shared_ptr<OffscreenSurface> createOffscreenSurface(long width, long height, PortImpl* contextPort, bool preservePixels = true);

class PortImpl : public Port {
public:
    PortImpl(GraphicsManager* graphicsMgr);
    virtual ~PortImpl();

	void        internalDrawCursor();
	void        internalSaveCursorBackground();
	void        internalRestoreCursorBackground();
    virtual bool        lockDrawingSurface();
    virtual void        unlockDrawingSurface();
    void        resizePort(long width, long height);
	void		setOpenGLModesForDrawing(bool useAlpha, BlendMode blendMode = blendMode_Normal, bool premultiplied = false);
	const pdg::Rect&  drawableRect() { return mClipRect; }

    void setPortRects(Rect portRect) { mDrawingRect = portRect; mClipRect = portRect; mClipChanged = true; }

    // Image cache management (new key-based system)
    CacheKey getCacheKey(const char* sourceName, int width, int height, bool useEdgeClamp);
    GLuint getTexture(CacheKey key);
    void setTexture(CacheKey key, GLuint texture);
    void releaseCachedEntry(CacheKey key);
    void beginFrame();
    bool initOffscreen(long width, long height, PortImpl* contextPort);
    
    // Legacy image cache methods (deprecated)
    ImageCacheEntry* getImageFromCache(const char* sourceName, int width, int height, bool useEdgeClamp);
    void addImageToCache(ImageCacheEntry* entry);
    void invalidateImageCache();
    
    // Text cache management
    TextCacheEntry* getTextFromCache(const char* text, int len, FontImpl* font, int size, uint32 style);
    void addTextToCache(TextCacheEntry* entry);
    void invalidateTextCache();

public: // public for sys framework implementation, nobody else
	GraphicsManager* mGraphicsMgr;

    bool            mNeedRedraw;
    Rect            mDrawingRect;
    Rect            mClipRect;
    float           mDrawableScaleX = 1.0f;
    float           mDrawableScaleY = 1.0f;
    size_t          mTextLabelsDrawn = 0, mNewTextLabels = 0;
    unsigned        mTextChurnFrames = 0;
    bool            mDigitCacheEnabled = false;

    Image*          mCurrentCursor;
    Point           mHotSpot;
    addr            mCurrentCursorBackground;
    long            mCurrentCursorBackgroundSize;

	Font*			mFontForStyle[NUM_TEXT_STYLES];
	float			mFontScalingFactor;

	ImageCache*		mImageCache;       // hash-based image cache for this port
	TextCache mTextCache;        // text cache for this port
	int				mPortIndex;        // unique index for this port
	OpenGLStateCache mStateCache;      // OpenGL texture binding cache for this port

    void* 			mPlatformWindowRef;  // we don't know what this is, we just carry it around
    									// and pass it to platform_xxx calls

    std::shared_ptr<OffscreenSurface> mOffscreen;
    // Private frame buffers. They are not registered as Ports or exposed as Images.
    struct CameraPass { Camera* camera; std::shared_ptr<OffscreenSurface> surface; };
    std::vector<CameraPass> mCameraPasses;
    std::vector<std::shared_ptr<OffscreenSurface>> mCameraSurfaces;
    std::shared_ptr<OffscreenSurface> mCameraWeightSurface, mCameraScratchSurface;
    std::shared_ptr<OffscreenSurface> mCameraBlendSurface;
    bool mCameraFrame = false, mCameraCompositing = false;
    unsigned mCameraCaptureDepth = 0;
    GLint mCameraDestinationFramebuffer=0, mCameraDestinationViewport[4]{};
    void beginCameraFrame();
    void finishCameraFrame();
    std::shared_ptr<OffscreenSurface> cameraDrawingSurface();
};

// Redirect an offscreen operation, restoring the caller's framebuffer and drawing state.
class ScopedOffscreenDrawing {
public:
    explicit ScopedOffscreenDrawing(Port* port, bool textOperation = false);
    explicit ScopedOffscreenDrawing(OffscreenSurface& surface, PortImpl* port = nullptr);
    ~ScopedOffscreenDrawing();
    ScopedOffscreenDrawing(const ScopedOffscreenDrawing&) = delete;
    ScopedOffscreenDrawing& operator=(const ScopedOffscreenDrawing&) = delete;
private:
    void begin(OffscreenSurface& surface, PortImpl* port);
    PortImpl* target = nullptr;
    PortImpl* previous = nullptr;
    OffscreenSurface* surface = nullptr;
    bool cameraCapture = false;
    bool switchedContext = false, savedDirty = false;
    GLint framebuffer = 0, texture = 0, renderbuffer = 0, matrixMode = 0, packAlignment = 4;
    GLint viewport[4], scissor[4];
    GLfloat modelview[16], projection[16], clearColor[4];
    GLboolean scissorEnabled = false;
};

void graphics_drawText(PortImpl& port, const char* text, int len, const Quad& quad, int size, uint32 style, Color rgba);
void graphics_drawTextRaster(PortImpl& port, const char* text, int len, const Quad& quad, int size, uint32 style,
                             Color rgba, TextCacheEntry* cachedEntry = nullptr);
void graphics_submitText(PortImpl& port, const TextCacheEntry& entry, const Quad& quad, Color color,
                         bool premultiplied = false, bool bottomOrigin = false);
void graphics_flushText();

} // end namespace pdg

#endif // PDG_GRAPHICS_OPENGL_H_INCLUDED
