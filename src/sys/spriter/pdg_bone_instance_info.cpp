#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "pdg_bone_instance_info.h"
#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
#include "pdg_image_file.h"
#include "spriterengine/global/settings.h"

#ifdef PDG_DEBUG_SPRITER
  #define SPRITER_DEBUG_ONLY(x) DEBUG_ONLY(x)
#else
  #define SPRITER_DEBUG_ONLY(x)
#endif


namespace pdg {

PDGBoneInstanceInfo::PDGBoneInstanceInfo(SpriterEngine::point size, Port* port)
    : SpriterEngine::BoneInstanceInfo(size)
    , mPort(port)
    , mSize(size)
    , mQuad()
{
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoneInstanceInfo: Created bone instance info with size (%.2f, %.2f)", size.x, size.y));
    // The bone origin is the left tip of the diamond, just like the
    // evaluated bone transform and its attached artwork.
    mQuad.points[0] = Point(0, 0);
    mQuad.points[1] = Point(4, -mSize.y / 2);
    mQuad.points[2] = Point(mSize.x, 0);
    mQuad.points[3] = Point(4, mSize.y / 2);
}

void PDGBoneInstanceInfo::render()
{
    if (!SpriterEngine::Settings::renderDebugBones) return;
    auto* layer = PDGImageFile::currentDrawingLayer();
    Port* port = layer ? layer->getSpritePort() : mPort;
    if (!layer && !port) port = GraphicsManager::getSingletonInstance()->getMainPort();
    if (!port) return;

    const auto position = getPosition();
    const auto scale = getScale();
    Quad quad = mQuad;
    for (auto& point : quad.points) {
        point.x *= scale.x;
        point.y *= scale.y;
    }
    quad.rotateAround(getAngle(), Point(0, 0));
    quad.moveRight(position.x);
    quad.moveDown(position.y);
    // Evaluated objects include the Sprite transform, but not its layer.
    if (layer) quad = layer->layerToPort(quad);
    port->drawQuad(quad, Attributes().fillColor(Color(0, 255, 0, 50))
        .lineColor(Color(0, 255, 0, 192)).lineThickness(1.0));
}

void PDGBoneInstanceInfo::setPort(Port* port)
{
    mPort = port;
}

}

#endif // !PDG_NO_GUI
