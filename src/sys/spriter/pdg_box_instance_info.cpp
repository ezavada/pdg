#include "pdg_box_instance_info.h"

#ifndef PDG_NO_GUI
#include "pdg/sys/coordinates.h"
#include "pdg/sys/port.h"
#include "pdg/sys/image.h"
#include "pdg/sys/graphicsmanager.h"
#endif

#include "pdg/sys/os.h"
#include "spriterengine/global/settings.h"


using namespace pdg;

//#define PDG_DEBUG_SPRITER

#ifdef PDG_DEBUG_SPRITER
  #define SPRITER_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define SPRITER_DEBUG_ONLY(x)
#endif

namespace pdg {

#ifndef PDG_NO_GUI
PDGBoxInstanceInfo::PDGBoxInstanceInfo(SpriterEngine::point size, Port* port)
    : SpriterEngine::BoxInstanceInfo(size)
    , mPort(port)
    , mSize(size)
    , mBoxName("")  // Initialize empty box name
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: Created box instance info with size (%.2f, %.2f)", size.x, size.y));
}
#else
PDGBoxInstanceInfo::PDGBoxInstanceInfo(SpriterEngine::point size)
    : SpriterEngine::BoxInstanceInfo(size)
    , mSize(size)
    , mBoxName("")  // Initialize empty box name
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: Created box instance info with size (%.2f, %.2f)", size.x, size.y));
}
#endif

void PDGBoxInstanceInfo::render()
{
#ifndef PDG_NO_GUI
    // Only render if debug boxes are enabled
    if (!SpriterEngine::Settings::renderDebugBoxes) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: Debug boxes disabled, skipping render"));
        return;
    }

    if (!mPort) {
        mPort = GraphicsManager::getSingletonInstance()->getMainPort();
        if (!mPort) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: No port available for rendering"));
            return;
        }
    }

    // Get sprite element properties from SpriterPlusPlus (same as pdg_image_file.cpp)
    SpriterEngine::point position = getPosition();
    SpriterEngine::real angle = getAngle();
    SpriterEngine::point scale = getScale();
    SpriterEngine::point pivot = getPivot();
    
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: Rendering box at position (%.2f, %.2f) angle %.2f scale (%.2f, %.2f) pivot (%.2f, %.2f)", 
              position.x, position.y, angle, scale.x, scale.y, pivot.x, pivot.y));
    
    // Calculate the destination rectangle for drawing (same approach as pdg_image_file.cpp)
    float width = mSize.x;
    float height = mSize.y;
    Point pivotPoint(pivot.x * width, pivot.y * height); // this is offset from top left corner

    RotatedRect drawRect(Rect(0, 0, width, height));
 
    drawRect.horzScale(scale.x);
    drawRect.vertScale(scale.y);
    Quad quad = drawRect.getQuad();
    quad.rotateAround(angle, pivotPoint);

    quad.moveDown(position.y - pivotPoint.y);
    quad.moveRight(position.x - pivotPoint.x);
    
    // Draw filled semi-transparent red rectangle for collisionbox
    mPort->drawQuad(quad, Attributes().fillColor(Color(255, 0, 0, 64)) // Semi-transparent red
        .lineColor(Color(255, 0, 0, 255))); // outline solid red

    SPRITER_DEBUG_ONLY(
      OS::_DOUT("PDGBoxInstanceInfo: Rendered debug box at (%.2f, %.2f) "
            "scale (%.2f, %.2f) pivot (%.2f, %.2f) angle %.2f --> pdg rotated rect (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)",
              position.x, position.y, scale.x, scale.y, pivot.x, pivot.y, angle,
              quad.points[0].x, quad.points[0].y, quad.points[1].x, quad.points[1].y, 
              quad.points[2].x, quad.points[2].y, quad.points[3].x, quad.points[3].y
            );
    )
#else
    // In non-GUI mode, rendering is not supported
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: Rendering not supported in non-GUI mode"));
#endif
}

void PDGBoxInstanceInfo::setObjectToLinear(SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::UniversalObjectInterface *resultObject)
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: setObjectToLinear"));
    // Interpolate between this object and bObject at time t
    SpriterEngine::point newPosition = SpriterEngine::linear(getPosition(), bObject->getPosition(), t);
    SpriterEngine::real newAngle = getAngle() + (bObject->getAngle() - getAngle()) * t;
    SpriterEngine::point newScale = SpriterEngine::linear(getScale(), bObject->getScale(), t);
    SpriterEngine::point newPivot = SpriterEngine::linear(getPivot(), bObject->getPivot(), t);
    SpriterEngine::real newAlpha = SpriterEngine::linear(getAlpha(), bObject->getAlpha(), t);

    // Apply the interpolated values to the result object
    resultObject->setPosition(newPosition);
    resultObject->setAngle(newAngle);
    resultObject->setScale(newScale);
    resultObject->setPivot(newPivot);
    resultObject->setAlpha(newAlpha);
}

void PDGBoxInstanceInfo::setToBlendedLinear(SpriterEngine::UniversalObjectInterface *aObject, SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::real blendRatio, SpriterEngine::ObjectRefInstance *blendedRefInstance)
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoxInstanceInfo: setToBlendedLinear"));
    // Store current values for blending
    SpriterEngine::real tempAngle = getAngle();
    SpriterEngine::point tempPosition = getPosition();
    SpriterEngine::point tempScale = getScale();
    SpriterEngine::point tempPivot = getPivot();
    SpriterEngine::real tempAlpha = getAlpha();

    // First, interpolate between aObject and bObject at time t
    aObject->setObjectToLinear(bObject, t, this);

    // Then blend between the stored values and the interpolated values
    setAngle(SpriterEngine::shortestAngleLinear(tempAngle, getAngle(), blendRatio));
    setPosition(SpriterEngine::linear(tempPosition, getPosition(), blendRatio));
    setScale(SpriterEngine::linear(tempScale, getScale(), blendRatio));
    setPivot(SpriterEngine::linear(tempPivot, getPivot(), blendRatio));
    setAlpha(SpriterEngine::linear(tempAlpha, getAlpha(), blendRatio));
}

#ifndef PDG_NO_GUI
void PDGBoxInstanceInfo::setPort(Port* port)
{
    mPort = port;
}
#endif

}

