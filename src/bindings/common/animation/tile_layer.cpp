// -----------------------------------------------
// tile_layer.cpp
//
// Implementation file for TileLayer bindings
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

#include "layer_lifecycle_macros.h"

// ========================================================================================
//MARK: TileLayer
// ========================================================================================

DECLARE_SYMBOL(tileType);
DECLARE_SYMBOL(facing);

WRAPPER_INITIALIZER_IMPL_FACTORY_ONLY(TileLayer, "createTileLayer", 
  OBJECT_SAVE(cppObj->mEventEmitterScriptObj, obj);
  OBJECT_SAVE(cppObj->mSpriteLayerScriptObj, obj);
  OBJECT_SAVE(cppObj->mTileLayerScriptObj, obj) )
    EXPORT_CLASS_SYMBOLS("TileLayer", TileLayer, , ,
    	// method section
		HAS_EMITTER_METHODS(TileLayer)
		HAS_SPRITE_LAYER_METHODS(TileLayer)
	  %#ifndef PDG_NO_GUI  CR
		HAS_SPRITE_LAYER_GUI_METHODS(TileLayer)
	  %#endif CR
	  %#ifdef PDG_USE_CHIPMUNK_PHYSICS CR
		HAS_SPRITE_LAYER_CHIPMUNK_METHODS(TileLayer)
	  %#endif CR
		HAS_METHOD(TileLayer, "setWorldSize", SetWorldSize)
		HAS_METHOD(TileLayer, "getWorldSize", GetWorldSize)
		HAS_METHOD(TileLayer, "defineTileSet", DefineTileSet)
		HAS_METHOD(TileLayer, "loadMapData", LoadMapData)
		HAS_METHOD(TileLayer, "getMapData", GetMapData)
		HAS_METHOD(TileLayer, "getTileSetImage", GetTileSetImage)
		HAS_METHOD(TileLayer, "getTileSize", GetTileSize)
		HAS_METHOD(TileLayer, "getTileTypeAt", GetTileTypeAt)
		HAS_METHOD(TileLayer, "getTileTypeAndFacingAt", GetTileTypeAndFacingAt)
		HAS_METHOD(TileLayer, "setTileTypeAt", SetTileTypeAt)
		HAS_METHOD(TileLayer, "checkCollision", CheckCollision)
		HAS_SPRITE_LAYER_EVENT_METHODS(TileLayer)
    );
	END
	
EMITTER_BASE_CLASS_IMPL(TileLayer)
%#ifndef PDG_NO_GUI
SPRITE_LAYER_BASE_CLASS_GUI_IMPL(TileLayer)
%#endif
SPRITE_LAYER_BASE_CLASS_IMPL(TileLayer)
%#ifdef PDG_USE_CHIPMUNK_PHYSICS
SPRITE_LAYER_CHIPMUNK_IMPL(TileLayer)
%#endif
METHOD_IMPL(TileLayer, SetWorldSize)
	METHOD_SIGNATURE("", undefined, 4, ([number int] width, [number int] height, boolean repeatingX = false, boolean repeatingY = false));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, width);
    REQUIRE_INT32_ARG(2, height);
    OPTIONAL_BOOL_ARG(3, repeatingX, false);
    OPTIONAL_BOOL_ARG(4, repeatingY, false);
	self->setWorldSize(width, height, repeatingX, repeatingY);
	NO_RETURN;
	END
METHOD_IMPL(TileLayer, GetWorldSize)
	METHOD_SIGNATURE("", [object Rect], 0, ());
    REQUIRE_ARG_COUNT(0);
    Rect r = self->getWorldSize();
	RETURN( RECT2VAL(r) );
	END
METHOD_IMPL(TileLayer, GetTileTypeAt)
	METHOD_SIGNATURE("", number, 0, ([number int] x, [number int] y));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, x);
    REQUIRE_INT32_ARG(2, y);
    uint8 tileType;
	tileType = self->getTileTypeAt(x, y);
   	RETURN_UNSIGNED(tileType);
	END
