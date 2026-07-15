#ifndef PDG_NO_GUI

// for rendering, so only include if we have a GUI

#include "pdg_image_file.h"
#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
#include "spriterengine/global/settings.h"
#include "spriterengine/objectinfo/universalobjectinterface.h"
#include "image-impl.h"

#ifdef PDG_DEBUG_SPRITER
#define SPRITER_DEBUG_ONLY(x) x
#else
#define SPRITER_DEBUG_ONLY(x)
#endif

namespace pdg {

PDGImageFile::PDGImageFile(const std::string& initialFilePath, 
                           SpriterEngine::point initialDefaultPivot, 
                           Image* pdgImage, 
                           //Sprite* sprite,
                           Port* port)
    : SpriterEngine::ImageFile(initialFilePath, initialDefaultPivot)
    , mPDGImage(pdgImage)
    //, mSprite(sprite)
    , mPort(port)
 {

    if (mPDGImage) {
        mPDGImage->addRef(); // Add a reference to prevent premature deletion
        SPRITER_DEBUG_ONLY(
            OS::_DOUT("PDGImageFile: Created wrapper for image: %s", initialFilePath.c_str());
        )
    } else {
        DEBUG_ONLY(
            OS::_DOUT("PDGImageFile: Warning - created wrapper with null PDG image: %s", initialFilePath.c_str());
        )
    }

    //if (mSprite) {
    //    mSprite->addRef(); // Add a reference to prevent premature deletion
    //    OS::_DOUT("PDGImageFile: Created wrapper for sprite: %s", initialFilePath.c_str());
    //} else {
    //    OS::_DOUT("PDGImageFile: Warning - created wrapper with null sprite: %s", initialFilePath.c_str());
    //}
}

PDGImageFile::~PDGImageFile()
{
    if (mPDGImage) {
        mPDGImage->release(); // Release our reference
        mPDGImage = nullptr;
    }
    //if (mSprite) {
    //    mSprite->release(); // Release our reference
    //    mSprite = nullptr;
    //}
}

// This is called by SpriterPlusPlus to render the sprite element
// The sprite element is contained in a pdg Sprite, which can be manipulated
// by the normal pdg Sprite methods; but also applies animations to the
// sprite elements using the SpriterPlusPlus interface.
void PDGImageFile::renderSprite(SpriterEngine::UniversalObjectInterface* spriteElementInfo)
{
    if (!mPDGImage || !spriteElementInfo) {
        DEBUG_ONLY(
            OS::_DOUT("PDGImageFile::renderSprite: Missing image or spriteElementInfo - mPDGImage=%p, spriteElementInfo=%p", mPDGImage, spriteElementInfo);
        )
        return;
    }
    
    // Get the port for rendering - use the set port or get from GraphicsManager
    Port* renderPort = mPort; //mSprite->mPort;
    if (!renderPort) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGImageFile: No port available for rendering"));
        return;
    }

    // Get sprite elementproperties from SpriterPlusPlus
    SpriterEngine::point position = spriteElementInfo->getPosition();
    SpriterEngine::real angle = spriteElementInfo->getAngle();
    SpriterEngine::point scale = spriteElementInfo->getScale();
    SpriterEngine::point pivot = spriteElementInfo->getPivot();
    SpriterEngine::real alpha = spriteElementInfo->getAlpha();
    
    // Set image properties based on alpha from Spriter and pdg Sprite's opacity
    float opacity = 255.0f; //mSprite->mOpacity; // 0 - 255
    mPDGImage->setOpacity((uint8)(alpha * opacity));

    //Point spritePos = mSprite->mLocation;
    //float spriteAngle = mSprite->mFacing;
    //Point spritePivot = mSprite->mCenterOffset;
    
    // Calculate the destination rectangle for drawing
    Rect baseRect = mPDGImage->getImageBounds();
    baseRect.horzScale(scale.x);
    baseRect.vertScale(scale.y);
    float width = baseRect.width();
    float height = baseRect.height();
    Point pivotPoint(pivot.x * width, pivot.y * height); // this is offset from top left corner
    baseRect.moveTo( position.x - pivotPoint.x, position.y - pivotPoint.y); // position is relative to the pivot point
 
//    RotatedRect drawRect(baseRect);
//    Point topLeftCornerOffset(- width/2, - height/2); // offset from center to top left corner
//    Point newCenter = topLeftCornerOffset + pivotPoint;
//    drawRect.setCenterOffset(newCenter);
//    drawRect.setRotation(angle);

    // Draw the image using PDG's Port with rotation
    Attributes imgAttrs; // = Attributes().texture(mPDGImage).fitType(fit_Fill);
    if (SpriterEngine::Settings::renderDebugBoxes) {
        imgAttrs.lineColor(Color(0.0f, 1.0f, 0.0f, 0.3f));
    } else {
        imgAttrs.lineStyle(lineStyle_None);
    }
//    renderPort->drawQuad(drawRect, imgAttrs);

    // Draw the actual image with rotation and scale transformations
    Point rotationPoint = baseRect.leftTop() + pivotPoint;
    imgAttrs.rotation(angle, rotationPoint);
    renderPort->drawImage(mPDGImage, baseRect, imgAttrs);

    ImageImpl* imageImpl = dynamic_cast<ImageImpl*>(mPDGImage);

    SPRITER_DEBUG_ONLY(
        std::string name = imageImpl->mSourceName;
        name = name.substr(name.find_last_of('/') + 1);
        //if (strcmp(name.c_str(), "head_0.png") == 0) {
        Quad quad = drawRect.getQuad();
        OS::_DOUT("PDGImageFile: Rendered spriter element image %s at (%.2f, %.2f) "
            "scale (%.2f, %.2f) pivot (%.2f, %.2f) angle %.2f alpha %.2f\npdgRRect (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)\n"
            "baseRect (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f) angle %.2f around (%.2f, %.2f)",
              name.c_str(), position.x, position.y, scale.x, scale.y, pivot.x, pivot.y, angle, alpha,
              quad.points[0].x, quad.points[0].y, quad.points[1].x, quad.points[1].y, quad.points[2].x, quad.points[2].y, quad.points[3].x, quad.points[3].y,
              baseRect.leftTop().x, baseRect.leftTop().y, baseRect.rightTop().x, baseRect.rightTop().y, baseRect.rightBottom().x, baseRect.rightBottom().y, baseRect.leftBottom().x, baseRect.leftBottom().y,
              angle, rotationPoint.x, rotationPoint.y
            );
        //}
    )
}

} // namespace pdg

#endif // !PDG_NO_GUI
