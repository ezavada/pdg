// Linux font and text support for the GLFW/OpenGL renderer.

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "font-fallback.h"
#include "font-impl.h"
#include "graphics-opengl.h"
#include "textcache-opengl.h"

#include "pdg/sys/graphicsmanager.h"

#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SYNTHESIS_H

#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace pdg {

namespace {

FT_Library getFreeTypeLibrary() {
    static FT_Library library = [] {
        FT_Library value = nullptr;
        return FT_Init_FreeType(&value) == 0 ? value : nullptr;
    }();
    return library;
}

struct FontFile { std::string path; int index = 0; };

FontFile findFontFile(const char* fontName, uint32 codePoint = 0) {
    if (!FcInit()) return {};

    const char* requestedName = fontName && *fontName ? fontName : "sans-serif";
    FcPattern* pattern = FcNameParse(reinterpret_cast<const FcChar8*>(requestedName));
    if (!pattern) return {};

    if (codePoint) {
        FcCharSet* characters = FcCharSetCreate();
        if (!characters) { FcPatternDestroy(pattern); return {}; }
        FcCharSetAddChar(characters, codePoint);
        FcPatternAddCharSet(pattern, FC_CHARSET, characters);
        FcCharSetDestroy(characters);
    }
    // Preserve requested families while giving absent desktop fonts a useful
    // generic substitute on Linux installations without Microsoft fonts.
    const char* generic = "sans-serif";
    if (std::strstr(requestedName, "Times")) generic = "serif";
    else if (std::strstr(requestedName, "Courier")) generic = "monospace";
    FcPatternAddString(pattern, FC_FAMILY, reinterpret_cast<const FcChar8*>(generic));
    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);
    FcResult result = FcResultNoMatch;
    FcPattern* match = FcFontMatch(nullptr, pattern, &result);
    FcPatternDestroy(pattern);
    if (!match) return {};

    FcChar8* file = nullptr;
    FontFile fileInfo;
    if (FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch && file) {
        fileInfo.path.assign(reinterpret_cast<const char*>(file));
    }
    FcPatternGetInteger(match, FC_INDEX, 0, &fileInfo.index);
    FcPatternDestroy(match);
    return fileInfo;
}

uint32 nextCodePoint(const char*& cursor, const char* end) {
    const auto first = static_cast<unsigned char>(*cursor++);
    if (first < 0x80) return first;

    int continuationCount = 0;
    uint32 value = 0;
    if ((first & 0xe0) == 0xc0) {
        continuationCount = 1;
        value = first & 0x1f;
    } else if ((first & 0xf0) == 0xe0) {
        continuationCount = 2;
        value = first & 0x0f;
    } else if ((first & 0xf8) == 0xf0) {
        continuationCount = 3;
        value = first & 0x07;
    } else {
        return 0xfffd;
    }

    while (continuationCount--) {
        if (cursor == end) return 0xfffd;
        const auto byte = static_cast<unsigned char>(*cursor);
        if ((byte & 0xc0) != 0x80) return 0xfffd;
        ++cursor;
        value = (value << 6) | (byte & 0x3f);
    }
    return value;
}

class FontImplUnix final : public FontImpl {
public:
    FontImplUnix(Port* port, const char* fontName, float scalingFactor)
        : FontImpl(port, fontName, scalingFactor) {
        const FontFile file = findFontFile(fontName);
        FT_Library library = getFreeTypeLibrary();
        if (library && !file.path.empty()) FT_New_Face(library, file.path.c_str(), file.index, &mFace);
    }

    ~FontImplUnix() override {
        for (auto& entry : mFallbackFaces) if (entry.second) FT_Done_Face(entry.second);
        if (mFace) FT_Done_Face(mFace);
    }

    FontMetricsInfo* getFontMetrics(int size, uint32 style) override {
        auto* metrics = static_cast<FontMetricsInfo*>(std::calloc(1, sizeof(FontMetricsInfo)));
        if (!metrics) return nullptr;
        metrics->size = size;
        metrics->style = style;

        const float scaledSize = std::max(1.0f, size * mScalingFactor);
        if (!setPixelSize(size)) {
            metrics->ascent = std::ceil(scaledSize * 0.8f);
            metrics->descent = std::ceil(scaledSize * 0.2f);
            metrics->height = metrics->ascent + metrics->descent;
            metrics->capHeight = metrics->ascent;
            return metrics;
        }

        metrics->ascent = std::ceil(mFace->size->metrics.ascender / 64.0f);
        metrics->descent = std::ceil(-mFace->size->metrics.descender / 64.0f);
        metrics->height = std::ceil(mFace->size->metrics.height / 64.0f);
        metrics->leading = std::max(0.0f, metrics->height - metrics->ascent - metrics->descent);
        metrics->capHeight = metrics->ascent;
        if (loadGlyph('H', style, false)) {
            metrics->capHeight = mFace->glyph->metrics.height / 64.0f;
        }
        return metrics;
    }

