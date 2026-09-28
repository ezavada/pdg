#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
#include "pdg_image_file.h"
#include "spriterengine/global/settings.h"

#include "pdg_point_instance_info.h"
#include "pdg/sys/coordinates.h"
#include "pdg/sys/port.h"
#include "pdg/sys/image.h"
#include "pdg/sys/graphicsmanager.h"

#include <cmath>

//#define PDG_DEBUG_SPRITER

#ifdef PDG_DEBUG_SPRITER
  #define SPRITER_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define SPRITER_DEBUG_ONLY(x)
#endif

namespace pdg {

PDGPointInstanceInfo::PDGPointInstanceInfo(Port* port)
    : mPort(port)
    , mPointName("")
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: Created point instance info at %p with port %p", this, port));
}

void PDGPointInstanceInfo::render()
{
    if (!SpriterEngine::Settings::renderDebugPoints) return;
    auto* layer = PDGImageFile::currentDrawingLayer();
    Port* port = layer ? layer->getSpritePort() : mPort;
    if (!layer && !port) port = GraphicsManager::getSingletonInstance()->getMainPort();
    if (!port) return;

    // Position is already evaluated through the Sprite root. Scaling it again
    // would move the socket away from its artwork and queried attachment point.
    const auto position = getPosition();
    const auto angle = getAngle();
    Point center(position.x, position.y);
    Point direction(position.x + std::cos(angle) * 10,
                    position.y + std::sin(angle) * 10);
    if (layer) {
        center = layer->layerToPort(center);
        direction = layer->layerToPort(direction);
    }
    // Keep the origin marker readable in port pixels at any zoom level.
    port->drawCircle(center, 5, Attributes().fillColor(Color(0, 0, 255, 128))
        .lineColor(Color(0, 0, 255, 255)));
    port->drawLine(center, direction, Attributes().lineColor(Color(0, 0, 255, 255)));
}

void PDGPointInstanceInfo::setObjectToLinear(SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::UniversalObjectInterface *resultObject)
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: setObjectToLinear"));
    // Interpolate between this object and bObject at time t
    SpriterEngine::point newPosition = SpriterEngine::linear(getPosition(), bObject->getPosition(), t);
    SpriterEngine::real newAngle = getAngle() + (bObject->getAngle() - getAngle()) * t;

    // Apply the interpolated values to the result object
    resultObject->setPosition(newPosition);
    resultObject->setAngle(newAngle);
}

void PDGPointInstanceInfo::setToBlendedLinear(SpriterEngine::UniversalObjectInterface *aObject, SpriterEngine::UniversalObjectInterface *bObject, SpriterEngine::real t, SpriterEngine::real blendRatio, SpriterEngine::ObjectRefInstance *blendedRefInstance)
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: setToBlendedLinear"));
    // Store current values for blending
    SpriterEngine::real tempAngle = getAngle();
    SpriterEngine::point tempPosition = getPosition();

    // First, interpolate between aObject and bObject at time t
    aObject->setObjectToLinear(bObject, t, this);

    // Then blend between the stored values and the interpolated values
    setAngle(SpriterEngine::shortestAngleLinear(tempAngle, getAngle(), blendRatio));
    setPosition(SpriterEngine::linear(tempPosition, getPosition(), blendRatio));
}

void PDGPointInstanceInfo::setPort(Port* port)
{
    mPort = port;
}

}

#endif // !PDG_NO_GUI
