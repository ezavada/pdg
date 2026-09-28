#ifndef PDG_NO_GUI

#include "pdg_image_file.h"
#include "pdg/sys/graphics.h"
#include "spriterengine/global/settings.h"
#include "spriterengine/objectinfo/universalobjectinterface.h"
#include <algorithm>
#include <cmath>

namespace pdg {
namespace {thread_local SpriteLayer* sDrawingLayer=nullptr;}
PDGImageFile::LayerScope::LayerScope(SpriteLayer* layer):mPrevious(sDrawingLayer){sDrawingLayer=layer;}
PDGImageFile::LayerScope::~LayerScope(){sDrawingLayer=mPrevious;}
SpriteLayer* PDGImageFile::currentDrawingLayer(){return sDrawingLayer;}

PDGImageFile::PDGImageFile(const std::string& initialFilePath,
                         SpriterEngine::point initialDefaultPivot,
                         Image* pdgImage)
    : SpriterEngine::ImageFile(initialFilePath, initialDefaultPivot),
      mPDGImage(pdgImage) {
    if (mPDGImage) mPDGImage->addRef();
}

PDGImageFile::~PDGImageFile() {
    if (mPDGImage) mPDGImage->release();
}

void PDGImageFile::renderSprite(SpriterEngine::UniversalObjectInterface* object) {
    auto* layer = sDrawingLayer;
    if (!mPDGImage || !object || !layer) return;
    Port* port = layer->getSpritePort();
    if (!port) return;

    const auto position = object->getPosition();
    const auto scale = object->getScale();
    const auto pivot = object->getPivot();
    const auto imageBounds = mPDGImage->getImageBounds();
    const float width = imageBounds.width() * scale.x;
    const float height = imageBounds.height() * scale.y;
    // Signed corner order preserves texture reflection; rotate around the
    // authored pivot before applying the layer transform exactly once.
    Quad quad(Rect(-pivot.x * width, -pivot.y * height,
                   (1 - pivot.x) * width, (1 - pivot.y) * height));
    quad.rotateAround(object->getAngle(), Point(0, 0));
    quad.moveRight(position.x);
    quad.moveDown(position.y);
    quad = layer->layerToPort(quad);

    struct RestoreOpacity {
        Image* image;
        uint8 opacity;
        ~RestoreOpacity() { image->setOpacity(opacity); }
    } restore{mPDGImage, mPDGImage->getOpacity()};
    const double alpha = object->getAlpha();
    mPDGImage->setOpacity(static_cast<uint8>(restore.opacity
        * (std::isfinite(alpha) ? std::clamp(alpha, 0.0, 1.0) : 0.0)));
    Attributes attributes;
    if (SpriterEngine::Settings::renderDebugBoxes)
        attributes.lineColor(Color(0.0f, 1.0f, 0.0f, 0.3f));
    else attributes.lineStyle(lineStyle_None);
    port->drawImage(mPDGImage, quad, attributes);
}
}
#endif // !PDG_NO_GUI