    bool setPixelSize(int size) {
        mActiveFace = mFace;
        mPixelSize = static_cast<FT_UInt>(std::max(1.0f, std::ceil(size * mScalingFactor)));
        if (!mFace) return false;
        return FT_Set_Pixel_Sizes(mFace, 0, mPixelSize) == 0;
    }

    FT_Face selectFace(uint32 codePoint) {
        mActiveFace = mFace;
        if (!mFace || FT_Get_Char_Index(mFace, codePoint)) return mActiveFace;
        auto known = mGlyphFaces.find(codePoint);
        if (known == mGlyphFaces.end()) {
            const FontFile file = findFontFile(mFontName.c_str(), codePoint);
            const std::string key = file.path + ":" + std::to_string(file.index);
            auto [entry, inserted] = mFallbackFaces.emplace(key, nullptr);
            if (inserted && !file.path.empty())
                FT_New_Face(getFreeTypeLibrary(), file.path.c_str(), file.index, &entry->second);
            FT_Face fallback = entry->second;
            known = mGlyphFaces.emplace(codePoint,
                fallback && FT_Get_Char_Index(fallback, codePoint) ? fallback : mFace).first;
        }
        mActiveFace = known->second;
        FT_Set_Pixel_Sizes(mActiveFace, 0, mPixelSize);
        return mActiveFace;
    }

    bool loadGlyph(uint32 codePoint, uint32 style, bool render) {
        if (!mActiveFace || FT_Load_Char(mActiveFace, codePoint, FT_LOAD_DEFAULT) != 0) return false;
        if (style & textStyle_Bold) FT_GlyphSlot_Embolden(mActiveFace->glyph);
        if (style & textStyle_Italic) FT_GlyphSlot_Oblique(mActiveFace->glyph);
        return !render || FT_Render_Glyph(mActiveFace->glyph, FT_RENDER_MODE_NORMAL) == 0;
    }

    FT_Face face() const { return mActiveFace; }

private:
    FT_Face mFace = nullptr, mActiveFace = nullptr;
    FT_UInt mPixelSize = 1;
    std::map<std::string, FT_Face> mFallbackFaces;
    std::map<uint32, FT_Face> mGlyphFaces;
};

float measureText(FontImplUnix& font, const char* text, int len, int size, uint32 style) {
    if (!font.setPixelSize(size)) return 0;
    const char* cursor = text;
    const char* end = text + len;
    FT_Face previousFace = nullptr;
    FT_UInt previous = 0;
    FT_Pos advance = 0;
    while (cursor < end) {
        const uint32 codePoint = nextCodePoint(cursor, end);
        font.selectFace(codePoint);
        const FT_UInt glyphIndex = FT_Get_Char_Index(font.face(), codePoint);
        if (previousFace == font.face() && previous && glyphIndex && FT_HAS_KERNING(font.face())) {
            FT_Vector kerning{};
            if (FT_Get_Kerning(font.face(), previous, glyphIndex, FT_KERNING_DEFAULT, &kerning) == 0) {
                advance += kerning.x;
            }
        }
        if (font.loadGlyph(codePoint, style, false)) advance += font.face()->glyph->advance.x;
        previousFace = font.face();
        previous = glyphIndex;
    }
    return advance / 64.0f;
}

void copyGlyphBitmap(std::vector<unsigned char>& pixels, int textureWidth, int textureHeight,
                     int x, int y, const FT_Bitmap& bitmap) {
    for (int row = 0; row < static_cast<int>(bitmap.rows); ++row) {
        const int targetY = y + row;
        if (targetY < 0 || targetY >= textureHeight) continue;
        for (int column = 0; column < static_cast<int>(bitmap.width); ++column) {
            const int targetX = x + column;
            if (targetX < 0 || targetX >= textureWidth) continue;
            unsigned char coverage = 0;
            if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY) {
                coverage = bitmap.buffer[row * bitmap.pitch + column];
            } else if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO) {
                coverage = (bitmap.buffer[row * bitmap.pitch + column / 8]
                            & (0x80 >> (column % 8))) ? 255 : 0;
            }
            auto& destination = pixels[static_cast<size_t>(targetY) * textureWidth + targetX];
            destination = std::max(destination, coverage);
        }
    }
}

class GraphicsManagerUnix final : public GraphicsManager {
public:
    GraphicsManagerUnix() { FontFallbackManager::getInstance().initialize(this); }

