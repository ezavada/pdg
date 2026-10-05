#include "pdg/framework.h"
#include "pdg_em_adaptors.h"
#include <array>
#include "pdg_em_parts.h"
#include "pdg_em_particles.h"
#include "pdg_em_animation_helpers.h"

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

// a way for us to insert special stuff into the automatic bindings

#ifndef PDG_NO_GUI
#define BrowserLayerView_Extra \
    .function("_layerToPortPoint", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Point& value) { return layer.layerToPort(value); })) \
    .function("_layerToPortOffset", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Offset& value) { return layer.layerToPort(value); })) \
    .function("_layerToPortVector", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Vector& value) { return layer.layerToPort(value); })) \
    .function("_layerToPortRect", &pdg::emscriptenLayerToPortRect) \
    .function("_portToLayerPoint", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Point& value) { return layer.portToLayer(value); })) \
    .function("_portToLayerOffset", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Offset& value) { return layer.portToLayer(value); })) \
    .function("_portToLayerVector", emscripten::optional_override([](const pdg::SpriteLayer& layer, const pdg::Vector& value) { return layer.portToLayer(value); })) \
    .function("_portToLayerRect", &pdg::emscriptenPortToLayerRect) \
    .function("setZoom", &pdg::SpriteLayer::setZoom) \
    .function("getZoom", &pdg::SpriteLayer::getZoom) \
    .function("_zoomTo", emscripten::optional_override([](pdg::SpriteLayer& layer, float zoom, double seconds, int easing, const pdg::Rect& bounds, emscripten::val center) { pdg::browserPartCall([&] { \
        if (easing < 0 || easing >= NUM_EASING_FUNCTIONS || !pdg::gEasingFunctions[easing]) throw std::invalid_argument("Unknown easing"); \
        pdg::Point point; const pdg::Point* anchor = nullptr; \
        if (!center.isNull() && !center.isUndefined()) { point = pdg::Point(center["x"].as<float>(), center["y"].as<float>()); anchor = &point; } \
        layer.zoomTo(zoom, seconds, pdg::gEasingFunctions[easing], bounds, anchor); \
    }); }))
#else
#define BrowserLayerView_Extra
#endif

#define Animated_Extra .constructor<>() BrowserAnimationHelpers_Extra
#define ConfigManager_Extra \
    .function("useConfig", &pdg::emscriptenConfigUseConfig) \
    .function("getConfigString", &pdg::emscriptenConfigGetString) \
    .function("getConfigLong", &pdg::emscriptenConfigGetLong) \
    .function("getConfigFloat", &pdg::emscriptenConfigGetFloat) \
    .function("getConfigBool", &pdg::emscriptenConfigGetBool) \
    .function("setConfigString", &pdg::emscriptenConfigSetString) \
    .function("setConfigLong", &pdg::emscriptenConfigSetLong) \
    .function("setConfigFloat", &pdg::emscriptenConfigSetFloat) \
    .function("setConfigBool", &pdg::emscriptenConfigSetBool)
#define CpArbiter_Extra 
#define CpConstraint_Extra 
#define CpSpace_Extra 
#define Deserializer_Extra .constructor<>()
#define EventEmitter_Extra \
    .constructor<>() \
    .function("_addNativeEventBridge", &pdg::emscriptenEventEmitterAddBridge)
#define EventManager_Extra \
    .function("_addNativeEventBridge", &pdg::emscriptenEventManagerAddEventBridge)
#define FileManager_Extra 
#define Font_Extra \
    .function("getFontName", &pdg::emscriptenFontGetName) \
    .function("_getFontHeight", &pdg::emscriptenFontGetHeight) \
    .function("_getFontLeading", &pdg::emscriptenFontGetLeading) \
    .function("_getFontCapHeight", &pdg::emscriptenFontGetCapHeight) \
    .function("_getFontAscent", &pdg::emscriptenFontGetAscent) \
    .function("_getFontDescent", &pdg::emscriptenFontGetDescent)
