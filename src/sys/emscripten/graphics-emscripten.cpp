// Browser-specific graphics and font support for the Emscripten build.

#include "pdg_project.h"

#ifndef PDG_NO_GUI

#include "font-fallback.h"
#include "font-impl.h"
#include "graphics-opengl.h"
#include "textcache-opengl.h"

#include "pdg/sys/graphicsmanager.h"

#include <emscripten.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>

namespace pdg {

EM_JS(double, pdg_em_measure_text, (const char* text, const char* family, int size, int style), {
    const value = UTF8ToString(text);
    const fontFamily = UTF8ToString(family) || "Arial";
    if (typeof document === 'undefined' && typeof OffscreenCanvas === 'undefined') {
        return value.length * size * 0.6;
    }
    const canvas = typeof OffscreenCanvas !== 'undefined'
        ? new OffscreenCanvas(1, 1)
        : document.createElement("canvas");
    const context = canvas.getContext("2d");
    const italic = (style & 2) ? "italic " : "";
    const bold = (style & 1) ? "bold " : "";
    context.font = italic + bold + size + "px " + fontFamily;
    return context.measureText(value).width;
});

EM_JS(void, pdg_em_rasterize_text,
      (const char* text, const char* family, int size, int style, int width, int height,
       int ascent, unsigned char* pixels), {
    const pixelCount = width * height;
    for (let index = 0; index < pixelCount; ++index) {
        const target = pixels + index * 4;
        HEAPU8[target] = 255;
        HEAPU8[target + 1] = 255;
        HEAPU8[target + 2] = 255;
        HEAPU8[target + 3] = 0;
    }
    if (typeof document === 'undefined' && typeof OffscreenCanvas === 'undefined') return;
    const canvas = typeof OffscreenCanvas !== 'undefined'
        ? new OffscreenCanvas(width, height)
        : document.createElement("canvas");
    canvas.width = width;
    canvas.height = height;
    const context = canvas.getContext("2d");
    const fontFamily = UTF8ToString(family) || "Arial";
    const italic = (style & 2) ? "italic " : "";
    const bold = (style & 1) ? "bold " : "";
    context.font = italic + bold + size + "px " + fontFamily;
    context.textBaseline = "alphabetic";
    context.fillStyle = "#fff";
    context.fillText(UTF8ToString(text), 0, ascent);
    if (style & 4) {
        const thickness = Math.max(1, Math.ceil(size / 12));
        context.fillRect(0, ascent + thickness, width, thickness);
    }
    const rgba = context.getImageData(0, 0, width, height).data;
    for (let index = 0; index < pixelCount; ++index) {
        HEAPU8[pixels + index * 4 + 3] = rgba[index * 4 + 3];
    }
});

class FontImplEmscripten final : public FontImpl {
public:
    FontImplEmscripten(Port* port, const char* fontName, float scalingFactor)
        : FontImpl(port, fontName, scalingFactor) {}

    FontMetricsInfo* getFontMetrics(int size, uint32 style) override {
        FontMetricsInfo* metrics = static_cast<FontMetricsInfo*>(std::malloc(sizeof(FontMetricsInfo)));
        if (!metrics) return nullptr;
        const float scaledSize = size * mScalingFactor;
        metrics->size = size;
        metrics->style = style;
        metrics->ascent = std::ceil(scaledSize * 0.8f);
        metrics->descent = std::ceil(scaledSize * 0.2f);
        metrics->leading = std::ceil(scaledSize * 0.1f);
        metrics->height = metrics->ascent + metrics->descent + metrics->leading;
        return metrics;
    }
};

class GraphicsManagerEmscripten final : public GraphicsManager {
public:
    GraphicsManagerEmscripten() {
        FontFallbackManager::getInstance().initialize(this);
    }

    Font* createFont(const char* fontName, float scalingFactor) override {
        FontCacheEntry* fontInfo = FontCacheEntry::findFontInCache(fontName, scalingFactor);
        if (!fontInfo->mFont) {
            FontImplEmscripten* font = new FontImplEmscripten(getMainPort(), fontName, scalingFactor);
            font->addRef();
            fontInfo->mFont = font;
        }
        FontImpl* cachedFont = dynamic_cast<FontImpl*>(fontInfo->mFont);
        if (cachedFont && getMainPort()) cachedFont->mPort = getMainPort();
        fontInfo->mFont->addRef();
        return fontInfo->mFont;
    }
};

Port* graphics_newPort(GraphicsManager* manager) {
    return new PortImpl(manager);
}

GraphicsManager* GraphicsManager::createSingletonInstance() {
    return new GraphicsManagerEmscripten();
}

int Port::getTextWidth(const char* text, int size, uint32 style, int len) {
    if (!text) return 0;
    if (len < 0) len = static_cast<int>(std::strlen(text));
    if (len == 0) return 0;
    FontImplEmscripten* font = dynamic_cast<FontImplEmscripten*>(getCurrentFont(style));
    if (!font) return 0;
    std::string value(text, static_cast<size_t>(len));
    const int scaledSize = std::max(1, static_cast<int>(std::ceil(size * font->mScalingFactor)));
    return static_cast<int>(std::ceil(pdg_em_measure_text(
        value.c_str(), font->getFontName(), scaledSize, static_cast<int>(style))));
}

void graphics_drawText(PortImpl& port, const char* text, int len, const Quad& quad,
                       int size, uint32 style, Color rgba) {
    FontImplEmscripten* font = dynamic_cast<FontImplEmscripten*>(port.getCurrentFont(style));
    if (!font) return;
    TextCacheEntry* textInfo = port.getTextFromCache(text, len, font, size, style);
    if (!textInfo) return;
    if (textInfo->width == 0) textInfo->width = port.getTextWidth(text, size, style, len);

    if (textInfo->texture == 0) {
        const int extraWidth = (style & textStyle_Italic) ? size : 0;
        const int textureWidth = std::max(1, textInfo->width + extraWidth);
        const int textureHeight = std::max(1, textInfo->charHeight);
        unsigned char* imageData = static_cast<unsigned char*>(
            std::malloc(static_cast<size_t>(textureWidth) * textureHeight * 4));
        if (!imageData) return;
        const int scaledSize = std::max(1, static_cast<int>(std::ceil(size * font->mScalingFactor)));
        pdg_em_rasterize_text(text, font->getFontName(), scaledSize, static_cast<int>(style),
                              textureWidth, textureHeight, textInfo->ascent, imageData);

        glGenTextures(1, &textInfo->texture);
        port.mStateCache.bindTexture(textInfo->texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // WebGL maps legacy alpha-only textures inconsistently under Emscripten's
        // fixed-function emulation. White RGB lets glColor4f tint the glyph while
        // the Canvas2D coverage remains in alpha.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        std::free(imageData);
        textInfo->tx = 1.0f;
        textInfo->ty = 1.0f;
        textInfo->tx_topoffset = 0.0f;
        port.addTextToCache(textInfo);
    }

    const Point& topLeft = quad.points[lftTop];
    const Point& topRight = quad.points[rgtTop];
    const Point& bottomLeft = quad.points[lftBot];
    const Point& bottomRight = quad.points[rgtBot];
    port.setOpenGLModesForDrawing(true);
    glColor4f(rgba.red, rgba.green, rgba.blue, rgba.alpha);
    glEnable(GL_TEXTURE_2D);
    port.mStateCache.bindTexture(textInfo->texture);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(bottomLeft.x, bottomLeft.y);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(topLeft.x, topLeft.y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(bottomRight.x, bottomRight.y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(topRight.x, topRight.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

} // namespace pdg

#endif // PDG_NO_GUI
