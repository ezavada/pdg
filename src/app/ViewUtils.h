// Internal helpers for application-framework views.

#ifndef PDG_APP_VIEW_UTILS_H_INCLUDED
#define PDG_APP_VIEW_UTILS_H_INCLUDED

#include "pdg/sys/attributes.h"
#include "pdg/sys/image.h"
#include "pdg/sys/port.h"
#include "pdg/sys/resource.h"

#include <algorithm>
#include <string>

namespace pdg::app {

inline Image* loadImage(
    Port* port,
    ResourceManager& resourceManager,
    int id,
    int index = 0,
    const Color* transparentColor = nullptr)
{
    std::string imageNameStorage;
    const char* imageName = resourceManager.getString(imageNameStorage, id, index);
    if (!imageName) {
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
    int style = textStyle_Plain + textStyle_Centered)
{
    if (!port || !text) {
        return 0;
    }

    Font* font = port->getCurrentFont(style);
    const int lineOffset = font->getFontHeight(size, style) + font->getFontLeading(size, style);
    const int x = (style & textStyle_Centered)
        ? textArea.left + textArea.width() / 2
        : ((style & textStyle_RightJustified) ? textArea.right : textArea.left);
    int y = textArea.top + font->getFontAscent(size, style);
    int linesDrawn = 0;
    std::string remaining(text);

    do {
        const std::size_t hardBreak = remaining.find('|');
        std::string paragraph = remaining.substr(0, hardBreak);
        if (hardBreak == std::string::npos) {
            remaining.clear();
        } else {
            remaining.erase(0, hardBreak + 1);
        }

        do {
            std::size_t length = paragraph.size();
            while (length > 0
                && textArea.width() < port->getTextWidth(paragraph.c_str(), size, style, static_cast<int>(length))) {
                --length;
            }
            if (length < paragraph.size()) {
                const std::size_t breakAt = paragraph.find_last_of(" -", length);
                length = (breakAt != std::string::npos && breakAt > 0)
                    ? breakAt + 1
                    : std::max<std::size_t>(length, 1);
            }

            const std::string line = paragraph.substr(0, length);
            port->drawText(
                line.c_str(),
                Point(x, y),
                Attributes().textSize(size).textStyle(style).fillColor(color));
            ++linesDrawn;
            y += lineOffset;
            paragraph.erase(0, length);
        } while (!paragraph.empty());
    } while (!remaining.empty());

    return linesDrawn * lineOffset;
}

} // namespace pdg::app

#endif // PDG_APP_VIEW_UTILS_H_INCLUDED
