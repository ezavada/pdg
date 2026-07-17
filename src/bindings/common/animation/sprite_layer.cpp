// -----------------------------------------------
// sprite_layer.cpp
//
// Implementation file for SpriteLayer bindings
//
// Written by Ed Zavada, 2013
// Copyright (c) 2013, Dream Rock Studios, LLC
// All Rights Reserved Worldwide
// -----------------------------------------------

#include "pdg_script_macros.h"
#include "../core/core_impl_macros.h"
#include "../data/data_impl_macros.h"
#include "animation_impl_macros.h"

%#include "pdg_project.h"

%#define PDG_COMPILING_SCRIPT_IMPL

%#include "pdg_script_interface.h"
%#include "pdg_script_impl.h"

%#include "internals.h"
%#include "pdg-lib.h"

%#include <cstdlib>


namespace pdg {
    

// ========================================================================================
//MARK: SpriteLayer
// ========================================================================================


WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY(SpriteLayer, "createSpriteLayer", 
    OBJECT_SAVE(cppObj->mEventEmitterScriptObj, obj); 
    OBJECT_SAVE(cppObj->mAnimatedScriptObj, obj);
    OBJECT_SAVE(cppObj->mSpriteLayerScriptObj, obj) )
      EXPORT_CLASS_SYMBOLS("SpriteLayer", SpriteLayer, , ,
          // method section
          HAS_EMITTER_METHODS(SpriteLayer)
          HAS_ANIMATED_METHODS(SpriteLayer)
          HAS_SERIALIZABLE_METHODS(SpriteLayer)
          HAS_SPRITE_LAYER_METHODS(SpriteLayer)
        %#ifndef PDG_NO_GUI  CR
          HAS_SPRITE_LAYER_GUI_METHODS(SpriteLayer)
        %#endif CR
        %#ifdef PDG_USE_CHIPMUNK_PHYSICS  CR
          HAS_SPRITE_LAYER_CHIPMUNK_METHODS(SpriteLayer)
        %#endif  CR
      //	HAS_METHOD(SpriteLayer, "cloneSprite", CloneSprite);
        %#ifdef PDG_SPRITER_SUPPORT CR
            HAS_METHOD(SpriteLayer, "createSpriteFromSpriterFile", CreateSpriteFromSpriterFile)
            HAS_METHOD(SpriteLayer, "createSpriteFromSpriterEntity", CreateSpriteFromSpriterEntity)
            HAS_METHOD(SpriteLayer, "applyCharacterMapToAll", ApplyCharacterMapToAll)
            HAS_METHOD(SpriteLayer, "removeCharacterMapFromAll", RemoveCharacterMapFromAll)
            HAS_METHOD(SpriteLayer, "enableSpriterEvents", EnableSpriterEvents)
        %#endif CR
          HAS_METHOD(SpriteLayer, "on", On)
          HAS_METHOD(SpriteLayer, "onCollideSprite", OnCollideSprite)
          HAS_METHOD(SpriteLayer, "onCollideWall", OnCollideWall)
          HAS_METHOD(SpriteLayer, "onOffscreen", OnOffscreen)
          HAS_METHOD(SpriteLayer, "onOnscreen", OnOnscreen)
          HAS_METHOD(SpriteLayer, "onExitLayer", OnExitLayer)
          HAS_METHOD(SpriteLayer, "onAnimationLoop", OnAnimationLoop)
          HAS_METHOD(SpriteLayer, "onAnimationEnd", OnAnimationEnd)
          HAS_METHOD(SpriteLayer, "onFadeComplete", OnFadeComplete)
          HAS_METHOD(SpriteLayer, "onFadeInComplete", OnFadeInComplete)
          HAS_METHOD(SpriteLayer, "onFadeOutComplete", OnFadeOutComplete)
          HAS_METHOD(SpriteLayer, "onMouseEnter", OnMouseEnter)
          HAS_METHOD(SpriteLayer, "onMouseLeave", OnMouseLeave)
          HAS_METHOD(SpriteLayer, "onMouseDown", OnMouseDown)
          HAS_METHOD(SpriteLayer, "onMouseUp", OnMouseUp)
          HAS_METHOD(SpriteLayer, "onMouseClick", OnMouseClick)
          HAS_METHOD(SpriteLayer, "onErasePort", OnErasePort)
          HAS_METHOD(SpriteLayer, "onPreDrawLayer", OnPreDrawLayer)
          HAS_METHOD(SpriteLayer, "onPostDrawLayer", OnPostDrawLayer)
          HAS_METHOD(SpriteLayer, "onDrawPortComplete", OnDrawPortComplete)
          HAS_METHOD(SpriteLayer, "onAnimationStart", OnAnimationStart)
          HAS_METHOD(SpriteLayer, "onPreAnimateLayer", OnPreAnimateLayer)
          HAS_METHOD(SpriteLayer, "onPostAnimateLayer", OnPostAnimateLayer)
          HAS_METHOD(SpriteLayer, "onAnimationComplete", OnAnimationComplete)
          HAS_METHOD(SpriteLayer, "onZoomComplete", OnZoomComplete)
          HAS_METHOD(SpriteLayer, "onLayerFadeInComplete", OnLayerFadeInComplete)
          HAS_METHOD(SpriteLayer, "onLayerFadeOutComplete", OnLayerFadeOutComplete)
      );
      END
      
