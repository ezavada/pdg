#include "pdg/framework.h"
#include "pdg_em_adaptors.h"
#include "pdg_em_c_dispatch.h"
#include <array>
#include "pdg_em_parts.h"
#include "pdg_em_bone.h"
#include "pdg_em_particles.h"
#include "pdg_em_animation_helpers.h"
#include "pdg_em_camera.h"
#include "pdg_em_animation_scripts.h"

// remap some constants

#define animate_StartToEnd Sprite::animate_StartToEnd
#define animate_EndToStart Sprite::animate_EndToStart
#define animate_Unidirectional Sprite::animate_Unidirectional
#define animate_Bidirectional Sprite::animate_Bidirectional
#define animate_NoLooping Sprite::animate_NoLooping
#define animate_Looping Sprite::animate_Looping
#define start_FromFirstFrame Sprite::start_FromFirstFrame
#define start_FromLastFrame Sprite::start_FromLastFrame
#define all_Frames Sprite::all_Frames
#define action_CollideSprite Sprite::action_CollideSprite
#define action_CollideWall Sprite::action_CollideWall
#define action_Offscreen Sprite::action_Offscreen
#define action_Onscreen Sprite::action_Onscreen
#define action_ExitLayer Sprite::action_ExitLayer
#define action_AnimationLoop Sprite::action_AnimationLoop
#define action_AnimationEnd Sprite::action_AnimationEnd
#define action_FadeComplete Sprite::action_FadeComplete
#define action_FadeInComplete Sprite::action_FadeInComplete
#define action_FadeOutComplete Sprite::action_FadeOutComplete
#define action_JointBreak Sprite::action_JointBreak
#define touch_MouseEnter Sprite::touch_MouseEnter
#define touch_MouseLeave Sprite::touch_MouseLeave
#define touch_MouseDown Sprite::touch_MouseDown
#define touch_MouseUp Sprite::touch_MouseUp
#define touch_MouseClick Sprite::touch_MouseClick
#define collide_None Sprite::collide_None
#define collide_Point Sprite::collide_Point
#define collide_BoundingBox Sprite::collide_BoundingBox
#define collide_CollisionRadius Sprite::collide_CollisionRadius
#define collide_AlphaChannel Sprite::collide_AlphaChannel
#define collide_Last Sprite::collide_Last

#define facing_North TileLayer::facing_North
#define facing_East TileLayer::facing_East
#define facing_South TileLayer::facing_South
#define facing_West TileLayer::facing_West
#define facing_Ignore TileLayer::facing_Ignore
#define flipped_None TileLayer::flipped_None
#define flipped_Horizontal TileLayer::flipped_Horizontal
#define flipped_Vertical TileLayer::flipped_Vertical
#define flipped_Both TileLayer::flipped_Both
#define flipped_Ignore TileLayer::flipped_Ignore


// remap some functions

#define rand OS::rand
#define srand OS::srand
#define registerSerializableClass Deserializer::registerClass

#define getFileManager FileManager::getSingletonInstance
#define getLogManager LogManager::getSingletonInstance
#define getConfigManager ConfigManager::getSingletonInstance
#define getResourceManager ResourceManager::getSingletonInstance
#define getEventManager EventManager::getSingletonInstance
#define getTimerManager TimerManager::getSingletonInstance
#define getGraphicsManager GraphicsManager::getSingletonInstance
#define getSoundManager SoundManager::getSingletonInstance


// remap some type names

namespace pdg {
    typedef ::cpSpace CpSpace;
    typedef ::cpArbiter CpArbiter;
    typedef ::cpConstraint CpConstraint;
};

// Metadata-generated registrations include the explicit custom adapter fragments.
#include "pdg.embind"

// Quad uses the ordinary JavaScript {points: [Point, Point, Point, Point]} shape.
// Keep the hand-written value conversion alongside other embind adapters.
namespace pdg {
static std::array<Point,4> drawingQuadPoints(const Quad& quad) {
    return {{quad.points[0],quad.points[1],quad.points[2],quad.points[3]}};
}
static void setDrawingQuadPoints(Quad& quad, const std::array<Point,4>& points) {
    for (unsigned i=0;i<4;++i) quad.points[i]=points[i];
}
}
EMSCRIPTEN_BINDINGS(pdg_quad_value) {
    emscripten::value_array<std::array<pdg::Point,4>>("_QuadPointsValue")
        .element(emscripten::index<0>()).element(emscripten::index<1>())
        .element(emscripten::index<2>()).element(emscripten::index<3>());
    emscripten::value_object<pdg::Quad>("_QuadValue")
        .field("points", &pdg::drawingQuadPoints, &pdg::setDrawingQuadPoints);
}

#ifdef PDG_BROWSER_BINDING_TESTS
#include "../../../test/cxx/browser_chipmunk_fixture.h"
#endif