#define GraphicsManager_Extra \
    .function("getNumScreens", &pdg::GraphicsManager::getNumScreens) \
    .function("getCurrentScreenMode", &pdg::emscriptenGraphicsGetCurrentScreenMode) \
    .function("getScreenBounds", &pdg::GraphicsManager::getScreenBounds) \
    .function("getNumSupportedScreenModes", &pdg::GraphicsManager::getNumSupportedScreenModes) \
    .function("getNthSupportedScreenMode", &pdg::emscriptenGraphicsGetNthSupportedScreenMode) \
    .function("setScreenMode", &pdg::GraphicsManager::setScreenMode) \
    .function("_createWindowPort", &pdg::emscriptenGraphicsCreateWindowPort, emscripten::allow_raw_pointers()) \
    .function("createOffscreenPort", &pdg::GraphicsManager::createOffscreenPort, emscripten::allow_raw_pointers()) \
    .function("closeGraphicsPort", &pdg::GraphicsManager::closeGraphicsPort, emscripten::allow_raw_pointers()) \
    .function("closeAllGraphicsPorts", &pdg::GraphicsManager::closeAllGraphicsPorts) \
    .function("_createFont", &pdg::emscriptenGraphicsCreateFont, emscripten::allow_raw_pointers()) \
    .function("getMainPort", &pdg::GraphicsManager::getMainPort, emscripten::allow_raw_pointers()) \
    .function("getFPS", &pdg::GraphicsManager::getFPS) \
    .function("setTargetFPS", &pdg::GraphicsManager::setTargetFPS) \
    .function("getTargetFPS", &pdg::GraphicsManager::getTargetFPS) \
    .function("getMouse", &pdg::GraphicsManager::getMouse)
#define Image_Extra 
#define ImageStrip_Extra 
#define IAnimationHelper_Extra 
#define IEventHandler_Extra .constructor<>()
#define ISerializable_Extra 
#define ISpriteDrawHelper_Extra 
#define LogManager_Extra 
#define MemBlock_Extra .constructor(&pdg::emscriptenCreateEmptyMemBlock, emscripten::allow_raw_pointers())
#define Port_Extra \
    .constructor(&pdg::emscriptenCreatePort, emscripten::allow_raw_pointers()) \
    .function("_getNativeIdentity", &pdg::emscriptenPortGetIdentity) \
    .function("getDrawingArea", &pdg::Port::getDrawingArea) \
    .function("getClipRect", &pdg::Port::getClipRect) \
    .function("resetClipRect", &pdg::Port::resetClipRect) \
    .function("_clear", &pdg::Port::clear) \
    .function("_setDrawingOrigin", &pdg::Port::setDrawingOrigin) \
    .function("setClipRect", &pdg::Port::setClipRect) \
    .function("_getTextWidth", &pdg::emscriptenPortGetTextWidth) \
    .function("getCurrentFont", &pdg::Port::getCurrentFont, emscripten::allow_raw_pointers()) \
    .function("setFont", &pdg::Port::setFont, emscripten::allow_raw_pointers()) \
    .function("setFontForStyle", &pdg::Port::setFontForStyle, emscripten::allow_raw_pointers()) \
    .function("setFontScalingFactor", &pdg::Port::setFontScalingFactor) \
    .function("startTrackingMouse", &pdg::emscriptenPortStartTrackingMouse) \
    .function("stopTrackingMouse", &pdg::Port::stopTrackingMouse) \
    .function("resetCursor", &pdg::Port::resetCursor) \
    .function("drawLine", &pdg::Port::drawLine) \
    .function("drawRect", &pdg::Port::drawRect) \
    .function("drawQuad", &pdg::emscriptenPortDrawQuad) \
    .function("drawPolygon", &pdg::Port::drawPolygon) \
    .function("drawSpline", &pdg::Port::drawSpline) \
    .function("drawCircle", &pdg::emscriptenPortDrawCircle) \
    .function("drawEllipse", &pdg::Port::drawEllipse) \
    .function("drawArc", &pdg::Port::drawArc) \
    .function("drawImage", &pdg::emscriptenPortDrawImage, emscripten::allow_raw_pointers()) \
    .function("drawDrawing", &pdg::emscriptenPortDrawDrawing) \
    .function("drawText", &pdg::emscriptenPortDrawText) \
    .function("drawSphere", &pdg::Port::drawSphere)
#ifndef PDG_NO_SOUND
#define ResourceManager_Extra \
    .function("_getSound", &pdg::emscriptenResourceGetSound, emscripten::allow_raw_pointers())