METHOD_IMPL(TileLayer, GetTileTypeAndFacingAt)
	METHOD_SIGNATURE("", object, 0, ([number int] x, [number int] y));
    REQUIRE_ARG_MIN_COUNT(2);
    REQUIRE_INT32_ARG(1, x);
    REQUIRE_INT32_ARG(2, y);
    uint8 tileType;
	TileLayer::TFacing facing;
	tileType = self->getTileTypeAt(x, y, &facing);
	if (self->mUseFacing || self->mUseFlipping) {
		if (self->mUseFlipping && (!self->mFlipHoriz || !self->mFlipVert)) {
			tileType &= 0x7f;
		} else {
			tileType &= 0x3f;
		}
	}
	OBJECT_REF tileInfo = OBJECT_CREATE_EMPTY(0);
	OBJECT_SET_PROPERTY_VALUE(tileInfo, SYMBOL(tileType), UINT2VAL(tileType));
	OBJECT_SET_PROPERTY_VALUE(tileInfo, SYMBOL(facing), UINT2VAL(facing));
	RETURN_OBJECT(tileInfo);		
	END
METHOD_IMPL(TileLayer, DefineTileSet)
	METHOD_SIGNATURE("", undefined, 5, ([number int] tileWidth, [number int] tileHeight, [object Image*] tiles, boolean hasTransparency = true, boolean flipTiles = false));
    REQUIRE_ARG_MIN_COUNT(3);
    REQUIRE_INT32_ARG(1, tileWidth);
    REQUIRE_INT32_ARG(2, tileHeight);
    REQUIRE_CPP_OBJECT_ARG(3, tiles, Image);
    OPTIONAL_BOOL_ARG(4, hasTransparency, true);
    OPTIONAL_BOOL_ARG(5, flipTiles, false);
	self->defineTileSet(tileWidth, tileHeight, tiles, hasTransparency, flipTiles);
	NO_RETURN;
	END
METHOD_IMPL(TileLayer, LoadMapData)
	METHOD_SIGNATURE("", undefined, 5, ({[object ByteArray]|[object MemBlock]} data, [number int] mapWidth = 0, [number int] mapHeight = 0, [number int] dstX = 0, [number int] dstY = 0));
    REQUIRE_ARG_MIN_COUNT(1);
    OPTIONAL_INT32_ARG(2, mapWidth, 0);
    OPTIONAL_INT32_ARG(3, mapHeight, 0);
    OPTIONAL_INT32_ARG(4, dstX, 0);
    OPTIONAL_INT32_ARG(5, dstY, 0);
    if (mapWidth < 0 || mapHeight < 0 || dstX < 0 || dstY < 0) { THROW_RANGE_ERR("negative tile map dimensions"); RETURN_NULL; }
    if (mapWidth > self->mWorldWidth) {
        THROW_RANGE_ERR("argument 2 (mapWidth) is larger than world width"); RETURN_NULL;
    }
    if (mapWidth > self->mWorldWidth - dstX) {
        THROW_RANGE_ERR("mapWidth + dstX is larger than world width"); RETURN_NULL;
    }
    if (mapHeight > self->mWorldHeight) {
        THROW_RANGE_ERR("argument 3 (mapHeight) is larger than world height"); RETURN_NULL;
    }
    if (mapHeight > self->mWorldHeight - dstY) {
        THROW_RANGE_ERR("mapHeight + dstY is larger than world height"); RETURN_NULL;
    }
    if (!IsUint8Array(ARGV[0]) && !VALUE_IS_MEMBLOCK(ARGV[0])) {
        THROW_TYPE_ERR("argument 1 (data) must be either a Uint8Array or an object of type MemBlock"); RETURN_NULL;
    }
    if (IsUint8Array(ARGV[0])) {
    	size_t bytes = 0;
        const uint8* ptr = nullptr;
        if (!GetUint8ArrayData(ARGV[0], ptr, bytes)) {
            THROW_TYPE_ERR("expected an attached, non-shared Uint8Array"); RETURN_NULL;
        }
        if (bytes > UINT32_MAX) { THROW_RANGE_ERR("byte array exceeds the supported size"); RETURN_NULL; }
    	if (bytes < ((size_t)mapWidth * (size_t)mapHeight)) {
            THROW_RANGE_ERR("argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size"); RETURN_NULL;
    	}
    	self->loadMapData(ptr, mapWidth, mapHeight, dstX, dstY);

	} else {
        if (!VALUE_IS_MEMBLOCK(ARGV[0])) { THROW_TYPE_ERR("expected Uint8Array or MemBlock"); RETURN_NULL; }
    	REQUIRE_CPP_OBJECT_ARG(1, memBlock, MemBlock);
    	if (memBlock->bytes < ((size_t)mapWidth * (size_t)mapHeight)) {
            THROW_RANGE_ERR("argument 1 (data) is insufficient, please check mapWidth and mapHeight against data size"); RETURN_NULL;
    	}
		self->loadMapData((uint8*)memBlock->ptr, mapWidth, mapHeight, dstX, dstY);
    }
	NO_RETURN;
	END
