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

typedef char* addr;

namespace pdg {

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
	void		setOpenGLModesForDrawing(bool useAlpha, BlendMode blendMode = blendMode_Normal);
	const pdg::Rect&  drawableRect() { return mClipRect.empty() ? mDrawingRect : mClipRect; }

    void setPortRects(Rect portRect) { mDrawingRect = portRect; mClipRect = portRect; }

    // Image cache management (new key-based system)
    CacheKey getCacheKey(const char* sourceName, int width, int height, bool useEdgeClamp);
    GLuint getTexture(CacheKey key);
    void setTexture(CacheKey key, GLuint texture);
    void releaseCachedEntry(CacheKey key);
    void beginFrame();
    
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

    Image*          mCurrentCursor;
    Point           mHotSpot;
    addr            mCurrentCursorBackground;
    long            mCurrentCursorBackgroundSize;

	Font*			mFontForStyle[NUM_TEXT_STYLES];
	float			mFontScalingFactor;

	ImageCache*		mImageCache;       // hash-based image cache for this port
	TextCacheEntry* mTextCache;        // text cache for this port
	int				mPortIndex;        // unique index for this port
	OpenGLStateCache mStateCache;      // OpenGL texture binding cache for this port

    void* 			mPlatformWindowRef;  // we don't know what this is, we just carry it around
    									// and pass it to platform_xxx calls

};

void graphics_drawText(PortImpl& port, const char* text, int len, const Quad& quad, int size, uint32 style, Color rgba);

} // end namespace pdg

#endif // PDG_GRAPHICS_OPENGL_H_INCLUDED