#else
#define ResourceManager_Extra
#endif
#define Serializer_Extra .constructor<>()
#define Sound_Extra \
    .constructor(&pdg::emscriptenCreateSound, emscripten::allow_raw_pointers()) \
    .function("_play", &pdg::emscriptenSoundPlay) \
    .function("start", &pdg::Sound::start) \
    .function("stop", &pdg::Sound::stop) \
    .function("pause", &pdg::Sound::pause) \
    .function("resume", &pdg::Sound::resume) \
    .function("isPaused", &pdg::Sound::isPaused) \
    .function("setLooping", &pdg::Sound::setLooping, emscripten::return_value_policy::reference()) \
    .function("isLooping", &pdg::Sound::isLooping) \
    .function("setVolume", &pdg::Sound::setVolume, emscripten::return_value_policy::reference()) \
    .function("getVolume", &pdg::Sound::getVolume) \
    .function("setPitch", &pdg::Sound::setPitch, emscripten::return_value_policy::reference()) \
    .function("changePitch", &pdg::emscriptenSoundChangePitch) \
    .function("setOffsetX", &pdg::Sound::setOffsetX, emscripten::return_value_policy::reference()) \
    .function("changeOffsetX", &pdg::emscriptenSoundChangeOffset) \
    .function("fadeOut", &pdg::emscriptenSoundFadeOut) \
    .function("fadeIn", &pdg::emscriptenSoundFadeIn) \
    .function("changeVolume", &pdg::emscriptenSoundChangeVolume) \
    .function("skip", &pdg::Sound::skip, emscripten::return_value_policy::reference()) \
    .function("skipTo", &pdg::Sound::skipTo, emscripten::return_value_policy::reference())
#define SoundManager_Extra \
    .function("setVolume", &pdg::SoundManager::setVolume) \
    .function("setMute", &pdg::SoundManager::setMute) \
    .function("stopAllSounds", &pdg::SoundManager::stopAllSounds)
#define SpriteIdentity_Extra SpriteParts_Extra \
    .function("_getNativeIdentity", emscripten::optional_override([](const pdg::Sprite& sprite){return reinterpret_cast<uintptr_t>(&sprite);}))
#define LayerIdentity_Extra \
    .function("_getNativeIdentity", emscripten::optional_override([](const pdg::SpriteLayer& layer){return reinterpret_cast<uintptr_t>(&layer);}))
