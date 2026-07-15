// -----------------------------------------------
// textcache-opengl.cpp
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


#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "pdg/msvcfix.h"

#include "textcache-opengl.h"
#include "font-impl.h"

#include <algorithm>

#define MAX_CACHED_STRING_TEXTURES 250

namespace pdg {


static FontCacheEntry* sFirstFontCacheEntry = 0;

// Removed global cache - each port has its own cache now

TextCacheEntry::TextCacheEntry( const char* inText, int inLen, FontImpl* font, int inSize, uint32 inStyle)
: nextEntry(0), usedWhen(0), mFont(font), mText(inText), len(inLen), size(inSize), style(inStyle), textChecksum(0),
texture(0), charHeight(0), ascent(0), width(0), tx(0.0), ty(0.0), tx_topoffset(0.0)
{
	// pre-fill these values
	ascent = std::ceil(font->getFontAscent(size, style));
	charHeight = ascent + std::ceil(font->getFontDescent(size, style));
	textChecksum = TextCacheEntry::calcChecksum(inText, inLen);
}

// Global cache methods removed - each port has its own cache now

int
TextCacheEntry::calcChecksum(const char* text, int len) {
	int sum = 0;
	const char* p = text;
	while (len) {
		len--;
		sum += *p;
	}
	return sum;
}

// Global invalidateAllTextures removed - each port has its own cache now

// Port-specific cache methods
TextCacheEntry*
TextCacheEntry::findTextInPortCache(const char* text, int len, FontImpl* font, int size, uint32 style) {
	// Search in this port's cache
	TextCacheEntry* entry = this;
	style &= TEXT_STYLES_MASK;
	int textChecksum = TextCacheEntry::calcChecksum(text, len);
	while (entry) {
		if (   (entry->textChecksum == textChecksum)
			&& (entry->len == len)
			&& (entry->size == size)
			&& (entry->style == style)
			&& (entry->mFont == font) ) {
			if (std::strcmp(text, entry->mText.c_str()) == 0) {
					// same text string found in this port's cache
				entry->usedWhen++;
				return entry;
			}
		}
		entry = entry->nextEntry;
	}
	// Not found in this port's cache, create new entry
	return new TextCacheEntry(text, len, font, size, style);
}

void
TextCacheEntry::addEntryToPortCache(TextCacheEntry* textInfo) {
	// Count current cache size
	int cacheSize = 0;
	TextCacheEntry* entry = this;
	while (entry) {
		cacheSize++;
		entry = entry->nextEntry;
	}
	
	if (cacheSize >= MAX_CACHED_STRING_TEXTURES) {
		// cache full, delete the least recently used cache entry
		uint32 smallestWhen = this->usedWhen;
		entry = this;
		TextCacheEntry* prev = 0;
		TextCacheEntry* smallestPrev = 0;
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
	textInfo->nextEntry = this;
	textInfo->usedWhen = this->usedWhen + 1;
	textInfo->style &= TEXT_STYLES_MASK;
	// Note: The caller will need to update the port's mTextCache pointer to point to textInfo
}

void
TextCacheEntry::invalidatePortTextures() {
	TextCacheEntry* entry = this;
	while (entry) {
		if (entry->texture != 0) {
			// Don't call glDeleteTextures here since the context might be destroyed
			entry->texture = 0;
		}
		entry = entry->nextEntry;
	}
}

FontCacheEntry::FontCacheEntry( const char* inFontName, float inScalingFactor )
	: nextEntry(0), mFontName(inFontName), scalingFactor(inScalingFactor), mFont(0)
{
	addEntryToCache(this);
}

FontCacheEntry*
FontCacheEntry::findFontInCache(const char* inFontName, float inScalingFactor ) {
	// try to find in cache
	FontCacheEntry* entry = sFirstFontCacheEntry;
	while (entry) {
		if (   (entry->scalingFactor == inScalingFactor)
			&& (std::strcmp(inFontName, entry->mFontName.c_str()) == 0) ) {
			// same font
			return entry;
		}
		entry = entry->nextEntry;
	}
	return new FontCacheEntry(inFontName, inScalingFactor);
}

void
FontCacheEntry::addEntryToCache(FontCacheEntry* fontInfo) {
	// now add the new entry
	fontInfo->nextEntry = sFirstFontCacheEntry;
	if (fontInfo->mFont) {
		fontInfo->mFontName = fontInfo->mFont->getFontName();
	}
	sFirstFontCacheEntry = fontInfo;
}


} // end namespace pdg

#endif // PDG_NO_GUI
