// Internal helpers for application-framework views.

#ifndef PDG_APP_VIEW_UTILS_H_INCLUDED
#define PDG_APP_VIEW_UTILS_H_INCLUDED

#include "pdg/sys/attributes.h"
#include "pdg/sys/image.h"
#include "pdg/sys/port.h"
#include "pdg/sys/resource.h"

#include <algorithm>
#include <string>
#include <string_view>

namespace pdg::app {

template <typename MeasureLine, typename DrawLine>
int forEachWrappedLine(
    const char* text,
    int maxLineWidth,
    MeasureLine measureLine,
    DrawLine drawLine)
{
    if (!text) {
        return 0;
    }

    int linesDrawn = 0;
    std::string_view remaining(text);

    do {
        const std::size_t hardBreak = remaining.find('|');
        std::string_view paragraph = remaining.substr(0, hardBreak);
        if (hardBreak == std::string_view::npos) {
            remaining = {};
        } else {
            remaining.remove_prefix(hardBreak + 1);
        }

        do {
            std::size_t length = paragraph.size();
            while (length > 0 && maxLineWidth < measureLine(paragraph, length)) {
                --length;
            }
            if (length < paragraph.size()) {
                const std::size_t breakAt = paragraph.find_last_of(" -", length);
                length = (breakAt != std::string_view::npos && breakAt > 0)
                    ? breakAt + 1
                    : std::max<std::size_t>(length, 1);
            }

            drawLine(paragraph.substr(0, length));
            ++linesDrawn;
            paragraph.remove_prefix(length);
        } while (!paragraph.empty());
    } while (!remaining.empty());

    return linesDrawn;
}

inline Image* loadImage(
    Port* port,
    ResourceManager& resourceManager,
    int id,
    int index = 0,
    const Color* transparentColor = nullptr)
{
    std::string imageNameStorage;
    const char* imageName = resourceManager.getString(imageNameStorage, id, index);
    if (!imageName || imageName[0] == '\0') {
        return nullptr;
    }

    Image* image = resourceManager.getImage(imageName);
    if (image) {
        image->setPort(port);
        if (transparentColor) {
            image->setTransparentColor(*transparentColor);
        }
    }
    return image;
}

inline void loadImageArray(
    Port* port,
    ResourceManager& resourceManager,
    Image* images[],
    int id,
    int imageCount,
    const Color* transparentColor = nullptr)
{
    for (int i = 0; i < imageCount; ++i) {
        images[i] = loadImage(port, resourceManager, id, i, transparentColor);
    }
}

inline void unloadImage(Image*& image)
{
    if (image) {
        image->release();
        image = nullptr;
    }
}

inline void unloadImageArray(Image* images[], int imageCount)
{
    for (int i = 0; i < imageCount; ++i) {
        unloadImage(images[i]);
    }
}

inline void scaleImage(
    Image*& image,
    float scale,
    Image::FilterType filter = Image::filter_Best)
{
    if (image) {
        Image* scaledImage = image->createImageScaled(scale, scale, filter);
        image->release();
        image = scaledImage;
    }
}

inline void scaleImageArray(
    Image* images[],
    int imageCount,
    float scale,
    Image::FilterType filter = Image::filter_Best)
{
    for (int i = 0; i < imageCount; ++i) {
        scaleImage(images[i], scale, filter);
    }
}

inline void scaleImageArrayToFit(
    Image* images[],
    int imageCount,
    const Rect& bounds,
    Image::FilterType filter = Image::filter_Best)
{
    for (int i = 0; i < imageCount; ++i) {
        if (images[i]) {
            Image* scaledImage = images[i]->createImageScaledToFit(bounds, fit_Fill, filter);
            images[i]->release();
            images[i] = scaledImage;
        }
    }
}

inline int drawMultilineText(
    Port* port,
    const char* text,
    int size,
    const Color& color,
    const Rect& textArea,
    int style = textStyle_Plain + textStyle_Centered,
    const Attributes* appearance = nullptr)
{
    if (!port || !text) {
        return 0;
    }

    Attributes attrs=Attributes().textSize(size).textStyle(style).fillColor(color);
    if (appearance) attrs=attrs.withAppearance(*appearance,true);
    size=attrs.getTextSize(); style=attrs.getTextStyle();
    Font* font = attrs.getFont() ? attrs.getFont() : port->getCurrentFont(style);
    struct FontScope {
        Port* port;
        Font* saved;
        int style;
        FontScope(Port* port, Font* replacement, int style) : port(port), saved(nullptr), style(style) {
            if (replacement) {
                saved = port->getCurrentFont(style);
                if (saved) saved->addRef();
                port->setFontForStyle(replacement, style);
            }
        }
        ~FontScope() {
            if (saved) { port->setFontForStyle(saved, style); saved->release(); }
        }
    } fontScope(port, attrs.getFont(), style);
    const int lineOffset = font->getFontHeight(size, style) + font->getFontLeading(size, style);
    const int x = (style & textStyle_Centered)
        ? textArea.left + textArea.width() / 2
        : ((style & textStyle_RightJustified) ? textArea.right : textArea.left);
    int y = textArea.top + font->getFontAscent(size, style);
    const int linesDrawn = forEachWrappedLine(
        text,
        textArea.width(),
        [port, size, style](std::string_view line, std::size_t length) {
            return port->getTextWidth(line.data(), size, style, static_cast<int>(length));
        },
        [port, attrs, x, &y, lineOffset](std::string_view line) {
            const std::string terminated(line);
            port->drawText(
                terminated.c_str(),
                Point(x, y),
                attrs);
            y += lineOffset;
        });

    return linesDrawn * lineOffset;
}

} // namespace pdg::app

#endif // PDG_APP_VIEW_UTILS_H_INCLUDED