#ifdef PDG_SPRITER_SUPPORT
#define Sprite_Extra SpriteIdentity_Extra \
    .function("_addNativeEventBridge", &pdg::emscriptenSpriteAddEventBridge) \
    .function("isSpriterSprite", &pdg::Sprite::isSpriterSprite) \
    .function("hasAnimation", &pdg::emscriptenSpriteHasAnimation) \
    .function("seekAnimation", &pdg::emscriptenSpriteSeekAnimation) \
    .function("transitionToAnimation", &pdg::emscriptenSpriteTransitionToAnimation) \
    .function("isAnimationTransitioning", &pdg::Sprite::isAnimationTransitioning) \
    .function("getAnimationTransitionProgress", &pdg::Sprite::getAnimationTransitionProgress) \
    .function("supportsAnimationPhysics", emscripten::optional_override([](const pdg::Sprite&){return pdg::Sprite::supportsAnimationPhysics();})) \
    .function("isAnimationPhysicsEnabled", &pdg::Sprite::isAnimationPhysicsEnabled) \
    .function("setupAnimationPhysics", &pdg::emscriptenSpriteSetupAnimationPhysics) \
    .function("setupPhysicsFromAnimationRig", &pdg::emscriptenSpriteSetupPhysicsFromAnimationRig) \
    .function("attachAnimationPhysicsPart", &pdg::emscriptenSpriteAttachAnimationPhysicsPart, emscripten::allow_raw_pointers()) \
    .function("detachAnimationPhysicsPart", &pdg::emscriptenSpriteDetachAnimationPhysicsPart, emscripten::allow_raw_pointers()) \
    .function("isAnimationPhysicsPartAttached", &pdg::Sprite::isAnimationPhysicsPartAttached, emscripten::allow_raw_pointers()) \
    .function("setAnimationPhysicsRoot", &pdg::emscriptenSpriteSetAnimationPhysicsRoot) \
    .function("getAnimationPhysicsRoot", &pdg::emscriptenSpriteGetAnimationPhysicsRoot) \
    .function("clearAnimationPhysicsRoot", &pdg::emscriptenSpriteClearAnimationPhysicsRoot) \
    .function("getAnimationPhysicsSetupWarnings", &pdg::emscriptenSpriteGetAnimationPhysicsSetupWarnings) \
    .function("setAnimationPhysicsMode", &pdg::emscriptenSpriteSetAnimationPhysicsMode) \
    .function("getAnimationPhysicsMode", &pdg::emscriptenSpriteGetAnimationPhysicsMode) \
    .function("setAnimationPhysicsDriveSettings", &pdg::emscriptenSpriteSetAnimationPhysicsDriveSettings) \
    .function("getAnimationPhysicsDriveSettings", &pdg::emscriptenSpriteGetAnimationPhysicsDriveSettings) \
    .function("disableAnimationPhysics", &pdg::emscriptenSpriteDisableAnimationPhysics) \
    .function("addAnimationDrawable", &pdg::emscriptenSpriteAddAnimationDrawable) \
    .function("removeAnimationDrawable", &pdg::Sprite::removeAnimationDrawable) \
    .function("clearAnimationDrawables", &pdg::Sprite::clearAnimationDrawables) \
    .function("setAnimationDrawableEnabled", &pdg::emscriptenSpriteSetAnimationDrawableEnabled) \
    .function("getAnimationDrawableError", &pdg::emscriptenSpriteGetAnimationDrawableError) \
    .function("getAnimationDrawBounds", &pdg::emscriptenSpriteGetAnimationDrawBounds) \
    .function("addAnimationIK", &pdg::emscriptenSpriteAddAnimationIK) \
    .function("setAnimationIKTarget", &pdg::emscriptenSpriteSetAnimationIKTarget) \
    .function("getAnimationIKResult", &pdg::emscriptenSpriteGetAnimationIKResult) \
    .function("addAnimationModifier", &pdg::emscriptenSpriteAddAnimationModifier) \
    .function("removeAnimationModifier", &pdg::Sprite::removeAnimationModifier) \
    .function("clearAnimationModifiers", &pdg::Sprite::clearAnimationModifiers) \
    .function("getAnimationModifierError", &pdg::emscriptenSpriteGetAnimationModifierError) \
    .function("setAnimationSource", &pdg::emscriptenSpriteSetAnimationSource) \
    .function("getAnimationSource", &pdg::Sprite::getAnimationSource) \
    .function("isAnimationDrawingSupported", &pdg::Sprite::isAnimationDrawingSupported) \
    .function("_setAnimationDebugDraw", &pdg::emscriptenSpriteSetAnimationDebugDraw) \
    .function("getAnimationDebugDraw", &pdg::Sprite::getAnimationDebugDraw) \
    .function("enableAnimationPose", &pdg::emscriptenSpriteEnableAnimationPose) \
    .function("disableAnimationPose", &pdg::Sprite::disableAnimationPose) \
    .function("isAnimationPoseEnabled", &pdg::Sprite::isAnimationPoseEnabled) \
    .function("getAnimationRigError", &pdg::Sprite::getAnimationRigError) \
    .function("getAnimationPose", &pdg::emscriptenSpriteGetAnimationPose) \
    .function("sampleAnimationPose", &pdg::emscriptenSpriteSampleAnimationPose) \
    .function("getAnimationBoneNames", &pdg::emscriptenSpriteGetAnimationBoneNames) \
    .function("getAnimationBindingNames", &pdg::emscriptenSpriteGetAnimationBindingNames) \
    .function("_getAnimationBoneTransform", &pdg::emscriptenSpriteGetAnimationBoneTransform) \
    .function("_getAnimationBindingTransform", &pdg::emscriptenSpriteGetAnimationBindingTransform) \
    .function("setAnimationBoneTransform", &pdg::emscriptenSpriteSetAnimationBoneTransform) \
    .function("clearAnimationBoneTransforms", &pdg::Sprite::clearAnimationBoneTransforms) \
    .function("startAnimation", &pdg::emscriptenSpriteStartAnimation) \
    .function("applyCharacterMap", &pdg::emscriptenSpriteApplyCharacterMap) \
    .function("removeCharacterMap", &pdg::emscriptenSpriteRemoveCharacterMap) \
    .function("removeAllCharacterMaps", &pdg::Sprite::removeAllCharacterMaps) \
    .function("getAppliedCharacterMaps", &pdg::emscriptenSpriteGetAppliedCharacterMaps) \
    .function("enableSpriterEvents", &pdg::Sprite::enableSpriterEvents) \
    .function("areSpriterEventsEnabled", &pdg::Sprite::areSpriterEventsEnabled) \
    .function("blendToAnimation", &pdg::emscriptenSpriteBlendToAnimation) \
    .function("isBlending", &pdg::Sprite::isBlending) \
    .function("getBlendProgress", &pdg::Sprite::getBlendProgress) \
    .function("pauseAnimation", &pdg::Sprite::pauseAnimation) \
    .function("resumeAnimation", &pdg::Sprite::resumeAnimation) \
    .function("stopAnimation", &pdg::Sprite::stopAnimation) \
    .function("isAnimationPlaying", &pdg::Sprite::isAnimationPlaying) \
    .function("isAnimationPaused", &pdg::Sprite::isAnimationPaused) \
    .function("getAnimationProgress", &pdg::Sprite::getAnimationProgress) \
    .function("hasAttachPoint", &pdg::emscriptenSpriteHasAttachPoint) \
    .function("getAttachPoint", &pdg::emscriptenSpriteGetAttachPoint) \
    .function("attachSprite", &pdg::emscriptenSpriteAttachSprite, emscripten::allow_raw_pointers()) \
    .function("detachSprite", &pdg::Sprite::detachSprite, emscripten::allow_raw_pointers()) \
    .function("getAttachedSprite", emscripten::optional_override([](const pdg::Sprite& sprite, const std::string& name) { return pdg::browserRetain(pdg::emscriptenSpriteGetAttachedSprite(sprite,name)); })) \
    .function("activateSubEntity", &pdg::emscriptenSpriteActivateSubEntity) \
    .function("getSpriterCollisionBox", &pdg::emscriptenSpriteGetCollisionBox) \
    .function("isSpriterCollisionActive", &pdg::emscriptenSpriteIsCollisionActive) \
    .function("getSpriterCollisionBoxCount", &pdg::Sprite::getSpriterCollisionBoxCount) \
    .function("getSpriterCollisionBoxName", &pdg::emscriptenSpriteGetCollisionBoxName)