  EMITTER_BASE_CLASS_IMPL(SpriteLayer)
  ANIMATED_BASE_CLASS_IMPL(SpriteLayer)
  SERIALIZABLE_BASE_CLASS_IMPL(SpriteLayer)
  %#ifndef PDG_NO_GUI
  SPRITE_LAYER_BASE_CLASS_GUI_IMPL(SpriteLayer)
  %#endif
  SPRITE_LAYER_BASE_CLASS_IMPL(SpriteLayer)
  %#ifdef PDG_USE_CHIPMUNK_PHYSICS
  SPRITE_LAYER_CHIPMUNK_IMPL(SpriteLayer)
  %#endif
  
  // METHOD_IMPL(SpriteLayer, CloneSprite)
  //    REQUIRE_ARG_COUNT(1);
  //    REQUIRE_CPP_OBJECT_ARG(1, originalSprite, Sprite);
  // 	  Sprite* newSprite = self->cloneSprite(originalSprite);
  //    RETURN_CPP_OBJECT(newSprite, Sprite);
  // 	END
  %#ifdef PDG_SPRITER_SUPPORT
  METHOD_IMPL(SpriteLayer, CreateSpriteFromSpriterFile)
      METHOD_SIGNATURE("", [object Sprite], 1, (string inFileName, string inEntityName = null)); 
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_STRING_ARG(1, inFileName);
      const char* inEntityName = 0;
      if (ARGC >= 2 && VALUE_IS_STRING(ARGV[1])) {
          REQUIRE_STRING_ARG(2, entityName);
          inEntityName = entityName;
      }
      Sprite* sprite = self->createSpriteFromSpriterFile(inFileName, inEntityName);
      RETURN_NEW_CPP_OBJECT(sprite, Sprite);
      END
  METHOD_IMPL(SpriteLayer, CreateSpriteFromSpriterEntity)
      METHOD_SIGNATURE("", [object Sprite], 1, (string inEntityName)); 
      REQUIRE_ARG_COUNT(1);
      REQUIRE_STRING_ARG(1, inEntityName);
      Sprite* sprite = self->createSpriteFromSpriterEntity(inEntityName);
      RETURN_NEW_CPP_OBJECT(sprite, Sprite);
      END
  METHOD_IMPL(SpriteLayer, ApplyCharacterMapToAll)
      METHOD_SIGNATURE("", undefined, 1, (string mapName));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_STRING_ARG(1, mapName);
      self->applyCharacterMapToAll(mapName);
      NO_RETURN;
      END
  METHOD_IMPL(SpriteLayer, RemoveCharacterMapFromAll)
      METHOD_SIGNATURE("", undefined, 1, (string mapName));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_STRING_ARG(1, mapName);
      self->removeCharacterMapFromAll(mapName);
      NO_RETURN;
      END
  METHOD_IMPL(SpriteLayer, EnableSpriterEvents)
      METHOD_SIGNATURE("", undefined, 1, (boolean enable = true));
      OPTIONAL_BOOL_ARG(1, enable, true);
      self->enableSpriterEvents(enable);
      NO_RETURN;
      END

