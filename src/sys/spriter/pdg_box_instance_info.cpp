#include "pdg_box_instance_info.h"

#ifndef PDG_NO_GUI
#include "pdg_image_file.h"
#include "pdg_spriter_transform.h"
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
    if (!SpriterEngine::Settings::renderDebugBoxes) return;
    auto* layer = PDGImageFile::currentDrawingLayer();
    Port* port = layer ? layer->getSpritePort() : mPort;
    if (!layer && !port) port = GraphicsManager::getSingletonInstance()->getMainPort();
    if (!port) return;

    // Use exactly the geometry exposed by Sprite collision-box queries,
    // including signed scale and the authored pivot, then map into the port.
    Quad quad = spriterBoxRect(*this).getQuad();
    if (layer) quad = layer->layerToPort(quad);
    port->drawQuad(quad, Attributes().fillColor(Color(255, 0, 0, 64))
        .lineColor(Color(255, 0, 0, 255)));
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