METHOD_IMPL(TileLayer, GetMapData)
	METHOD_SIGNATURE("", [object MemBlock], 4, ([number int] mapWidth = worldWidth, [number int] mapHeight = worldHeight, [number int] srcX = 0, [number int] srcY = 0));
    OPTIONAL_INT32_ARG(1, mapWidth, self->mWorldWidth);
    OPTIONAL_INT32_ARG(2, mapHeight, self->mWorldHeight);
    OPTIONAL_INT32_ARG(3, srcX, 0);
    OPTIONAL_INT32_ARG(4, srcY, 0);
    if (mapWidth > self->mWorldWidth) {
   		THROW_RANGE_ERR("argument 1 (mapWidth) is larger than world width");
    }
    if ((mapWidth + srcX) > self->mWorldWidth) {
   		THROW_RANGE_ERR("mapWidth + srcX is larger than world width");
    }
    if (mapHeight > self->mWorldHeight) {
   		THROW_RANGE_ERR("argument 2 (mapHeight) is larger than world height");
    }
    if ((mapHeight + srcY) > self->mWorldHeight) {
   		THROW_RANGE_ERR("mapHeight + srcY is larger than world height");
    }
	const uint8* dataPtr = self->getMapData(mapWidth, mapHeight, srcX, srcY);
	size_t bufferSize = mapWidth * mapHeight;
	uint8* ptr = (uint8*) std::malloc(bufferSize);
	std::memcpy(ptr, dataPtr, bufferSize);
 	MemBlock* memBlock = new MemBlock((char*)ptr, bufferSize, true);
	RETURN_CPP_OBJECT(memBlock, MemBlock);
	END
METHOD_IMPL(TileLayer, GetTileSetImage)
	METHOD_SIGNATURE("", [object Image*], 0, ());
    REQUIRE_ARG_COUNT(0);
    Image* tiles = self->getTileSetImage();
    RETURN_CPP_OBJECT(tiles, Image);
	END
METHOD_IMPL(TileLayer, GetTileSize)
	METHOD_SIGNATURE("", [object Point], 0, ());
    REQUIRE_ARG_COUNT(0);
    Point size = self->getTileSize();
	RETURN( POINT2VAL(size) );
	END
METHOD_IMPL(TileLayer, SetTileTypeAt)
	METHOD_SIGNATURE("", undefined, 0, ([number int] x, [number int] y, [number uint] t, [number uint] facing = facing_Ignore));
    REQUIRE_ARG_MIN_COUNT(3);
    REQUIRE_INT32_ARG(1, x);
    REQUIRE_INT32_ARG(2, y);
    REQUIRE_UINT32_ARG(3, t);
    OPTIONAL_UINT32_ARG(4, facing, (uint32) TileLayer::facing_Ignore);
	self->setTileTypeAt(x, y, t, (TileLayer::TFacing) facing);
	NO_RETURN;
	END
METHOD_IMPL(TileLayer, CheckCollision)
	METHOD_SIGNATURE("", number, 0, ([object Sprite*] movingSprite, [number uint] alphaThreshold = 128, boolean shortCircuit = true));
    REQUIRE_ARG_MIN_COUNT(1);
    REQUIRE_CPP_OBJECT_ARG(1, movingSprite, Sprite);
    OPTIONAL_UINT32_ARG(2, alphaThreshold, 128);
    OPTIONAL_BOOL_ARG(3, shortCircuit, true);
    uint32 overlapPx = self->checkCollision(movingSprite, alphaThreshold, shortCircuit);
    RETURN_UNSIGNED(overlapPx);
	END