  %#endif
  METHOD_IMPL(SpriteLayer, On)
      METHOD_SIGNATURE("", [object IEventHandler], 2, ([number int] eventCode, function func));
      REQUIRE_ARG_COUNT(2);
      REQUIRE_INT32_ARG(1, eventCode);
      REQUIRE_FUNCTION_ARG(2, func);
      ScriptEventHandler* handler = new ScriptEventHandler(func);
      if (!handler) RETURN_NULL;
      long evtCode;
      if (eventCode <= pdg::Sprite::action_CollideWall) {
          evtCode = pdg::eventType_SpriteCollide;
      } else if (eventCode <= pdg::SpriteLayer::action_FadeOutComplete) {
          evtCode = pdg::eventType_SpriteAnimate;
      } else if (eventCode >= pdg::SpriteLayer::action_ErasePort) {
          evtCode = pdg::eventType_SpriteLayer;
      } else {
          evtCode = pdg::eventType_SpriteTouch;
      }
      self->addHandler(handler, evtCode);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  // SpriteLayer convenience event methods
  METHOD_IMPL(SpriteLayer, OnCollideSprite)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptEventHandler* handler = new ScriptEventHandler(func);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteCollide);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnCollideWall)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptEventHandler* handler = new ScriptEventHandler(func);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteCollide);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnOffscreen)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Offscreen);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnOnscreen)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_Onscreen);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnExitLayer)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_ExitLayer);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnAnimationLoop)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationLoop);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnAnimationEnd)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
    METHOD_IMPL(SpriteLayer, OnFadeComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END

  METHOD_IMPL(SpriteLayer, OnFadeInComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END

  METHOD_IMPL(SpriteLayer, OnFadeOutComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteAnimate);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnMouseEnter)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteTouch);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnMouseLeave)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteTouch);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnMouseDown)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteTouch);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnMouseUp)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteTouch);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnMouseClick)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteTouch);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnErasePort)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ErasePort);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnPreDrawLayer)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreDrawLayer);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnPostDrawLayer)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostDrawLayer);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnDrawPortComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_DrawPortComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnAnimationStart)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationStart);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnPreAnimateLayer)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreAnimateLayer);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnPostAnimateLayer)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostAnimateLayer);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnAnimationComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnZoomComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ZoomComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnLayerFadeInComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeInComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  METHOD_IMPL(SpriteLayer, OnLayerFadeOutComplete)
      METHOD_SIGNATURE("", [object IEventHandler], 1, (function func));
      REQUIRE_ARG_COUNT(1);
      REQUIRE_FUNCTION_ARG(1, func);
      ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeOutComplete);
      if (!handler) RETURN_NULL;
      self->addHandler(handler, pdg::eventType_SpriteLayer);
      RETURN_CPP_OBJECT(handler, IEventHandler);
      END
  
  CLEANUP_IMPL(SpriteLayer)
  
  CPP_MANAGED_CONSTRUCTOR_IMPL(SpriteLayer)
    %#ifndef PDG_NO_GUI
      Port* port = GraphicsManager::getSingletonInstance()->getMainPort();
      return createSpriteLayer(port);
    %#else
       return createSpriteLayer();
    %#endif
      END
  
  FUNCTION_IMPL(CreateSpriteLayer)
      METHOD_SIGNATURE("", [object SpriteLayer], 1, ([object Port] port = null)); 
    %#ifndef PDG_NO_GUI
      OPTIONAL_CPP_OBJECT_ARG(1, port, Port, 0);
       SpriteLayer* layer = createSpriteLayer(port);
    %#else
       SpriteLayer* layer = createSpriteLayer();
    %#endif
      RETURN_CPP_OBJECT(layer, SpriteLayer);
      END
  
  FUNCTION_IMPL(CreateSpriteLayerFromSpriterFile)
      METHOD_SIGNATURE("", [object SpriteLayer], 1, (string layerSpriterFilename, boolean addSprites = true, [object Port] port = null)); 
      REQUIRE_ARG_MIN_COUNT(1);
      REQUIRE_STRING_ARG(1, layerSpriterFilename);
      OPTIONAL_BOOL_ARG(2, addSprites, true);
    %#ifndef PDG_NO_GUI
      OPTIONAL_CPP_OBJECT_ARG(3, port, Port, 0);
       SpriteLayer* layer = createSpriteLayerFromSpriterFile(layerSpriterFilename, addSprites, port);
    %#else
       SpriteLayer* layer = createSpriteLayerFromSpriterFile(layerSpriterFilename, addSprites);
    %#endif
      RETURN_CPP_OBJECT(layer, SpriteLayer);
      END
  
  FUNCTION_IMPL(CleanupLayer)
      METHOD_SIGNATURE("", undefined, 1, ([object SpriteLayer] layer)); 
      REQUIRE_ARG_COUNT(1);
      REQUIRE_CPP_OBJECT_ARG(1, layer, SpriteLayer);
      cleanupLayer(layer);
      NO_RETURN;
      END
  
  FUNCTION_IMPL(CreateTileLayer)
      METHOD_SIGNATURE("", [object TileLayer], 1, ([object Port] port = null)); 
    %#ifndef PDG_NO_GUI
      OPTIONAL_CPP_OBJECT_ARG(1, port, Port, 0);
       TileLayer* layer = createTileLayer(port);
    %#else
       TileLayer* layer = createTileLayer();
    %#endif
      RETURN_CPP_OBJECT(layer, TileLayer);
      END
  
  

} // pdg namespace

