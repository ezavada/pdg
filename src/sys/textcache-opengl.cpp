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
#include "graphics-opengl.h"

#include <algorithm>
#include <cstring>


namespace pdg {


static FontCacheEntry* sFirstFontCacheEntry = 0;

TextCacheEntry::TextCacheEntry(const char* text, int length, FontImpl* font, int fontSize, uint32 fontStyle)
    : mFont(font), mText(text, length), len(length), size(fontSize), style(fontStyle & TEXT_STYLES_MASK),
      texture(0), charHeight(0), ascent(0), width(0), tx(0), ty(0), tx_topoffset(0) {
    font->addRef();
    ascent = std::ceil(font->getFontAscent(size, style));
    charHeight = ascent + std::ceil(font->getFontDescent(size, style));
}

TextCacheEntry::~TextCacheEntry() {
    // Shared pages flush when their last owner releases the GPU texture.
    // Evicting measurement-only entries must not split a pending text batch.
    if (texture && !atlas) {
        graphics_flushText();
        glDeleteTextures(1, &texture);
    }
    mFont->release();
}

TextAtlasPage::~TextAtlasPage() {
    graphics_flushText();
    if (texture) glDeleteTextures(1, &texture);
}

void TextCache::reserveTexture(TextCacheEntry* entry, int width, int height, GLenum format,
                               OpenGLStateCache& state, bool repeatStandalone) {
    graphics_flushText();
    entry->atlasCoordinates = false;
    entry->sourceWidth = width; entry->sourceHeight = height;
    entry->atlasX = entry->atlasY = 0; entry->u0 = entry->v0 = 0;
    const int leftPadding = (entry->style & textStyle_Italic) ? entry->charHeight + 2 : 2;
    const int packedWidth = width + leftPadding + 2, packedHeight = height + 4;
    GLint maximum = 0; glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maximum);
    const int pageSize = std::min(1024, maximum);
    const int channels = format == GL_RGBA ? 4 : 1;
    if (packedWidth <= pageSize && packedHeight <= pageSize) {
        for (auto& page : mPages) {
            if (page->format != format) continue;
            int x = page->x, y = page->y, rowHeight = page->rowHeight;
            if (x + packedWidth > page->size) { x = 0; y += rowHeight; rowHeight = 0; }
            if (y + packedHeight > page->size) continue;
            entry->atlas = page; entry->atlasX = x + leftPadding; entry->atlasY = y + 2;
            page->x = x + packedWidth; page->y = y; page->rowHeight = std::max(rowHeight, packedHeight);
            break;
        }
        if (!entry->atlas) {
            auto page = std::make_shared<TextAtlasPage>();
            page->size = pageSize; page->format = format;
            page->bytes = size_t(pageSize) * pageSize * channels;
            glGenTextures(1, &page->texture); state.bindTexture(page->texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#ifdef __EMSCRIPTEN__
            glTexImage2D(GL_TEXTURE_2D, 0, format, pageSize, pageSize, 0, format, GL_UNSIGNED_BYTE, nullptr);
#else
            std::vector<unsigned char> transparent(page->bytes, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, format, pageSize, pageSize, 0, format, GL_UNSIGNED_BYTE, transparent.data());
#endif
            page->x = packedWidth; page->rowHeight = packedHeight;
            entry->atlas = page; entry->atlasX = leftPadding; entry->atlasY = 2;
            mPages.push_back(std::move(page)); mBytes += entry->atlas->bytes;
        }
        entry->texture = entry->atlas->texture;
        state.bindTexture(entry->texture);
    } else {
        glGenTextures(1, &entry->texture); state.bindTexture(entry->texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        const GLenum wrap = repeatStandalone ? GL_REPEAT : GL_CLAMP_TO_EDGE;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
    }
}

void TextCache::uploadPixels(TextCacheEntry* entry, const void* pixels, int width, int height,
                             GLenum format, OpenGLStateCache& state, int rowAlignment, bool repeatStandalone) {
    reserveTexture(entry, width, height, format, state, repeatStandalone);
    GLint alignment = 4; glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
    glPixelStorei(GL_UNPACK_ALIGNMENT, rowAlignment);
    glTexSubImage2D(GL_TEXTURE_2D, 0, entry->atlasX, entry->atlasY, width, height, format, GL_UNSIGNED_BYTE, pixels);
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
}

size_t TextCache::Hash::operator()(const Key& key) const {
    size_t hash = std::hash<std::string>{}(key.text);
    auto combine = [&](size_t value) { hash ^= value + 0x9e3779b9 + (hash << 6) + (hash >> 2); };
    combine(std::hash<FontImpl*>{}(key.font));
    combine(std::hash<int>{}(key.size));
    combine(std::hash<uint32>{}(key.style));
    return hash;
}

TextCacheEntry* TextCache::find(const char* text, int len, FontImpl* font, int size, uint32 style) {
    Key key{std::string(text, len), font, size, static_cast<uint32>(style & TEXT_STYLES_MASK)};
    auto found = mEntries.find(key);
    if (found != mEntries.end()) {
        mRecency.splice(mRecency.begin(), mRecency, found->second.recency);
        return found->second.entry.get();
    }
    auto entry = std::make_unique<TextCacheEntry>(text, len, font, size, style);
    auto* result = entry.get();
    mRecency.push_front(key);
    mEntries.emplace(std::move(key), Item{std::move(entry), mRecency.begin(), 0});
    trim(result);
    return result;
}

void TextCache::uploaded(TextCacheEntry* entry) {
    Key key{entry->mText, entry->mFont, entry->size, entry->style};
    auto found = mEntries.find(key);
    if (found == mEntries.end() || found->second.entry.get() != entry) return;
    mBytes -= found->second.bytes;
    found->second.bytes = entry->atlas ? 0 : entry->textureBytes;
    if (entry->atlas && !entry->atlasCoordinates) {
        entry->u0 = float(entry->atlasX) / entry->atlas->size;
        entry->v0 = float(entry->atlasY) / entry->atlas->size;
        entry->tx *= float(entry->sourceWidth) / entry->atlas->size;
        entry->ty *= float(entry->sourceHeight) / entry->atlas->size;
        entry->tx_topoffset *= float(entry->sourceWidth) / entry->atlas->size;
        entry->atlasCoordinates = true;
    }
    mBytes += found->second.bytes;
    mRecency.splice(mRecency.begin(), mRecency, found->second.recency);
    trim(entry);
}

void TextCache::trim(TextCacheEntry* keep) {
    // A single oversized texture remains alive through the current draw; the
    // next lookup can evict it. Never return a pointer to an evicted entry.
    while (mEntries.size() > 1 && (mEntries.size() > mMaxEntries || mBytes > mMaxBytes)) {
        auto oldest = std::prev(mRecency.end());
        auto found = mEntries.find(*oldest);
        if (found->second.entry.get() == keep) break;
        mBytes -= found->second.bytes;
        if (found->second.entry->texture) ++mTextureRevision;
        mEntries.erase(found);
        mRecency.erase(oldest);
        releaseEmptyPages();
    }
}

void TextCache::releaseEmptyPages() {
    for (auto page = mPages.begin(); page != mPages.end();) {
        if (page->use_count() == 1) {
            mBytes -= (*page)->bytes; ++mTextureRevision;
            page = mPages.erase(page);
        } else ++page;
    }
}

void TextCache::invalidateTextures() {
    graphics_flushText();
    for (auto& page : mPages) page->texture = 0;
    for (auto& [key, item] : mEntries) {
        // The owning GL context may already be gone. Forget IDs without GL calls.
        item.entry->texture = 0;
        item.entry->textureBytes = 0;
        item.entry->atlas.reset();
        item.entry->atlasCoordinates = false;
        item.bytes = 0;
    }
    mBytes = 0;
    mPages.clear();
}

void TextCache::clear() {
    mEntries.clear();
    mPages.clear();
    mRecency.clear();
    mBytes = 0;
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
