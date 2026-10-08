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

// Keep Canvas2D resources per WASM module, rather than allocating a canvas on
// every measurement or cache miss. Raster pixels stay in the browser/GPU path.
EM_JS(void, pdg_em_init_text_canvases, (), {
    if (Module['pdgTextCanvases']) return;
    if (typeof document === 'undefined' && typeof OffscreenCanvas === 'undefined') return;
    const create = () => {
        const canvas = typeof OffscreenCanvas !== 'undefined'
            ? new OffscreenCanvas(1, 1) : document.createElement('canvas');
        return {canvas, context: canvas.getContext('2d'), font: ''};
    };
    Module['pdgTextCanvases'] = {measure: create(), raster: create()};
});

EM_JS(double, pdg_em_measure_text, (const char* text, const char* family, int size, int style), {
    const value = UTF8ToString(text);
    const state = Module['pdgTextCanvases'];
    if (!state) return value.length * size * 0.6;
    const font = ((style & 2) ? 'italic ' : '') + ((style & 1) ? 'bold ' : '')
        + size + 'px ' + (UTF8ToString(family) || 'Arial');
    if (state.measure.font !== font) {
        state.measure.context.font = font;
        state.measure.font = font;
    }
    return state.measure.context.measureText(value).width;
});

EM_JS(double, pdg_em_cap_height, (const char* family, int size, int style), {
    const state = Module['pdgTextCanvases'];
    if (!state) return size * 0.8;
    const font = ((style & 2) ? 'italic ' : '') + ((style & 1) ? 'bold ' : '')
        + size + 'px ' + (UTF8ToString(family) || 'Arial');
    if (state.measure.font !== font) {
        state.measure.context.font = font;
        state.measure.font = font;
    }
    return state.measure.context.measureText('H').actualBoundingBoxAscent;
});

EM_JS(int, pdg_em_upload_text,
      (const char* text, const char* family, int size, int style, int width, int height, int ascent, int x, int y), {
    const state = Module['pdgTextCanvases'];
    if (!state) return 0;
    const {canvas, context} = state.raster;
    if (canvas.width !== width) canvas.width = width;
    if (canvas.height !== height) canvas.height = height;
    context.clearRect(0, 0, width, height);
    context.font = ((style & 2) ? 'italic ' : '') + ((style & 1) ? 'bold ' : '')
        + size + 'px ' + (UTF8ToString(family) || 'Arial');
    context.textBaseline = 'alphabetic';
    context.fillStyle = '#fff';
    context.fillText(UTF8ToString(text), 0, ascent);
    if (style & 4) {
        const thickness = Math.max(1, Math.ceil(size / 12));
        context.fillRect(0, ascent + thickness, width, thickness);
    }
    const gl = GL.currentContext.GLctx;
    const premultiplied = gl.getParameter(gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL);
    const flip = gl.getParameter(gl.UNPACK_FLIP_Y_WEBGL);
    gl.pixelStorei(gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, true);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, false);
    gl.texSubImage2D(gl.TEXTURE_2D, 0, x, y, gl.RGBA, gl.UNSIGNED_BYTE, canvas);
    gl.pixelStorei(gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, premultiplied);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, flip);
    return 1;
});

class FontImplEmscripten final : public FontImpl {
public:
    FontImplEmscripten(Port* port, const char* fontName, float scalingFactor)
        : FontImpl(port, fontName, scalingFactor) { pdg_em_init_text_canvases(); }

    FontMetricsInfo* getFontMetrics(int size, uint32 style) override {
        FontMetricsInfo* metrics = static_cast<FontMetricsInfo*>(std::malloc(sizeof(FontMetricsInfo)));
        if (!metrics) return nullptr;
        const float scaledSize = size * mScalingFactor;
        metrics->size = size;
        metrics->style = style;
        metrics->capHeight = pdg_em_cap_height(getFontName(), std::max(1, static_cast<int>(std::ceil(scaledSize))), style);
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
    auto& port = static_cast<PortImpl&>(*this);
    auto* entry = port.getTextFromCache(text, len, font, size, style);
    if (!entry->measured) {
        const int scaledSize = std::max(1, static_cast<int>(std::ceil(size * font->mScalingFactor)));
        const double advance = pdg_em_measure_text(
            entry->mText.c_str(), font->getFontName(), scaledSize, static_cast<int>(style));
        entry->advanceWidth = advance;
        entry->width = static_cast<int>(std::ceil(advance));
        entry->measured = true;
    }
    return entry->width;
}

void graphics_drawTextRaster(PortImpl& port, const char* text, int len, const Quad& quad,
                       int size, uint32 style, Color rgba, TextCacheEntry* cachedEntry) {
    FontImplEmscripten* font = dynamic_cast<FontImplEmscripten*>(port.getCurrentFont(style));
    if (!font) return;
    TextCacheEntry* textInfo = cachedEntry ? cachedEntry : port.getTextFromCache(text, len, font, size, style);
    if (!textInfo) return;
    if (!textInfo->measured) textInfo->width = port.getTextWidth(text, size, style, len);

    if (textInfo->texture == 0) {
        const int extraWidth = (style & textStyle_Italic) ? size : 0;
        const int textureWidth = std::max(1, textInfo->width + extraWidth);
        const int textureHeight = std::max(1, textInfo->charHeight);
        port.mTextCache.reserveTexture(textInfo, textureWidth, textureHeight, GL_RGBA, port.mStateCache);
        const int scaledSize = std::max(1, static_cast<int>(std::ceil(size * font->mScalingFactor)));
        if (!pdg_em_upload_text(textInfo->mText.c_str(), font->getFontName(), scaledSize,
                                static_cast<int>(style), textureWidth, textureHeight, textInfo->ascent, textInfo->atlasX, textInfo->atlasY)) {
            if (!textInfo->atlas) glDeleteTextures(1, &textInfo->texture);
            textInfo->atlas.reset();
            textInfo->texture = 0;
            port.mStateCache.resetState();
            return;
        }
        textInfo->tx = 1.0f;
        textInfo->ty = 1.0f;
        textInfo->tx_topoffset = 0.0f;
        textInfo->textureBytes = static_cast<size_t>(textureWidth) * textureHeight * 4;
        port.addTextToCache(textInfo);
    }

    graphics_submitText(port, *textInfo, quad, rgba, true);
}

} // namespace pdg

#endif // PDG_NO_GUI