#ifdef PDG_USE_CHIPMUNK_PHYSICS
#define AnimationLayerPhysics_Extra \
    .function("_setGravity", &pdg::SpriteLayer::setGravity) \
    .function("setDamping", &pdg::SpriteLayer::setDamping) \
    .function("setKeepGravityDownward", &pdg::SpriteLayer::setKeepGravityDownward)
#else
#define AnimationLayerPhysics_Extra
#endif
#define SpriteLayer_Extra BrowserLayerView_Extra LayerIdentity_Extra ParticleLayer_Extra AnimationLayerPhysics_Extra \
    .function("_addNativeEventBridge", &pdg::emscriptenSpriteLayerAddEventBridge) \
    .function("_createSpriteFromSpriterFile", emscripten::optional_override([](pdg::SpriteLayer& layer, const std::string& path, const std::string& entity) { return pdg::browserRetain(pdg::emscriptenLayerCreateSpriteFromFile(layer,path,entity)); })) \
    .function("createSpriteFromSpriterEntity", emscripten::optional_override([](pdg::SpriteLayer& layer, const std::string& entity) { return pdg::browserRetain(pdg::emscriptenLayerCreateSpriteFromEntity(layer,entity)); })) \
    .function("applyCharacterMapToAll", &pdg::emscriptenLayerApplyCharacterMap) \
    .function("removeCharacterMapFromAll", &pdg::emscriptenLayerRemoveCharacterMap) \
    .function("enableSpriterEvents", &pdg::SpriteLayer::enableSpriterEvents)
#else
#define Sprite_Extra SpriteIdentity_Extra .function("_addNativeEventBridge", &pdg::emscriptenSpriteAddEventBridge)
#define SpriteLayer_Extra BrowserLayerView_Extra LayerIdentity_Extra ParticleLayer_Extra .function("_addNativeEventBridge", &pdg::emscriptenSpriteLayerAddEventBridge)
#endif
#define TileLayer_Extra 
#define TimerManager_Extra 



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
