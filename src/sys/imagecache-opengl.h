// -----------------------------------------------
// imagecache-opengl.h
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


#ifndef PDG_IMAGECACHE_OPENGL_H_INCLUDED
#define PDG_IMAGECACHE_OPENGL_H_INCLUDED

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include <string>

#include "include-opengl.h"
#include "image-impl.h"

namespace pdg {

	
struct ImageCacheEntry {
	
	// cache management
	ImageCacheEntry* nextEntry;
	uint32		 usedWhen;
	
	// here's what we use to find the item in the cache
	std::string  mSourceName;
	int			 width;
	int			 height;
	bool		 useEdgeClamp;
	int			 imageChecksum;
	
	// and here's the information we cache
	GLuint		 texture;
	
	ImageCacheEntry( const char* inSourceName, int inWidth, int inHeight, bool inUseEdgeClamp);
	
	// Global cache methods removed - each port has its own cache now
	
	// Non-static methods for port-specific cache
	ImageCacheEntry*         findImageInPortCache(const char* sourceName, int width, int height, bool useEdgeClamp);
	void                     addEntryToPortCache(ImageCacheEntry* imageInfo);
	void                     invalidatePortTextures();
	
private:
	ImageCacheEntry() {}
	ImageCacheEntry(ImageCacheEntry&) {}
	static int				 calcChecksum(const char* inSourceName, int inWidth, int inHeight, bool inUseEdgeClamp);
};


} // end namespace pdg

#endif // PDG_NO_GUI
#endif // PDG_IMAGECACHE_OPENGL_H_INCLUDED
