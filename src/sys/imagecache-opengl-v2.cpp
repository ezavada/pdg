// -----------------------------------------------
// imagecache-opengl-v2.cpp
//
// Hash-based caching for OpenGL image drawing
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

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "imagecache-opengl-v2.h"
#include "imagecache-opengl.h"  // For ImageCacheEntry definition

#include <iostream>

namespace pdg {

ImageCache::ImageCache(int maxEntries)
: mMaxEntries(maxEntries), mCurrentFrame(0), mNextCacheKey(1)  // Start at 1, 0 is INVALID_CACHE_KEY
{
}

ImageCache::~ImageCache() {
    // Delete all OpenGL textures - cache owns them exclusively
    for (auto& pair : mCache) {
        if (pair.second.texture != 0) {
            glDeleteTextures(1, &pair.second.texture);
        }
    }
    mCache.clear();
    mLookupMap.clear();
    mLRUList.clear();
    mLRUMap.clear();
}

ImageCache::LookupKey ImageCache::makeLookupKey(const char* sourceName, int width, int height, bool useEdgeClamp) const {
    LookupKey key;
    key.sourceName = sourceName;
    key.width = width;
    key.height = height;
    key.useEdgeClamp = useEdgeClamp;
    return key;
}

// New interface methods

CacheKey ImageCache::getCacheKey(const char* sourceName, int width, int height, bool useEdgeClamp) {
    LookupKey lookupKey = makeLookupKey(sourceName, width, height, useEdgeClamp);
    
    // Check if we already have a cache key for this lookup
    auto it = mLookupMap.find(lookupKey);
    if (it != mLookupMap.end()) {
        // Found existing entry - increment ref count
        CacheKey cacheKey = it->second;
        auto cacheIt = mCache.find(cacheKey);
        if (cacheIt != mCache.end()) {
            cacheIt->second.refCount++;
            cacheIt->second.canEvict = false;  // Has active references
            return cacheKey;
        }
    }
    
    // Create new cache entry
    CacheKey newKey = mNextCacheKey++;
    CacheEntry entry;
    entry.lookupKey = lookupKey;
    entry.refCount = 1;
    entry.canEvict = false;
    entry.texture = 0;  // Not yet uploaded
    entry.lastUsedFrame = mCurrentFrame;
    
    mCache[newKey] = entry;
    mLookupMap[lookupKey] = newKey;
    
    // Add to front of LRU list
    mLRUList.push_front(newKey);
    mLRUMap[newKey] = mLRUList.begin();
    
    return newKey;
}

GLuint ImageCache::getTexture(CacheKey key) {
    if (key == INVALID_CACHE_KEY) {
        return 0;
    }
    
    auto it = mCache.find(key);
    if (it == mCache.end()) {
        return 0;  // Cache entry doesn't exist
    }
    
    // Update access tracking
    it->second.lastUsedFrame = mCurrentFrame;
    updateLRU(key);
    
    return it->second.texture;
}

void ImageCache::setTexture(CacheKey key, GLuint texture) {
    if (key == INVALID_CACHE_KEY) {
        return;
    }
    
    auto it = mCache.find(key);
    if (it != mCache.end()) {
        // Delete old texture if we're replacing it
        if (it->second.texture != 0 && it->second.texture != texture) {
            glDeleteTextures(1, &it->second.texture);
        }
        it->second.texture = texture;
        it->second.lastUsedFrame = mCurrentFrame;
        updateLRU(key);
    }
}

void ImageCache::releaseCachedEntry(CacheKey key) {
    if (key == INVALID_CACHE_KEY) {
        return;
    }
    
    auto it = mCache.find(key);
    if (it != mCache.end()) {
        // Decrement ref count
        if (it->second.refCount > 0) {
            it->second.refCount--;
        }
        
        // Mark as eligible for eviction when no more references
        if (it->second.refCount == 0) {
            it->second.canEvict = true;
        }
    }
}

void ImageCache::beginFrame() {
    mCurrentFrame++;
}

// Legacy method for backward compatibility (deprecated)
ImageCacheEntry* ImageCache::getImage(const char* sourceName, int width, int height, bool useEdgeClamp) {
    // This is now deprecated but kept for compatibility
    // Just create a new entry - caller will manage it
    return new ImageCacheEntry(sourceName, width, height, useEdgeClamp);
}

// Legacy method for backward compatibility (deprecated)
void ImageCache::addImage(ImageCacheEntry* entry) {
    // This is now deprecated but kept for compatibility
    // The new system doesn't use ImageCacheEntry pointers this way
    if (!entry) return;
    
    // Just get a cache key and set the texture if present
    CacheKey key = getCacheKey(entry->mSourceName.c_str(), entry->width, entry->height, entry->useEdgeClamp);
    if (entry->texture != 0) {
        setTexture(key, entry->texture);
    }
}

void ImageCache::invalidateAll() {
    for (auto& pair : mCache) {
        if (pair.second.texture != 0) {
            // Don't delete textures here - context might be destroyed
            // Just mark as invalid
            pair.second.texture = 0;
        }
    }
}

void ImageCache::evictLRU() {
    if (mLRUList.empty()) return;
    
    // Try to find an evictable entry
    // Start from least recently used (back of list) and search forward
    for (auto it = mLRUList.rbegin(); it != mLRUList.rend(); ++it) {
        CacheKey key = *it;
        auto cacheIt = mCache.find(key);
        
        if (cacheIt != mCache.end() && cacheIt->second.canEvict) {
            // Check frame-based protection: don't evict if used in current or previous frame
            if (cacheIt->second.lastUsedFrame + 1 >= mCurrentFrame) {
                continue;  // Too recent, try next candidate
            }
            
            // This entry can be evicted
            if (cacheIt->second.texture != 0) {
                glDeleteTextures(1, &cacheIt->second.texture);
            }
            
            // Remove from lookup map
            mLookupMap.erase(cacheIt->second.lookupKey);
            
            // Remove from cache
            mCache.erase(cacheIt);
            
            // Remove from LRU tracking
            // Convert reverse iterator to forward iterator for erase
            auto fwdIt = it.base();
            --fwdIt;
            mLRUMap.erase(key);
            mLRUList.erase(fwdIt);
            
            return;  // Successfully evicted one entry
        }
    }
    
    // If we get here, no entries can be evicted
    // This is a problem - all entries are either referenced or used too recently
    // We'll just skip eviction and allow cache to grow slightly
}

void ImageCache::updateLRU(CacheKey key) {
    auto it = mLRUMap.find(key);
    if (it != mLRUMap.end()) {
        // Remove from current position in LRU list
        mLRUList.erase(it->second);
    }
    
    // Add to front of LRU list (most recently used)
    mLRUList.push_front(key);
    mLRUMap[key] = mLRUList.begin();
}

} // end namespace pdg

#endif // PDG_NO_GUI

