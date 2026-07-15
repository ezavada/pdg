// -----------------------------------------------
// imagecache-opengl-v2.h
//
// Hash-based caching for OpenGL image drawing
// Replaces linked list with unordered_map for O(1) lookups
//
// Written by Ed Zavada, 2025
// Copyright (c) 2025, Dream Rock Studios, LLC, and the authors.
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

#ifndef PDG_IMAGECACHE_OPENGL_V2_H_INCLUDED
#define PDG_IMAGECACHE_OPENGL_V2_H_INCLUDED

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include <string>
#include <unordered_map>
#include <list>

#include "include-opengl.h"

namespace pdg {

// Forward declaration
struct ImageCacheEntry;

// Cache key type - integer handle for O(1) lookups
typedef uint32 CacheKey;
const CacheKey INVALID_CACHE_KEY = 0;

/**
 * ImageCache - Hash-based cache for OpenGL textures
 * 
 * Replaces the old linked-list approach with unordered_map for O(1) lookups.
 * Maintains LRU eviction policy with configurable max size and frame-based protection.
 * 
 * Cache owns all OpenGL textures exclusively. Images hold CacheKey handles and
 * request textures each frame. This prevents dangling references when cache evicts.
 */
class ImageCache {
public:
    ImageCache(int maxEntries = 100);
    ~ImageCache();
    
    /**
     * Get a cache key for an image
     * Creates new entry if not found, returns existing key if found
     */
    CacheKey getCacheKey(const char* sourceName, int width, int height, bool useEdgeClamp);
    
    /**
     * Get the OpenGL texture for a cache key
     * Returns 0 if texture hasn't been uploaded yet or was evicted
     */
    GLuint getTexture(CacheKey key);
    
    /**
     * Set the texture for a cache key (after uploading to OpenGL)
     * Marks the entry as having valid texture data
     */
    void setTexture(CacheKey key, GLuint texture);
    
    /**
     * Release a cache key (called when Image is destroyed)
     * Decrements ref count and marks entry as eligible for eviction
     */
    void releaseCachedEntry(CacheKey key);
    
    /**
     * Begin a new frame
     * Updates frame counter for frame-based eviction protection
     */
    void beginFrame();
    
    /**
     * Invalidate all cached textures (sets texture to 0 without deleting entries)
     */
    void invalidateAll();
    
    /**
     * Get cache statistics
     */
    int size() const { return mCache.size(); }
    int maxSize() const { return mMaxEntries; }
    
    // Legacy methods for compatibility (deprecated)
    ImageCacheEntry* getImage(const char* sourceName, int width, int height, bool useEdgeClamp);
    void addImage(ImageCacheEntry* entry);
    
private:
    struct LookupKey {
        std::string sourceName;
        int width;
        int height;
        bool useEdgeClamp;
        
        bool operator==(const LookupKey& other) const {
            return width == other.width && 
                   height == other.height &&
                   useEdgeClamp == other.useEdgeClamp &&
                   sourceName == other.sourceName;
        }
    };
    
    struct LookupKeyHash {
        size_t operator()(const LookupKey& key) const {
            // Combine hashes using XOR and bit shifting
            size_t h1 = std::hash<std::string>()(key.sourceName);
            size_t h2 = std::hash<int>()(key.width);
            size_t h3 = std::hash<int>()(key.height);
            size_t h4 = std::hash<bool>()(key.useEdgeClamp);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
    
    struct CacheEntry {
        LookupKey lookupKey;
        GLuint texture;
        uint32 refCount;        // Number of Images holding this key
        uint32 lastUsedFrame;   // Last frame this texture was accessed
        bool canEvict;          // true when refCount == 0
        
        CacheEntry() : texture(0), refCount(0), lastUsedFrame(0), canEvict(false) {}
    };
    
    // Hash map for O(1) lookups by lookup key
    std::unordered_map<LookupKey, CacheKey, LookupKeyHash> mLookupMap;
    
    // Array of cache entries indexed by CacheKey
    std::unordered_map<CacheKey, CacheEntry> mCache;
    
    // LRU list for eviction (most recently used at front) - stores CacheKeys
    std::list<CacheKey> mLRUList;
    
    // Map from CacheKey to position in LRU list (for fast updates)
    std::unordered_map<CacheKey, std::list<CacheKey>::iterator> mLRUMap;
    
    int mMaxEntries;
    uint32 mCurrentFrame;      // Current frame number for frame-based protection
    CacheKey mNextCacheKey;    // Counter for generating unique cache keys
    
    void evictLRU();
    void updateLRU(CacheKey key);
    LookupKey makeLookupKey(const char* sourceName, int width, int height, bool useEdgeClamp) const;
};

} // end namespace pdg

#endif // PDG_NO_GUI
#endif // PDG_IMAGECACHE_OPENGL_V2_H_INCLUDED