METHOD_IMPL(TileLayer, On)
	METHOD_SIGNATURE("", [object IEventHandler*], 2, ([number int] eventCode, function func));
	REQUIRE_ARG_COUNT(2);
	REQUIRE_INT32_ARG(1, eventCode);
	REQUIRE_FUNCTION_ARG(2, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	long evtCode;
	if (eventCode <= pdg::Sprite::action_CollideWall) {
		evtCode = pdg::eventType_SpriteCollide;
	} else if (eventCode <= pdg::TileLayer::action_FadeOutComplete) {
		evtCode = pdg::eventType_SpriteAnimate;
	} else if (eventCode >= pdg::TileLayer::action_ErasePort) {
		evtCode = pdg::eventType_SpriteLayer;
	} else {
		evtCode = pdg::eventType_SpriteTouch;
	}
	self->addHandler(handler, evtCode);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

// TileLayer convenience event methods
METHOD_IMPL(TileLayer, OnCollideSprite)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnCollideWall)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteCollide);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnOffscreen)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnOnscreen)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnExitLayer)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnAnimationLoop)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptEventHandler* handler = new ScriptEventHandler(func);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnAnimationEnd)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_AnimationEnd);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnFadeComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnFadeInComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeInComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnFadeOutComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptAnimationEventHandler* handler = new ScriptAnimationEventHandler(func, pdg::Sprite::action_FadeOutComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteAnimate);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnMouseEnter)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseEnter);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnMouseLeave)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseLeave);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnMouseDown)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseDown);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnMouseUp)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseUp);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnMouseClick)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptTouchEventHandler* handler = new ScriptTouchEventHandler(func, pdg::Sprite::touch_MouseClick);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteTouch);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnErasePort)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_ErasePort);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnPreDrawLayer)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreDrawLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnPostDrawLayer)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostDrawLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnDrawPortComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_DrawPortComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnAnimationStart)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationStart);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnPreAnimateLayer)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PreAnimateLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnPostAnimateLayer)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_PostAnimateLayer);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnAnimationComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_AnimationComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnLayerFadeInComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeInComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

METHOD_IMPL(TileLayer, OnLayerFadeOutComplete)
	METHOD_SIGNATURE("", [object IEventHandler*], 1, (function func));
	REQUIRE_ARG_COUNT(1);
	REQUIRE_FUNCTION_ARG(1, func);
	ScriptLayerEventHandler* handler = new ScriptLayerEventHandler(func, pdg::SpriteLayer::action_FadeOutComplete);
	if (!handler) RETURN_NULL;
	self->addHandler(handler, pdg::eventType_SpriteLayer);
	RETURN_CPP_OBJECT(handler, IEventHandler);
	END

%#ifdef PDG_USING_JAVASCRIPT_CORE
void CleanupTileLayerScriptObject(JSObjectRef obj) { if(obj)JSObjectSetPrivate(obj,nullptr); }
%#else
void CleanupTileLayerScriptObject(v8::UniquePersistent<v8::Object>& obj) {
    if(!obj.IsEmpty()) {
        auto* isolate=v8::Isolate::GetCurrent();
        auto value=v8::Local<v8::Object>::New(isolate,obj);
        if(auto* wrapper=dynamic_cast<TileLayerWrap*>(v8script::safe_unwrap_object_wrap_or_prototype(isolate,value)))wrapper->forgetCppObject();
        obj.Reset();
    }
}
%#endif

CPP_MANAGED_CONSTRUCTOR_IMPL(TileLayer)
	return new TileLayer();
	END


} // pdg namespace

/* @pdg-schema
{
  "name": "TileInfo",
  "value": {
    "kind": "record",
    "fields": {
      "tileType": {
        "type": "number"
      },
      "facing": {
        "type": "number"
      }
    }
  }
}
*/

/* @pdg-contract
{
  "name": "TileLayer.getTileTypeAndFacingAt",
  "value": {
    "returns": {
      "schema": "TileInfo"
    }
  }
}
*/

// @pdg-member {"name":"TileLayer.loadMapData","native_binding":{"adapter":"TileLayer.loadMapData","browser":{"wrapper":{"constraints":{"mapWidth":{"min":0},"mapHeight":{"min":0},"dstX":{"min":0},"dstY":{"min":0}}}},"binding_name":"_loadMapData"}}


// @pdg-class {"name":"TileLayer","native_binding":{"browser":{"generate":true,"base":"pdg::SpriteLayer"}}}

// Map byte ownership and collision output parameters still require adapters.
// @pdg-member {"name":"TileLayer.checkCollision","native_binding":{"browser":{"generate":false}}}

// @pdg-member {"name":"TileLayer.getMapData","native_binding":{"browser":{"generate":false}}}
