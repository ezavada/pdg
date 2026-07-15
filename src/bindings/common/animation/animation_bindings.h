// -----------------------------------------------
// animation_bindings.h
//
// Header file that contains animation-related interface declarations
// for pdg classes that are exposed to scripting languages
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

// Include the interface declarations for animation classes

#ifdef PDG_GENERATING_DOCS
#include "../../tools/js_docs_macros.h"
namespace pdg {
#else

#undef THIS // eliminate warning about Windows duplicate Macro
#include "pdg_script_macros.h"
#include "animation_macros.h"
#include "../core/core_macros.h"
#include "../data/data_macros.h"

%#ifndef PDG_ANIMATION_BINDINGS_H_INCLUDED
%#define PDG_ANIMATION_BINDINGS_H_INCLUDED

%#include "pdg_project.h"

%#include "pdg_script_impl.h"
%#include "pdg_script_interface.h"

%#ifndef PDG_NO_APP_FRAMEWORK
%#define PDG_NO_APP_FRAMEWORK
%#endif
%#include "pdg/framework.h"

%#include <cstdlib>

namespace pdg {

#endif //!PDG_GENERATING_DOCS

BINDING_CLASS(IAnimationHelper)
DECL_END



BINDING_CLASS(Animated)
  ANIMATED_METHODS(Animated)
	METHOD(Animated, Animate)
// 	METHOD(Animated, OnLocationChanged)
// 	METHOD(Animated, OnSizeChanged)
// 	METHOD(Animated, OnRotationChanged)
// 	METHOD(Animated, OnCenterChanged)
DECL_END

BINDING_CLASS(ISpriteCollideHelper)
DECL_END

%#ifndef PDG_NO_GUI
BINDING_CLASS(ISpriteDrawHelper)
DECL_END
%#endif //!PDG_NO_GUI

BINDING_CLASS(Sprite)
  EMITTER_METHODS(Sprite)
  ANIMATED_METHODS(Sprite)
  SERIALIZABLE_METHODS(Sprite)
	PROPERTY(Sprite, WantsAnimLoopEvents)
	PROPERTY(Sprite, WantsAnimEndEvents)
	PROPERTY(Sprite, Opacity)
	PROPERTY(Sprite, CollisionRadius)
	PROPERTY(Sprite, Elasticity)
	PROPERTY(Sprite, WantsCollideWallEvents)
	METHOD(Sprite, GetFrameRotatedBounds)
	METHOD(Sprite, SetFrame)
	METHOD(Sprite, GetCurrentFrame)
    METHOD(Sprite, GetFrameCount)
	METHOD(Sprite, StartFrameAnimation)
	METHOD(Sprite, StopFrameAnimation)
	METHOD(Sprite, AddFramesImage)
%#ifdef PDG_SPRITER_SUPPORT
	METHOD(Sprite, HasAnimation)
	METHOD(Sprite, StartAnimation)
	METHOD(Sprite, SetEntityScale)
	METHOD(Sprite, ApplyCharacterMap)
	METHOD(Sprite, RemoveCharacterMap)
	METHOD(Sprite, RemoveAllCharacterMaps)
	METHOD(Sprite, GetAppliedCharacterMaps)
	METHOD(Sprite, EnableSpriterEvents)
	METHOD(Sprite, AreSpriterEventsEnabled)
	METHOD(Sprite, BlendToAnimation)
	METHOD(Sprite, IsBlending)
	METHOD(Sprite, GetBlendProgress)
	METHOD(Sprite, PauseAnimation)
	METHOD(Sprite, ResumeAnimation)
	METHOD(Sprite, StopAnimation)
	METHOD(Sprite, IsAnimationPlaying)
	METHOD(Sprite, IsAnimationPaused)
	METHOD(Sprite, GetAnimationProgress)
  	METHOD(Sprite, GetAnimationName)
  	METHOD(Sprite, HasAttachPoint)
	METHOD(Sprite, GetAttachPoint)
	METHOD(Sprite, AttachSprite)
	METHOD(Sprite, ActivateSubEntity)
	METHOD(Sprite, DetachSprite)
	METHOD(Sprite, GetAttachedSprite)
	METHOD(Sprite, GetSpriterCollisionBox)
	METHOD(Sprite, IsSpriterCollisionActive)
	METHOD(Sprite, GetSpriterCollisionBoxCount)
	METHOD(Sprite, GetSpriterCollisionBoxName)
%#endif // PDG_SPRITER_SUPPORT
%#ifndef PDG_NO_GUI
	PROPERTY(Sprite, WantsMouseOverEvents)
	PROPERTY(Sprite, WantsClickEvents)
	PROPERTY(Sprite, MouseDetectMode)
	PROPERTY(Sprite, WantsOffscreenEvents)
	METHOD(Sprite, SetDrawHelper)
	METHOD(Sprite, SetPostDrawHelper)
%#endif //!PDG_NO_GUI
	METHOD(Sprite, ChangeFramesImage)
	METHOD(Sprite, OffsetFrameCenters)
	METHOD(Sprite, GetFrameCenterOffset)
	METHOD(Sprite, FadeTo)
	METHOD(Sprite, FadeIn)
	METHOD(Sprite, FadeOut)
	METHOD(Sprite, IsBehind)
	METHOD(Sprite, GetZOrder)
	METHOD(Sprite, MoveBehind)
	METHOD(Sprite, MoveInFrontOf)
	METHOD(Sprite, MoveToFront)
	METHOD(Sprite, MoveToBack)
	METHOD(Sprite, EnableCollisions)
	METHOD(Sprite, DisableCollisions)
	METHOD(Sprite, GetCollisionType)
	METHOD(Sprite, UseCollisionMask)
	METHOD(Sprite, SetCollisionHelper);
	METHOD(Sprite, SetUserData)
	METHOD(Sprite, FreeUserData)
	METHOD(Sprite, GetLayer)
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
	PROPERTY(Sprite, CollideGroup)
	METHOD(Sprite, MakeStatic)
	METHOD(Sprite, GetFriction)
	METHOD(Sprite, PinJoint)
	METHOD(Sprite, SlideJoint)
	METHOD(Sprite, PivotJoint)
	METHOD(Sprite, GrooveJoint)
	METHOD(Sprite, SpringJoint)
	METHOD(Sprite, RotarySpring)
	METHOD(Sprite, RotaryLimit)
	METHOD(Sprite, Ratchet)
	METHOD(Sprite, Gear)
	METHOD(Sprite, Motor)
	METHOD(Sprite, RemoveJoint)
	METHOD(Sprite, Disconnect)
	METHOD(Sprite, MakeJointBreakable)
	METHOD(Sprite, MakeJointUnbreakable)
%#endif
  METHOD(Sprite, On)
  METHOD(Sprite, OnCollideSprite)
  METHOD(Sprite, OnCollideWall)
  METHOD(Sprite, OnOffscreen)
  METHOD(Sprite, OnOnscreen)
  METHOD(Sprite, OnExitLayer)
  METHOD(Sprite, OnAnimationLoop)
  METHOD(Sprite, OnAnimationEnd)
  METHOD(Sprite, OnAnimationBlendComplete)
  METHOD(Sprite, OnFadeComplete)
  METHOD(Sprite, OnFadeInComplete)
  METHOD(Sprite, OnFadeOutComplete)
  METHOD(Sprite, OnMouseEnter)
  METHOD(Sprite, OnMouseLeave)
  METHOD(Sprite, OnMouseDown)
  METHOD(Sprite, OnMouseUp)
  METHOD(Sprite, OnMouseClick)
DECL_END


BINDING_CLASS(SpriteLayer)
  EMITTER_METHODS(SpriteLayer)
  ANIMATED_METHODS(SpriteLayer)
  SERIALIZABLE_METHODS(SpriteLayer)
  SPRITE_LAYER_METHODS(SpriteLayer)
%#ifndef PDG_NO_GUI
  SPRITE_LAYER_GUI_METHODS(SpriteLayer)
%#endif
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
  SPRITE_LAYER_CHIPMUNK_METHODS(SpriteLayer)
%#endif
%#ifdef PDG_SPRITER_SUPPORT
	METHOD(SpriteLayer, CreateSpriteFromSpriter)
	METHOD(SpriteLayer, CreateSpriteFromSpriterFile)
	METHOD(SpriteLayer, CreateSpriteFromSpriterEntity)
	METHOD(SpriteLayer, ApplyCharacterMapToAll)
	METHOD(SpriteLayer, RemoveCharacterMapFromAll)
	METHOD(SpriteLayer, EnableSpriterEvents)
%#endif // PDG_SPRITER_SUPPORT
  METHOD(SpriteLayer, On)
  METHOD(SpriteLayer, OnCollideSprite)
  METHOD(SpriteLayer, OnCollideWall)
  METHOD(SpriteLayer, OnOffscreen)
  METHOD(SpriteLayer, OnOnscreen)
  METHOD(SpriteLayer, OnExitLayer)
  METHOD(SpriteLayer, OnAnimationLoop)
  METHOD(SpriteLayer, OnAnimationEnd)
  METHOD(SpriteLayer, OnFadeComplete)
  METHOD(SpriteLayer, OnFadeInComplete)
  METHOD(SpriteLayer, OnFadeOutComplete)
  METHOD(SpriteLayer, OnMouseEnter)
  METHOD(SpriteLayer, OnMouseLeave)
  METHOD(SpriteLayer, OnMouseDown)
  METHOD(SpriteLayer, OnMouseUp)
  METHOD(SpriteLayer, OnMouseClick)
  METHOD(SpriteLayer, OnErasePort)
  METHOD(SpriteLayer, OnPreDrawLayer)
  METHOD(SpriteLayer, OnPostDrawLayer)
  METHOD(SpriteLayer, OnDrawPortComplete)
  METHOD(SpriteLayer, OnAnimationStart)
  METHOD(SpriteLayer, OnPreAnimateLayer)
  METHOD(SpriteLayer, OnPostAnimateLayer)
  METHOD(SpriteLayer, OnAnimationComplete)
  METHOD(SpriteLayer, OnZoomComplete)
  METHOD(SpriteLayer, OnLayerFadeInComplete)
  METHOD(SpriteLayer, OnLayerFadeOutComplete)
DECL_END

BINDING_CLASS(TileLayer)
  EMITTER_METHODS(TileLayer)
  ANIMATED_METHODS(TileLayer)
  SERIALIZABLE_METHODS(TileLayer)
  SPRITE_LAYER_METHODS(TileLayer)
%#ifndef PDG_NO_GUI
  SPRITE_LAYER_GUI_METHODS(TileLayer)
%#endif
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
  SPRITE_LAYER_CHIPMUNK_METHODS(TileLayer)
%#endif
	PROPERTY(TileLayer, WorldSize)
	METHOD(TileLayer, GetWorldBounds)
	METHOD(TileLayer, DefineTileSet)
	METHOD(TileLayer, LoadMapData)
	METHOD(TileLayer, GetMapData)
	METHOD(TileLayer, GetTileSetImage)
	METHOD(TileLayer, GetTileSize)
	METHOD(TileLayer, GetTileTypeAt)
	METHOD(TileLayer, GetTileTypeAndFacingAt)
	METHOD(TileLayer, SetTileTypeAt)
  METHOD(TileLayer, CheckCollision)
  METHOD(TileLayer, On)
  METHOD(TileLayer, OnCollideSprite)
  METHOD(TileLayer, OnCollideWall)
  METHOD(TileLayer, OnOffscreen)
  METHOD(TileLayer, OnOnscreen)
  METHOD(TileLayer, OnExitLayer)
  METHOD(TileLayer, OnAnimationLoop)
  METHOD(TileLayer, OnAnimationEnd)
  METHOD(TileLayer, OnFadeComplete)
  METHOD(TileLayer, OnFadeInComplete)
  METHOD(TileLayer, OnFadeOutComplete)
  METHOD(TileLayer, OnMouseEnter)
  METHOD(TileLayer, OnMouseLeave)
  METHOD(TileLayer, OnMouseDown)
  METHOD(TileLayer, OnMouseUp)
  METHOD(TileLayer, OnMouseClick)
  METHOD(TileLayer, OnErasePort)
  METHOD(TileLayer, OnPreDrawLayer)
  METHOD(TileLayer, OnPostDrawLayer)
  METHOD(TileLayer, OnDrawPortComplete)
  METHOD(TileLayer, OnAnimationStart)
  METHOD(TileLayer, OnPreAnimateLayer)
  METHOD(TileLayer, OnPostAnimateLayer)
  METHOD(TileLayer, OnAnimationComplete)
  METHOD(TileLayer, OnZoomComplete)
  METHOD(TileLayer, OnLayerFadeInComplete)
  METHOD(TileLayer, OnLayerFadeOutComplete)
DECL_END



%#endif // PDG_ANIMATION_BINDINGS_H_INCLUDED 

} // namespace pdg
