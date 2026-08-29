#include "pdg/framework.h"
#include "pdg_em_adaptors.h"

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

#define Animated_Extra .constructor<>()
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
#define EventEmitter_Extra .constructor<>()
#define EventManager_Extra 
#define FileManager_Extra 
#define Font_Extra 
#define GraphicsManager_Extra 
#define Image_Extra 
#define ImageStrip_Extra 
#define IAnimationHelper_Extra 
#define IEventHandler_Extra .constructor<>()
#define ISerializable_Extra 
#define ISpriteCollideHelper_Extra 
#define ISpriteDrawHelper_Extra 
#define LogManager_Extra 
#define MemBlock_Extra .constructor(&pdg::emscriptenCreateEmptyMemBlock, emscripten::allow_raw_pointers())
#define Port_Extra 
#define ResourceManager_Extra 
#define Serializer_Extra .constructor<>()
#define Sound_Extra 
#define SoundManager_Extra
#define Sprite_Extra 
#define SpriteLayer_Extra 
#define TileLayer_Extra 
#define TimerManager_Extra 



#include "pdg.embind"
