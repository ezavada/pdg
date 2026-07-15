#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
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
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo::render() called on %p", this));
    
    // Only render if debug points are enabled
    if (!SpriterEngine::Settings::renderDebugPoints) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: Debug points disabled, skipping render"));
        return;
    }

    if (!mPort) {
        mPort = GraphicsManager::getSingletonInstance()->getMainPort();
        if (!mPort) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: No port available for rendering"));
            return;
        }
    }

    // Get sprite element properties from SpriterPlusPlus (same as pdg_image_file.cpp)
    SpriterEngine::point position = getPosition();
    SpriterEngine::real angle = getAngle();
    SpriterEngine::point scale = getScale();
    
    // Handle flipped scaling for points - apply scale transformation to position
    float scaledX = position.x * scale.x;
    float scaledY = position.y * scale.y;
    
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGPointInstanceInfo: About to render point at (%.2f, %.2f) angle %.2f scale (%.2f, %.2f)", 
                                 scaledX, scaledY, angle, scale.x, scale.y));
    
    // Draw a small circle for the point with scaled position
    mPort->drawCircle(Point(scaledX, scaledY), 5, Attributes()
        .fillColor(Color(0, 0, 255, 128)) // translucent blue
        .lineColor(Color(0, 0, 255, 255))); // Blue border

    // draw a short line showing the angle with scaled position
    mPort->drawLine(Point(scaledX, scaledY), Point(scaledX + cos(angle) * 10, scaledY + sin(angle) * 10), 
        Attributes().lineColor(Color(0, 0, 255, 255)));
    
    SPRITER_DEBUG_ONLY(
      OS::_DOUT("PDGPointInstanceInfo: Successfully rendered debug point at (%.2f, %.2f) angle %.2f", 
            scaledX, scaledY, angle);
    )
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
