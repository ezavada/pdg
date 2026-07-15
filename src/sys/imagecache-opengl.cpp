// -----------------------------------------------
// imagecache-opengl.cpp
//
// Caching for OpenGL image drawing
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

#include "pdg/msvcfix.h"

#include "imagecache-opengl.h"
#include "image-impl.h"

#include <algorithm>

#define MAX_CACHED_IMAGE_TEXTURES 100

namespace pdg {


// Removed global cache - each port has its own cache now

ImageCacheEntry::ImageCacheEntry( const char* inSourceName, int inWidth, int inHeight, bool inUseEdgeClamp)
: nextEntry(0), usedWhen(0), mSourceName(inSourceName), width(inWidth), height(inHeight), useEdgeClamp(inUseEdgeClamp), imageChecksum(0), texture(0)
{
	imageChecksum = ImageCacheEntry::calcChecksum(inSourceName, inWidth, inHeight, inUseEdgeClamp);
}

// Global cache methods removed - each port has its own cache now

int
ImageCacheEntry::calcChecksum(const char* sourceName, int width, int height, bool useEdgeClamp) {
	int sum = 0;
	const char* p = sourceName;
	while (*p) {
		sum += *p;
		p++;
	}
	sum += width;
	sum += height;
	sum += useEdgeClamp ? 1 : 0;
	return sum;
}

// Global invalidateAllTextures removed - each port has its own cache now

// Port-specific cache methods
ImageCacheEntry*
ImageCacheEntry::findImageInPortCache(const char* sourceName, int width, int height, bool useEdgeClamp) {
	// Search in this port's cache
	ImageCacheEntry* entry = this;
	int imageChecksum = ImageCacheEntry::calcChecksum(sourceName, width, height, useEdgeClamp);
	while (entry) {
		if (   (entry->imageChecksum == imageChecksum)
			&& (entry->width == width)
			&& (entry->height == height)
			&& (entry->useEdgeClamp == useEdgeClamp) ) {
			if (std::strcmp(sourceName, entry->mSourceName.c_str()) == 0) {
					// same image found in this port's cache
				entry->usedWhen++;
				return entry;
			}
		}
		entry = entry->nextEntry;
	}
	// Not found in this port's cache, create new entry
	return new ImageCacheEntry(sourceName, width, height, useEdgeClamp);
}

void
ImageCacheEntry::addEntryToPortCache(ImageCacheEntry* imageInfo) {
	// Count current cache size
	int cacheSize = 0;
	ImageCacheEntry* entry = this;
	while (entry) {
		cacheSize++;
		entry = entry->nextEntry;
	}
	
	if (cacheSize >= MAX_CACHED_IMAGE_TEXTURES) {
		// cache full, delete the least recently used cache entry
		uint32 smallestWhen = this->usedWhen;
		entry = this;
		ImageCacheEntry* prev = 0;
		ImageCacheEntry* smallestPrev = 0;
		while (entry) {
			if (entry->usedWhen < smallestWhen) {
				smallestPrev = prev;
				smallestWhen = entry->usedWhen;
			}
			prev = entry;
			entry = entry->nextEntry;
		}
		if (smallestPrev) {
			entry = smallestPrev->nextEntry;
			smallestPrev->nextEntry = entry->nextEntry;
		} else {
			// This shouldn't happen since we're the head of the list
			entry = this;
		}
		glDeleteTextures(1, &entry->texture); // clean up the OpenGL texture now that we aren't caching it anymore
		delete entry;
	}
	// now add the new entry to the head of this port's cache
	imageInfo->nextEntry = this;
	imageInfo->usedWhen = this->usedWhen + 1;
	// Note: The caller will need to update the port's mImageCache pointer to point to imageInfo
}

void
ImageCacheEntry::invalidatePortTextures() {
	ImageCacheEntry* entry = this;
	while (entry) {
		if (entry->texture != 0) {
			// Don't call glDeleteTextures here since the context might be destroyed
			entry->texture = 0;
		}
		entry = entry->nextEntry;
	}
}


} // end namespace pdg

#endif // PDG_NO_GUI
