// -----------------------------------------------
// textcache-opengl.h
//
// Caching for OpenGL text drawing
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


#ifndef PDG_TEXTCACHE_OPENGL_H_INCLUDED
#define PDG_TEXTCACHE_OPENGL_H_INCLUDED

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include <memory>

#include "include-opengl.h"
#include "font-impl.h"

// Forward declaration
class PortImpl;

namespace pdg {

class OpenGLStateCache;
struct TextAtlasPage {
    GLuint texture = 0;
    GLenum format = GL_ALPHA;
    int size = 1024, x = 0, y = 0, rowHeight = 0;
    size_t bytes = 0;
    ~TextAtlasPage();
};

	
struct FontCacheEntry {

	// cache management
	FontCacheEntry* nextEntry;
	
	// here's what we use to find the item in the cache
	std::string	 mFontName;
	float scalingFactor;
	
	// and here's the information we cache
	FontImpl* mFont;
	
	// constructor, find in cache
	
	FontCacheEntry( const char* inFontName, float inScalingFactor );

	static FontCacheEntry*  findFontInCache(const char* inFontName, float inScalingFactor );
	static void detachPort(Port* port);
	
private:
	FontCacheEntry() {}
	FontCacheEntry(FontCacheEntry&) {}
	static void             addEntryToCache(FontCacheEntry* textInfo);
};

struct TextCacheEntry {
	
	// cache management
	
	// here's what we use to find the item in the cache
	FontImpl*    mFont;
	std::string  mText;
	int			 len;
	int			 size;
	uint32		 style;
	
	// and here's the information we cache
	GLuint		 texture;
	size_t       textureBytes = 0;
	bool         measured = false;
    float        advanceWidth = 0;
    unsigned char drawCount = 0;
    std::shared_ptr<TextAtlasPage> atlas;
    int atlasX = 0, atlasY = 0, sourceWidth = 0, sourceHeight = 0;
    float u0 = 0, v0 = 0;
    bool atlasCoordinates = false;
	int			 charHeight;
	int			 ascent;
	int			 width;
	float		 tx;
	float		 ty;
	float		 tx_topoffset;
	
	TextCacheEntry( const char* inText, int inLen, FontImpl* font, int inSize, uint32 inStyle);
	
	~TextCacheEntry();
	TextCacheEntry(const TextCacheEntry&) = delete;
};

// Measurement entries and textures have the same owner. Texture creation never
// inserts an entry a second time, including after context loss.
class TextCache {
public:
    explicit TextCache(size_t maxEntries = 4096, size_t maxBytes = 16 * 1024 * 1024)
        : mMaxEntries(std::max(size_t(1), maxEntries)), mMaxBytes(maxBytes) {}
    TextCacheEntry* find(const char* text, int len, FontImpl* font, int size, uint32 style);
    void uploaded(TextCacheEntry* entry);
    void reserveTexture(TextCacheEntry* entry, int width, int height, GLenum format,
                         OpenGLStateCache& state, bool repeatStandalone = false);
    void uploadPixels(TextCacheEntry* entry, const void* pixels, int width, int height, GLenum format,
                       OpenGLStateCache& state, int rowAlignment = 1, bool repeatStandalone = false);
    void invalidateTextures();
    void clear();
    size_t count() const { return mEntries.size(); }
    size_t bytes() const { return mBytes; }
    size_t textureRevision() const { return mTextureRevision; }
private:
    struct Key {
        std::string text;
        FontImpl* font;
        int size;
        uint32 style;
        bool operator==(const Key& other) const {
            return font == other.font && size == other.size && style == other.style && text == other.text;
        }
    };
    struct Hash { size_t operator()(const Key& key) const; };
    struct Item {
        std::unique_ptr<TextCacheEntry> entry;
        std::list<Key>::iterator recency;
        size_t bytes = 0;
    };
    void trim(TextCacheEntry* keep);
    void releaseEmptyPages();
    size_t mMaxEntries, mMaxBytes, mBytes = 0, mTextureRevision = 0;
    std::list<Key> mRecency;
    std::unordered_map<Key, Item, Hash> mEntries;
    std::list<std::shared_ptr<TextAtlasPage>> mPages;
};


} // end namespace pdg

#endif // PDG_NO_GUI
#endif // PDG_TEXTCACHE_OPENGL_H_INCLUDED