    Font* createFont(const char* fontName, float scalingFactor) override {
        FontCacheEntry* fontInfo = FontCacheEntry::findFontInCache(fontName, scalingFactor);
        if (!fontInfo->mFont) {
            auto* font = new FontImplUnix(getMainPort(), fontName, scalingFactor);
            font->addRef();
            fontInfo->mFont = font;
        }
        auto* cachedFont = dynamic_cast<FontImpl*>(fontInfo->mFont);
        if (cachedFont && getMainPort()) cachedFont->mPort = getMainPort();
        fontInfo->mFont->addRef();
        return fontInfo->mFont;
    }
};

} // namespace

Port* graphics_newPort(GraphicsManager* manager) {
    return new PortImpl(manager);
}

GraphicsManager* GraphicsManager::createSingletonInstance() {
    return new GraphicsManagerUnix();
}

int Port::getTextWidth(const char* text, int size, uint32 style, int len) {
    if (!text) return 0;
    if (len < 0) len = static_cast<int>(std::strlen(text));
    if (len == 0) return 0;
    auto* font = dynamic_cast<FontImplUnix*>(getCurrentFont(style));
    if (!font) return 0;
    auto& port = static_cast<PortImpl&>(*this);
    auto* entry = port.getTextFromCache(text, len, font, size, style);
    if (!entry->measured) {
        entry->advanceWidth = measureText(*font, text, len, size, style);
        entry->width = static_cast<int>(std::ceil(entry->advanceWidth));
        entry->measured = true;
    }
    return entry->width;
}

void graphics_drawTextRaster(PortImpl& port, const char* text, int len, const Quad& quad,
                       int size, uint32 style, Color rgba, TextCacheEntry* cachedEntry) {
    auto* font = dynamic_cast<FontImplUnix*>(port.getCurrentFont(style));
    if (!font) return;
    TextCacheEntry* textInfo = cachedEntry ? cachedEntry : port.getTextFromCache(text, len, font, size, style);
    if (!textInfo) return;
    if (!textInfo->measured) textInfo->width = port.getTextWidth(text, size, style, len);

    if (textInfo->texture == 0) {
        if (!font->setPixelSize(size)) return;
        const int extraWidth = (style & textStyle_Italic) ? size : 0;
        const int contentWidth = std::max(1, textInfo->width + extraWidth);
        const int contentHeight = std::max(1, textInfo->charHeight);
        const int textureWidth = static_cast<int>(std::bit_ceil(static_cast<unsigned>(contentWidth)));
        const int textureHeight = static_cast<int>(std::bit_ceil(static_cast<unsigned>(contentHeight)));
        std::vector<unsigned char> pixels(static_cast<size_t>(textureWidth) * textureHeight, 0);

        const char* cursor = text;
        const char* end = text + len;
        FT_Face previousFace = nullptr;
        FT_UInt previous = 0;
        FT_Pos pen = 0;
        while (cursor < end) {
            const uint32 codePoint = nextCodePoint(cursor, end);
            font->selectFace(codePoint);
            const FT_UInt glyphIndex = FT_Get_Char_Index(font->face(), codePoint);
            if (previousFace == font->face() && previous && glyphIndex && FT_HAS_KERNING(font->face())) {
                FT_Vector kerning{};
                if (FT_Get_Kerning(font->face(), previous, glyphIndex, FT_KERNING_DEFAULT, &kerning) == 0) {
                    pen += kerning.x;
                }
            }
            if (font->loadGlyph(codePoint, style, true)) {
                const FT_GlyphSlot glyph = font->face()->glyph;
                copyGlyphBitmap(pixels, textureWidth, textureHeight,
                                static_cast<int>(pen / 64) + glyph->bitmap_left,
                                textInfo->ascent - glyph->bitmap_top, glyph->bitmap);
                pen += glyph->advance.x;
            }
            previousFace = font->face();
            previous = glyphIndex;
        }

        if (style & textStyle_Underline) {
            const int underlineY = std::min(textureHeight - 1, textInfo->ascent + 1);
            const int thickness = std::max(1, size / 12);
            for (int row = 0; row < thickness && underlineY + row < textureHeight; ++row) {
                std::fill_n(pixels.begin() + static_cast<size_t>(underlineY + row) * textureWidth,
                            std::min(textInfo->width, textureWidth), 255);
            }
        }

        port.mTextCache.uploadPixels(textInfo, pixels.data(), textureWidth, textureHeight, GL_ALPHA, port.mStateCache);
        textInfo->tx = static_cast<float>(contentWidth) / textureWidth;
        textInfo->ty = static_cast<float>(contentHeight) / textureHeight;
        textInfo->tx_topoffset = 0.0f;
        textInfo->textureBytes = static_cast<size_t>(textureWidth) * textureHeight * 1;
        port.addTextToCache(textInfo);
    }

    graphics_submitText(port, *textInfo, quad, rgba);
}

} // namespace pdg

#endif // PDG_NO_GUI
