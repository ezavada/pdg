#ifndef PDG_NO_GUI

// for debug rendering, so only include if we have a GUI

#include "pdg_bone_instance_info.h"
#include "pdg/sys/os.h"
#include "pdg/sys/graphics.h"
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
    // create initial bone quad - ensure points form a proper quadrilateral
    // Use the same diamond shape as SFML example but ensure proper ordering
    mQuad.points[0] = Point(0, mSize.y/2);        // left center
    mQuad.points[1] = Point(4, 0);                // top point
    mQuad.points[2] = Point(mSize.x, mSize.y/2);  // right center  
    mQuad.points[3] = Point(4, mSize.y);          // bottom point
}

void PDGBoneInstanceInfo::render()
{
    // Only render if debug bones are enabled
    if (!SpriterEngine::Settings::renderDebugBones) {
        SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoneInstanceInfo: Debug bones disabled, skipping render"));
        return;
    }

    if (!mPort) {
        mPort = GraphicsManager::getSingletonInstance()->getMainPort();
        if (!mPort) {
            SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoneInstanceInfo: No port available for rendering"));
            return;
        }
    }
    
    // Get sprite element properties from SpriterPlusPlus (same as pdg_image_file.cpp)
    SpriterEngine::point position = getPosition();
    SpriterEngine::real angle = getAngle();
    SpriterEngine::point scale = getScale();
    
    SPRITER_DEBUG_ONLY(OS::_DOUT("PDGBoneInstanceInfo: Rendering bone at position (%.2f, %.2f) angle %.2f scale (%.2f, %.2f)", 
              position.x, position.y, angle, scale.x, scale.y));
    
    // Bones typically pivot at their left center point (like SFML example)
    Quad quad = mQuad;

    // Apply scale to the quad points
    quad.points[0].x = quad.points[0].x * scale.x;
    quad.points[0].y = quad.points[0].y * scale.y;
    quad.points[1].x = quad.points[1].x * scale.x;
    quad.points[1].y = quad.points[1].y * scale.y;
    quad.points[2].x = quad.points[2].x * scale.x;
    quad.points[2].y = quad.points[2].y * scale.y;
    quad.points[3].x = quad.points[3].x * scale.x;
    quad.points[3].y = quad.points[3].y * scale.y;

    // Apply rotation around the bone's center (left center point)
    Point center = Point(0, mSize.y * scale.y * 0.5f);
    quad.rotateAround(angle, center);

    // Apply position offset
    quad.moveDown(position.y);
    quad.moveRight(position.x);

    // Draw filled semi-transparent green diamond for bone
    mPort->drawQuad(quad, Attributes().fillColor(Color(0, 255, 0, 50)) // semi-transparent green
        .lineColor(Color(0, 255, 0, 192)).lineThickness(1.0)); // nearly solid green
    
    //center.x += position.x;
    //center.y += position.y;
    //mPort->fillCircle(center, 3, Color(0, 255, 0, 255));
    SPRITER_DEBUG_ONLY(
        OS::_DOUT("PDGBoneInstanceInfo: Rendered debug bone at (%.2f, %.2f) "
              "scale (%.2f, %.2f) angle %.2f --> pdg quad (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f) (%.2f, %.2f)",
                position.x, position.y, scale.x, scale.y, angle,
                quad.points[0].x, quad.points[0].y, quad.points[1].x, quad.points[1].y, 
                quad.points[2].x, quad.points[2].y, quad.points[3].x, quad.points[3].y
              );
    )
}

void PDGBoneInstanceInfo::setPort(Port* port)
{
    mPort = port;
}

}

#endif // !PDG_NO_GUI
